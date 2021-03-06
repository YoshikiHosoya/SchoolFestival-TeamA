//------------------------------------------------------------------------------
//
//シーン処理  [scene.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _SCENE_H_
#define _SCENE_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CScene2D;

class CScene
{
public:

	enum OBJTYPE
	{
		OBJTYPE_NONE = 0,					//未設定
		OBJTYPE_BACK,						//後ろ
		OBJTYPE_MAPOBJECT,					//マップに配置されるオブジェクト
		OBJTYPE_MESHFIELD,
		OBJTYPE_WAY,
		OBJTYPE_PLAYER,						//プレイヤー
		OBJTYPE_ENEMY,						//敵
		OBJTYPE_BULLET,						//弾
		OBJTYPE_ORBIT,						//軌跡
		OBJTYPE_2DGAUGE,					//2Dゲージ
		OBJTYPE_3DGAUGE,					//3Dゲージ
		OBJTYPE_EFFECT,						//エフェクト
		OBJTYPE_UI,							//UI
		OBJTYPE_NUMBER,						//数字
		OBJTYPE_2DEFFECT,					//エフェクト
		OBJTYPE_MINIMAP,					//ミニマップ
		OBJTYPE_FRONTUI,					//バックUI
		OBJTYPE_PAUSE,						//ポーズ
		OBJTYPE_OPTION,						//オプション
		OBJTYPE_FRONT,						//前面
		OBJTYPE_DEBUG,						//デバッグ系
		OBJTYPE_MAX							//最大値
	};

	CScene();

	//純粋仮想関数　オーバーライド用
	virtual ~CScene();
	virtual HRESULT Init() = 0;														//初期化
	virtual void Uninit() = 0;														//終了
	virtual void Update() = 0;														//更新
	virtual void Draw() = 0;														//描画
	virtual void ShowDebugInfo() = 0;												//デバッグ情報表記

	static void ShowNumAll();

	static void ReleaseAll();														//メモリ開放
	static void UpdateAll();														//更新処理
	static void DrawAll();															//描画処理
	static void ShowDebugInfoAll();													//全てのデバッグ情報表記処理

	static void ReleaseSpecificObject(OBJTYPE objtype);								//選択したオブジェクトタイプを全てリリース

	CScene::OBJTYPE GetObjType()				{ return m_objtype; };				//オブジェクトの種類取得
	static int GetNumAll()						{ return m_nNumAll; };				//総数取得

	void Release()								{ m_bDeadFlag = true; };			//メモリ開放
	void SetObjType(OBJTYPE objtype)			{ m_objtype = objtype; };			//オブジェクトタイプ設定関数

	static void SetStop(bool bStop)				{ m_bStop = bStop; };				//ストップ処理
	static void Set1FAction()					{ m_b1FAction = true; };			//１Fだけ進める処理

	static void GetSceneList(OBJTYPE objtype, std::vector<std::shared_ptr<CScene>> &SceneList);			//シーン情報取得（配列ごと）
	static bool GetStop()						{ return m_bStop; };				//ストップ状態か取得

	template <class T> void AddUniqueList(T ptr)		 //リストに追加
	{
		//ユニークポインタのリストに自分を追加
		m_UniqueSceneList[ptr->m_objtype].emplace_back(std::move(ptr));
	};

	template <class T> void AddSharedList(T ptr) 		//リストに追加
	{
		//共有ポインタのリストに自分を追加
		m_SharedSceneList[m_objtype].emplace_back(ptr);
	};

protected:

private:
	static int m_nNumAll;					//オブジェクト総数
	static int m_nCntStop;					//ストップのカウント
	static std::vector<std::unique_ptr<CScene>> m_UniqueSceneList[OBJTYPE_MAX];		//ユニークポインタ　独占すべきポインタ
	static std::vector<std::shared_ptr<CScene>> m_SharedSceneList[OBJTYPE_MAX];		//シェアポインタ	共有される事があると思われるポインタ
	static bool m_bStop;					//画面ストップするかどうか
	static bool m_b1FAction;				//1Fだけアクションするか

	bool m_bNonStop;						//ストップしない
	bool m_bDeadFlag;						//死亡フラグ
	OBJTYPE	m_objtype;						//タイプ

	static std::vector<int> m_fUpdateTimeList;
	static std::vector<int> m_fDrawTimeList;
};

#endif

