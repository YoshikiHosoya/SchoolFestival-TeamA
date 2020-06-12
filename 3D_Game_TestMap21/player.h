// =====================================================================================================================================================================
//
// プレイヤーの処理 [player.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "scene.h"

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define PLAYER_MOTION				(4)					// プレイヤーのモーション数

// =====================================================================================================================================================================
// 前方宣言
// =====================================================================================================================================================================
class CModelCharacter;			// モデルキャラクタークラス

// =====================================================================================================================================================================
// プレイヤークラス
// =====================================================================================================================================================================
class CPlayer : public CScene
{
public:
	// プレイヤーの状態
	enum PLAYERSTATE
	{
		PLAYERSTATE_NONE = -1,
		PLAYERSTATE_APPEAR,						// 出現時
		PLAYERSTATE_NORMAL,						// 通常時
		PLAYERSTATE_SPEED,						// スピードアップ時
		PLAYERSTATE_FALL,						// 落下時
		PLAYERSTATE_DEATH,						// 死亡時
		PLAYERSTATE_MAX,						// 最大数
	};

	CPlayer();									// コンストラクタ
	CPlayer(PRIORITY Priority);					// コンストラクタ
	~CPlayer();									// デストラクタ

	/* メンバ関数 */
	void				Init();					// 初期化
	void				Uninit();				// 終了
	void				Update();				// 更新
	void				Draw();					// 描画

	/* メンバ関数 */
	void				SetPos(D3DXVECTOR3 pos)			{ m_pos = pos; };						// 位置の設定
	void				SetRestartPos(D3DXVECTOR3 pos)	{ m_posRestart = pos; };				// 再開地点の設定
	D3DXVECTOR3			GetPos()						{ return m_pos; };						// 位置の取得
	D3DXVECTOR3			GetOldPos()						{ return m_posOld; };					// 過去の位置の取得
	float				GetLandingPos()					{ return m_fLandingPos; };				// 着地した時の位置の取得
	float				GetJumpingPos()					{ return m_fJumpingPos; };				// 地面から離れた瞬間の位置の取得
	bool				GetLandFlag()					{ return m_bLand; };					// 着地フラグの取得
	D3DXVECTOR3			GetSize()						{ return m_size; };						// サイズの取得
	D3DXVECTOR3			GetRot()						{ return m_rot; };						// 回転の取得
	CModelCharacter		*GetModelCharacter()			{ return m_pModelCharacter; };			// モデルキャラクターの取得
	PLAYERSTATE			GetPlayerState()				{ return m_state; };					// プレイヤーの状態の取得
	void				PlayerDamage(int nLife);	// ダメージ
	void				PlayerRecovery(int nLife);	// 回復

	/* 静的メンバ関数 */
	static  CPlayer		*Create();					// プレイヤーの生成
	static	HRESULT		Load();						// ロード
	static	void		Unload();					// アンロード
	static	void		SetPlayerState(PLAYERSTATE state) { m_state = state; };	// プレイヤーの状態の設定

private:
	/* メンバ関数 */
	void				MovePlayer();						// プレイヤーの移動処理
	void				PlayerStateConfig();				// プレイヤーの状態の各設定
	void				PlayerFallDeath();					// プレイヤーの落下死
	/* メンバ変数 */
	D3DXVECTOR3							m_pos;				// 位置
	D3DXVECTOR3							m_posOld;			// 過去の位置
	D3DXVECTOR3							m_posRestart;		// 再開位置
	D3DXVECTOR3							m_size;				// サイズ
	D3DXVECTOR3							m_move;				// 移動
	D3DXVECTOR3							m_rot;				// 向き(回転)
	D3DXVECTOR3							m_rotDiff;			// 向きの差分
	D3DXVECTOR3							m_rotDest;			// 目的の向き
	float								m_fJumpingPos;		// 地面から離れた瞬間の位置
	float								m_fLandingPos;		// 着地した時の位置
	D3DXMATRIX							m_mtxWorld;			// ワールドマトリックス
	bool								m_bJump;			// ジャンプフラグ
	bool								m_bFlashing;		// 死んだときの点滅フラグ
	bool								m_bLand;			// 着地したときのフラグ
	int									m_nCntDeath;		// 死んだときのカウント
	int									m_nLife;			// 体力
	float								m_LeftStick_X;		// 左スティックのXの値
	float								m_LeftStick_Y;		// 左スティックのYの値
	float								m_RightStick_X;		// 右スティックのXの値
	float								m_RightStick_Y;		// 右スティックのYの値
	/* 静的メンバ変数 */
	static	LPD3DXMESH					m_pMesh;			// メッシュ情報へのポインタ
	static	LPD3DXBUFFER				m_pBuffMat;			// マテリアル情報へのポインタ
	static	DWORD						m_nNumMat;			// マテリアル情報の数
	static	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;			// 頂点バッファへのポインタ
	static	CModelCharacter				*m_pModelCharacter;	// モデルキャラクターのポインタ
	static	PLAYERSTATE					m_state;			// 状態
};
#endif
