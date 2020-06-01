// ----------------------------------------
//
// 3D�V�[�������̐���[scene_three.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _SCENE_THREE_H_
#define _SCENE_THREE_H_	 // �t�@�C������������߂�

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
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
class CScene_THREE : public CScene
{
public:
	/* �֐� */
	CScene_THREE();
	CScene_THREE(ACTOR actor, LAYER layer);
	~CScene_THREE();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetSize(D3DXVECTOR3 size);						// �T�C�Y�ݒ�
	void SetPos(D3DXVECTOR3 pos);						// �ʒu�ݒ�
	void SetRot(D3DXVECTOR3 rot);						// ��]�ݒ�
	void SetCol(D3DXCOLOR col);							// �F�ݒ�
	void SetTex(D3DXVECTOR2 first,D3DXVECTOR2 last);	// �\���e�N�X�`���[�ݒ�
	D3DXVECTOR3 GetSize(void);							// �T�C�Y�擾
	D3DXVECTOR3 GetRot(void);							// ��]�擾
	D3DXVECTOR3 GetPos(void);							// �ʒu�擾
	void BindTexture(LPDIRECT3DTEXTURE9 p_Tex);			// �e�N�X�`���[
	void SetBillboard(bool bBillboard);					// �r���{�[�h���
	static CScene_THREE * Create(bool bBillboard);		// �쐬
	float GetHeight(D3DXVECTOR3 pos);					// �����擾
protected:
private:
	LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;					// ���S���W
	D3DXVECTOR3 m_OriginBlock;			// �����z�u
	D3DXMATRIX  m_mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_size;					// �T�C�Y
	D3DXVECTOR3 m_rot;					// �p�x
	float m_fLengh;						// ����
	float m_fAngle;						// �p�x
	bool m_bBillboard;					// �r���{�[�h���
};

#endif