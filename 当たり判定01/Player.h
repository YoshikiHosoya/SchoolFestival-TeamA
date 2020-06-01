#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#define MAX_MODEL (11)			//���f���̃p�[�c��
#define MAX_RAY_LENGTH (35)		//Ray�̍ő�̒���
#define RAY_FIRST_POINT (40.0f)	//Ray�̎n�_
class CModel;
class CCreateMap;
class CMeshOrbit;
class CParticle;
class CUI;
//�����_�����O�N���X
class CPlayer :public CScene
{
public:
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
	typedef enum
	{
		DEBUG_NORMAL = 0,			//�ʏ�
		DEBUG_CREATE_MAP,			//�}�b�v�쐬
		DEBUG_CREATE_ENEMY,			//�G�l�~�[�쐬
		DEBUG_MAX					//�ő吔
	}DEBUG_STATE;
	typedef enum
	{
		PLAYER_STATE_NONE,
		PLAYER_STATE_NORMAL,
		PLAYER_STATE_DAMAGE,
		PLAYER_STATE_INVINCIBLE,
		PLAYER_STATE_MAX
	}PLAYER_STATE;

	CPlayer(OBJ_TYPE type);
	~CPlayer();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Drow(void);
	void Move(float move, float fdest);
	void LoadMotion(void);
	void Moation(void);
	void HitPlayer(int Damage);
	void SetLife(int Life);
	void SetPosition(D3DXVECTOR3 pos);
	void CollisionModel(void);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetPositionOld(void);
	D3DXVECTOR3 GetMove(void);
	D3DXVECTOR3 GetOffset(int nCnt);
	DEBUG_STATE GetDebugState(void);
	PLAYER_STATE GetPlayerState(void);
	int GetWeponType(void);
	int GetLife(void);
	static CPlayer *Create(void);
private:
		D3DXVECTOR3 m_pos;								//�ʒu
		D3DXVECTOR3 m_posold;							//�O�̈ʒu
		D3DXVECTOR3 m_move;								//�ړ���
		D3DXVECTOR3 m_rot;								//��]
		D3DXVECTOR3 posBET[MAX_MODEL];					//���W�̍���
		D3DXVECTOR3 rotBET[MAX_MODEL];					//��]�̍���
		D3DXVECTOR3 pos[MAX_MODEL];						//�ʒu�̊i�[�p
		D3DXVECTOR3 rot[MAX_MODEL];						//��]�̊i�[�p
		D3DXVECTOR3 Dest;								//��]���鍷��
		D3DXVECTOR3 m_size;								//
		D3DXVECTOR3 m_vecAxis;							//��]��
		D3DXVECTOR3 m_aOffset[10];
		CModel *m_Model[MAX_MODEL];						//���f��
		CModel *m_WeponModel[3];						//���탂�f��
		CCreateMap *m_CreateMap;
		MOTION_PLAYER m_PlayerMotion[PLAYER_MOTION_MAX];//�v���C���[�̃��[�V����
		PLAYER_MOTION_STATE m_MotionState;				//���[�V�����̕ϐ�
		DEBUG_STATE m_DebugState;						//�f�o�b�O�̃X�e�[�^�X
		int m_Type;										//�^�C�v
		int m_WeponType;								//����̎��
		int m_MotionType;								//���[�V�����̐�
		int m_MotionOld;								//�O�̃��[�V����
		int m_CntKeySet;								//�L�[�Z�b�g�̃J�E���g
		int m_Fram;										//�t���[��
		int m_CntState;									//�X�e�[�^�X�̃J�E���g
		int m_nCnt;										//�S�̂̃J�E���g
		int m_Life;										//���C�t
		int m_nStateCnt;								//�X�e�[�^�X�̃J�E���g
		float m_Angle;
		bool m_Attack;									//�U����
		PLAYER_STATE m_state;							//
		LPDIRECT3DTEXTURE9 m_pTexture;					//�e�N�X�`��
		D3DXMATRIX  m_mtxWorld;							//�}�g���b�N�X
		D3DXMATRIX m_mtxRot;							//��]�}�g���b�N�X
		float m_fValueRot;								//��]�p�i��]��
		XINPUT_STATE state;
		XINPUT_VIBRATION vibration;
		WORD Oldstate;
};
#endif