//------------------------------------------------------------------------------
//
//���j���[����  [Menu.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "menu.h"
#include "scene2D.h"
#include "manager.h"
#include "sound.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CMenu::m_pTexture = nullptr;

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CMenu::CMenu()
{
	m_apScene2DList = {};

	m_nChoiseNum = 0;
	m_nSelectNum = 0;
	m_type = CMenu::MENU_VERTICAL;
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CMenu::~CMenu()
{
	//�z��̊J��
	m_apScene2DList.clear();
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CMenu::Init()
{
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CMenu::Uninit()
{

}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CMenu::Update()
{
	//nullcheck
	if (!m_apScene2DList.empty())
	{
		for (size_t nCnt = 0; nCnt < m_apScene2DList.size(); nCnt++)
		{
			//�J�[�\���̍��������͖̂��邭
			if (nCnt == m_nSelectNum)
			{
				m_apScene2DList[nCnt]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			//����ȊO�̍��ڂ͈Â�
			else
			{
				m_apScene2DList[nCnt]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
			}

			//�X�V����
			m_apScene2DList[nCnt]->Update();
		}
	}
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CMenu::Draw()
{
	//nullcheck
	if (!m_apScene2DList.empty())
	{
		for (size_t nCnt = 0; nCnt < m_apScene2DList.size(); nCnt++)
		{
			//�`�揈��
			m_apScene2DList[nCnt]->Draw();
		}
	}
}
//------------------------------------------------------------------------------
//�f�o�b�O���\��
//------------------------------------------------------------------------------
void CMenu::ShowDebugInfo()
{
#ifdef _DEBUG

#endif // _DEBUG

}
//------------------------------------------------------------------------------
//����
//------------------------------------------------------------------------------
std::unique_ptr<CMenu> CMenu::Create(D3DXVECTOR3 pos, D3DXVECTOR3 onesize, LPDIRECT3DTEXTURE9 pTex, D3DXVECTOR2 UVCnt, CMenu::TYPE type)
{
	//�������m��
	std::unique_ptr<CMenu> pMenu(new CMenu);

	//������
	pMenu->Init();

	//�I�����̐�
	pMenu->m_nChoiseNum = (int)UVCnt.y;
	pMenu->m_type = type;

	//UV�ݒ�
	D3DXVECTOR2 UVSize = D3DXVECTOR2(1 / UVCnt.x, 1 / UVCnt.y);

	//����
	for (int nCnt = 0; nCnt < pMenu->m_nChoiseNum; nCnt++)
	{
		switch (type)
		{
			//�c�̃��j���[
		case CMenu::MENU_VERTICAL:
			pMenu->m_apScene2DList.emplace_back(CScene2D::Create_SelfManagement(pos + D3DXVECTOR3(0.0f, -pMenu->m_nChoiseNum * onesize.y * 0.5f + onesize.y * nCnt, 0.0f), onesize));
			break;

			//���̃��j���[
		case CMenu::MENU_HORIZON:
			pMenu->m_apScene2DList.emplace_back(CScene2D::Create_SelfManagement(pos + D3DXVECTOR3(-onesize.x * 0.5f + onesize.x * nCnt, 0.0f, 0.0f), onesize));
			break;
		}
		//�e�N�X�`���Z�b�g
		pMenu->m_apScene2DList[nCnt]->BindTexture(pTex);
		pMenu->m_apScene2DList[nCnt]->SetAnimation(D3DXVECTOR2(0.0f, UVSize.y * nCnt), UVSize);
	}


	//�����������
	return pMenu;
}
//------------------------------------------------------------------------------
//�ԍ��擾
//------------------------------------------------------------------------------
void CMenu::MenuSelect()
{
	switch (m_type)
	{
		//�c���j���[
	case CMenu::MENU_VERTICAL:
		CHossoLibrary::SelectVerticalMenu(m_nSelectNum, m_nChoiseNum);
		break;

		//�����j���[
	case CMenu::MENU_HORIZON:
		CHossoLibrary::SelectHorizonMenu(m_nSelectNum, m_nChoiseNum);

		break;
	}
}
//------------------------------------------------------------------------------
//�ԍ��擾
//------------------------------------------------------------------------------
int CMenu::GetSelectNum()
{
	return m_nSelectNum;
}
