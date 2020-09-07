#pragma once
//====================================================================
//
//���̏��� [Shield.h]
//Author : �̂肳��
//
//====================================================================
#ifndef _SHIELD_H_
#define _SHIELD_H_

//====================================================================
//�C���N���[�h�t�@�C��
//====================================================================
#include "main.h"
#include "model.h"
//====================================================================
//�O���錾
//====================================================================
//====================================================================
//�V�[���h
//====================================================================
class CWeakEnemy;

class CShield : public CModel , public CGameObject
{
public:
	CShield() {};
	CShield(OBJ_TYPE type);											// �R���X�g���N�^
	~CShield();														// �f�X�g���N�^

	HRESULT	Init();													// ������
	void	Uninit();												// �I��
	void	Update();												// �X�V
	void	Draw();													// �`��
	static	CShield	* Create();
	int		GetLife() { return m_nLife; };
	int		SetLife(int life) { m_nLife = life;};					//�̗͂̐ݒ�
	void	AddDamage(int nLIfe);
	void	SetHandMtx(D3DXMATRIX *pMtx) { m_HasHandMtx = pMtx; };
	void	SetHasEnemyPtr(CWeakEnemy *pEnemy) { m_HasEnemyPtr = pEnemy; };
	void	AwayShield();


	D3DXVECTOR3 GetShieldPos() { return m_ShieldPos; };

private:
	/* �����o�ϐ� */
	int					m_nLife;						// �̗�
	int					m_nCntState;					// �J�E���^
	int					m_nDeleteCnt;					// �����j�󂳂�Ă��������܂ł̃J�E���g
	D3DXVECTOR3			m_ShieldPos;					// ���̍��W�@�R���W�����p
	D3DXMATRIX			*m_HasHandMtx;					// ������̃}�g���b�N�X
	CWeakEnemy			*m_HasEnemyPtr;					// �����Ă�G�̃|�C���^
	bool				m_bBreak;						// �j����
	D3DXVECTOR3			m_BreakShieldMoveValue;			// �����j�󂳂ꂽ���̐�����ԕ���
	D3DXVECTOR3			m_BreakShieldRotValue;			// �����j�󂳂ꂽ���̉�]��

};
#endif
