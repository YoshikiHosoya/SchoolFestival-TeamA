// =====================================================================================================================================================================
//
// 捕虜の処理 [prisoner.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "prisoner.h"
#include "model.h"
#include "collision.h"
#include "game.h"
#include "manager.h"
#include "map.h"
#include "item.h"
#include "debugproc.h"
//====================================================================
//マクロ定義
//====================================================================
#define PRISONER_COLLISION_SIZE			(D3DXVECTOR3(50.0f,65.0f,0.0f))			 //捕虜のサイズ
#define PRISONER_DIETIME				(180)									 //捕虜が消滅するまでの時間

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CPrisoner::CPrisoner(OBJ_TYPE type) :CCharacter(type)
{
	// ポインタの初期化
	m_pCollision		= nullptr;
	// 捕虜の初期状態
	m_PrisonerState		= PRISONER_STATE_STAY;
	// 捕虜が消滅するまでのカウントを初期化
	m_nDieCount			= 0;
}
// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CPrisoner::~CPrisoner()
{
#ifdef _DEBUG

	// 当たり判定の削除
	if (m_pCollision != nullptr)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}
#endif // _DEBUG

}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CPrisoner::Init(void)
{
	// キャラの初期化
	CCharacter::Init();
	// オフセットの取得
	LoadOffset(CCharacter::CHARACTER_TYPE_PRISONER);
	// キャラクタータイプの設定
	SetCharacterType(CCharacter::CHARACTER_TYPE_PRISONER);
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 当たり判定生成
	m_pCollision = CCollision::Create();
	m_pCollision->SetPos(&GetPosition());
	m_pCollision->SetSize2D(PRISONER_COLLISION_SIZE);
	m_pCollision->SetMove(&GetMove());
	m_pCollision->SetType(CCollision::COLLISION_PRISONER);
	m_pCollision->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);

	return S_OK;
}
//====================================================================
//終了
//====================================================================
void CPrisoner::Uninit(void)
{
	CCharacter::Uninit();
}
//====================================================================
//更新
//====================================================================
void CPrisoner::Update(void)
{
	// 当たり判定
	if (m_pCollision != nullptr)
	{
		// 座標の更新 pos
		m_pCollision->SetPos(&GetPosition());
	}

	this->PrisonerState();

	// キャラクターの更新
	CCharacter::Update();

	// 捕虜の状態
	CDebugProc::Print("\n 捕虜の状態 %d\n\n", m_PrisonerState);
}
//====================================================================
//描画
//====================================================================
void CPrisoner::Draw(void)
{
	CCharacter::Draw();
}
//====================================================================
//デバッグ
//====================================================================
void CPrisoner::DebugInfo(void)
{
	//CDebugProc::Print("");
}
//====================================================================
//モデルのクリエイト
//====================================================================
CPrisoner *CPrisoner::Create()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// メモリを確保
	CPrisoner*pPrisoner = new CPrisoner(OBJTYPE_PRISONER);
	// 初期化
	pPrisoner->Init();
	// 値を返す
	return pPrisoner;
}
//====================================================================
//捕虜のデフォルトモーション
//====================================================================
bool CPrisoner::DefaultMotion(void)
{
	SetMotion(CCharacter::PRISONER_MOTION_STAY);
	return false;
}

//====================================================================
//捕虜の状態別処理
//====================================================================
void CPrisoner::PrisonerState()
{
	switch (m_PrisonerState)
	{
		// 捕虜の状態アイテムを落とす状態になったら
	case PRISONER_STATE_DROPITEM:
	{
		// アイテムを落とすモーション
		//

		// アイテムの生成
		CItem::RandCreate(GetPosition());
		// 捕虜の状態の変更
		this->SetPrisonerState(PRISONER_STATE_RUN);
	}
	break;

	case PRISONER_STATE_RUN:
	{
		// 横に歩く
		SetMove(D3DXVECTOR3(-1.0f, 0.0f, 1.0f));
		Move(-1.0f, -1.57f);

		// 消滅までのカウントを加算
		m_nDieCount++;
		// カウントが一致値を超えたら
		if (m_nDieCount >= PRISONER_DIETIME)
		{
			// 削除
			Rerease();
		}

	}
	default:
		break;
	}
}

//====================================================================
//移動
//====================================================================
void CPrisoner::Move(float move, float fdest)
{
	GetMove().x += sinf(move * -D3DX_PI) * 1.0f;
	GetMove().z += cosf(move * -D3DX_PI) * 1.0f;
	GetRotDest().y = fdest *  D3DX_PI;
}
