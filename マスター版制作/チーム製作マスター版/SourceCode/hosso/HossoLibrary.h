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
#include "../main.h"
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
#define FlashColor			(D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f))			//�_�ŗp
#define MAX_TEXT			(128)
#define SCREEN_CENTER_POS	(D3DXVECTOR3(SCREEN_WIDTH * 0.5f , SCREEN_HEIGHT * 0.5f ,0.0f))			//��ʒ����̍��W
#define SCREEN_SIZE			(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT,0.0f))							//��ʂ̃T�C�Y
#define NEWLINE				("\n")																	//���s
#define COMMENT01			("//\n")																//�e�L�X�g�p�@�R�����g�@���s
#define COMMENT02			("//------------------------------------------------------------\n")	//�e�L�X�g�p�@��
#define EQUAL				("=")																	//�e�L�X�g�p�@�C�R�[��
#define MAX_CONTROLLER		(2)																		//�R���g���[���[�̍ő吔

//------------------------------------------------------------------------------
//�\���̒�`
//------------------------------------------------------------------------------
//int�^���i�[�ł���
typedef struct INTEGER2
{
	int x;
	int y;

	//�R���X�g���N�^
	INTEGER2()
	{
		//�����Ő��l�������Ă��Ȃ�������0
		x = 0;
		y = 0;
	};
	INTEGER2(int nX, int nY)
	{
		//�����ʂ�̐��l
		x = nX;
		y = nY;
	};

}INTEGER2;

//int�^��3�i�[�ł���
typedef struct INTEGER3
{
	int x;
	int y;
	int z;

	//�R���X�g���N�^
	INTEGER3()
	{
		//�����Ő��l�������Ă��Ȃ�������0
		x = 0;
		y = 0;
		z = 0;
	};
	INTEGER3(int nX, int nY,int nZ)
	{
		//�����ʂ�̐��l
		x = nX;
		y = nY;
		z = nZ;
	};
}INTEGER3;

typedef struct
{
	float		fLeftStickValue_X;			//L�X�e�B�b�N( �� )
	float		fLeftStickValue_Y;			//L�X�e�B�b�N( �c )
	bool		bLeftStickDown_X;			//L�X�e�B�b�N( �� )�����͂���Ă��邩
	bool		bLeftStickDown_Y;			//L�X�e�B�b�N( �c )�����͂���Ă��邩
}PAD_STICK;

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
class CXInputPad;

// �^�O���Ǘ�����N���X
class CGameObject
{
public:
	void	SetTag(TAG Tag) { m_Tag = Tag; };	// �^�O�̐ݒ�
	TAG		GetTag()		{ return m_Tag; };	// �^�O�̎擾

private:
	TAG		m_Tag;								// �^�O
};

class CHossoLibrary
{
public:

	static float Vec2Cross(D3DXVECTOR2 const &rVecA, D3DXVECTOR2 const &rVecB);									//2D �O�όv�Z
	static void CalcMatrix(D3DXMATRIX *pMtx,D3DXVECTOR3 const &rPos, D3DXVECTOR3 const &rRot);					//���[���h�}�g���b�N�X�v�Z
	static void SetBillboard(D3DXMATRIX *pMtx);																	//�r���{�[�h�ݒ�
	static void SetBillboard_XZ_Only(D3DXMATRIX *pMtx);															//�r���{�[�h�ݒ�@X��Z�̂�

	static float Random_PI();																					//-3.14����3.14�܂ł̃����_���ŕԂ�
	static float Random(float fInputValue);																		//���͂��ꂽ�l��+-�����_���Ȓl�ŕԂ�
	static D3DXVECTOR3 RandomVector3(float Max);																//�����_����vector3�^�Œl��Ԃ�
	static void CalcRotation(float &fRot);																		//��]��360�x�ȓ��ɂ���v�Z
	static void CalcRotation_XYZ(D3DXVECTOR3 &rot);																		//��]��360�x�ȓ��ɂ���v�Z

	static void SaveLastStickInfo();																			//�O��̃X�e�B�b�N���
	static DIRECTION CheckPadStick();																			//�X�e�B�b�N��|���Ă���������`�F�b�N
	static bool PressAnyButton(void);
	static bool PressStartButton(void);
	static bool PressPauseButton(void);																			//�|�[�Y�{�^�����������Ƃ�
	static bool PressDeterminationButton(void);																	//����{�^�����������Ƃ�
	static bool ImGui_Combobox(std::vector<std::string> aItemNameList, std::string aTitle, int &nValue);

	static bool PadMoveInput(D3DXVECTOR3 & rMove, DIRECTION & direction, bool bJump, TAG Tag);

	static PAD_STICK	m_PadStick[MAX_CONTROLLER];		// �R���g���[���[�̃X�e�B�b�N���
	static DIRECTION	m_direction;					//����

	//------------------------------------------------------------------------------
	//�͈͓��̒l�ɏC������֐�
	//int�ł�float�ł�������悤�Ƀe���v���[�g
	//------------------------------------------------------------------------------
	template <class X> static bool RangeLimit_Equal(X &Value, X Min, X Max)
	{
		//�ŏ��l��菬������
		if (Value < Min)
		{
			//�ŏ��l�ɍ��킷
			Value = Min;
			return true;
		}
		//�ő�l���傫����
		if (Value > Max)
		{
			//�ő�l�ɍ��킷
			Value = Max;
			return true;
		}
		return false;
	}

private:

};

#endif