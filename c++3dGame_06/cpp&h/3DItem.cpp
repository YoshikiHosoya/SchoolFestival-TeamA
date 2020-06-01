// ----------------------------------------
//
// 3Dアイテム処理の説明[3ditem.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
#include "3ditem.h"
#include "model_info.h"
#include "debugproc.h"
#include "player.h"
#include "3dparticle.h"
#include "mapmark.h"
#include "gameui.h"
// ----------------------------------------
//
// マクロ定義
//
// ----------------------------------------
#define ITEMCOLLISION_3D_SIZE (200.0f)

// ----------------------------------------
//
// 静的変数宣言
//
// ----------------------------------------
LPDIRECT3DTEXTURE9 C3DItem::m_pTexture[1] = {};			// テクスチャへのポインタ
CLoad			*C3DItem::m_pload = NULL;				// ロード
CModel_info		*C3DItem::m_pmodel_info = NULL;			// モデル情報
int				C3DItem::m_nAll = 0;					// 番号
int				C3DItem::m_nShardNum = 0;				//欠片の総数
// ----------------------------------------
// コンストラクタ
// ----------------------------------------
C3DItem::C3DItem()
{
	m_Type = TYPE_SHARD;
	//m_nTotal3DItem = 0; //3Dアイテムの総数
	//m_nTotal3DItem = m_pload->GetShard();
	m_bShard = false;
	m_ID.nId = 0;
}

// ----------------------------------------
// イニシャライザコンストラクタ
// ----------------------------------------
C3DItem::C3DItem(ACTOR actor, LAYER layer) : CScene_X::CScene_X(actor, layer)
{
	m_Type = TYPE_SHARD;
	//m_nShardNum = m_pload->GetShard();
}

//C3DItem::C3DItem() : CScene_X::CScene_X(ACTOR_3DITEM, LAYER_3DOBJECT)
//{
//	m_Type = TYPE_SHARD;
//	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 現在回転量
//	m_nTotal3DItem = 0; //3Dアイテムの総数
//}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
C3DItem::~C3DItem()
{
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void C3DItem::Init(void)
{
	// Xオブジェクト生成
	CScene_X::Init();
	// モデル情報設定
	CScene_X::BindModel(m_pmodel_info->GetModel_info());
	// テクスチャー設定
	for (int nCnt = 0; nCnt < 1; nCnt++)
	{
		CScene_X::BindTexture(m_pTexture[nCnt]);
	}

	/*if (m_ID.nId == 0)
	{
		m_ID.nId += 1;
	}*/
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void C3DItem::Uninit(void)
{
	CScene_X::Uninit();
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void C3DItem::Update(void)
{
	CPlayer *pPlayer = NULL;	// プレイヤー
	for (int nCntlayer = 0; nCntlayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntlayer++)
	{
		if (pPlayer = (CPlayer *)CScene::GetActor(CScene::ACTOR_PLAYER, CScene::LAYER_3DOBJECT, nCntlayer)) break;
	}

	// アイテムの取得
	if (CCalculation::Collision_Circle(
		D3DXVECTOR3(GetPos().x, GetPos().y + 100, GetPos().z),
		// 自分の位置
		ITEMCOLLISION_3D_SIZE, 		// 自分の半径
		D3DXVECTOR3(pPlayer->GetPos().x, pPlayer->GetPos().y - 100, pPlayer->GetPos().z), 			// 相手の位置
		PLAYERCOLLISION_SIZE))		// 相手の半径
	{
		if (m_Type == TYPE_SHARD)
		{
			// SEを鳴らす
			//CManager::GetSound()->PlaySound(CSound::LABEL_SE_8);
			Except3DItem();					// 3Dアイテムの総数マイナス

			CMapMark *pMapMark = NULL;

			for (int nCntlayer = 0; nCntlayer < CScene::GetMaxLayer(CScene::LAYER_UI); nCntlayer++)
			{
				if (pMapMark = (CMapMark *)CScene::GetActor(CScene::ACTOR_MAPMARK, CScene::LAYER_UI, nCntlayer)) break;
			}

			pMapMark->ReleseMaker((this->m_ID.nId));

			//C3DParticle::Create(C3DParticle::OFFSET_ID_EXPLOSION, GetPos());
			C3DParticle::Create(C3DParticle::OFFSET_ID_EXPLOSIONWAVE, GetPos());
			CGame_ui::SetAP(1);
		}
		Release();
	}

	// 回転上限
	if (m_pmodel_info->GetModel_info().rot.y > 6.28)
	{
		m_pmodel_info->GetModel_info().rot.y = 0;
	}

	//3Dアイテムの回転量
	m_pmodel_info->GetModel_info().rot.y += 0.000314f;

	//回転の反映
	SetRot(m_pmodel_info->GetModel_info().rot);

	CScene_X::Update();
}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void C3DItem::Draw(void)
{
	CScene_X::Draw();
}

// ----------------------------------------
// 作成処理
// ----------------------------------------
C3DItem * C3DItem::Create(void)
{
	// 変数宣言
	C3DItem * p3DItem;		// シーン3Dクラス
							// メモリの生成(初め->基本クラス,後->派生クラス)
	p3DItem = new C3DItem(ACTOR_3DITEM, LAYER_3DOBJECT);
	//p3DItem = new C3DItem();
	// 初期化処理
	p3DItem->Init();
	// 生成したオブジェクトを返す
	return p3DItem;
}

// ----------------------------------------
// 読み込み作成処理
// ----------------------------------------
void C3DItem::LoadCreate(void)
{
	// 変数宣言
	C3DItem * p3DItem;

	m_nShardNum = m_nAll;

	for (int nCntItem = 0; nCntItem < m_nAll; nCntItem++)
	{
		p3DItem = C3DItem::Create();						// 生成
		p3DItem->SetPos(m_pload->GetInfo(nCntItem).pos);	// 位置
		p3DItem->SetRot(m_pload->GetInfo(nCntItem).rot);	// 回転
		// Idの設定
		p3DItem->m_ID.nId = (nCntItem);
	}
}

// ----------------------------------------
// 読み込み処理4
// ----------------------------------------
HRESULT C3DItem::Load(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice =					// デバイスの取得
		CManager::GetRenderer()->GetDevice();
	char cTex[1][128] =							// テクスチャー名
	{
		"data/TEXTURE/obj_tex/Item00.png",
	};
	char cModelfile[TYPE_MAX][128] =			// モデルファイル名
	{
		"data/MODEL/object/Shard00.x",
	};
	// テクスチャー設定
	for (int nCnt = 0; nCnt < 1; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, cTex[nCnt], &m_pTexture[nCnt]);
	}
	// ロード生成
	m_pload = new CLoad;
	// ロード読み込み
	m_nAll = m_pload->Load("data/LOAD/OBJECT/3DItem00.txt");
	// モデル情報生成
	m_pmodel_info = new CModel_info;
	// モデル読み込み
	m_pmodel_info->Load(pDevice, cModelfile[0]);
	return S_OK;
}

// ----------------------------------------
// unload処理
// ----------------------------------------
void C3DItem::UnLoad(void)
{
	// テクスチャー設定
	for (int nCnt = 0; nCnt < 1; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
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
void C3DItem::SetPos(D3DXVECTOR3 pos)
{
	CScene_X::SetPos(pos);
}

// ----------------------------------------
// 回転の設定処理
// ----------------------------------------
void C3DItem::SetRot(D3DXVECTOR3 rot)
{
	CScene_X::SetRot(rot);
}

// ----------------------------------------
// 位置の取得処理
// ----------------------------------------
D3DXVECTOR3 C3DItem::GetPos(void)
{
	return CScene_X::GetPos();
}

// ----------------------------------------
// 欠片の現在の数
// ----------------------------------------
int C3DItem::GetShardNum(void)
{
	return m_nShardNum;
}

// ----------------------------------------
// 欠片のフラグ
// ----------------------------------------
bool C3DItem::ShardFlag(void)
{
	return m_bShard;
}

// ----------------------------------------
// 3Dアイテムの総数
// ----------------------------------------
void C3DItem::Except3DItem(void)
{
	//3Dアイテムの総数を減らす
	m_nShardNum--;
}


