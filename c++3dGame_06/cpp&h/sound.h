// ----------------------------------------
//
// �T�E���h�����̐���[sound.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _SOUND_H_
#define _SOUND_H_	 // �t�@�C������������߂�

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "main.h"

// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
#define MAX_SOUND (10)

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CSound
{
public:
	/* �񋓌^ */
	// ���x��
	typedef enum
	{
		LABEL_BGM_TITLE,		// �^�C�g��
		LABEL_BGM_GAME,			// �Q�[��
		LABEL_BGM_RUN,			// ����
		LABEL_BGM_BREATH,		// ���؂�
		LABEL_BGM_RESULT,		// ���U���g
		LABEL_SE_7,				// �R�C��
		LABEL_MAX,
	} LABEL;
	/* �֐� */
	CSound();
	~CSound();
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(LABEL label);
	void StopSound(LABEL label);
	void StopSound(void);
protected:

private:
	/* �֐� */
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	/* �ϐ� */
	static char m_pFilename[LABEL_MAX][64];					// �t�@�C����
	static int m_nCntLoop[LABEL_MAX];						// ���[�v�J�E���g
	static IXAudio2 *m_pXAudio2;							// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	static IXAudio2MasteringVoice *m_pMasteringVoice;		// �}�X�^�[�{�C�X
	static IXAudio2SourceVoice *m_apSourceVoice[LABEL_MAX];	// �\�[�X�{�C�X
	static BYTE *m_apDataAudio[LABEL_MAX];					// �I�[�f�B�I�f�[�^
	static DWORD m_aSizeAudio[LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
};

#endif