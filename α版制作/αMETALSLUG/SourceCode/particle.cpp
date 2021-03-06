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
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 CParticle::m_pVtxBuff = nullptr;
int CParticle::m_nVertexID = 0;
int COneParticle::nNumParticleAll = 0;

std::vector<std::unique_ptr<CParticleParam>> CParticleParam::m_pParticleDefaultParamList = {};
std::vector<std::string> CParticleParam::m_aFileNameList =
{
	{ "data/Load/EffectParamater/Default.txt" },
	{ "data/Load/EffectParamater/Explosion.txt" },
	{ "data/Load/EffectParamater/Blood.txt" },
	{ "data/Load/EffectParamater/Sumple.txt" },
	{ "data/Load/EffectParamater/BulletOrbit.txt" },

};
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
}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CParticle::~CParticle()
{
	//リストの開放
	m_pParticleList.clear();
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
	//ライフを減らす
	m_pParticleParam->UpdateParam();

	//ライフが0以下になった時
	if (m_pParticleParam->GetLife() <= 0)
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

	//加算合成
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ALPHABLEND_ADD);

	//Zテスト無効でZライティング有効
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_OFF_ZWRITING_ON);

	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, CTexture::GetTexture(m_pParticleParam->GetTex()));

	//パーティクルのリストの数分
	for (size_t nCnt = 0; nCnt < m_pParticleList.size(); nCnt++)
	{
		//マトリック計算
		CHossoLibrary::CalcMatrix(&m_pParticleList[nCnt]->m_Mtx, m_pParticleList[nCnt]->m_pos, m_pParticleList[nCnt]->m_rot);

		//ビルボード設定
		CHossoLibrary::SetBillboard(&m_pParticleList[nCnt]->m_Mtx);

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

		//頂点の座標
		pVtx[0].pos = D3DXVECTOR3(-m_pParticleParam->GetRadius(), m_pParticleParam->GetRadius(), 0.0f);
		pVtx[1].pos = D3DXVECTOR3( m_pParticleParam->GetRadius(), m_pParticleParam->GetRadius(), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-m_pParticleParam->GetRadius(), -m_pParticleParam->GetRadius(), 0.0f);
		pVtx[3].pos = D3DXVECTOR3( m_pParticleParam->GetRadius(), -m_pParticleParam->GetRadius(), 0.0f);

		//頂点の座標
		pVtx[0].col = m_pParticleParam->GetCol();
		pVtx[1].col = m_pParticleParam->GetCol();
		pVtx[2].col = m_pParticleParam->GetCol();
		pVtx[3].col = m_pParticleParam->GetCol();

		pVtx += 4;
	}
	//頂点データをアンロック
	m_pVtxBuff->Unlock();

	//頂点ID加算
	m_nVertexID += m_pParticleList.size();
}

//------------------------------------------------------------------------------
//生成処理
//------------------------------------------------------------------------------
void CParticle::Create(D3DXVECTOR3 pos, int nLife, float fRadius, D3DXCOLOR col, int nNumber,float fSpeed)
{
	//メモリ確保
	std::unique_ptr<CParticle> pParticle(new CParticle);

	//nullcheck
	if (pParticle)
	{
		//初期化
		pParticle->Init();

		//パーティクルのパラメータのメモリ確保
		pParticle->m_pParticleParam.reset(new CParticleParam);

		if (pParticle->m_pParticleParam)
		{
			//情報設定
			pParticle->m_pParticleParam->SetParamater(nLife, fRadius, col,nNumber,fSpeed);

			//パーティクルの設定
			pParticle->SetParticle(pos, pParticle->m_pParticleParam.get());

			//オブジェタイプ設定してSceneに所有権を渡す
			CParticleManager::AddParticleList(std::move(pParticle));
		}
	}
}

//------------------------------------------------------------------------------
//生成
//パーティクルのクラスを用いて生成
//------------------------------------------------------------------------------
void CParticle::CreateFromParam(D3DXVECTOR3 pos, CParticleParam *pInputParam)
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
			pParticle->SetParticle(pos, pParam);

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
void CParticle::CreateFromText(D3DXVECTOR3 pos, CParticleParam::PARTICLE_TEXT type)
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
			*pParam = *CParticleParam::GetDefaultParam(type);

			//メンバのポインタに格納
			pParticle->m_pParticleParam.reset(std::move(pParam));

			//パーティクルの設定
			pParticle->SetParticle(pos, pParam);

			//オブジェタイプ設定してSceneに所有権を渡す
			CParticleManager::AddParticleList(std::move(pParticle));
		}
	}
}
//------------------------------------------------------------------------------
//テキストからパラメータ取得
//------------------------------------------------------------------------------
HRESULT CParticleParam::LoadParticleDefaultParam()
{
	//ファイルポイント
	FILE *pFile;
	char cReadText[128];	//文字として読み取り用
	char cHeadText[128];	//比較する用
	char cDie[128];			//不要な文字
	int n_BoolValue;		//boolに変換するようの格納
	HRESULT hResult = S_OK;

	CParticleParam *pParam;

	//ファイル数分
	for (size_t nCnt = 0; nCnt < m_aFileNameList.size(); nCnt++)
	{
		//ファイル読み込み
		pFile = fopen(m_aFileNameList[nCnt].data(), "r");

		//ファイルが開けた時
		if (pFile != NULL)
		{
			//スクリプトが来るまでループ
			while (strcmp(cHeadText, "SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);	//一文を読み込む
				sscanf(cReadText, "%s", &cHeadText);		//比較用テキストに文字を代入
			}
			//スクリプトだったら
			if (strcmp(cHeadText, "SCRIPT") == 0)
			{
				//エンドスクリプトが来るまでループ
				while (strcmp(cHeadText, "END_SCRIPT") != 0)
				{
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s", &cHeadText);

					//パラメータセットだったら
					if (strcmp(cHeadText, "PARAMSET") == 0)
					{
						//メモリ確保
						pParam = new CParticleParam;

						//エンド来るまでループ
						while (strcmp(cHeadText, "END_PARAMSET") != 0)
						{

							fgets(cReadText, sizeof(cReadText), pFile);
							sscanf(cReadText, "%s", &cHeadText);


							//それぞれの項目を読み込み
							if (strcmp(cHeadText, "SPEEDRANDOM") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &n_BoolValue);
								pParam->m_bSpeedRandom = n_BoolValue ? true : false;
							}
							if (strcmp(cHeadText, "GRAVITY") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &n_BoolValue);
								pParam->m_bGravity = n_BoolValue ? true : false;
							}
							if (strcmp(cHeadText, "SHAPE") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pParam->m_shape);
							}
							if (strcmp(cHeadText, "TEXTURE") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pParam->m_Textype);
							}
							if (strcmp(cHeadText, "LIFE") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pParam->m_nLife);
							}
							if (strcmp(cHeadText, "NUMBER") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pParam->m_nNumber);
							}
							if (strcmp(cHeadText, "RADIUS") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDie, &cDie, &pParam->m_fRadius);
							}
							if (strcmp(cHeadText, "SPEED") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDie, &cDie, &pParam->m_fSpeed);
							}
							if (strcmp(cHeadText, "RANGE") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDie, &cDie, &pParam->m_fRange);
							}
							if (strcmp(cHeadText, "RADIUSDAMPING") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDie, &cDie, &pParam->m_fRadiusDamping);
							}
							if (strcmp(cHeadText, "ALPHADAMPING") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDie, &cDie, &pParam->m_fAlphaDamping);
							}
							if (strcmp(cHeadText, "GRAVITYPOWER") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDie, &cDie, &pParam->m_fGravityPower);
							}
							if (strcmp(cHeadText, "COLOR") == 0)
							{
								sscanf(cReadText, "%s %s %f %f %f %f", &cDie, &cDie,
										&pParam->m_col.r, &pParam->m_col.g, &pParam->m_col.b, &pParam->m_col.a);
							}
							if (strcmp(cHeadText, "ROT") == 0)
							{
								sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
									&pParam->m_rot.x, &pParam->m_rot.y, &pParam->m_rot.z);
							}
							if (strcmp(cHeadText, "END_PARAMSET") == 0)
							{
								pParam->m_ParticleType = (CParticleParam::PARTICLE_TEXT)nCnt;
								m_pParticleDefaultParamList.emplace_back(std::move(pParam));
							}
						}
					}
				}
			}

			//パラメータロード
			std::cout << "DefaultParticleParamLoad >>" << m_aFileNameList[nCnt].data() << NEWLINE;

			//ファイルを閉じる
			fclose(pFile);
		}

		//ファイル読み込めなかった場合
		else
		{
			std::cout << "LoadFailed!!  >>" << m_aFileNameList[nCnt].data() << NEWLINE;
			MessageBox(NULL, "パーティクルのパラメータ読み込み失敗", "警告", MB_ICONWARNING);
			hResult = E_FAIL;
		}
	}
	return S_OK;
}

//------------------------------------------------------------------------------
//パーティクルのパラメータ保存
//------------------------------------------------------------------------------
HRESULT CParticleParam::SaveParticleDefaultParam(CParticleParam *pSaveParam)
{
	FILE *pFile;

	int nRotNum = 0;
	char cWriteText[128];

	//ファイル読み込み
	pFile = fopen(PARAMATER_SAVE_FILENAME, "w");

	//nullcheck
	if (pFile && pSaveParam)
	{
		//ブロックコメント
		fputs(COMMENT02, pFile);
		fputs(COMMENT01, pFile);

		fputs("//ParticleParamater\n", pFile);
		fputs("//読み込み用のテキストにコピーしてください\n", pFile);
		fputs("//Author:Yoshiki Hosoya\n", pFile);

		fputs(COMMENT01, pFile);
		fputs(COMMENT02, pFile);
		fputs(NEWLINE, pFile);

		//ブロックコメント終了//

		//スクリプト
		fputs("SCRIPT", pFile);
		fputs(NEWLINE, pFile);


		//パラメータセット
		fputs("	PARAMSET", pFile);
		fputs(NEWLINE, pFile);

		//改行
		fputs(NEWLINE, pFile);

		//速度がランダムかどうか
		sprintf(cWriteText, "		%s %s %d			%s", "SPEEDRANDOM", &EQUAL, pSaveParam->m_bSpeedRandom, "//速度がランダムかどうか");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		//重力つけるか
		sprintf(cWriteText, "		%s %s %d				%s", "GRAVITY", &EQUAL, pSaveParam->m_bGravity, "//重力をつけるか");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		//パーティクルの出し方
		sprintf(cWriteText, "		%s %s %d				%s", "SHAPE", &EQUAL, pSaveParam->m_shape, "//パーティクルの出し方");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		//テクスチャ
		sprintf(cWriteText, "		%s %s %d				%s", "TEXTURE", &EQUAL, pSaveParam->m_Textype, "//テクスチャ");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		//ライフ
		sprintf(cWriteText, "		%s %s %d				%s", "LIFE", &EQUAL, pSaveParam->m_nLife, "//ライフ");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		//個数
		sprintf(cWriteText, "		%s %s %d				%s", "NUMBER", &EQUAL, pSaveParam->m_nNumber, "//個数");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		//半径
		sprintf(cWriteText, "		%s %s %.1f			%s", "RADIUS", &EQUAL, pSaveParam->m_fRadius, "//半径");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		//速度
		sprintf(cWriteText, "		%s %s %.1f			%s", "SPEED", &EQUAL, pSaveParam->m_fSpeed, "//速度");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		//範囲
		sprintf(cWriteText, "		%s %s %.1f				%s", "RANGE", &EQUAL, pSaveParam->m_fRange, "//範囲");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		//半径の減衰値
		sprintf(cWriteText, "		%s %s %.2f	%s", "RADIUSDAMPING", &EQUAL, pSaveParam->m_fRadiusDamping, "//半径の減衰値");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		//アルファ値の減衰値
		sprintf(cWriteText, "		%s %s %.2f		%s", "ALPHADAMPING", &EQUAL, pSaveParam->m_fAlphaDamping, "//アルファ値の減衰値");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		//重力の強さ
		sprintf(cWriteText, "		%s %s %.2f		%s", "GRAVITYPOWER", &EQUAL, pSaveParam->m_fGravityPower, "//重力の強さ");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		//色
		sprintf(cWriteText, "		%s %s %.1f %.1f %.1f %.1f	%s", "COLOR", &EQUAL,
			pSaveParam->m_col.r, pSaveParam->m_col.g, pSaveParam->m_col.b, pSaveParam->m_col.a, "//色");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		//回転量
		sprintf(cWriteText, "		%s %s %.2f %.2f %.2f 	%s", "ROT", &EQUAL,
				pSaveParam->m_rot.x, pSaveParam->m_rot.y, pSaveParam->m_rot.z, "//回転量");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);


		//改行
		fputs(NEWLINE, pFile);

		//パラメータセット
		fputs("	END_PARAMSET", pFile);
		fputs(NEWLINE, pFile);

		//キーセット終了
		fputs("END_SCRIPT", pFile);
		fputs(NEWLINE, pFile);

		//保存成功
		std::cout << "ParticleParam Save Succsess!! >>" << PARAMATER_SAVE_FILENAME << NEWLINE;

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		//ファイルが開けませんでした
		std::cout << "ParticleParam Save FAILED!!  Can't Open File. SaveParticleDefaultParam()" << NEWLINE;
		return E_FAIL;
	}
	return S_OK;
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
void CParticle::SetParticle(D3DXVECTOR3 &pos, CParticleParam *pParam)
{
	//変数宣言
	float fAngleX, fAngleY;
	D3DXVECTOR3 move;
	float fSpeed;

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
				move = D3DXVECTOR3(-sinf(fAngleY) * cosf(fAngleX) * fSpeed,
									sinf(fAngleX) * fSpeed,
									-cosf(fAngleY) * cosf(fAngleX) * fSpeed);

				break;
			default:
				break;
			}
		}


		//パーティクル生成
		std::unique_ptr<COneParticle>pOneParticle = COneParticle::Create(pos, move, ZeroVector3);

		//配列に追加
		m_pParticleList.emplace_back(std::move(pOneParticle));

	}
	//頂点の更新
	UpdateVertex();
}


//------------------------------------------------------------------------------
//コンボボックス
//------------------------------------------------------------------------------
bool CParticleParam::ShowParamConboBox(CParticleParam::PARTICLE_TEXT &rType)
{
	bool bChange = false;

#ifdef _DEBUG
	//combo開始
	if (ImGui::BeginCombo("ParamFileName", m_aFileNameList[rType].data()))
	{
		//要素分繰り返す
		for (size_t nCnt = 0; nCnt < m_aFileNameList.size(); nCnt++)
		{

			//選択番号があってるかどうか
			bool is_selected = (m_aFileNameList[rType] == m_aFileNameList[nCnt]);

			//選択された時の処理
			if (ImGui::Selectable(m_aFileNameList[nCnt].data(), is_selected))
			{
				//現在の選択項目設定
				rType = (CParticleParam::PARTICLE_TEXT)nCnt;
				bChange = true;
			}
		}
		//combo終了
		ImGui::EndCombo();

	}
#endif //DEBUG
	return bChange;
}
//------------------------------------------------------------------------------
//パラメータ設定
//------------------------------------------------------------------------------
void CParticleParam::SetParamater(int nLife, float fRadius, D3DXCOLOR col, int nNumber, float fSpeed)
{
	m_nLife = nLife;
	m_fRadius = fRadius;
	m_col = col;

	m_nNumber = nNumber;
	m_fSpeed = fSpeed;
}


//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CParticleParam::UpdateParam()
{
	m_nLife--;
	m_fRadius *= m_fRadiusDamping;
	m_col.a *= m_fAlphaDamping;
}


//------------------------------------------------------------------------------
//オペレータ
//クラスのパラメータを丸ごと代入できるように
//ポインタ同士
//------------------------------------------------------------------------------
void * CParticleParam::operator=(const CParticleParam * pParam)
{
	m_nLife					= pParam->m_nLife;
	m_fRadius				= pParam->m_fRadius;
	m_col					= pParam->m_col;
	m_nNumber				= pParam->m_nNumber;
	m_fSpeed				= pParam->m_fSpeed;
	m_fRadiusDamping		= pParam->m_fRadiusDamping;
	m_fAlphaDamping			= pParam->m_fAlphaDamping;
	m_Textype				= pParam->m_Textype;
	m_ParticleType			= pParam->m_ParticleType;
	m_shape					= pParam->m_shape;
	m_bGravity				= pParam->m_bGravity;
	m_fGravityPower			= pParam->m_fGravityPower;
	m_bSpeedRandom			= pParam->m_bSpeedRandom;
	m_rot					= pParam->m_rot;
	m_fRange				= pParam->m_fRange;
	return this;
}
