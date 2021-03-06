// =====================================================================================================================================================================
//
// グレネードの処理 [grenade.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "grenade.h"			// インクルードファイル
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "debugproc.h"
#include "texture.h"
#include "Player.h"
#include "particle.h"
// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
CGrenade::GRENADE_PARAM	CGrenade::m_GrenadeParam[CGrenadeFire::GRENADE_TYPE_MAX] = {};

// =====================================================================================================================================================================
// テキストファイル名
// =====================================================================================================================================================================
char *CGrenade::m_GrenadeFileName[CGrenadeFire::GRENADE_TYPE_MAX] =
{
	{ "data/Load/Grenade/HandGrenade.txt" },				// グレネード
	{ "data/Load/Grenade/TankGrenade.txt" },				// 戦車のグレネード
	{ "data/Load/Grenade/DropBomb.txt" },					// ドロップボム
};

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define GRENADE_GRAVITY				(0.8f)								// グレネードの重力
#define GRENADE_MOVE				(D3DXVECTOR3(10.0f, 15.0f, 0.0f))	// グレネードの移動量
#define ROT_DIVISION_Z				(7)									// 回転の分割数	( 縦 )

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CGrenade::CGrenade(OBJ_TYPE type) :CBullet(type)
{
	SetObjType(OBJTYPE_BULLET);
	m_move	= ZeroVector3;					// 移動値
	m_rot	= ZeroVector3;					// 回転
	m_type = CGrenadeFire::HAND_GRENADE;	// グレネードの種類
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CGrenade::~CGrenade()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CGrenade::Init()
{
	// 初期化
	CBullet::Init();
	m_move		= m_GrenadeParam[m_type].Move;		// 移動値

	return S_OK;
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CGrenade::Uninit(void)
{
	// 終了
	CBullet::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CGrenade::Update(void)
{
	// 重力
	GetMove().y -= m_GrenadeParam[m_type].fGravity;

	// グレネードの回転
	GrenadeRotation();

	// 回転の設定
	SetRot(m_rot);

	// 更新
	CBullet::Update();
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CGrenade::Draw(void)
{
	// 描画
	CBullet::Draw();
}

// =====================================================================================================================================================================
//
// 弾を消す処理
//
// =====================================================================================================================================================================
void CGrenade::DeleteBullet()
{
	switch (m_type)
	{
		case CGrenadeFire::GRENADE_TYPE::HAND_GRENADE:
			CParticle::CreateFromText(GetPosition(), ZeroVector3, CParticleParam::EFFECT_EXPLOSION_GRENADE, GetTag(), GetBulletParam(CGun::GUNTYPE_HANDGRENADE)->nPower);

			break;
		case CGrenadeFire::GRENADE_TYPE::TANK_GRENADE:
			CParticle::CreateFromText(GetPosition(), ZeroVector3, CParticleParam::EFFECT_EXPLOSION_TANK_GRENADE, GetTag(), GetBulletParam(CGun::GUNTYPE_TANKGRENADE)->nPower);

			break;
		case CGrenadeFire::GRENADE_TYPE::DROP_BOMB:
			CParticle::CreateFromText(GetPosition(), ZeroVector3, CParticleParam::EFFECT_EXPLOSION_GRENADE, GetTag(), GetBulletParam(CGun::GUNTYPE_DROPBOMB)->nPower);

			break;
	}

	CBullet::DeleteBullet();
}

// =====================================================================================================================================================================
//
// グレネードの生成
//
// =====================================================================================================================================================================
CGrenade * CGrenade::Create(D3DXVECTOR3 rot, CGrenadeFire::GRENADE_TYPE type)
{
	// 変数
	CGrenade *pGrenade;

	// メモリの確保
	pGrenade = new CGrenade(OBJTYPE_BULLET);

	pGrenade->m_type = type;

	// 初期化
	pGrenade->Init();

	// 放つ方向に合わせる
	pGrenade->GetMove() = D3DXVECTOR3(-sinf(rot.z)  * pGrenade->m_move.x, pGrenade->m_move.y, 0.0f);

	// モデルタイプの設定
	pGrenade->SetType(BULLET_MODEL);

	// モデルの変更
	switch (type)
	{
	case CGrenadeFire::HAND_GRENADE:
		pGrenade->SetModelID(MODEL_BULLET_GRENADE);
		break;

	case CGrenadeFire::TANK_GRENADE:
		pGrenade->SetModelID(MODEL_BULLET_TANKGRENADE);
		// 放つ方向に合わせる
		pGrenade->GetMove() = D3DXVECTOR3(1.0f * pGrenade->m_move.x, pGrenade->m_move.y, 0.0f);
		break;

	case CGrenadeFire::DROP_BOMB:
		pGrenade->SetModelID(MODEL_BULLET_MISSILE);
		break;
	}

	return pGrenade;
}

// =====================================================================================================================================================================
//
// グレネードのパラメーターのロード
//
// =====================================================================================================================================================================
void CGrenade::GrenadePramLoad()
{
	// ファイルポイント
	FILE *pFile;

	char cReadText[128];						// 文字として読み取る
	char cHeadText[128];						// 比較用
	char cDie[128];								// 不要な文字
	D3DXVECTOR3		move		= ZeroVector3;	// 移動量
	float			fGravity	= 0.0f;			// 重力

	for (int nCnt = 0; nCnt < CGrenadeFire::GRENADE_TYPE_MAX; nCnt++)
	{
		// ファイルを開く
		pFile = fopen(m_GrenadeFileName[nCnt], "r");

		// 開いているとき
		if (pFile != NULL)
		{
			// SCRIPTが来るまでループ
			while (strcmp(cHeadText, "SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s", &cHeadText);
			}

			// SCRIPTが来たら
			if (strcmp(cHeadText, "SCRIPT") == 0)
			{
				// END_SCRIPTが来るまでループ
				while (strcmp(cHeadText, "END_SCRIPT") != 0)
				{
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s", &cHeadText);

					// GRENADESETが来たら
					if (strcmp(cHeadText, "GRENADESET") == 0)
					{
						// END_GRENADESETが来るまでループ
						while (strcmp(cHeadText, "END_GRENADESET") != 0)
						{
							fgets(cReadText, sizeof(cReadText), pFile);
							sscanf(cReadText, "%s", &cHeadText);

							// MOVEが来たら
							if (strcmp(cHeadText, "MOVE") == 0)
							{
								sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &move.x, &move.y, &move.z);
							}
							// GRAVITYが来たら
							else if (strcmp(cHeadText, "GRAVITY") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDie, &cDie, &fGravity);
							}
							else if (strcmp(cHeadText, "END_GRENADESET") == 0)
							{
								m_GrenadeParam[nCnt].Move		= move;
								m_GrenadeParam[nCnt].fGravity	= fGravity;
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
			MessageBox(NULL, "グレネードののパラメーター読み込み失敗", "警告", MB_ICONWARNING);
		}
	}
}

// =====================================================================================================================================================================
//
// グレネードの回転
//
// =====================================================================================================================================================================
void CGrenade::GrenadeRotation()
{
	// 手榴弾
	if (m_type == CGrenadeFire::GRENADE_TYPE::HAND_GRENADE)
	{
		m_rot.z += (D3DX_PI / ROT_DIVISION_Z);
	}
	// 戦車のグレネード
	else if (m_type == CGrenadeFire::GRENADE_TYPE::TANK_GRENADE)
	{
		m_rot.z = D3DX_PI / 2;
	}
}