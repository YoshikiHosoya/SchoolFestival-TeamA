//------------------------------------------------------------------------------
//
//�V�F�[�_�[  [Shader.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _SHADER_H_
#define _SHADER_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------

//�V�F�[�_�[�̃n���h���̃N���X
class CShaderHandle
{
public:
	CShaderHandle() {};
	~CShaderHandle() {};
	//�V�F�[�_�[�̃O���[�o���ϐ��̃n���h��
	D3DXHANDLE m_hViewMtx;				//�r���[�}�g���b�N�X
	D3DXHANDLE m_hProjectionMtx;		//�v���W�F�N�V�����}�g���b�N�X
	D3DXHANDLE m_hLightDir0;			//�����̌���
	D3DXHANDLE m_hLightDir1;			//�����̌���
	D3DXHANDLE m_hLightDir2;			//�����̌���
	D3DXHANDLE m_hLightCol0;			//���̐F
	D3DXHANDLE m_hLightCol1;			//���̐F
	D3DXHANDLE m_hLightCol2;			//���̐F
	D3DXHANDLE m_hCount;				//�J�E���g

};
//�V�F�[�_�[�̃n���h���̃N���X
//���f���F�̃n���h��
class CShaderHandle_ModelColor
{
public:
	D3DXHANDLE m_hDiffuseCol;		//�g�U��
	D3DXHANDLE m_hSpecularCol;		//���ˌ�
	D3DXHANDLE m_hEmissiveCol;		//���ˌ�
	D3DXHANDLE m_Ambient;			//����
	D3DXHANDLE m_hPower;			//���˂̋���
};


class CShader
{
public:
	enum SHADER_TYPE
	{
		SHADER_NONE = -1,
		SHADER_MODELDRAW,
		SHADER_MAX,
	};

	CShader();
	~CShader();

	static void SetParamaterShader();
	static void InitStaticParam();
	static void UpdateStaticParam();
	static std::unique_ptr<CShader> Create();
	static HRESULT Load();
	static void UnLoad();
	ID3DXEffect *GetEffectPtr() { return m_pShaderEffect[m_type]; };
	static void SetModelColor(D3DXCOLOR DiffuseCol, D3DXCOLOR SpeculerCol, D3DXCOLOR EmissiveCol, D3DXCOLOR AmbientCol, float fPower);

	void SetType(SHADER_TYPE type)		{ m_type = type; };

private:
	static std::vector<ID3DXEffect*> m_pShaderEffect;								//�V�F�[�_�[�̃G�t�F�N�g�̃|�C���^�̃��X�g
	static std::vector<std::string> m_ShaderFileNameList;							//�V�F�[�_�[�̃t�@�C�����̃��X�g
	static std::vector<std::unique_ptr<CShaderHandle>> m_ShaderHandleList;			//�V�F�[�_�[�̃n���h���̃��X�g
	static std::unique_ptr<CShaderHandle_ModelColor> m_pModelColorHandle;
	SHADER_TYPE m_type;
	static int m_nCnt;





	static void GetGlobalHandle();

};
#endif