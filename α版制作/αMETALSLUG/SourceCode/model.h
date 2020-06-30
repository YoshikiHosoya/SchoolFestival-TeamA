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
		MODEL_PLAYER_WAIST,			//�v���C���[�̍�
		MODEL_PLAYER_BODY,			//�v���C���[�̑�
		MODEL_PLAYER_HEAD,			//�v���C���[�̓�
		MODEL_PLAYER_L_SHOLDER,		//�v���C���[�̍���
		MODEL_PLAYER_R_SHOLDER,		//�v���C���[�̉E��
		MODEL_PLAYER_LARM,			//�v���C���[�̍��r
		MODEL_PLAYER_RARM,			//�v���C���[�̉E�r
		MODEL_PLAYER_LHAND,			//�v���C���[�̍���
		MODEL_PLAYER_RHAND,			//�v���C���[�̉E��
		MODEL_PLAYER_LKNEE,			//�v���C���[�̍��G
		MODEL_PLAYER_RKNEE,			//�v���C���[�̉E�G
		MODEL_PLAYER_LLEG,			//�v���C���[�̍��r
		MODEL_PLAYER_RLEG,			//�v���C���[�̉E�r
		MODEL_PLAYER_LFOOT,			//�v���C���[�̍���
		MODEL_PLAYER_RFOOT,			//�v���C���[�̉E��
		MODEL_PLAYER_MAX
	}CHARA_MODEL;

	typedef enum
	{
		MODEL_PRISONER_HEAD,			//�ߗ��̓�
		MODEL_PRISONER_BODY,			//�ߗ��̑�
		MODEL_PRISONER_LARM,			//�ߗ��̍��r
		MODEL_PRISONER_RARM,			//�ߗ��̉E�r
		MODEL_PRISONER_LHAND,			//�ߗ��̍���
		MODEL_PRISONER_RHAND,			//�ߗ��̉E��
		MODEL_PRISONER_LLEG,			//�ߗ��̍��r
		MODEL_PRISONER_RLEG,			//�ߗ��̉E�r
		MODEL_PRISONER_LFOOT,			//�ߗ��̍���
		MODEL_PRISONER_RFOOT,			//�ߗ��̉E��
		MODEL_PRISONER_MAX
	}PRISONER_MODEL;

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
		OBSTACLE_MODEL,
		PRISONER_MODEL,
		TYPE_MAX
	}MODEL_TYPE;

	// ��Q���̎��
	typedef enum
	{
		OBSTACLE_TYPE_BOX = 0,								// �n�R
		OBSTACLE_TYPE_MAX,
	}OBSTACLE_TYPE;

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
	void DebugInfo();
	void SetParent(CModel *pModel);
	void SetPosition(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetSize(D3DXVECTOR3 size);
	void SetType(int type)				{ m_type = type; };					// ���f���^�C�v�̐ݒ�
	void SetModelConut(int nModelCount) { m_modelCount = nModelCount; };	// ���f���J�E���g�̐ݒ�
	void SetParentIdx(int nParentIdx)	{ m_nParentIdx = nParentIdx; };		// �e�ԍ��ݒ�
	int GetType()						{ return m_type; };					// ���f���^�C�v�̎擾
	int GetModelCount()					{ return m_modelCount; };			// ���f���J�E���g�̎擾
	int GetParentIdx()					{ return m_nParentIdx; };			// �e�ԍ��擾
	LPD3DXMESH GetMesh(void);
	D3DXMATRIX *GetMatrix(void);
	static void LoadModel(void);
	static void UnLoad(void);
	D3DXVECTOR3 &GetPosition(void);
	D3DXVECTOR3 &GetRot(void);
	D3DXVECTOR3 GetvtxMax(int nCnt);
	D3DXVECTOR3 GetvtxMin(int nCnt);
	static CModel *Create(int type, int modelCount);
	static CModel *CreateSceneManagement(int type, int modelCount);

	static char* GetModelFileName(int nType, int nModelCount);
	bool GetDieFlag() { return m_bDieFlag; };							// ���S�t���O�̎擾
	void SetDieFlag(bool DieFlag) { m_bDieFlag = DieFlag; };			// ���S�t���O�̐ݒ�
private:

	static MODEL m_Model[TYPE_MAX][MAX_ALLMODEL];
	static char *m_PlayerFileName[MODEL_PLAYER_MAX];
	static char *m_EnemyFileName[MODEL_ENEMY_MAX];
	static char *m_GunFileName[MODEL_GUN_MAX];
	static char *m_MapFileName[MODEL_MAP_MAX];
	static char *m_ObstacleFileName[OBSTACLE_TYPE_MAX];
	static char *m_PrisonerFileName[MODEL_PRISONER_MAX];


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
	int m_nParentIdx;					//�e�ԍ�
	bool m_bDieFlag;					// ���S�t���O
};
#endif
