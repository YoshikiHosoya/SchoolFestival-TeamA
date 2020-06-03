#pragma once
#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"

#define MAX_MODEL (11)			//���f���̃p�[�c��
class CModel;
//�����_�����O�N���X
class CCharacter :public CScene
{
public:
	typedef enum
	{
		CHARACTER_STATE_NONE,
		CHARACTER_STATE_NORMAL,
		CHARACTER_STATE_DAMAGE,
		CHARACTER_STATE_INVINCIBLE,
		CHARACTER_STATE_MAX
	}CHARACTER_STATE;
	//�L�[�v�f
	typedef struct
	{
		D3DXVECTOR3 pos;			//�ʒu
		D3DXVECTOR3 rot;			//��]
	}KEY;
	//�L�[���
	typedef struct
	{
		int nFram;					//�t���[����
		KEY key[MAX_MODEL];			//�p�[�c��
	}KEY_INFO;
	//�v���C���[�̃��[�V����
	typedef struct
	{
		int nLoop;					//���[�v
		int nNumKey;				//�L�[���̐�
		KEY_INFO key_info[10];		//�L�[�����Z�b�g���邩
		int Collision_nParts;		//�p�[�c�ԍ�
		D3DXVECTOR3 CollisionOfset;	//�I�t�Z�b�g
		float CollisionRadius;		//�~�̔��a
		int CollisionStartFram;		//�J�n�t���[��
		int CollisionEndFram;		//�I���t���[��
		int Collision_Damage;		//�_���[�W��
	}MOTION_PLAYER;
	typedef enum
	{
		PLAYER_MOTION_NORMAL = 0,	//�j���[�g����
		PLAYER_MOTION_WALK,			//����
		PLAYER_MOTION_ATTACK01,		//�ʏ�U��1
		PLAYER_MOTION_ATTACK02,		//�ʏ�U��2
		PLAYER_MOTION_ATTACK03,		//�ʏ�U��3
		PLAYER_MOTION_SKILL01,		//�X�L��1
		PLAYER_MOTION_SKILL02,		//�X�L��1
		PLAYER_MOTION_SKILL03,		//�X�L��3
		PLAYER_MOTION_ROWLING,		//���
		PLAYER_MOTION_DAMAGE,		//�_���[�W
		PLAYER_MOTION_MAX			//�ő吔
	}PLAYER_MOTION_STATE;

	CCharacter(OBJ_TYPE type);
	~CCharacter();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Move(float move, float fdest);
	void AddDamage(int Damage);
	void LoadMotion(void);
	void Moation(void);
	void LoadOffset(void);
	//�Z�b�c
	void SetPosition(D3DXVECTOR3 pos);
	void SetPotisionOld(D3DXVECTOR3 posOld);
	void SetMove(D3DXVECTOR3 move);
	void SetRot(D3DXVECTOR3 rot);
	void SetRotDest(D3DXVECTOR3 rotDest);
	void SetLife(int Life);
	void SetState(CHARACTER_STATE state);
	void SetMtxWorld(D3DXMATRIX mtxWorld);
	//�Q�b�g
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetPositionOld(void);
	D3DXVECTOR3 &GetMove(void);		//���Q�Ɠn���̊֐�
	D3DXVECTOR3 GetRot(void);
	D3DXVECTOR3 GetRotDest(void);
	CHARACTER_STATE GetCharacterState(void);
	int GetLife(void);
	D3DXMATRIX GetMtxWorld(void);
	void RayCollision(void);
	static CCharacter *Create(void);
private:

	D3DXVECTOR3 rotBET[MAX_MODEL];					//��]�̍���
	MOTION_PLAYER m_PlayerMotion[PLAYER_MOTION_MAX];//�v���C���[�̃��[�V����
	PLAYER_MOTION_STATE m_MotionState;				//���[�V�����̕ϐ�
	int m_MotionType;								//���[�V�����̐�
	int m_MotionOld;								//�O�̃��[�V����
	int m_CntKeySet;								//�L�[�Z�b�g�̃J�E���g
	int m_Fram;										//�t���[��
	static char *m_LoadFileName;					//�ǂݍ��ރt�@�C����
	std::vector<CModel*> m_vModelList;				//�ϒ��z�� �ݒu�������f��

	D3DXVECTOR3 m_pos;								//�ʒu
	D3DXVECTOR3 m_posold;							//�O�̈ʒu
	D3DXVECTOR3 m_move;								//�ړ���
	D3DXVECTOR3 m_rot;								//��]
	D3DXVECTOR3 m_rotDest;							//��]���鍷��
	int m_Life;										//���C�t
	int m_nStateCnt;								//�X�e�[�^�X�̃J�E���g
	CHARACTER_STATE m_state;						//
	D3DXMATRIX  m_mtxWorld;							//�}�g���b�N�X
};
#endif