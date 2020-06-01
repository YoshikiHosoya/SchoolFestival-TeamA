//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : Fujiwara Masato
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "joypad.h"
#include "manager.h"
#include "debugproc.h"
#include "player.h"
#include "mouse.h"
#include "title.h"
#include "pause.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define CAMERA_ROTRATE (0.06f)
// ----------------------------------------
// コンストラクタ処理
// ----------------------------------------
CCamera::CCamera()
{
	m_fx = 0;
	m_fz = 0;
	m_fy = 300;
	// カメラの初期化

	m_posV = D3DXVECTOR3(m_fx, m_fy, m_fz);
	m_posVDest = m_posV;
	m_posVDiff = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(500.0f, 200.0f, 500.0f);
	m_posRDest = m_posR;
	m_posRDiff = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_move = D3DXVECTOR3(1.0f, 3.0f, 3.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fLength = 0;
	m_nCntTime = 0;

	m_fDistance = 500;

	// 視点と注視点との距離計算
	D3DXVECTOR3 diffPos = D3DXVECTOR3(m_posV.x, m_posV.y, m_posV.z - m_fDistance);

	// 長さ計算
	m_fLength = 500;
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CCamera::~CCamera()
{
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void CCamera::Init(void)
{
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void CCamera::Uninit(void)
{
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void CCamera::Update(void)
{
	//一人称視点 プレイヤーと同期
	PlayerPos();

	// 回転
	Rot();

	//CDebugproc::Print("カメラの視点x:%f,y:%f,z:%f\n", m_posVDest.x, m_posVDest.y, m_posVDest.z);
	//CDebugproc::Print("カメラの注視点x:%f,y:%f,z:%f\n", m_posR.x, m_posR.y, m_posR.z);
	//CDebugproc::Print("カメラの角度x:%f,y:%f,z:%f\n", m_rot.x, m_rot.y, m_rot.z);
}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void CCamera::Draw(void)
{
}

// ----------------------------------------
// 作成処理
// ----------------------------------------
CCamera * CCamera::Create(void)
{
	// 変数宣言
	CCamera * pCamera;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pCamera = new CCamera();
	// 初期化処理
	pCamera->Init();
	// 生成したオブジェクトを返す
	return pCamera;
}

// ----------------------------------------
// 設定
// ----------------------------------------
void CCamera::Set(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得

	// プロジェクションマトリックス //
	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(
		&m_mtxProjection,							// (テレビ視点)
		D3DXToRadian(45.0f),						// 視野角(画角)
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	// アスペクト比
		10.0f,										// MearZ値(近いビュー平面のZ値)
		20000.0f);									// FarZ値(遠いビュー平面のZ値)初期値は1000

													// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// ビューマトリックス //
	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	// ビューマトリックスを作成
	D3DXMatrixLookAtLH(
		&m_mtxView,	// (カメラマン視点)
		&m_posV,		// カメラの視点
		&m_posR,		// カメラの注目点
		&m_posU);	// カメラの上方向ベクトル

							// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

// ----------------------------------------
// カメラの方向
// ----------------------------------------
D3DXVECTOR3 CCamera::GetRot(void)
{
	return m_rot;
}

// ----------------------------------------
// カメラの状態を変える
// ----------------------------------------
void CCamera::SetCamera(void)
{
}

// ----------------------------------------
// プレイヤーとの距離を計算
// ----------------------------------------
void CCamera::SetDistance(void)
{
	m_posV = D3DXVECTOR3(m_fx, m_fy, m_fz);

	// 視点と注視点との距離計算
	D3DXVECTOR3 diffPos = m_posV - m_posR;

	// 長さ計算
	m_fLength = sqrtf(diffPos.x*diffPos.x + diffPos.z * diffPos.z);
}

// ----------------------------------------
// カメラの回転を設定
// ----------------------------------------
void CCamera::SetRot(D3DXVECTOR3 rot)
{
	m_rot = D3DXVECTOR3(rot.x, rot.y, rot.z);
	m_rotDest = D3DXVECTOR3(rot.x, rot.y, rot.z);
}

// ----------------------------------------
// 回転
// ----------------------------------------
void CCamera::SetRotWarp(void)
{
	m_rot = D3DXVECTOR3(0.0f, -1.57f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, -1.57f, 0.0f);
}

// ----------------------------------------
// プレイヤー追従
// ----------------------------------------
void CCamera::PlayerFoll(void)
{
	/* 変数宣言 */
	CPlayer * pPlayer = NULL;	// プレイヤー
	// 情報取得
	for (int nCntLayer = 0; nCntLayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntLayer++)
	{
		if (pPlayer == NULL) pPlayer = (CPlayer*)CScene::GetActor(CScene::ACTOR_PLAYER, CScene::LAYER_3DOBJECT, nCntLayer);	// プレイヤー
	}

	m_nCntTime++;				// カウントタイム
	//-------------------- 視点移動 --------------------//
	// ゲームのカメラの回転の目的地
	m_posR = pPlayer->GetPos();
}

// ----------------------------------------
// プレイヤー座標
// ----------------------------------------
void CCamera::PlayerPos(void)
{
	/* 変数宣言 */
	CPlayer * pPlayer = NULL;	// プレイヤー
								// 情報取得
	for (int nCntLayer = 0; nCntLayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntLayer++)
	{
		if (pPlayer == NULL) pPlayer = (CPlayer*)CScene::GetActor(CScene::ACTOR_PLAYER, CScene::LAYER_3DOBJECT, nCntLayer);	// プレイヤー
	}

	m_nCntTime++;				// カウントタイム
								//-------------------- 視点移動 --------------------//
								// ゲームのカメラの位置

	if (pPlayer != NULL)
	{
		m_posV = pPlayer->GetPos();
	}
}

// ----------------------------------------
// 回転
// ----------------------------------------
void CCamera::Rot(void)
{
	CPlayer * pPlayer = NULL;	// プレイヤー

	int nValueH = 0;//スティックの横
	int nValueV = 0;//スティックの縦

								// 情報取得
	for (int nCntLayer = 0; nCntLayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntLayer++)
	{
		if (pPlayer == NULL) pPlayer = (CPlayer*)CScene::GetActor(CScene::ACTOR_PLAYER, CScene::LAYER_3DOBJECT, nCntLayer);	// プレイヤー
	}

	CManager::GetJoy()->GetStickRight(0, &nValueH, &nValueV);

	if (CPause::GetPause() == false)
	{
		if (CManager::GetMode() == CManager::MODE_TITLE && CManager::GetTitle()->GetMode() == CTitle::TITLEMODE_FREE || CManager::GetMode() == CManager::MODE_GAME)
		{
			if (nValueH != 0 || nValueV != 0)
			{
				// 左に倒している時
				if (nValueH <= -1)
				{
					m_rotDest.y -= CAMERA_ROTRATE;
					m_rotDest.y = CCalculation::Rot_One_Limit(m_rotDest.y);
					// -3.14～3.14に回転差分を固定させる
					// 視点更新
					m_posVDest.x = m_posRDest.x + sinf(m_rot.y) * m_fLength;
					m_posVDest.z = m_posRDest.z + cosf(m_rot.y) * m_fLength;
				}
				// 右に倒している時
				else if (nValueH >= 1)
				{
					m_rotDest.y += CAMERA_ROTRATE;
					m_rotDest.y = CCalculation::Rot_One_Limit(m_rotDest.y);
					// -3.14～3.14に回転差分を固定させる
					m_rot.y = CCalculation::Rot_One_Limit(m_rot.y);
					// 視点更新
					m_posVDest.x = m_posRDest.x + sinf(m_rot.y) * m_fLength;
					m_posVDest.z = m_posRDest.z + cosf(m_rot.y) * m_fLength;
				}
			}

			if (CManager::GetKeyboard()->GetKeyboardPress(DIK_LEFT))
			{//左 カメラ視点回転
				m_rotDest.y -= CAMERA_ROTRATE;
				m_rotDest.y = CCalculation::Rot_One_Limit(m_rotDest.y);
				// -3.14～3.14に回転差分を固定させる
				m_rot.y = CCalculation::Rot_One_Limit(m_rot.y);
				// 視点更新
				m_posVDest.x = m_posRDest.x + sinf(m_rot.y) * m_fLength;
				m_posVDest.z = m_posRDest.z + cosf(m_rot.y) * m_fLength;
			}

			else if (CManager::GetKeyboard()->GetKeyboardPress(DIK_RIGHT))
			{//右 カメラ視点回転
				m_rotDest.y += CAMERA_ROTRATE;
				m_rotDest.y = CCalculation::Rot_One_Limit(m_rotDest.y);
				// -3.14～3.14に回転差分を固定させる
				m_rot.y = CCalculation::Rot_One_Limit(m_rot.y);
				// 視点更新
				m_posVDest.x = m_posRDest.x + sinf(m_rot.y) * m_fLength;
				m_posVDest.z = m_posRDest.z + cosf(m_rot.y) * m_fLength;
			}

			// マウスでの視点移動
			//else
			//{
			//	m_rotDest.y = m_rot.y + ((float)CManager::GetMouse()->GetX()/70);
			//	m_rotDest.y = CCalculation::Rot_One_Limit(m_rotDest.y);
			//	// -3.14～3.14に回転差分を固定させる
			//	m_rot.y = CCalculation::Rot_One_Limit(m_rot.y);
			//	// 視点更新
			//	m_posVDest.x = m_posRDest.x + sinf(m_rot.y) * m_fLength;
			//	m_posVDest.z = m_posRDest.z + cosf(m_rot.y) * m_fLength;
			//}
		}
	}

	// 慣性
	float Rotdif = m_rotDest.y - m_rot.y;
	Rotdif = CCalculation::Rot_One_Limit(Rotdif);

	m_rot.y += Rotdif * 0.2f;
	m_rot.y = CCalculation::Rot_One_Limit(m_rot.y);

	if(pPlayer != NULL)
	{
		m_posR.y = pPlayer->GetPos().y;
		m_posR.x = m_posV.x + sinf(D3DX_PI + m_rot.y) * m_fDistance;
		m_posR.z = m_posV.z + cosf(D3DX_PI + m_rot.y) * m_fDistance;
	}
}
