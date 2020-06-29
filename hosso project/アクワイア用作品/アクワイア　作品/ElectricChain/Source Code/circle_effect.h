//------------------------------------------------------------------------------
//
//円のエフェクト処理  [circle_effect.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _CIRCLE_EFFECT_H_
#define _CIRCLE_EFFECT_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "meshcircle.h"

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CCircle_Effect : public CMeshCircle
{
public:
	CCircle_Effect();			//コンストラクタ
	~CCircle_Effect();			//デストラクタ

	HRESULT Init();				//初期化
	void Uninit();				//終了
	void Update();				//更新
	void Draw();				//描画
	void ShowDebugInfo();		//デバッグ情報表記

	static std::shared_ptr<CCircle_Effect> Create(D3DXVECTOR3 const pos,D3DXCOLOR col, int const nLife, float const fRadius ,float const fWidth, int const nSeparate,
												float const fRaidiusAddValue, float const fWidthAddValue,float const fAlphaDanpingValue);	//生成処理

private:
	int m_nLife;						//ライフ
	float m_fAlphaDampingValue;			//アルファ値の減少量
	float m_fRadiusAddValue;			//半径の増加量
	float m_fWidthAddValue;				//幅の増加量
};
#endif