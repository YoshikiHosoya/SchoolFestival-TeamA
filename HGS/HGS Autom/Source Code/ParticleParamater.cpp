//------------------------------------------------------------------------------
//
//�p�[�e�B�N���̃p�����[�^�N���X  [particleparamater.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "ParticleParamater.h"
#include "manager.h"
#include "renderer.h"
#include "collision.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
std::vector<std::unique_ptr<CParticleParam>> CParticleParam::m_pParticleDefaultParamList = {};
FILENAME_LIST CParticleParam::m_aFileNameList =
{
	{ "data/Load/EffectParam/Default.txt" },
	{ "data/Load/EffectParam/CountDown.txt" },
	{ "data/Load/EffectParam/Circle.txt" },
	{ "data/Load/EffectParam/triangle.txt" },
	{ "data/Load/EffectParam/square.txt" },
	{ "data/Load/EffectParam/star.txt" },
	{ "data/Load/EffectParam/cross.txt" },
	{ "data/Load/EffectParam/PlayerEngine.txt" },
	{ "data/Load/EffectParam/PlayerDeath01.txt" },
	{ "data/Load/EffectParam/PlayerDeath02.txt" },


};
//
//FILENAME_LIST CParticleCreators::m_aFileNameList =
//{
//	{ "data/Load/Effect/Creator/Default.txt" },
//};

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CParticleParam::CParticleParam()
{

	m_bGravity = false;														//�d��
	m_bSpeedRandom = false;													//���x�������_�����ǂ���
	m_bAlphaBlend_Add = true;												//���u�����h���邩
	m_bAlphaBlend_Sub = false;												//���u�����h���邩
	m_bZtest = false;														//Z�e�X�g
	m_bZWrite = true;														//Z���C�e�B���O
	m_bBillboard = false;													//�r���{�[�h
	m_bFollowing = false;													//�Ǐ]���邩
	m_nLife = 50;															//���C�t
	m_nNumber = 10;															//��
	m_fSpeed = 10.0f;														//���x
	m_fConeRange = 0.5f;													//�͈�
	m_fAlphaDamping = DEFAULT_DAMPING;										//�A���t�@�l�̌����l
	m_fGravityPower = DEFAULT_GRAVITY_POWER;								//�d�͂̑傫��

	m_Size = D3DXVECTOR3(15.0f, 15.0f, 0.0f);								//�T�C�Y
	m_SizeDamping = D3DXVECTOR3(DEFAULT_DAMPING, DEFAULT_DAMPING, 0.0f);	//�T�C�Y�̌����n
	m_col = WhiteColor;														//�F
	m_rot = ZeroVector3;													//�p�x

	m_LocalPos = ZeroVector3;												//���[�J�����W
	m_LocalPosRandomRange = ZeroVector3;									//���[�J�����W�������_�����̒l�͈̔�

	m_bAnimation = false;													//�A�j���[�V�������邩�ǂ���
	m_bAnimationLoop = false;												//�A�j���[�V�������[�v���邩�ǂ���
	m_nAnimationCntSwitch = 1;												//�A�j���[�V�����ؑւ̃J�E���g

	m_CollisionSize = m_Size;												//�����蔻��̑傫��
	m_bCollision = false;													//�����蔻�肠�邩
	m_bPenetration = true;
	m_bCollisionSizeCalc = false;											//�����蔻�萶�����ɃT�C�Y���v�Z���邩�ǂ����@ShotGun�Ƃ��ɕK�v
	m_nCollisionAttackValue = 1;											//�U����
	m_nCollisionCnt = 10;													//��������鎞��

	m_Textype = CTexture::TEX_EFFECT_PARTICLE;								//�e�N�X�`��
	m_SeparateTex = CTexture::SEPARATE_TEX_EFFECT_EXPLOSION00;				//�����e�N�X�`��
	m_shape = SHAPE_SPHERE;													//�p�[�e�B�N���̕���
	m_ParticleType = EFFECT_DEFAULT;										//�p�[�e�B�N���̃^�C�v
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CParticleParam::~CParticleParam()
{
}

//------------------------------------------------------------------------------
//�e�L�X�g����p�����[�^�擾
//------------------------------------------------------------------------------
HRESULT CParticleParam::LoadParticleDefaultParam()
{
	//�t�@�C���|�C���g
	FILE *pFile;
	char cReadText[128];	//�����Ƃ��ēǂݎ��pk
	char cHeadText[128];	//��r����p
	char cDie[128];			//�s�v�ȕ���
	int n_BoolValue;		//bool�ɕϊ�����悤�̊i�[
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


							//���ꂼ��̍��ڂ�ǂݍ���
							if (strcmp(cHeadText, "SPEEDRANDOM") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &n_BoolValue);
								pParam->m_bSpeedRandom = n_BoolValue ? true : false;
							}
							if (strcmp(cHeadText, "GRAVITY") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &n_BoolValue);
								pParam->m_bGravity = n_BoolValue ? true : false;
							}
							if (strcmp(cHeadText, "ALPHABLEND_ADD") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &n_BoolValue);
								pParam->m_bAlphaBlend_Add = n_BoolValue ? true : false;
							}
							if (strcmp(cHeadText, "ALPHABLEND_SUB") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &n_BoolValue);
								pParam->m_bAlphaBlend_Sub = n_BoolValue ? true : false;
							}
							if (strcmp(cHeadText, "ZTEST") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &n_BoolValue);
								pParam->m_bZtest = n_BoolValue ? true : false;
							}
							if (strcmp(cHeadText, "ZWRITE") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &n_BoolValue);
								pParam->m_bZWrite = n_BoolValue ? true : false;
							}
							if (strcmp(cHeadText, "BILLBOARD") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &n_BoolValue);
								pParam->m_bBillboard = n_BoolValue ? true : false;
							}
							if (strcmp(cHeadText, "FOLLOWING") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &n_BoolValue);
								pParam->m_bFollowing = n_BoolValue ? true : false;
							}
							if (strcmp(cHeadText, "ANIMATION") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &n_BoolValue);
								pParam->m_bAnimation = n_BoolValue ? true : false;
							}
							if (strcmp(cHeadText, "ANIMATION_LOOP") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &n_BoolValue);
								pParam->m_bAnimationLoop = n_BoolValue ? true : false;
							}
							if (strcmp(cHeadText, "ANIMATION_CNTSWITCH") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pParam->m_nAnimationCntSwitch);
							}
							if (strcmp(cHeadText, "COLLISION") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &n_BoolValue);
								pParam->m_bCollision = n_BoolValue ? true : false;
							}
							if (strcmp(cHeadText, "COLLISION_SIZE_CALC") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &n_BoolValue);
								pParam->m_bCollisionSizeCalc = n_BoolValue ? true : false;
							}
							if (strcmp(cHeadText, "COLLISION_ATTACK_VALUE") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pParam->m_nCollisionAttackValue);
							}
							if (strcmp(cHeadText, "PENETRATION") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &n_BoolValue);
								pParam->m_bPenetration = n_BoolValue ? true : false;
							}
							if (strcmp(cHeadText, "COLLISION_COUNT") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pParam->m_nCollisionCnt);
							}
							if (strcmp(cHeadText, "COLLISION_SIZE") == 0)
							{
								sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
									&pParam->m_CollisionSize.x, &pParam->m_CollisionSize.y, &pParam->m_CollisionSize.z);
							}
							if (strcmp(cHeadText, "TEXTURE") == 0)
							{
								//�A�j���[�V�������邩�ǂ����ő������ꏊ���ς��
								//�ʏ�e�N�X�`���������e�N�X�`����
								pParam->m_bAnimation ?
									sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pParam->m_SeparateTex) :
									sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pParam->m_Textype);
							}
							if (strcmp(cHeadText, "SHAPE") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pParam->m_shape);
							}
							if (strcmp(cHeadText, "LIFE") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pParam->m_nLife);
							}
							if (strcmp(cHeadText, "NUMBER") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pParam->m_nNumber);
							}
							if (strcmp(cHeadText, "SPEED") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDie, &cDie, &pParam->m_fSpeed);
							}
							if (strcmp(cHeadText, "RANGE") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDie, &cDie, &pParam->m_fConeRange);
							}
							if (strcmp(cHeadText, "ALPHADAMPING") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDie, &cDie, &pParam->m_fAlphaDamping);
							}
							if (strcmp(cHeadText, "GRAVITYPOWER") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDie, &cDie, &pParam->m_fGravityPower);
							}
							if (strcmp(cHeadText, "SIZE") == 0)
							{
								sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
									&pParam->m_Size.x, &pParam->m_Size.y, &pParam->m_Size.z);
							}
							if (strcmp(cHeadText, "SIZEDAMPING") == 0)
							{
								sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
									&pParam->m_SizeDamping.x, &pParam->m_SizeDamping.y, &pParam->m_SizeDamping.z);
							}
							if (strcmp(cHeadText, "COLOR") == 0)
							{
								sscanf(cReadText, "%s %s %f %f %f %f", &cDie, &cDie,
										&pParam->m_col.r, &pParam->m_col.g, &pParam->m_col.b, &pParam->m_col.a);
							}
							if (strcmp(cHeadText, "LOCALPOS") == 0)
							{
								sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
									&pParam->m_LocalPos.x, &pParam->m_LocalPos.y, &pParam->m_LocalPos.z);
							}
							if (strcmp(cHeadText, "LOCALPOS_RANGE") == 0)
							{
								sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
									&pParam->m_LocalPosRandomRange.x, &pParam->m_LocalPosRandomRange.y, &pParam->m_LocalPosRandomRange.z);
							}
							if (strcmp(cHeadText, "ROT") == 0)
							{
								sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
									&pParam->m_rot.x, &pParam->m_rot.y, &pParam->m_rot.z);
							}
							if (strcmp(cHeadText, "END_PARAMSET") == 0)
							{
								pParam->m_ParticleType = (CParticleParam::PARTICLE_TYPE)nCnt;
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
			std::cout << "LoadFailed!!  >>" << m_aFileNameList[nCnt].data() << NEWLINE;
			MessageBox(NULL, "�p�[�e�B�N���̃p�����[�^�ǂݍ��ݎ��s", "�x��", MB_ICONWARNING);
			hResult = E_FAIL;
		}
	}
	return S_OK;
}

//------------------------------------------------------------------------------
//�p�[�e�B�N���̃p�����[�^�ۑ�
//------------------------------------------------------------------------------
HRESULT CParticleParam::SaveParticleDefaultParam(CParticleParam *pSaveParam,std::string aSaveFileName)
{
	FILE *pFile;

	int nRotNum = 0;
	char cWriteText[128];

	//�t�@�C���ǂݍ���
	pFile = fopen(aSaveFileName.data(), "w");

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


		//���ꂼ��̍��ڏ����o��
		sprintf(cWriteText, "		%s %s %d							%s", "SPEEDRANDOM", &EQUAL, pSaveParam->m_bSpeedRandom, "//���x�������_�����ǂ���");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %d								%s", "GRAVITY", &EQUAL, pSaveParam->m_bGravity, "//�d�͂����邩");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %d						%s", "ALPHABLEND_ADD", &EQUAL, pSaveParam->m_bAlphaBlend_Add, "//���Z�������邩");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %d						%s", "ALPHABLEND_SUB", &EQUAL, pSaveParam->m_bAlphaBlend_Sub, "//���Z�������邩");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %d								%s", "ZTEST", &EQUAL, pSaveParam->m_bZtest, "//Z�e�X�g���邩");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %d								%s", "ZWRITE", &EQUAL, pSaveParam->m_bZWrite, "//Z���C�e�B���O���邩");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %d							%s", "BILLBOARD", &EQUAL, pSaveParam->m_bBillboard, "//�r���{�[�h���邩");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %d							%s", "FOLLOWING", &EQUAL, pSaveParam->m_bFollowing, "//�Ǐ]���邩");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %d							%s", "ANIMATION", &EQUAL, pSaveParam->m_bAnimation, "//�A�j���[�V�������邩");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %d							%s", "COLLISION", &EQUAL, pSaveParam->m_bCollision, "//�����蔻�肪���邩�ǂ���");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		//�A�j���[�V�������邩���Ȃ����Ńe�N�X�`���ԍ��ύX
		//�ʏ�̃e�N�X�`���������e�N�X�`����
		int TexID = pSaveParam->m_bAnimation ?
			pSaveParam->m_SeparateTex : pSaveParam->m_Textype;
		sprintf(cWriteText, "		%s %s %d							%s", "TEXTURE", &EQUAL, TexID, "//�e�N�X�`��");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		//�A�j���[�V����������ꍇ
		if (pSaveParam->m_bAnimation)
		{
			sprintf(cWriteText, "		%s %s %d						%s", "ANIMATION_LOOP", &EQUAL, pSaveParam->m_bAnimationLoop, "//�A�j���[�V�������[�v���邩");
			fputs(cWriteText, pFile);
			fputs(NEWLINE, pFile);

			sprintf(cWriteText, "		%s %s %d					%s", "ANIMATION_CNTSWITCH", &EQUAL, pSaveParam->m_nAnimationCntSwitch, "//�ؑւ̃J�E���g");
			fputs(cWriteText, pFile);
			fputs(NEWLINE, pFile);
		}

		//�R���W����������ꍇ
		if (pSaveParam->m_bCollision)
		{
			sprintf(cWriteText, "		%s %s %d					%s", "COLLISION_SIZE_CALC", &EQUAL, pSaveParam->m_bCollisionSizeCalc, "//�R���W�����̃T�C�Y�̌v�Z");
			fputs(cWriteText, pFile);
			fputs(NEWLINE, pFile);

			sprintf(cWriteText, "		%s %s %d				%s", "COLLISION_ATTACK_VALUE", &EQUAL, pSaveParam->m_nCollisionAttackValue, "//�U����");
			fputs(cWriteText, pFile);
			fputs(NEWLINE, pFile);

			sprintf(cWriteText, "		%s %s %d					%s", "COLLISION_COUNT", &EQUAL, pSaveParam->m_nCollisionCnt, "//����̃J�E���g");
			fputs(cWriteText, pFile);
			fputs(NEWLINE, pFile);

			sprintf(cWriteText, "		%s %s %d					%s", "PENETRATION", &EQUAL, pSaveParam->m_bPenetration, "//�ђʂ��邩�ǂ���");
			fputs(cWriteText, pFile);
			fputs(NEWLINE, pFile);

			sprintf(cWriteText, "		%s %s %.2f %.2f %.2f		%s", "COLLISION_SIZE", &EQUAL,
				pSaveParam->m_CollisionSize.x, pSaveParam->m_CollisionSize.y, pSaveParam->m_CollisionSize.z, "//�R���W�����̃T�C�Y");
			fputs(cWriteText, pFile);
			fputs(NEWLINE, pFile);
		}

		sprintf(cWriteText, "		%s %s %d								%s", "SHAPE", &EQUAL, pSaveParam->m_shape, "//�p�[�e�B�N���̏o����");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %d								%s", "LIFE", &EQUAL, pSaveParam->m_nLife, "//���C�t");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %d								%s", "NUMBER", &EQUAL, pSaveParam->m_nNumber, "//��");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %.1f								%s", "SPEED", &EQUAL, pSaveParam->m_fSpeed, "//���x");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %.1f								%s", "RANGE", &EQUAL, pSaveParam->m_fConeRange, "//�͈�");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %.2f						%s", "ALPHADAMPING", &EQUAL, pSaveParam->m_fAlphaDamping, "//�A���t�@�l�̌����l");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %.2f						%s", "GRAVITYPOWER", &EQUAL, pSaveParam->m_fGravityPower, "//�d�͂̋���");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %.2f %.2f %.2f				%s", "LOCALPOS", &EQUAL,
			pSaveParam->m_LocalPos.x, pSaveParam->m_LocalPos.y, pSaveParam->m_LocalPos.z, "//���[�J�����W");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %.2f %.2f %.2f			%s", "LOCALPOS_RANGE", &EQUAL,
			pSaveParam->m_LocalPosRandomRange.x, pSaveParam->m_LocalPosRandomRange.y, pSaveParam->m_LocalPosRandomRange.z, "//���[�J�����W�������_�����̒l�͈̔�");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %.2f %.2f %.2f				%s", "SIZE", &EQUAL,
			pSaveParam->m_Size.x, pSaveParam->m_Size.y, pSaveParam->m_Size.z, "//�T�C�Y");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %.2f %.2f %.2f			%s", "SIZEDAMPING", &EQUAL,
			pSaveParam->m_SizeDamping.x, pSaveParam->m_SizeDamping.y, pSaveParam->m_SizeDamping.z, "//�T�C�Y������");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %.1f %.1f %.1f %.1f					%s", "COLOR", &EQUAL,
			pSaveParam->m_col.r, pSaveParam->m_col.g, pSaveParam->m_col.b, pSaveParam->m_col.a, "//�F");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %.2f %.2f %.2f					%s", "ROT", &EQUAL,
				pSaveParam->m_rot.x, pSaveParam->m_rot.y, pSaveParam->m_rot.z, "//��]��");
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
		std::cout << "ParticleParam Save Succsess!! >>" << aSaveFileName.data() << NEWLINE;

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{
		//�t�@�C�����J���܂���ł���
		std::cout << "ParticleParam Save FAILED!!  Can't Open File. SaveParticleDefaultParam()" << aSaveFileName.data() << NEWLINE;
		return E_FAIL;
	}
	return S_OK;
}


//------------------------------------------------------------------------------
//�R���{�{�b�N�X
//------------------------------------------------------------------------------
bool CParticleParam::ShowParamConboBox(CParticleParam::PARTICLE_TYPE &rType)
{
	bool bChange = false;

#ifdef _DEBUG
	//combo�J�n
	if (ImGui::BeginCombo("ParamFileName", m_aFileNameList[rType].data()))
	{
		//�v�f���J��Ԃ�
		for (size_t nCnt = 0; nCnt < m_aFileNameList.size(); nCnt++)
		{

			//�I��ԍ��������Ă邩�ǂ���
			bool is_selected = (m_aFileNameList[rType] == m_aFileNameList[nCnt]);

			//�I�����ꂽ���̏���
			if (ImGui::Selectable(m_aFileNameList[nCnt].data(), is_selected))
			{
				//���݂̑I�����ڐݒ�
				rType = (CParticleParam::PARTICLE_TYPE)nCnt;
				bChange = true;
			}
		}
		//combo�I��
		ImGui::EndCombo();

	}
#endif //DEBUG
	return bChange;
}

//------------------------------------------------------------------------------
//�p�����[�^�ݒ�
//------------------------------------------------------------------------------
void CParticleParam::SetParamater(int nLife, D3DXVECTOR3 size, D3DXCOLOR col, int nNumber, float fSpeed)
{
	m_nLife = nLife;
	m_Size = size;
	m_col = col;

	m_nNumber = nNumber;
	m_fSpeed = fSpeed;
}


//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CParticleParam::UpdateParam()
{
	m_nLife--;
	m_Size.x *= m_SizeDamping.x;
	m_Size.y *= m_SizeDamping.y;
	m_Size.z *= m_SizeDamping.z;

	m_col.a *= m_fAlphaDamping;
}


//------------------------------------------------------------------------------
//�I�y���[�^
//�N���X�̃p�����[�^���ۂ��Ƒ���ł���悤��
//�l���R�s�[���ēn���Ă���
//�|�C���^���m
//------------------------------------------------------------------------------
void * CParticleParam::operator=(const CParticleParam * pParam)
{
	m_ParticleType				= pParam->m_ParticleType;
	m_shape						= pParam->m_shape;
	m_bAlphaBlend_Add			= pParam->m_bAlphaBlend_Add;
	m_bAlphaBlend_Sub			= pParam->m_bAlphaBlend_Sub;
	m_bZtest					= pParam->m_bZtest;
	m_bZWrite					= pParam->m_bZWrite;
	m_bBillboard				= pParam->m_bBillboard;
	m_bFollowing				= pParam->m_bFollowing;
	m_bAnimation				= pParam->m_bAnimation;
	m_bAnimationLoop			= pParam->m_bAnimationLoop;
	m_nAnimationCntSwitch		= pParam->m_nAnimationCntSwitch;
	m_nLife						= pParam->m_nLife;
	m_Size						= pParam->m_Size;
	m_col						= pParam->m_col;
	m_nNumber					= pParam->m_nNumber;
	m_fSpeed					= pParam->m_fSpeed;
	m_bSpeedRandom				= pParam->m_bSpeedRandom;
	m_fAlphaDamping				= pParam->m_fAlphaDamping;
	m_SizeDamping				= pParam->m_SizeDamping;
	m_bGravity					= pParam->m_bGravity;
	m_fGravityPower				= pParam->m_fGravityPower;
	m_rot						= pParam->m_rot;
	m_fConeRange				= pParam->m_fConeRange;
	m_Textype					= pParam->m_Textype;
	m_SeparateTex				= pParam->m_SeparateTex;
	m_CollisionSize				= pParam->m_CollisionSize;
	m_bCollision				= pParam->m_bCollision;
	m_bPenetration				= pParam->m_bPenetration;
	m_bCollisionSizeCalc		= pParam->m_bCollisionSizeCalc;
	m_nCollisionAttackValue		= pParam->m_nCollisionAttackValue;
	m_nCollisionCnt				= pParam->m_nCollisionCnt;
	m_LocalPosRandomRange		= pParam->m_LocalPosRandomRange;
	m_LocalPos					= pParam->m_LocalPos;

	return this;
}

////------------------------------------------------------------------------------
////�p�����[�^�ݒ�
////------------------------------------------------------------------------------
//void CParticleCreators::LoadParticleCreators()
//{
//	////�t�@�C���|�C���g
//	//FILE *pFile;
//	//char cReadText[128];	//�����Ƃ��ēǂݎ��p
//	//char cHeadText[128];	//��r����p
//	//char cDie[128];			//�s�v�ȕ���
//	//int n_BoolValue;		//bool�ɕϊ�����悤�̊i�[
//	//HRESULT hResult = S_OK;
//
//	//CParticleCreators *pCreator;
//
//	////�t�@�C������
//	//for (size_t nCnt = 0; nCnt < m_aFileNameList.size(); nCnt++)
//	//{
//	//	//�t�@�C���ǂݍ���
//	//	pFile = fopen(m_aFileNameList[nCnt].data(), "r");
//
//	//	//�t�@�C�����J������
//	//	if (pFile != NULL)
//	//	{
//	//		//�X�N���v�g������܂Ń��[�v
//	//		while (strcmp(cHeadText, "SCRIPT") != 0)
//	//		{
//	//			fgets(cReadText, sizeof(cReadText), pFile);	//�ꕶ��ǂݍ���
//	//			sscanf(cReadText, "%s", &cHeadText);		//��r�p�e�L�X�g�ɕ�������
//	//		}
//	//		//�X�N���v�g��������
//	//		if (strcmp(cHeadText, "SCRIPT") == 0)
//	//		{
//	//			//�G���h�X�N���v�g������܂Ń��[�v
//	//			while (strcmp(cHeadText, "END_SCRIPT") != 0)
//	//			{
//	//				fgets(cReadText, sizeof(cReadText), pFile);
//	//				sscanf(cReadText, "%s", &cHeadText);
//
//	//				//�p�����[�^�Z�b�g��������
//	//				if (strcmp(cHeadText, "PARAMSET") == 0)
//	//				{
//	//					//�������m��
//	//					pCreator = new CParticleCreators;
//
//	//					//�G���h����܂Ń��[�v
//	//					while (strcmp(cHeadText, "END_PARAMSET") != 0)
//	//					{
//
//	//						fgets(cReadText, sizeof(cReadText), pFile);
//	//						sscanf(cReadText, "%s", &cHeadText);
//
//
//	//						//���ꂼ��̍��ڂ�ǂݍ���
//	//						if (strcmp(cHeadText, "SPEEDRANDOM") == 0)
//	//						{
//	//							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &n_BoolValue);
//	//							pCreator-> = n_BoolValue ? true : false;
//	//						}
//
//	//						if (strcmp(cHeadText, "SHAPE") == 0)
//	//						{
//	//							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pCreator->m_shape);
//	//						}
//	//						if (strcmp(cHeadText, "TEXTURE") == 0)
//	//						{
//	//							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pCreator->m_Textype);
//	//						}
//
//	//					}
//	//				}
//	//			}
//	//		}
//
//	//		//�p�����[�^���[�h
//	//		std::cout << "DefaultParticleParamLoad >>" << m_aFileNameList[nCnt].data() << NEWLINE;
//
//	//		//�t�@�C�������
//	//		fclose(pFile);
//	//	}
//
//	//	//�t�@�C���ǂݍ��߂Ȃ������ꍇ
//	//	else
//	//	{
//	//		std::cout << "LoadFailed!!  >>" << m_aFileNameList[nCnt].data() << NEWLINE;
//	//		MessageBox(NULL, "�p�[�e�B�N���̃p�����[�^�ǂݍ��ݎ��s", "�x��", MB_ICONWARNING);
//	//		hResult = E_FAIL;
//	//	}
//	//}
//	//return S_OK;
//}
//
//
////------------------------------------------------------------------------------
////�p�����[�^�ݒ�
////------------------------------------------------------------------------------
//CParticleCreators * CParticleCreators::Create()
//{
//	return nullptr;
//}
