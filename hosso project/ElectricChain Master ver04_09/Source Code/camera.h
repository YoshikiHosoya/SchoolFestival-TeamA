//-----------------------------------------------------------------------------
//
// カメラ処理 [camera.h]
// Author : Yoshiki Hosoya
//
//-----------------------------------------------------------------------------
#ifndef _CAMERA_H_
#define _CAMERA_H_

#define _CRT_SECURE_NO_WARNINGS

//-----------------------------------------------------------------------------
// インクルードファイル
//-----------------------------------------------------------------------------
#include "main.h"

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CCollision;

class CCamera
{
public:
	typedef enum
	{
		CAMERA_TITLE = 0,
		CAMERA_GAME,
		CAMERA_CHAIN_EXPLOSION,
		CAMERA_RESULT,
		CAMERA_DEBUG
	} CAMERA_STATE;

	CCamera();
	~CCamera();
	void Init();															//初期化
	void Uninit();															//終了
	void Update();															//更新
	void SetCamera();														//カメラ設定

	void SetCameraPos(D3DXVECTOR3 const posR, D3DXVECTOR3 const posV);		//カメラの座標設定
	void SetCameraRot(D3DXVECTOR3 const rot);								//カメラの回転角度設定
	void SetDistance();
	void ShowCameraInfo();													//カメラ情報表示

	D3DXVECTOR3 GetCameraRot() { return m_rot; };						//回転情報取得
	D3DXVECTOR3 GetCameraPosV() { return m_posV; };						//視点取得
	D3DXVECTOR3 GetCameraPosR() { return m_posR; };						//注視点取得
	D3DXMATRIX GetMtxView() { return m_mtxView; };						//ビューマトリックス取得
	D3DXMATRIX GetMtxProjection() { return m_mtxProjection; };			//プロジェクションマトリック取得
	int GetCameraState() {return m_CameraState;};

	void SetState(int nState);						//カメラの状態切り替え
private:
	D3DXVECTOR3		m_posV;							//視点
	D3DXVECTOR3		m_posVDest;						//目的の視点
	D3DXVECTOR3		m_posVOld;						//1F前の座標
	D3DXVECTOR3		m_posR;							//注視点
	D3DXVECTOR3		m_posRDest;						//目的の注視点
	D3DXVECTOR3		m_move;							//移動量
	D3DXVECTOR3		m_rot;							//回転
	D3DXVECTOR3		m_rotDest;						//回転の決定地

	D3DXVECTOR3		m_vecU;							//ベクトル
	D3DXMATRIX		m_mtxProjection;				//マトリックスプロジェクション
	D3DXMATRIX		m_mtxView;						//マトリックスビュー
	D3DXMATRIX		m_mtxWorld;						//ワールドマトリックス
	float			m_fDistance;					//視点と注視点の距離
	float			m_fDefaultDistace;				//初期のカメラ距離

	D3DXVECTOR2		m_MousePosCurrent;				//現在のマウスの位置
	D3DXVECTOR2		m_MousePosOld;					//前回のマウスの位置
	D3DXVECTOR2		m_MouseRotSave;					//回転を保存
	D3DXVECTOR3		m_DirecVector;					//向いてるベクトル

	std::unique_ptr<CCollision> m_pCollision;		//判定

	static int	m_CameraState;						//カメラの状態

	void MoveCameraDebug();							//カメラ移動処理
	void RotCameraDebug();							//カメラ回転処理
	void MouseCameraOperation();					//マウスでカメラ操作

	void MoveCameraGame();							//カメラ移動処理
	void RotCameraGame();							//カメラ回転処理

	void MoveCameraChainExplosion();				//連鎖爆発中のカメラムーヴ

	void CollisionCamera();							//カメラの当たり判定

	//void ChainThunderCamera();
};

#endif