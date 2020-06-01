// ----------------------------------------
//
//	�}�b�v�ɕ\������}�[�N�����̐���[mapmark.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _MAPMARK_H_
#define _MAPMARK_H_	 // �t�@�C������������߂�

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
#define MAX_SHARDMARK (54)
#define TOTAL_MARK (55)
//=============================================================================
// �O���錾
//=============================================================================

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CMapMark : public CScene
{
public:
	/* �񋓌^ */
	typedef enum
	{
		/* �}�b�v��UI��� */
		MAP_MARK_SHARD = 0,								// ���Ђ̈ʒu�������}�[�N
		MAP_MARK_PLAYER,								// �v���C���[�̈ʒu�������}�[�N
		//MAP_MARK_ENEMY,									// �G�̈ʒu�������}�[�N
		MAP_MARK_MAX
	} MAP_MARK_TYPE;

	/* �֐� */
	CMapMark();
	~CMapMark();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMapMark * Create(void);							// �쐬
	static HRESULT Load(void);								// �ǂݍ���
	static void UnLoad(void);								// �j��
	void ReleseMaker(int nId);
	void SetMapMaker(D3DXVECTOR3 pos);

protected:
private:

	/* �֐� */
	void Various(int nCnt);									// ��ޕʏ���
															/* �ϐ� */
	static D3DXVECTOR3		m_pos[TOTAL_MARK];// �ʒu���
	static D3DXVECTOR2		m_size[MAP_MARK_MAX];			// �T�C�Y���
	static D3DXCOLOR		m_col[MAP_MARK_MAX];			// �F
	static MAP_MARK_TYPE	m_type[MAP_MARK_MAX];			// ui�̎��
	CScene_TWO				*m_aScene_Two[TOTAL_MARK];		//
	D3DXVECTOR3				m_move;							// �ړ�
	int						m_nCount;						// ���[�h�Ŏg���J�E���g
	//static D3DXVECTOR3		m_move[TOTAL_MARK];				// �ʒu���
};

#endif
