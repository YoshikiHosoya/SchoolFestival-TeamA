// ----------------------------------------
//
// ���b�V���h�[�������̐���[meshdome.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _MESHDOME_H_
#define _MESHDOME_H_	 // �t�@�C������������߂�

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "scene.h"

// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------


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
class CMeshdome : public CScene
{
public:
	/* �񋓌^ */
	typedef enum
	{
		TYPE_NORMAL,
		TYPE_WAVE,
		TYPE_START,
		TYPE_GOAL,
		TYPE_MAX
	} TYPE;
	/* �֐� */
	CMeshdome();
	~CMeshdome();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void UnLoad(void);
	static CMeshdome * Create(		// �쐬
		D3DXVECTOR3 pos,
		D3DXVECTOR3 size,
		D3DXVECTOR3 rot,
		D3DXCOLOR	col,
		int nWidth,
		int nDepth,
		TYPE type
	);
	void SetCol(D3DXCOLOR col);	// �F���
protected:

private:
	/* �֐� */
	void MakeVertex(LPDIRECT3DDEVICE9 pDevice);	// ���_���W�̐���
	/* �ϐ� */
	static LPDIRECT3DTEXTURE9 m_pTex[TYPE_MAX];
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9	m_pIndex;	// �C���f�b�N�X�o�b�t�@�̃|�C���^
	D3DXVECTOR3 m_OriginBlock;			// �����z�u
	D3DXMATRIX  m_mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_size;					// �T�C�Y
	D3DXVECTOR3 m_rot;					// �p�x
	D3DXCOLOR	m_col;					// �F
	int	m_nNumberVertex;				// �����_��
	int m_nNumIndex;					// ���C���f�b�N�X
	int m_nNumPolygon;					// ���|���S��
	int m_nBlock_Depth;					// �c�u���b�N��
	int m_nBlock_Width;					// ���u���b�N��
	TYPE m_type;							// �^�C�v
};

#endif