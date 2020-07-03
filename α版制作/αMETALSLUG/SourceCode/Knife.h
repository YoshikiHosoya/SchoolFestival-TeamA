// =====================================================================================================================================================================
//
// ナイフの処理 [Knife.h]
// Author : Yoshiki Hosoya
//
// =====================================================================================================================================================================
#ifndef _KNIFE_H_
#define _KNIFE_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "model.h"

// =====================================================================================================================================================================
// ガンクラス
// =====================================================================================================================================================================
class COrbit;
class CCollision;

class CKnife : public CModel
{
public:
	CKnife(OBJ_TYPE type);									//コンストラクタ
	~CKnife();												//デストラクタ

	/* メンバ関数 */
	virtual HRESULT			Init();							//初期化
	virtual void			Uninit();						//終了
	virtual void			Update();						//更新
	virtual void			Draw();							//描画
	virtual void			DebugInfo();					//デバッグ

	/* 静的メンバ関数 */
	static	CKnife			*Create(D3DXMATRIX *mtx);		//生成
	void					StartMeleeAttack();				//近接攻撃開始
	void					EndMeleeAttack();				//近接攻撃終了

	D3DXMATRIX				*GetHandMtx() { return m_HandMatrix;};					//手のマトリックス取得

private:
	COrbit		*m_pOrbit;					//軌跡のポインタ
	CCollision	*m_pCollision;				//当たり判定のポインタ
	D3DXMATRIX	*m_HandMatrix;				//ナイフを持つ手のマトリックスのポインタ
	bool		m_bAttack;					//攻撃中かどうか

	D3DXVECTOR3 m_worldpos;					//ワールド座標　当たり判定用
	void		CollisionKnife();			//ナイフの当たり判定処理
};
#endif
