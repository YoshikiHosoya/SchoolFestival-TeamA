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
	CTexAnimation3D_Collision *pEffectAnimation = new CTexAnimation3D_Collision(objtype);

	//nullcheck
	if (pEffectAnimation)
	{
		//初期化
		pEffectAnimation->Init();

		//情報をいれる　Scene側
		pEffectAnimation->SetPosition(pos);
		pEffectAnimation->SetSize(size);
		pEffectAnimation->SetRot(rot);
		pEffectAnimation->BindTexture(CTexture::GetSeparateTexture(type));
		pEffectAnimation->SetAnimation(ZeroVector2, CTexture::GetSparateTex_UVSize(type));
		pEffectAnimation->m_bPlayer = bPlayer;

		//情報をいれる　TexAnimation側
		pEffectAnimation->SetTex(type);
		pEffectAnimation->SetCntSwitch(nCntSwitch);

		pEffectAnimation->m_pCollision = CCollision::Create();
		pEffectAnimation->m_pCollision->SetPos(pEffectAnimation->GetPosPtr());
		pEffectAnimation->m_pCollision->SetSize(size);
		pEffectAnimation->m_pCollision->DeCollisionCreate(CCollision::COLLISIONTYPE_BLOCK);
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
