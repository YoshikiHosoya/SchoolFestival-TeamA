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
};


//テクスチャ名の設定
std::vector<std::string> CTexture::m_aSeparateTexFileName =
{
	{ "data/texture/DarkExplosion.png" },					//爆発
};

//-----------------------------------------------------------------------------
//テクスチャ一括ロード
//-----------------------------------------------------------------------------
void CTexture::TexLoad(HWND hwnd)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
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
		case SEPARATE_TEX_EFFECT_EXPLOSION:
			UVCnt = D3DXVECTOR2(2, 5);
			break;


			//UVサイズ設定
			UVSize = D3DXVECTOR2(1.0f / UVCnt.x, 1.0f / UVCnt.y);

			//リストに追加
			m_UVSizeList.emplace_back(UVSize);
			m_UVCntList.emplace_back(UVCnt);

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
