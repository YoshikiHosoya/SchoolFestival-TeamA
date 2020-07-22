// =====================================================================================================================================================================
//
// �A�C�e�������̐���[item.cpp]
// Author : Fujiwara Masato
//
// =====================================================================================================================================================================
#include "item.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "collision.h"
#include "debugproc.h"
#include "player.h"
#include "playerui.h"
#include "gun.h"
#include <random>
#include "inputKeyboard.h"

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
ITEM_DATA	CItem::m_ItemData		 = {};
int			CItem::m_nDropRate		 = 0;
int			CItem::m_nDeleteTime	 = 0;
int			CItem::m_nFlashTime		 = 0;
int			CItem::m_nBearScore		 = 0;
int			CItem::m_nCoinScore		 = 0;
int			CItem::m_nJewelryScore	 = 0;
int			CItem::m_nMedalScore	 = 0;
D3DXVECTOR3 CItem::m_CollisionSize	 = D3DXVECTOR3(0,0,0);
int			CItem::m_nAddCnt		 = 0;
// =====================================================================================================================================================================
// �e�L�X�g�t�@�C����
// =====================================================================================================================================================================
char *CItem::m_ItemFileName =
{
	"data/Load/Item/ItemData.txt" 			// �A�C�e���̏��
};

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CItem::CItem(OBJ_TYPE type) :CScene3D(type)
{
	// �����蔻��̃|�C���^
	m_pCollision = nullptr;

	// �A�C�e�����}�b�v�Ɏc�鎞��
	m_nRemainTime = m_nDeleteTime;

	// ���J���[�J�E���g
	m_nColCnt = 0;

	// �A�C�e���̎��
	m_Type = ITEMTYPE_HEAVYMACHINEGUN;

	// �A�C�e�����h���b�v��������
	m_Drop = ITEMDROP_WEAPON;
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CItem::~CItem()
{
	// �����蔻��̍폜
	if (m_pCollision != nullptr)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
HRESULT CItem::Init()
{
	// ������
	CScene3D::Init();

	// �����蔻�萶��
	m_pCollision = CCollision::Create();
	m_pCollision->SetPos(&GetPosition());
	m_pCollision->SetSize2D(m_CollisionSize);
	m_pCollision->DeCollisionCreate(CCollision::COLLISIONTYPE_NORMAL);

	return S_OK;
}

// =====================================================================================================================================================================
//
// �I������
//
// =====================================================================================================================================================================
void CItem::Uninit(void)
{
	// �I������
	CScene3D::Uninit();
}

// =====================================================================================================================================================================
//
// �X�V����
//
// =====================================================================================================================================================================
void CItem::Update(void)
{
	// �����蔻��
	if (m_pCollision != nullptr)
	{
		// ���W�̍X�V pos
		m_pCollision->SetPos(&GetPosition());
	}

	// �A�C�e���̑؍ݎ��ԊǗ�
	RemainTimer();

	// �X�V
	CScene3D::Update();
}

// =====================================================================================================================================================================
//
// �`�揈��
//
// =====================================================================================================================================================================
void CItem::Draw(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =									// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();

	// �A���t�@�e�X�g�̐ݒ�ɕύX
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// �A���t�@�e�X�g�L��
	pDevice->SetRenderState(D3DRS_ALPHAREF, 200);				// �A���t�@�l�̊�ݒ�(����傫���ƕ`�悷��)
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// �󋵂ɉ����ăA���t�@�e�X�g�����s����(�V�s�N�Z�� > ���݂̃s�N�Z��)
	pDevice->SetRenderState(D3DRS_LIGHTING, false);				// ���C�e�B���Ooff
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// �r���{�[�h
	// �r���[�}�g���b�N�X�̑���p
	D3DXMATRIX mtxView;
	// ���݂̃r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// �r���{�[�h����
	CHossoLibrary::SetBillboard(&mtxView);

	// �`��
	CScene3D::Draw();

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	// �A���t�@�e�X�g�̐ݒ��߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		// �A���t�@�e�X�g����
	pDevice->SetRenderState(D3DRS_LIGHTING, true);				// ���C�e�B���Oon
}

// =====================================================================================================================================================================
//
// �A�C�e���擾���̎�ޕʏ���
//
// =====================================================================================================================================================================
void CItem::ItemType(ITEMTYPE type)
{
	// �v���C���[�̃|�C���^���擾
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();

	// �A�C�e���̎�ނ��Ƃ̏���
	switch (type)
	{
		// �w�r�[�}�V���K��
	case (ITEMTYPE_HEAVYMACHINEGUN): {
		pPlayer->GetGun()->SetGunType(CGun::GUNTYPE_HEAVYMACHINEGUN);
	}break;

		// �V���b�g�K��
	case (ITEMTYPE_SHOTGUN): {
		pPlayer->GetGun()->SetGunType(CGun::GUNTYPE_SHOTGUN);
	}break;

		// ���[�U�[�K��
	case (ITEMTYPE_LASERGUN): {
		pPlayer->GetGun()->SetGunType(CGun::GUNTYPE_LASERGUN);
	}break;

		// ���P�b�g�����`���[
	case (ITEMTYPE_ROCKETLAUNCHER): {
		pPlayer->GetGun()->SetGunType(CGun::GUNTYPE_ROCKETLAUNCHER);
	}break;

		// �t���C���V���b�g
	case (ITEMTYPE_FLAMESHOT): {
		pPlayer->GetGun()->SetGunType(CGun::GUNTYPE_FLAMESHOT);
	}break;

		// �F
	case (ITEMTYPE_BEAR): {
		// �X�R�A�A�b�v
		pPlayer->GetPlayerUI()->SetScore(m_nBearScore);
	}break;

		// �R�C��
	case (ITEMTYPE_COIN): {
		// �R�C������邽�тɃR�C���̃X�R�A�A�b�v
		pPlayer->GetPlayerUI()->SetScore(AddCoinScore(m_nCoinScore));
	}break;
		// ���
	case (ITEMTYPE_JEWELRY): {
		// �X�R�A�A�b�v
		pPlayer->GetPlayerUI()->SetScore(m_nJewelryScore);
	}break;
		// ���_��
	case (ITEMTYPE_MEDAL): {
		// �X�R�A�A�b�v
		pPlayer->GetPlayerUI()->SetScore(m_nMedalScore);
	}break;

		// ���e�̐��𑝂₷
	case (ITEMTYPE_BOMBUP): {
	}break;

		// ��蕨�̑ϋv�l���񕜂���
	case (ITEMTYPE_ENERGYUP): {
	}break;

		// �n���h�K���ȊO�̒e�̎c�e���𑝂₷
	case (ITEMTYPE_BULLETUP): {
	}break;

	default:
		break;
	}
}
// =====================================================================================================================================================================
//
// �f�o�b�O
//
// =====================================================================================================================================================================
void CItem::DebugInfo()
{
}

// =====================================================================================================================================================================
//
// �A�C�e������������������
//
// =====================================================================================================================================================================
void CItem::HitItem(ITEMTYPE type)
{
	// ��ނ��Ƃ̏���
	ItemType(type);
	// �폜
	Rerease();
}

// =====================================================================================================================================================================
//
// �A�C�e���𗎂Ƃ��ʒu�̐ݒ�
//
// =====================================================================================================================================================================
void CItem::SetDropPos(D3DXVECTOR3 &characterpos)
{
	// �v���C���[�̃|�C���^�擾
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
	// �v���C���[�����݂�����
	if (pPlayer != nullptr)
	{
		// �v���C���[�̌������擾
		if (pPlayer->GetCharacterDirection() == CPlayer::CHARACTER_LEFT)
		{
			characterpos.x -= 50;
		}
		else if(pPlayer->GetCharacterDirection() == CPlayer::CHARACTER_RIGHT)
		{
			characterpos.x += 50;
		}

		characterpos.y += 50;
	}
}

// =====================================================================================================================================================================
//
// �؍ݎ��Ԃ��v�Z��0�ɂȂ�����폜����
//
// =====================================================================================================================================================================
void CItem::RemainTimer()
{
	// �A�C�e���̑؍ݎ��Ԃ�����
	m_nRemainTime--;

	// �c�莞�Ԃ�0�ȉ��ɂȂ�����폜
	if (m_nRemainTime <= 0)
	{
		// �_�ł�����
		Flashing();
	}
}

// =====================================================================================================================================================================
//
// �_�ŏ���
//
// =====================================================================================================================================================================
void CItem::Flashing()
{
	// �J�E���g���Z
	m_nColCnt++;
	// �]�肪0�̎������ɂ���
	if (m_nColCnt % 30 == 0)
	{
		this->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}
	// �]�肪0�̎��ʏ��Ԃɂ���
	else if(m_nColCnt % 15 == 0)
	{
		this->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	// 3�b�ȏ�o�߂�����A�C�e�����폜����
	if (m_nColCnt >= m_nFlashTime)
	{
		// �ϐ��̏�����
		m_nColCnt = 0;
		// �폜
		Rerease();
	}
}

// =====================================================================================================================================================================
//
// �A�C�e���̏��̐ݒ�
//
// =====================================================================================================================================================================
void CItem::SetItemData()
{
	// �h���b�v���̐ݒ�
	m_nDropRate		 = m_ItemData.nDropRate;
	// �A�C�e�����_�ł���܂ł̎���
	m_nDeleteTime	 = m_ItemData.nDeleteTime;
	// �A�C�e�����_�ł��鎞��
	m_nFlashTime	 = m_ItemData.nFlashTime;
	// �F�̃A�C�e���̃X�R�A
	m_nBearScore	 = m_ItemData.nBearScore;
	// �R�C���̃A�C�e���̃X�R�A
	m_nCoinScore	 = m_ItemData.nCoinScore;
	// ��΂̃A�C�e���̃X�R�A
	m_nJewelryScore	 = m_ItemData.nJewelryScore;
	// ���_���̃A�C�e���̃X�R�A
	m_nMedalScore	 = m_ItemData.nMedalScore;
	// �����蔻��̑傫��
	m_CollisionSize	 = m_ItemData.CollisionSize;
}

// =====================================================================================================================================================================
//
// �����_������
//
// =====================================================================================================================================================================
uint64_t CItem::get_rand_range(uint64_t min_val, uint64_t max_val)
{
	// �����Z���k�E�c�C�X�^�[�@�ɂ��[��������������A
	// �n�[�h�E�F�A�������V�[�h�ɂ��ď�����
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());

	// ����������
	static std::mt19937_64 mt64(seed_gen());

	// [min_val, max_val] �̈�l���z���� (int) �̕��z������
	std::uniform_int_distribution<uint64_t> get_rand_uni_int(min_val, max_val);

	// �����𐶐�
	return get_rand_uni_int(mt64);
	// �����𐶐�
	//return get_rand_uni_int(engine);
}

// =====================================================================================================================================================================
//
// �R�C���̃X�R�A�����Z���鏈��
//
// =====================================================================================================================================================================
int CItem::AddCoinScore(int nScore)
{
	// �R�C�����擾���邲�ƂɃR�C���̃X�R�A��{�ɂ���
	for (int nAdd = 0; nAdd < m_nAddCnt;nAdd++)
	{
		// ���ڂ͏������Ȃ�
		if (m_nAddCnt == 0)
		{
			// �X�L�b�v
			continue;
		}

		// �X�R�A�̒l��{�ɂ���
		nScore += nScore;
	}

	// �J�E���g���Z
	m_nAddCnt++;

	// �X�R�A�̒l��Ԃ�
	return nScore;
}

// =====================================================================================================================================================================
//
// �����_���@�͈͎w��
//
// =====================================================================================================================================================================
CItem::ITEMTYPE CItem::RandomRange(ITEMTYPE min, ITEMTYPE max)
{
	// �͈͂Ń����_���ɒl�����ߒl��Ԃ�
	//return (ITEMTYPE)(min + (int)(rand()*(max - min + 1.0) / (1.0 + RAND_MAX)));

	//return (ITEMTYPE)(min + (int)(rand()*(max - min) / (RAND_MAX)));

	return (ITEMTYPE)get_rand_range(min, max);
}

// =====================================================================================================================================================================
//
// �A�C�e�����h���b�v���鎞�̃p�^�[��
//
// =====================================================================================================================================================================
void CItem::DropPattern(ITEMDROP_PATTERN pattern , ITEMDROP drop, ITEMTYPE type)
{
	// �������ƂɃh���b�v�����������ς���
	switch (pattern)
	{
		// �h���b�v����A�C�e�����w�肷��
	case CItem::ITEMDROP_PATTERN_DESIGNATE:
		m_Type = type;
		break;

		// �h���b�v����A�C�e���������_���ɂ���
	case CItem::ITEMDROP_PATTERN_RANDOM:
		// �A�C�e���̃^�C�v�������_���ɐݒ�
		m_Type = RandDropItem(drop);
		break;
	default:
		break;
	}
}

// =====================================================================================================================================================================
//
// �f�o�b�O�p�A�C�e���R�}���h
//
// =====================================================================================================================================================================
void CItem::DebugItemCommand(CKeyboard *key)
{
	//�g��������
	CDebugProc::Print("\n---------Debug ItemCommand----------\n");

	CDebugProc::Print("[LShift] + �e���L�[ [0] : �w�r�[�}�V���K��\n");
	CDebugProc::Print("[LShift] + �e���L�[ [1] : �V���b�g�K��\n");
	CDebugProc::Print("[LShift] + �e���L�[ [2] : ���[�U�[�K��\n");
	CDebugProc::Print("[LShift] + �e���L�[ [3] : ���P�b�g�����`���[\n");
	CDebugProc::Print("[LShift] + �e���L�[ [4] : �t���C���V���b�g\n");
	CDebugProc::Print("[LShift] + �e���L�[ [5] : �F\n");
	CDebugProc::Print("[LShift] + �e���L�[ [6] : �R�C��\n");
	CDebugProc::Print("[LShift] + �e���L�[ [7] : ���\n");
	CDebugProc::Print("[LShift] + �e���L�[ [8] : ���_��\n");
	CDebugProc::Print("[LShift] + �e���L�[ [9] : BomUp\n");
	CDebugProc::Print("[LShift] + �e���L�[ [-] : �K�\����\n");
	CDebugProc::Print("[LShift] + �e���L�[ [+] : BulletUp\n");

	//LShift�����Ȃ���
	if (key->GetKeyboardPress(DIK_LSHIFT))
	{
		// �w�r�[�}�V���K���̐���
		if (key->GetKeyboardTrigger(DIK_NUMPAD0))
		{
			CItem::DebugCreate(ITEMTYPE_HEAVYMACHINEGUN);
		}
		// �V���b�g�K������
		else if (key->GetKeyboardTrigger(DIK_NUMPAD1))
		{
			CItem::DebugCreate(ITEMTYPE_SHOTGUN);
		}
		// ���[�U�[�K������
		else if (key->GetKeyboardTrigger(DIK_NUMPAD2))
		{
			CItem::DebugCreate(ITEMTYPE_LASERGUN);
		}
		// ���P�b�g�����`���[����
		else if (key->GetKeyboardTrigger(DIK_NUMPAD3))
		{
			CItem::DebugCreate(ITEMTYPE_ROCKETLAUNCHER);
		}
		// �t���C���V���b�g����
		else if (key->GetKeyboardTrigger(DIK_NUMPAD4))
		{
			CItem::DebugCreate(ITEMTYPE_FLAMESHOT);
		}
		// �F�̐���
		else 	if (key->GetKeyboardTrigger(DIK_NUMPAD5))
		{
			CItem::DebugCreate(ITEMTYPE_BEAR);
		}
		// �R�C���̐���
		else 	if (key->GetKeyboardTrigger(DIK_NUMPAD6))
		{
			CItem::DebugCreate(ITEMTYPE_COIN);
		}
		// ��΂̐���
		else 	if (key->GetKeyboardTrigger(DIK_NUMPAD7))
		{
			CItem::DebugCreate(ITEMTYPE_JEWELRY);
		}
		// ���_���̐���
		else 	if (key->GetKeyboardTrigger(DIK_NUMPAD8))
		{
			CItem::DebugCreate(ITEMTYPE_MEDAL);
		}
		// BomUp����
		else if (key->GetKeyboardTrigger(DIK_NUMPAD9))
		{
			CItem::DebugCreate(ITEMTYPE_BOMBUP);
		}
		// �K�\��������
		else if (key->GetKeyboardTrigger(DIK_NUMPADMINUS))
		{
			CItem::DebugCreate(ITEMTYPE_ENERGYUP);
		}
		// BulletUp����
		else if (key->GetKeyboardTrigger(DIK_NUMPADPLUS))
		{
			CItem::DebugCreate(ITEMTYPE_BULLETUP);
		}
	}
}

// =====================================================================================================================================================================
//
// �ÓI�ϐ��̏����� game�I����
//
// =====================================================================================================================================================================
void CItem::InitVariable()
{
	// �R�C���̃J�E���g���Z�p�ϐ��̏�����
	m_nAddCnt = 0;
}

// =====================================================================================================================================================================
//
// �f�o�b�O�p�A�C�e������
//
// =====================================================================================================================================================================
CItem * CItem::DebugCreate(ITEMTYPE type)
{
	// �ϐ�
	CItem *pItem;

	// �������̊m��
	pItem = new CItem(OBJTYPE_ITEM);

	// ������
	pItem->Init();

	// �T�C�Y�̐ݒ�
	pItem->SetSize(D3DXVECTOR3(
		m_CollisionSize.x / 2,
		m_CollisionSize.y / 2,
		m_CollisionSize.z / 2));


	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();

	if (pPlayer != nullptr)
	{
		D3DXVECTOR3 pos = pPlayer->GetPosition();
		// �A�C�e�������������ʒu�̒���
		pItem->SetDropPos(pos);

		// �A�C�e���̈ʒu�̐ݒ�
		pItem->SetPosition(pos);

		pItem->m_Type = type;
	}

	// ��ޕʂɃe�N�X�`����ݒ�
	pItem->SwitchTexture(pItem->m_Type, pItem);

	return pItem;
}

// =====================================================================================================================================================================
//
// �����_���֐�
//
// =====================================================================================================================================================================
int CItem::ItemRand(int max)
{
	// ������߂�
	int nAdjusted_max = (RAND_MAX + 1) - (RAND_MAX + 1) % max;

	// �����_���ɋ��߂��l���i�[�����r�p�ϐ�
	int nRandom = 0;

	// RAND_MAX + 1 �� max �Ŋ���؂�Ȃ��ꍇ�A���������̒[�����͈̔͂ɂȂ�����̂ĂĂ�蒼��
	do {
		// �����_���ɒl�����߂�
		nRandom = rand();
	} while (nRandom >= nAdjusted_max);

	// �l��Ԃ�
	return (int)(((float)nRandom / nAdjusted_max) * max);
}

// =====================================================================================================================================================================
//
// �A�C�e���̃f�[�^�̓ǂݍ���
//
// =====================================================================================================================================================================
void CItem::ItemLoad()
{
	// �t�@�C���|�C���g
	FILE *pFile;

	char cReadText[128];			// �����Ƃ��ēǂݎ��
	char cHeadText[128];			// ��r�p
	char cDie[128];					// �s�v�ȕ���

	// �t�@�C�����J��
	pFile = fopen(m_ItemFileName, "r");

	// �J���Ă���Ƃ�
	if (pFile != NULL)
	{
		// SCRIPT������܂Ń��[�v
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
			sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������
		}

		// SCRIPT��������
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			// END_SCRIPT������܂Ń��[�v
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
				sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

															// ITEMSET��������
				if (strcmp(cHeadText, "ITEMSET") == 0)
				{
					// END_ITEMSET������܂Ń��[�v
					while (strcmp(cHeadText, "END_ITEMSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
						sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

																	// SPEED��������
						if (strcmp(cHeadText, "RATE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ItemData.nDropRate);		// ��r�p�e�L�X�g��RATE����
						}
						// LIFE��������
						else if (strcmp(cHeadText, "DELETE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ItemData.nDeleteTime);	// ��r�p�e�L�X�g��DELETE����
						}
						// FLASH��������
						else if (strcmp(cHeadText, "FLASH") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ItemData.nFlashTime);	// ��r�p�e�L�X�g��FLASH����
						}
						// BEAR��������
						else if (strcmp(cHeadText, "BEAR") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ItemData.nBearScore);	// ��r�p�e�L�X�g��BEAR����
						}
						// BEAR��������
						else if (strcmp(cHeadText, "COIN") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ItemData.nCoinScore);	// ��r�p�e�L�X�g��COIN����
						}
						// BEAR��������
						else if (strcmp(cHeadText, "JEWELRY") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ItemData.nJewelryScore);	// ��r�p�e�L�X�g��JEWELRY����
						}
						// BEAR��������
						else if (strcmp(cHeadText, "MEDAL") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ItemData.nMedalScore);	// ��r�p�e�L�X�g��MEDAL����
						}
						// COLLISIONSIZE��������
						else if (strcmp(cHeadText, "COLLISIONSIZE") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
								&m_ItemData.CollisionSize.x,
								&m_ItemData.CollisionSize.y,
								&m_ItemData.CollisionSize.z);										// ��r�p�e�L�X�g��COLLISIONSIZE����
						}
						else if (strcmp(cHeadText, "END_ITEMSET") == 0)
						{
						}
					}
				}
			}
		}
		// �t�@�C�������
		fclose(pFile);
	}
	else
	{
		MessageBox(NULL, "�A�C�e���̃f�[�^�ǂݍ��ݎ��s", "�x��", MB_ICONWARNING);
	}

	// �ǂݍ��񂾏��̑��
	SetItemData();
}

// =====================================================================================================================================================================
//
// �L�����N�^�[���A�C�e���𗎂Ƃ��Ƃ��̐�������
//
// =====================================================================================================================================================================
CItem * CItem::DropCreate(D3DXVECTOR3 pos, ITEMDROP drop , ITEMDROP_PATTERN pattern ,ITEMTYPE type)
{
	// �ϐ�
	CItem *pItem;

	// �������̊m��
	pItem = new CItem(OBJTYPE_ITEM);

	// ������
	pItem->Init();

	// �T�C�Y�̐ݒ�
	pItem->SetSize(D3DXVECTOR3(
		m_CollisionSize.x /2,
		m_CollisionSize.y /2,
		m_CollisionSize.z /2));

	// �A�C�e�������������ʒu�̒���
	pItem->SetDropPos(pos);

	// �A�C�e���̈ʒu�̐ݒ�
	pItem->SetPosition(pos);

	// �A�C�e���̃h���b�v���p�^�[�����Ƃɕς���
	pItem->DropPattern(pattern, drop, type);

	// ��ޕʂɃe�N�X�`����ݒ�
	pItem->SwitchTexture(pItem->m_Type, pItem);

	return pItem;
}

// =====================================================================================================================================================================
//
// ��ޕʃe�N�X�`���o�C���h����
//
// =====================================================================================================================================================================
void CItem::SwitchTexture(ITEMTYPE type, CItem *pItem)
{
	switch (type)
	{
		//�w�r�[�}�V���K��
	case (ITEMTYPE_HEAVYMACHINEGUN):{
		// �e�N�X�`���̊��蓖��
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_HEAVYMACHINEGUN));
	}break;

		//�V���b�g�K��
	case (ITEMTYPE_SHOTGUN): {
		// �e�N�X�`���̊��蓖��
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_SHOTGUN));
	}break;

		//���[�U�[�K��
	case (ITEMTYPE_LASERGUN): {
		// �e�N�X�`���̊��蓖��
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_LASERGUN));
	}break;

		//���P�b�g�����`���[
	case (ITEMTYPE_ROCKETLAUNCHER): {
		// �e�N�X�`���̊��蓖��
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_ROCKETLAUNCHER));
	}break;

		//�t���C���V���b�g
	case (ITEMTYPE_FLAMESHOT): {
		// �e�N�X�`���̊��蓖��
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_FLAMESHOT));
	}break;

		//�F
	case (ITEMTYPE_BEAR): {
		// �e�N�X�`���̊��蓖��
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BEAR));
	}break;
		//�R�C��
	case (ITEMTYPE_COIN): {
		// �e�N�X�`���̊��蓖��
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_COIN));
	}break;
		//���
	case (ITEMTYPE_JEWELRY): {
		// �e�N�X�`���̊��蓖��
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_JEWELRY));
	}break;
		//���_��
	case (ITEMTYPE_MEDAL): {
		// �e�N�X�`���̊��蓖��
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_MEDAL));
	}break;
		// ���e�̐��𑝂₷
	case (ITEMTYPE_BOMBUP): {
		// �e�N�X�`���̊��蓖��
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BOMBUP));
	}break;

		// ��蕨�̑ϋv�l���񕜂���
	case (ITEMTYPE_ENERGYUP): {
		// �e�N�X�`���̊��蓖��
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_ENERGYUP));
	}break;

		// �n���h�K���ȊO�̒e�̎c�e���𑝂₷
	case (ITEMTYPE_BULLETUP): {
		// �e�N�X�`���̊��蓖��
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BULLETUP));
	}break;

	default:
		break;
	}
}

// =====================================================================================================================================================================
//
// �h���b�v����A�C�e���̃����_������
//
// =====================================================================================================================================================================
CItem::ITEMTYPE CItem::RandDropItem(ITEMDROP drop)
{
	// �l��Ԃ����߂̕ϐ�
	ITEMTYPE type;
	// �����ɂ���ăh���b�v������A�C�e���̎�ނɐ�����������
	switch (drop)
	{
		// ����݂̂̏ꍇ
	case CItem::ITEMDROP_WEAPON:
		// �����_���͈̔͂𕐊�݂̂ɑI��
		type = RandomRange(ITEMTYPE_HEAVYMACHINEGUN, ITEMTYPE_FLAMESHOT);
		break;

		// �X�R�A�A�b�v�݂̂̏ꍇ
	case CItem::ITEMDROP_SCORE:
		// �����_���͈̔͂��X�R�A�A�C�e���݂̂ɑI��
		type = RandomRange(ITEMTYPE_BEAR, ITEMTYPE_MEDAL);
		break;

		// �e��Ȃǂ݂̂̏ꍇ
	case CItem::ITEMDROP_CHARGE:
		// �����_���͈̔͂��X�R�A�A�C�e���݂̂ɑI��
		type = RandomRange(ITEMTYPE_BOMBUP, ITEMTYPE_BULLETUP);
		break;

		// �S�ẴA�C�e��
	case CItem::ITEMDROP_ALL:
		type = (ITEMTYPE)ItemRand(ITEMTYPE_MAX);
		break;
	default:
		break;
	}

	return type;
}

// =====================================================================================================================================================================
//
// �A�C�e�����h���b�v����m�������߂�
//
// =====================================================================================================================================================================
bool CItem::DropRate()
{
	// �A�C�e�����h���b�v���邩�̃t���O
	bool bDrop = false;

	// ���߂��h���b�v�����i�[����ϐ�
	int nDrop = 0;

	// �h���b�v����\���ϐ�
	int nRate = m_nDropRate;

	// �����_���Ƀh���b�v���邩�����߂�
	nDrop = ItemRand(nRate);

	// ���ʂ�0�Ȃ�A�C�e�����h���b�v���鋖���o��
	if (nDrop == 0)
	{
		bDrop = true;
	}

	// ���ʂ�����ȊO�Ȃ�A�C�e�����h���b�v���鋖���o���Ȃ�
	else
	{
		bDrop = false;
	}

	// ���ʂ�Ԃ�
	return bDrop;
}
