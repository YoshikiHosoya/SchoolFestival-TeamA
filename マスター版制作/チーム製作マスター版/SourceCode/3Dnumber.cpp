//------------------------------------------------------------------------------
//
//3Dナンバー処理  [3Dnumber.cpp]
//Author:Fujiwara Masato
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "3dnumber.h"
#include "manager.h"
#include "renderer.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------
D3DXVECTOR2 C3DNumber::m_UVsize = D3DXVECTOR2(0.0f, 0.0f);

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define ANIMATION_TIME (8)

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
C3DNumber::C3DNumber()
{
	m_bChangeAnimation = false;
	m_nCntAnimation = 0;
	m_DefaultSize = ZeroVector3;
}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
C3DNumber::~C3DNumber()
{
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT C3DNumber::Init()
{
	//初期化処理
	if (FAILED(CScene3D::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void C3DNumber::Uninit()
{
	//終了処理
	CScene3D::Uninit();
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void C3DNumber::Update()
{
	//アニメーションする時
	if (m_bChangeAnimation)
	{
		//カウンタ++
		m_nCntAnimation++;

		SetSize(m_DefaultSize + (m_DefaultSize * ((ANIMATION_TIME - m_nCntAnimation) * (1.0f / ANIMATION_TIME))));

		//アニメーションの時間に達したとき
		if (m_nCntAnimation >= ANIMATION_TIME)
		{
			m_bChangeAnimation = false;
			m_nCntAnimation = 0;
		}
	}
	//更新処理
	CScene3D::Update();
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void C3DNumber::Draw()
{
	//無駄な桁数は省く
	if (GetDisp())
	{
		//描画処理
		CScene3D::Draw();
	}

}
//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void C3DNumber::ShowDebugInfo()
{
#ifdef _DEBUG

#endif // _DEBUG

}
//------------------------------------------------------------------------------
//生成処理
//------------------------------------------------------------------------------
std::unique_ptr<C3DNumber> C3DNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	std::unique_ptr<C3DNumber> pNumber(new C3DNumber);

	//nullcheck
	if (pNumber)
	{
		//初期化
		pNumber->Init();

		//テクスチャ設定
		pNumber->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_NUM));
		pNumber->SetPosition(pos);
		pNumber->SetSize(size);
		pNumber->m_DefaultSize = size;

		//return
		return pNumber;
	}
	return nullptr;
}

