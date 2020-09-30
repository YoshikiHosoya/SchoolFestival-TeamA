// =====================================================================================================================================================================
//
// ��Q���̏��� [Obstacle.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

// =====================================================================================================================================================================
// �C���N���[�h�t�@�C��
// =====================================================================================================================================================================
#include "main.h"
#include "model.h"

// =====================================================================================================================================================================
// ��Q���̏��
// =====================================================================================================================================================================
struct OBSTACLE_PARAM
{
	int					nLife;			// �̗�
	D3DXVECTOR3			CollisionSize;	// �傫�� // �����蔻��Ɏg���T�C�Y
	bool				bBreak;			// ���邩�ǂ���
};

// =====================================================================================================================================================================
// �O���錾
// =====================================================================================================================================================================
// =====================================================================================================================================================================
// ��Q���N���X
// =====================================================================================================================================================================
class CObstacle : public CModel, public CGameObject
{
public:

	// ��Q���̎��
	enum OBSTACLE_TYPE
	{
		TYPE_NONE = -1,								// �����Ȃ�
		TYPE_BOX,									// �ؔ�
		TYPE_BARREL,								// �M
		TYPE_BARRELBOMB,							// �M���e
		TYPE_TREE,									// ��
		TYPE_CHEST,									// ����
		TYPE_SANDBAGS,								// �y�X
		TYPE_CAR,									// ��
		TYPE_BALLOON,								// ���D
		TYPE_PRESENTBOX,							// �v���[���g
		TYPE_PRESENTBOX_RARE,						// �v���[���g���A
		TYPE_BOSSMAP_BRIDGE,						// �{�X�̃}�b�v�Ŏg����
		TYPE_MAX,									// �ő吔
	};

	CObstacle() {};
	CObstacle(OBJ_TYPE type);						// �R���X�g���N�^
	virtual ~CObstacle();							// �f�X�g���N�^

	/* �����o�֐� */
	virtual HRESULT			Init();					// ������
	virtual void			Uninit();				// �I��
	virtual void			Update();				// �X�V
	virtual void			Draw();					// �`��
	virtual void			DebugInfo();			//�f�o�b�O

	/* �ÓI�����o�֐� */
	static	CObstacle		*Create(OBSTACLE_TYPE Type);// ��Q���̐���
	static	CObstacle		*Create_Editor();// ��Q���̐���
	static	CObstacle		*Create_Present(D3DXVECTOR3 pos, CObstacle::OBSTACLE_TYPE Type);// ��Q���̐���

	static	void			ObstacleLoad();			// ��Q���̃��[�h

	/* �����o�֐� */
	OBSTACLE_TYPE			&GetObstacleType()					{ return m_ObstacleType; };			// ��Q���̎�ނ̎擾
	void					SetObstacleType(OBSTACLE_TYPE type) { m_ObstacleType = type; };			// ��Q���̎�ނ̐ݒ�
	OBSTACLE_PARAM			*GetObstacleParam(int nCnt)			{ return  &m_ObstacleParam[nCnt]; };	// �e�̃p�����[�^�[�̍\���̂̎擾
	void					SetObstacleParam(CObstacle::OBSTACLE_TYPE type);
																									// ��Q���̏��ݒ�
	int						GetLife() { return m_nLife; };											// �̗͂̎擾
	void					SetLife(int nLife) { m_nLife = nLife; };								// �̗͂̐ݒ�
	void					SetCollisionSize(CObstacle::OBSTACLE_TYPE type);						// �傫���̐ݒ�

	void					Hit(TAG tag, int nDamage);												// ��Q�����󂳂��Ƃ��̏���
	void					DropItem();																// ��ނ��Ƃ̃h���b�v

private:
	/* �����o�֐�*/
	void					CheckDie(TAG tag);														// �̗͂����邩�m�F
	void					AddDamage(int Damage);													// �_���[�W�����Z����

	/* �ÓI�����o�ϐ� */
	static OBSTACLE_PARAM	m_ObstacleParam[CObstacle::TYPE_MAX];									// ��Q���̃p�����[�^�[
	static char				*m_ObstacleFileName[CObstacle::TYPE_MAX];								// ��Q���̃t�@�C����
	/* �����o�ϐ� */
	OBSTACLE_TYPE			m_ObstacleType;															// ��Q���̎��
	int						m_nLife;																// �̗�
	CObstacle				*m_pBalloon;															// ���D�̃|�C���^

	D3DXVECTOR3				m_BalloonMove;															// ���D�̈ړ�
	float					m_fGravity;																// �v���[���g�������Ă��鎞�̏d��
	bool					m_bGravity;																// �v���[���g�������Ă��鎖������
	bool					m_bBreakBalloon;
};
#endif
