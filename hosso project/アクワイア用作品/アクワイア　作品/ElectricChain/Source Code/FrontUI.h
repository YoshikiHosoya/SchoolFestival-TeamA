//------------------------------------------------------------------------------
//
//前面のUI  [FrontUI.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _FRONTUI_H_
#define _FRONTUI_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "scene2D.h"
//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CFrontUI : public CScene2D
{
public:
	//エフェクトの種類
	enum TEX_TYPE
	{
		PUSH_B = 0,				//B
		PLAYER_HIT,				//プレイヤー被弾
		RAIN,					//雨
		GAMESTART,				//ゲームスタート
		MAX,
	};

	CFrontUI();
	~CFrontUI();

	HRESULT Init();				//初期化
	void Uninit();				//終了
	void Update();				//更新
	void Draw();				//描画
	void ShowDebugInfo();		//デバッグ情報表示
	static void Create(D3DXVECTOR3 pos , D3DXVECTOR3 size, D3DXCOLOR col, TEX_TYPE type);	//生成処理

private:
	TEX_TYPE m_Type;					//タイプ
	int m_nCntUI;						//カウンタ
	static bool m_bPushB;				//pushBが表示されているかどうか　重複対策
};

#endif