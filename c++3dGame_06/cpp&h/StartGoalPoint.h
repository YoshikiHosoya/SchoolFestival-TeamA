// ----------------------------------------
//
// スタートゴール処理の説明[startgoal.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _STARTGOALPOINT_H_
#define _STARTGOALPOINT_H_	 // ファイル名を基準を決める

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


// ----------------------------------------
//
// 前方宣言
//
// ----------------------------------------

// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class CStartGoal : public CScene
{
public:
	/* 列挙型 */
	typedef enum
	{
		TYPE_START = 0,	// スタート
		TYPE_GOAL,			// ゴール
		TYPE_MAX
	} TYPE;

	/* 関数 */
	CStartGoal();
	~CStartGoal();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CStartGoal * Create(D3DXVECTOR3 pos , TYPE type);
protected:

private:
	/* 関数 */
	/* 変数 */
	D3DXVECTOR3					m_pos;			// 位置
	TYPE						m_type;			// 種類
};

#endif