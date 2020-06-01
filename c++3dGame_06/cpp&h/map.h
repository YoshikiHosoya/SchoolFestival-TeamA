// ----------------------------------------
//
//	�}�b�v�����̐���[map.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _MAP_H_
#define _MAP_H_	 // �t�@�C������������߂�

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

//=============================================================================
// �O���錾
//=============================================================================

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CMap : public CScene
{
public:
	/* �񋓌^ */
	typedef enum
	{
		/* �~�j�}�b�v��UI��� */
		MAP_UI_MAP = 0,									//�}�b�v�{��
		MAP_UI_FRAME,									//�O�g
		MAP_UI_MISSION00,								//���݂̖ړI��\��(���Ђ�S�ďW�߂�)
		MAP_UI_MAX
	} MAP_UI_TYPE;

	/* �֐� */
	CMap();
	~CMap();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CMap * Create(void);								// �쐬
	static HRESULT Load(void);								// �ǂݍ���
	static void UnLoad(void);								// �j��
protected:
private:
	static LPDIRECT3DTEXTURE9 m_pTex[MAP_UI_MAX];			// �e�N�X�`���[�ݒ�
	static D3DXVECTOR3 m_pos[MAP_UI_MAX];					// �ʒu���
	static D3DXVECTOR2 m_size[MAP_UI_MAX];					// �T�C�Y���
	static MAP_UI_TYPE m_type[MAP_UI_MAX];					// ui�̎��
	CScene_TWO *m_aScene_Two[MAP_UI_MAX];					// �|�[�Y�pui2D
};

#endif
