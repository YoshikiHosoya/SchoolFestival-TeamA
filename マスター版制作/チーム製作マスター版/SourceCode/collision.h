//=============================================================================
//
// Collision�w�b�_�[�����̐���[collision.h]
// Author : Fujiwara Masato
//
//=============================================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_	 // �t�@�C������������߂�

//=============================================================================
//
// �C���N���[�h�t�@�C��
//
//=============================================================================
#include "main.h"

//=============================================================================
//
// �}�N����`
//
//=============================================================================

//=============================================================================
//
// �O���錾
//
//=============================================================================
class CDebugcollision;
class CMap;
class CPrisoner;
class CEnemy;
class CPlayertank;
class CBattlePlane;
class CPlayer;

//=============================================================================
//
// �N���X
//
//=============================================================================
class CCollision
{
public:
	// �����蔻��̎�Ȏ��
	typedef enum
	{
		// �͈͔���
		COLLISIONTYPE_NORMAL = 0,			// ���S�_�����_�ɂ��锻��
		COLLISIONTYPE_CHARACTER,			// ���������_�ɂ��锻��
		COLLISIONTYPE_OTHER,				// ���S�_�����_�Ƃ���I�u�W�F�N�g�Ƒ��������_�ɂ���I�u�W�F�N�g�Ŕ���
		// �u���b�N����
		COLLISIONTYPE_BLOCK,				// ���S�_�����_�Ƃ���u���b�N�Ƒ��������_�̃I�u�W�F�N�g�Ŕ���
		COLLISIONTYPE_MAX
	} COLLISIONTYPE;

	/* �����o�֐� */
	CCollision();
	~CCollision();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void ShowDebugInfo();

	/* �ÓI�����o�֐� */
	static CCollision * Create();

	/* �����o�֐� */

	void SetPos(D3DXVECTOR3 *pos);													// ���W�̐ݒ�
	void SetPosOld(D3DXVECTOR3 *posold);											// 1�t���[���O�̍��W�̐ݒ�
	void SetSize(D3DXVECTOR3 size);													// �T�C�Y�̐ݒ�
	void SetSize2D(D3DXVECTOR3 size);												// 2D�p�T�C�Y�̐ݒ�
	void SetMove(D3DXVECTOR3 *move);												// �ړ��ʂ̐ݒ�
	void SetTime(int nTime) { m_nCollisionTime = nTime; };							// �p�����Ԃ̐ݒ�
	void SetCanCollision(bool bCollision) { m_bCanCollision = bCollision; };		//�����蔻��\���ǂ����ݒ�
	void SetGameObject(CGameObject *GameObject) { m_pGameObject = GameObject; };	// �Q�[���I�u�W�F�N�g( �^�O )�̐ݒ�
	bool GetCanCollison() { return m_bCanCollision; };								// �����蔻��ł��邩�ǂ����擾
	int	 GetTime() { return m_nCollisionTime; };									// �p�����Ԃ̐ݒ�
	void SetHeight(float height);													// Ray�̍����ݒ�
	bool Collision2D(CCollision *pCollision);										// �^�̓����蔻��
	bool CharCollision2D(CCollision *pCollision);									// �L�����N�^�[�p�^�̓����蔻��
	bool OtherCollision2D(CCollision *pCollision);									// �^�̓����蔻��
	bool BlockCollision2D(CCollision *pCollision);									// �^�u���b�N�̓����蔻��
	bool BlockNotUpsideCollision2D(CCollision *pCollision);							// �^�u���b�N�̓����蔻��

	// ��p
	bool BlockCollision2D_Bottom(CCollision *pCollision);
	bool BoxCollision2D_Character(CCollision *pCollision);// �L�����N�^�[���m

	bool RayBlockCollision(CMap *pMap, D3DXMATRIX *pMat);				// Ray�̔��� �L�����N�^�[
	bool RayCollision(CMap *pMap);										// Ray�̔��� �e�Ȃ�
	bool RayFloorCollision(CMap *pMap, D3DXMATRIX *pMat,D3DXVECTOR3 pdirection,D3DXVECTOR3 ppos);// Ray�̔��� �O���̏�

	void DeCollisionCreate(COLLISIONTYPE collisiontype)	;				// �f�o�b�O�p�����蔻��̐���
	bool ForPlayerBulletCollision(int nEnemyDamage,
							int nObstacleDamage,
							bool Penetration);							// �v���C���[�̒e���s������ �_���[�W�� �ђʂ��邩�ǂ���

	bool ForEnemyCollision(int nPlayerDamage,
		int nPlayerTankDamage,
		bool Penetration);												// �G�l�~�[�̒e���s������ �_���[�W�� �ђʂ��邩�ǂ���

	bool ForPlayer_EnemyCollision(bool Penetration);					// �v���C���[�ƃG�l�~�[���s������ �_���[�W�� �ђʂ��邩�ǂ���

	bool ForPlayer_ObstacleCollision();									// �v���C���[�Ə�Q�����s������ �_���[�W�� �ђʂ��邩�ǂ���

	bool ForPlayer_PrisonerCollision(bool Penetration);					// �v���C���[�ƕߗ����s������ �_���[�W�� �ђʂ��邩�ǂ���

	bool ForPlayer_ItemCollision(TAG Tag);				// �v���C���[�ƕߗ����s������ �_���[�W�� �ђʂ��邩�ǂ���

	CPrisoner		*ForPlayer_PrisonerCollision();						// �v���C���[�ƕߗ��̐ڐG���� �ߗ��̏�ԕύX
	CEnemy			*ForPlayer_EnemyCollision();						// �v���C���[�ƃG�l�~�[�̐ڐG����
	CPlayertank		*ForPlayer_TankCollision();							// �v���C���[�Ɛ�Ԃ̐ڐG����
	CBattlePlane	*ForPlayer_PlaneCollision();						// �v���C���[�Ɛ퓬�@�̐ڐG����

	bool ForPlayer_VehicleCollision(CCollision * pCollision);	// �v���C���[�Ə�蕨���s������
	void *ForPlayer_VehicleCollision();							// �v���C���[�Ə�蕨���s������
	bool ForVehicleCollision();									// ��蕨���s������
	bool ForTankCollision();									// ��Ԃ��s������

	void ForBossOne_PlayerCollision();
	bool BossOne_PlayerCollision();								// �{�X���s������

	bool KnifeCollision(D3DXVECTOR3 Knifepos,
		CCollision *pCollision);						// �i�C�t�ƃL�����N�^�[�̔���

	bool VehicleCollision(CCollision *pCollision);		// �v���C���[����蕨�ɏ�鎞�̔���

protected:
private:
	/* �����o�ϐ� */
	COLLISIONTYPE		m_Collisiontype;				// �����蔻��̃^�C�v
	D3DXVECTOR3			*m_ppos;						// �ʒu���̃|�C���^
	D3DXVECTOR3			*m_posOld;						// �O��̈ʒu���
	D3DXVECTOR3			m_size;							// �T�C�Y���
	D3DXVECTOR3			*m_pmove;						// �ړ����̃|�C���^
	CDebugcollision		*m_Debugcollision;				// �f�o�b�O�p�����蔻��̃|�C���^
	bool				m_bDeadFlag;					// ���S�t���O
	bool				m_bCanCollision;				// ������Ƃ邩�ǂ���
	int					m_nCollisionTime;				// �����蔻�肪�������鎞��
	float				m_fHeight;

	CGameObject			*m_pGameObject;					// �Q�[���I�u�W�F�N�g( �^�O )�̃|�C���^
};

#endif