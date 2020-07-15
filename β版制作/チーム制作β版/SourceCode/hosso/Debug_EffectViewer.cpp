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
#include "Debug_WorldLine.h"
#include "../Scene.h"
#include "../manager.h"
#include "../renderer.h"
#include "../inputKeyboard.h"
#include "../camera.h"
#include "../fade.h"
#include "../particle.h"
#include "../ParticleManager.h"
#include "../MeshField.h"
#include "../3Dline.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define EFFECT_CREATE_POS (D3DXVECTOR3(0.0f, 50.0f, 100.0f))
#define LINE_OFFSET (D3DXVECTOR3(0.0f,500.0f,0.0f))

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CDebug_EffectViewer::CDebug_EffectViewer()
{
	m_bLoop = false;
	m_nLoopInterval = 60;
	m_nCnt = 0;
	m_pParticleParam.reset();
	m_p3DLine = nullptr;
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CDebug_EffectViewer::~CDebug_EffectViewer()
{
	if (m_pWorldLine)
	{
		delete m_pWorldLine;
		m_pWorldLine = nullptr;
	}
}

//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CDebug_EffectViewer::Init()
{
	//��
	CMeshField::Create(ZeroVector3, D3DXVECTOR3(50.0f, 50.0f, 50.0f), INTEGER2(20, 20));

	//���
	m_pWorldLine = CDebug_WorldLine::Create(EFFECT_CREATE_POS);

	//���C���̐���
	m_p3DLine = C3DLine::Create(EFFECT_CREATE_POS, ZeroVector3, ZeroVector3, LINE_OFFSET, WhiteColor);

	//�p�[�e�B�N���̃}�l�[�W��
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
	CScene::RereaseAll();
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
	//�L�����N�^�[�����
	ImGui::Begin("EffectViewer");

	////Tab
	//if (ImGui::BeginTabBar("Viewer", m_bModel))
	//{
	//	//Tab
	//	if (ImGui::BeginTabItem("MotionViewer"))
	//	{
			//���[�V�����r���[��
			ParticleParamaterViewer();
			//ImGui::EndTabItem();
	//	}

	//	//TabEnd
	//	ImGui::EndTabBar();
	//}

	ImGui::End();

#endif
}

//------------------------------------------------------------------------------
//�p�[�e�B�N���̃p�����[�^�̃r���[��
//------------------------------------------------------------------------------
void CDebug_EffectViewer::ParticleParamaterViewer()
{
	//�ǂݍ��ރe�L�X�g�̔ԍ�
	static CParticleParam::PARTICLE_TEXT NowText = CParticleParam::PARTICLE_TEXT::PARTICLE_DEFAULT;
	static FILENAME_LIST aShapeName = { "Sphere","Cone","Circle_XY","Line" };

	//�~�܂��Ă邩�ǂ���
	if (!CScene::GetStopFlag())
	{
		//�J�E���^++
		m_nCnt++;
	}

	//�L�[�{�[�h�̃|�C���^�擾
	CKeyboard *pKeyboard = CManager::GetInputKeyboard();

	//Debug
	CDebugProc::Print("[Enter] �p�[�e�B�N������\n");
	CDebugProc::Print("[Ctrl] + [Enter] Loop %d \n", m_bLoop);

	//�R���{�{�b�N�X�@�t�@�C����
	if (CHossoLibrary::ImGui_Combobox(CParticleParam::GetFileNameList(), "ParamFileName", (int&)NowText))
	{
		//�������m��
		CParticleParam *pParam = new CParticleParam;

		//�p�����[�^���R�s�[
		//unique_ptr���Ƒ���ł��Ȃ�
		*pParam = *CParticleParam::GetDefaultParam(NowText);

		//�������m�ۂ��Ȃ���
		m_pParticleParam.reset(std::move(pParam));
	}

	//�R���{�{�b�N�X�@Shape
	if (CHossoLibrary::ImGui_Combobox(aShapeName, "Shape", (int&)m_pParticleParam->GetShape()))
	{

	}

	//�A�j���[�V�������邩�ǂ���
	ImGui::Checkbox("bAnimation", &m_pParticleParam->GetAnimation());

	//�R���{�{�b�N�X�@�e�N�X�`��
	m_pParticleParam->GetAnimation() ?
		CHossoLibrary::ImGui_Combobox(CTexture::GetSeparateFileName(), "SeparateTex", (int&)m_pParticleParam->GetSeparateTex()) :	//�^
		CHossoLibrary::ImGui_Combobox(CTexture::GetTexFileName(), "Texture", (int&)m_pParticleParam->GetTex());						//�U

	ImGui::Checkbox("bAlphaBlend", &m_pParticleParam->GetAlphaBlend());


	//���ꂼ��̃I�t�Z�b�g�𒲐�
	ImGui::DragFloat3("rot", m_pParticleParam->GetRot(), 0.005f, -D3DX_PI, D3DX_PI);
	ImGui::DragFloat("fRange", &m_pParticleParam->GetRange(), 0.01f, -D3DX_PI, D3DX_PI);

	//���ڂ̑傫���ݒ�
	ImGui::PushItemWidth(120);

	//�p�����[�^�ݒ�
	ImGui::DragInt("Life", &m_pParticleParam->GetLife(), 1, 1, 300);
	ImGui::DragFloat("Radius", &m_pParticleParam->GetRadius(), 0.5f, 1.0f, 250.0f);
	ImGui::DragFloat("Speed", &m_pParticleParam->GetSpeed(), 0.5f, 1.0f, 250.0f);
	ImGui::DragInt("ParticleNum", &m_pParticleParam->GetNumber(), 1, 0, 300);
	ImGui::DragFloat("RadiusDamping", &m_pParticleParam->GetRadiusDamping(), 0.001f, 0.5f, 1.0f);
	ImGui::DragFloat("AlphaDamping", &m_pParticleParam->GetAlphaDamping(), 0.001f, 0.5f, 1.0f);

	ImGui::Checkbox("bSpeedRandom", &m_pParticleParam->GetSpeedRandom());
	ImGui::Checkbox("bGravity", &m_pParticleParam->GetGravity());
	//�d�͂�ON�̎�
	if (m_pParticleParam->GetGravity())
	{
		//�����s
		ImGui::SameLine();

		//�d�͂̑傫��
		ImGui::DragFloat("GravityPower", &m_pParticleParam->GetGravityPower(), 0.005f, 0.1f, 2.0f);
	}

	//�O�Ղ̐F�@float�^�ɃL���X�g
	float *rCol = m_pParticleParam->GetCol();

	//���ڂ̑傫���ݒ�
	ImGui::SetNextItemWidth(250);

	//�F�̐ݒ�
	ImGui::ColorEdit4("Color", rCol);

	//�p�[�e�B�N�����ۑ�
	if (ImGui::Button("Save"))
	{
		//�Z�[�u
		CParticleParam::SaveParticleDefaultParam(m_pParticleParam.get());
	}

	//[Ctrl] + [Enter]
	if ((pKeyboard->GetKeyboardPress(DIK_LCONTROL) && pKeyboard->GetKeyboardTrigger(DIK_RETURN)))
	{
		//onoff�ݒ�
		m_bLoop ^= 1;
	}

	//( [Enter]���������Ƃ��@�܂��́@���[�v���鎞 ) �Ȃ�����Scene���~�܂��ĂȂ���
	if ((pKeyboard->GetKeyboardTrigger(DIK_RETURN) || (m_bLoop && m_nCnt % m_nLoopInterval == 0)) && !CScene::GetStopFlag())
	{
		CParticle::CreateFromParam(EFFECT_CREATE_POS, m_pParticleParam.get());
	}

}
