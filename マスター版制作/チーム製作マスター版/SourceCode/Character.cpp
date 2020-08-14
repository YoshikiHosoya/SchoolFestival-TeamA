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

//=============================================================================
// 静的メンバ変数初期化
//=============================================================================
std::vector<CCharacter::MOTION*> CCharacter::m_CharacterMotion = {};

//オフセットの読み込みファイル
char *CCharacter::m_LoadOffsetFileName[CHARACTER_TYPE_MAX] =
{
	{ "data/Load/Player/PlayerOffset.txt"},
	{"data/Load/Enemy/EnemyOffset.txt"},
	{"data/Load/Prisoner/PrisonerOffset.txt"},
	{"data/Load/Boss/BossOffset.txt"},
	{ "data/Load/DragonNosuke/Boss_OneOffset.txt" },
};
//モーションの読み込みファイル
char *CCharacter::m_LoadMotionFileName[CHARACTER_MOTION_MAX] =
{
	{ "data/Load/Player/Motion/Neutral.txt" },
	{ "data/Load/Player/Motion/Walk.txt" },
	{ "data/Load/Player/Motion/Attack.txt" },
	{ "data/Load/Player/Motion/Grenade.txt" },
	{ "data/Load/Player/Motion/Jump.txt" },
	{ "data/Load/Player/Motion/JumpStop.txt" },
	{ "data/Load/Player/Motion/Shoot.txt" },
	{ "data/Load/Player/Motion/Squat.txt" },
	{ "data/Load/Player/Motion/SquatStop.txt" },
	{ "data/Load/Player/Motion/Dead.txt" },
	{ "data/Load/Enemy/Motion/EnemyNeutral.txt" },
	{ "data/Load/Enemy/Motion/EnemyWalk.txt" },
	{ "data/Load/Enemy/Motion/EnemySquatStop.txt" },
	{ "data/Load/Enemy/Motion/EnemyDead_1.txt" },
	{ "data/Load/Enemy/Motion/EnemyDead_2.txt" },
	{ "data/Load/Enemy/Motion/EnemyGrenade.txt" },
	{ "data/Load/Enemy/Motion/EnemyJumpAttack.txt" },
	{ "data/Load/Boss/Motion/Neutral.txt" },
	{ "data/Load/Prisoner/Motion/PrisonerStay.txt" },
	{ "data/Load/Prisoner/Motion/PrisonerRelease.txt" },
	{ "data/Load/Prisoner/Motion/PrisonerRun.txt" },
	{ "data/Load/Prisoner/Motion/PrisonerSalute.txt" },
	{ "data/Load/Prisoner/Motion/PrisonerFall.txt" },
	{ "data/Load/Prisoner/Motion/PrisonerSkip.txt" },
};


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

	//nullcheck
	if (!m_vModelList.empty())
	{
		//パーツ数分
		for (size_t nCnt = 0; nCnt < m_vModelList.size(); nCnt++)
		{
			//メモリ開放
			delete m_vModelList[nCnt];
			m_vModelList[nCnt] = nullptr;
		}
		//配列を空にする
		m_vModelList.clear();
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
	m_Life				= 50;												// 体力
	m_HeightBet			= 0.0f;												//
	m_state				= CHARACTER_STATE_NORMAL;							// 状態
	m_bCanJump				= false;											// ジャンプフラグ
	m_bGravity			= true;												//
	m_bDieFlag			= false;											// 死亡フラグ
	m_bMotion			= true;												// モーションするかどうか
	m_bFall				= false;											//
	m_bDraw				= false;											//描画するかどうか

	// 当たり判定生成
	m_pCollision = CCollision::Create();

	//マトリックス初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	return S_OK;
}
//====================================================================
//終了
//====================================================================
void CCharacter::Uninit(void)
{

}
//====================================================================
//更新
//====================================================================
void CCharacter::Update(void)
{
	//描画の範囲内かチェック
	CheckDrawRange();

	if (!m_bDraw)
	{
		return;
	}

	//前Fの情報保存
	m_posold = m_pos;
	m_MotionOld = m_MotionType;
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
	Motion();
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
	for (unsigned int nCnt = 0; nCnt < m_vModelList.size(); nCnt++)
	{
		if (m_CharaType != CHARACTER_TYPE_BOSS_ONE)
		{
			if (nCnt == 2)
			{
				//目標点と現在の差分（回転）
				D3DXVECTOR3 diffHeadRot = m_AddHeadRot - m_vModelList[nCnt]->GetRot();

				//3.14の超過分の初期化（回転）
				CHossoLibrary::CalcRotation(m_vModelList[nCnt]->GetRot().x);

				//3.14の超過分の初期化（回転）
				CHossoLibrary::CalcRotation(diffHeadRot.x);

				//求めた差分だけ追従する計算
				m_vModelList[nCnt]->GetRot().x += diffHeadRot.x * ADD_ROTATION_SPEED;
			}
			else if (nCnt == 3 || nCnt == 4)
			{
				//目標点と現在の差分（回転）
				D3DXVECTOR3 diffArmRot = m_AddArmRot - m_vModelList[nCnt]->GetRot();

				//3.14の超過分の初期化（回転）
				CHossoLibrary::CalcRotation(m_vModelList[nCnt]->GetRot().x);

				//3.14の超過分の初期化（回転）
				CHossoLibrary::CalcRotation(diffArmRot.x);

				//求めた差分だけ追従する計算
				m_vModelList[nCnt]->GetRot().x += diffArmRot.x * ADD_ROTATION_SPEED;
			}
		}

		//描画処理
		m_vModelList[nCnt]->Draw(m_mtxWorld);

		/*if (nCnt == 2 || nCnt == 3 || nCnt == 4)
		{
			m_vModelList[nCnt]->SetRot(m_vModelList[nCnt]->GetRot());
		}*/
	}
}
//====================================================================
//ダメージを受けた時のリアクション
//====================================================================
void CCharacter::DamageReaction()
{
	SetState(CHARACTER_STATE_DAMAGE);
}
//====================================================================
//死亡時のリアクション
//====================================================================
void CCharacter::DeathReaction()
{
	// 当たり判定の削除
	if (m_pCollision != nullptr)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}
}
//====================================================================
//ステートに応じた処理
//====================================================================
void CCharacter::State()
{
	//カウントダウン
	m_nStateCnt--;

	//ステータスの処理
	switch (m_state)
	{
	case CHARACTER_STATE_NORMAL:
		break;
	case CHARACTER_STATE_DAMAGE:
		//カウントが0になったら通常に戻る
		if (m_nStateCnt <= 0)
		{
			SetState(CHARACTER_STATE_NORMAL);
		}

		//点滅処理
		else if (m_nStateCnt % 4 == 0 && m_nStateCnt % 8 != 0)
		{
			ChangeColor(true, D3DXCOLOR(0.0f, 0.0f, 0.0f, -1.0f));
		}
		else if (m_nStateCnt % 8 == 0)
		{
			ChangeColor(true, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
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
			ChangeColor(true, D3DXCOLOR(1.0f, 0.2f, 0.0f, 0.0f));
		}
		break;
	case CHARACTER_STATE_INVINCIBLE:
		//カウントが0になったら通常に戻す
		if (m_nStateCnt <= 0)
		{
			SetState(CHARACTER_STATE_NORMAL);
		}

		//白く点滅
		else if (m_nStateCnt % 4 == 0 && m_nStateCnt % 8 != 0)
		{
			ChangeColor(true, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		}
		else if (m_nStateCnt % 8 == 0)
		{
			ChangeColor(true, D3DXCOLOR(0.6f, 0.6f, 0.6f, 0.0f));
		}
		break;

	case CHARACTER_STATE_DEATH:
		//カウントが0になった時
		if (m_nStateCnt <= 0)
		{
			//死亡時のリアクション処理
			//派生クラスがオーバーライド
			DeathReaction();
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
		break;

	case CHARACTER_STATE_DAMAGE:
		m_nStateCnt = 60;

		break;
	case CHARACTER_STATE_DAMAGE_RED:
		m_nStateCnt = 3;

		break;
	case CHARACTER_STATE_INVINCIBLE:
		m_nStateCnt = 120;

		break;
	case CHARACTER_STATE_DEATH:
		m_nStateCnt = 10;

		//血のエフェクト
		CParticle::CreateFromText(GetPosition(), GetShotDirection(), CParticleParam::EFFECT_BLOOD);

		break;
	}
}
//====================================================================
//モデルのムーヴ
//====================================================================
void CCharacter::Move(float move, float fdest)
{
	m_move.x += sinf(move * -D3DX_PI) * 1.0f;
	m_move.z += cosf(move * -D3DX_PI) * 1.0f;
	m_rotDest.y = fdest *  D3DX_PI;
}
//====================================================================
//ポジションの設定
//====================================================================
void CCharacter::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
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
	//ライフを減らす
	GetLife() -= Damage;

	//HPが0になった時
	if (GetLife() <= 0)
	{
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
	m_Life = Life;
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
		ChangeColor(false, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

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
//モーションの設定
//====================================================================
void CCharacter::SetMotion(CHARACTER_MOTION_STATE type)
{
	if (m_MotionType != type)
	{
		m_Fram = 0;
		m_CntKeySet = 0;
	}
	m_MotionType = type;
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
	return m_Life;
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
//モーション情報の取得
//====================================================================
CCharacter::MOTION *CCharacter::GetCharacterMotion(CHARACTER_MOTION_STATE type)
{
	return m_CharacterMotion[type];
}
//====================================================================
//オフセットのファイル取得
//====================================================================
char * CCharacter::GetOffsetFileName(CHARACTER_TYPE type)
{
	return m_LoadOffsetFileName[type];
}
//====================================================================
//モーションのファイル取得
//====================================================================
char * CCharacter::GetMotionFileName(CHARACTER_MOTION_STATE motionstate)
{
	return m_LoadMotionFileName[motionstate];
}
//====================================================================
//色変更
//====================================================================
void CCharacter::ChangeColor(bool ColorChangeFlag, D3DXCOLOR AddColor)
{
	//モデルの色変更
	for (unsigned int nCnt = 0; nCnt < m_vModelList.size(); nCnt++)
	{
		// 加算する色の設定
		m_vModelList[nCnt]->SetAddColor(AddColor);
		// 色変更フラグの設定
		m_vModelList[nCnt]->SetColorChangeFlag(ColorChangeFlag);
	}
}
//====================================================================
//モーションのロード
//====================================================================
void CCharacter::LoadMotion(void)
{
	//ファイルポイント
	FILE *pFile;
	int nCntModel = 0;		//モデルのカウント
	int nCntKeySet = 0;		//フーレームの分割数
	int nCntKey = 0;
	char cReadText[128];	//文字として読み取り用
	char cHeadText[128];	//比較する用
	char cDie[128];			//不要な文字

	KEY *key;
	KEY_INFO *key_info;

	MOTION *pMotion;
	for (int nCnt = 0; nCnt < CHARACTER_MOTION_MAX; nCnt++)
	{
		pFile = fopen(m_LoadMotionFileName[nCnt], "r");//ファイルを開く
		//あいたら
		if (pFile != NULL)
		{
			pMotion = new MOTION;
			m_CharacterMotion.emplace_back(pMotion);
			//スクリプトが来るまでループ
			while (strcmp(cHeadText, "SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);	//一文を読み込む
				sscanf(cReadText, "%s", &cHeadText);		//比較用テキストに文字を代入
			}
			//スクリプトだったら
			if (strcmp(cHeadText, "SCRIPT") == 0)
			{
				//フレーム分割数の初期化
				nCntKeySet = 0;
				//エンドスクリプトが来るまでループ
				while (strcmp(cHeadText, "END_SCRIPT") != 0)
				{
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s", &cHeadText);

					//ループするかどうかの情報読み込み
					if (strcmp(cHeadText, "LOOP") == 0)
					{
						sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_CharacterMotion[nCnt]->nLoop);
					}
					else if (strcmp(cHeadText, "NUM_KEY") == 0)
					{
						sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_CharacterMotion[nCnt]->nNumKey);
					}
					else if (strcmp(cHeadText, "KEYSET") == 0)
					{
						key_info = new KEY_INFO;
						m_CharacterMotion[nCnt]->key_info.emplace_back(key_info);
						nCntKey = 0;

						while (strcmp(cHeadText, "END_KEYSET") != 0)
						{
							fgets(cReadText, sizeof(cReadText), pFile);
							sscanf(cReadText, "%s", &cHeadText);

							if (strcmp(cHeadText, "FRAME") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_CharacterMotion[nCnt]->key_info[nCntKeySet]->nFram);
							}
							//高さ
							else if (strcmp(cHeadText, "HEIGHT") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDie, &cDie, &m_CharacterMotion[nCnt]->key_info[nCntKeySet]->fHeight);
							}
							//キーだったら
							else if (strcmp(cHeadText, "KEY") == 0)
							{
								//メモリ確保
								key = new KEY;

								//配列に追加
								m_CharacterMotion[nCnt]->key_info[nCntKeySet]->key.emplace_back(key);

								sscanf(cReadText, "%s %s %s %f %f %f", &cDie, &cDie, &cDie,
									&m_CharacterMotion[nCnt]->key_info[nCntKeySet]->key[nCntKey]->rot.x,
									&m_CharacterMotion[nCnt]->key_info[nCntKeySet]->key[nCntKey]->rot.y,
									&m_CharacterMotion[nCnt]->key_info[nCntKeySet]->key[nCntKey]->rot.z);

								//キー加算
								nCntKey++;
							}
						}
						nCntKeySet++;
					}
				}

			}

			//debug
			std::cout << "Motion Load - " << nCnt << m_LoadMotionFileName[nCnt] << NEWLINE;

			//ファイルを閉じる
			fclose(pFile);
		}
		else
		{
			//debug
			std::cout << "LOAD FAILED!!! MotionFile - " << nCnt << m_LoadMotionFileName[nCnt] << NEWLINE;

			//失敗
			MessageBox(NULL, "モーション読み込み失敗", m_LoadMotionFileName[nCnt], MB_OK | MB_ICONHAND);
		}
	}
}
//====================================================================
//モーション
//====================================================================
void CCharacter::Motion(void)
{
	D3DXVECTOR3 Difrot;
	float Difpos;
		if (m_MotionType != m_MotionOld)
		{
			m_Fram = 0;
			m_CntKeySet = 0;
		}
	if (m_MotionType != -1)
	{
		for (unsigned int nCnt = 0; nCnt < m_vModelList.size(); nCnt++)
		{
			if (m_Fram == 0)
			{
				if (m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->nFram != 0)
				{
					//移動量ROTの計算-------------------------------------■■■■■
					Difrot = (m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->key[nCnt]->rot - m_vModelList[nCnt]->GetRot());
					Difpos = m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->fHeight - m_vModelList[0]->GetPosition().y;
					if (Difrot.y > D3DX_PI)
					{
						Difrot.y -= D3DX_PI * 2;
					}
					else if (Difrot.y < -D3DX_PI)
					{
						Difrot.y += D3DX_PI * 2;
					}

					if (Difrot.x > D3DX_PI)
					{
						Difrot.x -= D3DX_PI * 2;
					}
					else if (Difrot.x < -D3DX_PI)
					{
						Difrot.x += D3DX_PI * 2;
					}

					m_rotBET[nCnt] = Difrot / (float)m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->nFram;

					m_HeightBet = Difpos / (float)m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->nFram;
					//----------------------------------------------------■■■■■
				}
				else
				{
					//m_vModelList[nCnt]->GetPosition() = m_CharacterMotion[m_MotionType].key_info[m_CntKeySet].key[nCnt].pos;
					//m_vModelList[nCnt]->GetRot()		 = m_CharacterMotion[m_MotionType].key_info[m_CntKeySet].key[nCnt].rot;
					//posBET[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					//rotBET[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
			}
			//フレーム移動--------------------------------------------■■■■■
			if (m_Fram <= m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->nFram)
			{
				//	m_vModelList[nCnt]->SetPosition(m_vModelList[nCnt]->GetPosition() + posBET[nCnt]);
				m_vModelList[nCnt]->SetRot(m_vModelList[nCnt]->GetRot() + m_rotBET[nCnt]);
				if (nCnt == 0)
				{
				m_vModelList[0]->GetPosition().y += m_HeightBet;
				}

				if (m_vModelList[nCnt]->GetRot().y > D3DX_PI)
				{
					m_vModelList[nCnt]->SetRot(m_vModelList[nCnt]->GetRot() - D3DXVECTOR3(0.0f, D3DX_PI * 2.0f, 0.0f));
				}
				else if (m_vModelList[nCnt]->GetRot().y < -D3DX_PI)
				{
					m_vModelList[nCnt]->SetRot(m_vModelList[nCnt]->GetRot() + D3DXVECTOR3(0.0f, D3DX_PI * 2.0f, 0.0f));
				}
				if (m_vModelList[nCnt]->GetRot().x > D3DX_PI)
				{
					m_vModelList[nCnt]->SetRot(m_vModelList[nCnt]->GetRot() - D3DXVECTOR3(D3DX_PI * 2.0f, 0.0f, 0.0f));
				}
				else if (m_vModelList[nCnt]->GetRot().x < -D3DX_PI)
				{
					m_vModelList[nCnt]->SetRot(m_vModelList[nCnt]->GetRot() + D3DXVECTOR3(D3DX_PI * 2.0f, 0.0f, 0.0f));
				}
			}
			//--------------------------------------------------------■■■■■
		}
		if (m_Fram == m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->nFram)
		{
			m_CntKeySet++;
			m_Fram = 0;

			//キーセット数が規定値と同じになったら--------------------■■■■■
			if (m_CntKeySet == m_CharacterMotion[m_MotionType]->nNumKey)
			{
				//ループしないとき------------------------------------■■■■■
				if (m_CharacterMotion[m_MotionType]->nLoop == 0)
				{
					if (DefaultMotion())
					{
						m_CntKeySet = 0;
						m_Fram = m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->nFram;
					}
				}
				//ループするとき--------------------------------------■■■■■
				else if (m_CharacterMotion[m_MotionType]->nLoop == 1)
				{
					m_CntKeySet = 0;
				}
			}
		}
		//フレーム数が規定値と同じではないとき------------------------■■■■■
		else
		{
			//モーションをするとき
			if (m_bMotion)
			{
				m_Fram++;
			}
		}
	}
	else
	{
		m_Fram = 0;
		m_CntKeySet = 0;
	}
}
//====================================================================
//オフセットの読み込み
//====================================================================
void CCharacter::LoadOffset(CHARACTER_TYPE nType)
{
	char cReadText[1080];	//文字として読み取り用
	char cHeadText[1080];	//比較する用
	char cDie[1080];		//不要な文字
	int nCnt = 0;
	FILE *pFile;

	cReadText[0] = '\0';
	cHeadText[0] = '\0';
	D3DXVECTOR3 pos;
	int nIdxParent;			//親のインデックス
	int nIdx;				//モデルのインデックス
	int type;

	pFile = fopen(m_LoadOffsetFileName[nType], "r");
	if (pFile != NULL)
	{
		while (strcmp(cHeadText, "MODEL_OFFSET_END") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile);
			sscanf(cReadText, "%s", &cHeadText);
			//配置するモデルの最大数の読み込み
			if (strcmp(cHeadText, "SET_START") == 0)
			{
				//END_SETが来るまでループ
				while (strcmp(cHeadText, "SET_END") != 0)
				{
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s", &cHeadText);
					//MODEL_TYPEだったら
					if (strcmp(cHeadText, "MODEL_TYPE") == 0)
					{
						sscanf(cReadText, "%s %s %d",
							&cDie, &cDie,
							&type);
					}
					//IDXだったら
					else if (strcmp(cHeadText, "INDEX") == 0)
					{
						sscanf(cReadText, "%s %s %d",
							&cDie, &cDie,
							&nIdx);
					}
					//PARENTだったら
					else if (strcmp(cHeadText, "PARENT") == 0)
					{
						sscanf(cReadText, "%s %s %d",
							&cDie, &cDie,
							&nIdxParent);
					}
					//POSだったら
					else if (strcmp(cHeadText, "POS") == 0)
					{
						sscanf(cReadText, "%s %s %f %f %f",
							&cDie, &cDie,
							&pos.x,
							&pos.y,
							&pos.z);
					}
					//SET_ENDが来たら作成し追加
					else if (strcmp(cHeadText, "SET_END") == 0)
					{
						CModel *pModel = CModel::Create(type, nIdx);
						pModel->SetPosition(pos);
						pModel->SetParentIdx(nIdxParent);
						if (nIdxParent == -1)
						{
							pModel->SetParent(NULL);
						}
						else
						{
							pModel->SetParent(m_vModelList[nIdxParent]);
						}
						m_vModelList.emplace_back(pModel);
					}
				}
			}
		}

		fclose(pFile);
	}
	else
	{

	}

}
//====================================================================
//強制的に更新
//====================================================================
void CCharacter::ForcedUpdate()
{
	//モデル数分繰り返す
	for (size_t nCntKey = 0; nCntKey < m_vModelList.size(); nCntKey++)
	{
		//モーションの回転の決定先取得
		m_vModelList[nCntKey]->SetRot(m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->key[nCntKey]->rot);
	}

	m_vModelList[0]->GetPosition().y = m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->fHeight;
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
//開放
//====================================================================
void CCharacter::CharacterUnLoad(void)
{
	if (!m_CharacterMotion.empty())
	{
		for (size_t nCnt = 0; nCnt < m_CharacterMotion.size(); nCnt++)
		{
			if (!m_CharacterMotion[nCnt]->key_info.empty())
			{
				for (size_t nCntinfo = 0; nCntinfo < m_CharacterMotion[nCnt]->key_info.size(); nCntinfo++)
				{
					if (!m_CharacterMotion[nCnt]->key_info[nCntinfo]->key.empty())
					{
						for (size_t nCntkey = 0; nCntkey < m_CharacterMotion[nCnt]->key_info[nCntinfo]->key.size(); nCntkey++)
						{
							delete m_CharacterMotion[nCnt]->key_info[nCntinfo]->key[nCntkey];
							m_CharacterMotion[nCnt]->key_info[nCntinfo]->key[nCntkey] = nullptr;
						}
					}
					delete m_CharacterMotion[nCnt]->key_info[nCntinfo];
					m_CharacterMotion[nCnt]->key_info[nCntinfo] = nullptr;

				}
			}
			delete m_CharacterMotion[nCnt];
			m_CharacterMotion[nCnt] = nullptr;
		}
	}
	m_CharacterMotion.clear();
}

//====================================================================
//デバッグ
//====================================================================
void CCharacter::DebugInfo(void)
{
	CDebug_ModelViewer::OffsetViewer(m_vModelList);

	//CDebugProc::Print("腰の高さ%2f\n", m_vModelList[0]->GetPosition().y);

	//CDebugProc::Print("state >>%d\n", GetCharacterState());

	//CDebugProc::Print("");
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
	if (pMap && m_pCollision)
	{
		m_pCollision->SetHeight(m_vModelList[0]->GetPosition().y);
		// レイの判定
		if (m_pCollision->RayBlockCollision(pMap, m_vModelList[0]->GetMatrix()))
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
void CCharacter::CheckDrawRange()
{
	m_bDraw = CManager::GetRenderer()->CheckScreenRange(m_pos);
}


//====================================================================
//モーションタイプの取得
//====================================================================
CCharacter::CHARACTER_MOTION_STATE &CCharacter::GetMotionType(void)
{
	return m_MotionType;
}
//====================================================================
//前のモーションタイプの取得
//====================================================================
CCharacter::CHARACTER_MOTION_STATE CCharacter::GetMotionOldType(void)
{
	return m_MotionOld;
}
//====================================================================
//モーションしてるかどうか取得
//====================================================================
bool & CCharacter::GetMotion()
{
	return m_bMotion;
}
//====================================================================
//キーセットの取得
//====================================================================
int &CCharacter::GetKeySet(void)
{
	return m_CntKeySet;
}
//====================================================================
//フレームの取得
//====================================================================
int &CCharacter::GetFram(void)
{
	return m_Fram;

}
//====================================================================
//前のモーションタイプの設定
//====================================================================
CCharacter::CHARACTER_TYPE CCharacter::GetCharacterType()
{
	return m_CharaType;
}

//====================================================================
//モデルのリストを返す	参照渡し
//====================================================================
std::vector<CModel*>& CCharacter::GetCharacterModelList()
{
	return m_vModelList;
}
//====================================================================
//モデルパーツのリストを返す	参照渡し
//====================================================================
CModel* CCharacter::GetCharacterModelPartsList(int nCnt)
{
	return m_vModelList[nCnt];
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
//前のモーションタイプの設定
//====================================================================
void CCharacter::SetMotionOldType(CHARACTER_MOTION_STATE type)
{
	m_MotionOld = type;
}
//====================================================================
//キーセットの設定
//====================================================================
void CCharacter::SetKeySet(int keyset)
{
	m_CntKeySet = keyset;
}
//====================================================================
//フレームの設定
//====================================================================
void CCharacter::SetFram(int fram)
{
	m_Fram = fram;
}
//====================================================================
//キャラクタータイプ設定
//====================================================================
void CCharacter::SetCharacterType(CHARACTER_TYPE CharaType)
{
	m_CharaType = CharaType;
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
