// ------------------------------------------
//
// �����_�����O�����̐���[renderer.h]
// Author : Fujiwara Masato
//
// ------------------------------------------

#ifndef _RENDERER_H_
#define _RENDERER_H_	 // �t�@�C������������߂�

// ------------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ------------------------------------------
#include "main.h"

// ------------------------------------------
//
// �}�N���֐�
//
// ------------------------------------------

// ------------------------------------------
//
// �O���錾
//
// ------------------------------------------
class CDebugproc;
class CCamera;
class CLight;
class CPointLight;

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CRenderer
{
public:
	/* �֐� */
	CRenderer();
	~CRenderer();
	HRESULT  Init(HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	// ���擾
	LPDIRECT3DDEVICE9 GetDevice(void);	// �f�o�C�X
	static CCamera * GetCamera(void);			// �J����
	CLight * GetLight(void);			// ���C�g
protected:

private:
	/* �ϐ� */
	LPDIRECT3D9 m_pD3D;				// Direct3D�I�u�W�F�N�g�̃|�C���^
	LPDIRECT3DDEVICE9 m_pDevice;	// Direct3D�f�o�C�X�̃|�C���^
	static CCamera * m_pCamera;		// �J�������
	CLight * m_pLight;				// ���C�g���
	CPointLight * m_pPointLight;	// ���C�g���

#ifdef _DEBUG
	static CDebugproc * m_debugproc;		// �f�o�b�O�\��
	void DrawFPS(void);				// FPS�֐�
#endif
};

#endif // !_RENDERER_H_