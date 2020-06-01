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
#include "meshcylinder.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
int CSceneX::m_nNumSceneX = 0;

std::vector<D3DMATERIAL9> CSceneX::m_MaterialColor[CSceneX::MAT_MAX] ={};

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
	m_pos = ZeroVector3;
	m_rot = ZeroVector3;
	m_SceneXInfo = nullptr;
	m_MatCol = MAT_NORMAL;

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
	//�V�F�[�_�[�ݒ�
	m_pShader = CShader::Create();
	m_pShader->SetType(CShader::SHADER_MODELDRAW);

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
	CHossoLibrary::CalcMatrix(&m_mtxWorld, m_pos, m_rot);

	//���b�V���`��
	DrawMesh();
}
//------------------------------------------------------------------------------
//�V�F�[�_�ŕ`��
//------------------------------------------------------------------------------
void CSceneX::DrawShader()
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�}�e���A��
	D3DXMATERIAL		*pMat;

	//�V�F�[�_�[�ɏ���ݒ肷��
	m_pShader->GetEffectPtr()->SetMatrix("g_WorldMatrix", &m_mtxWorld);
	//m_pShader->GetEffectPtr()->SetTexture("pTex", CTexture::GetTexture(CTexture::TEX_MESH_FIELD));

	// �}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)m_SceneXInfo->GetMatBuff()->GetBufferPointer();

	//�V�F�[�_�[�̕`��J�n
	// �`��J�n
	m_pShader->GetEffectPtr()->SetTechnique("BasicTec");
	m_pShader->GetEffectPtr()->Begin(0, 0);
		m_pShader->GetEffectPtr()->BeginPass(0);

	for (int nCntMat = 0; nCntMat < (int)m_SceneXInfo->GetMatNum(); nCntMat++)
	{
		////�`��p�̃}�e���A���擾
		//D3DXCOLOR DiffuseCol = pMat[nCntMat].MatD3D.Diffuse;
		//float Power = pMat[nCntMat].MatD3D.Power;
		//D3DXCOLOR EmissiveCol = pMat[nCntMat].MatD3D.Emissive;
		//D3DXCOLOR SpecularCol = pMat[nCntMat].MatD3D.Specular;
		//D3DXCOLOR Ambient = pMat[nCntMat].MatD3D.Ambient;

		//DiffuseCol = D3DXCOLOR(1, 1, 1, 1);
		//m_pShader->SetModelColor(DiffuseCol, SpecularCol, EmissiveCol, Ambient, Power);

		//m_pShader->GetEffectPtr()->SetVector("g_DiffuseColor", &D3DXVECTOR4(DiffuseCol));
		//m_pShader->GetEffectPtr()->SetVector("g_SpecularColor", &D3DXVECTOR4(SpecularCol));
		//m_pShader->GetEffectPtr()->SetVector("g_EmissiveColor", &D3DXVECTOR4(EmissiveCol));
		//m_pShader->GetEffectPtr()->SetVector("g_Ambient", &D3DXVECTOR4(Ambient));
		//m_pShader->GetEffectPtr()->SetFloat("g_Power", Power);

		//m_pShader->GetEffectPtr()->CommitChanges();


		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// �`��
		m_SceneXInfo->GetMesh()->DrawSubset(nCntMat);


	}
		m_pShader->GetEffectPtr()->EndPass();
	m_pShader->GetEffectPtr()->End();
	//�V�F�[�_�̕`��I��

	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);

	////���_���ւ̃|�C���^
	//VERTEX_3D *pVtx;

	//LPDIRECT3DVERTEXBUFFER9 vertex;

	////���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	//m_SceneXInfo->GetMesh()->LockVertexBuffer(0, (void**)&pVtx);


	//for (int nCnt = 0; nCnt < m_SceneXInfo->GetMesh()->GetNumVertices(); nCnt++)
	//{
	//	//pVtx[0].col = BlueColor;
	//	pVtx->pos;
	//	pVtx++;
	//}

	////���_�f�[�^�A�����b�N
	//m_SceneXInfo->GetMesh()->UnlockVertexBuffer();

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
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

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
//�X�e���V���V���h�E
//------------------------------------------------------------------------------
void CSceneX::DrawStencilShadow()
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�X�e���V���o�b�t�@�L��
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	//Z�o�b�t�@�������݋֎~
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_ON_ZWRITING_OFF);



	//�F�`�悵�Ȃ�
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x00000000);

	//�V�����_�[����
	std::shared_ptr<CMeshCylinder> pCylinder = CMeshCylinder::Create(D3DXVECTOR3(0.0f,-200.0f,0.0f), D3DXVECTOR3(30.0f, 200.0f, 30.0f), INTEGER2(16, 4), &m_mtxWorld);




	//�\�ʃJ�����O
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_CULLING_CW);

	//�X�e���V������
	pDevice->SetRenderState(D3DRS_STENCILREF, 0);					//�X�e���V���̏����̒l
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);		//�X�e���V���̏��� ==
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_ZERO);	//�X�e���V��Z�e�X�g���ɍ��i���Ă��鎞�@0
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_ZERO);	//�X�e���V���e�X�g�ɕs���i�̎��@0
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_INCR);	//�X�e���V���ɍ��i�AZ�e�X�g�ɕs���i �C���N�������g

	//�F
	pCylinder->SetCol(D3DXCOLOR(0.8f, 0.0f, 0.0f, 0.0f));

	//�`��
	pCylinder->DrawShadowMesh();





	//���ʃJ�����O
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_CULLING_CCW);

	//�F�ݒ�
	pCylinder->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.8f, 0.0f));

	//�X�e���V������
	pDevice->SetRenderState(D3DRS_STENCILREF, 1);					//�X�e���V���̏����̒l
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);		//�X�e���V���̏��� ==
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);	//�X�e���V��Z�e�X�g���ɍ��i���Ă��鎞�@�C���N�������g
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_ZERO);	//�X�e���V���e�X�g�ɕs���i�̎��@0
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_ZERO);	//�X�e���V���ɍ��i�AZ�e�X�g�ɕs���i 0


	//�`��
	pCylinder->DrawShadowMesh();


	//���ʃJ�����O
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_CULLING_CCW);

	//�F�̕`��ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x0000000f);


	//�F�ݒ�
	pCylinder->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));

	//�X�e���V������
	pDevice->SetRenderState(D3DRS_STENCILREF, 2);						//�X�e���V���̏����̒l
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);			//�X�e���V���̏��� ==
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILCAPS_KEEP);	//�X�e���V��Z�e�X�g���ɍ��i���Ă��鎞 ���ɉ������Ȃ�
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILCAPS_KEEP);	//�X�e���V���e�X�g�ɕs���i�̎��@0
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILCAPS_KEEP);	//�X�e���V���ɍ��i�AZ�e�X�g�ɕs���i 0

	//�`��
	pCylinder->DrawShadowMesh();

	//Z�e�X�g�����ɖ߂�
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);

	//�J�����O�����ɖ߂�
	CHossoLibrary::CheckCulling();

	//�X�e���V���o�b�t�@����
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	//�V�����_�[�j��
	pCylinder->Release();
	pCylinder = nullptr;
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
