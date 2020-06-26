//------------------------------------------------------------------------------
//
//����ƂȂ郂�f������  [modelparts_weapon.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MODELPARTSWEAPON_H_
#define _MODELPARTSWEAPON_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "modelparts.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CCharacter;
class COrbit;
class CCollision;
class CMotion;

class CModelParts_Weapon : public CModelParts
{
public:
	CModelParts_Weapon();
	virtual ~CModelParts_Weapon();

	HRESULT Init();										//������
	void Uninit();										//�I��
	void Update();										//�X�V
	void Draw();										//�`��
	static std::unique_ptr<CModelParts_Weapon> Create(std::shared_ptr<CModelInfo> pModelInfo);		//��������
	void ShowDebugInfo();								//�f�o�b�O���\�L
	void StartAttack();									//�U���̊J�n
	void EndAttack();									//�U���̏I��
	void SetAttackInfo(CMotion::MOTION_TYPE motiontype);//�U���̏��X�V
	void ResetEnemyInvincible();						//�G�̖��G��ԉ����@���[�V�����؂�ւ�������ɔ���

	void SetHasCharacterPtr(std::shared_ptr<CCharacter> pCharacter) { m_pWeaponHasCharacter = std::weak_ptr<CCharacter>(pCharacter); };		//����������Ă���L�����N�^�[�ւ̃|�C���^
protected:

private:
	std::shared_ptr<COrbit> m_pOrbit;					//�O�Ղ̃|�C���^
	std::unique_ptr<CCollision> m_pCollision;			//�����蔻��̃|�C���^

	void Collision();

	int m_nDamage;										//�_���[�W
	int m_nBlueDamage;									//�_���[�W
	float m_fKnockBack_Front;							//�m�b�N�o�b�N��
	float m_fKnockBack_Up;								//�m�b�N�o�b�N��

	std::weak_ptr<CCharacter> m_pWeaponHasCharacter;	//����������Ă�L�����N�^�[�̃|�C���^

};
#endif