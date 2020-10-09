//------------------------------------------------------------------------------
//
//�V�[��3D����  [scene3D.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "scene3D.h"
#include "renderer.h"
#include "manager.h"
#include "keyboard.h"

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
int CScene3D::m_nNumScene3D = 0;
//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CScene3D::CScene3D()
{
	//������
	m_bBboard = false;

	//�������Z
	m_nNumScene3D++;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CScene3D::~CScene3D()
{
	//�������Z
	m_nNumScene3D--;
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CScene3D::Init()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;	//���_�o�b�t�@

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,	//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		NULL)))
	{
		return E_FAIL;
	}

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̍��W
	m_Vtx3D[0].pos = pVtx[0].pos = ZeroVector3;
	m_Vtx3D[1].pos = pVtx[1].pos = ZeroVector3;
	m_Vtx3D[2].pos = pVtx[2].pos = ZeroVector3;
	m_Vtx3D[3].pos = pVtx[3].pos = ZeroVector3;

	//���_�̓������W
	m_Vtx3D[0].nor = pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Vtx3D[1].nor = pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Vtx3D[2].nor = pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Vtx3D[3].nor = pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�̐F
	m_Vtx3D[0].col = pVtx[0].col = WhiteColor;
	m_Vtx3D[1].col = pVtx[1].col = WhiteColor;
	m_Vtx3D[2].col = pVtx[2].col = WhiteColor;
	m_Vtx3D[3].col = pVtx[3].col = WhiteColor;

	//�e�N�X�`�����W
	m_Vtx3D[0].tex = pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	m_Vtx3D[1].tex = pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	m_Vtx3D[2].tex = pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	m_Vtx3D[3].tex = pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�f�[�^���A�����b�N
	pVtxBuff->Unlock();

	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CScene3D::Uninit()
{

}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CScene3D::Update()
{

}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CScene3D::Draw()
{
	//���[���h�}�g���b�N�X�v�Z
	CHossoLibrary::CalcMatrix(GetMtxWorldPtr(), GetPos(), GetRot());

	if (m_bBboard)
	{
		CHossoLibrary::SetBillboard(GetMtxWorldPtr());
	}

	//�|���S���`��
	DrawPolygon();
}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CScene3D::ShowDebugInfo()
{
#ifdef _DEBUG
	////3D���
	//if (ImGui::TreeNode("Scene3DInfo"))
	//{
	//	//���W
	//	if (ImGui::TreeNode("pos"))
	//	{
	//		if (ImGui::InputFloat3("pos", m_pos))
	//		{
	//			//���W�ݒ�
	//			SetPos(m_pos);
	//		}
	//		ImGui::TreePop();
	//	}

	//	//�F
	//	if (ImGui::TreeNode("col"))
	//	{
	//		if (ImGui::ColorEdit4("col", GetColor()))
	//		{
	//			//�F�ݒ�
	//			SetVtxCol(GetColor());
	//		}
	//		//tree�I��
	//		ImGui::TreePop();
	//	}

	//	//���_���
	//	if (ImGui::TreeNode("VtxInfo"))
	//	{
	//		//���_���W
	//		if (ImGui::TreeNode("VtxPos"))
	//		{
	//			if (ImGui::SliderFloat3("pos[0]", m_Vtx3D[0].pos, -300.0f, 300.0f) ||
	//				ImGui::SliderFloat3("pos[1]", m_Vtx3D[1].pos, -300.0f, 300.0f) ||
	//				ImGui::SliderFloat3("pos[2]", m_Vtx3D[2].pos, -300.0f, 300.0f) ||
	//				ImGui::SliderFloat3("pos[3]", m_Vtx3D[3].pos, -300.0f, 300.0f))
	//			{
	//				//���_���ւ̃|�C���^
	//				VERTEX_3D *pVtx;

	//				//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	//				GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//				//���_�X�V
	//				pVtx[0].pos = m_Vtx3D[0].pos;
	//				pVtx[1].pos = m_Vtx3D[1].pos;
	//				pVtx[2].pos = m_Vtx3D[2].pos;
	//				pVtx[3].pos = m_Vtx3D[3].pos;

	//				//���_�f�[�^���A�����b�N
	//				GetVtxBuff()->Unlock();

	//				//�@���v�Z
	//				SetNormal();
	//			}
	//			//�c���[�m�[�h�I��
	//			ImGui::TreePop();
	//		}
	//		//���_�@��
	//		if (ImGui::TreeNode("VtxNor"))
	//		{
	//			//�@��
	//			ImGui::InputFloat3("nor[0]", m_Vtx3D[0].nor);
	//			ImGui::InputFloat3("nor[1]", m_Vtx3D[1].nor);
	//			ImGui::InputFloat3("nor[2]", m_Vtx3D[2].nor);
	//			ImGui::InputFloat3("nor[3]", m_Vtx3D[3].nor);

	//			//�c���[�m�[�h�I��
	//			ImGui::TreePop();
	//		}
	//		//tree�I��
	//		ImGui::TreePop();
	//	}
	//	//tree�I��
	//	ImGui::TreePop();
	//}
#endif //DEBUG
}
//------------------------------------------------------------------------------
//�ݒ菈��
//------------------------------------------------------------------------------
void CScene3D::DrawSettingMtx(D3DXMATRIX const &Mtx)
{
	//������mtx�𗘗p
	SetMtxWorld(Mtx);

	//�|���S���`��
	DrawPolygon();
}
//------------------------------------------------------------------------------
//�ݒ菈��
//------------------------------------------------------------------------------
void CScene3D::DrawPolygon()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD,GetMtxWorldPtr());

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, GetTexture());

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
							0,					//�J�n����C���f�b�N�X(���_)
							2);					//�|���S���̖���

}


//------------------------------------------------------------------------------
//�e�N�X�`���A�j���[�V�����̍X�V
//------------------------------------------------------------------------------
void CScene3D::SetAnimation(D3DXVECTOR2 UV, D3DXVECTOR2 size)
{
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(UV.x, UV.y);
	pVtx[1].tex = D3DXVECTOR2(UV.x + size.x, UV.y);
	pVtx[2].tex = D3DXVECTOR2(UV.x, UV.y + size.y);
	pVtx[3].tex = D3DXVECTOR2(UV.x + size.x, UV.y + size.y);

	//���_�f�[�^���A�����b�N
	GetVtxBuff()->Unlock();
}

//------------------------------------------------------------------------------
//�@���ݒ�
//------------------------------------------------------------------------------
void CScene3D::SetNormal()
{
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//���_���璸�_�ւ̃x�N�g��
	D3DXVECTOR3 VecA = m_Vtx3D[1].pos - m_Vtx3D[0].pos;
	D3DXVECTOR3 VecB = m_Vtx3D[2].pos - m_Vtx3D[1].pos;
	D3DXVECTOR3 VecC = m_Vtx3D[3].pos - m_Vtx3D[2].pos;

	//�|���S���ʂ̖@��
	D3DXVECTOR3 normal1, normal2, normal3;
	D3DXVec3Cross(&normal1, &VecA, &VecB);
	D3DXVec3Cross(&normal2, &-VecB, &VecC);

	//���K��
	D3DXVec3Normalize(&normal1, &normal1);
	D3DXVec3Normalize(&normal2, &normal2);
	D3DXVec3Normalize(&normal3, &(normal1 + normal2));

	//���_�̖@���ݒ�
	m_Vtx3D[0].nor = pVtx[0].nor = normal1;
	m_Vtx3D[1].nor = pVtx[1].nor = normal3;
	m_Vtx3D[2].nor = pVtx[2].nor = normal3;
	m_Vtx3D[3].nor = pVtx[3].nor = normal2;

	//���_�f�[�^���A�����b�N
	GetVtxBuff()->Unlock();
}

//------------------------------------------------------------------------------
//���������@���L�Ǘ��p
//------------------------------------------------------------------------------
std::shared_ptr<CScene3D> CScene3D::Create_Shared(D3DXVECTOR3 pos, D3DXVECTOR3 size, OBJTYPE objtype)
{
	//�������m��
	std::shared_ptr<CScene3D> pScene3D = std::make_shared<CScene3D>();

	//������
	pScene3D->Init();

	//���W�ƃT�C�Y�ݒ�
	pScene3D->SetPos(pos);
	pScene3D->SetSize(size);

	//Scene���ŊǗ�
	pScene3D->SetObjType(objtype);
	pScene3D->AddSharedList(pScene3D);

	return pScene3D;
}
//------------------------------------------------------------------------------
//���������@Cscene�ŊǗ��p
//------------------------------------------------------------------------------
void CScene3D::Create_SceneManagement(D3DXVECTOR3 pos, D3DXVECTOR3 size, OBJTYPE objtype)
{
	//�������m��
	std::unique_ptr<CScene3D> pScene3D(new CScene3D);

	//������
	pScene3D->Init();

	//���W�ƃT�C�Y�ݒ�
	pScene3D->SetPos(pos);
	pScene3D->SetSize(size);

	//Scene�ŊǗ�
	pScene3D->SetObjType(objtype);
	pScene3D->AddUniqueList(std::move(pScene3D));
}
//------------------------------------------------------------------------------
//���������@Return��ŊǗ��p
//------------------------------------------------------------------------------
std::unique_ptr<CScene3D> CScene3D::Create_SelfManagement(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������m��
	std::unique_ptr<CScene3D> pScene3D(new CScene3D);

	//������
	pScene3D->Init();

	//���W�ƃT�C�Y�ݒ�
	pScene3D->SetPos(pos);
	pScene3D->SetSize(size);

	//return
	return std::move(pScene3D);
}

//------------------------------------------------------------------------------
//���_�o�b�t�@����
//------------------------------------------------------------------------------
HRESULT CScene3D::MakeVertex()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;	//���_�o�b�t�@

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,	//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,			//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&pVtxBuff,
		NULL)))
	{
		//���_�o�b�t�@�쐬���s
		return E_FAIL;
	}

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̍��W
	m_Vtx3D[0].pos = pVtx[0].pos = ZeroVector3;
	m_Vtx3D[1].pos = pVtx[1].pos = ZeroVector3;
	m_Vtx3D[2].pos = pVtx[2].pos = ZeroVector3;
	m_Vtx3D[3].pos = pVtx[3].pos = ZeroVector3;

	//���_�̓������W
	m_Vtx3D[0].nor = pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Vtx3D[1].nor = pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Vtx3D[2].nor = pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Vtx3D[3].nor = pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�̐F
	m_Vtx3D[0].col = pVtx[0].col = WhiteColor;
	m_Vtx3D[1].col = pVtx[1].col = WhiteColor;
	m_Vtx3D[2].col = pVtx[2].col = WhiteColor;
	m_Vtx3D[3].col = pVtx[3].col = WhiteColor;

	//�e�N�X�`�����W
	m_Vtx3D[0].tex = pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	m_Vtx3D[1].tex = pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	m_Vtx3D[2].tex = pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	m_Vtx3D[3].tex = pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�f�[�^���A�����b�N
	pVtxBuff->Unlock();

	//���_�o�b�t�@�ݒ�
	BindVtxBuff(pVtxBuff);

	return S_OK;

}
