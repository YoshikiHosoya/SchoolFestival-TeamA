// ----------------------------------------
//
// �^�C�g���p�G���� [titleenemy.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------
#include "titleEnemy.h"
// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
#define ENEMY_KEYMOVE			(2)			// �L�[�ړ�
#define ENEMY_RESISTANCE (0.9f)				// ��R��
#define ENEMY_COLLISIONSIZE_X	(50.0f)		// �����蔻��̑傫��
#define ENEMY_COLLISIONSIZE_Y	(50.0f)		// �����蔻��̑傫��
#define ENEMY_COLLISIONSIZE_Z	(50.0f)		// �����蔻��̑傫��
#define ENEMY_REST_X (1300.0f)				// x�͈̔�
#define ENEMY_REST_Z (200.0f)				// z�͈̔�
// ----------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------
CLoad			*CTitleEnemy::m_pload = NULL;			// ���[�h
CModel_info		*CTitleEnemy::m_pModel_info = NULL;		// ���f�����
MODEL_OFFSET	*CTitleEnemy::m_pModel_offset = NULL;	// ���f���̏����z�u
MOTION			*CTitleEnemy::m_pMotion = NULL;			// ���[�V�������̕ۑ�
// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CTitleEnemy::CTitleEnemy() : CScene::CScene(ACTOR_ENEMY, LAYER_3DOBJECT)
{
	m_pos = D3DXVECTOR3(0.0f, 120.0f, -1600.0f);	// �ʒu
	//m_pos = D3DXVECTOR3(1200.0f, 0.0f, -300.0f);	// �ʒu
	//m_pos = D3DXVECTOR3(1200.0f, 0.0f, 2100.0f);	// �ʒu
	m_posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �O�̈ʒu
	//m_move = D3DXVECTOR3(0.0f, 0.0f, -5.0f);		// �ړ���
	m_rot = D3DXVECTOR3(0.0f, 3.14f, 0.0f);		// ���݉�]��
	//m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ���݉�]��

	m_rotLast = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ������������
	m_rotbetween = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]�̍���
	m_size = D3DXVECTOR3(							// ���f���̃T�C�Y
		ENEMY_COLLISIONSIZE_X,
		ENEMY_COLLISIONSIZE_Y,
		ENEMY_COLLISIONSIZE_Z);

	m_pCollision = NULL;
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CTitleEnemy::~CTitleEnemy()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CTitleEnemy::Init(void)
{
	// ���f���̐ݒ�
	for (int nCntModel = 0; nCntModel < TITLE_ENEMYTYPE_MAX; nCntModel++)
	{
		// ���f������
		m_pModel[nCntModel] = CModel::Create();
		// ���f�����n��
		m_pModel[nCntModel]->BindModel(
			m_pModel_info[nCntModel].GetModel_info(),
			m_pModel_offset[nCntModel]
		);
		// ���ׂĂ̐e�ȊO
		if (nCntModel != 0)
		{
			// �e���ݒ�
			m_pModel[nCntModel]->SetParent(m_pModel[m_pModel[nCntModel]->GetModelInfo()->nParent]);
		}
	}
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CTitleEnemy::Uninit(void)
{
	// ���f��
	for (int nCntModel = 0; nCntModel < TITLE_ENEMYTYPE_MAX; nCntModel++)
	{
		// �k���`�F�b�N
		if (m_pModel[nCntModel] != NULL)
		{
			delete m_pModel[nCntModel];
			m_pModel[nCntModel] = NULL;
		}

		//m_pModel[nCntModel]->Uninit();
	}
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CTitleEnemy::Update(void)
{
	//m_nMotiontype = 2;
	//m_pos += m_move;
	// �t���[���J�E���g�A�b�v
	m_nFrame++;
	// ���[�V�����^�C�v���ω�
	// ������
	if (m_nMotiontype != m_nMotiontypeOld)
	{
		m_nFrame = 0;		// �t���[���L�[���̃J�E���g
		m_keyinfoCnt = 0;	// �L�[���̃J�E���g
	}
	// ���[�V�����̕ۑ�
	m_nMotiontypeOld = m_nMotiontype;
	// �t���[�����������ɂȂ�����
	if (m_nFrame == m_pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].nFrame)
	{
		// ������
		m_nFrame = 0;	// �t���[��
						// �J�E���g�A�b�v
		m_keyinfoCnt++;
		// �L�[��񂪒�������
		if (m_keyinfoCnt >= m_pMotion[m_nMotiontype].nNumKey)
		{
			// ���[�v���Ȃ��Ƃ�
			if (m_pMotion[m_nMotiontype].nLoop == 0)
			{
				// ������
				m_keyinfoCnt = 0;				// �L�[���
				m_nMotiontype = 0;	// ���[�V�����^�C�v
			}

			// ���[�v���鎞
			else
			{
				// ������
				m_keyinfoCnt = 0;				// �L�[���
			}
		}
	}
	// ���f��
	for (int nCntModel = 0; nCntModel < TITLE_ENEMYTYPE_MAX; nCntModel++)
	{
		// �k���`�F�b�N
		if (m_pModel[nCntModel] != NULL)
		{
			m_pModel[nCntModel]->SetMotion(m_pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].Key[nCntModel], m_pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].nFrame);
			m_pModel[nCntModel]->Update();
		}
	}
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CTitleEnemy::Draw(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX			mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

											// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y,
		m_rot.x,
		m_rot.z);

	// �s��̐�(1:���[���h�s�� = 2:���[���h�s�� * 3:��]�s��)
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f //
	// ���s�ړ��s��쐬(�I�t�Z�b�g)
	D3DXMatrixTranslation(&mtxTrans,	// �����̓��ꕨ
		m_pos.x,
		m_pos.y,
		m_pos.z);

	// �s��̐�(1:���[���h�s�� = 2:���[���h�s�� * 3:�ړ��s��)
	D3DXMatrixMultiply(&m_mtxWorld,	// 1
		&m_mtxWorld,				// 2
		&mtxTrans);					// 3

									// ���f��
	for (int nCntModel = 0; nCntModel < TITLE_ENEMYTYPE_MAX; nCntModel++)
	{
		// �k���`�F�b�N
		if (m_pModel[nCntModel] != NULL)
		{
			m_pModel[nCntModel]->Draw(m_mtxWorld);
		}
	}
}

// ----------------------------------------
// �ʒu�擾����
// ----------------------------------------
D3DXVECTOR3 CTitleEnemy::GetPos(void)
{
	return m_pos;
}

// ----------------------------------------
// ��]�擾����
// ----------------------------------------
D3DXVECTOR3 CTitleEnemy::GetRot(void)
{
	return m_rot;
}

// ----------------------------------------
// ��������
// ----------------------------------------
CTitleEnemy * CTitleEnemy::Create()
{
	// �ϐ��錾
	CTitleEnemy * pTitleEnemy;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pTitleEnemy = new CTitleEnemy();
	// ����������
	pTitleEnemy->Init();

	// ���������I�u�W�F�N�g��Ԃ�
	return pTitleEnemy;
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
void CTitleEnemy::Load(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();

	// ���f�����̐���
	m_pModel_info = new CModel_info[TITLE_ENEMYTYPE_MAX];
	// ���f���̃I�t�Z�b�g�̐���
	m_pModel_offset = new MODEL_OFFSET[TITLE_ENEMYTYPE_MAX];
	// ���[�V�����̐���
	m_pMotion = new MOTION[MOTIONTYPE_TITLE_ENEMY_MAX];
	// �e�N�X�`���[�����
	char ModelData[TITLE_ENEMYTYPE_MAX][512] =
	{
		"data/MODEL/enemy/Body.x",			// [��]		00
		"data/MODEL/enemy/Head.x",			// [��]			01
		"data/MODEL/enemy/Arm_L.x",			// [���r]		02
		"data/MODEL/enemy/Arm_R.x",			// [�E�r]		03
		"data/MODEL/enemy/Leg_L.x",			// [����]		04
		"data/MODEL/enemy/Leg_R.x",			// [�E��]		05
	};

	// ���f���̃I�t�Z�b�g�ݒ�
	CModel_info::ModelOffset(
		m_pModel_offset,					// ���f���̃I�t�Z�b�g
		"data/MOTION/motion_enemy.txt"		// �t�@�C����
	);
	// ���[�V�����̐ݒ�
	CMotion::Load(
		m_pMotion,							// ���[�V����
		m_pModel_offset,					// �I�t�Z�b�g
		TITLE_ENEMYTYPE_MAX,						// �L�[
		"data/MOTION/motion_enemy.txt"		// �t�@�C����
	);
	// ���f���̕ۑ�
	for (int nCntModelLoad = 0; nCntModelLoad < TITLE_ENEMYTYPE_MAX; nCntModelLoad++)
	{
		// ���f������ǂݍ���
		m_pModel_info[nCntModelLoad].Load(
			pDevice,
			ModelData[nCntModelLoad]);
	}
}

// ----------------------------------------
// �ǂݍ��񂾏���j������
// ----------------------------------------
void CTitleEnemy::UnLoad(void)
{
	// ���f���̕`����j��
	for (int nCntModelLoad = 0; nCntModelLoad < TITLE_ENEMYTYPE_MAX; nCntModelLoad++)
	{
		// ���f�����̊J��
		m_pModel_info[nCntModelLoad].Unload();
	}
	// ���[�V�����̔j��
	//CMotion::UnLoad(
	//	m_pMotion,					// ���[�V����
	//	MOTIONTYPE_TITLE_ENEMY_MAX
	//);
	// ���f�����̔j��
	delete[] m_pModel_info;
	// ���f���̃I�t�Z�b�g�̔j��
	delete[] m_pModel_offset;
}

// ----------------------------------------
// �I�u�W�F�N�g�̍폜
// ----------------------------------------
void CTitleEnemy::ReleaseTEne(void)
{
	Release();
}

// ----------------------------------------
// �^�C�g���p ���[�V�����̐؂�ւ�
// ----------------------------------------
void CTitleEnemy::SetMotion(void)
{
	m_nMotiontype = MOTIONTYPE_TITLE_ENEMY_RUN;
}
