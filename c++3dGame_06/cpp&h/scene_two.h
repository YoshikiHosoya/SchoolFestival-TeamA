// ----------------------------------------
//
// 2D�V�[�������̐���[scene_two.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _SCENE_TWO_H_
#define _SCENE_TWO_H_	 // �t�@�C������������߂�

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "main.h"
#include "scene.h"

// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CScene_TWO : public CScene
{
public:
	/* �֐� */
	CScene_TWO();
	CScene_TWO(ACTOR actor, LAYER layer);
	~CScene_TWO();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetLengh(D3DXVECTOR2 dist);
	void SetSize(D3DXVECTOR2 size);						// �T�C�Y�ݒ�
	void SetGaugeSize(D3DXVECTOR2 size);				// �T�C�Y�ݒ�
	void SetPosition(D3DXVECTOR3 pos);					// �ʒu�ݒ�
	void SetRot(float frot);							// ��]�ݒ�
	void SetCol(D3DXCOLOR col);							// �F�ݒ�
	void SetTex(D3DXVECTOR2 first,D3DXVECTOR2 last);	// �\���e�N�X�`���[�ݒ�
	void SetRotTex(float frot);	// �\���e�N�X�`���[�ݒ�

	D3DXVECTOR2 GetSize(void);							// �T�C�Y���擾
	D3DXVECTOR3 GetPosition(void);						// �ʒu���擾
	float GetLengh(void);								// �������擾

	void BindTexture(LPDIRECT3DTEXTURE9 p_Tex);			// �e�N�X�`���[
	static CScene_TWO * Create();						// �쐬

protected:
private:
	LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;					// ���S���W
	float m_rot;						// �p�x
	float m_texrot;						// �p�x
	D3DXVECTOR2 m_size;					// �T�C�Y
	float m_fLengh;						// ����
	float m_fAngle;						// �p�x
};

#endif