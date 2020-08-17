#pragma once
#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"

#define MAX_MODEL (20)			//���f���̃p�[�c��
class CModel;
class CCollision;
//�����_�����O�N���X
class CCharacter :public CScene
{
public:
	typedef enum
	{
		CHARACTER_STATE_NONE,
		CHARACTER_STATE_NORMAL,
		CHARACTER_STATE_DAMAGE,
		CHARACTER_STATE_DAMAGE_RED,
		CHARACTER_STATE_DEATH,
		CHARACTER_STATE_INVINCIBLE,
		CHARACTER_STATE_MAX
	}CHARACTER_STATE;

	typedef enum
	{
		CHARACTER_TYPE_PLAYER,			// �v���C���[
		CHARACTER_TYPE_ENEMY,			// �G�l�~�[
		CHARACTER_TYPE_PRISONER,		// �ߗ�
		CHARACTER_TYPE_BOSS,			// �{�X
		CHARACTER_TYPE_BOSS_ONE,		// �{�X
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

	CCharacter() {};
	CCharacter(OBJ_TYPE type);
	~CCharacter();
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual bool DefaultMotion(void) = 0;
	virtual void DamageReaction();					//�_���[�W���̃��A�N�V����
	virtual void DeathReaction();					//���S�̃��A�N�V����
	virtual void State();							//�X�e�[�g�ɉ���������
	virtual void StateChangeReaction();				//�X�e�[�g�ύX����

	void Move(float move, float fdest);
	void AddDamage(int Damage);
	static void LoadMotion(void);
	void LoadOffset(CHARACTER_TYPE nType);
	void ForcedUpdate();						//�����I�Ƀ��[�V�����`�F���W
	void ResetCharacterDirection();				//��]�ʂ���Ɍ�����ݒ肵�Ȃ���
	static void CharacterUnLoad(void);

	//�Z�b�c
	void SetPosition(D3DXVECTOR3 pos);
	void SetPotisionOld(D3DXVECTOR3 posOld);
	void SetMove(D3DXVECTOR3 move);
	void SetRot(D3DXVECTOR3 rot);
	void SetRotDest(D3DXVECTOR3 rotDest);
	void SetLife(int Life);
	void SetJump(bool bJump);
	void SetState(CHARACTER_STATE state);
	void SetStateCount(int nCntState);
	void SetMtxWorld(D3DXMATRIX mtxWorld);
	void SetCharacterType(CHARACTER_TYPE CharaType);
	void SetGravity(bool gravity);
	void SetCharacterDirection(DIRECTION direction);
	void SetShotDirection(D3DXVECTOR3 direction);

	//���[�V�����֘A
	void SetMotion(CHARACTER_MOTION_STATE type);
	void SetMotionOldType(CHARACTER_MOTION_STATE type);
	void SetKeySet(int keyset);
	void SetFram(int fram);

	//�Q�b�g
	D3DXVECTOR3 &GetPosition(void);				//�Q�Ɠn��
	D3DXVECTOR3 &GetPositionOld(void);			//�Q�Ɠn��
	D3DXVECTOR3 &GetMove(void);					//�Q�Ɠn��
	D3DXVECTOR3 &GetRot(void);					//�Q�Ɠn��
	D3DXVECTOR3 &GetRotDest(void);				//�Q�Ɠn��
	D3DXVECTOR3 GetShotDirection(void);
	D3DXMATRIX *GetMtxWorld(void);
	CHARACTER_STATE GetCharacterState(void);
	int &GetLife(void);
	bool GetJump(void);
	bool GetGravity(void);
	float GetHeightBet(void);
	CHARACTER_TYPE GetCharacterType();								//�L�����N�^�[�̎�ގ擾
	CModel* GetCharacterModelPartsList(int nCnt);					//�L�����N�^�[�̃��f���p�[�c�擾
	DIRECTION &GetCharacterDirection(void);							//�����̎擾
	DIRECTION &GetCharacterDirectionOld(void);						//1F�O�̌����̎擾
	std::vector<CModel*> &GetCharacterModelList();					//�L�����N�^�[�̃��f���擾

	//���[�V�����֘A
	bool &GetMotion();
	int &GetKeySet(void);											//�L�[�Z�b�g�̎擾
	int &GetFram(void);												//�t���[���̎擾
	MOTION *GetCharacterMotion(CHARACTER_MOTION_STATE type);		//�L�����N�^�[���[�V�������̎擾
	CHARACTER_MOTION_STATE &GetMotionType(void);					//���[�V�����^�C�v�̎擾
	CHARACTER_MOTION_STATE GetMotionOldType(void);					//�O�̃��[�V�����^�C�v�擾

	char* GetOffsetFileName(CHARACTER_TYPE type);
	char* GetMotionFileName(CHARACTER_MOTION_STATE motionstate);

	D3DXVECTOR3 *GetPositionPtr()					{ return &m_pos; };							//���W�̃|�C���^�擾
	bool GetDieFlag()								{ return m_bDieFlag; };						// ���S�t���O�̎擾
	void SetDieFlag(bool DieFlag)					{ m_bDieFlag = DieFlag; };					// ���S�t���O�̐ݒ�
	bool GetDraw()									{ return m_bDraw; };						// �`�悷�邩�ǂ����擾

	bool GetFallFlag()								{ return m_bFall; };						// �����t���O�̎擾
	void SetFallFlag(bool bFall)					{ m_bFall = bFall; };						// �����t���O�̐ݒ�

	void ChangeColor(bool ColorChangeFlag, D3DXCOLOR AddColor);									// �F�ύX
	void CheckDrawRange();

	CCollision *GetCollision() { return m_pCollision; };			// �����蔻��̃|�C���^�擾
	virtual void		DebugInfo(void);						// �f�o�b�O�p�֐�

private:
	static char *m_LoadOffsetFileName[CHARACTER_TYPE_MAX];			//�ǂݍ��ރt�@�C����
	static char *m_LoadMotionFileName[CHARACTER_MOTION_MAX];		//�ǂݍ��ރt�@�C����
	std::vector<CModel*> m_vModelList;								//�ϒ��z�� �ݒu�������f��
	D3DXVECTOR3 m_rotBET[MAX_MODEL];
	float m_HeightBet;
	D3DXVECTOR3 m_pos;												//�ʒu
	D3DXVECTOR3 m_posfall;											//�������ʒu
	D3DXVECTOR3 m_posold;											//�O�̈ʒu
	D3DXVECTOR3 m_move;												//�ړ���
	D3DXVECTOR3 m_rot;												//��]
	D3DXVECTOR3 m_rotDest;											//��]���鍷��
	D3DXVECTOR3 m_ShotRotDest;										//�������̌���n�@�w�r�[�}�V���K���p
	D3DXVECTOR3 m_AddHeadRot;
	D3DXVECTOR3 m_AddArmRot;
	D3DXMATRIX  m_mtxWorld;											//�}�g���b�N�X
	CHARACTER_STATE m_state;										//
	CHARACTER_TYPE m_CharaType;										//�L�����N�^�[�̃^�C�v
	int m_Life;														//���C�t
	int m_nStateCnt;												//�X�e�[�^�X�̃J�E���g
	DIRECTION	m_CharacterDirection;								//�L�����N�^�[�̌���
	DIRECTION	m_CharacterDirectionOld;							//1F�O�̃L�����N�^�[�̌���

	//���[�V�����֘A�̏��
	static std::vector<MOTION*>m_CharacterMotion;					//�L�����N�^�[�̃��[�V�������
	CHARACTER_MOTION_STATE m_MotionType;							//���݂̃��[�V����
	CHARACTER_MOTION_STATE m_MotionOld;								//�O�̃��[�V����
	int m_CntKeySet;												//�L�[�Z�b�g�̃J�E���g
	int m_Fram;														//�t���[��
	bool m_bGravity;												//�d�͂��������Ă��邩
	bool m_bCanJump;												//�W�����v���Ă��邩�ǂ���
	bool m_bDieFlag;												// ���S�t���O
	bool m_bMotion;													//���[�V�������邩�ǂ���
	bool m_bFall;													//���[�V�������邩�ǂ���
	bool m_bDraw;													//�`�悷�邩�ǂ���
	CCollision				*m_pCollision;							//�����蔻��̃|�C���^

	void CalcShotDirection();										//���������߂�
	void CalcMove();												//�ړ��̌v�Z
	void CalcRotation();											//��]�̌v�Z
	void Motion(void);												//���[�V��������
	void SetAllModelDisp(bool bDisp);								//�_�ł̐؂�ւ�
	virtual void Collision();										//�����蔻�菈��

};
#endif