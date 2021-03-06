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
#define CAMETA_POSR_OFFSET (D3DXVECTOR3(0.0f,50.0f,0.0f))

#define DEFAULT_DISTANCE (1000.0f)
#define DEFAULT_CAMERA_ROTATION (D3DXVECTOR3(0.2f,0.0f,0.0f))
//=============================================================================
// カメラの初期化処理
//=============================================================================
void CCamera::InitCamera(void)
{
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

	//カメラの状態でカメラの動かし方を変える
	m_bCameraMode ?
		MouseMoveCamera() :
		CharacterFollowingMoveCamera();
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
		10.0f,
		10000.0f);

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
	CDebugProc::Print("[Ctrl] + [1] : カメラ切替 : CameraMode >> [%d]\n",m_bCameraMode);
	CDebugProc::Print("[Ctrl] + [↑] or [Ctrl] + [↓] : カメラ距離調整 : Distance>>[%f]\n", m_fDistance);

	CDebugProc::Print("m_posV %.1f %.1f %.1f \n", m_posV.x, m_posV.y, m_posV.z);
	CDebugProc::Print("m_posV %.1f %.1f %.1f \n", m_posR.x, m_posR.y, m_posR.z);
	CDebugProc::Print("m_rot  %.1f %.1f %.1f \n", m_rot.x, m_rot.y, m_rot.z);

	if (key->GetKeyboardPress(DIK_LCONTROL) || key->GetKeyboardPress(DIK_RCONTROL))
	{
		if (key->GetKeyboardTrigger(DIK_1))
		{
			//カメラ切り替え
			m_bCameraMode ^= 1;
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
#ifdef _DEBUG

	CKeyboard *key;
	key = CManager::GetInputKeyboard();
	//カメラの回転
	if (key->GetKeyboardPress(DIK_UP))
	{
		m_rot.x += CAMERA_ROTATION_SPEED;
	}
	if (key->GetKeyboardPress(DIK_DOWN))
	{
		m_rot.x -= CAMERA_ROTATION_SPEED;
	}
	if (key->GetKeyboardPress(DIK_RIGHT))
	{
		m_rot.y += CAMERA_ROTATION_SPEED;
	}
	if (key->GetKeyboardPress(DIK_LEFT))
	{
		m_rot.y -= CAMERA_ROTATION_SPEED;
	}
#endif

	//回転の数値指定
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y += -D3DX_PI * 2;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}
	if (m_rot.x > D3DX_PI*0.5f)
	{
		m_rot.x = D3DX_PI*0.5f;
	}
	if (m_rot.x < -D3DX_PI*0.5f)
	{
		m_rot.x = -D3DX_PI*0.5f;
	}
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
			m_posRDest = pPlayer->GetPosition() + CAMETA_POSR_OFFSET;
		}
	}

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
//カメラを初期座標に設定
//-----------------------------------------------------------------------------
void CCamera::ResetCamera()
{

	//初期座標へ
	m_rotDest = m_rot = DEFAULT_CAMERA_ROTATION;
	m_fDistance = DEFAULT_DISTANCE;
	m_posR = m_posRDest = ZeroVector3;

	m_posV.x = m_posVDest.x = m_posRDest.x - sinf(m_rot.y) * cosf(m_rot.x) * m_fDistance;
	m_posV.y = m_posVDest.y = m_posRDest.y + sinf(m_rot.x)	* m_fDistance;
	m_posV.z = m_posVDest.z = m_posRDest.z - cosf(m_rot.y) * cosf(m_rot.x) * m_fDistance;

	m_vecV = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_bCameraMode = false;


}

//-----------------------------------------------------------------------------
//カメラ座標設定
//-----------------------------------------------------------------------------
void CCamera::SetCameraPos(D3DXVECTOR3 posR, D3DXVECTOR3 posV)
{
	//情報格納
	m_posR = m_posRDest = posR;
	m_posV = m_posVDest = posV;

	//カメラの視点と注視点から角度と距離を求める
	D3DXVECTOR3	Length = m_posV - m_posR;																						//PosRとPosVの座標の差
	m_rot = m_rotDest = D3DXVECTOR3(atan2f(Length.y, Length.z), atan2f(-Length.x, -Length.z), atan2f(Length.x, Length.z));		//初期角度を求める
	m_fDistance = (float)sqrt((Length.y * Length.y + Length.z * Length.z) + Length.x * Length.x);								//視点と注視点の距離

}
