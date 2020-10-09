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
#include "../camera.h"
#include "../fade.h"
#include "../particle.h"
#include "../ParticleManager.h"
#include "../MeshField.h"
#include "../keyboard.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define EFFECT_CREATE_POS (D3DXVECTOR3(0.0f, 50.0f, 100.0f))
#define PARAMATER_SAVE_FILENAME ("data/Load/EffectParam/SaveParamater.txt")
#define LINE_LENGTH (500.0f)
#define LINE_OFFSET (D3DXVECTOR3(0.0f,LINE_LENGTH,0.0f))


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
HRESULT CDebug_EffectViewer::Init(HWND hWnd)
{
	//��
	//CMeshField::Create(ZeroVector3, D3DXVECTOR3(50.0f, 50.0f, 50.0f), INTEGER2(20, 20));

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
			//�G�t�F�N�g�r���[��
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
	static CParticleParam::PARTICLE_TYPE NowText = CParticleParam::PARTICLE_TYPE::EFFECT_DEFAULT;
	static FILENAME_LIST aShapeName = { "Sphere","Cone","Circle_XY","Line" };
	static bool bSquare = false;	//�����`��ۂ�
	//�L�[�{�[�h�̃|�C���^�擾
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	//�~�܂��Ă邩�ǂ���
	if (!CScene::GetStop())
	{
		//�J�E���^++
		m_nCnt++;
	}


	//Debug
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

	//�R���{�{�b�N�X�@�e�N�X�`��
	m_pParticleParam->GetAnimation() ?
		CHossoLibrary::ImGui_Combobox(CTexture::GetSeparateFileName(), "SeparateTex", (int&)m_pParticleParam->GetSeparateTex()) :	//�^
		CHossoLibrary::ImGui_Combobox(CTexture::GetTexFileName(), "Texture", (int&)m_pParticleParam->GetTex());						//�U

	//���ڂ̑傫���ݒ�
	ImGui::PushItemWidth(200);

	//���s
	ImGui::Separator();

	//�A�j���[�V�������邩�ǂ���
	ImGui::Checkbox("bAnimation", &m_pParticleParam->GetAnimation());

	//�A�j���[�V�������鎞
	if (m_pParticleParam->GetAnimation())
	{
		//�c���[
		if(ImGui::TreeNode("AnimationParam"))
		{
			//�A�j���[�V�����p�����[�^�ݒ�

			//���[�v���邩
			ImGui::Checkbox("bAnimationLoop", &m_pParticleParam->GetAnimationLoop());

			//�A�j���[�V�����؂�ւ��̃J�E���g
			ImGui::InputInt("AnimationCntSwitch", &m_pParticleParam->GetAnimationCntSwitch(), 1, 1, 20);

			//�c���[�I��
			ImGui::TreePop();
		}
	}

	//���s
	ImGui::Separator();

	//�����蔻�肪���邩�ǂ���
	ImGui::Checkbox("bCollision", &m_pParticleParam->GetCollision());

	//�����蔻�肪���鎞
	if (m_pParticleParam->GetCollision())
	{
		//�c���[
		if (ImGui::TreeNode("CollisionParam"))
		{
			//�����蔻�肪���邩�ǂ���
			ImGui::Checkbox("m_bCollisionSizeCalc", &m_pParticleParam->GetCollisionSizeCalc());

			//�A�j���[�V�����p�����[�^�ݒ�
			ImGui::DragFloat3("CollisionSize", m_pParticleParam->GetCollisionSize(), 0.5f, 1.0f, 250.0f);

			//�{�^���@�e�N�X�`���̃T�C�Y�ɂ���
			if(ImGui::Button("TexSize"))
			{
				//�R���W�����̃T�C�Y���e�N�X�`���̃T�C�Y�ɂ���
				m_pParticleParam->GetCollisionSize() = m_pParticleParam->GetSize();
			}

			//�R���W�����̌p������
			ImGui::InputInt("CollisionCnt", &m_pParticleParam->GetCollisionCnt());

			//�U����
			ImGui::InputInt("CollisionAttackValue", &m_pParticleParam->GetCollisionAttackValue());

			//�c���[�I��
			ImGui::TreePop();
		}
	}

	//���s
	ImGui::Separator();

	//�c���[
	if (ImGui::TreeNode("RendererSetting"))
	{
		//���Z�������邩
		ImGui::Checkbox("bAlphaBlend_Add", &m_pParticleParam->GetAlphaBlend_Add());
		ImGui::SameLine();

		//���Z�������邩
		ImGui::Checkbox("bAlphaBlend_Sub", &m_pParticleParam->GetAlphaBlend_Sub());

		//Z�e�X�g���邩
		ImGui::Checkbox("bZTest", &m_pParticleParam->GetZTest());
		ImGui::SameLine();

		//Z���C�e�B���O���邩
		ImGui::Checkbox("bZWrite", &m_pParticleParam->GetZWrite());

		//�r���{�[�h���邩
		ImGui::Checkbox("bBillboard", &m_pParticleParam->GetBillboard());

		//�Ǐ]���邩
		ImGui::Checkbox("bFollowing", &m_pParticleParam->GetFollowing());

		//�c���[�I��
		ImGui::TreePop();
	}

	//���s
	ImGui::Separator();

	//�R���{�{�b�N�X�@Shape
	CHossoLibrary::ImGui_Combobox(aShapeName, "Shape", (int&)m_pParticleParam->GetShape());

	//��]��
	if (ImGui::DragFloat3("rot", m_pParticleParam->GetRot(), 0.005f, -D3DX_PI, D3DX_PI))
	{
		//
		D3DXVECTOR3 TargetPos = D3DXVECTOR3(-sinf(m_pParticleParam->GetRot().y) * cosf(m_pParticleParam->GetRot().x) * LINE_LENGTH,
									sinf(m_pParticleParam->GetRot().x) * LINE_LENGTH,
									-cosf(m_pParticleParam->GetRot().y) * cosf(m_pParticleParam->GetRot().x) * LINE_LENGTH);


	}
	ImGui::DragFloat("fRange", &m_pParticleParam->GetRange(), 0.01f, -D3DX_PI, D3DX_PI);

	//���s
	ImGui::Separator();

	//�p�����[�^�ݒ�
	ImGui::DragInt("Life", &m_pParticleParam->GetLife(), 1, 1, 300);
	ImGui::DragInt("ParticleNum", &m_pParticleParam->GetNumber(), 1, 1, 300);
	ImGui::DragFloat("Speed", &m_pParticleParam->GetSpeed(), 0.5f, 0.0f, 250.0f);

	//�����s
	ImGui::SameLine();

	//�X�s�[�h�����_����
	ImGui::Checkbox("bSpeedRandom", &m_pParticleParam->GetSpeedRandom());

	ImGui::DragFloat3("LocalPos", m_pParticleParam->GetLocalPos(), 0.5f, 1.0f, 300.0f);
	ImGui::DragFloat3("LocalPos_Range", m_pParticleParam->GetLocalRandomPosRange(), 0.5f, 1.0f, 300.0f);



	//�����`��ۂƂ�
	if (bSquare)
	{
		//�T�C�Y�Őݒ肵���l��x��y�ɂ����Ɠ����
		//x�̃p�����[�^���������Ă�
		float fSize = m_pParticleParam->GetSize().x;
		float fSizeDamping = m_pParticleParam->GetSizeDamping().x;

		ImGui::DragFloat("Size", &fSize, 0.5f, 1.0f, 250.0f);
		ImGui::DragFloat("SizeDamping", &fSizeDamping, 0.001f, 0.5f, 1.0f);

		m_pParticleParam->GetSize().x = m_pParticleParam->GetSize().y = fSize;
		m_pParticleParam->GetSizeDamping().x = m_pParticleParam->GetSizeDamping().y = fSizeDamping;
	}
	else
	{
		//x.y.z���ꂼ��̃p�����[�^
		ImGui::DragFloat3("Size", m_pParticleParam->GetSize(), 0.5f, 1.0f, 250.0f);
		ImGui::DragFloat3("SizeDamping", m_pParticleParam->GetSizeDamping(), 0.001f, 0.5f, 1.0f);
	}
	//�����s
	ImGui::SameLine();

	//�����`��ۂ�
	ImGui::Checkbox("Square", &bSquare);

	//a�l�̌�����
	ImGui::DragFloat("AlphaDamping", &m_pParticleParam->GetAlphaDamping(), 0.001f, 0.5f, 1.0f);

	//�d�͂����邩
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

	//���s
	ImGui::Separator();

	//�p�[�e�B�N�����ۑ�
	if (ImGui::Button("Save"))
	{
		//�Z�[�u
		CParticleParam::SaveParticleDefaultParam(m_pParticleParam.get(), PARAMATER_SAVE_FILENAME);
	}

	if (ImGui::TreeNode("OverRideSave"))
	{

		//�p�[�e�B�N�����ۑ�
		if (ImGui::Button("OverRideSave"))
		{
			//�Z�[�u
			CParticleParam::SaveParticleDefaultParam(m_pParticleParam.get(), m_pParticleParam->GetFileNameList()[NowText]);
		}

		ImGui::TreePop();
	}


	//[Ctrl] + [Enter]
	if ((pKeyboard->GetPress(DIK_LCONTROL) && pKeyboard->GetTrigger(DIK_RETURN)))
	{
		//onoff�ݒ�
		m_bLoop ^= 1;
	}

	//( [Enter]���������Ƃ��@�܂��́@���[�v���鎞 ) �Ȃ�����Scene���~�܂��ĂȂ���
	if (pKeyboard->GetTrigger(DIK_RETURN) || ((m_bLoop && m_nCnt % m_nLoopInterval == 0) && !CScene::GetStop()))
	{
		CParticle::CreateFromParam(SCREEN_CENTER_POS,ZeroVector3 ,m_pParticleParam.get());
	}

}
