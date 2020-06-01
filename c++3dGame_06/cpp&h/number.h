// ----------------------------------------
//
// �ԍ������̐���[number.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _NUMBER_H_
#define _NUMBER_H_	 // �t�@�C������������߂�

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "manager.h"

// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
#define MAX_NUMBER (10)

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CNumber
{
public:
	/* �񋓌^ */
	// �e�N�X�`���[�^�C�v
	typedef enum
	{
		TEX_SCORE,
		TEX_STAGE,
		TEX_MAX
	} TEX;

	/* �֐� */
	CNumber();
	~CNumber();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNum(int nNum);		// �ԍ��ݒ�
	void SetPos(D3DXVECTOR3 pos, float fsize);
	void SetTex(TEX tex);		// �e�N�X�`���[
	void SetCol(D3DXCOLOR col);	// �J���[
	static HRESULT Load(void);
	static void UnLoad(void);
	static CNumber * Create();	// �쐬
protected:

private:
	static LPDIRECT3DTEXTURE9 m_pTex[TEX_MAX];
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	TEX m_texID;						// �e�N�X�`���[�ԍ�
	float m_rot;						// �p�x
	float m_fLengh;						// ����
	float m_fAngle;						// �p�x
};

#endif