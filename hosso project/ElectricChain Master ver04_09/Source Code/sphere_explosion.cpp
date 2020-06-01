//------------------------------------------------------------------------------
//
//メッシュスフィア処理  [meshsphere.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "renderer.h"
#include "manager.h"
#include "renderer.h"
#include "sphere_explosion.h"
#include "collision.h"
#include "enemy.h"
#include "traces.h"
#include "sound.h"
//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define BLOCK_NUM			(INTEGER2(8,8))						//メッシュのブロック数
#define EXPLOSION_DAMAGE	(35)									//爆発ダメージ
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CSphere_Explosion::CSphere_Explosion()
{
	m_nLife = 0;
}

//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CSphere_Explosion::~CSphere_Explosion()
{

}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CSphere_Explosion::Init()
{
	CMeshSphere::Init();

	return S_OK;

}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CSphere_Explosion::Uninit()
{
	CMeshSphere::Uninit();
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CSphere_Explosion::Update()
{
	//ライフが亡くなったら終了
	if (m_nLife-- < 0)
	{
		Release();
		return;
	}

	//回転
	D3DXVECTOR3 &rRot = GetRot();
	float &rRadius = GetRadius();

	//ちょっと回転
	rRot.y += 0.02f;
	rRot.z += 0.001f;

	//ちょっとずつ拡大
	rRadius += 3.0f;

	//頂点再設定
	ResetVtx(D3DXVECTOR3(rRadius, rRadius, rRadius));

	//色情報取得
	D3DXCOLOR rCol = GetCol();
	rCol.a -= 0.015f;
	//ライフが亡くなったら終了
	if (rCol.a < 0)
	{
		Release();
		return;
	}
	SetCol(rCol);

	//スフィア更新
	CMeshSphere::Update();
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CSphere_Explosion::Draw()
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ライティングOFF
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_LIGHTING_OFF);

	//加算合成
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ALPHABLEND_ADD);

	//Zテスト無効でZライティング有効
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_ON_ZWRITING_OFF);

	//描画
	CMeshSphere::Draw();

	//Zテスト通常
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);

	//通常合成
	CManager::GetRenderer()->SetRendererCommand(CRenderer::REDNERER_ALPHABLEND_DEFAULT);

	//ライティングON
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_LIGHTING_ON);
}
//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CSphere_Explosion::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}
//------------------------------------------------------------------------------
//生成
//------------------------------------------------------------------------------
std::shared_ptr<CSphere_Explosion> CSphere_Explosion::Create(D3DXVECTOR3 const pos, float const fRadius, int const nLife)
{
	std::shared_ptr<CSphere_Explosion> pSphereExplosion(new CSphere_Explosion);

	if (pSphereExplosion)
	{
		//初期化　情報設定
		pSphereExplosion->Init();
		pSphereExplosion->SetPos(pos);
		pSphereExplosion->SetSize(D3DXVECTOR3(fRadius * 2.0f, fRadius* 2.0f, fRadius* 2.0f));
		pSphereExplosion->SetBlockNum(BLOCK_NUM);
		pSphereExplosion->m_nLife = nLife;

		//頂点設定
		pSphereExplosion->MakeVertex();
		pSphereExplosion->SetNormal();

		//マトリックスの計算　このFでしか使わない
		CHossoLibrary::CalcMatrix(pSphereExplosion->GetMtx(), pSphereExplosion->GetPos(), pSphereExplosion->GetRot());

		//判定の生成
		pSphereExplosion->m_pCollision = CCollision::Create(pSphereExplosion->GetMtx(),CCollision::COLLISION_EXPLOSION);
		pSphereExplosion->m_pCollision->SetCollisionInfo(fRadius * 1.5f, 0.0f);

		//連鎖
		pSphereExplosion->CollisionExplosion();

		//痕跡の大きさ　空中で発生させた時は小さくする
		float fTracesRadius = fRadius * 5.0f - (pos.y);

		//床の爆発の痕跡を残す
		CTraces::Create(D3DXVECTOR3(pos.x, 0.0f, pos.z), D3DXVECTOR3(fTracesRadius, 0.0f, fTracesRadius));

		//テクスチャ張り付け
		pSphereExplosion->BindTexture(CTexture::GetTexture(CTexture::TEX_SPHEREEXPLOISON));

		//音再生
		CManager::GetSound()->Play(CSound::LABEL_SE_EXPLOSION);

		//シーンに追加
		pSphereExplosion->SetObjType(OBJTYPE_EFFECT_SPHERE);
		pSphereExplosion->AddSharedList(pSphereExplosion);

		//頂点更新
		pSphereExplosion->Update();

		CHossoLibrary::StartVibration(5);
	}

	return pSphereExplosion;
}

//------------------------------------------------------------------------------
//爆発の判定
//------------------------------------------------------------------------------
void CSphere_Explosion::CollisionExplosion()
{
	//シーンのリスト
	std::vector<std::shared_ptr<CScene>> pSceneList;

	//シーン情報取得
	CScene::GetSceneList(CScene::OBJTYPE_ENEMY, pSceneList);

	//配列に入ってるか
	if (!pSceneList.empty())
	{
		//要素分
		for (size_t nCnt = 0; nCnt < pSceneList.size(); nCnt++)
		{
			//ポインタ取得 CMeshField型にキャスト
			CEnemy *pEnemy = ((CEnemy*)pSceneList[nCnt].get());
			//nullcheck
			if (pEnemy)
			{
				//無敵判定のないとき
				if (!pEnemy->GetInvincible())
				{
					if (m_pCollision->CollisionExplosion(pEnemy->GetCollision()))
					{
						pEnemy->ApplyDamage(EXPLOSION_DAMAGE, 0);
					}
				}
			}
		}
	}
}