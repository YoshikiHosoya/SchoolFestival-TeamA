//==========================================================
// Scene2D�����FNORI
//==========================================================
//==========================================================
// �C���N���[�h�t�@�C��
//==========================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"
//==========================================================
// �R���X�g���N�^
//==========================================================
CScene2D::CScene2D(OBJ_TYPE type) : CSceneBase(type)
{
	m_nColCnt = 0;
}
//==========================================================
// �f�X�g���N�^
//==========================================================
CScene2D::~CScene2D()
{
}
//==========================================================
// ������
//==========================================================
HRESULT CScene2D::Init(void)
{
	// �ϐ�������
	m_bDisp = true;

	CSceneBase::Init();
	MakeVertex();
	return S_OK;
}
//==========================================================
// �I��
//==========================================================
void CScene2D::Uninit(void)
{
}
//==========================================================
// �X�V
//==========================================================
void CScene2D::Update(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	CSceneBase::GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);
	// ���_���̐ݒ�
	pVtx[0].pos = GetPosition() + D3DXVECTOR3(-GetSize().x, -GetSize().y, 0.0f);
	pVtx[1].pos = GetPosition() + D3DXVECTOR3(+GetSize().x, -GetSize().y, 0.0f);
	pVtx[2].pos = GetPosition() + D3DXVECTOR3(-GetSize().x, +GetSize().y, 0.0f);
	pVtx[3].pos = GetPosition() + D3DXVECTOR3(+GetSize().x, +GetSize().y, 0.0f);

	pVtx[0].col = GetColor();
	pVtx[1].col = GetColor();
	pVtx[2].col = GetColor();
	pVtx[3].col = GetColor();
	//���_�f�[�^���A�����b�N
	CSceneBase::GetVtxBuff()->Unlock();
}
//==========================================================
// �`��
//==========================================================
void CScene2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// �\������
	if (m_bDisp)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);
		pDevice->SetTexture(0, GetTexture());

		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_2D));

		CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_ON_ZWRITING_OFF);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);
	}
}
//==========================================================
// �f�o�b�O
//==========================================================
void CScene2D::DebugInfo(void)
{
}

//==========================================================
// �F�̐ݒ�
//==========================================================
void CScene2D::SetColor(D3DXCOLOR col)
{
	CSceneBase::SetColor(col);

	VERTEX_2D *pVtx;
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���̐ݒ�
	pVtx[0].col = GetColor();
	pVtx[1].col = GetColor();
	pVtx[2].col = GetColor();
	pVtx[3].col = GetColor();

	GetVtxBuff()->Unlock();

}
//==========================================================
// �N���G�C�g
//==========================================================
CScene2D * CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D*pScene2D;
	pScene2D = new CScene2D();
	pScene2D->SetPosition(pos);
	pScene2D->SetSize(size);
	pScene2D->Init();
	return pScene2D;
}
//==========================================================
// �N���G�C�g �V�[���ŊǗ�����
//==========================================================
CScene2D * CScene2D::CreateSceneManagement(D3DXVECTOR3 pos, D3DXVECTOR3 size,CScene::OBJ_TYPE objtype)
{
	CScene2D*pScene2D;
	pScene2D = new CScene2D(objtype);
	pScene2D->SetPosition(pos);
	pScene2D->SetSize(size);
	pScene2D->Init();
	return pScene2D;
}

//==========================================================
// �A�j���[�V�����̐ݒ�
//==========================================================
void CScene2D::SetAnimation(D3DXVECTOR2 UV, D3DXVECTOR2 UVsize)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	CSceneBase::GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(UV.x, UV.y);
	pVtx[1].tex = D3DXVECTOR2(UV.x + UVsize.x, UV.y);
	pVtx[2].tex = D3DXVECTOR2(UV.x, UV.y + UVsize.y);
	pVtx[3].tex = D3DXVECTOR2(UV.x + UVsize.x, UV.y + UVsize.y);

	//���_�f�[�^���A�����b�N
	CSceneBase::GetVtxBuff()->Unlock();
}
//==========================================================
// ���_�o�b�t�@�쐬
//==========================================================
void CScene2D::MakeVertex(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		NULL);
	VERTEX_2D *pVtx;
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	// ���_���̐ݒ�
	pVtx[0].pos = GetPosition() + D3DXVECTOR3(-GetSize().x, -GetSize().y, 0.0f);
	pVtx[1].pos = GetPosition() + D3DXVECTOR3(+GetSize().x, -GetSize().y, 0.0f);
	pVtx[2].pos = GetPosition() + D3DXVECTOR3(-GetSize().x, +GetSize().y, 0.0f);
	pVtx[3].pos = GetPosition() + D3DXVECTOR3(+GetSize().x, +GetSize().y, 0.0f);

	pVtx[0].rhm = 1.0f;
	pVtx[1].rhm = 1.0f;
	pVtx[2].rhm = 1.0f;
	pVtx[3].rhm = 1.0f;

	pVtx[0].col = GetColor();
	pVtx[1].col = GetColor();
	pVtx[2].col = GetColor();
	pVtx[3].col = GetColor();

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtxBuff->Unlock();

	CSceneBase::BindVtxBuff(pVtxBuff);

}
// =====================================================================================================================================================================
//
// �_�ŏ���
//
// =====================================================================================================================================================================
void CScene2D::Flashing()
{
	// �J�E���g���Z
	m_nColCnt++;
	// �]�肪0�̎������ɂ���
	if (m_nColCnt % 60 == 0)
	{
		this->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}
	// �]�肪0�̎��ʏ��Ԃɂ���
	else if (m_nColCnt % 30 == 0)
	{
		this->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}
