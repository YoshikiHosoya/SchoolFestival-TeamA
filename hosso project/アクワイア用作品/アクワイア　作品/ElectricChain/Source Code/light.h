//-----------------------------------------------------------------------------
//
// ライト処理 [light.h]
// Author : Yoshiki Hosoya
//
//-----------------------------------------------------------------------------
#ifndef _LIGHT_H_
#define _LIGHT_H_

#define _CRT_SECURE_NO_WARNINGS

//-----------------------------------------------------------------------------
// インクルードファイル
//-----------------------------------------------------------------------------
#include "main.h"

//-----------------------------------------------------------------------------
// マクロ
//-----------------------------------------------------------------------------
#define MAX_LIGHT (3)
//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CLight
{
public:
	CLight();
	~CLight();
	void Init();				//初期化
	void Uninit();				//終了
	void Update();				//更新
	void ShowLightInfo();		//imgui ライト情報表示
	D3DXVECTOR3 GetLightDir();	//ライトの方向取得　1番目のライトだけでいい
private:
	D3DLIGHT9 m_aLight[MAX_LIGHT];		//ライト
	D3DXVECTOR3 m_vecDir[MAX_LIGHT];	//ライトの向き
};

#endif