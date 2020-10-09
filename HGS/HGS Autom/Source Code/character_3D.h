//------------------------------------------------------------------------------
//
//3D�L�����N�^�[����  [character_3D.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _CHARACTER_3D_H_
#define _CHARACTER_3D_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "character.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CModelCharacter;
class CCollision;

//�L�����N�^�[�̃N���X
class CCharacter_3D : public CCharacter
{
public:


	CCharacter_3D();
	virtual ~CCharacter_3D();

	virtual HRESULT Init();									//������
	virtual void Uninit();									//�I��
	virtual void Update();									//�X�V
	virtual void Draw();									//�`��
	virtual void ShowDebugInfo();							//�f�o�b�O���\�L
	virtual void DamageAction() = 0;						//�_���[�W�󂯂����̃��A�N�V����
	virtual void DeathAction() = 0;							//���S���̃��A�N�V����
	virtual void SetState(STATE nextstate);					//�X�e�[�g�ύX����
	virtual void Move();									//�ړ��֐�
	virtual void Rot();										//��]�֐�
	virtual void State();									//��Ԃɉ���������
	void CreateModelCharacter(int type);
	void SetRotDest(D3DXVECTOR3 const &rotdest) { m_rotDest = rotdest; };										//��]�̌����ݒ�


	D3DXMATRIX		*GetMtx()								{ return &m_mtxWorld; };							//���[���h�}�g���b�N�X�擾
	CModelCharacter	*GetModelCharacterPtr()					{ return m_pModelCharacter.get(); };				//���f���L�����N�^�[���擾
	D3DXVECTOR3		 &GetRotDest()							{ return m_rotDest; };								//��]�̌����擾

	CMotion::MOTION_TYPE GetNowMotion();																		//���݂̃��[�V�����擾 �C���N���[�h����ĂȂ�����C�����C���s��
protected:

	void ShowCharacterInfo();								//�L�����N�^�[���\��
	void ChangeMotion(CMotion::MOTION_TYPE nextmotion);		//���[�V�����؂�ւ�
	bool ContinueAttack();									//�A���U��
	virtual void Collision();								//�����蔻��n�̏���
private:
	D3DXVECTOR3 m_rotDest;									//��]�̖ړI�n
	D3DXVECTOR3 m_rotDif;									//��]�̍���


	D3DXMATRIX m_mtxWorld;									//���[���h�}�g���b�N�X
	std::unique_ptr<CModelCharacter> m_pModelCharacter;		//���f���̃|�C���^

};
#endif