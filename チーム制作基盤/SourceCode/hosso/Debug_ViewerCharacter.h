//------------------------------------------------------------------------------
//
//�f�o�b�O�p�̃L�����N�^  [character.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _DEBUG_VIEWER_CHARACTER_H_
#define _DEBUG_VIEWER_CHARACTER_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "../../main.h"
#include "../../character.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CModelCharacter;

class CDebug_ViewerCharacter : public CCharacter
{
public:

	CDebug_ViewerCharacter();							//�R���X�g���N�^
	CDebug_ViewerCharacter(OBJ_TYPE type);
	~CDebug_ViewerCharacter();							//�f�X�g���N�^

	HRESULT Init();									//������
	void Uninit();									//�I��
	void Update();									//�X�V
	void Draw();									//�`��
	void ShowDebugInfo();							//�f�o�b�O���\�L
	static CDebug_ViewerCharacter* Create();		//�����֐�
	void DefaultMotion() { return SetMotion(CCharacter::PLAYER_MOTION_NORMAL); };

	void MotionViewer();							//���[�V�����r���[��
	void OffsetViewer();							//�I�t�Z�b�g�r���[��
private:
	bool ShowMotionComboBox(CCharacter::MOTION &motiontype);		//���[�V�����̃R���{�{�b�N�X

};
#endif