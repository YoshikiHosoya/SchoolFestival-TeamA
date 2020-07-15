//------------------------------------------------------------------------------
//
//当たり判定付きテクスチャアニメーション3D処理  [TexAnimation3D_Collision.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "TexAnimation3D_Collision.h"
#include "manager.h"
#include "renderer.h"
#include "collision.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CTexAnimation3D_Collision::CTexAnimation3D_Collision()
{

}
//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CTexAnimation3D_Collision::CTexAnimation3D_Collision(OBJ_TYPE obj) : CTexAnimation3D(obj)
{

}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CTexAnimation3D_Collision::~CTexAnimation3D_Collision()
{
	//nullcheck
	if (m_pCollision)
	{
		//当たり判定削除
		delete m_pCollision;
		m_pCollision = nullptr;
	}
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CTexAnimation3D_Collision::Init()
{
	m_CollisionPosOrigin = ZeroVector3;

	//初期化処理
	if (FAILED(CTexAnimation3D::Init()))
	{
		return E_FAIL;
	}
	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CTexAnimation3D_Collision::Uninit()
{
	//終了処理
	CTexAnimation3D::Uninit();
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CTexAnimation3D_Collision::Update()
{
	//更新処理
	CTexAnimation3D::Update();

	//当たり判定のカウントが亡くなった時
	if (m_nCntCollision-- > 0)
	{
		//判定をする
		Collision();
	}
	else
	{
		//nullcheck
		if (m_pCollision)
		{
			//当たり判定削除
			delete m_pCollision;
			m_pCollision = nullptr;
		}
	}

}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CTexAnimation3D_Collision::Draw()
{
	//描画処理
	CTexAnimation3D::Draw();
}
//------------------------------------------------------------------------------
//デバッグ情報表示
//------------------------------------------------------------------------------
void CTexAnimation3D_Collision::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //_DEBUG
}
//------------------------------------------------------------------------------
//生成処理
//------------------------------------------------------------------------------
void CTexAnimation3D_Collision::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, CTexture::SEPARATE_TEX_TYPE type,
										int nCntSwitch, CScene::OBJ_TYPE objtype, TAG tag, int nAttackValue, int nCntCollision,bool bOriginCenter)
{
	//メモリ確保
	CTexAnimation3D_Collision *pTexAnimation = new CTexAnimation3D_Collision(objtype);

	//nullcheck
	if (pTexAnimation)
	{
		//初期化
		pTexAnimation->Init();

		//情報をいれる　Scene側
		pTexAnimation->SetPosition(pos);
		pTexAnimation->SetRot(rot);
		pTexAnimation->BindTexture(CTexture::GetSeparateTexture(type));
		pTexAnimation->SetAnimation(ZeroVector2, CTexture::GetSparateTex_UVSize(type));
		pTexAnimation->m_tag = tag;
		pTexAnimation->m_nAttackValue = nAttackValue;
		pTexAnimation->m_nCntCollision = nCntCollision;

		//情報をいれる　TexAnimation側
		pTexAnimation->SetTex(type);
		pTexAnimation->SetCntSwitch(nCntSwitch);

		//マトリックス計算
		CHossoLibrary::CalcMatrix(pTexAnimation->GetMtxWorld(), ZeroVector3, rot);

		//当たり判定生成
		pTexAnimation->m_pCollision = CCollision::Create();
		//中央が原点かどうか
		if(bOriginCenter)
		{
			//テクスチャのサイズ設定
			pTexAnimation->SetSize(size);

			pTexAnimation->m_pCollision->SetPos(pTexAnimation->GetPosPtr());
			pTexAnimation->m_pCollision->SetSize(pTexAnimation->GetSize());
		}
		else
		{
			//テクスチャのサイズ設定
			pTexAnimation->SetSizeOfEdgeOrigin(size);

			//頂点座標
			D3DXVECTOR3 VtxPos[4] = {};

			//ローカル　当たり判定の中心
			D3DXVECTOR3 LocalPosOrigin = ZeroVector3;

			//頂点座標算出
			D3DXVec3TransformCoord(&VtxPos[0], &D3DXVECTOR3(-size.x, +size.y * 2.0f, 0.0f), pTexAnimation->GetMtxWorld());
			D3DXVec3TransformCoord(&VtxPos[1], &D3DXVECTOR3(+size.x, +size.y * 2.0f, 0.0f), pTexAnimation->GetMtxWorld());
			D3DXVec3TransformCoord(&VtxPos[2], &D3DXVECTOR3(-size.x, 0.0f, 0.0f), pTexAnimation->GetMtxWorld());
			D3DXVec3TransformCoord(&VtxPos[3], &D3DXVECTOR3(+size.x, 0.0f, 0.0f), pTexAnimation->GetMtxWorld());

			//当たり判定用のローカル座標計算
			D3DXVec3TransformCoord(&LocalPosOrigin, &D3DXVECTOR3(0.0f, size.y, 0.0f), pTexAnimation->GetMtxWorld());


			//計算用の変数　当たり判定のサイズ
			D3DXVECTOR3 Max = D3DXVECTOR3(-1000.0f, -1000.0f, -0.0f);


			//4頂点分
			for (int nCnt = 0; nCnt < 4; nCnt++)
			{
				//頂点情報を取得
				D3DXVECTOR3 vtx = VtxPos[nCnt];
				//最大の頂点座標を比較して出す
				if (Max.x < vtx.x)
				{
					Max.x = vtx.x;
				}
				if (Max.y < vtx.y)
				{
					Max.y = vtx.y;
				}
			}

			//マトリックス計算
			CHossoLibrary::CalcMatrix(pTexAnimation->GetMtxWorld(), pos, rot);

			//当たり判定用の原点作成　ちょっとキャラクター側とかに寄せる
			D3DXVec3TransformCoord(&pTexAnimation->m_CollisionPosOrigin, &D3DXVECTOR3(0.0f, size.y * 0.8f, 0.0f), pTexAnimation->GetMtxWorld());

			//当たり判定の設定
			pTexAnimation->m_pCollision->SetPos(&pTexAnimation->m_CollisionPosOrigin);
			pTexAnimation->m_pCollision->SetSize(D3DXVECTOR3(fabsf(LocalPosOrigin.x - Max.x), fabsf(LocalPosOrigin.y - Max.y), 0.0f) * 2.0f);
		}

		//デバッグの線表示
		pTexAnimation->m_pCollision->DeCollisionCreate(CCollision::COLLISIONTYPE_NORMAL);
	}
}

//------------------------------------------------------------------------------
//当たり判定処理
//------------------------------------------------------------------------------
bool CTexAnimation3D_Collision::Collision()
{
	//nullcheck
	if (m_pCollision)
	{
		//プレイヤーの攻撃だった場合
		if (m_tag == TAG_PLAYER)
		{
			//当たり判定　敵、捕虜、オブジェクトに対して　貫通有
			m_pCollision->ForPlayerBulletCollision(m_nAttackValue, 1, true);
		}
	}

	return false;
}
