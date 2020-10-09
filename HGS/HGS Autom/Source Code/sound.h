//------------------------------------------------------------------------------
//
// �T�E���h���� [sound.h]
// Author : Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _SOUND_H_
#define _SOUND_H_

#define _CRT_SECURE_NO_WARNINGS

//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "main.h"
#include "xaudio2.h"


class CSound
{
public:

	// �T�E���h�t�@�C��
	typedef enum
	{
		LABEL_BGM_TITLE = 0,						//�^�C�g��
		LABEL_BGM_GAME,								//�Q�[��
		LABEL_BGM_RANKING,							//���U���g

		//�G�t�F�N�g
		LABEL_SE_EXPLOSION_00,						//����
		LABEL_SE_EXPLOSION_01,						//����
		LABEL_SE_EXPLOSION_02,						//����
		LABEL_SE_EXPLOSION_03,						//����
		LABEL_SE_EXPLOSION_04,						//����

		LABEL_SE_COUNTDOWN,							//�J�E���g�_�E��
		LABEL_SE_GOOD,								//�O�b�h
		LABEL_SE_GREAT,								//�O���C�g
		LABEL_SE_PERFECT,							//�p�[�t�F�N�g

		LABEL_SE_SCORE_CHECK,						//�X�R�A�`�F�b�N
		LABEL_SE_SPEED_UP,							//�X�s�[�h�A�b�v
		LABEL_SE_ADDTIME,							//�^�C���ǉ�
		LABEL_SE_ARROW,								//���
		LABEL_SE_READY,								//���

		//�V�X�e����
		LABEL_SE_DECISION,						//����
		LABEL_SE_CANCEL,						//�L�����Z��
		LABEL_SE_SELECT,						//�I��
		LABEL_SE_PAUSE,							//�|�[�Y
		LABEL_SE_DEATH,							//��
		LABEL_SE_TIMEUP,						//�^�C���A�b�v


		LABEL_MAX,
	} LABEL;

	HRESULT Init(HWND hWnd);
	void Uninit(void);

	HRESULT Play(LABEL label);

	void Stop(LABEL label);
	void StopAll(void);

	void SetMute(bool bMute)	{ m_bMute = bMute; };
	bool GetMute()				{ return m_bMute; };

private:

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2 = NULL;										// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;					// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[LABEL_MAX] = {};				// �\�[�X�{�C�X
	BYTE *m_apDataAudio[LABEL_MAX] = {};								// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[LABEL_MAX] = {};									// �I�[�f�B�I�f�[�^�T�C�Y

	bool m_bMute;														//�~���[�g

	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDPARAM;

	// �e���f�ނ̃p�����[�^
	SOUNDPARAM m_aParam[LABEL_MAX] =
	{
		//BGM
		{ "data/BGM/title.wav", -1 },								//BGM
		{ "data/BGM/game.wav", -1 },								//BGM
		{ "data/BGM/ranking.wav", -1 },								//BGM

		//�G�t�F�N�g
		{ "data/SE/Effect/explosion_00.wav", 0 },					//SE ����
		{ "data/SE/Effect/explosion_01.wav", 0 },					//SE ����
		{ "data/SE/Effect/explosion_02.wav", 0 },					//SE ����
		{ "data/SE/Effect/explosion_03.wav", 0 },					//SE ����
		{ "data/SE/Effect/explosion_04.wav", 0 },					//SE ����

		{ "data/SE/Effect/countdown.wav", 0 },						//SE �J�E���g�_�E��
		{ "data/SE/Effect/good.wav", 0 },							//SE �O�b�h
		{ "data/SE/Effect/great.wav", 0 },							//SE �O���C�g
		{ "data/SE/Effect/perfect.wav", 0 },						//SE �p�[�t�F�N�g

		{ "data/SE/Effect/scorecheck.wav", 0 },						//SE �X�R�A�`�F�b�N
		{ "data/SE/Effect/speedup.wav", 0 },						//SE �X�s�[�h�A�b�v
		{ "data/SE/Effect/addtime.wav", 0 },						//SE �^�C���ǉ�
		{ "data/SE/Effect/arrow.wav", 0 },							//SE ���
		{ "data/SE/Effect/Ready.wav", 0 },							//SE ��

		//�V�X�e����
		{ "data/SE/System/Determining_sound.wav", 0 },				//SE ����
		{ "data/SE/System/cancel.wav", 0 },							//SE �L�����Z��
		{ "data/SE/System/select.wav", 0 },							//SE �I��
		{ "data/SE/System/pause.wav", 0 },							//SE �|�[�Y
		{ "data/SE/System/Death.wav", 0 },							//SE ��
		{ "data/SE/System/Death2.wav", 0 },							//SE ��
	};

};


#endif
