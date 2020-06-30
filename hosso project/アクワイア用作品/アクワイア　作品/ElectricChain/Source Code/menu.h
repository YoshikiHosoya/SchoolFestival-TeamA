//------------------------------------------------------------------------------
//
//���j���[����  [menu.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MENU_H_
#define _MENU_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CScene2D;

class CMenu
{
public:
	CMenu();
	~CMenu();

	enum TYPE
	{
		MENU_VERTICAL = 0,		//�c�̃��j���[
		MENU_HORIZON,			//���̃��j���[
		MAX
	} ;

	HRESULT Init();					//������
	void Uninit();					//�I��
	void Update();					//�X�V
	void Draw();					//�`��
	void ShowDebugInfo();			//�f�o�b�O���\�L
	static std::unique_ptr<CMenu> Create(D3DXVECTOR3 pos,D3DXVECTOR3 onesize, LPDIRECT3DTEXTURE9 pTex,D3DXVECTOR2 UVCnt,CMenu::TYPE type);	//��������
	void MenuSelect();				//���j���[�I������
	int GetSelectNum();				//���ݑI�����Ă��郁�j���[�ԍ��擾

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;						//�e�N�X�`���ւ̃|�C���^
	std::vector<std::shared_ptr<CScene2D>> m_apScene2DList;		//2D�|���S���̃|���S��
	D3DXVECTOR2 m_UVCnt;										//UV�̖���
	D3DXVECTOR2 m_UVSize;										//UV�̑傫��
	TYPE m_type;												//���
	int m_nChoiseNum;											//�I�����̐�
	int m_nSelectNum;											//����̔ԍ�

};

#endif