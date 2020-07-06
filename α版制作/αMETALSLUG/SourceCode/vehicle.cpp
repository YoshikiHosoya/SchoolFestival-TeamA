// =====================================================================================================================================================================
//
//��蕨�̏��� [vehicle.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "vehicle.h"
#include "model.h"
#include "collision.h"
#include "game.h"
#include "map.h"
#include "manager.h"
#include "debugproc.h"
#include "inputKeyboard.h"
#include "Xinput.h"
#include "hosso\/Debug_ModelViewer.h"

//====================================================================
// ���f���̃I�t�Z�b�g�ǂݍ��݃t�@�C���̐ݒ�
//====================================================================
char *CVehicle::m_LoadOffsetFileName[VEHICLE_TYPE_MAX] =
{
	{ "data/Load/PlayerTank/PlayerTankOffset.txt" },
};

//====================================================================
//�}�N����`
//====================================================================
#define VEHICLE_GRAVITY (0.5f)

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CVehicle::CVehicle(OBJ_TYPE type) :CScene(type)
{
	// �����蔻��̃|�C���^��null�ɂ���
	m_pCollision = nullptr;
}
// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CVehicle::~CVehicle()
{
	// �����蔻��̍폜
	if (m_pCollision != nullptr)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}
}
// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
HRESULT CVehicle::Init(void)
{
	// ���W�̏�����
	m_pos			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// 1�t���[���O�̍��W�̏�����
	m_posOld		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// �ړ��ʂ̏�����
	m_move			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// ��]�̏�����
	m_rot			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// ���Z�����]�ʂ̏�����
	m_AddRot		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// �̗͂̏�����
	m_nLife			= 1000;
	// ��Ԃ̏�����
	m_state			= VEHICLE_STATE_NORMAL;
	// ��]�ʂ̏�����
	m_rotDest.y		= -0.5f*  D3DX_PI;
	// �W�����v�t���O�̏�����
	m_bJump			= false;
	// �d�̓t���O�̏�����
	m_bGravity		= true;
	// ���S�t���O�̏�����
	m_bDieFlag		= false;
	// �e�̉�]�̏�����
	m_ShotRot		= D3DXVECTOR3(0.0f, 0.5f, 0.0f);
	// �����蔻�萶��
	m_pCollision	= CCollision::Create();
	// �}�g���b�N�X������
	D3DXMatrixIdentity(&m_mtxWorld);
	// ��]�ʂ�������
	m_AddRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// ��蕨�̍s����Ԃ�������
	m_Behaviorstate = VEHICLE_BEHAVIOR_NORMAL;
	// ��ނ�������
	m_VehicleType = VEHICLE_TYPE_TANK;
	// ���G��Ԃ���ʏ��Ԃɖ߂�܂ł̃J�E���g
	m_nStateCnt = 0;
	// ����
	m_VehicleDirection = VEHICLE_LEFT;
	// �W�����v���Ă��邩�̃t���O��������
	m_bJump = false;
	// �폜���邩�ǂ����̃t���O��������
	m_bDieFlag = false;

	return S_OK;
}
//====================================================================
//
//�I��
//
//====================================================================
void CVehicle::Uninit(void)
{
}
//====================================================================
//
//�X�V
//
//====================================================================
void CVehicle::Update(void)
{
	// ��������
	Inertia();

	// �d�͏���
	Gravity();

	// ��]�ʌv�Z����
	Rot();

	// ��ԕʏ���
	State();

	// �e���������̌v�Z
	ShotDirection();

	// �̗͂�0�ȉ��ɂȂ�����
	if (this->m_nLife <= 0)
	{
		// ��Ԃ�j��ɕύX
		m_state = VEHICLE_STATE_BREAK;
	}

}
//====================================================================
//
//�`��
//
//====================================================================
void CVehicle::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y,
		m_rot.x,
		m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x,
		m_pos.y,
		m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxTrans);


	//���f���̕`��
	for (unsigned int nCnt = 0; nCnt < m_vModelList.size(); nCnt++)
	{
		if (nCnt == 2 || nCnt == 3 || nCnt == 4)
		{
			//�ڕW�_�ƌ��݂̍����i��]�j
			D3DXVECTOR3 diffRot = m_AddRot - m_vModelList[nCnt]->GetRot();
			//3.14�̒��ߕ��̏������i��]�j
			if (m_vModelList[nCnt]->GetRot().x > D3DX_PI)
			{
				m_vModelList[nCnt]->GetRot().x -= D3DX_PI * 2;
			}
			else if (m_vModelList[nCnt]->GetRot().x < -D3DX_PI)
			{
				m_vModelList[nCnt]->GetRot().x += D3DX_PI * 2;
			}
			if (diffRot.x > D3DX_PI)
			{
				diffRot.x -= D3DX_PI * 2;
			}
			else if (diffRot.x < -D3DX_PI)
			{
				diffRot.x += D3DX_PI * 2;
			}
			//���߂����������Ǐ]����v�Z
			m_vModelList[nCnt]->GetRot().x += diffRot.x * 0.1f;

			m_vModelList[nCnt]->SetRot(m_vModelList[nCnt]->GetRot());
			CDebugProc::Print("ShotRot : %.1f, %.1f %.1f\n", m_ShotRot.x, m_ShotRot.y, m_ShotRot.z);

			CDebugProc::Print("HeadRot : %.1f, %.1f %.1f\n", m_vModelList[nCnt]->GetRot().x, m_vModelList[nCnt]->GetRot().y, m_vModelList[nCnt]->GetRot().z);
		}

		m_vModelList[nCnt]->Draw(m_mtxWorld);

		if (nCnt == 2 || nCnt == 3 || nCnt == 4)
		{
			m_vModelList[nCnt]->SetRot(m_vModelList[nCnt]->GetRot());
		}
	}
}
//====================================================================
//�f�o�b�O
//====================================================================
void CVehicle::DebugInfo(void)
{
	CDebug_ModelViewer::OffsetViewer(m_vModelList);


	//CDebugProc::Print("");
}

//====================================================================
// ��������
//====================================================================
void CVehicle::Inertia()
{
	m_move.x += (0 - m_move.x)* 0.2f;
	m_move.z += (0 - m_move.z)* 0.2f;
	m_move.y += m_move.y * -0.1f;
}

//====================================================================
// �d�͏���
//====================================================================
void CVehicle::Gravity()
{
	// �d�̓t���O��true��������
	if (m_bGravity == true)
	{
		// �d��
		m_move.y -= VEHICLE_GRAVITY;
	}

	m_pos += m_move;
}

//====================================================================
// ��]�ʌv�Z����
//====================================================================
void CVehicle::Rot()
{
	//�ڕW�_�ƌ��݂̍����i��]�j
	float diffRot = m_rotDest.y - m_rot.y;
	//3.14�̒��ߕ��̏������i��]�j
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}
	if (diffRot > D3DX_PI)
	{
		diffRot -= D3DX_PI * 2;
	}
	else if (diffRot < -D3DX_PI)
	{
		diffRot += D3DX_PI * 2;
	}
	//���߂����������Ǐ]����v�Z
	m_rot.y += diffRot * 0.1f;
}

//====================================================================
// ��蕨�̏�ԕʏ���
//====================================================================
void CVehicle::State()
{
	//�X�e�[�^�X�̏���
	switch (m_state)
	{
		// �ʏ���
	case VEHICLE_STATE_NORMAL:
		break;

		// �_���[�W���󂯂���
	case VEHICLE_STATE_DAMAGE:
		m_state = VEHICLE_STATE_NORMAL;
		break;

	case VEHICLE_STATE_INVINCIBLE:
		m_nStateCnt++;
		if (m_nStateCnt % 30 == 0)
		{
			m_state = VEHICLE_STATE_NORMAL;
		}
		break;

	case VEHICLE_STATE_BREAK:
		// �j�󎞂̃G�t�F�N�g

		// �폜
		Rerease();
		break;
	}
}

//====================================================================
// �e���������̌v�Z
//====================================================================
void CVehicle::ShotDirection()
{
	switch (m_VehicleDirection)
	{
	case VEHICLE_LEFT:
		m_ShotRot.x = 0.0f;
		m_ShotRot.y = 0.5f * D3DX_PI;
		m_AddRot.x = 0.0f;
		break;

	case VEHICLE_RIGHT:
		m_ShotRot.x = 0.0f;
		m_ShotRot.y = -0.5f * D3DX_PI;
		m_AddRot.x = 0.0f;
		break;
	case VEHICLE_UP:
		m_ShotRot.x = 0.5f * D3DX_PI;
		m_ShotRot.y = 0.0f;
		m_AddRot.x = 0.75f;
		break;
	case VEHICLE_DOWN:
		m_ShotRot.x = -0.5f * D3DX_PI;
		m_ShotRot.y = 0.5f * D3DX_PI;
		m_AddRot.x = -0.75f;
		break;

	default:
		break;
	}
}

//====================================================================
//�ړ�
//====================================================================
void CVehicle::Move(float move, float fdest)
{
	GetMove().x += sinf(move * -D3DX_PI) * 1.0f;
	GetMove().z += cosf(move * -D3DX_PI) * 1.0f;
	GetRotDest().y = fdest *  D3DX_PI;
}

//====================================================================
//�_���[�W���󂯂����̏���
//====================================================================
void CVehicle::AddDamage(int Damage)
{
	// ��蕨�̏�Ԃ�ύX
	m_state = VEHICLE_STATE_DAMAGE;
	// �̗͂���_���[�W�ʕ������Z
	this->m_nLife -= Damage;
	// ���ʂ��X�V
	SetLife(m_nLife);
}

//====================================================================
//�I�t�Z�b�g�̓ǂݍ���
//====================================================================
void CVehicle::LoadOffset(VEHICLE_TYPE nType)
{
	char cReadText[1080];	//�����Ƃ��ēǂݎ��p
	char cHeadText[1080];	//��r����p
	char cDie[1080];		//�s�v�ȕ���
	int nCnt = 0;
	FILE *pFile;

	D3DXVECTOR3 pos;
	int nIdxParent;			//�e�̃C���f�b�N�X
	int nIdx;				//���f���̃C���f�b�N�X
	int type;

	pFile = fopen(m_LoadOffsetFileName[nType], "r");
	if (pFile != NULL)
	{
		while (strcmp(cHeadText, "MODEL_OFFSET_END") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile);
			sscanf(cReadText, "%s", &cHeadText);
			//�z�u���郂�f���̍ő吔�̓ǂݍ���
			if (strcmp(cHeadText, "SET_START") == 0)
			{
				//END_SET������܂Ń��[�v
				while (strcmp(cHeadText, "SET_END") != 0)
				{
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s", &cHeadText);
					//MODEL_TYPE��������
					if (strcmp(cHeadText, "MODEL_TYPE") == 0)
					{
						sscanf(cReadText, "%s %s %d",
							&cDie, &cDie,
							&type);
					}
					//IDX��������
					else if (strcmp(cHeadText, "INDEX") == 0)
					{
						sscanf(cReadText, "%s %s %d",
							&cDie, &cDie,
							&nIdx);
					}
					//PARENT��������
					else if (strcmp(cHeadText, "PARENT") == 0)
					{
						sscanf(cReadText, "%s %s %d",
							&cDie, &cDie,
							&nIdxParent);
					}
					//POS��������
					else if (strcmp(cHeadText, "POS") == 0)
					{
						sscanf(cReadText, "%s %s %f %f %f",
							&cDie, &cDie,
							&pos.x,
							&pos.y,
							&pos.z);
					}
					//SET_END��������쐬���ǉ�
					else if (strcmp(cHeadText, "SET_END") == 0)
					{
						CModel *pModel = CModel::Create(type, nIdx);
						pModel->SetPosition(pos);
						pModel->SetParentIdx(nIdxParent);
						if (nIdxParent == -1)
						{
							pModel->SetParent(NULL);
						}
						else
						{
							pModel->SetParent(m_vModelList[nIdxParent]);
						}
						m_vModelList.emplace_back(pModel);
					}
				}
			}
		}

		fclose(pFile);
	}
	else
	{

	}

}
