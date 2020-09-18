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
class CGun : public CModel, public CGameObject
{
public:

	// 銃の種類
	enum GUN_TYPE
	{
		GUNTYPE_HANDGUN = 0,						// ハンドガン
		GUNTYPE_HEAVYMACHINEGUN,					// ヘビーマシンガン
		GUNTYPE_SHOTGUN,							// ショットガン
		GUNTYPE_LASERGUN,							// レーザーガン
		GUNTYPE_ROCKETLAUNCHER,						// ロケットランチャー
		GUNTYPE_FLAMESHOT,							// フレイムショット
		GUNTYPE_TANKGUN,							// 戦車の銃
		GUNTYPE_PLANEGUN,							// 戦闘機の銃
		GUNTYPE_HELIGUN,							// ヘリの銃
		GUNTYPE_BALKAN,								// バルカン
		GUNTYPE_FLAMETHROWER,						// 火炎放射器
		GUNTYPE_INCENDIARY,							// 焼夷弾
		GUNTYPE_HANDGRENADE,						// 手投げグレネード
		GUNTYPE_TANKGRENADE,						// 戦車のグレネード

		GUNTYPE_TRACKINGGUN,						// 追従銃
		GUNTYPE_DIFFUSIONGUN,						// 拡散銃
		GUNTYPE_BOSSLASERGUN,						// ボス用のレーザーガン
		GUNTYPE_HANDGUN_ENEMY,						// 敵のハンドガン
		GUNTYPE_MISSILE,							// ミサイル
		GUNTYPE_FLAMEBULLET,						// フレイムバレット
		GUNTYPE_DROPBOMB,							// ドロップボム

		GUNTYPE_MAX									// 銃の種類の最大数
	};

	CGun();											// コンストラクタ
	~CGun();										// デストラクタ

	/* メンバ関数 */
	virtual HRESULT		Init();					// 初期化
	virtual void		Uninit();				// 終了
	virtual void		Update();				// 更新
	virtual void		Draw();					// 描画
	virtual void		DebugInfo();			//デバッグ

	/* 静的メンバ関数 */
	static	CGun		*Create();		// 銃の生成
	void				NoDrawCalcMatrixOnly();			// マトリックスの計算

	/* メンバ関数 */
	GUN_TYPE			&GetGunType()				{ return m_GunType; };				// 銃の種類の取得
	int					GetGunAmmo()				{ return m_nAmmo; };				// 銃の残弾数取得
	D3DXVECTOR3			GetShotOffsetPos()			{ return m_ShotOffsetPos; };		// 発射位置のオフセットの取得
	D3DXVECTOR3			GetShotRot()				{ return m_ShotRot; };				// 撃つときの回転の向きの取得
	D3DXVECTOR3			GetShotVec()				{ return m_Shotvector; };			// 撃つときの向きの取得
	D3DXVECTOR3			GetShotPos()				{ return m_ShotPos; };				// 撃つときの座標取得
	D3DXVECTOR3			*GetShotPosPtr()			{ return &m_ShotPos; };				// 撃つときの座標のポインタ取得

	void				SetGunType(GUN_TYPE type);															// 銃の種類の設定
	void				GunAddAmmo(GUN_TYPE type);															// 弾数の加算
	void				SetGunTypeOnly(GUN_TYPE type)				{ m_GunType = type; };					// 銃の種類だけ変更
	void				SetHandMtx(D3DXMATRIX *pMtx)				{ m_HasHandMtx = pMtx; };				// 手のマトリックス設定
	void				SetShotOffsetPos(D3DXVECTOR3 ShotOffsetPos)	{ m_ShotOffsetPos = ShotOffsetPos; };	// 発射位置のオフセットの設定
	void				SetShotRot(D3DXVECTOR3 ShotRot)				{ m_ShotRot = ShotRot; };				// 撃つときの回転の向きの設定
	void				SetShotVec(D3DXVECTOR3 ShotVec)				{ m_Shotvector = ShotVec; };			// 撃つときの向きの設定
	void				SetMtxWorld(D3DXMATRIX *mtx)				{ m_HasHandMtx = mtx; };				// マトリックスの設定
	void				SetMoveZero(bool bMoveZero)					{ m_bMoveZero = bMoveZero; };			// 移動を無効にするかの設定
	void				Shot();																				// 銃の発射

private:
	/* メンバ関数 */
	void				MultipleShot();						// 複数発撃つ処理
	void				ProcessReduceMultipleBullet();		// 複数撃った弾を減らす処理

	/* メンバ変数 */
	GUN_TYPE			m_GunType;				// ガンの種類
	GUN_TYPE			m_GunTypeOld;			// 前回のガンの種類
	int					m_nAmmo;				// 弾薬数
	int					m_nInterval;			// インターバル
	D3DXMATRIX			*m_HasHandMtx;			// 持ち手のマトリックス
	bool				m_bMultiple;			// 複数撃つフラグ
	D3DXVECTOR3			m_ShotPos;				// 発射位置
	D3DXVECTOR3			m_ShotOffsetPos;		// 発射位置のオフセット
	D3DXVECTOR3			m_ShotRot;				// 撃つときの回転の向き
	D3DXVECTOR3			m_Shotvector;			// 撃つときの速度
	int					m_nCntFrame;			// フレームカウント
	int					m_nCntBullet;			// 弾のカウント
	bool				m_bMoveZero;			// 移動を無効にするフラグ
};
#endif
