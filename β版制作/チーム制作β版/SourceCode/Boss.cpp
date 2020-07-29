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
CBoss::CBoss(OBJ_TYPE type) :CCharacter(type)
{
	SetObjType(OBJTYPE_BOSS);
	m_pGun = nullptr;
}

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
	SetCharacterType(CCharacter::CHARACTER_TYPE_BOSS);
	m_Attack = false;
	//重力無し
	SetGravity(false);
	// 銃の生成
	m_pGun = CGun::Create(GetCharacterModelPartsList(CModel::MODEL_BOSS_BODY)->GetMatrix());
	m_pGun->SetGunType(CGun::GUNTYPE_TRACKINGGUN);
	// 銃の弾の種類
	m_pGun->GetTag() = TAG_ENEMY;
	// 当たり判定生成
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetPosOld(&GetPositionOld());
	GetCollision()->SetSize2D(BOSS_SIZE);
	GetCollision()->SetMove(&GetMove());
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);
	SetPosition(D3DXVECTOR3(0.0f, 300.0f, 0.0f));
	SetMotion(CCharacter::BOSS_MOTION_NORMAL);
	CCharacter::SetLife(1);
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
		m_pGun->Rerease();
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
	//体力が0以下になった時
	if (this->GetLife() <= 0)
	{
		this->SetDieFlag(true);
		CParticle::CreateFromText(GetPosition(), GetShotDirection(), CParticleParam::EFFECT_BLOOD);
	}
	//AI関連処理
	if (m_pAI != nullptr)
	{
		m_pGun->SetShotVec(m_pAI->GetTrackingShotRot());
		if (m_pAI->GetAITypeAttack() == m_pAI->AI_TRACKING)
		{
			m_pGun->Shot();
		}
		m_pAI->Update();
	}
	CCharacter::Update();
}
//====================================================================
//描画
//====================================================================
void CBoss::Draw(void)
{
	CCharacter::Draw();
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
bool CBoss::DefaultMotion(void)
{
	SetMotion(CCharacter::BOSS_MOTION_NORMAL);
	return true;
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
