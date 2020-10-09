//------------------------------------------------------------------------------
//
//�p�[�c�ƂȂ郂�f���̏���  [modelparts.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "model_object.h"
#include "renderer.h"
#include "manager.h"
#include "collision.h"
#include "modelinfo.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CModel_Object::CModel_Object()
{
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CModel_Object::~CModel_Object()
{

}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CModel_Object::Init()
{
	//������
	CSceneX::Init();

	//���f���ݒ�
	CSceneX::BindModelInfo(CModelInfo::GetModelInfo(CModelInfo::MODEL_MAPOBJECT_WALL));

	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CModel_Object::Uninit()
{
	CSceneX::Uninit();
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CModel_Object::Update()
{
	//�X�V
	CSceneX::Update();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CModel_Object::Draw()
{
	//�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�}�g���b�N�X���
	D3DXMATRIX			mtxShadow;		//�e�̃��[���h�}�g���b�N�X
	D3DXMATRIX			DrawMtx;		//�`��p�̃��[���h�}�g���b�N�X

	//�t�H�OON
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_FOG_ON);

	//�}�g���b�N�X�v�Z
	CHossoLibrary::CalcMatrix(GetMtxWorldPtr(), GetPos(), GetRot());

	//���f���̕`��
	CSceneX::DrawMesh();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxShadow);

	//���f���̃��[���h���W�擾
	pDevice->GetTransform(D3DTS_WORLD, &DrawMtx);

	//�e�̃}�g���b�N�X�v�Z
	CHossoLibrary::CalcShadowMatrix(mtxShadow, D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	//�`��p�̃}�g���b�N�X�ɂ������킹��
	D3DXMatrixMultiply(&DrawMtx, &DrawMtx, &mtxShadow);

	//���f�����W���烏�[���h���W�ɐݒ�
	pDevice->SetTransform(D3DTS_WORLD, &DrawMtx);

	//�e�̕`��
	CSceneX::DrawShadow();

	//�t�H�OOFF
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_FOG_OFF);
}

//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CModel_Object::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}

//------------------------------------------------------------------------------
//����
//------------------------------------------------------------------------------
void CModel_Object::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	//�������m��
	std::shared_ptr<CModel_Object> pModelObject(new CModel_Object);

	//������
	pModelObject->Init();

	//���ݒ�
	pModelObject->SetPos(pos);
	pModelObject->SetRot(rot);

	//�R���W��������
	pModelObject->m_pCollision = CCollision::Create(pModelObject->GetMtxWorldPtr(), CCollision::COLLISION_OBJECT);

	//�}�g���b�N�X�v�Z
	CHossoLibrary::CalcMatrix(pModelObject->GetMtxWorldPtr(), ZeroVector3, pModelObject->GetRot());

	//���f���̒��_�ݒ�
	MODEL_VTX modelVtx;
	//CHossoLibrary::SetModelVertex(modelVtx, *pModelObject->pModelInfo.get());

	//�R���W�����̑傫���ݒ�
	pModelObject->m_pCollision->SetCollisionVtx(modelVtx);

	//�I�u�W�F�N�g�^�C�v�ݒ�
	pModelObject->SetObjType(OBJTYPE_MAPOBJECT);
	pModelObject->AddSharedList(pModelObject);
}