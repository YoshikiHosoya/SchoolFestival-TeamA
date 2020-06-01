//------------------------------------------------------------------------------
//
//�|�[�Y����  [title.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _PAUSE_H_
#define _PAUSE_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CScene2D;
class CMenu;
class COption;

class CPause : public CScene
{
public:
	CPause();
	~CPause();

	//�e�N�X�`���̎��
	enum TEX_TYPE
	{
		TEX_BG,					//�w�i
		TEX_LOGO,				//���S
		TEX_MENU,				//���j���[
		TEX_MAX
	};

	HRESULT Init();									//������
	void Uninit();									//�I��
	void Update();									//�X�V
	void Draw();									//�`��
	void ShowDebugInfo();							//�f�o�b�O���\�L
	static std::shared_ptr<CPause> Create();		//��������
	bool GetOptionWindow();							//�I�v�V�����J���Ă��邩�ǂ���
private:
	std::vector<std::unique_ptr<CScene2D>> m_pScene2DList;			//2D�|���S��
	std::unique_ptr<CMenu>	m_pMenu;								//���j���[�ւ̃|�C���^
	std::unique_ptr<COption> m_pOption;								//�I�v�V�����̃|�C���^

};

#endif