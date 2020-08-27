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
#include "player.h"
#include "playerui.h"
#include "scoremanager.h"

//====================================================================
//マクロ定義
//====================================================================
#define PRISONER_COLLISION_SIZE			(D3DXVECTOR3(50.0f,65.0f,0.0f))			 //捕虜のサイズ
#define PRISONER_DIETIME				(150)									 //捕虜が消滅するまでの時間

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
PRISONER_DATA		CPrisoner::m_PrisonerData	= {};
int					CPrisoner::m_nDeleteTime	= 0;
float				CPrisoner::m_fMoveSpeed		= 0.0f;
D3DXVECTOR3			CPrisoner::m_CollisionSize	= D3DXVECTOR3(0, 0, 0);

// =====================================================================================================================================================================
// テキストファイル名
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
	// ポインタを検索する際使えるかどうか
	m_bUse				= false;
	// ステートが切り替わるまでの時間
	m_StateTime			= 60;
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
	LoadOffset(CCharacter::CHARACTER_TYPE_PRISONER);
	// キャラクタータイプの設定
	SetCharacterType(CCharacter::CHARACTER_TYPE_PRISONER);

	SetMotion(CCharacter::PRISONER_MOTION_STAY);
	CCharacter::SetState(CCharacter::CHARACTER_STATE_NONE);

	Move(0.0f, -1.57f);
	// 当たり判定生成
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetSize2D(PRISONER_COLLISION_SIZE);
	GetCollision()->SetMove(&GetMove());
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);

	return S_OK;
}
//====================================================================
//終了
//====================================================================
void CPrisoner::Uninit(void)
{
	CCharacter::Uninit();
}
//====================================================================
//更新
//====================================================================
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
			//縛られてる状態以外のとき
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
//====================================================================
//描画
//====================================================================
void CPrisoner::Draw(void)
{
	CCharacter::Draw();
}
//====================================================================
//デバッグ
//====================================================================
void CPrisoner::DebugInfo(void)
{
	//CDebugProc::Print("");
	//CCharacter::DebugInfo();
}
//====================================================================
//モデルのクリエイト
//====================================================================
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

	// 読み込んだ情報の代入
	SetPrisonerData();
}

//====================================================================
//捕虜の読み込んだ情報の設定
//====================================================================
void CPrisoner::SetPrisonerData()
{
	// 捕虜が消滅するまでの時間
	m_nDeleteTime = m_PrisonerData.nDeleteTime;
	// 捕虜の移動速度
	m_fMoveSpeed = m_PrisonerData.fMoveSpeed;
	// 当たり判定の大きさ
	m_CollisionSize = m_PrisonerData.CollisionSize;
}

//====================================================================
// 捕虜のデフォルトモーション
//====================================================================
bool CPrisoner::DefaultMotion(void)
{
	SetMotion(CCharacter::PRISONER_MOTION_STAY);
	return false;
}
//====================================================================
// 捕虜の当たり判定
//====================================================================
void CPrisoner::Collision()
{
	CMap *pMap;
	pMap = CManager::GetBaseMode()->GetMap();

	// マップモデルが存在した時して当たり判定が存在する時
	if (pMap && GetCollision())
	{
		GetCollision()->SetPos(&GetPosition());

		GetCollision()->SetHeight(CCharacter::GetCharacterModelPartsList(0)->GetPosition().y);

		// レイの判定
		if (GetCollision()->RayBlockCollision(pMap, CCharacter::GetCharacterModelPartsList(0)->GetMatrix()))
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
		CDebugProc::Print("トルゥーやで\n");
		}
	}

}

//====================================================================
// 捕虜の状態別処理
//====================================================================
void CPrisoner::PrisonerState()
{
	switch (m_PrisonerState)
	{
		// アイテムをドロップするステート
	case CPrisoner::PRISONER_STATE_DROPITEM:
	{
		// アイテムを落とすモーション
		SetMotion(CCharacter::PRISONER_MOTION_RELEASE);

		m_StateTime--;
		if (m_StateTime <= 0)
		{
			CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
			if (pPlayer && pPlayer->GetPlayerUI())
			{
				pPlayer->GetPlayerUI()->SetScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_RESCUE_PRISONER));
				// 体力の加算
				pPlayer->SetLife(pPlayer->GetLife() + 1);
			}
			SetStateTime(40);
			// 捕虜の状態の変更
			// 捕虜のタイプ別ドロップ処理
			PrisonerDropType();
			this->SetPrisonerState(PRISONER_STATE_SALUTE);
		}
	}
		break;

		// 暴れるする
	case CPrisoner::PRISONER_STATE_SALUTE:

		SetMotion(CCharacter::PRISONER_MOTION_SALUTE);

		m_StateTime--;
		if (m_StateTime <= 0)
		{
			SetStateTime(120);
			// 捕虜の状態の変更
			this->SetPrisonerState(PRISONER_STATE_RUN);
		}
		break;

		// 走る
	case CPrisoner::PRISONER_STATE_RUN:

		if (GetFallFlag())
		{
			SetMotion(CCharacter::PRISONER_MOTION_FALL);
		}
		else
		{
			// 横に走る
			SetMotion(CCharacter::PRISONER_MOTION_RUN);
			SetMove(D3DXVECTOR3(-15.0f, 0.0f, 1.0f));

			// 消滅までのカウントを加算
			m_nDieCount++;
			// カウントが一致値を超えたら
			if (m_nDieCount >= PRISONER_DIETIME)
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

//====================================================================
// 捕虜のタイプ別処理
//====================================================================
void CPrisoner::PrisonerDropType()
{
	switch (this->GetPrisonerDropType())
	{
		// アイテムを1種類指定して確定でドロップさせる
	case CPrisoner::PRISONER_ITEM_DROPTYPE_DESIGNATE_ONE:
		// アイテムの生成
		CItem::DropCreate(
			GetPosition(),
			CItem::ITEMDROP_NONE,
			CItem::ITEMDROP_PATTERN_DESIGNATE,
			GetPrisonerDropItem());
		break;

		// ドロップするアイテムを範囲で指定してドロップさせる
	case CPrisoner::PRISONER_ITEM_DROPTYPE_DESIGNATE_RANGE:
		CItem::DropCreate(
			GetPosition(),
			CItem::ITEMDROP_WEAPON,
			CItem::ITEMDROP_PATTERN_RANDOM,
			CItem::ITEMTYPE_NONE);
		break;

		// 全てのアイテムの中からランダムでアイテムをドロップさせる
	case CPrisoner::PRISONER_ITEM_DROPTYPE_ALL:
		CItem::DropCreate(
			GetPosition(),
			CItem::ITEMDROP_ALL,
			CItem::ITEMDROP_PATTERN_RANDOM,
			CItem::ITEMTYPE_NONE);
		break;
	default:
		break;
	}
}

//====================================================================
// 移動
//====================================================================
void CPrisoner::Move(float move, float fdest)
{
	GetMove().x += sinf(move * -D3DX_PI) * 3.0f;
	GetMove().z += cosf(move * -D3DX_PI) * 3.0f;
	GetRotDest().y = fdest *  D3DX_PI;
}
