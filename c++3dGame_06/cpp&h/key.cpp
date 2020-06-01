// ----------------------------------------
//
// 鍵処理の説明[key.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
#include "key.h"
#include "model_info.h"
#include "player.h"
#include "gate.h"
// ----------------------------------------
//
// 静的変数宣言
//
// ----------------------------------------
CModel_info	*CKey::m_pmodel_info = NULL;					// モデル情報
D3DXVECTOR3 CKey::m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
bool CKey::m_bGet = false;
// ----------------------------------------
// イニシャライザコンストラクタ
// ----------------------------------------
CKey::CKey() : CScene_X::CScene_X(ACTOR_X, LAYER_3DOBJECT)
{
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CKey::~CKey()
{
	m_bGet = false;
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void CKey::Init(void)
{
	// Xオブジェクト生成
	CScene_X::Init();
	// モデル情報設定
	CScene_X::BindModel(m_pmodel_info->GetModel_info());
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void CKey::Uninit(void)
{
	CScene_X::Uninit();
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void CKey::Update(void)
{
	CPlayer *pPlayer = NULL;	// プレイヤー

	for (int nCntlayer = 0; nCntlayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntlayer++)
	{
		if (pPlayer = (CPlayer *)CScene::GetActor(CScene::ACTOR_PLAYER, CScene::LAYER_3DOBJECT, nCntlayer)) break;
	}

	SetRot(GetRot() + D3DXVECTOR3(0.0, 0.03f,0.0f));

	// アイテムの取得
	if (CCalculation::Collision_Circle(
		D3DXVECTOR3(GetPos().x, GetPos().y + 100, GetPos().z),
		// 自分の位置
		200.0f, 		// 自分の半径
		D3DXVECTOR3(pPlayer->GetPos().x, pPlayer->GetPos().y - 100, pPlayer->GetPos().z), 			// 相手の位置
		PLAYERCOLLISION_SIZE))		// 相手の半径
	{
		CGate::LoadCreate();
		m_bGet = true;
		Release();
	}

	CScene_X::Update();
}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void CKey::Draw(void)
{
	CScene_X::Draw();
}

// ----------------------------------------
// 作成処理
// ----------------------------------------
CKey * CKey::Create(void)
{
	// 変数宣言
	CKey * pKey;		// シーン3Dクラス
						// メモリの生成(初め->基本クラス,後->派生クラス)
	pKey = new CKey();
	// 初期化処理
	pKey->Init();
	// 座標設定
	pKey->SetPos(m_pos);
	// 生成したオブジェクトを返す
	return pKey;
}

// ----------------------------------------
// 読み込み処理
// ----------------------------------------
HRESULT CKey::Load(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice =					// デバイスの取得
		CManager::GetRenderer()->GetDevice();
	char cModelfile[1][128] =			// モデルファイル名
	{
		"data/MODEL/object/key.x",
	};
	D3DXVECTOR3 pos =
	{
		D3DXVECTOR3(0.0f, 150, 1200.0f)
	};

	m_pos = pos;

	// モデル情報生成
	m_pmodel_info = new CModel_info;
	// モデル読み込み
	m_pmodel_info->Load(pDevice, cModelfile[0]);
	return S_OK;
}

// ----------------------------------------
// unload処理
// ----------------------------------------
void CKey::UnLoad(void)
{
	// モデルの破棄
	m_pmodel_info->Unload();
	delete m_pmodel_info;
	m_pmodel_info = NULL;
}

// ----------------------------------------
// 位置の設定処理
// ----------------------------------------
void CKey::SetPos(D3DXVECTOR3 pos)
{
	CScene_X::SetPos(pos);
}

// ----------------------------------------
// 回転の設定処理
// ----------------------------------------
void CKey::SetRot(D3DXVECTOR3 rot)
{
	CScene_X::SetRot(rot);
}

// ----------------------------------------
// 位置の取得処理
// ----------------------------------------
D3DXVECTOR3 CKey::GetPos(void)
{
	return CScene_X::GetPos();
}

// ----------------------------------------
// プレイヤーがカギを手に入れたかどうかのフラグを取得
// ----------------------------------------
bool CKey::bGetFlag(void)
{
	return m_bGet;
}
