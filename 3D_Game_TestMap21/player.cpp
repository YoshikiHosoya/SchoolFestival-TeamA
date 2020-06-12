// =====================================================================================================================================================================
//
// プレイヤーの処理 [player.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "player.h"			// インクルードファイル
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"
#include "camera.h"
#include "keyboard.h"
#include "game.h"
#include "scene3D.h"
#include "modelcharacter.h"
#include "slope.h"
#include "map.h"
#include "gameUI.h"
#include "fade.h"
#include "object2D.h"
#include "sound.h"
#include "xinputGpad.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
CModelCharacter				*CPlayer::m_pModelCharacter = NULL;
CPlayer::PLAYERSTATE		CPlayer::m_state = PLAYERSTATE::PLAYERSTATE_NONE;

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define TEXTURE_FILE		"data/TEXTURE/kids.jpg"	// 読み込むテクスチャファイル名

#define PLAYER_SIZEX		(300 / 2)				// 座標の幅
#define PLAYER_SIZEY		(220 / 2)				// 座標の高さ

#define PLAYER_SPEED		(2)						// プレイヤーの速さ
#define PLAYER_RADIUS		(10.0f)					// プレイヤーの半径
#define PLAYER_MAX_LIFE		(99)					// プレイヤーの最大体力

#define FALL_DISTANCE		(70)					// 落下死する距離

#define FLASHING_TIME		(90)					// 点滅する時間
#define FLASHING_INTERVAL	(3)						// 点滅する感覚

#define MOVE_MOTION_VALUE	(0.2f)					// 移動モーションするときの移動量
#define INERTIA_VALUE		(0.3f)					// 慣性の値
#define ROT_DIFFERENCE		(0.15f)					// 回転の差分
#define FIELD_LIMIT			(145.0f)				// フィールドの限界範囲
#define JUMP_VALUE			(4)						// ジャンプの値
#define GRAVITY_VALUE		(0.5f)					// 重力の値

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CPlayer::CPlayer():CScene()
{
}

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CPlayer::CPlayer(PRIORITY Priority) :CScene(Priority)
{
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CPlayer::~CPlayer()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
void CPlayer::Init()
{
	// 変数初期化
	m_pos			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 位置
	m_posOld		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 過去の位置
	m_posRestart	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 再開位置
	m_size			= D3DXVECTOR3(4.0f, 50.0f, 4.0f);			// サイズ
	m_move			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 移動
	m_rot			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 回転
	m_rotDiff		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの差分
	m_rotDest		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 目的の向き
	m_fJumpingPos	= 0;										// 地面から離れた瞬間の位置
	m_fLandingPos	= 0;										// 着地した時の位置
	m_bJump			= false;									// ジャンプフラグ
	m_bFlashing		= false;									// 死んだときの点滅フラグ
	m_bLand			= false;									// 着地したときのフラグ
	m_nCntDeath		= 0;										// 死んだときのカウント
	m_nLife			= 3;										// 体力
	m_state			= PLAYERSTATE_APPEAR;						// プレイヤーの状態
	m_LeftStick_X	= 0;										// 左スティックのXの値
	m_LeftStick_Y	= 0;										// 左スティックのYの値
	m_RightStick_X	= 0;										// 右スティックのXの値
	m_RightStick_Y	= 0;										// 右スティックのYの値
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CPlayer::Uninit(void)
{
	if (m_pModelCharacter != NULL)
	{
		// モデルキャラクターの終了
		m_pModelCharacter->Uninit();

		// メモリ開放
		delete m_pModelCharacter;
		m_pModelCharacter = NULL;
	}
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CPlayer::Update(void)
{
	// 変数
	CCamera *pCamera;
	CKeyboard *pKeyboard;
	CXinputGpad *pXinputGpad;
	// メモリの確保
	pKeyboard = CManager::GetKeyboard();
	pCamera = CRenderer::GetCamera();
	pXinputGpad = CManager::GetXinputGpad();

	m_bLand = false;	// 地上にいる判定
	m_posOld = m_pos;	// 過去の位置の保存

	// ==========================================================================
	// ----- [ ジャンプ ] -----
	// ==========================================================================
	if (!m_bJump)
	{
		if (pKeyboard->GetKeyboardTrigger(DIK_SPACE) || pXinputGpad->GetTriggerXinputGpad(CXinputGpad::XINPUT_A))
		{
			//	ジャンプ音
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_JUMP);

			m_fJumpingPos = m_pos.y;		// 飛ぶ位置の保存

			// ジャンプモーション
			m_pModelCharacter->SetMotion(CModelCharacter::PlayerMotionType_JUMP);

			m_bJump = true;			// ジャンプいている状態

			m_move.y += PLAYER_SPEED * JUMP_VALUE;		// ジャンプ値
		}
	}

	// 死んでないとき
	if (m_state != PLAYERSTATE_DEATH)
	{
		// プレイヤーの移動処理
		MovePlayer();
	}

	// 移動量を求める
	float MoveValue = D3DXVec2Length(&D3DXVECTOR2(m_move.x, m_move.z));
	// 絶対値計算
	MoveValue = fabsf(MoveValue);

	// ジャンプしていないとき
	if (!m_bJump)
	{
		// 一定の移動量に達していたら
		if (MoveValue >= MOVE_MOTION_VALUE)
		{
			// 歩きモーション
			m_pModelCharacter->SetMotion(CModelCharacter::PlayerMotionType_WALK);
		}
		else
		{
			// ニュートラルモーション
			m_pModelCharacter->SetMotion(CModelCharacter::PlayerMotionType_NEUTRAL);
		}
	}

	float fFallDistance = 0.0f;						// 落下する距離
	fFallDistance = m_fJumpingPos - m_pos.y;	// 落下している距離計算

	// 落下死判定
	if (fFallDistance >= FALL_DISTANCE)
	{
		// プレイヤーの落下死
		PlayerFallDeath();
	}

#ifdef _DEBUG
	// [ 初期値に戻る ]	試験的配置
	if (pKeyboard->GetKeyboardPress(DIK_0))
	{
		D3DXVECTOR3 pos = D3DXVECTOR3(m_pos.x, m_pos.y + 10.0f, m_pos.z);

		m_pos = pos;
	}
#endif

	// オブジェクトの当たり判定
	if (CMap::CollisionObjectAll(&m_pos, &m_posOld, &m_move, &m_size))
	{
		if (m_bJump)
		{
			//	着地音
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_LAND);
			// 着地判定
			m_bLand = true;
		}

		m_bJump = false;

		m_fLandingPos = m_pos.y;	// 飛ぶ位置の保存

		float fFallDistance = 0.0f;								// 落下した距離
		fFallDistance = m_fJumpingPos - m_fLandingPos;	// 落下した距離計算

		// 落下死判定
		if (fFallDistance >= FALL_DISTANCE)
		{
			// プレイヤーの落下死
			PlayerFallDeath();
		}
		m_fJumpingPos = m_pos.y;		// 飛ぶ位置の保存
	}
	// 2Dオブジェクトの当たり判定
	else if (CMap::CollisionObject2DAll(&m_pos, &m_posOld, &m_move, &m_size))
	{
		if (m_bJump)
		{
			//	着地音
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_LAND);
			// 着地判定
			m_bLand = true;
		}

		m_bJump = false;

		m_fLandingPos = m_pos.y;	// 飛ぶ位置の保存

		float fFallDistance = 0.0f;								// 落下した距離
		fFallDistance = m_fJumpingPos - m_fLandingPos;	// 落下した距離計算

		// 落下死判定
		if (fFallDistance >= FALL_DISTANCE)
		{
			// プレイヤーの落下死
			PlayerFallDeath();
		}
		m_fJumpingPos = m_pos.y;		// 飛ぶ位置の保存
	}
	// 坂の当たり判定
	else if (CMap::GetHeightSlopeAll(m_pos, m_move))
	{
		if (m_bJump)
		{
			//	着地音
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_LAND);
			// 着地判定
			m_bLand = true;
		}

		m_bJump = false;

		m_fLandingPos = m_pos.y;	// 飛ぶ位置の保存

		float fFallDistance = 0.0f;								// 落下した距離
		fFallDistance = m_fJumpingPos - m_fLandingPos;			// 落下した距離計算

		// 落下死判定
		if (fFallDistance >= FALL_DISTANCE)
		{
			// プレイヤーの落下死
			PlayerFallDeath();
		}
		m_fJumpingPos = m_pos.y;		// 飛ぶ位置の保存
	}
	else
	{
		m_bJump = true;		// ジャンプできる状態
	}

	// モデルキャラクターの更新
	m_pModelCharacter->Update();

	// ワールドマトリックスの計算
	CLibrary::MatrixCalculation(&m_mtxWorld, m_rot, m_pos);

	// ライフの設定
	CManager::GetGame()->GetGameUI()->SetLife(m_nLife);

	// プレイヤーの状態の各設定
	PlayerStateConfig();

	// デバッグ表示
	CDebugProc::Print("PlayerPos :(%.0f, %.0f, %.0f)\n", m_pos.x, m_pos.y, m_pos.z);

	ImGui::SliderFloat3("player_pos", m_pos, -50000.0f, 50000.0f);
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CPlayer::Draw(void)
{
	if (!m_bFlashing)
	{
		// マトリックスの設定
		m_pModelCharacter->SetMatrix(&m_mtxWorld);

		// モデルキャラクターの描画
		m_pModelCharacter->Draw();
	}
}

// =====================================================================================================================================================================
//
// プレイヤーの生成
//
// =====================================================================================================================================================================
CPlayer * CPlayer::Create()
{
	// 変数
	CPlayer *pPlayer;

	// メモリの確保
	pPlayer = new CPlayer(PRIORITY_MODEL);

	// モデルキャラクターの生成
	pPlayer->m_pModelCharacter = CModelCharacter::Create();

	// 初期化
	pPlayer->Init();

	return pPlayer;
}

// =====================================================================================================================================================================
//
// ロード
//
// =====================================================================================================================================================================
HRESULT CPlayer::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

	return S_OK;
}

// =====================================================================================================================================================================
//
// アンロード
//
// =====================================================================================================================================================================
void CPlayer::Unload(void)
{

}

// =====================================================================================================================================================================
//
// プレイヤーの移動処理
//
// =====================================================================================================================================================================
void CPlayer::MovePlayer(void)
{
	// 変数
	CCamera *pCamera;
	CKeyboard *pKeyboard;
	CXinputGpad *pXinputGpad;

	// メモリの確保
	pCamera = CManager::GetRenderer()->GetCamera();
	pKeyboard = CManager::GetKeyboard();
	pXinputGpad = CManager::GetXinputGpad();

	// カメラの回転
	D3DXVECTOR3 CameraRot = CManager::GetRenderer()->GetCamera()->GetRot();

	// 左スティックの値の取得
	pXinputGpad->GetLeftStickValue(m_LeftStick_X, m_LeftStick_Y);

	// 左スティックを倒したときの角度
	float fLeftStickAngle = atan2f(m_LeftStick_X, m_LeftStick_Y);
	// 左スティックを倒したときの向き
	D3DXVECTOR2 LeftStickVec = D3DXVECTOR2((float)sin(fLeftStickAngle - CameraRot.y), (float)cos(fLeftStickAngle - CameraRot.y));
	CDebugProc::Print("左スティック X ( %f )\n", LeftStickVec.x);
	CDebugProc::Print("左スティック Y ( %f )\n", LeftStickVec.y);

	// -------------------------------------------------------------------------
	// [ 左スティック移動 ]
	// -------------------------------------------------------------------------
	if (m_LeftStick_X > 0 || m_LeftStick_Y > 0 ||
		m_LeftStick_X < 0 || m_LeftStick_Y < 0)
	{
		if (m_move != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			m_rotDest.y = (D3DX_PI + fLeftStickAngle - CameraRot.y);
		}
		m_move.x += PLAYER_SPEED * LeftStickVec.x;
		m_move.z += PLAYER_SPEED * LeftStickVec.y;
	}

	// -------------------------------------------------------------------------
	// [ 左移動 ]
	// -------------------------------------------------------------------------
	if (pKeyboard->GetKeyboardPress(DIK_A))
	{
		if (pKeyboard->GetKeyboardPress(DIK_W))
		{// 左上
			// カメラモードが2Dじゃないとき
			if (pCamera->GetCameraMode() != CCamera::CAMERA_MODE_2D)
			{
				m_rotDest.y = (D3DX_PI * 0.75f - CameraRot.y);

				m_move.x += sinf(-D3DX_PI * 0.75f + CameraRot.y) * PLAYER_SPEED;
				m_move.z -= cosf(-D3DX_PI * 0.75f + CameraRot.y) * PLAYER_SPEED;
			}
		}
		else if (pKeyboard->GetKeyboardPress(DIK_S))
		{// 左下
			// カメラモードが2Dじゃないとき
			if (pCamera->GetCameraMode() != CCamera::CAMERA_MODE_2D)
			{
				m_rotDest.y = (D3DX_PI * 0.25f - CameraRot.y);

				m_move.x += sinf(-D3DX_PI * 0.25f + CameraRot.y) * PLAYER_SPEED;
				m_move.z -= cosf(-D3DX_PI * 0.25f + CameraRot.y) * PLAYER_SPEED;
			}
		}
		else
		{// 左
			m_rotDest.y = (D3DX_PI * 0.5f - CameraRot.y);

			m_move.x += sinf(-D3DX_PI * 0.5f + CameraRot.y) * PLAYER_SPEED;
			m_move.z -= cosf(-D3DX_PI * 0.5f + CameraRot.y) * PLAYER_SPEED;
		}
	}

	// -------------------------------------------------------------------------
	// [ 右移動 ]
	// -------------------------------------------------------------------------
	else if (pKeyboard->GetKeyboardPress(DIK_D))
	{
		if (pKeyboard->GetKeyboardPress(DIK_W))
		{// 右上
			// カメラモードが2Dじゃないとき
			if (pCamera->GetCameraMode() != CCamera::CAMERA_MODE_2D)
			{
				m_rotDest.y = (-D3DX_PI * 0.75f - CameraRot.y);

				m_move.x += sinf(D3DX_PI * 0.75f + CameraRot.y) * PLAYER_SPEED;
				m_move.z -= cosf(D3DX_PI * 0.75f + CameraRot.y) * PLAYER_SPEED;
			}

		}
		else if (pKeyboard->GetKeyboardPress(DIK_S))
		{// 右下
			// カメラモードが2Dじゃないとき
			if (pCamera->GetCameraMode() != CCamera::CAMERA_MODE_2D)
			{
				m_rotDest.y = (-D3DX_PI * 0.25f - CameraRot.y);

				m_move.x += sinf(D3DX_PI * 0.25f + CameraRot.y) * PLAYER_SPEED;
				m_move.z -= cosf(D3DX_PI * 0.25f + CameraRot.y) * PLAYER_SPEED;
			}

		}
		else
		{// 右
			m_rotDest.y = (-D3DX_PI * 0.5f - CameraRot.y);

			m_move.x += sinf(D3DX_PI * 0.5f + CameraRot.y) * PLAYER_SPEED;
			m_move.z -= cosf(D3DX_PI * 0.5f + CameraRot.y) * PLAYER_SPEED;
		}
	}
	// -------------------------------------------------------------------------
	// [ 前移動 ]
	// -------------------------------------------------------------------------
	else if (pKeyboard->GetKeyboardPress(DIK_W))
	{
		// カメラモードが2Dじゃないとき
		if (pCamera->GetCameraMode() != CCamera::CAMERA_MODE_2D)
		{
			m_rotDest.y = (D3DX_PI * 1.0f - CameraRot.y);

			m_move.x += sinf(D3DX_PI * 1.0f + CameraRot.y) * PLAYER_SPEED;
			m_move.z -= cosf(D3DX_PI * 1.0f + CameraRot.y) * PLAYER_SPEED;
		}
	}
	// -------------------------------------------------------------------------
	// [ 後移動 ]
	// -------------------------------------------------------------------------
	else if (pKeyboard->GetKeyboardPress(DIK_S))
	{
		// カメラモードが2Dじゃないとき
		if (pCamera->GetCameraMode() != CCamera::CAMERA_MODE_2D)
		{
			m_rotDest.y = (D3DX_PI * 0.0f - CameraRot.y);

			m_move.x += sinf(D3DX_PI * 0.0f + CameraRot.y) * PLAYER_SPEED;
			m_move.z -= cosf(D3DX_PI * 0.0f + CameraRot.y) * PLAYER_SPEED;
		}
	}

	// 差分
	m_rotDiff.y = m_rotDest.y - m_rot.y;

	// 回転情報の差分をただす
	if (m_rotDiff.y > D3DX_PI)
	{
		m_rotDiff.y -= D3DX_PI * 2;
	}
	if (m_rotDiff.y <= -D3DX_PI)
	{
		m_rotDiff.y += D3DX_PI * 2;
	}

	// 慣性処理
	m_move.x += (0 - m_move.x) * INERTIA_VALUE;
	m_move.z += (0 - m_move.z) * INERTIA_VALUE;

	// 重力処理
	m_move.y -= GRAVITY_VALUE;

	// 位置更新
	m_pos += m_move;

	// 回転更新 
	m_rot.y += m_rotDiff.y * ROT_DIFFERENCE;

	// 回転情報をただす
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2;
	}
	if (m_rot.y <= -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}

	// カメラモードが2Dのとき
	if (pCamera->GetCameraMode() == CCamera::CAMERA_MODE_2D)
	{
		m_pos.x = 0.0f;
	}

	// プレイヤーの移動制限
	if (m_pos.x <= -FIELD_LIMIT)
	{
		m_move.x = 0.0f;
		m_pos.x = -FIELD_LIMIT;
	}
	else if (m_pos.x >= FIELD_LIMIT)
	{
		m_move.x = 0.0f;
		m_pos.x = FIELD_LIMIT;
	}
}

// =====================================================================================================================================================================
//
// プレイヤーの状態の各設定
//
// =====================================================================================================================================================================
void CPlayer::PlayerStateConfig(void)
{
	// カメラの情報
	CCamera *pCamera;
	pCamera = CRenderer::GetCamera();

	switch (m_state)
	{
	case CPlayer::PLAYERSTATE_APPEAR:
		break;
	case CPlayer::PLAYERSTATE_NORMAL:
		break;
	case CPlayer::PLAYERSTATE_SPEED:
		break;
	case CPlayer::PLAYERSTATE_FALL:
		break;
	case CPlayer::PLAYERSTATE_DEATH:
		// カウントアップ
		m_nCntDeath++;

		// 点滅する感覚
		if (m_nCntDeath % FLASHING_INTERVAL == 0)
		{
			// 死んだときの点滅
			m_bFlashing = !m_bFlashing;
		}

		// 一定時間後にリスポーン
		if (m_nCntDeath >= FLASHING_TIME)
		{
			if (m_nLife > 0)
			{
				// リスポーン地点に戻す		( 試験的配置
				m_pos = m_posRestart;

				if (pCamera != NULL)
				{
					// プレイヤーが死んだときのカメラの位置
					pCamera->SetDeadPlayerCameraPos(m_pos);
				}
			}

			// 飛ぶ位置を現在地に指定
			m_fJumpingPos = m_pos.y;

			// 点滅を止める
			m_bFlashing = false;
			// カウント初期化
			m_nCntDeath = 0;
			// プレイヤーの状態を通常時に
			m_state = PLAYERSTATE_NORMAL;

			if (m_nLife <= 0)
			{
				// プレイヤーの状態を通常時に
				m_state = PLAYERSTATE_DEATH;

				// ゲーム終了(ゲームエンド)
				CManager::GetGame()->SetGameMode(CGame::GAME_MODE_END);
			}
		}
		// ゲージの回復
		CGameUI::RecoveryGage();
		break;
	}
}

// =====================================================================================================================================================================
//
// プレイヤーの落下死
//
// =====================================================================================================================================================================
void CPlayer::PlayerFallDeath(void)
{
	//	死んだときの音
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_DEATH);

	// プレイヤーダメージ
	PlayerDamage(1);

	m_state = PLAYERSTATE_DEATH;	// プレイヤーを死亡状態に
}

// =====================================================================================================================================================================
//
// ダメージ処理
//
// =====================================================================================================================================================================
void CPlayer::PlayerDamage(int nLife)
{
	// 死亡状態以外のとき
	if (m_state != PLAYERSTATE_DEATH)
	{
		m_nLife -= nLife;
	}

	// 体力がなくなったら
	if (m_nLife <= 0)
	{
		// 体力を0に
		m_nLife = 0;

		// 状態を死亡時へ
		m_state = PLAYERSTATE::PLAYERSTATE_NORMAL;
	}
}

// =====================================================================================================================================================================
//
// 回復処理
//
// =====================================================================================================================================================================
void CPlayer::PlayerRecovery(int nLife)
{
	m_nLife += nLife;

	// 上限
	if (m_nLife >= PLAYER_MAX_LIFE)
	{
		m_nLife = PLAYER_MAX_LIFE;
	}
}