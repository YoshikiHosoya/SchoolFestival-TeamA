// ----------------------------------------
//
// �A�C�e�������̐���[item.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _ITEM_H_
#define _ITEM_H_	 // �t�@�C������������߂�

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "scene_three.h"

// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CItem : public CScene_THREE
{
public:
	/* �񋓌^ */
	// �^�C�v
	typedef enum
	{
		TYPE_ROT = 0,	// ��]���A�b�v
		TYPE_JUMP,		// �W�����v�̓A�b�v
		TYPE_COIN,		// �R�C��
		TYPE_MAX
	} TYPE;

	/* �֐� */
	CItem();
	CItem(ACTOR actor, LAYER layer);
	~CItem();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTexture(TYPE type);							// �e�N�X�`���[�ݒ�
	void SetSize(D3DXVECTOR3 size);						// �T�C�Y�ݒ�
	void SetPos(D3DXVECTOR3 pos);						// �ʒu�ݒ�
	void SetRot(D3DXVECTOR3 rot);						// ��]�ݒ�
	void SetCol(D3DXCOLOR col);							// �F�ݒ�
	void SetTex(D3DXVECTOR2 first,D3DXVECTOR2 last);	// �\���e�N�X�`���[�ݒ�
	D3DXVECTOR3 GetSize(void);							// �T�C�Y�擾
	D3DXVECTOR3 GetRot(void);							// ��]�擾
	D3DXVECTOR3 GetPos(void);							// �ʒu�擾
	static CItem * Create(bool bBillboard);				// �쐬
	static void LoadCreate(void);						// �A�C�e������
	static HRESULT Load(void);							// �ǂݍ���
	static void UnLoad(void);							// �j��
	static CLoad *GetLoad(void);						// ���[�h�擾
protected:
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];		// �e�N�X�`���ւ̃|�C���^
	static CLoad	*m_pload;		// ���[�h
	static int		m_nAll;			// �ԍ�
	static int		m_nRotCntAll;		// ��]��
	static int		m_nJumpCntAll;		// �W�����v��
	D3DXVECTOR3		m_OriginBlock;	// �����z�u
	D3DXMATRIX		m_mtxWorld;		// ���[���h�}�g���b�N�X
	TYPE			m_Type;		// �^�C�v
	float			m_fLengh;		// ����
	float			m_fAngle;		// �p�x
	bool			m_bBillboard;	// �r���{�[�h���
};
#endif