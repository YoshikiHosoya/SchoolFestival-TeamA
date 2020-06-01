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
#include "titleobject.h"
#include "model_info.h"
#include "debugproc.h"
// ----------------------------------------
//
// 静的変数宣言
//
// ----------------------------------------
CLoad			*CTitleObject::m_pload = NULL;							// ロード
CModel_info		*CTitleObject::m_pmodel_info = NULL;					// モデル情報
int				CTitleObject::m_nAll = 0;								// 番号

// ----------------------------------------
// イニシャライザコンストラクタ
// ----------------------------------------
CTitleObject::CTitleObject() : CScene_X::CScene_X(ACTOR_BLOCK, LAYER_3DOBJECT)
{
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CTitleObject::~CTitleObject()
{
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void CTitleObject::Init(void)
{
	// Xオブジェクト生成
	CScene_X::Init();

	//CTitleObject *pTitleObject[MAX_TITLEOBJ] = {};	// 3Dアイテム
	//int nCount = 0;

	//for (int nCntLayer = 0; nCntLayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntLayer++)
	//{
	//	if ((CTitleObject *)CScene::GetActor(CScene::ACTOR_BLOCK, CScene::LAYER_3DOBJECT, nCntLayer))
	//	{
	//		pTitleObject[nCount] = (CTitleObject*)CScene::GetActor(CScene::ACTOR_BLOCK, CScene::LAYER_3DOBJECT, nCntLayer);

	//		pTitleObject[nCount]->BindModel(m_pmodel_info[nCount].GetModel_info());

	//		nCount++;
	//	}
	//}

	//for (int nCntModel = 0; nCntModel < MAX_TITLEOBJ; nCntModel++)
	//{
	//	// モデル情報設定
	//	pTitleObject[nCntModel]->BindModel(m_pmodel_info[nCntModel].GetModel_info());
	//}
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void CTitleObject::Uninit(void)
{
	CScene_X::Uninit();
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void CTitleObject::Update(void)
{
	CDebugproc::Print("座標		: %.2f,%.2f,%.2f\n", GetPos().x, GetPos().y, GetPos().z);
	/*D3DXVECTOR3 pos = D3DXVECTOR3(0,0,-2000);
	SetPos(pos);*/
	CScene_X::Update();
}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void CTitleObject::Draw(void)
{
	CScene_X::Draw();
}

// ----------------------------------------
// 作成処理
// ----------------------------------------
CTitleObject * CTitleObject::Create(void)
{
	// 変数宣言
	CTitleObject * pObject;		// シーン3Dクラス
							// メモリの生成(初め->基本クラス,後->派生クラス)
	pObject = new CTitleObject();
	// 初期化処理
	pObject->Init();
	// 生成したオブジェクトを返す
	return pObject;
}

// ----------------------------------------
// 読み込み作成処理
// ----------------------------------------
void CTitleObject::LoadCreate(void)
{
	// 変数宣言
	CTitleObject * pObject;	// ブロック
	for (int nCntModel = 0; nCntModel < m_nAll; nCntModel++)
	{
		pObject = CTitleObject::Create();					// 生成
		pObject->BindModel(m_pmodel_info[nCntModel].GetModel_info());
		pObject->SetPos(m_pload->GetInfo(nCntModel).pos);	// 位置
		pObject->SetRot(m_pload->GetInfo(nCntModel).rot);	// 回転
	}
}

// ----------------------------------------
// 読み込み処理
// ----------------------------------------
HRESULT CTitleObject::Load(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice =					// デバイスの取得
		CManager::GetRenderer()->GetDevice();

	char cModelfile[MAX_TITLEOBJ][128] =			// モデルファイル名
	{
		"data/MODEL/object/stage.x",
		"data/MODEL/object/curtain.x"
	};

	// ロード生成
	m_pload = new CLoad[MAX_TITLEOBJ];
	// ロード読み込み
	m_nAll = m_pload->Load("data/LOAD/OBJECT/Tit_obj_Location.txt");
	// モデル情報生成
	m_pmodel_info = new CModel_info[MAX_TITLEOBJ];
	// モデル読み込み
	for (int nCntModel = 0; nCntModel < MAX_TITLEOBJ; nCntModel++)
	{
		m_pmodel_info[nCntModel].Load(pDevice, cModelfile[nCntModel]);
	}
	return S_OK;
}

// ----------------------------------------
// unload処理
// ----------------------------------------
void CTitleObject::UnLoad(void)
{
	// モデルの描画情報破棄
	for (int nCntModelLoad = 0; nCntModelLoad < MAX_TITLEOBJ; nCntModelLoad++)
	{
		//モデルの破棄
		m_pmodel_info[nCntModelLoad].Unload();
	}

	delete[] m_pmodel_info;
	//m_pmodel_info = NULL;
	// ロードの破棄
	delete[] m_pload;
	//m_pload = NULL;
}

// ----------------------------------------
// 位置の設定処理
// ----------------------------------------
void CTitleObject::SetPos(D3DXVECTOR3 pos)
{
	CScene_X::SetPos(pos);
}

// ----------------------------------------
// 回転の設定処理
// ----------------------------------------
void CTitleObject::SetRot(D3DXVECTOR3 rot)
{
	CScene_X::SetRot(rot);
}

// ----------------------------------------
// 位置の取得処理
// ----------------------------------------
D3DXVECTOR3 CTitleObject::GetPos(void)
{
	return CScene_X::GetPos();
}