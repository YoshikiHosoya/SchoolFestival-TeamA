// =====================================================================================================================================================================
//
// エフェクトの処理 [effect.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "effect.h"			// インクルードファイル
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "debugproc.h"
#include "player.h"
#include "fade.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
LPDIRECT3DTEXTURE9	CEffect::m_apTexture[EFFECTTYPE::EFFECTTYPE_MAX]	= {};				// 先頭は型名

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define TEXTURE_FILE01		"data/TEXTURE/aura.png"			// 読み込むテクスチャファイル名			( オーラ )
#define TEXTURE_FILE02		"data/TEXTURE/gayser.png"		// 読み込むテクスチャファイル名			( 間欠泉 )
#define TEXTURE_FILE03		"data/TEXTURE/effect.jpg"		// 読み込むテクスチャファイル名			( アイテム )

#define EFFECT_SIZEX		(200 / 2)						// 座標の幅
#define EFFECT_SIZEY		(200 / 2)						// 座標の高さ

#define GAYSER_SIZEX		(50 / 2)						// 間欠泉の幅
#define GAYSER_SIZEY		(100 / 2)						// 間欠泉の高さ

#define SUB_COL				(1.0f)							// 色の減少
#define SUB_RADIUS			(1.0f)							// 半径の減少

#define AURA_ANIM_SPD		(3)								// アニメーションの速さ			( オーラ )
#define GAYSER_ANIM_SPD		(2)								// アニメーションの速さ			( 間欠泉 )

#define MAX_SYZE_Y_GAYSER	(150.0f)						// 間欠泉の高さの最大

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CEffect::CEffect() :CScene3D(PRIORITY_EFFECT)
{
	// 変数初期化
	m_size					= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// サイズ
	m_move					= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動
	m_col					= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 色
	m_type					= EFFECTTYPE::EFFECTTYPE_NONE;			// エフェクトの種類
	m_nCntAnim				= 0;									// カウンターアニメーション
	m_nPatternAnim			= 0;									// パターンアニメーション
	m_fRadius				= 0.0f;									// 半径
	m_bDamage				= false;								// ダメージフラグ
	m_bAction				= false;								// アクションフラグ
	m_nCntFrame				= 0;									// フレームカウント
	m_bAdditiveSynthesis	= false;								// 加算合成するフラグ
	m_UVcut					= INTEGER2(0, 0);						// UVサイズ
	m_UVsize				= D3DXVECTOR2(0.0f, 0.0f);				// 分割数
	m_nAnimSpeed			= 0;									// アニメーションスピード
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CEffect::~CEffect()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
void CEffect::Init()
{
	// 初期化
	CScene3D::Init();
	
	// エフェクトの種類別設定
	switch (m_type)
	{
	case CEffect::EFFECTTYPE_AURA:
		m_size = D3DXVECTOR3(EFFECT_SIZEX, EFFECT_SIZEY, 0.0f);	// サイズの設定
		m_UVcut = INTEGER2(5, 2);								// アニメーションの分割数
		m_nAnimSpeed = AURA_ANIM_SPD;							// アニメーションのスピード
		break;

	case CEffect::EFFECTTYPE_GAYSER:
		m_size = D3DXVECTOR3(GAYSER_SIZEX, 0.0f, 20.0f);		// サイズの設定
		m_UVcut = INTEGER2(3, 1);								// アニメーションの分割数
		m_nAnimSpeed = GAYSER_ANIM_SPD;							// アニメーションのスピード
		break;

	case CEffect::EFFECTTYPE_ITEM:
		m_size = D3DXVECTOR3(17, 17, 17);// サイズの設定
		m_UVcut = INTEGER2(1, 1);								// アニメーションの分割数
		m_nAnimSpeed = 2;										// アニメーションのスピード
		m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);				// 色
		break;
	}

	//色の設定
	CScene3D::SetColor(m_col);

	// アニメーションの枚数
	m_UVsize = D3DXVECTOR2(1.0f / m_UVcut.x, 1.0f / m_UVcut.y);

	// サイズの設定
	SetSize(m_size);

	// アニメーション分割
	D3DXVECTOR2 UV;
	UV.x = m_nPatternAnim % m_UVcut.x * m_UVsize.x;
	UV.y = m_nPatternAnim / m_UVcut.x * m_UVsize.y;

	// アニメーションの設定
	CScene3D::SetAnim(m_UVsize, UV);
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CEffect::Uninit(void)
{
	CScene3D::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CEffect::Update(void)
{
	// 色の設定
	static D3DXCOLOR col = D3DXCOLOR(0.5f, 0.1f, 1.0f,1.0f);
	float *fcol = col;

	// 位置の取得
	D3DXVECTOR3 pos = CScene3D::GetPos();

	// カウントアップ
	m_nCntAnim++;
	m_nCntFrame++;

	// プレイヤーとの当たり判定
	if (CollisionEffect() == true)
	{
		CScene3D::SetColor(col);

		if (m_type == EFFECTTYPE_GAYSER)
		{
			// プレイヤーダメージ
			CManager::GetGame()->GetPlayer()->PlayerDamage(1);

			// プレイヤーを死亡状態に
			CPlayer::SetPlayerState(CPlayer::PLAYERSTATE_DEATH);
		}
	}
	else
	{
		// 色の設定
		CScene3D::SetColor(m_col);
	}

	// エフェクトの設定
	EffectConfig(m_type);

	// 速さ変更
	if (m_nCntAnim % m_nAnimSpeed == 0)
	{
		// パターンカウントアップ
		m_nPatternAnim++;

		// アニメーション分割
		D3DXVECTOR2 UV;
		UV.x = m_nPatternAnim % m_UVcut.x * m_UVsize.x;
		UV.y = m_nPatternAnim / m_UVcut.x * m_UVsize.y;

		// アニメーションの設定
		CScene3D::SetAnim(m_UVsize, UV);

		// 終了
		if (m_nPatternAnim >= (m_UVcut.x * m_UVcut.y))
		{
			m_nPatternAnim = 0;
			return;
		}
	}
	else
	{
		// 位置の設定
		CScene3D::SetPos(pos);

		// 間欠泉のとき
		if (m_type == EFFECTTYPE_GAYSER)
		{
			// サイズの設定
			CScene3D::SetScaling(m_size);
		}
		else
		{
			// 更新
			CScene3D::Update();
		}
	}
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CEffect::Draw(void)
{	
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();	// デバイスの取得

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);						// テストをパスする
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// 加算合成をするかどうか
	if (m_bAdditiveSynthesis)
	{
		// レンダーステート(加算合成処理)
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	// 描画
	CScene3D::Draw();

	// レンダーステート(通常ブレンド処理)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);								// Zテストを有効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);							// デフォルトに戻す
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

// =====================================================================================================================================================================
//
// エフェクトの生成
//
// =====================================================================================================================================================================
CEffect * CEffect::Create(D3DXVECTOR3 pos, EFFECTTYPE type)
{
	// 変数
	CEffect *pEffect;

	// メモリの確保
	pEffect = new CEffect();

	// エフェクトの種類の設定
	pEffect->m_type = type;

	// 初期化
	pEffect->Init();

	// エフェクトの位置の設定
	pEffect->SetPos(pos);

	// テクスチャの割り当て
	pEffect->BindTexture(m_apTexture[type]);

	// ビルボードの設定
	pEffect->SetBillboard(true);

	return pEffect;
}

// =====================================================================================================================================================================
//
// ロード
//
// =====================================================================================================================================================================
HRESULT CEffect::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

	// テクスチャファイル名
	char *sTextureFileName[EFFECTTYPE_MAX]
	{
		{ TEXTURE_FILE01 },		// EFFECTTYPE_AURA				( オーラ
		{ TEXTURE_FILE02 },		// EFFECTTYPE_GAYSER			( 間欠泉
		{ TEXTURE_FILE03 },		// EFFECTTYPE_GAYSER			( アイテム
	};

	for (int nCntEfect = 0; nCntEfect < EFFECTTYPE_MAX; nCntEfect++)
	{
		// テクスチャ読み込み
		D3DXCreateTextureFromFile(pDevice, sTextureFileName[nCntEfect], &m_apTexture[nCntEfect]);
	}

	return S_OK;
}

// =====================================================================================================================================================================
//  
// アンロード
//
// =====================================================================================================================================================================
void CEffect::Unload(void)
{
	for (int nCntTex = 0; nCntTex < EFFECTTYPE::EFFECTTYPE_MAX; nCntTex++)
	{
		// テクスチャの開放
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}

// =====================================================================================================================================================================
//  
// プレイヤーとの当たり判定
//
// =====================================================================================================================================================================
bool CEffect::CollisionEffect(void)
{
	bool bHit = false;		// ヒットフラグ

	CPlayer * pPlayer = CManager::GetGame()->GetPlayer();		// プレイヤーの取得

	if (pPlayer != NULL)
	{
		D3DXVECTOR3 posPlayer = pPlayer->GetPos();				// プレイヤーの位置取得
		D3DXVECTOR3 posOldPlayer = pPlayer->GetOldPos();		// プレイヤーの過去位置取得
		D3DXVECTOR3 sizePlayer = pPlayer->GetSize();			// プレイヤーのサイズ取得
		D3DXVECTOR3 posEffect = GetPos();						// エフェクトの位置

		// ブロックの範囲 ( 横 )
		if (posEffect.x - m_size.x < posPlayer.x + sizePlayer.x &&
			posEffect.x + m_size.x > posPlayer.x - sizePlayer.x)
		{
			// ブロックの範囲 ( 縦 )
			if (posEffect.z - m_size.z < posPlayer.z + sizePlayer.z &&
				posEffect.z + m_size.z > posPlayer.z - sizePlayer.z)
			{
				// ブロックの範囲 ( 高さ )
				if (posEffect.y - m_size.y <= posPlayer.y + sizePlayer.y &&
					posEffect.y + m_size.y > posPlayer.y)
				{
					bHit = true;
				}
			}
		}
	}
	return bHit;
}

// =====================================================================================================================================================================
//  
// エフェクトの設定
//
// =====================================================================================================================================================================
void CEffect::EffectConfig(EFFECTTYPE type)
{
	switch (type)
	{
	case CEffect::EFFECTTYPE_AURA:		// オーラ
		// 加算合成する
		m_bAdditiveSynthesis = true;
		break;

	case CEffect::EFFECTTYPE_GAYSER:	// 間欠泉
		// 加算合成する
		m_bAdditiveSynthesis = true;

		if (m_nCntFrame % 180 == 0)
		{
			// 起動させる
			if (m_bAction)
			{
				// 機能停止
				m_bAction = false;	
			}
			else
			{
				// 起動する
				m_bAction = true;
				// α値を戻す
				m_col.a = 1.0f;
			}
			m_nCntFrame = 0;
		}

		if (m_bAction)
		{
			// サイズを縦に伸ばす
			m_size.y += 2.0f;

			// 間欠泉の半径を最大に
			if (m_size.y >= MAX_SYZE_Y_GAYSER)
			{
				m_size.y = MAX_SYZE_Y_GAYSER;
			}
		}
		else
		{
			// α値減衰
			m_col.a -= 0.1f;

			if (m_col.a <= 0.0f)
			{
				// 出ていない状態に
				m_size.y = 0.0f;
			}
		}
		break;

	case CEffect::EFFECTTYPE_ITEM:		// アイテム
		// 加算合成する
		m_bAdditiveSynthesis = true;
		break;
	}
}
