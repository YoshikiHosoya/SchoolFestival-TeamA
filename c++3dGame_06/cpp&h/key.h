// ----------------------------------------
//
// �������̐���[key.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _KEY_H_
#define _KEY_H_	 // �t�@�C������������߂�

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
class CKey : public CScene_X
{
public:
	/* �񋓌^ */

	/* �֐� */
	CKey();
	~CKey();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos);			// �ʒu�ݒ�
	void SetRot(D3DXVECTOR3 rot);			// ��]�ݒ�
	D3DXVECTOR3 GetPos(void);				// �ʒu�擾
	static bool bGetFlag(void);
	static CKey * Create(void);			// �쐬
	static HRESULT Load(void);				// �ǂݍ���
	static void UnLoad(void);				// �j��
protected:
private:
	static CModel_info	*m_pmodel_info;					// ���f�����
	static D3DXVECTOR3 m_pos;							// �ʒu���
	static bool			m_bGet;				// ������ɓ��ꂽ���ǂ���
};

#endif