#pragma once
#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"

#define MAX_MODEL (20)			//���f���̃p�[�c��
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
	typedef enum
	{
		CHARACTER_TYPE_PLAYER,
		CHARACTER_TYPE_ENEMY,
		CHARACTER_TYPE_NPC,
		CHARACTER_TYPE_MAX
	}CHARACTER_TYPE;

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
		std::vector<KEY*> key;
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
		CHARACTER_MOTION_STATE_NONE = -1,	//�������Ȃ����[�V�����X�e�[�g
		PLAYER_MOTION_NORMAL = 0,			//�j���[�g����
		PLAYER_MOTION_WALK,					//����
		PLAYER_MOTION_ATTACK01,				//�ʏ�U��1

		ENEMY_MOTION_NORMAL,				//�j���[�g����
		ENEMY_MOTION_WALK,					//����
		ENEMY_MOTION_ATTACK01,				//�ʏ�U��1

		CHARACTER_MOTION_MAX				//�ő吔
	}CHARACTER_MOTION_STATE;

	CCharacter() {};
	CCharacter(OBJ_TYPE type);
	~CCharacter();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Move(float move, float fdest);
	void AddDamage(int Damage);
	void Moation(void);
	static void LoadMotion(void);
	void LoadOffset(CHARACTER_TYPE nType);
	virtual void DefaultMotion(void) = 0;
	//�Z�b�c
	void SetPosition(D3DXVECTOR3 pos);
	void SetPotisionOld(D3DXVECTOR3 posOld);
	void SetMove(D3DXVECTOR3 move);
	void SetRot(D3DXVECTOR3 rot);
	void SetRotDest(D3DXVECTOR3 rotDest);
	void SetLife(int Life);
	void SetState(CHARACTER_STATE state);
	void SetMtxWorld(D3DXMATRIX mtxWorld);
	void SetMotion(CHARACTER_MOTION_STATE type);
	void SetMotionOldType(CHARACTER_MOTION_STATE type);
	void SetKeySet(int keyset);
	void SetFram(int fram);

	//�Q�b�g
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetPositionOld(void);
	D3DXVECTOR3 &GetMove(void);		//���Q�Ɠn���̊֐�
	D3DXVECTOR3 GetRot(void);
	D3DXVECTOR3 GetRotDest(void);
	CHARACTER_STATE GetCharacterState(void);
	int GetLife(void);
	D3DXMATRIX GetMtxWorld(void);
	MOTION *GetCharacterMotion(CHARACTER_MOTION_STATE type);//�L�����N�^�[���[�V�������̎擾
	CHARACTER_MOTION_STATE GetMotionType(void);				//���[�V�����^�C�v�̎擾
	CHARACTER_MOTION_STATE GetMotionOldType(void);			//�O�̃��[�V�����^�C�v�擾
	int GetKeySet(void);									//�L�[�Z�b�g�̎擾
	int GetFram(void);										//�t���[���̎擾


	void RayCollision(void);
private:
	static std::vector<MOTION*>m_CharacterMotion;			//�L�����N�^�[�̃��[�V�������
	//CHARACTER_MOTION_STATE m_MotionState;					//���[�V�����̕ϐ�
	CHARACTER_MOTION_STATE m_MotionType;					//���[�V�����̐�
	CHARACTER_MOTION_STATE m_MotionOld;						//�O�̃��[�V����
	int m_CntKeySet;										//�L�[�Z�b�g�̃J�E���g
	int m_Fram;												//�t���[��
	static char *m_LoadOffsetFileName[CHARACTER_TYPE_MAX];	//�ǂݍ��ރt�@�C����
	static char *m_LoadMotionFileName[CHARACTER_MOTION_MAX];//�ǂݍ��ރt�@�C����
	std::vector<CModel*> m_vModelList;						//�ϒ��z�� �ݒu�������f��
	D3DXVECTOR3 m_rotBET[MAX_MODEL];
	D3DXVECTOR3 m_pos;										//�ʒu
	D3DXVECTOR3 m_posold;									//�O�̈ʒu
	D3DXVECTOR3 m_move;										//�ړ���
	D3DXVECTOR3 m_rot;										//��]
	D3DXVECTOR3 m_rotDest;									//��]���鍷��
	int m_Life;												//���C�t
	int m_nStateCnt;										//�X�e�[�^�X�̃J�E���g
	CHARACTER_STATE m_state;								//
	D3DXMATRIX  m_mtxWorld;									//�}�g���b�N�X
	CHARACTER_TYPE m_nType;									//�L�����N�^�[�̃^�C�v


};
#endif