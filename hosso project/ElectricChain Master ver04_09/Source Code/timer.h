//------------------------------------------------------------------------------
//
//タイマー表示処理  [timer.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _TIMER_H_
#define _TIMER_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"
//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------

//前方宣言
class CMultiNumber;

class CTimer : public CScene
{
public:
	CTimer();
	~CTimer();
	HRESULT Init();																//初期化
	void Uninit();																//終了
	void Update();																//更新
	void Draw();																//描画
	void ShowDebugInfo();														//デバッグ情報表記
	static std::unique_ptr<CTimer> Create(D3DXVECTOR3 pos,int nTimer);			//生成処理
	static int GetTimer();														//タイマー取得
	void StopTimer();															//タイマーストップ
private:
	std::shared_ptr<CMultiNumber> m_pMultiNumber;								//ナンバーのポインタ
	static LPDIRECT3DTEXTURE9 m_pTexture;										//テクスチャのポインタ

	static int m_nTimer;														//タイマー 秒で管理
	int m_nCntFlame;															//カウント フレーム
	bool m_bStop;																//ストップ
};

#endif