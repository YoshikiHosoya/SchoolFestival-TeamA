//------------------------------------------------------------------------------
//
//���̗�����  [backthunder.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "backthunder.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "effectanimation2D.h"
#include "effectanimation3D.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define RANDOM_INTERVAL (rand() % 300 + 50)		//���̐U���Ă���C���^�[�o��
//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CBackThunder::CBackThunder()
{
	//������
	m_nCnt = 0;
	m_nNextThunder = RANDOM_INTERVAL;
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CBackThunder::~CBackThunder()
{
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CBackThunder::Init()
{
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CBackThunder::Uninit()
{
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CBackThunder::Update()
{
	//�J�E���^++
	m_nCnt++;

	//�K���ȃ^�C�~���O��
	if (m_nCnt % m_nNextThunder == 0)
	{
		//������
		D3DXVECTOR3 ThunderPos = ZeroVector3;

		//���[�h�ɉ����ė��̔����ꏊ�ݒ�
		switch (CManager::GetMode())
		{
			//�Q�[�������U���g��
		case CManager::MODE_GAME:
		case CManager::MODE_RESULT:
			ThunderPos = D3DXVECTOR3((float)(rand() % 1280), 300.0f, 0.0f);
			break;

			//�^�C�g����
		case CManager::MODE_TITLE:
			ThunderPos = D3DXVECTOR3(500.0f + (float)(rand() % 200), 700.0f, 0.0f);
			break;
		default:
			break;
		}

		//�t���b�V���Ɨ�����
		CEffectAnimation2D::Create(ThunderPos - D3DXVECTOR3(0.0f, 300.0f, 0.0f), D3DXVECTOR3(1000.0f, 1000.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_FLASH, 0.0f, 3, CScene::OBJTYPE_BACK);
		CEffectAnimation2D::Create(ThunderPos, D3DXVECTOR3(400.0f, 600.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_BACKTHUNDER, 0.0f, 3, CScene::OBJTYPE_BACK);

		//���̗����^�C�~���O�ݒ� �����_��
		m_nNextThunder = RANDOM_INTERVAL;
		m_nCnt = 0;

		//���Đ�
		CManager::GetSound()->Play(CSound::LABEL_SE_THUNDER);
	}

}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CBackThunder::Draw()
{
}
//------------------------------------------------------------------------------
//�f�o�b�O���\��
//------------------------------------------------------------------------------
void CBackThunder::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //_DEBUG
}
//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
void CBackThunder::Create()
{
	//�������m��
	std::unique_ptr<CBackThunder> pBackThunder(new CBackThunder);

	//nullcheck
	if (pBackThunder)
	{
		//������
		pBackThunder->Init();

		//Scene�̔z��ɒǉ�
		pBackThunder->SetObjType(CScene::OBJTYPE_BACK);
		pBackThunder->AddUniqueList(std::move(pBackThunder));
	}
}
