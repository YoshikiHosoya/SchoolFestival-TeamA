//------------------------------------------------------------------------------
//
//���C�u��������  [hossolibrary.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _HOSSOLIBRARY_H_
#define _HOSSOLIBRARY_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "texture.h"
#include "Debug/debugproc.h"
#include "ImGui/Imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define ZeroVector4			(D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f))		//�������p
#define ZeroVector3			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))				//�������p
#define ZeroVector2			(D3DXVECTOR2(0.0f, 0.0f))					//�������p
#define ZeroColor			(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f))			//����
#define WhiteColor			(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))			//��
#define RedColor			(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f))			//��
#define GreenColor			(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f))			//��
#define BlueColor			(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f))			//��
#define YellowColor			(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))			//��
#define OrangeColor			(D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f))			//��
#define BlackColor			(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f))			//��

#define MAX_TEXT			(128)
#define SCREEN_CENTER_POS	(D3DXVECTOR3(SCREEN_WIDTH * 0.5f , SCREEN_HEIGHT * 0.5f ,0.0f))			//��ʒ����̍��W
#define SCREEN_SIZE			(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT,0.0f))							//��ʂ̃T�C�Y
#define NEWLINE				("\n")																	//���s
#define COMMENT01			("//\n")																//�e�L�X�g�p�@�R�����g�@���s
#define COMMENT02			("//------------------------------------------------------------\n")	//�e�L�X�g�p�@��
#define EQUAL				("=")																	//�e�L�X�g�p�@�C�R�[��

//------------------------------------------------------------------------------
//�\���̒�`
//------------------------------------------------------------------------------
//int�^���i�[�ł���
typedef struct INTEGER2
{
	int x;
	int y;

	//�R���X�g���N�^
	INTEGER2() {};
	INTEGER2(int nX, int nY)
	{
		x = nX;
		y = nY;
	}

}INTEGER2;

//int�^��3�i�[�ł���
typedef struct INTEGER3
{
	int x;
	int y;
	int z;

	//�R���X�g���N�^
	INTEGER3() {};
	INTEGER3(int nX, int nY,int nZ)
	{
		x = nX;
		y = nY;
		z = nZ;
	}
}INTEGER3;

//int�^��3�i�[�ł���
typedef struct MODEL_VTX
{
	D3DXVECTOR3 VtxMax;	//�ő咸�_
	D3DXVECTOR3 VtxMin;	//�ŏ����_

	//�R���X�g���N�^
	MODEL_VTX() {};
	MODEL_VTX(D3DXVECTOR3 MinSize, D3DXVECTOR3 MaxSize)
	{
		VtxMin = MinSize;
		VtxMax = MaxSize;
	};

}MODEL_VTX;

// �^�O
enum class TAG
{
	NONE = -1,
	PLAYER_1,			// �v���C���[1
	PLAYER_2,			// �v���C���[2
	ENEMY,				// �G
	PRISONER,			// �ߗ�
	OBSTACLE,			// �I�u�W�F�N�g
	SHIELD,				// ��
};

enum class DIRECTION
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
};

//------------------------------------------------------------------------------
//�G�C���A�X�錾
//------------------------------------------------------------------------------
using FILENAME_LIST = std::vector<std::string>;		//�t�@�C�����̃��X�g

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CKeyboard;
class CPad_XInput;
class CModelInfo;


class CHossoLibrary
{
public:

	//���͂̎��
	enum INPUTTYPE
	{
		PRESS = 0,	//�v���X
		TRIGGER,	//�g���K�[
		MAX
	};

	//����
	enum DIRECTION
	{
		NONE = -1,
		UP,			//��
		DOWN,		//��
		LEFT,		//��
		RIGHT		//��
	};

	static bool CheckMove(DIRECTION);								//�ړ��p�֐�(AWSD + CrossKey) Press
	static DIRECTION CheckSelect();									//�Z���N�g�p�֐�(AWSD + ARROW + LStick) Trigger

	static bool CheckJump(INPUTTYPE type);							//�W�����v�{�^��
	static bool CheckDash(INPUTTYPE type);							//�_�b�V���{�^��
	static bool CheckCameraReset(INPUTTYPE type);					//�J�������Z�b�g�{�^��
	static bool CheckDecision();									//����{�^��
	static bool CheckSkipTutorial();								//�`���[�g���A���X�L�b�v
	static bool CheckCancel();										//�L�����Z���{�^��
	static bool CheckPause();										//�|�[�Y
	static bool CheckAnyButton();									//�����{�^�����B�B
	static void ResetStickInfo();									//�X�e�B�b�N�̃g���K�[��񃊃Z�b�g

	static D3DXCOLOR RandomColor();

	static bool Check3DMoveStick(D3DXVECTOR3 &Move, float const fMove,float const fCameraRot,float &fRotGoal);	//3D�p�@LStick�@�ړ��ʌv�Z
	static bool Check3DCameraStick(D3DXVECTOR3 &Rot,float fHolizonMove,float fVerticalMove);					//3D�p�@RStick�@�ړ��ʌv�Z

	static void StartVibration(int nCntVibration);					//�o�C�u���[�V��������

	static float Vec2Cross(D3DXVECTOR2 const &rVecA, D3DXVECTOR2 const &rVecB);									//2D �O�όv�Z
	static void CalcMatrix(D3DXMATRIX *pMtx,D3DXVECTOR3 const &rPos, D3DXVECTOR3 const &rRot);					//���[���h�}�g���b�N�X�v�Z
	static void CalcShadowMatrix(D3DXMATRIX &rShadowMtx, D3DXVECTOR3 const &rPos, D3DXVECTOR3 const &rNor);		//�V���h�[�}�g���b�N�X�̌v�Z
	static void SetModelVertex(MODEL_VTX &pModelVtx, CModelInfo &pModelInfo);									//���f���̍ő咸�_�ƍŏ����_��ݒ�
	static void SetModelVertexRotation(D3DXMATRIX & pMtx, MODEL_VTX & pModelVtx, CModelInfo & pModelInfo);		//���f���̍ő咸�_�ƍŏ����_��ݒ�@��]��������␳
	static void SetBillboard(D3DXMATRIX *pMtx);																	//�r���{�[�h�ݒ�
	static void SetBillboard_XZ_Only(D3DXMATRIX *pMtx);															//�r���{�[�h�ݒ�@X��Z�̂�

	static bool RangeLimit_Equal_Int(int &nValue, int nMin, int nMax);											//�͈͓��ɗ}����(int)
	static bool RangeLimit_Equal_Float(float &nValue, float nMin, float nMax);									//�͈͓��ɗ}����(float)

	static void SelectVerticalMenu(int &nSelectNum, int const &nMaxSelect);										//�c���j���[�̑I��
	static void SelectHorizonMenu(int &nSelectNum, int const &nMaxSelect);										//�����j���[�̑I��


	static HRESULT InitImgui(HWND hWnd);	//Imgui��������


	static void UninitImgui();				//Imgui�I��
	static void ShowDebugInfo();			//�f�o�b�O���\��
	static void CheckWireMode();			//���C���[�t���[���m�F
	static void CheckCulling();				//�J�����O�m�F
	static void CheckLighting();			//���C�e�B���O�m�F

	static float Random_PI();																					//-3.14����3.14�܂ł̃����_���ŕԂ�
	static float Random(float fInputValue);																		//���͂��ꂽ�l��+-�����_���Ȓl�ŕԂ�
	static D3DXVECTOR3 RandomVector3(float Max);																//�����_����vector3�^�Œl��Ԃ�
	static bool ImGui_Combobox(std::vector<std::string> aItemNameList, std::string aTitle, int & nValue);
	static void CalcRotation(float &fRot);																		//��]��360�x�ȓ��ɂ���v�Z
	static void CalcRotation_XYZ(D3DXVECTOR3 &rot);																	//��]��360�x�ȓ��ɂ���v�Z

	static bool CheckDebugPlayer() { return m_bDebugPlayer; };		//�f�o�b�O�p�̃v���C���[

private:
	static CKeyboard *m_pKeyboard;		//�L�[�{�[�h�ւ̃|�C���^
	static CPad_XInput *m_pXInput;		//XInput�̃p�b�h�ւ̃|�C���^
	static float m_fLeftStickX;			//���X�e�B�b�N�̏��
	static float m_fLeftStickY;			//���X�e�B�b�N�̏��
	static bool m_bStickX;				//�X�e�B�b�N���|��Ă邩�ǂ���
	static bool m_bStickY;				//�X�e�B�b�N���|��Ă邩�ǂ���6

	static bool m_WireFrame;			//���C���[�t���[����
	static bool m_Lighting;				//���C�e�B���O���邩
	static int m_Culling;				//�J�����O���
	static bool m_bDebugPlayer;			//�v���C���[�������쉻


};

#endif