//*************************************************************************************************************
//
// �p�[�e�B�N���̏���[particle.h]
// Author : Fujiwara Masato
//
//*************************************************************************************************************
//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "3Deffect.h"
#include "manager.h"
//-------------------------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ��̏�����
//-------------------------------------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9	C3DEffect::m_pVtxBuff = NULL;
C3DEffect::TEXTURE_INFO	*C3DEffect::m_pTexInfo = {};
C3DEffect::EFFECT		C3DEffect::m_aEffect[EFFECT_MAX] = {};
int						C3DEffect::m_nNumTextureMax = 0;
const float				C3DEffect::m_cfBaseAngle = D3DX_PI*0.25f;

//-------------------------------------------------------------------------------------------------------------
// ��������̃R���X�g���N�^
//-------------------------------------------------------------------------------------------------------------
C3DEffect::C3DEffect() :CScene(ACTOR_3DEFFECT,LAYER_3DPARTICLE)
{
}

//-------------------------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------------------------------------
C3DEffect::~C3DEffect()
{
}

//-------------------------------------------------------------------------------------------------------------
// �ǂݍ���
//-------------------------------------------------------------------------------------------------------------
HRESULT C3DEffect::Load(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9	pDevice;			// �f�o�C�X�̃|�C���^
	const char			*sFileName;			// �G�t�F�N�g���̃e�L�X�g�t�@�C����
	PFILETAG			pTextFileName;		// �e�N�X�`���t�@�C����
	PFILETAG			pFilePass;			// �t�@�C���p�X

	// �ϐ��̏�����
	pDevice		= CManager::GetRenderer()->GetDevice();		// �f�o�C�X�̎擾
	sFileName	= "data/LOAD/EffectInfo.txt";

	// �e�N�X�`�������擾
	m_nNumTextureMax = C3DEffect::LoadNumber(sFileName, "NUMBER");

	// �e�N�X�`���t�@�C�����̃������m��
	pTextFileName = new FILETAG[m_nNumTextureMax];
	// �e�N�X�`�����̃������m��
	m_pTexInfo = new C3DEffect::TEXTURE_INFO[m_nNumTextureMax];

	// �e�N�X�`���t�@�C�����̎擾
	C3DEffect::LoadTextureFile(sFileName, pTextFileName, m_nNumTextureMax);

	// �t�@�C���p�X�������m��
	pFilePass = new FILETAG;

	// �t�@�C���p�X�̎擾
	C3DEffect::LoadPass(sFileName, pFilePass, "PASS");

	for (int nCntTexture = 0; nCntTexture < m_nNumTextureMax; nCntTexture++)
	{
		char FileName[64];
		// ������̌���
		sprintf(FileName, "%s%s", pFilePass->string, pTextFileName[nCntTexture].string);
		// �e�N�X�`���̓ǂݍ���
		if (D3DXCreateTextureFromFile(pDevice, FileName, &m_pTexInfo[nCntTexture].pTexture) != D3D_OK)
		{
			MessageBox(NULL, "���ڂ�������܂���", "�x���I", MB_ICONWARNING);
			return E_FAIL;
		}
	}

	// �t�@�C�����̊J������
	delete[m_nNumTextureMax]pTextFileName;
	pTextFileName = NULL;
	// �t�@�C���p�X�̊J������
	delete pFilePass;
	pFilePass = NULL;

	return S_OK;
}

//-------------------------------------------------------------------------------------------------------------
// �J��
//-------------------------------------------------------------------------------------------------------------
void C3DEffect::Unload(void)
{
	for (int nCntTexture = 0; nCntTexture < m_nNumTextureMax; nCntTexture++)
	{// �e�N�X�`�����̊J��
		if (m_pTexInfo[nCntTexture].pTexture != NULL)
		{
			m_pTexInfo[nCntTexture].pTexture->Release();
			m_pTexInfo[nCntTexture].pTexture = NULL;
		}
	}
	// �e�N�X�`�����̃|�C���^�̊J��
	delete[m_nNumTextureMax]m_pTexInfo;
	m_pTexInfo = NULL;
}

//-------------------------------------------------------------------------------------------------------------
// ������
//-------------------------------------------------------------------------------------------------------------
void C3DEffect::Init(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9	pDevice;					// �f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

	// �l�̏�����
	this->InitValues();
	// ���_���쐬
	this->MakeVertex(pDevice);
}

//-------------------------------------------------------------------------------------------------------------
// �I��
//-------------------------------------------------------------------------------------------------------------
void C3DEffect::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//-------------------------------------------------------------------------------------------------------------
// �X�V
//-------------------------------------------------------------------------------------------------------------
void C3DEffect::Update(void)
{
	// �ϐ���`
	VERTEX_3D *pVtx;				// ���_���̃|�C���^
	C3DEffect::EFFECT *pEffect;		// �G�t�F�N�g�̃|�C���^
	// �|�C���^�̏�����
	pEffect = &C3DEffect::m_aEffect[0];

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �ő吔�����[�v
	for (int nCount = 0; nCount < EFFECT_MAX; nCount++, pEffect++, pVtx+=4)
	{
		// �g�p�t���O���I�t�̎�
		if (pEffect->bUse == false)
		{
			continue;
		}
		// �g�p���̂�̍X�V
		if (this->UpdateLife(pVtx, pEffect) == false)
		{
			continue;
		}

		// ���_���̍X�V
		if (this->UpdateVetex(pVtx, pEffect) == false)
		{
			continue;
		}
		// �ړ��̍X�V
		this->UpdateMove(pVtx, pEffect);

	}
	// ���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

//-------------------------------------------------------------------------------------------------------------
// �`��
//-------------------------------------------------------------------------------------------------------------
void C3DEffect::Draw(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9	pDevice;					// �f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans, mtxView;			// �v�Z�p�}�g���b�N�X
	C3DEffect::EFFECT *pEffect;						// �G�t�F�N�g�̃|�C���^

	pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	pEffect = &m_aEffect[0];						// �|�C���^�̏�����

	// ���C�e�B���O���[�h����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Z�o�b�t�@�@�L���@����
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_FALSE);

	// �����_�[�X�e�[�g(���Z��������)
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	// ����(�����)���J�����O����
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	for (int nCount = 0; nCount < EFFECT_MAX; nCount++, pEffect++)
	{
		if (pEffect->bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&pEffect->mtxWorld);

			// �}�g���b�N�X�r���[�̎擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�t�s��
			pEffect->mtxWorld._11 = mtxView._11;
			pEffect->mtxWorld._12 = mtxView._21;
			pEffect->mtxWorld._13 = mtxView._31;
			pEffect->mtxWorld._21 = mtxView._12;
			pEffect->mtxWorld._22 = mtxView._22;
			pEffect->mtxWorld._23 = mtxView._32;
			pEffect->mtxWorld._31 = mtxView._13;
			pEffect->mtxWorld._32 = mtxView._23;
			pEffect->mtxWorld._33 = mtxView._33;

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(
				&mtxRot,
				pEffect->rot.y,
				pEffect->rot.x,
				pEffect->rot.z);
			D3DXMatrixMultiply(
				&pEffect->mtxWorld,
				&pEffect->mtxWorld,
				&mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(
				&mtxTrans,
				pEffect->pos.x,
				pEffect->pos.y,
				pEffect->pos.z);
			D3DXMatrixMultiply(
				&pEffect->mtxWorld,
				&pEffect->mtxWorld,
				&mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &pEffect->mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_pTexInfo[pEffect->nTexType].pTexture);
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
		}
	}

	//�A���t�@�e�X�g�߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//Z�o�b�t�@�@�L���@����
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE);
	// ���C�e�B���O���[�h�L��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	// ����(�����)���J�����O����
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// �����_�[�X�e�[�g(�ʏ�u�����h����)
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//-------------------------------------------------------------------------------------------------------------
// �l�̏�����
//-------------------------------------------------------------------------------------------------------------
void C3DEffect::InitValues(void)
{
	// �ϐ��錾
	C3DEffect::EFFECT *pEffect;		// �G�t�F�N�g�̃|�C���^
	// �|�C���^�̏�����
	pEffect = &C3DEffect::m_aEffect[0];

	for (int nCount = 0; nCount < EFFECT_MAX; nCount++, pEffect++)
	{	// �ő吔�����[�v
		pEffect->pos			= D3DXVECTOR3(0.0f,0.0f,0.0f);			// �ʒu
		pEffect->rot			= D3DXVECTOR3(0.0f,0.0f,0.0f);			// ��]��
		pEffect->move			= D3DXVECTOR3(0.0f,0.0f,0.0f);			// �ړ���
		pEffect->col			= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �F
		pEffect->fRadius		= 0.0f;									// ���a
		pEffect->fAngle			= 0.0f;									// �p�x
		pEffect->fRadiusValue	= 0.0f;									// ���a�̕ω��l
		pEffect->fAlphaValue	= 0.0f;									// �A���t�@�l�̕ω��l
		pEffect->nLife			= 0;									// ��������
		pEffect->nTexType		= 0;									// �e�N�X�`���̎��
		pEffect->bUse			= false;								// �g�p���Ă��邩�ǂ���
		pEffect->EffectType		= C3DEffect::EFFECT_TYPE_NONE;			// �G�t�F�N�g�̎��
	}
}

//-------------------------------------------------------------------------------------------------------------
// ���_�̍쐬
//-------------------------------------------------------------------------------------------------------------
HRESULT C3DEffect::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	// �ϐ��錾
	VERTEX_3D *pVtx;							// ���_���̃|�C���^

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * EFFECT_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntEffect = 0; nCntEffect < EFFECT_MAX; nCntEffect++, pVtx += 4)
	{
		SetVartexSize(pVtx, NULL, &nCntEffect);

		// �@���x�N�g��
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		// ���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// texture���W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	// ���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------------------------------------
// ���_�T�C�Y�̐ݒ�
//-------------------------------------------------------------------------------------------------------------
void C3DEffect::SetVartexSize(VERTEX_3D * pVtx, EFFECT * pEffect, const int * nIndex)
{
	if (nIndex != NULL)
	{
		// �ϐ��錾
		C3DEffect::EFFECT *pLocalEffect;					// �G�t�F�N�g�̃|�C���^
		pLocalEffect = &C3DEffect::m_aEffect[*nIndex];		// �|�C���^�̏�����

		// ���_�̐ݒ�
		pVtx[0].pos.x = -sinf(m_cfBaseAngle + pLocalEffect->fAngle) * pLocalEffect->fRadius;
		pVtx[0].pos.y = -cosf(m_cfBaseAngle + pLocalEffect->fAngle) * pLocalEffect->fRadius;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = -sinf(m_cfBaseAngle - pLocalEffect->fAngle) * pLocalEffect->fRadius;
		pVtx[1].pos.y = cosf(m_cfBaseAngle - pLocalEffect->fAngle) * pLocalEffect->fRadius;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = sinf(m_cfBaseAngle - pLocalEffect->fAngle) * pLocalEffect->fRadius;
		pVtx[2].pos.y = -cosf(m_cfBaseAngle - pLocalEffect->fAngle) * pLocalEffect->fRadius;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = sinf(m_cfBaseAngle + pLocalEffect->fAngle) * pLocalEffect->fRadius;
		pVtx[3].pos.y = cosf(m_cfBaseAngle + pLocalEffect->fAngle) * pLocalEffect->fRadius;
		pVtx[3].pos.z = 0.0f;
	}
	if (pEffect != NULL)
	{
		// ���_�̐ݒ�
		pVtx[0].pos.x = -sinf(m_cfBaseAngle + pEffect->fAngle) * pEffect->fRadius;
		pVtx[0].pos.y = -cosf(m_cfBaseAngle + pEffect->fAngle) * pEffect->fRadius;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = -sinf(m_cfBaseAngle - pEffect->fAngle) * pEffect->fRadius;
		pVtx[1].pos.y = cosf(m_cfBaseAngle - pEffect->fAngle) * pEffect->fRadius;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = sinf(m_cfBaseAngle - pEffect->fAngle) * pEffect->fRadius;
		pVtx[2].pos.y = -cosf(m_cfBaseAngle - pEffect->fAngle) * pEffect->fRadius;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = sinf(m_cfBaseAngle + pEffect->fAngle) * pEffect->fRadius;
		pVtx[3].pos.y = cosf(m_cfBaseAngle + pEffect->fAngle) * pEffect->fRadius;
		pVtx[3].pos.z = 0.0f;
	}
}


//-------------------------------------------------------------------------------------------------------------
// ���_�J���[�̐ݒ�
//-------------------------------------------------------------------------------------------------------------
void C3DEffect::SetVetexColor(VERTEX_3D * pVtx, EFFECT * pEffect, const int * nIndex)
{
	if (nIndex != NULL)
	{
		// �ϐ��錾
		C3DEffect::EFFECT *pLocalEffect;					// �G�t�F�N�g�̃|�C���^
		pLocalEffect = &C3DEffect::m_aEffect[*nIndex];		// �|�C���^�̏�����

		pVtx[0].col =
			pVtx[1].col =
			pVtx[2].col =
			pVtx[3].col = pLocalEffect->col;
	}
	if (pEffect != NULL)
	{
		pVtx[0].col =
			pVtx[1].col =
			pVtx[2].col =
			pVtx[3].col = pEffect->col;
	}
}

//-------------------------------------------------------------------------------------------------------------
// ����
//-------------------------------------------------------------------------------------------------------------
C3DEffect * C3DEffect::Create(void)
{
	C3DEffect *p3DEffect = new C3DEffect;
	p3DEffect->Init();
	return p3DEffect;
}

//-------------------------------------------------------------------------------------------------------------
// �폜
//-------------------------------------------------------------------------------------------------------------
void C3DEffect::Delete(int nCntIndex)
{
}

//-------------------------------------------------------------------------------------------------------------
// �G�t�F�N�g�̐ݒ�
//-------------------------------------------------------------------------------------------------------------
void C3DEffect::Set3DEffect(
	EFFECT_TYPE EffectType, int nTexType,
	D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col,
	float fRadius, int nLife, float fRadiusValue)
{
	// �ϐ��錾
	C3DEffect::EFFECT *pEffect;			// �G�t�F�N�g�̃|�C���^
	pEffect = &C3DEffect::m_aEffect[0];	// �|�C���^�̏�����

	// �ő吔���[�v
	for (int nCntEffect = 0; nCntEffect < EFFECT_MAX; nCntEffect++, pEffect++)
	{
		// �g�p�t���O�I�t�̌̂̎�
		if (pEffect->bUse == false)
		{
			// �ϐ���`
			VERTEX_3D *pVtx;		// ���_�|�C���^
			//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
			// ���_�|�C���^�̍X�V
			pVtx += nCntEffect * 4;
			// ���C�t�̐ݒ�
			pEffect->nLife = nLife;
			// �e�N�X�`����ނ̐ݒ�
			pEffect->nTexType = nTexType;
			// �G�t�F�N�g��ނ̐ݒ�
			pEffect->EffectType = EffectType;
			// �ړ��ʂ̐ݒ�
			pEffect->move = move;
			// ���a�̐ݒ�
			pEffect->fRadius = fRadius;
			// �ʒu�̐ݒ�
			pEffect->pos = pos;
			// ���_�ʒu�̐ݒ�
			SetVartexSize(pVtx, pEffect);
			// �F�̐ݒ�
			pEffect->col = col;
			// ���_�J���[�̐ݒ�
			SetVetexColor(pVtx, pEffect);
			// �A���t�@�ω��l�̐ݒ�
			pEffect->fAlphaValue = pEffect->col.a / pEffect->nLife;
			if (pEffect->nTexType == 1)
			{
				// ���a�ω��l�̐ݒ�
				pEffect->fRadiusValue = -50.0f;
			}
			else
			{
				// ���a�ω��l�̐ݒ�
				pEffect->fRadiusValue = pEffect->fRadius / pEffect->nLife;
			}
			// �g�p�t���O���I��
			pEffect->bUse = true;
			//���_�f�[�^���A�����b�N
			m_pVtxBuff->Unlock();
			break;
		}
	}

}

//-------------------------------------------------------------------------------------------------------------
// �ԍ��̓ǂݍ���
//-------------------------------------------------------------------------------------------------------------
int C3DEffect::LoadNumber(const char * TxtName, const char * SetItem)
{
	// �ϐ��錾
	FILE *pFile = NULL;				// �t�@�C���̃|�C���^
	char cRead[128];				// �ǂݍ��ݗp
	char cComp[128];				// ��r�p
	char cEmpty[128];				// �v��Ȃ����̗p
	int nNumber = -1;				// ��
	int nCntError = 0;				// �G���[�p

	// �t�@�C�����J����Ă��Ȃ�������
	if ((pFile = fopen(TxtName, "r")) == NULL)
	{// ���b�Z�[�W�̕\��
#ifdef _DEBUG
		MessageBox(NULL, "�e�L�X�g�t�@�C����������܂���ł���", "�x���I", MB_ICONWARNING);
		return -1;
#endif // _DEBUG
	}
	// �X�N���v�g�����݂��Ă��邩�`�F�b�N
	if (!C3DEffect::Existenceofscript(pFile))
	{
#ifdef _DEBUG
		MessageBox(NULL, "[SCRIP]��������܂���\n�I�����Ă�������", "�x���I", MB_ICONWARNING);
		fclose(pFile);
		return -1;
#endif // _DEBUG
	}
	// END_SCRIPT������܂�
	while (strcmp(cComp, "END_SCRIPT") != 0)
	{// END_SCRIPT�܂Ń��[�v
	 // 1�s�ǂݍ���
		fgets(cRead, sizeof(cRead), pFile);
		// �ǂݍ���Ǖ�������
		sscanf(cRead, "%s", &cComp);

		// �G���[�J�E���g���C���N�������g
		nCntError++;
		if (nCntError > 1048576)
		{// �G���[
			nCntError = 0;
#ifdef _DEBUG
			MessageBox(NULL, "[END_SCRIPT]��������܂���\n�I�����Ă�������", "�x���I", MB_ICONWARNING);
			fclose(pFile);
			return -1;
#endif // _DEBUG

		}
		if (strcmp(cComp, SetItem) == 0)
		{
			sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty, &nNumber);
			cComp[0] = '\0';
		}
	}
	if (nNumber == -1)
	{
#ifdef _DEBUG
		MessageBox(NULL, "���ڂ�������܂���", "�x���I", MB_ICONWARNING);
		fclose(pFile);
		return -1;
#endif // _DEBUG
	}
	// �t�@�C�������
	fclose(pFile);

	return nNumber;

	return 0;
}

//-------------------------------------------------------------------------------------------------------------
// �p�X�̓ǂݍ���
//-------------------------------------------------------------------------------------------------------------
void C3DEffect::LoadPass(const char * TxtName, PFILETAG sFilePass , const char *ItemName)
{
	// �ϐ��錾
	FILE *pFile = NULL;				// �t�@�C���̃|�C���^
	char cRead[128];				// �ǂݍ��ݗp
	char cComp[128];				// ��r�p
	char cEmpty[128];				// �v��Ȃ����̗p
	int nCntError = 0;				// �G���[�p

									// �t�@�C�����J����Ă��Ȃ�������
	if ((pFile = fopen(TxtName, "r")) == NULL)
	{// ���b�Z�[�W�̕\��
#ifdef _DEBUG
		MessageBox(NULL, "�e�L�X�g�t�@�C����������܂���ł���", "�x���I", MB_ICONWARNING);
		return;
#endif // _DEBUG
	}
	// �X�N���v�g�����݂��Ă��邩�`�F�b�N
	if (!C3DEffect::Existenceofscript(pFile))
	{
#ifdef _DEBUG
		MessageBox(NULL, "[SCRIP]��������܂���\n�I�����Ă�������", "�x���I", MB_ICONWARNING);
		fclose(pFile);
		return;
#endif // _DEBUG
	}
	// END_SCRIPT������܂�
	while (strcmp(cComp, "END_SCRIPT") != 0)
	{
	 // 1�s�ǂݍ���
		fgets(cRead, sizeof(cRead), pFile);
		// �ǂݍ���Ǖ�������
		sscanf(cRead, "%s", &cComp);

		// �G���[�J�E���g���C���N�������g
		nCntError++;
		if (nCntError > 1048576)
		{// �G���[
			nCntError = 0;
#ifdef _DEBUG
			MessageBox(NULL, "[END_SCRIPT]��������܂���\n�I�����Ă�������", "�x���I", MB_ICONWARNING);
			fclose(pFile);
			return;
#endif // _DEBUG

		}
		if (strcmp(cComp, ItemName) == 0)
		{
			sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &sFilePass->string);
			cComp[0] = '\0';
		}
	}

	// �t�@�C�������
	fclose(pFile);
}

//-------------------------------------------------------------------------------------------------------------
// �e�N�X�`���t�@�C�����̓ǂݍ���
//-------------------------------------------------------------------------------------------------------------
void C3DEffect::LoadTextureFile(const char * sFileName, PFILETAG TexName,const int &nNumMax)
{
	// �ϐ��錾
	FILE *pFile = NULL;				// �t�@�C���̃|�C���^
	char cRead[128];				// �ǂݍ��ݗp
	char cComp[128];				// ��r�p
	char cEmpty[128];				// �v��Ȃ����̗p
	int nNumCount = 0;				// ���̃J�E���g
	int nCntError = 0;				// �G���[�p

	// �t�@�C�����J����Ă��Ȃ�������
	if ((pFile = fopen(sFileName, "r")) == NULL)
	{// ���b�Z�[�W�̕\��
#ifdef _DEBUG
		MessageBox(NULL, "�e�L�X�g�t�@�C����������܂���ł���", "�x���I", MB_ICONWARNING);
		return;
#endif // _DEBUG
	}
	// �X�N���v�g�����݂��Ă��邩�`�F�b�N
	if (!C3DEffect::Existenceofscript(pFile))
	{
#ifdef _DEBUG
		MessageBox(NULL, "[SCRIP]��������܂���\n�I�����Ă�������", "�x���I", MB_ICONWARNING);
		fclose(pFile);
		return;
#endif // _DEBUG
	}

	// END_SCRIPT������܂�
	while (strcmp(cComp, "END_SCRIPT") != 0)
	{// END_SCRIPT�܂Ń��[�v
	 // 1�s�ǂݍ���
		fgets(cRead, sizeof(cRead), pFile);
		// �ǂݍ���Ǖ�������
		sscanf(cRead, "%s", &cComp);

		// �G���[�J�E���g���C���N�������g
		nCntError++;
		if (nCntError > 1048576)
		{// �G���[
			nCntError = 0;
#ifdef _DEBUG
			MessageBox(NULL, "[END_SCRIPT]��������܂���\n�I�����Ă�������", "�x���I", MB_ICONWARNING);
			fclose(pFile);
			return;
#endif // _DEBUG

		}
		if (strcmp(cComp, "FILENAME") == 0)
		{
			if (nNumCount >= nNumMax)
			{
				MessageBox(NULL, "���f�����������Ă��܂���", "�x���I", MB_ICONWARNING);
				fclose(pFile);
				return;
			}
			sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &TexName[nNumCount].string);
			nNumCount++;
			cComp[0] = '\0';
		}
	}
	if (nNumCount < nNumMax)
	{
#ifdef _DEBUG
		MessageBox(NULL, "���ڂ�������܂���", "�x���I", MB_ICONWARNING);
		fclose(pFile);
		return;
#endif // _DEBUG
	}
	// �t�@�C�������
	fclose(pFile);
}

//-------------------------------------------------------------------------------------------------------------
// �X�N���v�g�����݂��邩����
//-------------------------------------------------------------------------------------------------------------
bool C3DEffect::Existenceofscript(FILE * pFile)
{
	// �ϐ��錾
	char cRead[128];	// �ǂݍ��ݗp
	char cComp[128];	// ��r�p
	int nCntError = 0;	// �G���[�p
	while (strcmp(cComp, "SCRIPT") != 0)
	{
		// 1�s�ǂݍ���
		fgets(cRead, sizeof(cRead), pFile);
		// �ǂݍ���Ǖ�������
		sscanf(cRead, "%s", &cComp);

		// �G���[�J�E���g���C���N�������g
		nCntError++;
		if (nCntError > 1048576)
		{// �G���[
			nCntError = 0;
			return false;
		}
	}
	return true;
}

//-------------------------------------------------------------------------------------------------------------
// ���C�t�̍X�V
//-------------------------------------------------------------------------------------------------------------
bool C3DEffect::UpdateLife(VERTEX_3D *pVtx, EFFECT * pEffect)
{
	if (pEffect->nLife < 0)
	{
		// ���C�t��0�ɂȂ����Ƃ�
		pEffect->bUse = false;
		return false;
	}
	else
	{
		// ���C�t�����炷w
		pEffect->nLife--;
		return true;
	}
}

//-------------------------------------------------------------------------------------------------------------
// ���_�̍X�V
//-------------------------------------------------------------------------------------------------------------
bool C3DEffect::UpdateVetex(VERTEX_3D * pVtx, EFFECT * pEffect)
{
	// ���a��ω�������
	pEffect->fRadius -= pEffect->fRadiusValue;

	if (pEffect->fRadius <= 0.0f)
	{
		pEffect->fRadius = 0.0f;
		pEffect->bUse = false;
		return false;
	}
	else
	{
		SetVartexSize(pVtx, pEffect);
	}

	// �A���t�@�l��ω�������
	pEffect->col.a -= pEffect->fAlphaValue;
	if (pEffect->col.a <= 0.0f)
	{
		pEffect->col.a = 0.0f;
		pEffect->bUse = false;
		return false;
	}
	else
	{
		SetVetexColor(pVtx, pEffect);
	}
	return true;
}

//-------------------------------------------------------------------------------------------------------------
// �ړ��̍X�V
//-------------------------------------------------------------------------------------------------------------
void C3DEffect::UpdateMove(VERTEX_3D * pVtx, EFFECT * pEffect)
{
	switch (pEffect->EffectType)
	{
	case C3DEffect::EFFECT_TYPE::EFFECT_TYPE_EXPLOSION:
		// ����
		pEffect->move.x += (0 - pEffect->move.x)*0.2f;
		pEffect->move.y += (0 - pEffect->move.y)*0.2f;
		pEffect->move.z += (0 - pEffect->move.z)*0.2f;
		// �ʒu���̍X�V
		pEffect->pos += pEffect->move;
		break;
	case C3DEffect::EFFECT_TYPE::EFFECT_TYPE_SPARK:
		// �ʒu���̍X�V
		pEffect->pos += pEffect->move;
		break;
	default:
		break;
	}
}


