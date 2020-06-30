//------------------------------------------------------------------------------
//
//後ろの雷処理  [backthunder.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "backthunder.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "effectanimation2D.h"
#include "effectanimation3D.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define RANDOM_INTERVAL (rand() % 300 + 50)		//雷の振ってくるインターバル
//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CBackThunder::CBackThunder()
{
	//初期化
	m_nCnt = 0;
	m_nNextThunder = RANDOM_INTERVAL;
}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CBackThunder::~CBackThunder()
{
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CBackThunder::Init()
{
	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CBackThunder::Uninit()
{
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CBackThunder::Update()
{
	//カウンタ++
	m_nCnt++;

	//適当なタイミングで
	if (m_nCnt % m_nNextThunder == 0)
	{
		//初期化
		D3DXVECTOR3 ThunderPos = ZeroVector3;

		//モードに応じて雷の発生場所設定
		switch (CManager::GetMode())
		{
			//ゲームかリザルト中
		case CManager::MODE_GAME:
		case CManager::MODE_RESULT:
			ThunderPos = D3DXVECTOR3((float)(rand() % 1280), 300.0f, 0.0f);
			break;

			//タイトル中
		case CManager::MODE_TITLE:
			ThunderPos = D3DXVECTOR3(500.0f + (float)(rand() % 200), 700.0f, 0.0f);
			break;
		default:
			break;
		}

		//フラッシュと雷生成
		CEffectAnimation2D::Create(ThunderPos - D3DXVECTOR3(0.0f, 300.0f, 0.0f), D3DXVECTOR3(1000.0f, 1000.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_FLASH, 0.0f, 3, CScene::OBJTYPE_BACK);
		CEffectAnimation2D::Create(ThunderPos, D3DXVECTOR3(400.0f, 600.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_BACKTHUNDER, 0.0f, 3, CScene::OBJTYPE_BACK);

		//次の落雷タイミング設定 ランダム
		m_nNextThunder = RANDOM_INTERVAL;
		m_nCnt = 0;

		//音再生
		CManager::GetSound()->Play(CSound::LABEL_SE_THUNDER);
	}

}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CBackThunder::Draw()
{
}
//------------------------------------------------------------------------------
//デバッグ情報表示
//------------------------------------------------------------------------------
void CBackThunder::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //_DEBUG
}
//------------------------------------------------------------------------------
//生成処理
//------------------------------------------------------------------------------
void CBackThunder::Create()
{
	//メモリ確保
	std::unique_ptr<CBackThunder> pBackThunder(new CBackThunder);

	//nullcheck
	if (pBackThunder)
	{
		//初期化
		pBackThunder->Init();

		//Sceneの配列に追加
		pBackThunder->SetObjType(CScene::OBJTYPE_BACK);
		pBackThunder->AddUniqueList(std::move(pBackThunder));
	}
}
