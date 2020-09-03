// ===================================================================
//
// shieldの処理 [shield.cpp]
// Author : のりさん
//
// ===================================================================
#include "shield.h"
#include "WeakEnemy.h"
#include "collision.h"

// ===================================================================
// 静的メンバ変数の初期化
// ===================================================================

// ===================================================================
// マクロ定義
// ===================================================================
#define SHIELD_LIFE				(12)			// shieldの体力
#define SHIELD_SIZE				(D3DXVECTOR3(30.0f,100.0f,0.0f))
#define SHIELD_OFFSET			(D3DXVECTOR3(0.0f,-30.0f,0.0f))
#define SHIELD_DELETE_COUNT		(60)
#define DAMAGE_FLASH_COUNT		(5)
#define BREAK_SHIELD_DEFAULT	(D3DXVECTOR3(CHossoLibrary::Random(20.0f), 15.0f, 0.0f))
// ===================================================================
// コンストラクタ
// ===================================================================
CShield::CShield(OBJ_TYPE type) :CModel(type)
{
}

// ===================================================================
// デストラクタ
// ===================================================================
CShield::~CShield()
{
}

// ===================================================================
// 初期化処理
// ===================================================================
HRESULT CShield::Init()
{
	m_bBreak = false;

	CModel::Init();
	// 変数初期化
	m_nLife = SHIELD_LIFE;				// 体力
	// 初期化
	SetPosition(D3DXVECTOR3(0.0f,-20.0f,0.0f));
	// 当たり判定生成
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetSize2D(SHIELD_SIZE);
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_NORMAL);

	//ダメージ受けた時の点滅色
	SetAddColor(D3DXCOLOR(1.0f, 0.4f, 0.0f, 0.0f));

	return S_OK;
}

// ===================================================================
// 終了処理
// ===================================================================
void CShield::Uninit(void)
{
	CModel::Uninit();
}

// ===================================================================
// 更新処理
// ===================================================================
void CShield::Update(void)
{
	// 更新
	CModel::Update();


	if (m_nCntState-- <= 0)
	{
		SetColorChangeFlag(false);
	}

	if (m_bBreak)
	{
		//消えるカウントダウン
		m_nDeleteCnt--;

		//盾吹っ飛ばし
		m_BreakShieldMoveValue.y -= 0.5f;
		m_ShieldPos += m_BreakShieldMoveValue;

		//盾回転
		GetRot().x += 0.05f;
		GetRot().z += 0.25f;

		//カウントが0になった時
		if (m_nDeleteCnt <= 0)
		{
			//消去
			Rerease();
			return;
		}
	}
	else
	{
		//盾の座標
		m_ShieldPos = D3DXVECTOR3(m_HasHandMtx->_41, m_HasHandMtx->_42, m_HasHandMtx->_43) + SHIELD_OFFSET;

		//当たり判定の座標設定
		GetCollision()->SetPos(&m_ShieldPos);
	}
}
// ===================================================================
// 描画処理
// ===================================================================
void CShield::Draw(void)
{
	if (m_bBreak)
	{
		SetPosition(m_ShieldPos);
		CModel::Draw();
	}
	else
	{
		CModel::Draw(*m_HasHandMtx);
	}
}
//====================================================================
//モデルのクリエイト
//====================================================================
CShield *CShield::Create()
{
	CShield*pShield;
	pShield = new CShield(OBJTYPE_SHIELD);
	pShield->Init();
	// モデルタイプの設定
	pShield->SetType(WEPON_MODEL);
	// モデルカウントの設定
	pShield->SetModelConut(MODEL_WEPON_SHIELD);

	return pShield;
}
//====================================================================
//ダメージ受ける
//====================================================================
void CShield::AddDamage(int nDamage)
{
	m_nLife -= nDamage;

	//赤く点滅
	SetColorChangeFlag(true);
	m_nCntState = DAMAGE_FLASH_COUNT;


	//ライフがなくなった時
	if (m_nLife <= 0)
	{
		m_HasEnemyPtr->ShieldBreak();

	}
}
//====================================================================
//盾が吹っ飛ぶ設定
//====================================================================
void CShield::AwayShield()
{
	m_bBreak = true;
	m_nDeleteCnt = SHIELD_DELETE_COUNT;
	DeleteCollision();
	SetRot(D3DXVECTOR3(D3DX_PI * 0.5f, D3DX_PI * 0.5f, 0.0f));
	m_BreakShieldMoveValue = (BREAK_SHIELD_DEFAULT);
}