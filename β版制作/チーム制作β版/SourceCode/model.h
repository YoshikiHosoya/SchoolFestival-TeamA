#pragma once
#ifndef _MODEL_H_
#define _MODEL_H_
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Scene.h"

#define MAX_ALLMODEL (100)
// =====================================================================================================================================================================
// �O���錾
// =====================================================================================================================================================================
class CCollision;
//�����_�����O�N���X
class CModel : public CScene
{
public:
	/*--- �v���C���[�̃p�[�c���f�� ---*/
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

	/*--- �ߗ��̃p�[�c���f�� ---*/
	typedef enum
	{
		MODEL_PRISONER_WAIST,			//�ߗ��̍�
		MODEL_PRISONER_BODY,			//�ߗ��̑�
		MODEL_PRISONER_HEAD,			//�ߗ��̓�
		MODEL_PRISONER_L_SHOLDER,		//�ߗ��̍���
		MODEL_PRISONER_R_SHOLDER,		//�ߗ��̉E��
		MODEL_PRISONER_LARM,			//�ߗ��̍��r
		MODEL_PRISONER_RARM,			//�ߗ��̉E�r
		MODEL_PRISONER_LHAND,			//�ߗ��̍���
		MODEL_PRISONER_RHAND,			//�ߗ��̉E��
		MODEL_PRISONER_LKNEE,			//�ߗ��̍��G
		MODEL_PRISONER_RKNEE,			//�ߗ��̉E�G
		MODEL_PRISONER_LLEG,			//�ߗ��̍��r
		MODEL_PRISONER_RLEG,			//�ߗ��̉E�r
		MODEL_PRISONER_LFOOT,			//�ߗ��̍���
		MODEL_PRISONER_RFOOT,			//�ߗ��̉E��
		MODEL_PRISONER_MAX
	}PRISONER_MODEL;

	typedef enum
	{
		MODEL_MAP_TUTORIAL,			//�`���[�g���A���}�b�v
		MODEL_MAP_STAGE1_1,			//�X�e�[�W1-1
		MODEL_MAP_STAGE1_2,			//�X�e�[�W1-2
		MODEL_MAP_STAGE1_3,			//�X�e�[�W1-3
		MODEL_MAP_STAGE1_BOSS,		//�{�X�X�e�[�W1
		MODEL_MAP_MAX
	}MAP_MODEL;
	/*--- �G�̃p�[�c���f�� ---*/
	typedef enum
	{
		MODEL_ENEMY_WAIST,		//��
		MODEL_ENEMY_HEAD,		//��
		MODEL_ENEMY_BODY,		//��
		MODEL_ENEMY_L_SHOLDER,	//����
		MODEL_ENEMY_R_SHOLDER,	//�E��
		MODEL_ENEMY_LARM,		//���r
		MODEL_ENEMY_RARM,		//�E�r
		MODEL_ENEMY_LHAND,		//����
		MODEL_ENEMY_RHAND,		//�E��
		MODEL_ENEMY_LKNEE,		//���G
		MODEL_ENEMY_RKNEE,		//�E�G
		MODEL_ENEMY_LLEG,		//���r
		MODEL_ENEMY_RLEG,		//�E�r
		MODEL_ENEMY_LFOOT,		//����
		MODEL_ENEMY_RFOOT,		//�E��
		MODEL_ENEMY_MAX
	}ENEMY_PARTS_MODEL;
	/*--- �e�̃��f�� ---*/
	typedef enum
	{
		MODEL_GUN_HANDGUN,				// �n���h�K��
		MODEL_GUN_HEAVYMACHINEGUN,		// �w�r�[�}�V���K��
		MODEL_GUN_SHOTGUN,				// �V���b�g�K��
		MODEL_GUN_LASERGUN,				// ���[�U�[�K��
		MODEL_GUN_ROCKETLAUNCHER,		// ���P�b�g�����`���[
		MODEL_GUN_FLAMESHOT,			// �t���C���V���b�g
		MODEL_GUN_TANKGUN,				// ��Ԃ̏e
		MODEL_GUN_PLANEGUN,				// �퓬�@�̏e
		MODEL_GUN_HELIGUN,				// �w���̏e
		MODEL_KNIFE,					// �i�C�t
		MODEL_GUN_MAX
	}GUN_MODEL;
	/*--- �e�̃��f�� ---*/
	typedef enum
	{
		MODEL_BULLET_SPHERE,			// ��
		MODEL_BULLET_ROCKETLAUNCHER,	// ���P�b�g�����`���[
		MODEL_BULLET_GRENADE,			// �O���l�[�h
		MODEL_BULLET_MAX
	}BULLET_MODEL;

	typedef enum
	{
		//===��Ԃ̃��f��===
		MODEL_TANK_TANKBODY,		// ��
		MODEL_TANK_TANK_FRONTWHEEL,	// �O�^�C��
		MODEL_TANK_TANK_BACKWHEEL,	// ��^�C��
		MODEL_TANK_TANKGUN,			// ����
		MODEL_TANK_MAX
	}TANK_PARTS_MODEL;

	// ���f���̎��
	typedef enum
	{
		//===�퓬�@�̃��f��===
		MODEL_PLANE_BODY,			// �@��
		MODEL_PLANE_GUN,			// ����
		MODEL_PLANE_MAX
	}PLANE_PARTS_MODEL;

	// ���f���̎��
	typedef enum
	{
		//===�w���̃��f��===
		MODEL_HELIBODY,				// �@��
		MODEL_HELIPROPELLER,		// �v���y��
		MODEL_HELIGUN,				// ����
		MODEL_HELI_MAX
	}HELI_PARTS_MODEL;

	// ���f���̎��
	typedef enum
	{
		//===�{�X�̃��f��===
		MODEL_BOSS_BODY,			// ��
		MODEL_BOSS_MAX
	}BOSS_PARTS_MODEL;

	//�S���f���̎��
	typedef enum
	{
		PLAYER_MODEL,
		ENEMY_MODEL,
		MAP_MODEL,
		GUN_MODEL,
		BULLET_MODEL,
		OBSTACLE_MODEL,
		PRISONER_MODEL,
		TANK_MODEL,
		PLANE_MODEL,
		HELI_MODEL,
		BOSS_MODEL,
		TYPE_MAX
	}MODEL_TYPE;

	// ��Q���̎��
	typedef enum
	{
		OBSTACLE_TYPE_BOX = 0,								// �n�R
		OBSTACLE_TYPE_BARREL,								// �M
		OBSTACLE_TYPE_TREE,									// ��
		OBSTACLE_TYPE_CHEST,								// ����
		OBSTACLE_TYPE_SANDBAGS,								// �y�X
		OBSTACLE_TYPE_MAX,									// ��Q��
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

	CModel() {};
	CModel(OBJ_TYPE type);				// �R���X�g���N�^
	~CModel();							// �f�X�g���N�^

	/* �����o�֐� */
	HRESULT Init(void);					// ����������
	void Uninit(void);					// �I������
	void Update(void);					// �X�V����
	void Draw(D3DXMATRIX mat);			// �`�揈��
	void Draw();						// �`�揈��
	void DebugInfo();					// �f�o�b�O���

	/* �ÓI�����o�֐� */
	static void LoadModel(void);									// ���f���̃��[�h
	static void UnLoad(void);										// ���f���̊J��
	static CModel *Create(int type, int modelCount);				// ���f���̃N���G�C�g
	static CModel *CreateSceneManagement(int type, int modelCount);	// ���f���̃N���G�C�g(�V�[���ŊǗ�����)
	static char* GetModelFileName(int nType, int nModelCount);		// ���f���̃t�@�C�����擾

	void NotDrawCalcMtxOnly(D3DXMATRIX *pParentMtx);				// �`�悹���Ƀ}�g���b�N�X�̌v�Z��������

	/* �����o�֐� */
	void SetParent(CModel *pModel)					{ m_pParent = pModel; };							// �e�̐ݒ�
	void SetPosition(D3DXVECTOR3 pos)				{ m_pos = pos; };									// ���f���̃I�t�Z�b�g�w��
	void SetRot(D3DXVECTOR3 rot)					{ m_rot = rot; };									// ��]�̐ݒ�
	void SetSize(D3DXVECTOR3 size)					{ m_size = size; };									// �T�C�Y�̐ݒ�
	void SetType(int type)							{ m_type = type; };									// ���f���^�C�v�̐ݒ�
	void SetModelConut(int nModelCount)				{ m_modelCount = nModelCount; };					// ���f���J�E���g�̐ݒ�
	void SetParentIdx(int nParentIdx)				{ m_nParentIdx = nParentIdx; };						// �e�ԍ��ݒ�
	void SetDieFlag(bool DieFlag)					{ m_bDieFlag = DieFlag; };							// ���S�t���O�̐ݒ�
	void SetColorChangeFlag(bool ColorChangeFlag)	{ m_bColorChangeFlag = ColorChangeFlag; };			// �F�ύX�t���O�̐ݒ�
	void SetAddColor(D3DXCOLOR AddColor)			{ m_AddColor = AddColor; };							// ���Z����F�̐ݒ�
	D3DXVECTOR3 &GetPosition(void)					{ return m_pos; };									// �ʒu�̎擾
	D3DXVECTOR3 &GetRot(void)						{ return m_rot; };									// ��]�̎擾
	D3DXVECTOR3 &GetSize(void)						{ return m_size; };									// �T�C�Y�̎擾
	D3DXVECTOR3 GetvtxMax(int nCnt)					{ return m_Model[MODEL_TYPE::MAP_MODEL][nCnt].vtxMax;};			// ���_����MAX�擾
	D3DXVECTOR3 GetvtxMin(int nCnt)					{ return m_Model[MODEL_TYPE::MAP_MODEL][nCnt].vtxMin; };		// ���_����MIN�擾
	int GetType()									{ return m_type; };									// ���f���^�C�v�̎擾
	int &GetModelCount()							{ return m_modelCount; };							// ���f���J�E���g�̎擾
	int &GetParentIdx()								{ return m_nParentIdx; };							// �e�ԍ��擾
	D3DXMATRIX *GetMatrix(void)						{ return &m_mtxWorld; };							// �}�g���b�N�X�̎擾
	LPD3DXMESH GetMesh(void)						{ return m_Model[m_type][m_modelCount].pMesh; };	// ���b�V���擾
	CCollision *GetCollision()						{ return m_pCollision; };							// �����蔻��̃|�C���^�擾
	bool GetDieFlag()								{ return m_bDieFlag; };								// ���S�t���O�̎擾
	bool GetColorChangeFlag()						{ return m_bColorChangeFlag; };						// �F�ύX�t���O�̎擾
	D3DXCOLOR	GetAddColor()						{ return m_AddColor; };								// ���Z����F�̎擾

private:
	/* �����o�֐� */
	void DrawMesh();			// �`��

	static MODEL m_Model[TYPE_MAX][MAX_ALLMODEL];
	static char *m_PlayerFileName[MODEL_PLAYER_MAX];
	static char *m_EnemyFileName[MODEL_ENEMY_MAX];
	static char *m_GunFileName[MODEL_GUN_MAX];
	static char *m_BulletFileName[MODEL_BULLET_MAX];
	static char *m_MapFileName[MODEL_MAP_MAX];
	static char *m_ObstacleFileName[OBSTACLE_TYPE_MAX];
	static char *m_PrisonerFileName[MODEL_PRISONER_MAX];
	static char *m_TankFileName[MODEL_TANK_MAX];
	static char *m_PlaneFileName[MODEL_PLANE_MAX];
	static char *m_HeliFileName[MODEL_HELI_MAX];
	static char *m_BossFileName[MODEL_BOSS_MAX];

	D3DXVECTOR3		m_pos;					//�ʒu
	D3DXVECTOR3		m_size;					//�T�C�Y
	D3DXVECTOR3		m_posold;				//�ʒu
	D3DXVECTOR3		m_move;					//�ړ���
	D3DXVECTOR3		m_rot;					//��]
	D3DXCOLOR		m_col;					//�J���[
	D3DXCOLOR		m_AddColor;				//���Z����F
	D3DXMATRIX		m_mtxWorld;				//�}�g���b�N�X
	D3DXMATRIX		m_mtxparent;
	CModel			*m_pParent;				//�e�̃|�C���^
	int				m_modelCount;			//���f���̎��
	int				m_type;
	int				m_nIdxModelpalent;		//�e�̃C���f�b�N�X
	int				m_nParentIdx;			//�e�ԍ�
	bool			m_bDieFlag;				// ���S�t���O
	bool			m_bColorChangeFlag;		// �F�ύX�t���O
	CCollision		*m_pCollision;			// �����蔻����
};
#endif
