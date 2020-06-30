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
//=============================================================================
// カメラの初期化処理
//=============================================================================
void CCamera::InitCamera(void)
{
	posVDest = posV = D3DXVECTOR3(0.0f, 500.0f, 330.0f);

	posRDest = posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vecV = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 diff = (posV-posR);
	//fDistance = sqrtf(diff.x*diff.x + diff.z*diff.z);
	fDistance = 300;
	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rot = D3DXVECTOR3(0.1f, 0.0f, 0.0f);
	//rot  = D3DXVECTOR3(atan2f(diff.y, diff.z),atan2f(diff.x, diff.z),atan2f(diff.x,diff.y));
	m_bCameraMode = false;
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
	D3DXMatrixIdentity(&mtxProjection);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		10000.0f);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&mtxView);

	// ビューマトリックスを作成
	D3DXMatrixLookAtLH(&mtxView,
		&posV,
		&posR,
		&vecV);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);
}
//=============================================================================
//カメラの移動関数
//=============================================================================
void CCamera::SetMoveCamera(float Crot)
{
	move.x += sinf(-D3DX_PI* Crot + rot.y) * 5;
	move.z += cosf(-D3DX_PI* Crot + rot.y) * 5;
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
	CDebugProc::Print("[Ctrl] + [2] or [Ctrl] + [3] : カメラ距離調整 : Distance>>[%f]\n",fDistance);



	if (key->GetKeyboardPress(DIK_LCONTROL))
	{
		if (key->GetKeyboardTrigger(DIK_1))
		{
			//カメラ切り替え
			m_bCameraMode ^= 1;
		}
		if (key->GetKeyboardPress(DIK_2))
		{
			fDistance += 5.0f;
			//カメラ切り替え
		}
		if (key->GetKeyboardPress(DIK_3))
		{
			//カメラ切り替え
			fDistance -= 5.0f;
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
		rot.x += 0.08f;
	}
	if (key->GetKeyboardPress(DIK_DOWN))
	{
		rot.x -= 0.08f;
	}
	if (key->GetKeyboardPress(DIK_RIGHT))
	{
		rot.y += 0.08f;
	}
	if (key->GetKeyboardPress(DIK_LEFT))
	{
		rot.y -= 0.08f;
	}
#endif

	//回転の数値指定
	if (rot.y > D3DX_PI)
	{
		rot.y += -D3DX_PI * 2;
	}
	if (rot.y < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2;
	}
	if (rot.x > D3DX_PI*0.5f)
	{
		rot.x = D3DX_PI*0.5f;
	}
	if (rot.x < -D3DX_PI*0.5f)
	{
		rot.x = -D3DX_PI*0.5f;
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
			pos = pPlayer->GetPosition();
		}
	}

	//視点の目的地の計算
	posVDest.x = pos.x - sinf(rot.y)*cosf(rot.x)*fDistance;
	posVDest.y = pos.y + sinf(rot.x)			*fDistance;
	posVDest.z = pos.z - cosf(rot.y)*cosf(rot.x)*fDistance;

	//視点の移動
	posV.x += (posVDest.x - posV.x) * 0.08f;
	posV.y += (posVDest.y - posV.y) * 0.08f;
	posV.z += (posVDest.z - posV.z) * 0.08f;

	//カメラ最終目的地の計算
	posRDest.x = pos.x;
	posRDest.y = pos.y;
	posRDest.z = pos.z;

	posR.x += (posRDest.x - posR.x) * 0.08f;
	posR.y += (posRDest.y - posR.y) * 0.08f;
	posR.z += (posRDest.z - posR.z) * 0.08f;

	//慣性抵抗
	move.x += (0 - move.x)*0.3f;
	move.y += (0 - move.y)*0.3f;
	move.z += (0 - move.z)*0.3f;
	pos += move;

	CDebugProc::Print("posV.x:%0.2f\nposV.y:%0.2f\nposV.z:%0.2f\n\n", posV.x, posV.y, posV.z);
	CDebugProc::Print("posR.x:%0.2f\nposR.y:%0.2f\nposR.z:%0.2f\n", posR.x, posR.y, posR.z);
	CDebugProc::Print("rot.x:%0.2f\nrot.y:%0.2f\nrot.z:%0.2f\n", rot.x, rot.y, rot.z);

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

	static D3DXVECTOR2 MousePosCurrent;
	static D3DXVECTOR2 MousePosOld;
	static D3DXVECTOR2 MouseRot;

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
		rotDest.y = NewRotation.y;

		// 回転量を360度ないに直す
		CHossoLibrary::CalcRotation(rotDest.y);

		// ピッチロー回転
		NewRotation.x = (MousePosCurrent.y - MousePosOld.y) / (D3DX_PI*2.0f) *0.03f + MouseRot.x;

		// 回転を90度未満に抑える
		if (NewRotation.x >= D3DX_PI*0.49f)
		{
			NewRotation.x = D3DX_PI*0.49f;
			MousePosOld = MousePosCurrent;
			MouseRot.y = rotDest.y;
			MouseRot.x = rotDest.x;

		}
		else if (NewRotation.x <= -D3DX_PI*0.49f)
		{
			NewRotation.x = -D3DX_PI*0.49f;
			MousePosOld = MousePosCurrent;
			MouseRot.y = rotDest.y;
			MouseRot.x = rotDest.x;

		}
		rotDest.x = NewRotation.x;
	}

	if (pMouse->GetRelease(1))
	{
		MouseRot.y = rotDest.y;
		MouseRot.x = rotDest.x;
	}

	//注視点回転
	if (pKeyboard->GetKeyboardPress(DIK_2))
	{
		rotDest.z += 0.01f;
	}
	else if (pKeyboard->GetKeyboardPress(DIK_X))
	{
		rotDest.z -= 0.01f;
	}

	// カメラの回転を90度未満に抑える
	if (rotDest.x >= D3DX_PI*0.49f)
	{
		rotDest.x = D3DX_PI*0.49f;
	}
	else if (rotDest.x <= -D3DX_PI*0.49f)
	{
		rotDest.x = -D3DX_PI*0.49f;
	}
	// 回転量を360度ないに直す
	CHossoLibrary::CalcRotation(rotDest.y);


	//[W]キーを押した時
	if (pKeyboard->GetKeyboardPress(DIK_W))
	{
		//奥
		posRDest.x += sinf(D3DX_PI * 0.0f + rotDest.y) * CAMERA_MOVE_SPEED;
		posRDest.z += cosf(D3DX_PI * 0.0f + rotDest.y) * CAMERA_MOVE_SPEED;
	}
	//[S]キーを押した時
	if (pKeyboard->GetKeyboardPress(DIK_S))
	{
		//前
		posRDest.x += sinf(D3DX_PI * 1.0f + rotDest.y) * CAMERA_MOVE_SPEED;
		posRDest.z += cosf(D3DX_PI * 1.0f + rotDest.y) * CAMERA_MOVE_SPEED;
	}
	//[A]キーを押した時
	if (pKeyboard->GetKeyboardPress(DIK_A))
	{
		//左
		posRDest.x += sinf(-D3DX_PI * 0.5f + rotDest.y) * CAMERA_MOVE_SPEED;
		posRDest.z += cosf(-D3DX_PI * 0.5f + rotDest.y) * CAMERA_MOVE_SPEED;
	}
	//[D]キーを押した時
	if (pKeyboard->GetKeyboardPress(DIK_D))
	{
		//右
		posRDest.x += sinf(D3DX_PI * 0.5f + rotDest.y) * CAMERA_MOVE_SPEED;
		posRDest.z += cosf(D3DX_PI * 0.5f + rotDest.y) * CAMERA_MOVE_SPEED;
	}

	//[1]キーを押した時
	else if (pKeyboard->GetKeyboardPress(DIK_1))
	{
		//上に移動
		posRDest.x += sinf(D3DX_PI * 0.0f) * CAMERA_MOVE_SPEED;
		posRDest.y += cosf(D3DX_PI * 0.0f) * CAMERA_MOVE_SPEED;
	}
	//[3]キーを押した時
	else if (pKeyboard->GetKeyboardPress(DIK_3))
	{
		//下に移動
		posRDest.x += sinf(D3DX_PI * 1.0f) * CAMERA_MOVE_SPEED;
		posRDest.y += cosf(D3DX_PI * 1.0f) * CAMERA_MOVE_SPEED;
	}

	//回転先
	rot = rotDest;

	// 視点の行く先の更新
	posVDest.x = posR.x - cosf(rot.x) * sinf(rot.y) * fDistance;
	posVDest.y = posR.y + sinf(rot.x) * fDistance;
	posVDest.z = posR.z - cosf(rot.x) * cosf(rot.y) * fDistance;

	// 視点の更新
	posV += (posVDest - posV) * 0.2f;


	// 注視点の更新
	posR += (posRDest - posR) * 0.2f;


}