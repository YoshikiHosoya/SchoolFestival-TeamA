// =====================================================================================================================================================================
//
// �v���C���[�̏��� [player.h]
// Author :Hanzawa
//
// =====================================================================================================================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
// =====================================================================================================================================================================
// �C���N���[�h�t�@�C��
// =====================================================================================================================================================================
#include "main.h"
#include "Scene.h"
#include "Character.h"

// =====================================================================================================================================================================
// �v���C���[�̃f�[�^
// =====================================================================================================================================================================
typedef struct
{
	int				nLife;			// �̗�
	int				nRespawnCnt;	// ���X�|�[���܂ł̃J�E���g
	float			fRunSpeed;		// ����X�s�[�h
	float			fCrouchSpeed;	// ���Ⴊ�ݕ������̃X�s�[�h
	float			fJump;			// �ʏ펞�̃W�����v
	float			fRideJump;		// ��Ԓ��̃W�����v
	D3DXVECTOR3		pos;			// �������W
}PLAYER_DATA;

// =====================================================================================================================================================================
// �O���錾
// =====================================================================================================================================================================
class CModel;
class CMeshOrbit;
class CParticle;
class CUI;
class CGun;
class CGrenadeFire;
class CPrisoner;
class CKnife;
class CPlayerUI;
class CVehicle;

// =====================================================================================================================================================================
// �v���C���[�N���X
// =====================================================================================================================================================================
class CPlayer :public CCharacter, public CGameObject
{
public:
	// �f�o�b�O���̃X�e�[�g
	typedef enum
	{
		DEBUG_NORMAL = 0,			//�ʏ�
		DEBUG_CREATE_MAP,			//�}�b�v�쐬
		DEBUG_CREATE_ENEMY,			//�G�l�~�[�쐬
		DEBUG_MAX					//�ő吔
	}DEBUG_STATE;

	// �v���C���[�̐l��
	enum PLAYER_NUM
	{
		PLAYER_NUM_NONE,
		PLAYER_NUM_ONE = 1,						// 1�l�v���C�I��
		PLAYER_NUM_TWO = 2,						// 2�l�v���C�I��
		PLAYER_NUM_MAX = 2						// �ő吔
	};

	/* �����o�֐� */
	CPlayer() {};
	CPlayer(OBJ_TYPE type);
	virtual ~CPlayer();

	virtual HRESULT Init(void) override;				//������
	virtual void Uninit(void) override;					//�I��
	virtual void Update(void) override;					//�X�V
	virtual void Draw(void) override;					//�`��
	virtual void DebugInfo(void) override;				//�f�o�b�O���\�L

	void DrawWepon(void);								//����̕`��
	void MoveUpdate(void);								//�ړ��Ɋւ���X�V
	void CollisionUpdate(void);							//�����蔻��Ɋւ���X�V
	void AttackUpdate(void);							//�U���Ɋւ���X�V
	void PadMoveUpdate(void);							//�p�b�h�ɂ��ړ�
	void ReSpawn(void);									//���X�|�[������

	void DamageReaction() override;						//�_���[�W�󂯂����̃��A�N�V����
	void DeathReaction() override;						//���S���̃��A�N�V����
	void StateChangeReaction() override;				//��Ԃ��ς�������̃��A�N�V����
	bool DefaultMotion(void) override;					//�f�t�H���g�̃��[�V�����Z�b�g
	void State() override;								//�X�e�[�g�ɉ���������

	DEBUG_STATE GetDebugState(void);					//STATE�擾
	void MapChangePlayerRespawn();						//�}�b�v�J�ڎ��̃v���C���[�ݒ�
	void ResetPlayer();									//�v���C���[������ԂɃ��Z�b�g

	/* �ݒ� �擾 �֐� */
	void			SetRideFlag(bool bRide)			{ m_bRideVehicle = bRide; };	// ���C�h�t���O�̐ݒ�
	void			SetRespawnFlag(bool bRespawn)	{ m_bRespawn = bRespawn; };		// ���X�|�[���t���O�擾
	static			void SetTwoPPlayFlag(bool flag)	{ m_bTwoPPlay = flag; };	// 2�l�v���C�Ȃ̂��̐ݒ�
	CGun			*GetGun()						{ return  m_pGun; };			// �e�̃|�C���^�擾
	CGrenadeFire	*GetGrenadeFire()				{ return  m_pGrenadeFire; };	// �O���l�[�h���ˈʒu�̃|�C���^�擾
	CPlayerUI		*GetPlayerUI()					{ return  m_pPlayerUI; };		// �v���C���[UI�̃|�C���^�擾
	bool			GetRideFlag()					{ return m_bRideVehicle; };		// ���C�h�t���O�̎擾
	bool			GetRespawnFlag()				{ return m_bRespawn; };			// ���X�|�[���t���O�̐ݒ�
	static			bool GetTwoPPlayFlag()			{ return m_bTwoPPlay; };		// 2�l�v���C���Ă��邩�̃t���O�̎擾

	/* �ÓI�����o�֐� */

	static CPlayer *Create(TAG Tag);	// ����
	static	void	PlayerLoad();					// �v���C���[�̃��[�h
private:
	/* �ÓI�����o�֐� */

	/* �����o�֐� */
	void Ride();									// ��蕨�ɏ���Ă��鎞

	/* �ÓI�����o�ϐ� */
	static			PLAYER_DATA		m_PlayerData;		// �v���C���[�̃f�[�^
	static			char			*m_PlayerFileName;	// �����L���O�̃t�@�C����
	static			bool			m_bTwoPPlay;		// 2�l�v���C���Ă��邩�ǂ���

	/* �����o�ϐ� */
	int				m_nRespawnCnt;						// ���X�|�[���܂ł̃J�E���g�����܂ł̃J�E���g
	D3DXVECTOR3		m_ShotRot;							//������
	DEBUG_STATE		m_DebugState;						// �f�o�b�O�̃X�e�[�^�X
	bool			m_bAttack;							// �ߐڍU���ł��邩�ǂ���
	bool			m_bKnifeAttack;						// �U�������Ă��邩�ǂ���
	bool			m_bRespawn;							// ���X�|�[���t���O
	bool			m_bCruch;							// �N���b�`
	bool			m_bRideVehicle;						// ��蕨�ɏ�荞��ł��邩�ǂ����̃t���O

	WORD			Oldstate;							// �R���g���[���[��1frame�O�̃X�e�[�g
	CGun			*m_pGun;							// �K���N���X�̃|�C���^
	CGrenadeFire	*m_pGrenadeFire;					// �O���l�[�h���˃N���X�̃|�C���^
	CPlayerUI		*m_pPlayerUI;						// �v���C���[UI�̃|�C���^
	CKnife			*m_pKnife;							// �i�C�t�̃|�C���^

	CVehicle		*m_pVehicle;						// ��蕨�N���X�̃|�C���^
	CXInputPad		*m_pPad;							// �p�b�h�̃|�C���^
};
#endif