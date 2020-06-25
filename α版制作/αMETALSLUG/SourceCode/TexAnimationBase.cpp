//------------------------------------------------------------------------------
//
//テクスチャアニメーションの基底クラス  [TexAnimationBase.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "manager.h"
#include "TexAnimationBase.h"
#include "SceneBase.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CTexAnimationBase::CTexAnimationBase()
{
	//初期化
	m_nPatternAnim = 0;
	m_nCntAnim = 0;
	m_nCntSwitch = 0;
	m_bLoop = false;
	m_EffectTex = CTexture::SEPARATE_TEX_EFFECT_EXPLOSION01;
}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CTexAnimationBase::~CTexAnimationBase()
{
}

//------------------------------------------------------------------------------
//アニメーションの更新
//アニメーション終了でfalseを返す
//------------------------------------------------------------------------------
bool CTexAnimationBase::UpdateAnimation(CSceneBase *pSceneBase)
{
	bool bDelete = false;	 //削除フラグ

	if (m_nLife-- <= 0)
	{
		bDelete = false;
	}
	//カウンターを進める
	m_nCntAnim++;

	//2フレームごとに
	if (m_nCntAnim % m_nCntSwitch == 0)
	{
		//パターンを進める
		m_nPatternAnim++;

		//最後のパターンまで進んだ時
		if (m_nPatternAnim >= CTexture::GetSparateTex_UVCnt(m_EffectTex).x *  CTexture::GetSparateTex_UVCnt(m_EffectTex).y)
		{
			m_bLoop ?
				m_nPatternAnim = 0 :		//ループする時		パターン最初に戻す
				bDelete = true;				//ループしない時　	フラグを立てる
		}

		//UV座標設定
		D3DXVECTOR2 UV;
		UV.x = m_nPatternAnim % (int)CTexture::GetSparateTex_UVCnt(m_EffectTex).x * CTexture::GetSparateTex_UVSize(m_EffectTex).x;
		UV.y = m_nPatternAnim / (int)CTexture::GetSparateTex_UVCnt(m_EffectTex).x * CTexture::GetSparateTex_UVSize(m_EffectTex).y;

		//テクスチャアニメーション処理
		pSceneBase->SetAnimation(UV, CTexture::GetSparateTex_UVSize(m_EffectTex));
	}
	return bDelete;
}

