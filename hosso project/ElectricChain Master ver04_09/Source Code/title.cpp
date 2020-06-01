//------------------------------------------------------------------------------
//
//タイトル処理  [title.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "scene.h"
#include "fade.h"
#include "title.h"
#include "Map.h"
#include "UI.h"
#include "effectanimation2D.h"
#include "sound.h"
#include "backthunder.h"
#include "keyboard.h"
//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define DEMOPLAY_FADE_COUNT		(1000)		//デモプレイに行くまでのカウンタ
#define TITLEUI_APPEAR_COUNT	(120)		//タイトルのUIが表示されるまでのカウンタ
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CTitle::CTitle()
{
	m_pBlack.reset();
	m_nCntState = DEMOPLAY_FADE_COUNT;
	m_titlestate = STATE_START;

}

//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CTitle::~CTitle()
{
	m_pBlack.reset();
}

//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CTitle::Init(HWND hWnd)
{
	//カメラ座標設定
	CManager::GetRenderer()->GetCamera()->SetCameraPos(ZeroVector3, D3DXVECTOR3(0.0f, 200.0f, -600.0f));
	CManager::GetRenderer()->GetCamera()->SetState(CCamera::CAMERA_TITLE);

	//ブラックアウト
	m_pBlack = CScene2D::Create_Shared(SCREEN_CENTER_POS, SCREEN_SIZE, CScene::OBJTYPE_2DUI);
	m_pBlack->SetVtxCol(BlackColor);

	//最初の電撃
	CEffectAnimation2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, 1000.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_TITLESPARK, 0.0f, 2,CScene::OBJTYPE_2DEFFECT);

	return S_OK;
}

//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CTitle::Uninit()
{
	//終了処理
	CScene::ReleaseAll();
}

//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CTitle::Update()
{
	//カウントダウン
	m_nCntState--;

	//タイトルの開始の時（最初のビリビリの間）
	if (m_titlestate == STATE_START)
	{
		//何かボタン
		if (CHossoLibrary::CheckAnyButton())
		{
			//UIでるとこまでスキップ
			m_nCntState = DEMOPLAY_FADE_COUNT - TITLEUI_APPEAR_COUNT;

		}

		//一定間隔
		if (m_nCntState % 15 == 0)
		{
			//電撃
			CManager::GetSound()->Play(CSound::LABEL_SE_TITLE_SPARKING);

			//電撃なエフェクト
			CEffectAnimation2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, 1000.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_TITLESPARK, 0.0f, 2, CScene::CScene::OBJTYPE_2DEFFECT);
		}
		if (m_nCntState == DEMOPLAY_FADE_COUNT - TITLEUI_APPEAR_COUNT)
		{
			//音停止
			CManager::GetSound()->Stop(CSound::LABEL_SE_TITLE_SPARKING);

			//音再生
			CManager::GetSound()->Play(CSound::LABEL_SE_TITLE_EXPLOSION);

			//黒背景消去
			m_pBlack->Release();

			//今まで出してたエフェクト前景
			CScene::ReleaseSpecificObject(CScene::OBJTYPE_2DEFFECT);

			//後ろで雷落とす
			CBackThunder::Create();

			//UI配置
			CUI::LoadPlace(CUI::SCENE_TITLE);

			//爆発の電撃
			CEffectAnimation2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(1500.0f, 1000.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_SPARKEXPLOSION, 0.0f, 2,CScene::CScene::OBJTYPE_2DEFFECT);

			//ステート切り替え
			m_titlestate = CTitle::STATE_NORMAL;
		}
	}

	//通常状態のとき
	if (m_titlestate == STATE_NORMAL)
	{
		//フェードしてない時
		if (CManager::GetRenderer()->GetFade()->GetFade() == CFade::FADE_NONE)
		{
			//ある程度時間たったら
			if (m_nCntState < 0)
			{
				//デモプレイ
				CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_DEMOPLAY);
			}

			//なんかボタン押されたとき
			if (CHossoLibrary::CheckAnyButton() && m_nCntState < DEMOPLAY_FADE_COUNT - TITLEUI_APPEAR_COUNT - 10)
			{
				//チュートリアルに遷移
				CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_TUTORIAL);
				CManager::GetSound()->Play(CSound::LABEL_SE_DECISION);

			}
		}
	}
}

//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CTitle::Draw()
{
}
