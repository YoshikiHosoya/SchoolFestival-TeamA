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
		TEX_MAX									//MAX
	};

	//�A�j���[�V�����p�̃e�N�X�`��
	//��������Ă���e�N�X�`��
	enum SEPARATE_TEX_TYPE
	{
		SEPARATE_TEX_EFFECT_EXPLOSION,			//����
		SEPARATE_TEX_MAX						//MAX
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