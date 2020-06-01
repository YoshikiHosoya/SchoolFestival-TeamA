// ----------------------------------------
//
// �����G�t�F�N�g�����̐���[lighteffect.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_	 // �t�@�C������������߂�

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
class CExplosion : public CScene_THREE
{
public:
	/* �񋓌^ */
	// �^�C�v
	typedef enum
	{
		TYPE_SMOKE = 0,		//��
		TYPE_EXPLOSION,		//����
		TYPE_MAX
	} TYPE;

	/* �֐� */
	CExplosion();
	~CExplosion();
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
	D3DXVECTOR3 GetSize(void);							// �T�C�Y�擾
	D3DXVECTOR3 GetRot(void);							// ��]�擾
	D3DXVECTOR3 GetPos(void);							// �ʒu�擾
	static CExplosion * Create(D3DXVECTOR3 pos,
								D3DXVECTOR3 size,
								TYPE type);		// �쐬
	static HRESULT Load(void);							// �ǂݍ���
	static void UnLoad(void);							// �j��
protected:
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];			// �e�N�X�`���ւ̃|�C���^
	D3DXMATRIX		m_mtxWorld;							// ���[���h�}�g���b�N�X
	float			m_fLengh;							// ����
	float			m_fAngle;							// �p�x
	TYPE			m_Type;								// �Ɩ��̎��
	bool			m_bBillboard;						// �r���{�[�h���
	int				m_nCntAnim;							// 1�t���[��������̃J�E���g
	int				m_nPatternAnim;						// �p�^�[����
	static D3DXVECTOR2		m_Tex[TYPE_MAX];								// �e�N�X�`�����W
	D3DXVECTOR2		m_TexFirst;							// �e�N�X�`�����W
	D3DXVECTOR2		m_TexFirstSMO;							// �e�N�X�`�����W
	D3DXVECTOR2		m_TexLast;							// �e�N�X�`�����W
	D3DXVECTOR2		m_TexLastSMO;							// �e�N�X�`�����W
	D3DXCOLOR		m_Col;								// �F
	D3DXVECTOR3		m_Size;								// �傫��
};
#endif
