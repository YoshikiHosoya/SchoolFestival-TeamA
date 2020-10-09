//------------------------------------------------------------------------------
//
//�L�����N�^�[����  [character.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "character.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "game.h"
#include "modelcharacter.h"
#include "collision.h"
#include "motion.h"
#include "camera.h"
#include "meshfield.h"
#include "model_object.h"
#include "Map.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
std::vector<std::unique_ptr<CDefaultParam>> CCharacter::m_DefaultParam = {};
std::vector<std::string> CCharacter::m_aParamFileName =
{
	{ "data/SAVEDATA/CHaracterParam/PlayerParam.txt" },
};

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define INERTIA	(0.2f)			//���C
#define AIR_INERTIA (0.05f)		//�󒆎��̖��C
#define GRAVITY (0.7f)			//�d��
//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CCharacter::CCharacter()
{
	m_pos = ZeroVector3;
	m_posOld = ZeroVector3;
	m_move = ZeroVector3;
	m_rot = ZeroVector3;
	m_nLife = 1;
	m_bAttack = false;
	m_bJump = false;
	m_bInvincible = false;
	m_bGravity = true;
	m_bAlive = true;
	m_nCntState = 0;
	m_State = STATE_NORMAL;
	m_Param = PARAM_PLAYER;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CCharacter::~CCharacter()
{
	if (m_pCollision)
	{
		m_pCollision.reset();
	}
}

//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CCharacter::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}

//------------------------------------------------------------------------------
//�_���[�W����
//------------------------------------------------------------------------------
bool CCharacter::ApplyDamage(int nDamage, int nBlueDamage)
{
	return false;
}

//------------------------------------------------------------------------------
//�X�e�[�g�ݒ�
//------------------------------------------------------------------------------
void CCharacter::SetState(STATE nextstate)
{
	m_State = nextstate;
}

//------------------------------------------------------------------------------
//�p�����[�^�ݒ�
//------------------------------------------------------------------------------
void CCharacter::SetParam(PARAM param)
{
	//�p�����[�^�ݒ�
	m_Param = param;

	//�ő�g�o�ݒ�
	m_nLife = m_DefaultParam[param]->GetMaxLife();
}

//------------------------------------------------------------------------------
//�L�����N�^�[���\��
//------------------------------------------------------------------------------
void CCharacter::ShowCharacterInfo()
{
#ifdef _DEBUG
	//�L�����N�^�[�����
	if (ImGui::TreeNode("CharacterInfo"))
	{
		ImGui::Text("pos %.2f,%.2f,,%.2f", m_pos.x, m_pos.y, m_pos.z);
		ImGui::Text("move %.2f,%.2f,,%.2f", m_move.x, m_move.y, m_move.z);
		ImGui::Text("rot %.2f,%.2f,,%.2f", m_rot.x, m_rot.y, m_rot.z);


		ImGui::Text("bJump [%d] bInvincible [%d]", m_bJump, m_bInvincible);
		ImGui::Text("State [%d] nCntState [%d]", m_State, m_nCntState);


		ImGui::TreePop();
	}
#endif //DEBUG
}


//------------------------------------------------------------------------------
//�p�����[�^�擾
//------------------------------------------------------------------------------
HRESULT CCharacter::LoadDefaultParam()
{
	//�ϐ��錾
	FILE *pFile;			//�t�@�C���̃|�C���^
	char cReadText[MAX_TEXT];
	char cHeadText[MAX_TEXT];
	char cDieText[MAX_TEXT];
	int nLife = 0;
	float fMoveSpeed = 0.0f;
	float fJumpSpeed = 0.0f;
	float fDashSpeed = 0.0f;
	float fAirSpeed = 0.0f;
	int nInvincinbleTime = 0;

	for (size_t nCnt = 0; nCnt < m_aParamFileName.size(); nCnt++)
	{
		//�t�@�C�����J��
		pFile = fopen(m_aParamFileName[nCnt].data(), "r");

		//�t�@�C�����������ꍇ
		if (pFile)
		{

			std::unique_ptr<CDefaultParam> pParam(new CDefaultParam);

			//�p�����[�^�̔z��ǉ�
			m_DefaultParam.emplace_back(std::move(pParam));

			std::cout << "new DefaultParam - " << nCnt << NEWLINE;

			//�X�N���v�g������܂�
			while (strcmp(cHeadText, "SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s", &cHeadText);
			}
			//�X�N���v�g��������
			if (strcmp(cHeadText, "SCRIPT") == 0)
			{
				//�G���h�X�N���v�g������O���[�v
				while (strcmp(cHeadText, "END_SCRIPT") != 0)
				{
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s", &cHeadText);
					//���s
					if (strcmp(cHeadText, "\n") == 0)
					{
					}
					//�L�����N�^�[�Z�b�g��������
					else if (strcmp(cHeadText, "PARAMSET") == 0)
					{
						//�G���h�L�����N�^�[�Z�b�g������܂Ń��[�v
						while (strcmp(cHeadText, "END_PARAMSET") != 0)
						{
							fgets(cReadText, sizeof(cReadText), pFile);
							sscanf(cReadText, "%s", &cHeadText);
							//�ő�HP
							if (strcmp(cHeadText, "MAX_LIFE") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &nLife);
								std::cout << "m_DefaultParam - " << nCnt  << " MAX_LIFE >> " << nLife << NEWLINE;
								m_DefaultParam[nCnt]->SetMaxLife(nLife);
							}
							//�ړ����x
							if (strcmp(cHeadText, "MOVE_SPEED") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDieText, &cDieText, &fMoveSpeed);
								std::cout << "m_DefaultParam - " << nCnt << " MOVE_SPEED >> " << fMoveSpeed << NEWLINE;
								m_DefaultParam[nCnt]->SetMoveSpeed(fMoveSpeed);
							}
							//�_�b�V�����x
							if (strcmp(cHeadText, "DASH_SPEED") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDieText, &cDieText, &fDashSpeed);
								std::cout << "m_DefaultParam - " << nCnt << " DASH_SPEED >> " << fDashSpeed << NEWLINE;
								m_DefaultParam[nCnt]->SetDashSpeed(fDashSpeed);
							}
							//�W�����v��
							if (strcmp(cHeadText, "JUMP_SPEED") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDieText, &cDieText, &fJumpSpeed);
								std::cout << "m_DefaultParam - " << nCnt << " JUMP_SPEED >> " << fJumpSpeed << NEWLINE;
								m_DefaultParam[nCnt]->SetJumpSpeed(fJumpSpeed);
							}
							//�󒆂̈ړ����x
							if (strcmp(cHeadText, "AIR_SPEED") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDieText, &cDieText, &fAirSpeed);
								std::cout << "m_DefaultParam - " << nCnt << " AIR_SPEED >> " << fAirSpeed << NEWLINE;
								m_DefaultParam[nCnt]->SetAirSpeed(fAirSpeed);
							}
							//���G����
							if (strcmp(cHeadText, "INVINCIBLE_TIME") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &nInvincinbleTime);
								std::cout << "m_DefaultParam - " << nCnt << " INVINCIBLE_TIME >> " << nInvincinbleTime << NEWLINE;
								m_DefaultParam[nCnt]->SetInvincinbleTime(nInvincinbleTime);
							}
							//�I��
							if (strcmp(cHeadText, "END_PARAMSET") == 0)
							{
								std::cout << "LoadSuccess!" << "LoadDefaultParam() - " << nCnt << NEWLINE;
								std::cout << NEWLINE;
								break;
							}
						}
					}
				}
			}
			fclose(pFile);
		}

		//�J���Ȃ�������
		else
		{
			std::cout << "LoadFailed!!  Can't Open File." << "LoadDefaultParam() - " << nCnt << NEWLINE;

		}
	}
	return S_OK;
}