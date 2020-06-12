// =====================================================================================================================================================================
//
// ���f���L�����N�^�[�̏��� [modelcharacter.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "modelcharacter.h"			// �C���N���[�h�t�@�C��
#include "debugproc.h"
#include "manager.h"
#include "renderer.h"
#include "partsmodel.h"
#include "motion.h"

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define SPEED				(1.0f)						// �ړ����x
#define PLAYER_FILE_NAME			("data/FILE/PLAYER_MODEL/PlayerModel0.txt")		// �Z�[�u�t�@�C��

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
LPDIRECT3DVERTEXBUFFER9				CModelCharacter::m_pVtxBuff				= NULL;
LPD3DXMESH							CModelCharacter::m_pMesh				= NULL;
LPD3DXBUFFER						CModelCharacter::m_pBuffMat				= NULL;
DWORD								CModelCharacter::m_nNumMat				= NULL;
CModelCharacter::PlayerMotionType	CModelCharacter::m_PlayerMotionType		= PlayerMotionType_NEUTRAL;
CModelCharacter::PlayerMotionType	CModelCharacter::m_PlayerMotionTypeOld	= PlayerMotionType_NEUTRAL;
int									CModelCharacter::m_nFrame				= 0;
int									CModelCharacter::m_nKeySet				= 0;

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CModelCharacter::CModelCharacter()
{
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CModelCharacter::~CModelCharacter()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
void CModelCharacter::Init(void)
{
	// ������
	for (int nCntParts = 0; nCntParts < PLAYER_PARTS; nCntParts++)
	{
		m_pModel[nCntParts] = CPartsModel::Create();		// �p�[�c���f���̐���
	}

	m_nFrame	= 0;			// �t���[����
	m_nKeySet	= 0;			// ���݂̃L�[

	// ���f���̓ǂݍ���
	ModelLoad();
}

// =====================================================================================================================================================================
//
// �I������
//
// =====================================================================================================================================================================
void CModelCharacter::Uninit(void)
{
	for (int nCntParts = 0; nCntParts < PLAYER_PARTS; nCntParts++)
	{
		m_pModel[nCntParts]->Uninit();

		delete m_pModel[nCntParts];
		m_pModel[nCntParts] = NULL;
	}
}

// =====================================================================================================================================================================
//
// �X�V����
//
// =====================================================================================================================================================================
void CModelCharacter::Update(void)
{
	// �O��̃��[�V�������
	m_PlayerMotionTypeOld = m_PlayerMotionType;

	// ���[�V�����̍X�V
	MotionUpdate();

	for (int nCntParts = 0; nCntParts < PLAYER_PARTS; nCntParts++)
	{
		m_pModel[nCntParts]->Update();
	}
}

// =====================================================================================================================================================================
//
// �`�揈��
//
// =====================================================================================================================================================================
void CModelCharacter::Draw(void)
{	
	for (int nCntParts = 0; nCntParts < PLAYER_PARTS; nCntParts++)
	{
		m_pModel[nCntParts]->Draw();
	}
}

// =====================================================================================================================================================================
//
// ���f���̐���
//
// =====================================================================================================================================================================
CModelCharacter * CModelCharacter::Create()
{
	// �ϐ�
	CModelCharacter *pModelCharacter;

	// �������̊m��
	pModelCharacter = new CModelCharacter;

	// ������
	pModelCharacter->Init();

	return pModelCharacter;
}

// =====================================================================================================================================================================
//
// ���[���h�}�g���b�N�X�̐ݒ�
//
// =====================================================================================================================================================================
void CModelCharacter::SetMatrix(D3DXMATRIX *mtx)
{
	for (int nCntParts = 0; nCntParts < PLAYER_PARTS; nCntParts++)
	{
		if (m_pModel[nCntParts]->GetParent() >= 0)
		{
			//�e��world�}�g���b�N�X�̃|�C���^�擾
			m_pModel[nCntParts]->SetParentWorldMatrix(m_pModel[m_pModel[nCntParts]->GetParent()]->GetMatrix());
		}
		else
		{
			//�e��world�}�g���b�N�X�̃|�C���^�擾
			m_pModel[nCntParts]->SetParentWorldMatrix(mtx);
		}
	}
}

// =====================================================================================================================================================================
//
// ���[�V�����̐ݒ�
//
// =====================================================================================================================================================================
void CModelCharacter::SetMotion(PlayerMotionType MotionType)
{
	// ���݂̃��[�V�������
	m_PlayerMotionType = MotionType;

	// ���݂ƑO��̏�񂪓�������Ȃ������珉����
	if (m_PlayerMotionType != m_PlayerMotionTypeOld)
	{
		m_nFrame = 0;
		m_nKeySet = 0;

		for (int nCntParts = 0; nCntParts < PLAYER_PARTS; nCntParts++)
		{
			// �v���C���[�̃��[�V����
			m_pModel[nCntParts]->SetMotionPlayer(m_PlayerMotionType, m_nKeySet);
		}
	}

}

// =====================================================================================================================================================================
//
// ���f���̓ǂݍ���
//
// =====================================================================================================================================================================
void CModelCharacter::ModelLoad(void)
{
	// �t�@�C���|�C���g
	FILE *pFile;

	char		cReadText[128];			// �����Ƃ��ēǂݎ��
	char		cHeadText[128];			// ��r�p
	char		cDie[128];				// �s�v�ȕ���
	D3DXVECTOR3 pos				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu
	int			nIndex			= 0;	// �C���f�b�N�X
	int			nParent			= 0;	// �e
	int			nCntParts		= 0;	// �p�[�c�J�E���g

	// �t�@�C�����J��
	pFile = fopen(PLAYER_FILE_NAME, "r");

	// �J���Ă���
	if (pFile != NULL)
	{
		// SCRIPT������܂Ń��[�v
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
			sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������
		}

		// SCRIPT��������
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			// END_SCRIPT������܂Ń��[�v
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
				sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

				// PARTSSET��������
				if (strcmp(cHeadText, "PARTSSET") == 0)
				{
					// END_PARTSSET������܂Ń��[�v
					while (strcmp(cHeadText, "END_PARTSSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
						sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

						// POS��������
						if (strcmp(cHeadText, "POS") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &pos.x, &pos.y, &pos.z);		// ��r�p�e�L�X�g��POS����
						}
						// INDEX��������
						else if (strcmp(cHeadText, "INDEX") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nIndex);		// ��r�p�e�L�X�g��INDEX����
						}
						// PARENT��������
						else if (strcmp(cHeadText, "PARENT") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nParent);		// ��r�p�e�L�X�g��PARENT����
						}
						else if (strcmp(cHeadText, "END_PARTSSET") == 0)
						{
							// �ʒu�̐ݒ�
							m_pModel[nCntParts]->SetPos(pos);

							// �C���f�b�N�X�̐ݒ�
							m_pModel[nCntParts]->SetIndex(nIndex);

							// �e�̐ݒ�
							m_pModel[nCntParts]->SetParent(nParent);

							// �J�E���g�A�b�v
							nCntParts++;
						}
					}
				}
			}
		}
	}
}

// =====================================================================================================================================================================
//
// ���[�V�����̍X�V
//
// =====================================================================================================================================================================
void CModelCharacter::MotionUpdate(void)
{
	int nFlame = CMotion::GetMotionFrame(m_PlayerMotionType, m_nKeySet);
	int nNumKey = CMotion::GetMotionNumKey(m_PlayerMotionType);
	int nLoop = CMotion::GetMotionLoop(m_PlayerMotionType);

	// �v���C���[�ƃ��[�V�����̃t���[�����������Ƃ�
	if (m_nFrame == nFlame)
	{
		// �L�[�Z�b�g�X�V
		m_nKeySet++;

		// �v���C���[�ƃ��[�V�����̃L�[�Z�b�g���������Ƃ�
		if (m_nKeySet == nNumKey)
		{
			m_nKeySet = 0;											// �L�[�Z�b�g�J�E���g���Z�b�g

			// ���[�v���Ȃ��Ƃ�
			if (nLoop == 0)
			{
				m_PlayerMotionType = PlayerMotionType_NEUTRAL;		// �v���C���[�̃��[�V�������j���[�g������

				m_nFrame = CMotion::GetMotionFrame(m_PlayerMotionType, m_nKeySet);		// �t���[������ݒ�
			}
			else
			{// ���[�v����Ƃ�
			}
		}
		if (m_nKeySet < nNumKey)
		{
			for (int nCntParts = 0; nCntParts < PLAYER_PARTS; nCntParts++)
			{
				// �v���C���[�̃��[�V����
				m_pModel[nCntParts]->SetMotionPlayer(m_PlayerMotionType, m_nKeySet);
			}

			m_nFrame = 0;		// �v���C���[�̃t���[���������Z�b�g
		}
	}
	else
	{
		// �J�E���g�A�b�v
		m_nFrame++;
	}

	// �f�o�b�O�\��
	CDebugProc::Print("Flame: %d\n", m_nFrame);
	CDebugProc::Print("NumKey: %d\n", m_nKeySet);
	CDebugProc::Print("Loop: %d\n", nLoop);
	CDebugProc::Print("Type: %d\n\n", m_PlayerMotionType);
}