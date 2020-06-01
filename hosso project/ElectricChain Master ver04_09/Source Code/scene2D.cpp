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
	m_pos = ZeroVector3;
	m_size = ZeroVector3;
	m_rot = ZeroVector3;
	m_col = WhiteColor;
	m_colalpha = WhiteColor;
	m_fAngle = 0.0f;
	m_fLength = 0.0f;
	m_bDisp = true;

	//�������Z
	m_nNumScene2D++;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CScene2D::~CScene2D()
{
	//���_�o�b�t�@�̊J��
	if (m_pVtxBuff)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//�������Z
	m_nNumScene2D--;
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CScene2D::Init()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̍��W
	pVtx[0].pos = m_pos + D3DXVECTOR3(-m_size.x * 0.5f, -m_size.y * 0.5f, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_size.x * 0.5f, -m_size.y * 0.5f, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-m_size.x * 0.5f, m_size.y * 0.5f, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_size.x * 0.5f, m_size.y * 0.5f, 0.0f);

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
	m_pVtxBuff->Unlock();

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

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̍��W
	pVtx[0].pos.x = m_pos.x + sinf(-D3DX_PI + m_fAngle + m_rot.z)	* m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(-D3DX_PI + m_fAngle + m_rot.z)	* m_fLength;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = m_pos.x + sinf(D3DX_PI - m_fAngle + m_rot.z)	* m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(D3DX_PI - m_fAngle + m_rot.z)	* m_fLength;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = m_pos.x + sinf(-m_fAngle + m_rot.z)	* m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(-m_fAngle + m_rot.z)	* m_fLength;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = m_pos.x + sinf(m_fAngle + m_rot.z)	* m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_fAngle + m_rot.z)	* m_fLength;
	pVtx[3].pos.z = 0.0f;

	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CScene2D::Draw()
{
	//�ʂ����ǂ���
	if (m_bDisp)
	{
		//�f�o�C�X�擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture);

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
			if (ImGui::InputFloat3("pos", m_pos))
			{
				//���W�ݒ�
				SetPos(m_pos);
			}
			ImGui::TreePop();
		}
		//�T�C�Y
		if (ImGui::TreeNode("size"))
		{
			if (ImGui::InputFloat3("size", m_size))
			{
				//���W�ݒ�
				SetSize(m_size);
			}
			ImGui::TreePop();
		}
		//�F
		if (ImGui::TreeNode("col"))
		{
			if (ImGui::ColorEdit4("col", m_col))
			{
				//�F�ݒ�
				SetVtxCol(m_col);
			}
			//tree�I��
			ImGui::TreePop();
		}
		//tree�I��
		ImGui::TreePop();
	}
#endif //DEBUG
}
//------------------------------------------------------------------------------
//�ݒ菈��
//------------------------------------------------------------------------------
void CScene2D::SetPos(D3DXVECTOR3 pos)
{
	//���W
	m_pos = pos;
}

//------------------------------------------------------------------------------
//�T�C�Y�̐ݒ�
//------------------------------------------------------------------------------
void CScene2D::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
	m_fAngle = atan2f(m_size.x, m_size.y);
	m_fLength = (float)sqrt(m_size.x * m_size.x + m_size.y * m_size.y) / 2;
}
//------------------------------------------------------------------------------
//�F�̐ݒ�
//------------------------------------------------------------------------------
void CScene2D::SetVtxCol(D3DXCOLOR col)
{
	//�F�ݒ�
	m_col = col;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();
}

//------------------------------------------------------------------------------
//�p�x�̐ݒ�
//------------------------------------------------------------------------------
void CScene2D::SetAngle(float fAngle)
{
	m_rot.z = fAngle;
}

//------------------------------------------------------------------------------
//�e�N�X�`���A�j���[�V�����̍X�V
//------------------------------------------------------------------------------
void CScene2D::SetAnimation(D3DXVECTOR2 UV, D3DXVECTOR2 size)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(UV.x, UV.y);
	pVtx[1].tex = D3DXVECTOR2(UV.x + size.x, UV.y);
	pVtx[2].tex = D3DXVECTOR2(UV.x, UV.y + size.y);
	pVtx[3].tex = D3DXVECTOR2(UV.x + size.x, UV.y + size.y);

	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();
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

	//������
	pScene2D->Init();

	//���W�ƃT�C�Y�ݒ�
	pScene2D->SetPos(pos);
	pScene2D->SetSize(size);

	//return
	return std::move(pScene2D);
}

//------------------------------------------------------------------------------
//�Q�[�W�p�̍X�V����
//------------------------------------------------------------------------------
void CScene2D::UpdateGauge(float fMag)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̍��W
	pVtx[0].pos = m_pos + D3DXVECTOR3(-m_size.x * 0.5f, -m_size.y * 0.5f, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_size.x * 0.5f - fMag * m_size.x, -m_size.y * 0.5f, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-m_size.x * 0.5f, m_size.y * 0.5f, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_size.x * 0.5f - fMag * m_size.x, m_size.y * 0.5f, 0.0f);

	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();
}


//------------------------------------------------------------------------------
//�|���S�������ǂ���
//------------------------------------------------------------------------------
bool CScene2D::Collision(D3DXVECTOR3 const & pos)
{
	//�͈͓����`�F�b�N
	if (pos.x <= m_pos.x + m_size.x * 0.5f &&
		pos.x >= m_pos.x - m_size.x * 0.5f &&
		pos.y <= m_pos.y + m_size.y * 0.5f &&
		pos.y >= m_pos.y - m_size.y * 0.5f)
	{
		//true
		return true;
	}
	//false
	return false;
}