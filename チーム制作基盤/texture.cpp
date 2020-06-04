//-----------------------------------------------------------------------------
//
//�e�N�X�`���Ǘ�  [texture.cpp]
// Author : Yoshiki Hosoya
//
//-----------------------------------------------------------------------------
#include "texture.h"
#include "manager.h"
#include "renderer.h"
//-----------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//-----------------------------------------------------------------------------
std::vector<LPDIRECT3DTEXTURE9> CTexture::m_apTextureList = {};
std::vector<LPDIRECT3DTEXTURE9> CTexture::m_apSeparateTextureList = {};

std::vector<D3DXVECTOR2> CTexture::m_UVSizeList = {};
std::vector<D3DXVECTOR2> CTexture::m_UVCntList = {};

//�e�N�X�`�����̐ݒ�
std::vector<std::string> CTexture::m_aTexFileName =
{
	{ "data/TEXTURE/UI/other/TexNone.png" },					//����
	{ "data/TEXTURE/UI/other/PressButton.png" },				//�v���X�{�^��
};


//�e�N�X�`�����̐ݒ�
std::vector<std::string> CTexture::m_aSeparateTexFileName =
{
	{ "data/texture/DarkExplosion.png" },					//����
};

//-----------------------------------------------------------------------------
//�e�N�X�`���ꊇ���[�h
//-----------------------------------------------------------------------------
void CTexture::TexLoad(HWND hwnd)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	LPDIRECT3DTEXTURE9 pTexture;

	//�e�N�X�`�����̃��X�g�̃T�C�Y��
	for (size_t nCnt = 0; nCnt < m_aTexFileName.size(); nCnt++)
	{
		//null
		pTexture = nullptr;

		//�e�N�X�`���̓ǂݍ���
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

			//���s
			MessageBox(hwnd, "�e�N�X�`���ǂݍ��ݎ��s", m_aTexFileName[nCnt].data(), MB_OK | MB_ICONHAND);
		}

		//���X�g�ɒǉ�
		m_apTextureList.emplace_back(pTexture);
	}

	//�e�N�X�`�����̃��X�g�̃T�C�Y��
	for (size_t nCnt = 0; nCnt < m_aSeparateTexFileName.size(); nCnt++)
	{
		//null
		pTexture = nullptr;

		//�e�N�X�`���̓ǂݍ���
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

			//���s
			MessageBox(hwnd, "�e�N�X�`���ǂݍ��ݎ��s", m_aSeparateTexFileName[nCnt].data(), MB_OK | MB_ICONHAND);
		}

		//���X�g�ɒǉ�
		m_apSeparateTextureList.emplace_back(pTexture);

		//UV�̏��@������
		D3DXVECTOR2 UVCnt = ZeroVector2;
		D3DXVECTOR2 UVSize = ZeroVector2;

		//���ꂼ���UV�����ݒ�
		switch (nCnt)
		{
		case SEPARATE_TEX_EFFECT_EXPLOSION:
			UVCnt = D3DXVECTOR2(2, 5);
			break;


			//UV�T�C�Y�ݒ�
			UVSize = D3DXVECTOR2(1.0f / UVCnt.x, 1.0f / UVCnt.y);

			//���X�g�ɒǉ�
			m_UVSizeList.emplace_back(UVSize);
			m_UVCntList.emplace_back(UVCnt);

		}
	}
}

	//-----------------------------------------------------------------------------
//�e�N�X�`���ꊇ�j��
//----------------------------------------------------------------------------
void CTexture::TexUnload()
{
	//�T�C�Y��
	for (size_t nCnt = 0; nCnt < m_apTextureList.size(); nCnt++)
	{
		//nullcheck
		if (m_apTextureList[nCnt])
		{
			//�e�N�X�`���̊J��
			m_apTextureList[nCnt]->Release();
			m_apTextureList[nCnt] = nullptr;
		}
	}

	//�T�C�Y��
	for (size_t nCnt = 0; nCnt < m_apSeparateTextureList.size(); nCnt++)
	{
		//nullcheck
		if (m_apSeparateTextureList[nCnt])
		{
			//�e�N�X�`���̊J��
			m_apSeparateTextureList[nCnt]->Release();
			m_apSeparateTextureList[nCnt] = nullptr;
		}
	}

	//�z��̊J��
	m_apTextureList.clear();
	m_apSeparateTextureList.clear();
}

//-----------------------------------------------------------------------------
//�e�N�X�`���擾�@�ʏ�
//----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEX_TYPE textype)
{
	//�z���菬�����l��
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
//�e�N�X�`���擾�@��������Ă���
//----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::GetSeparateTexture(SEPARATE_TEX_TYPE textype)
{
	//�z���菬�����l��
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
//�e�N�X�`����UV�T�C�Y�擾
//----------------------------------------------------------------------------
D3DXVECTOR2 CTexture::GetSparateTex_UVSize(SEPARATE_TEX_TYPE textype)
{
	//�z���菬�����l��
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
//�e�N�X�`����UV�����擾
//----------------------------------------------------------------------------
D3DXVECTOR2 CTexture::GetSparateTex_UVCnt(SEPARATE_TEX_TYPE textype)
{
	//�z���菬�����l��
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
