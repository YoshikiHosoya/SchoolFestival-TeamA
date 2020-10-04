// =====================================================================================================================================================================
//
// �A�j���[�V�����A�C�e�������̐���[animation_item.cpp]
// Author : Fujiwara Masato
//
// =====================================================================================================================================================================

// =====================================================================================================================================================================
//�C���N���[�h
// =====================================================================================================================================================================
#include "Anim_Item.h"
#include "collision.h"
#include "basemode.h"
#include "manager.h"
#include "renderer.h"
#include "particle.h"
#include "sound.h"
#include "player.h"
#include "scoremanager.h"
#include "playerui.h"
#include "map.h"

// =====================================================================================================================================================================
//�ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================

// =====================================================================================================================================================================
//�}�N��
// =====================================================================================================================================================================
#define SWITCHCOUNT (5)
// =====================================================================================================================================================================
//�R���X�g���N�^
// =====================================================================================================================================================================
CAnimationItem::CAnimationItem(OBJ_TYPE obj) : CItem(), CTexAnimation3D(obj)
{
}
// =====================================================================================================================================================================
//�f�X�g���N�^
// =====================================================================================================================================================================
CAnimationItem::~CAnimationItem()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
HRESULT CAnimationItem::Init()
{
	// �|���S���̐���
	CTexAnimation3D::Init();
	// �A�C�e���̏�����
	CItem::Init();

	// �����蔻��̍��W�̐ݒ�
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetSize(GetItem_Data().CollisionSize);
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);

	return S_OK;
}

// =====================================================================================================================================================================
//
// �I������
//
// =====================================================================================================================================================================
void CAnimationItem::Uninit(void)
{
	// �A�C�e���̏I������
	CItem::Uninit();
	// �|���S���̉��
	CTexAnimation3D::Uninit();
}

// =====================================================================================================================================================================
//
// �X�V����
//
// =====================================================================================================================================================================
void CAnimationItem::Update(void)
{
	// 1�t���[���O�̍��W��ݒ�
	m_PosOld = GetPosition();

	// �A�C�e���̋������Ƃ̈ړ�
	BehaviorType(GetPosition());

	// �A�C�e���̔���
	ItemCollision();

	// �A�C�e���̑؍ݎ��ԊǗ�
	RemainTimer();

	// ���W���X�V
	SetPosition(GetPosition());

	// �A�C�e���̍X�V
	CItem::Update();
	// �|���S���̍X�V
	CTexAnimation3D::Update();
}

// =====================================================================================================================================================================
//
// �`�揈��
//
// =====================================================================================================================================================================
void CAnimationItem::Draw(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =									// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();

	// �A���t�@�e�X�g�̐ݒ�ɕύX
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// �A���t�@�e�X�g�L��
	pDevice->SetRenderState(D3DRS_ALPHAREF, 200);				// �A���t�@�l�̊�ݒ�(����傫���ƕ`�悷��)
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// �󋵂ɉ����ăA���t�@�e�X�g�����s����(�V�s�N�Z�� > ���݂̃s�N�Z��)
	pDevice->SetRenderState(D3DRS_LIGHTING, false);				// ���C�e�B���Ooff
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// �r���[�}�g���b�N�X�̑���p
	D3DXMATRIX mtxView;
	// ���݂̃r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// �r���{�[�h����
	CHossoLibrary::SetBillboard(&mtxView);

	// �`��
	CTexAnimation3D::Draw();

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	// �A���t�@�e�X�g�̐ݒ��߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		// �A���t�@�e�X�g����
	pDevice->SetRenderState(D3DRS_LIGHTING, true);				// ���C�e�B���Oon
}

// =====================================================================================================================================================================
//
// �f�o�b�O
//
// =====================================================================================================================================================================
void CAnimationItem::DebugInfo()
{
}

// =====================================================================================================================================================================
//
// ��ޕʃe�N�X�`���o�C���h����
//
// =====================================================================================================================================================================
void CAnimationItem::SwitchTexture(ITEMTYPE type)
{
	switch (type)
	{
	case CItem::ANIM_ITEMTYPE_ROASTCHICKEN:
		this->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_ROASTCHICKEN));
		this->SetTex(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_ROASTCHICKEN);
		this->SetCntSwitch(SWITCHCOUNT);
		break;

	case CItem::ANIM_ITEMTYPE_FISH:
		this->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_FISH));
		this->SetTex(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_FISH);
		this->SetCntSwitch(SWITCHCOUNT);
		break;
	case CItem::ANIM_ITEMTYPE_BEAR:
		this->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_BEAR));
		this->SetTex(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_BEAR);
		this->SetCntSwitch(SWITCHCOUNT);
		break;


	case CItem::ANIM_ITEMTYPE_DOLL:
		this->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_DOLL));
		this->SetTex(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_DOLL);
		this->SetCntSwitch(SWITCHCOUNT);
		break;
	case CItem::ANIM_ITEMTYPE_LETTER:
		this->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_LETTER));
		this->SetTex(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_LETTER);
		this->SetCntSwitch(SWITCHCOUNT);
		break;
	case CItem::ANIM_ITEMTYPE_MEDAL:
		this->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_MEDAL));
		this->SetTex(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_MEDAL);
		this->SetCntSwitch(SWITCHCOUNT);
		break;
	case CItem::ANIM_ITEMTYPE_MEDAL2:
		this->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_MEDAL2));
		this->SetTex(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_MEDAL2);
		this->SetCntSwitch(SWITCHCOUNT);
		break;
	case CItem::ANIM_ITEMTYPE_COIN:
		this->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_COIN));
		this->SetTex(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_COIN);
		this->SetCntSwitch(SWITCHCOUNT);
		break;

	case CItem::ANIM_ITEMTYPE_RUBY:
		this->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_RUBY));
		this->SetTex(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_RUBY);
		this->SetCntSwitch(SWITCHCOUNT);
		break;
	case CItem::ANIM_ITEMTYPE_SAPPHIRE:
		this->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_SAPPHIRE));
		this->SetTex(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_SAPPHIRE);
		this->SetCntSwitch(SWITCHCOUNT);
		break;
	case CItem::ANIM_ITEMTYPE_TOPAZ:
		this->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_TOPAZ));
		this->SetTex(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_TOPAZ);
		this->SetCntSwitch(SWITCHCOUNT);
		break;
	case CItem::ANIM_ITEMTYPE_DANCEMONKEY:
		this->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_DANCEMONKEY));
		this->SetTex(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_DANCEMONKEY);
		this->SetCntSwitch(SWITCHCOUNT);
		break;
	case CItem::ANIM_ITEMTYPE_JUMPMONKEY:
		this->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_JUMPMONKEY));
		this->SetTex(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_JUMPMONKEY);
		this->SetCntSwitch(SWITCHCOUNT);
		break;
	case CItem::ANIM_ITEMTYPE_PRISONER:
		this->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_PRISONER));
		this->SetTex(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_PRISONER);
		this->SetCntSwitch(SWITCHCOUNT);
		break;
	}
}

// =====================================================================================================================================================================
//
// �A�C�e���̔���
//
// =====================================================================================================================================================================
void CAnimationItem::ItemCollision()
{
	// �����蔻��
	if (GetCollision() != nullptr)
	{
		// ���W�̍X�V pos
		GetCollision()->SetPos(&GetPosition());
		// �}�b�v�̃|�C���^�擾
		CMap *pMap = CManager::GetBaseMode()->GetMap();

		if (pMap)
		{
			if (GetCollision()->RayCollision(pMap, GetPosition(), m_PosOld))
			{
				if (GetBehavior() != BEHAVIOR_NONE)
				{
					// �܂����C�̔���Ɉ�x���G��Ă��Ȃ�������
					if (m_nHitRayCount <= 0)
					{
						// �A�C�e���̔��ˏ���
						ReflectionItem();
						// �d�͂̏�����
						m_fGravity = 0.0f;
					}
					else
					{
						m_Move = ZeroVector3;
					}
				}
				else
				{
					// �d�͂̏�����
					m_fGravity = 0.0f;
					m_Move = ZeroVector3;
				}

				m_nHitRayCount++;
			}
			else
			{
				if (m_nHitRayCount < 2)
				{
					// ���K��
					D3DXVec3Normalize(&m_Move, &m_Move);

					if (GetBehavior() == BEHAVIOR_BURSTS)
					{
						m_fGravity += 0.05f;
					}
					else
					{
						// �d�͂�����
						m_fGravity += 0.04f;
					}
					// �d�͂𔽉f
					GetPosition().y -= m_fGravity;
				}
			}
		}
	}
}

// =====================================================================================================================================================================
//
// ���ˏ���
//
// =====================================================================================================================================================================
void CAnimationItem::ReflectionItem()
{
	// �@���x�N�g��
	const D3DXVECTOR3 NormalV = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	// �i�s�x�N�g��
	D3DXVECTOR3 ProgressV = m_PosOld - GetPosition();
	// ���C�̔���ɂɐG�ꂽ�Ƃ��i�s�x�N�g����@���x�N�g���̕����ɕϊ�����
	ReflectingVectorCalculation(&m_Move, ProgressV, NormalV);
}

// =====================================================================================================================================================================
//
// �_�ŏ���
//
// =====================================================================================================================================================================
void CAnimationItem::Flashing()
{
	CItem::Flashing();

	// �]�肪0�̎������ɂ���
	if (m_nColCnt % 30 == 0)
	{
		this->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}
	// �]�肪0�̎��ʏ��Ԃɂ���
	else if (m_nColCnt % 15 == 0)
	{
		this->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	// �K�莞�Ԃ��߂���
	if (m_nColCnt >= GetItem_Data().nFlashTime)
	{
		// �A�C�e���̍폜
		Rerease();
		// �ϐ��̏�����
		m_nColCnt = 0;
	}
}

// =====================================================================================================================================================================
//
// �؍ݎ��Ԃ��v�Z��0�ɂȂ�����폜����
//
// =====================================================================================================================================================================
void CAnimationItem::RemainTimer()
{
	// �A�C�e���̑؍ݎ��Ԃ�����
	CItem::RemainTimer();

	// �c�莞�Ԃ�0�ȉ��ɂȂ�����폜
	if (GetRemainTime() <= 0)
	{
		// �_�ł�����
		Flashing();
	}
}

// =====================================================================================================================================================================
//
// �A�C�e������������������
//
// =====================================================================================================================================================================
void CAnimationItem::HitItem(ITEMTYPE type, TAG Tag)
{
	// �A�C�e������������������
	CItem::HitItem(type, Tag);

	// �A�C�e���擾�G�t�F�N�g���o��
	CParticle::CreateFromText(GetPosition(), ZeroVector3, CParticleParam::EFFECT_GETWEAPON);
	// �폜
	Rerease();
}

// =====================================================================================================================================================================
//
// �A�C�e���擾���̎�ޕʏ���
//
// =====================================================================================================================================================================
void CAnimationItem::ItemAcquisition(ITEMTYPE type, TAG Tag)
{
	// �A�C�e���̎�ނ��Ƃ̏���
	switch (type)
	{
	case CItem::ANIM_ITEMTYPE_ROASTCHICKEN:
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_ANI_FOOD), (int)Tag);
		break;
	case CItem::ANIM_ITEMTYPE_FISH:
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_ANI_FOOD), (int)Tag);
		break;
	case CItem::ANIM_ITEMTYPE_BEAR:
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_ANI_BEAR), (int)Tag);
		break;
	case CItem::ANIM_ITEMTYPE_DOLL:
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_ANI_BEAR), (int)Tag);
		break;
	case CItem::ANIM_ITEMTYPE_LETTER:
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_ANI_LETTER), (int)Tag);
		break;
	case CItem::ANIM_ITEMTYPE_MEDAL:
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_ANI_MEDAL), (int)Tag);
		break;
	case CItem::ANIM_ITEMTYPE_MEDAL2:
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_ANI_MEDAL), (int)Tag);
		break;
	case CItem::ANIM_ITEMTYPE_COIN:
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_GCOIN), (int)Tag);
		break;
	case CItem::ANIM_ITEMTYPE_RUBY:
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_ANI_JEWELRY), (int)Tag);
		break;
	case CItem::ANIM_ITEMTYPE_SAPPHIRE:
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_ANI_JEWELRY), (int)Tag);
		break;
	case CItem::ANIM_ITEMTYPE_TOPAZ:
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_ANI_JEWELRY), (int)Tag);
		break;
	case CItem::ANIM_ITEMTYPE_DANCEMONKEY:
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_ANI_MONKEY), (int)Tag);
		break;
	case CItem::ANIM_ITEMTYPE_JUMPMONKEY:
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_ANI_MONKEY), (int)Tag);
		break;
	case CItem::ANIM_ITEMTYPE_PRISONER:
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		CItem::GetPlayer((int)Tag)->SetLife(GetPlayer((int)Tag)->GetLife() + 1);
		break;
	}

	CItem::ItemAcquisition(type, Tag);
}


// =====================================================================================================================================================================
//
// �L�����N�^�[���A�C�e���𗎂Ƃ��Ƃ��̐������� �m�肵�Ȃ��Ȃ�type��NONE������
//
// =====================================================================================================================================================================
CAnimationItem * CAnimationItem::DropItem(D3DXVECTOR3 droppos, bool fixed, ITEMTYPE type)
{
	// �������̊m��
	CAnimationItem *pItem = new CAnimationItem(OBJTYPE_ANIMATIONITEM);

	// ������
	pItem->Init();
	// �T�C�Y�̐ݒ�
	pItem->SetSize(D3DXVECTOR3(
		pItem->GetItem_Data().CollisionSize.x / 2,
		pItem->GetItem_Data().CollisionSize.y / 2,
		pItem->GetItem_Data().CollisionSize.z / 2));

	// �A�C�e�������������ʒu�̒���
	//pItem->SetDropPos(droppos);

	droppos.y += 30.0f;
	droppos.z = 0.0f;
	// �A�C�e���̈ʒu�̐ݒ�
	pItem->SetPosition(droppos);

	pItem->SetBehavior(BEHAVIOR_NONE);

	// �A�C�e���̃h���b�v���p�^�[�����Ƃɕς���
	pItem->DropPattern(fixed, type);

	// ��ޕʂɃe�N�X�`����ݒ�
	pItem->SwitchTexture(pItem->GetItemType());

	return pItem;
}

// =====================================================================================================================================================================
//
// �A�C�e���𕡐���C�Ƀh���b�v�����鎞
//
// =====================================================================================================================================================================
void CAnimationItem::DropItem_Multiple(const D3DXVECTOR3 originpos, ITEM_LIST_DROPMULTIPLE type, ITEM_BEHAVIOR behavior)
{
	int nForNum = MULTIPLE_ITEM_NUM;

	if (behavior == BEHAVIOR_FULLBURSTS)
	{
		nForNum = MULTIPLE_ITEM_NUM*2;
	}

	// �������鐔��
	for (int nNum = 0; nNum < nForNum; nNum++)
	{
		// �������̊m��
		CAnimationItem *pItem = new CAnimationItem(OBJTYPE_ANIMATIONITEM);

		// ������
		pItem->Init();

		// �T�C�Y�̐ݒ�
		pItem->SetSize(D3DXVECTOR3(
			pItem->GetItem_Data().CollisionSize.x / 2,
			pItem->GetItem_Data().CollisionSize.y / 2,
			pItem->GetItem_Data().CollisionSize.z / 2));

		// �؂��痎����A�C�e������
		if (behavior == BEHAVIOR_FREEFALL)
		{
			pItem->SetPosition(pItem->RandomDropPosX(originpos, 100));
		}
		// ���̑��͌��_���W����ɂ���
		else
		{
			if (behavior == BEHAVIOR_BURSTS)
			{
				D3DXVECTOR3 pos = originpos;
				pItem->SetPosition(D3DXVECTOR3(pos.x, pos.y + 50, pos.z));

			}
			else
			{
				D3DXVECTOR3 pos = originpos;
				pItem->SetPosition(D3DXVECTOR3(pos.x, pos.y, 0.0f));
			}
		}

		// �����̐ݒ�
		pItem->SetBehavior(behavior);

		// �����̂̃^�C�v�ݒ�
		pItem->SetMultiType(type);

		// �A�C�e���̋����Ǝ�ނ̐ݒ�
		pItem->DropPattern_Multiple(type, behavior, nNum);
	}
}
