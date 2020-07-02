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
class C3DLine;
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
		COLLISIONTYPE_BOARD,			//�^
		COLLISIONTYPE_BOARDCHARA,		//�L�����N�^�[�p�^
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
	void BoardCollision(void);				// �^�̔���
	void BoardCharaCollision(void);			// �L�����N�^�[�^�̔���

	/* �����o�ϐ� */
	D3DXVECTOR3 * m_pos;					// ���W
	D3DXVECTOR3 * m_size;					// �T�C�Y
	COLLISIONTYPE m_type;					// �^�C�v
	C3DLine *m_p3DLine[MAX_VERTEX3D];		// ���C���̃|�C���^
	C3DLine *m_p2DLine[MAX_VERTEX2D];		// ���C���̃|�C���^
};

#endif