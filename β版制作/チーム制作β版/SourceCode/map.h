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

// =====================================================================================================================================================================
// �E�F�[�u�̏��
// =====================================================================================================================================================================
typedef struct
{
	D3DXVECTOR3 pos;			// ���_���W
	int			nFrame;			// �t���[��
	//bool		bEvent;
} WAVE_INFO;

typedef struct
{
	std::vector<WAVE_INFO> EnemyWaveInfo;
	std::vector<WAVE_INFO> horyoWaveInfo;

} WAVE;




// =====================================================================================================================================================================
// �}�b�v�N���X
// =====================================================================================================================================================================
class CMap
{
public:
	// �}�b�v�̎��
	enum MAP
	{
		MAP_1,			// 1
		MAP_2,			// 2
		MAP_MAX
	};

	// �G�f�B�^�[�̎��
	enum EDITOR
	{
		EDITOR_MAP,			// �}�b�v�G�f�B�^�[
		EDITOR_WAVE,		// �E�F�[�u�G�f�B�^�[
		EDITOR_MAX
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

	// �����̎��
	enum PLATOON
	{
		PLATOON_1,								// ����1
		PLATOON_2,								// ����2
		PLATOON_3,								// ����3
		PLATOON_MAX
	};

	CMap();																			// �R���X�g���N�^
	~CMap();																		// �f�X�g���N�^

	/* �ÓI�����o�֐� */
	static	CMap	*MapCreate();													// �}�b�v�̐���

	void	MapUpdate();															// �}�b�v�̍X�V
	void	MapLoad(MAP MapNum);													// �}�b�v�̃��[�h
	void	WaveLoad(WAVE WaveNum);													// �E�F�[�u�̃��[�h
	void	WaveCreate(WAVE WaveNum, int ModelType, int &frame);					// �E�F�[�u�̐���

	/* �����o�֐� */
	int				GetMaxModel();													// ���f���̍ő吔�擾
	int				GetMaxEnemy();													// �G�̍ő吔�擾
	int				GetMaxPrisoner();												// �ߗ��̍ő吔�擾
	int				GetMaxObstacle();												// ��Q���̍ő吔�擾
	int				GetMaxPlayerTank();												// ��Ԃ̍ő吔�擾
	int				GetMaxBattlePlane();											// �퓬�@�̍ő吔�擾
	int				GetMaxHelicopter();												// �w���̍ő吔�擾
	LPD3DXMESH		GetMesh(int nCnt);												// ���b�V���̎擾
	CModel			*GetModel(int nCnt)			{ return m_pMapModel[nCnt]; };		// ���f���̎擾
	CEnemy			*GetEnemy(int nCnt)			{ return m_pEnemy[nCnt]; };			// �G�̎擾
	CPrisoner		*GetPrisoner(int nCnt)		{ return m_pPrisoner[nCnt]; };		// �ߗ��̎擾
	CObstacle		*GetObstacle(int nCnt)		{ return m_pObstacle[nCnt]; };		// ��Q���̎擾
	CPlayertank		*GetPlayertank(int nCnt)	{ return m_pPlayerTank[nCnt]; };	// ��Ԃ̎擾
	CBattlePlane	*GetBattlePlane(int nCnt)	{ return m_pBattlePlane[nCnt]; };	// �퓬�@�̎擾
	CHelicopter		*GetHelicopter(int nCnt)	{ return m_pHelicopter[nCnt]; };	// �w���R�v�^�[�̎擾

	void			UpdateDieFlag();												// ���S�t���O�m�F�֐�

private:
	/* �����o�֐� */
	void			MapModelLoad();													// �z�u���郂�f���̃��[�h
	void			MapModelSave();													// �z�u���郂�f���̃Z�[�u

	void			MapModelCreate(int ModelType, int nType, 
											D3DXVECTOR3 pos, int nLife, D3DXVECTOR3 size);	// �z�u���郂�f���̐���
	void			LoadFailureMessage(int ModelType);										// �ǂݍ��ݎ��s���̌x���\��
	void			LoadSuccessMessage(int ModelType);										// �ǂݍ��ݐ������̌��ʕ\��
	char			*WaveFileName(int ModelType);											// �e�E�F�[�u�t�@�C����

	void			SaveModelHeader(FILE *pFile, int ModelType);							// �Z�[�u���郂�f���̃w�b�_�[
	void			SaveModelContents(FILE *pFile,int ModelType, int nCnt, int nNum);		// �Z�[�u���郂�f���̏��
	void			SaveWaveContents(FILE *pFile, int ModelType, int nCnt);					// �Z�[�u����E�F�[�u�̏��

	unsigned int	GetMaxMapModel(int ModelType);									// �z�u���郂�f���̍ő吔�擾
	void			*GetMapModel(int ModelType, int nCnt);							// �z�u���郂�f���̃|�C���^

	void			AllSaveButton();														// �z�u�������f����S�ăZ�[�u����{�^��
	void			AllLoadButton();														// �z�u�������f����S�ă��[�h����{�^��
	void			AllDeleteButton();														// �z�u�������f����S�ăf���[�g����{�^��
	void			ModelDeleteButton(int nNowSelect);										// �z�u���郂�f�����f���[�g����{�^��
	void			ModelCreateButton();													// �z�u���郂�f���𐶐�����{�^��
	
	D3DXVECTOR3		GetMapModelPos(int nNowSelect);									// �I�����Ă��郂�f���̈ʒu�̎擾
	void			SetMapModelPos(D3DXVECTOR3 pos, int nNowSelect);				// �I�����Ă��郂�f���̈ʒu�̐ݒ�
	void			SetMapModelColorChangeFlag(bool bFlag, int nNowSelect);			// �I�����Ă��郂�f���̐F�𔼓����ɂ���t���O�̐ݒ�
	void			MapModelTab();															// �}�b�v�ɔz�u���郂�f���̃^�u
	void			MapModelSet();															// �}�b�v�ɔz�u���郂�f���̐ݒu
	void			ComboBoxAll(int nNowSelect);											// �S�ẴR���{�{�b�N�X
	bool			ObstacleComboBox(int &nType);											// ��Q���̃R���{�{�b�N�X
	bool			EnemyComboBox(int &nType);												// �G�̃R���{�{�b�N�X
	bool			PrisonerComboBox(int &nType);											// �ߗ��̃R���{�{�b�N�X
	void			SetSelectMapModelPosRDest(D3DXVECTOR3 posR);							// �I�����Ă��郂�f���𒍎��_�̖ړI�n�ɐݒ�

	/* �ÓI�����o�ϐ� */
	static char					*m_MapModelFileName[MAP_MAX];				// �}�b�v���f���t�@�C����

	static char					*m_EnemyWaveFileName[WAVE_MAX];				// �G�t�@�C����
	static char					*m_PrisonerWaveFileName[WAVE_MAX];			// �ߗ��t�@�C����
	static char					*m_PlayerTankWaveFileName[WAVE_MAX];		// ��ԃt�@�C����
	static char					*m_BattlePlaneWaveFileName[WAVE_MAX];		// �퓬�@�t�@�C����
	static char					*m_HelicopterWaveFileName[WAVE_MAX];		// �w���t�@�C����

	static MAP					m_MapNum;									// �}�b�v�ԍ�
	static WAVE					m_WaveNum;									// �E�F�[�u�ԍ�
	static EDITOR				m_Editor;									// �G�f�B�^�[�̎��
	static ARRANGEMENT_MODEL	m_ArrangmentModel;							// �z�u���郂�f���̎��

	/* �����o�ϐ� */
	std::vector<CModel*>		m_pMapModel;								// �ϒ��z�� �ݒu���郂�f��
	std::vector<CEnemy*>		m_pEnemy;									// �ϒ��z�� �ݒu�����G�l�~�[
	std::vector<CPrisoner*>		m_pPrisoner;								// �ϒ��z�� �ݒu�����ߗ�
	std::vector<CObstacle*>		m_pObstacle;								// �ϒ��z�� �ݒu������Q��
	std::vector<CPlayertank*>	m_pPlayerTank;								// �ϒ��z�� �ݒu�������
	std::vector<CBattlePlane*>	m_pBattlePlane;								// �ϒ��z�� �ݒu�����퓬�@
	std::vector<CHelicopter*>	m_pHelicopter;								// �ϒ��z�� �ݒu�����w��
	std::vector<CVehicle*>		m_pVehicle;									// �ϒ��z�� �ݒu������蕨

	int							m_nOldSelect;								// �O��I�����Ă������m�̔ԍ�
	int							m_nWaveID;									// �E�F�[�u�̏o���ԍ�
	WAVE_INFO					m_aWaveInfo[128];							// �E�F�[�u�̏��
	D3DXVECTOR3					m_WavePos;									// �E�F�[�u�̈ʒu
};
#endif