//=============================================================================
// �L�����N�^�[���f���������� [Character.cpp] : NORI
//=============================================================================
#include "Character.h"
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
#include "ModelSet.h"
//=============================================================================
// �ÓI�����o�ϐ�������
//=============================================================================

//=============================================================================
// �}�N��
//=============================================================================
#define ADD_ROTATION_SPEED (0.15f)

//====================================================================
//�R���X�g���N�^
//====================================================================
CCharacter::CCharacter(OBJ_TYPE type) :CScene(type)
{
	// �����蔻��̃|�C���^��null�ɂ���
	m_pCollision = nullptr;
}
//====================================================================
//�f�X�g���N�^
//====================================================================
CCharacter::~CCharacter()
{
	// �����蔻��̍폜
	if (m_pCollision != nullptr)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}
	// �����蔻��̍폜
	if (m_pModelSet != nullptr)
	{
		delete m_pModelSet;
		m_pModelSet = nullptr;
	}
}
//====================================================================
//������
//====================================================================
HRESULT CCharacter::Init(void)
{
	m_pos				= ZeroVector3;										// �ʒu
	m_move				= ZeroVector3;										// �ړ���
	m_rot				= ZeroVector3;										// ��]
	m_AddArmRot			= ZeroVector3;										//
	m_AddHeadRot		= ZeroVector3;										//
	m_ShotRotDest		= D3DXVECTOR3(0.0f, 0.0f, 0.5f*  D3DX_PI);			// ������
	m_rotDest.y			= -0.5f*  D3DX_PI;									// ��]���鍷��
	m_nLife				= 100;												// �̗�
	m_nMaxLife			= 100;												// �ő�g�o
	m_HeightBet			= 0.0f;												//
	m_state				= CHARACTER_STATE_NORMAL;							// ���
	m_bCanJump			= false;											// �W�����v�t���O
	m_bGravity			= true;												//
	m_bDieFlag			= false;											// ���S�t���O
	m_bMotion			= true;												// ���[�V�������邩�ǂ���
	m_bFall				= false;											//
	m_bDraw				= true;												//�`�悷�邩�ǂ���
	m_bRotArm			= false;
	// �����蔻�萶��
	m_pCollision = CCollision::Create();
	m_pCollision->SetPos(&m_pos);
	m_pCollision->SetPosOld(&m_posold);
	m_pModelSet = CModelSet::CreateModelSet();
	//�}�g���b�N�X������
	D3DXMatrixIdentity(&m_mtxWorld);

	return S_OK;
}
//====================================================================
//�I��
//====================================================================
void CCharacter::Uninit(void)
{
	// �����蔻��̍폜
	if (m_pCollision != nullptr)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}
}
//====================================================================
//�X�V
//====================================================================
void CCharacter::Update(void)
{
	//�OF�̏��ۑ�
	m_posold = m_pos;
	m_CharacterDirectionOld = m_CharacterDirection;

	//�ړ��Ɋւ���v�Z
	CalcMove();

	//��]�Ɋւ���v�Z
	CalcRotation();

	//�e�ł��������߂�
	CalcShotDirection();

	//�X�e�[�g�ɉ���������
	State();


	//�������Ȃ��璅�n�����Ƃ�
	if (m_CharacterDirection == DIRECTION::DOWN && GetJump() == true)
	{
		ResetCharacterDirection();
	}

	//�����蔻�菈��
	//���z�֐�
	Collision();

	//���[�V��������
	if (m_pModelSet != nullptr)
	{
		if (m_pModelSet->Motion() == true)
		{
			DefaultMotion();
		}
	}
}
//====================================================================
//�`��
//====================================================================
void CCharacter::Draw(void)
{
	//�`�悵�Ȃ���
	if (!m_bDraw)
	{
		//return
		return;
	}
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�}�g���b�N�X�v�Z
	CHossoLibrary::CalcMatrix(&m_mtxWorld, m_pos, m_rot);


	//���f���̕`��
	for (unsigned int nCnt = 0; nCnt < m_pModelSet->GetCharacterModelList().size(); nCnt++)
	{
		if (m_bRotArm == true)
		{
			if (nCnt == 2)
			{
				//�ڕW�_�ƌ��݂̍����i��]�j
				D3DXVECTOR3 diffHeadRot = m_AddHeadRot - m_pModelSet->GetCharacterModelList()[nCnt]->GetRot();

				//3.14�̒��ߕ��̏������i��]�j
				CHossoLibrary::CalcRotation(m_pModelSet->GetCharacterModelList()[nCnt]->GetRot().x);

				//3.14�̒��ߕ��̏������i��]�j
				CHossoLibrary::CalcRotation(diffHeadRot.x);

				//���߂����������Ǐ]����v�Z
				m_pModelSet->GetCharacterModelList()[nCnt]->GetRot().x += diffHeadRot.x * ADD_ROTATION_SPEED;
			}

			else if (nCnt == 3 || nCnt == 4)
			{
				//�ڕW�_�ƌ��݂̍����i��]�j
				D3DXVECTOR3 diffArmRot = m_AddArmRot - m_pModelSet->GetCharacterModelList()[nCnt]->GetRot();

				//3.14�̒��ߕ��̏������i��]�j
				CHossoLibrary::CalcRotation(m_pModelSet->GetCharacterModelList()[nCnt]->GetRot().x);

				//3.14�̒��ߕ��̏������i��]�j
				CHossoLibrary::CalcRotation(diffArmRot.x);

				//���߂����������Ǐ]����v�Z
				m_pModelSet->GetCharacterModelList()[nCnt]->GetRot().x += diffArmRot.x * ADD_ROTATION_SPEED;
			}
		}

		//�`�揈��
		m_pModelSet->GetCharacterModelList()[nCnt]->Draw(m_mtxWorld);
	}
}
//====================================================================
//�_���[�W���󂯂����̃��A�N�V����
//====================================================================
void CCharacter::DamageReaction()
{
	CManager::GetSound()->Play(CSound::LABEL_SE_BULLET_HIT);
	SetState(CHARACTER_STATE_DAMAGE_FLASHING);
}
//====================================================================
//���S���̃��A�N�V����
//====================================================================
void CCharacter::DeathReaction()
{

}
//====================================================================
//�X�e�[�g�ɉ���������
//====================================================================
void CCharacter::State()
{
	//�J�E���g�_�E��
	if (m_nStateCnt-- <= 0)
	{
		m_nStateCnt = 0;
	}

	//�X�e�[�^�X�̏���
	switch (m_state)
	{
	case CHARACTER_STATE_NORMAL:

		//�_���[�W���󂯂�Ƃǂ�ǂ�Ԃ��Ȃ�
		if (m_nLife < m_nMaxLife * 0.5f)
		{
			CCharacter::GetModelSet()->ChangeColor(true, D3DXCOLOR(1.0f - ((float)(m_nLife * 2.0f) / m_nMaxLife), 0.0f, 0.0f, 0.0f));
		}

		break;
	case CHARACTER_STATE_DAMAGE_FLASHING:
		//�J�E���g��0�ɂȂ�����ʏ�ɖ߂�
		if (m_nStateCnt <= 0)
		{
			SetState(CHARACTER_STATE_NORMAL);
			if (GetModelSet()->GetCharacterType() != CModelSet::CHARACTER_TYPE::CHARACTER_TYPE_BOSS_ONE)
			{
				GetModelSet()->SetAllModelDisp(true);
			}
		}

		//�_�ŏ���
		else if (m_nStateCnt % 4 == 0 && m_nStateCnt % 8 != 0)
		{
			if (GetModelSet()->GetCharacterType() != CModelSet::CHARACTER_TYPE::CHARACTER_TYPE_BOSS_ONE)
			{
				GetModelSet()->SetAllModelDisp(false);
			}
		}
		else if (m_nStateCnt % 8 == 0)
		{
			if (GetModelSet()->GetCharacterType() != CModelSet::CHARACTER_TYPE::CHARACTER_TYPE_BOSS_ONE)
			{
				GetModelSet()->SetAllModelDisp(true);
			}
		}

		//�_���[�W���󂯂�Ƃǂ�ǂ�Ԃ��Ȃ�
		if (m_nLife < m_nMaxLife * 0.5f)
		{
			CCharacter::GetModelSet()->ChangeColor(true, D3DXCOLOR(1.0f - ((float)(m_nLife * 2.0f) / m_nMaxLife), 0.0f, 0.0f, 0.0f));
		}
		break;
	case CHARACTER_STATE_DAMAGE_RED:

		//���Ԍo�߂�
		if (m_nStateCnt <= 0)
		{
			//�X�e�[�g�����ɖ߂�
			SetState(CHARACTER_STATE_NORMAL);
		}
		else
		{
			//�Ԃ��_��
			GetModelSet()->ChangeColor(true, D3DXCOLOR(1.0f, 0.2f, 0.0f, 0.0f));
		}
		break;
	case CHARACTER_STATE_INVINCIBLE:
		GetCollision()->SetCanCollision(false);

		//�J�E���g��0�ɂȂ�����ʏ�ɖ߂�
		if (m_nStateCnt <= 0)
		{
			SetState(CHARACTER_STATE_NORMAL);
		}

		//�����_��
		else if (m_nStateCnt % 4 == 0 && m_nStateCnt % 8 != 0)
		{
			GetModelSet()->ChangeColor(true, ZeroColor);
		}
		else if (m_nStateCnt % 8 == 0)
		{
			GetModelSet()->ChangeColor(true, FlashColor);
		}
		break;

	case CHARACTER_STATE_DEATH:
		m_pCollision->SetCanCollision(false);

		//�J�E���g��0�ɂȂ�����
		if (m_nStateCnt <= 0)
		{
			//���S���̃��A�N�V��������
			//�h���N���X���I�[�o�[���C�h
			DeathReaction();

			SetState(CHARACTER_STATE_NONE);
		}

		break;

	default:
		//�J�E���g��0�ɂȂ�����
		if (m_nStateCnt <= 0)
		{
			SetState(CHARACTER_STATE_NORMAL);
		}
		break;
	}

}

//====================================================================
//�X�e�[�g���ύX�����u��
//�ǂꂭ�炢���̃X�e�[�g��������
//�I�[�o�[���C�h�ŏ㏑������
//====================================================================
void CCharacter::StateChangeReaction()
{
	switch (m_state)
	{
	case CHARACTER_STATE_NORMAL:
		m_nStateCnt = 0;
		if (m_pCollision)
		{
			m_pCollision->SetCanCollision(true);
		}
		if (GetModelSet()->GetCharacterType() != CModelSet::CHARACTER_TYPE::CHARACTER_TYPE_BOSS_ONE)
		{
			GetModelSet()->SetAllModelDisp(true);
		}
		break;

	case CHARACTER_STATE_DAMAGE_FLASHING:
		m_nStateCnt = 60;

		break;
	case CHARACTER_STATE_DAMAGE_RED:
		m_nStateCnt = 3;

		break;
	case CHARACTER_STATE_INVINCIBLE:
		m_nStateCnt = 120;

		break;
	case CHARACTER_STATE_DEATH:
		if (GetModelSet()->GetCharacterType() != CModelSet::CHARACTER_TYPE::CHARACTER_TYPE_BOSS_ONE)
		{
			GetModelSet()->SetAllModelDisp(true);
		}
		m_nStateCnt = 10;
		break;
	}
}
//====================================================================
//���f���̃��[��
//====================================================================
void CCharacter::Move(float move, float fdest,float fSpeed)
{
	m_move.x += sinf(move * -D3DX_PI) * fSpeed;
	m_move.z += cosf(move * -D3DX_PI) * fSpeed;
	m_rotDest.y = fdest *  D3DX_PI;
}
//====================================================================
//�|�W�V�����̐ݒ�
//====================================================================
void CCharacter::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
	m_posold = pos;
	if (m_pCollision)
	{
		m_pCollision->SetPos(&m_pos);
		m_pCollision->SetPosOld(&m_posold);

	}

	CHossoLibrary::CalcMatrix(&m_mtxWorld, pos, m_rot);
}
//====================================================================
//�O�̃|�W�V�����̐ݒ�
//====================================================================
void CCharacter::SetPotisionOld(D3DXVECTOR3 posOld)
{
	m_posold = posOld;
}
//====================================================================
//���[�u�̐ݒ�
//====================================================================
void CCharacter::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}
//====================================================================
//��]�̐ݒ�
//====================================================================
void CCharacter::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//====================================================================
//�_���[�W���󂯂����̏���
//====================================================================
void CCharacter::AddDamage(int Damage)
{
	if (m_state == CHARACTER_STATE::CHARACTER_STATE_NORMAL)
	{
		//���C�t�����炷
		GetLife() -= Damage;

		//HP��0�ɂȂ�����
		if (GetLife() <= 0)
		{
			SetLife(0);

			//���S��Ԃɂ���
			SetState(CHARACTER_STATE_DEATH);
		}
		else
		{
			//�_���[�W���󂯂����̃��A�N�V����
			//�I�[�o�[���C�h
			DamageReaction();
		}
	}
}
//====================================================================
//��]�̍����̐ݒ�
//====================================================================
void CCharacter::SetRotDest(D3DXVECTOR3 rotDest)
{
	m_rotDest = rotDest;
}
//====================================================================
//�̗͂̐ݒ�
//====================================================================
void CCharacter::SetLife(int Life)
{
	m_nLife = Life;
}
//====================================================================
//�ő�g�o�ݒ�
//====================================================================
void CCharacter::SetMaxLife(int nMaxLife)
{
	m_nMaxLife = nMaxLife;
	SetLife(nMaxLife);
}
//====================================================================
//�W�����v�t���O�̐ݒ�
//====================================================================
void CCharacter::SetJump(bool bJump)
{
	m_bCanJump = bJump;
}
//====================================================================
//�L������Ԃ̐ݒ�
//====================================================================
void CCharacter::SetState(CHARACTER_STATE state)
{
	if (m_state != state)
	{
		m_state = state;
		m_nStateCnt = 0;
		GetModelSet()->ChangeColor(false, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

		//�X�e�[�g���ύX�������̃��A�N�V����
		StateChangeReaction();
	}
}
//====================================================================
//�X�e�[�g�̃J�E���g�ݒ�
//====================================================================
void CCharacter::SetStateCount(int nCntState)
{
	m_nStateCnt = nCntState;
}
//====================================================================
//�}�g���b�N�X�̐ݒ�
//====================================================================
void CCharacter::SetMtxWorld(D3DXMATRIX mtxWorld)
{
	m_mtxWorld = mtxWorld;
}
//====================================================================
//��]�̍����̎擾
//====================================================================
D3DXVECTOR3 &CCharacter::GetRotDest(void)
{
	return m_rotDest;
}
//====================================================================
//�L�����N�^�[�̏�Ԃ̎擾
//====================================================================
CCharacter::CHARACTER_STATE CCharacter::GetCharacterState(void)
{
	return m_state;
}
//====================================================================
//���f���̐ݒ���擾
//====================================================================
CModelSet * CCharacter::GetModelSet(void)
{
	return m_pModelSet;
}
//====================================================================
//�|�W�V�����̎擾
//====================================================================
D3DXVECTOR3 &CCharacter::GetPosition(void)
{
	return m_pos;
}
//====================================================================
//�O�̃|�W�V�����̎擾
//====================================================================
D3DXVECTOR3 &CCharacter::GetPositionOld(void)
{
	return m_posold;
}
//====================================================================
//���[�u�̎擾
//====================================================================
D3DXVECTOR3 &CCharacter::GetMove(void)
{
	return m_move;
}
//====================================================================
//��]�̎擾
//====================================================================
D3DXVECTOR3 &CCharacter::GetRot(void)
{
	return m_rot;
}
//====================================================================
//�̗͂̎擾
//====================================================================
int &CCharacter::GetLife(void)
{
	return m_nLife;
}

//====================================================================
//�W�����v�̎擾
//====================================================================
bool CCharacter::GetJump(void)
{
	return m_bCanJump;
}
//====================================================================
//�d�͂̎擾
//====================================================================
bool CCharacter::GetGravity(void)
{
	return m_bGravity;
}
//====================================================================
//�}�g���b�N�X�̎擾
//====================================================================
D3DXMATRIX *CCharacter::GetMtxWorld(void)
{
	return &m_mtxWorld;
}
//====================================================================
//�������̎擾
//====================================================================
D3DXVECTOR3 CCharacter::GetShotDirection(void)
{
	return m_ShotRotDest;
}
//====================================================================
//�F�ύX
//====================================================================
//void CCharacter::ChangeColor(bool ColorChangeFlag, D3DXCOLOR AddColor)
//{
//	//���f���̐F�ύX
//	for (unsigned int nCnt = 0; nCnt < m_vModelList.size(); nCnt++)
//	{
//		// ���Z����F�̐ݒ�
//		m_vModelList[nCnt]->SetAddColor(AddColor);
//		// �F�ύX�t���O�̐ݒ�
//		m_vModelList[nCnt]->SetColorChangeFlag(ColorChangeFlag);
//	}
//}
//====================================================================
//�S���̃��f����Disp���ݒ�
//====================================================================
//void CCharacter::SetAllModelDisp(bool bDisp)
//{
//	//���f������
//	for (unsigned int nCnt = 0; nCnt < m_vModelList.size(); nCnt++)
//	{
//		if (m_vModelList[nCnt])
//		{
//			m_vModelList[nCnt]->SetDisp(bDisp);
//		}
//	}
//}
//====================================================================
//�����I�ɍX�V
//====================================================================
void CCharacter::ForcedUpdate()
{
}
//====================================================================
//�L�����N�^�[�̌����ݒ肵�Ȃ���
//====================================================================
void CCharacter::ResetCharacterDirection()
{
	if (GetRot().y > 0)
	{
		m_ShotRotDest.z = D3DX_PI * 0.5f;
		SetCharacterDirection(DIRECTION::LEFT);
	}
	else if (GetRot().y < 0)
	{
		m_ShotRotDest.z = -D3DX_PI * 0.5f;
		SetCharacterDirection(DIRECTION::RIGHT);
	}
}
//====================================================================
//�f�o�b�O
//====================================================================
void CCharacter::DebugInfo(void)
{
	//CDebug_ModelViewer::OffsetViewer(m_vModelList);

	char aTreeName[MAX_TEXT] = {};
	sprintf(aTreeName, "CharacterInfo [%d]", CScene::GetID());

	if (ImGui::TreeNode(aTreeName))
	{
		ImGui::Text("m_pos [%.2f %.2f %.2f]", m_pos.x, m_pos.y, m_pos.z); ImGui::SameLine();
		ImGui::Text("m_move [%.2f %.2f %.2f]", m_move.x, m_move.y, m_move.z);

		ImGui::Text("m_posfall [%.2f %.2f %.2f]", m_posfall.x, m_posfall.y, m_posfall.z); ImGui::SameLine();
		ImGui::Text("m_ShotRotDest [%.2f %.2f %.2f]", m_ShotRotDest.x, m_ShotRotDest.y, m_ShotRotDest.z);

		ImGui::Text("m_rot [%.2f %.2f %.2f]", m_rot.x, m_rot.y, m_rot.z); ImGui::SameLine();
		ImGui::Text("m_rotDest [%.2f %.2f %.2f]", m_rotDest.x, m_rotDest.y, m_rotDest.z);

		ImGui::Text("m_nLife [%d]", m_nLife); ImGui::SameLine();
		ImGui::Text("m_state [%d]", m_state); ImGui::SameLine();
		ImGui::Text("m_nStateCnt [%d]", m_nStateCnt);
		//ImGui::Text("m_CharaType [%d]", m_CharaType); ImGui::SameLine();
		ImGui::Text("m_CharacterDirection [%d]", m_CharacterDirection);

		ImGui::Text("m_bGravity [%d]", m_bGravity); ImGui::SameLine();
		ImGui::Text("m_bCanJump [%d]", m_bCanJump); ImGui::SameLine();
		ImGui::Text("m_bDieFlag [%d]", m_bDieFlag); ImGui::SameLine();
		ImGui::Text("m_bDraw [%d]", m_bDraw);

		if (ImGui::TreeNode("MotionInfo"))
		{
			//ImGui::Text("m_MotionType [%d]", m_MotionType); ImGui::SameLine();
			//ImGui::Text("m_MotionOld [%d]", m_MotionOld);
			//ImGui::Text("m_CntKeySet [%d]", m_CntKeySet); ImGui::SameLine();
			//ImGui::Text("m_Fram [%d]", m_Fram);

			ImGui::TreePop();
		}
		ImGui::TreePop();

		if (m_pCollision)
		{
			m_pCollision->ShowDebugInfo();
		}
	}


}
//====================================================================
//�e�̌������ݒ�
//====================================================================
void CCharacter::CalcShotDirection()
{
	//������
	if (m_CharacterDirection == DIRECTION::LEFT)
	{
		m_ShotRotDest.z = 0.5f*D3DX_PI;
		m_AddHeadRot.x = 0.5f;
		m_AddArmRot.x = 0.5f* D3DX_PI;

	}
	else if (m_CharacterDirection == DIRECTION::RIGHT)
	{
		m_ShotRotDest.z = -0.5f*D3DX_PI;
		m_AddHeadRot.x = 0.5f;
		m_AddArmRot.x = 0.5f* D3DX_PI;
	}
	else if (m_CharacterDirection == DIRECTION::UP)
	{
		m_ShotRotDest.z = 0.0f*D3DX_PI;
		m_AddHeadRot.x = 1.0f;
		m_AddArmRot.x = 1.0f* D3DX_PI;
	}
	else if (m_CharacterDirection == DIRECTION::DOWN)
	{
		m_ShotRotDest.z = D3DX_PI;
		m_AddHeadRot.x = -0.5f;
		m_AddArmRot.x = -0.3f* D3DX_PI;
	}
}
//====================================================================
//�ړ��̌v�Z
//====================================================================
void CCharacter::CalcMove()
{
	//�����̒�R
	m_move.x += (0 - m_move.x)* 0.4f;
	m_move.z += (0 - m_move.z)* 0.4f;
	m_move.y += m_move.y * -0.1f;

	//�d�͂������Ƃ�
	if (m_bGravity == true)
	{
		//�d�͉��Z
		m_move.y -= 0.5f;
	}

	//�ړ�����
	m_pos += m_move;


	//�ߗ��֘A
	if (m_bFall == false)
	{
		m_posfall = m_pos;
	}
	if (m_pos.y <= -100 && m_bFall == true)
	{
		if (m_pos.x < m_posfall.x)
		{
			m_pos.x = m_posfall.x + 50;
		}
		else
		{
			m_pos.x = m_posfall.x - 50;
		}
		m_pos.y = m_posfall.y + 30;
		m_bFall = false;
	}
}

//====================================================================
//��]�̌v�Z
//====================================================================
void CCharacter::CalcRotation()
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
//�����蔻��̏���
//====================================================================
void CCharacter::Collision()
{
	// �}�b�v�̃|�C���^�擾
	CMap *pMap;
	pMap = CManager::GetBaseMode()->GetMap();

	// �}�b�v���f�������݂��������ē����蔻�肪���݂��鎞
	if (pMap && m_pCollision &&m_pModelSet)
	{
		m_pCollision->SetPos(&m_pos);
		m_pCollision->SetPosOld(&m_posold);

		//�R���W�����̍����ݒ�
		m_pCollision->SetHeight(m_pModelSet->GetCharacterModelList()[0]->GetPosition().y);

		// ��Q���̔���ƃ��C�̔���
		if (m_pCollision->ForPlayer_ObstacleCollision() || m_pCollision->RayBlockCollision(pMap, (m_pModelSet->GetCharacterModelList()[0]->GetMatrix() )))
		{
			// �W�����v���邱�Ƃ����F����
			SetJump(true);
			m_bFall = false;
		}
		else
		{
			// �W�����v���邱�Ƃ����F���Ȃ�
			SetJump(false);
			m_bFall = true;
		}
	}


}
//====================================================================
//�`��͈͓̔����ǂ����m�F
//====================================================================
bool CCharacter::CheckDrawRange()
{
	//�`�悷�邩�ǂ���
	m_bDraw = CManager::GetRenderer()->CheckScreenRange(m_pos);

	//�`��͈͓̔��̏ꍇ
	if (m_bDraw)
	{
		//mullcheck
		if (m_pCollision)
		{
			//�����蔻��\
			m_pCollision->SetCanCollision(true);
		}
	}
	else
	{
		//nullcheck
		if (m_pCollision)
		{
			//�����蔻��s��
			m_pCollision->SetCanCollision(false);
		}
	}
	//return
	return m_bDraw;
}

//====================================================================
//�����擾
//====================================================================
DIRECTION &CCharacter::GetCharacterDirection(void)
{
	return m_CharacterDirection;
}
//====================================================================
//1F�O�̌����擾
//====================================================================
DIRECTION & CCharacter::GetCharacterDirectionOld(void)
{
	return m_CharacterDirectionOld;
}
//====================================================================
//���̍����̎擾
//====================================================================
float CCharacter::GetHeightBet(void)
{
	return m_HeightBet;
}
//====================================================================
//�d�͂̐ݒ�
//====================================================================
void CCharacter::SetGravity(bool gravity)
{
	m_bGravity = gravity;
}
//====================================================================
//�L�����N�^�[�̌���
//====================================================================
void CCharacter::SetCharacterDirection(DIRECTION direction)
{
	m_CharacterDirection = direction;
}
//====================================================================
//�������̐ݒ�
//====================================================================
void CCharacter::SetShotDirection(D3DXVECTOR3 direction)
{
	m_ShotRotDest = direction;
}
//====================================================================
//�r����]���邩
//====================================================================
void CCharacter::SetRotArm(bool use)
{
	m_bRotArm = use;
}
//====================================================================
//�w�肵���Ԑ��̃��f���̉�]�v�Z
//====================================================================
void CCharacter::SetArmCalculation(int nCnt)
{
}
