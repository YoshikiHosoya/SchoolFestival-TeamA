//------------------------------------------------------------------------------
//
//3D�L�����N�^�[����  [character_3D.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _CHARACTER_2D_H_
#define _CHARACTER_2D_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "character.h"
#include "scene2D.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CScene2D;

//�L�����N�^�[�̃N���X
class CCharacter_2D : public CCharacter
{
public:


	CCharacter_2D();
	virtual ~CCharacter_2D();

	virtual HRESULT Init();									//������
	virtual void Uninit();									//�I��
	virtual void Update();									//�X�V
	virtual void Draw();									//�`��
	virtual void ShowDebugInfo();							//�f�o�b�O���\�L
	virtual void DamageAction() = 0;						//�_���[�W�󂯂����̃��A�N�V����
	virtual void DeathAction() = 0;							//���S���̃��A�N�V����
	virtual void SetState(STATE nextstate);					//�X�e�[�g�ύX����
	void ShowCharacterInfo();
	virtual void Move();									//�ړ��֐�
	virtual void Rot();										//��]�֐�
	virtual void State();									//��Ԃɉ���������

	void SetScene2D(std::unique_ptr<CScene2D> pScene2D) { m_pScene2D = std::move(pScene2D); };
	CScene2D *GetScene2D() { return m_pScene2D.get(); };
protected:

	virtual void Collision();								//�����蔻��n�̏���
private:
	std::unique_ptr<CScene2D> m_pScene2D;

};
#endif