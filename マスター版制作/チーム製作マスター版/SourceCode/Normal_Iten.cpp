// =====================================================================================================================================================================
//
// �ʏ�̃A�C�e������[normal_item.cpp]
// Author : Fujiwara Masato
//
// =====================================================================================================================================================================

// =====================================================================================================================================================================
//�C���N���[�h
// =====================================================================================================================================================================
#include "Normal_Iten.h"
#include "collision.h"
#include "basemode.h"
#include "manager.h"
#include "renderer.h"
#include "particle.h"
#include "sound.h"
#include "player.h"
#include "scoremanager.h"
#include "playerui.h"
#include "grenade.h"

// =====================================================================================================================================================================
//�ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================

// =====================================================================================================================================================================
//�}�N��
// =====================================================================================================================================================================

// =====================================================================================================================================================================
//�R���X�g���N�^
// =====================================================================================================================================================================
CNormalItem::CNormalItem(OBJ_TYPE obj) : CItem(),CScene3D(obj)
{
}
// =====================================================================================================================================================================
//�f�X�g���N�^
// =====================================================================================================================================================================
CNormalItem::~CNormalItem()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
HRESULT CNormalItem::Init()
{
	// �|���S���̐���
	CScene3D::Init();
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
void CNormalItem::Uninit(void)
{
	// �A�C�e���̏I������
	CItem::Uninit();
	// �|���S���̉��
	CScene3D::Uninit();
}

// =====================================================================================================================================================================
//
// �X�V����
//
// =====================================================================================================================================================================
void CNormalItem::Update(void)
{
	// 1�t���[���O�̍��W��ݒ�
	m_PosOld = GetPosition();

	// �A�C�e���̋������Ƃ̈ړ�
	BehaviorType(GetPosition());

	// �A�C�e���̔���
	ItemCollision();

	// ���C�̔���Ɉ��ł��G��Ă�����
	//if (m_nHitRayCount >= 1)
	//{
		// �A�C�e���̑؍ݎ��ԊǗ�
		RemainTimer();
	//}

	// ���W���X�V
	SetPosition(GetPosition());

	// �A�C�e���̍X�V
	CItem::Update();
	// �|���S���̍X�V
	CScene3D::Update();
}

// =====================================================================================================================================================================
//
// �`�揈��
//
// =====================================================================================================================================================================
void CNormalItem::Draw(void)
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
	CScene3D::Draw();

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
void CNormalItem::DebugInfo()
{
}

// =====================================================================================================================================================================
//
// ��ޕʃe�N�X�`���o�C���h����
//
// =====================================================================================================================================================================
void CNormalItem::SwitchTexture(ITEMTYPE type)
{
	switch (type)
	{
	case CItem::ITEMTYPE_HEAVYMACHINEGUN:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_HEAVYMACHINEGUN));
	break;
	case CItem::ITEMTYPE_SHOTGUN:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_SHOTGUN));
	break;
	case CItem::ITEMTYPE_LASERGUN:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_LASERGUN));
	break;
	case CItem::ITEMTYPE_ROCKETLAUNCHER:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_ROCKETLAUNCHER));
	break;
	case CItem::ITEMTYPE_FLAMESHOT:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_FLAMESHOT));
	break;
	case CItem::ITEMTYPE_GOLDCOIN:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_GOLDCOIN));
	break;
	case CItem::ITEMTYPE_SILVERCOIN:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_SILVERCOIN));
	break;
	case CItem::ITEMTYPE_BRONZESCOIN:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BRONZESCOIN));
	break;
	case CItem::ITEMTYPE_DIAMOND:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_DIAMOND));
	break;
	case CItem::ITEMTYPE_BEAR:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BEAR));
	break;
	case CItem::ITEMTYPE_LETTER:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_LETTER));
	break;
	case CItem::ITEMTYPE_APPLE:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_APPLE));
	break;
	case CItem::ITEMTYPE_MELON:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_MELON));
	break;
	case CItem::ITEMTYPE_BANANA:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BANANA));
	break;
	case CItem::ITEMTYPE_MEAT:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_MEAT));
	break;
	case CItem::ITEMTYPE_RICEBALL:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_RICEBALL));
	break;
	case CItem::ITEMTYPE_CANDY:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_CANDY));
	break;
	case CItem::ITEMTYPE_DONUT:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_DONUT));
	break;
	case CItem::ITEMTYPE_LOLIPOP:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_LOLIPOP));
	break;
	case CItem::ITEMTYPE_BREAD:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BREAD));
	break;
	case CItem::ITEMTYPE_CHOCOLATE:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_CHOCOLATE));
	break;
	case CItem::ITEMTYPE_ICE:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_ICE));
	break;
	case CItem::ITEMTYPE_BOMBUP:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BOMBUP));
	break;
	case CItem::ITEMTYPE_BULLETUP:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BULLETUP));
	break;
	}

	SetItemType(type);
}

// =====================================================================================================================================================================
//
// �A�C�e���̔���
//
// =====================================================================================================================================================================
void CNormalItem::ItemCollision()
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
			if (GetCollision()->RayCollision(pMap, m_PosOld,GetPosition()))
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
void CNormalItem::ReflectionItem()
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
void CNormalItem::Flashing()
{
	CItem::Flashing();

	// �]�肪0�̎������ɂ���
	if (m_nColCnt % 30 == 0)
	{
		this->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}
	// �]�肪0�̎��ʏ��Ԃɂ���
	else if(m_nColCnt % 15 == 0)
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
void CNormalItem::RemainTimer()
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
void CNormalItem::HitItem(ITEMTYPE type, TAG Tag)
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
void CNormalItem::ItemAcquisition(ITEMTYPE type, TAG Tag)
{
	// �A�C�e���̎�ނ��Ƃ̏���
	switch (type)
	{
		// �w�r�[�}�V���K��
	case (ITEMTYPE_HEAVYMACHINEGUN): {
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_WEAPON);
		CManager::GetSound()->Play(CSound::LABEL_SE_VOICE_HEAVYMACHINEGUN);

		CItem::GetPlayer((int)Tag)->GetGun()->SetGunType(CGun::GUNTYPE_HEAVYMACHINEGUN);
	}break;

		// �V���b�g�K��
	case (ITEMTYPE_SHOTGUN): {
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_WEAPON);
		CManager::GetSound()->Play(CSound::LABEL_SE_VOICE_SHOTGUN);

		CItem::GetPlayer((int)Tag)->GetGun()->SetGunType(CGun::GUNTYPE_SHOTGUN);
	}break;

		// ���[�U�[�K��
	case (ITEMTYPE_LASERGUN): {
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_WEAPON);
		CManager::GetSound()->Play(CSound::LABEL_SE_VOICE_LAZERGUN);

		CItem::GetPlayer((int)Tag)->GetGun()->SetGunType(CGun::GUNTYPE_LASERGUN);
	}break;

		// ���P�b�g�����`���[
	case (ITEMTYPE_ROCKETLAUNCHER): {
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_WEAPON);
		CManager::GetSound()->Play(CSound::LABEL_SE_VOICE_ROCKETLAUNCHER);

		CItem::GetPlayer((int)Tag)->GetGun()->SetGunType(CGun::GUNTYPE_ROCKETLAUNCHER);
	}break;

		// �t���C���V���b�g
	case (ITEMTYPE_FLAMESHOT): {
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_WEAPON);
		CManager::GetSound()->Play(CSound::LABEL_SE_VOICE_FLAMESHOT);

		CItem::GetPlayer((int)Tag)->GetGun()->SetGunType(CGun::GUNTYPE_FLAMESHOT);
	}break;

		// ����
	case (ITEMTYPE_GOLDCOIN): {
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_GCOIN), (int)Tag);
	}break;

		// ���
	case (ITEMTYPE_SILVERCOIN): {
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_SCOIN), (int)Tag);
	}break;

		// ����
	case (ITEMTYPE_BRONZESCOIN): {
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_BCOIN), (int)Tag);
	}break;

		// �_�C�A�����h
	case (ITEMTYPE_DIAMOND): {
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_DIAMOND), (int)Tag);
	}break;
		// �F
	case (ITEMTYPE_BEAR): {
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_BEAR), (int)Tag);
	}break;

		// �莆
	case (ITEMTYPE_LETTER): {
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_LETTER), (int)Tag);

	}break;

		// �����S
	case ITEMTYPE_APPLE:
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FRUIT), (int)Tag);
		break;
		// ������
	case ITEMTYPE_MELON:
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FRUIT), (int)Tag);
		break;
		// �o�i�i
	case ITEMTYPE_BANANA:
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FRUIT), (int)Tag);
		break;


		// ��
	case ITEMTYPE_MEAT:
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD), (int)Tag);
		break;
		// ���ɂ���
	case (ITEMTYPE_RICEBALL):
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD), (int)Tag);
		break;
		// ��
	case (ITEMTYPE_CANDY):
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD), (int)Tag);
		break;
		// �h�[�i�c
	case (ITEMTYPE_DONUT):
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD), (int)Tag);
		break;
		// �����|�b�v
	case (ITEMTYPE_LOLIPOP):
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD), (int)Tag);
		break;
		// �F
	case (ITEMTYPE_BREAD):
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD), (int)Tag);
		break;
		// �`���R���[�g
	case (ITEMTYPE_CHOCOLATE):
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD), (int)Tag);
		break;
		// �A�C�X
	case (ITEMTYPE_ICE):
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD), (int)Tag);
		break;

		// ���e�̐��𑝂₷
	case (ITEMTYPE_BOMBUP): {
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_WEAPON);
		CItem::GetPlayer((int)Tag)->GetGrenadeFire()->GrenadeAddAmmo();
	}break;

		// �n���h�K���ȊO�̒e�̎c�e���𑝂₷
	case (ITEMTYPE_BULLETUP): {
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_WEAPON);
		CItem::GetPlayer((int)Tag)->GetGun()->GunAddAmmo(CItem::GetPlayer((int)Tag)->GetGun()->GetGunType());
	}break;
	}

	CItem::ItemAcquisition(type, Tag);
}


// =====================================================================================================================================================================
//
// �L�����N�^�[���A�C�e���𗎂Ƃ��Ƃ��̐������� �m�肵�Ȃ��Ȃ�type��NONE������
//
// =====================================================================================================================================================================
CNormalItem * CNormalItem::DropItem(D3DXVECTOR3 droppos, bool fixed, ITEMTYPE type)
{
	// �������̊m��
	CNormalItem *pItem = new CNormalItem(OBJTYPE_NORMALITEM);

	// ������
	pItem->Init();
	// �T�C�Y�̐ݒ�
	pItem->SetSize(D3DXVECTOR3(
		pItem->GetItem_Data().CollisionSize.x /2,
		pItem->GetItem_Data().CollisionSize.y /2,
		pItem->GetItem_Data().CollisionSize.z /2));

	// �A�C�e�������������ʒu�̒���
	//pItem->SetDropPos(droppos);

	droppos.y += 30.0f;

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
void CNormalItem::DropItem_Multiple(const D3DXVECTOR3 originpos, ITEM_LIST_DROPMULTIPLE type, ITEM_BEHAVIOR behavior)
{
	// �������鐔��
	for (int nNum = 0; nNum < MULTIPLE_ITEM_NUM; nNum++)
	{
		// �������̊m��
		CNormalItem *pItem = new CNormalItem(OBJTYPE_NORMALITEM);

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
				pItem->SetPosition(originpos);
			}
		}

		// �����̐ݒ�
		pItem->SetBehavior(behavior);

		// ���ʂȃA�C�e�����X�g���w�肳�ꂽ���̂݃A�C�e���̑I�l���@��ς���
		if (type == LIST_SPECIAL)
		{
			// �������X�g����A�C�e���������_���ɑI�ѐݒ肷��
			pItem->SwitchTexture(pItem->BoxRand());
		}
		else
		{
			// �����̂̃^�C�v�ݒ�
			pItem->SetMultiType(type);
		}

		// �A�C�e���̋����Ǝ�ނ̐ݒ�
		pItem->DropPattern_Multiple(type, behavior, nNum);
	}
}
