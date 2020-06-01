// ------------------------------------------
//
// gametly�����̐���[main.h]
// Author : Fujiwara Masato
//
// ------------------------------------------

#ifndef _MAIN_H_
#define _MAIN_H_	 // �t�@�C������������߂�

// ------------------------------------------
// �C���N���[�h�t�@�C��
// ------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>	// �E�B���h�E�A�v���P�[�V����
#include "d3dx9.h"
#include <stdlib.h>		// �V�X�e���w�b�_�[
#include <stdio.h>		// ��ʓI�ȃw�b�_�[
#include <time.h>		// �^�C���w�b�_�[
#include <math.h>		// ���w�֐��w�b�_�[
#include <vector>
#define DIRECTINPUT_VERSION (0x0800)	// �x���Ώ��p
#include "dinput.h"						// ���͋@��p
#include "xaudio2.h"					// BGM

// ------------------------------------------
//
// ���C�u�����̃����N
//
// ------------------------------------------
#pragma comment(lib,"d3d9.lib")		// �`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")	// [d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")	// DirectX�R���|�[�l���g(���i)
#pragma comment (lib,"winmm.lib")
#pragma comment (lib, "dinput8.lib")

// ------------------------------------------
//
// �}�N���֐���`
//
// ------------------------------------------
// �Q�c�|���S�����_�t�H�[�}�b�g( ���_���W[2D] / ���_�J���[ / �e�N�X�`�����W )
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX2)
// 3�c�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / �@���x�N�g�� /���_�J���[ / �e�N�X�`�����W )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGHT (720)
#define INTERVAL_TIME (60 * 10)

// ------------------------------------------
//
// �\����
//
// ------------------------------------------
// �Q�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float       rhw;	// 1.0�ŌŒ�
	D3DCOLOR    col;	// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`���[
} VERTEX_2D;

// 3�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	// �@���x�N�g��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;		// �e�N�X�`���[
} VERTEX_3D;

// ------------------------------------------
//
// �O���錾
//
// ------------------------------------------
class CRenderer;

// ------------------------------------------
//
// �v���g�^�C�v�錾
//
// ------------------------------------------
#if _DEBUG
int GetFPS(void);
#endif // _DEBUG

#endif // !_MAIN_H_