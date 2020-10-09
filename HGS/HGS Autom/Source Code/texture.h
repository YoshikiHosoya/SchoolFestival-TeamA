//------------------------------------------------------------------------------
//
//�e�N�X�`���Ǘ�  [texture.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

#ifndef _TEXTURE_H_
#define _TEXTURE_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
//�O���錾
class CTexture
{
public:
	CTexture() {};
	~CTexture() {};

	//�ʏ�̃e�N�X�`��
	enum TEX_TYPE
	{
		TEX_NONE = 0,

		TEX_EFFECT_PARTICLE,					//�p�[�e�B�N��

		//�L�����N�^�[
		TEX_PLAYER,						//�v���C���[
		TEX_ENEMY,							//�G

		TEX_WAY_UP,							//����
		TEX_WAY_RIGHT01,					//���E
		TEX_WAY_RIGHT02,					//���E
		TEX_WAY_LEFT01,						//����
		TEX_WAY_LEFT02,						//����

		TEX_ARROW_RIGHT,					//�E����
		TEX_ARROW_LEFT,						//������

		// --- UI ---
		// BG
		TEX_UI_BG_GRIDLINE,						// �O���b�h��
		TEX_UI_BG_CIRCLE,						// �܂�
		TEX_UI_BG_TRIANGLE,						// �O�p
		TEX_UI_BG_SQUARE,						// �l�p
		TEX_UI_BG_STAR,							// ��
		TEX_UI_BG_CROSS,						// �΂�

		// �Q�[��
		TEX_UI_GAME_LADY,						// Lady
		TEX_UI_GAME_GO,							// Go
		TEX_UI_GAME_GOOD,						// Good
		TEX_UI_GAME_GREAT,						// Great
		TEX_UI_GAME_PERFECT,					// Perfect
		TEX_UI_GAME_SPPED_UP,					// SpeeUp
		TEX_UI_GAME_ADDTIME_2,					// +2

		//�^�C�g��
		TEX_UI_TITLE_NAME,						// �^�C�g�����S

		//�����L���O
		TEX_UI_RANKING_NAME,					// �����L���O���S
		TEX_UI_RANKING_SCORE,					// �����L���O�X�R�A
		TEX_UI_RANKING_1st,						// 1��
		TEX_UI_RANKING_2nd,						// 2��
		TEX_UI_RANKING_3rd,						// 3��
		TEX_UI_RANKING_4th,						// 4��
		TEX_UI_RANKING_5th,						// 5��
		TEX_UI_RANKING_GO_TITLE,				// �^�C�g����

		TEX_UI_ENTER,							// Enter

		TEX_MAX									//MAX
	};

	//�A�j���[�V�����p�̃e�N�X�`��
	//��������Ă���e�N�X�`��
	enum SEPARATE_TEX_TYPE
	{
		SEPARATE_TEX_NONE = 0,

		//�G�t�F�N�g
		SEPARATE_TEX_EFFECT_EXPLOSION00,			//����

		SEPARATE_TEX_UI_NUMBER,						// �i���o�[

		SEPARATE_TEX_MAX							//MAX
	};

	typedef struct
	{
		LPDIRECT3DTEXTURE9 m_apSeparateTexture;		//�����e�N�X�`���ւ̃|�C���^
		SEPARATE_TEX_TYPE type;						//�e�N�X�`���̎��
		D3DXVECTOR2 m_UVCnt;						//UV�̖���
		D3DXVECTOR2 m_UVSize;						//UV�̑傫��

	}SEPARATE_TEX_INFO;

	static void TexLoad(HWND hwnd);						//�e�N�X�`������
	static void TexUnload();							//�e�N�X�`���j��

	static LPDIRECT3DTEXTURE9 GetTexture(TEX_TYPE textype);							//�ʏ�e�N�X�`���̎擾

	static std::vector<std::string> &GetTexFileName() { return m_aTexFileName; };						//�e�N�X�`�����擾
	static std::vector<std::string> &GetSeparateFileName() { return m_aSeparateTexFileNameList; };		//�����e�N�X�`�����擾

	static LPDIRECT3DTEXTURE9 GetSeparateTexture(SEPARATE_TEX_TYPE textype);		//�����e�N�X�`���擾
	static D3DXVECTOR2 GetSparateTex_UVSize(SEPARATE_TEX_TYPE textype);				//�����e�N�X�`���@UV�̃T�C�Y�擾
	static D3DXVECTOR2 GetSparateTex_UVCnt(SEPARATE_TEX_TYPE textype);				//�����e�N�X�`���@UV�̖����擾


private:
	static std::vector<LPDIRECT3DTEXTURE9> m_apTextureList;							//�ʏ�e�N�X�`���ւ̃|�C���^�̃��X�g
	static std::vector<std::string> m_aTexFileName;											//�ʏ�e�N�X�`���̃t�@�C����


	static std::vector<std::string> m_aSeparateTexFileNameList;								//�����e�N�X�`���̃t�@�C����
	static std::vector<SEPARATE_TEX_INFO> m_apSeparateTexInfoList;					//�����e�N�X�`���Ɋւ�����̃|�C���^

};

#endif