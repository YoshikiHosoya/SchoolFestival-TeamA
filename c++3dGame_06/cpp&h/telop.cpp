// ----------------------------------------
//
// テロップ処理の説明[telop.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
#include "telop.h"
#include "title.h"
#include "TelopComment.h"
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
LPDIRECT3DTEXTURE9 CTelop::m_pTexture = NULL;
D3DXVECTOR3 CTelop::m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR2 CTelop::m_size = D3DXVECTOR2(0.0f, 0.0f);
D3DXCOLOR CTelop::m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
// ----------------------------------------
// コンストラクタ処理
// ----------------------------------------
CTelop::CTelop() : CScene_TWO::CScene_TWO(ACTOR_TELOP, LAYER_UI)
{
	m_nCntCol = 0;
	m_nCommentCount = 0;
	m_bTelopFlag = false;
	m_bCommentFlag = false;
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CTelop::~CTelop()
{
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void CTelop::Init(void)
{
	CScene_TWO::Init();
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void CTelop::Uninit(void)
{
	CScene_TWO::Uninit();
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void CTelop::Update(void)
{
	// テロップが存在してENTERを押したとき
	if (CManager::GetTitle()->GetEnterflag() == true && GetTelopFlag() == true)
	{
		// 前のコメントが生成されてから1秒たったら
		if (m_bCommentFlag == false)
		{
			// 次のフェーズへ移行
			CTelopComment::SetPhase();
			// クールタイムを初期化
			m_nCommentCount = 0;
			// フラグをtrueにする
			m_bCommentFlag = true;
		}

		// 前のコメントが生成されてから1秒たったら
		else if (m_nCommentCount >= ONEMIN)
		{
			m_bCommentFlag = false;
			m_nCommentCount = 0;
		}
	}

	// コメントが生成されたら
	if (m_bCommentFlag == true)
	{
		// 次のコメントを生成できるまでのクールタイムをカウント
		m_nCommentCount++;
	}

	CScene_TWO::Update();
}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void CTelop::Draw(void)
{
	CScene_TWO::Draw();
}

// ----------------------------------------
// 読み込み処理
// ----------------------------------------
HRESULT CTelop::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice =		// デバイスの取得
		CManager::GetRenderer()->GetDevice();

	// テクスチャー情報代入
	char TexData[72] =
	{
		"data/TEXTURE/UI/Telop.png"
	};
	// 位置情報代入
	D3DXVECTOR3 pos =
	{
		D3DXVECTOR3(640.0f,600,0.0f)
	};
	// サイズ情報代入
	D3DXVECTOR2 size =
	{
		D3DXVECTOR2(600.0f,100.0f)
	};
	// 色情報代入
	D3DXCOLOR col =
	{
		D3DXCOLOR(1.0f,1.0f,1.0f,0.0f)
	};

	// テクスチャーがあったら
	if (strcmp(TexData, "") != 0)
	{
		D3DXCreateTextureFromFile(pDevice, TexData, &m_pTexture);
		m_pos = pos;
		m_size = size;
		m_Col = col;
	}

	return S_OK;
}

// ----------------------------------------
// 読み込んだ情報を破棄
// ----------------------------------------
void CTelop::UnLoad(void)
{
	// テクスチャの開放
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

// ----------------------------------------
// 作成処理
// ----------------------------------------
CTelop * CTelop::Create(void)
{
	// 変数宣言
	CTelop * pTelop;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pTelop = new CTelop();
	// テクスチャの設定
	pTelop->BindTexture(m_pTexture);
	// 初期化処理
	pTelop->Init();
	// 座標の設定
	pTelop->SetPosition(m_pos);
	// 大きさの反映
	pTelop->SetSize(m_size);
	// 色の設定
	pTelop->SetCol(m_Col);
	// 生成したオブジェクトを返す
	return pTelop;
}

// ----------------------------------------
// 透明化処理
// ----------------------------------------
void CTelop::Transparency(STATE state)
{
	switch (state)
	{
		// 出現
	case STATE_EMERGENCE:
		// 徐々にα値を加算
		if (m_Col.a <= 1.0f)
		{
			//徐々に透明にする
			m_Col.a += 0.01f;
			//色の更新
			SetCol(m_Col);
		}

		// 完全に不透明になったら
		if (m_Col.a >= 1.0f)
		{
			// 不透明フラグをtrueにする
			m_bTelopFlag = true;
		}
		break;

		// 消失
	case STATE_DISAPPEARANCE:
		// 徐々に透明化させる
		if (m_Col.a >= 0.0f)
		{
			//徐々に透明にする
			m_Col.a -= 0.01f;
			//色の更新
			SetCol(m_Col);
		}

		// 完全に透明になったら
		if (m_Col.a <= 0.0f)
		{
			// 消滅させる
			Release();
		}

		break;

	default:
		break;
	}
}

// ----------------------------------------
// フラグの取得
// ----------------------------------------
bool CTelop::GetTelopFlag(void)
{
	return m_bTelopFlag;
}
