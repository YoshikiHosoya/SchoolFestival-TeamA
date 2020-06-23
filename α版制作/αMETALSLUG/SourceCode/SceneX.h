#pragma once
#ifndef _SCENEX_H_
#define _SCENEX_H_
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#define MAX_MODEL (1)
//�����_�����O�N���X
class CSceneX :public CScene
{
public:
	CSceneX() {};
	CSceneX(OBJ_TYPE type);
	~CSceneX();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DebugInfo(void);
	static CSceneX *Create(void);
private:
	typedef struct
	{
		int nLife;
		D3DXVECTOR3 pos;					//�ʒu
		D3DXVECTOR3 posold;					//�ʒu
		D3DXVECTOR3 move;					//�ړ���
		LPD3DXBUFFER pBuffmat;				//�o�b�t�@
		DWORD nNumMat;						//�}�e���A���̐�
		LPD3DXMESH pMesh;					//���b�V��
		D3DXVECTOR3 vtxMin;					//�ŏ�
		D3DXVECTOR3 vtxMax;					//�ő�
		D3DXCOLOR col;						//�J���[
		D3DXVECTOR3 rot;					//��]
		D3DXMATRIX mtxWorld;				//�}�g���b�N�X
		int nType;							//�^�C�v
	} MODEL;
	static MODEL m_Model[MAX_MODEL];		//���f��
	DWORD m_nNumMatModel = MAX_MODEL;		//�}�e���A�����̐� 
	LPDIRECT3DTEXTURE9 m_pTextureModel;		//�e�N�X�`��
};
#endif