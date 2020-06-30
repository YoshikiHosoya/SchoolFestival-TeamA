//------------------------------------------------------------------------------
//
//ポーズ処理  [title.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _PAUSE_H_
#define _PAUSE_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"
//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CScene2D;
class CMenu;
class COption;

class CPause : public CScene
{
public:
	CPause();
	~CPause();

	//テクスチャの種類
	enum TEX_TYPE
	{
		TEX_BG,					//背景
		TEX_LOGO,				//ロゴ
		TEX_MENU,				//メニュー
		TEX_MAX
	};

	HRESULT Init();									//初期化
	void Uninit();									//終了
	void Update();									//更新
	void Draw();									//描画
	void ShowDebugInfo();							//デバッグ情報表記
	static std::shared_ptr<CPause> Create();		//生成処理
	bool GetOptionWindow();							//オプション開いているかどうか
private:
	std::vector<std::unique_ptr<CScene2D>> m_pScene2DList;			//2Dポリゴン
	std::unique_ptr<CMenu>	m_pMenu;								//メニューへのポインタ
	std::unique_ptr<COption> m_pOption;								//オプションのポインタ

};

#endif