// =====================================================================================================================================================================
//
// カメラ処理 [camera.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "camera.h"				// インクルードファイル
#include "keyboard.h"
#include "manager.h"
#include "renderer.h"
#include "scene3D.h"
#include "sceneX.h"
#include "debugproc.h"
#include "game.h"
#include "player.h"
#include "sound.h"
#include "xinputGpad.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
CCamera::CAMERA_MODE CCamera::m_CameraMode = CAMERA_MODE::CAMERA_MODE_3D;

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define CAMERA_SPEED			(1.5f)							// カメラのスピード

#define DISTANCE_V				(250.0f)						// 視点の距離
#define DISTANCE_R				(0.0f)							// 注視点の距離

#define NEAR_VALUE				(10.0f)							// ビューボリュームの近平面までの距離 NearZ値
#define FAR_VALUE				(2000.0f)						// ビューボリュームの遠平面までの距離 FarZ値
#define VIEWING_ANGLE			(45.0f)							// 視野角

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CCamera::CCamera()
{
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CCamera::~CCamera()
{
}
// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
void CCamera::Init(void)
{
	m_posV					= D3DXVECTOR3(0.0f, 80.0f, -150.0f);					// 視点
	m_posR					= D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 注視点( 参照点 )
	m_posVDest				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 目的の視点
	m_posRDest				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 目的の注視点( 参照点 )
	m_vecU					= D3DXVECTOR3(0.0f, 1.0f, 0.0f);						// 上方向ベクトル
	m_rot					= D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 回転
	m_rotDest				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 目的の回転
	m_fDistance				= 0;													// 距離
	m_RightStick_X			= 0;													// 右スティックのXの値
	m_RightStick_Y			= 0;													// 右スティックのYの値
	m_posVOld				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 過去の視点
	m_bSwitchingCameraMode	= false;												// カメラモードの切り替えフラグ
}

// =====================================================================================================================================================================
//
// カメラの終了処理
//
// =====================================================================================================================================================================
void CCamera::Uninit(void)
{
}

// =====================================================================================================================================================================
//
// カメラの更新処理
//
// =====================================================================================================================================================================
void CCamera::Update(void)
{
	// 変数
	CKeyboard	*pKeyboard		= CManager::GetKeyboard();
	CPlayer		*pPlayer		= CManager::GetGame()->GetPlayer();
	CXinputGpad *pXinputGpad	= CManager::GetXinputGpad();

	// 距離
	D3DXVECTOR3	fLength = m_posR - m_posV;
	m_fDistance = sqrtf(fLength.x * fLength.x + fLength.z * fLength.z);

	// 左スティックの値の取得
	pXinputGpad->GetRightStickValue(m_RightStick_X, m_RightStick_Y);
	// 左スティックを倒したときの角度
	float fLeftStickAngle = atan2f(m_RightStick_X, m_RightStick_Y);
	// 左スティックを倒したときの向き
	D3DXVECTOR2 LeftStickVec = D3DXVECTOR2((float)sin(fLeftStickAngle), (float)cos(fLeftStickAngle));

	// ゲームモードのとき
	if (CManager::GetMode() == CManager::GAME)
	{
		// === カメラのモードが3Dのとき ===
		if (m_CameraMode == CAMERA_MODE_3D)
		{
			// ----- [ 右スティック移動 ] -----
			// [ 左回転 ( 注視点 ) ]
			if (m_RightStick_X > 0)
			{
				m_rot.y -= 0.03f;
			}
			// [ 右回転 ( 注視点 ) ]
			else if (m_RightStick_X < -0)												// 初期値で少しカメラが傾く
			{
				m_rot.y += 0.03f;
			}

			// ----- [ 視点回転 ] -----
			// [ 左回転 ( 注視点 ) ]
			if (pKeyboard->GetKeyboardPress(DIK_LEFT))
			{
				m_rot.y += 0.03f;
			}
			// [ 右回転 ( 注視点 ) ]
			else if (pKeyboard->GetKeyboardPress(DIK_RIGHT))
			{
				m_rot.y -= 0.03f;
			}
		}
		// === カメラのモードが2Dのとき ===
		else if (m_CameraMode == CAMERA_MODE_2D)
		{
			if (pPlayer != NULL)
			{
				// 視点を2D視点に
				m_posV = pPlayer->GetPos() + D3DXVECTOR3(900.0f, 50.0f, 0.0f);
				m_rot.y = D3DX_PI / 2;
			}
		}

		// カメラのモード切替(2D, 3D)
		if (pKeyboard->GetKeyboardTrigger(DIK_C) || pXinputGpad->GetTriggerXinputGpad(CXinputGpad::XINPUT_RIGHT_SHOULDER))
		{
			//	カメラ切替え音
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_CHANGE);

			// 一回だけ通す
			if (m_bSwitchingCameraMode)
			{
				m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// カメラの回転初期化

				if (pPlayer != NULL)
				{
					// 視点を3D視点に
					m_posV = pPlayer->GetPos() + D3DXVECTOR3(0.0f, 120.0f, -200.0f);
				}

				m_bSwitchingCameraMode = false;		// カメラモードを3Dに
			}
			else
			{
				m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// カメラの回転初期化
				m_bSwitchingCameraMode = true;		// カメラモードを2Dに
			}
		}

	}
	// カメラのモード切替(常時)
	SwitchingCameraMode();

	// モードがゲームのとき
	if (CManager::GetMode() == CManager::MODE::GAME)
	{
		// 視点と注視点の設定
		if (pPlayer != NULL)
		{
			// 目的の注視点設定
			m_posRDest.x = pPlayer->GetPos().x + sinf(pPlayer->GetRot().y) * DISTANCE_R;
			m_posRDest.y = pPlayer->GetPos().y + 50;
			m_posRDest.z = pPlayer->GetPos().z - cosf(pPlayer->GetRot().y) * DISTANCE_R;

			// 目的の視点設定
			m_posVDest.x = pPlayer->GetPos().x + sinf(m_rot.y) * DISTANCE_V;
			m_posVDest.y = pPlayer->GetPos().y + 120;
			m_posVDest.z = pPlayer->GetPos().z - cosf(m_rot.y) * DISTANCE_V;

			// 注視点の追従設定
			m_posR.x += (m_posRDest.x - m_posR.x)* 0.08f;
			m_posR.y += (m_posRDest.y - m_posR.y)* 0.08f;
			m_posR.z += (m_posRDest.z - m_posR.z)* 0.08f;

			if (m_CameraMode == CAMERA_MODE_2D)
			{
				// 視点の追従設定
				m_posV.x += (m_posVDest.x - m_posV.x) * 0.03f;
				m_posV.y += (m_posVDest.y - m_posV.y) * 0.03f;
				m_posV.z += (m_posVDest.z - m_posV.z) * 0.03f;
			}
			else if (m_CameraMode == CAMERA_MODE_3D)
			{
				// 視点の追従設定
				m_posV.x += (m_posVDest.x - m_posV.x) * 0.03f;
				m_posV.y += (m_posVDest.y - m_posV.y) * 0.03f;
				m_posV.z += (m_posVDest.z - m_posV.z) * 0.03f;
			}
		}
	}
	// 回転情報をただす
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}

	CDebugProc::Print("\nCameraRot %f\n", m_rot.y);
}

// =====================================================================================================================================================================
//
// カメラの設定処理
//
// =====================================================================================================================================================================
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	// 近平面の縦幅 = zn * tan(Y方向の視野角/2) * 2
	float nearH = NEAR_VALUE * (float)tan(D3DXToRadian(90) / 2.0f) * 70.0f;
	// 近平面の横幅 = 近平面の縦幅 * アスペクト比
	float nearW = nearH * SCREEN_WIDTH / SCREEN_HEIGHT;

	// カメラモードで投影方法切替え
	switch (m_CameraMode)
	{
	case CCamera::CAMERA_MODE_3D:
		// プロジェクションマトリックスを作成
		D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
									D3DXToRadian(VIEWING_ANGLE),							// 視野角
									(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,				// アスペクト比
									NEAR_VALUE,												// Near Z値
									FAR_VALUE);												// Far Z値
		break;

	case CCamera::CAMERA_MODE_2D:
		// プロジェクションマトリックスを作成 ( 平行投影 )
		D3DXMatrixOrthoLH(&m_mtxProjection,
							nearW,				// ビューボリュームの横幅
							nearH,				// ビューボリュームの縦幅
							NEAR_VALUE,			// ビューボリュームの近平面までの距離
							FAR_VALUE);			// ビューボリュームの遠平面までの距離
		break;
	}

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);
	
	// ビューマトリックスを作成
	D3DXMatrixLookAtLH(&m_mtxView,
						&m_posV,													// カメラの視点
						&m_posR,													// カメラの注視点
						&m_vecU);													// カメラの上方向ベクトル

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

// =====================================================================================================================================================================
//
// カメラの初期座標設定
//
// =====================================================================================================================================================================
void CCamera::SetCameraPosInit(void)
{
	m_CameraMode = CAMERA_MODE::CAMERA_MODE_3D;							// カメラのモードを3Dに
	m_posV = D3DXVECTOR3(0.0f, 80.0f, -150.0f);							// 視点
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// 回転
	m_bSwitchingCameraMode = false;										// カメラモードの切り替え
}

// =====================================================================================================================================================================
//
// プレイヤーが死んだときのカメラの位置
//
// =====================================================================================================================================================================
void CCamera::SetDeadPlayerCameraPos(D3DXVECTOR3 pos)
{
	// 視点を3D視点に
	m_posV = pos + D3DXVECTOR3(0.0f, 120.0f, -200.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// 回転
}

// =====================================================================================================================================================================
//
// カメラモードの切り替え
//
// =====================================================================================================================================================================
void CCamera::SwitchingCameraMode(void)
{
	if (m_bSwitchingCameraMode)
	{
		// カメラのモードを2Dに
		m_CameraMode = CAMERA_MODE_2D;
	}
	else
	{
		// カメラのモードを3Dに
		m_CameraMode = CAMERA_MODE_3D;
	}
}