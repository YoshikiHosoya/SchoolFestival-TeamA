// ----------------------------------------
//
// オブジェクト処理の説明[object.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
#include "object.h"
#include "model_info.h"

// ----------------------------------------
//
// 静的変数宣言
//
// ----------------------------------------
CLoad			*CObject::m_pload = NULL;							// ロード
CModel_info		*CObject::m_pmodel_info = NULL;					// モデル情報
int				CObject::m_nAll = 0;									// 番号

// ----------------------------------------
// イニシャライザコンストラクタ
// ----------------------------------------
CObject::CObject() : CScene_X::CScene_X(ACTOR_BLOCK, LAYER_3DOBJECT)
{
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CObject::~CObject()
{
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void CObject::Init(void)
{
	// Xオブジェクト生成
	CScene_X::Init();
	// モデル情報設定
	CScene_X::BindModel(m_pmodel_info->GetModel_info());
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void CObject::Uninit(void)
{
	CScene_X::Uninit();
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void CObject::Update(void)
{
	CScene_X::Update();
}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void CObject::Draw(void)
{
	CScene_X::Draw();
}

// ----------------------------------------
// 作成処理
// ----------------------------------------
CObject * CObject::Create(void)
{
	// 変数宣言
	CObject * pObject;		// シーン3Dクラス
							// メモリの生成(初め->基本クラス,後->派生クラス)
	pObject = new CObject();
	// 初期化処理
	pObject->Init();
	// 生成したオブジェクトを返す
	return pObject;
}

// ----------------------------------------
// 読み込み作成処理
// ----------------------------------------
void CObject::LoadCreate(void)
{
	// 変数宣言
	CObject * pObject;	// ブロック
						// ブロック
	for (int nCntBlock = 0; nCntBlock < m_nAll; nCntBlock++)
	{
		pObject = CObject::Create();					// 生成
		pObject->SetPos(m_pload->GetInfo(nCntBlock).pos);	// 位置
		pObject->SetRot(m_pload->GetInfo(nCntBlock).rot);	// 回転
	}
}

// ----------------------------------------
// 読み込み処理
// ----------------------------------------
HRESULT CObject::Load(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice =					// デバイスの取得
		CManager::GetRenderer()->GetDevice();

	char cModelfile[OBJ_TYPE_MAX][128] =			// モデルファイル名
	{
		"data/MODEL/object/elevator.x",
	};

	// ロード生成
	m_pload = new CLoad;
	// ロード読み込み
	m_nAll = m_pload->Load("data/LOAD/OBJECT/obj_Location.txt");
	// モデル情報生成
	m_pmodel_info = new CModel_info;
	// モデル読み込み
	m_pmodel_info->Load(pDevice, cModelfile[0]);
	return S_OK;
}

// ----------------------------------------
// unload処理
// ----------------------------------------
void CObject::UnLoad(void)
{
	// ロードの破棄
	delete m_pload;
	m_pload = NULL;
	// モデルの破棄
	m_pmodel_info->Unload();
	delete m_pmodel_info;
	m_pmodel_info = NULL;
}

// ----------------------------------------
// 位置の設定処理
// ----------------------------------------
void CObject::SetPos(D3DXVECTOR3 pos)
{
	CScene_X::SetPos(pos);
}

// ----------------------------------------
// 回転の設定処理
// ----------------------------------------
void CObject::SetRot(D3DXVECTOR3 rot)
{
	CScene_X::SetRot(rot);
}

// ----------------------------------------
// 位置の取得処理
// ----------------------------------------
D3DXVECTOR3 CObject::GetPos(void)
{
	return CScene_X::GetPos();
}