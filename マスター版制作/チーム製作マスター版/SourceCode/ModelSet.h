#pragma once
// =====================================================================================================================================================================
//
// ���f���̐ݒ菈�� [ModelSet.h]
// Author :Hanzawa
//
// =====================================================================================================================================================================
#ifndef _MODELSET_H_
#define _MODELSET_H_
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"

#define MAX_MODEL (20)			//���f���̃p�[�c��
class CModel;
//�����_�����O�N���X
class CModelSet
{
public:
	typedef enum
	{
		CHARACTER_STATE_NONE,
		CHARACTER_STATE_NORMAL,
		CHARACTER_STATE_ITEMGET_FLASH,
		CHARACTER_STATE_DAMAGE_FLASHING,
		CHARACTER_STATE_DAMAGE_RED,
		CHARACTER_STATE_DEATH,
		CHARACTER_STATE_INVINCIBLE,

	}CHARACTER_STATE;

	typedef enum
	{
		CHARACTER_TYPE_PLAYER,			// �v���C���[
		CHARACTER_TYPE_ENEMY,			// �G�l�~�[
		CHARACTER_TYPE_PRISONER,		// �ߗ�
		CHARACTER_TYPE_BOSS,			// �{�X
		CHARACTER_TYPE_BOSS_ONE,		// �{�X
		CHARACTER_TYPE_TANK,			// ���
		CHARACTER_TYPE_PLANE,			// �퓬�@
		CHARACTER_TYPE_HELICOPTER,		// �w���R�v�^�[

		CHARACTER_TYPE_MAX
	}CHARACTER_TYPE;


	//�L�[�v�f
	typedef struct KEY
	{
		D3DXVECTOR3 pos;			//�ʒu
		D3DXVECTOR3 rot;			//��]

									//�R���X�g���N�^�@���������Ă���
		KEY()
		{
			pos = ZeroVector3;
			rot = ZeroVector3;
		}
	}KEY;

	//�L�[���
	typedef struct KEY_INFO
	{
		int nFram;					//�t���[����
		std::vector<KEY*> key;
		float fHeight;					//����
										//�R���X�g���N�^
		KEY_INFO()
		{
			nFram = 60;
			fHeight = 0.0f;
			key = {};
		}
	}KEY_INFO;
	//���f���̃��[�V����
	typedef struct
	{
		int nLoop;					//���[�v
		int nNumKey;				//�L�[���̐�
		std::vector<KEY_INFO*> key_info;
	}MOTION;
	typedef enum
	{
		// �v���C���[�̃��[�V����
		CHARACTER_MOTION_STATE_NONE = -1,	//�������Ȃ����[�V�����X�e�[�g
		PLAYER_MOTION_NORMAL = 0,			//�j���[�g����
		PLAYER_MOTION_WALK,					//����
		PLAYER_MOTION_ATTACK01,				//�ʏ�U��1
		PLAYER_MOTION_GRENADE,				//�O���l�[�h
		PLAYER_MOTION_JUMP,					//�W�����v
		PLAYER_MOTION_JUMPSTOP,				//�W�����v���Ă�����
		PLAYER_MOTION_SHOOT,				//����
		PLAYER_MOTION_SQUAT,				//���Ⴊ��
		PLAYER_MOTION_SQUATSTOP,			//���Ⴊ��ł���
		PLAYER_MOTION_DEAD,					//����

		// �G�̃��[�V����
		ENEMY_MOTION_NORMAL,				//�j���[�g����
		ENEMY_MOTION_WALK,					//����
		ENEMY_MOTION_SQUAT,					//�ʏ�U��1
		ENEMY_MOTION_DEAD_1,				//����
		ENEMY_MOTION_DEAD_2,				//����2
		ENEMY_MOTION_GRENADE,				//�O���l�[�h
		ENEMY_MOTION_JUMPATTACK,			//�ߐڍU��
		ENEMY_MOTION_KNIFEATTACK,			//�ߐڍU��2

		// �\���E�f�E���J�̃��[�V����
		BOSS_MOTION_NORMAL,					//�j���[�g����

		// �ߗ��̃��[�V����
		PRISONER_MOTION_STAY,				//�j���[�g����
		PRISONER_MOTION_RELEASE,			//�����Ă�
		PRISONER_MOTION_RUN,				//����
		PRISONER_MOTION_SALUTE,				//�h��
		PRISONER_MOTION_FALL,				//����
		PRISONER_MOTION_SKIP,				//�X�L�b�v�����Ȃ��瑖��
		CHARACTER_MOTION_MAX				//�ő吔
	}CHARACTER_MOTION_STATE;

	CModelSet();
	~CModelSet();
	HRESULT Init(void);
	void Uninit(void);
	bool Motion();							//���[�V��������
	static void LoadMotion(void);
	void LoadOffset(CHARACTER_TYPE nType);
	void ForcedUpdate();						//�����I�Ƀ��[�V�����`�F���W
	static void CharacterUnLoad(void);
	static CModelSet *CreateModelSet(void);
	//�Z�b�c
	void SetStateCount(int nCntState);
	void SetMtxWorld(D3DXMATRIX mtxWorld);
	void SetCharacterType(CHARACTER_TYPE CharaType);

	//���[�V�����֘A
	void SetMotion(CHARACTER_MOTION_STATE type);
	void SetMotionOldType(CHARACTER_MOTION_STATE type);
	void SetKeySet(int keyset);
	void SetFram(int fram);
	void SetUseMotion(bool use);
	//�Q�b�g
	CHARACTER_STATE GetCharacterState(void);
	CHARACTER_TYPE GetCharacterType();								//�L�����N�^�[�̎�ގ擾
	D3DXVECTOR3 &GetRot(void);
	std::vector<CModel*> &GetCharacterModelList();					//�L�����N�^�[�̃��f���擾
	//���[�V�����֘A
	bool &GetMotion();
	int &GetKeySet(void);											//�L�[�Z�b�g�̎擾
	int &GetFram(void);												//�t���[���̎擾
	int GetCharacterStateCnt() { return m_nStateCnt; };				// �L�����N�^�[�̃X�e�[�g�̃J�E���g
	float GetHeightBet(void);
	char* GetOffsetFileName(CHARACTER_TYPE type);
	char* GetMotionFileName(CHARACTER_MOTION_STATE motionstate);
	MOTION *GetCharacterMotion(CHARACTER_MOTION_STATE type);		//�L�����N�^�[���[�V�������̎擾
	CHARACTER_MOTION_STATE &GetMotionType(void);					//���[�V�����^�C�v�̎擾
	CHARACTER_MOTION_STATE GetMotionOldType(void);					//�O�̃��[�V�����^�C�v�擾

	void ChangeColor(bool ColorChangeFlag, D3DXCOLOR AddColor);									// �F�ύX
	void SetAllModelDisp(bool bDisp);								//�_�ł̐؂�ւ�

private:
	static char *m_LoadOffsetFileName[CHARACTER_TYPE_MAX];			//�ǂݍ��ރt�@�C����
	static char *m_LoadMotionFileName[CHARACTER_MOTION_MAX];		//�ǂݍ��ރt�@�C����
	std::vector<CModel*> m_vModelList;								//�ϒ��z�� �ݒu�������f��
	D3DXVECTOR3 m_rotBET[MAX_MODEL];
	float m_HeightBet;
	D3DXVECTOR3 m_rot;												//��]
	D3DXVECTOR3 m_rotDest;											//��]���鍷��
	D3DXVECTOR3 m_ShotRotDest;										//�������̌���n�@�w�r�[�}�V���K���p
	D3DXVECTOR3 m_AddHeadRot;
	D3DXVECTOR3 m_AddArmRot;
	D3DXMATRIX  m_mtxWorld;											//�}�g���b�N�X
	CHARACTER_STATE m_state;										//
	CHARACTER_TYPE m_CharaType;										//�L�����N�^�[�̃^�C�v
	int m_nStateCnt;												//�X�e�[�^�X�̃J�E���g
	bool m_bMotion;													//���[�V�������邩�ǂ���
	bool m_bFall;													//���[�V�������邩�ǂ���
	bool m_bDraw;													//�`�悷�邩�ǂ���
	DIRECTION	m_CharacterDirection;								//�L�����N�^�[�̌���
	DIRECTION	m_CharacterDirectionOld;							//1F�O�̃L�����N�^�[�̌���

																	//���[�V�����֘A�̏��
	static std::vector<MOTION*>m_CharacterMotion;					//�L�����N�^�[�̃��[�V�������
	CHARACTER_MOTION_STATE m_MotionType;							//���݂̃��[�V����
	CHARACTER_MOTION_STATE m_MotionOld;								//�O�̃��[�V����
	int m_CntKeySet;												//�L�[�Z�b�g�̃J�E���g
	int m_Fram;														//�t���[��

	void CalcRotation();											//��]�̌v�Z
};
#endif