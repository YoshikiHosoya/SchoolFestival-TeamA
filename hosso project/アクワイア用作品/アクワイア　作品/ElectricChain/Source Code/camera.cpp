//-----------------------------------------------------------------------------
//
// カメラ処理 [Camera.cpp]
// Author : Yoshiki Hosoya
//
//-----------------------------------------------------------------------------
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "game.h"
#include "player.h"
#include "tutorial.h"
#include "mouse.h"
#include "collision.h"
#include "model_object.h"
#include "option.h"
#include "Map.h"
#include "enemy.h"
//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define CAMERA_MOVE_SPEED			(10.0f)			//カメラ移動速度
#define CAMERA_ROT_SPEED			(0.015f)		//カメラ回転速度
#define CAMERA_LENGTH_NEAR			(10.0f)			//カメラの見える距離（近）
#define CAMERA_LENGTH_FAR			(4000.0f)		//カメラの見える距離（遠）
#define CAMERA_DEFAULT_POS			(D3DXVECTOR3(0.0f,100.0f,-200.0f))

#define CAMERA_HORIZON_ROTATION		(0.05f)			//カメラの横回転
#define CAMERA_VERTICAL_ROTATION	(0.02f)			//カメラの縦回転
#define CHAINEXPLOSION_LENGTH		(1500.0f)		//連鎖爆発中のカメラの距離

//-----------------------------------------------------------------------------
// 静的メンバ変数宣言
//-----------------------------------------------------------------------------
int CCamera::m_CameraState = CAMERA_DEBUG;

//-----------------------------------------------------------------------------
//コンストラクタ
//-----------------------------------------------------------------------------
CCamera::CCamera()
{
	//初期化
	m_posR = ZeroVector3;
	m_posV = ZeroVector3;
	m_posVOld = ZeroVector3;
	m_posRDest = ZeroVector3;
	m_posVDest = ZeroVector3;
	m_rot = ZeroVector3;
	m_rotDest = ZeroVector3;
	m_move = ZeroVector3;
	m_fDistance = 0.0f;
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_pCollision = nullptr;
	m_CameraState = 0;
	m_MousePosCurrent = ZeroVector2;
	m_MousePosOld = ZeroVector2;
	m_MouseRotSave = ZeroVector2;

	SetCameraPos(CAMERA_DEFAULT_POS, ZeroVector3);

}
//-----------------------------------------------------------------------------
//デストラクタ
//-----------------------------------------------------------------------------
CCamera::~CCamera()
{
	m_pCollision.reset();
}
//-----------------------------------------------------------------------------
//初期化
//-----------------------------------------------------------------------------
void CCamera::Init(void)
{
	//マトリックス計算
	CHossoLibrary::CalcMatrix(&m_mtxWorld, m_posV, m_rot);

	//コリジョン生成
	m_pCollision = CCollision::Create(&m_mtxWorld, CCollision::COLLISION_CAMERA);

	//コリジョン情報設定
	m_pCollision->SetCollisionInfo(10.0f, 10.0f);

	//初期の距離初期化
	m_fDefaultDistace = 0.0f;

}
//-----------------------------------------------------------------------------
//終了
//-----------------------------------------------------------------------------
void CCamera::Uninit(void)
{
}
//-----------------------------------------------------------------------------
//更新
//-----------------------------------------------------------------------------
void CCamera::Update(void)
{
	//1F前の座標保存
	m_posVOld = m_posV;

	switch (m_CameraState)
	{
		//タイトル
	case CCamera::CAMERA_TITLE:

		break;

		//爆発中
	case CCamera::CAMERA_CHAIN_EXPLOSION:
		MoveCameraChainExplosion();
		break;

		//ゲーム中
	case CCamera::CAMERA_GAME:
		if (CManager::GetGame())
		{
			//ポーズ中
			if (CManager::GetGame()->GetGamestate() == CGame::STATE_PAUSE)
			{
				//処理しない
				break;
			}
		}
		//初期の距離に縮める
		m_fDistance += (m_fDefaultDistace - m_fDistance) * 0.03f;

		//カメラ移動
		MoveCameraGame();

		//カメラ回転
		RotCameraGame();

		if (m_fDistance <= 700.0f)
		{
			//判定
			CollisionCamera();
		}
		break;
	case CCamera::CAMERA_RESULT:


		break;
	case CCamera::CAMERA_DEBUG:
		//マウス操作
		MouseCameraOperation();

		//カメラ移動
		MoveCameraDebug();

		//カメラ回転
		RotCameraDebug();
		break;
	}
	//マトリックス計算
	CHossoLibrary::CalcMatrix(&m_mtxWorld, m_posV, m_rot);

}
//-----------------------------------------------------------------------------
//設定処理
//-----------------------------------------------------------------------------
void CCamera::SetCamera(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(
		&m_mtxProjection,
		D3DXToRadian(45.0f),	//視野角
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,		//アスペクト比
		CAMERA_LENGTH_NEAR * 2,								//NearZ値
		CAMERA_LENGTH_FAR * 2);								//FarZ値

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

}

//-----------------------------------------------------------------------------
//カメラ座標設定
//-----------------------------------------------------------------------------
void CCamera::SetCameraPos(D3DXVECTOR3 posR, D3DXVECTOR3 posV)
{
	//情報格納
	m_posR = posR;
	m_posRDest = posR;
	m_posV = posV;
	m_posVDest = posV;

	//カメラの視点と注視点から角度と距離を求める
	D3DXVECTOR3	Length = m_posV - m_posR;																						//PosRとPosVの座標の差
	m_rot = m_rotDest = D3DXVECTOR3(atan2f(Length.y,Length.z), atan2f(-Length.x, -Length.z), atan2f(Length.x, Length.z));		//初期角度を求める
	m_fDistance = (float)sqrt((Length.y * Length.y + Length.z * Length.z) + Length.x * Length.x);								//視点と注視点の距離
	m_fDefaultDistace = m_fDistance;
}
//-----------------------------------------------------------------------------
//カメラの回転設定
//-----------------------------------------------------------------------------
void CCamera::SetCameraRot(D3DXVECTOR3 const rot)
{
	m_rotDest = rot;
}
//-----------------------------------------------------------------------------
//カメラが壁に当たった時に距離を知事メル
//-----------------------------------------------------------------------------
void CCamera::SetDistance()
{
	D3DXVECTOR3	Length = m_posV - m_posR;																			//PosRとPosVの座標の差
	m_fDistance = (float)sqrt((Length.y * Length.y + Length.z * Length.z) + Length.x * Length.x);					//視点と注視点の距離

}
//-----------------------------------------------------------------------------
//カメラ情報
//-----------------------------------------------------------------------------
void CCamera::ShowCameraInfo()
{
#ifdef _DEBUG

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (ImGui::CollapsingHeader("CameraInfo"))
	{
		ImGui::InputFloat3("PosV", m_posV);
		ImGui::InputFloat3("PosR", m_posR);
		ImGui::InputFloat3("Rot", m_rot);
		ImGui::InputFloat3("RotDest", m_rotDest);
		ImGui::InputFloat("distance", &m_fDistance, 10.0f, 10.0f);

		if (ImGui::RadioButton("CAMERA_GAME", &m_CameraState, 1))
		{

		}
		ImGui::SameLine();
		if (ImGui::RadioButton("CAMERA_DEBUG", &m_CameraState, 4))
		{

		}
	}
#endif //DEBUG
}

//-----------------------------------------------------------------------------
//移動処理
//-----------------------------------------------------------------------------
void CCamera::MoveCameraDebug(void)
{
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	//[W]キーを押した時
	if (pKeyboard->GetPress(DIK_W))
	{
		//奥
		m_posRDest.x += sinf(D3DX_PI * 0.0f + m_rotDest.y) * CAMERA_MOVE_SPEED;
		m_posRDest.z += cosf(D3DX_PI * 0.0f + m_rotDest.y) * CAMERA_MOVE_SPEED;
	}
	//[S]キーを押した時
	if (pKeyboard->GetPress(DIK_S))
	{
		//前
		m_posRDest.x += sinf(D3DX_PI * 1.0f + m_rotDest.y) * CAMERA_MOVE_SPEED;
		m_posRDest.z += cosf(D3DX_PI * 1.0f + m_rotDest.y) * CAMERA_MOVE_SPEED;
	}
	//[A]キーを押した時
	if (pKeyboard->GetPress(DIK_A))
	{
		//左
		m_posRDest.x += sinf(-D3DX_PI * 0.5f + m_rotDest.y) * CAMERA_MOVE_SPEED;
		m_posRDest.z += cosf(-D3DX_PI * 0.5f + m_rotDest.y) * CAMERA_MOVE_SPEED;
	}
	//[D]キーを押した時
	if (pKeyboard->GetPress(DIK_D))
	{
		//右
		m_posRDest.x += sinf(D3DX_PI * 0.5f + m_rotDest.y) * CAMERA_MOVE_SPEED;
		m_posRDest.z += cosf(D3DX_PI * 0.5f + m_rotDest.y) * CAMERA_MOVE_SPEED;
	}

	//[1]キーを押した時
	else if (pKeyboard->GetPress(DIK_1))
	{
		//上に移動
		m_posRDest.x += sinf(D3DX_PI * 0.0f) * CAMERA_MOVE_SPEED;
		m_posRDest.y += cosf(D3DX_PI * 0.0f) * CAMERA_MOVE_SPEED;
	}
	//[3]キーを押した時
	else if (pKeyboard->GetPress(DIK_3))
	{
		//下に移動
		m_posRDest.x += sinf(D3DX_PI * 1.0f) * CAMERA_MOVE_SPEED;
		m_posRDest.y += cosf(D3DX_PI * 1.0f) * CAMERA_MOVE_SPEED;
	}
}
//-----------------------------------------------------------------------------
//回転処理
//-----------------------------------------------------------------------------
void CCamera::RotCameraDebug(void)
{
	//3.14の範囲に抑える
	CHossoLibrary::CalcRotation(m_rotDest.y);

	//回転先
	m_rot = m_rotDest;

	/*---------------------------------------------
	//	視点の更新
	---------------------------------------------*/
	// 視点の行く先の更新
	m_posVDest.x = m_posR.x - cosf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
	m_posVDest.y = m_posR.y + sinf(m_rot.x) * m_fDistance;
	m_posVDest.z = m_posR.z - cosf(m_rot.x) * cosf(m_rot.y) * m_fDistance;

	// 視点の更新
	m_posV += (m_posVDest - m_posV) * 0.2f;

	/*---------------------------------------------
	//	注視点の更新
	---------------------------------------------*/
	// 注視点の行く先の更新
	m_posRDest.x;
	m_posRDest.y;
	m_posRDest.z;

	// 注視点の更新
	m_posR += (m_posRDest - m_posR) * 0.2f;
}

//-----------------------------------------------------------------------------
//カメラの操作
//-----------------------------------------------------------------------------
void CCamera::MouseCameraOperation()
{
	// キーボードの取得
	CKeyboard *pKeyboard = CManager::GetKeyboard();
	CMouse *pMouse = CManager::GetMouse();

	D3DXVECTOR2 NewRotation = ZeroVector2;

	// マウスの座標保持
	m_MousePosCurrent = pMouse->GetMousePos();

	//マウス入力されてない時
	if (pMouse->GetPress(1) == false)
	{
		// 前回の位置の設定
		m_MousePosOld = m_MousePosCurrent;
	}
	//マウス入力されているとき
	else
	{
		// 横回転
		NewRotation.y = (m_MousePosCurrent.x - m_MousePosOld.x) / (D3DX_PI*2.0f) *0.03f + m_MouseRotSave.y;
		m_rotDest.y = NewRotation.y;

		// 回転量を360度ないに直す
		CHossoLibrary::CalcRotation(m_rotDest.y);

		// ピッチロー回転
		NewRotation.x = (m_MousePosCurrent.y - m_MousePosOld.y) / (D3DX_PI*2.0f) *0.03f + m_MouseRotSave.x;

		// 回転を90度未満に抑える
		if (NewRotation.x >= D3DX_PI*0.49f)
		{
			NewRotation.x = D3DX_PI*0.49f;
			m_MousePosOld = m_MousePosCurrent;
			m_MouseRotSave.y = m_rotDest.y;
			m_MouseRotSave.x = m_rotDest.x;

		}
		else if (NewRotation.x <= -D3DX_PI*0.49f)
		{
			NewRotation.x = -D3DX_PI*0.49f;
			m_MousePosOld = m_MousePosCurrent;
			m_MouseRotSave.y = m_rotDest.y;
			m_MouseRotSave.x = m_rotDest.x;

		}
		m_rotDest.x = NewRotation.x;
	}

	if (pMouse->GetRelease(1))
	{
		m_MouseRotSave.y = m_rotDest.y;
		m_MouseRotSave.x = m_rotDest.x;
	}

	//注視点回転
	if (pKeyboard->GetPress(DIK_2))
	{
		m_rotDest.z += 0.01f;
	}
	else if (pKeyboard->GetPress(DIK_X))
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

	if (CManager::GetGame() == NULL)
	{
		return;
	}
}

//-----------------------------------------------------------------------------
//移動処理
//-----------------------------------------------------------------------------
void CCamera::MoveCameraGame(void)
{
	CKeyboard	*pKeyboard	= CManager::GetKeyboard();

	float fCameraRotation_X = CAMERA_HORIZON_ROTATION;
	float fCameraRotation_Y = CAMERA_VERTICAL_ROTATION;

	//オプションで反転がONだったら反転
	if (COption::GetCameraFlip_X())
	{
		fCameraRotation_X *= -1;
	}
	//オプションで反転がONだったら反転
	if (COption::GetCameraFlip_Y())
	{
		fCameraRotation_Y *= -1;
	}

	// 上昇
	if (pKeyboard->GetPress(DIK_W))
	{
		// 時計回りに回転
		m_rotDest.x += fCameraRotation_Y;
	}

	// 下降
	if (pKeyboard->GetPress(DIK_S))
	{
		// 時計回りに回転
		m_rotDest.x -= fCameraRotation_Y;
	}

	// 視点の回転
	if (pKeyboard->GetPress(DIK_D))
	{
		// 時計回りに回転
		m_rotDest.y -= fCameraRotation_X;
	}

	if (pKeyboard->GetPress(DIK_A))
	{
		// 時計回りに回転
		m_rotDest.y += fCameraRotation_X;
	}

	//右スティックでカメラの回転
	CHossoLibrary::Check3DCameraStick(m_rotDest, fCameraRotation_X, fCameraRotation_Y);

	//縦方向　回転制限
	if (m_rotDest.x < 2.0f)
	{
		m_rotDest.x = 2.0f;
	}
	if (m_rotDest.x > 3.1f)
	{
		m_rotDest.x = 3.1f;
	}

	//3.14の範囲に抑える
	CHossoLibrary::CalcRotation(m_rotDest.y);
}
//-----------------------------------------------------------------------------
//回転処理
//-----------------------------------------------------------------------------
void CCamera::RotCameraGame(void)
{
	//キーボードのポインタ
	CKeyboard	*pKeyboard = CManager::GetKeyboard();

	// posRとposVのそれぞれの差分
	D3DXVECTOR3 difposR, difposV;

	//プレイヤーの情報取得
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();

	//nullcheck
	if (pPlayer)
	{
		//注視点をプレイヤーに合わす
		m_posRDest = pPlayer->GetCenterPos();

		//m_posRDest.x -= sinf(pPlayer->GetRot().y) * 50.0f;
		//m_posRDest.z -= cosf(pPlayer->GetRot().y) * 50.0f;
	}

	//回転の差分
	D3DXVECTOR3 rotDiff = m_rotDest - m_rot;

	//3.14超えないようにする
	CHossoLibrary::CalcRotation(rotDiff.x);
	CHossoLibrary::CalcRotation(rotDiff.y);

	//回転
	m_rot += rotDiff * 0.1f;

	// 現在の注視点と目的の注視点の差分の計算
	difposR = m_posRDest - m_posR;

	// 注視点を追いかける速度
	m_posR += difposR * 0.1f;

	m_posVDest.x = m_posR.x + cosf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
	m_posVDest.y = m_posR.y + sinf(m_rot.x) * m_fDistance;
	m_posVDest.z = m_posR.z + cosf(m_rot.x) * cosf(m_rot.y) * m_fDistance;

	// 現在の視点と目的の視点の差分の計算
	difposV = m_posVDest - m_posV;

	// 視点が注視点に追いつく速度
	m_posV += difposV * 0.15f;

	//3.14超えないようにする
	CHossoLibrary::CalcRotation(m_rot.x);
	CHossoLibrary::CalcRotation(m_rot.y);

}
//-----------------------------------------------------------------------------
//連鎖爆発中のカメラ
//-----------------------------------------------------------------------------
void CCamera::MoveCameraChainExplosion()
{
	//カメラを離す
	m_fDistance = CHAINEXPLOSION_LENGTH;

	//カメラ回転処理
	RotCameraGame();

	//敵の総数が0になった
	if (CEnemy::GetStanEnemyNum() <= 0)
	{
		//元の状態に戻す
		CManager::GetRenderer()->GetCamera()->SetState(CCamera::CAMERA_GAME);
	}

}
//-----------------------------------------------------------------------------
//カメラと壁の当たり判定
//-----------------------------------------------------------------------------
void CCamera::CollisionCamera()
{
	//フィールドの広さ取得
	D3DXVECTOR3 FieldSize = CMap::GetFieldSize() * 0.5f;

	//フィールド外に出れないようにする
	if (CHossoLibrary::RangeLimit_Equal_Float(m_posV.x, -FieldSize.x, +FieldSize.x))
	{
		//カメラ関係リセット
		CCamera::SetDistance();
	}

	else if (CHossoLibrary::RangeLimit_Equal_Float(m_posV.z, -FieldSize.z, +FieldSize.z))
	{
		//カメラ関係リセット
		CCamera::SetDistance();
	}
}
//-----------------------------------------------------------------------------
//カメラのモードを変更
//-----------------------------------------------------------------------------
void CCamera::SetState(int nState)
{
	m_CameraState = nState;
}
