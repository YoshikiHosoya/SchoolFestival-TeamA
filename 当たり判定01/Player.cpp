//=============================================================================
// プレイヤー処理 [player.cpp]
//=============================================================================
#include "Player.h"
#include "inputKeyboard.h"
#include "model.h"
#include "game.h"
#include "fade.h"
#include "createmap.h"
#include "Xinput.h"
CPlayer::CPlayer(OBJ_TYPE type) :CScene(type)
{
	SetObjType(OBJTYPE_PLAYER);
}

CPlayer::~CPlayer()
{
}
//====================================================================
//初期化
//====================================================================
HRESULT CPlayer::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Life = 50;
	m_nCnt = 0;
	m_WeponType = 10;
	m_Attack = false;
	m_state = PLAYER_STATE_NORMAL;
	//モデルの設定--------------------■■■
	m_Model[0] = CModel::Create(CModel::PLAYER_MODEL,CModel::MODEL_PLAYER_BODY);		//体 0
	m_Model[0]->SetParent(NULL);														//(親)無し
	m_Model[0]->SetPosition(D3DXVECTOR3(0, 27, 0));
	m_Model[0]->SetSize(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	m_Model[1] = CModel::Create(CModel::PLAYER_MODEL, CModel::MODEL_PLAYER_HEAD);		//頭 1
	m_Model[1]->SetParent(m_Model[0]);													//(親)体
	m_Model[1]->SetPosition(D3DXVECTOR3(0, 10, 0));
	m_Model[1]->SetSize(D3DXVECTOR3(1.0f,1.0f,1.0f));

	m_Model[2] = CModel::Create(CModel::PLAYER_MODEL, CModel::MODEL_PLAYER_LARM);		//左腕 2
	m_Model[2]->SetParent(m_Model[0]);													//(親)体
	m_Model[2]->SetPosition(D3DXVECTOR3(5, 5, 0));
	m_Model[2]->SetSize(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	
	m_Model[3] = CModel::Create(CModel::PLAYER_MODEL, CModel::MODEL_PLAYER_RARM);		//右腕 3
	m_Model[3]->SetParent(m_Model[0]);													//(親)体
	m_Model[3]->SetPosition(D3DXVECTOR3(-5, 5, 0));
	m_Model[3]->SetSize(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	
	m_Model[4] = CModel::Create(CModel::PLAYER_MODEL, CModel::MODEL_PLAYER_LHAND);		//左手 4
	m_Model[4]->SetParent(m_Model[2]);													//(親)左腕
	m_Model[4]->SetPosition(D3DXVECTOR3(3, -5, 0));
	m_Model[4]->SetSize(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	
	m_Model[5] = CModel::Create(CModel::PLAYER_MODEL, CModel::MODEL_PLAYER_RHAND);		//右手 5
	m_Model[5]->SetParent(m_Model[3]);													//(親)右腕
	m_Model[5]->SetPosition(D3DXVECTOR3(-3, -5, 0));
	m_Model[5]->SetSize(D3DXVECTOR3(1.0f, 1.0f, 1.0f));


	m_Model[6] = CModel::Create(CModel::PLAYER_MODEL, CModel::MODEL_PLAYER_LFOOT);		//左脚　6
	m_Model[6]->SetParent(m_Model[0]);													//(親)体
	m_Model[6]->SetPosition(D3DXVECTOR3(3, -6, 0));
	m_Model[6]->SetSize(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	m_Model[7] = CModel::Create(CModel::PLAYER_MODEL, CModel::MODEL_PLAYER_RFOOT);		//右脚　7
	m_Model[7]->SetParent(m_Model[0]);													//(親)体
	m_Model[7]->SetPosition(D3DXVECTOR3(-3, -6, 0));
	m_Model[7]->SetSize(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	m_Model[8] = CModel::Create(CModel::PLAYER_MODEL, CModel::MODEL_PLAYER_LLEG);		//左足　8
	m_Model[8]->SetParent(m_Model[6]);													//(親)左脚
	m_Model[8]->SetPosition(D3DXVECTOR3(0, -9, -1));
	m_Model[8]->SetSize(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	m_Model[9] = CModel::Create(CModel::PLAYER_MODEL, CModel::MODEL_PLAYER_RLEG);		//右足　9
	m_Model[9]->SetParent(m_Model[7]);													//(親)右脚
	m_Model[9]->SetPosition(D3DXVECTOR3(0, -9, -1));
	m_Model[9]->SetSize(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	m_Model[10] = CModel::Create(CModel::PLAYER_MODEL, CModel::MODEL_PLAYER_FIRESWORD);	//武器　10
	m_Model[10]->SetParent(m_Model[5]);													//(親)右手
	m_Model[10]->SetPosition(D3DXVECTOR3(0, -5, 0));
	m_Model[10]->SetSize(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	CPlayer::LoadMotion();
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

	return S_OK;
}
//====================================================================
//終了
//====================================================================
void CPlayer::Uninit(void)
{
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
//	CParticle *pParticle;
	key = CManager::GetInputKeyboard();
	m_MotionOld = m_MotionType;
	m_posold = m_pos;
	m_nCnt++;
	Oldstate = state.Gamepad.wButtons;

	//ゲームパッド処理========================================================■■■
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
			m_MotionType = PLAYER_MOTION_WALK;
			//角度の計算
			m_move.x += sinf(m_Angle) * 1;
			m_move.z += cosf(m_Angle) * 1;
		}
	Dest.y = atan2f(-m_move.x, -m_move.z);

	//キーボード処理========================================================■■■

	// Aとの組み合わせ--------------------------------------■■■
	if (key->GetKeyboardPress(DIK_A))
	{
		if (key->GetKeyboardPress(DIK_S))
		{
			CPlayer::Move(0.75f, 0.25f);
		}
		else if (key->GetKeyboardPress(DIK_W))
		{
			CPlayer::Move(0.25f, 0.75f);
		}
		else
		{
			CPlayer::Move(0.5f, 0.5f);
		}
	}
	// Dとの組み合わせ--------------------------------------■■■
	else if (key->GetKeyboardPress(DIK_D))
	{
		if (key->GetKeyboardPress(DIK_W))
		{
			CPlayer::Move(-0.25f, -0.75f);
		}
		else if (key->GetKeyboardPress(DIK_S))
		{
			CPlayer::Move(-0.75f, -0.25f);
		}
		else
		{
			CPlayer::Move(-0.5f, -0.5f);
		}
	}
	// Wとの組み合わせ--------------------------------------■■■
	else if (key->GetKeyboardPress(DIK_W))
	{
		CPlayer::Move(0.0f, 1.0f);
	}
	// Sとの組み合わせ--------------------------------------■■■
	else if (key->GetKeyboardPress(DIK_S))
	{
		CPlayer::Move(1.0f, 0.0f);
	}
	//デバッグモードの切り替え------------------------------■■■
	if (key->GetKeyboardTrigger(DIK_F2))
	{
		trigger ^= 1;
	}
	if (trigger == true)
	{
		if (key->GetKeyboardTrigger(DIK_F3))
		{
			trigger2 ^= 1;
		}
		if (trigger2 == true)
		{
		m_DebugState = DEBUG_CREATE_ENEMY;
		}
		else
		{
		m_DebugState = DEBUG_CREATE_MAP;
		}
	}
	else
	{
		m_DebugState = DEBUG_NORMAL;
	}
	////慣性の抵抗--------------------------------------------■■■
	m_move.x += (0 - m_move.x)* 0.2f;
	m_move.z += (0 - m_move.z)* 0.2f;
	m_move.y += (0 - m_move.y)* 0.2f;
	m_pos += m_move;
	if (m_DebugState != DEBUG_NORMAL)
	{
	}
	if (key->GetKeyboardPress(DIK_SPACE))
	{
		m_move.y += 5;
	}
	if (key->GetKeyboardPress(DIK_LCONTROL))
	{
		m_pos.y -= 5;
	}

	//目標点と現在の差分（回転）
	float diffRot = Dest.y - m_rot.y;
	//3.14の超過分の初期化（回転）
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}
	if (diffRot > D3DX_PI)
	{
		diffRot -= D3DX_PI * 2;
	}
	else if (diffRot < -D3DX_PI)
	{
		diffRot += D3DX_PI * 2;
	}
	//求めた差分だけ追従する計算
	m_rot.y += diffRot * 0.1f;
	if (m_DebugState == DEBUG_NORMAL)
	{
		CDebugProc::Print("モーションキー：%d\nモーションフレーム：%d\n", m_CntKeySet, m_Fram);
		if (m_pos.y >0)
		{
			m_move.y -= 2.5f;
		}
	}
	else
	{
	}
	switch (m_state)
	{
	case PLAYER_STATE_NORMAL:
		break;
	case PLAYER_STATE_DAMAGE:
		m_nStateCnt++;
		if (m_nStateCnt % 60 == 0)
		{
			m_state = PLAYER_STATE_NORMAL;
		}

		break;
	case PLAYER_STATE_INVINCIBLE:
		m_nStateCnt++;
		if (m_nStateCnt % 30 == 0)
		{
			m_state = PLAYER_STATE_NORMAL;
		}
		break;
	}
	//死んだとき
	if (m_Life <= 0)
	{
		CFADE::SetFade(CManager::MODE_RESULT);
		Rerease();
	}
	CPlayer::Moation();
	XInputSetState(0, &vibration);
	CollisionModel();
}
//====================================================================
//描画
//====================================================================
void CPlayer::Drow(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y,
		m_rot.x,
		m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxRot);

	pDevice->SetTexture(0, m_pTexture);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x,
		m_pos.y,
		m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxTrans);

	//モデルの描画
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		//ダメージを受けてチカチカする処理
		if (m_state != PLAYER_STATE_DAMAGE)
		{
			m_Model[nCnt]->Drow(m_mtxWorld);
			if (nCnt == 10)
			{
				m_Model[nCnt]->Drow(m_mtxWorld);
			}
		}
		else if (m_state == PLAYER_STATE_DAMAGE)
		{
			if (m_nStateCnt % 2 == 0)
			{
				m_Model[nCnt]->Drow(m_mtxWorld);
			}
			else
			{

			}
		}
	}
}
//====================================================================
//モデルのクリエイト
//====================================================================
CPlayer *CPlayer::Create(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	CPlayer*pSceneX;
	pSceneX = new CPlayer(OBJTYPE_PLAYER);
	pSceneX->Init();
	return pSceneX;
}
//====================================================================
//モデルのムーヴ
//====================================================================
void CPlayer::Move(float move, float fdest)
{
	m_move.x += sinf(move * -D3DX_PI) * 1.0f;
	m_move.z += cosf(move * -D3DX_PI) * 1.0f;
	Dest.y = fdest *  D3DX_PI;
	m_MotionType = PLAYER_MOTION_WALK;
}

void CPlayer::LoadMotion(void)
{
	//ファイルポイント
	FILE *pFile;
	int nCntMotion = 0;		//モーションの数
	int nCntModel = 0;		//モデルのカウント
	int nCntKeySet = 0;		//フーレームの分割数
	int nCntKey = 0;		//パーツの番号
	char cReadText[128];	//文字として読み取り用
	char cHeadText[128];	//比較する用
	char cDie[128];			//不要な文字

							//ファイルを開く
	pFile = fopen("data/Load/PlayerMotion.txt", "r");

	//あいたら
	if (pFile != NULL)
	{
		//スクリプトが来るまでループ
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile);	//一文を読み込む
			sscanf(cReadText, "%s", &cHeadText);		//比較用テキストに文字を代入
		}
		//スクリプトだったら
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			//エンドスクリプトが来るまでループ
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s", &cHeadText);
				//モーションセットが来たら
				if (strcmp(cHeadText, "MOTIONSET") == 0)
				{
					//フレーム分割数の初期化
					nCntKeySet = 0;
					//エンドモーションセットが来るまでループ
					while (strcmp(cHeadText, "END_MOTIONSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile);//一文を抜き取る
						sscanf(cReadText, "%s", &cHeadText);
						//ループするかどうかの情報読み込み
						if (strcmp(cHeadText, "LOOP") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_PlayerMotion[nCntMotion].nLoop);
						}
						else if (strcmp(cHeadText, "NUM_KEY") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_PlayerMotion[nCntMotion].nNumKey);
						}
						else if (strcmp(cHeadText, "KEYSET") == 0)
						{
							nCntKey = 0;//キー情報初期化
							while (strcmp(cHeadText, "END_KEYSET") != 0)
							{
								fgets(cReadText, sizeof(cReadText), pFile);
								sscanf(cReadText, "%s", &cHeadText);

								if (strcmp(cHeadText, "FRAME") == 0)
								{
									sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_PlayerMotion[nCntMotion].key_info[nCntKeySet].nFram);
								}
								else if (strcmp(cHeadText, "KEY") == 0)
								{
									while (strcmp(cHeadText, "END_KEY") != 0)
									{
										fgets(cReadText, sizeof(cReadText), pFile);
										sscanf(cReadText, "%s", &cHeadText);
										if (strcmp(cHeadText, "POS") == 0)
										{
											//sscanf(cReadText, "%s %s %f %f %f",
											//	&cDie, &cDie,
											//	&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].pos.x,
											//	&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].pos.y,
											//	&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].pos.z);

											//m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].pos += m_Model[nCntKey]->GetPosition();
										}
										else if (strcmp(cHeadText, "ROT") == 0)
										{
											sscanf(cReadText, "%s %s %f %f %f",
												&cDie, &cDie,
												&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].rot.x,
												&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].rot.y,
												&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].rot.z);
										}
									}
									nCntKey++;
								}
							}
							nCntKeySet++;
						}
					}
					nCntMotion++;
				}
			}
		}
		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		MessageBox(NULL, "モデルデータの読み込み失敗", "警告", MB_ICONWARNING);
	}
}

void CPlayer::Moation(void)
{
	CKeyboard *key;
	key = CManager::GetInputKeyboard();
	D3DXVECTOR3 Difrot;
	if (m_MotionType != m_MotionOld)
	{
		m_Fram = 0;
		m_CntKeySet = 0;
	}
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (m_Fram == 0)
		{
			if (m_PlayerMotion[m_MotionType].key_info[m_CntKeySet].nFram != 0)
			{
				//移動量ROTの計算-------------------------------------■■■■■
				Difrot = (m_PlayerMotion[m_MotionType].key_info[m_CntKeySet].key[nCnt].rot - m_Model[nCnt]->GetRot());
				
				if (Difrot.y > D3DX_PI)
				{
					Difrot.y -= D3DX_PI * 2;
				}
				else if (Difrot.y < -D3DX_PI)
				{
					Difrot.y += D3DX_PI * 2;
				}

				if (Difrot.x > D3DX_PI)
				{
					Difrot.x -= D3DX_PI * 2;
				}
				else if (Difrot.x < -D3DX_PI)
				{
					Difrot.x += D3DX_PI * 2;
				}

				rotBET[nCnt] = Difrot / (float)m_PlayerMotion[m_MotionType].key_info[m_CntKeySet].nFram;
				//----------------------------------------------------■■■■■
			}
			else
			{
				//m_Model[nCnt]->GetPosition() = m_PlayerMotion[m_MotionType].key_info[m_CntKeySet].key[nCnt].pos;
				//m_Model[nCnt]->GetRot()		 = m_PlayerMotion[m_MotionType].key_info[m_CntKeySet].key[nCnt].rot;
				//posBET[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				//rotBET[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}

		//フレーム移動--------------------------------------------■■■■■
		if (m_Fram <= m_PlayerMotion[m_MotionType].key_info[m_CntKeySet].nFram)
		{
		//	m_Model[nCnt]->SetPosition(m_Model[nCnt]->GetPosition() + posBET[nCnt]);
			m_Model[nCnt]->SetRot(m_Model[nCnt]->GetRot() + rotBET[nCnt]);
			if (m_Model[nCnt]->GetRot().y > D3DX_PI)
			{
				m_Model[nCnt]->SetRot(m_Model[nCnt]->GetRot() - D3DXVECTOR3(0.0f, D3DX_PI * 2.0f, 0.0f));
			}
			else if (m_Model[nCnt]->GetRot().y < -D3DX_PI)
			{
				m_Model[nCnt]->SetRot(m_Model[nCnt]->GetRot() + D3DXVECTOR3(0.0f, D3DX_PI * 2.0f, 0.0f));
			}
			if (m_Model[nCnt]->GetRot().x > D3DX_PI)
			{
				m_Model[nCnt]->SetRot(m_Model[nCnt]->GetRot() - D3DXVECTOR3(D3DX_PI * 2.0f, 0.0f, 0.0f));
			}
			else if (m_Model[nCnt]->GetRot().x < -D3DX_PI)
			{
				m_Model[nCnt]->SetRot(m_Model[nCnt]->GetRot() + D3DXVECTOR3(D3DX_PI * 2.0f,0.0f, 0.0f));
			}
		}
		//--------------------------------------------------------■■■■■
	}
	if (m_Fram == m_PlayerMotion[m_MotionType].key_info[m_CntKeySet].nFram)
	{
		m_CntKeySet++;
		m_Fram = 0;
		//キーセット数が規定値と同じになったら--------------------■■■■■
		if (m_CntKeySet == m_PlayerMotion[m_MotionType].nNumKey)
		{
			//ループしないとき------------------------------------■■■■■
			if (m_PlayerMotion[m_MotionType].nLoop == 0)
			{
				m_CntKeySet = 0;
				m_MotionType = 0;
				m_Fram = m_PlayerMotion[m_MotionType].key_info[m_CntKeySet].nFram;
				m_Attack = false;
			}
			//ループするとき--------------------------------------■■■■■
			else if (m_PlayerMotion[m_MotionType].nLoop == 1)
			{
				m_CntKeySet = 0;
				m_MotionType = 0;
			}
		}
	}

	//フレーム数が規定値と同じではないとき------------------------■■■■■
	else
	{
		m_Fram++;
	}

}


//位置のセット
void CPlayer::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//攻撃の当たり判定
//デバッグステータスの取得
CPlayer::DEBUG_STATE CPlayer::GetDebugState(void)
{
	return m_DebugState;
}
CPlayer::PLAYER_STATE CPlayer::GetPlayerState(void)
{
	return m_state;
}
D3DXVECTOR3 CPlayer::GetOffset(int nCnt)
{
	return m_aOffset[nCnt];
}
//武器の種類の取得
int CPlayer::GetWeponType(void)
{
	return m_WeponType;
}
//プレイヤーのダメージを食らったとき
void CPlayer::HitPlayer(int Damage)
{
	//CSound::PlaySound(CSound::SOUND_LABEL_SE_PLAYERHIT);
	m_state = PLAYER_STATE_DAMAGE;
	int Life = GetLife();
	Life -= Damage;
	SetLife(Life);
}
//体力の取得
int CPlayer::GetLife(void)
{
	return m_Life;
}
//====================================================================
//当たり判定
//====================================================================
void CPlayer::CollisionModel(void)
{
	CCreateMap *pCreateMap;
	pCreateMap = CManager::GetGame()->GetCreateMap();
	// 地形判定
	BOOL  bIsHit = false;
	float fLandDistance=0;
	DWORD dwHitIndex = -1;
	float fHitU=0;
	float fHitV=0;
	D3DXMATRIX invmat;		//	逆行列を格納する変数
	D3DXVECTOR3 m_posAfter;	//	逆行列で出した終点情報を格納する
	D3DXVECTOR3 m_posBefore;//	終点情報を格納する
	D3DXVECTOR3 direction;	//	変換後の位置、方向を格納する変数：
	std::vector<float> vDistance;//長さの配列保存
	float fData = 0.0f;
	for (int nCnt = 0; nCnt < pCreateMap->GetMaxModel(); nCnt++)
	{
		D3DXMatrixInverse(&invmat, NULL, pCreateMap->GetModel(nCnt)->GetMatrix());	//	逆行列の取得
		//	逆行列を使用し、レイ始点情報を変換　位置と向きで変換する関数が異なるので要注意
		D3DXVec3TransformCoord(&m_posBefore, &D3DXVECTOR3(m_pos.x, m_pos.y + RAY_FIRST_POINT, m_pos.z), &invmat);
		//	レイ終点情報を変換
		D3DXVec3TransformCoord(&m_posAfter, &D3DXVECTOR3(m_pos.x, m_pos .y, m_pos.z), &invmat);
		//	レイ方向情報を変換
		D3DXVec3Normalize(&direction, &(m_posAfter - m_posBefore));						
		//Rayを飛ばす
		D3DXIntersect(pCreateMap->GetMesh(nCnt), &m_posBefore, &direction, &bIsHit, &dwHitIndex, &fHitU, &fHitV, &fLandDistance, NULL, NULL);
		if (bIsHit == TRUE)
		{
			CDebugProc::Print("当たってるよ\n");
			vDistance.emplace_back(fLandDistance); //長さの保存追加
		}
		else
		{
			CDebugProc::Print("当たって無いよ\n");
		}
	}
	//Rayのヒットした物があったとき
	if (!vDistance.empty())
	{
		//最初の比較対象
		fData = vDistance[0];
		for (unsigned int nCnt = 0; vDistance.size() > nCnt; nCnt++)
		{
			if (vDistance[nCnt] < fData)
			{
				//比較対象が小さかったら代入
				fData = vDistance[nCnt];
			}
		}
		if (fData < MAX_RAY_LENGTH)//Rayの長さの指定条件
		{
			m_pos.y = m_pos.y - fData + MAX_RAY_LENGTH;
		}
	}
	CDebugProc::Print("Rayの長さ(%f)\n", fLandDistance);
	CDebugProc::Print("キャラの高さ(%f)\n", m_pos.y);
	CDebugProc::Print("Rayからキャラの位置を引いた値(%f)\n", m_pos.y-fLandDistance);
}
//体力の設定
void CPlayer::SetLife(int Life)
{
	m_Life = Life;
}
//位置の取得
D3DXVECTOR3 CPlayer::GetPosition(void)
{
	return m_pos;
}
D3DXVECTOR3 CPlayer::GetPositionOld(void)
{
	return m_posold;
}
D3DXVECTOR3 CPlayer::GetMove(void)
{
	return m_move;
}
