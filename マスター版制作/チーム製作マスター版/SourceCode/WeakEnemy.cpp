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
//====================================================================
//マクロ定義
//====================================================================
#define ENEMY_SIZE			(D3DXVECTOR3(50.0f,75.0f,0.0f)) //敵のサイズ

CWeakEnemy::CWeakEnemy(OBJ_TYPE type) :CEnemy(type)
{
	SetObjType(OBJTYPE_ENEMY);
	m_pGun = nullptr;
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
	m_pGun = CGun::Create(GetCharacterModelPartsList(CModel::MODEL_ENEMY_RHAND)->GetMatrix());
	// 銃の弾の種類
	m_pGun->GetTag() = TAG_ENEMY;

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
	// 銃の解放
	if (m_pGun != nullptr)
	{
		// 銃の削除
		delete m_pGun;
		m_pGun = nullptr;
	}
	if (m_pAI != nullptr)
	{
		delete m_pAI;
		m_pAI = nullptr;
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
		//描画範囲外なら描画しない
		return;
	}

	//死亡していない時
	if (CCharacter::GetCharacterState() != CCharacter::CHARACTER_STATE_DEATH)
	{
		if (GetCollision() != nullptr)
		{

			// 弾を撃つ方向を設定
			m_pGun->SetShotRot(GetShotDirection());
			//AI関連処理
			if (m_pAI)
			{
				if (m_pAI->GetAIType() == m_pAI->AI_SHOT && m_pAI->GetShot() == true)
				{
					m_pGun->Shot();
				}

				m_pAI->Update();
			}
			if (m_pGun)
			{
				m_pGun->Update();
			}
		}
	}
	CEnemy::Update();
}
//====================================================================
//描画
//====================================================================
void CWeakEnemy::Draw(void)
{
	CEnemy::Draw();

	m_pGun->Draw();

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
	pWeakEnemy->m_pAI = CEnemyAI::CreateAI(pWeakEnemy);
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

		break;
	}
}
//====================================================================
//移動
//====================================================================
void CWeakEnemy::Move(float move, float fdest)
{
	GetMove().x += sinf(move * -D3DX_PI) * 3.0f;
	GetMove().z += cosf(move * -D3DX_PI) * 3.0f;
	//m_rotDest.y = fdest *  D3DX_PI;
}
