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
	{ "data/TEXTURE/Item/Heavymachinegun.png" },			//ヘビーマシンガンの弾
	{ "data/TEXTURE/Item/Shotgun.png" },					//ショットガンの弾
	{ "data/TEXTURE/Item/Lasergun.png" },					//レーザーガンの弾
	{ "data/TEXTURE/Item/Rocketlauncher.png" },				//ロケットランチャーの弾
	{ "data/TEXTURE/Item/Flameshot.png" },					//フレイムショットの弾
	{ "data/TEXTURE/Item/Bear.png" },						//熊
	{ "data/TEXTURE/Item/Bombup.png" },						//ボムアップ
	{ "data/TEXTURE/Item/Energyup.png" },					//乗り物の耐久値アップ
	{ "data/TEXTURE/Item/Bulletup.png" },					//残段数アップ
	{ "data/TEXTURE/Mesh/Grass.jpg" },						//草
	{ "data/TEXTURE/Mesh/Block.jpg" },						//ブロック
	{ "data/TEXTURE/Mesh/Water.jpg" },						//水
	{ "data/TEXTURE/UI/remain.png" },						//残機のUI
	{ "data/TEXTURE/UI/arms.png" },							//弾の残数のUI
	{ "data/TEXTURE/UI/bomb.png" },							//グレネードの残数のUI
	{ "data/TEXTURE/UI/infinity.png" },						//弾数無限のUI
	{ "data/TEXTURE/UI/frame.png" },						//枠のUI
	{ "data/TEXTURE/UI/title.png" },						//タイトルロゴ
	{ "data/TEXTURE/UI/start.png" },						//スタート
	{ "data/TEXTURE/UI/result.png" },						//リザルト
	{ "data/TEXTURE/UI/ranking.png" },						//ランキング
};

//テクスチャ名の設定
FILENAME_LIST CTexture::m_aSeparateTexFileNameList =
{
	{ "data/TEXTURE/TexNone.png"},								//白紙
	{ "data/TEXTURE/Effect/Explosion01.png" },					//爆発
	{ "data/TEXTURE/Effect/ShotFlash.png" },					//発砲時の光
	{ "data/TEXTURE/Effect/Spark.png" },						//電撃
	{ "data/TEXTURE/Effect/HitEffect.png" },					//着弾エフェクト
	{ "data/TEXTURE/Effect/Smoke.png" },						//煙
	{ "data/TEXTURE/Effect/ShotGun.png" },						//ショットガン
	{ "data/TEXTURE/Effect/Impact00.png" },						//インパクト
	{ "data/TEXTURE/Effect/Impact01.png" },						//インパクト
	{ "data/TEXTURE/Effect/Fire.png" },							//ファイア
	{ "data/TEXTURE/UI/num.png" },								//ナンバー
	{ "data/TEXTURE/UI/life.png" },								//体力のUI
};


//テクスチャ名の設定
std::vector<CTexture::SEPARATE_TEX_INFO> CTexture::m_apSeparateTexInfoList =
{
	//テクスチャのポインタ、テクスチャのパス、テクスチャのタイプ、テクスチャの分割数、テクスチャのUVサイズ
	//ポインタとUVサイズに関してはLoad関数で読み込み＆計算する
	{ nullptr, CTexture::SEPARATE_TEX_NONE,					D3DXVECTOR2(1,1),	ZeroVector2 },		//白紙
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_EXPLOSION01,	D3DXVECTOR2(5,3),	ZeroVector2 },		//爆発
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_SHOTFLASH,		D3DXVECTOR2(5,2),	ZeroVector2 },		//発砲時の光
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_SPARK,			D3DXVECTOR2(5,2),	ZeroVector2 },		//電撃
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_HITEFFECT,		D3DXVECTOR2(14,1),	ZeroVector2 },		//着弾エフェクト
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_SMOKE,			D3DXVECTOR2(10,1),	ZeroVector2 },		//煙
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_SHOTGUN,		D3DXVECTOR2(5,3),	ZeroVector2 },		//ショットガン
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_IMPACT00,		D3DXVECTOR2(2,5),	ZeroVector2 },		//インパクト
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_IMPACT01,		D3DXVECTOR2(2,6),	ZeroVector2 },		//インパクト
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_FIRE,			D3DXVECTOR2(8,1),	ZeroVector2 },		//ファイア
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
