//=============================================================================
// カメラ処理 [camera.cpp]
//=============================================================================
#include "camera.h"
#include "inputKeyboard.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "basemode.h"
#include "Player.h"
#include "Scene.h"
#include "mouse.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_LENGTH (-100) //カメラの距離
#define CAMERA_MOVE_SPEED (10.0f)
#define CAMERA_ROTATION_SPEED (0.05f)
#define CAMETA_POSR_OFFSET (D3DXVECTOR3(0.0f,200.0f,0.0f))

#define DEFAULT_DISTANCE (850.0f)
#define DEFAULT_CAMERA_ROTATION (D3DXVECTOR3(0.17f,0.0f,0.0f))

#define CAMERA_LENGTH_NEAR (10.0f)
#define CAMERA_LENGTH_FAR (3000.0f)
//=============================================================================
// カメラの初期化処理
//=============================================================================
void CCamera::InitCamera(void)
{
	// カメラをプレイや追従にする
	m_CameraFollowingType = CAMERA_FOLLOWING_TYPE_PLAYER;

	m_posCameraEndLine = ZeroVector3;
	m_fNear = CAMERA_LENGTH_NEAR;
	m_fFar = CAMERA_LENGTH_FAR;
	m_bStopMove = false;

	//カメラ初期化
	ResetCamera();
}
//=============================================================================
// カメラの終了処理
//=============================================================================
void CCamera::UninitCamera(void)
{
}
//=============================================================================
// カメラの更新処理
//=============================================================================
void CCamera::UpdateCamera(void)
{
#ifdef _DEBUG

	//カメラのデバッグコマンド
	DebugCommand();

#endif // _DEBUG

	// カメラの追従種類によってカメラの動かし方を変える
	switch (m_CameraFollowingType)
	{
	case CCamera::CAMERA_FOLLOWING_TYPE_PLAYER:
		// キャラクター追従カメラ
		CharacterFollowingMoveCamera();
		break;
	case CCamera::CAMERA_FOLLOWING_TYPE_MOUSE:
		// マウスによるカメラ操作
		MouseMoveCamera();
		break;
	}
}
//=============================================================================
// カメラの設定処理
//=============================================================================
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		m_fNear,
		m_fFar);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	// ビューマトリックスを作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecV);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}
//=============================================================================
//カメラの移動関数
//=============================================================================
void CCamera::SetMoveCamera(float Cm_rot)
{
	m_move.x += sinf(-D3DX_PI* Cm_rot + m_rot.y) * 5;
	m_move.z += cosf(-D3DX_PI* Cm_rot + m_rot.y) * 5;
}

//=============================================================================
//デバッグコマンド
//=============================================================================
void CCamera::DebugCommand()
{
	CKeyboard *key = CManager::GetInputKeyboard();

	//使い方説明
	CDebugProc::Print("---------Camera Debug Command----------\n");
	CDebugProc::Print("[Ctrl] + [1] : カメラ切替 : CameraMode >> [%d]\n", m_CameraFollowingType);
	CDebugProc::Print("[Ctrl] + [↑] or [Ctrl] + [↓] : カメラ距離調整 : Distance>>[%f]\n", m_fDistance);

	CDebugProc::Print("m_posV %.1f %.1f %.1f \n", m_posV.x, m_posV.y, m_posV.z);
	CDebugProc::Print("m_posR %.1f %.1f %.1f \n", m_posR.x, m_posR.y, m_posR.z);
	CDebugProc::Print("m_rot  %.1f %.1f %.1f \n", m_rot.x, m_rot.y, m_rot.z);
	CDebugProc::Print("bCameraStop >> %d",m_bStopMove);


	if (key->GetKeyboardPress(DIK_LCONTROL) || key->GetKeyboardPress(DIK_RCONTROL))
	{
		if (key->GetKeyboardTrigger(DIK_1))
		{
			//カメラ切り替え
			m_CameraFollowingType += 1;

			if (m_CameraFollowingType >= CAMERA_FOLLOWING_TYPE_MAX)
			{
				m_CameraFollowingType = CAMERA_FOLLOWING_TYPE_PLAYER;
			}
		}
		if (key->GetKeyboardPress(DIK_DOWN))
		{
			//カメラ距離++
			m_fDistance += 5.0f;
		}
		if (key->GetKeyboardPress(DIK_UP))
		{
			//カメラ--
			m_fDistance -= 5.0f;
		}
	}

}

//=============================================================================
//キャラクター追従カメラ
//=============================================================================
void CCamera::CharacterFollowingMoveCamera()
{
	//回転の数値指定
	CHossoLibrary::CalcRotation(m_rot.x);
	CHossoLibrary::CalcRotation(m_rot.y);

	//カメラの移動とめるかどうか
	if (!m_bStopMove)
	{
		//追従処理
		CBaseMode *pBaseMode = CManager::GetBaseMode();

		//nullcheck
		if (pBaseMode)
		{
			//プレイヤーのポインタ取得
			CPlayer *pPlayer = pBaseMode->GetPlayer();

			//nullcheck
			if (pPlayer)
			{
				//座標取得
				//カメラ最終目的地
				m_posRDest.x = pPlayer->GetPosition().x;
				m_posRDest.y = CAMETA_POSR_OFFSET.y;

				//カメラのエンドライン
				if (m_posCameraEndLine.x > pPlayer->GetPosition().x)
				{
					m_posRDest.x = m_posCameraEndLine.x;
				}
				else
				{
					//カメラのエンドライン設定
					m_posCameraEndLine.x = m_posRDest.x;
					//m_posCameraEndLine.y = m_posRDest.y;

				}
			}
		}
	}

	//カメラのxが0以下にならないようにする
	CHossoLibrary::RangeLimit_Equal(m_posRDest.x, 0.0f, 99999.0f);

	//視点の目的地の計算
	m_posVDest.x = m_posRDest.x - sinf(m_rot.y) * cosf(m_rot.x) * m_fDistance;
	m_posVDest.y = m_posRDest.y + sinf(m_rot.x)	* m_fDistance;
	m_posVDest.z = m_posRDest.z - cosf(m_rot.y) * cosf(m_rot.x) * m_fDistance;

	//視点の移動
	m_posV.x += (m_posVDest.x - m_posV.x) * 0.08f;
	m_posV.y += (m_posVDest.y - m_posV.y) * 0.08f;
	m_posV.z += (m_posVDest.z - m_posV.z) * 0.08f;

	//注視点の移動
	m_posR.x += (m_posRDest.x - m_posR.x) * 0.08f;
	m_posR.y += (m_posRDest.y - m_posR.y) * 0.08f;
	m_posR.z += (m_posRDest.z - m_posR.z) * 0.08f;

	//慣性抵抗
	m_move.x += (0 - m_move.x)*0.3f;
	m_move.y += (0 - m_move.y)*0.3f;
	m_move.z += (0 - m_move.z)*0.3f;
	m_posRDest += m_move;
}

//=============================================================================
//マウスによるカメラの操作
//=============================================================================
void CCamera::MouseMoveCamera()
{
	// キーボードの取得
	CKeyboard *pKeyboard = CManager::GetInputKeyboard();
	CMouse *pMouse = CManager::GetMouse();

	D3DXVECTOR2 NewRotation = ZeroVector2;

	static D3DXVECTOR2 MousePosCurrent = ZeroVector2;
	static D3DXVECTOR2 MousePosOld = ZeroVector2;
	static D3DXVECTOR2 MouseRot = ZeroVector2;

	// マウスの座標保持
	MousePosCurrent = pMouse->GetMousePos();

	//マウス入力されてない時
	if (pMouse->GetPress(1) == false)
	{
		// 前回の位置の設定
		MousePosOld = MousePosCurrent;
	}
	//マウス入力されているとき
	else
	{
		// 横回転
		NewRotation.y = (MousePosCurrent.x - MousePosOld.x) / (D3DX_PI*2.0f) *0.03f + MouseRot.y;
		m_rotDest.y = NewRotation.y;

		// 回転量を360度ないに直す
		CHossoLibrary::CalcRotation(m_rotDest.y);

		// ピッチロー回転
		NewRotation.x = (MousePosCurrent.y - MousePosOld.y) / (D3DX_PI*2.0f) *0.03f + MouseRot.x;

		// 回転を90度未満に抑える
		if (NewRotation.x >= D3DX_PI*0.49f)
		{
			NewRotation.x = D3DX_PI*0.49f;
			MousePosOld = MousePosCurrent;
			MouseRot.y = m_rotDest.y;
			MouseRot.x = m_rotDest.x;

		}
		else if (NewRotation.x <= -D3DX_PI*0.49f)
		{
			NewRotation.x = -D3DX_PI*0.49f;
			MousePosOld = MousePosCurrent;
			MouseRot.y = m_rotDest.y;
			MouseRot.x = m_rotDest.x;

		}
		m_rotDest.x = NewRotation.x;
	}

	if (pMouse->GetRelease(1))
	{
		MouseRot.y = m_rotDest.y;
		MouseRot.x = m_rotDest.x;
	}

	//注視点回転
	if (pKeyboard->GetKeyboardPress(DIK_2))
	{
		m_rotDest.z += 0.01f;
	}
	else if (pKeyboard->GetKeyboardPress(DIK_X))
	{
		m_rotDest.z -= 0.01f;
	}

	// カメラの回転を90度未満に抑える
	if (m_rotDest.x >= D3DX_PI*0.49f)
	{
		m_rotDest.x = D3DX_PI*0.49f;
	}
	else if (m_rotDest.x <= -D3DX_PI*0.49f)
	{
		m_rotDest.x = -D3DX_PI*0.49f;
	}
	// 回転量を360度ないに直す
	CHossoLibrary::CalcRotation(m_rotDest.y);

	//[W]キーを押した時
	if (pKeyboard->GetKeyboardPress(DIK_W))
	{
		//奥
		m_posRDest.x += sinf(D3DX_PI * 0.0f + m_rotDest.y) * CAMERA_MOVE_SPEED;
		m_posRDest.z += cosf(D3DX_PI * 0.0f + m_rotDest.y) * CAMERA_MOVE_SPEED;
	}
	//[S]キーを押した時
	if (pKeyboard->GetKeyboardPress(DIK_S))
	{
		//前
		m_posRDest.x += sinf(D3DX_PI * 1.0f + m_rotDest.y) * CAMERA_MOVE_SPEED;
		m_posRDest.z += cosf(D3DX_PI * 1.0f + m_rotDest.y) * CAMERA_MOVE_SPEED;
	}
	//[A]キーを押した時
	if (pKeyboard->GetKeyboardPress(DIK_A))
	{
		//左
		m_posRDest.x += sinf(-D3DX_PI * 0.5f + m_rotDest.y) * CAMERA_MOVE_SPEED;
		m_posRDest.z += cosf(-D3DX_PI * 0.5f + m_rotDest.y) * CAMERA_MOVE_SPEED;
	}
	//[D]キーを押した時
	if (pKeyboard->GetKeyboardPress(DIK_D))
	{
		//右
		m_posRDest.x += sinf(D3DX_PI * 0.5f + m_rotDest.y) * CAMERA_MOVE_SPEED;
		m_posRDest.z += cosf(D3DX_PI * 0.5f + m_rotDest.y) * CAMERA_MOVE_SPEED;
	}

	//[1]キーを押した時
	else if (pKeyboard->GetKeyboardPress(DIK_1))
	{
		//上に移動
		m_posRDest.x += sinf(D3DX_PI * 0.0f) * CAMERA_MOVE_SPEED;
		m_posRDest.y += cosf(D3DX_PI * 0.0f) * CAMERA_MOVE_SPEED;
	}
	//[3]キーを押した時
	else if (pKeyboard->GetKeyboardPress(DIK_3))
	{
		//下に移動
		m_posRDest.x += sinf(D3DX_PI * 1.0f) * CAMERA_MOVE_SPEED;
		m_posRDest.y += cosf(D3DX_PI * 1.0f) * CAMERA_MOVE_SPEED;
	}

	//回転先
	m_rot = m_rotDest;

	// 視点の行く先の更新
	m_posVDest.x = m_posR.x - cosf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
	m_posVDest.y = m_posR.y + sinf(m_rot.x) * m_fDistance;
	m_posVDest.z = m_posR.z - cosf(m_rot.x) * cosf(m_rot.y) * m_fDistance;

	// 視点の更新
	m_posV += (m_posVDest - m_posV) * 0.2f;

	// 注視点の更新
	m_posR += (m_posRDest - m_posR) * 0.2f;
}

//-----------------------------------------------------------------------------
//注視点を設定
//-----------------------------------------------------------------------------
void CCamera::SetPosR(D3DXVECTOR3 posR)
{
	m_posCameraEndLine = m_posR = m_posRDest = posR;

	m_posV.x = m_posVDest.x = m_posRDest.x - sinf(m_rot.y) * cosf(m_rot.x) * m_fDistance;
	m_posV.y = m_posVDest.y = m_posRDest.y + sinf(m_rot.x)	* m_fDistance;
	m_posV.z = m_posVDest.z = m_posRDest.z - cosf(m_rot.y) * cosf(m_rot.x) * m_fDistance;
}

//-----------------------------------------------------------------------------
//カメラを初期座標に設定
//-----------------------------------------------------------------------------
void CCamera::ResetCamera()
{
	//初期座標へ
	m_rotDest = m_rot = DEFAULT_CAMERA_ROTATION;
	m_fDistance = DEFAULT_DISTANCE;
	m_posCameraEndLine = m_posR = m_posRDest = ZeroVector3;

	m_posV.x = m_posVDest.x = m_posRDest.x - sinf(m_rot.y) * cosf(m_rot.x) * m_fDistance;
	m_posV.y = m_posVDest.y = m_posRDest.y + sinf(m_rot.x)	* m_fDistance;
	m_posV.z = m_posVDest.z = m_posRDest.z - cosf(m_rot.y) * cosf(m_rot.x) * m_fDistance;

	m_vecV = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// カメラをプレイや追従にする
	m_CameraFollowingType = CAMERA_FOLLOWING_TYPE_PLAYER;
	m_bStopMove = false;
}
//-----------------------------------------------------------------------------
//カメラ座標設定 角度と距離を基に算出
//-----------------------------------------------------------------------------
void CCamera::SetCameraPosfromDistance(D3DXVECTOR3 posR, D3DXVECTOR3 rot, float fDistance)
{
	//初期座標へ
	m_rotDest = m_rot = rot;
	m_fDistance = fDistance;
	m_posCameraEndLine = m_posR = m_posRDest = posR;

	m_posV.x = m_posVDest.x = m_posRDest.x - sinf(m_rot.y) * cosf(m_rot.x) * m_fDistance;
	m_posV.y = m_posVDest.y = m_posRDest.y + sinf(m_rot.x)	* m_fDistance;
	m_posV.z = m_posVDest.z = m_posRDest.z - cosf(m_rot.y) * cosf(m_rot.x) * m_fDistance;

	m_vecV = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// カメラをプレイや追従にする
	m_CameraFollowingType = CAMERA_FOLLOWING_TYPE_PLAYER;
}

//-----------------------------------------------------------------------------
//カメラ座標設定
//-----------------------------------------------------------------------------
void CCamera::SetCameraPos(D3DXVECTOR3 posR, D3DXVECTOR3 posV)
{
	//情報格納
	m_posCameraEndLine = m_posR = m_posRDest = posR;
	m_posV = m_posVDest = posV;

	//カメラの視点と注視点から角度と距離を求める
	D3DXVECTOR3	Length = m_posV - m_posR;																						//PosRとPosVの座標の差
	m_rot = m_rotDest = D3DXVECTOR3(atan2f(Length.y, Length.z), atan2f(-Length.x, -Length.z), atan2f(Length.x, Length.z));		//初期角度を求める
	m_fDistance = (float)sqrt((Length.y * Length.y + Length.z * Length.z) + Length.x * Length.x);								//視点と注視点の距離
}