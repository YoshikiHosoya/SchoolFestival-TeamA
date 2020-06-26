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
#include "effectanimation3D.h"
#include "collision.h"
#include "motion.h"
#include "camera.h"
#include "enemy.h"
#include "meshfield.h"
#include "model_object.h"
#include "Map.h"
#include "option.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
std::vector<std::unique_ptr<CDefaultParam>> CCharacter::m_DefaultParam = {};
std::vector<std::string> CCharacter::m_aParamFileName =
{
	{ "data/SAVEDATA/Woman/Param.txt" },
	{ "data/SAVEDATA/Armor/Param_Normal.txt" },
	{ "data/SAVEDATA/Armor/Param_Green.txt" },
	{ "data/SAVEDATA/Armor/Param_Black.txt" },

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
	m_pModelCharacter = nullptr;
	m_pos = ZeroVector3;
	m_posOld = ZeroVector3;
	m_move = ZeroVector3;
	m_rot = ZeroVector3;
	m_rotDest = ZeroVector3;
	m_rotDif = ZeroVector3;
	m_nLife = 1;
	m_bAttack = false;
	m_bAirAttack = false;
	m_bContinueAttack = false;
	m_bJump = false;
	m_bChangeMotion = false;
	m_bInvincible = false;
	m_bGravity = true;
	m_bAlive = true;
	m_nCntState = 0;
	m_State = STATE_NORMAL;
	m_fCenterPosOffset = 0.0f;
	D3DXMatrixIdentity(&m_mtxWorld);

}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CCharacter::~CCharacter()
{
	if (m_pModelCharacter)
	{
		m_pModelCharacter.reset();
	}
	if (m_pCollision)
	{
		m_pCollision.reset();
	}
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CCharacter::Init()
{
	//�R���W��������
	m_pCollision = CCollision::Create(GetMtx(), CCollision::COLLISION_CHARACTER);

	//����̏��ݒ�
	m_pCollision->SetCollisionInfo(30.0f, 100.0f);

	//����
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CCharacter::Uninit()
{

}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CCharacter::Update()
{
	//�O��̍��W�ۑ�
	m_posOld = m_pos;

	//���[�V�����ύX�������ǂ����@���Z�b�g
	m_bChangeMotion = false;

	//�ړ�����
	Move();

	//��]����
	Rot();

	//���[���h�}�g���b�N�X�̌v�Z
	CHossoLibrary::CalcMatrix(&m_mtxWorld, m_pos, m_rot);

	//�����蔻��
	Collision();

	//�X�e�[�g�ɉ���������
	State();

	//�U����Ԃ̎�
	if (m_bAttack)
	{
		//�ړ�����L�[���`�F�b�N
		if (m_pModelCharacter->CheckMoveKey())
		{
			//�v���C���[��Move�ɉ��Z
			//�����Ă���Ɉړ�
			m_move.x = -sinf(m_rotDest.y) * CMotion::GetAttackInfo(GetNowMotion())->fMoveFront;
			m_move.z = -cosf(m_rotDest.y) * CMotion::GetAttackInfo(GetNowMotion())->fMoveFront;

			//�㉺�̈ړ�
			m_move.y = CMotion::GetAttackInfo(GetNowMotion())->fMoveUp;

			//���Đ�
			CManager::GetSound()->Play(CSound::LABEL_SE_SWING);

			if (COption::GetAutoRotation())
			{
				switch (GetNowMotion())
				{
				case CMotion::PLAYER_LAND_ATTACK_Y_SPEAR:
				case CMotion::PLAYER_LAND_ATTACK_Y_05:
				case CMotion::PLAYER_AIR_ATTACK_X_04:
				case CMotion::PLAYER_LAND_ATTACK_X_05:
					//�J�����̉�]�ʎ擾
					D3DXVECTOR3 &CameraRot = CManager::GetRenderer()->GetCamera()->GetCameraRot();

					//���݌����Ă�������ݒ�
					CameraRot.y = GetRotDest().y + D3DX_PI;

					//3.14�Ɏ��߂�
					CHossoLibrary::CalcRotation(CameraRot.y);

					//�J������]
					CManager::GetRenderer()->GetCamera()->SetCameraRot(CameraRot);
				}
			}
		}
	}


	//���f���̓����̍X�V
	m_pModelCharacter->Update();

	//���[���h�}�g���b�N�X�̌v�Z
	CHossoLibrary::CalcMatrix(&m_mtxWorld, m_pos, m_rot);
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CCharacter::Draw()
{
	//���f���̕`��
	m_pModelCharacter->Draw();
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
	//�_���[�W������ꍇ�̓_���[�W���Z
	if (nDamage > 0)
	{
		//�_���[�W�Ɖ��Z
		m_nLife = m_nBlueLife - nDamage;
	}
	else
	{
		//�_���[�W
		m_nBlueLife -= nBlueDamage;
	}

	//��HP��HP��葽����
	if (m_nBlueLife > m_nLife)
	{
		m_nBlueLife = m_nLife;

	}

	//�X�e�[�g�ύX
	SetState(CCharacter::STATE_DAMAGE);

	//�_���[�W���󂯂����̃��A�N�V����
	//�h���N���X���I�[�o�[���C�h���Ďg�p
	DamageAction();

	//���C�t��0�ȉ��̏ꍇ
	if (m_nLife <= 0)
	{
		//���S���
		SetState(CCharacter::STATE_DEATH);
		return true;
	}

	return false;
}
//------------------------------------------------------------------------------
//�m�b�N�o�b�N
//------------------------------------------------------------------------------
void CCharacter::KnockBack(float fKnockBack_Front, float fKockBack_Up, float fAngle)
{
	//�v���C���[��Move�ɉ��Z
	//�����Ă���Ɉړ�
	m_move.x = sinf(fAngle) * -fKnockBack_Front;
	m_move.z = cosf(fAngle) * -fKnockBack_Front;

	//�㉺�̈ړ�
	m_move.y = fKockBack_Up;
}

//------------------------------------------------------------------------------
//���f���ݒ�
//------------------------------------------------------------------------------
void CCharacter::SetParameter(MODEL_TYPE modeltype, PARAM_TYPE Paramtype, std::shared_ptr<CCharacter> MyPtr)
{
	//���f���L�����N�^�[����
	m_pModelCharacter = CModelCharacter::Create(modeltype);

	//�}�g���b�N�X�ݒ�
	m_pModelCharacter->SetCharacterMtx(&m_mtxWorld);

	//�����̃|�C���^�ݒ�
	m_pModelCharacter->SetCharacterPtr(MyPtr);

	//�p�����[�^�^�C�v�ݒ�
	m_Paramtype = Paramtype;
	m_modeltype = modeltype;

	//�G�̎�ނœG�̃p�����[�^�ݒ�
	switch (m_Paramtype)
	{
	case CCharacter::PARAM_ENEMY:
		break;
	case CCharacter::PARAM_ENEMY_GREEN:
		m_pModelCharacter->SetPartsMaterialCol(CSceneX::MAT_ENEMY_GREEN);
		break;
	case CCharacter::PARAM_ENEMY_BLACK:
		m_pModelCharacter->SetPartsMaterialCol(CSceneX::MAT_ENEMY_BLACK);
		break;
	}

	//�p�����[�^�ݒ�
	m_nBlueLife = m_nLife = m_DefaultParam[m_Paramtype]->GetMaxLife();

	//���̍����擾�@�G�t�F�N�g�Ƃ��̔�����
	m_fCenterPosOffset = m_pModelCharacter->GetWaistHeight();
}

//------------------------------------------------------------------------------
//�X�e�[�g�ݒ�
//------------------------------------------------------------------------------
void CCharacter::SetState(STATE nextstate)
{
	m_State = nextstate;
	switch (nextstate)
	{
	case CCharacter::STATE_NORMAL:
		//���G���
		m_bInvincible = false;
		break;
	case CCharacter::STATE_DAMAGE:
		//���G���Ԑݒ�
		m_nCntState = m_DefaultParam[m_Paramtype]->GetInvincibleTime();

		//���G���
		m_bInvincible = true;
		break;
	case CCharacter::STATE_STAN:
		break;
	case CCharacter::STATE_DEATH:
		//���S���
		SetAlive(false);
		break;
	}
}
//------------------------------------------------------------------------------
//���݂̃��[�V�����擾
//------------------------------------------------------------------------------
CMotion::MOTION_TYPE CCharacter::GetNowMotion()
{
	return m_pModelCharacter->GetMotion();
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

		ImGui::Text("dest %.2f,%.2f,,%.2f", m_rotDest.x, m_rotDest.y, m_rotDest.z);
		ImGui::Text("dif %.2f,%.2f,,%.2f", m_rotDif.x, m_rotDif.y, m_rotDif.z);

		ImGui::Text("MaxLife %d : Life %d", m_DefaultParam[m_Paramtype]->GetMaxLife(),m_nLife);
		ImGui::Text("BlueLife %d", m_nBlueLife);

		ImGui::Text("bAttack [%d] bAirAttack [%d] bContinueAttack [%d]", m_bAttack, m_bAirAttack,m_bContinueAttack);
		ImGui::Text("bJump [%d] bInvincible [%d]", m_bJump, m_bInvincible);
		ImGui::Text("State [%d] nCntState [%d]", m_State, m_nCntState);

		m_pModelCharacter->ShowModelCharacterInfo();

		ImGui::TreePop();
	}
#endif //DEBUG
}
//------------------------------------------------------------------------------
//���[�V�����؂�ւ�
//------------------------------------------------------------------------------
void CCharacter::ChangeMotion(CMotion::MOTION_TYPE nextmotion)
{
	//���[�V�������؂�ւ������
	if (GetNowMotion() != nextmotion)
	{
		//���[�V�����ύX����
		m_bChangeMotion = true;

		//���[�V�����؂�ւ�
		m_pModelCharacter->SetMotion(nextmotion);
	}
}

//------------------------------------------------------------------------------
//���[�V�����؂�ւ�
//------------------------------------------------------------------------------
bool CCharacter::ContinueAttack()
{
	//�ŏI�L�[�������ꍇ
	if (m_pModelCharacter->GetKey() + 1 == CMotion::GetNumKey(m_pModelCharacter->GetMotion()))
	{
		return true;
	}
	return false;
}
//------------------------------------------------------------------------------
//�ړ�����
//------------------------------------------------------------------------------
void CCharacter::Move()
{
	if(m_bGravity)
	{
		//�d�͉��Z
		m_move.y -= GRAVITY;
	}
	else
	{
		//���d�̓J�E���^���O�ȉ��ɂȂ�����
		if (m_nCntGravity-- <= 0)
		{
			m_bGravity = true;
		}
	}

	//�ړ��ʉ��Z
	m_pos += m_move;

	//�󒆎�
	if (m_bJump)
	{
		//����
		m_move.x += (0 - m_move.x) * AIR_INERTIA;
		m_move.z += (0 - m_move.z) * AIR_INERTIA;
	}
	//����ȊO
	else
	{
		//����
		m_move.x += (0 - m_move.x) * INERTIA;
		m_move.z += (0 - m_move.z) * INERTIA;
	}
}
//------------------------------------------------------------------------------
//��]����
//------------------------------------------------------------------------------
void CCharacter::Rot()
{
	//��]�̍��������߂�
	m_rotDif.y = m_rotDest.y - m_rot.y;

	//3.14�ȓ��ɂ���
	CHossoLibrary::CalcRotation(m_rotDif.y);

	//���f���̉�]������
	m_rot.y += m_rotDif.y * 0.3f;

	//3.14�ȓ��ɂ���
	CHossoLibrary::CalcRotation(m_rot.y);
}

//------------------------------------------------------------------------------
//�����蔻��
//------------------------------------------------------------------------------
void CCharacter::Collision()
{
	bool bJump = true;

	//�t�B�[���h�̃T�C�Y�擾
	D3DXVECTOR3 FieldSize = CMap::GetFieldSize() * 0.5f;

	//�t�B�[���h�O�ɏo��Ȃ��悤�ɂ���
	CHossoLibrary::RangeLimit_Equal_Float(m_pos.x, -FieldSize.x, FieldSize.x);
	CHossoLibrary::RangeLimit_Equal_Float(m_pos.z, -FieldSize.z, FieldSize.z);

	//�͈͂���o�Ȃ��悤�ɂ���
	if (m_pos.y < 0)
	{
		//�������̗͂�����
		m_move.y = 0;

		//0�̈ʒu�ɍ��킷
		m_pos.y = 0;

		//�W�����v��ԉ���
		bJump = false;
		m_bAirAttack = false;
		m_bContinueAttack = false;

	}

	//Scene�̃��X�g
	std::vector<std::shared_ptr<CScene>> pSceneList;

	//�V�[�����擾
	CScene::GetSceneList(CScene::OBJTYPE_ENEMY, pSceneList);
	//�z��ɓ����Ă邩
	if (!pSceneList.empty())
	{
		//�v�f��
		for (size_t nCnt = 0; nCnt < pSceneList.size(); nCnt++)
		{
			//�|�C���^�擾 CMeshField�^�ɃL���X�g
			CEnemy *pEnemy = ((CEnemy*)pSceneList[nCnt].get());

			//nullcheck
			if (pEnemy && pEnemy != this)
			{
				//�����̍��W
				D3DXVECTOR3 CollisionAfterPos = pEnemy->GetPos();

				//�L�����N�^�[�̔���@�G
				if (m_pCollision->CollisionCharacter(pEnemy->GetCollision(), &CollisionAfterPos))
				{
					//���W�ړ�
					pEnemy->SetPos(CollisionAfterPos);
				}
			}
		}
	}

	//�W�����v��Ԃ�true����false�ɂȂ�����
	if (m_bJump == true && bJump == false && m_modeltype == MODEL_PLAYER)
	{
		//���Đ�
		CManager::GetSound()->Play(CSound::LABEL_SE_LANDING);
	}

	//�W�����v��Ԑݒ�
	m_bJump = bJump;
}
//------------------------------------------------------------------------------
//��Ԃɉ���������
//------------------------------------------------------------------------------
void CCharacter::State()
{
	switch (m_State)
	{
	case CCharacter::STATE_NONE:
		break;
	case CCharacter::STATE_NORMAL:
		break;
	case CCharacter::STATE_DAMAGE:
		m_nCntState--;
		if (m_nCntState < 0)
		{
			//�ʏ��Ԃɖ߂�
			SetState(CCharacter::STATE_NORMAL);
			m_bInvincible = false;

			//�j���[�g�����ɖ߂�
			m_pModelCharacter->ResetMotion();
			m_pModelCharacter->SetDefaultMotion();
		}
		break;
		//�X�^����
	case CCharacter::STATE_STAN:

		//�J�E���g�_�E��
		m_nCntState--;

		//15F�Ɉ��
		if (m_nCntState % 15 == 0)
		{
			//
			CEffectAnimation3D::Create(GetCenterPos(), D3DXVECTOR3(80.0f, 120.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_STANING,D3DXCOLOR(0.4f,0.4f,1.0f,1.0f), CHossoLibrary::Random_PI(), 2);
		}

		break;

		//���S
	case CCharacter::STATE_DEATH:

		//�J�E���g�_�E��
		m_nCntState--;

		//�J�E���^��0�ɂȂ�����
		if (m_nCntState < 0)
		{
			//���S���̃��A�N�V����
			//�h���N���X���I�[�o�[���C�h���Ďg�p
			DeathAction();
			SetState(STATE_NONE);
		}
		break;
	default:
		break;
	}
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