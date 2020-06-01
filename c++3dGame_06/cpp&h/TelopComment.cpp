// ----------------------------------------
//
// テロップコメント処理の説明[telopcomment.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
#include "telopcomment.h"
#include "title.h"
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
LPDIRECT3DTEXTURE9 CTelopComment::m_pTexture[TYPE_MAX] = {};
bool CTelopComment::bEndPhase = false;
CTelopComment::PHASE CTelopComment::m_phase = PHASE_NONE;
int CTelopComment::m_nCreateCount = 0;
// ----------------------------------------
// コンストラクタ処理
// ----------------------------------------
CTelopComment::CTelopComment() : CScene_TWO::CScene_TWO(ACTOR_TELOPCOMMENT, LAYER_UI)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	m_nCreateCount = 0;
	bDisFlag = false;
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CTelopComment::~CTelopComment()
{
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void CTelopComment::Init(void)
{
	CScene_TWO::Init();
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void CTelopComment::Uninit(void)
{
	CScene_TWO::Uninit();
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void CTelopComment::Update(void)
{
	//消滅フラグが立っていなかったら
	if (bDisFlag == false)
	{
		// 不透明度を加算
		Transparency(STATE_EMERGENCE);
	}
	CScene_TWO::Update();
}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void CTelopComment::Draw(void)
{
	CScene_TWO::Draw();
}

// ----------------------------------------
// 読み込み処理
// ----------------------------------------
HRESULT CTelopComment::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice =		// デバイスの取得
		CManager::GetRenderer()->GetDevice();

	// テクスチャー情報代入
	char TexData[TYPE_MAX][72] =
	{
		"data/TEXTURE/TUTORIAL/Comment000.png",
		"data/TEXTURE/TUTORIAL/Comment001.png",
		"data/TEXTURE/TUTORIAL/Comment002.png",
		"data/TEXTURE/TUTORIAL/Comment003.png",
		"data/TEXTURE/TUTORIAL/Comment004.png",
		/*"data/TEXTURE/UI/Comment003.png",
		"data/TEXTURE/UI/Comment004.png",*/
	};

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		// テクスチャーがあったら
		if (strcmp(TexData[nCnt], "") != 0)
		{
			D3DXCreateTextureFromFile(pDevice, TexData[nCnt], &m_pTexture[nCnt]);
		}
	}

	return S_OK;
}

// ----------------------------------------
// 読み込んだ情報を破棄
// ----------------------------------------
void CTelopComment::UnLoad(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		// テクスチャの開放
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

// ----------------------------------------
// 作成処理
// ----------------------------------------
CTelopComment * CTelopComment::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,TYPE type)
{
	// 変数宣言
	CTelopComment * pTelopComment;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pTelopComment = new CTelopComment();
	// テクスチャの設定
	pTelopComment->BindTexture(m_pTexture[type]);
	// 初期化処理
	pTelopComment->Init();
	// 座標の設定
	pTelopComment->SetPosition(pos);
	// 大きさの反映
	pTelopComment->SetSize(size);
	// 生成までの時間をリセットする
	m_nCreateCount = 0;
	// 生成したオブジェクトを返す
	return pTelopComment;
}

// ----------------------------------------
// 作成処理
// ----------------------------------------
void CTelopComment::CreateTelopCommnet(PHASE phase)
{
	switch (phase)
	{
	case PHASE_NONE:
		break;

	case PHASE_ONE:
		CTelopComment::Create(TELOP_POS, TELOP_SIZE, CTelopComment::TYPE_0);
		break;

	case PHASE_TWO:
		CTelopComment::Create(TELOP_POS, TELOP_SIZE, CTelopComment::TYPE_1);
		break;

	case PHASE_THREE:
		CTelopComment::Create(TELOP_POS, TELOP_SIZE, CTelopComment::TYPE_2);
		break;

	case PHASE_FOUR:
		CTelopComment::Create(TELOP_POS, TELOP_SIZE, CTelopComment::TYPE_3);
		break;

	case PHASE_FIVE:
		CTelopComment::Create(TELOP_POS, TELOP_SIZE, CTelopComment::TYPE_4);
		bEndPhase = true;
		break;

	case PHASE_END:
		bEndPhase = true;
		break;

	default:
		break;
	}
}

// ----------------------------------------
// 透明化処理
// ----------------------------------------
void CTelopComment::Transparency(STATE state)
{
	switch (state)
	{
		// 出現
	case STATE_EMERGENCE:
		// 徐々にα値を加算
		if (m_col.a <= 1.0f)
		{
			//徐々に不透明にする
			m_col.a += 0.03f;
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
			m_col.a -= 0.5f;
			//色の更新
			SetCol(m_col);
		}
		// 透明になったら削除
		if (m_col.a <= 0.0f)
		{
		}
		// 削除
		Release();
		break;

	default:
		break;
	}
}

// ----------------------------------------
// 次のフェイズへ
// ----------------------------------------
void CTelopComment::SetPhase(void)
{
	// 変数の初期化
	CTelopComment *pTelopComment = NULL;

	// コメントのポインタを検索
	for (int nCntlayer = 0; nCntlayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntlayer++)
	{
		if (pTelopComment = (CTelopComment *)CScene::GetActor(CScene::ACTOR_TELOPCOMMENT, CScene::LAYER_UI, nCntlayer)) break;
	}

	// 次のフェイズに移行
	switch (m_phase)
	{
	case PHASE_NONE:
		m_phase = PHASE_ONE;
		break;

	case PHASE_ONE:
		m_phase = PHASE_TWO;
		break;

	case PHASE_TWO:
		m_phase = PHASE_THREE;
		break;

	case PHASE_THREE:
		m_phase = PHASE_FOUR;
		break;

	case PHASE_FOUR:
		m_phase = PHASE_FIVE;
		break;

	case PHASE_FIVE:
		m_phase = PHASE_END;
		break;

	case PHASE_END:
		bEndPhase = true;
		break;

	default:
		break;
	}

	// コメントが存在していたら
	if (pTelopComment != NULL)
	{
		// 消滅フラグをtrueにする
		pTelopComment->bDisFlag = true;
		// 現在のコメントを削除
		pTelopComment->Release();
	}

	if (m_phase != PHASE_NONE)
	{
		// コメントの生成
		CreateTelopCommnet(m_phase);
	}

	// 新しいフェイズの処理
	Phase();
}

// ----------------------------------------
// フェイズごとに行う処理
// ----------------------------------------
void CTelopComment::Phase(void)
{
	switch (m_phase)
	{
	case PHASE_ONE:
		break;

	case PHASE_TWO:
		break;

	case PHASE_THREE:
		break;

	case PHASE_FOUR:
		break;

	case PHASE_FIVE:
		break;

	case PHASE_END:
		// 終了フラグをtrueにする
		bEndPhase = true;
		break;

	default:
		break;
	}

	// タイトルフラグをfalseにする
	CManager::GetTitle()->SetEnterflag();
}

// ----------------------------------------
// フェイズが終了したかの判定を取得
// ----------------------------------------
bool CTelopComment::GetEndPhaseFlag(void)
{
	return bEndPhase;
}

// ----------------------------------------
// 現在のフェイズの取得
// ----------------------------------------
CTelopComment::PHASE CTelopComment::GetPhase(void)
{
	return m_phase;
}
