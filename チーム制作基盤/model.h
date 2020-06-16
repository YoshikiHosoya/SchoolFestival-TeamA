#pragma once
#ifndef _MODEL_H_
#define _MODEL_H_
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Scene.h"

#define MAX_ALLMODEL (100)
//�����_�����O�N���X
class CModel : public CScene
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
		MODEL_PLAYER_MAX
	}CHARA_MODEL;
	typedef enum
	{
		MODEL_MAP_BLOCK,			//�}�b�v�̕���
		MODEL_MAP_ICESWORD,			//�}�b�v�̕���
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
		MODEL_ENEMY_MAX
	}ENEMY_PARTS_MODEL;
	/*--- �e�̃��f�� ---*/
	typedef enum
	{
		MODEL_GUN_HANDGUN,				// �n���h�K��
		MODEL_GUN_HEAVYMACHINEGUN,		// �w�r�[�}�V���K��
		MODEL_GUN_MAX
	}GUN_MODEL;
	typedef enum
	{
		PLAYER_MODEL,
		ENEMY_MODEL,
		MAP_MODEL,
		GUN_MODEL,
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

	CModel(OBJ_TYPE type);
	~CModel();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(D3DXMATRIX mat);
	void Draw();
	void SetParent(CModel *pModel);
	void SetPosition(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetSize(D3DXVECTOR3 size);
	void SetType(int type)				{ m_type = type; };					// ���f���^�C�v�̐ݒ�
	void SetModelConut(int nModelCount) { m_modelCount = nModelCount; };	// ���f���J�E���g�̐ݒ�
	int GetType()						{ return m_type; };					// ���f���^�C�v�̎擾
	int GetModelCount()					{ return m_modelCount; };			// ���f���J�E���g�̎擾
	LPD3DXMESH GetMesh(void);
	D3DXMATRIX *GetMatrix(void);
	static void LoadModel(void);
	static void UnLoad(void);
	D3DXVECTOR3 &GetPosition(void);
	D3DXVECTOR3 &GetRot(void);
	D3DXVECTOR3 GetvtxMax(int nCnt);
	D3DXVECTOR3 GetvtxMin(int nCnt);
	static CModel *Create(int type, int modelCount);

	static char* GetModelFileName(int nType, int nModelCount);
private:

	static MODEL m_Model[TYPE_MAX][MAX_ALLMODEL];
	static char *m_PlayerFileName[MODEL_PLAYER_MAX];
	static char *m_EnemyFileName[MODEL_ENEMY_MAX];
	static char *m_GunFileName[MODEL_GUN_MAX];
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
	int m_nIdxModelpalent;				//�e�̃C���f�b�N�X
	int m_nIdx;							//���f���̃C���f�b�N�X
};
#endif
