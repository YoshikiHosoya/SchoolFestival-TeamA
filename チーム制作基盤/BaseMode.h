#pragma once
//==========================================================
//ベースモード処理  [basemode.cpp]
//==========================================================
#ifndef _MODE_H_
#define _MODE_H_
//==========================================================
//インクルード
//==========================================================
#include "main.h"

//==========================================================
//クラス定義
//==========================================================
//前方宣言
class CPlayer;
class CCreateMap;
class CBaseMode
{
public:
	CBaseMode() {};
	virtual ~CBaseMode() {};

	virtual HRESULT Init() = 0;				//初期化
	virtual void Uninit() = 0;				//終了
	virtual void Update() = 0;				//更新
	virtual void Draw() = 0;				//描画
	virtual void ShowDebugInfo() = 0;		//デバッグ情報表記
	virtual CCreateMap *GetCreateMap() = 0;	//クリエイトマップ
	void DebugCommand(void);				//デバッグコマンド
	static void BaseLoad(HWND hWnd);		//全ての場面で使われるであろう素材の生成
	static void BaseUnload(void);			//全ての場面で使われるであろう素材の破棄
	virtual CPlayer* GetPlayer() = 0;		//プレイヤーのポインタ取得
private:
};

#endif