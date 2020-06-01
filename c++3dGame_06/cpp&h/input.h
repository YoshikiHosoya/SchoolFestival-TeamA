// ------------------------------------------
//
// �C���v�b�g�����̐���[input.h]
// Author : Fujiwara Masato
//
// ------------------------------------------

#ifndef _INPUT_H_
#define _INPUT_H_	 // �t�@�C������������߂�

// ------------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ------------------------------------------
#include "main.h"

// ------------------------------------------
//
// �}�N���֐�
//
// ------------------------------------------

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CInput
{
public:
	/* �񋓌^ */
	typedef enum
	{
		DEVICETYPE_KEYBOARD = 0,
		DEVICETYPE_JOYPAD
	} DEVICETYPE;

	/* �֐� */
	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;
	static void ReleaseAll(void);							// �e�q�����[�X

protected:
	static LPDIRECTINPUT8 m_pInput;							// ���̓f�o�C�X

private:
};

#endif // !_INPUT_H_