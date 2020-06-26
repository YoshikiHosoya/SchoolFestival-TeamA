//------------------------------------------------------------------------------
//
//デモプレイ処理  [demoplay.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "demoplay.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "player.h"
#include "fade.h"
#include "keyboard.h"
#include "camera.h"
#include "Map.h"
#include "enemy.h"
#include "ui.h"
#include "player_demo.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define DEFAULT_PLAYER_POS	(D3DXVECTOR3(0.0f, 0.0f, -800.0f))		//プレイヤーの初期座標
#define ENEMY_LINE			(INTEGER2(4,4))							//敵の列
#define ENEMY_SPACE			(150.0f)								//敵の感覚
#define TITLE_FADE_COUNT	(1200)									//タイトルにフェードするまでのカウンタ
//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CDemoPlay::CDemoPlay()
{
	//初期化
	m_pPlayer.reset();
	m_nCntTitleFade = TITLE_FADE_COUNT;
	m_nEnemyPopTime = 0;
}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CDemoPlay::~CDemoPlay()
{

}

//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CDemoPlay::Init(HWND hWnd)
{
	//カメラ座標設定
	CManager::GetRenderer()->GetCamera()->SetCameraPos(DEFAULT_PLAYER_POS, DEFAULT_PLAYER_POS + D3DXVECTOR3(0.0f, 200, -600));
	CManager::GetRenderer()->GetCamera()->SetState(CCamera::CAMERA_GAME);

	//マップ
	CMap::Create();

	//プレイヤー生成
	m_pPlayer = CPlayer_Demo::Create(DEFAULT_PLAYER_POS);

	//敵生成
	EnemyRespawn();

	return S_OK;
}

//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CDemoPlay::Uninit()
{
	//終了処理
	CScene::ReleaseAll();
}

//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CDemoPlay::Update()
{
	//フェードしてない時
	if (CManager::GetRenderer()->GetFade()->GetFade() == CFade::FADE_NONE)
	{
		//カウントダウン
		m_nCntTitleFade--;

		//ある程度時間たつか敵が全滅したかなんか入力されたとき
		if (m_nCntTitleFade <= 0 || CEnemy::GetEnemyNum() <= 0 || CHossoLibrary::CheckAnyButton())
		{
			//タイトルに戻る
			CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_TITLE);
			CManager::GetSound()->Play(CSound::LABEL_SE_DECISION);
		}
	}
}

//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CDemoPlay::Draw()
{

}
//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CDemoPlay::ShowDebugInfo()
{

}
//------------------------------------------------------------------------------
//プレイヤー取得
//------------------------------------------------------------------------------
CPlayer * CDemoPlay::GetPlayer()
{
	if (m_pPlayer)
	{
		return m_pPlayer.get();
	}
	return nullptr;
}

//------------------------------------------------------------------------------
//敵生成
//------------------------------------------------------------------------------
void CDemoPlay::EnemyRespawn()
{
	//敵生成
	for (int nCntH = 0; nCntH < ENEMY_LINE.x; nCntH++)
	{
		for (int nCntV = 0; nCntV < ENEMY_LINE.y; nCntV++)
		{
			CEnemy::Create(D3DXVECTOR3(
				-ENEMY_LINE.x * 0.5f * ENEMY_SPACE + nCntH * ENEMY_SPACE,
				0.0f,
				-ENEMY_LINE.y * 0.5f * ENEMY_SPACE + nCntV * ENEMY_SPACE), CEnemy::TYPE_NORMAL);
		}
	}
}
