// ----------------------------------------
//
// �I�u�W�F�N�g�����̐���[object.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _OBJECT_H_
#define _OBJECT_H_	 // �t�@�C������������߂�

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "scene_X.h"

// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------

//=============================================================================
// �O���錾
//=============================================================================

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CObject : public CScene_X
{
public:
	/*��*/
	typedef enum
	{
		OBJ_TYPE_CheckPoint,
		OBJ_TYPE_MAX
	} OBJ_TYPE;


	/* �֐� */
	CObject();
	~CObject();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos);			// �ʒu�ݒ�
	void SetRot(D3DXVECTOR3 rot);			// ��]�ݒ�
	D3DXVECTOR3 GetPos(void);				// �ʒu�擾
	static CObject * Create(void);			// �쐬
	static void CObject::LoadCreate(void);	// �ǂݍ��񂾂��̂𐶐�
	static HRESULT Load(void);				// �ǂݍ���
	static void UnLoad(void);				// �j��
protected:
private:
	static CLoad		*m_pload;							// ���[�h
	static CModel_info	*m_pmodel_info;					// ���f�����
	static int			m_nAll;								// ����
	OBJ_TYPE			m_type;
};

#endif
