//------------------------------------------------------------------------------
//
//武器となるモデルの処理  [modelparts_weapon.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "modelparts_weapon.h"
#include "renderer.h"
#include "manager.h"
#include "orbit.h"
#include "collision.h"
#include "player.h"
#include "enemy.h"
#include "sound.h"
#include "particle.h"
#include "effectanimation3D.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CModelParts_Weapon::CModelParts_Weapon()
{

}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CModelParts_Weapon::~CModelParts_Weapon()
{

}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CModelParts_Weapon::Init()
{
	//初期化
	CModelParts::Init();

	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CModelParts_Weapon::Uninit()
{
	CModelParts::Uninit();
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CModelParts_Weapon::Update()
{
	//更新
	CModelParts::Update();

	//プレイヤーの武器の場合
	if (m_pWeaponHasCharacter._Get()->GetObjType() == CScene::OBJTYPE_PLAYER)
	{
		//武器の根本の座標
		D3DXVECTOR3 pos = D3DXVECTOR3(GetMtx()->_41, GetMtx()->_42, GetMtx()->_43);

		//剣の先端の座標
		D3DXVECTOR3 pos2;

		//マトリックスの計算で適当に出す
		D3DXVec3TransformCoord(&pos2, &D3DXVECTOR3(0.0f,100.0f,0.0f), GetMtx());

		//差分計算
		D3DXVECTOR3 posdif = pos2 - pos;

		//乱数
		float fRand = (float)(rand() % 100) / 100.0f;

		//エフェクト パチパチしてるような
		CParticle::Create(pos + (posdif * fRand), 30, 2.5f, D3DXCOLOR(0.4f, 0.4f, 0.8f, 0.7f), 7, 4);
		CParticle::Create(pos + (posdif * fRand), 5, 12.0f, D3DXCOLOR(0.4f, 0.4f, 0.8f, 0.4f), 2, 1);
		CEffectAnimation3D::Create(pos + (posdif * fRand), D3DXVECTOR3((float)(rand() % 100), (float)(rand() % 100), 0.0f), CTexture::SEPARATE_TEX_EFFECT_STANING, D3DXCOLOR(0.4f,0.4f,1.0f,1.0f), CHossoLibrary::Random_PI(), 1);
	}

	//判定処理
	Collision();
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CModelParts_Weapon::Draw()
{
	CModelParts::Draw();
}
//------------------------------------------------------------------------------
//生成
//------------------------------------------------------------------------------
std::unique_ptr<CModelParts_Weapon> CModelParts_Weapon::Create(std::shared_ptr<CModelInfo> pModelInfo)
{
	//メモリ確保
	std::unique_ptr<CModelParts_Weapon> pModelParts_Weapon(new CModelParts_Weapon);

	//初期化
	pModelParts_Weapon->Init();

	//モデル情報設定
	pModelParts_Weapon->BindModelInfo(pModelInfo);

	//生成した情報
	return std::move(pModelParts_Weapon);
}

//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CModelParts_Weapon::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}

//------------------------------------------------------------------------------
//軌跡設定
//------------------------------------------------------------------------------
void CModelParts_Weapon::StartAttack()
{
	//nullcheck
	if (!m_pOrbit)
	{
		//軌跡生成
		m_pOrbit = COrbit::Create(GetMtx());
	}
	//nulcheck
	if (!m_pCollision)
	{
		m_pCollision = CCollision::Create(GetMtx(), CCollision::COLLISION_WEAPON);
	}
}
//------------------------------------------------------------------------------
//攻撃終了
//------------------------------------------------------------------------------
void CModelParts_Weapon::EndAttack()
{
	//nullcheck
	if (m_pOrbit)
	{
		//消去
		m_pOrbit->DeleteOrbit();
		m_pOrbit = nullptr;
	}

	//nullcehck
	if (m_pCollision)
	{
		//消去
		m_pCollision.reset();
	}

	//0にしとく
	m_nDamage = 0;
	m_nBlueDamage = 0;
	m_fKnockBack_Front = 0.0;
	m_fKnockBack_Up = 0.0f;

}
//------------------------------------------------------------------------------
//攻撃の情報更新
//------------------------------------------------------------------------------
void CModelParts_Weapon::SetAttackInfo(CMotion::MOTION_TYPE motiontype)
{
	//ポインタ取得
	CMotion::ATTACK_INFO *pAttackInfo = CMotion::GetAttackInfo(motiontype);

	//nullcheck
	if (m_pOrbit)
	{
		//軌跡の情報更新
		m_pOrbit->SetCol(pAttackInfo->orbitcol);

		//offset
		m_pOrbit->SetPosOffset(D3DXVECTOR3(0.0f, pAttackInfo->fLength, 0.0f));

	}

	//nulcheck
	if (m_pCollision)
	{
		m_pCollision->SetCollisionInfo(pAttackInfo->fRadius, pAttackInfo->fLength);
	}
	//ダメージ量
	m_nDamage = pAttackInfo->nAttack;
	m_nBlueDamage = pAttackInfo->nBlueAttack;
	m_fKnockBack_Front = pAttackInfo->fKnockBack_Front;
	m_fKnockBack_Up = pAttackInfo->fKnockBack_Up;
}


//------------------------------------------------------------------------------
//当たり判定処理
//------------------------------------------------------------------------------
void CModelParts_Weapon::Collision()
{
	//nullcheck
	if (m_pCollision)
	{
		//デバッグ情報表示
		m_pCollision->ShowDebugInfo();

		//Sceneのリスト
		std::vector<std::shared_ptr<CScene>> pSceneList;

		//持ってるキャラクターのオブジェクトタイプによって判定の対象を変える
		switch (m_pWeaponHasCharacter._Get()->GetObjType())
		{
		case CScene::OBJTYPE_PLAYER:
			//敵のリスト取得
			CScene::GetSceneList(CScene::OBJTYPE_ENEMY, pSceneList);
			break;

		case CScene::OBJTYPE_ENEMY:
			//プレイヤーのリスト取得
			CScene::GetSceneList(CScene::OBJTYPE_PLAYER, pSceneList);
			break;
		default:
			//それ以外は判定しない
			return;
			break;
		}

		//nullcheck
		if (!pSceneList.empty())
		{
			//要素分
			for (size_t nCnt = 0; nCnt < pSceneList.size(); nCnt++)
			{
				//ポインタ取得 CMeshField型にキャスト
				CCharacter *pCharacter = ((CCharacter*)pSceneList[nCnt].get());

				//nullcheck
				if (pCharacter)
				{
					//無敵判定のないとき
					if (!pCharacter->GetInvincible())
					{
						//接触判定
						if (m_pCollision->CollisionCylinder(pCharacter->GetCollision()))
						{
							//ノックバック
							pCharacter->KnockBack(m_fKnockBack_Front, m_fKnockBack_Up,m_pWeaponHasCharacter._Get()->GetRotDest().y);

							//ダメージを与える
							pCharacter->ApplyDamage(m_nDamage, m_nBlueDamage);
						}
					}
				}
			}
		}
	}
}

//------------------------------------------------------------------------------
//敵の無敵状態解除
//------------------------------------------------------------------------------
void CModelParts_Weapon::ResetEnemyInvincible()
{
	//Sceneのリスト
	std::vector<std::shared_ptr<CScene>> pSceneList;

	//持ってるキャラクターのオブジェクトタイプによって判定の対象を変える
	switch (m_pWeaponHasCharacter._Get()->GetObjType())
	{
		//持ってるキャラがプレイヤーの時
	case CScene::OBJTYPE_PLAYER:
		//敵のリスト取得
		CScene::GetSceneList(CScene::OBJTYPE_ENEMY, pSceneList);
		break;

	default:
		//それ以外はなんもしない
		return;
		break;
	}

	//nullcheck
	if (!pSceneList.empty())
	{
		//要素分
		for (size_t nCnt = 0; nCnt < pSceneList.size(); nCnt++)
		{
			//ポインタ取得 CMeshField型にキャスト
			CCharacter *pCharacter = ((CCharacter*)pSceneList[nCnt].get());

			//nullcheck
			if (pCharacter)
			{
				//無敵状態解除
				pCharacter->SetInvincible(false);
			}
		}
	}
}

