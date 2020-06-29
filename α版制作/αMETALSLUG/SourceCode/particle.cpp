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
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 CParticle::m_pVtxBuff = nullptr;
int CParticle::m_nVertexID = 0;
int COneParticle::nNumParticleAll = 0;

std::vector<std::unique_ptr<CParticleParam>> CParticleParam::m_pParticleDefaultParamList = {};
std::vector<std::string> CParticleParam::m_aFileNameList =
{
	{ "data/Load/EffectParamater/test.txt" },
	{ "data/Load/EffectParamater/Sumple.txt" },
	{ "data/Load/EffectParamater/test.txt" },

};
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
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CParticle::~CParticle()
{
	//���X�g�̊J��
	m_pParticleList.clear();
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

	//���C�t��0�ȉ��ɂȂ�����
	if (m_pParticleParam->GetLife() <= 0)
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

	//���Z����
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ALPHABLEND_ADD);

	//Z�e�X�g������Z���C�e�B���O�L��
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_OFF_ZWRITING_ON);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, CTexture::GetTexture(m_pParticleParam->GetTex()));

	//�p�[�e�B�N���̃��X�g�̐���
	for (size_t nCnt = 0; nCnt < m_pParticleList.size(); nCnt++)
	{
		//�}�g���b�N�v�Z
		CHossoLibrary::CalcMatrix(&m_pParticleList[nCnt]->m_Mtx, m_pParticleList[nCnt]->m_pos, m_pParticleList[nCnt]->m_rot);

		//�r���{�[�h�ݒ�
		CHossoLibrary::SetBillboard(&m_pParticleList[nCnt]->m_Mtx);

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
		//�ړ�
		m_pParticleList[nCnt]->m_pos += m_pParticleList[nCnt]->m_move;

		//���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(-m_pParticleParam->GetRadius(), m_pParticleParam->GetRadius(), 0.0f);
		pVtx[1].pos = D3DXVECTOR3( m_pParticleParam->GetRadius(), m_pParticleParam->GetRadius(), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-m_pParticleParam->GetRadius(), -m_pParticleParam->GetRadius(), 0.0f);
		pVtx[3].pos = D3DXVECTOR3( m_pParticleParam->GetRadius(), -m_pParticleParam->GetRadius(), 0.0f);

		//���_�̍��W
		pVtx[0].col = m_pParticleParam->GetCol();
		pVtx[1].col = m_pParticleParam->GetCol();
		pVtx[2].col = m_pParticleParam->GetCol();
		pVtx[3].col = m_pParticleParam->GetCol();

		pVtx += 4;
	}
	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();

	//���_ID���Z
	m_nVertexID += m_pParticleList.size();
}

//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
void CParticle::Create(D3DXVECTOR3 pos, int nLife, float fRadius, D3DXCOLOR col, int nNumber,float fSpeed)
{
	//�������m��
	std::unique_ptr<CParticle> pParticle(new CParticle);

	//nullcheck
	if (pParticle)
	{
		//������
		pParticle->Init();

		//�p�[�e�B�N���̃p�����[�^�̃������m��
		pParticle->m_pParticleParam.reset(new CParticleParam);

		if (pParticle->m_pParticleParam)
		{
			//���ݒ�
			pParticle->m_pParticleParam->SetParamater(nLife, fRadius, col);

			//�p�[�e�B�N���̐ݒ�
			pParticle->SetParticle(pos, fSpeed, nNumber);

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
//�p�[�e�B�N�������@�ׂ����ݒ�L
//------------------------------------------------------------------------------
void CParticle::DetailsCreate(D3DXVECTOR3 pos, int nLife, float fRadius, D3DXCOLOR col, int nNumber, float fSpeed, float fAlphaDamping, float fRadiusDamping, CTexture::TEX_TYPE textype)
{
	//�������m��
	std::unique_ptr<CParticle> pParticle(new CParticle);

	//nullcheck
	if (pParticle)
	{
		//������
		pParticle->Init();

		//�p�[�e�B�N���̃p�����[�^�̃������m��
		pParticle->m_pParticleParam.reset(new CParticleParam);

		if (pParticle->m_pParticleParam)
		{
			//���ݒ�
			pParticle->m_pParticleParam->SetParamater(nLife, fRadius, col,fRadiusDamping,fAlphaDamping,textype);

			//�p�[�e�B�N���̐ݒ�
			pParticle->SetParticle(pos, fSpeed, nNumber);

			//�I�u�W�F�^�C�v�ݒ肵��Scene�ɏ��L����n��
			CParticleManager::AddParticleList(std::move(pParticle));
		}
	}
}

//------------------------------------------------------------------------------
//�e�L�X�g�������Ƀp�[�e�B�N���쐬
//------------------------------------------------------------------------------
void CParticle::CreateFromText(D3DXVECTOR3 pos, CParticleParam::PARTICLE_TYPE type)
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
			*pParam = *CParticleParam::GetDefaultParam(type);

			//�����o�̃|�C���^�Ɋi�[
			pParticle->m_pParticleParam.reset(std::move(pParam));

			//�p�[�e�B�N���̐ݒ�
			pParticle->SetParticle(pos, pParticle->m_pParticleParam->GetSpeed(), pParticle->m_pParticleParam->GetNumber());

			//�I�u�W�F�^�C�v�ݒ肵��Scene�ɏ��L����n��
			CParticleManager::AddParticleList(std::move(pParticle));
		}
	}
}
//------------------------------------------------------------------------------
//�e�L�X�g����p�����[�^�擾
//------------------------------------------------------------------------------
HRESULT CParticleParam::LoadParticleDefaultParam()
{
	//�t�@�C���|�C���g
	FILE *pFile;
	char cReadText[128];	//�����Ƃ��ēǂݎ��p
	char cHeadText[128];	//��r����p
	char cDie[128];			//�s�v�ȕ���
	HRESULT hResult = S_OK;

	CParticleParam *pParam;

	//�t�@�C������
	for (size_t nCnt = 0; nCnt < m_aFileNameList.size(); nCnt++)
	{
		//�t�@�C���ǂݍ���
		pFile = fopen(m_aFileNameList[nCnt].data(), "r");

		//�t�@�C�����J������
		if (pFile != NULL)
		{
			//�X�N���v�g������܂Ń��[�v
			while (strcmp(cHeadText, "SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);	//�ꕶ��ǂݍ���
				sscanf(cReadText, "%s", &cHeadText);		//��r�p�e�L�X�g�ɕ�������
			}
			//�X�N���v�g��������
			if (strcmp(cHeadText, "SCRIPT") == 0)
			{
				//�G���h�X�N���v�g������܂Ń��[�v
				while (strcmp(cHeadText, "END_SCRIPT") != 0)
				{
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s", &cHeadText);

					//�p�����[�^�Z�b�g��������
					if (strcmp(cHeadText, "PARAMSET") == 0)
					{
						//�������m��
						pParam = new CParticleParam;

						//�G���h����܂Ń��[�v
						while (strcmp(cHeadText, "END_PARAMSET") != 0)
						{

							fgets(cReadText, sizeof(cReadText), pFile);
							sscanf(cReadText, "%s", &cHeadText);

							if (strcmp(cHeadText, "LIFE") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pParam->m_nLife);
							}
							if (strcmp(cHeadText, "RADIUS") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDie, &cDie, &pParam->m_fRadius);
							}
							if (strcmp(cHeadText, "COLOR") == 0)
							{
								sscanf(cReadText, "%s %s %f %f %f %f", &cDie, &cDie,
										&pParam->m_col.r, &pParam->m_col.g, &pParam->m_col.b, &pParam->m_col.a);
							}
							if (strcmp(cHeadText, "NUMBER") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pParam->m_nNumber);
							}
							if (strcmp(cHeadText, "SPEED") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDie, &cDie, &pParam->m_fSpeed);
							}
							if (strcmp(cHeadText, "RADIUSDAMPING") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDie, &cDie, &pParam->m_fRadiusDamping);
							}
							if (strcmp(cHeadText, "ALPHADAMPING") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDie, &cDie, &pParam->m_fAlphaDamping);
							}
							if (strcmp(cHeadText, "TEXTURE") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pParam->m_Textype);
							}
							if (strcmp(cHeadText, "END_PARAMSET") == 0)
							{
								m_pParticleDefaultParamList.emplace_back(std::move(pParam));
							}
						}
					}
				}
			}

			//�p�����[�^���[�h
			std::cout << "DefaultParticleParamLoad >>" << m_aFileNameList[nCnt].data() << NEWLINE;

			//�t�@�C�������
			fclose(pFile);
		}

		//�t�@�C���ǂݍ��߂Ȃ������ꍇ
		else
		{
			MessageBox(NULL, "�p�[�e�B�N���̃p�����[�^�ǂݍ��ݎ��s", "�x��", MB_ICONWARNING);
			hResult = E_FAIL;
		}
	}
	return S_OK;
}

//------------------------------------------------------------------------------
//�p�[�e�B�N���̃p�����[�^�ۑ�
//------------------------------------------------------------------------------
HRESULT CParticleParam::SaveParticleDefaultParam(CParticleParam *pSaveParam)
{
	FILE *pFile;

	int nRotNum = 0;
	char cWriteText[128];

	//�t�@�C���ǂݍ���
	pFile = fopen(PARAMATER_SAVE_FILENAME, "w");

	//nullcheck
	if (pFile && pSaveParam)
	{
		//�u���b�N�R�����g
		fputs(COMMENT02, pFile);
		fputs(COMMENT01, pFile);

		fputs("//ParticleParamater\n", pFile);
		fputs("//�ǂݍ��ݗp�̃e�L�X�g�ɃR�s�[���Ă�������\n", pFile);
		fputs("//Author:Yoshiki Hosoya\n", pFile);

		fputs(COMMENT01, pFile);
		fputs(COMMENT02, pFile);
		fputs(NEWLINE, pFile);

		//�u���b�N�R�����g�I��//

		//�X�N���v�g
		fputs("SCRIPT", pFile);
		fputs(NEWLINE, pFile);


		//�p�����[�^�Z�b�g
		fputs("	PARAMSET", pFile);
		fputs(NEWLINE, pFile);

		//���s
		fputs(NEWLINE, pFile);

		//���C�t
		sprintf(cWriteText, "		%s %s %d				%s", "LIFE", &EQUAL, pSaveParam->m_nLife, "//���C�t");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		//���a
		sprintf(cWriteText, "		%s %s %.1f			%s", "RADIUS", &EQUAL, pSaveParam->m_fRadius, "//���a");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		//�F
		sprintf(cWriteText, "		%s %s %.1f %.1f %.1f %.1f	%s", "COLOR", &EQUAL,
				pSaveParam->m_col.r, pSaveParam->m_col.g, pSaveParam->m_col.b, pSaveParam->m_col.a, "//�F");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		//���a
		sprintf(cWriteText, "		%s %s %d				%s", "NUMBER", &EQUAL, pSaveParam->m_nNumber, "//��");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		//���x
		sprintf(cWriteText, "		%s %s %.1f				%s", "SPEED", &EQUAL, pSaveParam->m_fSpeed, "//���x");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		//���a�̌����l
		sprintf(cWriteText, "		%s %s %.1f		%s", "RADIUSDAMPING", &EQUAL, pSaveParam->m_fRadiusDamping, "//���a�̌����l");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		//�A���t�@�l�̌����l
		sprintf(cWriteText, "		%s %s %.1f		%s", "ALPHADAMPING", &EQUAL, pSaveParam->m_fAlphaDamping, "//�A���t�@�l�̌����l");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		//���x
		sprintf(cWriteText, "		%s %s %d				%s", "TEXTURE", &EQUAL, pSaveParam->m_Textype, "//�e�N�X�`��");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);


		//���s
		fputs(NEWLINE, pFile);

		//�p�����[�^�Z�b�g
		fputs("	END_PARAMSET", pFile);
		fputs(NEWLINE, pFile);

		//�L�[�Z�b�g�I��
		fputs("END_SCRIPT", pFile);
		fputs(NEWLINE, pFile);

		//�ۑ�����
		std::cout << "ParticleParam Save Succsess!! >>" << PARAMATER_SAVE_FILENAME << NEWLINE;

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{
		//�t�@�C�����J���܂���ł���
		std::cout << "ParticleParam Save FAILED!!  Can't Open File. SaveParticleDefaultParam()" << NEWLINE;
		return E_FAIL;
	}
	return S_OK;
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
void CParticle::SetParticle(D3DXVECTOR3 &pos, float fSpeed,int nNumber)
{
	//�ϐ��錾
	float fAngleX, fAngleY;
	D3DXVECTOR3 move;

	//�����������
	for (int nCnt = 0; nCnt < nNumber; nCnt++)
	{
		//0���Z�h�~
		if(fSpeed <= 0)
		{
			move = ZeroVector3;
		}
		else
		{

			//�p�[�e�B�N���̔�ԋ����������_������
			float fLength = (float)(rand() % (int)fSpeed) + 1.0f;

			//360�x�����_�� 3.14 - 3.14
			fAngleX = CHossoLibrary::Random_PI();
			fAngleY = CHossoLibrary::Random_PI();

			//�ړ��̕�����ݒ�
			move = D3DXVECTOR3(sinf(fAngleY) * sinf(fAngleX) * fLength,
								cosf(fAngleX) * cosf(fAngleY) * fLength,
								sinf(fAngleY) * cosf(fAngleX) * fLength);
		}

		//�p�[�e�B�N������
		std::unique_ptr<COneParticle>pOneParticle = COneParticle::Create(pos, move, ZeroVector3);

		//�z��ɒǉ�
		m_pParticleList.emplace_back(std::move(pOneParticle));

		//���_�̍X�V
		UpdateVertex();

	}
}

//------------------------------------------------------------------------------
//�p�����[�^�ݒ�
//------------------------------------------------------------------------------
void CParticleParam::SetParamater(int nLife, float fRadius, D3DXCOLOR col, float fRadiusDamping, float fAlphaDamping, CTexture::TEX_TYPE textype, int nNumber, float fSpeed)
{
	m_nLife = nLife;
	m_fRadius = fRadius;
	m_col = col;
	m_fRadiusDamping = fRadiusDamping;
	m_fAlphaDamping = fAlphaDamping;
	m_Textype = textype;

	m_nNumber = nNumber;
	m_fSpeed = fSpeed;
}


//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CParticleParam::UpdateParam()
{
	m_nLife--;
	m_fRadius *= m_fRadiusDamping;
	m_col.a *= m_fAlphaDamping;
}


//------------------------------------------------------------------------------
//�I�y���[�^
//�N���X�̃p�����[�^���ۂ��Ƒ���ł���悤��
//�|�C���^���m
//------------------------------------------------------------------------------
void * CParticleParam::operator=(const CParticleParam * pParam)
{
	m_nLife = pParam->m_nLife;
	m_fRadius = pParam->m_fRadius;
	m_col = pParam->m_col;
	m_nNumber = pParam->m_nNumber;
	m_fSpeed = pParam->m_fSpeed;
	m_fRadiusDamping = pParam->m_fRadiusDamping;
	m_fAlphaDamping = pParam->m_fAlphaDamping;
	m_Textype = pParam->m_Textype;

	return this;
}
