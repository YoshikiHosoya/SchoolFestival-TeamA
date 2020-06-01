//=============================================================================
// �J�������� [camera.cpp]
//=============================================================================
#include "camera.h"
#include "inputKeyboard.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "Player.h"
#include "Scene.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_LENGTH (-100) //�J�����̋���
//=============================================================================
// �J�����̏���������
//=============================================================================
void CCamera::InitCamera(void)
{
	posVDest = posV = D3DXVECTOR3(0.0f, 500.0f, 330.0f);

	posRDest = posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vecV = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 diff = (posV-posR);
	fDistance = sqrtf(diff.x*diff.x + diff.z*diff.z);
	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rot  = D3DXVECTOR3(atan2f(diff.y, diff.z),atan2f(diff.x, diff.z),atan2f(diff.x,diff.y));
}
//=============================================================================
// �J�����̏I������
//=============================================================================
void CCamera::UninitCamera(void)
{
}
//=============================================================================
// �J�����̍X�V����
//=============================================================================
void CCamera::UpdateCamera(void)
{
#ifdef _DEBUG
	CKeyboard *key;
	key = CManager::GetInputKeyboard();
	//�J�����̉�]---------------------------------------------------------������
	if (key->GetKeyboardPress(DIK_UP))
	{
		rot.x += 0.08f;
	}
	if (key->GetKeyboardPress(DIK_DOWN))
	{
		rot.x -= 0.08f;
	}
	if (key->GetKeyboardPress(DIK_RIGHT))
	{
		rot.y += 0.08f;
	}
	if (key->GetKeyboardPress(DIK_LEFT))
	{
		rot.y -= 0.08f;
	}
#endif

	//��]�̐��l�w��-------------------------------------------------------������
	if (rot.y > D3DX_PI)
	{
		rot.y += -D3DX_PI * 2;
	}
	if (rot.y < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2;
	}
	if (rot.x > D3DX_PI*0.5f)
	{
		rot.x = D3DX_PI*0.5f;
	}
	if (rot.x < -D3DX_PI*0.5f)
	{
		rot.x = -D3DX_PI*0.5f;
	}
	//�Ǐ]����================================================================================������
	//�L���X�g
	CScene *pScene;
	pScene = CScene::GetScene(CScene::OBJTYPE_PLAYER);
	if (pScene != NULL)
	{
		pos = ((CPlayer*)pScene)->GetPosition();
	}
	////���_�̖ړI�n�̌v�Z-------------------------------------------------������
	posVDest.x = pos.x - sinf(rot.y)*cosf(rot.x)*fDistance;
	posVDest.y = pos.y + sinf(rot.x)			*fDistance;
	posVDest.z = pos.z - cosf(rot.y)*cosf(rot.x)*fDistance;

	//���_�̈ړ�-----------------------------------------------------------������
	posV.x += (posVDest.x - posV.x) * 0.08f;
	posV.y += (posVDest.y - posV.y) * 0.08f;
	posV.z += (posVDest.z - posV.z) * 0.08f;

	//�J�����ŏI�ړI�n�̌v�Z-----------------------------------------------������
	posRDest.x = pos.x;
	posRDest.y = pos.y;
	posRDest.z = pos.z;

	posR.x += (posRDest.x - posR.x) * 0.08f;
	posR.y += (posRDest.y - posR.y) * 0.08f;
	posR.z += (posRDest.z - posR.z) * 0.08f;
	//========================================================================================������

	//������R-------------------------------------------------------------������
	move.x += (0 - move.x)*0.3f;
	move.y += (0 - move.y)*0.3f;
	move.z += (0 - move.z)*0.3f;
	pos += move;

	CDebugProc::Print("posV.x:%0.2f\nposV.y:%0.2f\nposV.z:%0.2f\n\n", posV.x, posV.y, posV.z);
	CDebugProc::Print("posR.x:%0.2f\nposR.y:%0.2f\nposR.z:%0.2f\n", posR.x, posR.y, posR.z);
}
//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();

	// �v���W�F�N�V�����}�g���b�N�X�̏�����--------------------------------������
	D3DXMatrixIdentity(&mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬----------------------------------������
	D3DXMatrixPerspectiveFovLH(&mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		10000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�----------------------------------������
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);

	// �r���[�}�g���b�N�X�̏�����------------------------------------------������
	D3DXMatrixIdentity(&mtxView);

	// �r���[�}�g���b�N�X���쐬--------------------------------------------������
	D3DXMatrixLookAtLH(&mtxView,
		&posV,
		&posR,
		&vecV);

	// �r���[�}�g���b�N�X�̐ݒ�--------------------------------------------������
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);
}
//=============================================================================
//�J�����̈ړ��֐�
//=============================================================================
void CCamera::SetMoveCamera(float Crot)
{
	move.x += sinf(-D3DX_PI* Crot + rot.y) * 5;
	move.z += cosf(-D3DX_PI* Crot + rot.y) * 5;
}
