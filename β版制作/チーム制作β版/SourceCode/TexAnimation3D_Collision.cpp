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
	if(m_pCollision)
	{
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

	Collision();
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
void CTexAnimation3D_Collision::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, CTexture::SEPARATE_TEX_TYPE type, int nCntSwitch, CScene::OBJ_TYPE objtype, bool bPlayer)
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
		pTexAnimation->SetSizeOfEdgeOrigin(size);
		pTexAnimation->SetRot(rot);
		pTexAnimation->BindTexture(CTexture::GetSeparateTexture(type));
		pTexAnimation->SetAnimation(ZeroVector2, CTexture::GetSparateTex_UVSize(type));
		pTexAnimation->m_bPlayer = bPlayer;

		//���������@TexAnimation��
		pTexAnimation->SetTex(type);
		pTexAnimation->SetCntSwitch(nCntSwitch);

		//�}�g���b�N�X�v�Z
		CHossoLibrary::CalcMatrix(pTexAnimation->GetMtxWorld(), ZeroVector3, rot);


		D3DXVECTOR3 VtxPos[4] = {};
		D3DXVECTOR3 LocalPosOrigin = ZeroVector3;

		//���_���W�Z�o
		D3DXVec3TransformCoord(&VtxPos[0], &D3DXVECTOR3(-size.x, +size.y * 2.0f	, 0.0f), pTexAnimation->GetMtxWorld());
		D3DXVec3TransformCoord(&VtxPos[1], &D3DXVECTOR3(+size.x, +size.y * 2.0f	, 0.0f), pTexAnimation->GetMtxWorld());
		D3DXVec3TransformCoord(&VtxPos[2], &D3DXVECTOR3(-size.x, 0.0f			, 0.0f), pTexAnimation->GetMtxWorld());
		D3DXVec3TransformCoord(&VtxPos[3], &D3DXVECTOR3(+size.x, 0.0f			, 0.0f), pTexAnimation->GetMtxWorld());


		D3DXVec3TransformCoord(&LocalPosOrigin, &D3DXVECTOR3(0.0f, size.y, 0.0f), pTexAnimation->GetMtxWorld());
		D3DXVECTOR3 Max = D3DXVECTOR3(-1000.0f, -1000.0f, -0.0f);
		D3DXVECTOR3 Min = D3DXVECTOR3(1000.0f, 1000.0f, 0.0f);
		CHossoLibrary::RangeLimit_Equal_Float;


		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			//���_�����擾
			D3DXVECTOR3 vtx = VtxPos[nCnt];
			//�ő�̒��_���W�ƍŏ��̒��_���W���r���ďo��
			if (Min.x > vtx.x)
			{
				Min.x = vtx.x;
			}
			if (Max.x < vtx.x)
			{
				Max.x = vtx.x;
			}
			if (Min.y > vtx.y)
			{
				Min.y = vtx.y;
			}
			if (Max.y < vtx.y)
			{
				Max.y = vtx.y;
			}
		}



		//�}�g���b�N�X�v�Z
		CHossoLibrary::CalcMatrix(pTexAnimation->GetMtxWorld(), pos, rot);
		D3DXVec3TransformCoord(&pTexAnimation->m_CollisionPosOrigin, &D3DXVECTOR3(0.0f,size.y * 0.5f,0.0f), pTexAnimation->GetMtxWorld());

		//�����蔻��̐ݒ�
		pTexAnimation->m_pCollision = CCollision::Create();
		pTexAnimation->m_pCollision->SetPos(&pTexAnimation->m_CollisionPosOrigin);
		pTexAnimation->m_pCollision->SetSize(D3DXVECTOR3(fabsf(LocalPosOrigin.x - Max.x), fabsf(LocalPosOrigin.y - Max.y), 0.0f));
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
		if (m_bPlayer)
		{
			//�����蔻��
			m_pCollision->ForPlayerBulletCollision(1, 1, true);
		}
	}

	return false;
}
