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

	enum TEX_TYPE
	{
		TEX_NONE = 0,

		//UI関係
		TEX_UI_PRESS_ANY_BUTTON,

		TEX_UI_TITLE_LOGO,						//タイトルロゴ
		TEX_UI_TITLE_BG,						//タイトル背景

		TEX_UI_GAME_COMBO,						//コンボ
		TEX_UI_GAME_KILL,						//キル
		TEX_UI_GAME_PLAYERICON,					//プレイヤーアイコン
		TEX_UI_GAME_X_COMBOPATTERN,				//コンボパターン XInput
		TEX_UI_GAME_KEY_COMBOPATTERN,			//コンボパターン Keyboard
		TEX_UI_GAME_TIME,						//タイム

		TEX_UI_RESULT_LOGO,						//リザルトロゴ
		TEX_UI_RESULT_RESULTCALC,				//スコア計算

		TEX_UI_RANKING_LOGO,					//ランキングロゴ
		TEX_UI_RANKING_BG,						//ランキング背景
		TEX_UI_RANKING_1ST,						//1
		TEX_UI_RANKING_2ND,						//2
		TEX_UI_RANKING_3RD,						//3
		TEX_UI_RANKING_4TH,						//4
		TEX_UI_RANKING_5TH,						//5

		TEX_UI_TUTORIAL_X_SKIP,					//チュートリアル XInput　移動
		TEX_UI_TUTORIAL_X_MOVE,					//チュートリアル XInput　ダッシュ
		TEX_UI_TUTORIAL_X_DASH,					//チュートリアル XInput　ダッシュ
		TEX_UI_TUTORIAL_X_CAMERAMOVE,			//チュートリアル XInput　カメラ回転
		TEX_UI_TUTORIAL_X_CAMERARESET,			//チュートリアル XInput　始点リセット
		TEX_UI_TUTORIAL_X_JUMP,					//チュートリアル XInput　ジャンプ
		TEX_UI_TUTORIAL_X_ATTACK,				//チュートリアル XInput　攻撃
		TEX_UI_TUTORIAL_X_STARTCHAIN,			//チュートリアル XInput　連鎖
		TEX_UI_TUTORIAL_X_CHAINTHUNDER,			//チュートリアル XInput　連鎖爆発の説明

		TEX_UI_TUTORIAL_KEY_SKIP,				//チュートリアル Keyboard　移動
		TEX_UI_TUTORIAL_KEY_MOVE,				//チュートリアル Keyboard　ダッシュ
		TEX_UI_TUTORIAL_KEY_DASH,				//チュートリアル Keyboard　ダッシュ
		TEX_UI_TUTORIAL_KEY_CAMERAMOVE,			//チュートリアル Keyboard　カメラ回転
		TEX_UI_TUTORIAL_KEY_CAMERARESET,		//チュートリアル Keyboard　始点リセット
		TEX_UI_TUTORIAL_KEY_JUMP,				//チュートリアル Keyboard　ジャンプ
		TEX_UI_TUTORIAL_KEY_ATTACK,				//チュートリアル Keyboard　攻撃
		TEX_UI_TUTORIAL_KEY_STARTCHAIN,			//チュートリアル Keyboard　連鎖
		TEX_UI_TUTORIAL_KEY_CHAINTHUNDER,		//チュートリアル Keyboard　連鎖爆発の説明

		TEX_UI_TUTORIAL_FREE,					//チュートリアル　自由
		TEX_UI_TUTORIAL_END,					//チュートリアル　終了
		TEX_UI_TUTORIAL_OK,						//チュートリアル　OK

		TEX_UI_PAUSE_LOGO,						//ポーズロゴ
		TEX_UI_OPTION_LOGO,						//オプションロゴ

		TEX_MINIMAP_MAP,						//ミニマップ
		TEX_MINIMAP_PLAYER,						//プレイヤー
		TEX_MINIMAP_ENEMY,						//敵
		TEX_MINIMAP_EXPLOSION,					//爆発

		TEX_GAMESTART,							//ゲームスタート
		TEX_FINISH,								//終了

		TEX_MESH_FIELD,							//メッシュフィールド
		TEX_ORBIT_NORMAL,						//軌跡
		TEX_EFFECT_PARTICLE,					//パーティクル
		TEX_SPHEREEXPLOISON,					//スフィアの雷
		TEX_CIRCLETHUNDER,						//円の雷
		TEX_EXPLOSION_TRACE,					//爆発跡

		TEX_BACKUI_PUSH_B,						//pushB	XInput
		TEX_BACKUI_PUSH_Z,						//pushB Keyboard
		TEX_BACKUI_DAMAGED,						//被弾
		TEX_BACKUI_RAIN,						//雨

		TEX_MAX									//MAX
	};

	//アニメーション用のテクスチャ
	enum SEPARATE_TEX_TYPE
	{
		SEPARATE_TEX_UI_NUMBER,							//数字
		SEPARATE_TEX_UI_PAUSE_MENU,						//ポーズメニュー
		SEPARATE_TEX_UI_ON_OFF,							//ON_OFF
		SEPARATE_TEX_UI_OPTIONMENU,						//オプションメニュー

		SEPARATE_TEX_EFFECT_FLASH,						//背景の落雷
		SEPARATE_TEX_EFFECT_BACKTHUNDER,				//背景の落雷
		SEPARATE_TEX_EFFECT_LINETHUNDER,				//線の雷
		SEPARATE_TEX_EFFECT_PUSHING_B,					//PushB
		SEPARATE_TEX_EFFECT_CHAINELECTRIC,				//連鎖爆発
		SEPARATE_TEX_EFFECT_CHAINTHUNDER,				//連鎖爆発開始
		SEPARATE_TEX_EFFECT_HIT_SPARK,					//ヒットエフェクト　火花
		SEPARATE_TEX_EFFECT_HIT_STAN,					//ヒットエフェクト　スタン時
		SEPARATE_TEX_EFFECT_HIT_SLASH,					//ヒットエフェクト　斬撃
		SEPARATE_TEX_EFFECT_SMOKE,						//煙
		SEPARATE_TEX_EFFECT_SPARKEXPLOSION,				//電撃の爆発っぽいの
		SEPARATE_TEX_EFFECT_STANING,					//スタン状態
		SEPARATE_TEX_EFFECT_TITLESPARK,					//タイトルの最初の電撃
		SEPARATE_TEX_EFFECT_ENEMY_RESPAWN,				//敵出現する時のエフェクト
		SEPARATE_TEX_EFFECT_GAME_START,					//ゲーム開始のエフェクト

	};

	static void TexLoad(HWND hwnd);						//テクスチャ生成
	static void TexUnload();							//テクスチャ破棄

	static LPDIRECT3DTEXTURE9 GetTexture(TEX_TYPE textype);							//通常テクスチャの取得
	static LPDIRECT3DTEXTURE9 GetSeparateTexture(SEPARATE_TEX_TYPE textype);		//分割テクスチャ取得
	static D3DXVECTOR2 GetSparateTex_UVSize(SEPARATE_TEX_TYPE textype);				//分割テクスチャ　UVのサイズ取得
	static D3DXVECTOR2 GetSparateTex_UVCnt(SEPARATE_TEX_TYPE textype);				//分割テクスチャ　UVの枚数取得


private:
	static std::vector<LPDIRECT3DTEXTURE9> m_apTextureList;							//通常テクスチャへのポインタのリスト
	static std::vector<LPDIRECT3DTEXTURE9> m_apSeparateTextureList;					//分割テクスチャへのポインタのリスト

	static std::vector<D3DXVECTOR2> m_UVSizeList;									//UVのサイズのリスト
	static std::vector<D3DXVECTOR2> m_UVCntList;									//UVの枚数のリスト
	static std::vector<std::string> m_aTexFileName;									//通常テクスチャのファイル名
	static std::vector<std::string> m_aSeparateTexFileName;							//分割テクスチャのファイル名

};

#endif