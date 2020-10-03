//=============================================================================
// キャラクターモデル総括処理 [Character.cpp] : NORI
//=============================================================================
#include "Character.h"
#include "inputKeyboard.h"
#include "model.h"
#include "game.h"
#include "fade.h"
#include "map.h"
#include "Xinput.h"
#include "collision.h"
#include "hosso\/Debug_ModelViewer.h"
#include "particle.h"
#include "sound.h"
#include "ModelSet.h"
//=============================================================================
// 静的メンバ変数初期化
//=============================================================================

//=============================================================================
// マクロ
//=============================================================================
#define ADD_ROTATION_SPEED (0.15f)

//====================================================================
//コンストラクタ
//====================================================================
CCharacter::CCharacter(OBJ_TYPE type) :CScene(type)
{
	// 当たり判定のポインタをnullにする
	m_pCollision = nullptr;
}
//====================================================================
//デストラクタ
//====================================================================
CCharacter::~CCharacter()
{
	// 当たり判定の削除
	if (m_pCollision != nullptr)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}
	// 当たり判定の削除
	if (m_pModelSet != nullptr)
	{
		delete m_pModelSet;
		m_pModelSet = nullptr;
	}
}
//====================================================================
//初期化
//====================================================================
HRESULT CCharacter::Init(void)
{
	m_pos				= ZeroVector3;										// 位置
	m_move				= ZeroVector3;										// 移動量
	m_rot				= ZeroVector3;										// 回転
	m_AddArmRot			= ZeroVector3;										//
	m_AddHeadRot		= ZeroVector3;										//
	m_ShotRotDest		= D3DXVECTOR3(0.0f, 0.0f, 0.5f*  D3DX_PI);			// 撃つ向き
	m_rotDest.y			= -0.5f*  D3DX_PI;									// 回転する差分
	m_nLife				= 100;												// 体力
	m_nMaxLife			= 100;												// 最大ＨＰ
	m_HeightBet			= 0.0f;												//
	m_state				= CHARACTER_STATE_NORMAL;							// 状態
	m_bCanJump			= false;											// ジャンプフラグ
	m_bGravity			= true;												//
	m_bDieFlag			= false;											// 死亡フラグ
	m_bMotion			= true;												// モーションするかどうか
	m_bFall				= false;											//
	m_bDraw				= true;												//描画するかどうか
	m_bRotArm			= false;
	// 当たり判定生成
	m_pCollision = CCollision::Create();
	m_pCollision->SetPos(&m_pos);
	m_pCollision->SetPosOld(&m_posold);
	m_pModelSet = CModelSet::CreateModelSet();
	//マトリックス初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	return S_OK;
}
//====================================================================
//終了
//====================================================================
void CCharacter::Uninit(void)
{
	// 当たり判定の削除
	if (m_pCollision != nullptr)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}
}
//====================================================================
//更新
//====================================================================
void CCharacter::Update(void)
{
	//前Fの情報保存
	m_posold = m_pos;
	m_CharacterDirectionOld = m_CharacterDirection;

	//移動に関する計算
	CalcMove();

	//回転に関する計算
	CalcRotation();

	//弾打つ方向を決める
	CalcShotDirection();

	//ステートに応じた処理
	State();


	//下向きながら着地したとき
	if (m_CharacterDirection == DIRECTION::DOWN && GetJump() == true)
	{
		ResetCharacterDirection();
	}

	//当たり判定処理
	//仮想関数
	Collision();

	//モーション処理
	if (m_pModelSet != nullptr)
	{
		if (m_pModelSet->Motion() == true)
		{
			DefaultMotion();
		}
	}
}
//====================================================================
//描画
//====================================================================
void CCharacter::Draw(void)
{
	//描画しない時
	if (!m_bDraw)
	{
		//return
		return;
	}
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//マトリックス計算
	CHossoLibrary::CalcMatrix(&m_mtxWorld, m_pos, m_rot);


	//モデルの描画
	for (unsigned int nCnt = 0; nCnt < m_pModelSet->GetCharacterModelList().size(); nCnt++)
	{
		if (m_bRotArm == true)
		{
			if (nCnt == 2)
			{
				//目標点と現在の差分（回転）
				D3DXVECTOR3 diffHeadRot = m_AddHeadRot - m_pModelSet->GetCharacterModelList()[nCnt]->GetRot();

				//3.14の超過分の初期化（回転）
				CHossoLibrary::CalcRotation(m_pModelSet->GetCharacterModelList()[nCnt]->GetRot().x);

				//3.14の超過分の初期化（回転）
				CHossoLibrary::CalcRotation(diffHeadRot.x);

				//求めた差分だけ追従する計算
				m_pModelSet->GetCharacterModelList()[nCnt]->GetRot().x += diffHeadRot.x * ADD_ROTATION_SPEED;
			}

			else if (nCnt == 3 || nCnt == 4)
			{
				//目標点と現在の差分（回転）
				D3DXVECTOR3 diffArmRot = m_AddArmRot - m_pModelSet->GetCharacterModelList()[nCnt]->GetRot();

				//3.14の超過分の初期化（回転）
				CHossoLibrary::CalcRotation(m_pModelSet->GetCharacterModelList()[nCnt]->GetRot().x);

				//3.14の超過分の初期化（回転）
				CHossoLibrary::CalcRotation(diffArmRot.x);

				//求めた差分だけ追従する計算
				m_pModelSet->GetCharacterModelList()[nCnt]->GetRot().x += diffArmRot.x * ADD_ROTATION_SPEED;
			}
		}

		//描画処理
		m_pModelSet->GetCharacterModelList()[nCnt]->Draw(m_mtxWorld);
	}
}
//====================================================================
//ダメージを受けた時のリアクション
//====================================================================
void CCharacter::DamageReaction()
{
	CManager::GetSound()->Play(CSound::LABEL_SE_BULLET_HIT);
	SetState(CHARACTER_STATE_DAMAGE_FLASHING);
}
//====================================================================
//死亡時のリアクション
//====================================================================
void CCharacter::DeathReaction()
{

}
//====================================================================
//ステートに応じた処理
//====================================================================
void CCharacter::State()
{
	//カウントダウン
	if (m_nStateCnt-- <= 0)
	{
		m_nStateCnt = 0;
	}

	//ステータスの処理
	switch (m_state)
	{
	case CHARACTER_STATE_NORMAL:

		//ダメージを受けるとどんどん赤くなる
		if (m_nLife < m_nMaxLife * 0.5f)
		{
			CCharacter::GetModelSet()->ChangeColor(true, D3DXCOLOR(1.0f - ((float)(m_nLife * 2.0f) / m_nMaxLife), 0.0f, 0.0f, 0.0f));
		}

		break;
	case CHARACTER_STATE_DAMAGE_FLASHING:
		//カウントが0になったら通常に戻る
		if (m_nStateCnt <= 0)
		{
			SetState(CHARACTER_STATE_NORMAL);
			if (GetModelSet()->GetCharacterType() != CModelSet::CHARACTER_TYPE::CHARACTER_TYPE_BOSS_ONE)
			{
				GetModelSet()->SetAllModelDisp(true);
			}
		}

		//点滅処理
		else if (m_nStateCnt % 4 == 0 && m_nStateCnt % 8 != 0)
		{
			if (GetModelSet()->GetCharacterType() != CModelSet::CHARACTER_TYPE::CHARACTER_TYPE_BOSS_ONE)
			{
				GetModelSet()->SetAllModelDisp(false);
			}
		}
		else if (m_nStateCnt % 8 == 0)
		{
			if (GetModelSet()->GetCharacterType() != CModelSet::CHARACTER_TYPE::CHARACTER_TYPE_BOSS_ONE)
			{
				GetModelSet()->SetAllModelDisp(true);
			}
		}

		//ダメージを受けるとどんどん赤くなる
		if (m_nLife < m_nMaxLife * 0.5f)
		{
			CCharacter::GetModelSet()->ChangeColor(true, D3DXCOLOR(1.0f - ((float)(m_nLife * 2.0f) / m_nMaxLife), 0.0f, 0.0f, 0.0f));
		}
		break;
	case CHARACTER_STATE_DAMAGE_RED:

		//時間経過で
		if (m_nStateCnt <= 0)
		{
			//ステートを元に戻す
			SetState(CHARACTER_STATE_NORMAL);
		}
		else
		{
			//赤く点滅
			GetModelSet()->ChangeColor(true, D3DXCOLOR(1.0f, 0.2f, 0.0f, 0.0f));
		}
		break;
	case CHARACTER_STATE_INVINCIBLE:
		GetCollision()->SetCanCollision(false);

		//カウントが0になったら通常に戻す
		if (m_nStateCnt <= 0)
		{
			SetState(CHARACTER_STATE_NORMAL);
		}

		//白く点滅
		else if (m_nStateCnt % 4 == 0 && m_nStateCnt % 8 != 0)
		{
			GetModelSet()->ChangeColor(true, ZeroColor);
		}
		else if (m_nStateCnt % 8 == 0)
		{
			GetModelSet()->ChangeColor(true, FlashColor);
		}
		break;

	case CHARACTER_STATE_DEATH:
		m_pCollision->SetCanCollision(false);

		//カウントが0になった時
		if (m_nStateCnt <= 0)
		{
			//死亡時のリアクション処理
			//派生クラスがオーバーライド
			DeathReaction();

			SetState(CHARACTER_STATE_NONE);
		}

		break;

	default:
		//カウントが0になった時
		if (m_nStateCnt <= 0)
		{
			SetState(CHARACTER_STATE_NORMAL);
		}
		break;
	}

}

//====================================================================
//ステートが変更した瞬間
//どれくらいそのステートが続くか
//オーバーライドで上書きして
//====================================================================
void CCharacter::StateChangeReaction()
{
	switch (m_state)
	{
	case CHARACTER_STATE_NORMAL:
		m_nStateCnt = 0;
		if (m_pCollision)
		{
			m_pCollision->SetCanCollision(true);
		}
		if (GetModelSet()->GetCharacterType() != CModelSet::CHARACTER_TYPE::CHARACTER_TYPE_BOSS_ONE)
		{
			GetModelSet()->SetAllModelDisp(true);
		}
		break;

	case CHARACTER_STATE_DAMAGE_FLASHING:
		m_nStateCnt = 60;

		break;
	case CHARACTER_STATE_DAMAGE_RED:
		m_nStateCnt = 3;

		break;
	case CHARACTER_STATE_INVINCIBLE:
		m_nStateCnt = 120;

		break;
	case CHARACTER_STATE_DEATH:
		if (GetModelSet()->GetCharacterType() != CModelSet::CHARACTER_TYPE::CHARACTER_TYPE_BOSS_ONE)
		{
			GetModelSet()->SetAllModelDisp(true);
		}
		m_nStateCnt = 10;
		break;
	}
}
//====================================================================
//モデルのムーヴ
//====================================================================
void CCharacter::Move(float move, float fdest,float fSpeed)
{
	m_move.x += sinf(move * -D3DX_PI) * fSpeed;
	m_move.z += cosf(move * -D3DX_PI) * fSpeed;
	m_rotDest.y = fdest *  D3DX_PI;
}
//====================================================================
//ポジションの設定
//====================================================================
void CCharacter::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
	m_posold = pos;
	if (m_pCollision)
	{
		m_pCollision->SetPos(&m_pos);
		m_pCollision->SetPosOld(&m_posold);

	}

	CHossoLibrary::CalcMatrix(&m_mtxWorld, pos, m_rot);
}
//====================================================================
//前のポジションの設定
//====================================================================
void CCharacter::SetPotisionOld(D3DXVECTOR3 posOld)
{
	m_posold = posOld;
}
//====================================================================
//ムーブの設定
//====================================================================
void CCharacter::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}
//====================================================================
//回転の設定
//====================================================================
void CCharacter::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//====================================================================
//ダメージを受けた時の処理
//====================================================================
void CCharacter::AddDamage(int Damage)
{
	if (m_state == CHARACTER_STATE::CHARACTER_STATE_NORMAL)
	{
		//ライフを減らす
		GetLife() -= Damage;

		//HPが0になった時
		if (GetLife() <= 0)
		{
			SetLife(0);

			//死亡状態にする
			SetState(CHARACTER_STATE_DEATH);
		}
		else
		{
			//ダメージを受けた時のリアクション
			//オーバーライド
			DamageReaction();
		}
	}
}
//====================================================================
//回転の差分の設定
//====================================================================
void CCharacter::SetRotDest(D3DXVECTOR3 rotDest)
{
	m_rotDest = rotDest;
}
//====================================================================
//体力の設定
//====================================================================
void CCharacter::SetLife(int Life)
{
	m_nLife = Life;
}
//====================================================================
//最大ＨＰ設定
//====================================================================
void CCharacter::SetMaxLife(int nMaxLife)
{
	m_nMaxLife = nMaxLife;
	SetLife(nMaxLife);
}
//====================================================================
//ジャンプフラグの設定
//====================================================================
void CCharacter::SetJump(bool bJump)
{
	m_bCanJump = bJump;
}
//====================================================================
//キャラ状態の設定
//====================================================================
void CCharacter::SetState(CHARACTER_STATE state)
{
	if (m_state != state)
	{
		m_state = state;
		m_nStateCnt = 0;
		GetModelSet()->ChangeColor(false, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

		//ステートが変更した時のリアクション
		StateChangeReaction();
	}
}
//====================================================================
//ステートのカウント設定
//====================================================================
void CCharacter::SetStateCount(int nCntState)
{
	m_nStateCnt = nCntState;
}
//====================================================================
//マトリックスの設定
//====================================================================
void CCharacter::SetMtxWorld(D3DXMATRIX mtxWorld)
{
	m_mtxWorld = mtxWorld;
}
//====================================================================
//回転の差分の取得
//====================================================================
D3DXVECTOR3 &CCharacter::GetRotDest(void)
{
	return m_rotDest;
}
//====================================================================
//キャラクターの状態の取得
//====================================================================
CCharacter::CHARACTER_STATE CCharacter::GetCharacterState(void)
{
	return m_state;
}
//====================================================================
//モデルの設定情報取得
//====================================================================
CModelSet * CCharacter::GetModelSet(void)
{
	return m_pModelSet;
}
//====================================================================
//ポジションの取得
//====================================================================
D3DXVECTOR3 &CCharacter::GetPosition(void)
{
	return m_pos;
}
//====================================================================
//前のポジションの取得
//====================================================================
D3DXVECTOR3 &CCharacter::GetPositionOld(void)
{
	return m_posold;
}
//====================================================================
//ムーブの取得
//====================================================================
D3DXVECTOR3 &CCharacter::GetMove(void)
{
	return m_move;
}
//====================================================================
//回転の取得
//====================================================================
D3DXVECTOR3 &CCharacter::GetRot(void)
{
	return m_rot;
}
//====================================================================
//体力の取得
//====================================================================
int &CCharacter::GetLife(void)
{
	return m_nLife;
}

//====================================================================
//ジャンプの取得
//====================================================================
bool CCharacter::GetJump(void)
{
	return m_bCanJump;
}
//====================================================================
//重力の取得
//====================================================================
bool CCharacter::GetGravity(void)
{
	return m_bGravity;
}
//====================================================================
//マトリックスの取得
//====================================================================
D3DXMATRIX *CCharacter::GetMtxWorld(void)
{
	return &m_mtxWorld;
}
//====================================================================
//撃つ向きの取得
//====================================================================
D3DXVECTOR3 CCharacter::GetShotDirection(void)
{
	return m_ShotRotDest;
}
//====================================================================
//色変更
//====================================================================
//void CCharacter::ChangeColor(bool ColorChangeFlag, D3DXCOLOR AddColor)
//{
//	//モデルの色変更
//	for (unsigned int nCnt = 0; nCnt < m_vModelList.size(); nCnt++)
//	{
//		// 加算する色の設定
//		m_vModelList[nCnt]->SetAddColor(AddColor);
//		// 色変更フラグの設定
//		m_vModelList[nCnt]->SetColorChangeFlag(ColorChangeFlag);
//	}
//}
//====================================================================
//全部のモデルのDisp情報設定
//====================================================================
//void CCharacter::SetAllModelDisp(bool bDisp)
//{
//	//モデル数分
//	for (unsigned int nCnt = 0; nCnt < m_vModelList.size(); nCnt++)
//	{
//		if (m_vModelList[nCnt])
//		{
//			m_vModelList[nCnt]->SetDisp(bDisp);
//		}
//	}
//}
//====================================================================
//強制的に更新
//====================================================================
void CCharacter::ForcedUpdate()
{
}
//====================================================================
//キャラクターの向き設定しなおし
//====================================================================
void CCharacter::ResetCharacterDirection()
{
	if (GetRot().y > 0)
	{
		m_ShotRotDest.z = D3DX_PI * 0.5f;
		SetCharacterDirection(DIRECTION::LEFT);
	}
	else if (GetRot().y < 0)
	{
		m_ShotRotDest.z = -D3DX_PI * 0.5f;
		SetCharacterDirection(DIRECTION::RIGHT);
	}
}
//====================================================================
//デバッグ
//====================================================================
void CCharacter::DebugInfo(void)
{
	//CDebug_ModelViewer::OffsetViewer(m_vModelList);

	char aTreeName[MAX_TEXT] = {};
	sprintf(aTreeName, "CharacterInfo [%d]", CScene::GetID());

	if (ImGui::TreeNode(aTreeName))
	{
		ImGui::Text("m_pos [%.2f %.2f %.2f]", m_pos.x, m_pos.y, m_pos.z); ImGui::SameLine();
		ImGui::Text("m_move [%.2f %.2f %.2f]", m_move.x, m_move.y, m_move.z);

		ImGui::Text("m_posfall [%.2f %.2f %.2f]", m_posfall.x, m_posfall.y, m_posfall.z); ImGui::SameLine();
		ImGui::Text("m_ShotRotDest [%.2f %.2f %.2f]", m_ShotRotDest.x, m_ShotRotDest.y, m_ShotRotDest.z);

		ImGui::Text("m_rot [%.2f %.2f %.2f]", m_rot.x, m_rot.y, m_rot.z); ImGui::SameLine();
		ImGui::Text("m_rotDest [%.2f %.2f %.2f]", m_rotDest.x, m_rotDest.y, m_rotDest.z);

		ImGui::Text("m_nLife [%d]", m_nLife); ImGui::SameLine();
		ImGui::Text("m_state [%d]", m_state); ImGui::SameLine();
		ImGui::Text("m_nStateCnt [%d]", m_nStateCnt);
		//ImGui::Text("m_CharaType [%d]", m_CharaType); ImGui::SameLine();
		ImGui::Text("m_CharacterDirection [%d]", m_CharacterDirection);

		ImGui::Text("m_bGravity [%d]", m_bGravity); ImGui::SameLine();
		ImGui::Text("m_bCanJump [%d]", m_bCanJump); ImGui::SameLine();
		ImGui::Text("m_bDieFlag [%d]", m_bDieFlag); ImGui::SameLine();
		ImGui::Text("m_bDraw [%d]", m_bDraw);

		if (ImGui::TreeNode("MotionInfo"))
		{
			//ImGui::Text("m_MotionType [%d]", m_MotionType); ImGui::SameLine();
			//ImGui::Text("m_MotionOld [%d]", m_MotionOld);
			//ImGui::Text("m_CntKeySet [%d]", m_CntKeySet); ImGui::SameLine();
			//ImGui::Text("m_Fram [%d]", m_Fram);

			ImGui::TreePop();
		}
		ImGui::TreePop();

		if (m_pCollision)
		{
			m_pCollision->ShowDebugInfo();
		}
	}


}
//====================================================================
//弾の撃つ方向設定
//====================================================================
void CCharacter::CalcShotDirection()
{
	//撃つ向き
	if (m_CharacterDirection == DIRECTION::LEFT)
	{
		m_ShotRotDest.z = 0.5f*D3DX_PI;
		m_AddHeadRot.x = 0.5f;
		m_AddArmRot.x = 0.5f* D3DX_PI;

	}
	else if (m_CharacterDirection == DIRECTION::RIGHT)
	{
		m_ShotRotDest.z = -0.5f*D3DX_PI;
		m_AddHeadRot.x = 0.5f;
		m_AddArmRot.x = 0.5f* D3DX_PI;
	}
	else if (m_CharacterDirection == DIRECTION::UP)
	{
		m_ShotRotDest.z = 0.0f*D3DX_PI;
		m_AddHeadRot.x = 1.0f;
		m_AddArmRot.x = 1.0f* D3DX_PI;
	}
	else if (m_CharacterDirection == DIRECTION::DOWN)
	{
		m_ShotRotDest.z = D3DX_PI;
		m_AddHeadRot.x = -0.5f;
		m_AddArmRot.x = -0.3f* D3DX_PI;
	}
}
//====================================================================
//移動の計算
//====================================================================
void CCharacter::CalcMove()
{
	//慣性の抵抗
	m_move.x += (0 - m_move.x)* 0.4f;
	m_move.z += (0 - m_move.z)* 0.4f;
	m_move.y += m_move.y * -0.1f;

	//重力が効くとき
	if (m_bGravity == true)
	{
		//重力加算
		m_move.y -= 0.5f;
	}

	//移動処理
	m_pos += m_move;


	//捕虜関連
	if (m_bFall == false)
	{
		m_posfall = m_pos;
	}
	if (m_pos.y <= -100 && m_bFall == true)
	{
		if (m_pos.x < m_posfall.x)
		{
			m_pos.x = m_posfall.x + 50;
		}
		else
		{
			m_pos.x = m_posfall.x - 50;
		}
		m_pos.y = m_posfall.y + 30;
		m_bFall = false;
	}
}

//====================================================================
//回転の計算
//====================================================================
void CCharacter::CalcRotation()
{

	//目標点と現在の差分（回転）
	float diffRot = m_rotDest.y - m_rot.y;

	//3.14の超過分の初期化（回転）
	CHossoLibrary::CalcRotation(m_rot.y);
	CHossoLibrary::CalcRotation(diffRot);

	//求めた差分だけ追従する計算
	m_rot.y += diffRot * ADD_ROTATION_SPEED;
}
//====================================================================
//当たり判定の処理
//====================================================================
void CCharacter::Collision()
{
	// マップのポインタ取得
	CMap *pMap;
	pMap = CManager::GetBaseMode()->GetMap();

	// マップモデルが存在した時して当たり判定が存在する時
	if (pMap && m_pCollision &&m_pModelSet)
	{
		m_pCollision->SetPos(&m_pos);
		m_pCollision->SetPosOld(&m_posold);

		//コリジョンの高さ設定
		m_pCollision->SetHeight(m_pModelSet->GetCharacterModelList()[0]->GetPosition().y);

		// 障害物の判定とレイの判定
		if (m_pCollision->ForPlayer_ObstacleCollision() || m_pCollision->RayBlockCollision(pMap, (m_pModelSet->GetCharacterModelList()[0]->GetMatrix() )))
		{
			// ジャンプすることを承認する
			SetJump(true);
			m_bFall = false;
		}
		else
		{
			// ジャンプすることを承認しない
			SetJump(false);
			m_bFall = true;
		}
	}


}
//====================================================================
//描画の範囲内かどうか確認
//====================================================================
bool CCharacter::CheckDrawRange()
{
	//描画するかどうか
	m_bDraw = CManager::GetRenderer()->CheckScreenRange(m_pos);

	//描画の範囲内の場合
	if (m_bDraw)
	{
		//mullcheck
		if (m_pCollision)
		{
			//当たり判定可能
			m_pCollision->SetCanCollision(true);
		}
	}
	else
	{
		//nullcheck
		if (m_pCollision)
		{
			//当たり判定不可
			m_pCollision->SetCanCollision(false);
		}
	}
	//return
	return m_bDraw;
}

//====================================================================
//向き取得
//====================================================================
DIRECTION &CCharacter::GetCharacterDirection(void)
{
	return m_CharacterDirection;
}
//====================================================================
//1F前の向き取得
//====================================================================
DIRECTION & CCharacter::GetCharacterDirectionOld(void)
{
	return m_CharacterDirectionOld;
}
//====================================================================
//腰の高さの取得
//====================================================================
float CCharacter::GetHeightBet(void)
{
	return m_HeightBet;
}
//====================================================================
//重力の設定
//====================================================================
void CCharacter::SetGravity(bool gravity)
{
	m_bGravity = gravity;
}
//====================================================================
//キャラクターの向き
//====================================================================
void CCharacter::SetCharacterDirection(DIRECTION direction)
{
	m_CharacterDirection = direction;
}
//====================================================================
//撃つ向きの設定
//====================================================================
void CCharacter::SetShotDirection(D3DXVECTOR3 direction)
{
	m_ShotRotDest = direction;
}
//====================================================================
//腕が回転するか
//====================================================================
void CCharacter::SetRotArm(bool use)
{
	m_bRotArm = use;
}
//====================================================================
//指定した番数のモデルの回転計算
//====================================================================
void CCharacter::SetArmCalculation(int nCnt)
{
}
