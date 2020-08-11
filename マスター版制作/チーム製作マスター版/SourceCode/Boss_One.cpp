// =====================================================================================================================================================================
//
// ボス1の処理 [boss_one.cpp]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "Boss_One.h"
#include "model.h"
#include "collision.h"
#include "game.h"
#include "manager.h"
#include "map.h"

//====================================================================
//マクロ定義
//====================================================================

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
BOSS_ONE_DATA		CBoss_One::m_BossOneData = {};									// データ
int					CBoss_One::m_nLife;												// 体力
D3DXVECTOR3			CBoss_One::m_CollisionSize[POSTURETYPE_MAX] = {};				// 当たり判定の大きさ

// =====================================================================================================================================================================
// テキストファイル名
// =====================================================================================================================================================================
char *CBoss_One::m_BossOneFileName =
{
	"data/Load/DragonNosuke/Boss_OneData.txt" 			// ボスの情報
};

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CBoss_One::CBoss_One(OBJ_TYPE type) :CEnemy(type)
{

	// ボスの初期状態
	m_BossOneState = BOSS_ONE_STATE_NONE;
}
// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CBoss_One::~CBoss_One()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CBoss_One::Init(void)
{
	// キャラの初期化
	CCharacter::Init();
	// オフセットの取得
	LoadOffset(CCharacter::CHARACTER_TYPE_BOSS_ONE);
	// キャラクタータイプの設定
	SetCharacterType(CCharacter::CHARACTER_TYPE_BOSS_ONE);
	//重力無し
	SetGravity(false);
	// 角度の設定
	SetRotDest(D3DXVECTOR3(0.0f, 1.2f, 0.0f));
	//SetRotDest(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	// 体力の初期値
	CCharacter::SetLife(m_nLife);
	// モーションさせない設定
	SetMotion(CCharacter::CHARACTER_MOTION_STATE_NONE);
	// 当たり判定生成
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetSize2D(m_CollisionSize[0]);
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);

	return S_OK;
}
//====================================================================
//終了
//====================================================================
void CBoss_One::Uninit(void)
{
	CCharacter::Uninit();
}
//====================================================================
//更新
//====================================================================
void CBoss_One::Update(void)
{
	// 当たり判定
	if (GetCollision() != nullptr)
	{
		// 座標の更新 pos
		GetCollision()->SetPos(&GetPosition());
	}

	for (int nCnt = 0; nCnt < CModel::MODEL_BOSSONE_MAX; nCnt++)
	{
		GetCharacterModelPartsList(nCnt)->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	// キャラクターの更新
	CCharacter::Update();

	for (int nCnt = 0; nCnt < CModel::MODEL_BOSSONE_MAX;nCnt++)
	{
		CDebugProc::Print("rrroottt %f, %f, %f\n",
			GetCharacterModelPartsList(nCnt)->GetRot().x,
			GetCharacterModelPartsList(nCnt)->GetRot().y,
			GetCharacterModelPartsList(nCnt)->GetRot().z);
	}
}
//====================================================================
//描画
//====================================================================
void CBoss_One::Draw(void)
{
	CCharacter::Draw();
}
//====================================================================
//デバッグ
//====================================================================
void CBoss_One::DebugInfo(void)
{
	//CDebugProc::Print("");
	CCharacter::DebugInfo();
}
//====================================================================
//モデルのクリエイト
//====================================================================
CBoss_One *CBoss_One::Create()
{
	// メモリを確保
	CBoss_One*pBoss_One = new CBoss_One(OBJTYPE_BOSSONE);
	// 初期化
	pBoss_One->Init();
	// 値を返す
	return pBoss_One;
}

// =====================================================================================================================================================================
//
// ボスの情報の読み込み
//
// =====================================================================================================================================================================
void CBoss_One::Boss_One_DataLoad()
{
	FILE *pFile;					// ファイルポイント
	char cReadText[128];			// 文字として読み取る
	char cHeadText[128];			// 比較用
	char cDie[128];					// 不要な文字

									// ファイルを開く
	pFile = fopen(m_BossOneFileName, "r");

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
				if (strcmp(cHeadText, "BOSSONESET") == 0)
				{
					// END_ITEMSETが来るまでループ
					while (strcmp(cHeadText, "END_BOSSONESET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
						sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入

																	// DELETEが来たら
						if (strcmp(cHeadText, "LIFE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_BossOneData.nLife);	// 比較用テキストにDELETEを代入
						}
						// SPEEDが来たら
						else if (strcmp(cHeadText, "COOLTIME") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_BossOneData.nCoolTime);	// 比較用テキストにSPEEDを代入
						}
						// COLLISIONSIZEが来たら
						else if (strcmp(cHeadText, "COLLISIONSIZE_0") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
								&m_BossOneData.CollisionSize[POSTURETYPE_STAND].x,
								&m_BossOneData.CollisionSize[POSTURETYPE_STAND].y,
								&m_BossOneData.CollisionSize[POSTURETYPE_STAND].z);										// 比較用テキストにCOLLISIONSIZEを代入
						}
						// COLLISIONSIZEが来たら
						else if (strcmp(cHeadText, "COLLISIONSIZE_1") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
								&m_BossOneData.CollisionSize[POSTURETYPE_SQUAT].x,
								&m_BossOneData.CollisionSize[POSTURETYPE_SQUAT].y,
								&m_BossOneData.CollisionSize[POSTURETYPE_SQUAT].z);										// 比較用テキストにCOLLISIONSIZEを代入
						}
						else if (strcmp(cHeadText, "END_BOSSONESET") == 0)
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
		MessageBox(NULL, "ボス1のデータ読み込み失敗", "警告", MB_ICONWARNING);
	}

	// 読み込んだ情報の代入
	SetBoss_OneData();
}

//====================================================================
//ボスの読み込んだ情報の設定
//====================================================================
void CBoss_One::SetBoss_OneData()
{
	// 体力の設定
	m_nLife = m_BossOneData.nLife;
	// 当たり判定の設定
	for (int nCnt = 0; nCnt < POSTURETYPE_MAX; nCnt++)
	{
		m_CollisionSize[nCnt] = m_BossOneData.CollisionSize[nCnt];
	}
}

//====================================================================
// ボスのデフォルトモーション
//====================================================================
bool CBoss_One::Motion(void)
{
	return false;
}

bool CBoss_One::DefaultMotion(void){return false;}
void CBoss_One::BossOneState()
{
}
////====================================================================
////ダメージを受けた時のリアクション
////====================================================================
//void CBoss_One::DamageReaction()
//{
//	SetState(CCharacter::CHARACTER_STATE_DAMAGE_RED);
//
//	//CManager::GetSound()->Play(CSound::LABEL_SE_HIT);
//}
////====================================================================
////死んだ時のリアクション
////====================================================================
//void CBoss_One::DeathReaction()
//{
//	//死亡フラグをたてる
//	this->SetDieFlag(true);
//
//	CCharacter::DeathReaction();
//
//}
//
////====================================================================
////ステートが変更した瞬間の処理
////====================================================================
//void CBoss_One::StateChangeReaction()
//{
//
//	CCharacter::StateChangeReaction();
//
//	switch (CCharacter::GetCharacterState())
//	{
//	case CHARACTER_STATE_NORMAL:
//		break;
//
//	case CHARACTER_STATE_DAMAGE:
//
//		break;
//	case CHARACTER_STATE_DAMAGE_RED:
//
//		break;
//	case CHARACTER_STATE_INVINCIBLE:
//
//		break;
//	case CHARACTER_STATE_DEATH:
//		SetStateCount(60);
//		SetMotion(CCharacter::ENEMY_MOTION_DEAD_1);
//
//		break;
//	}
//}
