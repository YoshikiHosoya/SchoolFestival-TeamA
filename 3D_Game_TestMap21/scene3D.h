// =====================================================================================================================================================================
//
// �V�[��3D�̏��� [scene3D.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

// =====================================================================================================================================================================
// �C���N���[�h�t�@�C��
// =====================================================================================================================================================================
#include "main.h"
#include "scene.h"

// =====================================================================================================================================================================
// �I�u�W�F�N�g�N���X
// =====================================================================================================================================================================
class CScene3D : public CScene
{
public:
	CScene3D(PRIORITY Priority);			// �R���X�g���N�^
	virtual ~CScene3D();					// �f�X�g���N�^
	 
	/* �����o�֐� */
	virtual void	Init();					// ������
	virtual void	Uninit();				// �I��
	virtual void	Update();				// �X�V
	virtual void	Draw();					// �`��

	/* �ÓI�����o�֐� */
	static			CScene3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// 3D�|���S���̐���	

	/* �����o�֐� */
	void			SetPos(D3DXVECTOR3 pos)						{ m_pos = pos; };								// �ʒu�̐ݒ�
	void			SetRot(D3DXVECTOR3 rot)						{ m_rot = rot; };								// ��]�̐ݒ�
	void			SetSize(D3DXVECTOR3 size)					{ m_size = size; };								// �T�C�Y�̐ݒ�
	void			SetBillboard(bool bBillboard)				{ m_bBillboard = bBillboard; };					// �r���{�[�h�̐ݒ�
	void			SetBothSideCulling(bool bBothSideCulling)	{ m_bBothSideCulling = bBothSideCulling; };		// ���ʃJ�����O�̐ݒ�
	void			SetTexture(char TexName[]);										// �摜�̐ݒ�
	void			SetRadius(float fRadius);										// ���a�̐ݒ�
	void			SetScaling(D3DXVECTOR3 size);									// �g�k�̐ݒ�
	void			SetNormal();													// �@���̐ݒ�
	void			SetAnim(D3DXVECTOR2 UVsize, D3DXVECTOR2 UV);					// �A�j���[�V�����̐ݒ�
	void			SetColor(D3DXCOLOR col);										// �F�̐ݒ�
	void			SetTexSeparate(int nSeparate);									// �e�N�X�`���̕����ݒ�
	void			SetSlope(float Slope);											// ��̎Ζʂ̐ݒ�
	void			BindTexture(LPDIRECT3DTEXTURE9 pTexture);						// �摜�̑��
	bool			GetHeight(D3DXVECTOR3 &pos);									// �����̎擾
	D3DXVECTOR3		GetPos()									{ return m_pos; };	// �ʒu�̎擾
	D3DXVECTOR3		GetSize()									{ return m_size; };	// �T�C�Y�̎擾

private:
	/* �����o�ϐ� */
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX				m_mtxWorld;				// ���[���h�}�g���b�N�X
	bool					m_bBillboard;			// �r���{�[�h�t���O
	bool					m_bBothSideCulling;		// ���ʃJ�����O�t���O

	D3DXVECTOR3				m_pos;					// �ʒu
	D3DXVECTOR3				m_size;					// �T�C�Y
	D3DXVECTOR3				m_rot;					// ��]
	float					m_fSlope;				// �X��

	D3DXVECTOR3				m_vec2_0;				// �x�N�g��2_0
	D3DXVECTOR3				m_vec1_2;				// �x�N�g��1_2
	D3DXVECTOR3				m_vec2_3;				// �x�N�g��2_3

	D3DXVECTOR3				m_nor1_2_0;				// �@��1_2_0
	D3DXVECTOR3				m_nor1_2_3;				// �@��1_2_3
	D3DXVECTOR3				m_nor1_2;				// �@��1_2;	
};
#endif
