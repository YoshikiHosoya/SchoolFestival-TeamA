#pragma once
//=============================================================================
// カメラ処理 [camera.h]
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
class CCamera
{
public:

	// カメラの追従種類
	enum CAMERA_FOLLOWING_TYPE
	{
		CAMERA_FOLLOWING_TYPE_PLAYER,			// プレイヤー
		CAMERA_FOLLOWING_TYPE_MAPEDITOR,		// マップエディター
		CAMERA_FOLLOWING_TYPE_MOUSE,			// マウス
		CAMERA_FOLLOWING_TYPE_MAX
	};

	void InitCamera(void);
	void UninitCamera(void);
	void UpdateCamera(void);
	void SetCamera(void);
	void SetMoveCamera(float rot);

	void DebugCommand();						//デバッグ用のコマンド
	void CharacterFollowingMoveCamera();		//キャラクター追従カメラ
	void MouseMoveCamera();						//マウス操作カメラ

	void ResetCamera();
	void SetCameraPosfromDistance(D3DXVECTOR3 posR,D3DXVECTOR3 rot,float fDistance);
	void SetCameraPos(D3DXVECTOR3 posR, D3DXVECTOR3 posV);
	void SetCameraPosRDest(D3DXVECTOR3 posR) { m_posRDest = posR; };	// 注視点の目的地の設定
	void SetCameraStopMove(bool bStop) { m_bStopMove = bStop; };

	D3DXVECTOR3 GetPosV()			{ return m_posV; };				//視点
	D3DXVECTOR3 GetPosR()			{ return m_posR; };				//注視点
	D3DXVECTOR3 GetRot()			{ return m_rot; };				//向き
	D3DXMATRIX *GetProjMtxPtr()		{ return &m_mtxProjection; };	//プロジェクションマトリックス
	D3DXMATRIX *GetViewMtxPtr()		{ return &m_mtxView; };			//ビューマトリックス
	float GetDistance()				{ return m_fDistance; };		//視点と注視点の距離
	float GetNear()					{ return m_fNear; };			//Near値
	float GetFar()					{ return m_fFar; };				//Far値
	bool GetStop()					{ return m_bStopMove; };		//カメラの移動ストップ

private:
	D3DXVECTOR3 m_posV;							//視点
	D3DXVECTOR3 m_posVDest;						//視点の目的地
	D3DXVECTOR3 m_posR;							//注視点
	D3DXVECTOR3 m_posRDest;						//注視点の目的地
	D3DXVECTOR3 m_rot;							//向き
	D3DXVECTOR3 m_rotDest;						//向きたい方向
	D3DXVECTOR3 m_move;							//移動視点
	D3DXVECTOR3 m_vecV;							//上方向ベクトル
	D3DXMATRIX m_mtxProjection;					//プロジェクションマトリックス
	D3DXMATRIX m_mtxView;						//ビューマトリックス
	float m_fDistance;							//距離
	float m_fNear;								//Near値
	float m_fFar;								//Far値

	D3DXVECTOR3 m_posCameraEndLine;				//カメラのライン

	int m_nCountTimer;							//追従のタイマー
	int m_nCnt;
	int m_CameraFollowingType;					// カメラの追従種類

	bool m_bStopMove;							// カメラ移動しない
};
#endif
