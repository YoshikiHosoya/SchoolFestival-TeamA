//------------------------------------------------------------------------------
//
//�p�[�c�ƂȂ郂�f���̏���  [modelparts.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "modelparts.h"
#include "renderer.h"
#include "manager.h"

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CModelParts::CModelParts()
{
	//������
	m_pParentMtx = nullptr;
	m_nIndex = 0;
	m_nParent = 0;
	m_rot1F = ZeroVector3;
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CModelParts::~CModelParts()
{
	m_pParentMtx = nullptr;
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CModelParts::Init()
{
	//������
	CSceneX::Init();

	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CModelParts::Uninit()
{
	CSceneX::Uninit();
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CModelParts::Update()
{
	//���݂̉�]�擾
	D3DXVECTOR3 &rRot = GetRot();

	//��]�ɉ��Z
	rRot += m_rot1F;

	//3.14�ȓ��ɂ���
	CHossoLibrary::CalcRotation(rRot.y);

	//���_�̏ꍇ
	if (m_nIndex == 0)
	{
		//���_�̍��W�X�V
		D3DXVECTOR3 &rPos = GetPos();
		rPos.y += m_fHeight1F;
	}

	//�X�V
	CSceneX::Update();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CModelParts::Draw()
{
	//�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�}�g���b�N�X���
	D3DXMATRIX			mtxShadow;		//�e�̃��[���h�}�g���b�N�X
	D3DXMATRIX			DrawMtx;		//�`��p�̃��[���h�}�g���b�N�X

	//�}�g���b�N�X�v�Z
	CHossoLibrary::CalcMatrix(GetMtxWorldPtr(), GetPos(), GetRot());

	//�e�̏��������
	D3DXMatrixMultiply(GetMtxWorldPtr(), GetMtxWorldPtr(), m_pParentMtx);

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
}

//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CModelParts::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}

//------------------------------------------------------------------------------
//�e�̃}�g���b�N�X�ݒ�
//------------------------------------------------------------------------------
void CModelParts::SetParentMtx(D3DXMATRIX *pParentMtx)
{
	m_pParentMtx = pParentMtx;
}

//------------------------------------------------------------------------------
//�����ȏ��Z�b�g
//------------------------------------------------------------------------------
void CModelParts::SetPartsInfo(int nIndex, int nParent, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CSceneX::SetPos(pos);
	CSceneX::SetRot(rot);
	m_nParent = nParent;
	m_nIndex = nIndex;
}

//------------------------------------------------------------------------------
//����
//------------------------------------------------------------------------------
std::unique_ptr<CModelParts> CModelParts::Create(std::shared_ptr<CModelInfo> pModelInfo)
{
	//�������m��
	std::unique_ptr<CModelParts> pModelParts(new CModelParts);

	//������
	pModelParts->Init();

	//���f���ݒ�
	pModelParts->BindModelInfo(pModelInfo);

	//�����������
	return std::move(pModelParts);
}
//------------------------------------------------------------------------------
//��]�̍s���ݒ�
//------------------------------------------------------------------------------
void CModelParts::SetMotionRotDest(CMotion::MOTION_TYPE motiontype, int nKey)
{
	//�ϐ��錾
	D3DXVECTOR3 rotDest = CMotion::GetRotDest(motiontype, nKey,m_nIndex);		//��]�̍s��
	D3DXVECTOR3 rot = GetRot();													//���݂̉�]�l
	int nFrame = CMotion::GetFrame(motiontype, nKey);							//������t���[����

	//�����v�Z
	D3DXVECTOR3 rotDif = rotDest - rot;

	//3.14�ȓ��ɂ���
	CHossoLibrary::CalcRotation(rotDif.y);

	//1F������̉�]�ʂ��擾
	m_rot1F = rotDif / (float)nFrame;
}
//------------------------------------------------------------------------------
//��]�̍s��ɉ�]
//------------------------------------------------------------------------------
void CModelParts::SetForcedRot(CMotion::MOTION_TYPE motiontype, int nKey)
{
	//��]�ʐݒ�
	CSceneX::SetRot(CMotion::GetRotDest(motiontype, nKey, m_nIndex));
}

//------------------------------------------------------------------------------
//���_��1F������̈ړ�
//------------------------------------------------------------------------------
void CModelParts::SetMotionPosDest(CMotion::MOTION_TYPE motiontype, int nKey)
{
	//�ϐ��錾
	float fHeightDest = CMotion::GetOriginHeight(motiontype, nKey);				//��]�̍s��
	float fNowHeight = GetPos().y;												//���݂̉�]�l
	int nFrame = CMotion::GetFrame(motiontype, nKey);							//������t���[����

	//�����v�Z
	float fHeightDif = fHeightDest - fNowHeight;

	//1F������̉�]�ʂ��擾
	m_fHeight1F = fHeightDif / (float)nFrame;
}

//------------------------------------------------------------------------------
//��]�̍s��ɉ�]
//------------------------------------------------------------------------------
void CModelParts::SetForcedPos(CMotion::MOTION_TYPE motiontype, int nKey)
{
	//���_�̍����擾���Đݒ�
	CSceneX::SetPos(D3DXVECTOR3(GetPos().x, (CMotion::GetOriginHeight(motiontype, nKey)), GetPos().z));
}