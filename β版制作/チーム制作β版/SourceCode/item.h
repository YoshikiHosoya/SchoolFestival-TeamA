// =====================================================================================================================================================================
//
// �A�C�e�������̐���[item.h]
// Author : Fujiwara Masato
//
// =====================================================================================================================================================================
#ifndef _ITEM_H_
#define _ITEM_H_	 // �t�@�C������������߂�

// =====================================================================================================================================================================
// �C���N���[�h�t�@�C��
// =====================================================================================================================================================================
#include "scene3D.h"

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// �A�C�e���̃f�[�^
// =====================================================================================================================================================================
typedef struct
{
	int					nDropRate;		// �A�C�e���̃h���b�v��
	int					nDeleteTime;	// �_�ł���܂ł̎���
	int					nFlashTime;		// �_�ł��鎞��
	int					nBearScore;		// �F�̃A�C�e������������̃X�R�A�̒l
	D3DXVECTOR3			CollisionSize;	// �����蔻��̃T�C�Y
}ITEM_DATA;

// =====================================================================================================================================================================
// �O���錾
// =====================================================================================================================================================================
class CCollision;

// =====================================================================================================================================================================
// �A�C�e���N���X
// =====================================================================================================================================================================
class CItem : public CScene3D
{
public:
	/* �񋓌^ */
	// ���
	enum ITEMTYPE
	{
		ITEMTYPE_HEAVYMACHINEGUN,	// �w�r�[�}�V���K��
		ITEMTYPE_SHOTGUN,			// �V���b�g�K��
		ITEMTYPE_LASERGUN,			// ���[�U�[�K��
		ITEMTYPE_ROCKETLAUNCHER,	// ���P�b�g�����`���[
		ITEMTYPE_FLAMESHOT,			// �t���C���V���b�g

		ITEMTYPE_BEAR,				// �F-�X�R�A�A�b�v
		ITEMTYPE_BOMBUP,			// ���e�̐��𑝂₷
		ITEMTYPE_ENERGYUP,			// ��蕨�̑ϋv�l���񕜂���
		ITEMTYPE_BULLETUP,			// �n���h�K���ȊO�̒e�̎c�e���𑝂₷

		ITEMTYPE_MAX
	};

	// �A�C�e���̗p�r
	enum ITEMDROP
	{
		ITEMDROP_WEAPON,			// ���틭��
		ITEMDROP_SCORE,				// �X�R�A�A�b�v
		ITEMDROP_ALL,				// �S��
	};

	// �A�C�e���̃h���b�v�`��
	enum ITEMDROP_PATTERN
	{
		ITEMDROP_PATTERN_DESIGNATE,	// �w�肵�ăh���b�v������
		ITEMDROP_PATTERN_RANDOM,	// �����_���Ńh���b�v������
	};

	/* �֐� */
	CItem(OBJ_TYPE type);														// �R���X�g���N�^
	~CItem();																	// �f�X�g���N�^

	/* �����o�֐� */
	HRESULT						Init();											// ������
	void						Uninit();										// �I��
	void						Update();										// �X�V
	void						Draw();											// �`��
	void						ItemType(ITEMTYPE type);						// �A�C�e���擾���̎�ޕʏ���
	void						DebugInfo();									// �f�o�b�O
	void						HitItem(ITEMTYPE type);							// �A�C�e���擾���̎�ޕʏ���
	ITEMTYPE					GetItemType() { return m_Type; };				// �A�C�e���^�C�v�̎擾
	CCollision					*GetCollision() { return m_pCollision; };		// �����蔻��
	void						SetDropPos(D3DXVECTOR3 &characterpos);			// �A�C�e���𐶐��ʒu��ݒ�
	void						RemainTimer();									// �؍ݎ��Ԃ��v�Z��0�ɂȂ�����폜����
	void						Flashing();										// �_�ŏ���

	/* �ÓI�����o�֐� */
	static	CItem				*DropCreate(
		D3DXVECTOR3 pos,
		ITEMDROP drop,
		ITEMDROP_PATTERN pattern,
		ITEMTYPE type);															// �L�����N�^�[���A�C�e���𗎂Ƃ����̐���
	static	void				SwitchTexture(ITEMTYPE type, CItem *pItem);		// ��ޕʃe�N�X�`���ݒ�
	static	bool				DropRate();										// �A�C�e�����h���b�v����m��
	static	int					ItemRand(int max);								// �����_���ɒl��Ԃ�
	static	void				ItemLoad();										// �A�C�e���̃��[�h
	static	void				SetItemData();									// �A�C�e���̃f�[�^�ݒ�

	/* �����o�֐� */
	ITEMTYPE					RandDropItem(ITEMDROP drop);					// �A�C�e���̎�ނ������_���Ɍv�Z
	ITEMTYPE					RandomRange(ITEMTYPE min, ITEMTYPE max);		// �����_���͈̔͑I��
	void						DropPattern(
		ITEMDROP_PATTERN pattern,
		ITEMDROP drop,
		ITEMTYPE type);															// �A�C�e���̃h���b�v�p�^�[��

protected:
private:
	/* �ÓI�����o�ϐ� */
	static char					*m_ItemFileName;								// �A�C�e���̃t�@�C����
	static ITEM_DATA			m_ItemData;										// �A�C�e���̃f�[�^
	static int					m_nDropRate;									// �h���b�v��
	static int					m_nDeleteTime;									// �A�C�e�����_�ł���܂ł̎���
	static int					m_nFlashTime;									// �A�C�e�����_�ł��鎞��
	static int					m_nBearScore;									// �F�̃A�C�e���̃X�R�A
	static D3DXVECTOR3			m_CollisionSize;								// �����蔻��̑傫��

	/* �����o�֐� */
	uint64_t get_rand_range(uint64_t min_val, uint64_t max_val);				// �����_���֐� �͈�

	/* �����o�ϐ� */
	ITEMTYPE					m_Type;											// �A�C�e���^�C�v
	ITEMDROP					m_Drop;											// �A�C�e�����h���b�v�����鎞�̎��
	D3DXMATRIX					m_mtxWorld;										// ���[���h�}�g���b�N�X
	CCollision					*m_pCollision;									// �����蔻��
	int							m_nRemainTime;									// �A�C�e�����}�b�v�Ɏc�鎞��
	int							m_nColCnt;										// ���J���[�J�E���g
};
#endif