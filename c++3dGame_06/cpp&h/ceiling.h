// ----------------------------------------
//
// �V�䏈���̐���[ceiling.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _CEILING_H_
#define _CEILING_H_	 // �t�@�C������������߂�

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
#define MAX_CEILINGTEXTURE (2)
//=============================================================================
// �O���錾
//=============================================================================

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CCeiling : public CScene_X
{
public:
	/* �񋓌^ */
	typedef enum
	{//*1�� 300*300*0
		SIZE_NORMAL = 0,						// �ʏ�̓V��
		SIZE_GIMMICK,							// �����J���Ă�V��
		TYPE_MAX,
	} SIZE;

	/* �֐� */
	CCeiling();
	~CCeiling();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos);				// �ʒu�ݒ�
	void SetRot(D3DXVECTOR3 rot);				// ��]�ݒ�
	D3DXVECTOR3 GetPos(void);					// �ʒu�擾
	static CCeiling * Create(D3DXVECTOR3 pos,
		D3DXVECTOR3 rot,
		SIZE type);			// �쐬
	static void CCeiling::LoadCreate(void);		// �ǂݍ��񂾂��̂𐶐�
	static HRESULT Load(void);					// �ǂݍ���
	static void UnLoad(void);					// �j��
protected:
private:
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_CEILINGTEXTURE];	// �e�N�X�`���ւ̃|�C���^
	static CLoad				*m_pload;		// ���[�h
	static CModel_info			*m_pmodel_info;	// ���f�����
	static int					m_nAll;			// ����
	SIZE						m_type;			// ���
};

#endif