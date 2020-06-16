// ----------------------------------------
//
// �f�o�b�O�p�̓����蔻��\������[debugcollision.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
/* �`�� */
#include "debugcollision.h"
#include "3Dline.h"

// ----------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CDebugcollision::CDebugcollision(OBJ_TYPE type) :CScene(type)
{
	m_pos = NULL;										// ���W�|�C���^�̏�����
	m_size = NULL;										// �T�C�Y�|�C���^�̏�����
	m_type = COLLISIONTYPE_BOX;							// �^�C�v�̏�����
	for (int nCnt = 0; nCnt < MAX_VERTEX3D; nCnt++)		// line�N���X�̃|�C���^������
	{
		m_p3DLine[nCnt] = NULL;
	}

	for (int nCnt = 0; nCnt < MAX_VERTEX2D; nCnt++)		// line�N���X�̃|�C���^������
	{
		m_p2DLine[nCnt] = NULL;
	}
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CDebugcollision::~CDebugcollision()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
HRESULT CDebugcollision::Init(void)
{
	switch (m_type)
	{
	case COLLISIONTYPE_BOX:
		BoxCollision();
		break;

	case COLLISIONTYPE_BOARD:
		BoardCollision();
		break;

	default:
		break;
	}

	return S_OK;
}

// ----------------------------------------
// ���̓����蔻�菈��
// ----------------------------------------
void CDebugcollision::BoxCollision(void)
{
	// 1�{��
	m_p3DLine[0] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(-m_size->x * 0.5f, m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXVECTOR3(m_size->x * 0.5f, m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)
	);
	// 2�{��
	m_p3DLine[1] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(m_size->x * 0.5f, m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXVECTOR3(m_size->x * 0.5f, -m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)
	);
	// 3�{��
	m_p3DLine[2] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(m_size->x * 0.5f, -m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXVECTOR3(-m_size->x * 0.5f, -m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)
	);
	// 4�{��
	m_p3DLine[3] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(-m_size->x * 0.5f, -m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXVECTOR3(-m_size->x * 0.5f, m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)
	);
	// 5�{��
	m_p3DLine[4] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(-m_size->x * 0.5f, m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXVECTOR3(-m_size->x * 0.5f, m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)
	);
	// 6�{��
	m_p3DLine[5] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(m_size->x * 0.5f, m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXVECTOR3(m_size->x * 0.5f, m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)
	);
	// 7�{��
	m_p3DLine[6] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(m_size->x * 0.5f, -m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXVECTOR3(m_size->x * 0.5f, -m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)

	);
	// 8�{��
	m_p3DLine[7] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(-m_size->x * 0.5f, -m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXVECTOR3(-m_size->x * 0.5f, -m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)

	);
	// 9�{��
	m_p3DLine[8] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(-m_size->x * 0.5f, m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXVECTOR3(m_size->x * 0.5f, m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)

	);
	// 10�{��
	m_p3DLine[9] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(m_size->x * 0.5f, m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXVECTOR3(m_size->x * 0.5f, -m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)

	);
	// 11�{��
	m_p3DLine[10] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(m_size->x * 0.5f, -m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXVECTOR3(-m_size->x * 0.5f, -m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)

	);
	// 12�{��
	m_p3DLine[11] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(-m_size->x * 0.5f, -m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXVECTOR3(-m_size->x * 0.5f, m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)

	);

}

// ----------------------------------------
// �̓����蔻�菈��
// ----------------------------------------
void CDebugcollision::BoardCollision(void)
{
	// 1�{�� ���
	m_p2DLine[0] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(-m_size->x * 0.5f, m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXVECTOR3(m_size->x * 0.5f, m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)
	);
	// 2�{�� �E��
	m_p2DLine[1] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(m_size->x * 0.5f, m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXVECTOR3(m_size->x * 0.5f, -m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)
	);
	// 3�{�ډ���
	m_p2DLine[2] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(m_size->x * 0.5f, -m_size->y * 0.5f, m_size->z * 0.5f),
		D3DXVECTOR3(-m_size->x * 0.5f, -m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)
	);
	// 4�{�ڍ���
	m_p2DLine[3] = C3DLine::Create(
		*m_pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(-m_size->x * 0.5f, -m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXVECTOR3(-m_size->x * 0.5f, m_size->y * 0.5f, -m_size->z * 0.5f),
		D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)
	);
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CDebugcollision::Uninit(void)
{
	m_pos = NULL;										// ���W�|�C���^�̏�����
	m_size = NULL;										// �T�C�Y�|�C���^�̏�����
	for (int nCnt = 0; nCnt < MAX_VERTEX3D; nCnt++)		// line�N���X�̃|�C���^������
	{
		m_p3DLine[nCnt] = NULL;
	}
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CDebugcollision::Update(void)
{
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CDebugcollision::Draw(void)
{
}

// ----------------------------------------
// ��������
// ----------------------------------------
CDebugcollision * CDebugcollision::Create(
	D3DXVECTOR3 * pos,
	D3DXVECTOR3 * size,
	COLLISIONTYPE type
)
{
	// �ϐ��錾
	CDebugcollision * pDebugcollision;
	// �������m��
	pDebugcollision = new CDebugcollision(OBJTYPE_DEBUGCOLLISION);
	// ���W�̐ݒ�
	pDebugcollision->m_pos = pos;
	// �T�C�Y�̐ݒ�
	pDebugcollision->m_size = size;
	// ��ނ̐ݒ�
	pDebugcollision->m_type = type;
	// ������
	pDebugcollision->Init();
	return pDebugcollision;
}

// ----------------------------------------
// �ʒu�ݒ菈��
// ----------------------------------------
void CDebugcollision::SetPos(D3DXVECTOR3 * pos)
{
	// ���W�̃|�C���^��NULL����Ȃ�������ʂ�
	if (pos != NULL)
	{
		// ���W������
		m_pos = pos;

		// ����̎�ނ����^��������ʂ�
		if (m_type == COLLISIONTYPE_BOX)
		{
			// ���W�̃|�C���^��line�̍��W�ɐݒ�
			for (int nCnt = 0; nCnt < MAX_VERTEX3D; nCnt++)
			{
				if (m_p3DLine[nCnt] != NULL)
				{
					m_p3DLine[nCnt]->SetPosColi(*pos);
				}
			}
		}

		// ����̎�ނ��^��������ʂ�
		else if (m_type == COLLISIONTYPE_BOARD)
		{
			// ���W�̃|�C���^��line�̍��W�ɐݒ�
			for (int nCnt = 0; nCnt < MAX_VERTEX2D; nCnt++)
			{
				if (m_p2DLine[nCnt] != NULL)
				{
					m_p2DLine[nCnt]->SetPosColi(*pos);
				}
			}
		}
	}
}

// ----------------------------------------
// �T�C�Y�ݒ菈��
// ----------------------------------------
void CDebugcollision::SetSize(D3DXVECTOR3 * size)
{
	m_size = size;
}
