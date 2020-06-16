// ----------------------------------------
//
// デバッグ用の当たり判定表示処理[debugcollision.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
/* 描画 */
#include "debugcollision.h"
#include "3Dline.h"

// ----------------------------------------
//
// 静的変数宣言
//
// ----------------------------------------

// ----------------------------------------
// コンストラクタ処理
// ----------------------------------------
CDebugcollision::CDebugcollision(OBJ_TYPE type) :CScene(type)
{
	m_pos = NULL;										// 座標ポインタの初期化
	m_size = NULL;										// サイズポインタの初期化
	m_type = COLLISIONTYPE_BOX;							// タイプの初期化
	for (int nCnt = 0; nCnt < MAX_VERTEX3D; nCnt++)		// lineクラスのポインタ初期化
	{
		m_p3DLine[nCnt] = NULL;
	}

	for (int nCnt = 0; nCnt < MAX_VERTEX2D; nCnt++)		// lineクラスのポインタ初期化
	{
		m_p2DLine[nCnt] = NULL;
	}
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CDebugcollision::~CDebugcollision()
{
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
HRESULT CDebugcollision::Init(void)
{
	switch (m_type)
	{
	case COLLISIONTYPE_BOX:
		BoxCollision();
		break;

	case COLLISIONTYPE_BOARD:
		BoardCollision();
		break;

	default:
		break;
	}

	return S_OK;
}

// ----------------------------------------
// 箱の当たり判定処理
// ----------------------------------------
void CDebugcollision::BoxCollision(void)
{
	// 1本目
	m_p3DLine[0] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(-m_size->x * 0.5f, m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXVECTOR3(m_size->x * 0.5f, m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)
	);
	// 2本目
	m_p3DLine[1] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(m_size->x * 0.5f, m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXVECTOR3(m_size->x * 0.5f, -m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)
	);
	// 3本目
	m_p3DLine[2] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(m_size->x * 0.5f, -m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXVECTOR3(-m_size->x * 0.5f, -m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)
	);
	// 4本目
	m_p3DLine[3] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(-m_size->x * 0.5f, -m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXVECTOR3(-m_size->x * 0.5f, m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)
	);
	// 5本目
	m_p3DLine[4] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(-m_size->x * 0.5f, m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXVECTOR3(-m_size->x * 0.5f, m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)
	);
	// 6本目
	m_p3DLine[5] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(m_size->x * 0.5f, m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXVECTOR3(m_size->x * 0.5f, m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)
	);
	// 7本目
	m_p3DLine[6] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(m_size->x * 0.5f, -m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXVECTOR3(m_size->x * 0.5f, -m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)

	);
	// 8本目
	m_p3DLine[7] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(-m_size->x * 0.5f, -m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXVECTOR3(-m_size->x * 0.5f, -m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)

	);
	// 9本目
	m_p3DLine[8] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(-m_size->x * 0.5f, m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXVECTOR3(m_size->x * 0.5f, m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)

	);
	// 10本目
	m_p3DLine[9] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(m_size->x * 0.5f, m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXVECTOR3(m_size->x * 0.5f, -m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)

	);
	// 11本目
	m_p3DLine[10] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(m_size->x * 0.5f, -m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXVECTOR3(-m_size->x * 0.5f, -m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)

	);
	// 12本目
	m_p3DLine[11] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(-m_size->x * 0.5f, -m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXVECTOR3(-m_size->x * 0.5f, m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)

	);

}

// ----------------------------------------
// 板の当たり判定処理
// ----------------------------------------
void CDebugcollision::BoardCollision(void)
{
	// 1本目 上辺
	m_p2DLine[0] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(-m_size->x * 0.5f, m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXVECTOR3(m_size->x * 0.5f, m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)
	);
	// 2本目 右辺
	m_p2DLine[1] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(m_size->x * 0.5f, m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXVECTOR3(m_size->x * 0.5f, -m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)
	);
	// 3本目下辺
	m_p2DLine[2] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(m_size->x * 0.5f, -m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXVECTOR3(-m_size->x * 0.5f, -m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)
	);
	// 4本目左辺
	m_p2DLine[3] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(-m_size->x * 0.5f, -m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXVECTOR3(-m_size->x * 0.5f, m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)
	);
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void CDebugcollision::Uninit(void)
{
	m_pos = NULL;										// 座標ポインタの初期化
	m_size = NULL;										// サイズポインタの初期化
	for (int nCnt = 0; nCnt < MAX_VERTEX3D; nCnt++)		// lineクラスのポインタ初期化
	{
		m_p3DLine[nCnt] = NULL;
	}
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void CDebugcollision::Update(void)
{
}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void CDebugcollision::Draw(void)
{
}

// ----------------------------------------
// 生成処理
// ----------------------------------------
CDebugcollision * CDebugcollision::Create(
	D3DXVECTOR3 * pos,
	D3DXVECTOR3 * size,
	COLLISIONTYPE type
)
{
	// 変数宣言
	CDebugcollision * pDebugcollision;
	// メモリ確保
	pDebugcollision = new CDebugcollision(OBJTYPE_DEBUGCOLLISION);
	// 座標の設定
	pDebugcollision->m_pos = pos;
	// サイズの設定
	pDebugcollision->m_size = size;
	// 種類の設定
	pDebugcollision->m_type = type;
	// 初期化
	pDebugcollision->Init();
	return pDebugcollision;
}

// ----------------------------------------
// 位置設定処理
// ----------------------------------------
void CDebugcollision::SetPos(D3DXVECTOR3 * pos)
{
	// 座標のポインタがNULLじゃなかったら通す
	if (pos != NULL)
	{
		// 座標情報を代入
		m_pos = pos;

		// 判定の種類が箱型だったら通す
		if (m_type == COLLISIONTYPE_BOX)
		{
			// 座標のポインタをlineの座標に設定
			for (int nCnt = 0; nCnt < MAX_VERTEX3D; nCnt++)
			{
				if (m_p3DLine[nCnt] != NULL)
				{
					m_p3DLine[nCnt]->SetPosColi(*pos);
				}
			}
		}

		// 判定の種類が板型だったら通す
		else if (m_type == COLLISIONTYPE_BOARD)
		{
			// 座標のポインタをlineの座標に設定
			for (int nCnt = 0; nCnt < MAX_VERTEX2D; nCnt++)
			{
				if (m_p2DLine[nCnt] != NULL)
				{
					m_p2DLine[nCnt]->SetPosColi(*pos);
				}
			}
		}
	}
}

// ----------------------------------------
// サイズ設定処理
// ----------------------------------------
void CDebugcollision::SetSize(D3DXVECTOR3 * size)
{
	m_size = size;
}
