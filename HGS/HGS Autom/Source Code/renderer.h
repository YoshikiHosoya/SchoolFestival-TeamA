//------------------------------------------------------------------------------
//
//�����_�����O����  [renderer.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _RENDERER_H_
#define _RENDERER_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CFade;
class CDebugProc;
class CCamera;
class CLight;

class CRenderer
{
public:

	//�����_���[����̃R�}���h
	enum RENDERER_COMMAND
	{
		RENDERER_LIGHTING_ON,				//���C�e�B���OON
		RENDERER_LIGHTING_OFF,				//���C�e�B���OOFF
		RENDERER_CULLING_NONE,				//�J�����O���Ȃ�
		RENDERER_CULLING_CCW,				//�����J�����O
		RENDERER_CULLING_CW,				//�\���J�����O
		RENDERER_ALPHABLEND_ADD,			//���Z����
		RENDERER_ALPHABLEND_SUB,			//���Z����
		REDNERER_ALPHABLEND_DEFAULT,		//�ʏ���
		RENDERER_ZTEST_OFF,					//Z�e�X�g����
		RENDERER_ZTEST_OFF_ZWRITING_ON,		//Z�e�X�g������Z���C�e�B���O�L��
		RENDERER_ZTEST_ON_ZWRITING_OFF,		//Z�e�X�g�L����Z���C�e�B���O����
		RENDERER_ZTEST_DEFAULT,				//Z�e�X�g�ʏ���
		RENDERER_FOG_ON,					//�t�H�OON
		RENDERER_FOG_OFF,					//�t�H�OOFF
		RENDERER_WIRE_ON,					//���C���[ON
		RENDERER_WIRE_OFF,					//���C���[OFF
	};

	CRenderer();			//�R���X�g���N�^
	~CRenderer();			//�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);		//������
	void Uninit();													//�I��
	void Update();													//�X�V
	void Draw();													//�`��
	void SetRendererCommand(RENDERER_COMMAND Command);				//�����_���[�ݒ�@�V���[�g�J�b�g�p
	void ResetRenderer();											//���[�h�J�ڎ��̃����_���[���̃��Z�b�g

	void SetDispImGuiInfo(bool ImGuiInfo)		{ m_bDispImGuiInfo = ImGuiInfo; };			//Imgui�\����\���ݒ�
	void SetDispDebugProcInfo(bool bDebugInfo) { m_bDispDebugProcInfo = bDebugInfo; };		//DebugProc�\����\���ݒ�

	bool CheckShowImGuiInfo()		{ return m_bDispImGuiInfo; };							//Imgui���\�����Ă邩�m�F
	bool CheckShowDebugProcInfo()	{ return m_bDispDebugProcInfo; };						//DebugProc���\�����Ă邩�m�F

	LPDIRECT3DDEVICE9 GetDevice()	{ return m_pD3DDevice; };		//�f�o�C�X���擾
	CFade *GetFade()				{ return m_pFade.get();};		//�t�F�[�h�擾
	CCamera *GetCamera()			{ return m_pCamera.get(); };	//�J�����擾
	CLight *GetLight()				{ return m_pLight.get(); };		//���C�g�̏��擾

private:
	static D3DXCOLOR m_BackColor;					//�w�i�F

	LPDIRECT3D9			m_pD3D;						//�E�B���h�E�����ɕK�v
	LPDIRECT3DDEVICE9	m_pD3DDevice;				//�E�B���h�E�����ɕK�v
	D3DPRESENT_PARAMETERS m_d3dpp;					//�v���[���e�[�V�����p�����[�^

	std::unique_ptr<CFade>		m_pFade;			//�t�F�[�h�̃|�C���^
	std::unique_ptr<CDebugProc>	m_pDebugProc;		//�f�o�b�O�e�L�X�g�ւ̃|�C���^
	std::unique_ptr<CCamera>	m_pCamera;			//�J�����ւ̃|�C���^
	std::unique_ptr<CLight>		m_pLight;			//���C�g�ւ̃|�C���^

	bool				m_bDispImGuiInfo;			//Imgui�`�悷�邩�ǂ���
	bool				m_bDispDebugProcInfo;		//�f�o�b�O�e�L�X�g�\�����邩


	void ResetDevice();								//Imgui�̃��Z�b�g
	void RendererDebugInfo();						//�����_���[�̃f�o�b�O���\�L
};

#endif