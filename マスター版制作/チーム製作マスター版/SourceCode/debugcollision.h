// ----------------------------------------
//
// �f�o�b�O�p�����蔻��\������[debugcollision.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _DEBUGCOLLISION_H_
#define _DEBUGCOLLISION_H_	 // �t�@�C������������߂�

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "scene.h"
// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
#define MAX_VERTEX3D (12)
#define MAX_VERTEX2D (4)

// ------------------------------------------
//
// �O���錾
//
// ------------------------------------------
class CMeshBox;

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CDebugcollision : public CScene
{
public:
	/* �����蔻��̎�� */
	typedef enum
	{
		COLLISIONTYPE_BOX = 0,			//���^
		COLLISIONTYPE_BOX_CHARA,		//���^
		COLLISIONTYPE_MAX
	} COLLISIONTYPE;

	CDebugcollision(OBJ_TYPE type);
	~CDebugcollision();

	/* �����o�֐� */
	virtual HRESULT Init(void);
	virtual	void Uninit(void);
	virtual	void Update(void);
	virtual	void Draw(void);
	virtual void DebugInfo(void);
	/* �ÓI�����o�֐� */
	static CDebugcollision * Create(
		D3DXVECTOR3 * pos,
		D3DXVECTOR3 * size,
		COLLISIONTYPE type
	);

	/* �����o�֐� */
	void SetPos(D3DXVECTOR3 *pos);
	void SetSize(D3DXVECTOR3 *size);
	void DeleteDeCollision();
protected:

private:
	/* �����o�֐� */
	void BoxCollision(void);				// ���^�̔���
	void Box_CharaCollision(void);			// �L�����N�^�[�^�̔���


	/* �����o�ϐ� */
	D3DXVECTOR3 * m_pos;					// ���W
	D3DXVECTOR3 * m_size;					// �T�C�Y
	COLLISIONTYPE m_type;					// �^�C�v
	CMeshBox *m_pMeshBox;					// ���b�V���{�b�N�X�̃|�C���^
};

#endif