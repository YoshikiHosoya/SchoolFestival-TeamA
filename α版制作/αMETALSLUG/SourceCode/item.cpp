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
	m_pCollision = nullptr;
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CItem::~CItem()
{
#ifdef _DEBUG

	// �����蔻��̍폜
	if (m_pCollision != nullptr)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}
#endif // _DEBUG

}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
HRESULT CItem::Init()
{
	// �ϐ�������
	m_Type = ITEMTYPE_HEAVYMACHINEGUN;			// �^�C�v

	// ������
	CScene3D::Init();

	// �����蔻�萶��
	m_pCollision = CCollision::Create();
	m_pCollision->SetPos(&GetPosition());
	m_pCollision->SetSize2D(ITEM_COLLISION_SIZE_XY);
	m_pCollision->SetMove(nullptr);
	m_pCollision->SetType(CCollision::COLLISION_ITEM);
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

	// �}�b�v�̃|�C���^�擾
	CMap *pMap;
	pMap = CManager::GetBaseMode()->GetMap();

	// �}�b�v���f�������݂�����
	if (pMap != nullptr)
	{
		// ���C�̔���
		if (m_pCollision->RayCollision(pMap))
		{
			// �e�̍폜
			Rerease();
		}
		else
		{
		}
	}

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

	//CHossoLibrary::SetBillboard(&mtxView);
	// �t�s��
	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;

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
		//�w�r�[�}�V���K��
	case (ITEMTYPE_HEAVYMACHINEGUN): {
		pPlayer->GetGun()->SetGunType(CGun::GUNTYPE_HEAVYMACHINEGUN);
	}break;

		//�V���b�g�K��
	case (ITEMTYPE_SHOTGUN): {
		pPlayer->GetGun()->SetGunType(CGun::GUNTYPE_SHOTGUN);
	}break;

		//���[�U�[�K��
	case (ITEMTYPE_LASERGUN): {
		pPlayer->GetGun()->SetGunType(CGun::GUNTYPE_LASERGUN);
	}break;

		//���P�b�g�����`���[
	case (ITEMTYPE_ROCKETLAUNCHER): {
		pPlayer->GetGun()->SetGunType(CGun::GUNTYPE_ROCKETLAUNCHER);
	}break;

		//�t���C���V���b�g
	case (ITEMTYPE_FLAMESHOT): {
		pPlayer->GetGun()->SetGunType(CGun::GUNTYPE_FLAMESHOT);
	}break;

		//�F
	case (ITEMTYPE_BEAR): {
		// �X�R�A�A�b�v
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
// ��������
//
// =====================================================================================================================================================================
CItem * CItem::Create(D3DXVECTOR3 pos, ITEMTYPE type)
{
	// �ϐ�
	CItem *pItem;

	// �������̊m��
	pItem = new CItem(OBJTYPE_ITEM);

	// ������
	pItem->Init();

	// �T�C�Y�̐ݒ�
	pItem->SetSize(ITEM_SIZE_XY);

	// �A�C�e���̈ʒu�̐ݒ�
	pItem->SetPosition(pos);

	// �A�C�e���̃^�C�v��ݒ�
	pItem->m_Type = type;

	// ��ޕʂɃe�N�X�`����ݒ�
	pItem->SwitchTexture(type,	pItem);

	return pItem;
}

// =====================================================================================================================================================================
//
// �ߗ��p��������
//
// =====================================================================================================================================================================
CItem * CItem::RandCreate(const D3DXVECTOR3 pos)
{
	// �ϐ�
	CItem *pItem;

	// �������̊m��
	pItem = new CItem(OBJTYPE_ITEM);

	// ������
	pItem->Init();

	// �T�C�Y�̐ݒ�
	pItem->SetSize(ITEM_SIZE_XY);

	// �A�C�e���̈ʒu�̐ݒ�
	pItem->SetPosition(pos);

	// �A�C�e���̃^�C�v�������_���ɐݒ�
	pItem->m_Type = RandDropItem();

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

	default:
		break;
	}
}

// =====================================================================================================================================================================
//
// �h���b�v����A�C�e���̃����_������
//
// =====================================================================================================================================================================
CItem::ITEMTYPE CItem::RandDropItem()
{
	return ITEMTYPE(rand() % ITEMTYPE_MAX);
}
