//------------------------------------------------------------------------------
//
//�V�[��2D����  [scene2D.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "keyboard.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
int CScene2D::m_nNumScene2D = 0;

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CScene2D::CScene2D()
{
	//������
	GetPos() = ZeroVector3;
	GetSize() = ZeroVector3;
	m_fAngle = 0.0f;
	m_fLength = 0.0f;

	//�������Z
	m_nNumScene2D++;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CScene2D::~CScene2D()
{
	//�������Z
	m_nNumScene2D--;
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CScene2D::Init()
{
	MakeVertex();

	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CScene2D::Uninit()
{

}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CScene2D::Update()
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	m_fAngle = atan2f(GetSize().x, GetSize().y);
	m_fLength = (float)sqrt(GetSize().x * GetSize().x + GetSize().y * GetSize().y) / 2;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̍��W
	pVtx[0].pos.x = GetPos().x + sinf(-D3DX_PI + m_fAngle + GetRot().z)	* m_fLength;
	pVtx[0].pos.y = GetPos().y + cosf(-D3DX_PI + m_fAngle + GetRot().z)	* m_fLength;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = GetPos().x + sinf(D3DX_PI - m_fAngle + GetRot().z)	* m_fLength;
	pVtx[1].pos.y = GetPos().y + cosf(D3DX_PI - m_fAngle + GetRot().z)	* m_fLength;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = GetPos().x + sinf(-m_fAngle + GetRot().z)	* m_fLength;
	pVtx[2].pos.y = GetPos().y + cosf(-m_fAngle + GetRot().z)	* m_fLength;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = GetPos().x + sinf(m_fAngle + GetRot().z)	* m_fLength;
	pVtx[3].pos.y = GetPos().y + cosf(m_fAngle + GetRot().z)	* m_fLength;
	pVtx[3].pos.z = 0.0f;

	//���_�f�[�^���A�����b�N
	GetVtxBuff()->Unlock();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CScene2D::Draw()
{
	//�ʂ����ǂ���
	if (GetDisp())
	{
		//�f�o�C�X�擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, GetTexture());

		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
								0,					//�J�n����C���f�b�N�X(���_)
								2);					//�|���S���̖���
	}
}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CScene2D::ShowDebugInfo()
{
#ifdef _DEBUG
	//2D���
	if (ImGui::TreeNode("Scene2DInfo"))
	{
		//���W
		if (ImGui::TreeNode("pos"))
		{
			if (ImGui::InputFloat3("pos", GetPos()))
			{
				//���W�ݒ�
				SetPos(GetPos());
			}
			ImGui::TreePop();
		}
		//�T�C�Y
		if (ImGui::TreeNode("size"))
		{
			if (ImGui::InputFloat3("size", GetSize()))
			{
				//���W�ݒ�
				SetSize(GetSize());
			}
			ImGui::TreePop();
		}

		//tree�I��
		ImGui::TreePop();
	}
#endif //DEBUG
}

//------------------------------------------------------------------------------
//�e�N�X�`���A�j���[�V�����̍X�V
//------------------------------------------------------------------------------
void CScene2D::SetAnimation(D3DXVECTOR2 UV, D3DXVECTOR2 size)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

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
//�F�ݒ�
//------------------------------------------------------------------------------
void CScene2D::SetColor(D3DXCOLOR col)
{
	CSceneBase::SetColor(col);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̐F
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�f�[�^���A�����b�N
	GetVtxBuff()->Unlock();
}

//------------------------------------------------------------------------------
//���������@���L�Ǘ��p
//------------------------------------------------------------------------------
std::shared_ptr<CScene2D> CScene2D::Create_Shared(D3DXVECTOR3 pos, D3DXVECTOR3 size, OBJTYPE objtype)
{
	//�������m��
	std::shared_ptr<CScene2D> pScene2D = std::make_shared<CScene2D>();

	//������
	pScene2D->Init();

	//���W�ƃT�C�Y�ݒ�
	pScene2D->SetPos(pos);
	pScene2D->SetSize(size);

	//Scene�ŊǗ�
	pScene2D->SetObjType(objtype);
	pScene2D->AddSharedList(pScene2D);

	//return
	return pScene2D;
}
//------------------------------------------------------------------------------
//���������@Cscene�ŊǗ��p
//------------------------------------------------------------------------------
void CScene2D::Create_SceneManagement(D3DXVECTOR3 pos, D3DXVECTOR3 size, OBJTYPE objtype)
{
	//�������m��
	std::unique_ptr<CScene2D> pScene2D(new CScene2D);

	//������
	pScene2D->Init();

	//���W�ƃT�C�Y�ݒ�
	pScene2D->SetPos(pos);
	pScene2D->SetSize(size);

	//Scene�ŊǗ�
	pScene2D->SetObjType(objtype);
	pScene2D->AddUniqueList(std::move(pScene2D));
}
//------------------------------------------------------------------------------
//���������@Return��ŊǗ��p
//------------------------------------------------------------------------------
std::unique_ptr<CScene2D> CScene2D::Create_SelfManagement(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������m��
	std::unique_ptr<CScene2D> pScene2D(new CScene2D);


	//���W�ƃT�C�Y�ݒ�
	pScene2D->SetPos(pos);
	pScene2D->SetSize(size);

	//������
	pScene2D->Init();

	//return
	return std::move(pScene2D);
}

//------------------------------------------------------------------------------
//���_�o�b�t�@�쐬
//------------------------------------------------------------------------------
HRESULT CScene2D::MakeVertex()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;	//���_�o�b�t�@

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		NULL)))
	{
		//���_�o�b�t�@�쐬���s
		return E_FAIL;
	}

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̍��W
	pVtx[0].pos = GetPos() + D3DXVECTOR3(-GetSize().x * 0.5f, -GetSize().y * 0.5f, 0.0f);
	pVtx[1].pos = GetPos() + D3DXVECTOR3(GetSize().x * 0.5f, -GetSize().y * 0.5f, 0.0f);
	pVtx[2].pos = GetPos() + D3DXVECTOR3(-GetSize().x * 0.5f, GetSize().y * 0.5f, 0.0f);
	pVtx[3].pos = GetPos() + D3DXVECTOR3(GetSize().x * 0.5f, GetSize().y * 0.5f, 0.0f);

	//���_�̓������W
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�̐F
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�f�[�^���A�����b�N
	pVtxBuff->Unlock();

	//���_�o�b�t�@�ݒ�
	BindVtxBuff(pVtxBuff);

	return S_OK;
}
