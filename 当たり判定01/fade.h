#pragma once
//=============================================================================
//
// �t�F�[�h���� [fade.h]
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_
#define _CRT_SECURE_NO_WARNINGS
//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "manager.h"

class CManager;
//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
class CFADE
{
public:
	typedef enum
	{
		FADE_NONE = 0,		// �����Ȃ����
		FADE_IN,			// �t�F�[�h�C������
		FADE_OUT,			// �t�F�[�h�A�E�g����
		FADE_MAX
	} FADE;

	void InitFade(void);
	void UninitFade(void);
	void UpdateFade(void);
	void DrawFade(void);
	static void SetFade(CManager::GAME_MODE modeNext);
	static FADE GetFade(void);
	void MakeVertexFade(void);
private:
	LPDIRECT3DTEXTURE9		m_pTextureFade = NULL;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffFade = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	static FADE					m_fade;						// �t�F�[�h���
	static CManager::GAME_MODE		m_modeNext;					// ���̉�ʁi���[�h�j
	static D3DXCOLOR				m_colorFade;				// �t�F�[�h�F
};

#endif
