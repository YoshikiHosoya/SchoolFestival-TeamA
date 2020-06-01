//=============================================================================
// �v���C���[���� [player.cpp]
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
//������
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
	//���f���̐ݒ�--------------------������
	m_Model[0] = CModel::Create(CModel::PLAYER_MODEL,CModel::MODEL_PLAYER_BODY);		//�� 0
	m_Model[0]->SetParent(NULL);														//(�e)����
	m_Model[0]->SetPosition(D3DXVECTOR3(0, 27, 0));
	m_Model[0]->SetSize(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	m_Model[1] = CModel::Create(CModel::PLAYER_MODEL, CModel::MODEL_PLAYER_HEAD);		//�� 1
	m_Model[1]->SetParent(m_Model[0]);													//(�e)��
	m_Model[1]->SetPosition(D3DXVECTOR3(0, 10, 0));
	m_Model[1]->SetSize(D3DXVECTOR3(1.0f,1.0f,1.0f));

	m_Model[2] = CModel::Create(CModel::PLAYER_MODEL, CModel::MODEL_PLAYER_LARM);		//���r 2
	m_Model[2]->SetParent(m_Model[0]);													//(�e)��
	m_Model[2]->SetPosition(D3DXVECTOR3(5, 5, 0));
	m_Model[2]->SetSize(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	
	m_Model[3] = CModel::Create(CModel::PLAYER_MODEL, CModel::MODEL_PLAYER_RARM);		//�E�r 3
	m_Model[3]->SetParent(m_Model[0]);													//(�e)��
	m_Model[3]->SetPosition(D3DXVECTOR3(-5, 5, 0));
	m_Model[3]->SetSize(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	
	m_Model[4] = CModel::Create(CModel::PLAYER_MODEL, CModel::MODEL_PLAYER_LHAND);		//���� 4
	m_Model[4]->SetParent(m_Model[2]);													//(�e)���r
	m_Model[4]->SetPosition(D3DXVECTOR3(3, -5, 0));
	m_Model[4]->SetSize(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	
	m_Model[5] = CModel::Create(CModel::PLAYER_MODEL, CModel::MODEL_PLAYER_RHAND);		//�E�� 5
	m_Model[5]->SetParent(m_Model[3]);													//(�e)�E�r
	m_Model[5]->SetPosition(D3DXVECTOR3(-3, -5, 0));
	m_Model[5]->SetSize(D3DXVECTOR3(1.0f, 1.0f, 1.0f));


	m_Model[6] = CModel::Create(CModel::PLAYER_MODEL, CModel::MODEL_PLAYER_LFOOT);		//���r�@6
	m_Model[6]->SetParent(m_Model[0]);													//(�e)��
	m_Model[6]->SetPosition(D3DXVECTOR3(3, -6, 0));
	m_Model[6]->SetSize(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	m_Model[7] = CModel::Create(CModel::PLAYER_MODEL, CModel::MODEL_PLAYER_RFOOT);		//�E�r�@7
	m_Model[7]->SetParent(m_Model[0]);													//(�e)��
	m_Model[7]->SetPosition(D3DXVECTOR3(-3, -6, 0));
	m_Model[7]->SetSize(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	m_Model[8] = CModel::Create(CModel::PLAYER_MODEL, CModel::MODEL_PLAYER_LLEG);		//�����@8
	m_Model[8]->SetParent(m_Model[6]);													//(�e)���r
	m_Model[8]->SetPosition(D3DXVECTOR3(0, -9, -1));
	m_Model[8]->SetSize(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	m_Model[9] = CModel::Create(CModel::PLAYER_MODEL, CModel::MODEL_PLAYER_RLEG);		//�E���@9
	m_Model[9]->SetParent(m_Model[7]);													//(�e)�E�r
	m_Model[9]->SetPosition(D3DXVECTOR3(0, -9, -1));
	m_Model[9]->SetSize(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	m_Model[10] = CModel::Create(CModel::PLAYER_MODEL, CModel::MODEL_PLAYER_FIRESWORD);	//����@10
	m_Model[10]->SetParent(m_Model[5]);													//(�e)�E��
	m_Model[10]->SetPosition(D3DXVECTOR3(0, -5, 0));
	m_Model[10]->SetSize(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	CPlayer::LoadMotion();
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

	return S_OK;
}
//====================================================================
//�I��
//====================================================================
void CPlayer::Uninit(void)
{
}
//====================================================================
//�X�V
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

	//�Q�[���p�b�h����========================================================������
	// Simply get the state of the controller from XInput.
	DWORD dwResult = XInputGetState(0, &state);
	if (dwResult == ERROR_SUCCESS)
	{
		// Controller is connected
		CDebugProc::Print("controller�ڑ�\n");
	}
	else
	{
		// Controller is not connected
		CDebugProc::Print("controller�ؒf\n");
	}
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A && m_Attack == false)
	{
		// A �{�^���������ꂽ
	}
	if (state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD &&state.Gamepad.wButtons & XINPUT_GAMEPAD_X)
	{
		// ���g���K�[�������ꂽ
		//vibration.wLeftMotorSpeed =  65535; // use any value between 0-65535 here
		//vibration.wRightMotorSpeed = 65535; // use any value between 0-65535 here
	}
	else
	{
		vibration.wLeftMotorSpeed = 0;
		vibration.wRightMotorSpeed = 0;
	}
	 //�f�b�g�]�[���̏���
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
			//�p�x�̌v�Z
			m_move.x += sinf(m_Angle) * 1;
			m_move.z += cosf(m_Angle) * 1;
		}
	Dest.y = atan2f(-m_move.x, -m_move.z);

	//�L�[�{�[�h����========================================================������

	// A�Ƃ̑g�ݍ��킹--------------------------------------������
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
	// D�Ƃ̑g�ݍ��킹--------------------------------------������
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
	// W�Ƃ̑g�ݍ��킹--------------------------------------������
	else if (key->GetKeyboardPress(DIK_W))
	{
		CPlayer::Move(0.0f, 1.0f);
	}
	// S�Ƃ̑g�ݍ��킹--------------------------------------������
	else if (key->GetKeyboardPress(DIK_S))
	{
		CPlayer::Move(1.0f, 0.0f);
	}
	//�f�o�b�O���[�h�̐؂�ւ�------------------------------������
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
	////�����̒�R--------------------------------------------������
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

	//�ڕW�_�ƌ��݂̍����i��]�j
	float diffRot = Dest.y - m_rot.y;
	//3.14�̒��ߕ��̏������i��]�j
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
	//���߂����������Ǐ]����v�Z
	m_rot.y += diffRot * 0.1f;
	if (m_DebugState == DEBUG_NORMAL)
	{
		CDebugProc::Print("���[�V�����L�[�F%d\n���[�V�����t���[���F%d\n", m_CntKeySet, m_Fram);
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
	//���񂾂Ƃ�
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
//�`��
//====================================================================
void CPlayer::Drow(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y,
		m_rot.x,
		m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxRot);

	pDevice->SetTexture(0, m_pTexture);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x,
		m_pos.y,
		m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxTrans);

	//���f���̕`��
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		//�_���[�W���󂯂ă`�J�`�J���鏈��
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
//���f���̃N���G�C�g
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
//���f���̃��[��
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
	//�t�@�C���|�C���g
	FILE *pFile;
	int nCntMotion = 0;		//���[�V�����̐�
	int nCntModel = 0;		//���f���̃J�E���g
	int nCntKeySet = 0;		//�t�[���[���̕�����
	int nCntKey = 0;		//�p�[�c�̔ԍ�
	char cReadText[128];	//�����Ƃ��ēǂݎ��p
	char cHeadText[128];	//��r����p
	char cDie[128];			//�s�v�ȕ���

							//�t�@�C�����J��
	pFile = fopen("data/Load/PlayerMotion.txt", "r");

	//��������
	if (pFile != NULL)
	{
		//�X�N���v�g������܂Ń��[�v
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile);	//�ꕶ��ǂݍ���
			sscanf(cReadText, "%s", &cHeadText);		//��r�p�e�L�X�g�ɕ�������
		}
		//�X�N���v�g��������
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			//�G���h�X�N���v�g������܂Ń��[�v
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s", &cHeadText);
				//���[�V�����Z�b�g��������
				if (strcmp(cHeadText, "MOTIONSET") == 0)
				{
					//�t���[���������̏�����
					nCntKeySet = 0;
					//�G���h���[�V�����Z�b�g������܂Ń��[�v
					while (strcmp(cHeadText, "END_MOTIONSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile);//�ꕶ�𔲂����
						sscanf(cReadText, "%s", &cHeadText);
						//���[�v���邩�ǂ����̏��ǂݍ���
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
							nCntKey = 0;//�L�[��񏉊���
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
		//�t�@�C�������
		fclose(pFile);
	}
	else
	{
		MessageBox(NULL, "���f���f�[�^�̓ǂݍ��ݎ��s", "�x��", MB_ICONWARNING);
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
				//�ړ���ROT�̌v�Z-------------------------------------����������
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
				//----------------------------------------------------����������
			}
			else
			{
				//m_Model[nCnt]->GetPosition() = m_PlayerMotion[m_MotionType].key_info[m_CntKeySet].key[nCnt].pos;
				//m_Model[nCnt]->GetRot()		 = m_PlayerMotion[m_MotionType].key_info[m_CntKeySet].key[nCnt].rot;
				//posBET[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				//rotBET[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}

		//�t���[���ړ�--------------------------------------------����������
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
		//--------------------------------------------------------����������
	}
	if (m_Fram == m_PlayerMotion[m_MotionType].key_info[m_CntKeySet].nFram)
	{
		m_CntKeySet++;
		m_Fram = 0;
		//�L�[�Z�b�g�����K��l�Ɠ����ɂȂ�����--------------------����������
		if (m_CntKeySet == m_PlayerMotion[m_MotionType].nNumKey)
		{
			//���[�v���Ȃ��Ƃ�------------------------------------����������
			if (m_PlayerMotion[m_MotionType].nLoop == 0)
			{
				m_CntKeySet = 0;
				m_MotionType = 0;
				m_Fram = m_PlayerMotion[m_MotionType].key_info[m_CntKeySet].nFram;
				m_Attack = false;
			}
			//���[�v����Ƃ�--------------------------------------����������
			else if (m_PlayerMotion[m_MotionType].nLoop == 1)
			{
				m_CntKeySet = 0;
				m_MotionType = 0;
			}
		}
	}

	//�t���[�������K��l�Ɠ����ł͂Ȃ��Ƃ�------------------------����������
	else
	{
		m_Fram++;
	}

}


//�ʒu�̃Z�b�g
void CPlayer::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//�U���̓����蔻��
//�f�o�b�O�X�e�[�^�X�̎擾
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
//����̎�ނ̎擾
int CPlayer::GetWeponType(void)
{
	return m_WeponType;
}
//�v���C���[�̃_���[�W��H������Ƃ�
void CPlayer::HitPlayer(int Damage)
{
	//CSound::PlaySound(CSound::SOUND_LABEL_SE_PLAYERHIT);
	m_state = PLAYER_STATE_DAMAGE;
	int Life = GetLife();
	Life -= Damage;
	SetLife(Life);
}
//�̗͂̎擾
int CPlayer::GetLife(void)
{
	return m_Life;
}
//====================================================================
//�����蔻��
//====================================================================
void CPlayer::CollisionModel(void)
{
	CCreateMap *pCreateMap;
	pCreateMap = CManager::GetGame()->GetCreateMap();
	// �n�`����
	BOOL  bIsHit = false;
	float fLandDistance=0;
	DWORD dwHitIndex = -1;
	float fHitU=0;
	float fHitV=0;
	D3DXMATRIX invmat;		//	�t�s����i�[����ϐ�
	D3DXVECTOR3 m_posAfter;	//	�t�s��ŏo�����I�_�����i�[����
	D3DXVECTOR3 m_posBefore;//	�I�_�����i�[����
	D3DXVECTOR3 direction;	//	�ϊ���̈ʒu�A�������i�[����ϐ��F
	std::vector<float> vDistance;//�����̔z��ۑ�
	float fData = 0.0f;
	for (int nCnt = 0; nCnt < pCreateMap->GetMaxModel(); nCnt++)
	{
		D3DXMatrixInverse(&invmat, NULL, pCreateMap->GetModel(nCnt)->GetMatrix());	//	�t�s��̎擾
		//	�t�s����g�p���A���C�n�_����ϊ��@�ʒu�ƌ����ŕϊ�����֐����قȂ�̂ŗv����
		D3DXVec3TransformCoord(&m_posBefore, &D3DXVECTOR3(m_pos.x, m_pos.y + RAY_FIRST_POINT, m_pos.z), &invmat);
		//	���C�I�_����ϊ�
		D3DXVec3TransformCoord(&m_posAfter, &D3DXVECTOR3(m_pos.x, m_pos .y, m_pos.z), &invmat);
		//	���C��������ϊ�
		D3DXVec3Normalize(&direction, &(m_posAfter - m_posBefore));						
		//Ray���΂�
		D3DXIntersect(pCreateMap->GetMesh(nCnt), &m_posBefore, &direction, &bIsHit, &dwHitIndex, &fHitU, &fHitV, &fLandDistance, NULL, NULL);
		if (bIsHit == TRUE)
		{
			CDebugProc::Print("�������Ă��\n");
			vDistance.emplace_back(fLandDistance); //�����̕ۑ��ǉ�
		}
		else
		{
			CDebugProc::Print("�������Ė�����\n");
		}
	}
	//Ray�̃q�b�g���������������Ƃ�
	if (!vDistance.empty())
	{
		//�ŏ��̔�r�Ώ�
		fData = vDistance[0];
		for (unsigned int nCnt = 0; vDistance.size() > nCnt; nCnt++)
		{
			if (vDistance[nCnt] < fData)
			{
				//��r�Ώۂ���������������
				fData = vDistance[nCnt];
			}
		}
		if (fData < MAX_RAY_LENGTH)//Ray�̒����̎w�����
		{
			m_pos.y = m_pos.y - fData + MAX_RAY_LENGTH;
		}
	}
	CDebugProc::Print("Ray�̒���(%f)\n", fLandDistance);
	CDebugProc::Print("�L�����̍���(%f)\n", m_pos.y);
	CDebugProc::Print("Ray����L�����̈ʒu���������l(%f)\n", m_pos.y-fLandDistance);
}
//�̗͂̐ݒ�
void CPlayer::SetLife(int Life)
{
	m_Life = Life;
}
//�ʒu�̎擾
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
