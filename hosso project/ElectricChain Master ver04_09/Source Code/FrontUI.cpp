//------------------------------------------------------------------------------
//
//�O�ʂ�UI  [FrontUI.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "frontUI.h"
#include "manager.h"
#include "renderer.h"
#include "basemode.h"
#include "Pad_XInput.h"
#include "player.h"
#include "sound.h"
#include "enemy.h"
#include "effectanimation2D.h"
#include "camera.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
bool CFrontUI::m_bPushB = false;
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CFrontUI::CFrontUI()
{
	m_nCntUI = 0;
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CFrontUI::~CFrontUI()
{
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CFrontUI::Init()
{
	//����������
	if (FAILED(CScene2D::Init()))
	{
		return E_FAIL;
	}
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CFrontUI::Uninit()
{
	//�I������
	CScene2D::Uninit();
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CFrontUI::Update()
{
	//�J�E���^++
	m_nCntUI++;

	//�F������
	D3DXCOLOR col = WhiteColor;
	D3DXVECTOR2 UV = ZeroVector2;

	//�v���C���[�̃|�C���^�@������
	CPlayer *pPlayer = nullptr;

	switch (m_Type)
	{
	case CFrontUI::PUSH_B:
		//�_�ŏ���
		if (m_nCntUI % 2 == 0)
		{
			//�r���I�_���a
			SetDisp(GetDisp() ^= 1);
		}

		//�v���C���[�̃|�C���^�擾
		pPlayer = CManager::GetBaseMode()->GetPlayer();

		//nullcheck
		if (pPlayer)
		{
			//�����G�����X�|�[�����đ������Y������
			if (CEnemy::GetEnemyNum() != CEnemy::GetStanEnemyNum())
			{
				//����
				Release();
				m_bPushB = false;
			}
			//���������Ă邩
			if (pPlayer->GetChainThunder())
			{
				//�G�t�F�N�g����
				CEffectAnimation2D::Create(GetPos(), GetSize() * 2.0f, CTexture::SEPARATE_TEX_EFFECT_PUSHING_B, 0.0f, 2, CScene::OBJTYPE_FRONTUI);

				//���Đ�
				CManager::GetSound()->Play(CSound::LABEL_SE_SLASH_STAN);

				//�Q�[�����̂Ƃ�
				if (CManager::GetRenderer()->GetCamera()->GetCameraState() == CCamera::CAMERA_GAME)
				{
					//�J������A���������̏���
					CManager::GetRenderer()->GetCamera()->SetState(CCamera::CAMERA_CHAIN_EXPLOSION);
				}

				//����
				Release();
				m_bPushB = false;
			}
		}
		break;

		//�v���C���[��e
	case CFrontUI::PLAYER_HIT:

		//�F�擾
		col = GetCol();

		//�����ɂ���
		col.a -= 0.1f;

		//�����ɂȂ�����
		if (col.a <= 0.0f)
		{
			//����
			Release();
		}

		//�F�ݒ�
		SetVtxCol(col);
		break;

	case CFrontUI::RAIN:
		//UV�ړ� ���ɓ����Ă�悤�Ɍ�����
		UV = D3DXVECTOR2(-0.0015f * m_nCntUI,-0.05f * m_nCntUI);

		//UV�ݒ�
		SetAnimation(UV, D3DXVECTOR2(2.0f, 2.0f));
		break;

	case CFrontUI::GAMESTART:

		//�F�擾
		col = GetCol();

		//�����ɂ���
		col.a -= 0.04f;

		//�����ɂȂ�����
		if (col.a <= 0.0f)
		{
			//����
			Release();
		}

		//�F�ݒ�
		SetVtxCol(col);
		break;
	}

	//�X�V����
	CScene2D::Update();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CFrontUI::Draw()
{
	//��e�G�t�F�N�g�ƉJ�͉��Z��������
	if (m_Type == CFrontUI::PLAYER_HIT || m_Type == CFrontUI::RAIN)
	{
		//���Z����
		CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ALPHABLEND_ADD);

		//Z�e�X�g����
		CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_OFF);
	}

	//�`�揈��
	CScene2D::Draw();

	//Z�e�X�g�ʏ�
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);

	//�ʏ퍇��
	CManager::GetRenderer()->SetRendererCommand(CRenderer::REDNERER_ALPHABLEND_DEFAULT);

}
//------------------------------------------------------------------------------
//�f�o�b�O���\��
//------------------------------------------------------------------------------
void CFrontUI::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //_DEBUG
}

//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
void CFrontUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TEX_TYPE type)
{
	//�������m��
	std::unique_ptr<CFrontUI> pBackUI(new CFrontUI);

	//nullcheck
	if (pBackUI)
	{
		//������
		pBackUI->Init();

		//������
		pBackUI->m_Type = type;
		pBackUI->SetPos(pos);
		pBackUI->SetSize(size);
		pBackUI->SetVtxCol(col);

		//�^�C�v�ɂ���ăe�N�X�`�������ւ�
		switch (pBackUI->m_Type)
		{
		case CFrontUI::PUSH_B:
			//pushB����������Ă����ꍇ
			if (m_bPushB)
			{
				//�������J�����ďI��
				pBackUI.reset();
				return;
			}

			//�R���g���[�����ڑ�����Ă��邩�ǂ����Ńe�N�X�`�������ւ�
			CManager::GetXInput()->GetConnect() ?
				pBackUI->BindTexture(CTexture::GetTexture(CTexture::TEX_BACKUI_PUSH_B)) :
				pBackUI->BindTexture(CTexture::GetTexture(CTexture::TEX_BACKUI_PUSH_Z));

			//PushB
			m_bPushB = true;
			break;

			//��e
		case CFrontUI::PLAYER_HIT:
			pBackUI->BindTexture(CTexture::GetTexture(CTexture::TEX_BACKUI_DAMAGED));
			break;

			//�J
		case CFrontUI::RAIN:
			pBackUI->BindTexture(CTexture::GetTexture(CTexture::TEX_BACKUI_RAIN));
			pBackUI->SetVtxCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
			break;

			//�Q�[���X�^�[�g
		case CFrontUI::GAMESTART:
			pBackUI->BindTexture(CTexture::GetTexture(CTexture::TEX_GAMESTART));
			break;
		default:

			break;
		}
		//�I�u�W�F�^�C�v�ǉ�����Scene�ɒǉ�
		pBackUI->SetObjType(OBJTYPE_FRONTUI);
		pBackUI->AddUniqueList(std::move(pBackUI));
	}
}