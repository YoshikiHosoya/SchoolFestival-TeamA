// ----------------------------------------
//
// �Ǐ����̐���[wall.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _WALL_H_
#define _WALL_H_	 // �t�@�C������������߂�

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "scene_X.h"

// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
#define MAX_WALLTEXTURE (2)
//=============================================================================
// �O���錾
//=============================================================================

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CWall : public CScene_X
{
public:
	/* �񋓌^ */
	typedef enum
	{//*1�� 300*300*0
		SIZE_I = 0,								// 1�����̑傫��
		SIZE_II,								// 2�����̑傫��
		SIZE_III,								// 3�����̑傫��
		SIZE_IV,								// 4�����̑傫��
		SIZE_V,									// 5�����̑傫��
		SIZE_VI,								// 6�����̑傫��
		SIZE_VII,								// 7�����̑傫��
		SIZE_VIII,								// 8�����̑傫��
		SIZE_IX,								// 9�����̑傫��
		SIZE_X,									// 10�����̑傫��
		SIZE_XV,								// 15�����̑傫��
		SIZE_XXI,								// 21�����̑傫��
		TYPE_MAX,
	} SIZE;

	/* �֐� */
	CWall();
	~CWall();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos);				// �ʒu�ݒ�
	void SetRot(D3DXVECTOR3 rot);				// ��]�ݒ�
	D3DXVECTOR3 GetPos(void);					// �ʒu�擾
	static CWall * Create(	D3DXVECTOR3 pos,
							D3DXVECTOR3 rot,
							SIZE type);			// �쐬
	static void CWall::LoadCreate(void);		// �ǂݍ��񂾂��̂𐶐�
	static HRESULT Load(void);					// �ǂݍ���
	static void UnLoad(void);					// �j��
protected:
private:
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_WALLTEXTURE];	// �e�N�X�`���ւ̃|�C���^
	static CLoad				*m_pload;		// ���[�h
	static CModel_info			*m_pmodel_info;	// ���f�����
	static int					m_nAll;			// ����
	SIZE						m_type;			// ���
	//D3DXVECTOR3					m_pos;			// ���W
	//D3DXVECTOR3					m_rot;			// ��]
};

#endif