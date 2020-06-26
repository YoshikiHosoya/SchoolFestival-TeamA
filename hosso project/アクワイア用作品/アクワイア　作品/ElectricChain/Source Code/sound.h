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
		LABEL_SE_SLASH,								//�a��
		LABEL_SE_SLASH_STAN,						//�a�� �X�^����
		LABEL_SE_SLASH_PLAYER,						//�a���@�v���C���[�q�b�g
		LABEL_SE_SWING,								//�f�U��
		LABEL_SE_WALK,								//����
		LABEL_SE_JUMP,								//�W�����v
		LABEL_SE_LANDING,							//���n
		LABEL_SE_APPEAR,							//�o��


		//�G�t�F�N�g
		LABEL_SE_EXPLOSION,							//����
		LABEL_SE_SPARK,								//�d��
		LABEL_SE_START_CHAIN,						//�A���J�n�̗�
		LABEL_SE_CHAINING_SPARK,					//�A�����̓d��
		LABEL_SE_THUNDER,							//����

		//�^�C�g���p
		LABEL_SE_TITLE_SPARKING,					//�^�C�g���@�r���r���[
		LABEL_SE_TITLE_EXPLOSION,					//�^�C�g���@�o�[�����Ċ�����
		LABEL_SE_RANKING_THUNDER,					//�����L���O�@�����o�Ă���Ƃ���

		//�����Ƃ�
		LABEL_SE_DECISION,							//����
		LABEL_SE_CANCEL,							//�L�����Z��
		LABEL_SE_SELECT,							//�I��
		LABEL_SE_PAUSE,								//�|�[�Y
		LABEL_SE_GAMEOVER,							//�Q�[���I�[�o�[
		LABEL_SE_GAMECLEAR,							//�Q�[���N���A

		LABEL_MAX,
	} LABEL;

	HRESULT Init(HWND hWnd);
	void Uninit(void);

	HRESULT Play(LABEL label);
	void Stop(LABEL label);
	void StopAll(void);

private:

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[LABEL_MAX] = {};						// �I�[�f�B�I�f�[�^�T�C�Y


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
		{ "data/SE/CharacterAction/slash.wav", 0 },				//SE �a��
		{ "data/SE/CharacterAction/slash_stan.wav", 0 },		//SE �a��
		{ "data/SE/CharacterAction/player_hit.wav", 0 },		//SE �a���@�v���C���[�q�b�g
		{ "data/SE/CharacterAction/swing.wav", 0 },				//SE �f�U��
		{ "data/SE/CharacterAction/walking.wav", 0 },			//SE ����
		{ "data/SE/CharacterAction/jump.wav", 0 },				//SE �W�����v
		{ "data/SE/CharacterAction/landing.wav", 0 },			//SE ���n
		{ "data/SE/CharacterAction/appear.wav", 0 },			//SE �o��

		//�G�t�F�N�g
		{ "data/SE/Effect/explosion.wav", 0 },					//SE ����
		{ "data/SE/Effect/spark.wav", 0 },						//SE �d��
		{ "data/SE/Effect/ChainStartThunder.wav", 0 },			//SE �d��
		{ "data/SE/Effect/ChainingSpark.wav", 0 },				//SE �d��
		{ "data/SE/Effect/Thunder.wav", 0 },					//SE ����

		//�^�C�g���p
		{ "data/SE/Title/Sparking.wav", 0 },					//SE �r���r��
		{ "data/SE/Title/Title_Explosion.wav", 0 },				//SE �o�[��
		{ "data/SE/Ranking/Ranking_Thunder.wav", 0 },			//SE �����o�Ă���Ƃ��̗�

		//����
		{ "data/SE/System/decision.wav", 0 },					//SE ����
		{ "data/SE/System/cancel.wav", 0 },						//SE �L�����Z��
		{ "data/SE/System/select.wav", 0 },						//SE �I��
		{ "data/SE/System/pause.wav", 0 },						//SE �|�[�Y
		{ "data/SE/System/gameover.wav", 0 },					//SE �Q�[���I�[�o�[
		{ "data/SE/System/gameclear.wav", 0 },					//SE �Q�[���N���A

	};

};


#endif
