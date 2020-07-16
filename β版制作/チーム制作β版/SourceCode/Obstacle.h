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
typedef struct
{
	int					nLife;			// �̗�
	D3DXVECTOR3			CollisionSize;	// �傫�� // �����蔻��Ɏg���T�C�Y
}OBSTACLE_PARAM;

// =====================================================================================================================================================================
// �O���錾
// =====================================================================================================================================================================
// =====================================================================================================================================================================
// ��Q���N���X
// =====================================================================================================================================================================
class CObstacle : public CModel
{
public:

	// ��Q���̎��
	enum OBSTACLE_TYPE
	{
		TYPE_BOX = 0,								// �ؔ�
		TYPE_BARREL,								// �M
		TYPE_TREE,									// ��
		TYPE_CHEST,									// ����
		TYPE_SANDBAGS,								// �y�X
		TYPE_MAX,									// �ő吔
	};

	CObstacle(OBJ_TYPE type);						// �R���X�g���N�^
	~CObstacle();									// �f�X�g���N�^

	/* �����o�֐� */
	virtual HRESULT			Init();					// ������
	virtual void			Uninit();				// �I��
	virtual void			Update();				// �X�V
	virtual void			Draw();					// �`��
	virtual void			DebugInfo();			//�f�o�b�O

	/* �ÓI�����o�֐� */
	static	CObstacle		*Create();				// ��Q���̐���
	static	void			ObstacleLoad();			// ��Q���̃��[�h

	/* �����o�֐� */
	OBSTACLE_TYPE			&GetObstacleType()					{ return m_ObstacleType; };			// ��Q���̎�ނ̎擾
	void					SetObstacleType(OBSTACLE_TYPE type) { m_ObstacleType = type; };			// ��Q���̎�ނ̐ݒ�
	OBSTACLE_PARAM			*GetObstacleParam(int nCnt)			{ return &m_ObstacleParam[nCnt]; };	// �e�̃p�����[�^�[�̍\���̂̎擾
	void					SetObstacleParam(CObstacle::OBSTACLE_TYPE type)
								{ m_nLife = m_ObstacleParam[type].nLife; };							// ��Q���̏��ݒ�
	int						GetLife() { return m_nLife; };											// �̗͂̎擾
	void					SetLife(int nLife) { m_nLife = nLife; };								// �̗͂̐ݒ�
	void					SetCollisionSize(CObstacle::OBSTACLE_TYPE type);						// �傫���̐ݒ�

	void					Hit(OBSTACLE_TYPE type, int nDamage);									// ��Q�����󂳂��Ƃ��̏���

private:
	/* �����o�֐�*/
	void					CheckDie();																// �̗͂����邩�m�F
	void					AddDamage(int Damage);													// �_���[�W�����Z����
	/* �ÓI�����o�ϐ� */
	static OBSTACLE_PARAM	m_ObstacleParam[CObstacle::TYPE_MAX];									// ��Q���̃p�����[�^�[
	static char				*m_ObstacleFileName[CObstacle::TYPE_MAX];								// ��Q���̃t�@�C����
	/* �����o�ϐ� */
	OBSTACLE_TYPE			m_ObstacleType;															// ��Q���̎��
	D3DXVECTOR3				m_pos;																	// ���W
	int						m_nLife;																// �̗�
};
#endif
