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
#include "gate.h"
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
LPDIRECT3DTEXTURE9 CGate::m_pTexture[TYPE_MAX] = {};		// �e�N�X�`���ւ̃|�C���^
CLoad	*CGate::m_pload = NULL;								// ���[�h
int		CGate::m_nAll = 0;									// �ԍ�

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CGate::CGate() : CScene_THREE::CScene_THREE(ACTOR_GATE, LAYER_3DOBJECT)
{
	// �ϐ��̏�����
	m_Type = TYPE_TURN_R;
	m_UseType = USETYPE_TITLE;
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CGate::~CGate()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CGate::Init(void)
{
	// �V�[��3D�̏�����
	CScene_THREE::Init();
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CGate::Uninit(void)
{
	CScene_THREE::Uninit();
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CGate::Update(void)
{
	// �ϐ��錾
	CPlayer *pPlayer = NULL;	// �v���C���[
								// ���擾
	for (int nCntlayer = 0; nCntlayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntlayer++)
	{
		if (pPlayer = (CPlayer *)CScene::GetActor(CScene::ACTOR_PLAYER, CScene::LAYER_3DOBJECT, nCntlayer)) break;
	}

	// �A�C�e���̎擾
	if (CCalculation::Collision_Circle(
		GetPos(),					// �����̈ʒu
		60.0f, 						// �����̔��a
		pPlayer->GetPos(), 			// ����̈ʒu
		PLAYERCOLLISION_SIZE))		// ����̔��a
	{
		// SE��炷
		//CManager::GetSound()->PlaySound(CSound::LABEL_SE_7);

		if (CManager::GetMode() == CManager::MODE_TITLE)
		{
			// �Q�[�����[�h�ɑJ��
			CManager::GetFade()->SetFade(CManager::MODE_GAME);
		}
		else if (CManager::GetMode() == CManager::MODE_GAME)
		{
			// �Q�[�����[�h�ɑJ��
			CManager::GetFade()->SetFade(CManager::MODE_TITLE);
		}

		// �G�ꂽ�������
		Release();
	}

	if (m_Type == TYPE_TURN_R)
	{
		CScene_THREE::SetRot(CScene_THREE::GetRot() + D3DXVECTOR3(0.0f, 0.0f, 0.01f));

	}
	else
	{
		CScene_THREE::SetRot(CScene_THREE::GetRot() - D3DXVECTOR3(0.0f, 0.0f, 0.01f));
	}

	CScene_THREE::Update();
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CGate::Draw(void)
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
void CGate::SetTexture(TYPE type)
{
	// �ݒ�
	CScene_THREE::BindTexture(m_pTexture[type]);	// �e�N�X�`���[
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
CGate * CGate::Create()
{
	// �ϐ��錾
	CGate * pStartingPoint;		// �V�[��3D�N���X
											// �������̐���(����->��{�N���X,��->�h���N���X)
	pStartingPoint = new CGate();
	// ����������
	pStartingPoint->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pStartingPoint;
}

// ----------------------------------------
// �ǂݍ��ݍ쐬����
// ----------------------------------------
void CGate::LoadCreate(void)
{
	// �ϐ��錾
	CGate * pGate;	// �u���b�N
										// �u���b�N
	for (int nCntItem = 0; nCntItem < USETYPE_MAX; nCntItem++)
	{
		if (CManager::GetMode() == CManager::MODE_TITLE)
		{
			pGate = CGate::Create();						// ����
			pGate->SetTexture((TYPE)m_pload->GetInfo(nCntItem).nType);
			pGate->m_Type = (TYPE)m_pload->GetInfo(nCntItem).nType;
			pGate->SetPos(m_pload->GetInfo(nCntItem).pos);		// �ʒu
			pGate->SetRot(m_pload->GetInfo(nCntItem).rot);		// ��]
			pGate->SetSize(m_pload->GetInfo(nCntItem).size);	// �T�C�Y
			pGate->SetCol(m_pload->GetInfo(nCntItem).col);	// �F
		}
		else if (CManager::GetMode() == CManager::MODE_GAME)
		{
			pGate = CGate::Create();						// ����
			pGate->SetTexture((TYPE)m_pload->GetInfo(nCntItem + 2).nType);
			pGate->m_Type = (TYPE)m_pload->GetInfo(nCntItem + 2).nType;
			pGate->SetPos(m_pload->GetInfo(nCntItem + 2).pos);		// �ʒu
			pGate->SetRot(m_pload->GetInfo(nCntItem + 2).rot);		// ��]
			pGate->SetSize(m_pload->GetInfo(nCntItem + 2).size);	// �T�C�Y
			pGate->SetCol(m_pload->GetInfo(nCntItem + 2).col);	// �F
		}

	}
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT CGate::Load(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =					// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();
	char cTex[TYPE_MAX][128] =					// �e�N�X�`���[��
	{
		"data/TEXTURE/UI/StartPoint.png",
		"data/TEXTURE/GAME/key01.png",
	};

	// �e�N�X�`���[�ݒ�
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, cTex[nCnt], &m_pTexture[nCnt]);
	}
	// ���[�h����
	m_pload = new CLoad;
	// ���[�h�ǂݍ���
	m_nAll = m_pload->Load("data/LOAD/OBJECT/Gate_Location.txt");

	return S_OK;
}

// ----------------------------------------
// unload����
// ----------------------------------------
void CGate::UnLoad(void)
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
CLoad * CGate::GetLoad(void)
{
	return m_pload;
}

// ----------------------------------------
// �ʒu�̐ݒ菈��
// ----------------------------------------
void CGate::SetPos(D3DXVECTOR3 pos)
{
	CScene_THREE::SetPos(pos);
}

// ----------------------------------------
// �T�C�Y�ݒ菈��
// ----------------------------------------
void CGate::SetSize(D3DXVECTOR3 size)
{
	CScene_THREE::SetSize(size);
}

// ----------------------------------------
// ��]�̐ݒ菈��
// ----------------------------------------
void CGate::SetRot(D3DXVECTOR3 rot)
{
	CScene_THREE::SetRot(rot);
}
// ----------------------------------------
// �F�̐ݒ菈��
// ----------------------------------------
void CGate::SetCol(D3DXCOLOR col)
{
	CScene_THREE::SetCol(col);
}

// ----------------------------------------
// �\���e�N�X�`���[�ݒ菈��
// ----------------------------------------
void CGate::SetTex(D3DXVECTOR2 first, D3DXVECTOR2 last)
{
}

// ----------------------------------------
// �T�C�Y�̎擾����
// ----------------------------------------
D3DXVECTOR3 CGate::GetSize(void)
{
	return CScene_THREE::GetSize();
}

// ----------------------------------------
// ��]�̎擾����
// ----------------------------------------
D3DXVECTOR3 CGate::GetRot(void)
{
	return CScene_THREE::GetRot();
}

// ----------------------------------------
// �ʒu�̎擾����
// ----------------------------------------
D3DXVECTOR3 CGate::GetPos(void)
{
	return CScene_THREE::GetPos();
}
