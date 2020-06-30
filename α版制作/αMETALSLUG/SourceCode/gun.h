// =====================================================================================================================================================================
//
// ガンの処理 [gun.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _GUN_H_
#define _GUN_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "model.h"

// =====================================================================================================================================================================
// ガンクラス
// =====================================================================================================================================================================
class CGun : public CModel
{
public:

	// 弾の種類
	enum BULLET_TYPE
	{
		TYPE_PLAYER = 0,
		TYPE_ENEMY,
		TYPE_MAX,
	};

	// 銃の種類
	enum GUN_TYPE
	{
		GUNTYPE_HANDGUN = 0,						// ハンドガン
		GUNTYPE_HEAVYMACHINEGUN,					// ヘビーマシンガン
		GUNTYPE_SHOTGUN,							// ショットガン
		GUNTYPE_LASERGUN,							// レーザーガン
		GUNTYPE_ROCKETLAUNCHER,						// ロケットランチャー
		GUNTYPE_FLAMESHOT,							// フレイムショット
		GUNTYPE_GRENADE,							// グレネード
		GUNTYPE_MAX									// 銃の種類の最大数
	};

	CGun(OBJ_TYPE type);							// コンストラクタ
	~CGun();										// デストラクタ

	/* メンバ関数 */
	virtual HRESULT			Init();					// 初期化
	virtual void			Uninit();				// 終了
	virtual void			Update();				// 更新
	virtual void			Draw();					// 描画
	virtual void			DebugInfo();			//デバッグ

	/* 静的メンバ関数 */
	static	CGun			*Create(D3DXMATRIX *mtx);		// 銃の生成

	/* メンバ関数 */
	GUN_TYPE				&GetGunType() { return m_GunType; };				// 銃の種類の取得
	void					SetGunType(GUN_TYPE type);							// 銃の種類の設定
	BULLET_TYPE				&GetBulletType() { return m_BulletType; };				// 弾の種類の取得
	void					SetBulletType(BULLET_TYPE type) { m_BulletType = type; };	// 弾の種類の設定

	void					Shot(D3DXVECTOR3 rot);								// 銃の発射

private:
	/* メンバ関数 */
	void					MultipleShot();			// 複数発撃つ処理
	/* メンバ変数 */
	GUN_TYPE				m_GunType;				// ガンの種類
	BULLET_TYPE				m_BulletType;			// 弾の種類
	int						m_nAmmo;				// 弾薬数
	int						m_nInterval;			// インターバル
	D3DXMATRIX				*m_mtx;					// マトリックス
	bool					m_bMultiple;			// 複数撃つフラグ
	D3DXVECTOR3				m_rot;					// 回転
	int						m_nCntFrame;			// フレームカウント
	int						m_nCntBullet;			// 弾のカウント
};
#endif
