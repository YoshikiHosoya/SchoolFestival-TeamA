//------------------------------------------------------------------------------
//
//テクスチャ管理  [texture.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

#ifndef _TEXTURE_H_
#define _TEXTURE_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
//前方宣言
class CTexture
{
public:
	CTexture() {};
	~CTexture() {};

	//通常のテクスチャ
	enum TEX_TYPE
	{
		TEX_NONE = 0,

		TEX_EFFECT_PARTICLE,					//パーティクル
		TEX_BULLET_HANDGUN,						//ハンドガンの弾
		TEX_ITEM_HEAVYMACHINEGUN,				//ヘビーマシンガン
		TEX_ITEM_SHOTGUN,						//ショットガン
		TEX_ITEM_LASERGUN,						//レーザーガン
		TEX_ITEM_ROCKETLAUNCHER,				//ロケットランチャー
		TEX_ITEM_FLAMESHOT,						//フレイムショット

		TEX_MAX									//MAX
	};

	//アニメーション用のテクスチャ
	//分割されているテクスチャ
	enum SEPARATE_TEX_TYPE
	{
		SEPARATE_TEX_NONE = 0,

		SEPARATE_TEX_EFFECT_EXPLOSION01,			//爆発
		SEPARATE_TEX_EFFECT_SHOTFLASH,				//発砲時の光
		SEPARATE_TEX_EFFECT_SPARK,					//電撃
		SEPARATE_TEX_EFFECT_HITEFFECT,				//着弾エフェクト
		SEPARATE_TEX_EFFECT_SMOKE,					//煙

		SEPARATE_TEX_MAX							//MAX
	};

	typedef struct
	{
		LPDIRECT3DTEXTURE9 m_apSeparateTexture;		//分割テクスチャへのポインタ
		std::string m_aSeparateTexFileName;			//分割テクスチャの名前
		SEPARATE_TEX_TYPE type;						//テクスチャの種類
		D3DXVECTOR2 m_UVCnt;							//UVの枚数
		D3DXVECTOR2 m_UVSize;						//UVの大きさ

	}SEPARATE_TEX_INFO;

	static void TexLoad(HWND hwnd);						//テクスチャ生成
	static void TexUnload();							//テクスチャ破棄

	static LPDIRECT3DTEXTURE9 GetTexture(TEX_TYPE textype);							//通常テクスチャの取得

	static LPDIRECT3DTEXTURE9 GetSeparateTexture(SEPARATE_TEX_TYPE textype);		//分割テクスチャ取得
	static D3DXVECTOR2 GetSparateTex_UVSize(SEPARATE_TEX_TYPE textype);				//分割テクスチャ　UVのサイズ取得
	static D3DXVECTOR2 GetSparateTex_UVCnt(SEPARATE_TEX_TYPE textype);					//分割テクスチャ　UVの枚数取得


private:
	static std::vector<LPDIRECT3DTEXTURE9> m_apTextureList;							//通常テクスチャへのポインタのリスト
	static std::vector<std::string> m_aTexFileName;									//通常テクスチャのファイル名

	static std::vector<SEPARATE_TEX_INFO> m_apSeparateTexInfoList;					//分割テクスチャに関する情報のポインタ

};

#endif