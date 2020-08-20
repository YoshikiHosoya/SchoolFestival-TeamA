//====================================================================
// エネミー処理 [enemy.cpp]: NORI
//====================================================================
#include "weakenemy.h"
#include "model.h"
#include "game.h"
#include "fade.h"
#include "collision.h"
#include "debugproc.h"
#include "item.h"
#include "EnemyAI.h"
#include "gun.h"
#include "particle.h"
#include "sound.h"
#include "shield.h"
//====================================================================
//マクロ定義
//====================================================================
#define ENEMY_SIZE			(D3DXVECTOR3(50.0f,75.0f,0.0f)) //敵のサイズ

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
	//キャラの初期化
	CEnemy::Init();
	LoadOffset(CCharacter::CHARACTER_TYPE_ENEMY);
	SetCharacterType(CCharacter::CHARACTER_TYPE_ENEMY);
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	m_Attack = false;

	// 銃の生成
	GetGunPtr()->SetHandMtx(GetCharacterModelPartsList(CModel::MODEL_ENEMY_RHAND)->GetMatrix());

	// 銃の弾の種類
	GetGunPtr()->GetTag() = TAG_ENEMY;

	//盾生成
	m_pShield = nullptr;
	m_pShield = CShield::Create();
	m_pShield->SetHandMtx(GetCharacterModelPartsList(CModel::MODEL_ENEMY_RHAND)->GetMatrix());
	m_pShield->SetHasEnemyPtr(this);

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

	CEnemy::Uninit();
}
//====================================================================
//更新
//====================================================================
void CWeakEnemy::Update(void)
{
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
CWeakEnemy *CWeakEnemy::Create(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CWeakEnemy*pWeakEnemy;
	pWeakEnemy = new CWeakEnemy(OBJTYPE_ENEMY);
	pWeakEnemy->Init();
	pWeakEnemy->SetAIPtr(CEnemyAI::CreateAI(pWeakEnemy));

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
	//死亡フラグをたてる
	this->SetDieFlag(true);

	CCharacter::DeathReaction();

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

	case CHARACTER_STATE_DAMAGE:

		break;
	case CHARACTER_STATE_DAMAGE_RED:

		break;
	case CHARACTER_STATE_INVINCIBLE:

		break;
	case CHARACTER_STATE_DEATH:
		SetStateCount(60);
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
