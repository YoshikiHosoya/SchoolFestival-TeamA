// ----------------------------------------
//
// �X�^�[�g�n�_�����̐���[startingpoint.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "startingpoint.h"
#include "player.h"
#include "fade.h"
// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------

// ----------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------
LPDIRECT3DTEXTURE9 CStartingPoint::m_pTexture[TYPE_MAX] = {};		// �e�N�X�`���ւ̃|�C���^
CLoad	*CStartingPoint::m_pload = NULL;								// ���[�h
int		CStartingPoint::m_nAll = 0;									// �ԍ�

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CStartingPoint::CStartingPoint()
{
	// �ϐ��̏�����
	m_Type = TYPE_TURN_R;
	m_fLengh = 0;
	m_fAngle = 0;
	m_bBillboard = false;
}

// ----------------------------------------
// �C�j�V�����C�U�R���X�g���N�^
// ----------------------------------------
CStartingPoint::CStartingPoint(ACTOR actor, LAYER layer) : CScene_THREE::CScene_THREE(actor, layer)
{
	// �ϐ��̏�����
	m_fLengh = 0;
	m_fAngle = 0;
	m_bBillboard = false;
	m_Type = TYPE_TURN_R;
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CStartingPoint::~CStartingPoint()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CStartingPoint::Init(void)
{
	// �V�[��3D�̏�����
	CScene_THREE::Init();
	//CScene_THREE::SetBillboard(true);				// �r���{�[�h
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CStartingPoint::Uninit(void)
{
	CScene_THREE::Uninit();
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CStartingPoint::Update(void)
{
	// �ϐ��錾
	CPlayer *pPlayer = NULL;	// �v���C���[
							// ���擾
	for (int nCntlayer = 0; nCntlayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntlayer++)
	{
		if (pPlayer = (CPlayer *)CScene::GetActor(CScene::ACTOR_PLAYER, CScene::LAYER_3DOBJECT, nCntlayer)) break;
	}

	//if (CCalculation::Cube_Juge(
	//	GetPos(),
	//	D3DXVECTOR3(150.0f,150.0f,30.0f),
	//	pPlayer->GetPos(),
	//	D3DXVECTOR3(60.0f, 60.0f, 60.0f)))
	//{
	//	// SE��炷
	//	CManager::GetSound()->PlaySound(CSound::LABEL_SE_8);
	//	CManager::GetFade()->SetFade(CManager::MODE_GAME);
	//}



	// �A�C�e���̎擾
	if (CCalculation::Collision_Circle(
		GetPos(),					// �����̈ʒu
		60.0f, 						// �����̔��a
		pPlayer->GetPos(), 			// ����̈ʒu
		PLAYERCOLLISION_SIZE))		// ����̔��a
	{
		// SE��炷
		CManager::GetSound()->PlaySound(CSound::LABEL_SE_7);
		// �Q�[�����[�h�ɑJ��
		CManager::GetFade()->SetFade(CManager::MODE_GAME);

		// �G�ꂽ�������
		Release();
	}

	CScene_THREE::SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	CScene_THREE::SetRot(CScene_THREE::GetRot() + D3DXVECTOR3(0.0f, 0.0f, 0.01f));
	CScene_THREE::Update();
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CStartingPoint::Draw(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9	pDevice;					// �f�o�C�X�̃|�C���^

	pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

													// ���C�e�B���O���[�h����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Z�o�b�t�@�@�L���@����
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_FALSE);

	// �����_�[�X�e�[�g(���Z��������)
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	// ����(�����)���J�����O����
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	CScene_THREE::Draw();

	//�A���t�@�e�X�g�߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//Z�o�b�t�@�@�L���@����
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE);
	// ���C�e�B���O���[�h�L��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	// ����(�����)���J�����O����
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// �����_�[�X�e�[�g(�ʏ�u�����h����)
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

// ----------------------------------------
// �e�N�X�`���[�ݒ菈��
// ----------------------------------------
void CStartingPoint::SetTexture(TYPE type)
{
	// �ݒ�
	CScene_THREE::BindTexture(m_pTexture[type]);	// �e�N�X�`���[
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
CStartingPoint * CStartingPoint::Create(bool bBillboard)
{
	// �ϐ��錾
	CStartingPoint * pStartingPoint;		// �V�[��3D�N���X
						// �������̐���(����->��{�N���X,��->�h���N���X)
	pStartingPoint = new CStartingPoint(ACTOR_ITEM, LAYER_3DOBJECT);
	// �r���{�[�h�̂����邩�ǂ���
	pStartingPoint->m_bBillboard = bBillboard;
	// ����������
	pStartingPoint->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pStartingPoint;
}

// ----------------------------------------
// �ǂݍ��ݍ쐬����
// ----------------------------------------
void CStartingPoint::LoadCreate(void)
{
	// �ϐ��錾
	CStartingPoint * pStartingPoint;	// �u���b�N
					// �u���b�N
	for (int nCntItem = 0; nCntItem < m_nAll; nCntItem++)
	{
		pStartingPoint = CStartingPoint::Create(true);						// ����
		pStartingPoint->SetTexture((TYPE)m_pload->GetInfo(nCntItem).nType);
		pStartingPoint->m_Type = (TYPE)m_pload->GetInfo(nCntItem).nType;
		pStartingPoint->SetPos(m_pload->GetInfo(nCntItem).pos);		// �ʒu
		pStartingPoint->SetRot(m_pload->GetInfo(nCntItem).rot);		// ��]
		pStartingPoint->SetSize(m_pload->GetInfo(nCntItem).size);	// �T�C�Y
	}
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT CStartingPoint::Load(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =					// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();
	char cTex[TYPE_MAX][128] =					// �e�N�X�`���[��
	{
		"data/TEXTURE/UI/StartPoint.png",
		"data/TEXTURE/UI/StartPoint.png",
	};

	// �e�N�X�`���[�ݒ�
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, cTex[nCnt], &m_pTexture[nCnt]);
	}
	// ���[�h����
	m_pload = new CLoad;
	// ���[�h�ǂݍ���
	m_nAll = m_pload->Load("data/LOAD/OBJECT/StartPoint_Location.txt");

	return S_OK;
}

// ----------------------------------------
// unload����
// ----------------------------------------
void CStartingPoint::UnLoad(void)
{
	// �e�N�X�`���[�ݒ�
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
	// ���[�h�̔j��
	delete m_pload;
	m_pload = NULL;
}

// ----------------------------------------
// ���[�h�擾
// ----------------------------------------
CLoad * CStartingPoint::GetLoad(void)
{
	return m_pload;
}

// ----------------------------------------
// �ʒu�̐ݒ菈��
// ----------------------------------------
void CStartingPoint::SetPos(D3DXVECTOR3 pos)
{
	CScene_THREE::SetPos(pos);
}

// ----------------------------------------
// �T�C�Y�ݒ菈��
// ----------------------------------------
void CStartingPoint::SetSize(D3DXVECTOR3 size)
{
	CScene_THREE::SetSize(size);
}

// ----------------------------------------
// ��]�̐ݒ菈��
// ----------------------------------------
void CStartingPoint::SetRot(D3DXVECTOR3 rot)
{
	CScene_THREE::SetRot(rot);
}
// ----------------------------------------
// �F�̐ݒ菈��
// ----------------------------------------
void CStartingPoint::SetCol(D3DXCOLOR col)
{
}

// ----------------------------------------
// �\���e�N�X�`���[�ݒ菈��
// ----------------------------------------
void CStartingPoint::SetTex(D3DXVECTOR2 first, D3DXVECTOR2 last)
{
}

// ----------------------------------------
// �T�C�Y�̎擾����
// ----------------------------------------
D3DXVECTOR3 CStartingPoint::GetSize(void)
{
	return CScene_THREE::GetSize();
}

// ----------------------------------------
// ��]�̎擾����
// ----------------------------------------
D3DXVECTOR3 CStartingPoint::GetRot(void)
{
	return CScene_THREE::GetRot();
}

// ----------------------------------------
// �ʒu�̎擾����
// ----------------------------------------
D3DXVECTOR3 CStartingPoint::GetPos(void)
{
	return CScene_THREE::GetPos();
}
