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
	enum class FADESTATE
	{
		FADESTATE_NONE = -1,		// �����Ȃ����
		FADESTATE_IN,			// �t�F�[�h�C������
		FADESTATE_OUT,			// �t�F�[�h�A�E�g����
	};

	enum class FADETYPE
	{
		FADETYPE_NONE = -1,			//NONE
		FADETYPE_MODE,				//���[�h�J��
		FADETYPE_MAPMOVE,			//�}�b�v�J��
		FADETYPE_STAGE_CHANGE,		//�X�e�[�W�J��
	};

	void InitFade(void);
	void UninitFade(void);
	void UpdateFade(void);
	void DrawFade(void);
	void MakeVertexFade(void);
	FADESTATE GetFadeState(void);
	static CFADE *CreateFade(void);

	template <class ID> void SetFade(FADETYPE type, ID NextID);		//�t�F�[�h�̐ݒ�
private:
	LPDIRECT3DTEXTURE9		m_pTextureFade = NULL;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffFade = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	FADESTATE				m_fadeState;				// �t�F�[�h���
	FADETYPE				m_fadeType;					// �t�F�[�h�̎�ޔ�
	int						m_NextID;					// ���̉�ʁi���[�h�j

	D3DXVECTOR3				m_pos;						// ���W
	D3DXCOLOR				m_colorFade;				// �t�F�[�h�F

	void ResetFadeParam();								// �t�F�[�h����̂ɕK�v�ȃp�����[�^������
	void FadeWhiteOut();
	void FadeWipe();
	void FadeOut();
	void UpdateVertex();

};



//=============================================================================
// �t�F�[�h�̏�Ԑݒ�
// �e���v���[�g�Ȃ̂ŃC�����C���֐�S
//=============================================================================
template<class ID>
inline void CFADE::SetFade(FADETYPE type, ID NextID)
{
	if (m_fadeState == FADESTATE::FADESTATE_NONE)
	{
		m_fadeState = FADESTATE::FADESTATE_NONE;
		m_NextID = NextID;
		m_fadeType = type;
		ResetFadeParam();
	}
}
#endif
