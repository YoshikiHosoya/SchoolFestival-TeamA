// ----------------------------------------
//
// �f�������̐���[bulletinboard.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _BULLETINBOARD_H_
#define _BULLETINBOARD_H_	 // �t�@�C������������߂�

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

//=============================================================================
// �O���錾
//=============================================================================

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CBulletinBoard : public CScene_THREE
{
public:
	/* �񋓌^ */
	// �^�C�v
	typedef enum
	{
		TYPE_A = 0,	//
		TYPE_B,		//
		TYPE_C,		//
		TYPE_MAX
	} TYPE;

	typedef enum
	{
		STATE_EMERGENCE = 0,				// �o��
		STATE_DISAPPEARANCE					// ����
	} STATE;

	/* �֐� */
	CBulletinBoard();
	CBulletinBoard(ACTOR actor, LAYER layer);
	~CBulletinBoard();
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
	void SetAnim(void);									// �A�j���[�V�����Đ�
	void Transparency(STATE state);						// ������
	D3DXVECTOR3 GetSize(void);							// �T�C�Y�擾
	D3DXVECTOR3 GetRot(void);							// ��]�擾
	D3DXVECTOR3 GetPos(void);							// �ʒu�擾
	static CBulletinBoard * Create();					// �쐬
	static void LoadCreate(void);						// �A�C�e������
	static HRESULT Load(void);							// �ǂݍ���
	static void UnLoad(void);							// �j��
	static CLoad *GetLoad(void);						// ���[�h�擾
protected:
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];		// �e�N�X�`���ւ̃|�C���^
	static CLoad	*m_pload;		// ���[�h
	static int		m_nAll;			// �ԍ�
	TYPE			m_Type;			// �^�C�v
	float			m_fLengh;		// ����
	float			m_fAngle;		// �p�x
	D3DXCOLOR		m_col;			// �F
	int				m_nCntAnim;		// 1�t���[��������̃J�E���g
	D3DXVECTOR2		m_TexFirst;		// �e�N�X�`�����W�̖ڕW
	D3DXVECTOR2		m_TexLast;		// �e�N�X�`�����W�̖ڕW
	D3DXVECTOR2		m_TexFirstSign;	// �e�N�X�`�����W
	D3DXVECTOR2		m_TexLastSign;	// �e�N�X�`�����W
};
#endif