// ----------------------------------------
//
// ��ʑJ�ڏ����̐���[fade.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _FADE_H_
#define _FADE_H_	 // �t�@�C������������߂�

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "manager.h"

// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
#define MAX_FADE (10)

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CFade
{
public:
	typedef enum
	{
		FADE_NONE = 0,		// �����Ȃ����
		FADE_IN,			// �t�F�[�h�C������
		FADE_OUT,			// �t�F�[�h�A�E�g����
		FADE_MAX
	} FADE;

	/* �֐� */
	CFade();
	~CFade();
	void Init(CManager::MODE Mode);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetFade(CManager::MODE Mode);	// ��ʑJ�ڐݒ�
	FADE GetFade(void);					// ��ʑJ�ڏ��擾

	static HRESULT Load(void);
	static void UnLoad(void);
protected:

private:
	static LPDIRECT3DTEXTURE9 m_pTex;	// �e�N�X�`���[
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	FADE					m_fade;		// �t�F�[�h���
	CManager::MODE			m_modeNext;	// ���̉�ʁi���[�h�j
	D3DXCOLOR				m_col;		// �t�F�[�h�F
};

#endif