// =====================================================================================================================================================================
//
// 捕虜の処理 [prisoner.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "prisoner.h"
#include "model.h"
#include "collision.h"
#include "game.h"
#include "manager.h"
#include "map.h"
#include "item.h"
#include "scoremanager.h"
#include "ModelSet.h"
#include "player.h"

// =====================================================================================================================================================================
//
//マクロ定義
//
// =====================================================================================================================================================================
#define PLAYER_PRISONER_MINDISTANCE (150) // 捕虜のステート[PRISONER_STATE_SKIP]の時のプレイヤーと捕虜の距離の最大値

// =====================================================================================================================================================================
//
// 静的メンバ変数の初期化
//
// =====================================================================================================================================================================
PRISONER_DATA		CPrisoner::m_PrisonerData	= {};

// =====================================================================================================================================================================
//
// テキストファイル名
//
// =====================================================================================================================================================================
char *CPrisoner::m_PrisonerFileName =
{
	"data/Load/Prisoner/PrisonerData.txt" 			// 捕虜の情報
};

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CPrisoner::CPrisoner(OBJ_TYPE type) :CCharacter(type)
{
	// 捕虜の初期状態
	m_PrisonerState		= PRISONER_STATE_STAY;
	// 捕虜が消滅するまでのカウントを初期化
	m_nDieCount			= 0;
	// ステートが切り替わるまでの時間
	m_StateTime			= 60;
	//
	m_bDrop = false;
}
// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CPrisoner::~CPrisoner()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CPrisoner::Init(void)
{
	// キャラの初期化
	CCharacter::Init();
	// オフセットの取得
	GetModelSet()->LoadOffset(CModelSet::CHARACTER_TYPE_PRISONER);
	// キャラクタータイプの設定
	GetModelSet()->SetCharacterType(CModelSet::CHARACTER_TYPE_PRISONER);
	// デフォルトモーションの設定
	GetModelSet()->SetMotion(CModelSet::PRISONER_MOTION_STAY);
	// ステートの設定
	CCharacter::SetState(CCharacter::CHARACTER_STATE_NONE);
	// 向き
	Move(0.0f, -1.57f);
	// 当たり判定生成
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetSize(m_PrisonerData.CollisionSize);
	GetCollision()->SetMove(&GetMove());
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_NORMAL);
	GetCollision()->SetGameObject(this);

	return S_OK;
}
// =====================================================================================================================================================================
//
// 終了
//
// =====================================================================================================================================================================
void CPrisoner::Uninit(void)
{
	CCharacter::Uninit();
}
// =====================================================================================================================================================================
//
// 更新
//
// =====================================================================================================================================================================
void CPrisoner::Update(void)
{
	//描画の範囲内かチェック
	if (!CheckDrawRange())
	{
		// 当たり判定
		if (GetCollision() != nullptr)
		{
			// 座標の更新 pos
			GetCollision()->SetPos(&GetPosition());
			if (m_PrisonerState != PRISONER_STATE_STAY)
			{
				//消去
				SetDieFlag(true);
			}
			//処理しない
			return;
		}
	}

	// 捕虜の状態別処理
	this->PrisonerState();
	// キャラクターの更新
	CCharacter::Update();
}
// =====================================================================================================================================================================
//
// 描画
//
// =====================================================================================================================================================================
void CPrisoner::Draw(void)
{
	CCharacter::Draw();
}
// =====================================================================================================================================================================
//
// デバッグ
//
// =====================================================================================================================================================================
void CPrisoner::DebugInfo(void)
{
}
// =====================================================================================================================================================================
//
// モデルのクリエイト
//
// =====================================================================================================================================================================
CPrisoner *CPrisoner::Create()
{
	// メモリを確保
	CPrisoner*pPrisoner = new CPrisoner(OBJTYPE_PRISONER);
	// 初期化
	pPrisoner->Init();
	// 値を返す
	return pPrisoner;
}

// =====================================================================================================================================================================
//
// 捕虜の情報の読み込み
//
// =====================================================================================================================================================================
void CPrisoner::PrisonerLoad()
{
	// ファイルポイント
	FILE *pFile;

	char cReadText[128];			// 文字として読み取る
	char cHeadText[128];			// 比較用
	char cDie[128];					// 不要な文字

									// ファイルを開く
	pFile = fopen(m_PrisonerFileName, "r");

	// 開いているとき
	if (pFile != NULL)
	{
		// SCRIPTが来るまでループ
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
			sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入
		}

		// SCRIPTが来たら
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			// END_SCRIPTが来るまでループ
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
				sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入

															// ITEMSETが来たら
				if (strcmp(cHeadText, "PRISONERSET") == 0)
				{
					// END_ITEMSETが来るまでループ
					while (strcmp(cHeadText, "END_PRISONERSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
						sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入

						// DELETEが来たら
						if (strcmp(cHeadText, "DELETE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_PrisonerData.nDeleteTime);	// 比較用テキストにDELETEを代入
						}
						// SPEEDが来たら
						else if (strcmp(cHeadText, "SPEED") == 0)
						{
							sscanf(cReadText, "%s %s %f", &cDie, &cDie, &m_PrisonerData.fMoveSpeed);	// 比較用テキストにSPEEDを代入
						}
						// COLLISIONSIZEが来たら
						else if (strcmp(cHeadText, "COLLISIONSIZE") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
								&m_PrisonerData.CollisionSize.x,
								&m_PrisonerData.CollisionSize.y,
								&m_PrisonerData.CollisionSize.z);										// 比較用テキストにCOLLISIONSIZEを代入
						}
						else if (strcmp(cHeadText, "END_PRISONERSET") == 0)
						{
						}
					}
				}
			}
		}
		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		MessageBox(NULL, "捕虜のデータ読み込み失敗", "警告", MB_ICONWARNING);
	}
}

// =====================================================================================================================================================================
//
// 捕虜のデフォルトモーション
//
// =====================================================================================================================================================================
bool CPrisoner::DefaultMotion(void)
{
	GetModelSet()->SetMotion(CModelSet::PRISONER_MOTION_STAY);
	return false;
}
// =====================================================================================================================================================================
//
// 捕虜の当たり判定
//
// =====================================================================================================================================================================
void CPrisoner::Collision()
{
	CMap *pMap = CManager::GetBaseMode()->GetMap();

	// マップモデルが存在した時して当たり判定が存在する時
	if (pMap && GetCollision())
	{
		GetCollision()->SetPos(&GetPosition());

		GetCollision()->SetHeight(GetModelSet()->GetCharacterModelList()[0]->GetPosition().y);

		// レイの判定
		if (GetCollision()->RayBlockCollision(pMap, GetModelSet()->GetCharacterModelList()[0]->GetMatrix()))
		{
			// ジャンプすることを承認する
			SetJump(true);
			SetFallFlag(false);
		}
		else
		{
			// ジャンプすることを承認しない
			SetJump(false);
			SetFallFlag(true);
		}
		if (GetFallFlag() == true)
		{
		}
	}

}

// =====================================================================================================================================================================
//
// 捕虜の状態別処理
//
// =====================================================================================================================================================================
void CPrisoner::PrisonerState()
{
	// 捕虜の状態によって行動を変える
	switch (m_PrisonerState)
	{
		// 初期状態
	case CPrisoner::PRISONER_STATE_STAY:
		// 特に何もしない
		break;

		// プレイヤーとの距離によって次の行動を考える
	case CPrisoner::PRISONER_STATE_THINKING:

		// プレイヤーと捕虜の距離がn以下だった時捕虜のステートを[PRISONER_STATE_DROPITEM]に移行する
		if (GetDistance_Player_This() <= PLAYER_PRISONER_MINDISTANCE)
		{
			SetStateTime(20 * 4 + 60);
			this->SetPrisonerState(PRISONER_STATE_DROPITEM);
		}

		// 距離がn以上離れていたら距離がn以下になるまで捕虜のステートを[PRISONER_STATE_SKIP]にする
		else
		{
			this->SetPrisonerState(PRISONER_STATE_SKIP);
		}

		break;

		// プレイヤーの方を向いてスキップする
	case CPrisoner::PRISONER_STATE_SKIP:

		if (GetFallFlag())
		{
			SetMove(D3DXVECTOR3(0.0f, -2.0f, 0.0f));
			SetStateTime(120);	GetModelSet()->SetMotion(CModelSet::PRISONER_MOTION_FALL);
		}
		else
		{
			// スキップのモーションをする
			GetModelSet()->SetMotion(CModelSet::PRISONER_MOTION_SKIP);

			// 捕虜がプレイヤーより右にいたら左に動く
			if (this->PrisonerPosX_Than_Large())
			{
				Move(0.0f,-1.57f);
				SetMove(D3DXVECTOR3(-3.0f, 0.0f, 0.0f));
			}
			// 左なら左へ
			else
			{
				// 向き
				Move(0.0f, 1.57f);
				SetMove(D3DXVECTOR3(3.0f, 0.0f, 0.0f));
			}
		}

		// 捕虜とプレイヤーの距離が規定値より下回ったら捕虜のステートを[PRISONER_STATE_DROPITEM]に移行する
		if (GetRotDest().y <= D3DX_PI / 2)
		{
			if (GetDistance_Player_This() <= PLAYER_PRISONER_MINDISTANCE)
			{
				// 20フレーム*4
				SetStateTime(20 * 4 + 60);
				this->SetPrisonerState(PRISONER_STATE_DROPITEM);
			}
		}
		else if(GetRotDest().y >= -D3DX_PI / 2)
		{
			if (GetDistance_Player_This() <= PLAYER_PRISONER_MINDISTANCE)
			{
				// 20フレーム*4
				SetStateTime(20 * 4 + 60);
				this->SetPrisonerState(PRISONER_STATE_DROPITEM);
			}
		}

		break;

		// アイテムをドロップする
	case CPrisoner::PRISONER_STATE_DROPITEM:
		// アイテムを落とすモーションをする
		GetModelSet()->SetMotion(CModelSet::PRISONER_MOTION_DROP);

		// モーションが終わったら捕虜のステート[PRISONER_STATE_RAMPAGE]に移行させる
		m_StateTime--;
		if (m_StateTime <= 40)
		{
			// 捕虜の状態の変更
			// 捕虜のタイプ別ドロップ処理
			PrisonerDropType();

			if (m_StateTime <= 0)
			{
				SetStateTime(60);
				this->SetPrisonerState(PRISONER_STATE_RAMPAGE);
			}
		}
		break;

		// 暴れる
	case CPrisoner::PRISONER_STATE_RAMPAGE:
		// 暴れるモーションをさせる
		GetModelSet()->SetMotion(CModelSet::PRISONER_MOTION_SALUTE);

		// 一定時間経過したらステートを[PRISONER_STATE_RUN]に移行する
		// この時捕虜は移動しない
		m_StateTime--;

		if (m_StateTime <= 0)
		{
			this->SetPrisonerState(PRISONER_STATE_RUN);
		}
		break;

	case CPrisoner::PRISONER_STATE_RUN:
		if (m_StateTime <= 0)
		{
			if (GetFallFlag())
			{
				SetMove(D3DXVECTOR3(0.0f, -3.0f, 0.0f));
				GetModelSet()->SetMotion(CModelSet::PRISONER_MOTION_FALL);
			}
			else
			{
				// 左向きにに走る
				GetModelSet()->SetMotion(CModelSet::PRISONER_MOTION_RUN);
				Move(0.0f, -1.57f);
				SetMove(D3DXVECTOR3(-15.0f, 0.0f, 0.0f));
			}

			// 消滅までのカウントを加算
			m_nDieCount++;
			// カウントが一致値を超えたら
			if (m_nDieCount >= m_PrisonerData.nDeleteTime)
			{
				SetDieFlag(true);
			}
		}
		break;
	}

	//当たり判定可能かどうか設定
	//縛られている状態以外は当たり判定がつかないようにする
	GetCollision()->SetCanCollision(m_PrisonerState == PRISONER_STATE_STAY);
}

// =====================================================================================================================================================================
//
// 捕虜のタイプ別処理
//
// =====================================================================================================================================================================
void CPrisoner::PrisonerDropType()
{
	if (!m_bDrop)
	{
		D3DXVECTOR3 DropPos = GetPosition();
		if (GetRotDest().y <= D3DX_PI / 2)
		{
			DropPos.x -= 50.0f;
		}
		else if(GetRotDest().y >= -D3DX_PI / 2)
		{
			DropPos.x += 50.0f;
		}

		switch (m_PrisonerDropType)
		{
			// アイテムを1種類指定して確定でドロップさせる
		case CPrisoner::PRISONER_ITEM_DROPTYPE_PICK_ONE:
			// アイテムの生成[捕虜の座標 ドロップするアイテムを確定させるかどうか 確定させるアイテムのタイプの指定]
			CItem::DropItem(
				DropPos,
				true,
				GetPrisonerDropItem());
			break;

			// ドロップするアイテムを範囲で指定してドロップさせる
		case CPrisoner::PRISONER_ITEM_DROPTYPE_RANGE:
			CItem::DropItem(
				DropPos,
				false,
				CItem::ITEMTYPE_NONE);
			break;
		}

		m_bDrop = true;
	}
}

// =====================================================================================================================================================================
//
// プレイヤーと選択された捕虜の距離の長さを求める 結果は必ず自然数
//
// =====================================================================================================================================================================
unsigned int CPrisoner::GetDistance_Player_This()
{
	// 今は1pのポインタを取得し1pの距離で参照している
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer(TAG::PLAYER_1);

	// プレイヤーと捕虜の距離を自然数で求める
	return (unsigned int)fabs(this->GetPosition().x - pPlayer->GetPosition().x);
}

// =====================================================================================================================================================================
//
// 捕虜のx座標から見て左にいるか右にいるかの結果を返す
//
// =====================================================================================================================================================================
bool CPrisoner::PrisonerPosX_Than_Large()
{
	// 今は1pのポインタを取得し1pの距離で参照している
	CPlayer *pPlayer =  CManager::GetBaseMode()->GetPlayer(TAG::PLAYER_1);

	 // 比べる対象(今はプレイヤーのみ)が捕虜の座標より左にいるか右にいるかを求める
	 // 左(捕虜より値が小さかったらfalse)右(値が大きかったらtrue)
	 if (this->GetPosition().x >= pPlayer->GetPosition().x)
	 {
		 return true;
	 }
	 else
	 {
		 return false;
	 }

	return false;
}

// =====================================================================================================================================================================
//
// 移動
//
// =====================================================================================================================================================================
void CPrisoner::Move(float move, float fdest)
{
	GetMove().x += sinf(move * -D3DX_PI) * 3.0f;
	GetMove().z += cosf(move * -D3DX_PI) * 3.0f;
	GetRotDest().y = fdest *  D3DX_PI;
}
