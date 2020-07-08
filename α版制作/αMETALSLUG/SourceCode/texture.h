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
		TEX_ITEM_BEAR,							//�F-�X�R�A�A�b�v

		TEX_MESH_GRASS,							//��
		TEX_MESH_BLOCK,							//�u���b�N
		TEX_MESH_WATER,							//��

		TEX_UI_LIFE,							//�̗͂�UI
		TEX_UI_REMAIN,							//�c�@��UI
		TEX_UI_ARMS,							//�e�̎c����UI
		TEX_UI_BOMB,							//�O���l�[�h�̎c����UI
		TEX_UI_INFINITY,						//�e��������UI
		TEX_UI_FRAME,							//�g��UI

		TEX_MAX									//MAX
	};

	//�A�j���[�V�����p�̃e�N�X�`��
	//��������Ă���e�N�X�`��
	enum SEPARATE_TEX_TYPE
	{
		SEPARATE_TEX_NONE = 0,

		SEPARATE_TEX_EFFECT_EXPLOSION01,			//����
		SEPARATE_TEX_EFFECT_SHOTFLASH,				//���C���̌�
		SEPARATE_TEX_EFFECT_SPARK,					//�d��
		SEPARATE_TEX_EFFECT_HITEFFECT,				//���e�G�t�F�N�g
		SEPARATE_TEX_EFFECT_SMOKE,					//��
		SEPARATE_TEX_EFFECT_SHOTGUN,				//�V���b�g�K��
		SEPARATE_TEX_EFFECT_IMPACT00,				//�C���p�N�g
		SEPARATE_TEX_EFFECT_IMPACT01,				//�C���p�N�g
		SEPARATE_TEX_NUM,							//�i���o�[

		SEPARATE_TEX_MAX							//MAX
	};

	typedef struct
	{
		LPDIRECT3DTEXTURE9 m_apSeparateTexture;		//�����e�N�X�`���ւ̃|�C���^
		std::string m_aSeparateTexFileName;			//�����e�N�X�`���̖��O
		SEPARATE_TEX_TYPE type;						//�e�N�X�`���̎��
		D3DXVECTOR2 m_UVCnt;						//UV�̖���
		D3DXVECTOR2 m_UVSize;						//UV�̑傫��

	}SEPARATE_TEX_INFO;

	static void TexLoad(HWND hwnd);						//�e�N�X�`������
	static void TexUnload();							//�e�N�X�`���j��

	static LPDIRECT3DTEXTURE9 GetTexture(TEX_TYPE textype);							//�ʏ�e�N�X�`���̎擾

	static LPDIRECT3DTEXTURE9 GetSeparateTexture(SEPARATE_TEX_TYPE textype);		//�����e�N�X�`���擾
	static D3DXVECTOR2 GetSparateTex_UVSize(SEPARATE_TEX_TYPE textype);				//�����e�N�X�`���@UV�̃T�C�Y�擾
	static D3DXVECTOR2 GetSparateTex_UVCnt(SEPARATE_TEX_TYPE textype);					//�����e�N�X�`���@UV�̖����擾


private:
	static std::vector<LPDIRECT3DTEXTURE9> m_apTextureList;							//�ʏ�e�N�X�`���ւ̃|�C���^�̃��X�g
	static std::vector<std::string> m_aTexFileName;									//�ʏ�e�N�X�`���̃t�@�C����

	static std::vector<SEPARATE_TEX_INFO> m_apSeparateTexInfoList;					//�����e�N�X�`���Ɋւ�����̃|�C���^

};

#endif