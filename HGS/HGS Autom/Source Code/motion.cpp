//------------------------------------------------------------------------------
//
//���[�V��������  [motion.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "motion.h"
#include "renderer.h"
#include "manager.h"
#include "modelcharacter.h"

//------------------------------------------------------------------------------
// �}�N��
//------------------------------------------------------------------------------
#define MOTION_FILE_NAME ("data/SAVEDATA/MotionFIleName.txt")
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
std::vector<std::unique_ptr<CMotion::MOTION_INFO>> CMotion::m_pMotionInfoList = {};
std::vector<std::string> CMotion::m_apFileName = {};
//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CMotion::CMotion()
{
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CMotion::~CMotion()
{
}

//------------------------------------------------------------------------------
//���[�V�����ǂݍ���
//------------------------------------------------------------------------------
HRESULT CMotion::Load()
{
	//���[�V�����̃t�@�C�����擾
	LoadMotionFileName();

	//���X�g���J��Ԃ�
	for (size_t nCnt = 0; nCnt < m_apFileName.size(); nCnt++)
	{
		//�������m��
		std::unique_ptr<MOTION_INFO> pMotion(new MOTION_INFO);

		//�z��ɒǉ�
		m_pMotionInfoList.emplace_back(std::move(pMotion));

		//debug
		std::cout << "new MOTION_INFO : " << nCnt << "-";

		//���f���ǂݍ���
		if (FAILED(LoadMotion((CMotion::MOTION_TYPE)nCnt)))
		{
			//���s
			std::cout << "LoadMotion() [FAILED] : " << NEWLINE;		//����
			return E_FAIL;
		}
		else
		{
			std::cout << "LoadMotion() [Success] : " << NEWLINE;		//����
		}
		//���s
		std::cout << NEWLINE;
	}
	//����
	return S_OK;
}
//------------------------------------------------------------------------------
//���[�V�������j��
//------------------------------------------------------------------------------
void CMotion::UnLoad()
{

}

//------------------------------------------------------------------------------
//�f�o�b�O���o��
//------------------------------------------------------------------------------
void CMotion::ShowDebugInfo()
{
#ifdef _DEBUG



#endif //_DEBUG
}

//------------------------------------------------------------------------------
//�L�[�ǉ�
//------------------------------------------------------------------------------
void CMotion::AddKeyInfo(MOTION_TYPE NowMotion, int model)
{
	std::unique_ptr<KEY> pKey;						//���̃|�C���^
	std::unique_ptr<KEY_INFO> pKeyInfo;				//���̃|�C���^

	//�������m��
	pKeyInfo.reset(new KEY_INFO);

	//�z��ɒǉ�
	m_pMotionInfoList[NowMotion]->pKeyInfoList.emplace_back(std::move(pKeyInfo));

	//�L�[�����ǉ�
	for (int nCnt = 0; nCnt < CModelCharacter::GetModelNum((CModelCharacter::CHARACTER_TYPE) model) ; nCnt++)
	{
		//�������m��
		pKey.reset(new KEY);

		//�z��ɒǉ�
		m_pMotionInfoList[NowMotion]->pKeyInfoList[m_pMotionInfoList[NowMotion]->nNumKey - 1]->pKeyList.emplace_back(std::move(pKey));
	}
}
//------------------------------------------------------------------------------
//�L�[����
//------------------------------------------------------------------------------
void CMotion::PopbackKeyInfo(MOTION_TYPE NowMotion)
{
	m_pMotionInfoList[NowMotion]->pKeyInfoList.pop_back();
}


//------------------------------------------------------------------------------
//���[�V�����ǂݍ���
//------------------------------------------------------------------------------
HRESULT CMotion::LoadMotion(MOTION_TYPE motiontype)
{
	//�ϐ��錾
	FILE *pFile;					//�t�@�C���̃|�C���^
	char cReadText[MAX_TEXT] = {};
	char cHeadText[MAX_TEXT] = {};
	char cDieText[MAX_TEXT] = {};
	int nLoop = 0;						//���[�v���邩
	int nCntkeyInfo = 0;				//�L�[���
	int nCntKey = 0;					//�L�[
	int boolAttack = 0;					//�U�����邩

	std::unique_ptr<KEY> pKey;						//���̃|�C���^
	std::unique_ptr<KEY_INFO> pKeyInfo;				//���̃|�C���^

	//�t�@�C�����J��
	pFile = fopen(m_apFileName[motiontype].data(), "r");

	//debug ���f�����o��
	std::cout << "Name >> " << m_apFileName[motiontype].data() << NEWLINE;

	//�t�@�C�����������ꍇ
	if (pFile != NULL)
	{
		//�X�N���v�g������܂�
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile);
			sscanf(cReadText, "%s", &cHeadText);
		}
		//�X�N���v�g��������
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			//�G���h�X�N���v�g������O���[�v
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s", &cHeadText);
				//���s
				if (strcmp(cHeadText, "\n") == 0)
				{
				}

				//���[�v���邩
				if (strcmp(cHeadText, "LOOP") == 0)
				{
					sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &nLoop);		//��Uint�^�Ɋi�[
					m_pMotionInfoList[motiontype]->bLoop = nLoop ? true : false;				//0��1�����f
				}
				//�L�[��
				if (strcmp(cHeadText, "NUM_KEY") == 0)
				{
					sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &m_pMotionInfoList[motiontype]->nNumKey);
				}
				//�U�����邩
				if (strcmp(cHeadText, "ATTACK") == 0)
				{
					sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &boolAttack);

					//�U�����邩�ǂ����ݒ�
					m_pMotionInfoList[motiontype]->bAttack = boolAttack ? true : false;				//0��1�����f
				}

				//�U�����̐ݒ�
				else if (strcmp(cHeadText, "ATTACKSET") == 0)
				{
					//�������m��
					m_pMotionInfoList[motiontype]->pAttackInfo.reset(new ATTACK_INFO);

					//�G���h�A�^�b�N�Z�b�g������܂Ń��[�v
					while (strcmp(cHeadText, "END_ATTACKSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile);
						sscanf(cReadText, "%s", &cHeadText);

						//�U����
						if (strcmp(cHeadText, "ATTACK_VALUE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &m_pMotionInfoList[motiontype]->pAttackInfo->nAttack);
							std::cout << "AttackInfo - " << motiontype << " - ATTACK_VALUE - " << m_pMotionInfoList[motiontype]->pAttackInfo->nAttack << NEWLINE;
						}
						//�U����
						if (strcmp(cHeadText, "BLUEATTACK_VALUE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &m_pMotionInfoList[motiontype]->pAttackInfo->nBlueAttack);
							std::cout << "AttackInfo - " << motiontype << " - BLUEATTACK_VALUE - " << m_pMotionInfoList[motiontype]->pAttackInfo->nBlueAttack << NEWLINE;
						}
						//����̒���
						if (strcmp(cHeadText, "COLLISION_LENGTH") == 0)
						{
							sscanf(cReadText, "%s %s %f", &cDieText, &cDieText, &m_pMotionInfoList[motiontype]->pAttackInfo->fLength);
							std::cout << "AttackInfo - " << motiontype << " - COLLISION_LENGTH - " << m_pMotionInfoList[motiontype]->pAttackInfo->fLength << NEWLINE;
						}
						//����̔��a
						if (strcmp(cHeadText, "COLLISION_RADIUS") == 0)
						{
							sscanf(cReadText, "%s %s %f", &cDieText, &cDieText, &m_pMotionInfoList[motiontype]->pAttackInfo->fRadius);
							std::cout << "AttackInfo - " << motiontype << " - COLLISION_RADIUS - " << m_pMotionInfoList[motiontype]->pAttackInfo->fRadius << NEWLINE;
						}
						//����J�n
						if (strcmp(cHeadText, "COLLISION_START") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &m_pMotionInfoList[motiontype]->pAttackInfo->nStartCollisonKey);
							std::cout << "AttackInfo - " << motiontype << " - COLLISION_START - " << m_pMotionInfoList[motiontype]->pAttackInfo->nStartCollisonKey << NEWLINE;
						}
						//����I��
						if (strcmp(cHeadText, "COLLISION_END") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &m_pMotionInfoList[motiontype]->pAttackInfo->nEndCollisionKey);
							std::cout << "AttackInfo - " << motiontype << " - COLLISION_END - " << m_pMotionInfoList[motiontype]->pAttackInfo->nEndCollisionKey << NEWLINE;
						}
						//�ړ����x
						if (strcmp(cHeadText, "MOVE_KEY") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &m_pMotionInfoList[motiontype]->pAttackInfo->nMoveKey);
							std::cout << "AttackInfo - " << motiontype << " - MOVE_KEY - " << m_pMotionInfoList[motiontype]->pAttackInfo->nMoveKey << NEWLINE;
						}
						//�ړ����x
						if (strcmp(cHeadText, "MOVE_FRONT_VALUE") == 0)
						{
							sscanf(cReadText, "%s %s %f", &cDieText, &cDieText, &m_pMotionInfoList[motiontype]->pAttackInfo->fMoveFront);
							std::cout << "AttackInfo - " << motiontype << " - MOVE_FRONT_VALUE - " << m_pMotionInfoList[motiontype]->pAttackInfo->fMoveFront << NEWLINE;
						}
						//�ړ����x
						if (strcmp(cHeadText, "MOVE_UP_VALUE") == 0)
						{
							sscanf(cReadText, "%s %s %f", &cDieText, &cDieText, &m_pMotionInfoList[motiontype]->pAttackInfo->fMoveUp);
							std::cout << "AttackInfo - " << motiontype << " - MOVE_UP_VALUE - " << m_pMotionInfoList[motiontype]->pAttackInfo->fMoveUp << NEWLINE;
						}
						//�m�b�N�o�b�N�̈ړ���
						if (strcmp(cHeadText, "KNOCKBACK_FRONT_VALUE") == 0)
						{
							sscanf(cReadText, "%s %s %f", &cDieText, &cDieText, &m_pMotionInfoList[motiontype]->pAttackInfo->fKnockBack_Front);
							std::cout << "AttackInfo - " << motiontype << " - KNOCKBACK_FRONT_VALUE - " << m_pMotionInfoList[motiontype]->pAttackInfo->fKnockBack_Front << NEWLINE;
						}
						//�m�b�N�o�b�N�̈ړ���
						if (strcmp(cHeadText, "KNOCKBACK_UP_VALUE") == 0)
						{
							sscanf(cReadText, "%s %s %f", &cDieText, &cDieText, &m_pMotionInfoList[motiontype]->pAttackInfo->fKnockBack_Up);
							std::cout << "AttackInfo - " << motiontype << " - KNOCKBACK_UP_VALUE - " << m_pMotionInfoList[motiontype]->pAttackInfo->fKnockBack_Up << NEWLINE;
						}
						//�O�Ղ̐F
						if (strcmp(cHeadText, "ORBIT_COL") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f %f", &cDieText, &cDieText,
								&m_pMotionInfoList[motiontype]->pAttackInfo->orbitcol.r, &m_pMotionInfoList[motiontype]->pAttackInfo->orbitcol.g,
								&m_pMotionInfoList[motiontype]->pAttackInfo->orbitcol.b, &m_pMotionInfoList[motiontype]->pAttackInfo->orbitcol.a);
						}
					}
				}
				//���f���ԍ���������
				else if (strcmp(cHeadText, "KEYSET") == 0)
				{
					//�������m��
					pKeyInfo.reset(new KEY_INFO);

					//�z��ɒǉ�
					m_pMotionInfoList[motiontype]->pKeyInfoList.emplace_back(std::move(pKeyInfo));

					//�J�E���g���Z�b�g
					nCntKey = 0;

					//�G���h�p�[�c�Z�b�g������܂Ń��[�v
					while (strcmp(cHeadText, "END_KEYSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile);
						sscanf(cReadText, "%s", &cHeadText);

						//���s
						if (strcmp(cHeadText, "\n") == 0)
						{
						}

						//�t���[����
						else if (strcmp(cHeadText, "FRAME") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &m_pMotionInfoList[motiontype]->pKeyInfoList[nCntkeyInfo]->nFrame);
						}
						//�t���[����
						else if (strcmp(cHeadText, "HEIGHT") == 0)
						{
							sscanf(cReadText, "%s %s %f", &cDieText, &cDieText, &m_pMotionInfoList[motiontype]->pKeyInfoList[nCntkeyInfo]->fOriginHeight);
						}
						//�L�[��������
						else if (strcmp(cHeadText, "KEY") == 0)
						{
							//�������m��
							pKey.reset(new KEY);

							//�z��ɒǉ�
							m_pMotionInfoList[motiontype]->pKeyInfoList[nCntkeyInfo]->pKeyList.emplace_back(std::move(pKey));

							sscanf(cReadText, "%s %s %s %f %f %f", &cDieText, &cDieText, &cDieText,
								&m_pMotionInfoList[motiontype]->pKeyInfoList[nCntkeyInfo]->pKeyList[nCntKey]->rotDest.x,
								&m_pMotionInfoList[motiontype]->pKeyInfoList[nCntkeyInfo]->pKeyList[nCntKey]->rotDest.y,
								&m_pMotionInfoList[motiontype]->pKeyInfoList[nCntkeyInfo]->pKeyList[nCntKey]->rotDest.z);

							//�L�[���Z
							nCntKey++;
						}
						//�I��
						if (strcmp(cHeadText, "END_KEYSET") == 0)
						{
							//�L�[�����Z
							nCntkeyInfo++;
						}
					}
				}
			}
		}
		//�ۑ�����
		std::cout << "Load Succsess!!  LoadMotion()" << NEWLINE;

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{
		//�t�@�C�����J���܂���ł���
		std::cout << "Load FAILED!!  Can't Open File. LoadMotion()" << NEWLINE;
		return E_FAIL;
	}
	return S_OK;
}

//------------------------------------------------------------------------------
//�U�����邩�m�F
//------------------------------------------------------------------------------
bool CMotion::CheckAttackKey(MOTION_TYPE NowMotion, int nNowKey)
{
	if (m_pMotionInfoList[NowMotion]->bAttack)
	{
		if (nNowKey >= m_pMotionInfoList[NowMotion]->pAttackInfo->nStartCollisonKey && nNowKey <= m_pMotionInfoList[NowMotion]->pAttackInfo->nEndCollisionKey)
		{
			return true;
		}
	}
	return false;
}
//------------------------------------------------------------------------------
//���[�V�����̕ۑ�
//------------------------------------------------------------------------------
HRESULT CMotion::SaveMotion(MOTION_TYPE motiontype)
{
	FILE *pFile;

	int nRotNum = 0;
	char cHeadtext[128];
	char cWriteText[128];

	//�t�@�C���ǂݍ���
	pFile = fopen(m_apFileName[motiontype].data(), "w");

	//nullcheck
	if (pFile != nullptr)
	{
		//�u���b�N�R�����g
		fputs(COMMENT02, pFile);
		fputs(COMMENT01, pFile);

		strcpy(cHeadtext, "//Motion\n");
		fputs(cHeadtext, pFile);

		strcpy(cHeadtext, "//Author:Yoshiki Hosoya\n");
		fputs(cHeadtext, pFile);

		fputs(COMMENT01, pFile);
		fputs(COMMENT02, pFile);
		fputs(NEWLINE, pFile);

		//�u���b�N�R�����g�I��//

		//�X�N���v�g
		strcpy(cHeadtext, "SCRIPT");
		fputs(cHeadtext, pFile);
		fputs(NEWLINE, pFile);

		//���s
		fputs(NEWLINE, pFile);

		//���[�v
		strcpy(cHeadtext, "LOOP");
		sprintf(cWriteText, "	%s %s %d		%s", "LOOP", &EQUAL, m_pMotionInfoList[motiontype]->bLoop,	"//���[�v���邩�ǂ���");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		//�L�[��
		strcpy(cHeadtext, "NUM_KEY");
		sprintf(cWriteText, "	%s %s %d		%s", "NUM_KEY", &EQUAL, m_pMotionInfoList[motiontype]->nNumKey, "//�L�[��");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		//�U�����邩�ǂ���
		strcpy(cHeadtext, "ATTACK");
		sprintf(cWriteText, "	%s %s %d		%s","ATTACK", &EQUAL, m_pMotionInfoList[motiontype]->bAttack, "//�U�����邩�ǂ���");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);
		fputs(NEWLINE, pFile);

		//�U������ꍇ
		if (m_pMotionInfoList[motiontype]->bAttack)
		{
			//�A�^�b�N�Z�b�g
			fputs("	ATTACKSET", pFile);
			fputs(NEWLINE, pFile);

			//�U����
			sprintf(cWriteText, "		%s %s %d		%s", "ATTACK_VALUE", &EQUAL, m_pMotionInfoList[motiontype]->pAttackInfo->nAttack, "//�U����");
			fputs(cWriteText, pFile);
			fputs(NEWLINE, pFile);

			//�U���́i�j
			sprintf(cWriteText, "		%s %s %d		%s", "BLUEATTACK_VALUE", &EQUAL, m_pMotionInfoList[motiontype]->pAttackInfo->nBlueAttack, "//�U����");
			fputs(cWriteText, pFile);
			fputs(NEWLINE, pFile);

			//����̒���
			sprintf(cWriteText, "		%s %s %.1f		%s", "COLLISION_LENGTH", &EQUAL, m_pMotionInfoList[motiontype]->pAttackInfo->fLength, "//����̒���");
			fputs(cWriteText, pFile);
			fputs(NEWLINE, pFile);

			//����̔��a
			sprintf(cWriteText, "		%s %s %.1f		%s", "COLLISION_RADIUS", &EQUAL, m_pMotionInfoList[motiontype]->pAttackInfo->fRadius, "//����̔��a");
			fputs(cWriteText, pFile);
			fputs(NEWLINE, pFile);

			//����J�n
			sprintf(cWriteText, "		%s %s %d		%s", "COLLISION_START", &EQUAL, m_pMotionInfoList[motiontype]->pAttackInfo->nStartCollisonKey, "//����J�n�̃L�[");
			fputs(cWriteText, pFile);
			fputs(NEWLINE, pFile);

			//����I��
			sprintf(cWriteText, "		%s %s %d		%s", "COLLISION_END", &EQUAL, m_pMotionInfoList[motiontype]->pAttackInfo->nEndCollisionKey, "//����I���̃L�[");
			fputs(cWriteText, pFile);
			fputs(NEWLINE, pFile);

			//�ړ�����L�[
			sprintf(cWriteText, "		%s %s %d		%s", "MOVE_KEY", &EQUAL, m_pMotionInfoList[motiontype]->pAttackInfo->nMoveKey, "//�ړ�����L�[");
			fputs(cWriteText, pFile);
			fputs(NEWLINE, pFile);

			//�ړ���
			sprintf(cWriteText, "		%s %s %.1f		%s", "MOVE_FRONT_VALUE", &EQUAL, m_pMotionInfoList[motiontype]->pAttackInfo->fMoveFront, "//�O���̈ړ���");
			fputs(cWriteText, pFile);
			fputs(NEWLINE, pFile);

			//�ړ���
			sprintf(cWriteText, "		%s %s %.1f		%s", "MOVE_UP_VALUE", &EQUAL, m_pMotionInfoList[motiontype]->pAttackInfo->fMoveUp, "//�㉺�̈ړ���");
			fputs(cWriteText, pFile);
			fputs(NEWLINE, pFile);

			//�m�b�N�o�b�N
			sprintf(cWriteText, "		%s %s %.1f		%s", "KNOCKBACK_FRONT_VALUE", &EQUAL, m_pMotionInfoList[motiontype]->pAttackInfo->fKnockBack_Front, "//�m�b�N�o�b�N�̈ړ��ʁ@�O��");
			fputs(cWriteText, pFile);
			fputs(NEWLINE, pFile);

			//�m�b�N�o�b�N
			sprintf(cWriteText, "		%s %s %.1f		%s", "KNOCKBACK_UP_VALUE", &EQUAL, m_pMotionInfoList[motiontype]->pAttackInfo->fKnockBack_Up, "//�m�b�N�o�b�N�̈ړ��ʏ㉺");
			fputs(cWriteText, pFile);
			fputs(NEWLINE, pFile);

			//�O�Ղ̐F
			sprintf(cWriteText, "		%s %s %.1f %.1f %.1f %.1f		%s", "ORBIT_COL", &EQUAL, m_pMotionInfoList[motiontype]->pAttackInfo->orbitcol.r,
				m_pMotionInfoList[motiontype]->pAttackInfo->orbitcol.g,
				m_pMotionInfoList[motiontype]->pAttackInfo->orbitcol.b,
				m_pMotionInfoList[motiontype]->pAttackInfo->orbitcol.a, "//�O�Ղ̐F");
			fputs(cWriteText, pFile);
			fputs(NEWLINE, pFile);

			//�A�^�b�N�Z�b�g�I��
			fputs("	END_ATTACKSET", pFile);
			fputs(NEWLINE, pFile);
			fputs(NEWLINE, pFile);


		}

		//nullcheck
		if (!m_pMotionInfoList[motiontype]->pKeyInfoList.empty())
		{
			for (int nCnt = 0; nCnt < m_pMotionInfoList[motiontype]->nNumKey; nCnt++)
			{
				//�L�[�Z�b�g
				sprintf(cWriteText, "	KEYSET		//---< KEY : %d / %d >---", nCnt, m_pMotionInfoList[motiontype]->nNumKey);
				fputs(cWriteText, pFile);
				fputs(NEWLINE, pFile);

				//�t���[����
				sprintf(cWriteText, "		%s %s %d		%s", "FRAME", &EQUAL, m_pMotionInfoList[motiontype]->pKeyInfoList[nCnt]->nFrame, "//�t���[����");
				fputs(cWriteText, pFile);
				fputs(NEWLINE, pFile);

				//����
				sprintf(cWriteText, "		%s %s %.2f		%s", "HEIGHT", &EQUAL, m_pMotionInfoList[motiontype]->pKeyInfoList[nCnt]->fOriginHeight, "//���_�̍���");
				fputs(cWriteText, pFile);
				fputs(NEWLINE, pFile);

				fputs(NEWLINE, pFile);

				for (size_t nCntParts = 0; nCntParts < m_pMotionInfoList[motiontype]->pKeyInfoList[nCnt]->pKeyList.size(); nCntParts++)
				{
					//�L�[
					sprintf(cWriteText, "		KEY [%d] = %.3f %.3f %.3f", nCntParts, m_pMotionInfoList[motiontype]->pKeyInfoList[nCnt]->pKeyList[nCntParts]->rotDest.x,
					m_pMotionInfoList[motiontype]->pKeyInfoList[nCnt]->pKeyList[nCntParts]->rotDest.y, m_pMotionInfoList[motiontype]->pKeyInfoList[nCnt]->pKeyList[nCntParts]->rotDest.z);
					fputs(cWriteText, pFile);
					fputs(NEWLINE, pFile);

				}
			//�L�[�Z�b�g�I��
			fputs("	END_KEYSET", pFile);
			fputs(NEWLINE, pFile);
			fputs(NEWLINE, pFile);
			}

		}

		//�L�[�Z�b�g�I��
		fputs("END_SCRIPT", pFile);
		fputs(NEWLINE, pFile);

		//�ۑ�����
		std::cout << "Motion Save Succsess!! >>" << m_apFileName[motiontype].data() << NEWLINE;

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{
		//�t�@�C�����J���܂���ł���
		std::cout << "Motion Save FAILED!!  Can't Open File. SavePlaceData()" << NEWLINE;
		return E_FAIL;
	}
	return S_OK;
}
//------------------------------------------------------------------------------
//���[�V�����R�s�[
//------------------------------------------------------------------------------
void CMotion::MotionCopy(MOTION_TYPE Nowmotion, int NowKey, MOTION_TYPE CopyMotion, int CopyKey)
{
	//�͈͊O����Ȃ����ǂ���
	if (CopyMotion != CMotion::MOTION_NONE && CopyKey != -1)
	{
		//�R�s�[
		for (size_t nCnt = 0; nCnt < m_pMotionInfoList[Nowmotion]->pKeyInfoList[NowKey]->pKeyList.size(); nCnt++)
		{
			m_pMotionInfoList[Nowmotion]->pKeyInfoList[NowKey]->pKeyList[nCnt]->rotDest = m_pMotionInfoList[CopyMotion]->pKeyInfoList[CopyKey]->pKeyList[nCnt]->rotDest;
		}
	}
}
//------------------------------------------------------------------------------
//���[�V�����̃t�@�C�����擾
//------------------------------------------------------------------------------
void CMotion::LoadMotionFileName()
{
	//�ϐ��錾
	FILE *pFile;					//�t�@�C���̃|�C���^
	char cReadText[MAX_TEXT] = {};
	char cHeadText[MAX_TEXT] = {};
	char cDieText[MAX_TEXT] = {};

	//�t�@�C���ǂݍ���
	pFile = fopen(MOTION_FILE_NAME, "r");

	//nullcheck
	if (pFile != nullptr)
	{
		//�X�N���v�g������܂�
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile);
			sscanf(cReadText, "%s", &cHeadText);
		}
		//�X�N���v�g��������
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			//�G���h�X�N���v�g������O���[�v
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s", &cHeadText);
				//���s
				if (strcmp(cHeadText, "\n") == 0)
				{
				}

				//�t�@�C����
				if (strcmp(cHeadText, "FILENAME") == 0)
				{
					//���̕�����
					char aName[128] = {};

					//�t�@�C�������
					sscanf(cReadText, "%s %s %s %s %s", &cDieText, &cDieText, &aName, &cDieText, &cDieText);

					//�z��ɒǉ�
					m_apFileName.emplace_back(aName);

					//debug ���f�����o��
					std::cout << "Name >> " << aName << NEWLINE;
				}
			}
		}

		//�ۑ�����
		std::cout << "Load Succsess!!  LoadMotionFileName()" << NEWLINE;

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{
		//�t�@�C�����J���܂���ł���
		std::cout << "Load FAILED!!  Can't Open File. LoadMotionFileName()" << NEWLINE;
	}
}