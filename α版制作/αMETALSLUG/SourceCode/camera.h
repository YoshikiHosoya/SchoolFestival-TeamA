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
	void InitCamera(void);
	void UninitCamera(void);
	void UpdateCamera(void);
	void SetCamera(void);
	void SetMoveCamera(float rot);

	void DebugCommand();						//デバッグ用のコマンド
	void CharacterFollowingMoveCamera();		//キャラクター追従カメラ
	void MouseMoveCamera();						//マウス操作カメラ
private:
	D3DXVECTOR3 posV;			//視点
	D3DXVECTOR3 posVDest;		//視点の目的地
	D3DXVECTOR3 posR;			//注視点
	D3DXVECTOR3 posRDest;		//注視点の目的地
	D3DXVECTOR3 rot;			//向き
	D3DXVECTOR3 rotDest;		//向きたい方向
	D3DXVECTOR3 move;			//移動視点
	D3DXVECTOR3 vecV;			//上方向ベクトル
	D3DXMATRIX mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX mtxView;			//ビューマトリックス
	float fDistance;			//距離
	int nCountTimer;			//追従のタイマー
	int nCnt;
	D3DXVECTOR3 pos;			//ポジション

	bool m_bCameraMode;		//デバッグカメラかどうか
};
#endif
