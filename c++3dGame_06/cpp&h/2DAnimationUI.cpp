// ----------------------------------------
//
// 2Dアニメーション処理の説明[2DAnimationUI.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
#include "2DAnimationUI.h"

// ----------------------------------------
//
// マクロ定義
//
// ----------------------------------------

// ----------------------------------------
//
// 静的変数宣言
//
// ----------------------------------------
LPDIRECT3DTEXTURE9 C2DAnimation::m_pTexture[TYPE_MAX] = {};		// テクスチャへのポインタ

// ----------------------------------------
// コンストラクタ処理
// ----------------------------------------
C2DAnimation::C2DAnimation() : CScene_TWO::CScene_TWO(ACTOR_ANIMATION, LAYER_UI)
{
	// 変数の初期化
	m_Type = TYPE_KEY;
	m_nCntAnim = 0;
	m_nPatternAnim = 0;
	m_TexFirst = D3DXVECTOR2(0.0f, 0.0f);
	m_TexLast = D3DXVECTOR2(0.2f, 1.0f);
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
C2DAnimation::~C2DAnimation()
{
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void C2DAnimation::Init(void)
{
	CScene_TWO::Init();
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void C2DAnimation::Uninit(void)
{
	CScene_TWO::Uninit();
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void C2DAnimation::Update(void)
{
	// アニメーションの更新
	SetAnim();
	// 回転の反映
	//CScene_TWO::SetRot(CScene_TWO::GetLengh() + 0.1f);
	CScene_TWO::Update();
}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void C2DAnimation::Draw(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice =					// デバイスの取得
		CManager::GetRenderer()->GetDevice();
	// アルファテストの設定に変更
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// アルファテスト有効
	pDevice->SetRenderState(D3DRS_ALPHAREF, 200);				// アルファ値の基準設定(基準より大きいと描画する)
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// 状況に応じてアルファテストを実行する(新ピクセル > 現在のピクセル)
	pDevice->SetRenderState(D3DRS_LIGHTING, false);				// ライティングoff
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// 描画
	CScene_TWO::Draw();

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	// アルファテストの設定を戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		// アルファテスト無効
	pDevice->SetRenderState(D3DRS_LIGHTING, true);				// ライティングon
}

// ----------------------------------------
// テクスチャー設定処理
// ----------------------------------------
void C2DAnimation::SetTexture(TYPE type)
{
	// テクスチャー設定
	CScene_TWO::BindTexture(m_pTexture[type]);
}

// ----------------------------------------
// 作成処理
// ----------------------------------------
C2DAnimation * C2DAnimation::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXVECTOR2 texf, D3DXVECTOR2 texr, TYPE type)
{
	// 変数宣言
	C2DAnimation * p2DAnimation;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	p2DAnimation = new C2DAnimation();
	// 種類の設定
	p2DAnimation->m_Type = type;
	// 初期化処理
	p2DAnimation->Init();
	// 座標の設定
	p2DAnimation->SetPos(pos);
	// 大きさの設定
	p2DAnimation->SetSize(size);
	// 左上の頂点座標
	p2DAnimation->m_TexFirst = texf;
	// 右下の頂点座標
	p2DAnimation->m_TexLast = texr;
	// テクスチャ座標の設定
	p2DAnimation->SetTex(texf, texr);
	// テクスチャの設定
	p2DAnimation->SetTexture(type);
	// 生成したオブジェクトを返す
	return p2DAnimation;
}

// ----------------------------------------
// 読み込み処理
// ----------------------------------------
HRESULT C2DAnimation::Load(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice =					// デバイスの取得
		CManager::GetRenderer()->GetDevice();

	// テクスチャ情報の読み込み
	char cTex[TYPE_MAX][128] =					// テクスチャー名
	{
		"data/TEXTURE/UI/Animation00.png",
		"data/TEXTURE/UI/Animation01.png",
		"data/TEXTURE/UI/Animation02.png"
	};

	// テクスチャー設定
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, cTex[nCnt], &m_pTexture[nCnt]);
	}

	return S_OK;
}

// ----------------------------------------
// unload処理
// ----------------------------------------
void C2DAnimation::UnLoad(void)
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
}

// ----------------------------------------
// 位置の設定処理
// ----------------------------------------
void C2DAnimation::SetPos(D3DXVECTOR3 pos)
{
	CScene_TWO::SetPosition(pos);
}

// ----------------------------------------
// サイズ設定処理
// ----------------------------------------
void C2DAnimation::SetSize(D3DXVECTOR2 size)
{
	CScene_TWO::SetSize(size);
}

// ----------------------------------------
// 回転の設定処理
// ----------------------------------------
void C2DAnimation::SetRot(float rot)
{
	CScene_TWO::SetRot(rot);
}
// ----------------------------------------
// 色の設定処理
// ----------------------------------------
void C2DAnimation::SetCol(D3DXCOLOR col)
{
	CScene_TWO::SetCol(col);
}

// ----------------------------------------
// 表示テクスチャー設定処理
// ----------------------------------------
void C2DAnimation::SetTex(D3DXVECTOR2 first, D3DXVECTOR2 last)
{
	CScene_TWO::SetTex(first, last);
}

// ----------------------------------------
// アニメーションの設定
// ----------------------------------------
void C2DAnimation::SetAnim(void)
{
	switch (m_Type)
	{
	case TYPE_KEY:

		m_nCntAnim++;//カウンター加算

		// 1フレームごとに更新
		if (m_nCntAnim % (ONEFRAME) == 0)
		{
			// 常にXはアニメーション
			m_TexFirst.x += 0.2f;
			m_TexLast.x += 0.2f;

			// xが右端まで行ってyが最下段じゃなかった時
			if (m_TexFirst.x >= 0.8f && m_TexLast.x >= 1.0f && m_TexFirst.y < 0.75f && m_TexLast.y <= 1.0f)
			{
				m_TexFirst.y += 0.25f;
				m_TexLast.y += 0.25f;
			}

			// xが右端まで行ってyが最下段だった時
			else if (m_TexFirst.x >= 0.8f && m_TexLast.x >= 1.0f && m_TexFirst.y >= 0.75f && m_TexLast.y >= 1.0f)
			{
				m_TexFirst.y = 0.0f;
				m_TexLast.y = 0.25f;
			}

			// テクスチャ座標の更新
			SetTex(D3DXVECTOR2(m_TexFirst.x, m_TexFirst.y), D3DXVECTOR2(m_TexLast.x, m_TexLast.y));

			break;
		}
	default:
		break;
	}
}

// ----------------------------------------
// サイズの取得処理
// ----------------------------------------
D3DXVECTOR2 C2DAnimation::GetSize(void)
{
	return CScene_TWO::GetSize();
}

// ----------------------------------------
// 位置の取得処理
// ----------------------------------------
D3DXVECTOR3 C2DAnimation::GetPos(void)
{
	return CScene_TWO::GetPosition();
}

// ----------------------------------------
// 回転の取得処理
// ----------------------------------------
float C2DAnimation::GetRot(void)
{
	return CScene_TWO::GetLengh();
}