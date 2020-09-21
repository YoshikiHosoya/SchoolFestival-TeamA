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
		ITEMTYPE_GOLDCOIN,			// ����
		ITEMTYPE_SILVERCOIN,		// ���
		ITEMTYPE_BRONZESCOIN,		// ����
		ITEMTYPE_DIAMOND,			// �_�C�A�����h
		ITEMTYPE_BEAR,				// �F
		ITEMTYPE_LETTER,			// �莆
		ITEMTYPE_APPLE,				// �����S
		ITEMTYPE_MELON,				// ������
		ITEMTYPE_BANANA,			// �o�i�i
		ITEMTYPE_MEAT,				// ��
		ITEMTYPE_RICEBALL,			// ���ɂ���
		ITEMTYPE_CANDY,				// ��
		ITEMTYPE_DONUT,				// �h�[�i�c
		ITEMTYPE_LOLIPOP,			// �����|�b�v
		ITEMTYPE_BREAD,				// �p��
		ITEMTYPE_CHOCOLATE,			// �`���R���[�g
		ITEMTYPE_ICE,				// �A�C�X

		// ------ �`���[�W ------ //
		ITEMTYPE_BOMBUP,			// ���e�̐��𑝂₷
		ITEMTYPE_BULLETUP,			// �n���h�K���ȊO�̒e�̎c�e���𑝂₷

		ITEMTYPE_MAX				// �ő�
	};

	// �A�C�e���͈̔�
	enum ITEMDROP
	{
		ITEMDROP_NONE = -1,			// �h���b�v���Ȃ�
		ITEMDROP_WEAPON,			// ����n
		ITEMDROP_SCORE,				// �X�R�A�n
		ITEMDROP_CHARGE,			// �e��n

		ITEMDROP_SCO_CHA,			// �e��ƃX�R�A�A�b�v

		ITEMDROP_FRUIT,				// �X�R�A�A�b�v_�t���[�c
		ITEMDROP_COIN,				// �X�R�A�A�b�v_�R�C��
		ITEMDROP_RARE,				// �X�R�A�A�b�v_���A
		ITEMDROP_FOOD,				// �H�ו�
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

	// �A�C�e�����h���b�v���鎞�̋���
	enum ITEM_BEHAVIOR
	{
		BEHAVIOR_NONE = -1,	// �����Ȃ�
		BEHAVIOR_FREEFALL,	// ���R����
		BEHAVIOR_BURSTS,	// ������Ƀ����_���ɒe����
	};

	// �܂Ƃ߂ăh���b�v���鎞�̂܂Ƃ܂�̎��
	enum ITEM_LIST_DROPMULTIPLE
	{
		LIST_FRUIT,			// �t���[�c
		LIST_FOOD,			// �H�ו�
		LIST_COIN,			// �R�C��
		LIST_RARE			// ���A�A�C�e�� ���
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
	void						SetMove(D3DXVECTOR3 move);						// �ړ��ʂ̐ݒ�

	/* �ÓI�����o�֐� */
	static	CItem				*DropItem(D3DXVECTOR3 droppos, bool fixed, ITEMTYPE type);	// �L�����N�^�[���A�C�e���𗎂Ƃ����̐���
	static	void				DropItem_Multiple(
		const D3DXVECTOR3 &originpos,
		ITEM_LIST_DROPMULTIPLE type,
		ITEM_BEHAVIOR behavior);												// �A�C�e���𕡐���C�Ƀh���b�v�����鎞


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

	void						DropPattern(bool fixed, ITEMTYPE type);				// �A�C�e���̃h���b�v�p�^�[��
	void						DropPattern_Multiple(
		ITEM_LIST_DROPMULTIPLE list,
		ITEM_BEHAVIOR behavior,
		int nNum);																	// ������C�Ƀh���b�v�����鎞

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

	void						BurstsItem();									// ������C�ɃA�C�e������������鎞�̃A�C�e���̋�������
	void						BounceItem();									// �󒆂ɂ������A�C�e�������ɒ����������˕Ԃ鏈��

	D3DXVECTOR3					RandomDropPosX(const D3DXVECTOR3 &originpos,int radius);//���_����w�肳�ꂽ�w��͈͂�X���W��Ԃ�
	void						SetMultiType(ITEM_LIST_DROPMULTIPLE list);		// �����̂̃^�C�v�ݒ�

	/* �����o�ϐ� */
	CCollision					*m_pCollision;									// �����蔻��
	CPlayer						*m_pPlayer[MAX_CONTROLLER];						// �v���C���[�̃|�C���^

	ITEMTYPE					m_Type;											// �A�C�e���^�C�v
	ITEMDROP					m_Drop;											// �A�C�e�����h���b�v�����鎞�̎��
	ITEM_BEHAVIOR				m_Behavior;										// �A�C�e���̋���
	ITEM_LIST_DROPMULTIPLE		m_MultipleListType;								// �����h���b�v�����鎞�̂܂Ƃ܂�̎��

	int							m_nRemainTime;									// �A�C�e�����}�b�v�Ɏc�鎞��
	int							m_nColCnt;										// ���J���[�J�E���g
	D3DXVECTOR3					m_Move;											// �ړ���
};
#endif