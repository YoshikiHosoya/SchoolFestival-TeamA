// =====================================================================================================================================================================
//
// オブジェクトモデルの処理 [objectmodel.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _OBJECTMODEL_H_
#define _OBJECTMODEL_H_

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "scene.h"
#include "sceneX.h"

// =====================================================================================================================================================================
// オブジェクトモデルクラス
// =====================================================================================================================================================================
class CObjectModel : public CSceneX
{
public:
	// オブジェクトの種類
	enum OBJECTTYPE
	{
		OBJECTTYPE_NONE = -1,
		OBJECTTYPE_STONE,						// 石
		OBJECTTYPE_BOX,							// 箱
		OBJECTTYPE_GROUND_L,					// 地面 (大
		OBJECTTYPE_GROUND_M,					// 地面 (中
		OBJECTTYPE_GROUND_S,					// 地面 (小
		OBJECTTYPE_GAYSER,						// 間欠泉
		OBJECTTYPE_SCAFFOLD,					// 足場
		OBJECTTYPE_SCAFFOLD_HIT,				// 2Dでも当たる足場
		OBJECTTYPE_SCAFFOLD_MOVE,				// 動く足場
		OBJECTTYPE_WALL,						// 壁
		OBJECTTYPE_GROUND_HALF,					// 地面 (ハーフ
		OBJECTTYPE_GROUND_QUARTER,				// 地面 (4/1
		OBJECTTYPE_SIGNBOARD_FALL,				// 看板 (落ちる
		OBJECTTYPE_SIGNBOARD_JUMP,				// 看板 (ジャンプ
		OBJECTTYPE_SIGNBOARD_GAYSER,			// 看板 (間欠泉
		OBJECTTYPE_SIGNBOARD_CHANGE,			// 看板 (カメラ切替え
		OBJECTTYPE_SIGNBOARD_ALL_RIDE,			// 看板 (2Dでも乗れる
		OBJECTTYPE_SIGNBOARD_3D_RIDE,			// 看板 (3Dでしか乗れない
		OBJECTTYPE_MAX,
	};

	CObjectModel();								// コンストラクタ
	virtual ~CObjectModel();					// デストラクタ
	
	/* メンバ関数 */
	void				Init();					// 初期化
	void				Uninit();				// 終了
	void				Update();				// 更新
	void				Draw();					// 描画

	/* 静的メンバ関数 */
	static	CObjectModel	*Create(D3DXVECTOR3 pos, OBJECTTYPE type);		// オブジェクトモデルの生成	
	static	HRESULT			Load();				// ロード
	static	void			Unload();			// アンロード

	/* メンバ関数 */
	bool					CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pSize, CObjectModel **ppObjectRet);	// オブジェクトの当たり判定
	OBJECTTYPE				GetObjectType()		{ return m_ObjectType; };	// オブジェクトの種類の取得
	void					SetObjectType(OBJECTTYPE type);					// オブジェクトの種類の設定

private:
	/* 静的メンバ変数 */
	static	LPDIRECT3DTEXTURE9	m_apTexture[OBJECTTYPE::OBJECTTYPE_MAX];	// 共有テクスチャのポインタ
	static MODEL_DRAWINFO		m_ModelDrawInfo[OBJECTTYPE_MAX];			// モデルの描画情報

	/* メンバ変数 */
	D3DXVECTOR3					m_posOld;		// 過去の位置
	D3DXVECTOR3					m_move;			// 移動
	D3DXVECTOR3					m_VtxMin;		// 最小頂点
	D3DXVECTOR3					m_VtxMax;		// 最大頂点
	OBJECTTYPE					m_ObjectType;	// オブジェクトの種類
};
#endif
