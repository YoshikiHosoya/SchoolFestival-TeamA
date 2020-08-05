//------------------------------------------------------------------------------
//
//�������̐����̏���  [multinumber.cpp]
// Author : Fujiwara Masato
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "3Dmultinumber.h"
#include "3Dnumber.h"

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define DISAPPEAR_COUNT			(60)
#define DISAPPEAR_SCALE_VALUE	(1.0f)
//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
C3DMultiNumber::C3DMultiNumber()
{
	//������
	m_pNumberList.clear();
	m_nCnt = 0;
	m_nValue = 0;
	m_type = C3DMultiNumber::TYPE_NORMAL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
C3DMultiNumber::~C3DMultiNumber()
{
	m_pNumberList.clear();
}

//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT C3DMultiNumber::Init()
{
	//������
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void C3DMultiNumber::Uninit()
{

}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void C3DMultiNumber::Update()
{
	//�J�E���g���Z
	m_nCnt++;

	// �^�C�v�ɂ���ď�����ς���
	switch (m_type)
	{
		//�_�Ń^�C�v
	case C3DMultiNumber::TYPE_FLASHING:
		//2F���ƂɐF��ς���
		if (m_nCnt % 4 == 0)
		{
			//��
			SetCol(D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f));
		}
		else if (m_nCnt % 4 == 2)
		{
			//��
			SetCol(D3DXCOLOR(1.0f, 1.0f, 0.1f, 1.0f));
		}
		break;
	}
	//nullcheck
	if (!m_pNumberList.empty())
	{
		//�T�C�Y��
		for (size_t nCnt = 0; nCnt < m_pNumberList.size(); nCnt++)
		{
			//nullcheck
			if (m_pNumberList[nCnt])
			{
				//�X�V
				m_pNumberList[nCnt]->Update();
			}
		}
	}
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void C3DMultiNumber::Draw()
{
	//nullcheck
	if (!m_pNumberList.empty())
	{
		//�T�C�Y��
		for (size_t nCnt = 0; nCnt < m_pNumberList.size(); nCnt++)
		{
			//nullcheck
			if (m_pNumberList[nCnt])
			{
				//�`��
				m_pNumberList[nCnt]->Draw();
			}
		}
	}
}

//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
void C3DMultiNumber::DebugInfo()
{
#ifdef _DEBUG

#endif //_DEBUG
}

//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
C3DMultiNumber * C3DMultiNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 onesize, int nValue, int nDigits, CScene::OBJ_TYPE objtype)
{
	//�������m��
	C3DMultiNumber *pMultiNumber = new C3DMultiNumber(objtype);

	//nullcheck
	if (pMultiNumber)
	{
		//����������
		pMultiNumber->Init();
		pMultiNumber->m_pos = pos;
		pMultiNumber->m_onesize = onesize;

		//Number�̐���
		for (int nCnt = 0; nCnt < nDigits; nCnt++)
		{
			//�z��ɒǉ�
			//���l�̕��Ԓ��S��pos�Ƃ���
			pMultiNumber->m_pNumberList.emplace_back(C3DNumber::Create(pos + D3DXVECTOR3(-onesize.x * (nDigits - 1) * 0.5f + onesize.x * nCnt, 0.0f, 0.0f), onesize));
		}

		//���l�̏�����
		pMultiNumber->SetMultiNumber(nValue);


		//���^�[��
		return pMultiNumber;
	}
	return nullptr;
}
//------------------------------------------------------------------------------
//�X�R�A���Z����
//------------------------------------------------------------------------------
void C3DMultiNumber::SetMultiNumber(int nValue)
{
	//�����������Ă��錅��
	int nDigits = 0;

	//�l�����Z
	m_nValue = nValue;

	//�J�E���g�X�g�b�v�@��������Ɍv�Z
	if (m_nValue >= (int)powf(10.0f, (float)m_pNumberList.size()))
	{
		m_nValue = (int)powf(10.0f, (float)m_pNumberList.size()) - 1;
	}
	//0�ȉ��ɂ��Ȃ�
	else if (m_nValue < 0)
	{
		m_nValue = 0;
	}

	//�e���̌v�Z
	for (size_t nCnt = 0; nCnt < m_pNumberList.size(); nCnt++)
	{
		//���l���o��
		int nMultiNumber = m_nValue % (int)powf(10.0f, m_pNumberList.size() - (float)nCnt) / (int)powf(10.0f, m_pNumberList.size() - (float)nCnt - 1.0f);
		float fMultiNumber = (float)nMultiNumber / 10.0f;

		//UV���W�ݒ�
		m_pNumberList[nCnt]->SetAnimation(D3DXVECTOR2(fMultiNumber, 0.0f), D3DXVECTOR2(0.1f, 1.0f));

		//���݂̌��Ő؂�̂Ă����ɒl��0�ȏ�ꍇ
		if (fabs(m_nValue / (int)powf(10.0f, m_pNumberList.size() - (float)nCnt - 1.0f)) > 0)
		{
			//�����J�E���g
			nDigits++;
		}
	}
	//����0�̂Ƃ���1�ɐݒ�
	if (nDigits == 0)
	{
		nDigits = 1;
	}

	//�����ɉ����ĕ\����\���̐ݒ�
	for (size_t nCnt = 0; nCnt < m_pNumberList.size(); nCnt++)
	{
		//�ő包�� - ���݂̌������J�E���g��菬�����ꍇ��true
		m_pNumberList[nCnt]->SetDisp(nCnt >= m_pNumberList.size() - nDigits ? true : false);
	}
}
//------------------------------------------------------------------------------
//�A�j���[�V�����Z�b�g
//------------------------------------------------------------------------------
void C3DMultiNumber::SetChangeAnimation(int nValue, int nValueOld)
{
	//������
	for (size_t nCnt = 0; nCnt < m_pNumberList.size(); nCnt++)
	{
		//�e���̐����Z�o
		int nNumber = nValue % (int)powf(10.0f, m_pNumberList.size() - (float)nCnt) / (int)powf(10.0f, m_pNumberList.size() - (float)nCnt - 1.0f);
		int nNumberOld = nValueOld % (int)powf(10.0f, m_pNumberList.size() - (float)nCnt) / (int)powf(10.0f, m_pNumberList.size() - (float)nCnt - 1.0f);

		//�O�̐����ƍ��̐������Ⴄ�ƋC
		if (nNumber != nNumberOld)
		{
			//�A�j���[�V����
			m_pNumberList[nCnt]->SetChangeAnimtion();
		}
	}
}
//------------------------------------------------------------------------------
//�F�ݒ�
//------------------------------------------------------------------------------
void C3DMultiNumber::SetCol(D3DXCOLOR col)
{
	if (!m_pNumberList.empty())
	{
		//�������J��Ԃ�
		for (size_t nCnt = 0; nCnt < m_pNumberList.size(); nCnt++)
		{
			//nullcheck
			if (m_pNumberList[nCnt])
			{
				//�F�ݒ�
				m_pNumberList[nCnt]->SetColor(col);
			}
		}
	}
}
//------------------------------------------------------------------------------
//���W�ݒ�
//------------------------------------------------------------------------------
void C3DMultiNumber::SetPos(D3DXVECTOR3 pos)
{
	//���W���
	m_pos = pos;

	//�������J��Ԃ�
	for (size_t nCnt = 0; nCnt < m_pNumberList.size(); nCnt++)
	{
		//nullcheck
		if (m_pNumberList[nCnt])
		{
			//���W�ݒ�
			m_pNumberList[nCnt]->SetPosition(pos + D3DXVECTOR3(-m_pNumberList[nCnt]->GetSize().x * (m_pNumberList.size() - 1) * 0.5f + m_pNumberList[nCnt]->GetSize().x * nCnt, 0.0f, 0.0f));
		}
	}
}
//------------------------------------------------------------------------------
//�T�C�Y�ݒ�
//------------------------------------------------------------------------------
void C3DMultiNumber::SetSize(D3DXVECTOR3 size)
{
	//���W���
	m_onesize = size;

	//�������J��Ԃ�
	for (size_t nCnt = 0; nCnt < m_pNumberList.size(); nCnt++)
	{
		//nullcheck
		if (m_pNumberList[nCnt])
		{
			//���W�ݒ�
			m_pNumberList[nCnt]->SetSize(size);
		}
	}
	SetPos(GetPos());
}

//------------------------------------------------------------------------------
//�\���E��\���̐ݒ�
//------------------------------------------------------------------------------
void C3DMultiNumber::SetDisp(bool bDisp)
{
	//�������J��Ԃ�
	for (size_t nCnt = 0; nCnt < m_pNumberList.size(); nCnt++)
	{
		//nullcheck
		if (m_pNumberList[nCnt])
		{
			//���W�ݒ�
			m_pNumberList[nCnt]->SetDisp(bDisp);
		}
	}
}