//====================================================================
// プレイヤー処理 [player.cpp]: NORI
//====================================================================
#include "Player.h"
#include "inputKeyboard.h"
#include "model.h"
#include "game.h"
#include "fade.h"
#include "Xinput.h"
#include "handgun.h"
#include "heavymachinegun.h"
#include "gun.h"
#include "collision.h"

CPlayer::CPlayer(OBJ_TYPE type) :CCharacter(type)
{
	SetObjType(OBJTYPE_PLAYER);
	m_pCollision = NULL;
}

CPlayer::~CPlayer()
{
}
//====================================================================
//初期化
//====================================================================
HRESULT CPlayer::Init(void)
{
	//キャラの初期化
	CCharacter::Init();
	LoadOffset(CCharacter::CHARACTER_TYPE_PLAYER);
	SetCharacterType(CCharacter::CHARACTER_TYPE_PLAYER);
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	m_Attack = false;
	m_ShotRot = D3DXVECTOR3(0.0f, 0.5f, 0.0f);
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

	 // 銃の生成
	m_pGun = CGun::Create(CCharacter::GetMtxWorld());
	// 銃の弾の種類
	m_pGun->GetBulletType() = CGun::TYPE_PLAYER;

	// 当たり判定生成
	m_pCollision = CCollision::Create();
	m_pCollision->SetPos(&GetPosition());
	m_pCollision->SetSize2D(D3DXVECTOR3(50.0f, 100.0f, 0.0f));
	m_pCollision->SetMove(&GetMove());
	m_pCollision->SetType(CCollision::OBJTYPE_PLAYER);

	return S_OK;
}
//====================================================================
//終了
//====================================================================
void CPlayer::Uninit(void)
{
	CCharacter::Uninit();
}
//====================================================================
//更新
//====================================================================
void CPlayer::Update(void)
{
	float rot = 0.0f;
	static bool trigger = false;
	static bool trigger2 = false;
	CKeyboard *key;
	key = CManager::GetInputKeyboard();
	Oldstate = state.Gamepad.wButtons;

	//ゲームパッド処理
	// Simply get the state of the controller from XInput.
	DWORD dwResult = XInputGetState(0, &state);
	if (dwResult == ERROR_SUCCESS)
	{
		// Controller is connected
		CDebugProc::Print("controller接続\n");
	}
	else
	{
		// Controller is not connected
		CDebugProc::Print("controller切断\n");
	}
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A && m_Attack == false)
	{
		// A ボタンが押された
	}
	if (state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD &&state.Gamepad.wButtons & XINPUT_GAMEPAD_X)
	{
		// 左トリガーが押された
		//vibration.wLeftMotorSpeed =  65535; // use any value between 0-65535 here
		//vibration.wRightMotorSpeed = 65535; // use any value between 0-65535 here
	}
	else
	{
		vibration.wLeftMotorSpeed = 0;
		vibration.wRightMotorSpeed = 0;
	}
	//デットゾーンの処理
	if ((state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		state.Gamepad.sThumbLX = 0;
		state.Gamepad.sThumbLY = 0;
	}
	D3DXVECTOR3 speed = D3DXVECTOR3(state.Gamepad.sThumbLX / 32767.0f, 0.0f, state.Gamepad.sThumbLY / 32767.0f);

	float fDistance = D3DXVec2Length(&D3DXVECTOR2(speed.x, speed.z));
	if (fabsf(fDistance) > 0.2f && m_Attack == false)
	{
		//m_MotionType = PLAYER_MOTION_WALK;
		//角度の計算
		GetMove().x += sinf(m_Angle) * 1;
		GetMove().z += cosf(m_Angle) * 1;
	}
	//Dest.y = atan2f(-m_move.x, -m_move.z);

	//キーボード処理

		// 銃を撃つ
	if (key->GetKeyboardTrigger(DIK_P))
	{
		// 銃発射処理
		m_pGun->Shot(m_ShotRot);
	}
	if (key->GetKeyboardTrigger(DIK_O))
	{
		// ヘビーマシンガンの弾の生成
		CHeavyMachinegun::Create(CPlayer::GetRot());
	}

	// Aの処理
	if (key->GetKeyboardPress(DIK_A))
	{
		CPlayer::Move(0.5f, 0.5f);
		m_ShotRot.x = 0.0f;
		m_ShotRot.y = 0.5f * D3DX_PI;
	}
	// Dの処理
	else if (key->GetKeyboardPress(DIK_D))
	{
		CPlayer::Move(-0.5f, -0.5f);
		m_ShotRot.x = 0.0f;
		m_ShotRot.y = -0.5f * D3DX_PI;
	}

	else if (key->GetKeyboardPress(DIK_W))
	{
		SetCharacterDirection(CHARACTER_UP);
		m_ShotRot.y = 0.0f;
		m_ShotRot.x = 0.5f * D3DX_PI;
	}
	//ジャンプしたときの下向発射
	if (key->GetKeyboardPress(DIK_S) && GetJump() == false)
	{
		SetCharacterDirection(CHARACTER_DOWN);
		m_ShotRot.y = 0.0f;
		m_ShotRot.x = -0.5f * D3DX_PI;
	}
	if (GetCharacterDirection() == CHARACTER_DOWN && GetJump() == true  )
	{
		m_ShotRot.x = GetRot().x;
		m_ShotRot.y = GetRot().y;
	}

	//デバッグモードの切り替え
	if (key->GetKeyboardTrigger(DIK_F2))
	{
		trigger ^= 1;
	}
	if (trigger == true)
	{
		m_DebugState = DEBUG_CREATE_MAP;
		SetGravity(false);
	}
	else
	{
		m_DebugState = DEBUG_NORMAL;
		SetGravity(true);
	}
	if (m_DebugState != DEBUG_NORMAL)
	{
	}
	//ジャンプ
	if (key->GetKeyboardTrigger(DIK_SPACE) && GetJump() == true && m_DebugState == DEBUG_NORMAL)
	{
		GetMove().y += 27;
	}

	else if (key->GetKeyboardPress(DIK_SPACE) && m_DebugState != DEBUG_NORMAL)
	{
		GetMove().y += 2;
	}

	if (key->GetKeyboardPress(DIK_LCONTROL))
	{
		GetRot().x -= 0.2f;
	}
	if (key->GetKeyboardTrigger(DIK_1))
	{
		SetMotion(CCharacter::CHARACTER_MOTION_STATE_NONE);
	}
	if (key->GetKeyboardTrigger(DIK_2))
	{
		SetMotion(CCharacter::PLAYER_MOTION_WALK);
	}

	// 当たり判定
	if (m_pCollision != NULL)
	{
		// 座標の更新 posとposold
		m_pCollision->SetPos(&GetPosition());

		if (m_pCollision->GetObjtype() == CCollision::OBJTYPE_PLAYER)
		{
			// 当たり判定 相手がエネミーだったら
			if (m_pCollision->Collision2D(CCollision::OBJTYPE_ENEMY))
			{
				CDebugProc::Print("\n時機が敵に当たったよ！\n");
			}

			else
			{
				CDebugProc::Print("\n時機が敵に当たってないよ！\n");
			}
		}
	}

	XInputSetState(0, &vibration);
	CCharacter::Update();
}
//====================================================================
//描画
//====================================================================
void CPlayer::Draw(void)
{
	CCharacter::Draw();
}
//====================================================================
//モデルのクリエイト
//====================================================================
CPlayer *CPlayer::Create(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	CPlayer*pPlayer;
	pPlayer = new CPlayer(OBJTYPE_PLAYER);
	pPlayer->Init();
	return pPlayer;
}
void CPlayer::DefaultMotion(void)
{
	SetMotion(CCharacter::PLAYER_MOTION_NORMAL);
}
//====================================================================
//デバッグステータスの取得
//====================================================================
CPlayer::DEBUG_STATE CPlayer::GetDebugState(void)
{
	return m_DebugState;
}
//====================================================================
//移動
//====================================================================
void CPlayer::Move(float move, float fdest)
{
	GetMove().x += sinf(move * -D3DX_PI) * 1.0f;
	GetMove().z += cosf(move * -D3DX_PI) * 1.0f;
	GetRotDest().y = fdest *  D3DX_PI;
}
