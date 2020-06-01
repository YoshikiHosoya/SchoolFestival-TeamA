//------------------------------------------------------------------------------
//
//UI����  [UI.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _UI_H_
#define _UI_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scene2D.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CMenu;

class CScene2D_UI : public CScene2D
{
public:
	CScene2D_UI();
	~CScene2D_UI();

	HRESULT Init();					//������
	void Uninit();					//�I��
	void Update();					//�X�V
	void Draw();					//�`��
	static std::shared_ptr<CScene2D_UI> Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, int nTexID, CScene::OBJTYPE objtype);			//����
	void ShowDebugInfo();			//�f�o�b�O���\�L

	void SetTexID(CTexture::TEX_TYPE TexID);		//�e�N�X�`����ID�ݒ�
	CTexture::TEX_TYPE GetTexID();					//�e�N�X�`����ID�擾
protected:

private:
	CTexture::TEX_TYPE m_nTexID;					//�e�N�X�`���ԍ�
	int m_nCnt;										//�J�E���g
};

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CUI : public CScene
{
public:
	//UI�̃V�[��
	enum UI_SCENE
	{
		SCENE_TITLE = 0,			//�^�C�g��
		SCENE_GAME,					//�Q�[��
		SCENE_RESULT,				//���U���g
		SCENE_PAUSE,				//�|�[�Y
		SCENE_GAMEEND,				//�Q�[���I��
		SCENE_RANKING,				//�����L���O
		SCENE_MAX
	};

	//UI�̃^�C�v
	enum UI_TYPE
	{
		TYPE_SCENE2D = 0,			//Scene2D
		TYPE_MENU_VERTICAL,			//�c���j���[
		TYPE_MENU_HORIZON,			//�����j���[
		TYPE_MAX
	};


	CUI(); 							//�R���X�g���N�^
	~CUI();							//�f�X�g���N�^

	HRESULT Init();					//������
	void Uninit();					//�I��
	void Update();					//�X�V
	void Draw();					//�`��
	static void Create();			//����
	void ShowDebugInfo();			//�f�o�b�O���\�L

	static HRESULT LoadTexName();								//�e�N�X�`�����ǂݍ���
	HRESULT SavePlaceData();									//�z�u���ۑ�
	static HRESULT LoadPlace(UI_SCENE scene);					//�z�u���ǂݍ���

	static bool ShowTexComboBox(int &nTexID);						//Imgui�̃R���{�{�b�N�X�@�e�N�X�`��
	static bool ShowTypeComboBox(int &nType);						//Imgui�̃R���{�{�b�N�X�@�^�C�v
	static LPDIRECT3DTEXTURE9 GetTexture(int nTexID);				//�e�N�X�`�����擾
	void DeleteAll();

protected:

private:
	static std::vector<LPDIRECT3DTEXTURE9>		m_pTextureList;			//�e�N�X�`���ւ̃|�C���^
	static std::vector<std::string>				m_aTexNameList;			//�e�N�X�`�����̃|�C���^
	std::vector<std::shared_ptr<CScene2D_UI>>	m_pScene2DUIList;		//�|���S���̃|�C���^
	std::vector<std::shared_ptr<CMenu>>			m_pMenuList;			//���j���[�̃|�C���^

	static std::vector<std::string>				m_aPlaceFileName;		//�ꏊ�̃t�@�C����
	static std::vector<std::string>				m_aTypeNameList;		//�e�N�X�`�����̃|�C���^

};

#endif