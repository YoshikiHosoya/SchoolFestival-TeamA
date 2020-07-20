// =====================================================================================================================================================================
//
// �A�C�e�������̐���[item.cpp]
// Author : Fujiwara Masato
//
// =====================================================================================================================================================================
#include "item.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "collision.h"
#include "debugproc.h"
#include "player.h"
#include "playerui.h"
#include "gun.h"

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define ITEM_SIZE_XY				(D3DXVECTOR3(20.0f,20.0f,0.0f))				// �A�C�e���̃T�C�Y
#define ITEM_COLLISION_SIZE_XY		(D3DXVECTOR3(40.0f,40.0f,0.0f))				// �A�C�e���̃T�C�Y

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CItem::CItem(OBJ_TYPE type) :CScene3D(type)
{
	// �����蔻��̃|�C���^
	m_pCollision = nullptr;

	// �A�C�e�����}�b�v�Ɏc�鎞��
	m_nRemainTime = 240;

	// ���J���[�J�E���g
	m_nColCnt = 0;

	// �A�C�e���̎��
	m_Type = ITEMTYPE_HEAVYMACHINEGUN;

	// �A�C�e�����h���b�v��������
	m_Drop = ITEMDROP_WEAPON;
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CItem::~CItem()
{
	// �����蔻��̍폜
	if (m_pCollision != nullptr)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
HRESULT CItem::Init()
{
	// ������
	CScene3D::Init();

	// �����蔻�萶��
	m_pCollision = CCollision::Create();
	m_pCollision->SetPos(&GetPosition());
	m_pCollision->SetSize2D(ITEM_COLLISION_SIZE_XY);
	m_pCollision->DeCollisionCreate(CCollision::COLLISIONTYPE_NORMAL);

	return S_OK;
}

// =====================================================================================================================================================================
//
// �I������
//
// =====================================================================================================================================================================
void CItem::Uninit(void)
{
	// �I������
	CScene3D::Uninit();
}

// =====================================================================================================================================================================
//
// �X�V����
//
// =====================================================================================================================================================================
void CItem::Update(void)
{
	// �����蔻��
	if (m_pCollision != nullptr)
	{
		// ���W�̍X�V pos
		m_pCollision->SetPos(&GetPosition());
	}

	// �A�C�e���̑؍ݎ��ԊǗ�
	RemainTimer();

	// �X�V
	CScene3D::Update();
}

// =====================================================================================================================================================================
//
// �`�揈��
//
// =====================================================================================================================================================================
void CItem::Draw(void)
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

	// �r���{�[�h
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
// �A�C�e���擾���̎�ޕʏ���
//
// =====================================================================================================================================================================
void CItem::ItemType(ITEMTYPE type)
{
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();

	switch (type)
	{
		// �w�r�[�}�V���K��
	case (ITEMTYPE_HEAVYMACHINEGUN): {
		pPlayer->GetGun()->SetGunType(CGun::GUNTYPE_HEAVYMACHINEGUN);
	}break;

		// �V���b�g�K��
	case (ITEMTYPE_SHOTGUN): {
		pPlayer->GetGun()->SetGunType(CGun::GUNTYPE_SHOTGUN);
	}break;

		// ���[�U�[�K��
	case (ITEMTYPE_LASERGUN): {
		pPlayer->GetGun()->SetGunType(CGun::GUNTYPE_LASERGUN);
	}break;

		// ���P�b�g�����`���[
	case (ITEMTYPE_ROCKETLAUNCHER): {
		pPlayer->GetGun()->SetGunType(CGun::GUNTYPE_ROCKETLAUNCHER);
	}break;

		// �t���C���V���b�g
	case (ITEMTYPE_FLAMESHOT): {
		pPlayer->GetGun()->SetGunType(CGun::GUNTYPE_FLAMESHOT);
	}break;

		// �F
	case (ITEMTYPE_BEAR): {
		// �X�R�A�A�b�v
		CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
		pPlayer->GetPlayerUI()->SetScore(100);
	}break;

		// ���e�̐��𑝂₷
	case (ITEMTYPE_BOMBUP): {
	}break;

		// ��蕨�̑ϋv�l���񕜂���
	case (ITEMTYPE_ENERGYUP): {
	}break;

		// �n���h�K���ȊO�̒e�̎c�e���𑝂₷
	case (ITEMTYPE_BULLETUP): {
	}break;

	default:
		break;
	}
}
// =====================================================================================================================================================================
//
// �f�o�b�O
//
// =====================================================================================================================================================================
void CItem::DebugInfo()
{
}

// =====================================================================================================================================================================
//
// �A�C�e������������������
//
// =====================================================================================================================================================================
void CItem::HitItem(ITEMTYPE type)
{
	// ��ނ��Ƃ̏���
	ItemType(type);
	// �폜
	Rerease();
}

// =====================================================================================================================================================================
//
// �A�C�e���𗎂Ƃ��ʒu�̐ݒ�
//
// =====================================================================================================================================================================
void CItem::SetDropPos(D3DXVECTOR3 &characterpos)
{
	// �v���C���[�̃|�C���^�擾
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
	// �v���C���[�����݂�����
	if (pPlayer != nullptr)
	{
		// �v���C���[�̌������擾
		if (pPlayer->GetCharacterDirection() == CPlayer::CHARACTER_LEFT)
		{
			characterpos.x -= 50;
		}
		else if(pPlayer->GetCharacterDirection() == CPlayer::CHARACTER_RIGHT)
		{
			characterpos.x += 50;
		}

		characterpos.y += 50;
	}
}

// =====================================================================================================================================================================
//
// �؍ݎ��Ԃ��v�Z��0�ɂȂ�����폜����
//
// =====================================================================================================================================================================
void CItem::RemainTimer()
{
	// �A�C�e���̑؍ݎ��Ԃ�����
	m_nRemainTime--;

	// �c�莞�Ԃ�0�ȉ��ɂȂ�����폜
	if (m_nRemainTime <= 0)
	{
		// �_�ł�����
		Flashing();
	}
}

// =====================================================================================================================================================================
//
// �_�ŏ���
//
// =====================================================================================================================================================================
void CItem::Flashing()
{
	// �J�E���g���Z
	m_nColCnt++;
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

	// 3�b�ȏ�o�߂�����A�C�e�����폜����
	if (m_nColCnt >= 180)
	{
		// �ϐ��̏�����
		m_nColCnt = 0;
		// �폜
		Rerease();
	}
}

// =====================================================================================================================================================================
//
// �����_���@�͈͎w��
//
// =====================================================================================================================================================================
CItem::ITEMTYPE CItem::RandomRange(ITEMTYPE min, ITEMTYPE max)
{
	// �͈͂Ń����_���ɒl�����ߒl��Ԃ�
	return (ITEMTYPE)(min + (int)(rand()*(max - min + 1.0) / (1.0 + RAND_MAX)));
}

// =====================================================================================================================================================================
//
// �����_���֐�
//
// =====================================================================================================================================================================
int CItem::ItemRand(int max)
{
	// ������߂�
	int nAdjusted_max = (RAND_MAX + 1) - (RAND_MAX + 1) % max;

	// �����_���ɋ��߂��l���i�[�����r�p�ϐ�
	int nRandom = 0;

	// RAND_MAX + 1 �� max �Ŋ���؂�Ȃ��ꍇ�A���������̒[�����͈̔͂ɂȂ�����̂ĂĂ�蒼��
	do {
		// �����_���ɒl�����߂�
		nRandom = rand();
	} while (nRandom >= nAdjusted_max);

	return (int)(((float)nRandom / nAdjusted_max) * max);
}

// =====================================================================================================================================================================
//
// �L�����N�^�[���A�C�e���𗎂Ƃ��Ƃ��̐�������
//
// =====================================================================================================================================================================
CItem * CItem::DropCreate(D3DXVECTOR3 pos, ITEMDROP drop)
{
	// �ϐ�
	CItem *pItem;

	// �������̊m��
	pItem = new CItem(OBJTYPE_ITEM);

	// ������
	pItem->Init();

	// �T�C�Y�̐ݒ�
	pItem->SetSize(ITEM_SIZE_XY);

	// �A�C�e�������������ʒu�̒���
	pItem->SetDropPos(pos);

	// �A�C�e���̈ʒu�̐ݒ�
	pItem->SetPosition(pos);

	// �A�C�e���̃^�C�v�������_���ɐݒ�
	pItem->m_Type = RandDropItem(drop);

	// ��ޕʂɃe�N�X�`����ݒ�
	pItem->SwitchTexture(pItem->m_Type, pItem);

	return pItem;
}

// =====================================================================================================================================================================
//
// ��ޕʃe�N�X�`���o�C���h����
//
// =====================================================================================================================================================================
void CItem::SwitchTexture(ITEMTYPE type, CItem *pItem)
{
	switch (type)
	{
		//�w�r�[�}�V���K��
	case (ITEMTYPE_HEAVYMACHINEGUN):{
		// �e�N�X�`���̊��蓖��
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_HEAVYMACHINEGUN));
	}break;

		//�V���b�g�K��
	case (ITEMTYPE_SHOTGUN): {
		// �e�N�X�`���̊��蓖��
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_SHOTGUN));
	}break;

		//���[�U�[�K��
	case (ITEMTYPE_LASERGUN): {
		// �e�N�X�`���̊��蓖��
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_LASERGUN));
	}break;

		//���P�b�g�����`���[
	case (ITEMTYPE_ROCKETLAUNCHER): {
		// �e�N�X�`���̊��蓖��
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_ROCKETLAUNCHER));
	}break;

		//�t���C���V���b�g
	case (ITEMTYPE_FLAMESHOT): {
		// �e�N�X�`���̊��蓖��
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_FLAMESHOT));
	}break;

		//�F
	case (ITEMTYPE_BEAR): {
		// �e�N�X�`���̊��蓖��
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BEAR));
	}break;

		// ���e�̐��𑝂₷
	case (ITEMTYPE_BOMBUP): {
		// �e�N�X�`���̊��蓖��
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BOMBUP));
	}break;

		// ��蕨�̑ϋv�l���񕜂���
	case (ITEMTYPE_ENERGYUP): {
		// �e�N�X�`���̊��蓖��
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_ENERGYUP));
	}break;

		// �n���h�K���ȊO�̒e�̎c�e���𑝂₷
	case (ITEMTYPE_BULLETUP): {
		// �e�N�X�`���̊��蓖��
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BULLETUP));
	}break;

	default:
		break;
	}
}

// =====================================================================================================================================================================
//
// �h���b�v����A�C�e���̃����_������
//
// =====================================================================================================================================================================
CItem::ITEMTYPE CItem::RandDropItem(ITEMDROP drop)
{
	// �l��Ԃ����߂̕ϐ�
	ITEMTYPE type;
	// �����ɂ���ăh���b�v������A�C�e���̎�ނɐ�����������
	switch (drop)
	{
		// ����݂̂̏ꍇ
	case CItem::ITEMDROP_WEAPON:
		// �����_���͈̔͂𕐊�݂̂ɑI��
		type = RandomRange(ITEMTYPE_HEAVYMACHINEGUN, ITEMTYPE_FLAMESHOT);
		break;

		// �X�R�A�A�b�v�݂̂̏ꍇ
	case CItem::ITEMDROP_SCORE:
		// �����_���͈̔͂��X�R�A�A�C�e���݂̂ɑI��
		type = RandomRange(ITEMTYPE_BEAR, ITEMTYPE_BULLETUP);
		break;

		// �S�ẴA�C�e��
	case CItem::ITEMDROP_ALL:
		type = ITEMTYPE(rand() % ITEMTYPE_MAX);
		break;
	default:
		break;
	}

	return type;
}

// =====================================================================================================================================================================
//
// �A�C�e�����h���b�v����m�������߂�
//
// =====================================================================================================================================================================
bool CItem::DropRate()
{
	// �A�C�e�����h���b�v���邩�̃t���O
	bool bDrop = false;

	// ���߂��h���b�v�����i�[����ϐ�
	int nDrop = 0;

	// �h���b�v����\���ϐ�
	int nRate = 4;

	// �����_���Ƀh���b�v���邩�����߂�
	nDrop = ItemRand(nRate);

	// ���ʂ�0�Ȃ�A�C�e�����h���b�v���鋖���o��
	if (nDrop == 0)
	{
		bDrop = true;
	}

	// ���ʂ�����ȊO�Ȃ�A�C�e�����h���b�v���鋖���o���Ȃ�
	else
	{
		bDrop = false;
	}

	// ���ʂ�Ԃ�
	return bDrop;
}
