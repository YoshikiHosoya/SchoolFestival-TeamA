// ----------------------------------------
//
// ブロック処理の説明[block.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
#include "wall.h"
#include "model_info.h"

// ----------------------------------------
//
// 静的変数宣言
//
// ----------------------------------------
LPDIRECT3DTEXTURE9 CWall::m_pTexture[MAX_WALLTEXTURE] = {};		// テクスチャへのポインタ
CLoad	*CWall::m_pload = NULL;							// ロード
CModel_info	*CWall::m_pmodel_info = NULL;					// モデル情報
int		CWall::m_nAll = 0;									// 番号

// ----------------------------------------
// イニシャライザコンストラクタ
// ----------------------------------------
CWall::CWall() : CScene_X::CScene_X(ACTOR_WALL, LAYER_3DOBJECT)
{
	m_type = SIZE_I;
	//m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CWall::~CWall()
{
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void CWall::Init(void)
{
	// Xオブジェクト生成
	CScene_X::Init();
	// モデル情報設定
	CScene_X::BindModel(m_pmodel_info[m_type].GetModel_info());
	// テクスチャー設定
	for (int nCnt = 0; nCnt < MAX_WALLTEXTURE; nCnt++)
	{
		CScene_X::BindTexture(m_pTexture[nCnt]);
	}
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void CWall::Uninit(void)
{
	CScene_X::Uninit();
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void CWall::Update(void)
{
	CScene_X::Update();
}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void CWall::Draw(void)
{
	CScene_X::Draw();
}

// ----------------------------------------
// 作成処理
// ----------------------------------------
CWall * CWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, SIZE type)
{
	// 変数宣言
	CWall * pWall;		// シーン3Dクラス
						// メモリの生成(初め->基本クラス,後->派生クラス)
	pWall = new CWall();
	// 種類の設定
	pWall->m_type = type;
	// 初期化処理
	pWall->Init();
	// 座標の設定
	//pWall->m_pos = pos;
	pWall->SetPos(pos);
	// 回転の設定
	//pWall->m_rot = rot;
	pWall->SetRot(rot);
	// 生成したオブジェクトを返す
	return pWall;
}

// ----------------------------------------
// 読み込み作成処理
// ----------------------------------------
void CWall::LoadCreate(void)
{
	// 変数宣言
	CWall * pWall;	// ブロック
					// ブロック
	for (int nCntWall = 0; nCntWall < m_nAll; nCntWall++)
	{
		pWall = CWall::Create(m_pload->GetInfo(nCntWall).pos,
			m_pload->GetInfo(nCntWall).rot,
			(SIZE)m_pload->GetInfo(nCntWall).nType);		// 生成

		//pWall->SetPos(m_pload->GetInfo(nCntWall).pos);	// 位置
		//pWall->SetRot(m_pload->GetInfo(nCntWall).rot);	// 回転
		//pWall->m_pload->GetInfo(nCntWall).nType;			// 種類

		/*if (m_pload->GetInfo(nCntWall).nType == 2)
		{
			if (pWall->m_pload->GetInfo(nCntWall).rot.y == 0.0f)
			{
				CCollision::Create_Single(m_pload->GetInfo(nCntWall).pos, D3DXVECTOR3(300, 300, 0));
			}
		}*/
	}
}

// ----------------------------------------
// 読み込み処理
// ----------------------------------------
HRESULT CWall::Load(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice =					// デバイスの取得
		CManager::GetRenderer()->GetDevice();
	char cTex[MAX_WALLTEXTURE][128] =					// テクスチャー名
	{
		"data/TEXTURE/obj_tex/WallPattern00.jpg",
		"data/TEXTURE/obj_tex/wall.jpg",
	};
	char cModelfile[TYPE_MAX][256] =			// モデルファイル名
	{
		"data/MODEL/object/Wall_001.x",
		"data/MODEL/object/Wall_002.x",
		"data/MODEL/object/Wall_003.x",
		"data/MODEL/object/Wall_004.x",
		"data/MODEL/object/Wall_005.x",
		"data/MODEL/object/Wall_006.x",
		"data/MODEL/object/Wall_007.x",
		"data/MODEL/object/Wall_008.x",
		"data/MODEL/object/Wall_009.x",
		"data/MODEL/object/Wall_010.x",
		"data/MODEL/object/Wall_015.x",
		"data/MODEL/object/Wall_021.x",
	};
	// テクスチャー設定
	for (int nCnt = 0; nCnt < MAX_WALLTEXTURE; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, cTex[nCnt], &m_pTexture[nCnt]);
	}
	// ロード生成
	m_pload = new CLoad[TYPE_MAX];
	// ロード読み込み
	m_nAll = m_pload->Load("data/LOAD/OBJECT/Wall_Location.txt");
	// モデル情報生成
	m_pmodel_info = new CModel_info[TYPE_MAX];
	// モデル読み込み
	for (int nCntModel = 0; nCntModel < TYPE_MAX; nCntModel++)
	{
		m_pmodel_info[nCntModel].Load(pDevice, cModelfile[nCntModel]);
	}
	return S_OK;
}

// ----------------------------------------
// unload処理
// ----------------------------------------
void CWall::UnLoad(void)
{
	// テクスチャー設定
	for (int nCnt = 0; nCnt < MAX_WALLTEXTURE; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}

	// モデルの描画情報破棄
	for (int nCntModelLoad = 0; nCntModelLoad < TYPE_MAX; nCntModelLoad++)
	{
		//モデルの破棄
		m_pmodel_info[nCntModelLoad].Unload();
	}

	delete[] m_pmodel_info;
	//m_pmodel_info = NULL;
	// ロードの破棄
	delete[] m_pload;
	//m_pload = NULL;
	//// ロードの破棄
	//delete m_pload;
	//m_pload = NULL;
	//// モデルの破棄
	//m_pmodel_info->Unload();
	//delete m_pmodel_info;
	//m_pmodel_info = NULL;
}

// ----------------------------------------
// 位置の設定処理
// ----------------------------------------
void CWall::SetPos(D3DXVECTOR3 pos)
{
	CScene_X::SetPos(pos);
}

// ----------------------------------------
// 回転の設定処理
// ----------------------------------------
void CWall::SetRot(D3DXVECTOR3 rot)
{
	CScene_X::SetRot(rot);
}

// ----------------------------------------
// 位置の取得処理
// ----------------------------------------
D3DXVECTOR3 CWall::GetPos(void)
{
	return CScene_X::GetPos();
}