// ------------------------------------------
//
// �^�C�g���w�b�_�[���� [title.h]
// Author : Fujiwara Masato
//
// ------------------------------------------
#ifndef _TITLE_H_
#define _TITLE_H_

#define _CRT_SECURE_NO_WARNINGS

// ------------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ------------------------------------------
#include "main.h"

// ------------------------------------------
//
// �}�N����`
//
// ------------------------------------------
//#define ONEMIN (60)

// ------------------------------------------
//
// �O���錾
//
// ------------------------------------------
class CTitle_ui;
class CTitleEnemy;
class CLightEffect;
class CTelop;
// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CTitle
{
public:
	/* �񋓌^ */
	typedef enum
	{
		/* �^�C�g���v���C���ɂ͏o�����Ȃ�UI */
		TITLEMODE_TITLE = 0,				// �^�C�g���\�����[�h
		TITLEMODE_TUTORIAL,					// �`���[�g���A�����[�h
		TITLEMODE_FREE,						// ���R�ɍs���\
		TITLEMODE_MAX
	} TITLEMODE;

	/* �֐� */
	CTitle();
	~CTitle();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void CreateTitleObj(void);				//�^�C�g���Ŏg���I�u�W�F�N�g�̐���

	void SetMode(void);						//�^�C�g���̃��[�h�ݒ�
	void Mode(void);						//�^�C�g�����[�h���Ƃ̏���
	TITLEMODE GetMode(void);				//�^�C�g���̌��݂̃��[�h�擾
	void SetEnterflag(void);
	bool GetEnterflag(void);

protected:
private:
	TITLEMODE	m_Mode;						//�^�C�g���̃��[�h
	static CTitle_ui * m_pTitle_ui;			//�^�C�g���̕ϐ�
	static CTitleEnemy *m_pTitleEnemy;		//�^�C�g���p�̓G
	static CLightEffect *m_pLightEffect;	//���C�g�̕ϐ�
	static CTelop *m_pTelop;				//�e���b�v�ɕϐ�
	static bool m_bFlag;					//��x����������ʂ��悤�̃t���O
	static bool m_bStartFlag;				//��x����������ʂ��悤�̃t���O
	static bool m_bTelopFlag;				//��x����������ʂ��悤�̃t���O
	int			m_CreateCnt;				//���������܂ł̃J�E���g
	bool		m_Enterflag;				//�G���^�[����������true�ɂȂ�t���O
	int			m_PhaseCount;				//���̒i�K�֍s���܂ł̃N�[���^�C��
	bool		m_Phaseflag;				//���ڂ���������ʂ��t���O
};
#endif
