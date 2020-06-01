// ----------------------------------------
//
// デバッグ用の当たり判定表示処理の説明[debugcollision.h]
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
#define MAX_DEBUGCOLLISION (10)

// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class CDebugcollision : public CScene
{
public:
	/* 列挙型 */
	typedef enum
	{
		COLLISIONTYPE_BOX = 0,	//箱型
		COLLISIONTYPE_CICLE,	//円
		COLLISIONTYPE_BOARD,//板
		COLLISIONTYPE_MAX
	} COLLISIONTYPE;

	/* 関数 */
	CDebugcollision();
	~CDebugcollision();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CDebugcollision * Create(
		D3DXVECTOR3 * pos,
		D3DXVECTOR3 * size,
		COLLISIONTYPE type
	);
protected:

private:
	void BoxCollision(void);//箱型
	void BoardCollision(void);//板型

	D3DXVECTOR3 * m_pos;
	D3DXVECTOR3 * m_size;
	COLLISIONTYPE m_type;
};

#endif