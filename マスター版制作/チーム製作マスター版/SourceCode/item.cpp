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
#include "playergetscoreui.h"
#include "gun.h"
#include <random>
#include "inputKeyboard.h"
#include "sound.h"
#include "scoremanager.h"
#include "particle.h"
#include "grenadefire.h"
#include <algorithm>

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
ITEM_DATA	CItem::m_ItemData				 = {};
int			CItem::m_nAddCoin				 = 1;
ITEM_GACHA CItem::m_ItemGachaData			 = {};

std::vector<unsigned int>					CItem::m_nSaveHitItem				 = {};
std::vector<CItem::ITEM_RARITY>				CItem::m_nBoxRandRarityDataList		 = {};
std::vector<CItem::ITEM_RARITY>				CItem::m_nDefaultRarityList			 = {};
std::vector<std::vector<CItem::ITEMTYPE>>	CItem::m_nBoxRandDefaultRarityData	 = {};

// =====================================================================================================================================================================
// �e�L�X�g�t�@�C����
// =====================================================================================================================================================================
char *CItem::m_ItemFileName =
{
	"data/Load/Item/ItemData.txt" ,			// �A�C�e���̏��
};

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define FULLRAND_HITPROBABILITY (5)
#define MULTIPLE_ITEM_NUM (5)// �܂Ƃ߂Đ�������ۂ̐�

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CItem::CItem(OBJ_TYPE type) :CScene3D(type)
{
	// �v���C���[�̃|�C���^
	m_pPlayer[MAX_CONTROLLER] = {};
	// �����蔻��̃|�C���^
	m_pCollision = nullptr;
	// �A�C�e�����}�b�v�Ɏc�鎞��
	m_nRemainTime = m_ItemData.nDeleteTime;
	// ���J���[�J�E���g
	m_nColCnt = 0;
	// �A�C�e���̎��
	m_Type = ITEMTYPE_NONE;
	// �A�C�e�����h���b�v��������
	m_Drop = ITEMDROP_WEAPON;
	// �ړ���
	m_Move = D3DXVECTOR3(0.0f,-1.0f, 0.0f);
	// �d�͂̏����l
	m_fGravity = 0.0f;
	// ����񐔂̏�����
	m_nHitRayCount = 0;
	// 1�t���[���O�̍��W
	m_PosOld = ZeroVector3;
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
	for (int nCntPlayer = 0; nCntPlayer < MAX_CONTROLLER; nCntPlayer++)
	{
		m_pPlayer[nCntPlayer] = CManager::GetBaseMode()->GetPlayer((TAG)(nCntPlayer));
	}

	// ������
	CScene3D::Init();

	// �d�͂̏����l
	m_fGravity = 1.0f;

	// �����蔻�萶��
	m_pCollision = CCollision::Create();
	m_pCollision->SetPos(&GetPosition());
	m_pCollision->SetSize(m_ItemData.CollisionSize);
	m_pCollision->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);

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
	// �����蔻��n
	ItemCollision();

	// ���C�̔���Ɉ��ł��G��Ă�����
	if (m_nHitRayCount >= 1)
	{
		// �A�C�e���̑؍ݎ��ԊǗ�
		RemainTimer();
	}

	if (m_Behavior == BEHAVIOR_BURSTS)
	{
		GetPosition() += m_Move * 4.0f;
	}
	else
	{
		GetPosition() += m_Move * 1.5f;
	}
	SetPosition(GetPosition());

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
void CItem::ItemAcquisition(ITEMTYPE type, TAG Tag)
{
	// �A�C�e���̎�ނ��Ƃ̏���
	switch (type)
	{
		// �w�r�[�}�V���K��
	case (ITEMTYPE_HEAVYMACHINEGUN): {
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_WEAPON);
		CManager::GetSound()->Play(CSound::LABEL_SE_VOICE_HEAVYMACHINEGUN);

		m_pPlayer[(int)Tag]->GetGun()->SetGunType(CGun::GUNTYPE_HEAVYMACHINEGUN);
	}break;

		// �V���b�g�K��
	case (ITEMTYPE_SHOTGUN): {
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_WEAPON);
		CManager::GetSound()->Play(CSound::LABEL_SE_VOICE_SHOTGUN);

		m_pPlayer[(int)Tag]->GetGun()->SetGunType(CGun::GUNTYPE_SHOTGUN);
	}break;

		// ���[�U�[�K��
	case (ITEMTYPE_LASERGUN): {
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_WEAPON);
		CManager::GetSound()->Play(CSound::LABEL_SE_VOICE_LAZERGUN);

		m_pPlayer[(int)Tag]->GetGun()->SetGunType(CGun::GUNTYPE_LASERGUN);
	}break;

		// ���P�b�g�����`���[
	case (ITEMTYPE_ROCKETLAUNCHER): {
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_WEAPON);
		CManager::GetSound()->Play(CSound::LABEL_SE_VOICE_ROCKETLAUNCHER);

		m_pPlayer[(int)Tag]->GetGun()->SetGunType(CGun::GUNTYPE_ROCKETLAUNCHER);
	}break;

		// �t���C���V���b�g
	case (ITEMTYPE_FLAMESHOT): {
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_WEAPON);
		CManager::GetSound()->Play(CSound::LABEL_SE_VOICE_FLAMESHOT);

		m_pPlayer[(int)Tag]->GetGun()->SetGunType(CGun::GUNTYPE_FLAMESHOT);
	}break;

		// ����
	case (ITEMTYPE_GOLDCOIN): {
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_GCOIN));
	}break;

		// ���
	case (ITEMTYPE_SILVERCOIN): {
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_SCOIN));
	}break;

		// ����
	case (ITEMTYPE_BRONZESCOIN): {
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_BCOIN));
	}break;

		// �_�C�A�����h
	case (ITEMTYPE_DIAMOND): {
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_DIAMOND));
	}break;
		// �F
	case (ITEMTYPE_BEAR): {
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_BEAR));
	}break;

		// �莆
	case (ITEMTYPE_LETTER): {
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);

		// �R�C������邽�тɃR�C���̃X�R�A�A�b�v
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(AddCoinScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_LETTER)));
	}break;

		// �����S
	case ITEMTYPE_APPLE:
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FRUIT));
		break;
		// ������
	case ITEMTYPE_MELON:
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FRUIT));
		break;
		// �o�i�i
	case ITEMTYPE_BANANA:
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FRUIT));
	break;


		// ��
	case ITEMTYPE_MEAT:
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD));
		break;
		// ���ɂ���
	case (ITEMTYPE_RICEBALL):
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD));
		break;
		// ��
	case (ITEMTYPE_CANDY):
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD));
		break;
		// �h�[�i�c
	case (ITEMTYPE_DONUT):
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD));
		break;
		// �����|�b�v
	case (ITEMTYPE_LOLIPOP):
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD));
		break;
		// �F
	case (ITEMTYPE_BREAD):
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD));
		break;
		// �`���R���[�g
	case (ITEMTYPE_CHOCOLATE):
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD));
		break;
		// �A�C�X
	case (ITEMTYPE_ICE):
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// �X�R�A�A�b�v
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD));
	break;

		// ���e�̐��𑝂₷
	case (ITEMTYPE_BOMBUP): {
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_WEAPON);
		m_pPlayer[(int)Tag]->GetGrenadeFire()->GrenadeAddAmmo();
	}break;

		// �n���h�K���ȊO�̒e�̎c�e���𑝂₷
	case (ITEMTYPE_BULLETUP): {
		// SE��炷
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_WEAPON);
		m_pPlayer[(int)Tag]->GetGun()->GunAddAmmo(m_pPlayer[(int)Tag]->GetGun()->GetGunType());
	}break;
	}

	m_pPlayer[(int)Tag]->SetState(CCharacter::CHARACTER_STATE_ITEMGET_FLASH);

	CParticle::CreateFromText(GetPosition(), ZeroVector3, CParticleParam::EFFECT_GETWEAPON);
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
void CItem::HitItem(ITEMTYPE type, TAG Tag)
{
	// ��ނ��Ƃ̏���
	ItemAcquisition(type, Tag);
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
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer(TAG::PLAYER_1);
	// �v���C���[�����݂�����
	if (pPlayer != nullptr)
	{
		// �v���C���[�̌������擾
		if (pPlayer->GetCharacterDirection() == DIRECTION::LEFT)
		{
			characterpos.x -= 50;
		}
		else if(pPlayer->GetCharacterDirection() == DIRECTION::RIGHT)
		{
			characterpos.x += 50;
		}

		characterpos.y += 50;
	}
}

// =====================================================================================================================================================================
//
// �ړ��ʂ̐ݒ�
//
// =====================================================================================================================================================================
void CItem::SetMove(D3DXVECTOR3 move)
{
	m_Move = move;
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
	if (m_nColCnt >= m_ItemData.nFlashTime)
	{
		// �ϐ��̏�����
		m_nColCnt = 0;
		// �폜
		Rerease();
	}
}

// =====================================================================================================================================================================
//
// �����_������
//
// =====================================================================================================================================================================
uint64_t CItem::GetRandRange(uint64_t min_val, uint64_t max_val)
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
}

// =====================================================================================================================================================================
//
// �R�C���̃X�R�A�����Z���鏈��
//
// =====================================================================================================================================================================
int CItem::AddCoinScore(int nScore)
{
	// �X�R�A�ƃJ�E���g��������
	nScore *= m_nAddCoin;

	// �J�E���g��{�ɂ���
	m_nAddCoin += m_nAddCoin;

	// �X�R�A�̒l��Ԃ�
	return nScore;
}

// =====================================================================================================================================================================
//
// ���S����
//
// =====================================================================================================================================================================
CItem::ITEMTYPE CItem::FullRand()
{
	//FULLRAND_HITPROBABILITY
	// ���S�����ŏo���A�C�e���̌��ʂ�ۑ�
	//nSaveHitItem
	// n��A���Ł�3���o�Ă��Ȃ������������I�Ɂ�3�̃A�C�e�����h���b�v����
	//if
	return ITEMTYPE();
}

// =====================================================================================================================================================================
//
// �{�b�N�X����
//
// =====================================================================================================================================================================
CItem::ITEMTYPE CItem::BoxRand()
{
	// �s�b�N���ꂽ�����̗v�f���폜����
	if (!m_nDefaultRarityList.empty())
	{
		// ���A���e�B���X�g�̖�������s�b�N����(���X�g�͊��Ƀ����_��������Ă���)
		const ITEM_RARITY Rarity = m_nDefaultRarityList.back();
		// �s�b�N���ꂽ�����̗v�f���폜����
		m_nDefaultRarityList.pop_back();
		// ���A���e�B���X�g����s�b�N���ꂽ���A���e�B�̃��X�g�̒����烉���_���ɃA�C�e����I�o����
		//v.list[Rarity].�ŏ��@.�Ō� ���s�ڂ̉��Ԗڂ� (0�Ԗڂ���ő吔��)
		//const ITEMTYPE type = ItemRandomRange(m_nBoxRandDefaultRarityData.at(Rarity).at(0), m_nBoxRandDefaultRarityData.at(Rarity).at(m_nBoxRandDefaultRarityData.at(Rarity).size() - 1));
		const ITEMTYPE type = ItemWhichOnePick(m_nBoxRandDefaultRarityData, Rarity);

		// �z�񂪋󂾂�����
		if (m_nDefaultRarityList.empty())
		{
			// �{�b�N�X�����h�̃��X�g�Đݒ�
			SetBoxRandDataList();
		}

		return type;
	}

	// �G���[�h�~
	return ITEMTYPE_HEAVYMACHINEGUN;
}

// =====================================================================================================================================================================
//
// �{�b�N�X�����̕ꐔ��0�ȉ��ɂȂ��������ʂ����Z�b�g���� ���݂̃}�b�v�̏󋵂ɂ���Č��ʂ�ς���
//
// =====================================================================================================================================================================
void CItem::SetBoxRandDataList()
{
	// �{�b�N�X�����h�̃��X�g�Ƀf�[�^��ݒ�
	AddBoxRandList();
}

// =====================================================================================================================================================================
//
// �A�C�e���̃��A���e�B�ƕꐔ�����Ƀ����_���ȃ��X�g�𐶐�����
//
// =====================================================================================================================================================================
void CItem::AddBoxRandList()
{
	// �f�t�H���g�̃{�b�N�X�����̃f�[�^
	// ���A���e�B*�e���A���e�B�̐�
	for (int nNum = 0; nNum < ITEM_RARITY_TOTAL; nNum++)
	{
		for (unsigned int nCnt = 0; nCnt < m_ItemGachaData.BoxRandDefault_RarityNum[nNum]; nCnt++)
		{
			// ���X�g�Ɋe���A���e�B�̐��𐔕��ǉ�
			m_nDefaultRarityList.emplace_back((ITEM_RARITY)nNum);
		}
	}

	// �v�f���V���b�t�����ݒ肷��
	random_shuffle(m_nDefaultRarityList.begin(), m_nDefaultRarityList.end());
}

// =====================================================================================================================================================================
//
// ������C�ɃA�C�e������������鎞�̃A�C�e���̋�������
//
// =====================================================================================================================================================================
void CItem::BurstsItem()
{
}

// =====================================================================================================================================================================
//
// �󒆂ɂ������A�C�e�������ɒ����������˕Ԃ鏈��
//
// =====================================================================================================================================================================
void CItem::BounceItem()
{
}

// =====================================================================================================================================================================
//
// ���_����w�肳�ꂽ�w��͈͂�X���W��Ԃ�
//
// =====================================================================================================================================================================
D3DXVECTOR3 CItem::RandomDropPosX(const D3DXVECTOR3 originpos, int radius)
{
	// �A�C�e�����h���b�v��������W
	D3DXVECTOR3 DropPos = originpos;
	// ���_���甼�a�����������W�Ɣ��a�𑫂������W�͈͓̔��̍��W�������_���ɕԂ�
	//DropPos.x = (float)GetRandRange((int)originpos.x - radius, (int)originpos.x + radius);

	DropPos.x = CHossoLibrary::Random((float)radius);
	DropPos.z = 0.0f;

	return DropPos;
}

// =====================================================================================================================================================================
//
// �����̂̃^�C�v�ݒ�
//
// =====================================================================================================================================================================
void CItem::SetMultiType(ITEM_LIST_DROPMULTIPLE list)
{
	switch (list)
	{
	case CItem::LIST_FRUIT:
		// �t���[�c�̂�
		SwitchTexture(this->RandDropItem(ITEMDROP_FRUIT), this);
		break;

	case CItem::LIST_FOOD:
		// �H�ו��̂�
		SwitchTexture(this->RandDropItem(ITEMDROP_FOOD), this);
		break;

	case CItem::LIST_COIN:
		// �R�C���̂�
		SwitchTexture(this->RandDropItem(ITEMDROP_COIN), this);
		break;

	case CItem::LIST_RARE:
		// ���A�ȃA�C�e���̂�
		SwitchTexture(this->RandDropItem(ITEMDROP_RARE), this);
		break;
	}
}

// =====================================================================================================================================================================
//
// ����n
//
// =====================================================================================================================================================================
void CItem::ItemCollision()
{
	// �����蔻��
	if (m_pCollision != nullptr)
	{
		// ���W�̍X�V pos
		m_pCollision->SetPos(&GetPosition());
		// �}�b�v�̃|�C���^�擾
		CMap *pMap = CManager::GetBaseMode()->GetMap();
		// 1�t���[���O�̍��W�����߂�
		m_PosOld = GetPosition();

		if (pMap)
		{
			if (m_pCollision->RayCollision(pMap,GetPosition() - D3DXVECTOR3(0.0f,30.0f,0.0f),GetPosition()))
			{
				if (m_Behavior != BEHAVIOR_NONE)
				{
					// �܂����C�̔���Ɉ�x���G��Ă��Ȃ�������
					if (m_nHitRayCount <= 0)
					{
						// �A�C�e���̔��ˏ���
						ReflectionItem();
						// �d�͂̏�����
						m_fGravity = 0.0f;
					}
					else
					{
						m_Move = ZeroVector3;
					}
				}

				m_nHitRayCount++;
			}
			else
			{
				if (m_nHitRayCount < 2)
				{
					// ���K��
					D3DXVec3Normalize(&m_Move, &m_Move);

					if (m_Behavior == BEHAVIOR_BURSTS)
					{
						m_fGravity += 0.1f;
					}
					else
					{
						// �d�͂�����
						m_fGravity += 0.05f;
					}
					// �d�͂𔽉f
					GetPosition().y -= m_fGravity;
				}
			}
		}
	}
}

// =====================================================================================================================================================================
//
// ���ˏ���
//
// =====================================================================================================================================================================
void CItem::ReflectionItem()
{
	// �@���x�N�g��
	const D3DXVECTOR3 NormalV = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	// �i�s�x�N�g��
	D3DXVECTOR3 ProgressV = m_PosOld - GetPosition();
	// ���C�̔���ɂɐG�ꂽ�Ƃ��i�s�x�N�g����@���x�N�g���̕����ɕϊ�����
	ReflectingVectorCalculation(&m_Move, ProgressV, NormalV);
}

// =====================================================================================================================================================================
//
// �e�X�g�p
//
// =====================================================================================================================================================================
D3DXVECTOR3 * CItem::ReflectingVectorCalculation(D3DXVECTOR3 *outV, const D3DXVECTOR3 &ProgressV, const D3DXVECTOR3 &Normal)
{
	// �@���x�N�g���ϊ��p
	D3DXVECTOR3 NormalVector;
	// �@���x�N�g���𐳋K��
	D3DXVec3Normalize(&NormalVector, &Normal);
	// ���˃x�N�g�������߂�
	return D3DXVec3Normalize(outV, &(ProgressV - 2.0f * D3DXVec3Dot(&ProgressV, &NormalVector) * NormalVector));
}

// =====================================================================================================================================================================
//
// �����_���@�A�C�e���̎�ނ͈̔�
//
// =====================================================================================================================================================================
CItem::ITEMTYPE CItem::ItemRandomRange(ITEMTYPE min, ITEMTYPE max)
{
	// �͈͂Ń����_���ɒl�����ߒl��Ԃ�
	return (ITEMTYPE)GetRandRange(min, max);
}

// =====================================================================================================================================================================
//
// �����_�� �A�C�e���̃��A���e�B�͈̔�
//
// =====================================================================================================================================================================
CItem::ITEM_RARITY CItem::RarityRandomRange(ITEM_RARITY min, ITEM_RARITY max)
{
	return (ITEM_RARITY)GetRandRange(min, max);
}

// =====================================================================================================================================================================
//
// �A�C�e�����h���b�v���鎞�̃p�^�[��
//
// =====================================================================================================================================================================
void CItem::DropPattern(bool fixed, ITEMTYPE type)
{
	// �m�肵�Ă���Ȃ炻�̃^�C�v��ݒ肷��
	if (fixed)
	{
		m_Type = type;
	}
	// �m�肵�Ă��Ȃ��Ȃ畐��ȊO�̃^�C�v��ݒ肷��
	else
	{
		// �^�C�v�������_���ɐݒ�
		m_Type = RandDropItem(ITEMDROP_SCO_CHA);
	}
}

// =====================================================================================================================================================================
//
// �A�C�e���𕡐���C�Ƀh���b�v�����鎞 �ړ���,�����̐ݒ�
//
// =====================================================================================================================================================================
void CItem::DropPattern_Multiple(ITEM_LIST_DROPMULTIPLE list, ITEM_BEHAVIOR behavior,int nNum)
{
	switch (behavior)
	{
	case CItem::BEHAVIOR_NONE:
		break;

		// ���R����
	case CItem::BEHAVIOR_FREEFALL:
		break;

		// �e�����
	case CItem::BEHAVIOR_BURSTS:

		// �������珇�Ɏ΂߂ɔ�΂�nNum5��

		if (nNum == 0)
		{
			SetMove(D3DXVECTOR3(-2.5f, 5.0f, 0.0f));
		}
		if (nNum == 1)
		{
			SetMove(D3DXVECTOR3(-7.5f, 5.0f, 0.0f));
		}
		if (nNum == 2)
		{
			SetMove(D3DXVECTOR3(0.0f, 5.0f, 0.0f));
		}
		if (nNum == 3)
		{
			SetMove(D3DXVECTOR3(7.5f, 5.0f, 0.0f));
		}
		if (nNum == 4)
		{
			SetMove(D3DXVECTOR3(2.5f, 5.0f, 0.0f));
		}
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
	CDebugProc::Print_Right("\n---------Debug ItemCommand----------\n");

	CDebugProc::Print_Right("[LShift] + �e���L�[ [0] : �w�r�[�}�V���K��\n");
	CDebugProc::Print_Right("[LShift] + �e���L�[ [1] : �V���b�g�K��\n");
	CDebugProc::Print_Right("[LShift] + �e���L�[ [2] : ���[�U�[�K��\n");
	CDebugProc::Print_Right("[LShift] + �e���L�[ [3] : ���P�b�g�����`���[\n");
	CDebugProc::Print_Right("[LShift] + �e���L�[ [4] : �t���C���V���b�g\n");
	CDebugProc::Print_Right("[LShift] + �e���L�[ [5] : �R�C��\n");
	CDebugProc::Print_Right("[LShift] + �e���L�[ [6] : BomUp\n");
	CDebugProc::Print_Right("[LShift] + �e���L�[ [7] : BulletUp\n");
	CDebugProc::Print_Right("[LShift] + �e���L�[ [ENTER] : BoxRand\n");

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
		// �R�C���̐���
		else 	if (key->GetKeyboardTrigger(DIK_NUMPAD6))
		{
			CItem::DebugCreate(ITEMTYPE_GOLDCOIN);
		}
		// BomUp����
		else if (key->GetKeyboardTrigger(DIK_NUMPAD9))
		{
			CItem::DebugCreate(ITEMTYPE_BOMBUP);
		}
		// BulletUp����
		else if (key->GetKeyboardTrigger(DIK_NUMPADPLUS))
		{
			CItem::DebugCreate(ITEMTYPE_BULLETUP);
		}
		// boxramd�e�X�g�p
		else if (key->GetKeyboardTrigger(DIK_NUMPADENTER))
		{
			CItem::DropCreate_TEST();
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
	m_nAddCoin = 1;
	// �z��̑S�v�f���폜
	m_nSaveHitItem.clear();
	m_nBoxRandRarityDataList.clear();
}

// =====================================================================================================================================================================
//
// // �h���b�v�������ɃA�C�e�����h���b�v���邩�����߂Č��ʂ�Ԃ�
//
// =====================================================================================================================================================================
bool CItem::DecideIfItemDrop(int nRate)
{
	// �A�C�e�����h���b�v���邩�̃t���O
	bool bDrop = false;

	// ��U
	if (GetRandRange(0, nRate) == 0)
	{
		bDrop = true;
	}

	return bDrop;
}

// =====================================================================================================================================================================
//
// �f�o�b�O�p�A�C�e������
//
// =====================================================================================================================================================================
CItem * CItem::DebugCreate(ITEMTYPE type)
{
	// �������̊m��
	CItem * pItem = new CItem(OBJTYPE_ITEM);

	// ������
	pItem->Init();

	// �T�C�Y�̐ݒ�
	pItem->SetSize(D3DXVECTOR3(
		m_ItemData.CollisionSize.x / 2,
		m_ItemData.CollisionSize.y / 2,
		m_ItemData.CollisionSize.z / 2));

	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer(TAG::PLAYER_1);

	if (pPlayer != nullptr)
	{
		D3DXVECTOR3 pos = pPlayer->GetPosition();
		// �A�C�e�������������ʒu�̒���
		pItem->SetDropPos(pos);

		// �A�C�e���̈ʒu�̐ݒ�
		pItem->SetPosition(pos);

		pItem->m_Type = type;

		pItem->m_Behavior = BEHAVIOR_NONE;
	}

	// ��ޕʂɃe�N�X�`����ݒ�
	pItem->SwitchTexture(pItem->m_Type, pItem);

	return pItem;
}

// =====================================================================================================================================================================
//
// ���A���e�B�̐���
//
// =====================================================================================================================================================================
void CItem::SetRarityList()
{
	// �e���A���e�B�ɊY������A�C�e���̐ݒ�
	CItem::m_nBoxRandDefaultRarityData = {
		{ ITEMTYPE_HEAVYMACHINEGUN, ITEMTYPE_ROCKETLAUNCHER },
		{ ITEMTYPE_LASERGUN },
		{ ITEMTYPE_SHOTGUN, ITEMTYPE_FLAMESHOT },
	};

	// �e���A���e�B�̗v�f����ݒ�
	for (unsigned int Line = 0; Line < m_nBoxRandDefaultRarityData.size(); Line++)
	{
		m_ItemGachaData.BoxRandDefault_RarityNum[Line] = m_nBoxRandDefaultRarityData.at(Line).size();
	}

	// ���X�g�ɏ���ǉ�
	AddBoxRandList();
}

// =====================================================================================================================================================================
//
// �������X�g�̒�����1��I�ь��ʂ�Ԃ�
//
// =====================================================================================================================================================================
CItem::ITEMTYPE CItem::ItemWhichOnePick(std::vector<std::vector<CItem::ITEMTYPE>> list ,int line)
{
	// ���X�g�̃A�C�e���̈ꗗ��ۑ�����ϐ�
	std::vector<ITEMTYPE> Pick;
	// �ŏI�I�Ƀs�b�N����A�C�e���̎��
	ITEMTYPE type;

	for (unsigned int Column = 0; Column < list.at(line).size(); Column++)
	{
		// ���X�g����A�C�e�����̈ꗗ���擾
		Pick.emplace_back(list.at(line).at(Column));
	}

	std::random_device get_rand_dev;
	std::mt19937 get_rand_mt(get_rand_dev()); // seed�ɗ������w��
	std::shuffle(Pick.begin(), Pick.end(), get_rand_mt);

	type = Pick.back();

	return type;
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

				// 1�ڂ̃t�@�C����������
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

		// ���A���e�B���X�g�̐ݒ�
		SetRarityList();

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{
		MessageBox(NULL, "�A�C�e���̃f�[�^�ǂݍ��ݎ��s", "�x��", MB_ICONWARNING);
	}
}

// =====================================================================================================================================================================
//
// �L�����N�^�[���A�C�e���𗎂Ƃ��Ƃ��̐������� �m�肵�Ȃ��Ȃ�type��NONE������
//
// =====================================================================================================================================================================
CItem * CItem::DropItem(D3DXVECTOR3 droppos, bool fixed,ITEMTYPE type)
{
	// �������̊m��
	CItem *pItem = new CItem(OBJTYPE_ITEM);

	// ������
	pItem->Init();

	// �T�C�Y�̐ݒ�
	pItem->SetSize(D3DXVECTOR3(
		m_ItemData.CollisionSize.x /2,
		m_ItemData.CollisionSize.y /2,
		m_ItemData.CollisionSize.z /2));

	// �A�C�e�������������ʒu�̒���
	//pItem->SetDropPos(droppos);

	droppos.y += 30.0f;

	// �A�C�e���̈ʒu�̐ݒ�
	pItem->SetPosition(droppos);

	pItem->m_Behavior = BEHAVIOR_NONE;

	// �A�C�e���̃h���b�v���p�^�[�����Ƃɕς���
	pItem->DropPattern(fixed, type);

	// ��ޕʂɃe�N�X�`����ݒ�
	pItem->SwitchTexture(pItem->m_Type, pItem);

	return pItem;
}

// =====================================================================================================================================================================
//
// �A�C�e���𕡐���C�Ƀh���b�v�����鎞
//
// =====================================================================================================================================================================
void CItem::DropItem_Multiple(const D3DXVECTOR3 originpos, ITEM_LIST_DROPMULTIPLE type, ITEM_BEHAVIOR behavior)
{
	// �������鐔��
	for (int nNum = 0; nNum < MULTIPLE_ITEM_NUM; nNum++)
	{
		// �������̊m��
		CItem *pItem = new CItem(OBJTYPE_ITEM);

		// ������
		pItem->Init();

		// �T�C�Y�̐ݒ�
		pItem->SetSize(D3DXVECTOR3(
			m_ItemData.CollisionSize.x / 2,
			m_ItemData.CollisionSize.y / 2,
			m_ItemData.CollisionSize.z / 2));

		// �؂��痎����A�C�e������
		if (behavior == BEHAVIOR_FREEFALL)
		{
			pItem->SetPosition(pItem->RandomDropPosX(originpos, 100));
			//pItem->SetPosition(originpos);
		}
		// ���̑��͌��_���W����ɂ���
		else
		{
			if (behavior == BEHAVIOR_BURSTS)
			{
				D3DXVECTOR3 pos = originpos;
				pItem->SetPosition(D3DXVECTOR3(pos.x, pos.y + 50, pos.z));

			}
			else
			{
				pItem->SetPosition(originpos);
			}
		}

		// �����̐ݒ�
		pItem->m_Behavior = behavior;
		// �����̂̃^�C�v�ݒ�
		pItem->SetMultiType(type);
		// �A�C�e���̋����Ǝ�ނ̐ݒ�
		pItem->DropPattern_Multiple(type, behavior, nNum);
	}
}

// =====================================================================================================================================================================
//
// �f�o�b�O�p�A�C�e������
//
// =====================================================================================================================================================================
CItem * CItem::DropCreate_TEST()
{
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer((TAG)(0));
	D3DXVECTOR3 pos = pPlayer->GetPosition();

	// �ϐ�
	CItem *pItem;

	// �������̊m��
	pItem = new CItem(OBJTYPE_ITEM);

	// ������
	pItem->Init();

	// �T�C�Y�̐ݒ�
	pItem->SetSize(D3DXVECTOR3(
		m_ItemData.CollisionSize.x / 2,
		m_ItemData.CollisionSize.y / 2,
		m_ItemData.CollisionSize.z / 2));

	// �A�C�e�������������ʒu�̒���
	pItem->SetDropPos(pos);
	// �A�C�e���̈ʒu�̐ݒ�
	pItem->SetPosition(pos);
	// �{�b�N�X�����h�ŃA�C�e����I�o����
	pItem->m_Type = pItem->BoxRand();
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
	case CItem::ITEMTYPE_HEAVYMACHINEGUN:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_HEAVYMACHINEGUN));
		break;
	case CItem::ITEMTYPE_SHOTGUN:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_SHOTGUN));
		break;
	case CItem::ITEMTYPE_LASERGUN:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_LASERGUN));
		break;
	case CItem::ITEMTYPE_ROCKETLAUNCHER:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_ROCKETLAUNCHER));
		break;
	case CItem::ITEMTYPE_FLAMESHOT:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_FLAMESHOT));
		break;
	case CItem::ITEMTYPE_GOLDCOIN:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_GOLDCOIN));
		break;
	case CItem::ITEMTYPE_SILVERCOIN:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_SILVERCOIN));
		break;
	case CItem::ITEMTYPE_BRONZESCOIN:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BRONZESCOIN));
		break;
	case CItem::ITEMTYPE_DIAMOND:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_DIAMOND));
		break;
	case CItem::ITEMTYPE_BEAR:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BEAR));
		break;
	case CItem::ITEMTYPE_LETTER:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_LETTER));
		break;
	case CItem::ITEMTYPE_APPLE:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_APPLE));
		break;
	case CItem::ITEMTYPE_MELON:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_MELON));
		break;
	case CItem::ITEMTYPE_BANANA:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BANANA));
		break;
	case CItem::ITEMTYPE_MEAT:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_MEAT));
		break;
	case CItem::ITEMTYPE_RICEBALL:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_RICEBALL));
		break;
	case CItem::ITEMTYPE_CANDY:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_CANDY));
		break;
	case CItem::ITEMTYPE_DONUT:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_DONUT));
		break;
	case CItem::ITEMTYPE_LOLIPOP:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_LOLIPOP));
		break;
	case CItem::ITEMTYPE_BREAD:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BREAD));
		break;
	case CItem::ITEMTYPE_CHOCOLATE:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_CHOCOLATE));
		break;
	case CItem::ITEMTYPE_ICE:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_ICE));
		break;
	case CItem::ITEMTYPE_BOMBUP:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BOMBUP));
		break;
	case CItem::ITEMTYPE_BULLETUP:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BULLETUP));
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
	switch (drop)
	{
	case CItem::ITEMDROP_WEAPON:
		return m_Type = ItemRandomRange(ITEMTYPE_HEAVYMACHINEGUN, ITEMTYPE_FLAMESHOT);
		break;
	case CItem::ITEMDROP_SCORE:
		return m_Type = ItemRandomRange(ITEMTYPE_BEAR, ITEMTYPE_ICE);
		break;
	case CItem::ITEMDROP_CHARGE:
		return m_Type = ItemRandomRange(ITEMTYPE_BOMBUP, ITEMTYPE_BULLETUP);
		break;
	case CItem::ITEMDROP_SCO_CHA:
		return m_Type = ItemRandomRange(ITEMTYPE_BEAR, ITEMTYPE_BULLETUP);
		break;
	case CItem::ITEMDROP_FRUIT:
		return m_Type = ItemRandomRange(ITEMTYPE_APPLE, ITEMTYPE_BANANA);
		break;
	case CItem::ITEMDROP_COIN:
		return m_Type = ItemRandomRange(ITEMTYPE_GOLDCOIN, ITEMTYPE_BRONZESCOIN);
		break;
	case CItem::ITEMDROP_RARE:
		return m_Type = ItemRandomRange(ITEMTYPE_GOLDCOIN, ITEMTYPE_LETTER);
		break;
	case CItem::ITEMDROP_FOOD:
		return m_Type = ItemRandomRange(ITEMTYPE_MEAT, ITEMTYPE_ICE);
		break;
	case CItem::ITEMDROP_ALL:
		return m_Type = ItemRandomRange(ITEMTYPE_HEAVYMACHINEGUN, ITEMTYPE_BULLETUP);
		break;
	}

	return ITEMTYPE_NONE;
}

// =====================================================================================================================================================================
//
// �A�C�e�����h���b�v����m�������߂�
//
// =====================================================================================================================================================================
bool CItem::DropRate()
{
	// �����_���Ƀh���b�v���邩�����߂�
	return DecideIfItemDrop(m_ItemData.nDropRate);
}
