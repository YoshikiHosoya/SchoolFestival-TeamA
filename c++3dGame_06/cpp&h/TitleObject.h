// ----------------------------------------
//
// �I�u�W�F�N�g�����̐���[object.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _TITLEOBJECT_H_
#define _TITLEOBJECT_H_	 // �t�@�C������������߂�

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
// -----------------------------------
#define MAX_TITLEOBJ (2)
//=============================================================================
// �O���錾
//=============================================================================

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CTitleObject : public CScene_X
{
public:
	/* �֐� */
	CTitleObject();
	~CTitleObject();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos);			// �ʒu�ݒ�
	void SetRot(D3DXVECTOR3 rot);			// ��]�ݒ�
	D3DXVECTOR3 GetPos(void);				// �ʒu�擾
	static CTitleObject * Create(void);			// �쐬
	static void CTitleObject::LoadCreate(void);	// �ǂݍ��񂾂��̂𐶐�
	static HRESULT Load(void);				// �ǂݍ���
	static void UnLoad(void);				// �j��
protected:
private:
	static CLoad		*m_pload;							// ���[�h
	static CModel_info	*m_pmodel_info;					// ���f�����
	static int			m_nAll;								// ����
};

#endif

