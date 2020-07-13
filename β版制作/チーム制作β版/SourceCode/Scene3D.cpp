//==========================================================
// Scene3D�����FNORI
//==========================================================
//==========================================================
// �C���N���[�h�t�@�C��
//==========================================================
#include "main.h"
#include "scene3D.h"
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"
#include "inputKeyboard.h"
//==========================================================
// �R���X�g���N�^
//==========================================================
CScene3D::CScene3D(OBJ_TYPE type) : CSceneBase(type)
{
}
//==========================================================
// �R���X�g���N�^
//==========================================================
CScene3D::~CScene3D()
{
}
//==========================================================
// �R���X�g���N�^
//==========================================================
HRESULT CScene3D::Init(void)
{
	m_bBillboard = false;														// �r���{�[�h�t���O

	CSceneBase::Init();
	MakeVertex();

	return S_OK;
}
//==========================================================
// �R���X�g���N�^
//==========================================================
void CScene3D::Uninit(void)
{
}
//==========================================================
// �R���X�g���N�^
//==========================================================
void CScene3D::Update(void)
{

}
//==========================================================
// �R���X�g���N�^
//==========================================================
void CScene3D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//���[���h�}�g���b�N�X�̌v�Z
	MtxCalc();
	// �r���{�[�h����Ƃ�
	if (m_bBillboard)
	{
		CHossoLibrary::SetBillboard(GetMtxWorld());
	}
	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, GetMtxWorld());
	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_3D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, GetTexture());
	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//==========================================================
// �f�o�b�O
//==========================================================
void CScene3D::DebugInfo(void)
{
}
//==========================================================
// �R���X�g���N�^
//==========================================================
void CScene3D::SetAnimation(D3DXVECTOR2 UV, D3DXVECTOR2 UVsize)
{
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

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
// �R���X�g���N�^
//==========================================================
CScene3D * CScene3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,D3DXVECTOR3 rot)
{
	CScene3D*pScene3D;
	pScene3D = new CScene3D();
	pScene3D->Init();
	pScene3D->SetPosition(pos);
	pScene3D->SetSize(size);
	pScene3D->SetRot(rot);
	return pScene3D;
}
//==========================================================
// �T�C�Y�ݒ�
//==========================================================
void CScene3D::SetSize(D3DXVECTOR3 size)
{
	GetSize() = size;

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);
	// ���_����
	pVtx[0].pos = D3DXVECTOR3(-GetSize().x, +GetSize().y, +GetSize().z);
	pVtx[1].pos = D3DXVECTOR3(+GetSize().x, +GetSize().y, +GetSize().z);
	pVtx[2].pos = D3DXVECTOR3(-GetSize().x, -GetSize().y, -GetSize().z);
	pVtx[3].pos = D3DXVECTOR3(+GetSize().x, -GetSize().y, -GetSize().z);

	//���_�f�[�^���A�����b�N
	GetVtxBuff()->Unlock();
}
//==========================================================
// �J���[�ݒ�
//==========================================================
void CScene3D::SetColor(D3DXCOLOR col)
{
	GetColor() = col;

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����
	pVtx[0].col = GetColor();
	pVtx[1].col = GetColor();
	pVtx[2].col = GetColor();
	pVtx[3].col = GetColor();

	//���_�f�[�^���A�����b�N
	GetVtxBuff()->Unlock();
}
//==========================================================
// �R���X�g���N�^
//==========================================================
void CScene3D::MakeVertex(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;

	CRenderer*pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		NULL);
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	// ���_����
	pVtx[0].pos = D3DXVECTOR3(-GetSize().x, +GetSize().y, +GetSize().z);
	pVtx[1].pos = D3DXVECTOR3(+GetSize().x, +GetSize().y, +GetSize().z);
	pVtx[2].pos = D3DXVECTOR3(-GetSize().x, -GetSize().y, -GetSize().z);
	pVtx[3].pos = D3DXVECTOR3(+GetSize().x, -GetSize().y, -GetSize().z);

	pVtx[0].col = GetColor();
	pVtx[1].col = GetColor();
	pVtx[2].col = GetColor();
	pVtx[3].col = GetColor();

	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�f�[�^���A�����b�N
	pVtxBuff->Unlock();

	CSceneBase::BindVtxBuff(pVtxBuff);
}
