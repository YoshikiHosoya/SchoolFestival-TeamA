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
#include "../main.h"
#include "../character.h"
#include "../ModelSet.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CGun;
class CKnife;

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
	void DebugInfo();								//�f�o�b�O���\�L
	static CDebug_ViewerCharacter* Create();		//�����֐�
	bool DefaultMotion() { GetModelSet()->GetMotion() = false; GetModelSet()->GetKeySet()--; return false; };

	void MotionViewer();							//���[�V�����r���[��
private:
	bool ShowMotionComboBox(CModelSet::CHARACTER_MOTION_STATE &motiontype);		//���[�V�����̃R���{�{�b�N�X

	void AddKeyInfo(CModelSet::MOTION *pMotion);
	void PopbackKeyInfo(CModelSet::MOTION *pMotion);
	void ResetKey();
	void CopyMotionPaste(CModelSet::CHARACTER_MOTION_STATE CopyMotionType, int nCopyKey, CModelSet::CHARACTER_MOTION_STATE NowMotion, int nNowKey);
	HRESULT SaveMotion(CModelSet::CHARACTER_MOTION_STATE motiontype);

	CGun *m_pGun;				//�i�C�t�e�|�C���^
	CKnife *m_pKnife;			//�i�C�t�̃|�C���^
};
#endif