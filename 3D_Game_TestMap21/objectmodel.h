// =====================================================================================================================================================================
//
// �I�u�W�F�N�g���f���̏��� [objectmodel.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _OBJECTMODEL_H_
#define _OBJECTMODEL_H_

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// �C���N���[�h�t�@�C��
// =====================================================================================================================================================================
#include "main.h"
#include "scene.h"
#include "sceneX.h"

// =====================================================================================================================================================================
// �I�u�W�F�N�g���f���N���X
// =====================================================================================================================================================================
class CObjectModel : public CSceneX
{
public:
	// �I�u�W�F�N�g�̎��
	enum OBJECTTYPE
	{
		OBJECTTYPE_NONE = -1,
		OBJECTTYPE_STONE,						// ��
		OBJECTTYPE_BOX,							// ��
		OBJECTTYPE_GROUND_L,					// �n�� (��
		OBJECTTYPE_GROUND_M,					// �n�� (��
		OBJECTTYPE_GROUND_S,					// �n�� (��
		OBJECTTYPE_GAYSER,						// �Ԍ���
		OBJECTTYPE_SCAFFOLD,					// ����
		OBJECTTYPE_SCAFFOLD_HIT,				// 2D�ł������鑫��
		OBJECTTYPE_SCAFFOLD_MOVE,				// ��������
		OBJECTTYPE_WALL,						// ��
		OBJECTTYPE_GROUND_HALF,					// �n�� (�n�[�t
		OBJECTTYPE_GROUND_QUARTER,				// �n�� (4/1
		OBJECTTYPE_SIGNBOARD_FALL,				// �Ŕ� (������
		OBJECTTYPE_SIGNBOARD_JUMP,				// �Ŕ� (�W�����v
		OBJECTTYPE_SIGNBOARD_GAYSER,			// �Ŕ� (�Ԍ���
		OBJECTTYPE_SIGNBOARD_CHANGE,			// �Ŕ� (�J�����ؑւ�
		OBJECTTYPE_SIGNBOARD_ALL_RIDE,			// �Ŕ� (2D�ł�����
		OBJECTTYPE_SIGNBOARD_3D_RIDE,			// �Ŕ� (3D�ł������Ȃ�
		OBJECTTYPE_MAX,
	};

	CObjectModel();								// �R���X�g���N�^
	virtual ~CObjectModel();					// �f�X�g���N�^
	
	/* �����o�֐� */
	void				Init();					// ������
	void				Uninit();				// �I��
	void				Update();				// �X�V
	void				Draw();					// �`��

	/* �ÓI�����o�֐� */
	static	CObjectModel	*Create(D3DXVECTOR3 pos, OBJECTTYPE type);		// �I�u�W�F�N�g���f���̐���	
	static	HRESULT			Load();				// ���[�h
	static	void			Unload();			// �A�����[�h

	/* �����o�֐� */
	bool					CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pSize, CObjectModel **ppObjectRet);	// �I�u�W�F�N�g�̓����蔻��
	OBJECTTYPE				GetObjectType()		{ return m_ObjectType; };	// �I�u�W�F�N�g�̎�ނ̎擾
	void					SetObjectType(OBJECTTYPE type);					// �I�u�W�F�N�g�̎�ނ̐ݒ�

private:
	/* �ÓI�����o�ϐ� */
	static	LPDIRECT3DTEXTURE9	m_apTexture[OBJECTTYPE::OBJECTTYPE_MAX];	// ���L�e�N�X�`���̃|�C���^
	static MODEL_DRAWINFO		m_ModelDrawInfo[OBJECTTYPE_MAX];			// ���f���̕`����

	/* �����o�ϐ� */
	D3DXVECTOR3					m_posOld;		// �ߋ��̈ʒu
	D3DXVECTOR3					m_move;			// �ړ�
	D3DXVECTOR3					m_VtxMin;		// �ŏ����_
	D3DXVECTOR3					m_VtxMax;		// �ő咸�_
	OBJECTTYPE					m_ObjectType;	// �I�u�W�F�N�g�̎��
};
#endif
