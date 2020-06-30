//------------------------------------------------------------------------------
//
//�f�o�b�O�@�G�t�F�N�g�r���[���p�̏���  [Debug_EffectViewer.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "Debug_EffectViewer.h"
#include "../Scene.h"
#include "../manager.h"
#include "../renderer.h"
#include "../inputKeyboard.h"
#include "../camera.h"
#include "../fade.h"
#include "../particle.h"
#include "../ParticleManager.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define DEFAULT_PLAYER_POS (ZeroVector3)
#define DEFAULT_SCORE_POS (D3DXVECTOR3(1150.0f, 50.0f, 0.0f))

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CDebug_EffectViewer::CDebug_EffectViewer()
{
	m_bLoop = false;
	m_nLoopInterval = 60;
	m_nCnt = 0;
	m_pParticleParam.reset();
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CDebug_EffectViewer::~CDebug_EffectViewer()
{

}

//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CDebug_EffectViewer::Init()
{
	////�J�������W�ݒ�
	//CManager::GetRenderer()->getca()->SetCameraPos(DEFAULT_PLAYER_POS, DEFAULT_PLAYER_POS + D3DXVECTOR3(0.0f, 300.0f, -500.0f));
	//CManager::GetRenderer()->GetCamera()->SetState(CCamera::CAMERA_DEBUG);
	//CManager::GetRenderer()->GetCamera()->SetCameraRot(D3DXVECTOR3( 0.4f, 0.0f, 0.0f));

	//CMeshField::Create(ZeroVector3, D3DXVECTOR3(100.0f, 0.0f, 100.0f), INTEGER2(5, 5));

	CParticleManager::Create();

	//�p�[�e�B�N���̃p�����[�^�̃������m��
	m_pParticleParam.reset(new CParticleParam);

	return S_OK;
}

//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CDebug_EffectViewer::Uninit()
{

	//�I������
	//CScene::ReleaseAll();
}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CDebug_EffectViewer::Update()
{

}

//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CDebug_EffectViewer::Draw()
{

}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CDebug_EffectViewer::ShowDebugInfo()
{
#ifdef _DEBUG

	//CParticleParam::PARTICLE_TYPE type = ;

	if (!CScene::GetStopFlag())
	{
		//�J�E���^++
		m_nCnt++;
	}

	//�L�[�{�[�h�̃|�C���^�擾
	CKeyboard *pKeyboard = CManager::GetInputKeyboard();

	//Debug
	CDebugProc::Print("[Enter] �p�[�e�B�N������\n");
	CDebugProc::Print("[Ctrl] + [Enter] Loop %d \n",m_bLoop);

	ImGui::PushItemWidth(120);

	//�p�����[�^�ݒ�
	ImGui::DragInt("Life", &m_pParticleParam->GetLife(), 1, 1, 300);
	ImGui::DragFloat("Radius", &m_pParticleParam->GetRadius(), 0.5f, 1.0f, 250.0f);
	ImGui::DragFloat("Speed", &m_pParticleParam->GetSpeed(), 0.5f, 1.0f, 250.0f);
	ImGui::DragInt("ParticleNum", &m_pParticleParam->GetNumber(), 1, 0, 300);
	ImGui::DragFloat("RadiusDamping", &m_pParticleParam->GetRadiusDamping(), 0.001f, 0.5f, 1.0f);
	ImGui::DragFloat("AlphaDamping", &m_pParticleParam->GetAlphaDamping(), 0.001f, 0.5f, 1.0f);


	//�O�Ղ̐F�@float�^�ɃL���X�g
	float *rCol = m_pParticleParam->GetCol();

	ImGui::SetNextItemWidth(250);

	//�F�̐ݒ�
	ImGui::ColorEdit4("Color", rCol);

	//�p�[�e�B�N�����ۑ�
	if(ImGui::Button("Save"))
	{
		//�Z�[�u
		CParticleParam::SaveParticleDefaultParam(m_pParticleParam.get());
	}

	////�R���{�{�b�N�X�\��
	//if (CParticleParam::ShowParamConboBox(m_pParticleParam->GetType()))
	//{
	//	CParticleParam *pParam = new CParticleParam;

	//	//���ݒ�
	//	//Uniqueptr���g���ƃI�y���[�^�ł��Ȃ��������畁�ʂ̃|�C���^���m�ŃI�y���[�^
	//	*pParam = *CParticleParam::GetDefaultParam(type);
	//}

	//[Ctrl] + [Enter]
	if ((pKeyboard->GetKeyboardPress(DIK_LCONTROL) && pKeyboard->GetKeyboardTrigger(DIK_RETURN)))
	{
		//onoff�ݒ�
		m_bLoop ^= 1;
	}

	//[Enter]���������Ƃ��@�܂��́@���[�v���鎞
	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) || (m_bLoop && m_nCnt % m_nLoopInterval == 0))
	{
		CParticle::DetailsCreate(D3DXVECTOR3(0.0f, 50.0f, 100.0f),
			m_pParticleParam->GetLife(), m_pParticleParam->GetRadius(), m_pParticleParam->GetCol(), m_pParticleParam->GetNumber(),
			m_pParticleParam->GetSpeed(), m_pParticleParam->GetAlphaDamping(), m_pParticleParam->GetRadiusDamping(), m_pParticleParam->GetTex());
	}

#endif
}