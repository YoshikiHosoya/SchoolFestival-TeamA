// =====================================================================================================================================================================
//
// ナイフの処理 [Knife.h]
// Author : Yoshiki Hosoya
//
// =====================================================================================================================================================================
#include "Knife.h"
#include "manager.h"
#include "renderer.h"
#include "orbit.h"
#include "collision.h"
// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define KNIFE_ORBIT_OFFSET (D3DXVECTOR3(0.0,0.0,-30.0f))

// =====================================================================================================================================================================
// コンストラクタ
// =====================================================================================================================================================================
CKnife::CKnife(OBJ_TYPE type) :CModel(type)
{
}

// =====================================================================================================================================================================
// デストラクタ
// =====================================================================================================================================================================
CKnife::~CKnife()
{
}

// =====================================================================================================================================================================
// 初期化処理
// =====================================================================================================================================================================
HRESULT CKnife::Init()
{
	// 初期化
	CModel::Init();

	m_bAttack = false;
	m_pOrbit = nullptr;
	m_worldpos = ZeroVector3;

	return S_OK;
}

// =====================================================================================================================================================================
// 終了処理
// =====================================================================================================================================================================
void CKnife::Uninit(void)
{
	// 終了
	CModel::Uninit();
}

// =====================================================================================================================================================================
// 更新処理
// =====================================================================================================================================================================
void CKnife::Update(void)
{
	// 更新
	CModel::Update();

	if (m_bAttack)
	{
		//当たり判定処理
		CollisionKnife();
	}
}

// =====================================================================================================================================================================
// 描画処理
// =====================================================================================================================================================================
void CKnife::Draw(void)
{
	//攻撃しているかどうか
	if (m_bAttack)
	{
		// 描画
		CModel::Draw(*m_HandMatrix);
	}
}
// =====================================================================================================================================================================
// デバッグ
// =====================================================================================================================================================================
void CKnife::DebugInfo()
{
	char aDebugString[64];

	//軌跡が出てるかどうか
	m_pOrbit ?
		sprintf(aDebugString, "Orbit_ON\n") :	//true
		sprintf(aDebugString, "Orbit_OFF\n");	//false

	//デバッグ表記
	CDebugProc::Print("%s", aDebugString);
}

// =====================================================================================================================================================================
// 生成
// =====================================================================================================================================================================
CKnife * CKnife::Create(D3DXMATRIX *mtx)
{
	// 変数
	CKnife *pKnife;

	// メモリの確保
	pKnife = new CKnife(OBJTYPE_MODEL);

	// 初期化
	pKnife->Init();

	// マトリックス代入
	pKnife->m_HandMatrix = mtx;

	// 位置の設定
	pKnife->SetPosition(D3DXVECTOR3(ZeroVector3));

	// モデルタイプの設定
	pKnife->SetType(GUN_MODEL);

	// モデルカウントの設定
	pKnife->SetModelConut(MODEL_KNIFE);

	return pKnife;
}

// =====================================================================================================================================================================
// 攻撃開始
// =====================================================================================================================================================================
void CKnife::StartMeleeAttack()
{
	//マトリックス計算
	//軌跡の初期座標用
	CHossoLibrary::CalcMatrix(GetMatrix(), GetPosition(), GetRot());

	//手のマトリックス計算
	D3DXMatrixMultiply(GetMatrix(),GetMatrix(), GetHandMtx());

	//軌跡作成
	m_pOrbit = COrbit::Create(GetMatrix());

	//nullcheck
	if (m_pOrbit)
	{
		m_pOrbit->SetCol(RedColor);
		m_pOrbit->SetPosOffset(KNIFE_ORBIT_OFFSET);
	}

	//コリジョン生成
	m_pCollision = CCollision::Create();
	if (m_pCollision)
	{
		m_pCollision->SetPos(&D3DXVECTOR3(m_HandMatrix->_41, m_HandMatrix->_42, m_HandMatrix->_43));
		m_pCollision->SetSize(D3DXVECTOR3(80.0f, 60.0f, 0.0f));
		m_pCollision->DeCollisionCreate(CCollision::COLLISIONTYPE_NORMAL);

	}

	//攻撃終了
	m_bAttack = true;

}

// =====================================================================================================================================================================
// 攻撃終了
// =====================================================================================================================================================================
void CKnife::EndMeleeAttack()
{
	//nullcheck
	if (m_pOrbit)
	{
		//軌跡削除
		m_pOrbit->DeleteOrbit();
		m_pOrbit = nullptr;
	}

	//nullcheck
	if (m_pCollision)
	{
		//軌跡削除
		delete m_pCollision;
		m_pCollision = nullptr;
	}

	//攻撃状態終了
	m_bAttack = false;
}

// =====================================================================================================================================================================
// ナイフの攻撃判定処理
// =====================================================================================================================================================================
void CKnife::CollisionKnife()
{
	if (CManager::GetGameState() == CManager::MODE_GAME)
	{

		if (m_pCollision)
		{
			//当たり判定
			//敵、捕虜、オブジェクトに対して判定
			m_pCollision->ForPlayerBulletCollision(10, 10, true);
		}
	}
}
