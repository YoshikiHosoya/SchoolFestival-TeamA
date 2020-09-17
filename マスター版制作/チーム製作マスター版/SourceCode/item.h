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
#define ITEM_FILE_NUM (2)
// =====================================================================================================================================================================
// �A�C�e���̃f�[�^
// =====================================================================================================================================================================
struct ITEM_DATA
{
	int					nDropRate;		// �A�C�e���̃h���b�v��
	int					nDeleteTime;	// �_�ł���܂ł̎���
	int					nFlashTime;		// �_�ł��鎞��
	D3DXVECTOR3			CollisionSize;	// �����蔻��̃T�C�Y
	unsigned int		Rarity[12];		// �S�A�C�e���̃��A���e�B[��1���灚3�܂�]
};
// =====================================================================================================================================================================
// �A�C�e���K�`���̃f�[�^
// =====================================================================================================================================================================
struct ITEM_GACHA
{
	unsigned int BoxRand_TotalNum;					// �{�b�N�X�����̕ꐔ
	unsigned int BoxRandDefault_RarityNum[3];		// �{�b�N�X�����̃f�t�H���g�̃��A���e�B�̐�
};
// =====================================================================================================================================================================
// �O���錾
// =====================================================================================================================================================================
class CCollision;
class CPlayer;

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
		ITEMTYPE_NONE = -1,			// ���I��
		// ------ ���� ------ //
		ITEMTYPE_HEAVYMACHINEGUN,	// �w�r�[�}�V���K��
		ITEMTYPE_SHOTGUN,			// �V���b�g�K��
		ITEMTYPE_LASERGUN,			// ���[�U�[�K��
		ITEMTYPE_ROCKETLAUNCHER,	// ���P�b�g�����`���[
		ITEMTYPE_FLAMESHOT,			// �t���C���V���b�g

		// ------ �X�R�A ------ //
		ITEMTYPE_BEAR,				// �F
		ITEMTYPE_COIN,				// �R�C��
		ITEMTYPE_JEWELRY,			// ���
		ITEMTYPE_MEDAL,				// ���_��

		// ------ �`���[�W ------ //
		ITEMTYPE_BOMBUP,			// ���e�̐��𑝂₷
		ITEMTYPE_ENERGYUP,			// ��蕨�̑ϋv�l���񕜂���
		ITEMTYPE_BULLETUP,			// �n���h�K���ȊO�̒e�̎c�e���𑝂₷

		ITEMTYPE_MAX
	};

	// �A�C�e���͈̔�
	enum ITEMDROP
	{
		ITEMDROP_NONE = -1,			// �h���b�v���Ȃ�
		ITEMDROP_WEAPON,			// ����n
		ITEMDROP_SCORE,				// �X�R�A�A�b�v
		ITEMDROP_CHARGE,			// �e��Ȃ�
		ITEMDROP_WEA_SCO,			// ���틭���ƃX�R�A�A�b�v
		ITEMDROP_ALL,				// �S��
	};

	// �A�C�e���̃h���b�v�`��
	enum ITEMDROP_PATTERN
	{
		ITEMDROP_PATTERN_NONE = -1,	// �������Ȃ�
		ITEMDROP_PATTERN_DESIGNATE,	// �w�肵�ăh���b�v������
		ITEMDROP_PATTERN_RANDOM,	// �����_���Ńh���b�v������
	};

	// �A�C�e���̃��A���e�B_���������قǃ��A���e�B������
	enum ITEM_RARITY
	{
		ITEM_RARITY_STAR_1,	// ��
		ITEM_RARITY_STAR_2,	// ����
		ITEM_RARITY_STAR_3,	// ������
		ITEM_RARITY_TOTAL	// ����
	};

	/* �֐� */
	CItem(OBJ_TYPE type);														// �R���X�g���N�^
	~CItem();																	// �f�X�g���N�^

	/* �����o�֐� */
	HRESULT						Init();											// ������
	void						Uninit();										// �I��
	void						Update();										// �X�V
	void						Draw();											// �`��
	void						DebugInfo();									// �f�o�b�O

	void						ItemAcquisition(ITEMTYPE type, TAG Tag);		// �A�C�e���擾���̎�ޕʏ���
	void						HitItem(ITEMTYPE type, TAG Tag);				// �A�C�e���擾���̎�ޕʏ���
	void						RemainTimer();									// �؍ݎ��Ԃ��v�Z��0�ɂȂ�����폜����
	void						Flashing();										// �_�ŏ���

	ITEMTYPE					GetItemType() { return m_Type; };				// �A�C�e���^�C�v�̎擾
	CCollision					*GetCollision() { return m_pCollision; };		// �����蔻��
	void						SetDropPos(D3DXVECTOR3 &characterpos);			// �A�C�e���𐶐��ʒu��ݒ�

	/* �ÓI�����o�֐� */
	static	CItem				*DropItem(
		D3DXVECTOR3 pos,
		ITEMDROP drop,
		ITEMDROP_PATTERN pattern,
		ITEMTYPE type);															// �L�����N�^�[���A�C�e���𗎂Ƃ����̐���


	static	CItem				*DropCreate_TEST();								// �e�X�g�p�N���G�C�g����


	static	void				SwitchTexture(ITEMTYPE type, CItem *pItem);		// ��ޕʃe�N�X�`���ݒ�
	static	bool				DropRate();										// �A�C�e�����h���b�v�����邩�̃t���O��Ԃ�
	static	bool				DecideIfItemDrop(int nRate);					// �h���b�v�������ɃA�C�e�����h���b�v���邩�����߂Č��ʂ�Ԃ�
	static	uint64_t			GetRandRange(uint64_t min_val, uint64_t max_val);// �����_���֐� �͈�

	static	void				InitVariable();									// �ÓI�ϐ��̏�����
	static	void				ItemLoad();										// �A�C�e���̏��̓ǂݍ���
	static  void				DebugItemCommand(CKeyboard *key);				// �f�o�b�O�p�A�C�e���R�}���h

	/* �����o�֐� */
	ITEMTYPE					RandDropItem(ITEMDROP drop);						// �A�C�e���̎�ނ������_���Ɍv�Z
	ITEMTYPE					ItemRandomRange(ITEMTYPE min, ITEMTYPE max);		// �����_���͈̔͑I��
	ITEM_RARITY					RarityRandomRange(ITEM_RARITY min, ITEM_RARITY max);// �����_���͈̔͑I��

	void						DropPattern(
		ITEMDROP_PATTERN pattern,
		ITEMDROP drop,
		ITEMTYPE type);															// �A�C�e���̃h���b�v�p�^�[��

protected:
private:
	/* �ÓI�����o�֐� */
	static CItem				*DebugCreate(ITEMTYPE type);					// �f�o�b�O�p�A�C�e������
	static void					SetRarityList();								// ���A���e�B�̐���
	static ITEMTYPE				ItemWhichOnePick(std::vector<std::vector<CItem::ITEMTYPE>> list,int line);	// ���X�g�̒�����1��I��

	/* �ÓI�����o�ϐ� */
	static char					*m_ItemFileName;								// �A�C�e���̃t�@�C����

	static ITEM_DATA			m_ItemData;										// �A�C�e���̃f�[�^
	static ITEM_GACHA			m_ItemGachaData;								// �A�C�e���K�`���̃f�[�^
	static int					m_nAddCoin;										// �R�C���̉��Z�p

	// --- �A�C�e���K�`�� --- //
	static std::vector<unsigned int>	m_nSaveHitItem;							// ���S�����ŃA�C�e�����h���b�v���������̌��ʂ�ۑ�
	static std::vector<ITEM_RARITY>		m_nBoxRandRarityDataList;				// �{�b�N�X�����Ŏg���A�C�e���̃��A���e�B�̈ꗗ��ۑ�

	static std::vector<ITEM_RARITY>		m_nDefaultRarityList;					// �擾���������灚�����̏����܂Ƃ߂ĕۑ�����
	static std::vector<std::vector<ITEMTYPE>> m_nBoxRandDefaultRarityData;		// �f�t�H���g�̃{�b�N�X�����p�̃��A���e�B���Ƃ̃A�C�e���̎��

	/* �����o�֐� */
	int							AddCoinScore(int nScore);						// �R�C���̃X�R�A���v�Z�����ʂ�Ԃ�

	ITEMTYPE					FullRand();										// ���S���� // ������
	ITEMTYPE					BoxRand();										// �{�b�N�X����

	void						SetBoxRandDataList();							// �{�b�N�X�����̕ꐔ��0�ȉ��ɂȂ��������e�����Z�b�g����
	static void					AddBoxRandList();								// �A�C�e���̃��A���e�B�ƕꐔ�����Ƀ����_���ȃ��X�g�𐶐�����

	/* �����o�ϐ� */
	CCollision					*m_pCollision;									// �����蔻��
	CPlayer						*m_pPlayer[MAX_CONTROLLER];						// �v���C���[�̃|�C���^

	ITEMTYPE					m_Type;											// �A�C�e���^�C�v
	ITEMDROP					m_Drop;											// �A�C�e�����h���b�v�����鎞�̎��
	int							m_nRemainTime;									// �A�C�e�����}�b�v�Ɏc�鎞��
	int							m_nColCnt;										// ���J���[�J�E���g
};
#endif