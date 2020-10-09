//------------------------------------------------------------------------------
//
//���C�u��������  [HossoLibrary.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "hossolibrary.h"
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "light.h"
#include "mouse.h"
#include "sound.h"
#include "scene.h"
#include "scene2D.h"
#include "scene3D.h"
#include "particle.h"
#include "modelinfo.h"
#include "Pad_XInput.h"
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define STICK_ON	(0.8f)
#define JOY_MAX_RANGE  (32768.0f)

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
CKeyboard *CHossoLibrary::m_pKeyboard = nullptr;
CPad_XInput *CHossoLibrary::m_pXInput = nullptr;

bool CHossoLibrary::m_bStickX = false;
bool CHossoLibrary::m_bStickY = false;
float CHossoLibrary::m_fLeftStickX = false;
float CHossoLibrary::m_fLeftStickY = false;
bool CHossoLibrary::m_WireFrame = false;
bool CHossoLibrary::m_Lighting = true;
bool CHossoLibrary::m_bDebugPlayer = false;
int CHossoLibrary::m_Culling = false;

//------------------------------------------------------------------------------
//�ړ��p�̃`�F�b�N�֐�
//------------------------------------------------------------------------------
bool CHossoLibrary::CheckMove(DIRECTION direction)
{
	switch (direction)
	{
	case DIRECTION::UP:
		//��
		if (m_pKeyboard->GetTrigger(DIK_W) || m_pKeyboard->GetTrigger(DIK_UP) || m_pXInput->GetPress(CPad_XInput::JOYPADKEY_UP))
		{
			return true;
		}
		break;
	case DIRECTION::DOWN:
		//��
		if (m_pKeyboard->GetTrigger(DIK_S) || m_pKeyboard->GetTrigger(DIK_DOWN) || m_pXInput->GetPress(CPad_XInput::JOYPADKEY_DOWN))
		{
			return true;
		}
		break;
	case DIRECTION::LEFT:
		//��
		if (m_pKeyboard->GetTrigger(DIK_A) || m_pKeyboard->GetTrigger(DIK_LEFT) || m_pXInput->GetPress(CPad_XInput::JOYPADKEY_LEFT))
		{
			return true;
		}
		break;
	case DIRECTION::RIGHT:

		//��
		if (m_pKeyboard->GetTrigger(DIK_D) || m_pKeyboard->GetTrigger(DIK_RIGHT) || m_pXInput->GetPress(CPad_XInput::JOYPADKEY_RIGHT))
		{
			return true;
		}
		break;
	}
	return false;
}

//------------------------------------------------------------------------------
//�I�����p�`�F�b�N�֐�
//------------------------------------------------------------------------------
CHossoLibrary::DIRECTION CHossoLibrary::CheckSelect()
{
	CHossoLibrary::DIRECTION direction = CHossoLibrary::NONE;

	//��
	if ((m_pKeyboard->GetTrigger(DIK_W) || m_pKeyboard->GetTrigger(DIK_UP) || m_pXInput->GetTrigger(CPad_XInput::JOYPADKEY_UP,1) || (m_fLeftStickY / JOY_MAX_RANGE > STICK_ON && m_bStickY == false)))
	{
		direction = CHossoLibrary::UP;
	}
	//��
	else if ((m_pKeyboard->GetTrigger(DIK_S) || m_pKeyboard->GetTrigger(DIK_DOWN) || m_pXInput->GetTrigger(CPad_XInput::JOYPADKEY_DOWN, 1) || (m_fLeftStickY / JOY_MAX_RANGE < -STICK_ON && m_bStickY == false)))
	{
		direction = CHossoLibrary::DOWN;
	}
	//��
	else if ((m_pKeyboard->GetTrigger(DIK_D) || m_pKeyboard->GetTrigger(DIK_RIGHT) || m_pXInput->GetTrigger(CPad_XInput::JOYPADKEY_RIGHT, 1) || (m_fLeftStickX / JOY_MAX_RANGE > STICK_ON && m_bStickX == false)))
	{
		direction = CHossoLibrary::RIGHT;
	}
	//��
	else if ((m_pKeyboard->GetTrigger(DIK_A) || m_pKeyboard->GetTrigger(DIK_LEFT) || m_pXInput->GetTrigger(CPad_XInput::JOYPADKEY_LEFT, 1)  || (m_fLeftStickX / JOY_MAX_RANGE < -STICK_ON && m_bStickX == false)))
	{
		direction = CHossoLibrary::LEFT;
	}

	return direction;
}

//------------------------------------------------------------------------------
//�W�����v
//------------------------------------------------------------------------------
bool CHossoLibrary::CheckJump(INPUTTYPE type)
{
	switch (type)
	{
	case CHossoLibrary::PRESS:
		if (m_pKeyboard->GetPress(DIK_SPACE) || m_pXInput->GetPress(CPad_XInput::JOYPADKEY_A))
		{
			return true;
		}
		break;
	case CHossoLibrary::TRIGGER:
		if (m_pKeyboard->GetTrigger(DIK_SPACE) || m_pXInput->GetTrigger(CPad_XInput::JOYPADKEY_A, 1))
		{
			return true;
		}
		break;
	}
	return false;
}
//------------------------------------------------------------------------------
//���� �g���K�[�̂�
//------------------------------------------------------------------------------
bool CHossoLibrary::CheckDash(INPUTTYPE type)
{
	switch (type)
	{
	case CHossoLibrary::PRESS:
		if (m_pKeyboard->GetPress(DIK_LSHIFT) || m_pXInput->GetPress(CPad_XInput::JOYPADKEY_R2))
		{
			return true;
		}
		break;
	case CHossoLibrary::TRIGGER:
		if (m_pKeyboard->GetTrigger(DIK_LSHIFT) || m_pXInput->GetTrigger(CPad_XInput::JOYPADKEY_R2, 5))
		{
			return true;
		}
		break;
	}

	return false;
}
//------------------------------------------------------------------------------
//�J�������Z�b�g
//------------------------------------------------------------------------------
bool CHossoLibrary::CheckCameraReset(INPUTTYPE type)
{
	switch (type)
	{
	case CHossoLibrary::PRESS:
		if (m_pKeyboard->GetPress(DIK_V) || m_pXInput->GetPress(CPad_XInput::JOYPADKEY_L2))
		{
			return true;
		}
		break;
	case CHossoLibrary::TRIGGER:
		if (m_pKeyboard->GetTrigger(DIK_V) || m_pXInput->GetTrigger(CPad_XInput::JOYPADKEY_L2, 1))
		{
			return true;
		}
		break;
	}

	return false;
}
//------------------------------------------------------------------------------
//���� �g���K�[�̂�
//------------------------------------------------------------------------------
bool CHossoLibrary::CheckDecision()
{
	if (m_pKeyboard->GetTrigger(DIK_RETURN) || m_pKeyboard->GetTrigger(DIK_SPACE) ||
		m_pXInput->GetTrigger(CPad_XInput::JOYPADKEY_A, 1))
	{
		CManager::GetSound()->Play(CSound::LABEL_SE_DECISION);
		return true;
	}
	return false;
}
//------------------------------------------------------------------------------
//�`���[�g���A���X�L�b�v
//------------------------------------------------------------------------------
bool CHossoLibrary::CheckSkipTutorial()
{
	if (m_pKeyboard->GetTrigger(DIK_RETURN) ||
		m_pXInput->GetTrigger(CPad_XInput::JOYPADKEY_START, 1))
	{
		return true;
	}
	return false;
}
//------------------------------------------------------------------------------
//�L�����Z�� �g���K�[�̂�
//------------------------------------------------------------------------------
bool CHossoLibrary::CheckCancel()
{
	if (m_pKeyboard->GetTrigger(DIK_BACKSPACE) || m_pKeyboard->GetTrigger(DIK_DELETE) ||
		m_pXInput->GetTrigger(CPad_XInput::JOYPADKEY_BACK, 1) || m_pXInput->GetTrigger(CPad_XInput::JOYPADKEY_B, 1))
	{
		CManager::GetSound()->Play(CSound::LABEL_SE_CANCEL);

		return true;
	}
	return false;
}
//------------------------------------------------------------------------------
//�|�[�Y �g���K�[�̂�
//------------------------------------------------------------------------------
bool CHossoLibrary::CheckPause()
{
	if (m_pKeyboard->GetTrigger(DIK_P) || m_pXInput->GetTrigger(CPad_XInput::JOYPADKEY_START, 1))
	{
		CManager::GetSound()->Play(CSound::LABEL_SE_PAUSE);
		return true;

	}
	return false;
}

//------------------------------------------------------------------------------
//�����{�^�������ĉ������p�@�g���K�[
//------------------------------------------------------------------------------
bool CHossoLibrary::CheckAnyButton()
{
	if (m_pKeyboard->GetTrigger(DIK_RETURN)						|| m_pKeyboard->GetTrigger(DIK_SPACE) ||
		m_pXInput->GetTrigger(CPad_XInput::JOYPADKEY_START, 1)	|| m_pXInput->GetTrigger(CPad_XInput::JOYPADKEY_BACK, 1) ||
		m_pXInput->GetTrigger(CPad_XInput::JOYPADKEY_A, 1)		|| m_pXInput->GetTrigger(CPad_XInput::JOYPADKEY_B, 1) ||
		m_pXInput->GetTrigger(CPad_XInput::JOYPADKEY_X, 1)		|| m_pXInput->GetTrigger(CPad_XInput::JOYPADKEY_Y, 1))
	{
		return true;
	}
	return false;
}
//------------------------------------------------------------------------------
//�X�e�B�b�N�̓|��Ă邩�̏������Z�b�g
//------------------------------------------------------------------------------
void CHossoLibrary::ResetStickInfo()
{
	//1F�O�̃X�e�B�b�N�������ɓ|��Ă邩�`�F�b�N
	fabsf(m_fLeftStickX / JOY_MAX_RANGE) > STICK_ON ? m_bStickX = true : m_bStickX = false;
	fabsf(m_fLeftStickY / JOY_MAX_RANGE) > STICK_ON ? m_bStickY = true : m_bStickY = false;

	//���t���[���̃X�e�B�b�N���擾
	m_pXInput->GetStickLeft(&m_fLeftStickX, &m_fLeftStickY);
}

D3DXCOLOR CHossoLibrary::RandomColor()
{
	return D3DXCOLOR(CHossoLibrary::Random(1), CHossoLibrary::Random(1), CHossoLibrary::Random(1), 1.0f);
}

void CHossoLibrary::StartVibration(int nCntVibration)
{
	m_pXInput->StartVibration(nCntVibration);
}

//------------------------------------------------------------------------------
//3D��ł̈ړ�����
//------------------------------------------------------------------------------
bool CHossoLibrary::Check3DMoveStick(D3DXVECTOR3 & Move, float const fMove, float const fCameraRot, float & fRotGoal)
{

	D3DXVECTOR3	Pad = ZeroVector3;

	//�p�b�h�̒l�擾
	m_pXInput->GetStickLeft(&Pad.x, &Pad.y);

	//joypad�̒l���o��
	Pad.x /= JOY_MAX_RANGE;
	Pad.y /= JOY_MAX_RANGE;

	float fAngle = atan2f((float)Pad.x, (float)Pad.y);				//�p�x
	float fLength = sqrtf(Pad.x * Pad.x + Pad.y * Pad.y);			//����

	//���ȉ��̒l�̏ꍇ�͔��肵�Ȃ�
	if (fabsf(fLength) < 0.2f)
	{
		fLength = 0;
		return false;
	}

	//��]�̌v�Z
	fRotGoal = D3DX_PI + fAngle + fCameraRot;

	CHossoLibrary::CalcRotation(fRotGoal);

	//�v���C���[��move�ɉ��Z
	Move.x += sinf(fAngle + fCameraRot) * fMove;
	Move.z += cosf(fAngle + fCameraRot) * fMove;


	return true;

}
//------------------------------------------------------------------------------
//R�X�e�B�b�N�ɂ��J������]
//------------------------------------------------------------------------------
bool CHossoLibrary::Check3DCameraStick(D3DXVECTOR3 & Rot, float fHolizonMove, float fVerticalMove)
{
	D3DXVECTOR3 Pad = ZeroVector3;

	//�p�b�h�̒l�擾
	m_pXInput->GetStickRight(&Pad.x, &Pad.y);

	//joypad�̒l���o��
	Pad.x /= JOY_MAX_RANGE;
	Pad.y /= JOY_MAX_RANGE;

	float fAngle = atan2f((float)Pad.x, (float)Pad.y);				//�p�x
	float fLength = sqrtf(Pad.x * Pad.x + Pad.y * Pad.y);			//����

	//���ȉ��̒l�̏ꍇ�͔��肵�Ȃ�
	if (fabsf(fLength) < 0.2f)
	{
		fLength = 0;
		return false;
	}

	//�J�����̉�]�����Z
	Rot.y += sinf(fAngle) * (fHolizonMove * fLength);
	Rot.x += cosf(fAngle) * (fVerticalMove * fLength);

	return true;
}
//------------------------------------------------------------------------------
//2D�̊O�όv�Z
//------------------------------------------------------------------------------
float CHossoLibrary::Vec2Cross(D3DXVECTOR2 const &rVecA, D3DXVECTOR2 const &rVecB)
{
	return rVecA.x * rVecB.y - rVecB.x * rVecA.y;
}

//------------------------------------------------------------------------------
//�}�g���b�N�X�v�Z
//------------------------------------------------------------------------------
void CHossoLibrary::CalcMatrix(D3DXMATRIX *pMtx, D3DXVECTOR3 const &rPos, D3DXVECTOR3 const &rRot)
{
	D3DXMATRIX	mtxRot, mtxTrans;			//�v�Z�p

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(pMtx);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rRot.y, rRot.x, rRot.z);
	D3DXMatrixMultiply(pMtx, pMtx, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, rPos.x, rPos.y, rPos.z);
	D3DXMatrixMultiply(pMtx, pMtx, &mtxTrans);
}
//------------------------------------------------------------------------------
//�}�g���b�N�X�v�Z
//------------------------------------------------------------------------------
void CHossoLibrary::CalcShadowMatrix(D3DXMATRIX & rShadowMtx, D3DXVECTOR3 const & rPos, D3DXVECTOR3 const & rNor)
{
	D3DXPLANE planeField;
	D3DXVECTOR3 LightVec = CManager::GetRenderer()->GetLight()->GetLightDir(0);
	D3DXVECTOR4 ShadowLightVec = ZeroVector4;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&rShadowMtx);

	//�e�p�̃��C�g�̐ݒ�
	ShadowLightVec = D3DXVECTOR4(-LightVec.x, -LightVec.y, -LightVec.z, 0);

	//�e�`��p�̃v���[������
	D3DXPlaneFromPointNormal(&planeField, &rPos, &rNor);

	//�e�̃}�g���b�N�X�ݒ�
	D3DXMatrixShadow(&rShadowMtx, &ShadowLightVec, &planeField);
}

//------------------------------------------------------------------------------
//Imgui������
//------------------------------------------------------------------------------
 HRESULT CHossoLibrary::InitImgui(HWND hWnd)
{
	//�Q�[���p�b�h�ƃL�[�{�[�h�̏��擾
	//���L���͖���ĂȂ�����J���̕K�v�͂Ȃ�
	m_pXInput = CManager::GetXInput();
	m_pKeyboard = CManager::GetKeyboard();

	//NULL�`�F�b�N
	if (!m_pXInput || !m_pKeyboard)
	{
		return E_FAIL;
	}

	//create
	IMGUI_CHECKVERSION();

	//����
	ImGui::CreateContext();

	//�f�t�H���g�J���[�ݒ�
	ImGui::StyleColorsDark();

	//������
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(CManager::GetRenderer()->GetDevice());

	return S_OK;
}
//------------------------------------------------------------------------------
//Imgui�I��
//------------------------------------------------------------------------------
void CHossoLibrary::UninitImgui()
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
//------------------------------------------------------------------------------
//Imgui �f�o�b�O���\��
//------------------------------------------------------------------------------
void CHossoLibrary::ShowDebugInfo()
{
#ifdef _DEBUG

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�J�n
	if (ImGui::CollapsingHeader("Debug"))
	{
		//FPS���
		if (ImGui::TreeNode("FPS"))
		{
			//FPS
			ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::TreePop();
		}
		//Scene�̐�
		if (ImGui::TreeNode("NumInfo"))
		{
			ImGui::Text("NumAll (%d)", CScene::GetNumAll());
			ImGui::Text("NumScene2D (%d)", CScene2D::GetNumScene2D());
			ImGui::Text("NumScene3D (%d)", CScene3D::GetNumScene3D());
			ImGui::Text("ParticleAll (%d)", COneParticle::GetNumAll());
			ImGui::TreePop();
		}

		//���
		if (ImGui::TreeNode("DebugCommand"))
		{
			//���C���[�t���[��
			if (ImGui::Checkbox("WireFrame", &m_WireFrame))
			{
				CheckWireMode();
			}

			//���C�e�B���O
			if (ImGui::Checkbox("Lighting", &m_Lighting))
			{
				pDevice->SetRenderState(D3DRS_LIGHTING, m_Lighting);		// ���C�e�B���O���[�h�؂�ւ�
			}

			//�J�����O
			if (ImGui::TreeNode("tree1", "CULLING"))
			{
				if (ImGui::RadioButton("D3DCULL_CCW", &m_Culling, 0))
				{
					//���ʃJ�����O
					CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_CULLING_CCW);
				}
				ImGui::SameLine();
				if (ImGui::RadioButton("D3DCULL_CW", &m_Culling, 1))
				{
					//�\�ʃJ�����O
					CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_CULLING_CW);
				}
				ImGui::SameLine();
				if (ImGui::RadioButton("D3DCULL_NONE", &m_Culling, 2))
				{
					//�J�����O���Ȃ�
					CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_CULLING_NONE);
				}
				ImGui::TreePop();
			}
			//�v���C���[�f�o�b�O
			if (ImGui::Checkbox("DebugPlayer", &m_bDebugPlayer))
			{

			}
			ImGui::TreePop();
		}
	}

#endif //DEBUG
}
//------------------------------------------------------------------------------
//���C���[�t���[�����ǂ����m�F
//Imgui�̃E�B���h�E�������C���[�t���[���ɂȂ�Ȃ��ׂɕK�v
//------------------------------------------------------------------------------
void CHossoLibrary::CheckWireMode()
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//true��false���Ō��߂�
	m_WireFrame ?
		CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_WIRE_ON):
		CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_WIRE_OFF);
}
//------------------------------------------------------------------------------
//�J�����O�̏�Ԋm�F�Ɛݒ�
//�ꎞ�I�ɏ�����ς����㉽�ɖ߂��ׂ����m�F�p
//------------------------------------------------------------------------------
void CHossoLibrary::CheckCulling()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	switch (m_Culling)
	{
	case 0:
		//���ʃJ�����O
		CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_CULLING_CCW);
		break;
	case 1:
		//�\�ʃJ�����O
		CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_CULLING_CW);
		break;
	case 2:
		//�J�����O���Ȃ�
		CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_CULLING_NONE);
		break;
	default:
		break;
	}
}
//------------------------------------------------------------------------------
//�J�����O�̏�Ԋm�F�Ɛݒ�
//�ꎞ�I�Ƀ��C�e�B���O��؂�����ɖ߂��ׂ����m�F�p
//------------------------------------------------------------------------------
void CHossoLibrary::CheckLighting()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	pDevice->SetRenderState(D3DRS_LIGHTING, m_Lighting);		// ���C�e�B���O���[�h�؂�ւ�
}

//------------------------------------------------------------------------------
//��]�̌v�Z�@360�x�ȓ��ɂ���
//------------------------------------------------------------------------------
void CHossoLibrary::CalcRotation(float &fRot)
{
	//������3.14���ȏ�̎�
	if (fRot > D3DX_PI)
	{
		//6.28����
		fRot -= D3DX_PI * 2;
	}
	//������-3.14�ȉ��̎�
	if (fRot < -D3DX_PI)
	{
		//6.28���Z
		fRot += D3DX_PI * 2;
	}
}


//------------------------------------------------------------------------------
//XYZ���S��3.14�ȓ��Ɏ��߂�
//------------------------------------------------------------------------------
void CHossoLibrary::CalcRotation_XYZ(D3DXVECTOR3 & rot)
{
	CHossoLibrary::CalcRotation(rot.x);
	CHossoLibrary::CalcRotation(rot.y);
	CHossoLibrary::CalcRotation(rot.z);

}
//------------------------------------------------------------------------------
//���f���̍ő咸�_�ƍŏ����_�����߂�
//------------------------------------------------------------------------------
void CHossoLibrary::SetModelVertex(MODEL_VTX & pModelVtx, CModelInfo & pModelInfo)
{
	int		nNumVertices;
	DWORD	sizeFVF;
	BYTE	*pVertexBuffer;

	pModelVtx.VtxMax = ZeroVector3;
	pModelVtx.VtxMin = ZeroVector3;

	//���_���擾
	nNumVertices = pModelInfo.GetMesh()->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(pModelInfo.GetMesh()->GetFVF());

	// ���_�o�b�t�@�̃��b�N
	pModelInfo.GetMesh()->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertexBuffer);

	//���_�̐������J��Ԃ�
	for (int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++)
	{
		//���_�����擾
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVertexBuffer;

		//�ő�̒��_���W�ƍŏ��̒��_���W���r���ďo��
		if (pModelVtx.VtxMin.x > vtx.x)
		{
			pModelVtx.VtxMin.x = vtx.x;
		}
		if (pModelVtx.VtxMax.x < vtx.x)
		{
			pModelVtx.VtxMax.x = vtx.x;
		}
		if (pModelVtx.VtxMin.z > vtx.z)
		{
			pModelVtx.VtxMin.z = vtx.z;
		}
		if (pModelVtx.VtxMax.z < vtx.z)
		{
			pModelVtx.VtxMax.z = vtx.z;
		}
		if (pModelVtx.VtxMin.y > vtx.y)
		{
			pModelVtx.VtxMin.y = vtx.y;
		}
		if (pModelVtx.VtxMax.y < vtx.y)
		{
			pModelVtx.VtxMax.y = vtx.y;
		}
		//�o�b�t�@���i�߂�
		pVertexBuffer += sizeFVF;
	}
	//�A�����b�N
	pModelInfo.GetMesh()->UnlockVertexBuffer();

}


//------------------------------------------------------------------------------
//���f���̍ő咸�_�ƍŏ����_�����߂�@��]�������̒���
//------------------------------------------------------------------------------
void CHossoLibrary::SetModelVertexRotation(D3DXMATRIX & pMtx, MODEL_VTX & pModelVtx, CModelInfo & pModelInfo)
{
	int		nNumVertices;
	DWORD	sizeFVF;
	BYTE	*pVertexBuffer;

	pModelVtx.VtxMax = ZeroVector3;
	pModelVtx.VtxMin = ZeroVector3;

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_���擾
	nNumVertices = pModelInfo.GetMesh()->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(pModelInfo.GetMesh()->GetFVF());

	// ���_�o�b�t�@�̃��b�N
	pModelInfo.GetMesh()->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertexBuffer);

	//���_�̐������J��Ԃ�
	for (int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++)
	{
		//���_�����擾
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVertexBuffer;

		//���[���h�}�g���b�N�X���|�����킹��
		D3DXVec3TransformCoord(&vtx, &vtx, &pMtx);

		//�ő�̒��_���W�ƍŏ��̒��_���W���r���ďo��
		if (pModelVtx.VtxMin.x > vtx.x)
		{
			pModelVtx.VtxMin.x = vtx.x;
		}
		if (pModelVtx.VtxMax.x < vtx.x)
		{
			pModelVtx.VtxMax.x = vtx.x;
		}
		if (pModelVtx.VtxMin.z > vtx.z)
		{
			pModelVtx.VtxMin.z = vtx.z;
		}
		if (pModelVtx.VtxMax.z < vtx.z)
		{
			pModelVtx.VtxMax.z = vtx.z;
		}
		if (pModelVtx.VtxMin.y > vtx.y)
		{
			pModelVtx.VtxMin.y = vtx.y;
		}
		if (pModelVtx.VtxMax.y < vtx.y)
		{
			pModelVtx.VtxMax.y = vtx.y;
		}
		//�o�b�t�@���i�߂�
		pVertexBuffer += sizeFVF;
	}
	//�A�����b�N
	pModelInfo.GetMesh()->UnlockVertexBuffer();
}

//------------------------------------------------------------------------------
//�r���{�[�h�ݒ� X��Z�̂�
//------------------------------------------------------------------------------
void CHossoLibrary::SetBillboard_XZ_Only(D3DXMATRIX * pMtx)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�v�Z�p�ϐ�
	D3DXMATRIX mtxView;

	//�r���[�}�g���b�N�X������
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�r���{�[�h�ݒ�
	pMtx->_11 = mtxView._11;
	pMtx->_12 = mtxView._21;
	pMtx->_13 = mtxView._31;
	//pMtx->_21 = mtxView._12;
	//pMtx->_22 = mtxView._22;
	//pMtx->_23 = mtxView._32;
	pMtx->_31 = mtxView._13;
	pMtx->_32 = mtxView._23;
	pMtx->_33 = mtxView._33;
}
//------------------------------------------------------------------------------
//�r���{�[�h�ݒ�
//------------------------------------------------------------------------------
void CHossoLibrary::SetBillboard(D3DXMATRIX * pMtx)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�v�Z�p�ϐ�
	D3DXMATRIX mtxView;

	//�r���[�}�g���b�N�X������
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�r���{�[�h�ݒ�
	pMtx->_11 = mtxView._11;
	pMtx->_12 = mtxView._21;
	pMtx->_13 = mtxView._31;
	pMtx->_21 = mtxView._12;
	pMtx->_22 = mtxView._22;
	pMtx->_23 = mtxView._32;
	pMtx->_31 = mtxView._13;
	pMtx->_32 = mtxView._23;
	pMtx->_33 = mtxView._33;
}
//------------------------------------------------------------------------------
//�͈͓��̒l�ɏC��
//------------------------------------------------------------------------------
bool CHossoLibrary::RangeLimit_Equal_Int(int & nValue, int nMin, int nMax)
{
	//�ŏ��l��菬������
	if (nValue < nMin)
	{
		//�ŏ��l�ɍ��킷
		nValue = nMin;
		return true;
	}
	//�ő�l���傫����
	if (nValue > nMax)
	{
		//�ő�l�ɍ��킷
		nValue = nMax;
		return true;
	}
	return false;
}
//------------------------------------------------------------------------------
//�͈͓��̒l�ɏC��
//------------------------------------------------------------------------------
bool CHossoLibrary::RangeLimit_Equal_Float(float & nValue, float nMin, float nMax)
{
	//�ŏ��l��菬������
	if (nValue < nMin)
	{
		//�ŏ��l�ɍ��킷
		nValue = nMin;
		return true;
	}
	//�ő�l���傫����
	if (nValue > nMax)
	{
		//�ő�l�ɍ��킷
		nValue = nMax;
		return true;
	}
	return false;
}
//------------------------------------------------------------------------------
//�c�̃��j���[�I��
//------------------------------------------------------------------------------
void CHossoLibrary::SelectVerticalMenu(int & nSelectNum, int const & nMaxSelect)
{
	//��
	if (CHossoLibrary::CheckSelect() == CHossoLibrary::UP)
	{
		nSelectNum--;
		//��ԁ��ɂ�������
		if (nSelectNum < 0)
		{
			//��ԁ��ɍ��킹��
			nSelectNum = 0;
		}
		else
		{
			CManager::GetSound()->Play(CSound::LABEL_SE_SELECT);
		}
	}
	//��
	if (CHossoLibrary::CheckSelect() == CHossoLibrary::DOWN)
	{
		nSelectNum++;
		//��ԁ��ɂ�������
		if (nSelectNum > nMaxSelect - 1)
		{
			//��ԁ��ɍ��킹��
			nSelectNum = nMaxSelect - 1;
		}
		else
		{
			CManager::GetSound()->Play(CSound::LABEL_SE_SELECT);
		}
	}
}
//------------------------------------------------------------------------------
//���̃��j���[�I��
//------------------------------------------------------------------------------
void CHossoLibrary::SelectHorizonMenu(int & nSelectNum, int const & nMaxSelect)
{
	//��
	if (CHossoLibrary::CheckSelect() == CHossoLibrary::LEFT)
	{
		nSelectNum--;
		if (nSelectNum < 0)
		{
			nSelectNum = 0;
		}
		else
		{
			CManager::GetSound()->Play(CSound::LABEL_SE_SELECT);
		}
	}
	//��
	if (CHossoLibrary::CheckSelect() == CHossoLibrary::RIGHT)
	{
		nSelectNum++;
		if (nSelectNum > nMaxSelect - 1)
		{
			nSelectNum = nMaxSelect - 1;
		}
		else
		{
			CManager::GetSound()->Play(CSound::LABEL_SE_SELECT);
		}
	}
}
//------------------------------------------------------------------------------
//-3.14�`3.14��Ԃ�
//------------------------------------------------------------------------------
float CHossoLibrary::Random_PI()
{
	return float(rand() % 314 / 100.0f) - float(rand() % 314) / 100.0f;
}

//------------------------------------------------------------------------------
//���͂��ꂽ�l��+-�����_���Ȓl�ŕԂ�
//------------------------------------------------------------------------------
float CHossoLibrary::Random(float fInputValue)
{
	//0���Z�h�~
	if (fInputValue <= 0.0f)
	{
		return 0.0f;
	}

	int nValue = int(fInputValue * 100);

	float fValue;

	rand() % 2 ?
		fValue = float(rand() % nValue / 100.0f) :
		fValue = -float(rand() % nValue / 100.0f);

	return fValue;
}

//------------------------------------------------------------------------------
//���͂��ꂽ�l��+-�����_���Ȓl�ŕԂ�
//------------------------------------------------------------------------------
D3DXVECTOR3 CHossoLibrary::RandomVector3(float Max)
{
	D3DXVECTOR3 Value = ZeroVector3;

	Value.x = Random(Max);
	Value.y = Random(Max);
	Value.z = Random(Max);


	return Value;
}


//------------------------------------------------------------------------------
//ImGui�̃R���{�{�b�N�X
//------------------------------------------------------------------------------
bool CHossoLibrary::ImGui_Combobox(std::vector<std::string> aItemNameList, std::string aTitle, int & nValue)
{
	bool bChange = false;

#ifdef _DEBUG
	//combo�J�n
	if (ImGui::BeginCombo(aTitle.data(), aItemNameList[nValue].data()))
	{
		//�v�f���J��Ԃ�
		for (size_t nCnt = 0; nCnt < aItemNameList.size(); nCnt++)
		{

			//�I��ԍ��������Ă邩�ǂ���
			bool is_selected = (aItemNameList[nValue] == aItemNameList[nCnt]);

			//�I�����ꂽ���̏���
			if (ImGui::Selectable(aItemNameList[nCnt].data(), is_selected))
			{
				//���݂̑I�����ڐݒ�
				nValue = nCnt;
				bChange = true;
			}
		}
		//combo�I��
		ImGui::EndCombo();

	}
#endif //DEBUG
	return bChange;
}
