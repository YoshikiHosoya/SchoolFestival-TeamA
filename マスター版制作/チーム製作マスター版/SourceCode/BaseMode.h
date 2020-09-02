#pragma once
//==========================================================
//�x�[�X���[�h����  [basemode.cpp]
//==========================================================
#ifndef _MODE_H_
#define _MODE_H_
//==========================================================
//�C���N���[�h
//==========================================================
#include "main.h"

//==========================================================
//�N���X��`
//==========================================================
//�O���錾
class CPlayer;
class CEnemy;
class CMap;
class CBaseMode
{
public:
	CBaseMode() {};
	virtual ~CBaseMode() {};

	virtual HRESULT		Init()								= 0;	//������
	virtual void		Uninit()							= 0;	//�I��
	virtual void		Update()							= 0;	//�X�V
	virtual void		Draw()								= 0;	//�`��
	virtual void		ShowDebugInfo()						= 0;	//�f�o�b�O���\�L
	virtual CPlayer*	GetPlayer(CONTROLLER Controller)	= 0;	//�v���C���[�̃|�C���^�擾
	virtual CMap*		GetMap()							= 0;	// �}�b�v�̃|�C���^�擾

	void				DebugCommand(void);		//�f�o�b�O�R�}���h
	static void			BaseLoad(HWND hWnd);	//�S�Ă̏�ʂŎg����ł��낤�f�ނ̐���
	static void			BaseUnload(void);		//�S�Ă̏�ʂŎg����ł��낤�f�ނ̔j��
private:
};

#endif