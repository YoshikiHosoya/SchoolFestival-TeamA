//=============================================================================
// カメラ処理 [camera.cpp]
//=============================================================================
#include "camera.h"
#include "inputKeyboard.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "Player.h"
#include "Scene.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_LENGTH (-100) //カメラの距離
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
	fDistance = sqrtf(diff.x*diff.x + diff.z*diff.z);
	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rot  = D3DXVECTOR3(atan2f(diff.y, diff.z),atan2f(diff.x, diff.z),atan2f(diff.x,diff.y));
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
	CKeyboard *key;
	key = CManager::GetInputKeyboard();
	//カメラの回転---------------------------------------------------------■■■
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

	//回転の数値指定-------------------------------------------------------■■■
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
	//追従処理================================================================================■■■
	//キャスト
	CScene *pScene;
	pScene = CScene::GetScene(CScene::OBJTYPE_PLAYER);
	if (pScene != NULL)
	{
		pos = ((CPlayer*)pScene)->GetPosition();
	}
	////視点の目的地の計算-------------------------------------------------■■■
	posVDest.x = pos.x - sinf(rot.y)*cosf(rot.x)*fDistance;
	posVDest.y = pos.y + sinf(rot.x)			*fDistance;
	posVDest.z = pos.z - cosf(rot.y)*cosf(rot.x)*fDistance;

	//視点の移動-----------------------------------------------------------■■■
	posV.x += (posVDest.x - posV.x) * 0.08f;
	posV.y += (posVDest.y - posV.y) * 0.08f;
	posV.z += (posVDest.z - posV.z) * 0.08f;

	//カメラ最終目的地の計算-----------------------------------------------■■■
	posRDest.x = pos.x;
	posRDest.y = pos.y;
	posRDest.z = pos.z;

	posR.x += (posRDest.x - posR.x) * 0.08f;
	posR.y += (posRDest.y - posR.y) * 0.08f;
	posR.z += (posRDest.z - posR.z) * 0.08f;
	//========================================================================================■■■

	//慣性抵抗-------------------------------------------------------------■■■
	move.x += (0 - move.x)*0.3f;
	move.y += (0 - move.y)*0.3f;
	move.z += (0 - move.z)*0.3f;
	pos += move;

	CDebugProc::Print("posV.x:%0.2f\nposV.y:%0.2f\nposV.z:%0.2f\n\n", posV.x, posV.y, posV.z);
	CDebugProc::Print("posR.x:%0.2f\nposR.y:%0.2f\nposR.z:%0.2f\n", posR.x, posR.y, posR.z);
}
//=============================================================================
// カメラの設定処理
//=============================================================================
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();

	// プロジェクションマトリックスの初期化--------------------------------■■■
	D3DXMatrixIdentity(&mtxProjection);

	// プロジェクションマトリックスを作成----------------------------------■■■
	D3DXMatrixPerspectiveFovLH(&mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		10000.0f);

	// プロジェクションマトリックスの設定----------------------------------■■■
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);

	// ビューマトリックスの初期化------------------------------------------■■■
	D3DXMatrixIdentity(&mtxView);

	// ビューマトリックスを作成--------------------------------------------■■■
	D3DXMatrixLookAtLH(&mtxView,
		&posV,
		&posR,
		&vecV);

	// ビューマトリックスの設定--------------------------------------------■■■
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
