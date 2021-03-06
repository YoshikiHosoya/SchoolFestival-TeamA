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
		TEX_ITEM_BEAR,							//熊-スコアアップ
		TEX_ITEM_COIN,							//コイン-スコアアップ
		TEX_ITEM_JEWELRY,						//宝石-スコアアップ
		TEX_ITEM_MEDAL,							//メダル-スコアアップ
		TEX_ITEM_BOMBUP,						//爆弾の数加算
		TEX_ITEM_ENERGYUP,						//ガソリン
		TEX_ITEM_BULLETUP,						//残段数加算

		TEX_MESH_GRASS,							//草
		TEX_MESH_BLOCK,							//ブロック
		TEX_MESH_WATER,							//水

		TEX_UI_REMAIN,							//残機のUI
		TEX_UI_ARMS,							//弾の残数のUI
		TEX_UI_BOMB,							//グレネードの残数のUI
		TEX_UI_INFINITY,						//弾数無限のUI
		TEX_UI_FRAME,							//枠のUI

		TEX_UI_TITLE,							//タイトルロゴ
		TEX_UI_START,							//スタート

		TEX_UI_TUTORIAL_NAME,					// チュートリアル名前ロゴ
		TEX_UI_TUTORIAL_START,					// 開始宣言
		TEX_UI_TUTORIAL_ORDER1,					// チュートリアル指示1
		TEX_UI_TUTORIAL_ORDER2,					// チュートリアル指示2
		TEX_UI_TUTORIAL_ORDER3,					// チュートリアル指示3
		TEX_UI_TUTORIAL_ORDER4,					// チュートリアル指示4
		TEX_UI_TUTORIAL_ORDER5,					// チュートリアル指示5
		TEX_UI_TUTORIAL_ORDER6,					// チュートリアル指示6
		TEX_UI_TUTORIAL_FINAL,					// 終了宣言

		TEX_UI_RESULT_BG,						//背景
		TEX_UI_RESULT_NAME,						//名前ロゴ
		TEX_UI_RESULT_1P,						//1P
		TEX_UI_RESULT_2P,						//2P
		TEX_UI_RESULT_GOOD,						//評価0
		TEX_UI_RESULT_GREATE,					//評価1
		TEX_UI_RESULT_NOPRISONER,				//評価2
		TEX_UI_RESULT_MISSION1COMPLETE,			//クリアロゴ0
		TEX_UI_RESULT_MISSION2COMPLETE,			//クリアロゴ1

		TEX_UI_RANKING_NAME,					//ランキング名前ロゴ
		TEX_UI_RANKING_1st,						//ランキング1位
		TEX_UI_RANKING_2nd,						//ランキング2位
		TEX_UI_RANKING_3rd,						//ランキング3位
		TEX_UI_RANKING_4th,						//ランキング4位
		TEX_UI_RANKING_5th,						//ランキング5位

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
		SEPARATE_TEX_EFFECT_SHOTGUN,				//ショットガン
		SEPARATE_TEX_EFFECT_IMPACT00,				//インパクト
		SEPARATE_TEX_EFFECT_IMPACT01,				//インパクト
		SEPARATE_TEX_EFFECT_FIRE00,					//ファイア
		SEPARATE_TEX_EFFECT_FIRE01,					//ファイア
		SEPARATE_TEX_EFFECT_FIRE02,					//ファイア

		SEPARATE_TEX_NUM,							//ナンバー

		SEPARATE_TEX_UI_LIFE,						//体力のUI

		SEPARATE_TEX_MAX							//MAX
	};

	typedef struct
	{
		LPDIRECT3DTEXTURE9 m_apSeparateTexture;		//分割テクスチャへのポインタ
		SEPARATE_TEX_TYPE type;						//テクスチャの種類
		D3DXVECTOR2 m_UVCnt;						//UVの枚数
		D3DXVECTOR2 m_UVSize;						//UVの大きさ

	}SEPARATE_TEX_INFO;

	static void TexLoad(HWND hwnd);						//テクスチャ生成
	static void TexUnload();							//テクスチャ破棄

	static LPDIRECT3DTEXTURE9 GetTexture(TEX_TYPE textype);							//通常テクスチャの取得

	static std::vector<std::string> &GetTexFileName() { return m_aTexFileName; };						//テクスチャ名取得
	static std::vector<std::string> &GetSeparateFileName() { return m_aSeparateTexFileNameList; };		//分割テクスチャ名取得

	static LPDIRECT3DTEXTURE9 GetSeparateTexture(SEPARATE_TEX_TYPE textype);		//分割テクスチャ取得
	static D3DXVECTOR2 GetSparateTex_UVSize(SEPARATE_TEX_TYPE textype);				//分割テクスチャ　UVのサイズ取得
	static D3DXVECTOR2 GetSparateTex_UVCnt(SEPARATE_TEX_TYPE textype);				//分割テクスチャ　UVの枚数取得


private:
	static std::vector<LPDIRECT3DTEXTURE9> m_apTextureList;							//通常テクスチャへのポインタのリスト
	static std::vector<std::string> m_aTexFileName;											//通常テクスチャのファイル名


	static std::vector<std::string> m_aSeparateTexFileNameList;								//分割テクスチャのファイル名
	static std::vector<SEPARATE_TEX_INFO> m_apSeparateTexInfoList;					//分割テクスチャに関する情報のポインタ

};

#endif