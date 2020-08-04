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
#include "../manager.h"
#include "../renderer.h"
#include "../inputKeyboard.h"
#include "../XInputPad.h"
#include "../sound.h"
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

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
//��������L�[���������Ƃ�
//------------------------------------------------------------------------------
bool CHossoLibrary::PressAnyButton(void)
{
	CKeyboard *Keyboard;
	Keyboard = CManager::GetInputKeyboard();
	CXInputPad *InpudPad;
	InpudPad = CManager::GetPad();

	if (Keyboard->GetKeyboardTrigger(DIK_RETURN)||
		Keyboard->GetKeyboardTrigger(DIK_SPACE)||
		InpudPad->GetTrigger(CXInputPad::JOYPADKEY_START,1)||
		InpudPad->GetTrigger(CXInputPad::JOYPADKEY_A, 1))
	{
		//CManager::GetSound()->Play(CSound::LABEL_SE_DECISION);

		return true;
	}
	return false;
}
//------------------------------------------------------------------------------
//�X�^�[�g�{�^�����������Ƃ�
//------------------------------------------------------------------------------
bool CHossoLibrary::PressStartButton(void)
{
	CKeyboard *Keyboard;
	Keyboard = CManager::GetInputKeyboard();
	CXInputPad *InpudPad;
	InpudPad = CManager::GetPad();
	if (Keyboard->GetKeyboardTrigger(DIK_RETURN) || InpudPad->GetTrigger(CXInputPad::JOYPADKEY_START, 1))
	{
		return true;
	}
	return false;
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

//------------------------------------------------------------------------------
//�p�b�h�̓��͏���
//------------------------------------------------------------------------------
bool CHossoLibrary::PadMoveInput(D3DXVECTOR3 & rMove, DIRECTION & direction,bool bJump)
{
	bool bInput = false;

	CXInputPad *pad;
	pad = CManager::GetPad();
	D3DXVECTOR3 InputValue = ZeroVector3;
	pad->GetStickLeft(&InputValue.x, &InputValue.y);//�p�b�h�̓��͒l����
	InputValue.x /= STICK_MAX_RANGE;//�l�̐��K��
	InputValue.y /= STICK_MAX_RANGE;//�l�̐��K��

	CDebugProc::Print("�p�b�h�̓��͒l X : %2f Y : %2f\n", InputValue.x, InputValue.y);

	//�E
	if (InputValue.x > 0.5f)
	{
		rMove = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
		direction = DIRECTION::RIGHT;
		bInput = true;

	}
	//��
	else if (InputValue.x < -0.5f)
	{
		rMove = D3DXVECTOR3(0.5f, 0.5f, 0.0f);
		direction = DIRECTION::LEFT;
		bInput = true;

	}
	//��
	if (InputValue.y > 0.6f)
	{
		direction = DIRECTION::UP;

	}
	//��
	else if (InputValue.y < -0.6f && bJump == false)
	{
		direction = DIRECTION::DOWN;
	}
	return bInput;
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
//-3.14�`3.14��Ԃ�
//------------------------------------------------------------------------------
float CHossoLibrary::Random_PI()
{
	return Random(3.14f);
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
	//Value.z = Random(Max);


	return Value;
}
