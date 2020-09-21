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
#include "meshbox.h"

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
	m_pos = nullptr;										// 座標ポインタの初期化
	m_size = nullptr;										// サイズポインタの初期化
	m_type = COLLISIONTYPE_BOX;							// タイプの初期化
	m_pMeshBox = nullptr;
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CDebugcollision::~CDebugcollision()
{
	if (m_pMeshBox)
	{
		this->m_pMeshBox->Rerease();
		this->m_pMeshBox = nullptr;
	}
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

	case COLLISIONTYPE_BOX_CHARA:
		Box_CharaCollision();
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
	m_pMeshBox = CMeshBox::Create(*m_pos,*m_size, CMeshBox::TYPE_CENTER);
}
// ----------------------------------------
// 箱の当たり判定処理
// ----------------------------------------
void CDebugcollision::Box_CharaCollision(void)
{
	m_pMeshBox = CMeshBox::Create(*m_pos, *m_size, CMeshBox::TYPE_GROUND);
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void CDebugcollision::Uninit(void)
{
	m_pos = nullptr;										// 座標ポインタの初期化
	m_size = nullptr;										// サイズポインタの初期化
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void CDebugcollision::Update(void)
{
	// 判定の種類が箱型だったら通す
	if (m_type == COLLISIONTYPE_BOX)
	{
		if (m_pMeshBox)
		{
			m_pMeshBox->SetPos(*m_pos);
		}
	}

	// 判定の種類が板型だったら通す
	else if (m_type == COLLISIONTYPE_BOX_CHARA)
	{
		if (m_pMeshBox)
		{
			m_pMeshBox->SetPos(*m_pos);
		}
	}

}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void CDebugcollision::Draw(void)
{
}
// ----------------------------------------
// デバッグ
// ----------------------------------------
void CDebugcollision::DebugInfo(void)
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
	// 座標のポインタがnullptrじゃなかったら通す

	if (pos != nullptr)
	{
		// 座標情報を代入
		m_pos = pos;

		// 判定の種類が箱型だったら通す
		if (m_type == COLLISIONTYPE_BOX)
		{
			if (m_pMeshBox)
			{
				m_pMeshBox->SetPos(*m_pos);
			}
		}

		// 判定の種類が板型だったら通す
		else if (m_type == COLLISIONTYPE_BOX_CHARA)
		{
			if (m_pMeshBox)
			{
				m_pMeshBox->SetPos(*m_pos);
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
	m_pMeshBox->SetSize(*m_size);
}

// ----------------------------------------
// ラインの削除
// ----------------------------------------
void CDebugcollision::DeleteDeCollision()
{
	if (m_pMeshBox)
	{
		this->m_pMeshBox->Rerease();
		this->m_pMeshBox = nullptr;
	}
}
