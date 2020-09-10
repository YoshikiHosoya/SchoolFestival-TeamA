//=============================================================================
// �L�����N�^�[���f���������� [Character.cpp] : NORI
//=============================================================================
#include "ModelSet.h"
#include "inputKeyboard.h"
#include "model.h"
#include "game.h"
#include "fade.h"
#include "map.h"
#include "Xinput.h"
#include "collision.h"
#include "hosso\/Debug_ModelViewer.h"
#include "particle.h"
#include "sound.h"

//=============================================================================
// �ÓI�����o�ϐ�������
//=============================================================================
std::vector<CModelSet::MOTION*> CModelSet::m_CharacterMotion = {};

//�I�t�Z�b�g�̓ǂݍ��݃t�@�C��
char *CModelSet::m_LoadOffsetFileName[CHARACTER_TYPE_MAX] =
{
	{ "data/Load/Player/PlayerOffset.txt" },
	{ "data/Load/Enemy/Enemy_Human_Offset.txt" },
	{ "data/Load/Enemy/Enemy_Helicopter_Offset.txt" },
	{ "data/Load/Enemy/Enemy_MeltyHoney_Offset.txt" },
	{ "data/Load/Enemy/Enemy_Zycocca_Offset.txt" },
	{ "data/Load/Prisoner/PrisonerOffset.txt" },
	{ "data/Load/Boss/BossOffset.txt" },
	{ "data/Load/DragonNosuke/Boss_OneOffset.txt" },
	{ "data/Load/PlayerTank/PlayerTankOffset.txt" },
	{ "data/Load/BattlePlane/BattlePlaneOffset.txt" },
	{ "data/Load/Helicopter/HelicopterOffset.txt" },
};
//���[�V�����̓ǂݍ��݃t�@�C��
char *CModelSet::m_LoadMotionFileName[CHARACTER_MOTION_MAX] =
{
	{ "data/Load/Player/Motion/Neutral.txt" },
	{ "data/Load/Player/Motion/Walk.txt" },
	{ "data/Load/Player/Motion/Attack.txt" },
	{ "data/Load/Player/Motion/Grenade.txt" },
	{ "data/Load/Player/Motion/Jump.txt" },
	{ "data/Load/Player/Motion/JumpStop.txt" },
	{ "data/Load/Player/Motion/Shoot.txt" },
	{ "data/Load/Player/Motion/Squat.txt" },
	{ "data/Load/Player/Motion/SquatStop.txt" },
	{ "data/Load/Player/Motion/Dead.txt" },
	{ "data/Load/Enemy/Motion/EnemyNeutral.txt" },
	{ "data/Load/Enemy/Motion/EnemyWalk.txt" },
	{ "data/Load/Enemy/Motion/EnemySquatStop.txt" },
	{ "data/Load/Enemy/Motion/EnemyDead_1.txt" },
	{ "data/Load/Enemy/Motion/EnemyDead_2.txt" },
	{ "data/Load/Enemy/Motion/EnemyGrenade.txt" },
	{ "data/Load/Enemy/Motion/EnemyJumpAttack.txt" },
	{ "data/Load/Enemy/Motion/EnemyKnifeAttack.txt" },
	{ "data/Load/Boss/Motion/Neutral.txt" },
	{ "data/Load/Prisoner/Motion/PrisonerStay.txt" },
	{ "data/Load/Prisoner/Motion/PrisonerRelease.txt" },
	{ "data/Load/Prisoner/Motion/PrisonerRun.txt" },
	{ "data/Load/Prisoner/Motion/PrisonerSalute.txt" },
	{ "data/Load/Prisoner/Motion/PrisonerFall.txt" },
	{ "data/Load/Prisoner/Motion/PrisonerSkip.txt" },
};

//=============================================================================
// �}�N��
//=============================================================================
#define ADD_ROTATION_SPEED (0.15f)

//====================================================================
//�R���X�g���N�^
//====================================================================
CModelSet::CModelSet()
{
}
//====================================================================
//�f�X�g���N�^
//====================================================================
CModelSet::~CModelSet()
{
	//nullcheck
	if (!m_vModelList.empty())
	{
		//�p�[�c����
		for (size_t nCnt = 0; nCnt < m_vModelList.size(); nCnt++)
		{
			//�������J��
			delete m_vModelList[nCnt];
			m_vModelList[nCnt] = nullptr;
		}
		//�z�����ɂ���
		m_vModelList.clear();
	}
}
//====================================================================
//������
//====================================================================
HRESULT CModelSet::Init(void)
{
	m_HeightBet = 0.0f;											//
	m_state = CHARACTER_STATE_NORMAL;							// ���
	m_bMotion = true;											// ���[�V�������邩�ǂ���
	m_bFall = false;											//
	m_bDraw = true;												//�`�悷�邩�ǂ���
	//�}�g���b�N�X������
	D3DXMatrixIdentity(&m_mtxWorld);

	return S_OK;
}
//====================================================================
//�I��
//====================================================================
void CModelSet::Uninit(void)
{
}
//====================================================================
//�X�e�[�g�̃J�E���g�ݒ�
//====================================================================
void CModelSet::SetStateCount(int nCntState)
{
	m_nStateCnt = nCntState;
}
//====================================================================
//�}�g���b�N�X�̐ݒ�
//====================================================================
void CModelSet::SetMtxWorld(D3DXMATRIX mtxWorld)
{
	m_mtxWorld = mtxWorld;
}
//====================================================================
//���[�V�����̐ݒ�
//====================================================================
void CModelSet::SetMotion(CHARACTER_MOTION_STATE type)
{
	if (m_MotionType != type)
	{
		m_Fram = 0;
		m_CntKeySet = 0;
	}
	m_MotionType = type;
}
//====================================================================
//�L�����N�^�[�̏�Ԃ̎擾
//====================================================================
CModelSet::CHARACTER_STATE CModelSet::GetCharacterState(void)
{
	return m_state;
}
//====================================================================
//���[�V�������̎擾
//====================================================================
CModelSet::MOTION *CModelSet::GetCharacterMotion(CHARACTER_MOTION_STATE type)
{
	return m_CharacterMotion[type];
}
//====================================================================
//�I�t�Z�b�g�̃t�@�C���擾
//====================================================================
char * CModelSet::GetOffsetFileName(CHARACTER_TYPE type)
{
	return m_LoadOffsetFileName[type];
}
//====================================================================
//���[�V�����̃t�@�C���擾
//====================================================================
char * CModelSet::GetMotionFileName(CHARACTER_MOTION_STATE motionstate)
{
	return m_LoadMotionFileName[motionstate];
}
//====================================================================
//�F�ύX
//====================================================================
void CModelSet::ChangeColor(bool ColorChangeFlag, D3DXCOLOR AddColor)
{
	//���f���̐F�ύX
	for (unsigned int nCnt = 0; nCnt < m_vModelList.size(); nCnt++)
	{
		// ���Z����F�̐ݒ�
		m_vModelList[nCnt]->SetAddColor(AddColor);
		// �F�ύX�t���O�̐ݒ�
		m_vModelList[nCnt]->SetColorChangeFlag(ColorChangeFlag);
	}
}
//====================================================================
//���[�V�����̃��[�h
//====================================================================
void CModelSet::LoadMotion(void)
{
	//�t�@�C���|�C���g
	FILE *pFile;
	int nCntModel = 0;		//���f���̃J�E���g
	int nCntKeySet = 0;		//�t�[���[���̕�����
	int nCntKey = 0;
	char cReadText[128];	//�����Ƃ��ēǂݎ��p
	char cHeadText[128];	//��r����p
	char cDie[128];			//�s�v�ȕ���

	KEY *key;
	KEY_INFO *key_info;

	MOTION *pMotion;
	for (int nCnt = 0; nCnt < CHARACTER_MOTION_MAX; nCnt++)
	{
		pFile = fopen(m_LoadMotionFileName[nCnt], "r");//�t�@�C�����J��
													   //��������
		if (pFile != NULL)
		{
			pMotion = new MOTION;
			m_CharacterMotion.emplace_back(pMotion);
			//�X�N���v�g������܂Ń��[�v
			while (strcmp(cHeadText, "SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);	//�ꕶ��ǂݍ���
				sscanf(cReadText, "%s", &cHeadText);		//��r�p�e�L�X�g�ɕ�������
			}
			//�X�N���v�g��������
			if (strcmp(cHeadText, "SCRIPT") == 0)
			{
				//�t���[���������̏�����
				nCntKeySet = 0;
				//�G���h�X�N���v�g������܂Ń��[�v
				while (strcmp(cHeadText, "END_SCRIPT") != 0)
				{
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s", &cHeadText);

					//���[�v���邩�ǂ����̏��ǂݍ���
					if (strcmp(cHeadText, "LOOP") == 0)
					{
						sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_CharacterMotion[nCnt]->nLoop);
					}
					else if (strcmp(cHeadText, "NUM_KEY") == 0)
					{
						sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_CharacterMotion[nCnt]->nNumKey);
					}
					else if (strcmp(cHeadText, "KEYSET") == 0)
					{
						key_info = new KEY_INFO;
						m_CharacterMotion[nCnt]->key_info.emplace_back(key_info);
						nCntKey = 0;

						while (strcmp(cHeadText, "END_KEYSET") != 0)
						{
							fgets(cReadText, sizeof(cReadText), pFile);
							sscanf(cReadText, "%s", &cHeadText);

							if (strcmp(cHeadText, "FRAME") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_CharacterMotion[nCnt]->key_info[nCntKeySet]->nFram);
							}
							//����
							else if (strcmp(cHeadText, "HEIGHT") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDie, &cDie, &m_CharacterMotion[nCnt]->key_info[nCntKeySet]->fHeight);
							}
							//�L�[��������
							else if (strcmp(cHeadText, "KEY") == 0)
							{
								//�������m��
								key = new KEY;

								//�z��ɒǉ�
								m_CharacterMotion[nCnt]->key_info[nCntKeySet]->key.emplace_back(key);

								sscanf(cReadText, "%s %s %s %f %f %f", &cDie, &cDie, &cDie,
									&m_CharacterMotion[nCnt]->key_info[nCntKeySet]->key[nCntKey]->rot.x,
									&m_CharacterMotion[nCnt]->key_info[nCntKeySet]->key[nCntKey]->rot.y,
									&m_CharacterMotion[nCnt]->key_info[nCntKeySet]->key[nCntKey]->rot.z);

								//�L�[���Z
								nCntKey++;
							}
						}
						nCntKeySet++;
					}
				}

			}

			//debug
			std::cout << "Motion Load - " << nCnt << m_LoadMotionFileName[nCnt] << NEWLINE;

			//�t�@�C�������
			fclose(pFile);
		}
		else
		{
			//debug
			std::cout << "LOAD FAILED!!! MotionFile - " << nCnt << m_LoadMotionFileName[nCnt] << NEWLINE;

			//���s
			MessageBox(NULL, "���[�V�����ǂݍ��ݎ��s", m_LoadMotionFileName[nCnt], MB_OK | MB_ICONHAND);
		}
	}
}
//====================================================================
//���[�V����
//====================================================================
bool CModelSet::Motion(void)
{
	D3DXVECTOR3 Difrot;
	float Difpos;
	m_MotionOld = m_MotionType;

	if (m_MotionType != m_MotionOld)
	{
		m_Fram = 0;
		m_CntKeySet = 0;
	}
	if (m_MotionType != -1)
	{
		for (unsigned int nCnt = 0; nCnt < m_vModelList.size(); nCnt++)
		{
			if (m_Fram == 0)
			{
				if (m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->nFram != 0)
				{
					//�ړ���ROT�̌v�Z-------------------------------------����������
					Difrot = (m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->key[nCnt]->rot - m_vModelList[nCnt]->GetRot());
					Difpos = m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->fHeight - m_vModelList[0]->GetPosition().y;
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

					m_rotBET[nCnt] = Difrot / (float)m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->nFram;

					m_HeightBet = Difpos / (float)m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->nFram;
					//----------------------------------------------------����������
				}
				else
				{
					//m_vModelList[nCnt]->GetPosition() = m_CharacterMotion[m_MotionType].key_info[m_CntKeySet].key[nCnt].pos;
					//m_vModelList[nCnt]->GetRot()		 = m_CharacterMotion[m_MotionType].key_info[m_CntKeySet].key[nCnt].rot;
					//posBET[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					//rotBET[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
			}
			//�t���[���ړ�--------------------------------------------����������
			if (m_Fram <= m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->nFram)
			{
				//	m_vModelList[nCnt]->SetPosition(m_vModelList[nCnt]->GetPosition() + posBET[nCnt]);
				m_vModelList[nCnt]->SetRot(m_vModelList[nCnt]->GetRot() + m_rotBET[nCnt]);
				if (nCnt == 0)
				{
					m_vModelList[0]->GetPosition().y += m_HeightBet;
				}

				if (m_vModelList[nCnt]->GetRot().y > D3DX_PI)
				{
					m_vModelList[nCnt]->SetRot(m_vModelList[nCnt]->GetRot() - D3DXVECTOR3(0.0f, D3DX_PI * 2.0f, 0.0f));
				}
				else if (m_vModelList[nCnt]->GetRot().y < -D3DX_PI)
				{
					m_vModelList[nCnt]->SetRot(m_vModelList[nCnt]->GetRot() + D3DXVECTOR3(0.0f, D3DX_PI * 2.0f, 0.0f));
				}
				if (m_vModelList[nCnt]->GetRot().x > D3DX_PI)
				{
					m_vModelList[nCnt]->SetRot(m_vModelList[nCnt]->GetRot() - D3DXVECTOR3(D3DX_PI * 2.0f, 0.0f, 0.0f));
				}
				else if (m_vModelList[nCnt]->GetRot().x < -D3DX_PI)
				{
					m_vModelList[nCnt]->SetRot(m_vModelList[nCnt]->GetRot() + D3DXVECTOR3(D3DX_PI * 2.0f, 0.0f, 0.0f));
				}
			}
			//--------------------------------------------------------����������
		}
		if (m_Fram == m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->nFram)
		{
			m_CntKeySet++;
			m_Fram = 0;

			//�L�[�Z�b�g�����K��l�Ɠ����ɂȂ�����--------------------����������
			if (m_CntKeySet == m_CharacterMotion[m_MotionType]->nNumKey)
			{
				//���[�v���Ȃ��Ƃ�------------------------------------����������
				if (m_CharacterMotion[m_MotionType]->nLoop == 0)
				{
						m_CntKeySet = 0;
						m_Fram = m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->nFram;
						return true;
				}
				//���[�v����Ƃ�--------------------------------------����������
				else if (m_CharacterMotion[m_MotionType]->nLoop == 1)
				{
					m_CntKeySet = 0;
					return false;
				}
			}
		}
		//�t���[�������K��l�Ɠ����ł͂Ȃ��Ƃ�------------------------����������
		else
		{
			//���[�V����������Ƃ�
			if (m_bMotion)
			{
				m_Fram++;
			}
		}
	}
	else
	{
		m_Fram = 0;
		m_CntKeySet = 0;
	}
	return false;
}
//====================================================================
//�S���̃��f����Disp���ݒ�
//====================================================================
void CModelSet::SetAllModelDisp(bool bDisp)
{
	//���f������
	for (unsigned int nCnt = 0; nCnt < m_vModelList.size(); nCnt++)
	{
		if (m_vModelList[nCnt])
		{
			m_vModelList[nCnt]->SetDisp(bDisp);
		}
	}
}
//====================================================================
//�I�t�Z�b�g�̓ǂݍ���
//====================================================================
void CModelSet::LoadOffset(CHARACTER_TYPE nType)
{
	char cReadText[1080];	//�����Ƃ��ēǂݎ��p
	char cHeadText[1080];	//��r����p
	char cDie[1080];		//�s�v�ȕ���
	int nCnt = 0;
	FILE *pFile;

	cReadText[0] = '\0';
	cHeadText[0] = '\0';
	D3DXVECTOR3 pos;
	int nIdxParent;			//�e�̃C���f�b�N�X
	int nIdx;				//���f���̃C���f�b�N�X
	int type;

	pFile = fopen(m_LoadOffsetFileName[nType], "r");
	if (pFile != NULL)
	{
		while (strcmp(cHeadText, "MODEL_OFFSET_END") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile);
			sscanf(cReadText, "%s", &cHeadText);
			//�z�u���郂�f���̍ő吔�̓ǂݍ���
			if (strcmp(cHeadText, "SET_START") == 0)
			{
				//END_SET������܂Ń��[�v
				while (strcmp(cHeadText, "SET_END") != 0)
				{
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s", &cHeadText);
					//MODEL_TYPE��������
					if (strcmp(cHeadText, "MODEL_TYPE") == 0)
					{
						sscanf(cReadText, "%s %s %d",
							&cDie, &cDie,
							&type);
					}
					//IDX��������
					else if (strcmp(cHeadText, "INDEX") == 0)
					{
						sscanf(cReadText, "%s %s %d",
							&cDie, &cDie,
							&nIdx);
					}
					//PARENT��������
					else if (strcmp(cHeadText, "PARENT") == 0)
					{
						sscanf(cReadText, "%s %s %d",
							&cDie, &cDie,
							&nIdxParent);
					}
					//POS��������
					else if (strcmp(cHeadText, "POS") == 0)
					{
						sscanf(cReadText, "%s %s %f %f %f",
							&cDie, &cDie,
							&pos.x,
							&pos.y,
							&pos.z);
					}
					//SET_END��������쐬���ǉ�
					else if (strcmp(cHeadText, "SET_END") == 0)
					{
						CModel *pModel = CModel::Create(type, nIdx);
						pModel->SetPosition(pos);
						pModel->SetParentIdx(nIdxParent);
						if (nIdxParent == -1)
						{
							pModel->SetParent(NULL);
						}
						else
						{
							pModel->SetParent(m_vModelList[nIdxParent]);
						}
						m_vModelList.emplace_back(pModel);
					}
				}
			}
		}

		fclose(pFile);
	}
	else
	{

	}

}
//====================================================================
//�����I�ɍX�V
//====================================================================
void CModelSet::ForcedUpdate()
{
	//���f�������J��Ԃ�
	for (size_t nCntKey = 0; nCntKey < m_vModelList.size(); nCntKey++)
	{
		//���[�V�����̉�]�̌����擾
		m_vModelList[nCntKey]->SetRot(m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->key[nCntKey]->rot);
	}

	m_vModelList[0]->GetPosition().y = m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->fHeight;
}
//====================================================================
//�J��
//====================================================================
void CModelSet::CharacterUnLoad(void)
{
	if (!m_CharacterMotion.empty())
	{
		for (size_t nCnt = 0; nCnt < m_CharacterMotion.size(); nCnt++)
		{
			if (!m_CharacterMotion[nCnt]->key_info.empty())
			{
				for (size_t nCntinfo = 0; nCntinfo < m_CharacterMotion[nCnt]->key_info.size(); nCntinfo++)
				{
					if (!m_CharacterMotion[nCnt]->key_info[nCntinfo]->key.empty())
					{
						for (size_t nCntkey = 0; nCntkey < m_CharacterMotion[nCnt]->key_info[nCntinfo]->key.size(); nCntkey++)
						{
							delete m_CharacterMotion[nCnt]->key_info[nCntinfo]->key[nCntkey];
							m_CharacterMotion[nCnt]->key_info[nCntinfo]->key[nCntkey] = nullptr;
						}
					}
					delete m_CharacterMotion[nCnt]->key_info[nCntinfo];
					m_CharacterMotion[nCnt]->key_info[nCntinfo] = nullptr;

				}
			}
			delete m_CharacterMotion[nCnt];
			m_CharacterMotion[nCnt] = nullptr;
		}
	}
	m_CharacterMotion.clear();
}
//====================================================================
//���f���Z�b�g�̃N���G�C�g
//====================================================================
CModelSet * CModelSet::CreateModelSet(void)
{
	CModelSet *pModelSet;
	pModelSet = new CModelSet();
	pModelSet->Init();
	return pModelSet;
}
//====================================================================
//��]�̌v�Z
//====================================================================
void CModelSet::CalcRotation()
{

	//�ڕW�_�ƌ��݂̍����i��]�j
	float diffRot = m_rotDest.y - m_rot.y;

	//3.14�̒��ߕ��̏������i��]�j
	CHossoLibrary::CalcRotation(m_rot.y);
	CHossoLibrary::CalcRotation(diffRot);

	//���߂����������Ǐ]����v�Z
	m_rot.y += diffRot * ADD_ROTATION_SPEED;
}
//====================================================================
//���[�V�����^�C�v�̎擾
//====================================================================
CModelSet::CHARACTER_MOTION_STATE &CModelSet::GetMotionType(void)
{
	return m_MotionType;
}
//====================================================================
//�O�̃��[�V�����^�C�v�̎擾
//====================================================================
CModelSet::CHARACTER_MOTION_STATE CModelSet::GetMotionOldType(void)
{
	return m_MotionOld;
}
//====================================================================
//���[�V�������Ă邩�ǂ����擾
//====================================================================
bool & CModelSet::GetMotion()
{
	return m_bMotion;
}
//====================================================================
//�L�[�Z�b�g�̎擾
//====================================================================
int &CModelSet::GetKeySet(void)
{
	return m_CntKeySet;
}
//====================================================================
//�t���[���̎擾
//====================================================================
int &CModelSet::GetFram(void)
{
	return m_Fram;

}
//====================================================================
//���f���̃��X�g��Ԃ�	�Q�Ɠn��
//====================================================================
std::vector<CModel*>& CModelSet::GetCharacterModelList()
{
	return m_vModelList;
}
//====================================================================
//���f���p�[�c�̃��X�g��Ԃ�	�Q�Ɠn��
//====================================================================
//CModel* CModelSet::GetCharacterModelPartsList(int nCnt)
//{
//	return m_vModelList[nCnt];
//}
//====================================================================
//���̍����̎擾
//====================================================================
float CModelSet::GetHeightBet(void)
{
	return m_HeightBet;
}
//====================================================================
//�O�̃��[�V�����^�C�v�̐ݒ�
//====================================================================
void CModelSet::SetMotionOldType(CHARACTER_MOTION_STATE type)
{
	m_MotionOld = type;
}
//====================================================================
//�L�[�Z�b�g�̐ݒ�
//====================================================================
void CModelSet::SetKeySet(int keyset)
{
	m_CntKeySet = keyset;
}
//====================================================================
//�t���[���̐ݒ�
//====================================================================
void CModelSet::SetFram(int fram)
{
	m_Fram = fram;
}
//====================================================================
//���[�V�������邩���Ȃ���
//====================================================================
void CModelSet::SetUseMotion(bool use)
{
	m_bMotion = use;
}
//====================================================================
//�L�����N�^�[�^�C�v�ݒ�
//====================================================================
void CModelSet::SetCharacterType(CHARACTER_TYPE CharaType)
{
	m_CharaType = CharaType;
}
//====================================================================
//�L�����N�^�[�^�C�v�̐ݒ�
//====================================================================
CModelSet::CHARACTER_TYPE CModelSet::GetCharacterType()
{
	return m_CharaType;
}
//====================================================================
//��]�̎擾
//====================================================================
D3DXVECTOR3 &CModelSet::GetRot(void)
{
	return m_rot;
}
