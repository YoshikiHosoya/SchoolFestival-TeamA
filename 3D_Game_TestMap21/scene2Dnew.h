// =====================================================================================================================================================================
//
// �V�[��2Dnew�̏��� [scene2Dnew.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _SCENE2DNEW_H_
#define _SCENE2DNEW_H_

// =====================================================================================================================================================================
// �C���N���[�h�t�@�C��
// =====================================================================================================================================================================
#include "main.h"
#include "scene.h"

// =====================================================================================================================================================================
// �I�u�W�F�N�g�N���X
// =====================================================================================================================================================================
class CScene2Dnew
{
public:
	CScene2Dnew();														// �R���X�g���N�^
	virtual ~CScene2Dnew();												// �f�X�g���N�^
	
	/* �����o�֐� */
	virtual void	Init();												// ������
	virtual void	Uninit();											// �I��
	virtual void	Update();											// �X�V
	virtual void	Draw();												// �`��

	/* �����o�֐� */
	void			SetPos(D3DXVECTOR3 pos)		{ m_pos = pos; };			// �ʒu�̐ݒ�
	D3DXVECTOR3		GetPos()					{ return m_pos; };			// �ʒu�̎擾
	D3DXVECTOR3		GetSize()					{ return m_size; };			// �T�C�Y�̎擾
	void			SetSize(D3DXVECTOR3 size)	{ m_size = size; };			// �T�C�Y�̐ݒ�
	void			SetAnim(D3DXVECTOR2 UVsize, D3DXVECTOR2 UV);			// �A�j���[�V�����̐ݒ�
	void			SetRadius(float fRadius);								// ���a�̐ݒ�
	void			SetRotation(float fAngle, float fLength, float fRot);	// ��]�̐ݒ�
	void			SetCol(D3DXCOLOR col);									// �F�̐ݒ�
	void			BindTexture(LPDIRECT3DTEXTURE9 pTexture);				// �摜�̑��

	/* �ÓI�����o�֐� */
	static			CScene2Dnew *Create();										// 2D�|���S���̐���

private:
	/* �����o�ϐ� */
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;				// �ʒu
	D3DXVECTOR3				m_size;				// �T�C�Y
	D3DXVECTOR3				m_rot;				// ��]
	float					m_fAngle;			// �p�x
	float					m_fLength;			// ����
};
#endif