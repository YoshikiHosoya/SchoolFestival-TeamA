//====================================================================
// エネミー処理 [enemy.cpp]: NORI
//====================================================================
#include "EnemyShield.h"
#include "inputKeyboard.h"
#include "model.h"
#include "game.h"
#include "fade.h"
#include "Xinput.h"
#include "collision.h"
#include "debugproc.h"
#include "item.h"
#include "gun.h"
#include "particle.h"
#include "sound.h"

//====================================================================
//マクロ定義
//====================================================================
#define ENEMY_SIZE			(D3DXVECTOR3(50.0f,75.0f,0.0f)) //敵のサイズ

CEnemyShield::CEnemyShield(OBJ_TYPE type) :CEnemy(type)
{
	SetObjType(OBJTYPE_ENEMY);
	m_pGun = nullptr;
}

CEnemyShield::~CEnemyShield()
{


}
//====================================================================
//初期化
//====================================================================
HRESULT CEnemyShield::Init(void)
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
void CEnemyShield::Uninit(void)
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
void CEnemyShield::Update(void)
{
	//描画の範囲内かチェック
	CheckDrawRange();

	if (!GetDraw())
	{
		return;
	}

	//死亡していない時
	if (CCharacter::GetCharacterState() != CCharacter::CHARACTER_STATE_DEATH)
	{
		CKeyboard *key;
		key = CManager::GetInputKeyboard();
		if (GetCollision() != nullptr)
		{
			if (GetCollision() != nullptr)
			{
				//座標の更新
				GetCollision()->SetPos(&GetPosition());
			}
			//体力が0以下になった時
			if (this->GetLife() <= 0)
			{
			}
			else
			{
				// 弾を撃つ方向を設定
				m_pGun->SetShotRot(GetShotDirection());
			}
		}
	}
	CCharacter::Update();

	m_pGun->Update();
}
//====================================================================
//描画
//====================================================================
void CEnemyShield::Draw(void)
{
	CCharacter::Draw();

	m_pGun->Draw();
}
//====================================================================
//デバッグ
//====================================================================
void CEnemyShield::DebugInfo(void)
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
}
//====================================================================
//モデルのクリエイト
//====================================================================
CEnemyShield *CEnemyShield::Create(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CEnemyShield*pEnemy;
	pEnemy = new CEnemyShield(OBJTYPE_ENEMY);
	pEnemy->Init();
	return pEnemy;
}
//====================================================================
//デフォルトのモーション設定
//====================================================================
bool CEnemyShield::DefaultMotion(void)
{
	SetMotion(CCharacter::ENEMY_MOTION_NORMAL);
	return true;
}
//====================================================================
//ダメージを受けた時のリアクション
//====================================================================
void CEnemyShield::DamageReaction()
{
	SetState(CCharacter::CHARACTER_STATE_DAMAGE_RED);

	CManager::GetSound()->Play(CSound::LABEL_SE_HIT);
}
//====================================================================
//死んだ時のリアクション
//====================================================================
void CEnemyShield::DeathReaction()
{
	//死亡フラグをたてる
	this->SetDieFlag(true);

	CCharacter::DeathReaction();

}
//====================================================================
//ステートが変更した瞬間の処理
//====================================================================
void CEnemyShield::StateChangeReaction()
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
void CEnemyShield::Move(float move, float fdest)
{
	GetMove().x += sinf(move * -D3DX_PI) * 3.0f;
	GetMove().z += cosf(move * -D3DX_PI) * 3.0f;
	//m_rotDest.y = fdest *  D3DX_PI;
}
