//------------------------------------------------------------------------------
//
//UI処理  [UI.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _UI_H_
#define _UI_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "scene2D.h"

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CMenu;

class CScene2D_UI : public CScene2D
{
public:
	CScene2D_UI();
	~CScene2D_UI();

	HRESULT Init();					//初期化
	void Uninit();					//終了
	void Update();					//更新
	void Draw();					//描画
	static std::shared_ptr<CScene2D_UI> Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, int nTexID, CScene::OBJTYPE objtype);			//生成
	void ShowDebugInfo();			//デバッグ情報表記

	void SetTexID(CTexture::TEX_TYPE TexID);		//テクスチャのID設定
	CTexture::TEX_TYPE GetTexID();					//テクスチャのID取得
protected:

private:
	CTexture::TEX_TYPE m_nTexID;					//テクスチャ番号
	int m_nCnt;										//カウント
};

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CUI : public CScene
{
public:
	//UIのシーン
	enum UI_SCENE
	{
		SCENE_TITLE = 0,			//タイトル
		SCENE_GAME,					//ゲーム
		SCENE_RESULT,				//リザルト
		SCENE_PAUSE,				//ポーズ
		SCENE_GAMEEND,				//ゲーム終了
		SCENE_RANKING,				//ランキング
		SCENE_MAX
	};

	//UIのタイプ
	enum UI_TYPE
	{
		TYPE_SCENE2D = 0,			//Scene2D
		TYPE_MENU_VERTICAL,			//縦メニュー
		TYPE_MENU_HORIZON,			//横メニュー
		TYPE_MAX
	};


	CUI(); 							//コンストラクタ
	~CUI();							//デストラクタ

	HRESULT Init();					//初期化
	void Uninit();					//終了
	void Update();					//更新
	void Draw();					//描画
	static void Create();			//生成
	void ShowDebugInfo();			//デバッグ情報表記

	static HRESULT LoadTexName();								//テクスチャ名読み込み
	HRESULT SavePlaceData();									//配置情報保存
	static HRESULT LoadPlace(UI_SCENE scene);					//配置情報読み込み

	static bool ShowTexComboBox(int &nTexID);						//Imguiのコンボボックス　テクスチャ
	static bool ShowTypeComboBox(int &nType);						//Imguiのコンボボックス　タイプ
	static LPDIRECT3DTEXTURE9 GetTexture(int nTexID);				//テクスチャ情報取得
	void DeleteAll();

protected:

private:
	static std::vector<LPDIRECT3DTEXTURE9>		m_pTextureList;			//テクスチャへのポインタ
	static std::vector<std::string>				m_aTexNameList;			//テクスチャ名のポインタ
	std::vector<std::shared_ptr<CScene2D_UI>>	m_pScene2DUIList;		//ポリゴンのポインタ
	std::vector<std::shared_ptr<CMenu>>			m_pMenuList;			//メニューのポインタ

	static std::vector<std::string>				m_aPlaceFileName;		//場所のファイル名
	static std::vector<std::string>				m_aTypeNameList;		//テクスチャ名のポインタ

};

#endif