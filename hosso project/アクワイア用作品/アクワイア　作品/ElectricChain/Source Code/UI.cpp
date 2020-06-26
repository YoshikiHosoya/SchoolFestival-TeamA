//------------------------------------------------------------------------------
//
//�V�[��2D����  [scene2D.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "UI.h"
#include "scene2D.h"
#include "renderer.h"
#include "menu.h"
#include "manager.h"
#include "keyboard.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
std::vector<LPDIRECT3DTEXTURE9> CUI::m_pTextureList = {};
std::vector<std::string> CUI::m_aTexNameList = {};

//�t�@�C���̏ꏊ
std::vector<std::string> CUI::m_aPlaceFileName =
{
	{ "data/SAVEDATA/UI/TitleUI_Place.txt " },
	{ "data/SAVEDATA/UI/GameUI_Place.txt " },
	{ "data/SAVEDATA/UI/ResultUI_Place.txt " },
	{ "data/SAVEDATA/UI/PauseUI_Place.txt " },
	{ "data/SAVEDATA/UI/GameendUI_Place.txt " },
	{ "data/SAVEDATA/UI/RankingUI_Place.txt " },
};

//UI�̃^�C�v
std::vector<std::string> CUI::m_aTypeNameList =
{
	{ "Scene2D" },
	{ "Menu_Vertical" },
	{ "Menu_Horizon" },
};
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define TEXFILE_NAME ("data/SAVEDATA/UI/TexName.txt")
#define SAVEFILE_NAME ("data/SAVEDATA/UI/Save.txt")
#define FLASHING_INTERVAL_ALPHA (0.015f)

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CUI::CUI()
{

}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CUI::~CUI()
{

}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CUI::Init()
{

	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CUI::Uninit()
{
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CUI::Update()
{

}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CUI::Draw()
{
}
//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
void CUI::Create()
{

}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CUI::ShowDebugInfo()
{
#ifdef _DEBUG

	//UI���
	if (ImGui::TreeNode("UIINfo"))
	{
		//tree�I��
		ImGui::TreePop();
	}
#endif //DEBUG
}

//------------------------------------------------------------------------------
//�e�N�X�`�����ǂݍ���
//------------------------------------------------------------------------------
HRESULT CUI::LoadTexName()
{
	//�ϐ��錾
	FILE *pFile;			//�t�@�C���̃|�C���^
	char cReadText[MAX_TEXT];
	char cHeadText[MAX_TEXT];
	char cDieText[MAX_TEXT];
	int nCntTex = 0;
	int nNumTex = 0;

	//�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�t�@�C�����J��
	pFile = fopen(TEXFILE_NAME, "r");

	//�t�@�C�����������ꍇ
	if (pFile)
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
				//���f���ԍ���������
				else if (strcmp(cHeadText, "NUM_TEXTURE") == 0)
				{
					sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &nNumTex);

					while (1)
					{
						fgets(cReadText, sizeof(cReadText), pFile);
						sscanf(cReadText, "%s", &cHeadText);

						//�t�@�C���l�[���̓ǂݍ���
						if (strcmp(cHeadText, "TEXTURE_FILENAME") == 0)
						{
							LPDIRECT3DTEXTURE9 pTex;

							//�� �e�N�X�`����
							char cData[MAX_TEXT];

							//���f�������
							sscanf(cReadText, "%s %s %s %s %s", &cDieText, &cDieText, &cData, &cDieText, &cDieText);

							//�e�N�X�`���̓ǂݍ���
							D3DXCreateTextureFromFile(pDevice,
								cData,
								&pTex);

							//NULL�`�F�b�N
							if (!pTex)
							{
								//���s
								std::cout << "�e�N�X�`���ǂݍ��ݎ��s " << "-" << nNumTex << NEWLINE;
							}


							//�z��ɒǉ�
							m_aTexNameList.emplace_back(cData);
							m_pTextureList.emplace_back(pTex);

							//debug
							std::cout << "new  : " << "pTexName" << "-" << nCntTex << "-";
							std::cout << "Name" << ">>" << m_aTexNameList[nCntTex].data() << NEWLINE;

							//���f�����J�E���g�A�b�v
							nCntTex++;

							//�ŏ��ɐ錾���ꂽ���f�����ɂȂ�����
							if (nCntTex == nNumTex)
							{
								//���[�v�𔲂���
								break;
							}
						}
					}
				}
			}
		}
		//�t�@�C�������
		fclose(pFile);
	}
	//�J���Ȃ�������
	else
	{
		std::cout << "�e�L�X�g�ǂݍ��ݎ��s" << "LoadTexname()" << NEWLINE;
		return E_FAIL;
	}
	return S_OK;
}
//------------------------------------------------------------------------------
//�z�u���ۑ�
//------------------------------------------------------------------------------
HRESULT CUI::SavePlaceData()
{
	FILE *pFile;

	int nRotNum = 0;
	char cHeadtext[128];
	char cWriteText[128];

	pFile = fopen(SAVEFILE_NAME, "w");

	if (pFile != nullptr)
	{
		//�u���b�N�R�����g
		fputs(COMMENT02, pFile);
		fputs(COMMENT01, pFile);

		strcpy(cHeadtext, "#Block\n");
		fputs(cHeadtext, pFile);

		strcpy(cHeadtext, "#Author:Yoshiki Hosoya\n");
		fputs(cHeadtext, pFile);

		fputs(COMMENT01, pFile);
		fputs(COMMENT02, pFile);
		fputs(NEWLINE, pFile);

		//�u���b�N�R�����g�I��//

		//�X�N���v�g
		strcpy(cHeadtext, "SCRIPT");
		fputs(cHeadtext, pFile);
		fputs(NEWLINE, pFile);

		//nullcheck
		if (!m_pScene2DUIList.empty())
		{
			for (size_t nCnt = 0; nCnt < m_pScene2DUIList.size(); nCnt++)
			{
				//Scene2D�Z�b�g
				strcpy(cHeadtext, "SCENE2DSET\n");
				sprintf(cWriteText, "	%s", &cHeadtext);
				fputs(cWriteText, pFile);

				//�e�N�X�`�����
				strcpy(cHeadtext, "TEX_TYPE");
				sprintf(cWriteText, "		%s %s %d", &cHeadtext, &EQUAL, m_pScene2DUIList[nCnt]->GetTexID());
				fputs(cWriteText, pFile);
				fputs(NEWLINE, pFile);

				//���W
				strcpy(cHeadtext, "POS");
				sprintf(cWriteText, "		%s %s %0.1f %0.1f %0.1f", &cHeadtext, &EQUAL, m_pScene2DUIList[nCnt]->GetPos().x, m_pScene2DUIList[nCnt]->GetPos().y, m_pScene2DUIList[nCnt]->GetPos().z);
				fputs(cWriteText, pFile);
				fputs(NEWLINE, pFile);

				//�T�C�Y
				strcpy(cHeadtext, "SIZE");
				sprintf(cWriteText, "		%s %s %0.1f %0.1f %0.1f", &cHeadtext, &EQUAL, m_pScene2DUIList[nCnt]->GetSize().x, m_pScene2DUIList[nCnt]->GetSize().y, m_pScene2DUIList[nCnt]->GetSize().z);
				fputs(cWriteText, pFile);
				fputs(NEWLINE, pFile);

				//�G���h�Z�b�g
				strcpy(cHeadtext, "END_SCENE2DSET");
				sprintf(cWriteText, "	%s", &cHeadtext);
				fputs(cWriteText, pFile);
				fputs(NEWLINE, pFile);
				fputs(NEWLINE, pFile);

				std::cout << "SavingScene2D : " << nCnt << NEWLINE;

			}
		}
		else
		{
			//�z�񂪋�
			std::cout << "m_pScene2DUIList.empty() " << NEWLINE;
		}


		//nullcheck
		if (!m_pMenuList.empty())
		{

		}
		else
		{
			//�z�񂪋�
			std::cout << "m_pMenuList.empty() " << NEWLINE;
		}

		//�X�N���v�g
		strcpy(cHeadtext, "END_SCRIPT");
		fputs(cHeadtext, pFile);
		fputs(NEWLINE, pFile);

		//�Z�[�u����
		std::cout << "Save Success! SavePlaceData()" << NEWLINE;

		//�t�@�C�������
		fclose(pFile);

	}
	else
	{
		//�t�@�C�����J���܂���ł���
		std::cout << "Save FAILED!!  Can't Open File. SavePlaceData()" << NEWLINE;
		return E_FAIL;
	}
	return S_OK;
}

//------------------------------------------------------------------------------
//�z�u���ǂݍ���
//------------------------------------------------------------------------------
HRESULT CUI::LoadPlace(UI_SCENE scene)
{
	//�ϐ��錾
	FILE *pFile;			//�t�@�C���̃|�C���^
	char cReadText[MAX_TEXT];
	char cHeadText[MAX_TEXT];
	char cDieText[MAX_TEXT];

	int nTexID = 0;							//�e�N�X�`��ID
	D3DXVECTOR3 pos;						//���W
	D3DXVECTOR3 size;						//�T�C�Y
	D3DXCOLOR col;							//�F

	//�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�t�@�C�����J��
	pFile = fopen(m_aPlaceFileName[scene].data(), "r");

	//�t�@�C�����������ꍇ
	if (pFile)
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
				//���f���ԍ���������
				else if (strcmp(cHeadText, "SCENE2DSET") == 0)
				{
					//�G���h�X�N���v�g������O���[�v
					while (strcmp(cHeadText, "END_SCENE2DSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile);
						sscanf(cReadText, "%s", &cHeadText);

						//�e�N�X�`���̎��
						if (strcmp(cHeadText, "TEX_TYPE") == 0)
						{
							sscanf(cReadText, "%s %s %d",&cDieText, &cDieText, &nTexID);
						}

						//���W
						if (strcmp(cHeadText, "POS") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDieText, &cDieText, &pos.x, &pos.y, &pos.z);
						}

						//�T�C�Y
						if (strcmp(cHeadText, "SIZE") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDieText, &cDieText, &size.x, &size.y, &size.z);
						}
						//�F
						if (strcmp(cHeadText, "COLOR") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f %f", &cDieText, &cDieText, &col.r, &col.g, &col.b, &col.a);
						}

						//�I��
						if (strcmp(cHeadText, "END_SCENE2DSET") == 0)
						{
							CScene2D_UI::Create(pos, size, col,nTexID,CScene::OBJTYPE_2DUI);
						}
					}
				}
			}
		}
	}
	//�J���Ȃ�������
	else
	{
		std::cout << "�e�L�X�g�ǂݍ��ݎ��s" << "LoadPlace()" << NEWLINE;
		return E_FAIL;
	}
	return S_OK;

}
//------------------------------------------------------------------------------
//�R���{�{�b�N�X(Tex)
//------------------------------------------------------------------------------
bool CUI::ShowTexComboBox(int &nTexID)
{
	bool bChange = false;

#ifdef _DEBUG
		//combo�J�n
	if (ImGui::BeginCombo("TextureName", m_aTexNameList[nTexID].data()))
	{
		//�v�f���J��Ԃ�
		for (size_t nCnt = 0; nCnt < m_aTexNameList.size(); nCnt++)
		{
			//�I��ԍ��������Ă邩�ǂ���
			bool is_selected = (m_aTexNameList[nTexID] == m_aTexNameList[nCnt]);

			//�I�����ꂽ���̏���
			if (ImGui::Selectable(m_aTexNameList[nCnt].data(), is_selected))
			{
				//���݂̑I�����ڐݒ�
				nTexID = nCnt;
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
//�R���{�{�b�N�X(Type)
//------------------------------------------------------------------------------
bool CUI::ShowTypeComboBox(int & nType)
{
	bool bChange = false;

#ifdef _DEBUG
	//combo�J�n
	if (ImGui::BeginCombo("TypeName", m_aTypeNameList[nType].data()))
	{
		//�v�f���J��Ԃ�
		for (size_t nCnt = 0; nCnt < m_aTypeNameList.size(); nCnt++)
		{
			//�I��ԍ��������Ă邩�ǂ���
			bool is_selected = (m_aTypeNameList[nType] == m_aTypeNameList[nCnt]);

			//�I�����ꂽ���̏���
			if (ImGui::Selectable(m_aTypeNameList[nCnt].data(), is_selected))
			{
				//���݂̑I�����ڐݒ�
				nType = nCnt;
				bChange = true;

				//�e�N�X�`���ݒ�
			}
		}
		//combo�I��
		ImGui::EndCombo();
	}
#endif //DEBUG
	return bChange;
}
//------------------------------------------------------------------------------
//�e�N�X�`�����擾
//------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CUI::GetTexture(int nTexID)
{
	return m_pTextureList[nTexID];
}
//------------------------------------------------------------------------------
//����
//------------------------------------------------------------------------------
void CUI::DeleteAll()
{
	//nullcheck
	if (!m_pScene2DUIList.empty())
	{
		for (size_t nCnt = 0; nCnt < m_pScene2DUIList.size(); nCnt++)
		{
			m_pScene2DUIList[nCnt]->Release();
		}
		m_pScene2DUIList.clear();
	}
}

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CScene2D_UI::CScene2D_UI()
{
	m_nCnt = 0;
	m_nTexID = CTexture::TEX_NONE;
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CScene2D_UI::~CScene2D_UI()
{
}
//------------------------------------------------------------------------------
//������
//------------------------------------------------------------------------------
HRESULT CScene2D_UI::Init()
{
	CScene2D::Init();

	return S_OK;
}
//------------------------------------------------------------------------------
//�I��
//------------------------------------------------------------------------------
void CScene2D_UI::Uninit()
{
	CScene2D::Uninit();

}
//------------------------------------------------------------------------------
//�X�V
//------------------------------------------------------------------------------
void CScene2D_UI::Update()
{
	CScene2D::Update();

	switch (m_nTexID)
	{

	case CTexture::TEX_UI_PRESS_ANY_BUTTON:
		//�J�E���g�A�b�v
		m_nCnt++;

		float fCol_a;

		//a�l�擾
		fCol_a = GetCol().a;

		//�������œ_��
		m_nCnt % 180 >= 90 ? fCol_a += FLASHING_INTERVAL_ALPHA : fCol_a -= FLASHING_INTERVAL_ALPHA;

		//�F�ݒ�
		SetVtxCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, fCol_a));
		break;

	}

}
//------------------------------------------------------------------------------
//�`��
//------------------------------------------------------------------------------
void CScene2D_UI::Draw()
{
	CScene2D::Draw();

}

//------------------------------------------------------------------------------
//����
//------------------------------------------------------------------------------
std::shared_ptr<CScene2D_UI> CScene2D_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, int nTexID,CScene::OBJTYPE objtype)
{
	//������
	std::shared_ptr<CScene2D_UI> pScene2D_UI = std::make_shared<CScene2D_UI>();

	//nullcheck
	if (pScene2D_UI)
	{
		pScene2D_UI->Init();

		//���W�ƃT�C�Y�ݒ�
		pScene2D_UI->SetPos(pos);
		pScene2D_UI->SetSize(size);
		pScene2D_UI->SetVtxCol(col);
		pScene2D_UI->SetTexID((CTexture::TEX_TYPE)nTexID);

		//Scene�̃|�C���^�ɒǉ�
		pScene2D_UI->SetObjType(objtype);
		pScene2D_UI->AddSharedList(pScene2D_UI);

		return pScene2D_UI;
	}
	return nullptr;
}
//------------------------------------------------------------------------------
//�f�o�b�O���\��
//------------------------------------------------------------------------------
void CScene2D_UI::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}
//------------------------------------------------------------------------------
//�e�N�X�`���ݒ�
//------------------------------------------------------------------------------
void CScene2D_UI::SetTexID(CTexture::TEX_TYPE TexID)
{
	//�e�N�X�`���ԍ��ݒ�
	m_nTexID = TexID;

	//�e�N�X�`���ݒ�
	BindTexture(CTexture::GetTexture((CTexture::TEX_TYPE)TexID));
}
//------------------------------------------------------------------------------
//�e�N�X�`���ԍ��o��
//------------------------------------------------------------------------------
CTexture::TEX_TYPE CScene2D_UI::GetTexID()
{
	return m_nTexID;
}
