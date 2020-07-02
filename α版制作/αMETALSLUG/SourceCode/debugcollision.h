// ----------------------------------------
//
// デバッグ用当たり判定表示処理[debugcollision.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _DEBUGCOLLISION_H_
#define _DEBUGCOLLISION_H_	 // ファイル名を基準を決める

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
#include "scene.h"
// ----------------------------------------
//
// マクロ定義
//
// ----------------------------------------
#define MAX_VERTEX3D (12)
#define MAX_VERTEX2D (4)

// ------------------------------------------
//
// 前方宣言
//
// ------------------------------------------
class C3DLine;
// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class CDebugcollision : public CScene
{
public:
	/* 当たり判定の種類 */
	typedef enum
	{
		COLLISIONTYPE_BOX = 0,			//箱型
		COLLISIONTYPE_BOARD,			//板型
		COLLISIONTYPE_BOARDCHARA,		//キャラクター用板型
		COLLISIONTYPE_MAX
	} COLLISIONTYPE;

	CDebugcollision(OBJ_TYPE type);
	~CDebugcollision();

	/* メンバ関数 */
	virtual HRESULT Init(void);
	virtual	void Uninit(void);
	virtual	void Update(void);
	virtual	void Draw(void);
	virtual void DebugInfo(void);
	/* 静的メンバ関数 */
	static CDebugcollision * Create(
		D3DXVECTOR3 * pos,
		D3DXVECTOR3 * size,
		COLLISIONTYPE type
	);

	/* メンバ関数 */
	void SetPos(D3DXVECTOR3 *pos);
	void SetSize(D3DXVECTOR3 *size);
	void DeleteDeCollision();
protected:

private:
	/* メンバ関数 */
	void BoxCollision(void);				// 箱型の判定
	void BoardCollision(void);				// 板型の判定
	void BoardCharaCollision(void);			// キャラクター板型の判定

	/* メンバ変数 */
	D3DXVECTOR3 * m_pos;					// 座標
	D3DXVECTOR3 * m_size;					// サイズ
	COLLISIONTYPE m_type;					// タイプ
	C3DLine *m_p3DLine[MAX_VERTEX3D];		// ラインのポインタ
	C3DLine *m_p2DLine[MAX_VERTEX2D];		// ラインのポインタ
};

#endif