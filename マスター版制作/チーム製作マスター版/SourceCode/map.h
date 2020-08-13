// =====================================================================================================================================================================
//
// �}�b�v�̏��� [map.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _MAP_H_
#define _MAP_H_

// =====================================================================================================================================================================
// �C���N���[�h�t�@�C��
// =====================================================================================================================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "Scene.h"
#include "inputKeyboard.h"

// =====================================================================================================================================================================
// �O���錾
// =====================================================================================================================================================================
class CModel;
class CEnemy;
class CPrisoner;
class CObstacle;
class CPlayertank;
class CBattlePlane;
class CHelicopter;
class CVehicle;
class CShield;
class CBoss_One;
// =====================================================================================================================================================================
// �}�b�v�N���X
// =====================================================================================================================================================================
class CMap
{
public:
	// ----------- �\���� -----------
	// �E�F�[�u�̃p�����[�^�[
	typedef struct
	{
		int			nType;			// ���
		int			nItemType;		// �m��h���b�v����A�C�e���̃^�C�v
		D3DXVECTOR3	pos;			// �ʒu
		int			nFrame;			// �t���[��
		bool		bEvent;			// �C�x���g�t���O
	} WAVE_PARAM;

	// �E�F�[�u�̏��
	typedef struct
	{
		std::vector<WAVE_PARAM*> EnemyWaveInfo;			// �G�̃E�F�[�u�̃p�����[�^�[
		std::vector<WAVE_PARAM*> PrisonerWaveInfo;		// �ߗ��̃E�F�[�u�p�����[�^�[
		D3DXVECTOR3 EventPos;							// �C�x���g���N����ʒu
	} WAVE_INFO;

	// �}�b�v�̎��
	enum MAP
	{
		MAP_TUTORIAL,		// �`���[�g���A��
		MAP_1_1,			// 1_1
		MAP_1_2,			// 1_2
		MAP_1_3,			// 1_3
		MAP_1_BOSS,			// 1_BOSS
		MAP_MAX
	};

	// �z�u���郂�f���̎��
	enum ARRANGEMENT_MODEL
	{
		ARRANGEMENT_MODEL_MAP,					// �}�b�v
		ARRANGEMENT_MODEL_ENEMY,				// �G
		ARRANGEMENT_MODEL_PRISONER,				// �ߗ�
		ARRANGEMENT_MODEL_OBSTACLE,				// ��Q��
		ARRANGEMENT_MODEL_TANK,					// ���
		ARRANGEMENT_MODEL_BATTLEPLANE,			// �퓬�@
		ARRANGEMENT_MODEL_HELICOPTER,			// �w���R�v�^�[
		ARRANGEMENT_MODEL_BOSS,					// �{�X
		ARRANGEMENT_MODEL_BOSS_ONE,				// �{�X1
		ARRANGEMENT_MODEL_MAX
	};

	// �E�F�[�u�̎��
	enum WAVE
	{
		WAVE_1,									// �E�F�[�u1
		WAVE_2,									// �E�F�[�u2
		WAVE_3,									// �E�F�[�u3
		WAVE_MAX
	};

	CMap();																			// �R���X�g���N�^
	~CMap();																		// �f�X�g���N�^

	/* �ÓI�����o�֐� */
	static	CMap	*MapCreate();													// �}�b�v�̐���

	/* �����o�֐� */
	void			MapUpdate();													// �}�b�v�̍X�V
	void			MapLoad(MAP MapNum);											// �}�b�v�̃��[�h
	void			WaveLoad(WAVE WaveNum);											// �E�F�[�u�̃��[�h
	void			UpdateDieFlag();												// ���S�t���O�m�F�֐�
	void			AllDelete();													// �z�u���Ă��郂�f����S�Ĕj��
	void			WaveCreate(int nModelType, int nType, int nItemType, D3DXVECTOR3 pos);	// Wave�̐���

	int				GetMaxModel();													// ���f���̍ő吔�擾
	int				GetMaxEnemy();													// �G�̍ő吔�擾
	int				GetMaxPrisoner();												// �ߗ��̍ő吔�擾
	int				GetMaxObstacle();												// ��Q���̍ő吔�擾
	int				GetMaxPlayerTank();												// ��Ԃ̍ő吔�擾
	int				GetMaxBattlePlane();											// �퓬�@�̍ő吔�擾
	int				GetMaxHelicopter();												// �w���̍ő吔�擾

	// �� ������
	int				GetMaxBoss_One();												//

	MAP				GetMapNum() { return m_MapNum; };								// �}�b�v�ԍ��擾
	LPD3DXMESH		GetMesh(int nCnt);												// ���b�V���̎擾
	CModel			*GetModel(int nCnt) { return m_pMapModel[nCnt]; };				// ���f���̎擾
	CEnemy			*GetEnemy(int nCnt) { return m_pEnemy[nCnt]; };					// �G�̎擾
	CPrisoner		*GetPrisoner(int nCnt) { return m_pPrisoner[nCnt]; };			// �ߗ��̎擾
	CObstacle		*GetObstacle(int nCnt) { return m_pObstacle[nCnt]; };			// ��Q���̎擾
	CPlayertank		*GetPlayertank(int nCnt) { return m_pPlayerTank[nCnt]; };		// ��Ԃ̎擾
	CBattlePlane	*GetBattlePlane(int nCnt) { return m_pBattlePlane[nCnt]; };		// �퓬�@�̎擾
	CHelicopter		*GetHelicopter(int nCnt) { return m_pHelicopter[nCnt]; };		// �w���R�v�^�[�̎擾
	CBoss_One		*GetBoss_One(int nCnt) { return m_pBoss_One[nCnt]; };			// �{�X1�̎擾

	WAVE_INFO		GetWaveInfo(int nWaveNum) { return m_aWaveInfo[nWaveNum]; };	// �E�F�[�u���̎擾
	D3DXVECTOR3		GetTransitionPos() { return m_TransitionPos; };					// �J�ڂ��邽�߂̈ʒu�̎擾
	int				GetTransitionMapID() { return m_TransitionMapID; }				// ���ɑJ�ڂ��邽�߂̃}�b�v�ԍ��̎擾
	CShield			*GetShield(int nCnt) { return m_pShield[nCnt]; };				// shield�̎擾
private:
	/* �����o�֐� */
	void			MapModelLoad();																// �z�u���郂�f���̃��[�h
	void			MapModelSave();																// �z�u���郂�f���̃Z�[�u

	void			MapModelCreate(int ModelType, int nType, D3DXVECTOR3 pos, int nItemType);	// �z�u���郂�f���̐���
	void			LoadSuccessMessage(int ModelType);											// �ǂݍ��ݐ������̌��ʕ\��

	void			SaveModelHeader(FILE *pFile, int ModelType);								// �Z�[�u���郂�f���̃w�b�_�[
	void			SaveModelContents(FILE *pFile, int ModelType, int nCnt, int nNum);			// �Z�[�u���郂�f���̏��
	void			SaveBGContents(FILE *pFile);												// �Z�[�u����w�i�̏��

	size_t			GetMaxMapModel(int ModelType);												// �z�u���郂�f���̍ő吔�擾
	void			*GetMapModel(int ModelType, int nCnt);										// �z�u���郂�f���̃|�C���^

	void			ModelDelete(int nNowSelect);												// �z�u���郂�f�����f���[�g
	void			ModelCreat();																// �z�u���郂�f���𐶐�

	D3DXVECTOR3		GetMapModelPos(int nNowSelect);												// �I�����Ă��郂�f���̈ʒu�̎擾
	void			SetMapModelPos(D3DXVECTOR3 pos, int nNowSelect);							// �I�����Ă��郂�f���̈ʒu�̐ݒ�
	void			SetMapModelColorChangeFlag(bool bFlag, int nNowSelect);						// �I�����Ă��郂�f���̐F�𔼓����ɂ���t���O�̐ݒ�
	void			MapModelTab();																// �}�b�v�ɔz�u���郂�f���̃^�u
	void			MapModelSet();																// �}�b�v�ɔz�u���郂�f���̐ݒu
	void			ComboBoxAll(int nNowSelect);												// �S�ẴR���{�{�b�N�X
	void			MapComboBox(int &nSelectType, int nNowSelect);								// �}�b�v�̃R���{�{�b�N�X
	void			MapTypeComboBox();															// �}�b�v�̎�ނ̃R���{�{�b�N�X
	void			ObstacleTypeComboBox(int &nSelectType, int nNowSelect);						// ��Q���̎�ނ̃R���{�{�b�N�X
	void			EnemyTypeComboBox(int &nSelectType, int nNowSelect);						// �G�̎�ނ̃R���{�{�b�N�X
	void			PrisonerDropTypeComboBox(int &nSelectType, int nNowSelect);					// �ߗ��̃h���b�v�^�C�v�̃R���{�{�b�N�X
	void			PrisonerItemTypeComboBox(int &nSelectType, int nNowSelect);					// �ߗ��̃A�C�e���^�C�v�̃R���{�{�b�N�X
	void			SetSelectMapModelPosRDest(D3DXVECTOR3 posR);								// �I�����Ă��郂�f���𒍎��_�̖ړI�n�ɐݒ�

	/* �ÓI�����o�ϐ� */
	static char					*m_MapModelFileName[MAP_MAX];				// �}�b�v���f���t�@�C����
	static char					*m_WaveFileName[WAVE_MAX];					// �E�F�[�u�t�@�C����

	static MAP					m_MapNum;									// �}�b�v�ԍ�
	static WAVE					m_WaveNum;									// �E�F�[�u�ԍ�
	static ARRANGEMENT_MODEL	m_ArrangmentModel;							// �z�u���郂�f���̎��
	static WAVE_INFO			m_aWaveInfo[WAVE_MAX];						// �E�F�[�u�̏��

	/* �����o�ϐ� */
	std::vector<CModel*>		m_pMapModel;								// �ϒ��z�� �ݒu����}�b�v���f��
	std::vector<CEnemy*>		m_pEnemy;									// �ϒ��z�� �ݒu�����G�l�~�[
	std::vector<CPrisoner*>		m_pPrisoner;								// �ϒ��z�� �ݒu�����ߗ�
	std::vector<CObstacle*>		m_pObstacle;								// �ϒ��z�� �ݒu������Q��
	std::vector<CPlayertank*>	m_pPlayerTank;								// �ϒ��z�� �ݒu�������
	std::vector<CBattlePlane*>	m_pBattlePlane;								// �ϒ��z�� �ݒu�����퓬�@
	std::vector<CHelicopter*>	m_pHelicopter;								// �ϒ��z�� �ݒu�����w��
	std::vector<CVehicle*>		m_pVehicle;									// �ϒ��z�� �ݒu������蕨
	std::vector<CShield*>		m_pShield;
	// �� ������
	std::vector<CBoss_One*>		m_pBoss_One;								// �ϒ��z�� �ݒu�����{�X1

	int							m_nOldSelect;								// �O��I�����Ă������m�̔ԍ�
	D3DXVECTOR3					m_WavePos;									// �E�F�[�u�̈ʒu
	D3DXVECTOR3					m_TransitionPos;							// �J�ڂ���ʒu
	D3DXVECTOR3					m_CameraPos;								// �J�����̈ʒu
	int							m_TransitionMapID;							// ���ɑJ�ڂ���}�b�v�̔ԍ�
	int							m_nBGTexID;									// �w�i�̃e�N�X�`���ԍ�
	bool						m_bCameraFollowing;							// �J������Ǐ]����t���O
	bool						m_bMapExclusion;							// �}�b�v���f���ȊO�K�p����t���O
};

#endif