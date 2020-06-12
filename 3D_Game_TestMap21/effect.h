// =====================================================================================================================================================================
//
// エフェクトの処理 [effect.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "scene3D.h"

// =====================================================================================================================================================================
// エフェクトクラス
// =====================================================================================================================================================================
class CEffect : public CScene3D
{
public:

	// エフェクトの種類
	enum EFFECTTYPE
	{
		EFFECTTYPE_NONE = -1,
		EFFECTTYPE_AURA,					// オーラ
		EFFECTTYPE_GAYSER,					// 間欠泉
		EFFECTTYPE_ITEM,					// アイテム
		EFFECTTYPE_MAX,
	};

	CEffect();									// コンストラクタ
	~CEffect();									// デストラクタ

	/* メンバ関数 */
	void				Init();					// 初期化
	void				Uninit();				// 終了
	void				Update();				// 更新
	void				Draw();					// 描画

	/* 静的メンバ関数 */
	static	CEffect		*Create(D3DXVECTOR3 pos, EFFECTTYPE type);			// エフェクトの生成
	static	HRESULT		Load();												// ロード
	static	void		Unload();											// アンロード

private:
	/* メンバ関数 */
	bool						CollisionEffect();							// エフェクトの当たり判定
	void						EffectConfig(EFFECTTYPE type);				// エフェクトの設定
	/* 静的メンバ変数 */
	static	LPDIRECT3DTEXTURE9	m_apTexture[EFFECTTYPE::EFFECTTYPE_MAX];	// 共有テクスチャのポインタ
	/* メンバ変数 */
	D3DXVECTOR3					m_size;										// サイズ
	D3DXVECTOR3					m_move;										// 移動
	D3DXCOLOR					m_col;										// 色
	EFFECTTYPE					m_type;										// 種類
	int							m_nCntAnim;									// カウンターアニメーション
	int							m_nPatternAnim;								// パターンアニメーション
	float						m_fRadius;									// 半径
	bool						m_bDamage;									// ダメージフラグ
	bool						m_bAction;									// アクションフラグ
	int							m_nCntFrame;								// フレームカウント
	bool						m_bAdditiveSynthesis;						// 加算合成をするフラグ
	D3DXVECTOR2					m_UVsize;									// UVサイズ
	INTEGER2					m_UVcut;									// 分割数
	int							m_nAnimSpeed;								// アニメーションのスピード

};
#endif
