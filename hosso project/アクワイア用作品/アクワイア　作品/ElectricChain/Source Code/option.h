//------------------------------------------------------------------------------
//
//オプション処理  [option.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _OPTION_H_
#define _OPTION_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"
//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CScene2D;

class COption : public CScene
{
public:
	COption();
	~COption();

	//テクスチャの種類
	enum TEX_TYPE
	{
		TEX_OPTION_BG,		//背景
		TEX_OPTION_LOGO,	//ロゴ
		TEX_OPTION_MENU,	//メニュー
		TEX_ON_OFF,			//ON　OFF
		TEX_MAX
	};

	enum OPTION_ITEM
	{
		OPTION_CAMERA_AUTO_ROTATION = 0,		//カメラの自動回転
		OPTION_CAMERA_FLIP_X,					//X軸反転
		OPTION_CAMERA_FLIP_Y,					//Y軸反転
		OPTOIN_MAX
	};

	HRESULT Init();									//初期化
	void Uninit();									//終了
	void Update();									//更新
	void Draw();									//描画
	void ShowDebugInfo();							//デバッグ情報表記
	static std::unique_ptr<COption> Create();		//生成処理

	//Get関数
	static bool GetAutoRotation() { return m_bAutoRotation; };		//カメラの自動回転
	static bool GetCameraFlip_X() { return m_bCameraFlip_X; };		//X軸反転
	static bool GetCameraFlip_Y() { return m_bCameraFlip_Y; };		//Y軸反転

private:
	std::vector<std::unique_ptr<CScene2D>> m_pScene2DList;			//2Dポリゴン
	std::vector<std::unique_ptr<CScene2D>> m_pOptionItemList;		//2Dポリゴンオプションのリスト
	std::vector<std::unique_ptr<CScene2D>> m_OnOffList;				//ONOFFのリスト

	int m_NowSelectItem;											//現在選択しているアイテム

	static bool m_bCameraFlip_X;		//カメラX軸の反転
	static bool m_bCameraFlip_Y;		//カメラY軸の反転
	static bool m_bAutoRotation;		//カメラ自動回転
};

#endif