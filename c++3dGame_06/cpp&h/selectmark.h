// ----------------------------------------
//
// �󏈗��̐���[selectmark.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _SELECTMARK_H_
#define _SELECTMARK_H_	 // �t�@�C������������߂�

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
class CSelectMark : public CScene_TWO
{
public:
	/* �񋓌^ */
	// �^�C�v
	typedef enum
	{
		MARK_ARROW = 0,		// ���
		MARK_SHAPE,			// �}�`
		MARK_MAX
	} MARK;

	/* �֐� */
	CSelectMark();
	~CSelectMark();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetSize(D3DXVECTOR2 size);						// �T�C�Y�ݒ�
	void SetPos(D3DXVECTOR3 pos);						// �ʒu�ݒ�
	void SetRot(float rot);								// ��]�ݒ�
	void SetCol(D3DXCOLOR col);							// �F�ݒ�
	void SetTexure(MARK type);							// �e�N�X�`���[�ݒ�
	void SetCount(int nCnt);							// �J�E���^�[�ݒ�
	void CalculationCount(int nCnt);					// �J�E���^�[�ݒ�
	void ResetCount(void);								// �J�E���g�����Z�b�g
	void ReleaseSelMark(void);							// �}�[�N�̍폜
	void Transparency(void);							// ������

	int			GetCount(void);							// �J�E���g���擾
	D3DXVECTOR2 GetSize(void);							// �T�C�Y�擾
	D3DXVECTOR3 GetPos(void);							// �ʒu�擾
	static CSelectMark * Create(D3DXVECTOR3 pos,		// �쐬
		float rot,
		D3DXVECTOR2 size,
		D3DXCOLOR col,
		MARK type);

	static HRESULT Load(void);							// �ǂݍ���
	static void UnLoad(void);							// �j��

protected:
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MARK_MAX];		// �e�N�X�`���ւ̃|�C���^
	float			m_fLengh;							// ����
	float			m_fAngle;							// �p�x
	MARK			m_type;								// �Ɩ��̎��
	D3DXVECTOR3		m_pos;								// ���W
	float			m_frot;								// ��]
	D3DXVECTOR2		m_size;								// �傫��
	D3DXCOLOR		m_col;								// �F
	int				m_nSelectCount;						// ����ړ���������
};
#endif

