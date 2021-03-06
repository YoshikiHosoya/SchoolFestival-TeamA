//------------------------------------------------------------------------------
//
//モデルビューワ用処理  [Debug_ModelViewer.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _DEBUG_MODELVIEWER_H_
#define _DEBUG_MODELVIEWER_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "../main.h"
#include "../BaseMode.h"

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CDebug_ViewerCharacter;
class CModel;

class CDebug_ModelViewer : public CBaseMode
{
public:

	CDebug_ModelViewer();
	~CDebug_ModelViewer();
	HRESULT Init();								//初期化
	void Uninit();								//終了
	void Update();								//更新
	void Draw();								//描画
	void ShowDebugInfo();						//デバッグ情報表記

	CMap *GetMap() { return nullptr; };			//マップ
	CPlayer* GetPlayer() { return nullptr; };	//プレイヤーのポインタ取得


	static void OffsetViewer(std::vector<CModel*> vModelList);
	static HRESULT SaveModelOffset(std::vector<CModel*> vModelList);
private:
	bool m_bModel;
	CDebug_ViewerCharacter *m_pViewerCharacter;
};

#endif