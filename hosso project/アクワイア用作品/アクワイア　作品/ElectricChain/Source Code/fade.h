//------------------------------------------------------------------------------
//
// �t�F�[�h���� [fade.h]
// Author : Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _FADE_H_
#define _FADE_H_

#define _CRT_SECURE_NO_WARNINGS

//------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include "manager.h"

class CFade
{
public:
	// �t�F�[�h�̏��
	typedef enum
	{
		FADE_NONE = 0,								// �����Ȃ����
		FADE_IN,									// �t�F�[�h�C������
		FADE_OUT,									// �t�F�[�h�A�E�g����
		FADE_MAX
	} FADESTATE;

	CFade();
	~CFade();
	void Init();									//�t�F�[�h�̏���������
	void Uninit();									//�t�F�[�h�̏I������
	void Update();									//�t�F�[�h�̍X�V����
	void Draw();									//�t�F�[�h�̕`�揈��
	static std::unique_ptr<CFade> Create();			//��������

	void SetModeFade(CManager::MODE nextmode);		//�t�F�[�h�Z�b�g
	FADESTATE GetFade(void);						//�t�F�[�h��Ԏ擾

private:

	LPDIRECT3DTEXTURE9		m_pTextureFade;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffFade;			// ���_�o�b�t�@�ւ̃|�C���^
	FADESTATE				m_fadestate;			// �t�F�[�h���
	CManager::MODE			m_modeNext;				// ���̉�ʁi���[�h�j
	D3DXCOLOR				m_colorFade;			// �t�F�[�h�F

	void UpdateMode();		//�X�V
};


#endif
