// =====================================================================================================================================================================
//
// モデルキャラクターの処理 [modelcharacter.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _MODELCHARACTER_H_
#define _MODELCHARACTER_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "scene.h"
#include "sceneX.h"

// =====================================================================================================================================================================
// 前方宣言
// =====================================================================================================================================================================
class CPartsModel;				// パーツモデルクラス

// =====================================================================================================================================================================
// モデルキャラクター
// =====================================================================================================================================================================
class CModelCharacter
{
public:
	// プレイヤーのモーションの種類
	enum PlayerMotionType
	{
		PlayerMotionType_NEUTRAL = 0,			// 待機
		PlayerMotionType_WALK,					// 歩き
		PlayerMotionType_JUMP,					// ジャンプ
		PlayerMotionType_LANDING,				// 着地
		PlayerMotionType_MAX,
	};

	CModelCharacter();							// コンストラクタ
	virtual ~CModelCharacter();					// デストラクタ
	
	/* メンバ関数 */
	void				Init();					// 初期化
	void				Uninit();				// 終了
	void				Update();				// 更新
	void				Draw();					// 描画

	/* 静的メンバ関数 */
	static	CModelCharacter		*Create();		// 3Dポリゴンの生成	

	/* メンバ関数 */
	void				SetMatrix(D3DXMATRIX *mtx);					// マトリックスの設定
	void				SetMotion(PlayerMotionType MotionType);		// モーションの設定

private:
	/* メンバ関数 */
	void				ModelLoad();			// モデルの読み込み
	void				MotionUpdate();			// モーションの更新

	/* メンバ変数 */
	D3DXVECTOR3							m_pos;						// 現在の位置
	D3DXVECTOR3							m_posOld;					// 前回の位置
	D3DXVECTOR3							m_posDif;					// 位置の差分
	D3DXVECTOR3							m_posDest;					// 目的の位置
	D3DXVECTOR3							m_posInit;					// 初期位置
	D3DXVECTOR3							m_rot;						// 向き(回転)
	D3DXVECTOR3							m_rotDiff;					// 向きの差分
	D3DXVECTOR3							m_rotDest;					// 目的向き
	D3DXVECTOR3							m_move;						// 移動
	D3DXMATRIX							m_mtxWorld;					// ワールドマトリックス
	LPDIRECT3DTEXTURE9					m_pTexture = {};			// テクスチャへのポインタ
	CPartsModel							*m_pModel[PLAYER_PARTS];	// モデルへのポインタ

	/* 静的メンバ変数 */
	static	LPD3DXMESH					m_pMesh;					// メッシュ情報へのポインタ
	static	LPD3DXBUFFER				m_pBuffMat;					// マテリアル情報へのポインタ
	static	DWORD						m_nNumMat;					// マテリアル情報の数
	static	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;					// 頂点バッファへのポインタ
	static	PlayerMotionType			m_PlayerMotionType;			// 現在プレイヤーのモーションの種類
	static	PlayerMotionType			m_PlayerMotionTypeOld;		// 前回のプレイヤーのモーションの種類
	static	int							m_nFrame;					// フレーム数
	static	int							m_nKeySet;					// 現在のキー

};
#endif
