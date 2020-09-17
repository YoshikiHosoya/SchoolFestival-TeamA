// =====================================================================================================================================================================
//
// グレネード発射の処理 [grenadefire.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _GRENADEFIRE_H_
#define _GRENADEFIRE_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "scene.h"
#include "bullet.h"

// =====================================================================================================================================================================
// グレネード発射クラス
// =====================================================================================================================================================================
class CGrenadeFire : public CScene, public CGameObject
{
public:
	// グレネードの種類
	enum GRENADE_TYPE
	{
		HAND_GRENADE = 0,				// 手榴弾
		TANK_GRENADE,					// 戦車のグレネード
		DROP_BOMB,						// ドロップボム
		GRENADE_TYPE_MAX
	};

	CGrenadeFire(OBJ_TYPE type);							// コンストラクタ
	~CGrenadeFire();										// デストラクタ

	/* メンバ関数 */
	HRESULT						Init();						// 初期化
	void						Uninit();					// 終了
	void						Update();					// 更新
	void						Draw();						// 描画
	void						DebugInfo(void);			// デバッグ

	/* 静的メンバ関数 */
	static	CGrenadeFire		*Create(D3DXMATRIX *mtx, GRENADE_TYPE type);	// グレネード放つ位置の生成

	/* メンバ関数 */
	void						Fire(D3DXVECTOR3 rot);					// グレネードを放つ
	int							GetGrenadeAmmo() { return m_nAmmo; };	// グレネードの残弾数取得
	void						SetGrenadeAmmoDefault();				// グレネードの弾数初期化
	void						GrenadeAddAmmo();						// グレネードの弾数追加

private:
	/* メンバ関数 */
	void						MultipleFire();						// 複数発放つ処理
	void						ProcessReduceMultipleGrenade();		// 複数放ったグレネードを減らす処理

	/* メンバ変数 */
	int							m_nAmmo;					// 残弾数
	int							m_nInterval;				// インターバル
	D3DXMATRIX					*m_mtx;						// マトリックス
	GRENADE_TYPE				m_type;						// グレネードの種類
	bool						m_bMultiple;				// 複数放つフラグ
	int							m_nCntFrame;				// フレームカウント
	int							m_nCntGrenade;				// グレネードのカウント
	CBullet::BULLET_PARAM		*m_pBulletParam;			// 弾(グレネード)のパラメーター
	D3DXVECTOR3					m_rot;						// 回転
};
#endif