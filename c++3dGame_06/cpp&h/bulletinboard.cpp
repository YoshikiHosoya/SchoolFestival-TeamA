// ----------------------------------------
//
// 掲示板処理の説明[bulletinboard.h]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
#include "bulletinboard.h"
#include "debugproc.h"
// ----------------------------------------
//
// マクロ定義
//
// ----------------------------------------
#define BULLETINBOARD_COLLISION_SIZE (30.0f)

// ----------------------------------------
//
// 静的変数宣言
//
// ----------------------------------------
LPDIRECT3DTEXTURE9 CBulletinBoard::m_pTexture[TYPE_MAX] = {};		// テクスチャへのポインタ
CLoad	*CBulletinBoard::m_pload = NULL;								// ロード
int		CBulletinBoard::m_nAll = 0;									// 番号

// ----------------------------------------
// コンストラクタ処理
// ----------------------------------------
CBulletinBoard::CBulletinBoard()
{
	// 変数の初期化
	m_Type = TYPE_A;
	m_fLengh = 0;
	m_fAngle = 0;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	m_nCntAnim = 0;
	m_TexFirst = D3DXVECTOR2(0.0f, 0.0f);
	m_TexLast = D3DXVECTOR2(0.2f, 1.0f);
	m_TexFirstSign = m_TexFirst;
	m_TexLastSign = m_TexLast;
}

// ----------------------------------------
// イニシャライザコンストラクタ
// ----------------------------------------
CBulletinBoard::CBulletinBoard(ACTOR actor, LAYER layer) : CScene_THREE::CScene_THREE(actor, layer)
{
	// 変数の初期化
	m_fLengh = 0;
	m_fAngle = 0;
	m_Type = TYPE_A;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	m_nCntAnim = 0;
	m_TexFirst = D3DXVECTOR2(0.0f, 0.0f);
	m_TexLast = D3DXVECTOR2(0.2f, 1.0f);
	m_TexFirstSign = m_TexFirst;
	m_TexLastSign = m_TexLast;
}


// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CBulletinBoard::~CBulletinBoard()
{
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void CBulletinBoard::Init(void)
{
	// シーン3Dの初期化
	CScene_THREE::Init();
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void CBulletinBoard::Uninit(void)
{
	CScene_THREE::Uninit();
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void CBulletinBoard::Update(void)
{
	// 透明から不透明にする
	Transparency(STATE_EMERGENCE);

	// アニメーションの更新
	SetAnim();

	CScene_THREE::Update();

	// テクスチャ座標の確認
	CDebugproc::Print("テクスチャ座標 : %.2f,%.2f \n", m_TexFirst.x, m_TexLast.x);
	CDebugproc::Print("テクスチャ座標 : %.2f,%.2f \n", m_TexFirstSign.x, m_TexLastSign.x);
}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void CBulletinBoard::Draw(void)
{
	// 描画方法の変更
	//if (m_col.a <= 1.0f)
	//{
		// 変数宣言
		LPDIRECT3DDEVICE9	pDevice;					// デバイスのポインタ
		pDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得

														// ライティングモード無効
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		//Zバッファ　有効　無効
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_FALSE);

		// レンダーステート(加算合成処理)
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		// 描画
		CScene_THREE::Draw();

		//アルファテスト戻す
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		//Zバッファ　有効　無効
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE);
		// ライティングモード有効
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

		// レンダーステート(通常ブレンド処理)
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//}

	//else
	//{
	//	// 変数宣言
	//	LPDIRECT3DDEVICE9 pDevice =					// デバイスの取得
	//		CManager::GetRenderer()->GetDevice();
	//	// アルファテストの設定に変更
	//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// アルファテスト有効
	//	pDevice->SetRenderState(D3DRS_ALPHAREF, 200);				// アルファ値の基準設定(基準より大きいと描画する)
	//	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// 状況に応じてアルファテストを実行する(新ピクセル > 現在のピクセル)
	//	pDevice->SetRenderState(D3DRS_LIGHTING, false);				// ライティングoff

	//	// 描画
	//	CScene_THREE::Draw();
	//	// アルファテストの設定を戻す
	//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		// アルファテスト無効
	//	pDevice->SetRenderState(D3DRS_LIGHTING, true);				// ライティングon
	//}
}

// ----------------------------------------
// テクスチャー設定処理
// ----------------------------------------
void CBulletinBoard::SetTexture(TYPE type)
{
	// 設定
	CScene_THREE::BindTexture(m_pTexture[type]);	// テクスチャー
}

// ----------------------------------------
// 作成処理
// ----------------------------------------
CBulletinBoard * CBulletinBoard::Create(void)
{
	// 変数宣言
	CBulletinBoard * pBulletinBoard;		// シーン3Dクラス
						// メモリの生成(初め->基本クラス,後->派生クラス)
	pBulletinBoard = new CBulletinBoard(ACTOR_BULLETINBOARD, LAYER_3DOBJECT);
	// 初期化処理
	pBulletinBoard->Init();
	// 生成したオブジェクトを返す
	return pBulletinBoard;
}

// ----------------------------------------
// 読み込み作成処理
// ----------------------------------------
void CBulletinBoard::LoadCreate(void)
{
	// 変数宣言
	CBulletinBoard * pBulletinBoard;
	// 読み込んだ数だけ
	for (int nCntItem = 0; nCntItem < m_nAll; nCntItem++)
	{
		// 生成
		pBulletinBoard = CBulletinBoard::Create();
		// テクスチャーを設定
		pBulletinBoard->SetTexture((TYPE)m_pload->GetInfo(nCntItem).nType);
		// タイプを設定
		pBulletinBoard->m_Type = (TYPE)m_pload->GetInfo(nCntItem).nType;
		// 座標を設定
		pBulletinBoard->SetPos(m_pload->GetInfo(nCntItem).pos);
		// 回転を設定
		pBulletinBoard->SetRot(m_pload->GetInfo(nCntItem).rot);
		// 大きさを設定
		pBulletinBoard->SetSize(m_pload->GetInfo(nCntItem).size);
		// 色情報を設定
		pBulletinBoard->m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		// 色を設定
		pBulletinBoard->SetCol(pBulletinBoard->m_col);
		// テクスチャ座標を設定
		pBulletinBoard->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.2f, 1.0f));
	}
}

// ----------------------------------------
// 読み込み処理
// ----------------------------------------
HRESULT CBulletinBoard::Load(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice =					// デバイスの取得
		CManager::GetRenderer()->GetDevice();
	char cTex[TYPE_MAX][128] =					// テクスチャー名
	{
		"data/TEXTURE/TUTORIAL/Board000.png",
		"data/TEXTURE/obj_tex/Board01.png",
		"data/TEXTURE/obj_tex/Board02.png"
	};

	// テクスチャー設定
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, cTex[nCnt], &m_pTexture[nCnt]);
	}
	// ロード生成
	m_pload = new CLoad;
	// ロード読み込み
	m_nAll = m_pload->Load("data/LOAD/OBJECT/Board_Location.txt");

	return S_OK;
}

// ----------------------------------------
// unload処理
// ----------------------------------------
void CBulletinBoard::UnLoad(void)
{
	// テクスチャー設定
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
	// ロードの破棄
	delete m_pload;
	m_pload = NULL;
}

// ----------------------------------------
// アニメーションの設定
// ----------------------------------------
void CBulletinBoard::SetAnim(void)
{
	//カウンター加算
	m_nCntAnim++;

	// フレームごとに更新
	if (m_nCntAnim % (ONEMIN * 2) == 0)
	{
		// 常にXはアニメーション
		m_TexFirst.x += 0.2f;
		m_TexLast.x += 0.2f;
	}

	// 目標のテクスチャ座標になるまで加算
	else if (m_TexFirstSign.x < m_TexFirst.x && m_TexLastSign.x < m_TexLast.x)
	{
		// テクスチャ座標加算
		m_TexFirstSign.x += 0.005f;
		m_TexLastSign.x += 0.005f;

		// 目標を超えたら目標の座標を代入し超えないようにする
		if (m_TexFirst.x <= m_TexFirstSign.x)
		{
			m_TexFirstSign.x = m_TexFirst.x;
		}
		// 目標を超えたら目標の座標を代入し超えないようにする
		if (m_TexLast.x <= m_TexLastSign.x)
		{
			m_TexLastSign.x = m_TexLast.x;
		}
	}

	// テクスチャ座標の更新
	SetTex(D3DXVECTOR2(m_TexFirstSign.x, m_TexFirstSign.y), D3DXVECTOR2(m_TexLastSign.x, m_TexLastSign.y));
}


// ----------------------------------------
// ロード取得
// ----------------------------------------
CLoad * CBulletinBoard::GetLoad(void)
{
	return m_pload;
}

// ----------------------------------------
// 位置の設定処理
// ----------------------------------------
void CBulletinBoard::SetPos(D3DXVECTOR3 pos)
{
	CScene_THREE::SetPos(pos);
}

// ----------------------------------------
// サイズ設定処理
// ----------------------------------------
void CBulletinBoard::SetSize(D3DXVECTOR3 size)
{
	CScene_THREE::SetSize(size);
}

// ----------------------------------------
// 回転の設定処理
// ----------------------------------------
void CBulletinBoard::SetRot(D3DXVECTOR3 rot)
{
	CScene_THREE::SetRot(rot);
}
// ----------------------------------------
// 色の設定処理
// ----------------------------------------
void CBulletinBoard::SetCol(D3DXCOLOR col)
{
	CScene_THREE::SetCol(col);
}

// ----------------------------------------
// 表示テクスチャー設定処理
// ----------------------------------------
void CBulletinBoard::SetTex(D3DXVECTOR2 first, D3DXVECTOR2 last)
{
	CScene_THREE::SetTex(first, last);
}

// ----------------------------------------
// 透明化処理
// ----------------------------------------
void CBulletinBoard::Transparency(STATE state)
{
	switch (state)
	{
		// 出現
	case STATE_EMERGENCE:
		// 徐々にα値を加算
		if (m_col.a <= 1.0f)
		{
			//徐々に透明にする
			m_col.a += 0.01f;
			//色の更新
			SetCol(m_col);
		}
		break;

		// 消失
	case STATE_DISAPPEARANCE:
		// 徐々に透明化させる
		if (m_col.a >= 0.0f)
		{
			//徐々に透明にする
			m_col.a -= 0.01f;
			//色の更新
			SetCol(m_col);
		}
		if (m_col.a <= 0.0f)
		{
			Release();
		}
		break;

	default:
		break;
	}
}


// ----------------------------------------
// サイズの取得処理
// ----------------------------------------
D3DXVECTOR3 CBulletinBoard::GetSize(void)
{
	return CScene_THREE::GetSize();
}

// ----------------------------------------
// 回転の取得処理
// ----------------------------------------
D3DXVECTOR3 CBulletinBoard::GetRot(void)
{
	return CScene_THREE::GetRot();
}

// ----------------------------------------
// 位置の取得処理
// ----------------------------------------
D3DXVECTOR3 CBulletinBoard::GetPos(void)
{
	return CScene_THREE::GetPos();
}
