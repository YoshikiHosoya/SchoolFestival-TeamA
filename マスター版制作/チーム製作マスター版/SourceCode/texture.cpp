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

//テクスチャ名の設定
FILENAME_LIST CTexture::m_aTexFileName =
{
	{ "data/TEXTURE/TexNone.png" },							//白紙
	{ "data/TEXTURE/Effect/particle.jpg" },					//パーティクル用の丸いの
	{ "data/TEXTURE/Bullet/bullet00.png" },					//ハンドガンの弾

	{ "data/TEXTURE/Item/Weapon/Heavymachinegun.png" },		//ヘビーマシンガンの弾
	{ "data/TEXTURE/Item/Weapon/Shotgun.png" },				//ショットガンの弾
	{ "data/TEXTURE/Item/Weapon/Lasergun.png" },			//レーザーガンの弾
	{ "data/TEXTURE/Item/Weapon/Rocketlauncher.png" },		//ロケットランチャーの弾
	{ "data/TEXTURE/Item/Weapon/Flameshot.png" },			//フレイムショットの弾

	{ "data/TEXTURE/Item/Score/GoldCoin.png" },				//金貨
	{ "data/TEXTURE/Item/Score/SilverCoin.png" },			//銀貨
	{ "data/TEXTURE/Item/Score/BronzeCoin.png" },			//銅貨
	{ "data/TEXTURE/Item/Score/Diamond.png" },				//ダイアモンド
	{ "data/TEXTURE/Item/Score/Bear.png" },					//熊
	{ "data/TEXTURE/Item/Score/Letter.png" },				//手紙
	{ "data/TEXTURE/Item/Score/Apple.png" },				//リンゴ
	{ "data/TEXTURE/Item/Score/Melon.png" },				//メロン
	{ "data/TEXTURE/Item/Score/Banana.png" },				//バナナ
	{ "data/TEXTURE/Item/Score/Meat.png" },					//肉
	{ "data/TEXTURE/Item/Score/RiceBall.png" },				//おにぎり
	{ "data/TEXTURE/Item/Score/Candy.png" },				//飴
	{ "data/TEXTURE/Item/Score/Donut.png" },				//ドーナツ
	{ "data/TEXTURE/Item/Score/Lolipop.png" },				//ロリポップ
	{ "data/TEXTURE/Item/Score/Bread.png" },				//パン
	{ "data/TEXTURE/Item/Score/Chocolate.png" },			//チョコレート
	{ "data/TEXTURE/Item/Score/Ice.png" },					//アイス

	{ "data/TEXTURE/Item/Ammo/Bombup.png" },				//ボムアップ
	{ "data/TEXTURE/Item/Ammo/Bulletup.png" },				//残段数アップ

	{ "data/TEXTURE/Mesh/Grass.jpg" },						//草
	{ "data/TEXTURE/Mesh/Block.jpg" },						//ブロック
	{ "data/TEXTURE/Mesh/Water.jpg" },						//水
	{ "data/TEXTURE/UI/Player_UI/stock.png" },				//残機のUI
	{ "data/TEXTURE/UI/Player_UI/arms.png" },				//弾の残数のUI
	{ "data/TEXTURE/UI/Player_UI/bomb.png" },				//グレネードの残数のUI
	{ "data/TEXTURE/UI/Player_UI/infinity.png" },			//弾数無限のUI
	{ "data/TEXTURE/UI/Player_UI/frame.png" },				//枠のUI

	{ "data/TEXTURE/UI/Title_UI/title.png" },				//タイトルロゴ
	{ "data/TEXTURE/UI/Title_UI/start.png" },				//スタート
	{ "data/TEXTURE/UI/Title_UI/BulletHole1.png" },			//弾痕1
	{ "data/TEXTURE/UI/Title_UI/BulletHole2.png" },			//弾痕2
	{ "data/TEXTURE/UI/Title_UI/BulletHole3.png" },			//弾痕3
	{ "data/TEXTURE/UI/Title_UI/Player_1.png" },			//プレイヤー選択1
	{ "data/TEXTURE/UI/Title_UI/Player_2.png" },			//プレイヤー選択2
	{ "data/TEXTURE/UI/Title_UI/Arrow.png" },				//矢印

	{ "data/TEXTURE/UI/Tutorial_UI/Tutorial_Name.png" },	//チュートリアル名前ロゴ
	{ "data/TEXTURE/UI/Tutorial_UI/Tutorial_1.png" },		//チュートリアル開始
	{ "data/TEXTURE/UI/Tutorial_UI/Tutorial_2.png" },		//チュートリアル指示1
	{ "data/TEXTURE/UI/Tutorial_UI/Tutorial_3.png" },		//チュートリアル指示2
	{ "data/TEXTURE/UI/Tutorial_UI/Tutorial_4.png" },		//チュートリアル指示3
	{ "data/TEXTURE/UI/Tutorial_UI/Tutorial_5.png" },		//チュートリアル指示4
	{ "data/TEXTURE/UI/Tutorial_UI/Tutorial_6.png" },		//チュートリアル指示5
	{ "data/TEXTURE/UI/Tutorial_UI/Tutorial_7.png" },		//チュートリアル指示6
	{ "data/TEXTURE/UI/Tutorial_UI/Tutorial_8.png" },		//チュートリアル終了

	{ "data/TEXTURE/UI/Result_UI/Bg.png" },					//背景
	{ "data/TEXTURE/UI/Result_UI/RESULT_NAME.png" },		//リザルト名ロゴ
	{ "data/TEXTURE/UI/Result_UI/1P.png" },					//1P
	{ "data/TEXTURE/UI/Result_UI/2P.png" },					//2P
	{ "data/TEXTURE/UI/Result_UI/GOOD.png" },				//評価0
	{ "data/TEXTURE/UI/Result_UI/GREATE.png" },				//評価1
	{ "data/TEXTURE/UI/Result_UI/NOPRISONER.png" },			//評価2
	{ "data/TEXTURE/UI/Result_UI/MISSION1COMPRLETE.png" },	//ミッションクリア0
	{ "data/TEXTURE/UI/Result_UI/MISSION2COMPRLETE.png" },	//ミッションクリア1

	{ "data/TEXTURE/UI/Ranking_UI/RANKING_NAME.png" },		//ランキング
	{ "data/TEXTURE/UI/Ranking_UI/1st.png" },				//ランキング
	{ "data/TEXTURE/UI/Ranking_UI/2nd.png" },				//ランキング
	{ "data/TEXTURE/UI/Ranking_UI/3rd.png" },				//ランキング
	{ "data/TEXTURE/UI/Ranking_UI/4th.png" },				//ランキング
	{ "data/TEXTURE/UI/Ranking_UI/5th.png" },				//ランキング
	{ "data/TEXTURE/UI/Ranking_UI/6th.png" },				//ランキング
	{ "data/TEXTURE/UI/Ranking_UI/7th.png" },				//ランキング
	{ "data/TEXTURE/UI/Ranking_UI/Total.png" },				//ランキング
	{ "data/TEXTURE/UI/Ranking_UI/ThankYouForPlaying.png" },//ランキング

	{ "data/TEXTURE/BG/sky01.jpg" },						//空の背景	( 晴れ )
	{ "data/TEXTURE/BG/sky02.jpg" },						//空の背景	( 曇り )
	{ "data/TEXTURE/BG/sky06.jpg" },						//空の背景	( 暗雲 )

	{ "data/TEXTURE/UI/Game_UI/go.png" },					//Goサイン
	{ "data/TEXTURE/UI/Game_UI/Gameover.png" },				//ゲームオーバー

	{ "data/TEXTURE/UI/Game_UI/P1.png" },					//2人プレイ時1P頭上に表示
	{ "data/TEXTURE/UI/Game_UI/P2.png" },					//2人プレイ時2P頭上に表示

	{ "data/TEXTURE/UI/Pause_UI/black.jpg" },				//ポーズの背景
	{ "data/TEXTURE/UI/Pause_UI/exit.png" },				//再開
	{ "data/TEXTURE/UI/Pause_UI/reset.png" },				//タイトルに戻る
	{ "data/TEXTURE/UI/Pause_UI/GamePause.png" },			//ポーズ(文字)
	{ "data/TEXTURE/UI/Pause_UI/arrow.png" },				//矢印

	{ "data/TEXTURE/Collision/Frame.png" },					//当たり判定のフレーム
};

//テクスチャ名の設定
FILENAME_LIST CTexture::m_aSeparateTexFileNameList =
{
	{ "data/TEXTURE/TexNone.png"},								//白紙
	{ "data/TEXTURE/Effect/Explosion00.png" },					//爆発
	{ "data/TEXTURE/Effect/Explosion01.png" },					//爆発
	{ "data/TEXTURE/Effect/Explosion02.png" },					//爆発
	{ "data/TEXTURE/Effect/Explosion03.png" },					//爆発
	{ "data/TEXTURE/Effect/Impact00.png" },						//インパクト
	{ "data/TEXTURE/Effect/Impact01.png" },						//インパクト
	{ "data/TEXTURE/Effect/Impact02.png" },						//インパクト
	{ "data/TEXTURE/Effect/Impact03.png" },						//インパクト
	{ "data/TEXTURE/Effect/Impact04.png" },						//インパクト
	{ "data/TEXTURE/Effect/Impact05.png" },						//インパクト
	{ "data/TEXTURE/Effect/Fire00.png" },						//ファイア
	{ "data/TEXTURE/Effect/Fire01.png" },						//ファイア
	{ "data/TEXTURE/Effect/Fire02.png" },						//ファイア
	{ "data/TEXTURE/Effect/Fire03.png" },						//ファイア
	{ "data/TEXTURE/Effect/Fire04.png" },						//ファイア
	{ "data/TEXTURE/Effect/ShotFlash.png" },					//発砲時の光
	{ "data/TEXTURE/Effect/HitEffect.png" },					//着弾エフェクト
	{ "data/TEXTURE/Effect/Smoke.png" },						//煙
	{ "data/TEXTURE/Effect/ShotGun.png" },						//ショットガン
	{ "data/TEXTURE/Effect/Flashing.jpg" },						//フラッシュ
	{ "data/TEXTURE/Effect/Charge00.png" },						//チャージ
	{ "data/TEXTURE/Effect/Charge01.png" },						//チャージ

	{ "data/TEXTURE/Effect/Fireworks1.png" },					//花火1
	{ "data/TEXTURE/Effect/Fireworks3.png" },					//花火2
	{ "data/TEXTURE/Effect/Fireworks5.png" },					//花火3

	{ "data/TEXTURE/Effect/Explosion04.png" },					//爆発
	{ "data/TEXTURE/Effect/Explosion05.png" },					//爆発
	{ "data/TEXTURE/Effect/Explosion06.png" },					//爆発
	{ "data/TEXTURE/Effect/Explosion07.png" },					//爆発
	{ "data/TEXTURE/Effect/Explosion08.png" },					//爆発

	{ "data/TEXTURE/Effect/smokeRed.png" },						//赤い煙

	{ "data/TEXTURE/UI/Title_UI/Fracturing.png" },				//Fracturing
	{ "data/TEXTURE/Effect/Charge.png" },						//攻撃を撃つ前の溜め
	{ "data/TEXTURE/Effect/Charge02.png" },						//キャラクターの出現時
	{ "data/TEXTURE/Effect/Glitter.png" },						//きらきら

	{ "data/TEXTURE/Item/Score/Ani_Bear.png" },					//アニメーションするアイテム熊
	{ "data/TEXTURE/Item/Score/Ani_Coin.png" },					//アニメーションするアイテムコイン
	{ "data/TEXTURE/Item/Score/Ani_Doll.png" },					//アニメーションするアイテム人形
	{ "data/TEXTURE/Item/Score/Ani_Fish.png" },					//アニメーションするアイテム魚
	{ "data/TEXTURE/Item/Score/Ani_Letter.png" },				//アニメーションするアイテム手紙
	{ "data/TEXTURE/Item/Score/Ani_Medal.png" },				//アニメーションするアイテムメダル
	{ "data/TEXTURE/Item/Score/Ani_Medal2.png" },				//アニメーションするアイテムメダル2
	{ "data/TEXTURE/Item/Score/Ani_RoastChicken.png" },			//アニメーションするアイテムローストチキン
	{ "data/TEXTURE/Item/Score/Ani_Ruby.png" },					//アニメーションするアイテムルビー
	{ "data/TEXTURE/Item/Score/Ani_Sapphire.png" },				//アニメーションするアイテムサファイア
	{ "data/TEXTURE/Item/Score/Ani_Topaz.png" },				//アニメーションするアイテムトパーズ
	{ "data/TEXTURE/Item/Score/Ani_DanceMonkey.png" },			//アニメーションするアイテム踊るサル
	{ "data/TEXTURE/Item/Score/Ani_JumpMonkey.png" },			//アニメーションするアイテム飛ぶサル
	{ "data/TEXTURE/Item/Ammo/Anim_Prisoner.png" },				//アニメーションするアイテム捕虜

	{ "data/TEXTURE/Effect/LightBulb.png" },					//電球
	{ "data/TEXTURE/Effect/Confetti.png" },						//紙吹雪

	{ "data/TEXTURE/Effect/Fireworks2.png" },					//花火4
	{ "data/TEXTURE/Effect/Fireworks4.png" },					//花火5
	{ "data/TEXTURE/Effect/Fireworks6.png" },					//花火6

	{ "data/TEXTURE/UI/num.png" },								//ナンバー
	{ "data/TEXTURE/UI/Player_UI/life.png" },					//体力のUI

};


//テクスチャ名の設定
std::vector<CTexture::SEPARATE_TEX_INFO> CTexture::m_apSeparateTexInfoList =
{
	//テクスチャのポインタ、テクスチャのパス、テクスチャのタイプ、テクスチャの分割数、テクスチャのUVサイズ
	//ポインタとUVサイズに関してはLoad関数で読み込み＆計算する
	{ nullptr, CTexture::SEPARATE_TEX_NONE,					D3DXVECTOR2(1,1),	ZeroVector2 },		//白紙

	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_EXPLOSION00,	D3DXVECTOR2(4,2),	ZeroVector2 },		//爆発
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_EXPLOSION01,	D3DXVECTOR2(5,3),	ZeroVector2 },		//爆発
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_EXPLOSION02,	D3DXVECTOR2(5,6),	ZeroVector2 },		//爆発
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_EXPLOSION03,	D3DXVECTOR2(7,1),	ZeroVector2 },		//爆発
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_IMPACT00,		D3DXVECTOR2(2,5),	ZeroVector2 },		//インパクト
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_IMPACT01,		D3DXVECTOR2(2,6),	ZeroVector2 },		//インパクト
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_IMPACT02,		D3DXVECTOR2(2,5),	ZeroVector2 },		//インパクト
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_IMPACT03,		D3DXVECTOR2(5,2),	ZeroVector2 },		//インパクト
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_IMPACT04,		D3DXVECTOR2(5,3),	ZeroVector2 },		//インパクト
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_IMPACT05,		D3DXVECTOR2(5,3),	ZeroVector2 },		//インパクト
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_FIRE00,		D3DXVECTOR2(5,4),	ZeroVector2 },		//ファイア
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_FIRE01,		D3DXVECTOR2(5,4),	ZeroVector2 },		//ファイア
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_FIRE02,		D3DXVECTOR2(8,1),	ZeroVector2 },		//ファイア
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_FIRE03,		D3DXVECTOR2(5,2),	ZeroVector2 },		//ファイア
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_FIRE04,		D3DXVECTOR2(8,1),	ZeroVector2 },		//ファイア
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_SHOTFLASH,		D3DXVECTOR2(5,2),	ZeroVector2 },		//発砲時の光
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_HITEFFECT,		D3DXVECTOR2(14,1),	ZeroVector2 },		//着弾エフェクト
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_SMOKE,			D3DXVECTOR2(10,1),	ZeroVector2 },		//煙
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_SHOTGUN,		D3DXVECTOR2(5,3),	ZeroVector2 },		//ショットガン
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_FLASH,			D3DXVECTOR2(5,1),	ZeroVector2 },		//フラッシュ
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_CHARGE00,		D3DXVECTOR2(5,2),	ZeroVector2 },		//チャージ
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_CHARGE01,		D3DXVECTOR2(5,2),	ZeroVector2 },		//チャージ

	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_FIREWORKS1,	D3DXVECTOR2(14,1),	ZeroVector2 },		//花火1
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_FIREWORKS2,	D3DXVECTOR2(14,1),	ZeroVector2 },		//花火2
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_FIREWORKS3,	D3DXVECTOR2(14,1),	ZeroVector2 },		//花火3

	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_EXPLOSION04,	D3DXVECTOR2(4,4),	ZeroVector2 },		//爆発
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_EXPLOSION05,	D3DXVECTOR2(5,3),	ZeroVector2 },		//爆発
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_EXPLOSION06,	D3DXVECTOR2(5,3),	ZeroVector2 },		//爆発
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_EXPLOSION07,	D3DXVECTOR2(5,3),	ZeroVector2 },		//爆発
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_EXPLOSION08,	D3DXVECTOR2(8,2),	ZeroVector2 },		//爆発
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_REDSMOKE,		D3DXVECTOR2(10,1),	ZeroVector2 },		//爆発

	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_FRACTURING,	D3DXVECTOR2(5,2),	ZeroVector2 },		//ガラスが砕け散る
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_CHARGE,		D3DXVECTOR2(7,1),	ZeroVector2 },		//溜め
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_CHARGE02,		D3DXVECTOR2(5,3),	ZeroVector2 },		//溜め
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_GLITTER,		D3DXVECTOR2(5,2),	ZeroVector2 },		//きらきら

	{ nullptr, CTexture::SEPARATE_TEX_ITEM_BEAR,			D3DXVECTOR2(5,1),	ZeroVector2 },		//アイテム 熊
	{ nullptr, CTexture::SEPARATE_TEX_ITEM_COIN,			D3DXVECTOR2(9,1),	ZeroVector2 },		//アイテム コイン
	{ nullptr, CTexture::SEPARATE_TEX_ITEM_DOLL,			D3DXVECTOR2(5,1),	ZeroVector2 },		//アイテム 人形
	{ nullptr, CTexture::SEPARATE_TEX_ITEM_FISH,			D3DXVECTOR2(6,1),	ZeroVector2 },		//アイテム 魚
	{ nullptr, CTexture::SEPARATE_TEX_ITEM_LETTER,			D3DXVECTOR2(11,1),	ZeroVector2 },		//アイテム 手紙
	{ nullptr, CTexture::SEPARATE_TEX_ITEM_MEDAL,			D3DXVECTOR2(7,1),	ZeroVector2 },		//アイテム メダル
	{ nullptr, CTexture::SEPARATE_TEX_ITEM_MEDAL2,			D3DXVECTOR2(6,1),	ZeroVector2 },		//アイテム メダル2
	{ nullptr, CTexture::SEPARATE_TEX_ITEM_ROASTCHICKEN,	D3DXVECTOR2(11,1),	ZeroVector2 },		//アイテム ローストチキン
	{ nullptr, CTexture::SEPARATE_TEX_ITEM_RUBY,			D3DXVECTOR2(21,1),	ZeroVector2 },		//アイテム ルビー
	{ nullptr, CTexture::SEPARATE_TEX_ITEM_SAPPHIRE,		D3DXVECTOR2(21,1),	ZeroVector2 },		//アイテム サファイア
	{ nullptr, CTexture::SEPARATE_TEX_ITEM_TOPAZ,			D3DXVECTOR2(21,1),	ZeroVector2 },		//アイテム トパーズ
	{ nullptr, CTexture::SEPARATE_TEX_ITEM_DANCEMONKEY,		D3DXVECTOR2(10,1),	ZeroVector2 },		//アイテム 踊るサル
	{ nullptr, CTexture::SEPARATE_TEX_ITEM_JUMPMONKEY,		D3DXVECTOR2(9,1),	ZeroVector2 },		//アイテム 飛ぶサル
	{ nullptr, CTexture::SEPARATE_TEX_ITEM_PRISONER,		D3DXVECTOR2(12,1),	ZeroVector2 },		//アイテム 捕虜

	{ nullptr, CTexture::SEPARATE_TEX_LIGHTBULB,			D3DXVECTOR2(5,2),	ZeroVector2 },		//電球
	{ nullptr, CTexture::SEPARATE_TEX_CONFETTI,				D3DXVECTOR2(1,12),	ZeroVector2 },		//紙吹雪

	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_FIREWORKS4,	D3DXVECTOR2(14,1),	ZeroVector2 },		//花火4
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_FIREWORKS5,	D3DXVECTOR2(14,1),	ZeroVector2 },		//花火5
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_FIREWORKS6,	D3DXVECTOR2(14,1),	ZeroVector2 },		//花火6


	{ nullptr, CTexture::SEPARATE_TEX_NUM,					D3DXVECTOR2(10,1),	ZeroVector2 },		//ナンバー
	{ nullptr, CTexture::SEPARATE_TEX_UI_LIFE,				D3DXVECTOR2(5,1),	ZeroVector2 },		//体力のUI
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
	for (size_t nCnt = 0; nCnt < m_apSeparateTexInfoList.size(); nCnt++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			m_aSeparateTexFileNameList[nCnt].data(),
			&m_apSeparateTexInfoList[nCnt].m_apSeparateTexture);

		//debug
		std::cout << "SeparateTex Load - " << nCnt << m_aSeparateTexFileNameList[nCnt].data() << NEWLINE;

		//nullcheck
		if (!m_apSeparateTexInfoList[nCnt].m_apSeparateTexture)
		{
			//debug
			std::cout << "LOADFAILED!!! SeparateTex - " << nCnt << m_aSeparateTexFileNameList[nCnt].data() << NEWLINE;

			//失敗
			MessageBox(hwnd, "テクスチャ読み込み失敗", m_aSeparateTexFileNameList[nCnt].data(), MB_OK | MB_ICONHAND);
		}

		//どちらかの値が0だった場合は計算しない
		//0除算防止
		if (m_apSeparateTexInfoList[nCnt].m_UVCnt.x * m_apSeparateTexInfoList[nCnt].m_UVCnt.y)
		{
			//UVサイズ計算
			m_apSeparateTexInfoList[nCnt].m_UVSize = D3DXVECTOR2(1.0f / m_apSeparateTexInfoList[nCnt].m_UVCnt.x, 1.0f / m_apSeparateTexInfoList[nCnt].m_UVCnt.y);
		}
		else
		{
			m_apSeparateTexInfoList[nCnt].m_UVSize = ZeroVector2;
			//警告文
			MessageBox(hwnd, "0除算をしようとしました　値を確認してください", m_aSeparateTexFileNameList[nCnt].data(), MB_OK | MB_ICONHAND);
		}
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
	for (size_t nCnt = 0; nCnt < m_apSeparateTexInfoList.size(); nCnt++)
	{
		//nullcheck
		if (m_apSeparateTexInfoList[nCnt].m_apSeparateTexture)
		{
			//テクスチャの開放
			m_apSeparateTexInfoList[nCnt].m_apSeparateTexture->Release();
			m_apSeparateTexInfoList[nCnt].m_apSeparateTexture = nullptr;
		}
	}

	//配列の開放
	m_apTextureList.clear();
	m_apSeparateTexInfoList.clear();
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
	if (textype < (int)m_apSeparateTexInfoList.size())
	{
		//nullcheck
		if (m_apSeparateTexInfoList[textype].m_apSeparateTexture)
		{
			return m_apSeparateTexInfoList[textype].m_apSeparateTexture;
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
	//配列外のモノを指定されていた場合はアクセス違反なるので注意
	if (textype < (int)m_apSeparateTexInfoList.size())
	{
		return m_apSeparateTexInfoList[textype].m_UVSize;
	}
	return ZeroVector2;
}

//-----------------------------------------------------------------------------
//テクスチャのUV枚数取得
//----------------------------------------------------------------------------
D3DXVECTOR2 CTexture::GetSparateTex_UVCnt(SEPARATE_TEX_TYPE textype)
{
	//配列より小さい値か
	//配列外のモノを指定されていた場合はアクセス違反なるので注意
	if (textype < (int)m_apSeparateTexInfoList.size())
	{
		return m_apSeparateTexInfoList[textype].m_UVCnt;
	}
	return ZeroVector2;
}
