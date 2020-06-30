//------------------------------------------------------------------------------
//
//�����蔻�菈��  [collision.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "collision.h"
#include "manager.h"
#include "renderer.h"
#include "meshcylinder.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CCollision::CCollision()
{
	//������
	m_ModelVtx.VtxMax = ZeroVector3;
	m_ModelVtx.VtxMin = ZeroVector3;
	m_fRadius = 0.0f;
	m_fLength = 0.0f;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CCollision::~CCollision()
{
#ifdef  _DEBUG

	if (m_pDebugMesh)
	{
		m_pDebugMesh->Release();
		m_pDebugMesh.reset();
	}
#endif //  _DEBUG
}

//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CCollision::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}
//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
std::unique_ptr<CCollision> CCollision::Create(D3DXMATRIX * pMtx, COLLISION_TYPE ColisionType)
{
	//�ϐ��錾
	std::unique_ptr<CCollision> pCollision(new CCollision);

	//nullcheck
	if (pCollision)
	{
		//���̃}�g���b�N�X�擾
		pCollision->m_pParentMtx = pMtx;

		switch (ColisionType)
		{
		case CCollision::COLLISION_CHARACTER:
		case CCollision::COLLISION_WEAPON:
#ifdef _DEBUG
			//���b�V������
			pCollision->CreateMesh();
#endif // _DEBUG
			break;
		}

		//�����������
		return pCollision;
	}
	return nullptr;
}

//------------------------------------------------------------------------------
//���ݒ�
//------------------------------------------------------------------------------
void CCollision::SetCollisionInfo(float fRadius, float fLength)
{
	//�����
	m_fRadius = fRadius;
	m_fLength = fLength;

	//�ŏ����_�ƍő咸�_�ݒ�
	m_ModelVtx.VtxMax = D3DXVECTOR3(fRadius, fLength, fRadius);
	m_ModelVtx.VtxMin = D3DXVECTOR3(-fRadius, 0.0f, -fRadius);

#ifdef  _DEBUG

	if (m_pDebugMesh)
	{
		//���_���Đݒ�
		m_pDebugMesh->ResetVtx(D3DXVECTOR3(m_fRadius, m_fLength * 0.5f, m_fRadius));
	}
#endif //_DEBUG
}
//------------------------------------------------------------------------------
//���ݒ�
//------------------------------------------------------------------------------
void CCollision::SetCollisionVtx(MODEL_VTX & modelVtx)
{
	m_ModelVtx = modelVtx;
}
//------------------------------------------------------------------------------
//�V�����_�[�̓����蔻�菈��
//------------------------------------------------------------------------------
bool CCollision::CollisionCylinder(CCollision * pTargetCollision)
{
	//���a�̘a
	float fSumRadius = m_fRadius + pTargetCollision->m_fRadius;

	//���ꂼ��̎n�_�ƏI�_,�n�_����I�_�ւ̃x�N�g��
	D3DXVECTOR3 posStart1, posStart2, posEnd1, posEnd2, vecStart_End1, vecStart_End2;

	//�n�_
	posStart1 = D3DXVECTOR3(m_pParentMtx->_41, m_pParentMtx->_42, m_pParentMtx->_43);
	posStart2 = D3DXVECTOR3(pTargetCollision->m_pParentMtx->_41, pTargetCollision->m_pParentMtx->_42, pTargetCollision->m_pParentMtx->_43);

	//�I�_
	D3DXVec3TransformCoord(&posEnd1, &D3DXVECTOR3(0.0f, m_fLength, 0.0f), m_pParentMtx);
	D3DXVec3TransformCoord(&posEnd2, &D3DXVECTOR3(0.0f, pTargetCollision->m_fLength, 0.0f), pTargetCollision->m_pParentMtx);

	//���ꂼ��̎n�_����I�_�ւ̃x�N�g��
	vecStart_End1 = posEnd1 - posStart1;
	vecStart_End2 = posEnd2 - posStart2;

	//���K��
	D3DXVec3Normalize(&vecStart_End1, &vecStart_End1);
	D3DXVec3Normalize(&vecStart_End2, &vecStart_End2);

	//�@��
	D3DXVECTOR3 nor;
	D3DXVec3Cross(&nor, &vecStart_End1, &vecStart_End2);

	//���K��
	D3DXVec3Normalize(&nor, &nor);

	//���ꂼ��̎n�_����n�_�ւ̃x�N�g��
	D3DXVECTOR3 vec1_2 = posStart2 - posStart1;
	D3DXVECTOR3 vec2_1 = posStart1 - posStart2;

	//�ŒZ����
	float fCollisionLength = fabsf(D3DXVec3Dot(&nor, &vec1_2));

	//�n�_����I�_�@�Ɓ@�n�_����n�_�@�̓���
	float fDotDirection = D3DXVec3Dot(&vecStart_End1, &vec1_2);

	//X����Z���݂̂ł݂����̋����@���ꂼ��̎n�_
	float f2DDirection = D3DXVec2Length(&D3DXVECTOR2(vec1_2.x, vec1_2.z));

	//Y���Ō������@�Ώۂ̃V�����_�[�̊ԂɎ����̎n�_���I�_�������Ă�����
	if ((posStart2.y <= posStart1.y && posEnd2.y >= posStart1.y) || (posStart2.y <= posEnd1.y && posEnd2.y >= posEnd1.y))
	{
		//���a�̘a�ƍŒZ�������r && ���ςƔ��a�̘a���O�ȏ� && X����Z���ł݂����̋��������̒��������Z���ꍇ
		if (fCollisionLength < fSumRadius && fDotDirection + pTargetCollision->m_fRadius > 0 && f2DDirection < m_fLength)
		{
#ifdef _DEBUG
			//HIT
			CDebugProc::Print(CDebugProc::PLACE_LEFT, "HIT\n");

			//���b�V���̐F
			m_pDebugMesh->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.7f));

#endif //_DEBUG
			return true;

		}
	}
#ifdef _DEBUG

	//�������ĂȂ����͒ʏ�F
	m_pDebugMesh->SetCol(D3DXCOLOR(0.0f, 0.3f, 1.0f, 0.3f));
#endif //_DEBUG

	return false;

}

//------------------------------------------------------------------------------
//�L�����N�^�[���m�̔��� X��Z�̒l�̂ݎg��
//------------------------------------------------------------------------------
bool CCollision::CollisionCharacter(CCollision * pTargetCollision, D3DXVECTOR3 *pOut)
{
	//���W�擾
	//�Q�ƂŖႤ
	D3DXVECTOR2 &rMyPos = D3DXVECTOR2(m_pParentMtx->_41, m_pParentMtx->_43);
	D3DXVECTOR2 &rTargetPos = D3DXVECTOR2(pTargetCollision->m_pParentMtx->_41, pTargetCollision->m_pParentMtx->_43);

	//��������^�[�Q�b�g�Ɍ������x�N�g��
	D3DXVECTOR2 Vec_My_Target = rTargetPos - rMyPos;

	//��������^�[�Q�b�g�܂ł̋���
	float fLength = D3DXVec2Length(&Vec_My_Target);

	//���a�̘a
	float fSumRadius = (m_fRadius * 1.2f) + pTargetCollision->m_fRadius;

	//���a�̘a�Ƌ����𑪂�
	//���a�̘a��苗�����Z�������ꍇ
	if (fSumRadius > fLength)
	{
		//�p�x
		float fAngle = atan2f(Vec_My_Target.x, Vec_My_Target.y);

		//�ړ���̍��W�ݒ�
		pOut->x = rMyPos.x + sinf(fAngle) * fSumRadius;
		pOut->z = rMyPos.y + cosf(fAngle) * fSumRadius;

		//true
		return true;
	}

	//false
	return false;
}
//------------------------------------------------------------------------------
//�����p�̔���@���a���g��������
//------------------------------------------------------------------------------
bool CCollision::CollisionExplosion(CCollision * pTargetCollision)
{
	//���W�擾
	//�Q�ƂŖႤ
	D3DXVECTOR2 &rMyPos = D3DXVECTOR2(m_pParentMtx->_41, m_pParentMtx->_43);
	D3DXVECTOR2 &rTargetPos = D3DXVECTOR2(pTargetCollision->m_pParentMtx->_41, pTargetCollision->m_pParentMtx->_43);

	//��������^�[�Q�b�g�Ɍ������x�N�g��
	D3DXVECTOR2 Vec_My_Target = rTargetPos - rMyPos;

	//��������^�[�Q�b�g�܂ł̋���
	float fLength = fabsf(D3DXVec2Length(&Vec_My_Target));

	//���a�̘a
	float fSumRadius = m_fRadius + pTargetCollision->m_fRadius;

	//���a�̘a�Ƌ����𑪂�
	//���a�̘a��苗�����Z�������ꍇ
	if (fSumRadius > (fLength))
	{
		return true;
	}
	return false;

}

//-----------------------------------------------------------------------------
// ���f���̓����蔻�菈��
//-----------------------------------------------------------------------------
bool CCollision::CollisionObject(CCollision * pTargetCollision, D3DXVECTOR3 &rPos, D3DXVECTOR3 &rPosOld, D3DXVECTOR3 & rMove)
{
	//�Q�ƂŖႤ
	D3DXVECTOR3 &rMyPos = rPos;
	D3DXVECTOR3 &rTargetPos = D3DXVECTOR3(pTargetCollision->m_pParentMtx->_41, pTargetCollision->m_pParentMtx->_42, pTargetCollision->m_pParentMtx->_43);

	//��ɂ̂�����
	bool bLand = false;

	//�킩��₷�����邽��
	MODEL_VTX &rObjectVtx = pTargetCollision->m_ModelVtx;

	//�u���b�N�̕��̒����ǂ���
	if (rTargetPos.x + rObjectVtx.VtxMax.x > rMyPos.x + m_ModelVtx.VtxMin.x &&
		rTargetPos.x + rObjectVtx.VtxMin.x < rMyPos.x + m_ModelVtx.VtxMax.x &&
		rTargetPos.y + rObjectVtx.VtxMax.y > rMyPos.y &&
		rTargetPos.y + rObjectVtx.VtxMin.y < rMyPos.y + m_ModelVtx.VtxMax.y)
	{
		//�u���b�N�̉���
		if (rTargetPos.z + rObjectVtx.VtxMax.z <= rPosOld.z + m_ModelVtx.VtxMin.z &&
			rTargetPos.z + rObjectVtx.VtxMax.z > rMyPos.z + m_ModelVtx.VtxMin.z)
		{
			rMyPos.z = rTargetPos.z + rObjectVtx.VtxMax.z + m_ModelVtx.VtxMax.z;
			rMove.z = 0.0f;
		}

		//�u���b�N�̎�O
		else if (rTargetPos.z + rObjectVtx.VtxMin.z >= rPosOld.z + m_ModelVtx.VtxMax.z &&
				rTargetPos.z + rObjectVtx.VtxMin.z < rMyPos.z + m_ModelVtx.VtxMax.z)
		{
			rMyPos.z = rTargetPos.z + rObjectVtx.VtxMin.z + m_ModelVtx.VtxMin.z;
			rMove.z = 0.0f;
		}
	}
	if (rTargetPos.z +rObjectVtx.VtxMax.z > rMyPos.z + m_ModelVtx.VtxMin.z &&
		rTargetPos.z +rObjectVtx.VtxMin.z < rMyPos.z + m_ModelVtx.VtxMax.z &&
		rTargetPos.y +rObjectVtx.VtxMax.y > rMyPos.y &&
		rTargetPos.y +rObjectVtx.VtxMin.y < rMyPos.y + m_ModelVtx.VtxMax.y)
	{
		//�����ɂԂ���
		if (rTargetPos.x +rObjectVtx.VtxMax.x <= rPosOld.x + m_ModelVtx.VtxMin.x &&
			rTargetPos.x +rObjectVtx.VtxMax.x > rMyPos.x + m_ModelVtx.VtxMin.x)
		{
			rMyPos.x = rTargetPos.x + rObjectVtx.VtxMax.x + m_ModelVtx.VtxMax.x;
			rMove.x = 0.0f;
		}
		//�E���ɂԂ���
		else if (rTargetPos.x + rObjectVtx.VtxMin.x >= rPosOld.x + m_ModelVtx.VtxMax.x &&
				 rTargetPos.x + rObjectVtx.VtxMin.x < rMyPos.x + m_ModelVtx.VtxMax.x)
		{
			rMyPos.x = rTargetPos.x + rObjectVtx.VtxMin.x + m_ModelVtx.VtxMin.x;
			rMove.x = 0.0f;
		}
	}

	//��ɏ��
	if (rTargetPos.x + rObjectVtx.VtxMax.x > rMyPos.x + m_ModelVtx.VtxMin.x &&
		rTargetPos.x + rObjectVtx.VtxMin.x < rMyPos.x + m_ModelVtx.VtxMax.x &&
		rTargetPos.z + rObjectVtx.VtxMax.z> rMyPos.z + m_ModelVtx.VtxMin.z &&
		rTargetPos.z + rObjectVtx.VtxMin.z < rMyPos.z + m_ModelVtx.VtxMax.z)
	{
		//��ɏ��
		if (rTargetPos.y + rObjectVtx.VtxMax.y <= rPosOld.y && rTargetPos.y + rObjectVtx.VtxMax.y > rMyPos.y)
		{

			rMyPos.y = rTargetPos.y + rObjectVtx.VtxMax.y;
			rMove.y = 0.0f;

			bLand = true;
		}
	}
	return bLand;

}
//-----------------------------------------------------------------------------
//�J�����ƕǂƂ̔���
//-----------------------------------------------------------------------------
bool CCollision::CollisionObjectToCamera(CCollision * pTargetCollision, D3DXVECTOR3 & rPos, D3DXVECTOR3 & rPosOld)
{
	//�Q�ƂŖႤ
	D3DXVECTOR3 &rMyPos = rPos;
	D3DXVECTOR3 &rTargetPos = D3DXVECTOR3(pTargetCollision->m_pParentMtx->_41, pTargetCollision->m_pParentMtx->_42, pTargetCollision->m_pParentMtx->_43);

	//��ɂ̂�����
	bool bHit = false;

	//�킩��₷�����邽��
	MODEL_VTX &rObjectVtx = pTargetCollision->m_ModelVtx;

	//�u���b�N�̕��̒����ǂ���
	if (rTargetPos.x + rObjectVtx.VtxMax.x > rMyPos.x + m_ModelVtx.VtxMin.x &&
		rTargetPos.x + rObjectVtx.VtxMin.x < rMyPos.x + m_ModelVtx.VtxMax.x &&
		rTargetPos.y + rObjectVtx.VtxMax.y * 15> rMyPos.y &&
		rTargetPos.y + rObjectVtx.VtxMin.y < rMyPos.y + m_ModelVtx.VtxMax.y)
	{
		//�u���b�N�̉���
		if (rTargetPos.z + rObjectVtx.VtxMax.z <= rPosOld.z + m_ModelVtx.VtxMin.z &&
			rTargetPos.z + rObjectVtx.VtxMax.z > rMyPos.z + m_ModelVtx.VtxMin.z)
		{
			rMyPos.z = rTargetPos.z + rObjectVtx.VtxMax.z + m_ModelVtx.VtxMax.z;
			bHit = true;
		}

		//�u���b�N�̎�O
		else if (rTargetPos.z + rObjectVtx.VtxMin.z >= rPosOld.z + m_ModelVtx.VtxMax.z &&
			rTargetPos.z + rObjectVtx.VtxMin.z < rMyPos.z + m_ModelVtx.VtxMax.z)
		{
			rMyPos.z = rTargetPos.z + rObjectVtx.VtxMin.z + m_ModelVtx.VtxMin.z;
			bHit = true;
		}
	}
	if (rTargetPos.z + rObjectVtx.VtxMax.z > rMyPos.z + m_ModelVtx.VtxMin.z &&
		rTargetPos.z + rObjectVtx.VtxMin.z < rMyPos.z + m_ModelVtx.VtxMax.z &&
		rTargetPos.y + rObjectVtx.VtxMax.y * 15 > rMyPos.y &&
		rTargetPos.y + rObjectVtx.VtxMin.y < rMyPos.y + m_ModelVtx.VtxMax.y)
	{
		//�����ɂԂ���
		if (rTargetPos.x + rObjectVtx.VtxMax.x <= rPosOld.x + m_ModelVtx.VtxMin.x &&
			rTargetPos.x + rObjectVtx.VtxMax.x > rMyPos.x + m_ModelVtx.VtxMin.x)
		{
			rMyPos.x = rTargetPos.x + rObjectVtx.VtxMax.x + m_ModelVtx.VtxMax.x;
			bHit = true;
		}
		//�E���ɂԂ���
		else if (rTargetPos.x + rObjectVtx.VtxMin.x >= rPosOld.x + m_ModelVtx.VtxMax.x &&
			rTargetPos.x + rObjectVtx.VtxMin.x < rMyPos.x + m_ModelVtx.VtxMax.x)
		{
			rMyPos.x = rTargetPos.x + rObjectVtx.VtxMin.x + m_ModelVtx.VtxMin.x;
			bHit = true;
		}
	}
	return bHit;
}

#ifdef  _DEBUG
//------------------------------------------------------------------------------
//�V�����_�[����
//------------------------------------------------------------------------------
void CCollision::CreateMesh()
{
	//���b�V������
	m_pDebugMesh = CMeshCylinder::Create(ZeroVector3, D3DXVECTOR3(m_fRadius, m_fLength * 0.5f, m_fRadius), { 10,2 }, m_pParentMtx);

	//nullcheck
	if (m_pDebugMesh)
	{
		//�p�����[�^�ݒ�
		m_pDebugMesh->SetCol(D3DXCOLOR(0.0f, 0.3f, 1.0f, 0.3f));
		m_pDebugMesh->SetTex(false);
	}

}
#endif //_DEBUG