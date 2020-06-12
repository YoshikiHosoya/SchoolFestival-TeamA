// =====================================================================================================================================================================
//
// ゲームUIの処理 [resultUI.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "gameUI.h"			// インクルードファイル
#include "manager.h"
#include "renderer.h"
#include "number.h"
#include "game.h"
#include "keyboard.h"
#include "player.h"
#include "sound.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
LPDIRECT3DTEXTURE9	CGameUI::m_apTexture[GAMEUITYPE::G_UI_MAX]	= {};						// テクスチャ
CNumber				*CGameUI::m_apNumber[LIFE_DIGIT]			= {};						// ナンバーのポインタ
D3DXVECTOR2			CGameUI::m_UVsize							= D3DXVECTOR2(0.1f, 1.0f);	// UVサイズ
bool				CGameUI::m_bGageDecrease					= true;						// ゲージの減少

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define TEXTURE_FILE00		"data/TEXTURE/Dlunker.png"			// 読み込むテクスチャファイル名	( アイコン )
#define TEXTURE_FILE01		"data/TEXTURE/min.png"				// 読み込むテクスチャファイル名	( MIN )
#define TEXTURE_FILE02		"data/TEXTURE/max.png"				// 読み込むテクスチャファイル名	( MAX )
#define TEXTURE_FILE03		"data/TEXTURE/gage.png"				// 読み込むテクスチャファイル名	( ゲージ )
#define TEXTURE_FILE04		"data/TEXTURE/towa00.png"			// 読み込むテクスチャファイル名	( 三角 )		triangle

#define ICON_POSX			(250.0f)							// アイコンの座標X
#define ICON_POSY			(50.0f)								// アイコンの座標Y
#define ICON_SIZEX			(60.0f / 2)							// アイコンの幅
#define ICON_SIZEY			(60.0f / 2)							// アイコンの高さ

#define STOP_MIN_POSX		(440.0f)							// MINの座標X
#define START_MAX_POSX		(840.0f)							// MAXの座標X
#define MIN_MAX_POSY		(30.0f)								// MINとMAXの座標Y
#define MIN_MAX_SIZEX		(60.0f / 2)							// MINとMAXの幅
#define MIN_MAX_SIZEY		(40.0f / 2)							// MINとMAXの高さ

#define GAGE_POSX			(640.0f)							// ゲージの座標X
#define GAGE_POSY			(60.0f)								// ゲージの座標Y
#define GAGE_SIZEX			(200.0f)							// ゲージの幅
#define GAGE_SIZEY			(10.0f)								// ゲージの高さ
#define GAGE_RECOVERY_SPEED	(50)								// ゲージの回復する速さ

#define TRIANGLE_POSX		(GAGE_POSX + GAGE_SIZEX)			// 三角の座標X
#define TRIANGLE_MOVEX		(-0.02f)							// 三角の移動
#define TRIANGLE_SIZEX		(15.0f)								// 三角の幅
#define TRIANGLE_SIZEY		(15.0f)								// 三角の高さ

#define LIFE_POSX			(300.0f)							// 体力の座標X
#define LIFE_POSY			(50.0f)								// 体力の座標Y
#define LIFE_SIZEX			(15.0f)								// 体力の幅
#define LIFE_SIZEY			(20.0f)								// 体力の高さ
#define LIFE_SPACE			(25.0f)								// 体力の間隔

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CGameUI::CGameUI():CScene2D(PRIORITY_UI)
{
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CGameUI::~CGameUI()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
void CGameUI::Init()
{
	m_fTriangleMoveX	= 0.0f;			// 三角の横移動
	m_bGageDecrease		= true;			// ゲージが減少しているか

	for (int nCnt = 0; nCnt < GAMEUITYPE::G_UI_MAX; nCnt++)
	{
		// 初期化
		m_aCol[nCnt] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);		// 色

		if (m_apScene2D != NULL)
		{
			// 変数初期化
			m_UV[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 移動

			// シーン2Dの生成														// CScene2Dは = の形で生成する ( リターンが行われなくなるため )
			m_apScene2D[nCnt] = CScene2D::Create();

			// テクスチャの割り当て
			m_apScene2D[nCnt]->BindTexture(m_apTexture[nCnt]);

			// 初期化
			m_apScene2D[nCnt]->Init();

			switch (nCnt)
			{
			case GAMEUITYPE::G_UI_ICON:

				//位置の設定
				m_apScene2D[nCnt]->SetPos(D3DXVECTOR3(ICON_POSX, ICON_POSY, 0.0f));
				// サイズの設定
				m_apScene2D[nCnt]->SetSize(D3DXVECTOR3(ICON_SIZEX, ICON_SIZEY, 0.0f));
				// 色の設定
				m_apScene2D[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;

			case GAMEUITYPE::G_UI_STOP_MIN:

				//位置の設定
				m_apScene2D[nCnt]->SetPos(D3DXVECTOR3(STOP_MIN_POSX, MIN_MAX_POSY, 0.0f));
				// サイズの設定
				m_apScene2D[nCnt]->SetSize(D3DXVECTOR3(MIN_MAX_SIZEX, MIN_MAX_SIZEY, 0.0f));
				// 色の設定
				m_apScene2D[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;

			case GAMEUITYPE::G_UI_START_MAX:

				//位置の設定
				m_apScene2D[nCnt]->SetPos(D3DXVECTOR3(START_MAX_POSX, MIN_MAX_POSY, 0.0f));
				// サイズの設定
				m_apScene2D[nCnt]->SetSize(D3DXVECTOR3(MIN_MAX_SIZEX, MIN_MAX_SIZEY, 0.0f));
				// 色の設定
				m_apScene2D[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;

			case GAMEUITYPE::G_UI_GAGE:

				//位置の設定
				m_apScene2D[nCnt]->SetPos(D3DXVECTOR3(GAGE_POSX, GAGE_POSY, 0.0f));
				// サイズの設定
				m_apScene2D[nCnt]->SetSize(D3DXVECTOR3(GAGE_SIZEX, GAGE_SIZEY, 0.0f));
				// 色の設定
				m_apScene2D[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;

			case GAMEUITYPE::G_UI_TRIANGLE:

				//位置の設定
				m_apScene2D[nCnt]->SetPos(D3DXVECTOR3(TRIANGLE_POSX, GAGE_POSY, 0.0f));
				// サイズの設定
				m_apScene2D[nCnt]->SetSize(D3DXVECTOR3(TRIANGLE_SIZEX, TRIANGLE_SIZEY, 0.0f));
				// 色の設定
				m_apScene2D[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
			}
		}
	}
	for (int nCnt = 0; nCnt < LIFE_DIGIT; nCnt++)
	{
		if (m_apNumber != NULL)
		{
			// シーン2Dの生成
			m_apNumber[nCnt] = CNumber::Create();

			// 初期化
			m_apNumber[nCnt]->Init();

			//位置の設定
			m_apNumber[nCnt]->SetPos(D3DXVECTOR3(LIFE_POSX + nCnt * LIFE_SPACE, LIFE_POSY, 0.0f));

			// サイズの設定
			m_apNumber[nCnt]->SetSize(D3DXVECTOR3(LIFE_SIZEX, LIFE_SIZEY, 0.0f));

			// アニメーションの設定
			m_apNumber[nCnt]->SetAnim(D3DXVECTOR2(0.1f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
		}
	}
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CGameUI::Uninit(void)
{
	for (int nCnt = 0; nCnt < GAMEUITYPE::G_UI_MAX; nCnt++)
	{
		if (m_apScene2D != NULL)
		{
			// 終了
			m_apScene2D[nCnt]->Uninit();
		}
	}
	for (int nCnt = 0; nCnt < LIFE_DIGIT; nCnt++)
	{
		if (m_apNumber != NULL)
		{
			m_apNumber[nCnt]->Release();
			m_apNumber[nCnt] = NULL;
		}
	}
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CGameUI::Update(void)
{
	// 変数
	D3DXVECTOR3 pos;

	for (int nCnt = 0; nCnt < GAMEUITYPE::G_UI_MAX; nCnt++)
	{
		if (m_apScene2D != NULL)
		{
			// 三角の移動
			MoveTriangle();
			// 更新
			m_apScene2D[nCnt]->Update();
		}
	}
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CGameUI::Draw(void)
{	
	for (int nCnt = 0; nCnt < GAMEUITYPE::G_UI_MAX; nCnt++)
	{
		if (m_apScene2D != NULL)
		{
			m_apScene2D[nCnt]->Draw();
		}
	}
}

// =====================================================================================================================================================================
//
// 体力の設定
//
// =====================================================================================================================================================================
void CGameUI::SetLife(int nLife)
{
	// 変数宣言
	int nNumber = 0;

	for (int nCntScore = 0; nCntScore < LIFE_DIGIT; nCntScore++)
	{
		// 桁数計算
		nNumber = nLife % (int)pow(10.0f, LIFE_DIGIT - nCntScore) / (int)pow(10.0f, (LIFE_DIGIT - nCntScore - 1));

		// アニメーションの設定
		m_apNumber[nCntScore]->SetAnim(m_UVsize, D3DXVECTOR2(nNumber * 0.1f, 0.0f));
	}
}

// =====================================================================================================================================================================
//
// ゲームUIの生成
//
// =====================================================================================================================================================================
CGameUI * CGameUI::Create()
{
	// 変数
	CGameUI *pGameUI;

	// メモリの確保
	pGameUI = new CGameUI();

	// 初期化
	pGameUI->Init();

	return pGameUI;
}

// =====================================================================================================================================================================
//
// ロード
//
// =====================================================================================================================================================================
HRESULT CGameUI::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

	// テクスチャファイル名
	char *sTextureFileName[G_UI_MAX]
	{
		{ TEXTURE_FILE00 },		// G_UI_ICON			( アイコン
		{ TEXTURE_FILE01 },		// G_UI_STOP_MIN		( MIN
		{ TEXTURE_FILE02 },		// G_UI_START_MAX		( MAX
		{ TEXTURE_FILE03 },		// G_UI_GAGE			( ゲージ
		{ TEXTURE_FILE04 },		// G_UI_TRIANGLE		( 三角
	};

	for (int nCntUI = 0; nCntUI < G_UI_MAX; nCntUI++)
	{
		// テクスチャ読み込み
		D3DXCreateTextureFromFile(pDevice, sTextureFileName[nCntUI], &m_apTexture[nCntUI]);
	}

	for (int nCnt = 0; nCnt < G_UI_MAX; nCnt++)
	{
		// エラーチェック
		if (m_apTexture[nCnt] == NULL)
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

// =====================================================================================================================================================================
//
// アンロード
//
// =====================================================================================================================================================================
void CGameUI::Unload(void)
{
	for (int nCnt = 0; nCnt < GAMEUITYPE::G_UI_MAX; nCnt++)
	{
		// テクスチャの開放
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}

// =====================================================================================================================================================================
//
// ゲージを回復
//
// =====================================================================================================================================================================
void CGameUI::RecoveryGage(void)
{
	//	ゲージの回復音
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_GAGE);

	m_bGageDecrease = false;		// ゲージを回復させる
}

// =====================================================================================================================================================================
//
// 三角の移動処理
//
// =====================================================================================================================================================================
void CGameUI::MoveTriangle(void)
{
	// プレイヤーの情報取得
	CPlayer *pPlayer;
	pPlayer = CManager::GetGame()->GetPlayer();

	// 位置の取得
	D3DXVECTOR3 pos	= m_apScene2D[G_UI_TRIANGLE]->GetPos();

	// ゲージが減少しているか
	if (m_bGageDecrease)
	{
		m_fTriangleMoveX = TRIANGLE_MOVEX;		// 三角の移動値
	}
	else
	{
		m_fTriangleMoveX = -TRIANGLE_MOVEX * GAGE_RECOVERY_SPEED;	// 最大値まで回復

		// 最大値まで回復したとき
		if (pos.x >= START_MAX_POSX)
		{
			m_fTriangleMoveX = 0.0f;		// 移動を止める
			m_bGageDecrease = true;		// ゲージを減少させる
		}
	}

	// MINに達したとき
	if (pos.x <= STOP_MIN_POSX)
	{
		m_fTriangleMoveX = 0.0f;		// 移動を止める

		// プレイヤーにダメージ
		pPlayer->PlayerDamage(1);
		// プレイヤーを死んだ状態に
		pPlayer->SetPlayerState(CPlayer::PLAYERSTATE_DEATH);
		// ゲージ回復
		m_fTriangleMoveX = -TRIANGLE_MOVEX * GAGE_RECOVERY_SPEED;	// 最大値まで回復
	}

	// 位置更新
	pos.x += m_fTriangleMoveX;

	// 位置の設定
	m_apScene2D[G_UI_TRIANGLE]->SetPos(pos);
}