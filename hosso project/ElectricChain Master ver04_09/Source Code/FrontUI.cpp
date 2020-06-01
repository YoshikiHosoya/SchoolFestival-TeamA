//------------------------------------------------------------------------------
//
//前面のUI  [FrontUI.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "frontUI.h"
#include "manager.h"
#include "renderer.h"
#include "basemode.h"
#include "Pad_XInput.h"
#include "player.h"
#include "sound.h"
#include "enemy.h"
#include "effectanimation2D.h"
#include "camera.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------
bool CFrontUI::m_bPushB = false;
//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CFrontUI::CFrontUI()
{
	m_nCntUI = 0;
}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CFrontUI::~CFrontUI()
{
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CFrontUI::Init()
{
	//初期化処理
	if (FAILED(CScene2D::Init()))
	{
		return E_FAIL;
	}
	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CFrontUI::Uninit()
{
	//終了処理
	CScene2D::Uninit();
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CFrontUI::Update()
{
	//カウンタ++
	m_nCntUI++;

	//色初期化
	D3DXCOLOR col = WhiteColor;
	D3DXVECTOR2 UV = ZeroVector2;

	//プレイヤーのポインタ　初期化
	CPlayer *pPlayer = nullptr;

	switch (m_Type)
	{
	case CFrontUI::PUSH_B:
		//点滅処理
		if (m_nCntUI % 2 == 0)
		{
			//排他的論理和
			SetDisp(GetDisp() ^= 1);
		}

		//プレイヤーのポインタ取得
		pPlayer = CManager::GetBaseMode()->GetPlayer();

		//nullcheck
		if (pPlayer)
		{
			//もし敵がリスポーンして総数がズレた時
			if (CEnemy::GetEnemyNum() != CEnemy::GetStanEnemyNum())
			{
				//消す
				Release();
				m_bPushB = false;
			}
			//雷発動してるか
			if (pPlayer->GetChainThunder())
			{
				//エフェクト生成
				CEffectAnimation2D::Create(GetPos(), GetSize() * 2.0f, CTexture::SEPARATE_TEX_EFFECT_PUSHING_B, 0.0f, 2, CScene::OBJTYPE_FRONTUI);

				//音再生
				CManager::GetSound()->Play(CSound::LABEL_SE_SLASH_STAN);

				//ゲーム中のとき
				if (CManager::GetRenderer()->GetCamera()->GetCameraState() == CCamera::CAMERA_GAME)
				{
					//カメラを連鎖爆発中の処理
					CManager::GetRenderer()->GetCamera()->SetState(CCamera::CAMERA_CHAIN_EXPLOSION);
				}

				//消去
				Release();
				m_bPushB = false;
			}
		}
		break;

		//プレイヤー被弾
	case CFrontUI::PLAYER_HIT:

		//色取得
		col = GetCol();

		//透明にする
		col.a -= 0.1f;

		//透明になったら
		if (col.a <= 0.0f)
		{
			//消去
			Release();
		}

		//色設定
		SetVtxCol(col);
		break;

	case CFrontUI::RAIN:
		//UV移動 ↓に動いてるように見せる
		UV = D3DXVECTOR2(-0.0015f * m_nCntUI,-0.05f * m_nCntUI);

		//UV設定
		SetAnimation(UV, D3DXVECTOR2(2.0f, 2.0f));
		break;

	case CFrontUI::GAMESTART:

		//色取得
		col = GetCol();

		//透明にする
		col.a -= 0.04f;

		//透明になったら
		if (col.a <= 0.0f)
		{
			//消去
			Release();
		}

		//色設定
		SetVtxCol(col);
		break;
	}

	//更新処理
	CScene2D::Update();
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CFrontUI::Draw()
{
	//被弾エフェクトと雨は加算合成する
	if (m_Type == CFrontUI::PLAYER_HIT || m_Type == CFrontUI::RAIN)
	{
		//加算合成
		CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ALPHABLEND_ADD);

		//Zテスト無効
		CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_OFF);
	}

	//描画処理
	CScene2D::Draw();

	//Zテスト通常
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);

	//通常合成
	CManager::GetRenderer()->SetRendererCommand(CRenderer::REDNERER_ALPHABLEND_DEFAULT);

}
//------------------------------------------------------------------------------
//デバッグ情報表示
//------------------------------------------------------------------------------
void CFrontUI::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //_DEBUG
}

//------------------------------------------------------------------------------
//生成処理
//------------------------------------------------------------------------------
void CFrontUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TEX_TYPE type)
{
	//メモリ確保
	std::unique_ptr<CFrontUI> pBackUI(new CFrontUI);

	//nullcheck
	if (pBackUI)
	{
		//初期化
		pBackUI->Init();

		//初期化
		pBackUI->m_Type = type;
		pBackUI->SetPos(pos);
		pBackUI->SetSize(size);
		pBackUI->SetVtxCol(col);

		//タイプによってテクスチャ差し替え
		switch (pBackUI->m_Type)
		{
		case CFrontUI::PUSH_B:
			//pushBが生成されていた場合
			if (m_bPushB)
			{
				//メモリ開放して終了
				pBackUI.reset();
				return;
			}

			//コントローラが接続されているかどうかでテクスチャ差し替え
			CManager::GetXInput()->GetConnect() ?
				pBackUI->BindTexture(CTexture::GetTexture(CTexture::TEX_BACKUI_PUSH_B)) :
				pBackUI->BindTexture(CTexture::GetTexture(CTexture::TEX_BACKUI_PUSH_Z));

			//PushB
			m_bPushB = true;
			break;

			//被弾
		case CFrontUI::PLAYER_HIT:
			pBackUI->BindTexture(CTexture::GetTexture(CTexture::TEX_BACKUI_DAMAGED));
			break;

			//雨
		case CFrontUI::RAIN:
			pBackUI->BindTexture(CTexture::GetTexture(CTexture::TEX_BACKUI_RAIN));
			pBackUI->SetVtxCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
			break;

			//ゲームスタート
		case CFrontUI::GAMESTART:
			pBackUI->BindTexture(CTexture::GetTexture(CTexture::TEX_GAMESTART));
			break;
		default:

			break;
		}
		//オブジェタイプ追加してSceneに追加
		pBackUI->SetObjType(OBJTYPE_FRONTUI);
		pBackUI->AddUniqueList(std::move(pBackUI));
	}
}