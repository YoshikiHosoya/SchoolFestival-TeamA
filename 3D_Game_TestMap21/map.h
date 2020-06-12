// =====================================================================================================================================================================
//
// �}�b�v�̏��� [map.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _MAP_H_
#define _MAP_H_

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define MAX_OBJECT				(100)										// �I�u�W�F�N�g�̍ő吔
#define MAX_OBJECT2D			(30)										// 2D�I�u�W�F�N�g�̍ő吔
#define MAX_ITEM				(50)										// �A�C�e���̍ő吔
#define MAX_SLOPE				(20)										// ��̍ő吔

// =====================================================================================================================================================================
// �C���N���[�h�t�@�C��
// =====================================================================================================================================================================
#include "main.h"

// =====================================================================================================================================================================
// �O���錾
// =====================================================================================================================================================================
class	CObjectModel;			// �I�u�W�F�N�g���f���N���X
class	CEffect;				// �G�t�F�N�g�N���X
class	CItem;					// �A�C�e���N���X
class	CObject2D;				// 2D�I�u�W�F�N�g�N���X
class	CSlope;					// ��N���X

// =====================================================================================================================================================================
// �}�b�v�N���X
// =====================================================================================================================================================================
class CMap
{
public:
	/* �ÓI�����o�֐� */
	static	bool	CollisionObjectAll(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pSize);	// �I�u�W�F�N�g�̓����蔻��
	static	bool	CollisionObject2DAll(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pSize);	// 2D�I�u�W�F�N�g�̓����蔻��
	static	bool	GetHeightSlopeAll(D3DXVECTOR3 &pos, D3DXVECTOR3 &move);		// ��̍����̎擾
	static	void	MapUpdate();							// �}�b�v�̍X�V
	static	void	ObjectLoad();							// �}�b�v�̓ǂݍ���
	static	void	Object2DLoad();							// 2D�I�u�W�F�N�g�̓ǂݍ���
	static	void	ItemLoad();								// �A�C�e���̓ǂݍ���
	static	void	SlopeLoad();							// ��̓ǂݍ���
	static	void	ReleaseMap();							// �}�b�v�̊J��

	static	void	SetProvisionalMap();					// �����I�}�b�v�̔z�u

private:
	/* �ÓI�����o�֐� */
	static	void	ObjectSave();							// �}�b�v�̏�������
	static	void	Object2DSave();							// 2D�I�u�W�F�N�g�̏�������
	static	void	ItemSave();								// �A�C�e���̏�������
	static	void	SlopeSave();							// ��̏�������
	static	void	ObjectSet();							// �I�u�W�F�N�g�̃Z�b�g
	static	void	Object2DSet();							// 2D�I�u�W�F�N�g�̃Z�b�g
	static	void	ItemSet();								// �A�C�e���̃Z�b�g
	static	void	SlopeSet();								// ��̃Z�b�g

	/* �ÓI�����o�ϐ� */
	static CObjectModel		*m_pObject[MAX_OBJECT];			// �I�u�W�F�N�g���
	static CObject2D		*m_pObject2D[MAX_OBJECT2D];		// 2D�I�u�W�F�N�g���
	static CItem			*m_pItem[MAX_ITEM];				// �A�C�e�����
	static CSlope			*m_pSlope[MAX_SLOPE];			// ��̏��
};
#endif
