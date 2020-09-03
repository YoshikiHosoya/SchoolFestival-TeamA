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
#include "enemy.h"
#include "map.h"
#include "basemode.h"
#include "item.h"
#include "sound.h"
// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define KNIFE_ORBIT_OFFSET (D3DXVECTOR3(0.0,0.0,-30.0f))
#define PLAYER_KNIFE_DAMAGE (20)

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

	//ワールド座標更新
	m_worldpos = D3DXVECTOR3(m_HandMatrix->_41, m_HandMatrix->_42, m_HandMatrix->_43);

	if (m_bAttack)
	{
		//当たり判定処理
		CollisionKnife();
	}

	if (m_pCollision != nullptr)
	{
		// 継続時間をマイナスする
		m_pCollision->SetTime(m_pCollision->GetTime() - 1);

		// 継続時間が0以下になったら削除
		if (m_pCollision->GetTime() <= 0)
		{
			//当たり判定削除
			delete m_pCollision;
			m_pCollision = nullptr;
		}
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
	//char aDebugString[64];

	////軌跡が出てるかどうか
	//m_pOrbit ?
	//	sprintf(aDebugString, "Orbit_ON\n") :	//true
	//	sprintf(aDebugString, "Orbit_OFF\n");	//false

	////デバッグ表記
	//CDebugProc::Print("%s", aDebugString);
}

// =====================================================================================================================================================================
// 生成
// =====================================================================================================================================================================
CKnife * CKnife::Create(D3DXMATRIX * mtx, D3DXVECTOR3 knifesize, TAG tag)
{
	// 変数
	CKnife *pKnife;

	// メモリの確保
	pKnife = new CKnife(OBJTYPE_MODEL);

	// 初期化
	pKnife->Init();

	// マトリックス代入
	pKnife->m_HandMatrix = mtx;

	// タグの設定
	pKnife->SetTag(tag);

	// 判定の大きさ設定
	pKnife->m_KnifeCollisionSize = knifesize;

	//ワールド座標設定
	pKnife->m_worldpos = D3DXVECTOR3(pKnife->m_HandMatrix->_41, pKnife->m_HandMatrix->_42, pKnife->m_HandMatrix->_43);

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

	// 既に判定があったら削除する
	if (m_pCollision)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}

	// 判定の生成
	m_pCollision = CCollision::Create();
	// 当たり判定が継続する時間の設定
	m_pCollision->SetTime(60);

	if (m_pCollision)
	{
		// 判定の設定
		m_pCollision->SetPos(&m_worldpos);
		m_pCollision->SetSize(m_KnifeCollisionSize);
		m_pCollision->DeCollisionCreate(CCollision::COLLISIONTYPE_NORMAL);
		m_pCollision->SetGameObject(this);
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
		//当たり判定削除
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
	bool bHit = false;
	//ゲームの時のみ
	//ビューワ上とかで判定おこさない
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		//nullcheck
		if (m_pCollision)
		{
			//持ち主がプレイヤーの場合
			if (GetTag() == TAG::PLAYER_1 || GetTag() == TAG::PLAYER_2)
			{
				//敵、捕虜、障害物と判定
				if (m_pCollision->ForPlayerBulletCollision(PLAYER_KNIFE_DAMAGE, PLAYER_KNIFE_DAMAGE, true))
				{
					//true
					bHit = true;
				}
			}
			//持ち主が敵の場合
			else if (GetTag() == TAG::ENEMY)
			{
				//プレイヤー側との判定
				if (m_pCollision->ForEnemyCollision(1, 1, true))
				{
					//当たってた時
					bHit = true;
				}
			}
		}
	}

	//当たっていた場合
	if (bHit)
	{
		//音再生
		CManager::GetSound()->Play(CSound::LABEL_SE_KNIFE_HIT);
	}
}
