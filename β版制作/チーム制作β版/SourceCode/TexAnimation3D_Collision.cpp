//------------------------------------------------------------------------------
//
//�����蔻��t���e�N�X�`���A�j���[�V����3D����  [TexAnimation3D_Collision.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "TexAnimation3D_Collision.h"
#include "manager.h"
#include "renderer.h"
#include "collision.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CTexAnimation3D_Collision::CTexAnimation3D_Collision()
{

}
//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CTexAnimation3D_Collision::CTexAnimation3D_Collision(OBJ_TYPE obj) : CTexAnimation3D(obj)
{

}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CTexAnimation3D_Collision::~CTexAnimation3D_Collision()
{
	//nullcheck
	if (m_pCollision)
	{
		//�����蔻��폜
		delete m_pCollision;
		m_pCollision = nullptr;
	}
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CTexAnimation3D_Collision::Init()
{
	m_CollisionPosOrigin = ZeroVector3;

	//����������
	if (FAILED(CTexAnimation3D::Init()))
	{
		return E_FAIL;
	}
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CTexAnimation3D_Collision::Uninit()
{
	//�I������
	CTexAnimation3D::Uninit();
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CTexAnimation3D_Collision::Update()
{
	//�X�V����
	CTexAnimation3D::Update();

	//�����蔻��̃J�E���g���S���Ȃ�����
	if (m_nCntCollision-- > 0)
	{
		//���������
		Collision();
	}
	else
	{
		//nullcheck
		if (m_pCollision)
		{
			//�����蔻��폜
			delete m_pCollision;
			m_pCollision = nullptr;
		}
	}

}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CTexAnimation3D_Collision::Draw()
{
	//�`�揈��
	CTexAnimation3D::Draw();
}
//------------------------------------------------------------------------------
//�f�o�b�O���\��
//------------------------------------------------------------------------------
void CTexAnimation3D_Collision::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //_DEBUG
}
//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
void CTexAnimation3D_Collision::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, CTexture::SEPARATE_TEX_TYPE type,
										int nCntSwitch, CScene::OBJ_TYPE objtype, TAG tag, int nAttackValue, int nCntCollision,bool bOriginCenter)
{
	//�������m��
	CTexAnimation3D_Collision *pTexAnimation = new CTexAnimation3D_Collision(objtype);

	//nullcheck
	if (pTexAnimation)
	{
		//������
		pTexAnimation->Init();

		//���������@Scene��
		pTexAnimation->SetPosition(pos);
		pTexAnimation->SetRot(rot);
		pTexAnimation->BindTexture(CTexture::GetSeparateTexture(type));
		pTexAnimation->SetAnimation(ZeroVector2, CTexture::GetSparateTex_UVSize(type));
		pTexAnimation->m_tag = tag;
		pTexAnimation->m_nAttackValue = nAttackValue;
		pTexAnimation->m_nCntCollision = nCntCollision;

		//���������@TexAnimation��
		pTexAnimation->SetTex(type);
		pTexAnimation->SetCntSwitch(nCntSwitch);

		//�}�g���b�N�X�v�Z
		CHossoLibrary::CalcMatrix(pTexAnimation->GetMtxWorld(), ZeroVector3, rot);

		//�����蔻�萶��
		pTexAnimation->m_pCollision = CCollision::Create();
		//���������_���ǂ���
		if(bOriginCenter)
		{
			//�e�N�X�`���̃T�C�Y�ݒ�
			pTexAnimation->SetSize(size);

			pTexAnimation->m_pCollision->SetPos(pTexAnimation->GetPosPtr());
			pTexAnimation->m_pCollision->SetSize(pTexAnimation->GetSize());
		}
		else
		{
			//�e�N�X�`���̃T�C�Y�ݒ�
			pTexAnimation->SetSizeOfEdgeOrigin(size);

			//���_���W
			D3DXVECTOR3 VtxPos[4] = {};

			//���[�J���@�����蔻��̒��S
			D3DXVECTOR3 LocalPosOrigin = ZeroVector3;

			//���_���W�Z�o
			D3DXVec3TransformCoord(&VtxPos[0], &D3DXVECTOR3(-size.x, +size.y * 2.0f, 0.0f), pTexAnimation->GetMtxWorld());
			D3DXVec3TransformCoord(&VtxPos[1], &D3DXVECTOR3(+size.x, +size.y * 2.0f, 0.0f), pTexAnimation->GetMtxWorld());
			D3DXVec3TransformCoord(&VtxPos[2], &D3DXVECTOR3(-size.x, 0.0f, 0.0f), pTexAnimation->GetMtxWorld());
			D3DXVec3TransformCoord(&VtxPos[3], &D3DXVECTOR3(+size.x, 0.0f, 0.0f), pTexAnimation->GetMtxWorld());

			//�����蔻��p�̃��[�J�����W�v�Z
			D3DXVec3TransformCoord(&LocalPosOrigin, &D3DXVECTOR3(0.0f, size.y, 0.0f), pTexAnimation->GetMtxWorld());


			//�v�Z�p�̕ϐ��@�����蔻��̃T�C�Y
			D3DXVECTOR3 Max = D3DXVECTOR3(-1000.0f, -1000.0f, -0.0f);


			//4���_��
			for (int nCnt = 0; nCnt < 4; nCnt++)
			{
				//���_�����擾
				D3DXVECTOR3 vtx = VtxPos[nCnt];
				//�ő�̒��_���W���r���ďo��
				if (Max.x < vtx.x)
				{
					Max.x = vtx.x;
				}
				if (Max.y < vtx.y)
				{
					Max.y = vtx.y;
				}
			}

			//�}�g���b�N�X�v�Z
			CHossoLibrary::CalcMatrix(pTexAnimation->GetMtxWorld(), pos, rot);

			//�����蔻��p�̌��_�쐬�@������ƃL�����N�^�[���Ƃ��Ɋ񂹂�
			D3DXVec3TransformCoord(&pTexAnimation->m_CollisionPosOrigin, &D3DXVECTOR3(0.0f, size.y * 0.8f, 0.0f), pTexAnimation->GetMtxWorld());

			//�����蔻��̐ݒ�
			pTexAnimation->m_pCollision->SetPos(&pTexAnimation->m_CollisionPosOrigin);
			pTexAnimation->m_pCollision->SetSize(D3DXVECTOR3(fabsf(LocalPosOrigin.x - Max.x), fabsf(LocalPosOrigin.y - Max.y), 0.0f) * 2.0f);
		}

		//�f�o�b�O�̐��\��
		pTexAnimation->m_pCollision->DeCollisionCreate(CCollision::COLLISIONTYPE_NORMAL);
	}
}

//------------------------------------------------------------------------------
//�����蔻�菈��
//------------------------------------------------------------------------------
bool CTexAnimation3D_Collision::Collision()
{
	//nullcheck
	if (m_pCollision)
	{
		//�v���C���[�̍U���������ꍇ
		if (m_tag == TAG_PLAYER)
		{
			//�����蔻��@�G�A�ߗ��A�I�u�W�F�N�g�ɑ΂��ā@�ђʗL
			m_pCollision->ForPlayerBulletCollision(m_nAttackValue, 1, true);
		}
	}

	return false;
}
