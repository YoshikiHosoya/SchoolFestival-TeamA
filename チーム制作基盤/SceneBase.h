#pragma once
#ifndef _SCENEBASE_H_
#define _SCENEBASE_H_

#include "main.h"
#include "scene.h"
//�����_�����O�N���X
class CSceneBase :public CScene
{
public:
	CSceneBase() {};//Scene�ŊǗ�����Ȃ��R���X�g���N�^
	CSceneBase(OBJ_TYPE type);
	virtual	~CSceneBase()		= 0;
	virtual	HRESULT Init(void);
	virtual	void Uninit(void);
	virtual	void Update(void)	= 0;
	virtual	void Draw(void)		= 0;

	void MtxCalc(void);
	//�Z�b�g�������
	virtual void SetPosition(D3DXVECTOR3 pos);
	virtual void SetSize(D3DXVECTOR3 size);
	virtual void SetColor(D3DXCOLOR col);
	virtual void SetRot(D3DXVECTOR3 rot);
	virtual void SetAnimation(D3DXVECTOR2 UV, D3DXVECTOR2 UVsize) = 0;
	virtual void BindTexture(LPDIRECT3DTEXTURE9 tex);
	virtual void BindVtxBuff(LPDIRECT3DVERTEXBUFFER9 pVtxBuff);
	virtual void SetMtxWorld(D3DXMATRIX mtxWorld);
	//�Q�b�g�������
	D3DXVECTOR3 &GetPosition(void);
	D3DXVECTOR3 &GetSize(void);
	D3DXCOLOR &GetColor(void);
	D3DXVECTOR3 &GetRot(void);
	LPDIRECT3DTEXTURE9 GetTexture(void);
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void);
	D3DXMATRIX *GetMtxWorld(void);
protected:

private:
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
	D3DXCOLOR m_col;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxWorld;
};
#endif