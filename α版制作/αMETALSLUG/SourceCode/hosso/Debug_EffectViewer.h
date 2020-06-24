//------------------------------------------------------------------------------
//
//エフェクトビューワ用処理  [Debug_EffectViewer.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _DEBUG_EFFECTVIEWER_H_
#define _DEBUG_EFFECTVIEWER_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "../main.h"
#include "../basemode.h"
//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CDebug_EffectViewer : public CBaseMode
{
public:

	CDebug_EffectViewer();
	~CDebug_EffectViewer();
	HRESULT Init();			//初期化
	void Uninit();						//終了
	void Update();						//更新
	void Draw();						//描画
	void ShowDebugInfo();				//デバッグ情報表記

	CMap *GetMap() { return nullptr; };
	CPlayer* GetPlayer() { return nullptr; };

private:
	int m_nLife;					//パーティクルのライフ
	int m_nNumParticle;				//パーティクルの数
	float m_fRadius;				//半径
	float m_fSpeed;					//速度
	float m_fRadiusDamping;			//半径の減衰
	float m_fAlphaDamping;			//アルファ値の減衰
	CTexture::TEX_TYPE m_textype;	//テクスチャ
	D3DXCOLOR m_col;				//色

	bool m_bLoop;					//ループさせるか
	int m_nLoopInterval;			//ループのインターバル
	int m_nCnt;						//カウント


};

#endif