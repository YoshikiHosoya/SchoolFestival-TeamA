// ----------------------------------------
//
// 2D�̃A�j���[�V���������̐���[2DAnimation.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _2DANIMATION_H_
#define _2DANIMATION_H_	 // �t�@�C������������߂�

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "scene_two.h"

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
class C2DAnimation : public CScene_TWO
{
public:
	/* �񋓌^ */
	// �^�C�v
	typedef enum
	{
		TYPE_KEY = 0,	// ��
		TYPE_1,			//
		TYPE_2,			//
		TYPE_MAX
	} TYPE;

	/* �֐� */
	C2DAnimation();
	~C2DAnimation();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTexture(TYPE type);								// �e�N�X�`���[�ݒ�
	void SetSize(D3DXVECTOR2 size);							// �T�C�Y�ݒ�
	void SetPos(D3DXVECTOR3 pos);							// �ʒu�ݒ�
	void SetRot(float rot);									// ��]�ݒ�
	void SetCol(D3DXCOLOR col);								// �F�ݒ�
	void SetTex(D3DXVECTOR2 first, D3DXVECTOR2 last);		// �\���e�N�X�`���[�ݒ�
	void SetAnim(void);										// �A�j���[�V�����Đ�
	D3DXVECTOR2 GetSize(void);								// �T�C�Y�擾
	float GetRot(void);										// ��]�擾
	D3DXVECTOR3 GetPos(void);								// �ʒu�擾
	static C2DAnimation * Create(D3DXVECTOR3 pos,
								D3DXVECTOR2 size,
								D3DXVECTOR2 texf,
								D3DXVECTOR2 texr,
								TYPE type);					// �쐬
	static HRESULT Load(void);								// �ǂݍ���
	static void UnLoad(void);								// �j��
protected:
private:
	static LPDIRECT3DTEXTURE9	m_pTexture[TYPE_MAX];		// �e�N�X�`���ւ̃|�C���^
	TYPE						m_Type;						// �^�C�v
	int							m_nCntAnim;					// 1�t���[��������̃J�E���g
	int							m_nPatternAnim;				// �p�^�[����
	D3DXVECTOR2					m_TexFirst;					// �e�N�X�`�����W
	D3DXVECTOR2					m_TexLast;					// �e�N�X�`�����W
};
#endif