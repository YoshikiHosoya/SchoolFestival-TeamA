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
FILENAME_LIST CTexture::m_aTexFileName =
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
	{ "data/TEXTURE/Item/Bombup.png" },						//�{���A�b�v
	{ "data/TEXTURE/Item/Energyup.png" },					//��蕨�̑ϋv�l�A�b�v
	{ "data/TEXTURE/Item/Bulletup.png" },					//�c�i���A�b�v
	{ "data/TEXTURE/Mesh/Grass.jpg" },						//��
	{ "data/TEXTURE/Mesh/Block.jpg" },						//�u���b�N
	{ "data/TEXTURE/Mesh/Water.jpg" },						//��
	{ "data/TEXTURE/UI/remain.png" },						//�c�@��UI
	{ "data/TEXTURE/UI/arms.png" },							//�e�̎c����UI
	{ "data/TEXTURE/UI/bomb.png" },							//�O���l�[�h�̎c����UI
	{ "data/TEXTURE/UI/infinity.png" },						//�e��������UI
	{ "data/TEXTURE/UI/frame.png" },						//�g��UI
	{ "data/TEXTURE/UI/title.png" },						//�^�C�g�����S
	{ "data/TEXTURE/UI/start.png" },						//�X�^�[�g
	{ "data/TEXTURE/UI/result.png" },						//���U���g
	{ "data/TEXTURE/UI/ranking.png" },						//�����L���O
};

//�e�N�X�`�����̐ݒ�
FILENAME_LIST CTexture::m_aSeparateTexFileNameList =
{
	{ "data/TEXTURE/TexNone.png"},								//����
	{ "data/TEXTURE/Effect/Explosion01.png" },					//����
	{ "data/TEXTURE/Effect/ShotFlash.png" },					//���C���̌�
	{ "data/TEXTURE/Effect/Spark.png" },						//�d��
	{ "data/TEXTURE/Effect/HitEffect.png" },					//���e�G�t�F�N�g
	{ "data/TEXTURE/Effect/Smoke.png" },						//��
	{ "data/TEXTURE/Effect/ShotGun.png" },						//�V���b�g�K��
	{ "data/TEXTURE/Effect/Impact00.png" },						//�C���p�N�g
	{ "data/TEXTURE/Effect/Impact01.png" },						//�C���p�N�g
	{ "data/TEXTURE/Effect/Fire.png" },							//�t�@�C�A
	{ "data/TEXTURE/UI/num.png" },								//�i���o�[
	{ "data/TEXTURE/UI/life.png" },								//�̗͂�UI
};


//�e�N�X�`�����̐ݒ�
std::vector<CTexture::SEPARATE_TEX_INFO> CTexture::m_apSeparateTexInfoList =
{
	//�e�N�X�`���̃|�C���^�A�e�N�X�`���̃p�X�A�e�N�X�`���̃^�C�v�A�e�N�X�`���̕������A�e�N�X�`����UV�T�C�Y
	//�|�C���^��UV�T�C�Y�Ɋւ��Ă�Load�֐��œǂݍ��݁��v�Z����
	{ nullptr, CTexture::SEPARATE_TEX_NONE,					D3DXVECTOR2(1,1),	ZeroVector2 },		//����
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_EXPLOSION01,	D3DXVECTOR2(5,3),	ZeroVector2 },		//����
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_SHOTFLASH,		D3DXVECTOR2(5,2),	ZeroVector2 },		//���C���̌�
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_SPARK,			D3DXVECTOR2(5,2),	ZeroVector2 },		//�d��
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_HITEFFECT,		D3DXVECTOR2(14,1),	ZeroVector2 },		//���e�G�t�F�N�g
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_SMOKE,			D3DXVECTOR2(10,1),	ZeroVector2 },		//��
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_SHOTGUN,		D3DXVECTOR2(5,3),	ZeroVector2 },		//�V���b�g�K��
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_IMPACT00,		D3DXVECTOR2(2,5),	ZeroVector2 },		//�C���p�N�g
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_IMPACT01,		D3DXVECTOR2(2,6),	ZeroVector2 },		//�C���p�N�g
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_FIRE,			D3DXVECTOR2(8,1),	ZeroVector2 },		//�t�@�C�A
	{ nullptr, CTexture::SEPARATE_TEX_NUM,					D3DXVECTOR2(10,1),	ZeroVector2 },		//�i���o�[
	{ nullptr, CTexture::SEPARATE_TEX_UI_LIFE,				D3DXVECTOR2(5,1),	ZeroVector2 },		//�̗͂�UI

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
			m_aSeparateTexFileNameList[nCnt].data(),
			&m_apSeparateTexInfoList[nCnt].m_apSeparateTexture);

		//debug
		std::cout << "SeparateTex Load - " << nCnt << m_aSeparateTexFileNameList[nCnt].data() << NEWLINE;

		//nullcheck
		if (!m_apSeparateTexInfoList[nCnt].m_apSeparateTexture)
		{
			//debug
			std::cout << "LOADFAILED!!! SeparateTex - " << nCnt << m_aSeparateTexFileNameList[nCnt].data() << NEWLINE;

			//���s
			MessageBox(hwnd, "�e�N�X�`���ǂݍ��ݎ��s", m_aSeparateTexFileNameList[nCnt].data(), MB_OK | MB_ICONHAND);
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
			MessageBox(hwnd, "0���Z�����悤�Ƃ��܂����@�l���m�F���Ă�������", m_aSeparateTexFileNameList[nCnt].data(), MB_OK | MB_ICONHAND);
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
