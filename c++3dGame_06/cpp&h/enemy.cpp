// ----------------------------------------
//
// ���f������ [enemy.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------
#include "enemy.h"
#include "scene_X.h"
#include "input.h"
#include "debugproc.h"
#include "game.h"
#include "floartile.h"
#include "player.h"
// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
#define ENEMY_MOVE				(0.4f)		// �L�[�ړ�
#define ENEMY_RESISTANCE		(0.9f)		// ��R��
#define ENEMY_COLLISIONSIZE_X	(50.0f)		// �����蔻��̑傫��
#define ENEMY_COLLISIONSIZE_Y	(50.0f)		// �����蔻��̑傫��
#define ENEMY_COLLISIONSIZE_Z	(50.0f)		// �����蔻��̑傫��
#define ENEMY_REST_X			(200.0f)	// x�͈̔�
#define ENEMY_REST_Z			(200.0f)	// z�͈̔�
#define ENEMY_ROT				(3.14f)		// ��]�����l

// ----------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------
CLoad			*CEnemy::m_pload = NULL;			// ���[�h
CModel_info		*CEnemy::m_pModel_info = NULL;		// ���f�����
MODEL_OFFSET	*CEnemy::m_pModel_offset = NULL;	// ���f���̏����z�u
MOTION			*CEnemy::m_pMotion = NULL;			// ���[�V�������̕ۑ�
bool			 CEnemy::m_bCaught = false;			//
bool			 CEnemy::m_bFreeze = false;
// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CEnemy::CEnemy() : CScene::CScene(ACTOR_ENEMY, LAYER_3DOBJECT)
{
	m_pos = D3DXVECTOR3(900.0f, 0.0f, -3900.0f);		// �ʒu
	m_posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �O�̈ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ړ���
	m_rot = D3DXVECTOR3(0.0f, ENEMY_ROT, 0.0f);			// ���݉�]��
	m_rotLast = D3DXVECTOR3(0.0f, ENEMY_ROT, 0.0f);		// ������������
	m_rotbetween = D3DXVECTOR3(0.0f, ENEMY_ROT, 0.0f);	// ��]�̍���

	m_size = D3DXVECTOR3(							// ���f���̃T�C�Y
		ENEMY_COLLISIONSIZE_X,
		ENEMY_COLLISIONSIZE_Y,
		ENEMY_COLLISIONSIZE_Z);

	m_bStopMove = false;
	m_bJudg = false;
	m_bProcessing = false;
	m_pFloarTile = NULL;
	m_bUse = false;
	m_nResult = 0;
	m_nCount = 0;
	m_nMotiontype = 2;

	m_bForward = false;
	m_bBackward = false;
	m_bLeft = false;
	m_bRight = false;
	//srand((unsigned int)time(NULL));//��������
	m_RotState = ROT_FORWARD;
	m_RotCurrentB = ROT_BACKWARD;
	m_RotPossible = ROT_FORWARD;
	m_nDirectionCnt = 0;
	m_bStopFlag = false;
	m_FreezeCnt = 0;
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CEnemy::~CEnemy()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CEnemy::Init(void)
{
	// ���f���̐ݒ�
	for (int nCntModel = 0; nCntModel < ENEMYTYPE_MAX; nCntModel++)
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
void CEnemy::Uninit(void)
{
	// ���f��
	for (int nCntModel = 0; nCntModel < ENEMYTYPE_MAX; nCntModel++)
	{
		// �k���`�F�b�N
		if (m_pModel[nCntModel] != NULL)
		{
			delete m_pModel[nCntModel];
			m_pModel[nCntModel] = NULL;
		}

		//m_pModel[nCntModel]->Uninit();
	}

	m_bCaught = false;
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CEnemy::Update(void)
{
	//if (m_bFreeze == false)
	//{
	//	// �ړ�
	//	Move();
	//	// ���[�V����
	//	Motion();
	//}
	//else
	//{
	//	m_FreezeCnt++;
	//	if (m_FreezeCnt >= ONEMIN * 5)
	//	{
	//		m_bFreeze = false;
	//	}
	//}

	//// ��]����
	//RotInertia();

	//CDebugproc::Print("�G�X�e�[�^�X���\n");
	CDebugproc::Print("�G ���W		: %.2f,%.2f,%.2f\n", m_pos.x, m_pos.y,m_pos.z);
	CDebugproc::Print("�G ��]���		: %d \n", m_RotState);
}

// ----------------------------------------
// �ړ�����
// ----------------------------------------
void CEnemy::Move(void)
{
	if (m_bStopFlag == false)
	{
		// �G�l�~�[�̉�]�ʂ��܂߂��ړ��ʂ̌v�Z
		m_move.x += sinf(D3DX_PI + m_rot.y) * ENEMY_MOVE;
		m_move.z += cosf(D3DX_PI + m_rot.y) * ENEMY_MOVE;

		// �ړ��ʂ����W�ɉ��Z
		m_pos += m_move;

		// ��R��
		m_move.x *= 0.9f;
		m_move.z *= 0.9f;
	}
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CEnemy::Draw(void)
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
	for (int nCntModel = 0; nCntModel < ENEMYTYPE_MAX; nCntModel++)
	{
		// �k���`�F�b�N
		if (m_pModel[nCntModel] != NULL)
		{
			m_pModel[nCntModel]->Draw(m_mtxWorld);
		}
	}
}

// ----------------------------------------
// ��]�X�V����
// ----------------------------------------
void CEnemy::SetRot(D3DXVECTOR3 rot, ROT rotstate)
{
	m_rotLast = rot;
	m_RotState = rotstate;
}

void CEnemy::StopMove(void)
{
	m_bStopFlag = true;
}

// ----------------------------------------
// �ʒu�擾����
// ----------------------------------------
D3DXVECTOR3 CEnemy::GetPos(void)
{
	return m_pos;
}

// ----------------------------------------
// ��]�擾����
// ----------------------------------------
D3DXVECTOR3 CEnemy::GetRot(void)
{
	return m_rot;
}

// ----------------------------------------
// ��]��Ԏ擾����
// ----------------------------------------
CEnemy::ROT CEnemy::GetEnemyROT(void)
{
	return m_RotState;
}

// ----------------------------------------
// ��������
// ----------------------------------------
CEnemy * CEnemy::Create()
{
	// �ϐ��錾
	CEnemy * pEnemy;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pEnemy = new CEnemy();
	// ����������
	pEnemy->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pEnemy;
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
void CEnemy::Load(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();
	// ���f�����̐���
	m_pModel_info = new CModel_info[ENEMYTYPE_MAX];
	// ���f���̃I�t�Z�b�g�̐���
	m_pModel_offset = new MODEL_OFFSET[ENEMYTYPE_MAX];
	// ���[�V�����̐���
	m_pMotion = new MOTION[MOTIONTYPE_ENEMY_MAX];
	// �e�N�X�`���[�����
	char ModelData[ENEMYTYPE_MAX][512] =
	{
		"data/MODEL/enemy/Body.x",			// [��]			00
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
		ENEMYTYPE_MAX,						// �L�[
		"data/MOTION/motion_enemy.txt"		// �t�@�C����
	);
	// ���f���̕ۑ�
	for (int nCntModelLoad = 0; nCntModelLoad < ENEMYTYPE_MAX; nCntModelLoad++)
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
void CEnemy::UnLoad(void)
{
	// ���f���̕`����j��
	for (int nCntModelLoad = 0; nCntModelLoad < ENEMYTYPE_MAX; nCntModelLoad++)
	{
		// ���f�����̊J��
		m_pModel_info[nCntModelLoad].Unload();
	}
	// ���[�V�����̔j��
	CMotion::UnLoad(
		m_pMotion,
		MOTIONTYPE_ENEMY_MAX
	);
	// ���f�����̔j��
	delete[] m_pModel_info;
	// ���f���̃I�t�Z�b�g�̔j��
	delete[] m_pModel_offset;
}

// ----------------------------------------
// ���x���̐ݒ�
// ----------------------------------------
void CEnemy::AddLevel(void)
{
}

// ----------------------------------------
// ���Ƃ̔���
// ----------------------------------------
void CEnemy::EnemyColi()
{
	//CPlayer *pPlayer = NULL;	// �v���C���[

	//for (int nCntlayer = 0; nCntlayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntlayer++)
	//{
	//	if (pPlayer = (CPlayer *)CScene::GetActor(CScene::ACTOR_PLAYER, CScene::LAYER_3DOBJECT, nCntlayer)) break;
	//}

	////
	//if (CCalculation::Collision_Circle(
	//	D3DXVECTOR3(GetPos().x, GetPos().y + 250, GetPos().z),
	//	// �����̈ʒu
	//	150.0f, 		// �����̔��a
	//	D3DXVECTOR3(pPlayer->GetPos().x, pPlayer->GetPos().y, pPlayer->GetPos().z), 			// ����̈ʒu
	//	100.0f))		// ����̔��a
	//{
	//	SetEndFlag();
	//}
}

// ----------------------------------------
// AI����
// ----------------------------------------
void CEnemy::EnemyAI(void)
{
}

// ----------------------------------------
// �i�s����������
// ----------------------------------------
void CEnemy::Direction(void)
{
}

// ----------------------------------------
// ��������߂�
// ----------------------------------------
void CEnemy::SeekBackwards(void)
{
}

// ----------------------------------------
// ��]
// ----------------------------------------
void CEnemy::Rot(ROT rot)
{
}

// ----------------------------------------
// ���[�V����
// ----------------------------------------
void CEnemy::Motion()
{
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
	for (int nCntModel = 0; nCntModel < ENEMYTYPE_MAX; nCntModel++)
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
// ��]�̊���
// ----------------------------------------
void CEnemy::RotInertia(void)
{
	// ���݉�]����
	m_rotbetween.y = m_rotLast.y - m_rot.y;

	// ���x����
	m_rotbetween.y = CCalculation::Rot_One_Limit(m_rotbetween.y);

	// ��]�ړ�
	m_rot.y += m_rotbetween.y * 0.1f;

	// ���x����
	m_rot.y = CCalculation::Rot_One_Limit(m_rot.y);
}

// ----------------------------------------
// �v���C���[��߂܂������t���O��true
// ----------------------------------------
void CEnemy::SetEndFlag(void)
{
	m_bCaught = true;
}

// ----------------------------------------
// �t���O�̎擾
// ----------------------------------------
bool CEnemy::GetEndFlag(void)
{
	return m_bCaught;
}

// ----------------------------------------
// �t���O���Z�b�g����
// ----------------------------------------
void CEnemy::SetFreezeFlag(void)
{
	m_bFreeze = true;
}
