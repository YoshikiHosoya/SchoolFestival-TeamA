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

	enum TEX_TYPE
	{
		TEX_NONE = 0,

		//UI�֌W
		TEX_UI_PRESS_ANY_BUTTON,

		TEX_UI_TITLE_LOGO,						//�^�C�g�����S
		TEX_UI_TITLE_BG,						//�^�C�g���w�i

		TEX_UI_GAME_COMBO,						//�R���{
		TEX_UI_GAME_KILL,						//�L��
		TEX_UI_GAME_PLAYERICON,					//�v���C���[�A�C�R��
		TEX_UI_GAME_X_COMBOPATTERN,				//�R���{�p�^�[�� XInput
		TEX_UI_GAME_KEY_COMBOPATTERN,			//�R���{�p�^�[�� Keyboard
		TEX_UI_GAME_TIME,						//�^�C��

		TEX_UI_RESULT_LOGO,						//���U���g���S
		TEX_UI_RESULT_RESULTCALC,				//�X�R�A�v�Z

		TEX_UI_RANKING_LOGO,					//�����L���O���S
		TEX_UI_RANKING_BG,						//�����L���O�w�i
		TEX_UI_RANKING_1ST,						//1
		TEX_UI_RANKING_2ND,						//2
		TEX_UI_RANKING_3RD,						//3
		TEX_UI_RANKING_4TH,						//4
		TEX_UI_RANKING_5TH,						//5

		TEX_UI_TUTORIAL_X_SKIP,					//�`���[�g���A�� XInput�@�ړ�
		TEX_UI_TUTORIAL_X_MOVE,					//�`���[�g���A�� XInput�@�_�b�V��
		TEX_UI_TUTORIAL_X_DASH,					//�`���[�g���A�� XInput�@�_�b�V��
		TEX_UI_TUTORIAL_X_CAMERAMOVE,			//�`���[�g���A�� XInput�@�J������]
		TEX_UI_TUTORIAL_X_CAMERARESET,			//�`���[�g���A�� XInput�@�n�_���Z�b�g
		TEX_UI_TUTORIAL_X_JUMP,					//�`���[�g���A�� XInput�@�W�����v
		TEX_UI_TUTORIAL_X_ATTACK,				//�`���[�g���A�� XInput�@�U��
		TEX_UI_TUTORIAL_X_STARTCHAIN,			//�`���[�g���A�� XInput�@�A��
		TEX_UI_TUTORIAL_X_CHAINTHUNDER,			//�`���[�g���A�� XInput�@�A�������̐���

		TEX_UI_TUTORIAL_KEY_SKIP,				//�`���[�g���A�� Keyboard�@�ړ�
		TEX_UI_TUTORIAL_KEY_MOVE,				//�`���[�g���A�� Keyboard�@�_�b�V��
		TEX_UI_TUTORIAL_KEY_DASH,				//�`���[�g���A�� Keyboard�@�_�b�V��
		TEX_UI_TUTORIAL_KEY_CAMERAMOVE,			//�`���[�g���A�� Keyboard�@�J������]
		TEX_UI_TUTORIAL_KEY_CAMERARESET,		//�`���[�g���A�� Keyboard�@�n�_���Z�b�g
		TEX_UI_TUTORIAL_KEY_JUMP,				//�`���[�g���A�� Keyboard�@�W�����v
		TEX_UI_TUTORIAL_KEY_ATTACK,				//�`���[�g���A�� Keyboard�@�U��
		TEX_UI_TUTORIAL_KEY_STARTCHAIN,			//�`���[�g���A�� Keyboard�@�A��
		TEX_UI_TUTORIAL_KEY_CHAINTHUNDER,		//�`���[�g���A�� Keyboard�@�A�������̐���

		TEX_UI_TUTORIAL_FREE,					//�`���[�g���A���@���R
		TEX_UI_TUTORIAL_END,					//�`���[�g���A���@�I��
		TEX_UI_TUTORIAL_OK,						//�`���[�g���A���@OK

		TEX_UI_PAUSE_LOGO,						//�|�[�Y���S
		TEX_UI_OPTION_LOGO,						//�I�v�V�������S

		TEX_MINIMAP_MAP,						//�~�j�}�b�v
		TEX_MINIMAP_PLAYER,						//�v���C���[
		TEX_MINIMAP_ENEMY,						//�G
		TEX_MINIMAP_EXPLOSION,					//����

		TEX_GAMESTART,							//�Q�[���X�^�[�g
		TEX_FINISH,								//�I��

		TEX_MESH_FIELD,							//���b�V���t�B�[���h
		TEX_ORBIT_NORMAL,						//�O��
		TEX_EFFECT_PARTICLE,					//�p�[�e�B�N��
		TEX_SPHEREEXPLOISON,					//�X�t�B�A�̗�
		TEX_CIRCLETHUNDER,						//�~�̗�
		TEX_EXPLOSION_TRACE,					//������

		TEX_BACKUI_PUSH_B,						//pushB	XInput
		TEX_BACKUI_PUSH_Z,						//pushB Keyboard
		TEX_BACKUI_DAMAGED,						//��e
		TEX_BACKUI_RAIN,						//�J

		TEX_MAX									//MAX
	};

	//�A�j���[�V�����p�̃e�N�X�`��
	enum SEPARATE_TEX_TYPE
	{
		SEPARATE_TEX_UI_NUMBER,							//����
		SEPARATE_TEX_UI_PAUSE_MENU,						//�|�[�Y���j���[
		SEPARATE_TEX_UI_ON_OFF,							//ON_OFF
		SEPARATE_TEX_UI_OPTIONMENU,						//�I�v�V�������j���[

		SEPARATE_TEX_EFFECT_FLASH,						//�w�i�̗���
		SEPARATE_TEX_EFFECT_BACKTHUNDER,				//�w�i�̗���
		SEPARATE_TEX_EFFECT_LINETHUNDER,				//���̗�
		SEPARATE_TEX_EFFECT_PUSHING_B,					//PushB
		SEPARATE_TEX_EFFECT_CHAINELECTRIC,				//�A������
		SEPARATE_TEX_EFFECT_CHAINTHUNDER,				//�A�������J�n
		SEPARATE_TEX_EFFECT_HIT_SPARK,					//�q�b�g�G�t�F�N�g�@�Ή�
		SEPARATE_TEX_EFFECT_HIT_STAN,					//�q�b�g�G�t�F�N�g�@�X�^����
		SEPARATE_TEX_EFFECT_HIT_SLASH,					//�q�b�g�G�t�F�N�g�@�a��
		SEPARATE_TEX_EFFECT_SMOKE,						//��
		SEPARATE_TEX_EFFECT_SPARKEXPLOSION,				//�d���̔������ۂ���
		SEPARATE_TEX_EFFECT_STANING,					//�X�^�����
		SEPARATE_TEX_EFFECT_TITLESPARK,					//�^�C�g���̍ŏ��̓d��
		SEPARATE_TEX_EFFECT_ENEMY_RESPAWN,				//�G�o�����鎞�̃G�t�F�N�g
		SEPARATE_TEX_EFFECT_GAME_START,					//�Q�[���J�n�̃G�t�F�N�g

	};

	static void TexLoad(HWND hwnd);						//�e�N�X�`������
	static void TexUnload();							//�e�N�X�`���j��

	static LPDIRECT3DTEXTURE9 GetTexture(TEX_TYPE textype);							//�ʏ�e�N�X�`���̎擾
	static LPDIRECT3DTEXTURE9 GetSeparateTexture(SEPARATE_TEX_TYPE textype);		//�����e�N�X�`���擾
	static D3DXVECTOR2 GetSparateTex_UVSize(SEPARATE_TEX_TYPE textype);				//�����e�N�X�`���@UV�̃T�C�Y�擾
	static D3DXVECTOR2 GetSparateTex_UVCnt(SEPARATE_TEX_TYPE textype);				//�����e�N�X�`���@UV�̖����擾


private:
	static std::vector<LPDIRECT3DTEXTURE9> m_apTextureList;							//�ʏ�e�N�X�`���ւ̃|�C���^�̃��X�g
	static std::vector<LPDIRECT3DTEXTURE9> m_apSeparateTextureList;					//�����e�N�X�`���ւ̃|�C���^�̃��X�g

	static std::vector<D3DXVECTOR2> m_UVSizeList;									//UV�̃T�C�Y�̃��X�g
	static std::vector<D3DXVECTOR2> m_UVCntList;									//UV�̖����̃��X�g
	static std::vector<std::string> m_aTexFileName;									//�ʏ�e�N�X�`���̃t�@�C����
	static std::vector<std::string> m_aSeparateTexFileName;							//�����e�N�X�`���̃t�@�C����

};

#endif