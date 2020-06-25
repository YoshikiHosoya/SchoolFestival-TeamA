// =====================================================================================================================================================================
//
// バレットの処理 [bullet.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "bullet.h"			// インクルードファイル
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "debugproc.h"
#include "gun.h"
#include "collision.h"
#include "Player.h"
#include "Enemy.h"
#include "map.h"
// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
BULLET_PARAM	CBullet::m_BulletParam[CGun::GUNTYPE_MAX] = {};

// =====================================================================================================================================================================
// テキストファイル名
// =====================================================================================================================================================================
char *CBullet::m_BulletFileName[CGun::GUNTYPE_MAX] =
{
	{ "data/Load/HandGun.txt" },				// ハンドガン
	{ "data/Load/HeavyMachineGun.txt" },		// ヘビーマシンガン
	{ "data/Load/ShotGun.txt" },				// ショットガン
	{ "data/Load/LaserGun.txt" },				// レーザーガン
	{ "data/Load/RocketLauncher.txt" },			// ロケットランチャー
	{ "data/Load/FlameShot.txt" },				// フレイムショット
};

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define BULLET_LIFE			(100)			// 弾の体力

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CBullet::CBullet(OBJ_TYPE type) :CScene3D(type)
{
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CBullet::~CBullet()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CBullet::Init()
{
	// 変数初期化
	m_move			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動値
	m_pCollision	= NULL;									// 当たり判定のポインタ
	m_nLife			= 0;				// 体力

	// 初期化
	CScene3D::Init();

	// ビルボードの設定
	CScene3D::SetBillboard(true);

	// 当たり判定生成
	m_pCollision = CCollision::Create();
	m_pCollision->SetPos(&GetPosition());
	m_pCollision->SetSize2D(D3DXVECTOR3(40.0f, 40.0f, 0.0f));
	m_pCollision->SetMove(&m_move);
	m_pCollision->SetType(CCollision::OBJTYPE_PLAYERBULLET);
	m_pCollision->DeCollisionCreate(CCollision::COLLISIONTYPE_NORMAL);

	return S_OK;
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CBullet::Uninit(void)
{
	CScene3D::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CBullet::Update(void)
{
	// プレイヤーの情報取得
	//CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
	// エネミーの情報取得
	//CEnemy *pEnemy = CManager::GetBaseMode()->GetEnemy();

	// 位置の取得
	D3DXVECTOR3 pos		= CScene3D::GetPosition();
	D3DXVECTOR3 size	= CScene3D::GetSize();

	// 位置更新
	pos += m_move;

	// 体力減少												配列の[ 0 ]のところには銃の種類が入る
	m_nLife--;

	// 体力が0になったら									配列の[ 0 ]のところには銃の種類が入る
	if (m_nLife <= 0)
	{
		if (m_pCollision != nullptr)
		{
			// 判定の削除
			m_pCollision->ReleaseCollision(m_pCollision);
			m_pCollision = nullptr;
		}

		Rerease();
	}

	// 位置の設定
	CScene3D::SetPosition(pos);

	// ------------- 当たり判定 ------------- //
	if (m_pCollision != nullptr)
	{
		// 判定の座標を更新
		m_pCollision->SetPos(&GetPosition());

		// プレイヤーの弾だったら
		if (m_pCollision->GetObjtype() == CCollision::OBJTYPE_PLAYERBULLET)
		{
			// 当たり判定 相手がエネミーだったら
			// 敵の総数分
			for (int nCnt = 0; nCnt < CManager::GetBaseMode()->GetMap()->GetMaxEnemy(); nCnt++)
			{
				CEnemy *pEnemy = CManager::GetBaseMode()->GetMap()->GetEnemy(nCnt);
				if (pEnemy != nullptr)
				{
					if (m_pCollision->OtherCollision2D(pEnemy->GetCollision()))
					{
						// 敵のライフ減衰
						pEnemy->CCharacter::AddDamage(10);
						if (pEnemy->CCharacter::GetLife() <= 0)
						{
							// 敵の当たり判定の削除
							//pEnemy->GetCollision()->Delete(pEnemy->GetCollision());
							pEnemy->DeleteCollision();
							pEnemy = NULL;
						}

						// 弾の判定の削除
						m_pCollision->ReleaseCollision(m_pCollision);
						m_pCollision = nullptr;
						// 弾の削除
						Rerease();
					}
					else
					{
						CDebugProc::Print("\n弾が敵に当たってないよ！ \n");
					}
				}
			}
		}

		// エネミーの弾だったら
		//else if (m_pCollision->GetObjtype() == CCollision::OBJTYPE_ENEMYBULLET)
		//{
		//	// 当たり判定 相手がプレイヤーだったら
		//	if (m_pCollision->Collision2D(CCollision::OBJTYPE_PLAYER))
		//	{
		//		// 判定の削除
		//		m_pCollision->Delete(m_pCollision);
		//		m_pCollision = NULL;
		//		// 弾の削除
		//		Rerease();
		//		// プレイヤーのライフ減衰
		//		//pPlayer->CCharacter::SetLife(-10);
		//	}
		//}
	}

	// 更新
	CScene3D::Update();

#ifdef _DEBUG
	// デバッグ表示
	CDebugProc::Print("\nbullet_pos %.1f, %.1f, %.1f\n", pos);
	CDebugProc::Print("bullet_move %.1f, %.1f, %.1f\n\n", m_move);

	CDebugProc::Print("\n\nbullet_type %d\n\n", m_type);		// 弾の種類(自分か敵か）
#endif // DEBUG
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CBullet::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ライティングモード無効
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 描画
	CScene3D::Draw();

	// ライティングモード有効
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

// =====================================================================================================================================================================
//
// 弾のロード
//
// =====================================================================================================================================================================
void CBullet::BulletLoad()
{
	// ファイルポイント
	FILE *pFile;

	char cReadText[128];			// 文字として読み取る
	char cHeadText[128];			// 比較用
	char cDie[128];					// 不要な文字
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置

	for (int nCnt = 0; nCnt < CGun::GUNTYPE_MAX; nCnt++)
	{
		// ファイルを開く
		pFile = fopen(m_BulletFileName[nCnt], "r");

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

					// BULLETSETが来たら
					if (strcmp(cHeadText, "BULLETSET") == 0)
					{
						// END_BULLETSETが来るまでループ
						while (strcmp(cHeadText, "END_BULLETSET") != 0)
						{
							fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
							sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入

							// SPEEDが来たら
							if (strcmp(cHeadText, "SPEED") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDie, &cDie, &m_BulletParam[nCnt].fBulletSpeed);		// 比較用テキストにSPEEDを代入
							}
							// LIFEが来たら
							else if (strcmp(cHeadText, "LIFE") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_BulletParam[nCnt].nLife);			// 比較用テキストにLIFEを代入
							}
							// SIZEが来たら
							else if (strcmp(cHeadText, "SIZE") == 0)
							{
								sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &m_BulletParam[nCnt].size.x, &m_BulletParam[nCnt].size.y, &m_BulletParam[nCnt].size.z);		// 比較用テキストにSIZEを代入
							}
							// POWERが来たら
							else if (strcmp(cHeadText, "POWER") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDie, &cDie, &m_BulletParam[nCnt].fPower);			// 比較用テキストにPOWERを代入
							}
							// AMMOが来たら
							else if (strcmp(cHeadText, "AMMO") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_BulletParam[nCnt].nAmmo);			// 比較用テキストにAMMOを代入
							}
							// TRIGGERが来たら
							else if (strcmp(cHeadText, "TRIGGER") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_BulletParam[nCnt].nTrigger);			// 比較用テキストにTRIGGERを代入
							}
							else if (strcmp(cHeadText, "END_BULLETSET") == 0)
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
			MessageBox(NULL, "弾のパラメーター読み込み失敗", "警告", MB_ICONWARNING);
		}
	}
}

// =====================================================================================================================================================================
//
// 弾のパラメーター設定
//
// =====================================================================================================================================================================
void CBullet::SetBulletParam(CGun::GUN_TYPE type)
{
	m_nLife = m_BulletParam[type].nLife;	// 体力
}