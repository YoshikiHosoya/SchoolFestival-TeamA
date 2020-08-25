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
		LABEL_BGM_TUTORIAL,							//���U���g
		LABEL_BGM_GAME,								//�Q�[��
		LABEL_BGM_RESULT,							//���U���g
		LABEL_BGM_RANKING,							//�����L���O
		LABEL_BGM_RAIN,								//�J��

		//�L�����N�^�[�A�N�V����
		LABEL_SE_HIT,								//�a��
		LABEL_SE_SLASH_PLAYER,						//�a���@�v���C���[�q�b�g
		LABEL_SE_SWING,								//�f�U��
		LABEL_SE_WALK,								//����
		LABEL_SE_JUMP,								//�W�����v
		LABEL_SE_LANDING,							//���n

		//�G�t�F�N�g
		LABEL_SE_EXPLOSION,							//����
		LABEL_SE_SHOT,								//�d��

		//�����Ƃ�
		LABEL_SE_DECISION,							//����
		LABEL_SE_CANCEL,							//�L�����Z��
		LABEL_SE_SELECT,							//�I��
		LABEL_SE_PAUSE,								//�|�[�Y
		LABEL_SE_GAMEOVER,							//�Q�[���I�[�o�[
		LABEL_SE_GAMECLEAR,							//�Q�[���N���A

		//����n�A�C�e���擾��
		LABEL_SE_ITEM_HMG,							//�w�r�[�}�V���K��

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

	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[LABEL_MAX] = {};						// �I�[�f�B�I�f�[�^�T�C�Y

	bool m_bMute;											//�~���[�g

	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDPARAM;

	// �e���f�ނ̃p�����[�^
	SOUNDPARAM m_aParam[LABEL_MAX] =
	{
		{ "data/BGM/title.wav", -1 },							//BGM
		{ "data/BGM/tutorial.wav", -1 },						//BGM
		{ "data/BGM/game.wav", -1 },							//BGM
		{ "data/BGM/result.wav", -1 },							//BGM
		{ "data/BGM/ranking.wav", -1 },							//BGM
		{ "data/BGM/rain.wav", -1 },							//BGM

		//�L�����N�^�[�A�N�V����
		{ "data/SE/CharacterAction/hit.wav", 0 },				//SE �a��
		{ "data/SE/CharacterAction/player_hit.wav", 0 },		//SE �a���@�v���C���[�q�b�g
		{ "data/SE/CharacterAction/swing.wav", 0 },				//SE �f�U��
		{ "data/SE/CharacterAction/walking.wav", 0 },			//SE ����
		{ "data/SE/CharacterAction/jump.wav", 0 },				//SE �W�����v
		{ "data/SE/CharacterAction/landing.wav", 0 },			//SE ���n

		//�G�t�F�N�g
		{ "data/SE/Effect/explosion.wav", 0 },					//SE ����
		{ "data/SE/Effect/shot.wav", 0 },						//SE �d��

		//����
		{ "data/SE/System/decision.wav", 0 },					//SE ����
		{ "data/SE/System/cancel.wav", 0 },						//SE �L�����Z��
		{ "data/SE/System/select.wav", 0 },						//SE �I��
		{ "data/SE/System/pause.wav", 0 },						//SE �|�[�Y
		{ "data/SE/System/gameover.wav", 0 },					//SE �Q�[���I�[�o�[
		{ "data/SE/System/gameclear.wav", 0 },					//SE �Q�[���N���A

		//����n�A�C�e���擾��
		{ "data/SE/Weapon/HeavyMachineGun.wav", 0 },			//SE HMG

	};

};


#endif
