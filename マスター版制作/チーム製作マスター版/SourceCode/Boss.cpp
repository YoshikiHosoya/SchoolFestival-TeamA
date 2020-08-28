//====================================================================
// ボス処理 [Boss.cpp]: NORI
//====================================================================
#include "Boss.h"
#include "inputKeyboard.h"
#include "GameManager.h"
#include "model.h"
#include "game.h"
#include "fade.h"
#include "Xinput.h"
#include "collision.h"
#include "debugproc.h"
#include "item.h"
#include "EnemyAI.h"
#include "gun.h"
#include "particle.h"
#include "BossAI.h"
//====================================================================
//マクロ定義
//====================================================================
#define BOSS_SIZE			(D3DXVECTOR3(50.0f,75.0f,0.0f)) //敵のサイズ
#define BOSS_LIFE			(450)

//====================================================================
//コンストラクタ
//====================================================================
CBoss::CBoss(OBJ_TYPE type) :CEnemy(type)
{
	SetObjType(OBJTYPE_BOSS);
}
//====================================================================
//デストラクタ
//====================================================================
CBoss::~CBoss()
{


}
//====================================================================
//初期化
//====================================================================
HRESULT CBoss::Init(void)
{
	//キャラの初期化
	CEnemy::Init();
	LoadOffset(CCharacter::CHARACTER_TYPE_BOSS);
	SetMotion(CCharacter::BOSS_MOTION_NORMAL);

	CCharacter::SetLife(BOSS_LIFE);
	SetCharacterType(CCharacter::CHARACTER_TYPE_BOSS);

	m_Attack = false;
	m_AttackCastCnt = 0;
	m_AttackCnt = 0;
	SetRotDest(D3DXVECTOR3(0.0f, 0.0f*D3DX_PI, 0.0f));
	//重力無し
	SetGravity(false);

	// 銃の生成
	GetGunPtr()->SetHandMtx(GetCharacterModelPartsList(CModel::MODEL_BOSS_BODY)->GetMatrix());
	GetGunPtr()->SetGunType(CGun::GUNTYPE_TRACKINGGUN);

	// 銃の弾の種類
	GetGunPtr()->GetTag() = TAG_ENEMY;

	//銃を描画しない
	GetGunPtr()->SetDisp(false);

	// 当たり判定生成
	GetCollision()->SetSize2D(BOSS_SIZE);
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_NORMAL);
	return S_OK;
}
//====================================================================
//終了
//====================================================================
void CBoss::Uninit(void)
{
	CEnemy::Uninit();
}
//====================================================================
//更新
//====================================================================
void CBoss::Update(void)
{
	CEnemy::Update();
}
//====================================================================
//描画
//====================================================================
void CBoss::Draw(void)
{
	CEnemy::Draw();

	//ガンのマトリックスの計算だけ
	GetGunPtr()->NoDrawCalcMatrixOnly();

}
//====================================================================
//デバッグ
//====================================================================
void CBoss::DebugInfo(void)
{
	CDebugProc::Print("BossLife >> %d\n", GetLife());
}
//====================================================================
//モデルのクリエイト
//====================================================================
CBoss *CBoss::Create(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CBoss*pBoss;
	pBoss = new CBoss(OBJTYPE_BOSS);
	pBoss->Init();
	pBoss->SetAIPtr(CBossAI::CreateAI(pBoss));
	return pBoss;
}
//====================================================================
//ボスのデフォルトモーション
//====================================================================
bool CBoss::DefaultMotion(void)
{
	SetMotion(CCharacter::BOSS_MOTION_NORMAL);
	return true;
}
//====================================================================
//死亡時のリアクション
//====================================================================
void CBoss::DeathReaction()
{
	CCharacter::DeathReaction();

	//イベントクリア
	CManager::GetGame()->GetGameManager()->EventClear();

	//nullcheck
	if(CManager::GetGame())
	{
		CManager::GetGame()->GetGameManager()->SetGameState(CGameManager::GAMESTATE::RESULT);
	}

	SetDieFlag(true);
}
//====================================================================
//ステートに応じた処理
//====================================================================
void CBoss::State()
{
	CCharacter::State();

	//ステータスの処理
	switch (CCharacter::GetCharacterState())
	{
	case CHARACTER_STATE_DEATH:
		//爆発
		if (GetCharacterStateCnt() % 3 == 0)
		{
			CParticle::CreateFromText(GetPosition() + CHossoLibrary::RandomVector3(250.0f), ZeroVector3, CParticleParam::EFFECT_NO_COLLISION_EXPLOSION);
		}
		break;
	}
}
//====================================================================
//ステート切り替え時のリアクション
//====================================================================
void CBoss::StateChangeReaction()
{
	CCharacter::StateChangeReaction();

	//ステータスの処理
	switch (CCharacter::GetCharacterState())
	{
	case CHARACTER_STATE_DEATH:
 		SetStateCount(300);
		CEnemy::DeleteAI();
		break;
	}
}