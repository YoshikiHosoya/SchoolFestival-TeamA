//------------------------------------------------------------------------------
//
//�f�o�b�O���[��  [DebugRoom.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _TESTMODE_H_
#define _TESTMODE_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "../main.h"
#include "../basemode.h"
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------

class CDebug_Room : public CBaseMode
{
public:

	CDebug_Room();
	~CDebug_Room();
	HRESULT Init(HWND hWnd);								//������
	void Uninit();											//�I��
	void Update();											//�X�V
	void Draw();											//�`��
	void ShowDebugInfo();									//�f�o�b�O���\�L

	CPlayer* GetPlayer() { return nullptr; };		//�v���C���[�擾����

private:
};

#endif