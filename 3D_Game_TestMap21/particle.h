// =====================================================================================================================================================================
//
// パーティクルの処理 [particle.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "scene3D.h"

// =====================================================================================================================================================================
// パーティクルクラス
// =====================================================================================================================================================================
class CParticle : public CScene3D
{
public:

	// パーティクルの種類
	enum PARTICLETYPE
	{
		PARTICLE_NONE = -1,
		PARTICLE_RED,							// 赤
		PARTICLE_BLUE,							// 青
		PARTICLE_MAX,
	};

	CParticle();								// コンストラクタ
	~CParticle();								// デストラクタ

	/* メンバ関数 */
	void				Init();					// 初期化
	void				Uninit();				// 終了
	void				Update();				// 更新
	void				Draw();					// 描画

	/* 静的メンバ関数 */
	static	CParticle	*Create(D3DXVECTOR3 pos, PARTICLETYPE type);		// パーティクルの生成
	static	HRESULT		Load();												// ロード
	static	void		Unload();											// アンロード

private:
	/* メンバ変数 */
	bool						CollisionPlayer();							// プレイヤーとの当たり判定
	void						ParticleCircle();							// 円のパーティクル
	void						ParticleCircleShort();						// 小さい円のパーティクル
	/* 静的メンバ変数 */
	static	LPDIRECT3DTEXTURE9	m_apTexture[PARTICLETYPE::PARTICLE_MAX];	// 共有テクスチャのポインタ
	static	D3DXVECTOR2			m_UVsize;									// UVサイズ
	static	INTEGER2			m_UVcut;									// 分割数
	/* メンバ変数 */
	D3DXVECTOR3					m_move;										// 移動
	D3DXVECTOR3					m_size;										// サイズ
	D3DXCOLOR					m_col;										// 色
	PARTICLETYPE				m_type;										// 種類
	int							m_nCntAnim;									// カウンターアニメーション
	int							m_nPatternAnim;								// パターンアニメーション
	int							m_nSpeed;									// 速さ
	float						m_fRot;										// 回転
	float						m_fAngle;									// 角度
	float						m_fLength;									// 長さ
	float						m_fRadius;									// 半径

};
#endif
