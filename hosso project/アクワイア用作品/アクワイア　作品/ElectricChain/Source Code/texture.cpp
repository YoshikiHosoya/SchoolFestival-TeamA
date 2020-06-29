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

	{ "data/TEXTURE/UI/title/TitleLogo.png" },					//�^�C�g�����S
	{ "data/TEXTURE/UI/title/BG.jpg" },							//�^�C�g���w�i
	{ "data/TEXTURE/UI/game/Combo.png" },						//�R���{
	{ "data/TEXTURE/UI/game/KILL01.png" },						//�L��
	{ "data/TEXTURE/UI/game/PlayerIcon.png" },					//�v���C���[�A�C�R��
	{ "data/TEXTURE/UI/tutorial/X_ComboPattern.png" },			//�R���{�p�^�[��
	{ "data/TEXTURE/UI/tutorial/Key_ComboPattern.png" },		//�R���{�p�^�[��
	{ "data/TEXTURE/UI/game/Time.png" },						//�^�C��

	{ "data/TEXTURE/UI/result/ResultLogo.png" },				//���U���g���S
	{ "data/TEXTURE/UI/result/ResultCalc.png" },				//�X�R�A�v�Z

	{ "data/TEXTURE/UI/ranking/RankingLogo.png" },				//�����L���O���S
	{ "data/TEXTURE/UI/ranking/BG.jpg" },						//�����L���O�w�i
	{ "data/TEXTURE/UI/ranking/1ST.png" },						//1
	{ "data/TEXTURE/UI/ranking/2ND.png" },						//2
	{ "data/TEXTURE/UI/ranking/3RD.png" },						//3
	{ "data/TEXTURE/UI/ranking/4TH.png" },						//4
	{ "data/TEXTURE/UI/ranking/5TH.png" },						//5

	{ "data/TEXTURE/UI/tutorial/X_Skip.png" },					//�`���[�g���A�� XInput�@�X�L�b�v
	{ "data/TEXTURE/UI/tutorial/X_Move.png" },					//�`���[�g���A�� XInput�@�ړ�
	{ "data/TEXTURE/UI/tutorial/X_Dash.png" },					//�`���[�g���A�� XInput�@�_�b�V��
	{ "data/TEXTURE/UI/tutorial/X_CameraRoll.png" },			//�`���[�g���A�� XInput�@�J������]
	{ "data/TEXTURE/UI/tutorial/X_CameraReset.png" },			//�`���[�g���A�� XInput�@�n�_���Z�b�g
	{ "data/TEXTURE/UI/tutorial/X_Jump.png" },					//�`���[�g���A�� XInput�@�W�����v
	{ "data/TEXTURE/UI/tutorial/X_Attack.png" },				//�`���[�g���A�� XInput�@�U��
	{ "data/TEXTURE/UI/tutorial/X_StartChain.png" },			//�`���[�g���A�� XInput�@�A��
	{ "data/TEXTURE/UI/tutorial/X_ChainThunder.png" },			//�`���[�g���A�� XInput�@�A�������̐���

	{ "data/TEXTURE/UI/tutorial/Key_Skip.png" },				//�`���[�g���A�� Keyboard�@�X�L�b�v
	{ "data/TEXTURE/UI/tutorial/Key_Move.png" },				//�`���[�g���A�� Keyboard�@�ړ�
	{ "data/TEXTURE/UI/tutorial/Key_Dash.png" },				//�`���[�g���A�� Keyboard�@�_�b�V��
	{ "data/TEXTURE/UI/tutorial/Key_CameraRoll.png" },			//�`���[�g���A�� Keyboard�@�J������]
	{ "data/TEXTURE/UI/tutorial/Key_CameraReset.png" },			//�`���[�g���A�� Keyboard�@�n�_���Z�b�g
	{ "data/TEXTURE/UI/tutorial/Key_Jump.png" },				//�`���[�g���A�� Keyboard�@�W�����v
	{ "data/TEXTURE/UI/tutorial/Key_Attack.png" },				//�`���[�g���A�� Keyboard�@�U��
	{ "data/TEXTURE/UI/tutorial/Key_StartChain.png" },			//�`���[�g���A�� Keyboard�@�A��
	{ "data/TEXTURE/UI/tutorial/Key_ChainThunder.png" },		//�`���[�g���A�� Keyboard�@�A�������̐���

	{ "data/TEXTURE/UI/tutorial/Free.png" },					//�`���[�g���A���@���R
	{ "data/TEXTURE/UI/tutorial/End.png" },						//�`���[�g���A���@�I��
	{ "data/TEXTURE/UI/tutorial/OK.png" },						//�`���[�g���A���@OK

	{ "data/TEXTURE/UI/Pause/PauseLogo.png" },					//�|�[�Y���S
	{ "data/TEXTURE/UI/option/OptionLogo.png" },				//�I�v�V�������S

	{ "data/TEXTURE/UI/minimap/MiniMap.png" },					//�~�j�}�b�v
	{ "data/TEXTURE/UI/minimap/PlayerMapping.png" },			//�v���C���[
	{ "data/TEXTURE/UI/minimap/EnemyMapping.png" },				//�G
	{ "data/TEXTURE/UI/minimap/ExplosionMapping.png" },			//����

	{ "data/TEXTURE/UI/other/Start.png" },						//�I��
	{ "data/TEXTURE/UI/other/Finish.png" },						//�I��

	{ "data/TEXTURE/mesh/field000.jpg" },						//���b�V���t�B�[���h
	{ "data/TEXTURE/orbit/orbit03.jpg" },						//�O��
	{ "data/TEXTURE/effect/particle.jpg" },						//�p�[�e�B�N��
	{ "data/TEXTURE/effect/SphereExplosion.jpg" },				//�X�t�B�A�̗�
	{ "data/TEXTURE/effect/CircleThunder.jpeg" },				//�X�t�B�A�̗�

	{ "data/TEXTURE/effect/ExplosionShadow.jpg" },				// ������

	{ "data/TEXTURE/UI/backUI/pushB.png" },						// pushB
	{ "data/TEXTURE/UI/backUI/pushZ.png" },						// pushB
	{ "data/TEXTURE/UI/backUI/PlayerHit.jpg" },					// �v���C���[��e
	{ "data/TEXTURE/UI/backUI/Rain.jpg" },						// �J
};


//�e�N�X�`�����̐ݒ�
std::vector<std::string> CTexture::m_aSeparateTexFileName =
{
	{ "data/TEXTURE/UI/other/Number00.png" },					//����
	{ "data/TEXTURE/UI/pause/Menu.png" },						//�|�[�Y���j���[
	{ "data/TEXTURE/UI/option/ON_OFF.png" },					//ON_OFF
	{ "data/TEXTURE/UI/option/OptionMenu.png" },				//�I�v�V�������j���[

	{ "data/TEXTURE/effect/particle.jpg" },						//�p�[�e�B�N��
	{ "data/TEXTURE/effect/BackThunder.jpg" },					//�w�i�̗���
	{ "data/TEXTURE/effect/LineThunder.png" },					//�w�i�̗���
	{ "data/TEXTURE/effect/pushingB.png" },						//PushB
	{ "data/TEXTURE/effect/ChainElectric.png" },				//�A������
	{ "data/TEXTURE/effect/ChainThunderStart.png" },			//�A�������J�n
	{ "data/TEXTURE/effect/hit_spark.png" },					//�q�b�g�G�t�F�N�g�@�Ή�
	{ "data/TEXTURE/effect/hit_stan.png" },						//�q�b�g�G�t�F�N�g�@�X�^����
	{ "data/TEXTURE/effect/slash.png" },						//�q�b�g�G�t�F�N�g�@�a��
	{ "data/TEXTURE/effect/smoke.png" },						//��
	{ "data/TEXTURE/effect/SparkExplosion.png" },				//�d���̔������ۂ���
	{ "data/TEXTURE/effect/stan.png" },							//�X�^�����
	{ "data/TEXTURE/effect/TitleSpark.png" },					//�^�C�g���̍ŏ��̓d��
	{ "data/TEXTURE/effect/EnemyRespawn.jpg" },					//�G�o�����̃G�t�F�N�g
	{ "data/TEXTURE/effect/GameStart.jpg" },					//�Q�[���J�n

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

		//UV�T�C�Y�ݒ�
		UVSize = D3DXVECTOR2(1.0f / UVCnt.x, 1.0f / UVCnt.y);

		//���X�g�ɒǉ�
		m_UVSizeList.emplace_back(UVSize);
		m_UVCntList.emplace_back(UVCnt);

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
