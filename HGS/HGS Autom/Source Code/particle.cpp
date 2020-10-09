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
#include "sound.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 CParticle::m_pVtxBuff = nullptr;
int CParticle::m_nVertexID = 0;
int COneParticle::nNumParticleAll = 0;

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CParticle::CParticle()
{
	//������
	m_bDeleteFlag = false;
	m_posOrigin = ZeroVector3;
	m_posEndPoint = ZeroVector3;
	m_rotOrigin = ZeroVector3;
	m_CollisionOrigin = ZeroVector3;
	m_pPosOriginPtr = nullptr;
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CParticle::~CParticle()
{
	//���X�g�̊J��
	m_pParticleList.clear();

	//nullcheck
	if (m_pCollision)
	{
		//�R���W�����̊J��
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
	//���C�t�����炷
	m_pParticleParam->UpdateParam();

	//�����蔻��
	if (m_pParticleParam->GetCollision())
	{
		//nullcheck
		if (m_pCollision)
		{
			//�����蔻�菈��
			Collision();

			//�J�E���g�_�E��
			m_pParticleParam->GetCollisionCnt()--;

			//�����蔻��̃J�E���g��0�ɂȂ��������
			if (m_pParticleParam->GetCollisionCnt() <= 0)
			{
				//�������J��
				delete m_pCollision;
				m_pCollision = nullptr;
			}
		}
	}

	//�A�j���[�V�����̏���������ꍇ
	if (m_pParticleParam->GetAnimation())
	{
		//�A�j���[�V�����X�V����
		UpdateAnimation();
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

	//�`�悷��ׂ̐ݒ�
	RendererSetting();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	//�A�j���[�V�������邩�ǂ����ŕω�
	m_pParticleParam->GetAnimation() ?
		pDevice->SetTexture(0, CTexture::GetSeparateTexture(m_pParticleParam->GetSeparateTex())) :
		pDevice->SetTexture(0, CTexture::GetTexture(m_pParticleParam->GetTex()));


	for (size_t nCnt = 0; nCnt < m_pParticleList.size(); nCnt++)
	{
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
	//nullcheck
	//���_�̃|�C���^��nullcheck
	if (m_pPosOriginPtr)
	{
		//�R���W�����̃T�C�Y�ɒ������鎞
		if (m_pParticleParam->GetCollisionSizeCalc())
		{
			//�}�g���b�N�X�v�Z
			CHossoLibrary::CalcMatrix(&m_WorldMtx, *m_pPosOriginPtr, m_rotOrigin);

			//�����蔻��p�̌��_�쐬�@������ƃL�����N�^�[���Ƃ��Ɋ񂹂�
			D3DXVec3TransformCoord(&m_posOrigin, &ZeroVector3, &m_WorldMtx);

		}
		//�Ǐ]���鎞
		else if(m_pParticleParam->GetFollowing())
		{
			m_posOrigin = *m_pPosOriginPtr;
		}
	}

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

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

		//���_�̍��W
		pVtx[0].pos = m_pParticleList[nCnt]->m_pos +  D3DXVECTOR3( -m_pParticleParam->GetSize().x,  -m_pParticleParam->GetSize().y, 0.0f);
		pVtx[1].pos = m_pParticleList[nCnt]->m_pos +  D3DXVECTOR3(  m_pParticleParam->GetSize().x,   -m_pParticleParam->GetSize().y, 0.0f);
		pVtx[2].pos = m_pParticleList[nCnt]->m_pos +  D3DXVECTOR3( -m_pParticleParam->GetSize().x, +m_pParticleParam->GetSize().y, 0.0f);
		pVtx[3].pos = m_pParticleList[nCnt]->m_pos +  D3DXVECTOR3(  m_pParticleParam->GetSize().x,  +m_pParticleParam->GetSize().y, 0.0f);

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
void CParticle::CreateFromText(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CParticleParam::PARTICLE_TYPE type, TAG tag, int nAttack,D3DXCOLOR col, D3DXVECTOR3 *PosPtr)
{
	//�������m��
	std::unique_ptr<CParticle> pParticle(new CParticle);

	//nullcheck
	if (pParticle)
	{
		//������
		pParticle->Init();
		pParticle->SetTag(tag);

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

			//���_�̃|�C���^
			pParticle->m_pPosOriginPtr = PosPtr;

			//�p�[�e�B�N���̐ݒ�
			pParticle->SetParticle(pos, rot, pParam);

			//a�l�������l�������Ƃ�
			if (col.a > 0)
			{
				//�F�ݒ�
				pParticle->m_pParticleParam->GetCol() = col;
			}

			//ParticleManager�ɏ��L����n��
			CParticleManager::AddParticleList(std::move(pParticle));
		}
	}
}
//------------------------------------------------------------------------------
//�R���W�����̃T�C�Y�v�Z
//------------------------------------------------------------------------------
void CParticle::CalcCollisionSize(D3DXVECTOR3 size)
{
	D3DXMATRIX RotationMatrix;

	//�}�g���b�N�X�v�Z
	CHossoLibrary::CalcMatrix(&RotationMatrix, m_posOrigin, m_rotOrigin);

	//���_���W
	D3DXVECTOR3 VtxPos[4] = {};

	//���_���W�Z�o
	D3DXVec3TransformCoord(&VtxPos[0], &D3DXVECTOR3(-size.x, +size.y * 2.0f, 0.0f), &RotationMatrix);
	D3DXVec3TransformCoord(&VtxPos[1], &D3DXVECTOR3(+size.x, +size.y * 2.0f, 0.0f), &RotationMatrix);
	D3DXVec3TransformCoord(&VtxPos[2], &D3DXVECTOR3(-size.x, 0.0f, 0.0f), &RotationMatrix);
	D3DXVec3TransformCoord(&VtxPos[3], &D3DXVECTOR3(+size.x, 0.0f, 0.0f), &RotationMatrix);

	//�I�_���W�v�Z
	D3DXVec3TransformCoord(&m_posEndPoint, &D3DXVECTOR3(0.0f, +size.y * 2.0f, 0.0f), &RotationMatrix);

	//�����蔻��p�̃��[�J�����W�v�Z
	D3DXVec3TransformCoord(&m_CollisionOrigin, &D3DXVECTOR3(0.0f, m_pParticleParam->GetCollisionSize().y, 0.0f), &RotationMatrix);

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

	////�����蔻��̐ݒ�
	//m_pCollision->SetPos(&m_CollisionOrigin);
	//m_pCollision->SetSize(D3DXVECTOR3(fabsf(m_CollisionOrigin.x - Max.x), fabsf(m_CollisionOrigin.y - Max.y), 0.0f) * 2.0f);
}
//------------------------------------------------------------------------------
//���_�o�b�t�@�m��
//------------------------------------------------------------------------------
HRESULT CParticle::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * MAX_PARTICLE * 4,	//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			//���_�t�H�[�}�b�g
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
	VERTEX_2D *pVtx;

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
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

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
void CParticle::SetParticle(D3DXVECTOR3 & pos, D3DXVECTOR3 const & rot, CParticleParam * pParam)
{
	//�ϐ��錾
	float fAngleX, fAngleY;
	D3DXVECTOR3 move;
	float fSpeed;

	//���[�J�����W���Z
	pos += pParam->GetLocalPos();

	//���_�ɕۑ�
	m_CollisionOrigin = m_posOrigin = pos;
	m_rotOrigin = rot;

	//�����������
	for (int nCnt = 0; nCnt < pParam->GetNumber(); nCnt++)
	{
		//�����_�����W���v�Z
		D3DXVECTOR3 randompos = D3DXVECTOR3(
			CHossoLibrary::Random(pParam->GetLocalRandomPosRange().x),
			CHossoLibrary::Random(pParam->GetLocalRandomPosRange().y),
			CHossoLibrary::Random(pParam->GetLocalRandomPosRange().z));

		//0���Z�h�~
		if (pParam->GetSpeed() == 0)
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

				fAngleX += rot.x;
				fAngleY += rot.y;

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

				//move = D3DXVECTOR3(-sinf(fAngleY) * cosf(fAngleX) * fSpeed,
				//	sinf(fAngleX) * fSpeed,
				//	-cosf(fAngleY) * cosf(fAngleX) * fSpeed);


				move = D3DXVECTOR3(-sinf(rot.z) * fSpeed,
									cosf(rot.z) * fSpeed,
									0.0f);

				break;
			default:
				break;
			}
		}


		//�p�[�e�B�N������
		std::unique_ptr<COneParticle>pOneParticle = COneParticle::Create(pos, move, rot);
		//�z��ɒǉ�
		m_pParticleList.emplace_back(std::move(pOneParticle));
	}

	//�A�j���[�V�����̃p�����[�^�ݒ�
	if (m_pParticleParam->GetAnimation())
	{
		SetAnimationParam();
	}

	//���肪����Ƃ��͓����蔻��̃|�C���^�쐬
	if (m_pParticleParam->GetCollision())
	{
		SetCollsionParam();
	}
	//���_�̍X�V
	UpdateVertex();

	//���Đ�
	SetSound();
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

	////�����蔻�萶��
	//m_pCollision = CCollision::Create();

	////nullcheck
	//if (m_pCollision)
	//{

	//	// �Q�[���I�u�W�F�N�g( �^�O )�̐ݒ�
	//	m_pCollision->SetGameObject(this);

	//	//���������_���ǂ���
	//	if (!m_pParticleParam->GetCollisionSizeCalc())
	//	{
	//		m_pCollision->SetPos(&m_posOrigin);
	//		m_pCollision->SetSize(m_pParticleParam->GetCollisionSize() * 2);
	//	}
	//	else
	//	{
	//		//�R���W�����̑傫������ɓ����蔻��̐ݒ�
	//		//��]�������ɂ��Ή�����悤��
	//		CalcCollisionSize(m_pParticleParam->GetCollisionSize());
	//	}

	//	//�f�o�b�O�̐��\��
	//	m_pCollision->DeCollisionCreate(CCollision::COLLISIONTYPE_NORMAL);
	//}
}


//------------------------------------------------------------------------------
//����
//------------------------------------------------------------------------------
void CParticle::Collision()
{
//
////nullcheck
//	if (m_pCollision)
//	{
//		//���[�U�[�̏ꍇ
//		if (m_pParticleParam->GetType() == CParticleParam::EFFECT_LAZER)
//		{
//			//�R���W�����̒������ς�������ǂ����̃t���O
//			bool bChangeLength = false;
//
//			//���C�ɂ�锻��
//			//���Ƃ̔���
//			if (m_pCollision->RayCollisionGetLength(m_posOrigin, m_posEndPoint, m_pParticleParam->GetSize().y))
//			{
//				//�T�C�Y�����킹��
//				m_pParticleParam->GetCollisionSize().y = m_pParticleParam->GetSize().y;
//
//				//�����蔻��̃T�C�Y�v�Z
//				CalcCollisionSize(m_pParticleParam->GetSize());
//
//				//�t���O��true�ɂ���
//				bChangeLength = true;
//			}
//
//
//			//�����I�u�W�F�N�g�܂ł̋��������߂�
//			if (m_pCollision->LazerCollisionGetLength(m_posOrigin, m_pParticleParam->GetSize().y))
//			{
//				//�T�C�Y�����킹��
//				m_pParticleParam->GetCollisionSize().y = m_pParticleParam->GetSize().y;
//
//				//�����蔻��̃T�C�Y�v�Z
//				CalcCollisionSize(m_pParticleParam->GetSize());
//
//				//�t���O��true�ɂ���
//				bChangeLength = true;
//			}
//
//			//�t���O��true�̎�
//			if (bChangeLength)
//			{
//				//�I�_�ɃG�t�F�N�g����
//				CParticle::CreateFromText(m_posEndPoint, ZeroVector3, CParticleParam::EFFECT_LAZERGRASE);
//			}
//		}
//
//		//�v���C���[�̍U���������ꍇ
//		if (GetTag() == TAG::PLAYER_1 || GetTag() == TAG::PLAYER_2)
//		{
//			if (CManager::GetMode() == CManager::MODE_GAME)
//			{
//				//�����蔻��@�G�A�ߗ��A�I�u�W�F�N�g�ɑ΂���
//				m_pCollision->ForPlayerBulletCollision(m_pParticleParam->GetCollisionAttackValue(), m_pParticleParam->GetCollisionAttackValue(), m_pParticleParam->GetPenetration());
//			}
//		}
//		//�v���C���[�̍U���������ꍇ
//		if (GetTag() == TAG::ENEMY)
//		{
//			if (CManager::GetMode() == CManager::MODE_GAME)
//			{
//				//�����蔻��@�v���C���[�ɑ΂���
//				m_pCollision->ForEnemyCollision(m_pParticleParam->GetCollisionAttackValue(), m_pParticleParam->GetCollisionAttackValue(), m_pParticleParam->GetPenetration());
//			}
//		}
//	}
}

//------------------------------------------------------------------------------
//�����_���[�̐ݒ�1
//------------------------------------------------------------------------------
void CParticle::RendererSetting()
{
	//���C�e�B���OOFF
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_LIGHTING_OFF);

	//���Z����
	if (m_pParticleParam->GetAlphaBlend_Add())
	{
		CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ALPHABLEND_ADD);
	}
	//���Z����
	else if (m_pParticleParam->GetAlphaBlend_Sub())
	{
		CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ALPHABLEND_SUB);
	}

	//Z�e�X�g�����@Z���C�e�B���O�L��
	if (!m_pParticleParam->GetZTest() && m_pParticleParam->GetZWrite())
	{
		CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_OFF);
	}
	//Z�e�X�g�L���@Z���C�e�B���O����
	else if (m_pParticleParam->GetZTest() && !m_pParticleParam->GetZWrite())
	{
		CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_ON_ZWRITING_OFF);

	}
	//Z�e�X�g�����C�e�B���O������
	else if (!m_pParticleParam->GetZTest() && !m_pParticleParam->GetZWrite())
	{
		CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_OFF);
	}

}

//------------------------------------------------------------------------------
//�G�t�F�N�g�ɍ��킹�����Đ�
//------------------------------------------------------------------------------
void CParticle::SetSound()
{
	//switch (m_pParticleParam->GetType())
	//{

	//}
}
