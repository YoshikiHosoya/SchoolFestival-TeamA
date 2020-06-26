//-----------------------------------------------------------------------------
//
//テクスチャ管理  [texture.cpp]
// Author : Yoshiki Hosoya
//
//-----------------------------------------------------------------------------
#include "texture.h"
#include "manager.h"
#include "renderer.h"
//-----------------------------------------------------------------------------
//静的メンバ変数の初期化
//-----------------------------------------------------------------------------
std::vector<LPDIRECT3DTEXTURE9> CTexture::m_apTextureList = {};
std::vector<LPDIRECT3DTEXTURE9> CTexture::m_apSeparateTextureList = {};

std::vector<D3DXVECTOR2> CTexture::m_UVSizeList = {};
std::vector<D3DXVECTOR2> CTexture::m_UVCntList = {};

//テクスチャ名の設定
std::vector<std::string> CTexture::m_aTexFileName =
{
	{ "data/TEXTURE/UI/other/TexNone.png" },					//白紙
	{ "data/TEXTURE/UI/other/PressButton.png" },				//プレスボタン

	{ "data/TEXTURE/UI/title/TitleLogo.png" },					//タイトルロゴ
	{ "data/TEXTURE/UI/title/BG.jpg" },							//タイトル背景
	{ "data/TEXTURE/UI/game/Combo.png" },						//コンボ
	{ "data/TEXTURE/UI/game/KILL01.png" },						//キル
	{ "data/TEXTURE/UI/game/PlayerIcon.png" },					//プレイヤーアイコン
	{ "data/TEXTURE/UI/tutorial/X_ComboPattern.png" },			//コンボパターン
	{ "data/TEXTURE/UI/tutorial/Key_ComboPattern.png" },		//コンボパターン
	{ "data/TEXTURE/UI/game/Time.png" },						//タイム

	{ "data/TEXTURE/UI/result/ResultLogo.png" },				//リザルトロゴ
	{ "data/TEXTURE/UI/result/ResultCalc.png" },				//スコア計算

	{ "data/TEXTURE/UI/ranking/RankingLogo.png" },				//ランキングロゴ
	{ "data/TEXTURE/UI/ranking/BG.jpg" },						//ランキング背景
	{ "data/TEXTURE/UI/ranking/1ST.png" },						//1
	{ "data/TEXTURE/UI/ranking/2ND.png" },						//2
	{ "data/TEXTURE/UI/ranking/3RD.png" },						//3
	{ "data/TEXTURE/UI/ranking/4TH.png" },						//4
	{ "data/TEXTURE/UI/ranking/5TH.png" },						//5

	{ "data/TEXTURE/UI/tutorial/X_Skip.png" },					//チュートリアル XInput　スキップ
	{ "data/TEXTURE/UI/tutorial/X_Move.png" },					//チュートリアル XInput　移動
	{ "data/TEXTURE/UI/tutorial/X_Dash.png" },					//チュートリアル XInput　ダッシュ
	{ "data/TEXTURE/UI/tutorial/X_CameraRoll.png" },			//チュートリアル XInput　カメラ回転
	{ "data/TEXTURE/UI/tutorial/X_CameraReset.png" },			//チュートリアル XInput　始点リセット
	{ "data/TEXTURE/UI/tutorial/X_Jump.png" },					//チュートリアル XInput　ジャンプ
	{ "data/TEXTURE/UI/tutorial/X_Attack.png" },				//チュートリアル XInput　攻撃
	{ "data/TEXTURE/UI/tutorial/X_StartChain.png" },			//チュートリアル XInput　連鎖
	{ "data/TEXTURE/UI/tutorial/X_ChainThunder.png" },			//チュートリアル XInput　連鎖爆発の説明

	{ "data/TEXTURE/UI/tutorial/Key_Skip.png" },				//チュートリアル Keyboard　スキップ
	{ "data/TEXTURE/UI/tutorial/Key_Move.png" },				//チュートリアル Keyboard　移動
	{ "data/TEXTURE/UI/tutorial/Key_Dash.png" },				//チュートリアル Keyboard　ダッシュ
	{ "data/TEXTURE/UI/tutorial/Key_CameraRoll.png" },			//チュートリアル Keyboard　カメラ回転
	{ "data/TEXTURE/UI/tutorial/Key_CameraReset.png" },			//チュートリアル Keyboard　始点リセット
	{ "data/TEXTURE/UI/tutorial/Key_Jump.png" },				//チュートリアル Keyboard　ジャンプ
	{ "data/TEXTURE/UI/tutorial/Key_Attack.png" },				//チュートリアル Keyboard　攻撃
	{ "data/TEXTURE/UI/tutorial/Key_StartChain.png" },			//チュートリアル Keyboard　連鎖
	{ "data/TEXTURE/UI/tutorial/Key_ChainThunder.png" },		//チュートリアル Keyboard　連鎖爆発の説明

	{ "data/TEXTURE/UI/tutorial/Free.png" },					//チュートリアル　自由
	{ "data/TEXTURE/UI/tutorial/End.png" },						//チュートリアル　終了
	{ "data/TEXTURE/UI/tutorial/OK.png" },						//チュートリアル　OK

	{ "data/TEXTURE/UI/Pause/PauseLogo.png" },					//ポーズロゴ
	{ "data/TEXTURE/UI/option/OptionLogo.png" },				//オプションロゴ

	{ "data/TEXTURE/UI/minimap/MiniMap.png" },					//ミニマップ
	{ "data/TEXTURE/UI/minimap/PlayerMapping.png" },			//プレイヤー
	{ "data/TEXTURE/UI/minimap/EnemyMapping.png" },				//敵
	{ "data/TEXTURE/UI/minimap/ExplosionMapping.png" },			//爆発

	{ "data/TEXTURE/UI/other/Start.png" },						//終了
	{ "data/TEXTURE/UI/other/Finish.png" },						//終了

	{ "data/TEXTURE/mesh/field000.jpg" },						//メッシュフィールド
	{ "data/TEXTURE/orbit/orbit03.jpg" },						//軌跡
	{ "data/TEXTURE/effect/particle.jpg" },						//パーティクル
	{ "data/TEXTURE/effect/SphereExplosion.jpg" },				//スフィアの雷
	{ "data/TEXTURE/effect/CircleThunder.jpeg" },				//スフィアの雷

	{ "data/TEXTURE/effect/ExplosionShadow.jpg" },				// 爆発跡

	{ "data/TEXTURE/UI/backUI/pushB.png" },						// pushB
	{ "data/TEXTURE/UI/backUI/pushZ.png" },						// pushB
	{ "data/TEXTURE/UI/backUI/PlayerHit.jpg" },					// プレイヤー被弾
	{ "data/TEXTURE/UI/backUI/Rain.jpg" },						// 雨
};


//テクスチャ名の設定
std::vector<std::string> CTexture::m_aSeparateTexFileName =
{
	{ "data/TEXTURE/UI/other/Number00.png" },					//数字
	{ "data/TEXTURE/UI/pause/Menu.png" },						//ポーズメニュー
	{ "data/TEXTURE/UI/option/ON_OFF.png" },					//ON_OFF
	{ "data/TEXTURE/UI/option/OptionMenu.png" },				//オプションメニュー

	{ "data/TEXTURE/effect/particle.jpg" },						//パーティクル
	{ "data/TEXTURE/effect/BackThunder.jpg" },					//背景の落雷
	{ "data/TEXTURE/effect/LineThunder.png" },					//背景の落雷
	{ "data/TEXTURE/effect/pushingB.png" },						//PushB
	{ "data/TEXTURE/effect/ChainElectric.png" },				//連鎖爆発
	{ "data/TEXTURE/effect/ChainThunderStart.png" },			//連鎖爆発開始
	{ "data/TEXTURE/effect/hit_spark.png" },					//ヒットエフェクト　火花
	{ "data/TEXTURE/effect/hit_stan.png" },						//ヒットエフェクト　スタン時
	{ "data/TEXTURE/effect/slash.png" },						//ヒットエフェクト　斬撃
	{ "data/TEXTURE/effect/smoke.png" },						//煙
	{ "data/TEXTURE/effect/SparkExplosion.png" },				//電撃の爆発っぽいの
	{ "data/TEXTURE/effect/stan.png" },							//スタン状態
	{ "data/TEXTURE/effect/TitleSpark.png" },					//タイトルの最初の電撃
	{ "data/TEXTURE/effect/EnemyRespawn.jpg" },					//敵出現時のエフェクト
	{ "data/TEXTURE/effect/GameStart.jpg" },					//ゲーム開始

};

//-----------------------------------------------------------------------------
//テクスチャ一括ロード
//-----------------------------------------------------------------------------
void CTexture::TexLoad(HWND hwnd)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	LPDIRECT3DTEXTURE9 pTexture;

	//テクスチャ名のリストのサイズ分
	for (size_t nCnt = 0; nCnt < m_aTexFileName.size(); nCnt++)
	{
		//null
		pTexture = nullptr;

		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			m_aTexFileName[nCnt].data(),
			&pTexture);

		//debug
		std::cout << "Tex Load - " << nCnt << m_aTexFileName[nCnt].data() << NEWLINE;

		//nullcheck
		if (!pTexture)
		{
			//debug
			std::cout << "LOADFAILED!!! Tex - " << nCnt << m_aTexFileName[nCnt].data() << NEWLINE;

			//失敗
			MessageBox(hwnd, "テクスチャ読み込み失敗", m_aTexFileName[nCnt].data(), MB_OK | MB_ICONHAND);
		}

		//リストに追加
		m_apTextureList.emplace_back(pTexture);
	}

	//テクスチャ名のリストのサイズ分
	for (size_t nCnt = 0; nCnt < m_aSeparateTexFileName.size(); nCnt++)
	{
		//null
		pTexture = nullptr;

		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			m_aSeparateTexFileName[nCnt].data(),
			&pTexture);

		//debug
		std::cout << "SeparateTex Load - " << nCnt << m_aSeparateTexFileName[nCnt].data() << NEWLINE;

		//nullcheck
		if (!pTexture)
		{
			//debug
			std::cout << "LOADFAILED!!! SeparateTex - " << nCnt << m_aSeparateTexFileName[nCnt].data() << NEWLINE;

			//失敗
			MessageBox(hwnd, "テクスチャ読み込み失敗", m_aSeparateTexFileName[nCnt].data(), MB_OK | MB_ICONHAND);
		}

		//リストに追加
		m_apSeparateTextureList.emplace_back(pTexture);

		//UVの情報　初期化
		D3DXVECTOR2 UVCnt = ZeroVector2;
		D3DXVECTOR2 UVSize = ZeroVector2;

		//それぞれのUV枚数設定
		switch (nCnt)
		{
		case SEPARATE_TEX_UI_PAUSE_MENU:
			UVCnt = D3DXVECTOR2(1, 4);
			break;

		case SEPARATE_TEX_UI_ON_OFF:
			UVCnt = D3DXVECTOR2(2, 1);
			break;

		case SEPARATE_TEX_UI_OPTIONMENU:
			UVCnt = D3DXVECTOR2(1, 3);
			break;

		case SEPARATE_TEX_EFFECT_FLASH:
			UVCnt = D3DXVECTOR2(1, 1);
			break;

		case SEPARATE_TEX_EFFECT_BACKTHUNDER:
			UVCnt = D3DXVECTOR2(5, 1);
			break;

		case SEPARATE_TEX_EFFECT_LINETHUNDER:
			UVCnt = D3DXVECTOR2(5, 1);
			break;

		case SEPARATE_TEX_EFFECT_PUSHING_B:
			UVCnt = D3DXVECTOR2(1, 7);
			break;

		case SEPARATE_TEX_EFFECT_CHAINELECTRIC:
			UVCnt = D3DXVECTOR2(5, 3);
			break;

		case SEPARATE_TEX_EFFECT_CHAINTHUNDER:
			UVCnt = D3DXVECTOR2(2, 10);
			break;

		case SEPARATE_TEX_EFFECT_HIT_SPARK:
			UVCnt = D3DXVECTOR2(12, 1);
			break;

		case SEPARATE_TEX_EFFECT_HIT_STAN:
			UVCnt = D3DXVECTOR2(5, 1);
			break;

		case SEPARATE_TEX_EFFECT_HIT_SLASH:
			UVCnt = D3DXVECTOR2(1, 1);
			break;

		case SEPARATE_TEX_EFFECT_SMOKE:
			UVCnt = D3DXVECTOR2(10, 1);
			break;

		case SEPARATE_TEX_EFFECT_SPARKEXPLOSION:
			UVCnt = D3DXVECTOR2(5, 2);
			break;

		case SEPARATE_TEX_EFFECT_STANING:
			UVCnt = D3DXVECTOR2(2, 2);
			break;

		case SEPARATE_TEX_EFFECT_TITLESPARK:
			UVCnt = D3DXVECTOR2(5, 5);
			break;

		case SEPARATE_TEX_EFFECT_ENEMY_RESPAWN:
			UVCnt = D3DXVECTOR2(5, 1);
			break;

		case SEPARATE_TEX_EFFECT_GAME_START:
			UVCnt = D3DXVECTOR2(5, 2);
			break;
		}

		//UVサイズ設定
		UVSize = D3DXVECTOR2(1.0f / UVCnt.x, 1.0f / UVCnt.y);

		//リストに追加
		m_UVSizeList.emplace_back(UVSize);
		m_UVCntList.emplace_back(UVCnt);

	}
}

//-----------------------------------------------------------------------------
//テクスチャ一括破棄
//----------------------------------------------------------------------------
void CTexture::TexUnload()
{
	//サイズ分
	for (size_t nCnt = 0; nCnt < m_apTextureList.size(); nCnt++)
	{
		//nullcheck
		if (m_apTextureList[nCnt])
		{
			//テクスチャの開放
			m_apTextureList[nCnt]->Release();
			m_apTextureList[nCnt] = nullptr;
		}
	}

	//サイズ分
	for (size_t nCnt = 0; nCnt < m_apSeparateTextureList.size(); nCnt++)
	{
		//nullcheck
		if (m_apSeparateTextureList[nCnt])
		{
			//テクスチャの開放
			m_apSeparateTextureList[nCnt]->Release();
			m_apSeparateTextureList[nCnt] = nullptr;
		}
	}

	//配列の開放
	m_apTextureList.clear();
	m_apSeparateTextureList.clear();
}

//-----------------------------------------------------------------------------
//テクスチャ取得　通常
//----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEX_TYPE textype)
{
	//配列より小さい値か
	if (textype < (int)m_apTextureList.size())
	{
		//nullcheck
		if (m_apTextureList[textype])
		{
			return m_apTextureList[textype];
		}
	}
	return nullptr;
}

//-----------------------------------------------------------------------------
//テクスチャ取得　分割されてるやつ
//----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::GetSeparateTexture(SEPARATE_TEX_TYPE textype)
{
	//配列より小さい値か
	if (textype < (int)m_apSeparateTextureList.size())
	{
		//nullcheck
		if (m_apSeparateTextureList[textype])
		{
			return m_apSeparateTextureList[textype];
		}
	}
	return nullptr;
}
//-----------------------------------------------------------------------------
//テクスチャのUVサイズ取得
//----------------------------------------------------------------------------
D3DXVECTOR2 CTexture::GetSparateTex_UVSize(SEPARATE_TEX_TYPE textype)
{
	//配列より小さい値か
	if (textype < (int)m_UVSizeList.size())
	{
		//nullcheck
		if (m_UVSizeList[textype])
		{
			return m_UVSizeList[textype];
		}
	}
	return ZeroVector2;
}

//-----------------------------------------------------------------------------
//テクスチャのUV枚数取得
//----------------------------------------------------------------------------
D3DXVECTOR2 CTexture::GetSparateTex_UVCnt(SEPARATE_TEX_TYPE textype)
{
	//配列より小さい値か
	if (textype < (int)m_UVCntList.size())
	{
		//nullcheck
		if (m_UVCntList[textype])
		{
			return m_UVCntList[textype];
		}
	}
	return ZeroVector2;
}
