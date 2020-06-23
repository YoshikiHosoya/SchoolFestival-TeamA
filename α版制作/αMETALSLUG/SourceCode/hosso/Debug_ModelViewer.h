//------------------------------------------------------------------------------
//
//���f���r���[���p����  [Debug_ModelViewer.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _DEBUG_MODELVIEWER_H_
#define _DEBUG_MODELVIEWER_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "../main.h"
#include "../BaseMode.h"

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CDebug_ViewerCharacter;

class CDebug_ModelViewer : public CBaseMode
{
public:

	CDebug_ModelViewer();
	~CDebug_ModelViewer();
	HRESULT Init();			//������
	void Uninit();						//�I��
	void Update();						//�X�V
	void Draw();						//�`��
	void ShowDebugInfo();				//�f�o�b�O���\�L
	CMap *GetMap();						//�}�b�v
	CPlayer* GetPlayer();				//�v���C���[�̃|�C���^�擾



private:
	bool m_bModel;
	CDebug_ViewerCharacter *m_pViewerCharacter;
};

#endif