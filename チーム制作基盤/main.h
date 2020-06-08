//=========================================================================
//Author : Hnazawa
//[main.h]�E�B���h�E�\������
//=========================================================================
#ifndef _MAIN_H_
#define _MAIN_H_


#define _CRT_SECURE_NO_WARNINGS		// �x������
#define DIRECTINPUT_VERSION (0x0800)//�x���Ώ��p

#include <windows.h>
#include <stdio.h>
#include "d3dx9.h"
#include "dinput.h"
#include "xaudio2.h"
#include <Xinput.h>
#include <vector>
#include <iostream>
#include "SourceCode/hosso/HossoLibrary.h"
#include "SourceCode/ImGui/Imgui.h"
#include "SourceCode/ImGui/imgui_impl_dx9.h"
#include "SourceCode/ImGui/imgui_impl_win32.h"
#include "texture.h"
//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")		//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")	//[d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")	//DirectX�R���|�[�l���g�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")	//�V�X�e�����Ԏ擾�ɕK�v
#pragma comment(lib,"dinput8.lib")
#pragma comment (lib, "xinput.lib")

//�}�N����`
#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE| D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//�\���̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float rhm;			//1.0�ŌŒ�@�������W
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
	D3DXVECTOR3 bec;	//�x�N�g��
} VERTEX_2D;

typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_3D;

int GetFps(void);
//�O���錾�@�@Friend

//�v���g�^�C�v�錾

#endif