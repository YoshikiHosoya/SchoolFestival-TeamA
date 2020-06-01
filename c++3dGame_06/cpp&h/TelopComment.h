// ----------------------------------------
//
// �e���b�v�R�����g�����̐���[TelopComment.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _TELOPCOMMENT_H_
#define _TELOPCOMMENT_H_	 // �t�@�C������������߂�

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
#define TELOP_POS (D3DXVECTOR3(640.0f, 590, 0.0f))
#define TELOP_SIZE (D3DXVECTOR2(520.0f, 40.0f))

// ----------------------------------------
//
// �O���錾
//
// ----------------------------------------

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CTelopComment : public CScene_TWO
{
public:

	typedef enum
	{
		TYPE_0 = 0,
		TYPE_1,
		TYPE_2,
		TYPE_3,
		TYPE_4,
		TYPE_MAX
	} TYPE;

	typedef enum
	{
		PHASE_NONE = 0,
		PHASE_ONE,
		PHASE_TWO,
		PHASE_THREE,
		PHASE_FOUR,
		PHASE_FIVE,
		PHASE_END
	} PHASE;

	typedef enum
	{
		STATE_EMERGENCE = 0,				// �o��
		STATE_DISAPPEARANCE					// ����
	} STATE;

	/* �֐� */
	CTelopComment();
	~CTelopComment();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);						// �ǂݍ���
	static void UnLoad(void);						// UnLoad����

	static CTelopComment * Create(D3DXVECTOR3 pos,
								D3DXVECTOR2 size,
								TYPE type);			// �쐬

	static void CreateTelopCommnet(PHASE phase);				// �쐬

	void Transparency(STATE state);					// ������
	static void SetPhase(void);						// ���̒i�K��
	static void Phase(void);						// �e�i�K�̏���
	static bool GetEndPhaseFlag(void);				// �t���O�̎擾
	static PHASE GetPhase(void);					// ���݂̃t�F�C�Y�̎擾

protected:

private:

	/* �ϐ� */
	static LPDIRECT3DTEXTURE9	m_pTexture[TYPE_MAX];	// �e�N�X�`���[�ݒ�
	D3DXCOLOR					m_col;					// �J���[
	D3DXVECTOR3					m_pos;					// ���W
	D3DXVECTOR2					m_size;					// �傫��
	static PHASE				m_phase;				// �i�K
	static bool					bEndPhase;				// �R�����g��S�ď����������̔���
	static int					m_nCreateCount;			//���������܂ł̎���
	bool						bDisFlag;				//���Ńt���O
};

#endif
