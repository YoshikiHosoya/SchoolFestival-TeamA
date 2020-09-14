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
#include "item.h"
#include "ModelSet.h"
#include "hosso/Debug_ModelViewer.h"
//====================================================================
//マクロ定義
//====================================================================
#define ENEMY_HUMAN_COLLISIONSIZE				(D3DXVECTOR3(50.0f,75.0f,50.0f))			//敵の当たり判定サイズ
#define ENEMY_HELICOPTER_COLLISIONSIZE			(D3DXVECTOR3(350.0f,150.0f,350.0f))		//敵の当たり判定サイズ
#define ENEMY_MELTYHONEY_COLLISIONSIZE			(D3DXVECTOR3(250.0f,200.0f,250.0f))		//敵の当たり判定サイズ
#define ENEMY_ZYCOCCA_COLLISIONSIZE				(D3DXVECTOR3(110.0f,95.0f,110.0f))		//敵の当たり判定サイズ

#define ENEMY_HUMAN_LIFE						(1)										//ライフ
#define ENEMY_HELICOPTER_LIFE					(20)									//ライフ
#define ENEMY_MELTYHONEY_LIFE					(50)									//ライフ
#define ENEMY_ZYCOCCA_LIFE						(20)									//ライフ


#define KNIFE_COLLISOIN_SIZE	(D3DXVECTOR3(40.0f,60.0f,0.0f))
//====================================================================
//コンストラクタ
//====================================================================
CWeakEnemy::CWeakEnemy(OBJ_TYPE type) :CEnemy(type)
{
	SetObjType(OBJTYPE_ENEMY);
}

//====================================================================
//デストラクタ
//====================================================================
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
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	m_Attack = false;

	// 敵のタイプ設定
	switch (GetEnemyType())
	{
	case CWeakEnemy::ENEMY_TYPE::ENEMY_NORMAL:
		//オフセット設定
		GetModelSet()->SetCharacterType(CModelSet::CHARACTER_TYPE_ENEMY_HUMAN);
		GetModelSet()->LoadOffset(CModelSet::CHARACTER_TYPE_ENEMY_HUMAN);

		SetAIPtr(CEnemyAI::CreateAI(this));

		// 銃の生成
		GetGunPtr()->SetHandMtx(GetModelSet()->GetCharacterModelList()[8]->GetMatrix());
		// 銃の弾の種類
		GetGunPtr()->SetDisp(true);
		GetGunPtr()->SetGunTypeOnly(CGun::GUNTYPE_HANDGUN_ENEMY);

		// ナイフの生成
		m_pKnife = CKnife::Create(GetModelSet()->GetCharacterModelList()[7]->GetMatrix(), KNIFE_COLLISOIN_SIZE, TAG::ENEMY);
		//腕が回転するか
		SetRotArm(true);

		// 当たり判定生成
		GetCollision()->SetSize(ENEMY_HUMAN_COLLISIONSIZE);

		//HP設定
		CCharacter::SetLife(ENEMY_HUMAN_LIFE);

		break;
	case CWeakEnemy::ENEMY_TYPE::ENEMY_SHIELD:
		//オフセット設定
		GetModelSet()->SetCharacterType(CModelSet::CHARACTER_TYPE_ENEMY_HUMAN);
		GetModelSet()->LoadOffset(CModelSet::CHARACTER_TYPE_ENEMY_HUMAN);

		//AIの追加
		SetAIPtr(CShieldEnemyAI::CreateAI(this));

		//盾生成
		m_pShield = nullptr;
		m_pShield = CShield::Create();
		m_pShield->SetHandMtx(GetModelSet()->GetCharacterModelList()[8]->GetMatrix());
		m_pShield->SetHasEnemyPtr(this);

		// 銃の弾の種類
		GetGunPtr()->SetDisp(false);

		// ナイフの生成
		m_pKnife = CKnife::Create(GetModelSet()->GetCharacterModelList()[7]->GetMatrix(), KNIFE_COLLISOIN_SIZE, TAG::ENEMY);
		//腕が回転するか
		SetRotArm(true);

		//HP設定
		CCharacter::SetLife(ENEMY_HUMAN_LIFE);

		// 当たり判定生成
		GetCollision()->SetSize(ENEMY_HUMAN_COLLISIONSIZE);
		break;

	case CWeakEnemy::ENEMY_TYPE::ENEMY_HELICOPTER:
		//オフセット設定
		GetModelSet()->SetCharacterType(CModelSet::CHARACTER_TYPE_ENEMY_HELICOPTER);
		GetModelSet()->LoadOffset(CModelSet::CHARACTER_TYPE_ENEMY_HELICOPTER);

		//モーションoff
		CCharacter::GetModelSet()->SetUseMotion(false);
		CCharacter::GetModelSet()->SetMotion(CModelSet::CHARACTER_MOTION_STATE_NONE);

		//重力無効
		CCharacter::SetGravity(false);

		// 当たり判定生成
		GetCollision()->SetSize(ENEMY_HELICOPTER_COLLISIONSIZE);

		//HP設定
		CCharacter::SetLife(ENEMY_HELICOPTER_LIFE);

		break;

	case CWeakEnemy::ENEMY_TYPE::ENEMY_MELTYHONEY:
		//オフセット設定
		GetModelSet()->SetCharacterType(CModelSet::CHARACTER_TYPE_ENEMY_MELTYHONEY);
		GetModelSet()->LoadOffset(CModelSet::CHARACTER_TYPE_ENEMY_MELTYHONEY);

		//モーションoff
		CCharacter::GetModelSet()->SetUseMotion(false);
		CCharacter::GetModelSet()->SetMotion(CModelSet::CHARACTER_MOTION_STATE_NONE);

		// 当たり判定生成
		GetCollision()->SetSize(ENEMY_MELTYHONEY_COLLISIONSIZE);

		//HP設定
		CCharacter::SetLife(ENEMY_MELTYHONEY_LIFE);

		break;

	case CWeakEnemy::ENEMY_TYPE::ENEMY_ZYCOCCA:
		//オフセット設定
		GetModelSet()->SetCharacterType(CModelSet::CHARACTER_TYPE_ENEMY_ZYCOCCA);
		GetModelSet()->LoadOffset(CModelSet::CHARACTER_TYPE_ENEMY_ZYCOCCA);

		//モーションoff
		CCharacter::GetModelSet()->SetUseMotion(false);
		CCharacter::GetModelSet()->SetMotion(CModelSet::CHARACTER_MOTION_STATE_NONE);

		// 当たり判定生成
		GetCollision()->SetSize(ENEMY_ZYCOCCA_COLLISIONSIZE);

		//HP設定
		CCharacter::SetLife(ENEMY_ZYCOCCA_LIFE);


		break;

	default:
		break;
	}

	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_NORMAL);

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
		//画面の左端より左に行った場合は死亡扱い
		if (CManager::GetRenderer()->GetMinScreenPos().x > GetPosition().x)
		{
			//死亡
			DeathReaction();
		}
		return;
	}

	//更新
	UpdateVehicle();

	//debug
	//CCharacter::GetMove().x += 1.0f;

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
	char aTreeName[MAX_TEXT] = {};
	sprintf(aTreeName, "WeakEnemyInfo [%d]", CScene::GetID());

	if (ImGui::TreeNode(aTreeName))
	{
		ImGui::Text("m_Attack [%d]", m_Attack);

		CEnemy::DebugInfo();

		if (m_pShield)
		{
			m_pShield->DebugInfo();
		}

		if (m_pKnife)
		{
			m_pKnife->DebugInfo();
		}

		ImGui::TreePop();
	}

	//オフセットビューワ
	if (GetEnemyType() == CWeakEnemy::ENEMY_TYPE::ENEMY_ZYCOCCA)
	{
		CDebug_ModelViewer::OffsetViewer(CCharacter::GetModelSet()->GetCharacterModelList());
	}

}
//====================================================================
//乗り物の更新
//====================================================================
void CWeakEnemy::UpdateVehicle()
{
	switch (GetEnemyType())
	{
	case CEnemy::ENEMY_TYPE::ENEMY_MELTYHONEY:
		//車輪の回転処理
		VehiclePartsRotCondition(GetModelSet()->GetCharacterModelList()[1], MODEL_ROT_TYPE_MOVING, CCharacter::GetMove(), CCharacter::GetShotDirection(), CCharacter::GetCharacterDirection());
		VehiclePartsRotCondition(GetModelSet()->GetCharacterModelList()[2], MODEL_ROT_TYPE_MOVING, CCharacter::GetMove(), CCharacter::GetShotDirection(), CCharacter::GetCharacterDirection());
		VehiclePartsRotCondition(GetModelSet()->GetCharacterModelList()[3], MODEL_ROT_TYPE_MOVING, CCharacter::GetMove(), CCharacter::GetShotDirection(), CCharacter::GetCharacterDirection());
		VehiclePartsRotCondition(GetModelSet()->GetCharacterModelList()[4], MODEL_ROT_TYPE_MOVING, CCharacter::GetMove(), CCharacter::GetShotDirection(), CCharacter::GetCharacterDirection());

		break;

	case CEnemy::ENEMY_TYPE::ENEMY_HELICOPTER:
		//プロペラの回転
		VehiclePartsRotCondition(GetModelSet()->GetCharacterModelList()[1], MODEL_ROT_TYPE_ALWAYS, CCharacter::GetMove(), CCharacter::GetShotDirection(), CCharacter::GetCharacterDirection());

		break;

	case CEnemy::ENEMY_TYPE::ENEMY_ZYCOCCA:
		//車輪の回転処理
		VehiclePartsRotCondition(GetModelSet()->GetCharacterModelList()[1], MODEL_ROT_TYPE_MOVING, CCharacter::GetMove(), CCharacter::GetShotDirection(), CCharacter::GetCharacterDirection());
		VehiclePartsRotCondition(GetModelSet()->GetCharacterModelList()[2], MODEL_ROT_TYPE_MOVING, CCharacter::GetMove(), CCharacter::GetShotDirection(), CCharacter::GetCharacterDirection());

		break;
	default:
		break;
	}
}
//====================================================================
//モデルのクリエイト
//====================================================================
CWeakEnemy *CWeakEnemy::Create(ENEMY_TYPE type)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CWeakEnemy*pWeakEnemy;
	pWeakEnemy = new CWeakEnemy(OBJTYPE_ENEMY);
	pWeakEnemy->SetEnemyType(type);
	// タグの設定
	pWeakEnemy->SetTag(TAG::ENEMY);
	pWeakEnemy->Init();


	return pWeakEnemy;
}
//====================================================================
//デフォルトのモーション設定
//====================================================================
bool CWeakEnemy::DefaultMotion(void)
{
	bool bContinue = false;
	switch (GetEnemyType())
	{
	case CEnemy::ENEMY_TYPE::ENEMY_MELTYHONEY:
	case CEnemy::ENEMY_TYPE::ENEMY_ZYCOCCA:
	case CEnemy::ENEMY_TYPE::ENEMY_HELICOPTER:

		GetModelSet()->SetMotion(CModelSet::CHARACTER_MOTION_STATE_NONE);
		bContinue = false;

		break;
	case CEnemy::ENEMY_TYPE::ENEMY_NORMAL:
	case CEnemy::ENEMY_TYPE::ENEMY_SHIELD:

		GetModelSet()->SetMotion(CModelSet::ENEMY_MOTION_NORMAL);
		bContinue = true;

		break;
	}
	return bContinue;
}
//====================================================================
//ダメージを受けた時のリアクション
//====================================================================
void CWeakEnemy::DamageReaction()
{
	SetState(CCharacter::CHARACTER_STATE_DAMAGE_RED);
}
//====================================================================
//死んだ時のリアクション
//====================================================================
void CWeakEnemy::DeathReaction()
{
	if (CHossoLibrary::Random(10) <= 1)
	{
		// ランダムな確率でアイテムをドロップする
		if (CItem::DropRate())
		{
			//アイテムを生成
			CItem::DropCreate(GetPosition(),
				CItem::ITEMDROP_CHARGE,
				CItem::ITEMDROP_PATTERN_DESIGNATE,
				CItem::ITEMTYPE_NONE);
		}
	}

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

		switch (GetEnemyType())
		{
		case CEnemy::ENEMY_TYPE::ENEMY_NORMAL:
		case CEnemy::ENEMY_TYPE::ENEMY_SHIELD:
			//悲鳴
			CManager::GetSound()->Play(CSound::LABEL_SE_VOICE_ENEMY_DEATH);

			GetModelSet()->SetMotion(CModelSet::ENEMY_MOTION_DEAD_1);

			//血のエフェクト
			CParticle::CreateFromText(GetPosition(), GetShotDirection(), CParticleParam::EFFECT_BLOOD);

			if (m_pKnife)
			{
				m_pKnife->EndMeleeAttack();
			}

			break;

		case CEnemy::ENEMY_TYPE::ENEMY_MELTYHONEY:
		case CEnemy::ENEMY_TYPE::ENEMY_ZYCOCCA:
		case CEnemy::ENEMY_TYPE::ENEMY_HELICOPTER:
			CParticle::CreateFromText(GetPosition(), ZeroVector3, CParticleParam::EFFECT_NO_COLLISION_EXPLOSION);
			SetStateCount(1);

			break;
		default:
			break;
		}

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
