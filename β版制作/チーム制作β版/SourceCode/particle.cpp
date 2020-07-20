//------------------------------------------------------------------------------
//
//パーティクル処理  [praticle.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "particle.h"
#include "manager.h"
#include "renderer.h"
#include "ParticleManager.h"
#include "collision.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 CParticle::m_pVtxBuff = nullptr;
int CParticle::m_nVertexID = 0;
int COneParticle::nNumParticleAll = 0;

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define PARAMATER_SAVE_FILENAME ("data/Load/EffectParamater/SaveParamater.txt")

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CParticle::CParticle()
{
	//初期化
	m_bDeleteFlag = false;
	m_posOrigin = ZeroVector3;
	m_rotOrigin = ZeroVector3;
}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CParticle::~CParticle()
{
	//リストの開放
	m_pParticleList.clear();

	if (m_pCollision)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CParticle::Init()
{
	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CParticle::Uninit()
{

}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CParticle::Update()
{
	if (m_pParticleParam->GetType() == CParticleParam::EFFECT_LAZER)
	{
		CDebugProc::Print("Rot >>  %.2f,%.2f,%.2f\n", m_rotOrigin.x, m_rotOrigin.y, m_rotOrigin.z);
	}

	//ライフを減らす
	m_pParticleParam->UpdateParam();

	if (m_pParticleParam->GetAnimation())
	{
		//アニメーション更新処理
		UpdateAnimation();
	}

	//コリジョン
	if (m_pParticleParam->GetCollision() && m_pParticleParam->GetCollisionCnt() >= 0)
	{
		m_pParticleParam->GetCollisionCnt()--;
		Collision();
	}
	else
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}

	//ライフが0以下になった時かアニメーションが終了した時
	if (m_pParticleParam->GetLife() <= 0 || CTexAnimationBase::GetEndFlag())
	{
		//消す
		m_bDeleteFlag = true;
		return;
	}
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CParticle::Draw()
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ライティングOFF
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_LIGHTING_OFF);

	if (m_pParticleParam->GetAlphaBlend())
	{
		//加算合成
		CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ALPHABLEND_ADD);
	}

	//Zテスト無効でZライティング有効
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_OFF_ZWRITING_ON);

	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	m_pParticleParam->GetAnimation() ?
		pDevice->SetTexture(0, CTexture::GetSeparateTexture(m_pParticleParam->GetSeparateTex())) :
		pDevice->SetTexture(0, CTexture::GetTexture(m_pParticleParam->GetTex()));

	//パーティクルのリストの数分
	for (size_t nCnt = 0; nCnt < m_pParticleList.size(); nCnt++)
	{
		//マトリック計算
		CHossoLibrary::CalcMatrixAndBillboard(&m_pParticleList[nCnt]->m_Mtx, m_pParticleList[nCnt]->m_pos, m_pParticleList[nCnt]->m_rot);

		//ビルボード設定
		//CHossoLibrary::SetBillboard(&m_pParticleList[nCnt]->m_Mtx);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_pParticleList[nCnt]->m_Mtx);

		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//プリミティブの種類
			(4 * m_nVertexID) + nCnt * 4,					//開始するインデックス(頂点) (前回までの分で使った頂点) + 現在使う分
			2);												//ポリゴンの枚数
	}

	//頂点ID加算
	m_nVertexID += m_pParticleList.size();

	//Zテスト通常
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);

	//通常合成
	CManager::GetRenderer()->SetRendererCommand(CRenderer::REDNERER_ALPHABLEND_DEFAULT);

	//ライティングON
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_LIGHTING_ON);

}

//------------------------------------------------------------------------------
//デバッグ情報表示
//------------------------------------------------------------------------------
void CParticle::ShowDebugInfo()
{

#ifdef _DEBUG

#endif // _DEBUG
}

//------------------------------------------------------------------------------
//頂点更新
//------------------------------------------------------------------------------
void CParticle::UpdateVertex()
{
	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点ID分進める
	pVtx += (4 * m_nVertexID);

	for (size_t nCnt = 0; nCnt < m_pParticleList.size(); nCnt++)
	{
		//重力をかける場合
		if (m_pParticleParam->GetGravity())
		{
			//↓方向に力を加算
			m_pParticleList[nCnt]->m_move.y -= m_pParticleParam->GetGravityPower();
		}
		//移動
		m_pParticleList[nCnt]->m_pos += m_pParticleList[nCnt]->m_move;

		//中心が原点じゃない場合
		if (m_pParticleParam->GetCollisionSizeCalc())
		{
			//頂点の座標
			pVtx[0].pos = D3DXVECTOR3(-m_pParticleParam->GetSize().x, +m_pParticleParam->GetSize().y * 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(+m_pParticleParam->GetSize().x, +m_pParticleParam->GetSize().y * 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-m_pParticleParam->GetSize().x, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(+m_pParticleParam->GetSize().x, 0.0f, 0.0f);
		}
		else
		{
			//頂点の座標
			pVtx[0].pos = D3DXVECTOR3(-m_pParticleParam->GetSize().x, m_pParticleParam->GetSize().y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(m_pParticleParam->GetSize().x, m_pParticleParam->GetSize().y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-m_pParticleParam->GetSize().x, -m_pParticleParam->GetSize().y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(m_pParticleParam->GetSize().x, -m_pParticleParam->GetSize().y, 0.0f);
		}
		//頂点の座標
		pVtx[0].col = m_pParticleParam->GetCol();
		pVtx[1].col = m_pParticleParam->GetCol();
		pVtx[2].col = m_pParticleParam->GetCol();
		pVtx[3].col = m_pParticleParam->GetCol();

		//アニメーションする時はUV計算
		if (m_pParticleParam->GetAnimation())
		{
			D3DXVECTOR2 UV = CTexAnimationBase::CalcUV();
			D3DXVECTOR2 UVsize = CTexture::GetSparateTex_UVSize(CTexAnimationBase::GetEffectTex());

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(UV.x, UV.y);
			pVtx[1].tex = D3DXVECTOR2(UV.x + UVsize.x, UV.y);
			pVtx[2].tex = D3DXVECTOR2(UV.x, UV.y + UVsize.y);
			pVtx[3].tex = D3DXVECTOR2(UV.x + UVsize.x, UV.y + UVsize.y);
		}
		//アニメーションしてない時は通常
		else
		{
			//テクスチャ座標
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}


		pVtx += 4;
	}
	//頂点データをアンロック
	m_pVtxBuff->Unlock();

	//頂点ID加算
	m_nVertexID += m_pParticleList.size();
}

//------------------------------------------------------------------------------
//生成
//パーティクルのクラスを用いて生成
//------------------------------------------------------------------------------
void CParticle::CreateFromParam(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CParticleParam *pInputParam)
{
	//メモリ確保
	std::unique_ptr<CParticle> pParticle(new CParticle);

	//nullcheck
	if (pParticle)
	{
		//初期化
		pParticle->Init();

		//パーティクルのパラメータのメモリ確保
		CParticleParam *pParam = new CParticleParam;

		//nullcheck
		if (pParam)
		{
			//情報設定
			//Uniqueptrを使うとオペレータできなかったから普通のポインタ同士でオペレータ
			*pParam = pInputParam;

			//メンバのポインタに格納
			pParticle->m_pParticleParam.reset(std::move(pParam));

			//パーティクルの設定
			pParticle->SetParticle(pos, rot, pParam);

			//オブジェタイプ設定してSceneに所有権を渡す
			CParticleManager::AddParticleList(std::move(pParticle));
		}
	}
}

//------------------------------------------------------------------------------
//テクスチャ破棄
//------------------------------------------------------------------------------
void CParticle::ReleaseVertex()
{
	//nullcheck
	if (m_pVtxBuff)
	{
		//バッファの開放
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//------------------------------------------------------------------------------
//頂点IDリセット
//------------------------------------------------------------------------------
void CParticle::ResetVertexID()
{
	m_nVertexID = 0;
}

//------------------------------------------------------------------------------
//テキスト情報を元にパーティクル作成
//------------------------------------------------------------------------------
void CParticle::CreateFromText(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CParticleParam::PARTICLE_TEXT type,TAG tag, int nAttack)
{
	//メモリ確保
	std::unique_ptr<CParticle> pParticle(new CParticle);

	//nullcheck
	if (pParticle)
	{
		//初期化
		pParticle->Init();
		pParticle->m_Tag = tag;

		//パーティクルのパラメータのメモリ確保
		CParticleParam *pParam = new CParticleParam;

		//nullcheck
		if (pParam)
		{
			//情報設定
			//Uniqueptrを使うとオペレータできなかったから普通のポインタ同士でオペレータ
			*pParam = *CParticleParam::GetDefaultParam(type);

			//攻撃力が入力されていた場合
			if (nAttack > 0)
			{
				pParam->GetCollisionAttackValue() = nAttack;
			}

			//メンバのポインタに格納
			pParticle->m_pParticleParam.reset(std::move(pParam));

			//パーティクルの設定
			pParticle->SetParticle(pos, rot, pParam);

			//オブジェタイプ設定してSceneに所有権を渡す
			CParticleManager::AddParticleList(std::move(pParticle));
		}
	}
}
//------------------------------------------------------------------------------
//頂点バッファ確保
//------------------------------------------------------------------------------
HRESULT CParticle::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_PARTICLE * 4,	//確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,			//頂点フォーマット
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr);

	//頂点情報初期化
	ResetVertex();

	return S_OK;
}
//------------------------------------------------------------------------------
//頂点情報初期化
//------------------------------------------------------------------------------
void CParticle::ResetVertex()
{
	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		//頂点の座標
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//頂点の同次座標
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点の色
		pVtx[0].col = WhiteColor;
		pVtx[1].col = WhiteColor;
		pVtx[2].col = WhiteColor;
		pVtx[3].col = WhiteColor;

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点データをアンロック
	m_pVtxBuff->Unlock();
}
//------------------------------------------------------------------------------
//パーティクル設定
//------------------------------------------------------------------------------
void CParticle::SetParticle(D3DXVECTOR3 const & pos, D3DXVECTOR3 const & rot, CParticleParam * pParam)
{
	//変数宣言
	float fAngleX, fAngleY;
	D3DXVECTOR3 move;
	float fSpeed;

	m_posOrigin = pos;
	m_rotOrigin = rot;

	//生成する個数分
	for (int nCnt = 0; nCnt < pParam->GetNumber(); nCnt++)
	{
		//0除算防止
		if (pParam->GetSpeed() <= 0)
		{
			move = ZeroVector3;
		}
		else
		{
			pParam->GetSpeedRandom() ?
				fSpeed = float(rand() % 1000 / 1000.0f) * pParam->GetSpeed() :
				fSpeed = pParam->GetSpeed();

			//パーティクルの飛ぶ距離をランダム生成
			switch (pParam->GetShape())
			{
			case CParticleParam::SHAPE_SPHERE:

				//360度ランダム 3.14 - 3.14
				fAngleX = CHossoLibrary::Random_PI();
				fAngleY = CHossoLibrary::Random_PI();

				//移動の方向を設定
				move = D3DXVECTOR3(sinf(fAngleY) * sinf(fAngleX) * fSpeed,
					sinf(fAngleY) * cosf(fAngleX) * fSpeed,
					cosf(fAngleY) * cosf(fAngleX) * fSpeed);
				break;
			case CParticleParam::SHAPE_CIRCLE_XY:
				//360度ランダム 3.14 - 3.14
				fAngleX = CHossoLibrary::Random_PI();
				fAngleY = CHossoLibrary::Random_PI();

				//移動の方向を設定
				move = D3DXVECTOR3(sinf(fAngleX) *  fSpeed,
					cosf(fAngleX) * fSpeed,
					0.0f);
				break;

			case CParticleParam::SHAPE_CONE:
				//移動の方向を設定
				//視点の目的地の計算
				fAngleX = pParam->GetRot().x + CHossoLibrary::Random(pParam->GetRange());
				fAngleY = pParam->GetRot().y + CHossoLibrary::Random(pParam->GetRange());

				move = D3DXVECTOR3(-sinf(fAngleY) * cosf(fAngleX) * fSpeed,
					sinf(fAngleX) * fSpeed,
					-cosf(fAngleY) * cosf(fAngleX) * fSpeed);


				break;
			case CParticleParam::SHAPE_LINE:
				//移動の方向を設定
				//視点の目的地の計算
				fAngleX = pParam->GetRot().x;
				fAngleY = pParam->GetRot().y;

				fAngleX += rot.x;
				fAngleY += rot.y;

				move = D3DXVECTOR3(-sinf(fAngleY) * cosf(fAngleX) * fSpeed,
					sinf(fAngleX) * fSpeed,
					-cosf(fAngleY) * cosf(fAngleX) * fSpeed);

				break;
			default:
				break;
			}
		}

		if (pParam->GetType() == CParticleParam::EFFECT_LAZER)
		{
			std::unique_ptr<COneParticle>pOneParticle = COneParticle::Create(pos, move, D3DXVECTOR3(0.0f, 0.0f, rot.x - D3DX_PI * 0.5f));
			//配列に追加
			m_pParticleList.emplace_back(std::move(pOneParticle));
		}
		else
		{

			//パーティクル生成
			std::unique_ptr<COneParticle>pOneParticle = COneParticle::Create(pos, move, D3DXVECTOR3(rot));
			//配列に追加
			m_pParticleList.emplace_back(std::move(pOneParticle));
		}
	}

	//アニメーションのパラメータ設定
	SetAnimationParam();

	//判定があるときは当たり判定のポインタ作成
	if (m_pParticleParam->GetCollision())
	{
		SetCollsionParam();
	}
	//頂点の更新
	UpdateVertex();
}

//------------------------------------------------------------------------------
//アニメーションに関する情報設定
//------------------------------------------------------------------------------
void CParticle::SetAnimationParam()
{
	CTexAnimationBase::SetLife(m_pParticleParam->GetLife());
	CTexAnimationBase::SetTex(m_pParticleParam->GetSeparateTex());
	CTexAnimationBase::SetLoop(m_pParticleParam->GetAnimationLoop());
	CTexAnimationBase::SetCntSwitch(m_pParticleParam->GetAnimationCntSwitch());

}

//------------------------------------------------------------------------------
//コリジョンの情報設定
//------------------------------------------------------------------------------
void CParticle::SetCollsionParam()
{
	m_pCollision = CCollision::Create();

	m_pCollision->SetPos(&m_posOrigin);
	m_pCollision->SetSize(m_pParticleParam->GetCollisionSize());

	D3DXMATRIX RotationMatrix;

	//当たり判定生成
	m_pCollision = CCollision::Create();

	//nullcheck
	if (m_pCollision)
	{
		//中央が原点かどうか
		if (!m_pParticleParam->GetCollisionSizeCalc())
		{
			m_pCollision->SetPos(&m_posOrigin);
			m_pCollision->SetSize(m_pParticleParam->GetCollisionSize() * 2);
		}
		else
		{
			//角度調整
			m_rotOrigin.z = m_rotOrigin.y;
			m_rotOrigin.y = 0.0f;
			m_rotOrigin.x = 0.0f;

			//マトリックス計算
			CHossoLibrary::CalcMatrix(&RotationMatrix, ZeroVector3, m_rotOrigin);

			//頂点座標
			D3DXVECTOR3 VtxPos[4] = {};

			//ローカル　当たり判定の中心
			D3DXVECTOR3 LocalPosOrigin = ZeroVector3;

			D3DXVECTOR3 size = m_pParticleParam->GetCollisionSize();

			//頂点座標算出
			D3DXVec3TransformCoord(&VtxPos[0], &D3DXVECTOR3(-size.x, +size.y * 2.0f, 0.0f), &RotationMatrix);
			D3DXVec3TransformCoord(&VtxPos[1], &D3DXVECTOR3(+size.x, +size.y * 2.0f, 0.0f), &RotationMatrix);
			D3DXVec3TransformCoord(&VtxPos[2], &D3DXVECTOR3(-size.x, 0.0f, 0.0f), &RotationMatrix);
			D3DXVec3TransformCoord(&VtxPos[3], &D3DXVECTOR3(+size.x, 0.0f, 0.0f), &RotationMatrix);

			//当たり判定用のローカル座標計算
			D3DXVec3TransformCoord(&LocalPosOrigin, &D3DXVECTOR3(0.0f, m_pParticleParam->GetCollisionSize().y, 0.0f), &RotationMatrix);

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
			CHossoLibrary::CalcMatrix(&RotationMatrix, m_posOrigin, m_rotOrigin);

			//当たり判定用の原点作成　ちょっとキャラクター側とかに寄せる
			D3DXVec3TransformCoord(&m_posOrigin, &D3DXVECTOR3(0.0f, m_pParticleParam->GetCollisionSize().y * 0.8f, 0.0f), &RotationMatrix);

			//当たり判定の設定
			m_pCollision->SetPos(&m_posOrigin);
			m_pCollision->SetSize(D3DXVECTOR3(fabsf(LocalPosOrigin.x - Max.x), fabsf(LocalPosOrigin.y - Max.y), 0.0f) * 2.0f);
		}

		//デバッグの線表示
		m_pCollision->DeCollisionCreate(CCollision::COLLISIONTYPE_NORMAL);
	}
}


//------------------------------------------------------------------------------
//判定
//------------------------------------------------------------------------------
void CParticle::Collision()
{
//nullcheck
	if (m_pCollision)
	{
		//プレイヤーの攻撃だった場合
		if (m_Tag == TAG_PLAYER)
		{
			if (CManager::GetGameState() == CManager::MODE_GAME)
			{
				//当たり判定　敵、捕虜、オブジェクトに対して　貫通有
				m_pCollision->ForPlayerBulletCollision(m_pParticleParam->GetCollisionAttackValue(), m_pParticleParam->GetCollisionAttackValue(), true);
			}
		}
	}
}