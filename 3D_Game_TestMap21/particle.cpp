// =====================================================================================================================================================================
//
// パーティクルの処理 [particle.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "particle.h"			// インクルードファイル
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "debugproc.h"
#include "player.h"
#include "fade.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
LPDIRECT3DTEXTURE9	CParticle::m_apTexture[PARTICLETYPE::PARTICLE_MAX]	= {};				// 先頭は型名
INTEGER2			CParticle::m_UVcut									= INTEGER2(0, 0);
D3DXVECTOR2			CParticle::m_UVsize									= D3DXVECTOR2(0.0f, 0.0f);

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define TEXTURE_FILE01		"data/TEXTURE/ef_anim01.png"	// 読み込むテクスチャファイル名			( 光　青 )
#define TEXTURE_FILE02		"data/TEXTURE/ef_anim02.png"	// 読み込むテクスチャファイル名		( 光　緑 )

#define EFFECT_SIZEX		(20 / 2)						// 座標の幅
#define EFFECT_SIZEY		(20 / 2)						// 座標の高さ

#define ITEM_EFFECT_SIZEX	(10 / 2)						// 座標の幅
#define ITEM_EFFECT_SIZEY	(10 / 2)						// 座標の高さ

#define SUB_COL				(1.0f)							// 色の減少
#define SUB_RADIUS			(1.0f)							// 半径の減少

#define ANIM_SPD			(5)								// アニメーションの速さ

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CParticle::CParticle() :CScene3D(PRIORITY_EFFECT)
{
	// 変数初期化
	m_size	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// サイズ
	m_move	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 移動
	m_col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// 色
	m_type	= PARTICLETYPE::PARTICLE_NONE;				// パーティクルの種類
	m_nCntAnim		= 0;								// カウンターアニメーション
	m_nPatternAnim	= 0;								// パターンアニメーション

	m_nSpeed	= 0;								// 速さ
	m_fRot		= 0.0f;								// 回転
	m_fAngle	= 0.0f;								// 角度
	m_fLength	= 0;								// 長さ
	m_fRadius	= 0;								// 半径

}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CParticle::~CParticle()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
void CParticle::Init()
{
	// 初期化
	CScene3D::Init();
	
	//色の設定
	CScene3D::SetColor(m_col);

	// パーティクルの種類別設定
	switch (m_type)
	{
	case CParticle::PARTICLE_RED:
		m_size = D3DXVECTOR3(EFFECT_SIZEX, EFFECT_SIZEY, 0.0f);	// サイズの設定
		m_UVcut = INTEGER2(8, 1);								// アニメーションの分割数
		break;

	case CParticle::PARTICLE_BLUE:
		m_size = D3DXVECTOR3(ITEM_EFFECT_SIZEX, ITEM_EFFECT_SIZEY, 0.0f);	// サイズの設定
		m_UVcut = INTEGER2(8, 1);								// アニメーションの分割数

		break;
	}

	// アニメーションの枚数
	m_UVsize = D3DXVECTOR2(1.0f / m_UVcut.x, 1.0f / m_UVcut.y);

	// テクスチャの割り当て
	BindTexture(m_apTexture[m_type]);

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
void CParticle::Uninit(void)
{
	CScene3D::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CParticle::Update(void)
{
	// 色の設定
	static D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
	float *fcol = col;

	// 位置の取得
	D3DXVECTOR3 pos = CScene3D::GetPos();

	// カウントアップ
	m_nCntAnim++;
	m_fRadius += 1.0f;

	// 位置更新
	pos += m_move;

	//// プレイヤーとの当たり判定
	//if (CollisionPlayer() == true)
	//{
	//}

	// 速さ変更
	if (m_nCntAnim % ANIM_SPD == 0)
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
			Release();
			return;
		}

	}
	else
	{
		// 位置の設定
		CScene3D::SetPos(pos);

		// 更新
		CScene3D::Update();

		//// 半径の設定
		//CScene3D::SetRadius(m_fRadius);

	}
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CParticle::Draw(void)
{	
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();	// デバイスの取得

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);						// テストをパスする
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// レンダーステート(加算合成処理)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

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
// パーティクルの生成
//
// =====================================================================================================================================================================
CParticle * CParticle::Create(D3DXVECTOR3 pos, PARTICLETYPE type)
{
	// 変数
	CParticle *pParticle;

	// メモリの確保
	pParticle = new CParticle();

	// パーティクルの種類の設定
	pParticle->m_type = type;

	// 初期化
	pParticle->Init();

	// 種類別
	if (pParticle->m_type != CParticle::PARTICLE_RED)
	{
		// 小さい円のパーティクル
		pParticle->ParticleCircleShort();
	}
	else
	{
		// 円のパーティクル
		pParticle->ParticleCircle();
	}

	// パーティクルの位置の設定
	pParticle->SetPos(pos);

	// テクスチャの割り当て
	pParticle->BindTexture(m_apTexture[type]);

	// ビルボードの設定
	pParticle->SetBillboard(true);

	return pParticle;
}

// =====================================================================================================================================================================
//
// ロード
//
// =====================================================================================================================================================================
HRESULT CParticle::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

	// テクスチャファイル名
	char *sTextureFileName[PARTICLE_MAX]
	{
		{ TEXTURE_FILE01 },		// PARTICLE_AURA				( オーラ
		{ TEXTURE_FILE02 },		// PARTICLE_GAYSER			( 間欠泉
	};

	for (int nCntParticle = 0; nCntParticle < PARTICLE_MAX; nCntParticle++)
	{
		// テクスチャ読み込み
		D3DXCreateTextureFromFile(pDevice, sTextureFileName[nCntParticle], &m_apTexture[nCntParticle]);
	}

	return S_OK;
}

// =====================================================================================================================================================================
//  
// アンロード
//
// =====================================================================================================================================================================
void CParticle::Unload(void)
{
	for (int nCntTex = 0; nCntTex < PARTICLETYPE::PARTICLE_MAX; nCntTex++)
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
bool CParticle::CollisionPlayer(void)
{
	CPlayer * pPlayer		= CManager::GetGame()->GetPlayer();		// プレイヤーの取得
	D3DXVECTOR3 posPlayer	= pPlayer->GetPos();					// プレイヤーの位置取得
	D3DXVECTOR3 posParticle	= GetPos();								// パーティクルの位置

	float x = posParticle.x - posPlayer.x;
	float y = posParticle.y - posPlayer.y;
	float z = posParticle.z - posPlayer.z;
	float fDistancec = (float)sqrt(x * x + y * y + z * z);

	// 範囲内に入ったとき
	if (fDistancec <= 20.0f + EFFECT_SIZEX)
	{
		Release();
		return true;
	}
	return false;
}

// =====================================================================================================================================================================
//
// 円のパーティクル
//
// =====================================================================================================================================================================
void CParticle::ParticleCircle(void)
{
	// ランダム(円)
	m_fRot = rand() % 314 * 0.01f - rand() % 314 * 0.01f;
	m_nSpeed = rand() % 7 - 4;

	m_move.x += sinf(D3DX_PI * m_fRot) * m_nSpeed;
	m_move.y += cosf(D3DX_PI * m_fRot) * m_nSpeed;
	m_move.z += (m_move.x - m_move.y) / 2;
}

// =====================================================================================================================================================================
//
// 小さい円のパーティクル
//
// =====================================================================================================================================================================
void CParticle::ParticleCircleShort(void)
{
	// ランダム(円)
	m_fRot = rand() % 314 * 0.01f - rand() % 314 * 0.01f;
	m_nSpeed = rand() % 4 - 1;

	m_move.x += sinf(D3DX_PI * m_fRot) * m_nSpeed;
	m_move.y += cosf(D3DX_PI * m_fRot) * m_nSpeed;
	m_move.z += (m_move.x - m_move.y) / 2;
}