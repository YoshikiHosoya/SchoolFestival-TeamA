//------------------------------------------------------------------------------
//
//�f�o�b�O�p�̃L�����N�^  [character.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _DEBUG_CHARACTER_H_
#define _DEBUG_CHARACTER_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "../main.h"
#include "../character.h"
#include "../motion.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CModelCharacter;

class CDebug_Character : public CCharacter
{
public:

	CDebug_Character();								//�R���X�g���N�^
	~CDebug_Character();							//�f�X�g���N�^

	HRESULT Init();									//������
	void Uninit();									//�I��
	void Update();									//�X�V
	void Draw();									//�`��
	void ShowDebugInfo();							//�f�o�b�O���\�L
	void DamageAction() {};							//�_���[�W���̃��A�N�V����
	void DeathAction() {};							//���S���̃��A�N�V����
	void AttackTurning() {};						//�U�����̐���
	static std::shared_ptr<CDebug_Character> Create(MODEL_TYPE modeltype,CCharacter::PARAM_TYPE paramtype);		//�����֐�

private:
	bool ShowMotionComboBox(CMotion::MOTION_TYPE &motiontype);		//���[�V�����̃R���{�{�b�N�X

	void MotionViewer();		//���[�V�����r���[��
	void OffsetViewer();		//�I�t�Z�b�g�r���[��
};
#endif