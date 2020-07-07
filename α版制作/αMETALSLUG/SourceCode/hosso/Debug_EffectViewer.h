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
class CParticleParam;
class CDebug_WorldLine;
class C3DLine;

class CDebug_EffectViewer : public CBaseMode
{
public:

	CDebug_EffectViewer();
	~CDebug_EffectViewer();
	HRESULT Init();						//初期化
	void Uninit();						//終了
	void Update();						//更新
	void Draw();						//描画
	void ShowDebugInfo();				//デバッグ情報表記

	CMap *GetMap() { return nullptr; };
	CPlayer* GetPlayer() { return nullptr; };

private:
	CDebug_WorldLine *m_pWorldLine;						//ワールド線
	std::unique_ptr<CParticleParam> m_pParticleParam;	//パーティクルのパラメータ

	bool m_bLoop;										//ループさせるか
	int m_nLoopInterval;								//ループのインターバル
	int m_nCnt;											//カウント

	C3DLine *m_p3DLine;									//3Dの線 Shapeとかrotを視覚化する為

};

#endif