//------------------------------------------------------------------------------
//
//����ƂȂ郂�f���̏���  [modelparts_weapon.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "modelparts_weapon.h"
#include "renderer.h"
#include "manager.h"
#include "orbit.h"
#include "collision.h"
#include "player.h"
#include "enemy.h"
#include "sound.h"
#include "particle.h"
#include "effectanimation3D.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CModelParts_Weapon::CModelParts_Weapon()
{

}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CModelParts_Weapon::~CModelParts_Weapon()
{

}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CModelParts_Weapon::Init()
{
	//������
	CModelParts::Init();

	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CModelParts_Weapon::Uninit()
{
	CModelParts::Uninit();
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CModelParts_Weapon::Update()
{
	//�X�V
	CModelParts::Update();

	//�v���C���[�̕���̏ꍇ
	if (m_pWeaponHasCharacter._Get()->GetObjType() == CScene::OBJTYPE_PLAYER)
	{
		//����̍��{�̍��W
		D3DXVECTOR3 pos = D3DXVECTOR3(GetMtx()->_41, GetMtx()->_42, GetMtx()->_43);

		//���̐�[�̍��W
		D3DXVECTOR3 pos2;

		//�}�g���b�N�X�̌v�Z�œK���ɏo��
		D3DXVec3TransformCoord(&pos2, &D3DXVECTOR3(0.0f,100.0f,0.0f), GetMtx());

		//�����v�Z
		D3DXVECTOR3 posdif = pos2 - pos;

		//����
		float fRand = (float)(rand() % 100) / 100.0f;

		//�G�t�F�N�g �p�`�p�`���Ă�悤��
		CParticle::Create(pos + (posdif * fRand), 30, 2.5f, D3DXCOLOR(0.4f, 0.4f, 0.8f, 0.7f), 7, 4);
		CParticle::Create(pos + (posdif * fRand), 5, 12.0f, D3DXCOLOR(0.4f, 0.4f, 0.8f, 0.4f), 2, 1);
		CEffectAnimation3D::Create(pos + (posdif * fRand), D3DXVECTOR3((float)(rand() % 100), (float)(rand() % 100), 0.0f), CTexture::SEPARATE_TEX_EFFECT_STANING, D3DXCOLOR(0.4f,0.4f,1.0f,1.0f), CHossoLibrary::Random_PI(), 1);
	}

	//���菈��
	Collision();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CModelParts_Weapon::Draw()
{
	CModelParts::Draw();
}
//------------------------------------------------------------------------------
//����
//------------------------------------------------------------------------------
std::unique_ptr<CModelParts_Weapon> CModelParts_Weapon::Create(std::shared_ptr<CModelInfo> pModelInfo)
{
	//�������m��
	std::unique_ptr<CModelParts_Weapon> pModelParts_Weapon(new CModelParts_Weapon);

	//������
	pModelParts_Weapon->Init();

	//���f�����ݒ�
	pModelParts_Weapon->BindModelInfo(pModelInfo);

	//�����������
	return std::move(pModelParts_Weapon);
}

//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CModelParts_Weapon::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}

//------------------------------------------------------------------------------
//�O�Րݒ�
//------------------------------------------------------------------------------
void CModelParts_Weapon::StartAttack()
{
	//nullcheck
	if (!m_pOrbit)
	{
		//�O�Ր���
		m_pOrbit = COrbit::Create(GetMtx());
	}
	//nulcheck
	if (!m_pCollision)
	{
		m_pCollision = CCollision::Create(GetMtx(), CCollision::COLLISION_WEAPON);
	}
}
//------------------------------------------------------------------------------
//�U���I��
//------------------------------------------------------------------------------
void CModelParts_Weapon::EndAttack()
{
	//nullcheck
	if (m_pOrbit)
	{
		//����
		m_pOrbit->DeleteOrbit();
		m_pOrbit = nullptr;
	}

	//nullcehck
	if (m_pCollision)
	{
		//����
		m_pCollision.reset();
	}

	//0�ɂ��Ƃ�
	m_nDamage = 0;
	m_nBlueDamage = 0;
	m_fKnockBack_Front = 0.0;
	m_fKnockBack_Up = 0.0f;

}
//------------------------------------------------------------------------------
//�U���̏��X�V
//------------------------------------------------------------------------------
void CModelParts_Weapon::SetAttackInfo(CMotion::MOTION_TYPE motiontype)
{
	//�|�C���^�擾
	CMotion::ATTACK_INFO *pAttackInfo = CMotion::GetAttackInfo(motiontype);

	//nullcheck
	if (m_pOrbit)
	{
		//�O�Ղ̏��X�V
		m_pOrbit->SetCol(pAttackInfo->orbitcol);

		//offset
		m_pOrbit->SetPosOffset(D3DXVECTOR3(0.0f, pAttackInfo->fLength, 0.0f));

	}

	//nulcheck
	if (m_pCollision)
	{
		m_pCollision->SetCollisionInfo(pAttackInfo->fRadius, pAttackInfo->fLength);
	}
	//�_���[�W��
	m_nDamage = pAttackInfo->nAttack;
	m_nBlueDamage = pAttackInfo->nBlueAttack;
	m_fKnockBack_Front = pAttackInfo->fKnockBack_Front;
	m_fKnockBack_Up = pAttackInfo->fKnockBack_Up;
}


//------------------------------------------------------------------------------
//�����蔻�菈��
//------------------------------------------------------------------------------
void CModelParts_Weapon::Collision()
{
	//nullcheck
	if (m_pCollision)
	{
		//�f�o�b�O���\��
		m_pCollision->ShowDebugInfo();

		//Scene�̃��X�g
		std::vector<std::shared_ptr<CScene>> pSceneList;

		//�����Ă�L�����N�^�[�̃I�u�W�F�N�g�^�C�v�ɂ���Ĕ���̑Ώۂ�ς���
		switch (m_pWeaponHasCharacter._Get()->GetObjType())
		{
		case CScene::OBJTYPE_PLAYER:
			//�G�̃��X�g�擾
			CScene::GetSceneList(CScene::OBJTYPE_ENEMY, pSceneList);
			break;

		case CScene::OBJTYPE_ENEMY:
			//�v���C���[�̃��X�g�擾
			CScene::GetSceneList(CScene::OBJTYPE_PLAYER, pSceneList);
			break;
		default:
			//����ȊO�͔��肵�Ȃ�
			return;
			break;
		}

		//nullcheck
		if (!pSceneList.empty())
		{
			//�v�f��
			for (size_t nCnt = 0; nCnt < pSceneList.size(); nCnt++)
			{
				//�|�C���^�擾 CMeshField�^�ɃL���X�g
				CCharacter *pCharacter = ((CCharacter*)pSceneList[nCnt].get());

				//nullcheck
				if (pCharacter)
				{
					//���G����̂Ȃ��Ƃ�
					if (!pCharacter->GetInvincible())
					{
						//�ڐG����
						if (m_pCollision->CollisionCylinder(pCharacter->GetCollision()))
						{
							//�m�b�N�o�b�N
							pCharacter->KnockBack(m_fKnockBack_Front, m_fKnockBack_Up,m_pWeaponHasCharacter._Get()->GetRotDest().y);

							//�_���[�W��^����
							pCharacter->ApplyDamage(m_nDamage, m_nBlueDamage);
						}
					}
				}
			}
		}
	}
}

//------------------------------------------------------------------------------
//�G�̖��G��ԉ���
//------------------------------------------------------------------------------
void CModelParts_Weapon::ResetEnemyInvincible()
{
	//Scene�̃��X�g
	std::vector<std::shared_ptr<CScene>> pSceneList;

	//�����Ă�L�����N�^�[�̃I�u�W�F�N�g�^�C�v�ɂ���Ĕ���̑Ώۂ�ς���
	switch (m_pWeaponHasCharacter._Get()->GetObjType())
	{
		//�����Ă�L�������v���C���[�̎�
	case CScene::OBJTYPE_PLAYER:
		//�G�̃��X�g�擾
		CScene::GetSceneList(CScene::OBJTYPE_ENEMY, pSceneList);
		break;

	default:
		//����ȊO�͂Ȃ�����Ȃ�
		return;
		break;
	}

	//nullcheck
	if (!pSceneList.empty())
	{
		//�v�f��
		for (size_t nCnt = 0; nCnt < pSceneList.size(); nCnt++)
		{
			//�|�C���^�擾 CMeshField�^�ɃL���X�g
			CCharacter *pCharacter = ((CCharacter*)pSceneList[nCnt].get());

			//nullcheck
			if (pCharacter)
			{
				//���G��ԉ���
				pCharacter->SetInvincible(false);
			}
		}
	}
}

