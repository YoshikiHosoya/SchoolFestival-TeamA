// =====================================================================================================================================================================
//
// アイテム処理の説明[item.h]
// Author : Fujiwara Masato
//
// =====================================================================================================================================================================
#ifndef _ITEM_H_
#define _ITEM_H_	 // ファイル名を基準を決める

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "scene3D.h"

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// アイテムクラス
// =====================================================================================================================================================================
class CItem : public CScene3D
{
public:
	/* 列挙型 */
	// タイプ
	typedef enum
	{
		ITEMTYPE_NONE = 0,
		ITEMTYPE_HEAVYMACHINEGUN,	//ヘビーマシンガン
		ITEMTYPE_SHOTGUN,			//ショットガン
		ITEMTYPE_LASERGUN,			//レーザーガン
		ITEMTYPE_ROCKETLAUNCHER,	//ロケットランチャー
		ITEMTYPE_FLAMESHOT,			//フレイムショット
		ITEMTYPE_MAX
	} ITEMTYPE;

	/* 関数 */
	CItem(OBJ_TYPE type);														// コンストラクタ
	~CItem();																	// デストラクタ

	/* メンバ関数 */
	HRESULT						Init();											// 初期化
	void						Uninit();										// 終了
	void						Update();										// 更新
	void						Draw();											// 描画
	void						ItemType(ITEMTYPE type);						// アイテム取得時の種類別処理

	/* 静的メンバ関数 */
	static	CItem				*Create(D3DXVECTOR3 pos, ITEMTYPE type);		// アイテムの生成
	static	void				SwitchTexture(ITEMTYPE type, CItem *pItem);		// 種類別テクスチャ設定

protected:
private:
	/* メンバ変数 */
	ITEMTYPE					m_Type;											// アイテムタイプ
	D3DXMATRIX					m_mtxWorld;										// ワールドマトリックス
};
#endif