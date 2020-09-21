// =====================================================================================================================================================================
//
// バレットの処理 [bullet.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "model.h"
#include "gun.h"

// =====================================================================================================================================================================
// 前方宣言
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// バレットクラス
// =====================================================================================================================================================================
class CBullet : public CModel, public CGameObject
{
public:
	// ----- 弾のパラメーター -----
	typedef struct
	{
		float				fBulletSpeed;	// 弾速
		int					nLife;			// 体力
		int					nPower;			// 威力
		int					nAmmo;			// 弾薬数
		int					nTrigger;		// 1トリガーで発射される弾数
		int					nInterval;		// インターバル
		D3DXVECTOR3			CollisionSize;	// 当たり判定のサイズ
	}BULLET_PARAM;

	CBullet(OBJ_TYPE type);			// コンストラクタ
	~CBullet();						// デストラクタ

	/* メンバ関数 */
	virtual HRESULT				Init();													// 初期化
	virtual void				Uninit();												// 終了
	virtual void				Update();												// 更新
	virtual void				Draw();													// 描画
	virtual void				DeleteBullet();											// 弾消去
	virtual void				BulletReaction(D3DXVECTOR3 rot);						// 弾の反応

	/* 静的メンバ関数 */
	static	void				BulletLoad();											// 弾のロード
	void						CalcBulletMove(D3DXVECTOR3 ShotRot,int Guntype);		// 弾の発射方向計算
	void						CalcIncendiaryMove(D3DXVECTOR3 ShotRot, float move_x, float move_y);// 弾の発射方向計算

	/* メンバ関数 */
	D3DXVECTOR3					&GetMove()						{ return m_move; };					// 移動値の取得
	void						SetMove(D3DXVECTOR3 move)		{ m_move = move; };					// 移動値の設定
	static	BULLET_PARAM		*GetBulletParam(int nCnt)		{ return &m_BulletParam[nCnt]; };	// 弾のパラメーターの構造体の取得
	void						SetBulletParam(CGun::GUN_TYPE type);								// 弾のパラメーター設定

	int							GetLife()						{ return m_nLife; };
	void						SetBulletPoint(CBullet *pBullet) { m_pBullet = pBullet; };
	CBullet						*GetBullePoint()				{ return m_pBullet; };

private:
	/* メンバ変数 */
	D3DXVECTOR3					m_move;					// 移動値
	CGun::GUN_TYPE				m_GunType;				// ガンのタイプ
	int							m_nLife;				// 体力
	CBullet						*m_pBullet;				// 弾の種類
	/* 静的メンバ変数 */
	static char					*m_BulletFileName[CGun::GUNTYPE_MAX];	// 弾のファイル名
	static	BULLET_PARAM		m_BulletParam[CGun::GUNTYPE_MAX];		// 弾のパラメーター

	void			BulletHitSound();		// 弾が当たった時のサウンド再生

};
#endif
