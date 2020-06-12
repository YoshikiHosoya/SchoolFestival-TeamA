// =====================================================================================================================================================================
//
// �����L���OUI�̏���[rankingUI.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _RANKINGUI_H_
#define _RANKINGUI_H_	 

#define _CRT_SECURE_NO_WARNINGS

#include "main.h"			// �C���N���[�h�t�@�C��
#include"scene2D.h"

// =====================================================================================================================================================================
// �����L���OUI�N���X
// =====================================================================================================================================================================
class CRankingUI : public CScene2D
{
public:

	// UI�̎��
	enum RANKINGUITYPE
	{
		RK_UI_NONE = -1,
		RK_UI_RANK_1,				// 1��
		RK_UI_RANK_2,				// 2��
		RK_UI_RANK_3,				// 3��
		RK_UI_RANK_4,				// 4��
		RK_UI_RANK_5,				// 5��
		RK_UI_RANKING,				// �����L���O
		RK_UI_ENTER,				// Enter�L�[

		RK_UI_MAX,
	};

	CRankingUI();								// �R���X�g���N�^
	~CRankingUI();								// �f�X�g���N�^

	/* �����o�֐� */
	void				Init();					// ������
	void				Uninit();				// �I��
	void				Update();				// �X�V
	void				Draw();					// �`��

	/* �ÓI�����o�֐� */
	static  CRankingUI	*Create();				// ���U���gUI�̐���
	static	HRESULT		Load();					// ���[�h				( �ǂݍ��� )
	static	void		Unload();				// �A�����[�h			( �j�� )

private:
	/* �ÓI�����o�ϐ� */
	static	LPDIRECT3DTEXTURE9	m_apTexture[RANKINGUITYPE::RK_UI_MAX];		// ���L�e�N�X�`���̃|�C���^
	/* �����o�ϐ� */
	CScene2D					*m_apScene2D[RANKINGUITYPE::RK_UI_MAX];		// �V�[��2D�̃|�C���^
	D3DXVECTOR3					m_UV[RANKINGUITYPE::RK_UI_MAX];				// UV
};
#endif
