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
#include "scene.h"

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define ITEM_FILE_NUM (2)
#define MULTIPLE_ITEM_NUM (5)// �܂Ƃ߂Đ�������ۂ̐�

// =====================================================================================================================================================================
// �A�C�e���̃f�[�^ ���ʂ̏��
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
class CItem
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

		// ------ �A�j���[�V��������A�C�e�� ------ //
		// ------ �X�R�A ------ //
		ANIM_ITEMTYPE_ROASTCHICKEN,	// ���[�X�g�`�L��
		ANIM_ITEMTYPE_FISH,			// ��
		ANIM_ITEMTYPE_BEAR,			// �F
		ANIM_ITEMTYPE_DOLL,			// �l�`
		ANIM_ITEMTYPE_LETTER,		// �莆

		ANIM_ITEMTYPE_MEDAL,		// ���_��
		ANIM_ITEMTYPE_MEDAL2,		// ���_��2

		ANIM_ITEMTYPE_COIN,			// �R�C��
		ANIM_ITEMTYPE_RUBY,			// ���r�[
		ANIM_ITEMTYPE_SAPPHIRE,		// �T�t�@�C�A
		ANIM_ITEMTYPE_TOPAZ,		// �g�p�[�Y
		// ------ �`���[�W ------ //
		ANIM_ITEMTYPE_PRISONER,		// �ߗ� �c�@�A�b�v

		ANIM_ITEMTYPE_DANCEMONKEY,	// �x��T��
		ANIM_ITEMTYPE_JUMPMONKEY,	// ��ԃT��

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

		ITEMDROP_ANI_NORMAL,		// �A�j���[�V��������A�C�e��
		ITEMDROP_ANI_RARE,			// �A�j���[�V��������A�C�e��
		ITEMDROP_ANI_MONKEY,		// �T��
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
		BEHAVIOR_FULLBURSTS,// �S�����Ƀ����_���ɒe����
	};

	// �܂Ƃ߂ăh���b�v���鎞�̂܂Ƃ܂�̎��
	enum ITEM_LIST_DROPMULTIPLE
	{
		LIST_FRUIT,			// �t���[�c
		LIST_FOOD,			// �H�ו�
		LIST_COIN,			// �R�C��
		LIST_RARE,			// ���A�A�C�e�� ���
		LIST_WEAPON,		// ����
		LIST_SPECIAL,		// �{�X�}�b�v�p�̓��ʂȃA�C�e���p���X�g

		LIST_ANI_NORMAL,	// �A�j���[�V��������A�C�e��
		LIST_ANI_RARE,		// �A�j���[�V��������A�C�e��
		LIST_ANI_MONKEY,	// �T��
	};

	// �֐�
	CItem();																	// �R���X�g���N�^
	~CItem();																	// �f�X�g���N�^

	/* �����o�֐� */
	virtual HRESULT				Init();											// ������
	virtual void				Uninit();										// �I��
	virtual void				Update();										// �X�V
	virtual void				Draw();											// �`��
	virtual void				DebugInfo();									// �f�o�b�O
	virtual	void				SwitchTexture(ITEMTYPE type);					// ��ޕʃe�N�X�`���ݒ�
	virtual	void				Flashing();										// �_�ŏ���
	virtual void				ItemCollision();								// �����蔻��n
	virtual void				ReflectionItem();								// ���ˏ���
	virtual void				RemainTimer();									// �؍ݎ��Ԃ��v�Z��0�ɂȂ�����폜����
	virtual void				HitItem(ITEMTYPE type, TAG Tag);				// �A�C�e���擾���̎�ޕʏ���
	virtual void				ItemAcquisition(ITEMTYPE type, TAG Tag);		// �A�C�e���擾���̎�ޕʏ���

	D3DXVECTOR3					SetPosOld() { return m_PosOld; };				// 1�t���[���O�̍��W��ݒ�
	int							GetRemainTime() const { return m_nRemainTime; };// �A�C�e���̎c�莞�Ԃ��擾

	// --- �ݒ� �擾 --- //
	ITEMTYPE					GetItemType() { return m_Type; };				// �A�C�e���^�C�v�̎擾
	void						SetItemType(ITEMTYPE type) { m_Type = type; };	// �A�C�e���^�C�v�̐ݒ�
	CCollision					*GetCollision() { return m_pCollision; };		// �����蔻��
	void						SetDropPos(D3DXVECTOR3 &characterpos);			// �A�C�e���𐶐��ʒu��ݒ�
	void						SetMove(D3DXVECTOR3 move);						// �ړ��ʂ̐ݒ�
	ITEM_DATA					GetItem_Data() const{ return m_ItemData; };		// �A�C�e���̃f�[�^�̎擾 �Ăяo�����͏��������s��
	void						SetBehavior(ITEM_BEHAVIOR behavior) { m_Behavior = behavior; };// �A�C�e���̋����̐ݒ�
	ITEM_BEHAVIOR				GetBehavior() { return m_Behavior; };			// �A�C�e���̋����̐ݒ�
	CPlayer						*GetPlayer(int nCnt) { return m_pPlayer[nCnt]; };	// �A�C�e���̋����̐ݒ�

	/* �ÓI�����o�֐� */
	static ITEMTYPE				RandomWeapon();									// ����̃����_��
	static ITEMTYPE				ItemRandomRange(ITEMTYPE min, ITEMTYPE max);	// �����_���͈̔͑I��

	static bool					DropRate();										// �A�C�e�����h���b�v�����邩�̃t���O��Ԃ�
	static bool					DecideIfItemDrop(int nRate);					// �h���b�v�������ɃA�C�e�����h���b�v���邩�����߂Č��ʂ�Ԃ�
	static uint64_t				GetRandRange(uint64_t min_val, uint64_t max_val);// �����_���֐� �͈�
	static void					InitVariable();									// �ÓI�ϐ��̏�����
	static void					ItemLoad();										// �A�C�e���̏��̓ǂݍ���
	static void					DebugItemCommand(CKeyboard *key);				// �f�o�b�O�p�A�C�e���R�}���h

	/* �����o�֐� */
	ITEMTYPE					RandDropItem(ITEMDROP drop);						// �A�C�e���̎�ނ������_���Ɍv�Z
	ITEM_RARITY					RarityRandomRange(ITEM_RARITY min, ITEM_RARITY max);// �����_���͈̔͑I��

	void						DropPattern(bool fixed, ITEMTYPE type);				// �A�C�e���̃h���b�v�p�^�[��
	void						DropPattern_Multiple(
		ITEM_LIST_DROPMULTIPLE list,
		ITEM_BEHAVIOR behavior,
		int nNum);																	// ������C�Ƀh���b�v�����鎞

	void						BehaviorType(D3DXVECTOR3 &pos);						// �A�C�e���̋����̎�ނ��Ƃ̏���
protected:
	/* �����o�֐� */

	ITEMTYPE					BoxRand();										// �{�b�N�X����
	void						SetMultiType(ITEM_LIST_DROPMULTIPLE list);		// �����̂̃^�C�v�ݒ�
	D3DXVECTOR3					RandomDropPosX(const D3DXVECTOR3 originpos, int radius);//���_����w�肳�ꂽ�w��͈͂�X���W��Ԃ�

	D3DXVECTOR3					*ReflectingVectorCalculation(					// ���˃x�N�g�������߂�
		D3DXVECTOR3 *outV,
		const D3DXVECTOR3 &ProgressV,
		const D3DXVECTOR3 &Normal);


	/* �����o�ϐ� */
	D3DXVECTOR3					m_PosOld;										// 1�t���[���O�̍��W
	float						m_fGravity;										// �d��
	int							m_nHitRayCount;									// ���C�̔���ɐG�ꂽ��
	D3DXVECTOR3					m_Move;											// �ړ���
	int							m_nColCnt;										// ���J���[�J�E���g

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
	void						SetBoxRandDataList();							// �{�b�N�X�����̕ꐔ��0�ȉ��ɂȂ��������e�����Z�b�g����
	static void					AddBoxRandList();								// �A�C�e���̃��A���e�B�ƕꐔ�����Ƀ����_���ȃ��X�g�𐶐�����
	void						BurstsItem();									// ������C�ɃA�C�e������������鎞�̃A�C�e���̋�������
	void						BounceItem();									// �󒆂ɂ������A�C�e�������ɒ����������˕Ԃ鏈��

	/* �����o�ϐ� */
	CCollision					*m_pCollision;									// �����蔻��
	CPlayer						*m_pPlayer[MAX_CONTROLLER];						// �v���C���[�̃|�C���^
	ITEMTYPE					m_Type;											// �A�C�e���^�C�v
	ITEMDROP					m_Drop;											// �A�C�e�����h���b�v�����鎞�̎��
	ITEM_BEHAVIOR				m_Behavior;										// �A�C�e���̋���
	ITEM_LIST_DROPMULTIPLE		m_MultipleListType;								// �����h���b�v�����鎞�̂܂Ƃ܂�̎��
	int							m_nRemainTime;									// �A�C�e�����}�b�v�Ɏc�鎞��
};
#endif