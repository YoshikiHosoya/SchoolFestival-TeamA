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
		LABEL_BGM_TUTORIAL,							//�`���[�g���A��
		LABEL_BGM_STAGE_01,							//�X�e�[�W1
		LABEL_BGM_STAGE_02,							//�X�e�[�W2
		LABEL_BGM_STAGE_01_BOSS,					//�X�e�[�W1�{�X
		LABEL_BGM_STAGE_02_BOSS,					//�X�e�[�W2�{�X
		LABEL_BGM_RANKING,							//�����L���O

		//�L�����N�^�[�A�N�V����
		LABEL_SE_WALK,								//����
		LABEL_SE_JUMP,								//�W�����v
		LABEL_SE_LANDING,							//���n

		//�G�t�F�N�g
		LABEL_SE_EXPLOSION_00,						//����
		LABEL_SE_EXPLOSION_01,						//����
		LABEL_SE_EXPLOSION_02,						//����
		LABEL_SE_EXPLOSION_03,						//����
		LABEL_SE_EXPLOSION_04,						//����

		//����֘A
		LABEL_SE_SHOT_HANDGUN,						//�n���h�K��
		LABEL_SE_SHOT_MACHINEGUN,					//�}�V���K��
		LABEL_SE_SHOT_LAUNCHER,						//�����`���[
		LABEL_SE_SHOT_SHOTGUN,						//�V���b�g�K��
		LABEL_SE_SHOT_LASER,						//���[�U�[
		LABEL_SE_SHOT_FIRE,							//�t�@�C�A
		LABEL_SE_SHOT_BOSSLASER,					//���[�U�[
		LABEL_SE_SHOT_CHARGE,						//�`���[�W
		LABEL_SE_SHOT_FLASHING,						//������

		//�����Ƃ�
		LABEL_SE_DECISION,							//����
		LABEL_SE_CANCEL,							//�L�����Z��
		LABEL_SE_SELECT,							//�I��
		LABEL_SE_PAUSE,								//�|�[�Y
		LABEL_SE_GAMEOVER,							//�Q�[���I�[�o�[
		LABEL_SE_GAMECLEAR,							//�Q�[���N���A

		//�Q�[�������ʉ�
		LABEL_SE_GET_WEAPON,						//����擾
		LABEL_SE_GET_SCORE_ITEM,					//�X�R�A�A�C�e���擾
		LABEL_SE_ADD_SCORE00,						//���U���g���̃X�R�A���Z
		LABEL_SE_ADD_SCORE01,						//���U���g���̃X�R�A���Z
		LABEL_SE_ADD_SCORE_BONUS,					//���U���g���̃X�R�A���Z
		LABEL_SE_BULLET_HIT,						//�i�C�t�_���[�W
		LABEL_SE_KNIFE_HIT,							//�e�_���[�W

		//����n�A�C�e���擾���̃{�C�X
		LABEL_SE_VOICE_HEAVYMACHINEGUN,				//�w�r�[�}�V���K��
		LABEL_SE_VOICE_DEATH,						//���S���@�ܰ


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
		{ "data/BGM/title.wav", -1 },								//BGM
		{ "data/BGM/tutorial.wav", -1 },							//BGM
		{ "data/BGM/stage_01.wav", -1 },							//BGM
		{ "data/BGM/stage_02.wav", -1 },							//BGM
		{ "data/BGM/stage_01_boss.wav", -1 },						//BGM
		{ "data/BGM/stage_02_boss.wav", -1 },						//BGM
		{ "data/BGM/ranking.wav", -1 },								//BGM

		//�L�����N�^�[�A�N�V����
		{ "data/SE/CharacterAction/walking.wav", 0 },				//SE ����
		{ "data/SE/CharacterAction/jump.wav", 0 },					//SE �W�����v
		{ "data/SE/CharacterAction/landing.wav", 0 },				//SE ���n

		//�G�t�F�N�g
		{ "data/SE/Effect/explosion_00.wav", 0 },					//SE ����
		{ "data/SE/Effect/explosion_01.wav", 0 },					//SE ����
		{ "data/SE/Effect/explosion_02.wav", 0 },					//SE ����
		{ "data/SE/Effect/explosion_03.wav", 0 },					//SE ����
		{ "data/SE/Effect/explosion_04.wav", 0 },					//SE ����

		//����
		{ "data/SE/Weapon/handgun.wav", 0 },						//SE �n���h�K��
		{ "data/SE/Weapon/machinegun.wav", 0 },						//SE �}�V���K��
		{ "data/SE/Weapon/launcher.wav", 0 },						//SE �����`���[
		{ "data/SE/Weapon/shotgun.wav", 0 },						//SE �V���b�g�K��
		{ "data/SE/Weapon/laser.wav", 0 },							//SE ���[�U�[
		{ "data/SE/Weapon/Fire.wav", 0 },							//SE �t�@�C�A
		{ "data/SE/Weapon/boss_laser.wav", 0 },						//SE �{�X���[�U�[
		{ "data/SE/Weapon/boss_charge.wav", 0 },					//SE �`���[�W
		{ "data/SE/Weapon/boss_flashing.wav", 0 },					//SE ����������

		//����
		{ "data/SE/System/decision.wav", 0 },						//SE ����
		{ "data/SE/System/cancel.wav", 0 },							//SE �L�����Z��
		{ "data/SE/System/select.wav", 0 },							//SE �I��
		{ "data/SE/System/pause.wav", 0 },							//SE �|�[�Y
		{ "data/SE/System/gameover.wav", 0 },						//SE �Q�[���I�[�o�[
		{ "data/SE/System/stage_clear.wav", 0 },					//SE �X�e�[�W�N���A

		//�Q�[�����ʉ�
		{ "data/SE/Game/getweapon.wav", 0 },						//SE ����擾
		{ "data/SE/Game/getscore.wav", 0 },							//SE �X�R�A�A�C�e���擾
		{ "data/SE/Game/score_00.wav", 0 },							//SE ���U���g���̃X�R�A���Z
		{ "data/SE/Game/score_01.wav", 0 },							//SE ���U���g���̃X�R�A���Z
		{ "data/SE/Game/score_bonus.wav", 0 },						//SE ���U���g���̃X�R�A���Z
		{ "data/SE/Game/hit_bullet.wav", 0 },						//SE �e�_���[�W
		{ "data/SE/Game/hit_knife.wav", 0 },						//SE �i�C�t�_���[�W

		//����n�A�C�e���擾��
		{ "data/SE/Voice/HeavyMachineGun.wav", 0 },				//SE HMG
		{ "data/SE/Voice/Death.wav", 0 },						//SE ���S�{�C�X

	};

};


#endif
