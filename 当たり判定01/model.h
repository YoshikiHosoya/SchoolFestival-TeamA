#pragma once
#ifndef _MODEL_H_
#define _MODEL_H_
#include "main.h"
#include "manager.h"
#include "renderer.h"
#define MAX_ALLMODEL (100)
//�����_�����O�N���X
class CModel
{
public:
	typedef enum
	{
		MODEL_PLAYER_HEAD,			//�v���C���[�̓�
		MODEL_PLAYER_BODY,			//�v���C���[�̑�
		MODEL_PLAYER_LARM,			//�v���C���[�̍��r
		MODEL_PLAYER_RARM,			//�v���C���[�̉E�r
		MODEL_PLAYER_LHAND,			//�v���C���[�̍���
		MODEL_PLAYER_RHAND,			//�v���C���[�̉E��
		MODEL_PLAYER_LLEG,			//�v���C���[�̍��r
		MODEL_PLAYER_RLEG,			//�v���C���[�̉E�r
		MODEL_PLAYER_LFOOT,			//�v���C���[�̍���
		MODEL_PLAYER_RFOOT,			//�v���C���[�̉E��
		MODEL_PLAYER_FIRESWORD,		//�v���C���[�̕���
		MODEL_PLAYER_ICESWORD,		//�v���C���[�̕���
		MODEL_PLAYER_THUNDERSWORD,	//�v���C���[�̕���
		MODEL_PLAYER_BALL,			//����
		MODEL_PLAYER_MAX
	}CHARA_MODEL;
	typedef enum
	{
		MODEL_MAP_BLOCK,		//�}�b�v�̕���
		MODEL_MAP_ICESWORD,			//�}�b�v�̕���
		MODEL_MAP_MPPOTION,		//�}�b�v�̕���
		MODEL_MAP_HPPOTION,				//
		MODEL_MAP_PORTAL,				//
		MODEL_MAP_BLOCK02,
		MODEL_MAP_MAX
	}CREATE_MAP_MODEL;
	typedef enum
	{
		//===[��]===
		MODEL_ENEMY_HEAD_01,		//��
		MODEL_ENEMY_BODY_01,		//��
		MODEL_ENEMY_LARM_01,		//���r
		MODEL_ENEMY_RARM_01,		//�E�r
		MODEL_ENEMY_LHAND_01,		//����
		MODEL_ENEMY_RHAND_01,		//�E��
		MODEL_ENEMY_LLEG_01,		//���r
		MODEL_ENEMY_RLEG_01,		//�E�r
		MODEL_ENEMY_LFOOT_01,		//����
		MODEL_ENEMY_RFOOT_01,		//�E��
		MODEL_ENEMY_WEPON_01,		//����
		//===[��]===
		MODEL_ENEMY_HEAD_02,		//��
		MODEL_ENEMY_CHIN,			//�{
		MODEL_ENEMY_BODY_02,		//��
		MODEL_ENEMY_LARM_02,		//���r
		MODEL_ENEMY_RARM_02,		//�E�r
		MODEL_ENEMY_LHAND_02,		//����
		MODEL_ENEMY_RHAND_02,		//�E��
		MODEL_ENEMY_LLEG_02,		//���r
		MODEL_ENEMY_RLEG_02,		//�E�r
		MODEL_ENEMY_LFOOT_02,		//����
		MODEL_ENEMY_RFOOT_02,		//�E��
		MODEL_ENEMY_WEPON_02,		//����
		//===[�X]===
		MODEL_ENEMY_HEAD_03,		//��
		MODEL_ENEMY_BODY_03,		//��
		MODEL_ENEMY_LARM_03,		//���r
		MODEL_ENEMY_RARM_03,		//�E�r
		MODEL_ENEMY_LHAND_03,		//����
		MODEL_ENEMY_RHAND_03,		//�E��
		MODEL_ENEMY_LEG_03,			//�r
		MODEL_ENEMY_WEPON_03,		//����
		//===[BOSS]===
		MODEL_BOSS_HEAD,		//��
		MODEL_BOSS_BODY,		//��
		MODEL_BOSS_LARM,		//���r
		MODEL_BOSS_RARM,		//�E�r
		MODEL_BOSS_LHAND,		//����
		MODEL_BOSS_RHAND,		//�E��
		MODEL_BOSS_LFOOT,		//��
		MODEL_BOSS_RFOOT,		//��
		MODEL_BOSS_LEG,			//�r
		MODEL_BOSS_WEPON01,		//����
		MODEL_BOSS_WEPON02,		//����
		MODEL_ENEMY_MAX
	}ENEMY_PARTS_MODEL;
	typedef enum
	{
		PLAYER_MODEL,
		ENEMY_MODEL,
		MAP_MODEL,
		TYPE_MAX
	}MODEL_TYPE;
	typedef struct
	{
		LPD3DXBUFFER pBuffmat;
		DWORD nNumMat;
		LPD3DXMESH pMesh;
		LPDIRECT3DTEXTURE9 *m_pTexture;
		D3DXVECTOR3 vtxMax;
		D3DXVECTOR3 vtxMin;
		//D3DXVECTOR3 Dest;
	} MODEL;

	CModel();
	~CModel();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Drow(D3DXMATRIX mat);
	void SetParent(CModel *pModel);
	void SetPosition(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetSize(D3DXVECTOR3 size);
	void SetType(int type);
	int GetType(void);
	LPD3DXMESH GetMesh(void);
	D3DXMATRIX *GetMatrix(void);
	static void LoadModel(void);
	static void UnLoad(void);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetRot(void);
	D3DXVECTOR3 GetvtxMax(int nCnt);
	D3DXVECTOR3 GetvtxMin(int nCnt);
	static CModel *Create(int type, int modelCount);
private:

	static MODEL m_Model[TYPE_MAX][MAX_ALLMODEL];
	static char *m_PlayerFileName[MODEL_PLAYER_MAX];
	static char *m_EnemyFileName[MODEL_ENEMY_MAX];
	static char *m_MapFileName[MODEL_MAP_MAX];

	D3DXVECTOR3 m_pos;					//�ʒu
	D3DXVECTOR3 m_size;					//�T�C�Y
	D3DXVECTOR3 m_posold;				//�ʒu
	D3DXVECTOR3 m_move;					//�ړ���
	D3DXVECTOR3 m_rot;					//��]
	D3DXCOLOR m_col;					//�J���[
	D3DXMATRIX m_mtxWorld;				//�}�g���b�N�X
	D3DXMATRIX m_mtxparent;
	CModel *m_pParent;					//�e�̃|�C���^
	int m_modelCount;					//���f���̎��
	int m_type;
	int m_nIdxModelpalzajient;				//�e�̃C���f�b�N�X
	int m_nIdx;							//���f���̃C���f�b�N�X
};
#endif