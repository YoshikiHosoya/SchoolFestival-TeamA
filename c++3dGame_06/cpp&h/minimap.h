// ----------------------------------------
//
// �~�j�}�b�v�����̐���[minimap.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _MINIMAP_H_
#define _MINIMAP_H_	 // �t�@�C������������߂�

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
class CMinimap : public CScene_TWO
{
public:
	/* �񋓌^ */
	typedef enum
	{
		/* �~�j�}�b�v��UI��� */
		MINIMAP_UI_MAP = 0,									//�}�b�v�{��
		MINIMAP_UI_SHARD_POS,								//���Ђ̍��W
		MINIMAP_UI_ENEMY_POS,								//�G�l�~�[�̍��W
		MINIMAP_UI_PLAYER_POS,								//�v���C���[�̍��W
		MINIMAP_UI_FRAME,									//�O�g
		MINIMAP_UI_MISSION00,								//���݂̖ړI��\��(���Ђ�S�ďW�߂�)
		MINIMAP_UI_MISSION01,								//���݂̖ړI��\��(�S�[����ڎw��)
		MINIMAP_UI_MAX
	} MINIMAP_UI_TYPE;

	/* �֐� */
	CMinimap();
	~CMinimap();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTexture(MINIMAP_UI_TYPE type);					// �e�N�X�`���[�ݒ�
	void SetSize(D3DXVECTOR2 size);							// �T�C�Y�ݒ�
	void SetPos(D3DXVECTOR3 pos);							// �ʒu�ݒ�
	void SetRot(float rot);									// ��]�ݒ�
	void SetCol(D3DXCOLOR col);								// �F�ݒ�
	void SetTex(D3DXVECTOR2 first, D3DXVECTOR2 last);		// �\���e�N�X�`���[�ݒ�
	D3DXVECTOR2 GetSize(void);								// �T�C�Y�擾
	D3DXVECTOR3 GetPos(void);								// �ʒu�擾

	void TexRange(void);
	void MAP_MOVE(void);

	void ExceptUI(void);									// �������炷

	static CMinimap * Create(void);							// �쐬
	static void CMinimap::LoadCreate(void);					// �ǂݍ��񂾂��̂𐶐�
	static HRESULT Load(void);								// �ǂݍ���
	static void UnLoad(void);								// �j��
	static CLoad2D *GetLoad(void);							// ���[�h�擾
protected:
private:
	/* �񋓌^ */
	typedef enum
	{
		/* �~�j�}�b�v��UI��� */
		MINIMAP_STATE_NORMAL = 0,							//�~�j�}�b�v�̏��
		MINIMAP_STATE_ALLMAP,								//�}�b�v�̑S�̕\�����
		MINIMAP_STATE_MAX
	} MINIMAP_STATE;

	/* �֐� */
	void Various(int nCnt);									// ��ޕʏ���

	/* �ϐ� */
	static LPDIRECT3DTEXTURE9 m_pTexture[MINIMAP_UI_MAX];	// �e�N�X�`���[�ݒ�
	static CLoad2D		*m_pload2D;							// ���[�h
	static int			m_nAll;								// ����
	float	m_fMult;										// �{��
	float	m_fAdd;											// ���Z
	int		m_nRange;										// �`�悷�镝
	MINIMAP_STATE m_state;
	MINIMAP_UI_TYPE m_type;
	float	m_rot;											//�~�j�}�b�v�̉�]
	D3DXVECTOR3 m_pos;										//���ЂƃG�l�~�[�̍��W
	D3DXVECTOR3 m_move;										//���ЂƃG�l�~�[�̍��W

	D3DXVECTOR2	m_TexFirstMove;
	D3DXVECTOR2	m_TexLastMove;

	D3DXVECTOR2	m_TexFirst;									//�~�j�}�b�v�̃e�N�X�`�����W
	D3DXVECTOR2	m_TexLast;									//�~�j�}�b�v�̃e�N�X�`�����W
	//D3DXVECTOR3 m_tex;
};

#endif
