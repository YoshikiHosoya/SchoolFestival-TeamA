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
class CModel;

class CDebug_ModelViewer : public CBaseMode
{
public:

	CDebug_ModelViewer();
	~CDebug_ModelViewer();
	HRESULT Init();								//������
	void Uninit();								//�I��
	void Update();								//�X�V
	void Draw();								//�`��
	void ShowDebugInfo();						//�f�o�b�O���\�L

	CMap *GetMap() { return nullptr; };			//�}�b�v
	CPlayer* GetPlayer() { return nullptr; };	//�v���C���[�̃|�C���^�擾


	static void OffsetViewer(std::vector<CModel*> vModelList);
	static HRESULT SaveModelOffset(std::vector<CModel*> vModelList);
private:
	bool m_bModel;
	CDebug_ViewerCharacter *m_pViewerCharacter;
};

#endif