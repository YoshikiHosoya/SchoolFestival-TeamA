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
//====================================================================
//マクロ定義
//====================================================================
#define ENEMY_SIZE			(D3DXVECTOR3(50.0f,75.0f,0.0f)) //敵のサイズ

CEnemy::CEnemy(OBJ_TYPE type) :CCharacter(type)
{
	SetObjType(OBJTYPE_ENEMY);
}

CEnemy::~CEnemy()
{
	if (m_pAI != nullptr)
	{
		delete m_pAI;
		m_pAI = nullptr;
	}

	CItem::Create(this->GetPosition(), CItem::ITEMTYPE_HEAVYMACHINEGUN);
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
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetPosOld(&GetPositionOld());
	GetCollision()->SetSize2D(ENEMY_SIZE);
	GetCollision()->SetMove(&GetMove());
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);
	CCharacter::SetLife(50);
	return S_OK;
}
//====================================================================
//終了
//====================================================================
void CEnemy::Uninit(void)
{
	CCharacter::Uninit();
}
//====================================================================
//更新
//====================================================================
void CEnemy::Update(void)
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
	{//アイテムを生成
		m_pGun->Rerease();
		m_pGun = nullptr;
		//CItem::Create(this->GetPosition(), CItem::ITEMTYPE_HEAVYMACHINEGUN);
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
		//m_pAI->Update();
	}

	//CDebugProc::Print("\n敵のライフ %d\n", CCharacter::GetLife());
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
