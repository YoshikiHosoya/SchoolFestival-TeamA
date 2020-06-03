#pragma once
#ifndef _CREATEMAP_H_
#define _CREATEMAP_H_
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "Scene.h"
#include "inputKeyboard.h"
class CModel;
//�����_�����O�N���X
class CCreateMap:public CScene
{
public:
	CCreateMap(OBJ_TYPE type);
	 ~CCreateMap();
	 typedef struct
	 {
		 D3DXVECTOR3 pos;
		 D3DXVECTOR3 rot;
	 }LOAD_MODEL;
	 typedef enum
	 {
		 LOOAD_MAP_TUTORIAL,		//�`���[�g���A���}�b�v
		 LOOAD_MAP_GAME01,			//�Q�[��01�}�b�v
		 LOOAD_MAP_GAME02,			//�Q�[��02�}�b�v
		 LOOAD_MAP_GAME03,			//�Q�[��03�}�b�v
		 LOOAD_MAP_MAX
	 }CREATE_MAP_MODEL;

	HRESULT Init(void);
	void Uninit(void) ;
	void Update(void) ;
	void Draw(void);
	void Save(void);
	void Load(int type);
	bool Collision(void);
	//bool CollisionModel(D3DXVECTOR3 *size , D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move);
	int GetMaxModel(void);
	static CCreateMap * Create(int type);
	D3DXVECTOR3 GetPosition(void);
	LPD3DXMESH GetMesh(int nCnt);
	CModel*GetModel(int nCnt);
private:
	std::vector<CModel*> m_vec;			//�ϒ��z�� �ݒu�������f��
	std::vector<CModel*> m_map;			//�ϒ��z�� �ݒu���郂�f��
	std::vector<CEnemy*> m_Enemy;		//�ϒ��z�� �ݒu�����G�l�~�[

	static char *m_LoadFileName[LOOAD_MAP_MAX];
	D3DXVECTOR3 m_pos;					//�ʒu
	D3DXVECTOR3 m_move;					//�ړ���
	D3DXVECTOR3 m_rot;					//��]
	D3DXCOLOR m_col;					//�J���[
	D3DXMATRIX m_mtxWorld;				//�}�g���b�N�X
	D3DXMATRIX m_mtxRot;				//��]�}�g���b�N�X
	CCreateMap *m_pParent;				//�e�̃|�C���^
	CPlayer *m_Player;
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPD3DXMESH pMesh;
	int m_nIdxModelpalent;				//�e�̃C���f�b�N�X
	int m_nIdx;							//���f���̃C���f�b�N�X
	int m_type;
	int m_max;
	bool set;
};
#endif