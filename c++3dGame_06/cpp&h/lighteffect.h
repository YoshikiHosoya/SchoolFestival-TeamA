// ----------------------------------------
//
// �Ɩ��G�t�F�N�g�����̐���[lighteffect.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _LIGHTEFFECT_H_
#define _LIGHTEFFECT_H_	 // �t�@�C������������߂�

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
class CLightEffect : public CScene_THREE
{
public:
	/* �񋓌^ */
	// �^�C�v
	typedef enum
	{
		TYPE_S_LIGHT = 0,	//
		TYPE_P_LIGHT,		//
		TYPE_MAX
	} TYPE;

	/* �֐� */
	CLightEffect();
	~CLightEffect();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetSize(D3DXVECTOR3 size);						// �T�C�Y�ݒ�
	void SetPos(D3DXVECTOR3 pos);						// �ʒu�ݒ�
	void SetRot(D3DXVECTOR3 rot);						// ��]�ݒ�
	void SetCol(D3DXCOLOR col);							// �F�ݒ�
	void SetTex(D3DXVECTOR2 first, D3DXVECTOR2 last);	// �e�N�X�`���[���W�ݒ�
	void SetTexure(TYPE type);							// �e�N�X�`���[�ݒ�

	void Transparency(void);							// ����


	D3DXVECTOR3 GetSize(void);							// �T�C�Y�擾
	D3DXVECTOR3 GetRot(void);							// ��]�擾
	D3DXVECTOR3 GetPos(void);							// �ʒu�擾
	static CLightEffect * Create(D3DXVECTOR3 pos,		// �쐬
		D3DXVECTOR3 rot,
		D3DXVECTOR3 size,
		D3DXCOLOR col,
		TYPE type,
		bool bBill);

	static HRESULT Load(void);							// �ǂݍ���
	static void UnLoad(void);							// �j��
	static void ReleaseLight(TYPE type);							// �G�t�F�N�g�̍폜

protected:
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];		// �e�N�X�`���ւ̃|�C���^
	static int		m_nAll;			// �ԍ�
	D3DXMATRIX		m_mtxWorld;		// ���[���h�}�g���b�N�X
	float			m_fLengh;		// ����
	float			m_fAngle;		// �p�x
	TYPE			m_type;			// �Ɩ��̎��
	bool			m_bBillboard;	// �r���{�[�h���
	D3DXVECTOR3		m_pos;			// ���W
	D3DXVECTOR3		m_rot;			// ��]
	D3DXVECTOR3		m_size;			// �傫��
	D3DXCOLOR		m_col;			// �F
};
#endif
