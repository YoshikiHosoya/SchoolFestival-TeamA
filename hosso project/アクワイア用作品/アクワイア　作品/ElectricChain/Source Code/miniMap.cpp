//------------------------------------------------------------------------------
//
//ミニマップ処理  [minimap.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "minimap.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "enemy.h"
#include "camera.h"
#include "basemode.h"
#include "scene2D.h"
#include "UI.h"
#include "sphere_explosion.h"
//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define MINIMAP_POS			(D3DXVECTOR3(1180.0f,100.0f,100.0f))
#define MINIMAP_RANGE		(80.0f)
#define MAX_MAPPING			(100)
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CMiniMap::CMiniMap()
{
	m_pEnemyMappingList.clear();
}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CMiniMap::~CMiniMap()
{
	m_pEnemyMappingList.clear();
}
//------------------------------------------------------------------------------
//初期化
//------------------------------------------------------------------------------
HRESULT CMiniMap::Init()
{
	//レーダーの〇
	std::shared_ptr<CScene2D> pMap = CScene2D::Create_Shared(MINIMAP_POS, D3DXVECTOR3(MINIMAP_RANGE * 2, MINIMAP_RANGE * 2, 0.0f), CScene::OBJTYPE_MINIMAP);
	pMap->BindTexture(CTexture::GetTexture(CTexture::TEX_MINIMAP_MAP));

	//敵のマッピングと爆発のマッピング設定
	for (int nCnt = 0; nCnt < MAX_MAPPING; nCnt++)
	{
		//敵のマッピング
		m_pEnemyMappingList.emplace_back(CScene2D::Create_Shared(MINIMAP_POS, D3DXVECTOR3(10.0f, 10.0f, 0.0f),CScene::OBJTYPE_MINIMAP));
		m_pEnemyMappingList[nCnt]->SetDisp(false);
		m_pEnemyMappingList[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_MINIMAP_ENEMY));

		//爆発のマッピング
		m_pExplosionMappingList.emplace_back(CScene2D::Create_Shared(MINIMAP_POS, D3DXVECTOR3(20.0f, 20.0f, 0.0f), CScene::OBJTYPE_MINIMAP));
		m_pExplosionMappingList[nCnt]->SetDisp(false);
		m_pExplosionMappingList[nCnt]->SetVtxCol(YellowColor);
		m_pExplosionMappingList[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_MINIMAP_EXPLOSION));
	}

	//プレイヤーのマッピング
	m_pPlayerMapping = CScene2D::Create_Shared(MINIMAP_POS, D3DXVECTOR3(15.0f, 15.0f, 0.0f), CScene::OBJTYPE_MINIMAP);
	m_pPlayerMapping->SetVtxCol(GreenColor);
	m_pPlayerMapping->BindTexture(CTexture::GetTexture(CTexture::TEX_MINIMAP_PLAYER));

	return S_OK;

}
//------------------------------------------------------------------------------
//終了
//------------------------------------------------------------------------------
void CMiniMap::Uninit()
{

}
//------------------------------------------------------------------------------s
//更新
//------------------------------------------------------------------------------
void CMiniMap::Update()
{
	//マッピング全部を非表示に設定
	for (size_t nCnt = 0; nCnt < MAX_MAPPING; nCnt++)
	{
		m_pEnemyMappingList[nCnt]->SetDisp(false);
		m_pExplosionMappingList[nCnt]->SetDisp(false);
	}

	//Sceneのリスト
	std::vector<std::shared_ptr<CScene>> pSceneList;

	//敵のリスト取得
	CScene::GetSceneList(CScene::OBJTYPE_ENEMY, pSceneList);
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
	float fCameraRot = CManager::GetRenderer()->GetCamera()->GetCameraRot().y;

	//角度設定
	m_pPlayerMapping->SetAngle(-pPlayer->GetRot().y + fCameraRot);

	//nullcheck
	if (!pSceneList.empty() && pPlayer)
	{
		//要素分
		for (size_t nCnt = 0; nCnt < pSceneList.size(); nCnt++)
		{
			//ポインタ取得 CEnemy型にキャスト
			CEnemy *pEnemy = ((CEnemy*)pSceneList[nCnt].get());

			//nullcheck
			if (pEnemy)
			{
				//マップ上の敵の座標計算
				D3DXVECTOR3 posDiff = (pPlayer->GetPos() - pEnemy->GetPos()) * 0.1f;

				//y軸は反転
				posDiff.x *= -1.0f;

				//距離と角度を求める
				float fDistance = D3DXVec2Length(&D3DXVECTOR2(posDiff.x, posDiff.z));
				float fAngle = atan2f(posDiff.x, posDiff.z);

				//範囲内に抑える
				CHossoLibrary::RangeLimit_Equal_Float(fDistance, 0.0f, MINIMAP_RANGE);

				//マッピング上の敵の座標計算
				D3DXVECTOR3 pMappingEnemyPos = ZeroVector3;
				pMappingEnemyPos.x = MINIMAP_POS.x + sinf(fAngle + fCameraRot) * fDistance;
				pMappingEnemyPos.z = MINIMAP_POS.z + cosf(fAngle + fCameraRot) * fDistance;

				//マップ上の敵の座標設定
				m_pEnemyMappingList[nCnt]->SetPos(D3DXVECTOR3(pMappingEnemyPos.x, pMappingEnemyPos.z, 0.0f));
				m_pEnemyMappingList[nCnt]->SetDisp(true);

				//スタン中は青　それ以外は赤
				if (pEnemy->GetStan())
				{
					m_pEnemyMappingList[nCnt]->SetVtxCol(BlueColor);
				}
				else
				{
					m_pEnemyMappingList[nCnt]->SetVtxCol(RedColor);
				}
			}
		}
	}

	//爆発のリスト取得
	CScene::GetSceneList(CScene::OBJTYPE_EFFECT_SPHERE, pSceneList);

	//nullcheck
	if (!pSceneList.empty() && pPlayer)
	{
		//要素分
		for (size_t nCnt = 0; nCnt < pSceneList.size(); nCnt++)
		{
			//ポインタ取得 CSphere_Explosion型にキャスト
			CSphere_Explosion *pExplosion = ((CSphere_Explosion*)pSceneList[nCnt].get());

			//nullcheck
			if (pExplosion)
			{
				//マップ上の敵の座標計算
				D3DXVECTOR3 posDiff = (pPlayer->GetPos() - pExplosion->GetPos()) * 0.1f;

				//y軸は反転
				posDiff.x *= -1.0f;

				//距離と角度を求める
				float fDistance = D3DXVec2Length(&D3DXVECTOR2(posDiff.x, posDiff.z));
				float fAngle = atan2f(posDiff.x, posDiff.z);

				//範囲内に抑える
				CHossoLibrary::RangeLimit_Equal_Float(fDistance, 0.0f, MINIMAP_RANGE);

				//マッピング上の敵の座標計算
				D3DXVECTOR3 pMappingExplosionPos = ZeroVector3;
				pMappingExplosionPos.x = MINIMAP_POS.x + sinf(fAngle + fCameraRot) * fDistance;
				pMappingExplosionPos.z = MINIMAP_POS.z + cosf(fAngle + fCameraRot) * fDistance;

				//マップ上の敵の座標設定
				m_pExplosionMappingList[nCnt]->SetPos(D3DXVECTOR3(pMappingExplosionPos.x, pMappingExplosionPos.z, 0.0f));
				m_pExplosionMappingList[nCnt]->SetDisp(true);
			}
		}
	}
}
//------------------------------------------------------------------------------
//描画
//------------------------------------------------------------------------------
void CMiniMap::Draw()
{

}
//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CMiniMap::ShowDebugInfo()
{
}
//------------------------------------------------------------------------------
//生成処理
//------------------------------------------------------------------------------
void CMiniMap::Create()
{
	//メモリ確保
	std::unique_ptr<CMiniMap> pMap(new CMiniMap);

	if (pMap)
	{
		//初期化
		pMap->Init();

		//オブジェクト設定
		pMap->SetObjType(CScene::OBJTYPE_MINIMAP);
		pMap->AddUniqueList(std::move(pMap));
	}
}
