#pragma once
// =====================================================================================================================================================================
//
// ���f���̏��� [Model.h]
// Author :Hanzawa
//
// =====================================================================================================================================================================
#ifndef _MODEL_H_
#define _MODEL_H_
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Scene.h"

#define MAX_ALLMODEL (130)
// =====================================================================================================================================================================
// �O���錾
// =====================================================================================================================================================================
class CCollision;
//�����_�����O�N���X
class CModel : public CScene
{
public:
	/*--- ���f���ꗗ ---*/
	typedef enum
	{
		//===�v���C���[�̃��f��===
		MODEL_PLAYER_WAIST,				// �v���C���[�̍�
		MODEL_PLAYER_BODY,				// �v���C���[�̑�
		MODEL_PLAYER_HEAD,				// �v���C���[�̓�
		MODEL_PLAYER_L_SHOLDER,			// �v���C���[�̍���
		MODEL_PLAYER_R_SHOLDER,			// �v���C���[�̉E��
		MODEL_PLAYER_LARM,				// �v���C���[�̍��r
		MODEL_PLAYER_RARM,				// �v���C���[�̉E�r
		MODEL_PLAYER_LHAND,				// �v���C���[�̍���
		MODEL_PLAYER_RHAND,				// �v���C���[�̉E��
		MODEL_PLAYER_LKNEE,				// �v���C���[�̍��G
		MODEL_PLAYER_RKNEE,				// �v���C���[�̉E�G
		MODEL_PLAYER_LLEG,				// �v���C���[�̍��r
		MODEL_PLAYER_RLEG,				// �v���C���[�̉E�r
		MODEL_PLAYER_LFOOT,				// �v���C���[�̍���
		MODEL_PLAYER_RFOOT,				// �v���C���[�̉E��
		//===�G�̃��f��===
		//�l�^
		MODEL_ENEMY_HUMAN_WAIST=100,			// ��
		MODEL_ENEMY_HUMAN_HEAD,					// ��
		MODEL_ENEMY_HUMAN_BODY,					// ��
		MODEL_ENEMY_HUMAN_L_SHOLDER,			// ����
		MODEL_ENEMY_HUMAN_R_SHOLDER,			// �E��
		MODEL_ENEMY_HUMAN_LARM,					// ���r
		MODEL_ENEMY_HUMAN_RARM,					// �E�r
		MODEL_ENEMY_HUMAN_LHAND,				// ����
		MODEL_ENEMY_HUMAN_RHAND,				// �E��
		MODEL_ENEMY_HUMAN_LKNEE,				// ���G
		MODEL_ENEMY_HUMAN_RKNEE,				// �E�G
		MODEL_ENEMY_HUMAN_LLEG,					// ���r
		MODEL_ENEMY_HUMAN_RLEG,					// �E�r
		MODEL_ENEMY_HUMAN_LFOOT,				// ����
		MODEL_ENEMY_HUMAN_RFOOT,				// �E��

		//�w��
		MODEL_ENEMY_HELICOPTER_BODY,			// ����
		MODEL_ENEMY_HELICOPTER_PROPELLER,		// �v���y��

		//MeltyHoney(???)
		MODEL_ENEMY_MELTYHONEY_BODY,			// ����
		MODEL_ENEMY_MELTYHONEY_WHEEL,			// �z�C�[��

		//Zycocca(???)
		MODEL_ENEMY_ZYCOCCA_BODY,				// ����
		MODEL_ENEMY_ZYCOCCA_WHEEL,				// �z�C�[��

		//===�}�b�v�̃��f��===
		MODEL_MAP_TUTORIAL=200,			// �`���[�g���A���}�b�v
		MODEL_MAP_STAGE1_1,				// �X�e�[�W1-1
		MODEL_MAP_STAGE1_2,				// �X�e�[�W1-2
		MODEL_MAP_STAGE1_3,				// �X�e�[�W1-3
		MODEL_MAP_STAGE1_BOSS,			// �{�X�X�e�[�W1
		MODEL_MAP_STAGE2_1,				// �X�e�[�W2-1
		MODEL_MAP_STAGE2_2,				// �X�e�[�W2-2
		MODEL_MAP_STAGE2_3,				// �X�e�[�W2-3
		MODEL_MAP_STAGE2_BOSS,			// �{�X�X�e�[�W2
		//===�e�̃��f��===
		MODEL_GUN_HANDGUN=300,			// �n���h�K��
		MODEL_GUN_HEAVYMACHINEGUN,		// �w�r�[�}�V���K��
		MODEL_GUN_SHOTGUN,				// �V���b�g�K��
		MODEL_GUN_LASERGUN,				// ���[�U�[�K��
		MODEL_GUN_ROCKETLAUNCHER,		// ���P�b�g�����`���[
		MODEL_GUN_FLAMESHOT,			// �t���C���V���b�g
		MODEL_GUN_TANKGUN,				// ��Ԃ̏e
		MODEL_GUN_PLANEGUN,				// �퓬�@�̏e
		MODEL_GUN_HELIGUN,				// �w���̏e
		MODEL_GUN_BALKAN,				// �o���J��
		MODEL_GUN_FLAMETHROWER,			// �Ή����ˊ�
		MODEL_GUN_INCENDIARY,			// �ĈΒe
		MODEL_KNIFE,					// �i�C�t
		//===�e�̃��f��===
		MODEL_BULLET_SPHERE=400,		// ��
		MODEL_BULLET_ROCKETLAUNCHER,	// ���P�b�g�����`���[
		MODEL_BULLET_GRENADE,			// �O���l�[�h
		MODEL_BULLET_TANKGRENADE,		// ��Ԃ̃O���l�[�h
		MODEL_BULLET_MISSILE,			// �~�T�C��
		//===��Q���̃��f��===
		OBSTACLE_TYPE_BOX=500,			// �n�R
		OBSTACLE_TYPE_BARREL,			// �M
		OBSTACLE_TYPE_BARRELBOMB,		// �M���e
		OBSTACLE_TYPE_TREE,				// ��
		OBSTACLE_TYPE_CHEST,			// ����
		OBSTACLE_TYPE_SANDBAGS,			// �y�X
		OBSTACLE_TYPE_CAR,				// ��
		OBSTACLE_TYPE_MAX,				// �ő吔(�v�Z�p)

		//===�ߗ��̃��f��===
		MODEL_PRISONER_WAIST=600,		// �ߗ��̍�
		MODEL_PRISONER_BODY,			// �ߗ��̑�
		MODEL_PRISONER_HEAD,			// �ߗ��̓�
		MODEL_PRISONER_L_SHOLDER,		// �ߗ��̍���
		MODEL_PRISONER_R_SHOLDER,		// �ߗ��̉E��
		MODEL_PRISONER_LARM,			// �ߗ��̍��r
		MODEL_PRISONER_RARM,			// �ߗ��̉E�r
		MODEL_PRISONER_LHAND,			// �ߗ��̍���
		MODEL_PRISONER_RHAND,			// �ߗ��̉E��
		MODEL_PRISONER_LKNEE,			// �ߗ��̍��G
		MODEL_PRISONER_RKNEE,			// �ߗ��̉E�G
		MODEL_PRISONER_LLEG,			// �ߗ��̍��r
		MODEL_PRISONER_RLEG,			// �ߗ��̉E�r
		MODEL_PRISONER_LFOOT,			// �ߗ��̍���
		MODEL_PRISONER_RFOOT,			// �ߗ��̉E��

		//===��Ԃ̃��f��===
		MODEL_TANK_TANKBODY=700,		// ��
		MODEL_TANK_TANK_FRONTWHEEL,		// �O�^�C��
		MODEL_TANK_TANK_BACKWHEEL,		// ��^�C��
		MODEL_TANK_TANKGUN,				// ����
		//MODEL_TANK_TANKHEAD,
		//===�퓬�@�̃��f��===
		MODEL_PLANE_BODY=800,			// �@��
		MODEL_PLANE_GUN,			// ����
		//===�w���̃��f��===
		MODEL_HELIBODY=900,				// �@��
		MODEL_HELIPROPELLER,			// �v���y��
		MODEL_HELIGUN,					// ����
		//===2�ʃ{�X�̃��f��===
		MODEL_BOSS_BODY=1000,			// ��
		//===�{�X �h���S���m�X�P�̃��f��===
		MODEL_BOSSONE_BODY=1100,		// ��
		MODEL_BOSSONE_HEAD,				// ��
		MODEL_BOSSONE_KNEE_L_FRONT,		// ���O���
		MODEL_BOSSONE_KNEE_L_REAR,		// ������
		MODEL_BOSSONE_KNEE_R_FRONT,		// �E�O���
		MODEL_BOSSONE_KNEE_R_REAR,		// �E����
		MODEL_BOSSONE_KNEE2_L_FRONT,	// ���O���2
		MODEL_BOSSONE_KNEE2_L_REAR,		// ������2
		MODEL_BOSSONE_KNEE2_R_FRONT,	// �E�O���2
		MODEL_BOSSONE_KNEE2_R_REAR,		// �E����2
		MODEL_BOSSONE_LEG_L_FRONT,		// ���O����
		MODEL_BOSSONE_LEG_L_REAR,		// ���㉺��
		MODEL_BOSSONE_LEG_R_FRONT,		// �E�O����
		MODEL_BOSSONE_LEG_R_REAR,		// �E�㉺��
		MODEL_BOSSONE_L_VENTILATION,	// �S��
		MODEL_BOSSONE_R_VENTILATION,	// �S��
		MODEL_BOSSONE_LIGHT_L_FRONT,	// �d�C
		MODEL_BOSSONE_LIGHT_L_REAR,		// �d�C
		MODEL_BOSSONE_LIGHT_R_FRONT,	// �d�C
		MODEL_BOSSONE_LIGHT_R_REAR,		// �d�C
		MODEL_BOSSONE_GUN_BALKAN,		// �o���J��
		MODEL_BOSSONE_GUN_FLAMETHROWER,	// �Ή����ˊ�
		MODEL_BOSSONE_GUN_INCENDIARY,	// �ĈΒe
		//===�����f��===
		MODEL_WEPON_SHIELD=1200,		// ��
		MODEL_MAX
	}CHARA_MODEL;
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
		BOSS_ONE_MODEL,
		WEPON_MODEL,
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
		CHARA_MODEL ModelID;

	} MODEL;
	typedef struct
	{
		char *modelFileName;
		CHARA_MODEL FileModelID;
	}MODEL_FILE_NAME;

	CModel() {};
	CModel(OBJ_TYPE type);				// �R���X�g���N�^
	virtual~CModel();							// �f�X�g���N�^

	/* �����o�֐� */
	HRESULT Init(void);					// ����������
	void Uninit(void);					// �I������
	void Update(void);					// �X�V����
	void Draw(D3DXMATRIX mat);			// �`�揈��
	void Draw();						// �`�揈��
	virtual void DebugInfo();			// �f�o�b�O���

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
	void SetType(int type)					;					// ���f���^�C�v�̐ݒ�
	void SetModelConut(int nModelCount)		;					// ���f���J�E���g�̐ݒ�
	void SetParentIdx(int nParentIdx)				{ m_nParentIdx = nParentIdx; };						// �e�ԍ��ݒ�
	void SetDieFlag(bool DieFlag)					{ m_bDieFlag = DieFlag; };							// ���S�t���O�̐ݒ�
	void SetColorChangeFlag(bool ColorChangeFlag)	{ m_bColorChangeFlag = ColorChangeFlag; };			// �F�ύX�t���O�̐ݒ�
	void SetAddColor(D3DXCOLOR AddColor)			{ m_AddColor = AddColor; };							// ���Z����F�̐ݒ�
	void SetDisp(bool bDisp)						{ m_bDisp = bDisp; };								// ��ʂɕ`�悷�邩�ǂ���
	D3DXVECTOR3 &GetPosition(void)					{ return m_pos; };									// �ʒu�̎擾
	D3DXVECTOR3 *GetPositionPtr()					{ return &m_pos; };									// �ʒu�̎擾�@�|�C���^��
	D3DXVECTOR3 &GetRot(void)						{ return m_rot; };									// ��]�̎擾
	D3DXVECTOR3 &GetSize(void)						{ return m_size; };									// �T�C�Y�̎擾
	D3DXVECTOR3 GetvtxMax(int nCnt)					{ return m_vModel[nCnt]->vtxMax;};					// ���_����MAX�擾
	D3DXVECTOR3 GetvtxMin(int nCnt)					{ return m_vModel[nCnt]->vtxMin; };					// ���_����MIN�擾
	int GetType()									{ return m_type; };									// ���f���^�C�v�̎擾
	int &GetModelCount()							{ return m_modelCount; };							// ���f���J�E���g�̎擾
	int &GetParentIdx()								{ return m_nParentIdx; };							// �e�ԍ��擾
	D3DXMATRIX *GetMatrix(void)						{ return &m_mtxWorld; };							// �}�g���b�N�X�̎擾
	LPD3DXMESH GetMesh(void);																			// ���b�V���擾
	CCollision *GetCollision()						{ return m_pCollision; };							// �����蔻��̃|�C���^�擾
	bool GetDieFlag()								{ return m_bDieFlag; };								// ���S�t���O�̎擾
	bool GetColorChangeFlag()						{ return m_bColorChangeFlag; };						// �F�ύX�t���O�̎擾
	D3DXCOLOR	GetAddColor()						{ return m_AddColor; };								// ���Z����F�̎擾
	bool		GetDisp()							{ return m_bDisp; };								// �`�悷�邩�ǂ����擾
	void DeleteCollision();																				// ����̏���
	void SetModelID(CHARA_MODEL model);
	static int GetModelID(CHARA_MODEL model);

private:
	/* �����o�֐� */
	void DrawMesh();			// �`��
	static std::vector<MODEL_FILE_NAME> m_vModelFileName;
	static std::vector<MODEL*>m_vModel;

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
	bool			m_bDisp;				// �`�悷�邩�ǂ���
	CCollision		*m_pCollision;			// �����蔻����
	CHARA_MODEL		m_modelID;
	int				m_ModelCountID;
};
#endif
