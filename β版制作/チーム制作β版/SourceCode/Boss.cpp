//====================================================================
// ボス処理 [Boss.cpp]: NORI
//====================================================================
#include "Boss.h"
#include "inputKeyboard.h"
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
#define BOSS_LIFE			(1500)


//====================================================================
//コンストラクタ
//====================================================================
CBoss::CBoss(OBJ_TYPE type) :CEnemy(type)
{
	SetObjType(OBJTYPE_BOSS);
	m_pGun = nullptr;
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
	CCharacter::Init();
	LoadOffset(CCharacter::CHARACTER_TYPE_BOSS);
	SetPosition(D3DXVECTOR3(0.0f, 300.0f, 0.0f));
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
	m_pGun = CGun::Create(GetCharacterModelPartsList(CModel::MODEL_BOSS_BODY)->GetMatrix());
	m_pGun->SetGunType(CGun::GUNTYPE_TRACKINGGUN);

	// 銃の弾の種類
	m_pGun->GetTag() = TAG_ENEMY;

	// 当たり判定生成
	GetCollision()->SetPos(GetPositionPtr());
	GetCollision()->SetPosOld(&GetPositionOld());
	GetCollision()->SetSize2D(BOSS_SIZE);
	GetCollision()->SetMove(&GetMove());
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);
	return S_OK;
}
//====================================================================
//終了
//====================================================================
void CBoss::Uninit(void)
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

	CCharacter::Uninit();
}
//====================================================================
//更新
//====================================================================
void CBoss::Update(void)
{
	//AI関連処理
	if (m_pAI != nullptr)
	{
		m_pAI->Update();
	}
	CCharacter::Update();

	m_pGun->Update();

}
//====================================================================
//描画
//====================================================================
void CBoss::Draw(void)
{
	CCharacter::Draw();

	//ガンのマトリックスの計算だけ
	m_pGun->NoDrawCalcMatrixOnly();

}
//====================================================================
//デバッグ
//====================================================================
void CBoss::DebugInfo(void)
{

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
	pBoss->m_pAI = CBossAI::CreateAI(pBoss);
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

	//nullcheck
	if(CManager::GetGame())
	{
		CManager::GetGame()->SetGameMode(CGame::GAME_MODE_RESULT);
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
		CParticle::CreateFromText(GetPosition() + CHossoLibrary::RandomVector3(150.0f), ZeroVector3, CParticleParam::EFFECT_NO_COLLISION_EXPLOSION);
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

		if (m_pAI != nullptr)
		{
			delete m_pAI;
			m_pAI = nullptr;
		}
		break;
	}
}
//====================================================================
//ボスの銃の取得
//====================================================================
CGun *CBoss::GetGun(void)
{
	return m_pGun;
}
//====================================================================
//移動
//====================================================================
void CBoss::Move(float move, float fdest)
{
	GetMove().x += sinf(move * -D3DX_PI) * 1.0f;
	GetMove().z += cosf(move * -D3DX_PI) * 1.0f;
	//m_rotDest.y = fdest *  D3DX_PI;
}
