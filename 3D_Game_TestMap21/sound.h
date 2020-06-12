// =====================================================================================================================================================================
//
// �T�E���h���� [sound.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

// =====================================================================================================================================================================
// �O���錾	( �|�C���^�����Ȃ�g���� )
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// �T�E���h�N���X
// =====================================================================================================================================================================
class CSound
{
public:

// =====================================================================================================================================================================
// �p�����[�^�\���̒�`
// =====================================================================================================================================================================
typedef struct
{
	char *pFilename;	// �t�@�C����
	int nCntLoop;		// ���[�v�J�E���g
} SOUNDPARAM;

	// �T�E���h�t�@�C��
	typedef enum
	{
		SOUND_LABEL_BGM_TITLE = 0,	// �^�C�g��
		SOUND_LABEL_BGM_GAME,		// ���C��
		SOUND_LABEL_BGM_OVER,		// �Q�[���I�[�o�[
		SOUND_LABEL_BGM_RANK,		// �����L���O
		SOUND_LABEL_SE_JUMP,		// �W�����v
		SOUND_LABEL_SE_LAND,		// ���n
		SOUND_LABEL_SE_ITEM,		// �A�C�e��
		SOUND_LABEL_SE_HEAL,		// ��
		SOUND_LABEL_SE_DEATH,		// ��
		SOUND_LABEL_SE_GAYSER,		// �Ԍ���
		SOUND_LABEL_SE_ENTER,		// ����
		SOUND_LABEL_SE_GAGE,		// �Q�[�W
		SOUND_LABEL_SE_CHANGE,		// �ؑւ�
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	CSound();												// �R���X�g���N�^
	~CSound();												// �f�X�g���N�^

	/* �����o�֐� */
	HRESULT				Init(HWND hWnd);					// ������
	void				Uninit();							// �I��

	/* �ÓI�����o�֐� */

	/* �����o�֐� */
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

private:
	/* �ÓI�����o�ϐ� */

	/* �����o�֐� */
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	// �����o�ϐ�
	IXAudio2				*m_pXAudio2							= NULL;				// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice	*m_pMasteringVoice					= NULL;				// �}�X�^�[�{�C�X
	IXAudio2SourceVoice		*m_apSourceVoice[SOUND_LABEL_MAX]	= {};				// �\�[�X�{�C�X
	BYTE					*m_apDataAudio[SOUND_LABEL_MAX]		= {};				// �I�[�f�B�I�f�[�^
	DWORD					m_aSizeAudio[SOUND_LABEL_MAX]		= {};				// �I�[�f�B�I�f�[�^�T�C�Y

	// �e���f�ނ̃p�����[�^
	SOUNDPARAM m_aParam[SOUND_LABEL_MAX] =
	{
		{ "data/SOUND/BGM/title.wav", -1 },				// �^�C�g��
		{ "data/SOUND/BGM/game.wav", -1 },				// ���C��
		{ "data/SOUND/BGM/clear.wav", -1 },				// �Q�[���I�[�o�[
		{ "data/SOUND/BGM/rank.wav", -1 },				// �����L���O
		{ "data/SOUND/SE/jump.wav", 0 },				// �W�����v
		{ "data/SOUND/SE/land.wav", 0 },				// ���n
		{ "data/SOUND/SE/item.wav", 0 },				// �A�C�e��
		{ "data/SOUND/SE/heal.wav", 0 },				// ��
		{ "data/SOUND/SE/death.wav", 0 },				// ��
		{ "data/SOUND/SE/gayser.wav", 0 },				// �Ԍ���
		{ "data/SOUND/SE/enter.wav", 0 },				// ����
		{ "data/SOUND/SE/gage.wav", 0 },				// �Q�[�W
		{ "data/SOUND/SE/change.wav", 0 },				// �ؑւ�
	};

};
#endif