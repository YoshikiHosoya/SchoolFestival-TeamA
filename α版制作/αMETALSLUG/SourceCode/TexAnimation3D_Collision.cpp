//------------------------------------------------------------------------------
//
//当たり判定付きテクスチャアニメーション3D処理  [TexAnimation3D_Collision.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "TexAnimation3D_Collision.h"
#include "manager.h"
#include "renderer.h"
#include "collision.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CTexAnimation3D_Collision::CTexAnimation3D_Collision()
{

}
//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CTexAnimation3D_Collision::CTexAnimation3D_Collision(OBJ_TYPE obj) : CTexAnimation3D(obj)
{

}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CTexAnimation3D_Collision::~CTexAnimation3D_Collision()
{
	if(m_pCollision)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CTexAnimation3D_Collision::Init()
{
	//初期化処理
	if (FAILED(CTexAnimation3D::Init()))
	{
		return E_FAIL;
	}
	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CTexAnimation3D_Collision::Uninit()
{
	//終了処理
	CTexAnimation3D::Uninit();
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CTexAnimation3D_Collision::Update()
{
	//更新処理
	CTexAnimation3D::Update();

	Collision();
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CTexAnimation3D_Collision::Draw()
{
	//描画処理
	CTexAnimation3D::Draw();
}
//------------------------------------------------------------------------------
//デバッグ情報表示
//------------------------------------------------------------------------------
void CTexAnimation3D_Collision::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //_DEBUG
}
//------------------------------------------------------------------------------
//生成処理
//------------------------------------------------------------------------------
void CTexAnimation3D_Collision::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, CTexture::SEPARATE_TEX_TYPE type, int nCntSwitch, CScene::OBJ_TYPE objtype, bool bPlayer)
{
	//メモリ確保
	CTexAnimation3D_Collision *pTexAnimation = new CTexAnimation3D_Collision(objtype);

	//nullcheck
	if (pTexAnimation)
	{
		//初期化
		pTexAnimation->Init();

		//情報をいれる　Scene側
		pTexAnimation->SetPosition(pos);
		pTexAnimation->SetSize(size);
		pTexAnimation->SetRot(rot);
		pTexAnimation->BindTexture(CTexture::GetSeparateTexture(type));
		pTexAnimation->SetAnimation(ZeroVector2, CTexture::GetSparateTex_UVSize(type));
		pTexAnimation->m_bPlayer = bPlayer;

		//情報をいれる　TexAnimation側
		pTexAnimation->SetTex(type);
		pTexAnimation->SetCntSwitch(nCntSwitch);

		//当たり判定の設定
		pTexAnimation->m_pCollision = CCollision::Create();
		pTexAnimation->m_pCollision->SetPos(pTexAnimation->GetPosPtr());
		pTexAnimation->m_pCollision->SetSize(size);
		pTexAnimation->m_pCollision->DeCollisionCreate(CCollision::COLLISIONTYPE_NORMAL);
	}
}

//------------------------------------------------------------------------------
//当たり判定処理
//------------------------------------------------------------------------------
bool CTexAnimation3D_Collision::Collision()
{
	//nullcheck
	if (m_pCollision)
	{
		//プレイヤーの攻撃だった場合
		if (m_bPlayer)
		{
			//当たり判定
			m_pCollision->ForPlayerBulletCollision(1, 1, true);
		}
	}

	return false;
}
