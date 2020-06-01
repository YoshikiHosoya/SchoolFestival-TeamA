// ----------------------------------------
//
// �v���C���[���� [player.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------
#include "player.h"
#include "enemy.h"
#include "floor.h"
#include "input.h"
#include "debugproc.h"
#include "camera.h"
#include "3Dparticle.h"
#include "gauge.h"
#include "game.h"
#include "item.h"
#include "score.h"
#include "manager.h"
#include "fade.h"
#include "title.h"
#include "mapmark.h"
#include "gameui.h"
// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
#define PLAYER_KEYMOVE			(1.3f)					// �L�[�ړ�
#define PLAYER_COLLISIONSIZE	(50.0f)					// �����蔻��̑傫��
#define PLAYER_RESISTANCE (0.9f)						// ��R��
#define PLAYER_REST_X (1300.0f)							// x�͈̔�
#define PLAYER_REST_Z (200.0f)							// z�͈̔�

// ----------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------
CModel_info		*CPlayer::m_pModel_info = NULL;		// ���f�����
MODEL_OFFSET	*CPlayer::m_pModel_offset = NULL;	// ���f���̏����z�u
MOTION			*CPlayer::m_pMotion = NULL;			// ���[�V�������̕ۑ�

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CPlayer::CPlayer() : CScene::CScene(ACTOR_PLAYER, LAYER_3DOBJECT)
{
	if (CManager::GetMode() == CManager::MODE_TITLE)
	{
		m_pos = D3DXVECTOR3(0.0f, 320.0f, 2300.0f);				// �ʒu
		m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ���݉�]��
	}
	else if (CManager::GetMode() == CManager::MODE_GAME)
	{
		m_pos = D3DXVECTOR3(0.0f, 220.0f, 0.0f);				// �ʒu
		m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ���݉�]��
	}

	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		CManager::GetRenderer()->GetCamera()->SetRot(D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	}

	m_posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �O�̈ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// �ړ���
	m_rotLast = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ������������
	m_rotbetween = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�̍���
	m_size = D3DXVECTOR3(										// ���f���̃T�C�Y
		PLAYER_COLLISIONSIZE,
		PLAYER_COLLISIONSIZE,
		PLAYER_COLLISIONSIZE);

	m_pCollision = NULL;										// �����蔻��
	m_bRun = false;												// ����
	m_nAbilityPoint = 0;										// �A�r���e�B�̃|�C���g
	m_nCoolTime = 0;											// �A�r���e�B�̃N�[���^�C��
	m_bAbilityFlag = false;										// �A�r���e�B���g���Ă��邩�ǂ���
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CPlayer::~CPlayer()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CPlayer::Init(void)
{
	// ���f���̐ݒ�
	for (int nCntModel = 0; nCntModel < PLAYERTYPE_MAX; nCntModel++)
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

	// �����蔻�萶��
	m_pCollision = CCollision::Create();
	m_pCollision->SetPos(&m_pos);
	m_pCollision->SetSize(m_size);
	m_pCollision->SetMove(&m_move);
	m_pCollision->SetType(CCollision::OBJTYPE_PLAYER);
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CPlayer::Uninit(void)
{
	// ���f��
	for (int nCntModel = 0; nCntModel < PLAYERTYPE_MAX; nCntModel++)
	{
		// �k���`�F�b�N
		if (m_pModel[nCntModel] != NULL)
		{
			delete m_pModel[nCntModel];
			m_pModel[nCntModel] = NULL;
		}
	}
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CPlayer::Update(void)
{
	// �^�C�g���̏�Ԃ��s���\��Ԃ����[�h���Q�[���̎��A�ړ��\
	if (CManager::GetTitle()->GetMode() == CManager::GetTitle()->TITLEMODE_FREE || CManager::GetMode() == CManager::MODE_GAME)
	{
		// �ړ�
		Move();
	}

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
			else
			{// ���[�v���鎞
				// ������
				m_keyinfoCnt = 0;				// �L�[���
			}
		}
	}
	// ���f��
	for (int nCntModel = 0; nCntModel < PLAYERTYPE_MAX; nCntModel++)
	{
		// �k���`�F�b�N
		if (m_pModel[nCntModel] != NULL)
		{
			m_pModel[nCntModel]->SetMotion(m_pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].Key[nCntModel], m_pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].nFrame);
			m_pModel[nCntModel]->Update();
		}
	}

	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		// �A�r���e�B�\
		Ability();
	}

	//�s���͈͐���
	Restriction();

	//�����蔻��̍��W�X�V
	m_pCollision->SetPos(&m_pos);

	CDebugproc::Print("�v���C���[�̃X�e�[�^�X���\n");
	CDebugproc::Print("���W		: %.2f,%.2f,%.2f\n", GetPos().x, GetPos().y, GetPos().z);
}

// ----------------------------------------
// �ړ�����
// ----------------------------------------
void CPlayer::Move(void)
{
	// �ϐ��錾
	float fRot;
	CFloor * pFloor = NULL;	// ��

	int nValueH = 0;//�X�e�B�b�N�̉�
	int nValueV = 0;//�X�e�B�b�N�̏c

	// ���擾
	for (int nCntLayer = 0; nCntLayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntLayer++)
	{
		if (pFloor == NULL) pFloor = (CFloor*)CScene::GetActor(CScene::ACTOR_FLOOR, CScene::LAYER_3DOBJECT, nCntLayer);	// ��
	}

	fRot = CManager::GetRenderer()->GetCamera()->GetRot().y;	// ��]���擾

	//�W���C�p�b�h�ł̏���
	CManager::GetJoy()->GetStickLeft(0, &nValueH, &nValueV);

	if (nValueH != 0 || nValueV != 0)
	{
		// ���ɓ|���Ă��鎞
		if (nValueH <= -1)
		{
			if (nValueV >= 1)
			{
				m_move.x += sinf(D3DX_PI * 0.75f + fRot) * PLAYER_KEYMOVE;
				m_move.z += cosf(D3DX_PI * 0.75f + fRot) * PLAYER_KEYMOVE;
			}
			else if (nValueV <= -1)
			{
				m_move.x += sinf(D3DX_PI * 0.25f + fRot) * PLAYER_KEYMOVE;
				m_move.z += cosf(D3DX_PI * 0.25f + fRot) * PLAYER_KEYMOVE;
			}
			else
			{
				m_move.x += sinf(D3DX_PI * 0.5f + fRot) * PLAYER_KEYMOVE;
				m_move.z += cosf(D3DX_PI * 0.5f + fRot) * PLAYER_KEYMOVE;
			}
		}

		// �E�ɓ|���Ă��鎞
		else if (nValueH >= 1)
		{
			if (nValueV  >= 1)
			{
				m_move.x += sinf(-D3DX_PI * 0.75f + fRot) * PLAYER_KEYMOVE;
				m_move.z += cosf(-D3DX_PI * 0.75f + fRot) * PLAYER_KEYMOVE;
			}

			else if (nValueV <= -1)
			{
				m_move.x += sinf(-D3DX_PI * 0.25f + fRot) * PLAYER_KEYMOVE;
				m_move.z += cosf(-D3DX_PI * 0.25f + fRot) * PLAYER_KEYMOVE;
			}

			else
			{
				m_move.x += sinf(-D3DX_PI * 0.5f + fRot) * PLAYER_KEYMOVE;
				m_move.z += cosf(-D3DX_PI * 0.5f + fRot) * PLAYER_KEYMOVE;
			}
		}

		else if (nValueV >= 1)
		{
			m_move.x += sinf(D3DX_PI * 1.0f + fRot) * PLAYER_KEYMOVE;
			m_move.z += cosf(D3DX_PI * 1.0f + fRot) * PLAYER_KEYMOVE;
		}
		else if (nValueV <= -1)
		{
			m_move.x += sinf(D3DX_PI * 0.0f + fRot) * PLAYER_KEYMOVE;
			m_move.z += cosf(D3DX_PI * 0.0f + fRot) * PLAYER_KEYMOVE;
		}

		// �����Ă�����
		if (m_bRun == false)
		{
			CManager::GetSound()->PlaySound(CSound::LABEL_BGM_RUN);
			CManager::GetSound()->PlaySound(CSound::LABEL_BGM_BREATH);
			m_bRun = true;
		}
	}

	// �����Ă��Ȃ�������
	else
	{
		CManager::GetSound()->StopSound(CSound::LABEL_BGM_RUN);
		CManager::GetSound()->StopSound(CSound::LABEL_BGM_BREATH);
		m_bRun = false;
	}

	// �ړ� //
	// ��
	if (CManager::GetKeyboard()->GetKeyboardPress(DIK_A))
	{
		// ��
		if (CManager::GetKeyboard()->GetKeyboardPress(DIK_W))
		{
			//m_rotLast.y = -D3DX_PI * 0.25f + fRot;

			m_move.x += sinf(D3DX_PI * 0.75f + fRot) * PLAYER_KEYMOVE;
			m_move.z += cosf(D3DX_PI * 0.75f + fRot) * PLAYER_KEYMOVE;
		}
		// ��O
		else if (CManager::GetKeyboard()->GetKeyboardPress(DIK_S))
		{
			//m_rotLast.y = -D3DX_PI * 0.75f + fRot;

			m_move.x += sinf(D3DX_PI * 0.25f + fRot) * PLAYER_KEYMOVE;
			m_move.z += cosf(D3DX_PI * 0.25f + fRot) * PLAYER_KEYMOVE;
		}
		// ��
		else
		{
			//m_rotLast.y = -D3DX_PI * 0.5f + fRot;

			m_move.x += sinf(D3DX_PI * 0.5f + fRot) * PLAYER_KEYMOVE;
			m_move.z += cosf(D3DX_PI * 0.5f + fRot) * PLAYER_KEYMOVE;
		}
	}
	// �E
	else if (CManager::GetKeyboard()->GetKeyboardPress(DIK_D))
	{
		// ��
		if (CManager::GetKeyboard()->GetKeyboardPress(DIK_W))
		{
			//m_rotLast.y = D3DX_PI * 0.25f + fRot;

			m_move.x += sinf(-D3DX_PI * 0.75f + fRot) * PLAYER_KEYMOVE;
			m_move.z += cosf(-D3DX_PI * 0.75f + fRot) * PLAYER_KEYMOVE;
		}
		// ��O
		else if (CManager::GetKeyboard()->GetKeyboardPress(DIK_S))
		{
			//m_rotLast.y = D3DX_PI * 0.75f + fRot;

			m_move.x += sinf(-D3DX_PI * 0.25f + fRot) * PLAYER_KEYMOVE;
			m_move.z += cosf(-D3DX_PI * 0.25f + fRot) * PLAYER_KEYMOVE;
		}
		// �E
		else
		{
			//m_rotLast.y = D3DX_PI * 0.5f + fRot;

			m_move.x += sinf(-D3DX_PI * 0.5f + fRot) * PLAYER_KEYMOVE;
			m_move.z += cosf(-D3DX_PI * 0.5f + fRot) * PLAYER_KEYMOVE;
		}
	}
	// ���ɍs��
	else if (CManager::GetKeyboard()->GetKeyboardPress(DIK_W))
	{
		//m_rotLast.y = -D3DX_PI * 0.0f + fRot;
		m_move.x += sinf(-D3DX_PI * 1.0f + fRot) * PLAYER_KEYMOVE;
		m_move.z += cosf(-D3DX_PI * 1.0f + fRot) * PLAYER_KEYMOVE;
	}
	// ��O�ɍs��
	else if (CManager::GetKeyboard()->GetKeyboardPress(DIK_S))
	{
		//m_rotLast.y = D3DX_PI * 1.0f + fRot;

		m_move.x += sinf(D3DX_PI * 0.0f + fRot) * PLAYER_KEYMOVE;
		m_move.z += cosf(D3DX_PI * 0.0f + fRot) * PLAYER_KEYMOVE;
	}

	// ���݉�]����
	m_rotbetween.y = m_rotLast.y - m_rot.y;

	// ���x����
	m_rotbetween.y = CCalculation::Rot_One_Limit(m_rotbetween.y);

	// ��]�ړ�
	m_rot.y += m_rotbetween.y * 0.1f;

	// ���x����
	m_rot.y = CCalculation::Rot_One_Limit(m_rot.y);

	// �d��
	//m_move.y -= PLAYER_G;	// �ړ���
	m_pos += m_move;

	// ��R��
	m_move.x *= PLAYER_RESISTANCE;
	m_move.z *= PLAYER_RESISTANCE;

	// ���̍�������
	/*if (pFloor != NULL)
	{
		if (m_pos.y < pFloor->GetHeight(m_pos))
		{
			m_pos.y = pFloor->GetHeight(m_pos);
		}
	}*/

	m_pCollision->Collision();
	// �����蔻��ɐG�ꂽ��
	//if (m_pCollision->Collision_Player())
	//{

	//}
	//else
	//{
	//	//�ǂ��ɂ��������Ă��Ȃ�������t���O��false�ɂ���
	//	ResetFlag();
	//}

	// �������
	//Restriction();
}

// ----------------------------------------
// �\�͏���
// ----------------------------------------
void CPlayer::Ability(void)
{
	// �A�r���e�B�\�|�C���g�����܂��Ă�����
	if (CGame_ui::GetbUse())
	{
		if (m_bAbilityFlag == false)
		{
			// �A�r���e�B�\�Q�[�W�����܂��Ă��ď����X�y�[�X���������Ƃ�
			if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_SPACE))
			{
				// �J�E���g�������A�G�̍X�V�����߂��b���~�߂�
				CGame_ui::SetAP(-10);
				CEnemy::SetFreezeFlag();
				CGauge::Create();
				m_nCoolTime = 0;
				m_bAbilityFlag = true;
			}
		}
	}

	// �A�r���e�B���g������
	if (m_bAbilityFlag == true)
	{
		// �N�[���^�C�����Z
		m_nCoolTime++;

		if (m_nCoolTime >= (ONEMIN * 10))
		{
			m_bAbilityFlag = false;
		}
	}
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CPlayer::Draw(void)
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
	for (int nCntModel = 0; nCntModel < PLAYERTYPE_MAX; nCntModel++)
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
D3DXVECTOR3 CPlayer::GetPos(void)
{
	return m_pos;
}

// ----------------------------------------
// ��]�擾����
// ----------------------------------------
D3DXVECTOR3 CPlayer::GetRot(void)
{
	return m_rot;
}

// ----------------------------------------
// ��������
// ----------------------------------------
CPlayer * CPlayer::Create()
{
	// �ϐ��錾
	CPlayer * pPlayer;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pPlayer = new CPlayer();
	// ����������
	pPlayer->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pPlayer;
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
void CPlayer::Load(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();
	// ���f�����̐���
	m_pModel_info = new CModel_info[PLAYERTYPE_MAX];
	// ���f���̃I�t�Z�b�g�̐���
	m_pModel_offset = new MODEL_OFFSET[PLAYERTYPE_MAX];
	// ���[�V�����̐���
	m_pMotion = new MOTION[MOTIONTYPE_MAX];
	// �e�N�X�`���[�����
	char ModelData[PLAYERTYPE_MAX][72] =
	{
		"data/MODEL/bane/Head.x",			// [��]01
		"data/MODEL/bane/Head.x",			// [��]00
	};
	// ���f���̃I�t�Z�b�g�ݒ�
	CModel_info::ModelOffset(
		m_pModel_offset,					// ���f���̃I�t�Z�b�g
		"data/MOTION/motion_banekun.txt"	// �t�@�C����
	);
	// ���[�V�����̐ݒ�
	CMotion::Load(
		m_pMotion,							// ���[�V����
		m_pModel_offset,					// �I�t�Z�b�g
		PLAYERTYPE_MAX,						// �L�[
		"data/MOTION/motion_banekun.txt"	// �t�@�C����
	);
	// ���f���̕ۑ�
	for (int nCntModelLoad = 0; nCntModelLoad < PLAYERTYPE_MAX; nCntModelLoad++)
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
void CPlayer::UnLoad(void)
{
	// ���f���̕`����j��
	for (int nCntModelLoad = 0; nCntModelLoad < PLAYERTYPE_MAX; nCntModelLoad++)
	{
		// ���f�����̊J��
		m_pModel_info[nCntModelLoad].Unload();
	}
	// ���[�V�����̔j��
	CMotion::UnLoad(
		m_pMotion,					// ���[�V����
		MOTIONTYPE_MAX
	);
	// ���f�����̔j��
	delete[] m_pModel_info;
	// ���f���̃I�t�Z�b�g�̔j��
	delete[] m_pModel_offset;
}

// ----------------------------------------
// �v���C���[�̍s���ł���͈͂𐧌�
// ----------------------------------------
void CPlayer::Restriction(void)
{
	//�^�C�g���̃��[�h���t���[��������
	if (CManager::GetTitle()->GetMode() == CManager::GetTitle()->TITLEMODE_FREE &&
		CManager::GetMode() == CManager::MODE_TITLE)
	{
		if (m_pos.x >= 2500)
		{
			m_pos.x = 2500;
		}

		else if (m_pos.x <= -2500)
		{
			m_pos.x = -2500;
		}

		if (m_pos.z >= 2000)
		{
			m_pos.z = 2000;
		}

		else if (m_pos.z <= -2000)
		{
			m_pos.z = -2000;
		}
	}
}

// ----------------------------------------
// �ړ��ʂ̎擾
// ----------------------------------------
D3DXVECTOR3 CPlayer::GetMove(void)
{
	return m_move;
}

// ----------------------------------------
// �A�r���e�B�\�|�C���g�̌v�Z
// ----------------------------------------
void CPlayer::SetAbilityPoint(void)
{
	m_nAbilityPoint++;
}

// ----------------------------------------
// �A�r���e�B�\�t���O�̎擾
// ----------------------------------------
bool CPlayer::GetAbilityFlag(void)
{
	return m_bAbilityFlag;
}
