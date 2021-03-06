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
#include "sound.h"
#include "GameManager.h"
#include "ModelSet.h"
#include "grenadefire.h"
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


}
//====================================================================
//初期化
//====================================================================
HRESULT CEnemy::Init(void)
{
	//キャラの初期化
	CCharacter::Init();

	//ガンのポインタ生成
	m_pGun = CGun::Create();
	m_pGun->SetTag(TAG::ENEMY);
	m_pGun->SetDisp(false);

	// グレネード放つ位置の生成
	m_pGrenadeFire = CGrenadeFire::Create();
	m_pGrenadeFire->SetTag(TAG::ENEMY);

	//イベントのフラグ
	m_bEventFlag = false;

	// 当たり判定生成
	GetCollision()->SetPos(GetPositionPtr());
	GetCollision()->SetPosOld(&GetPositionOld());
	GetCollision()->SetSize(ENEMY_SIZE);
	GetCollision()->SetMove(&GetMove());
	GetCollision()->SetGameObject(this);

	CCharacter::SetMaxLife(1);

	SetCharacterDirection(DIRECTION::LEFT);

	return S_OK;
}
//====================================================================
//終了
//====================================================================
void CEnemy::Uninit(void)
{
	if (m_pAI != nullptr)
	{
		delete m_pAI;
		m_pAI = nullptr;
	}
	// 銃の解放
	if (m_pGun != nullptr)
	{
		// 銃の削除
		delete m_pGun;
		m_pGun = nullptr;
	}
	// グレネード発射位置のポインタ
	if (m_pGrenadeFire)
	{
		m_pGrenadeFire->Rerease();
		m_pGrenadeFire = nullptr;
	}
	CCharacter::Uninit();
}
//====================================================================
//更新
//====================================================================
void CEnemy::Update(void)
{
	//死亡していない時
	if (CCharacter::GetCharacterState() != CCharacter::CHARACTER_STATE_DEATH)
	{
		// 弾を撃つ方向を設定
		GetGunPtr()->SetShotRot(GetShotDirection());

		//AI関連処理
		if (m_pAI)
		{
			m_pAI->Update();
		}
		if (m_pGun)
		{
			m_pGun->Update();
		}
	}
	//キャラクターの更新
	CCharacter::Update();
}
//====================================================================
//描画
//====================================================================
void CEnemy::Draw(void)
{
	CCharacter::Draw();

	m_pGun->Draw();
}
//====================================================================
//デバッグ
//====================================================================
void CEnemy::DebugInfo(void)
{
	char aTreeName[MAX_TEXT] = {};
	sprintf(aTreeName, "EnemyInfo [%d]", CScene::GetID());

	if (ImGui::TreeNode(aTreeName))
	{
		ImGui::Text("m_bEventFlag [%d]", m_bEventFlag); ImGui::SameLine();
		ImGui::Text("m_type [%d]", m_type);

		CCharacter::DebugInfo();

		if (m_pAI)
		{
			m_pAI->DebugInfo();
		}

		if (m_pGun)
		{
			m_pGun->DebugInfo();
		}

		ImGui::TreePop();
	}

}

//====================================================================
//デフォルトのモーション設定
//====================================================================
bool CEnemy::DefaultMotion(void)
{
	GetModelSet()->SetMotion(CModelSet::ENEMY_MOTION_NORMAL);
	return true;
}
//====================================================================
//ダメージを受けた時のリアクション
//====================================================================
void CEnemy::DamageReaction()
{
	SetState(CCharacter::CHARACTER_STATE_DAMAGE_RED);
}
//====================================================================
//死んだ時のリアクション
//====================================================================
void CEnemy::DeathReaction()
{
	//死亡フラグをたてる
	this->SetDieFlag(true);

	//死亡リアクション
	CCharacter::DeathReaction();

	//フラグが立っている時
	if (m_bEventFlag)
	{
		//イベントクリア
		CManager::GetGame()->GetGameManager()->EventClear();
	}
}
//====================================================================
//ステートが変更した瞬間の処理
//====================================================================
void CEnemy::StateChangeReaction()
{

}
//====================================================================
//コリジョン関数
//====================================================================
void CEnemy::Collision()
{
	CCharacter::Collision();
}
//====================================================================
//AI消去
//====================================================================
void CEnemy::DeleteAI()
{
	if (m_pAI != nullptr)
	{
		delete m_pAI;
		m_pAI = nullptr;
	}
}
