//------------------------------------------------------------------------------
//
//X�t�@�C�����f������  [SceneX.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "sceneX.h"
#include "renderer.h"
#include "manager.h"
#include "keyboard.h"
#include "light.h"
#include "modelinfo.h"

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
int CSceneX::m_nNumSceneX = 0;

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define SHADOW_COLOR (D3DXCOLOR(0.0f,0.0f,0.0f,0.5f))

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CSceneX::CSceneX()
{
	//������
	m_SceneXInfo = nullptr;

	//�������Z
	m_nNumSceneX++;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CSceneX::~CSceneX()
{
	//�|�C���^�̊J��
	m_SceneXInfo = nullptr;

	//�������Z
	m_nNumSceneX--;
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CSceneX::Init()
{

	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CSceneX::Uninit()
{
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CSceneX::Update()
{
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CSceneX::Draw()
{
	//�}�g���b�N�X�v�Z
	CHossoLibrary::CalcMatrix(GetMtxWorldPtr(), GetPos(), GetRot());

	//���b�V���`��
	DrawMesh();
}

//------------------------------------------------------------------------------
//���_�������Ƀ��b�V���̕`��
//------------------------------------------------------------------------------
void CSceneX::DrawMesh()
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATERIAL		*pMat;
	D3DMATERIAL9		matDef;
	D3DMATERIAL9		DrawMat;

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, GetMtxWorldPtr());

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)m_SceneXInfo->GetMatBuff()->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_SceneXInfo->GetMatNum(); nCntMat++)
	{
		//�`��p�̃}�e���A���擾
		DrawMat = pMat[nCntMat].MatD3D;

		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&DrawMat);

		// �`��
		m_SceneXInfo->GetMesh()->DrawSubset(nCntMat);
	}
	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}
//------------------------------------------------------------------------------
//�e�̃}�g���b�N�X�`��
//------------------------------------------------------------------------------
void CSceneX::DrawShadow()
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATERIAL		*pMat;
	D3DMATERIAL9		matDef;
	D3DMATERIAL9		matBlack;

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//������
	matBlack = matDef;

	//���ݒ�
	matBlack.Diffuse = SHADOW_COLOR;

	// �}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)m_SceneXInfo->GetMatBuff()->GetBufferPointer();

	//�X�e���V���L���@0�̂Ƃ���ɂ̂ݕ`��\
	pDevice->SetRenderState(D3DRS_STENCILREF, 0);					//�X�e���V���̏����̒l
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);		//�X�e���V���̏��� ==
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);				//�X�e���V����o�b�t�@�L��

	for (int nCntMat = 0; nCntMat < (int)m_SceneXInfo->GetMatNum(); nCntMat++)
	{
		//�X�e���V���ݒ�
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);

		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&matBlack);

		// �`��
		m_SceneXInfo->GetMesh()->DrawSubset(nCntMat);
	}

	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);	// �X�e���V����o�b�t�@����

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CSceneX::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}


//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
CSceneX * CSceneX::Create(D3DXVECTOR3 pos, OBJTYPE objtype)
{
	//�ϐ��錾
	CSceneX *pSceneX;

	//�������m��
	pSceneX = new CSceneX();

	//������
	pSceneX->Init();

	//���W�ƃT�C�Y�ݒ�
	pSceneX->SetPos(pos);

	//�I�u�W�F�N�g�^�C�v�ݒ�
	pSceneX->SetObjType(objtype);

	//�����������
	return pSceneX;
}
