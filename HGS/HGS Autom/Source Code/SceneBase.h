//------------------------------------------------------------------------------
//
//�V�[��2D����  [scene2D.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _SCENEBASE_H_
#define _SCENEBASE_H_

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CSceneBase :public CScene
{
public:
	CSceneBase();													//�R���X�g���N�^
	virtual	~CSceneBase();											//�f�X�g���N�^
	virtual	HRESULT Init(void)	= 0;								//������
	virtual	void Uninit(void)	= 0;								//�I��
	virtual	void Update(void)	= 0;								//�X�V
	virtual	void Draw(void)		= 0;								//�`��
	virtual void ShowDebugInfo() = 0;								//�f�o�b�O���\�L

	//Set�֐�
	//���z�֐��@���_�o�b�t�@�̍Ē����Ƃ��I�[�o�[���C�h�ł��Ă��炤
	virtual void SetPos(D3DXVECTOR3 pos)							{ m_pos = pos; };					//���W
	virtual void SetSize(D3DXVECTOR3 size)							{ m_size = size; };					//�T�C�Y
	virtual void SetColor(D3DXCOLOR col)							{ m_col = col; };					//�F
	virtual void SetRot(D3DXVECTOR3 rot)							{ m_rot = rot; };					//��]��
	virtual void SetAnimation(D3DXVECTOR2 UV, D3DXVECTOR2 UVsize) {};

	void BindTexture(LPDIRECT3DTEXTURE9 tex)				{ m_pTexture = tex; };						//�e�N�X�`��
	void BindVtxBuff(LPDIRECT3DVERTEXBUFFER9 pVtxBuff)		{ m_pVtxBuff = pVtxBuff; };					//���_�o�b�t�@
	void SetMtxWorld(D3DXMATRIX mtxWorld)					{ m_mtxWorld = mtxWorld; };					//���[���h�}�g���b�N�X
	void SetDisp(bool bDisp)								{ m_bDisp = bDisp; };						//�\����\��

	//Get�֐�
	D3DXVECTOR3 &GetPos(void)										{ return m_pos; };					//���W
	D3DXVECTOR3 *GetPosPtr()										{ return &m_pos; };					//���W�̃|�C���^�@�����蔻��Ƃ��͂�����g��
	D3DXVECTOR3 &GetSize(void)										{ return m_size; };					//�T�C�Y
	D3DXCOLOR &GetColor(void)										{ return m_col; };					//�F
	D3DXVECTOR3 &GetRot(void)										{ return m_rot; };					//��]��
	LPDIRECT3DTEXTURE9 GetTexture(void)								{ return m_pTexture; };				//�e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void)						{ return m_pVtxBuff; };				//���_�o�b�t�@
	D3DXMATRIX *GetMtxWorldPtr(void)								{ return &m_mtxWorld; };			//���[���h�}�g���b�N�X
	bool GetDisp()													{ return m_bDisp; };				//�\����\��
protected:

private:
	LPDIRECT3DTEXTURE9 m_pTexture;							//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;						//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;										//���W
	D3DXVECTOR3 m_size;										//�T�C�Y
	D3DXCOLOR m_col;										//�F
	D3DXVECTOR3 m_rot;										//��]��
	D3DXMATRIX m_mtxWorld;									//���[���h�}�g���b�N�X
	bool m_bDisp;											//�\����\���̐ݒ�

};
#endif