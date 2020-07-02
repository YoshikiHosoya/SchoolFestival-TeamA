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

//�e�N�X�`�����̐ݒ�
std::vector<std::string> CTexture::m_aTexFileName =
{
	{ "data/TEXTURE/TexNone.png" },							//����
	{ "data/TEXTURE/Effect/particle.jpg" },					//�p�[�e�B�N���p�̊ۂ���
	{ "data/TEXTURE/Bullet/bullet00.png" },					//�n���h�K���̒e
	{ "data/TEXTURE/Item/Heavymachinegun.png" },			//�w�r�[�}�V���K���̒e
	{ "data/TEXTURE/Item/Shotgun.png" },					//�V���b�g�K���̒e
	{ "data/TEXTURE/Item/Lasergun.png" },					//���[�U�[�K���̒e
	{ "data/TEXTURE/Item/Rocketlauncher.png" },				//���P�b�g�����`���[�̒e
	{ "data/TEXTURE/Item/Flameshot.png" },					//�t���C���V���b�g�̒e
	{ "data/TEXTURE/Item/Bear.png" },						//�F
	{ "data/TEXTURE/Mesh/Grass.jpg" },						//��
	{ "data/TEXTURE/Mesh/Block.jpg" },						//�u���b�N
	{ "data/TEXTURE/Mesh/Water.jpg" },						//��
};


//�e�N�X�`�����̐ݒ�
std::vector<CTexture::SEPARATE_TEX_INFO> CTexture::m_apSeparateTexInfoList =
{
	//�e�N�X�`���̃|�C���^�A�e�N�X�`���̃p�X�A�e�N�X�`���̃^�C�v�A�e�N�X�`���̕������A�e�N�X�`����UV�T�C�Y
	//�|�C���^��UV�T�C�Y�Ɋւ��Ă�Load�֐��œǂݍ��݁��v�Z����
	{ nullptr, "data/TEXTURE/TexNone.png",					CTexture::SEPARATE_TEX_NONE,					D3DXVECTOR2(1,1),	ZeroVector2 },		//����
	{ nullptr, "data/TEXTURE/Effect/Explosion01.png",		CTexture::SEPARATE_TEX_EFFECT_EXPLOSION01,		D3DXVECTOR2(5,3),	ZeroVector2 },		//����
	{ nullptr, "data/TEXTURE/Effect/ShotFlash.png",			CTexture::SEPARATE_TEX_EFFECT_SHOTFLASH,		D3DXVECTOR2(5,2),	ZeroVector2 },		//���C���̌�
	{ nullptr, "data/TEXTURE/Effect/Spark.png",				CTexture::SEPARATE_TEX_EFFECT_SPARK,			D3DXVECTOR2(5,2),	ZeroVector2 },		//�d��
	{ nullptr, "data/TEXTURE/Effect/hit.png",				CTexture::SEPARATE_TEX_EFFECT_HITEFFECT,		D3DXVECTOR2(7,1),	ZeroVector2 },		//���e�G�t�F�N�g
	{ nullptr, "data/TEXTURE/Effect/Smoke.png",				CTexture::SEPARATE_TEX_EFFECT_SMOKE,			D3DXVECTOR2(10,1),	ZeroVector2 },		//��

};

//-----------------------------------------------------------------------------
//�e�N�X�`���ꊇ���[�h
//-----------------------------------------------------------------------------
void CTexture::TexLoad(HWND hwnd)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
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
	for (size_t nCnt = 0; nCnt < m_apSeparateTexInfoList.size(); nCnt++)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			m_apSeparateTexInfoList[nCnt].m_aSeparateTexFileName.data(),
			&m_apSeparateTexInfoList[nCnt].m_apSeparateTexture);

		//debug
		std::cout << "SeparateTex Load - " << nCnt << m_apSeparateTexInfoList[nCnt].m_aSeparateTexFileName.data() << NEWLINE;

		//nullcheck
		if (!m_apSeparateTexInfoList[nCnt].m_apSeparateTexture)
		{
			//debug
			std::cout << "LOADFAILED!!! SeparateTex - " << nCnt << m_apSeparateTexInfoList[nCnt].m_aSeparateTexFileName.data() << NEWLINE;

			//���s
			MessageBox(hwnd, "�e�N�X�`���ǂݍ��ݎ��s", m_apSeparateTexInfoList[nCnt].m_aSeparateTexFileName.data(), MB_OK | MB_ICONHAND);
		}

		//�ǂ��炩�̒l��0�������ꍇ�͌v�Z���Ȃ�
		//0���Z�h�~
		if (m_apSeparateTexInfoList[nCnt].m_UVCnt.x * m_apSeparateTexInfoList[nCnt].m_UVCnt.y)
		{
			//UV�T�C�Y�v�Z
			m_apSeparateTexInfoList[nCnt].m_UVSize = D3DXVECTOR2(1.0f / m_apSeparateTexInfoList[nCnt].m_UVCnt.x, 1.0f / m_apSeparateTexInfoList[nCnt].m_UVCnt.y);
		}
		else
		{
			m_apSeparateTexInfoList[nCnt].m_UVSize = ZeroVector2;
			//�x����
			MessageBox(hwnd, "0���Z�����悤�Ƃ��܂����@�l���m�F���Ă�������", m_apSeparateTexInfoList[nCnt].m_aSeparateTexFileName.data(), MB_OK | MB_ICONHAND);
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
	for (size_t nCnt = 0; nCnt < m_apSeparateTexInfoList.size(); nCnt++)
	{
		//nullcheck
		if (m_apSeparateTexInfoList[nCnt].m_apSeparateTexture)
		{
			//�e�N�X�`���̊J��
			m_apSeparateTexInfoList[nCnt].m_apSeparateTexture->Release();
			m_apSeparateTexInfoList[nCnt].m_apSeparateTexture = nullptr;
		}
	}

	//�z��̊J��
	m_apTextureList.clear();
	m_apSeparateTexInfoList.clear();
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
//�e�N�X�`����UV�T�C�Y�擾
//----------------------------------------------------------------------------
D3DXVECTOR2 CTexture::GetSparateTex_UVSize(SEPARATE_TEX_TYPE textype)
{
	//�z���菬�����l��
	//�z��O�̃��m���w�肳��Ă����ꍇ�̓A�N�Z�X�ᔽ�Ȃ�̂Œ���
	if (textype < (int)m_apSeparateTexInfoList.size())
	{
		return m_apSeparateTexInfoList[textype].m_UVSize;
	}
	return ZeroVector2;
}

//-----------------------------------------------------------------------------
//�e�N�X�`����UV�����擾
//----------------------------------------------------------------------------
D3DXVECTOR2 CTexture::GetSparateTex_UVCnt(SEPARATE_TEX_TYPE textype)
{
	//�z���菬�����l��
	//�z��O�̃��m���w�肳��Ă����ꍇ�̓A�N�Z�X�ᔽ�Ȃ�̂Œ���
	if (textype < (int)m_apSeparateTexInfoList.size())
	{
		return m_apSeparateTexInfoList[textype].m_UVCnt;
	}
	return ZeroVector2;
}
