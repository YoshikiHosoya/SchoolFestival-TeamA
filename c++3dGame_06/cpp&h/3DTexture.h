// ----------------------------------------
//
// 3D�e�N�X�`�������̐���[3dtexture.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _3DTEXTURE_H_
#define _3DTEXTURE_H_	 // �t�@�C������������߂�

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
class C3DTexture : public CScene_THREE
{
public:
	/* �񋓌^ */
	// �^�C�v
	typedef enum
	{
		TYPE_EFFECT_000 = 0,	// Effect000
		TYPE_EFFECT_001,		// Effect001
		TYPE_MAX
	} TYPE;

	/* �֐� */
	C3DTexture();
	~C3DTexture();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTexture(TYPE type);							// �e�N�X�`���[�ݒ�
	void SetSize(D3DXVECTOR3 size);						// �T�C�Y�ݒ�
	void SetPos(D3DXVECTOR3 pos);						// �ʒu�ݒ�
	void SetRot(D3DXVECTOR3 rot);						// ��]�ݒ�
	void SetCol(D3DXCOLOR col);							// �F�ݒ�
	void SetTex(D3DXVECTOR2 first, D3DXVECTOR2 last);	// �\���e�N�X�`���[�ݒ�
	D3DXVECTOR3 GetSize(void);							// �T�C�Y�擾
	D3DXVECTOR3 GetRot(void);							// ��]�擾
	D3DXVECTOR3 GetPos(void);							// �ʒu�擾

	static C3DTexture * Create(	D3DXVECTOR3 pos,
								D3DXVECTOR3 rot,
								D3DXVECTOR3 size,
								D3DXCOLOR col,
								TYPE type,
								bool bBillboard);		// �쐬

	static HRESULT Load(void);							// �ǂݍ���
	static void UnLoad(void);							// �j��
protected:
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];		// �e�N�X�`���ւ̃|�C���^
	D3DXMATRIX		m_mtxWorld;		// ���[���h�}�g���b�N�X
	TYPE			m_Type;		// �^�C�v
	bool			m_bBillboard;	// �r���{�[�h���
};
#endif