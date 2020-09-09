//====================================================================
// エネミー処理 [enemy.cpp]: NORI
//====================================================================
#include "weakenemy.h"
#include "Enemy.h"
#include "model.h"
#include "game.h"
#include "fade.h"
#include "collision.h"
#include "debugproc.h"
#include "ShieldEnemyAI.h"
#include "EnemyAI.h"
#include "gun.h"
#include "particle.h"
#include "sound.h"
#include "shield.h"
#include "Knife.h"
#include "item.h"
#include "ModelSet.h"
//====================================================================
//マクロ定義
//====================================================================
#define ENEMY_SIZE			(D3DXVECTOR3(50.0f,75.0f,0.0f)) //敵のサイズ
#define KNIFE_COLLISOIN_SIZE	(D3DXVECTOR3(40.0f,60.0f,0.0f))

CWeakEnemy::CWeakEnemy(OBJ_TYPE type) :CEnemy(type)
{
	SetObjType(OBJTYPE_ENEMY);
}

CWeakEnemy::~CWeakEnemy()
{
}
//====================================================================
//初期化
//====================================================================
HRESULT CWeakEnemy::Init(void)
{
	// キャラの初期化
	CEnemy::Init();
	GetModelSet()->LoadOffset(CModelSet::CHARACTER_TYPE_ENEMY);
	GetModelSet()->SetCharacterType(CModelSet::CHARACTER_TYPE_ENEMY);
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	m_Attack = false;

	// 銃の生成
	GetGunPtr()->SetHandMtx(GetModelSet()->GetCharacterModelList()[8]->GetMatrix());
	// 銃の弾の種類
	GetGunPtr()->SetTag(TAG::ENEMY);

	GetGunPtr()->SetGunTypeOnly(CGun::GUNTYPE_HANDGUN_ENEMY);
	// ナイフの生成

	m_pKnife = CKnife::Create(GetModelSet()->GetCharacterModelList()[7]->GetMatrix(), KNIFE_COLLISOIN_SIZE,TAG::ENEMY);
	//腕が回転するか
	SetRotArm(true);

	// 敵のタイプ設定
	switch (GetEnemyType())
	{
	case CWeakEnemy::WEAKENEMY_TYPE::ENEMY_NORMAL:
		SetAIPtr(CEnemyAI::CreateAI(this));
		break;
	case CWeakEnemy::WEAKENEMY_TYPE::ENEMY_SHIELD:
		//AIの追加
		SetAIPtr(CShieldEnemyAI::CreateAI(this));
		//盾生成
		m_pShield = nullptr;
		m_pShield = CShield::Create();
		m_pShield->SetHandMtx(GetModelSet()->GetCharacterModelList()[8]->GetMatrix());
		m_pShield->SetHasEnemyPtr(this);
		break;
	default:
		break;
	}


	// 当たり判定生成
	GetCollision()->SetSize2D(ENEMY_SIZE);
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);

	CCharacter::SetLife(1);
	
	return S_OK;
}
//====================================================================
//終了
//====================================================================
void CWeakEnemy::Uninit(void)
{
	if (m_pShield)
	{
		m_pShield->Rerease();
		m_pShield = nullptr;
	}
	if (m_pKnife)
	{
		m_pKnife->Rerease();
		m_pKnife = nullptr;
	}

	CEnemy::Uninit();
}
//====================================================================
//更新
//====================================================================
void CWeakEnemy::Update(void)
{
	//描画の範囲内かチェック
	if (!CheckDrawRange())
	{
		//画面の左端より左に行った場合は死亡扱い
		if (CManager::GetRenderer()->GetMinScreenPos().x > GetPosition().x)
		{
			//死亡
			DeathReaction();
		}
		return;
	}
	CEnemy::Update();
}
//====================================================================
//描画
//====================================================================
void CWeakEnemy::Draw(void)
{
	CEnemy::Draw();

}
//====================================================================
//デバッグ
//====================================================================
void CWeakEnemy::DebugInfo(void)
{

}
//====================================================================
//モデルのクリエイト
//====================================================================
CWeakEnemy *CWeakEnemy::Create(WEAKENEMY_TYPE type)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CWeakEnemy*pWeakEnemy;
	pWeakEnemy = new CWeakEnemy(OBJTYPE_ENEMY);
	pWeakEnemy->SetEnemyType(type);
	// タグの設定
	pWeakEnemy->SetTag(TAG::ENEMY);
	pWeakEnemy->Init();


	return pWeakEnemy;
}
//====================================================================
//デフォルトのモーション設定
//====================================================================
bool CWeakEnemy::DefaultMotion(void)
{
	GetModelSet()->SetMotion(CModelSet::ENEMY_MOTION_NORMAL);
	return true;
}
//====================================================================
//ダメージを受けた時のリアクション
//====================================================================
void CWeakEnemy::DamageReaction()
{
	SetState(CCharacter::CHARACTER_STATE_DAMAGE_RED);
}
//====================================================================
//死んだ時のリアクション
//====================================================================
void CWeakEnemy::DeathReaction()
{
	if (CHossoLibrary::Random(10) <= 1)
	{
		// ランダムな確率でアイテムをドロップする
		if (CItem::DropRate())
		{
			//アイテムを生成
			CItem::DropCreate(GetPosition(),
				CItem::ITEMDROP_CHARGE,
				CItem::ITEMDROP_PATTERN_DESIGNATE,
				CItem::ITEMTYPE_NONE);
		}
	}

	CEnemy::DeathReaction();

}
//====================================================================
//ステートが変更した瞬間の処理
//====================================================================
void CWeakEnemy::StateChangeReaction()
{

	CCharacter::StateChangeReaction();

	switch (CCharacter::GetCharacterState())
	{
	case CHARACTER_STATE_NORMAL:
		break;

	case CHARACTER_STATE_DAMAGE_RED:

		break;
	case CHARACTER_STATE_DEATH:
		SetStateCount(60);
		m_pKnife->EndMeleeAttack();
		GetModelSet()->SetMotion(CModelSet::ENEMY_MOTION_DEAD_1);

		switch (GetEnemyType())
		{
		case CEnemy::WEAKENEMY_TYPE::ENEMY_NORMAL:
		case CEnemy::WEAKENEMY_TYPE::ENEMY_SHIELD:
			//悲鳴
			CManager::GetSound()->Play(CSound::LABEL_SE_VOICE_ENEMY_DEATH);

			//血のエフェクト
			CParticle::CreateFromText(GetPosition(), GetShotDirection(), CParticleParam::EFFECT_BLOOD);
		default:
			break;
		}

		if (m_pShield)
		{
			//盾破壊
			ShieldBreak();
		}

		break;
	}
}
//====================================================================
//縦破壊
//====================================================================
void CWeakEnemy::ShieldBreak()
{
	//nullcheck
	if (m_pShield)
	{
		//シールド吹っ飛ばす処理
		m_pShield->AwayShield();

		//null
		m_pShield = nullptr;

	}
}
