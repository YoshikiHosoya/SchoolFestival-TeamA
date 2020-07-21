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
		EDITOR_PLATOON,		// �����G�f�B�^�[
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
	CMap();																			// �R���X�g���N�^
	~CMap();																		// �f�X�g���N�^

	/* �ÓI�����o�֐� */
	static	CMap	*MapCreate(MAP MapNum);											// �}�b�v�̐���
	void	MapUpdate();															// �}�b�v�̍X�V

	/* �����o�֐� */
	int				GetMaxModel();													// ���f���̍ő吔�擾
	int				GetMaxEnemy();													// �G�̍ő吔�擾
	int				GetMaxPrisoner();												// �ߗ��̍ő吔�擾
	int				GetMaxObstacle();												// ��Q���̍ő吔�擾
	int				GetMaxPlayerTank();												// ��Ԃ̍ő吔�擾
	int				GetMaxBattlePlane();											// �퓬�@�̍ő吔�擾
	int				GetMaxHelicopter();												// �w���̍ő吔�擾
	LPD3DXMESH		GetMesh(int nCnt);												// ���b�V���̎擾
	CModel			*GetModel(int nCnt)			{ return m_pModel[nCnt]; };			// ���f���̎擾
	CEnemy			*GetEnemy(int nCnt)			{ return m_pEnemy[nCnt]; };			// �G�̎擾
	CPrisoner		*GetPrisoner(int nCnt)		{ return m_pPrisoner[nCnt]; };		// �ߗ��̎擾
	CObstacle		*GetObstacle(int nCnt)		{ return m_pObstacle[nCnt]; };		// ��Q���̎擾
	CPlayertank		*GetPlayertank(int nCnt)	{ return m_pPlayerTank[nCnt]; };	// ��Ԃ̎擾
	CBattlePlane	*GetBattlePlane(int nCnt)	{ return m_pBattlePlane[nCnt]; };	// �퓬�@�̎擾
	CHelicopter		*GetHelicopter(int nCnt)	{ return m_pHelicopter[nCnt]; };	// �w���R�v�^�[�̎擾

	void			UpdateDieFlag();												// ���S�t���O�m�F�֐�

private:
	/* �����o�֐� */
	void			ArrangementModelLoad();													// �z�u���郂�f���̃��[�h
	void			ArrangementModelCreate(int ModelType, int nType, 
											D3DXVECTOR3 pos, int nLife, D3DXVECTOR3 size);	// �z�u���郂�f���̐���
	void			LoadFailureMessage(int ModelType);										// �ǂݍ��ݎ��s���̌x���\��
	void			LoadSuccessMessage(int ModelType);										// �ǂݍ��ݐ������̌��ʕ\��

	char			*ArrangementModelFileName(int ModelType);								// �z�u���郂�f���t�@�C����(�����z�u)

	void			SaveModelHeader(FILE *pFile, int ModelType);							// �Z�[�u���郂�f���̃w�b�_�[
	void			SaveModelContents(FILE *pFile,int ModelType, int nCnt);					// �Z�[�u���郂�f���̏��

	unsigned int	GetMaxArrangementModel(int ModelType);									// �z�u���郂�f���̍ő吔�擾
	void			*GetArrangementModel(int ModelType, int nCnt);							// �z�u���郂�f���̃|�C���^
	void			ArrangementModelSave(int ModelType);									// �z�u���郂�f���̃Z�[�u

	void			AllSaveButton();														// �z�u�������f����S�ăZ�[�u����{�^��
	void			MapModelTab();															// �}�b�v�ɔz�u���郂�f���̃^�u
	void			ObstacleSet();															// ��Q���̐ݒu
	void			EnemySet();																// �G�̐ݒu
	void			PlayerTankSet();														// ��Ԃ̐ݒu
	void			BattlePlaneSet();														// �퓬�@�̐ݒu
	void			HelicopterSet();														// �w���̐ݒu
	bool			ObstacleComboBox(int &nType);											// ��Q���̃R���{�{�b�N�X
	void			PrisonerSet();															// �ߗ��̐ݒu
	bool			EnemyComboBox(int &nType);												// �G�̃R���{�{�b�N�X
	bool			PrisonerComboBox(int &nType);											// �ߗ��̃R���{�{�b�N�X
	void			SetSelectMapModelPosRDest(D3DXVECTOR3 posR);							// �I�����Ă��郂�f���𒍎��_�̖ړI�n�ɐݒ�

	/* �ÓI�����o�ϐ� */
	static char					*m_MapFileName[MAP_MAX];					// �}�b�v�t�@�C����
	static char					*m_EnemyFileName[MAP_MAX];					// �G�t�@�C����
	static char					*m_PrisonerFileName[MAP_MAX];				// �ߗ��t�@�C����
	static char					*m_ObstacleFileName[MAP_MAX];				// ��Q���t�@�C����
	static char					*m_PlayerTankFileName[MAP_MAX];				// ��ԃt�@�C����
	static char					*m_BattlePlaneFileName[MAP_MAX];			// �퓬�@�t�@�C����
	static char					*m_HelicopterFileName[MAP_MAX];				// �w���t�@�C����
	static MAP					m_MapNum;									// �}�b�v�ԍ�
	static EDITOR				m_Editor;									// �G�f�B�^�[�̎��
	static int					m_ArrangmentModel;							// �z�u���郂�f���̎��

	/* �����o�ϐ� */
	std::vector<CModel*>		m_pModel;									// �ϒ��z�� �ݒu���郂�f��
	std::vector<CEnemy*>		m_pEnemy;									// �ϒ��z�� �ݒu�����G�l�~�[
	std::vector<CPrisoner*>		m_pPrisoner;								// �ϒ��z�� �ݒu�����ߗ�
	std::vector<CObstacle*>		m_pObstacle;								// �ϒ��z�� �ݒu������Q��
	std::vector<CPlayertank*>	m_pPlayerTank;								// �ϒ��z�� �ݒu�������
	std::vector<CBattlePlane*>	m_pBattlePlane;								// �ϒ��z�� �ݒu�����퓬�@
	std::vector<CHelicopter*>	m_pHelicopter;								// �ϒ��z�� �ݒu�����w��
	int							m_nOldSelect;								// �O��I�����Ă������m�̔ԍ�
};
#endif