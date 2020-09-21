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
		TEX_BULLET_HANDGUN,						//�n���h�K���̒e

		TEX_ITEM_HEAVYMACHINEGUN,				//�w�r�[�}�V���K��
		TEX_ITEM_SHOTGUN,						//�V���b�g�K��
		TEX_ITEM_LASERGUN,						//���[�U�[�K��
		TEX_ITEM_ROCKETLAUNCHER,				//���P�b�g�����`���[
		TEX_ITEM_FLAMESHOT,						//�t���C���V���b�g

		TEX_ITEM_GOLDCOIN,						//�R�C��-�X�R�A�A�b�v
		TEX_ITEM_SILVERCOIN,					//�R�C��-�X�R�A�A�b�v
		TEX_ITEM_BRONZESCOIN,					//�R�C��-�X�R�A�A�b�v

		TEX_ITEM_DIAMOND,						//���-�X�R�A�A�b�v
		TEX_ITEM_BEAR,							//�F-�X�R�A�A�b�v
		TEX_ITEM_LETTER,						//�莆-�X�R�A�A�b�v

		TEX_ITEM_APPLE,							//�����S-�X�R�A�A�b�v
		TEX_ITEM_MELON,							//������-�X�R�A�A�b�v
		TEX_ITEM_BANANA,						//�o�i�i-�X�R�A�A�b�v
		TEX_ITEM_MEAT,							//��-�X�R�A�A�b�v
		TEX_ITEM_RICEBALL,						//���ɂ���-�X�R�A�A�b�v
		TEX_ITEM_CANDY,							//�L�����f�B-�X�R�A�A�b�v
		TEX_ITEM_DONUT,							//�h�[�i�c-�X�R�A�A�b�v
		TEX_ITEM_LOLIPOP,						//�����|�b�v-�X�R�A�A�b�v
		TEX_ITEM_BREAD,							//�p��-�X�R�A�A�b�v
		TEX_ITEM_CHOCOLATE,						//�`���R���[�g-�X�R�A�A�b�v
		TEX_ITEM_ICE,							//�A�C�X-�X�R�A�A�b�v

		TEX_ITEM_BOMBUP,						//���e�̐����Z
		TEX_ITEM_BULLETUP,						//�c�i�����Z

		TEX_MESH_GRASS,							//��
		TEX_MESH_BLOCK,							//�u���b�N
		TEX_MESH_WATER,							//��

		TEX_UI_REMAIN,							//�c�@��UI
		TEX_UI_ARMS,							//�e�̎c����UI
		TEX_UI_BOMB,							//�O���l�[�h�̎c����UI
		TEX_UI_INFINITY,						//�e��������UI
		TEX_UI_FRAME,							//�g��UI

		TEX_UI_TITLE,							// �^�C�g�����S
		TEX_UI_START,							// �X�^�[�g
		TEX_UI_BULLET_HOLE1,					// �e��1
		TEX_UI_BULLET_HOLE2,					// �e��2
		TEX_UI_BULLET_HOLE3,					// �e��3
		TEX_UI_PLAYER_1,						// �v���C���[�I��1
		TEX_UI_PLAYER_2,						// �v���C���[�I��2
		TEX_UI_ARROW,							// �I��p���

		TEX_UI_TUTORIAL_NAME,					// �`���[�g���A�����O���S
		TEX_UI_TUTORIAL_START,					// �J�n�錾
		TEX_UI_TUTORIAL_ORDER1,					// �`���[�g���A���w��1
		TEX_UI_TUTORIAL_ORDER2,					// �`���[�g���A���w��2
		TEX_UI_TUTORIAL_ORDER3,					// �`���[�g���A���w��3
		TEX_UI_TUTORIAL_ORDER4,					// �`���[�g���A���w��4
		TEX_UI_TUTORIAL_ORDER5,					// �`���[�g���A���w��5
		TEX_UI_TUTORIAL_ORDER6,					// �`���[�g���A���w��6
		TEX_UI_TUTORIAL_FINAL,					// �I���錾

		TEX_UI_RESULT_BG,						//�w�i
		TEX_UI_RESULT_NAME,						//���O���S
		TEX_UI_RESULT_1P,						//1P
		TEX_UI_RESULT_2P,						//2P
		TEX_UI_RESULT_GOOD,						//�]��0
		TEX_UI_RESULT_GREATE,					//�]��1
		TEX_UI_RESULT_NOPRISONER,				//�]��2
		TEX_UI_RESULT_MISSION1COMPLETE,			//�N���A���S0
		TEX_UI_RESULT_MISSION2COMPLETE,			//�N���A���S1

		TEX_UI_RANKING_NAME,					//�����L���O���O���S
		TEX_UI_RANKING_1st,						//�����L���O1��
		TEX_UI_RANKING_2nd,						//�����L���O2��
		TEX_UI_RANKING_3rd,						//�����L���O3��
		TEX_UI_RANKING_4th,						//�����L���O4��
		TEX_UI_RANKING_5th,						//�����L���O5��
		TEX_UI_RANKING_6th,						//�����L���O6��
		TEX_UI_RANKING_7th,						//�����L���O7��
		TEX_UI_RANKING_TOTAL,					//����
		TEX_UI_RANKING_THANKS,					//�V��ł���Ă��肪�Ƃ��I


		TEX_BG_SKY_SUNNY,						//��̔w�i	( ���� )
		TEX_BG_SKY_CLOUDY,						//��̔w�i	( �܂� )
		TEX_BG_SKY_DARKCLOUDS,					//��̔w�i	( �É_ )

		TEX_UI_GAME_GO,							//Go�T�C��
		TEX_UI_GAME_GAMEOVER,					//�Q�[���I�[�o�[

		TEX_UI_GAME_PLAYER_1P,					//2�l�v���C��1P����ɕ\��
		TEX_UI_GAME_PLAYER_2P,					//2�l�v���C��2P����ɕ\��

		TEX_UI_PAUSE_BG,						//�|�[�Y�̔w�i
		TEX_UI_PAUSE_EXIT,						//�ĊJ
		TEX_UI_PAUSE_RESET,						//�^�C�g���ɖ߂�
		TEX_UI_PAUSE_TEXT,						//�|�[�Y(����)
		TEX_UI_PAUSE_ARROW,						//���

		TEX_COLLISION_FRAME,					//�����蔻��

		TEX_MAX									//MAX
	};

	//�A�j���[�V�����p�̃e�N�X�`��
	//��������Ă���e�N�X�`��
	enum SEPARATE_TEX_TYPE
	{
		SEPARATE_TEX_NONE = 0,

		SEPARATE_TEX_EFFECT_EXPLOSION00,			//����
		SEPARATE_TEX_EFFECT_EXPLOSION01,			//����
		SEPARATE_TEX_EFFECT_EXPLOSION02,			//����
		SEPARATE_TEX_EFFECT_EXPLOSION03,			//����
		SEPARATE_TEX_EFFECT_IMPACT00,				//�C���p�N�g
		SEPARATE_TEX_EFFECT_IMPACT01,				//�C���p�N�g
		SEPARATE_TEX_EFFECT_IMPACT02,				//�C���p�N�g
		SEPARATE_TEX_EFFECT_IMPACT03,				//�C���p�N�g
		SEPARATE_TEX_EFFECT_IMPACT04,				//�C���p�N�g
		SEPARATE_TEX_EFFECT_IMPACT05,				//�C���p�N�g
		SEPARATE_TEX_EFFECT_FIRE00,					//�t�@�C�A
		SEPARATE_TEX_EFFECT_FIRE01,					//�t�@�C�A
		SEPARATE_TEX_EFFECT_FIRE02,					//�t�@�C�A
		SEPARATE_TEX_EFFECT_FIRE03,					//�t�@�C�A
		SEPARATE_TEX_EFFECT_FIRE04,					//�t�@�C�A
		SEPARATE_TEX_EFFECT_SHOTFLASH,				//���C���̌�
		SEPARATE_TEX_EFFECT_HITEFFECT,				//���e�G�t�F�N�g
		SEPARATE_TEX_EFFECT_SMOKE,					//��
		SEPARATE_TEX_EFFECT_SHOTGUN,				//�V���b�g�K��
		SEPARATE_TEX_EFFECT_FLASH,					//�t���b�V��
		SEPARATE_TEX_EFFECT_CHARGE00,				//�`���[�W
		SEPARATE_TEX_EFFECT_CHARGE01,				//�`���[�W

		SEPARATE_TEX_EFFECT_FIREWORKS1,				//�ԉ�1
		SEPARATE_TEX_EFFECT_FIREWORKS2,				//�ԉ�2
		SEPARATE_TEX_EFFECT_FIREWORKS3,				//�ԉ�3

		SEPARATE_TEX_NUM,							//�i���o�[
		SEPARATE_TEX_UI_LIFE,						//�̗͂�UI

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