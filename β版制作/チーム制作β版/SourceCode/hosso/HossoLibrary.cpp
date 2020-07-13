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
//-3.14�`3.14��Ԃ�
//------------------------------------------------------------------------------
float CHossoLibrary::Random_PI()
{
	return float(rand() % 314 / 100.0f) - float(rand() % 314) / 100.0f;
}
