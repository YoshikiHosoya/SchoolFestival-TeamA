//==========================================================
// SceneBase�����FNORI
//==========================================================
//==========================================================
// �C���N���[�h�t�@�C��
//==========================================================
#include "SceneBase.h"
#include "renderer.h"
#include "manager.h"

//==========================================================
// �R���X�g���N�^
//==========================================================
CSceneBase::CSceneBase()
{
	m_pos = ZeroVector3;
	m_size = ZeroVector3;
	m_col = WhiteColor;
	m_rot = ZeroVector3;
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;
	m_bDisp = true;
	D3DXMatrixIdentity(&m_mtxWorld);

}

//==========================================================
// �f�X�g���N�^
//==========================================================
CSceneBase::~CSceneBase()
{
	//nullcheck
	if (m_pVtxBuff)
	{
		//���_�o�b�t�@�̊J��
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}
