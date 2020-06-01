// ----------------------------------------
//
// ���[�v�Q�[�g�����̐���[warp.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "warp.h"
#include "player.h"
#include "fade.h"
#include "debugproc.h"
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
LPDIRECT3DTEXTURE9 CWarp::m_pTexture[TYPE_MAX] = {};		// �e�N�X�`���ւ̃|�C���^
CLoad	*CWarp::m_pload = NULL;								// ���[�h
int		CWarp::m_nAll = 0;									// �ԍ�

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CWarp::CWarp()
{
	// �ϐ��̏�����
	m_Type = TYPE_ENTRANCE;
}

// ----------------------------------------
// �C�j�V�����C�U�R���X�g���N�^
// ----------------------------------------
CWarp::CWarp(ACTOR actor, LAYER layer) : CScene_THREE::CScene_THREE(actor, layer)
{
	// �ϐ��̏�����
	m_Type = TYPE_ENTRANCE;
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CWarp::~CWarp()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CWarp::Init(void)
{
	// �V�[��3D�̏�����
	CScene_THREE::Init();
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CWarp::Uninit(void)
{
	CScene_THREE::Uninit();
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CWarp::Update(void)
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
		50, 		// �����̔��a
		pPlayer->GetPos(), 			// ����̈ʒu
		PLAYERCOLLISION_SIZE))		// ����̔��a
	{
		if (m_Type == TYPE_ENTRANCE)
		{
			//pPlayer->SetRotPos(0, 1);
		}
		else if (m_Type == TYPE_EXIT)
		{
			//pPlayer->SetRotPos(1, 0);
		}

		// SE��炷
		//CManager::GetSound()->PlaySound(CSound::LABEL_SE_8);
		//CManager::GetFade()->SetFade(CManager::MODE_GAME);
	}

	CScene_THREE::SetRot(CScene_THREE::GetRot() + D3DXVECTOR3(0.0f, 0.0f, 0.01f));
	CScene_THREE::Update();

	CDebugproc::Print("���W		: %.2f,%.2f,%.2f\n", GetPos().x, GetPos().y, GetPos().z);
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CWarp::Draw(void)
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
void CWarp::SetTexture(TYPE type)
{
	// �ݒ�
	CScene_THREE::BindTexture(m_pTexture[type]);	// �e�N�X�`���[
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
CWarp * CWarp::Create()
{
	// �ϐ��錾
	CWarp * pWarp;		// �V�[��3D�N���X
											// �������̐���(����->��{�N���X,��->�h���N���X)
	pWarp = new CWarp(ACTOR_WARP, LAYER_3DOBJECT);
	// ����������
	pWarp->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pWarp;
}

// ----------------------------------------
// �ǂݍ��ݍ쐬����
// ----------------------------------------
void CWarp::LoadCreate(void)
{
	// �ϐ��錾
	CWarp * pWarp;
	for (int nCntWarp = 0; nCntWarp < m_nAll; nCntWarp++)
	{
		pWarp = CWarp::Create();						// ����
		pWarp->SetTexture((TYPE)m_pload->GetInfo(nCntWarp).nType);
		pWarp->m_Type = (TYPE)m_pload->GetInfo(nCntWarp).nType;
		pWarp->SetPos(m_pload->GetInfo(nCntWarp).pos);		// �ʒu
		pWarp->SetRot(m_pload->GetInfo(nCntWarp).rot);		// ��]
		pWarp->SetSize(m_pload->GetInfo(nCntWarp).size);	// �T�C�Y
		pWarp->SetCol(m_pload->GetInfo(nCntWarp).col);
	}
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT CWarp::Load(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =					// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();
	char cTex[TYPE_MAX][128] =					// �e�N�X�`���[��
	{
		"data/TEXTURE/Effect/Effect0002.jpg",
		"data/TEXTURE/Effect/Effect0002.jpg",
	};

	// �e�N�X�`���[�ݒ�
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, cTex[nCnt], &m_pTexture[nCnt]);
	}
	// ���[�h����
	m_pload = new CLoad;
	// ���[�h�ǂݍ���
	m_nAll = m_pload->Load("data/LOAD/OBJECT/Warp_Location.txt");

	return S_OK;
}

// ----------------------------------------
// unload����
// ----------------------------------------
void CWarp::UnLoad(void)
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
CLoad * CWarp::GetLoad(void)
{
	return m_pload;
}

// ----------------------------------------
// �ʒu�̐ݒ菈��
// ----------------------------------------
void CWarp::SetPos(D3DXVECTOR3 pos)
{
	CScene_THREE::SetPos(pos);
}

// ----------------------------------------
// �T�C�Y�ݒ菈��
// ----------------------------------------
void CWarp::SetSize(D3DXVECTOR3 size)
{
	CScene_THREE::SetSize(size);
}

// ----------------------------------------
// ��]�̐ݒ菈��
// ----------------------------------------
void CWarp::SetRot(D3DXVECTOR3 rot)
{
	CScene_THREE::SetRot(rot);
}
// ----------------------------------------
// �F�̐ݒ菈��
// ----------------------------------------
void CWarp::SetCol(D3DXCOLOR col)
{
	CScene_THREE::SetCol(col);
}

// ----------------------------------------
// �\���e�N�X�`���[�ݒ菈��
// ----------------------------------------
void CWarp::SetTex(D3DXVECTOR2 first, D3DXVECTOR2 last)
{
}

// ----------------------------------------
// �T�C�Y�̎擾����
// ----------------------------------------
D3DXVECTOR3 CWarp::GetSize(void)
{
	return CScene_THREE::GetSize();
}

// ----------------------------------------
// ��]�̎擾����
// ----------------------------------------
D3DXVECTOR3 CWarp::GetRot(void)
{
	return CScene_THREE::GetRot();
}

// ----------------------------------------
// �ʒu�̎擾����
// ----------------------------------------
D3DXVECTOR3 CWarp::GetPos(void)
{
	return CScene_THREE::GetPos();
}
