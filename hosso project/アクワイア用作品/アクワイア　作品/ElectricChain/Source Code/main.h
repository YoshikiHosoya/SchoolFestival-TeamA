//------------------------------------------------------------------------------
//
//���C������  [main.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#define	DIRECTINPUT_VERSION	(0x0800)

#ifndef _MAIN_H_
#define _MAIN_H_


//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include <stdlib.h>
#include <crtdbg.h>
#include <windows.h>
#include "d3dx9.h"
#include <vector>

#include "hossolibrary.h"

#include <iostream>
#include <memory>


//------------------------------------------------------------------------------
//���C�u�����̃����N
//------------------------------------------------------------------------------
#pragma comment(lib,"d3d9.lib")		//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")	//[d3dx9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")	//DirectX�R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")	//�V�X�e�����Ԏ擾�ɕK�v
#pragma comment(lib,"dinput8.lib")	//���͏����ɕK�v DirectInput
#pragma comment(lib,"xinput.lib")	//���͏����ɕK�v XInput

//------------------------------------------------------------------------------
//�}�N����`
//------------------------------------------------------------------------------
#define SCREEN_WIDTH	(1280)		//�E�B���h�E�̕�
#define SCREEN_HEIGHT	(720)		//�E�B���h�E�̍���
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)					// 2�c�|���S�����_�t�H�[�}�b�g( ���_���W[2D] / ���_�J���[ / �e�N�X�`�����W)
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)		// 3�c�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / �@�� / ���_�J���[ / �e�N�X�`�����W)



//------------------------------------------------------------------------------
//�\����
//------------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3	pos;	//���_���W
	float		rhw;	//1.0�ŌŒ�@�������W
	D3DCOLOR	col;	//���_�J���[
	D3DXVECTOR2	tex;	//�e�N�X�`�����W
} VERTEX_2D;

// 3�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	// �@���̃x�N�g��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_3D;



//�f�o�b�O�p
#ifdef _DEBUG
int			GetFPS(void);
#endif
#endif