// ----------------------------------------
//
// �Q�[�g�����̐���[gate.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _GATE_H_
#define _GATE_H_	 // �t�@�C������������߂�

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
class CGate : public CScene_THREE
{
public:
	/* �񋓌^ */
	// �^�C�v
	typedef enum
	{
		TYPE_TURN_R = 0,	// �E��] ��
		TYPE_TURN_L,		// ����] ��O
		TYPE_MAX
	} TYPE;

	typedef enum
	{
		USETYPE_TITLE = 0,	// �^�C�g���Ŏg��
		USETYPE_GAME,		// �Q�[���Ŏg��
		USETYPE_MAX
	} USETYPE;

	/* �֐� */
	CGate();
	~CGate();
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
	static CGate * Create();							// �쐬
	static void LoadCreate(void);						// �A�C�e������
	static HRESULT Load(void);							// �ǂݍ���
	static void UnLoad(void);							// �j��
	static CLoad *GetLoad(void);						// ���[�h�擾
protected:
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];		// �e�N�X�`���ւ̃|�C���^
	static CLoad	*m_pload;		// ���[�h
	static int		m_nAll;			// �ԍ�
	D3DXMATRIX		m_mtxWorld;		// ���[���h�}�g���b�N�X
	TYPE			m_Type;			// �^�C�v
	USETYPE			m_UseType;
};
#endif