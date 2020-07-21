//------------------------------------------------------------------------------
//
//�p�[�e�B�N������  [praticle.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "particle.h"
#include "manager.h"
#include "renderer.h"
#include "ParticleManager.h"
#include "collision.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 CParticle::m_pVtxBuff = nullptr;
int CParticle::m_nVertexID = 0;
int COneParticle::nNumParticleAll = 0;

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define PARAMATER_SAVE_FILENAME ("data/Load/EffectParamater/SaveParamater.txt")

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CParticle::CParticle()
{
	//������
	m_bDeleteFlag = false;
	m_posOrigin = ZeroVector3;
	m_rotOrigin = ZeroVector3;
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CParticle::~CParticle()
{
	//���X�g�̊J��
	m_pParticleList.clear();

	if (m_pCollision)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CParticle::Init()
{
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CParticle::Uninit()
{

}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CParticle::Update()
{
	if (m_pParticleParam->GetType() == CParticleParam::EFFECT_LAZER)
	{
		CDebugProc::Print("Rot >>  %.2f,%.2f,%.2f\n", m_rotOrigin.x, m_rotOrigin.y, m_rotOrigin.z);
	}

	//���C�t�����炷
	m_pParticleParam->UpdateParam();

	if (m_pParticleParam->GetAnimation())
	{
		//�A�j���[�V�����X�V����
		UpdateAnimation();
	}

	//�R���W����
	if (m_pParticleParam->GetCollision() && m_pParticleParam->GetCollisionCnt() >= 0)
	{
		m_pParticleParam->GetCollisionCnt()--;
		Collision();
	}
	else
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}

	//���C�t��0�ȉ��ɂȂ��������A�j���[�V�������I��������
	if (m_pParticleParam->GetLife() <= 0 || CTexAnimationBase::GetEndFlag())
	{
		//����
		m_bDeleteFlag = true;
		return;
	}
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CParticle::Draw()
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���C�e�B���OOFF
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_LIGHTING_OFF);

	if (m_pParticleParam->GetAlphaBlend())
	{
		//���Z����
		CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ALPHABLEND_ADD);
	}

	//Z�e�X�g������Z���C�e�B���O�L��
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_OFF_ZWRITING_ON);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	m_pParticleParam->GetAnimation() ?
		pDevice->SetTexture(0, CTexture::GetSeparateTexture(m_pParticleParam->GetSeparateTex())) :
		pDevice->SetTexture(0, CTexture::GetTexture(m_pParticleParam->GetTex()));

	//�p�[�e�B�N���̃��X�g�̐���
	for (size_t nCnt = 0; nCnt < m_pParticleList.size(); nCnt++)
	{
		//�}�g���b�N�v�Z
		CHossoLibrary::CalcMatrixAndBillboard(&m_pParticleList[nCnt]->m_Mtx, m_pParticleList[nCnt]->m_pos, m_pParticleList[nCnt]->m_rot);

		//�r���{�[�h�ݒ�
		//CHossoLibrary::SetBillboard(&m_pParticleList[nCnt]->m_Mtx);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_pParticleList[nCnt]->m_Mtx);

		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
			(4 * m_nVertexID) + nCnt * 4,					//�J�n����C���f�b�N�X(���_) (�O��܂ł̕��Ŏg�������_) + ���ݎg����
			2);												//�|���S���̖���
	}

	//���_ID���Z
	m_nVertexID += m_pParticleList.size();

	//Z�e�X�g�ʏ�
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);

	//�ʏ퍇��
	CManager::GetRenderer()->SetRendererCommand(CRenderer::REDNERER_ALPHABLEND_DEFAULT);

	//���C�e�B���OON
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_LIGHTING_ON);

}

//------------------------------------------------------------------------------
//�f�o�b�O���\��
//------------------------------------------------------------------------------
void CParticle::ShowDebugInfo()
{

#ifdef _DEBUG

#endif // _DEBUG
}

//------------------------------------------------------------------------------
//���_�X�V
//------------------------------------------------------------------------------
void CParticle::UpdateVertex()
{
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_ID���i�߂�
	pVtx += (4 * m_nVertexID);

	for (size_t nCnt = 0; nCnt < m_pParticleList.size(); nCnt++)
	{
		//�d�͂�������ꍇ
		if (m_pParticleParam->GetGravity())
		{
			//�������ɗ͂����Z
			m_pParticleList[nCnt]->m_move.y -= m_pParticleParam->GetGravityPower();
		}
		//�ړ�
		m_pParticleList[nCnt]->m_pos += m_pParticleList[nCnt]->m_move;

		//���S�����_����Ȃ��ꍇ
		if (m_pParticleParam->GetCollisionSizeCalc())
		{
			//���_�̍��W
			pVtx[0].pos = D3DXVECTOR3(-m_pParticleParam->GetSize().x, +m_pParticleParam->GetSize().y * 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(+m_pParticleParam->GetSize().x, +m_pParticleParam->GetSize().y * 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-m_pParticleParam->GetSize().x, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(+m_pParticleParam->GetSize().x, 0.0f, 0.0f);
		}
		else
		{
			//���_�̍��W
			pVtx[0].pos = D3DXVECTOR3(-m_pParticleParam->GetSize().x, m_pParticleParam->GetSize().y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(m_pParticleParam->GetSize().x, m_pParticleParam->GetSize().y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-m_pParticleParam->GetSize().x, -m_pParticleParam->GetSize().y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(m_pParticleParam->GetSize().x, -m_pParticleParam->GetSize().y, 0.0f);
		}
		//���_�̍��W
		pVtx[0].col = m_pParticleParam->GetCol();
		pVtx[1].col = m_pParticleParam->GetCol();
		pVtx[2].col = m_pParticleParam->GetCol();
		pVtx[3].col = m_pParticleParam->GetCol();

		//�A�j���[�V�������鎞��UV�v�Z
		if (m_pParticleParam->GetAnimation())
		{
			D3DXVECTOR2 UV = CTexAnimationBase::CalcUV();
			D3DXVECTOR2 UVsize = CTexture::GetSparateTex_UVSize(CTexAnimationBase::GetEffectTex());

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(UV.x, UV.y);
			pVtx[1].tex = D3DXVECTOR2(UV.x + UVsize.x, UV.y);
			pVtx[2].tex = D3DXVECTOR2(UV.x, UV.y + UVsize.y);
			pVtx[3].tex = D3DXVECTOR2(UV.x + UVsize.x, UV.y + UVsize.y);
		}
		//�A�j���[�V�������ĂȂ����͒ʏ�
		else
		{
			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}


		pVtx += 4;
	}
	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();

	//���_ID���Z
	m_nVertexID += m_pParticleList.size();
}

//------------------------------------------------------------------------------
//����
//�p�[�e�B�N���̃N���X��p���Đ���
//------------------------------------------------------------------------------
void CParticle::CreateFromParam(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CParticleParam *pInputParam)
{
	//�������m��
	std::unique_ptr<CParticle> pParticle(new CParticle);

	//nullcheck
	if (pParticle)
	{
		//������
		pParticle->Init();

		//�p�[�e�B�N���̃p�����[�^�̃������m��
		CParticleParam *pParam = new CParticleParam;

		//nullcheck
		if (pParam)
		{
			//���ݒ�
			//Uniqueptr���g���ƃI�y���[�^�ł��Ȃ��������畁�ʂ̃|�C���^���m�ŃI�y���[�^
			*pParam = pInputParam;

			//�����o�̃|�C���^�Ɋi�[
			pParticle->m_pParticleParam.reset(std::move(pParam));

			//�p�[�e�B�N���̐ݒ�
			pParticle->SetParticle(pos, rot, pParam);

			//�I�u�W�F�^�C�v�ݒ肵��Scene�ɏ��L����n��
			CParticleManager::AddParticleList(std::move(pParticle));
		}
	}
}

//------------------------------------------------------------------------------
//�e�N�X�`���j��
//------------------------------------------------------------------------------
void CParticle::ReleaseVertex()
{
	//nullcheck
	if (m_pVtxBuff)
	{
		//�o�b�t�@�̊J��
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//------------------------------------------------------------------------------
//���_ID���Z�b�g
//------------------------------------------------------------------------------
void CParticle::ResetVertexID()
{
	m_nVertexID = 0;
}

//------------------------------------------------------------------------------
//�e�L�X�g�������Ƀp�[�e�B�N���쐬
//------------------------------------------------------------------------------
void CParticle::CreateFromText(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CParticleParam::PARTICLE_TEXT type,TAG tag, int nAttack)
{
	//�������m��
	std::unique_ptr<CParticle> pParticle(new CParticle);

	//nullcheck
	if (pParticle)
	{
		//������
		pParticle->Init();
		pParticle->m_Tag = tag;

		//�p�[�e�B�N���̃p�����[�^�̃������m��
		CParticleParam *pParam = new CParticleParam;

		//nullcheck
		if (pParam)
		{
			//���ݒ�
			//Uniqueptr���g���ƃI�y���[�^�ł��Ȃ��������畁�ʂ̃|�C���^���m�ŃI�y���[�^
			*pParam = *CParticleParam::GetDefaultParam(type);

			//�U���͂����͂���Ă����ꍇ
			if (nAttack > 0)
			{
				pParam->GetCollisionAttackValue() = nAttack;
			}

			//�����o�̃|�C���^�Ɋi�[
			pParticle->m_pParticleParam.reset(std::move(pParam));

			//�p�[�e�B�N���̐ݒ�
			pParticle->SetParticle(pos, rot, pParam);

			//�I�u�W�F�^�C�v�ݒ肵��Scene�ɏ��L����n��
			CParticleManager::AddParticleList(std::move(pParticle));
		}
	}
}
//------------------------------------------------------------------------------
//���_�o�b�t�@�m��
//------------------------------------------------------------------------------
HRESULT CParticle::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_PARTICLE * 4,	//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,			//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr);

	//���_��񏉊���
	ResetVertex();

	return S_OK;
}
//------------------------------------------------------------------------------
//���_��񏉊���
//------------------------------------------------------------------------------
void CParticle::ResetVertex()
{
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		//���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//���_�̓������W
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�̐F
		pVtx[0].col = WhiteColor;
		pVtx[1].col = WhiteColor;
		pVtx[2].col = WhiteColor;
		pVtx[3].col = WhiteColor;

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();
}
//------------------------------------------------------------------------------
//�p�[�e�B�N���ݒ�
//------------------------------------------------------------------------------
void CParticle::SetParticle(D3DXVECTOR3 const & pos, D3DXVECTOR3 const & rot, CParticleParam * pParam)
{
	//�ϐ��錾
	float fAngleX, fAngleY;
	D3DXVECTOR3 move;
	float fSpeed;

	m_posOrigin = pos;
	m_rotOrigin = rot;

	//�����������
	for (int nCnt = 0; nCnt < pParam->GetNumber(); nCnt++)
	{
		//0���Z�h�~
		if (pParam->GetSpeed() <= 0)
		{
			move = ZeroVector3;
		}
		else
		{
			pParam->GetSpeedRandom() ?
				fSpeed = float(rand() % 1000 / 1000.0f) * pParam->GetSpeed() :
				fSpeed = pParam->GetSpeed();

			//�p�[�e�B�N���̔�ԋ����������_������
			switch (pParam->GetShape())
			{
			case CParticleParam::SHAPE_SPHERE:

				//360�x�����_�� 3.14 - 3.14
				fAngleX = CHossoLibrary::Random_PI();
				fAngleY = CHossoLibrary::Random_PI();

				//�ړ��̕�����ݒ�
				move = D3DXVECTOR3(sinf(fAngleY) * sinf(fAngleX) * fSpeed,
					sinf(fAngleY) * cosf(fAngleX) * fSpeed,
					cosf(fAngleY) * cosf(fAngleX) * fSpeed);
				break;
			case CParticleParam::SHAPE_CIRCLE_XY:
				//360�x�����_�� 3.14 - 3.14
				fAngleX = CHossoLibrary::Random_PI();
				fAngleY = CHossoLibrary::Random_PI();

				//�ړ��̕�����ݒ�
				move = D3DXVECTOR3(sinf(fAngleX) *  fSpeed,
					cosf(fAngleX) * fSpeed,
					0.0f);
				break;

			case CParticleParam::SHAPE_CONE:
				//�ړ��̕�����ݒ�
				//���_�̖ړI�n�̌v�Z
				fAngleX = pParam->GetRot().x + CHossoLibrary::Random(pParam->GetRange());
				fAngleY = pParam->GetRot().y + CHossoLibrary::Random(pParam->GetRange());

				move = D3DXVECTOR3(-sinf(fAngleY) * cosf(fAngleX) * fSpeed,
					sinf(fAngleX) * fSpeed,
					-cosf(fAngleY) * cosf(fAngleX) * fSpeed);


				break;
			case CParticleParam::SHAPE_LINE:
				//�ړ��̕�����ݒ�
				//���_�̖ړI�n�̌v�Z
				fAngleX = pParam->GetRot().x;
				fAngleY = pParam->GetRot().y;

				fAngleX += rot.x;
				fAngleY += rot.y;

				move = D3DXVECTOR3(-sinf(fAngleY) * cosf(fAngleX) * fSpeed,
					sinf(fAngleX) * fSpeed,
					-cosf(fAngleY) * cosf(fAngleX) * fSpeed);

				break;
			default:
				break;
			}
		}

		if (pParam->GetType() == CParticleParam::EFFECT_LAZER)
		{
			std::unique_ptr<COneParticle>pOneParticle = COneParticle::Create(pos, move, D3DXVECTOR3(0.0f, 0.0f, rot.x - D3DX_PI * 0.5f));
			//�z��ɒǉ�
			m_pParticleList.emplace_back(std::move(pOneParticle));
		}
		else
		{

			//�p�[�e�B�N������
			std::unique_ptr<COneParticle>pOneParticle = COneParticle::Create(pos, move, D3DXVECTOR3(rot));
			//�z��ɒǉ�
			m_pParticleList.emplace_back(std::move(pOneParticle));
		}
	}

	//�A�j���[�V�����̃p�����[�^�ݒ�
	SetAnimationParam();

	//���肪����Ƃ��͓����蔻��̃|�C���^�쐬
	if (m_pParticleParam->GetCollision())
	{
		SetCollsionParam();
	}
	//���_�̍X�V
	UpdateVertex();
}

//------------------------------------------------------------------------------
//�A�j���[�V�����Ɋւ�����ݒ�
//------------------------------------------------------------------------------
void CParticle::SetAnimationParam()
{
	CTexAnimationBase::SetLife(m_pParticleParam->GetLife());
	CTexAnimationBase::SetTex(m_pParticleParam->GetSeparateTex());
	CTexAnimationBase::SetLoop(m_pParticleParam->GetAnimationLoop());
	CTexAnimationBase::SetCntSwitch(m_pParticleParam->GetAnimationCntSwitch());

}

//------------------------------------------------------------------------------
//�R���W�����̏��ݒ�
//------------------------------------------------------------------------------
void CParticle::SetCollsionParam()
{
	m_pCollision = CCollision::Create();

	m_pCollision->SetPos(&m_posOrigin);
	m_pCollision->SetSize(m_pParticleParam->GetCollisionSize());

	D3DXMATRIX RotationMatrix;

	//�����蔻�萶��
	m_pCollision = CCollision::Create();

	//nullcheck
	if (m_pCollision)
	{
		//���������_���ǂ���
		if (!m_pParticleParam->GetCollisionSizeCalc())
		{
			m_pCollision->SetPos(&m_posOrigin);
			m_pCollision->SetSize(m_pParticleParam->GetCollisionSize() * 2);
		}
		else
		{
			//�p�x����
			m_rotOrigin.z = m_rotOrigin.y;
			m_rotOrigin.y = 0.0f;
			m_rotOrigin.x = 0.0f;

			//�}�g���b�N�X�v�Z
			CHossoLibrary::CalcMatrix(&RotationMatrix, ZeroVector3, m_rotOrigin);

			//���_���W
			D3DXVECTOR3 VtxPos[4] = {};

			//���[�J���@�����蔻��̒��S
			D3DXVECTOR3 LocalPosOrigin = ZeroVector3;

			D3DXVECTOR3 size = m_pParticleParam->GetCollisionSize();

			//���_���W�Z�o
			D3DXVec3TransformCoord(&VtxPos[0], &D3DXVECTOR3(-size.x, +size.y * 2.0f, 0.0f), &RotationMatrix);
			D3DXVec3TransformCoord(&VtxPos[1], &D3DXVECTOR3(+size.x, +size.y * 2.0f, 0.0f), &RotationMatrix);
			D3DXVec3TransformCoord(&VtxPos[2], &D3DXVECTOR3(-size.x, 0.0f, 0.0f), &RotationMatrix);
			D3DXVec3TransformCoord(&VtxPos[3], &D3DXVECTOR3(+size.x, 0.0f, 0.0f), &RotationMatrix);

			//�����蔻��p�̃��[�J�����W�v�Z
			D3DXVec3TransformCoord(&LocalPosOrigin, &D3DXVECTOR3(0.0f, m_pParticleParam->GetCollisionSize().y, 0.0f), &RotationMatrix);

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
			CHossoLibrary::CalcMatrix(&RotationMatrix, m_posOrigin, m_rotOrigin);

			//�����蔻��p�̌��_�쐬�@������ƃL�����N�^�[���Ƃ��Ɋ񂹂�
			D3DXVec3TransformCoord(&m_posOrigin, &D3DXVECTOR3(0.0f, m_pParticleParam->GetCollisionSize().y * 0.8f, 0.0f), &RotationMatrix);

			//�����蔻��̐ݒ�
			m_pCollision->SetPos(&m_posOrigin);
			m_pCollision->SetSize(D3DXVECTOR3(fabsf(LocalPosOrigin.x - Max.x), fabsf(LocalPosOrigin.y - Max.y), 0.0f) * 2.0f);
		}

		//�f�o�b�O�̐��\��
		m_pCollision->DeCollisionCreate(CCollision::COLLISIONTYPE_NORMAL);
	}
}


//------------------------------------------------------------------------------
//����
//------------------------------------------------------------------------------
void CParticle::Collision()
{
//nullcheck
	if (m_pCollision)
	{
		//�v���C���[�̍U���������ꍇ
		if (m_Tag == TAG_PLAYER)
		{
			if (CManager::GetGameState() == CManager::MODE_GAME)
			{
				//�����蔻��@�G�A�ߗ��A�I�u�W�F�N�g�ɑ΂��ā@�ђʗL
				m_pCollision->ForPlayerBulletCollision(m_pParticleParam->GetCollisionAttackValue(), m_pParticleParam->GetCollisionAttackValue(), true);
			}
		}
	}
}