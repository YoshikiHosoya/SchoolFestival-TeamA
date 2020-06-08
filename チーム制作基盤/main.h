//=========================================================================
//Author : Hnazawa
//[main.h]ウィンドウ表示処理
//=========================================================================
#ifndef _MAIN_H_
#define _MAIN_H_


#define _CRT_SECURE_NO_WARNINGS		// 警告除去
#define DIRECTINPUT_VERSION (0x0800)//警告対処用

#include <windows.h>
#include <stdio.h>
#include "d3dx9.h"
#include "dinput.h"
#include "xaudio2.h"
#include <Xinput.h>
#include <vector>
#include <iostream>
#include "SourceCode/hosso/HossoLibrary.h"
#include "SourceCode/ImGui/Imgui.h"
#include "SourceCode/ImGui/imgui_impl_dx9.h"
#include "SourceCode/ImGui/imgui_impl_win32.h"
#include "texture.h"
//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")		//描画処理に必要
#pragma comment(lib,"d3dx9.lib")	//[d3d9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")	//DirectXコンポーネント使用に必要
#pragma comment(lib,"winmm.lib")	//システム時間取得に必要
#pragma comment(lib,"dinput8.lib")
#pragma comment (lib, "xinput.lib")

//マクロ定義
#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE| D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//構造体定義
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	float rhm;			//1.0で固定　同次座標
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
	D3DXVECTOR3 bec;	//ベクトル
} VERTEX_2D;

typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	D3DXVECTOR3 nor;	//法線ベクトル
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
} VERTEX_3D;

int GetFps(void);
//前方宣言　　Friend

//プロトタイプ宣言

#endif