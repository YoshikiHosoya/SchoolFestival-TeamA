// =====================================================================================================================================================================
//
// �v���C���[�̏��� [player.h]
// Author :
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

// =====================================================================================================================================================================
// �v���C���[�N���X
// =====================================================================================================================================================================
class CPlayer :public CCharacter
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

	/* �����o�֐� */
	CPlayer(OBJ_TYPE type);
	~CPlayer();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void DebugInfo(void);
	void MoveUpdate(void);
	void CollisionUpdate(void);
	void AttackUpdate(void);
	void PadMoveUpdate(void);
	void ReSpawn(void);
	void DamageReaction();
	void DeathReaction();
	void StateChangeReaction();
	DEBUG_STATE GetDebugState(void);
	bool DefaultMotion(void);
	void MapChangePlayerRespawn();

	/* �ݒ� �擾 �֐� */
	CGun			*GetGun()						{ return  m_pGun; };			// �e�̃|�C���^�擾
	CGrenadeFire	*GetGrenadeFire()				{ return  m_pGrenadeFire; };	// �O���l�[�h���ˈʒu�̃|�C���^�擾
	CPlayerUI		*GetPlayerUI()					{ return  m_pPlayerUI; };		// �v���C���[UI�̃|�C���^�擾
	void			SetRideFlag(bool bRide)			{ m_bRideVehicle = bRide; };	// ���C�h�t���O�̐ݒ�
	bool			GetRideFlag()					{ return m_bRideVehicle; };		// ���C�h�t���O�̎擾
	void			SetRespawnFlag(bool bRespawn)	{ m_bRespawn = bRespawn; };		// ���X�|�[���t���O�擾
	bool			GetRespawnFlag()				{ return m_bRespawn; };			// ���X�|�[���t���O�̐ݒ�

	/* �ÓI�����o�֐� */
	static CPlayer *Create(void);					// ����
	static	void	PlayerLoad();					// �v���C���[�̃��[�h
private:
	/* �ÓI�����o�֐� */
	static void		SetPlayerData();				// �ǂݍ��񂾃f�[�^�̐ݒ�

	/* �����o�֐� */
	void Move(float move, float fdest);				//
	void Ride();									//

	/* �ÓI�����o�ϐ� */
	static			PLAYER_DATA		m_PlayerData;		// �v���C���[�̃f�[�^
	static			char			*m_PlayerFileName;	// �����L���O�̃t�@�C����

	/* �ǂݍ��񂾃f�[�^���i�[���郁���o�ϐ� */
	static			int				m_nLife[2];			// �̗͏����c�@
	static			int				m_nRespawnCnt;		// ���X�|�[���܂ł̃J�E���g�����܂ł̃J�E���g
	static			float			m_fRunSpeed;		// ����X�s�[�h
	static			float			m_fCrouchSpeed;		// ���Ⴊ�ݕ������̃X�s�[�h
	static			float			m_fJump;			// �ʏ펞�̃W�����v
	static			float			m_fRideJump;		// ��Ԓ��̃W�����v
	static			D3DXVECTOR3						m_pos[2];				// �������W

	/* �����o�ϐ� */
	D3DXVECTOR3		m_ShotRot;							//������
	DEBUG_STATE		m_DebugState;						// �f�o�b�O�̃X�e�[�^�X
	bool			m_bAttack;							// �ߐڍU���ł��邩�ǂ���
	bool			m_bKnifeAttack;						// �U�������Ă��邩�ǂ���
	bool			m_bRespawn;							// ���X�|�[���t���O
	float			m_Angle;							// �A���O��
	bool			m_bCruch;							// �N���b�`
	WORD			Oldstate;							// �R���g���[���[��1frame�O�̃X�e�[�g
	CGun			*m_pGun;							// �K���N���X�̃|�C���^
	CGrenadeFire	*m_pGrenadeFire;					// �O���l�[�h���˃N���X�̃|�C���^
	CPlayerUI		*m_pPlayerUI;						// �v���C���[UI�̃|�C���^
	CKnife			*m_pKnife;							// �i�C�t�̃|�C���^
	bool			m_bRideVehicle;						// ��蕨�ɏ�荞��ł��邩�ǂ����̃t���O
};
#endif