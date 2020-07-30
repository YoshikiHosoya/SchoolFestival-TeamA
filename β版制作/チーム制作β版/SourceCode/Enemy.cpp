//====================================================================
// エネミー処理 [enemy.cpp]: NORI
//====================================================================
#include "Enemy.h"
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
//====================================================================
//マクロ定義
//====================================================================
#define ENEMY_SIZE			(D3DXVECTOR3(50.0f,75.0f,0.0f)) //敵のサイズ

CEnemy::CEnemy(OBJ_TYPE type) :CCharacter(type)
{
	SetObjType(OBJTYPE_ENEMY);
	m_pGun = nullptr;
}

CEnemy::~CEnemy()
{


}
//====================================================================
//初期化
//====================================================================
HRESULT CEnemy::Init(void)
{
	//キャラの初期化
	CCharacter::Init();
	LoadOffset(CCharacter::CHARACTER_TYPE_ENEMY);
	SetCharacterType(CCharacter::CHARACTER_TYPE_ENEMY);
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	m_Attack = false;

	// 銃の生成
	m_pGun = CGun::Create(GetCharacterModelPartsList(CModel::MODEL_ENEMY_RHAND)->GetMatrix());
	// 銃の弾の種類
	m_pGun->GetTag() = TAG_ENEMY;
	// 当たり判定生成
	GetCollision()->SetPos(GetPositionPtr());
	GetCollision()->SetPosOld(&GetPositionOld());
	GetCollision()->SetSize2D(ENEMY_SIZE);
	GetCollision()->SetMove(&GetMove());
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);
	CCharacter::SetLife(1);
	return S_OK;
}
//====================================================================
//終了
//====================================================================
void CEnemy::Uninit(void)
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
void CEnemy::Update(void)
{
	//描画の範囲内かチェック
	CheckDrawRange();

	if (!GetDraw())
	{
		return;
	}

	CKeyboard *key;
	key = CManager::GetInputKeyboard();
	if (GetCollision() != nullptr)
	{

		CKeyboard *key;
		key = CManager::GetInputKeyboard();

		if (key->GetKeyboardTrigger(DIK_8))
		{
			SetMotion(CCharacter::ENEMY_MOTION_NORMAL);
		}
		if (key->GetKeyboardTrigger(DIK_9))
		{
			SetMotion(CCharacter::ENEMY_MOTION_WALK);
		}
		if (GetCollision() != nullptr)
		{

			//座標の更新
			GetCollision()->SetPos(&GetPosition());
		}
		//体力が0以下になった時
		if (this->GetLife() <= 0)
		{
			this->SetDieFlag(true);
			CParticle::CreateFromText(GetPosition(), GetShotDirection(), CParticleParam::EFFECT_BLOOD);
		}
		else
		{
			// 弾を撃つ方向を設定
			m_pGun->SetShotRot(GetShotDirection());
		}
		//AI関連処理
		if (m_pAI != nullptr)
		{
			if (m_pAI->GetAIType() == m_pAI->AI_SHOT && m_pAI->GetShot() == true)
			{
				m_pGun->Shot();
			}

			m_pAI->Update();
		}
	}
	CCharacter::Update();

}
//====================================================================
//描画
//====================================================================
void CEnemy::Draw(void)
{
	CCharacter::Draw();
}
//====================================================================
//デバッグ
//====================================================================
void CEnemy::DebugInfo(void)
{
}
//====================================================================
//モデルのクリエイト
//====================================================================
CEnemy *CEnemy::Create(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CEnemy*pEnemy;
	pEnemy = new CEnemy(OBJTYPE_ENEMY);
	pEnemy->Init();
	pEnemy->m_pAI = CEnemyAI::CreateAI(pEnemy);
	return pEnemy;
}
bool CEnemy::DefaultMotion(void)
{
	SetMotion(CCharacter::ENEMY_MOTION_NORMAL);
	return true;
}
//====================================================================
//移動
//====================================================================
void CEnemy::Move(float move, float fdest)
{
	GetMove().x += sinf(move * -D3DX_PI) * 1.0f;
	GetMove().z += cosf(move * -D3DX_PI) * 1.0f;
	//m_rotDest.y = fdest *  D3DX_PI;
}
