// ----------------------------------------
//
// ���f����񏈗� [model_info.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------
#include "model_info.h"

// ----------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CModel_info::CModel_info()
{
	m_model_info.pMesh = NULL;
	m_model_info.pBuffMat = NULL;
	m_model_info.pTexture = NULL;
	m_model_info.nNumMat = 0;
	m_model_info.vtxMinMaterials = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_model_info.vtxMaxMaterials = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_model_info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_model_info.posDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_model_info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_model_info.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_model_info.nParent = 0;
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CModel_info::~CModel_info()
{
}

// ----------------------------------------
// �ǂݍ���
// ----------------------------------------
void CModel_info::Load(
	LPDIRECT3DDEVICE9 pDevice,
	const char * charModel
)
{
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(
		charModel,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_model_info.pBuffMat,
		NULL,
		&m_model_info.nNumMat,
		&m_model_info.pMesh);

	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/UV_TEX2.png", &m_model_info.pTexture);

	// ���f���̒��_���W�̍ő�l�E�ŏ��l�̐ݒ�
	int nNumVertex;			// ���_��
	DWORD sizeFVF;			// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVertexBuffer;	// ���_�o�b�t�@�ւ̃|�C���^
							// �}�e���A���̒��_�ʒu�̍ő�l�E�ŏ��l
	m_model_info.vtxMinMaterials = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
	m_model_info.vtxMaxMaterials = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
	// ���_�����擾
	nNumVertex = m_model_info.pMesh->GetNumVertices();
	// ���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(m_model_info.pMesh->GetFVF());
	// ���_�o�b�t�@�����b�N
	m_model_info.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertexBuffer);
	// ���_�����J��Ԃ�
	for (int nCntVtx = 0; nCntVtx < nNumVertex; nCntVtx++)
	{
		// �Ԓn����D3DXVE
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVertexBuffer;

		// -----------���ׂĂ̒��_�����r���čŏ��l�E�ő�l�𔲂��o��---------- //
		// x //
		// �ŏ��l
		if (m_model_info.vtxMinMaterials.x > vtx.x)
		{
			m_model_info.vtxMinMaterials.x = vtx.x;
		}
		// �ő�l
		if (m_model_info.vtxMaxMaterials.x < vtx.x)
		{
			m_model_info.vtxMaxMaterials.x = vtx.x;
		}
		// y //
		// �ŏ��l
		if (m_model_info.vtxMinMaterials.y > vtx.y)
		{
			m_model_info.vtxMinMaterials.y = vtx.y;
		}
		// �ő�l
		if (m_model_info.vtxMaxMaterials.y < vtx.y)
		{
			m_model_info.vtxMaxMaterials.y = vtx.y;
		}
		// z //
		// �ŏ��l
		if (m_model_info.vtxMinMaterials.z > vtx.z)
		{
			m_model_info.vtxMinMaterials.z = vtx.z;
		}
		// �ő�l
		if (m_model_info.vtxMaxMaterials.z < vtx.z)
		{
			m_model_info.vtxMaxMaterials.z = vtx.z;
		}
		// �T�C�Y�|�C���^��i�߂�
		pVertexBuffer += sizeFVF;
	}
	// �A�����b�N
	m_model_info.pMesh->UnlockVertexBuffer();

	m_model_info.scal = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

// ----------------------------------------
// Unload
// ----------------------------------------
void CModel_info::Unload(void)
{
	// ���b�V���̊J��
	if (m_model_info.pMesh != NULL)
	{
		m_model_info.pMesh->Release();
		m_model_info.pMesh = NULL;
	}

	// �}�e���A���̊J��
	if (m_model_info.pBuffMat != NULL)
	{
		m_model_info.pBuffMat->Release();
		m_model_info.pBuffMat = NULL;
	}

	// �e�N�X�`���[�̊J��
	if (m_model_info.pTexture != NULL)
	{
		m_model_info.pTexture->Release();
		m_model_info.pTexture = NULL;
	}
}

// ----------------------------------------
// ���f�����擾
// ----------------------------------------
MODEL_INFO & CModel_info::GetModel_info(void)
{
	return m_model_info;
}

// ----------------------------------------
// ���b�V�����擾
// ----------------------------------------
LPD3DXMESH & CModel_info::GetMesh(void)
{
	return m_model_info.pMesh;
}

// ----------------------------------------
// �}�e���A�����擾
// ----------------------------------------
LPD3DXBUFFER & CModel_info::GetBuffmat(void)
{
	return m_model_info.pBuffMat;
}

// ----------------------------------------
// �e�N�X�`���[���擾
// ----------------------------------------
LPDIRECT3DTEXTURE9 & CModel_info::GetTex(void)
{
	return m_model_info.pTexture;
}

// ----------------------------------------
// �}�e���A�������擾
// ----------------------------------------
DWORD & CModel_info::GetNumMat(void)
{
	return m_model_info.nNumMat;
}

// ----------------------------------------
// ���_���W�̍ŏ������擾
// ----------------------------------------
D3DXVECTOR3 & CModel_info::GetvtxMinMat(void)
{
	return m_model_info.vtxMinMaterials;
}

// ----------------------------------------
// ���_���W�̍ő吔���擾
// ----------------------------------------
D3DXVECTOR3 & CModel_info::GetvtxMaxMat(void)
{
	return m_model_info.vtxMaxMaterials;
}

// ----------------------------------------
// �ʒu���擾
// ----------------------------------------
D3DXVECTOR3 & CModel_info::GetPos(void)
{
	return m_model_info.pos;
}

// ----------------------------------------
// ��]���擾
// ----------------------------------------
D3DXVECTOR3 & CModel_info::GetRot(void)
{
	return m_model_info.rot;
}

// ----------------------------------------
// �e���擾
// ----------------------------------------
int & CModel_info::GetParent(void)
{
	return m_model_info.nParent;
}

// ----------------------------------------
// ���f���̃I�t�Z�b�g�̐ݒ�
// ----------------------------------------
void  CModel_info::ModelOffset(
	MODEL_OFFSET * pModel_offset,
	const char * file_name
	)
{
	// ��邱��
	// �t�@�C���|�C���g
	FILE *pFile;

	// �ϐ��錾
	int  nCntLoad = 0;
	int nCntPlayer = 0;
	int	nCntModel = 0;
	char cRaedText[128];	// �����Ƃ��ēǂݎ��p
	char cHeadText[128];	// ��r����悤
	char cDie[128];			// �s�K�v�ȕ���

	// �t�@�C���J
	pFile = fopen(file_name, "r");

	// �J����
	if (pFile != NULL)
	{
		// �X�N���v�g������܂Ń��[�v
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cRaedText, sizeof(cRaedText), pFile);	// �ꕶ��ǂݍ���
			sscanf(cRaedText, "%s", &cHeadText);		// ��r�p�e�N�X�g�ɕ�������
		}

		// �X�N���v�g��������
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			// �G���h�X�N���v�g������܂Ń��[�v
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cRaedText, sizeof(cRaedText), pFile);
				sscanf(cRaedText, "%s", &cHeadText);

				// ���s��������
				if (strcmp(cHeadText, "\n") == 0)
				{
				}

				// ���f���Z�b�g��������
				else if (strcmp(cHeadText, "PARTSSET") == 0)
				{
					// �G���h���f���Z�b�g������܂Ń��[�v
					while (strcmp(cHeadText, "END_PARTSSET") != 0)
					{
						fgets(cRaedText, sizeof(cRaedText), pFile);
						sscanf(cRaedText, "%s", &cHeadText);

						// �e���ǂݍ���
						if (strcmp(cHeadText, "PARENT") == 0)
						{
							sscanf(cRaedText, "%s %s %d", &cDie, &cDie,
								&pModel_offset[nCntModel].nParent);
						}

						// �ʒu���ǂݍ���
						else if (strcmp(cHeadText, "POS") == 0)
						{
							sscanf(cRaedText, "%s %s %f %f %f",
								&cDie, &cDie,
								&pModel_offset[nCntModel].pos.x,
								&pModel_offset[nCntModel].pos.y,
								&pModel_offset[nCntModel].pos.z);
						}

						// ��]���ǂݍ���
						else if (strcmp(cHeadText, "ROT") == 0)
						{
							sscanf(cRaedText, "%s %s %f %f %f", &cDie, &cDie,
								&pModel_offset[nCntModel].rot.x,
								&pModel_offset[nCntModel].rot.y,
								&pModel_offset[nCntModel].rot.z);
						}
					}
					// ���f���̍X�V
					nCntModel++;
				}
			}
		}
		// �t�@�C����
		fclose(pFile);
	}

	// �J���Ȃ�
	else
	{
		MessageBox(NULL, "�v���C���[�f�[�^�̓ǂݍ��݂Ɏ��s���܂���", "�x���I", MB_ICONWARNING);
	}
}
