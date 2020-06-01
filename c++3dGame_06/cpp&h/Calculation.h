// ����������������������������������������������������������������������
//
// Calculation�w�b�_�[�����̐���[calculation.h]
// Author : Fujiwara Masato
//
// ����������������������������������������������������������������������

#ifndef _CALCULATION_H_
#define _CALCULATION_H_	 // �t�@�C������������߂�

// ����������������������������������������������������������������������
//
// �C���N���[�h�t�@�C��
//
// ����������������������������������������������������������������������
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"

// ����������������������������������������������������������������������
//
// �}�N����`
//
// ����������������������������������������������������������������������

// ����������������������������������������������������������������������
//
// Calculation���
//
// ����������������������������������������������������������������������

// ����������������������������������������������������������������������
//
// �\���̒�`
//
// ����������������������������������������������������������������������

// ------------------------------------------
//
// ���O��`
//
// ------------------------------------------
// ���������s�̕����|�C���^�[
typedef const char * P_CST_CHAR;

typedef struct INTEGER2
{
	INTEGER2() {}
	INTEGER2(int X, int Y)
	{
		nMax = X;
		nMin = Y;
	}
	int nMax;
	int	nMin;
}INTEGER2, *PINTEGER2;

typedef struct STATUS_INFO
{
	STATUS_INFO() {}
	STATUS_INFO(float fsJumpforce, float	fsRateJumpforce, float fsRotforce, float fsRateRotforce)
	{
		fJumpforce		= fsJumpforce;		// �W�����v��
		fRateJumpforce	= fsRateJumpforce;	// �W�����v�͂̏㏸��
		fRotforce		= fsRotforce;		// ��]��
		fRateRotforce	= fsRateRotforce;	// ��]�͂̏㏸��
	}
	float	fJumpforce;				// �W�����v��
	float	fRateJumpforce;			// �W�����v�͂̏㏸��
	float	fRotforce;				// ��]��
	float	fRateRotforce;			// ��]�͂̏㏸��
} STATUS_INFO;

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------

class CCalculation
{
public:
	/* �֐� */
	// �����̌v�Z //

	static D3DXVECTOR3 Difference_Between(
		D3DXVECTOR3 posA,
		D3DXVECTOR3 posB);

	// �O�ς̌v�Z //
	static D3DXVECTOR3 Cross_product(
		D3DXVECTOR3 VecA,
		D3DXVECTOR3 VecB);

	// ���ς̌v�Z //
	static float Dot_product(
		D3DXVECTOR3 VecA,
		D3DXVECTOR3 VecB);

	// �l�p�`�͈͓̔��Ɏl�p�`�������Ă��邩�ǂ���
	static bool Cube_Juge(
		D3DXVECTOR3 pos0,
		D3DXVECTOR3 size0,
		D3DXVECTOR3 pos1,
		D3DXVECTOR3 size1
	);

	// ���ʂ͈͓̔��ɕ��ʂ������Ă��邩�ǂ���
	static bool Plane_Juge_XZ(
		D3DXVECTOR3 pos0,
		D3DXVECTOR3 size0,
		D3DXVECTOR3 pos1,
		D3DXVECTOR3 size1
	);

	// ���ʂ̏�ɕ��̂�����Ă��邩
	static bool Plane_GetOn(
		D3DXVECTOR3 pos0,
		D3DXVECTOR3 size0,
		D3DXVECTOR3 pos1,
		D3DXVECTOR3 size1
	);

	// �l�p�`�̒��ɓ����Ă��邩���Ȃ���
	static bool SquareBottom_Judg(
		D3DXVECTOR3 pos,
		D3DXVECTOR3 size,
		D3DXVECTOR3 rot,
		int			nBlock_W,
		int			nBlock_H,
		D3DXVECTOR3 worldpos
	);

	// �l�p�`�̒��ɓ����Ă��邩���Ȃ���
	static bool SquareSide_Judg(
		D3DXVECTOR3 pos,
		D3DXVECTOR3 size,
		D3DXVECTOR3 rot,
		int			nBlock_W,
		int			nBlock_H,
		D3DXVECTOR3 worldpos
	);

	// �~�̑����Z //
	static float Addition_Circle(
		float Length_x,
		float Length_y,
		float Length_z
	);

	// �~�̓����蔻�� //
	static bool Collision_Circle(
		D3DXVECTOR3 Me,
		float		fMeSize,
		D3DXVECTOR3 Opponent,
		float		fOppSize
	);

	// ��]�ʂ̏�� //
	static float Rot_One_Limit(
		float fRot);

	// �X�N���[�����W�����[���h���W�ɕϊ�
	static D3DXVECTOR3* CalcScreenToWorld(
		D3DXVECTOR3* pout,		// �}�E�X�|�C���g
		float Sx,				// �X�N���[��X���W
		float Sy,				// �X�N���[��Y���W
		float fZ,				// �ˉe��Ԃł�Z�l�i0�`1�j
		float Screen_w,			// �X�N���[���̉���
		float Screen_h,			// �X�N���[���̍���
		D3DXMATRIX* mtxView,	// �r���[�}�g���b�N�X
		D3DXMATRIX* mtxPrj		// �v���W�F�N�V�����}�g���b�N�X
	);	

	// �X�N���[�����W��XZ���ʂ̃��[���h���W��_�Z�o
	static D3DXVECTOR3* CalcScreenToXZ(
		D3DXVECTOR3* pout,		// �}�E�X�|�C���g
		float Sx,				// �X�N���[��X���W
		float Sy,				// �X�N���[��Y���W
		float Screen_w,			// �X�N���[���̉���
		float Screen_h,			// �X�N���[���̍���
		D3DXMATRIX* mtxView,	// �r���[�}�g���b�N�X
		D3DXMATRIX* mtxPrj,		// �v���W�F�N�V�����}�g���b�N�X
		D3DXVECTOR3 obj);		// �I�u�W�F�N�g�̈ʒu

	// ���[���h���W���X�N���[�����W�ɕϊ�(����)
	static D3DXVECTOR3* CalcWorldToScreen(
		D3DXVECTOR3* Obj,		// �I�u�W�F�N�g�̈ʒu
		float Sx,					// �X�N���[��X���W
		float Sy,					// �X�N���[��Y���W
		float fZ,				// �ˉe��Ԃł�Z�l�i0�`1�j
		float Screen_w,			// �X�N���[���̉���
		float Screen_h,			// �X�N���[���̍���
		D3DXMATRIX* mtxView,	// �r���[�}�g���b�N�X
		D3DXMATRIX* mtxPrj);	// �v���W�F�N�V�����}�g���b�N�X

	// �ꎟ�֐�
	static D3DXVECTOR2 Linear_function(
		D3DXVECTOR3 Apos,			// �n�_
		D3DXVECTOR3 Bpos);			// �I�_

	// 2�����̌�_(�A��������)
	static D3DXVECTOR3 TwoLine_Inse(
		D3DXVECTOR2 ALinear,	// ���@
		D3DXVECTOR2 BLinear);	// ���A

	// �r���̌v�Z
	static bool TlyCollision(
		D3DXVECTOR3 ObjectPos,
		D3DXVECTOR3,
		...
		);
	// �O�ς̓����蔻��
	static bool CrossCollision(
		D3DXVECTOR3 *ObjectPos,
		D3DXVECTOR3 *PosA,
		D3DXVECTOR3 *PosB,
		D3DXVECTOR3 *PosC
	);
protected:

private:
	/* �ϐ� */
};

// ����������������������������������������������������������������������
//
// �v���g�^�C�v�錾
//
// ����������������������������������������������������������������������

#endif