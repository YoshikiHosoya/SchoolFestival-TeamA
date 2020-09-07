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
	{ "data/TEXTURE/Item/Coin.png" },						//�R�C��
	{ "data/TEXTURE/Item/Jewelry.png" },					//���
	{ "data/TEXTURE/Item/Medal.png" },						//���_��
	{ "data/TEXTURE/Item/Bombup.png" },						//�{���A�b�v
	{ "data/TEXTURE/Item/Energyup.png" },					//��蕨�̑ϋv�l�A�b�v
	{ "data/TEXTURE/Item/Bulletup.png" },					//�c�i���A�b�v
	{ "data/TEXTURE/Mesh/Grass.jpg" },						//��
	{ "data/TEXTURE/Mesh/Block.jpg" },						//�u���b�N
	{ "data/TEXTURE/Mesh/Water.jpg" },						//��
	{ "data/TEXTURE/UI/Player_UI/stock.png" },				//�c�@��UI
	{ "data/TEXTURE/UI/Player_UI/arms.png" },				//�e�̎c����UI
	{ "data/TEXTURE/UI/Player_UI/bomb.png" },				//�O���l�[�h�̎c����UI
	{ "data/TEXTURE/UI/Player_UI/infinity.png" },			//�e��������UI
	{ "data/TEXTURE/UI/Player_UI/frame.png" },				//�g��UI

	{ "data/TEXTURE/UI/Title_UI/title.png" },				//�^�C�g�����S
	{ "data/TEXTURE/UI/Title_UI/start.png" },				//�X�^�[�g
	{ "data/TEXTURE/UI/Title_UI/BulletHole1.png" },			//�e��1
	{ "data/TEXTURE/UI/Title_UI/BulletHole2.png" },			//�e��2
	{ "data/TEXTURE/UI/Title_UI/BulletHole3.png" },			//�e��3
	{ "data/TEXTURE/UI/Title_UI/Player_1.png" },			//�v���C���[�I��1
	{ "data/TEXTURE/UI/Title_UI/Player_2.png" },			//�v���C���[�I��2
	{ "data/TEXTURE/UI/Title_UI/Arrow.png" },				//���

	{ "data/TEXTURE/UI/Tutorial_UI/Tutorial_Name.png" },	//�`���[�g���A�����O���S
	{ "data/TEXTURE/UI/Tutorial_UI/Tutorial_1.png" },		//�`���[�g���A���J�n
	{ "data/TEXTURE/UI/Tutorial_UI/Tutorial_2.png" },		//�`���[�g���A���w��1
	{ "data/TEXTURE/UI/Tutorial_UI/Tutorial_3.png" },		//�`���[�g���A���w��2
	{ "data/TEXTURE/UI/Tutorial_UI/Tutorial_4.png" },		//�`���[�g���A���w��3
	{ "data/TEXTURE/UI/Tutorial_UI/Tutorial_5.png" },		//�`���[�g���A���w��4
	{ "data/TEXTURE/UI/Tutorial_UI/Tutorial_6.png" },		//�`���[�g���A���w��5
	{ "data/TEXTURE/UI/Tutorial_UI/Tutorial_7.png" },		//�`���[�g���A���w��6
	{ "data/TEXTURE/UI/Tutorial_UI/Tutorial_8.png" },		//�`���[�g���A���I��

	{ "data/TEXTURE/UI/Result_UI/Bg.png" },					//�w�i
	{ "data/TEXTURE/UI/Result_UI/RESULT_NAME.png" },		//���U���g�����S
	{ "data/TEXTURE/UI/Result_UI/1P.png" },					//1P
	{ "data/TEXTURE/UI/Result_UI/2P.png" },					//2P
	{ "data/TEXTURE/UI/Result_UI/GOOD.png" },				//�]��0
	{ "data/TEXTURE/UI/Result_UI/GREATE.png" },				//�]��1
	{ "data/TEXTURE/UI/Result_UI/NOPRISONER.png" },			//�]��2
	{ "data/TEXTURE/UI/Result_UI/MISSION1COMPRLETE.png" },	//�~�b�V�����N���A0
	{ "data/TEXTURE/UI/Result_UI/MISSION2COMPRLETE.png" },	//�~�b�V�����N���A1

	{ "data/TEXTURE/UI/Ranking_UI/RANKING_NAME.png" },		//�����L���O
	{ "data/TEXTURE/UI/Ranking_UI/1st.png" },				//�����L���O
	{ "data/TEXTURE/UI/Ranking_UI/2nd.png" },				//�����L���O
	{ "data/TEXTURE/UI/Ranking_UI/3rd.png" },				//�����L���O
	{ "data/TEXTURE/UI/Ranking_UI/4th.png" },				//�����L���O
	{ "data/TEXTURE/UI/Ranking_UI/5th.png" },				//�����L���O
	{ "data/TEXTURE/UI/Ranking_UI/6th.png" },				//�����L���O
	{ "data/TEXTURE/UI/Ranking_UI/7th.png" },				//�����L���O
	{ "data/TEXTURE/UI/Ranking_UI/Total.png" },				//�����L���O
	{ "data/TEXTURE/UI/Ranking_UI/ThankYouForPlaying.png" },//�����L���O

	{ "data/TEXTURE/BG/sky01.jpg" },						//��̔w�i	( ���� )
	{ "data/TEXTURE/BG/sky02.jpg" },						//��̔w�i	( �܂� )
	{ "data/TEXTURE/BG/sky06.jpg" },						//��̔w�i	( �É_ )

	{ "data/TEXTURE/UI/Game_UI/go.png" },					//Go�T�C��
	{ "data/TEXTURE/UI/Game_UI/Gameover.png" },				//�Q�[���I�[�o�[

	{ "data/TEXTURE/UI/Game_UI/P1.png" },				//�Q�[���I�[�o�[
	{ "data/TEXTURE/UI/Game_UI/P2.png" },				//�Q�[���I�[�o�[

};

//�e�N�X�`�����̐ݒ�
FILENAME_LIST CTexture::m_aSeparateTexFileNameList =
{
	{ "data/TEXTURE/TexNone.png"},								//����
	{ "data/TEXTURE/Effect/Explosion00.png" },					//����
	{ "data/TEXTURE/Effect/Explosion01.png" },					//����
	{ "data/TEXTURE/Effect/Explosion02.png" },					//����
	{ "data/TEXTURE/Effect/Explosion03.png" },					//����
	{ "data/TEXTURE/Effect/Impact00.png" },						//�C���p�N�g
	{ "data/TEXTURE/Effect/Impact01.png" },						//�C���p�N�g
	{ "data/TEXTURE/Effect/Impact02.png" },						//�C���p�N�g
	{ "data/TEXTURE/Effect/Impact03.png" },						//�C���p�N�g
	{ "data/TEXTURE/Effect/Impact04.png" },						//�C���p�N�g
	{ "data/TEXTURE/Effect/Impact05.png" },						//�C���p�N�g
	{ "data/TEXTURE/Effect/Fire00.png" },						//�t�@�C�A
	{ "data/TEXTURE/Effect/Fire01.png" },						//�t�@�C�A
	{ "data/TEXTURE/Effect/Fire02.png" },						//�t�@�C�A
	{ "data/TEXTURE/Effect/Fire03.png" },						//�t�@�C�A
	{ "data/TEXTURE/Effect/Fire04.png" },						//�t�@�C�A
	{ "data/TEXTURE/Effect/ShotFlash.png" },					//���C���̌�
	{ "data/TEXTURE/Effect/HitEffect.png" },					//���e�G�t�F�N�g
	{ "data/TEXTURE/Effect/Smoke.png" },						//��
	{ "data/TEXTURE/Effect/ShotGun.png" },						//�V���b�g�K��
	{ "data/TEXTURE/Effect/Flashing.jpg" },						//�t���b�V��
	{ "data/TEXTURE/Effect/Charge00.png" },						//�`���[�W
	{ "data/TEXTURE/Effect/Charge01.png" },						//�`���[�W

	{ "data/TEXTURE/UI/num.png" },								//�i���o�[
	{ "data/TEXTURE/UI/Player_UI/life.png" },					//�̗͂�UI
};


//�e�N�X�`�����̐ݒ�
std::vector<CTexture::SEPARATE_TEX_INFO> CTexture::m_apSeparateTexInfoList =
{
	//�e�N�X�`���̃|�C���^�A�e�N�X�`���̃p�X�A�e�N�X�`���̃^�C�v�A�e�N�X�`���̕������A�e�N�X�`����UV�T�C�Y
	//�|�C���^��UV�T�C�Y�Ɋւ��Ă�Load�֐��œǂݍ��݁��v�Z����
	{ nullptr, CTexture::SEPARATE_TEX_NONE,					D3DXVECTOR2(1,1),	ZeroVector2 },		//����

	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_EXPLOSION00,	D3DXVECTOR2(4,2),	ZeroVector2 },		//����
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_EXPLOSION01,	D3DXVECTOR2(5,3),	ZeroVector2 },		//����
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_EXPLOSION02,	D3DXVECTOR2(5,6),	ZeroVector2 },		//����
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_EXPLOSION03,	D3DXVECTOR2(7,1),	ZeroVector2 },		//����
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_IMPACT00,		D3DXVECTOR2(2,5),	ZeroVector2 },		//�C���p�N�g
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_IMPACT01,		D3DXVECTOR2(2,6),	ZeroVector2 },		//�C���p�N�g
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_IMPACT02,		D3DXVECTOR2(2,5),	ZeroVector2 },		//�C���p�N�g
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_IMPACT03,		D3DXVECTOR2(5,2),	ZeroVector2 },		//�C���p�N�g
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_IMPACT04,		D3DXVECTOR2(5,3),	ZeroVector2 },		//�C���p�N�g
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_IMPACT05,		D3DXVECTOR2(5,3),	ZeroVector2 },		//�C���p�N�g
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_FIRE00,		D3DXVECTOR2(5,4),	ZeroVector2 },		//�t�@�C�A
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_FIRE01,		D3DXVECTOR2(5,4),	ZeroVector2 },		//�t�@�C�A
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_FIRE02,		D3DXVECTOR2(8,1),	ZeroVector2 },		//�t�@�C�A
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_FIRE03,		D3DXVECTOR2(5,2),	ZeroVector2 },		//�t�@�C�A
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_FIRE04,		D3DXVECTOR2(8,1),	ZeroVector2 },		//�t�@�C�A
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_SHOTFLASH,		D3DXVECTOR2(5,2),	ZeroVector2 },		//���C���̌�
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_HITEFFECT,		D3DXVECTOR2(14,1),	ZeroVector2 },		//���e�G�t�F�N�g
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_SMOKE,			D3DXVECTOR2(10,1),	ZeroVector2 },		//��
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_SHOTGUN,		D3DXVECTOR2(5,3),	ZeroVector2 },		//�V���b�g�K��
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_FLASH,			D3DXVECTOR2(5,1),	ZeroVector2 },		//�t���b�V��
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_CHARGE00,		D3DXVECTOR2(5,2),	ZeroVector2 },		//�`���[�W
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_CHARGE01,		D3DXVECTOR2(5,2),	ZeroVector2 },		//�`���[�W

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
