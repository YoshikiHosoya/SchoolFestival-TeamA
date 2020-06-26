//------------------------------------------------------------------------------
//
//�O�ʂ�UI  [FrontUI.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _FRONTUI_H_
#define _FRONTUI_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scene2D.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CFrontUI : public CScene2D
{
public:
	//�G�t�F�N�g�̎��
	enum TEX_TYPE
	{
		PUSH_B = 0,				//B
		PLAYER_HIT,				//�v���C���[��e
		RAIN,					//�J
		GAMESTART,				//�Q�[���X�^�[�g
		MAX,
	};

	CFrontUI();
	~CFrontUI();

	HRESULT Init();				//������
	void Uninit();				//�I��
	void Update();				//�X�V
	void Draw();				//�`��
	void ShowDebugInfo();		//�f�o�b�O���\��
	static void Create(D3DXVECTOR3 pos , D3DXVECTOR3 size, D3DXCOLOR col, TEX_TYPE type);	//��������

private:
	TEX_TYPE m_Type;					//�^�C�v
	int m_nCntUI;						//�J�E���^
	static bool m_bPushB;				//pushB���\������Ă��邩�ǂ����@�d���΍�
};

#endif