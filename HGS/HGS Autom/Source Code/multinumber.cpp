//------------------------------------------------------------------------------
//
//�������̐��l�̏���  [multinumber.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "multinumber.h"
#include "number.h"

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
CMultiNumber::CMultiNumber()
{
	//������
	m_pNumberList.clear();
	m_nCnt = 0;
	m_nValue = 0;
	m_type = CMultiNumber::TYPE_NORMAL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CMultiNumber::~CMultiNumber()
{
	m_pNumberList.clear();
}

//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CMultiNumber::Init()
{
	//������
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CMultiNumber::Uninit()
{

}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CMultiNumber::Update()
{
	//�J�E���g���Z
	m_nCnt++;

	// �^�C�v�ɂ���ď�����ς���
	switch (m_type)
	{
		//�_�Ń^�C�v
	case CMultiNumber::TYPE_FLASHING:
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

		//�����ɏo�Ă��ď��X�ɏ����Ă�
	case CMultiNumber::TYPE_CENTER_DISAPPEAR:
		//�J�E���g�����ȏ�ɂȂ�����
		if (m_nCnt >= DISAPPEAR_COUNT)
		{
			//�J��
			Release();
			return;
		}

		//�F�ݒ� ���X�ɓ����ɂȂ銴��
		SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, (DISAPPEAR_COUNT - m_nCnt) * 0.01f));
		SetSize(GetSize() + D3DXVECTOR3(DISAPPEAR_SCALE_VALUE, DISAPPEAR_SCALE_VALUE, 0.0f));
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
void CMultiNumber::Draw()
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
void CMultiNumber::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //_DEBUG
}

//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
std::shared_ptr<CMultiNumber> CMultiNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 onesize, int nValue, int nDigits, CScene::OBJTYPE objtype)
{
	//�������m��
	std::shared_ptr<CMultiNumber> pMultiNumber(new CMultiNumber);

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
			pMultiNumber->m_pNumberList.emplace_back(CNumber::Create(pos + D3DXVECTOR3(-onesize.x * (nDigits - 1) * 0.5f + onesize.x * nCnt, 0.0f, 0.0f), onesize));
		}

		//���l�̏�����
		pMultiNumber->SetMultiNumber(nValue);

		//Scene�̃��X�g�ŊǗ�
		pMultiNumber->SetObjType(objtype);
		pMultiNumber->AddSharedList(pMultiNumber);

		//���^�[��
		return pMultiNumber;
	}
	return nullptr;
}
//------------------------------------------------------------------------------
//�X�R�A���Z����
//------------------------------------------------------------------------------
void CMultiNumber::SetMultiNumber(int nValue)
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
void CMultiNumber::SetChangeAnimation(int nValue, int nValueOld)
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
void CMultiNumber::SetCol(D3DXCOLOR col)
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
void CMultiNumber::SetPos(D3DXVECTOR3 pos)
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
			m_pNumberList[nCnt]->SetPos(pos + D3DXVECTOR3(-m_pNumberList[nCnt]->GetSize().x * (m_pNumberList.size() - 1) * 0.5f + m_pNumberList[nCnt]->GetSize().x * nCnt, 0.0f, 0.0f));
		}
	}
}
//------------------------------------------------------------------------------
//�T�C�Y�ݒ�
//------------------------------------------------------------------------------
void CMultiNumber::SetSize(D3DXVECTOR3 size)
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
