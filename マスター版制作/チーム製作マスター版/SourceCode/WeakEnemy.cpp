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
	LoadOffset(CCharacter::CHARACTER_TYPE_ENEMY);
	SetCharacterType(CCharacter::CHARACTER_TYPE_ENEMY);
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	m_Attack = false;

	// 銃の生成
	GetGunPtr()->SetHandMtx(GetCharacterModelPartsList(CModel::MODEL_ENEMY_RHAND)->GetMatrix());

	// 銃の弾の種類
	GetGunPtr()->GetTag() = TAG_ENEMY;
	// ナイフの生成

	m_pKnife = CKnife::Create(GetCharacterModelPartsList(CModel::MODEL_ENEMY_LHAND)->GetMatrix(), KNIFE_COLLISOIN_SIZE,TAG::TAG_ENEMY);

	// 敵のタイプ設定
	switch (m_type)
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
		m_pShield->SetHandMtx(GetCharacterModelPartsList(CModel::MODEL_ENEMY_RHAND)->GetMatrix());
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
	pWeakEnemy->m_type = type;
	pWeakEnemy->Init();


	return pWeakEnemy;
}
//====================================================================
//デフォルトのモーション設定
//====================================================================
bool CWeakEnemy::DefaultMotion(void)
{
	SetMotion(CCharacter::ENEMY_MOTION_NORMAL);
	return true;
}
//====================================================================
//ダメージを受けた時のリアクション
//====================================================================
void CWeakEnemy::DamageReaction()
{
	SetState(CCharacter::CHARACTER_STATE_DAMAGE_RED);

	CManager::GetSound()->Play(CSound::LABEL_SE_HIT);
}
//====================================================================
//死んだ時のリアクション
//====================================================================
void CWeakEnemy::DeathReaction()
{
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
		SetMotion(CCharacter::ENEMY_MOTION_DEAD_1);

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
