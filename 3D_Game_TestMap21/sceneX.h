// =====================================================================================================================================================================
//
// �V�[��X�̏��� [sceneX.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _SCENEX_H_
#define _SCENEX_H_

// =====================================================================================================================================================================
// �C���N���[�h�t�@�C��
// =====================================================================================================================================================================
#include "main.h"
#include "scene.h"

// =====================================================================================================================================================================
// �\���̒�`
// =====================================================================================================================================================================
// === ���f���`��ɕK�v�ȏ�� ===
typedef struct
{
	LPD3DXMESH					Mesh;				// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER				BuffMat;			// �}�e���A�����ւ̃|�C���^
	DWORD						nNumMat;			// �}�e���A�����̐�
}MODEL_DRAWINFO;

// =====================================================================================================================================================================
// �I�u�W�F�N�g�N���X
// =====================================================================================================================================================================
class CSceneX : public CScene
{
public:
	CSceneX();								// �R���X�g���N�^
	CSceneX(PRIORITY Priority);				// �R���X�g���N�^
	virtual ~CSceneX();						// �f�X�g���N�^
	 
	/* �����o�֐� */
	virtual void	Init();					// ������
	virtual void	Uninit();				// �I��
	virtual void	Update();				// �X�V
	virtual void	Draw();					// �`��

	/* �ÓI�����o�֐� */
	static	CSceneX		*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// 3D�|���S���̐���	

	/* �����o�֐� */
	void			SetPos(D3DXVECTOR3 pos)						{ m_pos = pos; };						// �ʒu�̐ݒ�
	void			SetRot(D3DXVECTOR3 rot)						{ m_rot = rot; };						// ��]�̐ݒ�
	void			SetMatrix(D3DXMATRIX mtx)					{ m_mtxWorld = mtx; };					// �}�g���b�N�X�̐ݒ�
	void			SetModelDraw(MODEL_DRAWINFO *ModelDrawInfo)	{ m_pModelDrawInfo = ModelDrawInfo; };	// ���f���`����̐ݒ�
	D3DXVECTOR3		GetPos()									{ return m_pos; };						// �ʒu�̎擾
	D3DXVECTOR3		GetRot()									{ return m_rot; };						// ��]�̎擾
	D3DXMATRIX		*GetMatrix()								{ return &m_mtxWorld; };				// �}�g���b�N�X�̎擾
	void			SetTexture(char TexName[]);									// �摜�̐ݒ�
	void			BindTexture(LPDIRECT3DTEXTURE9 pTexture);					// �摜�̑��
	void			DrawModel();												// ���f���̕`��
private:

	D3DXVECTOR3				m_pos;		// �ʒu
	D3DXVECTOR3				m_move;		// �ړ�
	D3DXVECTOR3				m_size;		// �T�C�Y
	D3DXVECTOR3				m_rot;		// ����(��])

	MODEL_DRAWINFO			*m_pModelDrawInfo;	// ���f���̕`��ɕK�v�ȏ��
	D3DXMATRIX				m_mtxWorld;			// ���[���h�}�g���b�N�X
	LPDIRECT3DTEXTURE9		m_pTexture	= {};	// �e�N�X�`���ւ̃|�C���^
};
#endif
