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

	// �}�b�v�ɔz�u���郂�f���̎��
	enum MAP_MODEL_TYPE
	{
		MAP_MODEL_TYPE_ENEMY,					// �G
		MAP_MODEL_TYPE_OBSTACLE,				// ��Q��
		MAP_MODEL_TYPE_PRISONER,				// �ߗ�
		MAP_MODEL_TYPE_PLAYERTANK,				// �v���C���[�p�̐��
		MAP_MODEL_TYPE_MAX
	};

	CMap();																	// �R���X�g���N�^
	~CMap();																// �f�X�g���N�^

	/* �ÓI�����o�֐� */
	static	CMap	*MapCreate(MAP MapNum);									// �}�b�v�̐���
	void	MapUpdate();											// �}�b�v�̍X�V

	/* �����o�֐� */
	int				GetMaxModel();												// ���f���̍ő吔�擾
	int				GetMaxEnemy();												// �G�̍ő吔�擾
	int				GetMaxPrisoner();											// �ߗ��̍ő吔�擾
	int				GetMaxObstacle();											// ��Q���̍ő吔�擾
	int				GetMaxPlayerTank();											// ��Ԃ̍ő吔�擾
	LPD3DXMESH		GetMesh(int nCnt);											// ���b�V���̎擾
	CModel			*GetModel(int nCnt) { return m_pModel[nCnt]; };				// ���f���̎擾
	CEnemy			*GetEnemy(int nCnt) { return m_pEnemy[nCnt]; };				// �G�̎擾
	CPrisoner		*GetPrisoner(int nCnt) { return m_pPrisoner[nCnt]; };		// �ߗ��̎擾
	CObstacle		*GetObstacle(int nCnt) { return m_pObstacle[nCnt]; };		// ��Q���̎擾
	CPlayertank		*GetPlayertank(int nCnt) { return m_pPlayerTank[nCnt]; };	// ��Ԃ̎擾

	void			UpdateDieFlag();										// ���S�t���O�m�F�֐�

private:
	/* �����o�֐� */
	void			ModelLoad(MAP MapNum);									// ���f���̃��[�h
	void			EnemyLoad(MAP MapNum);									// �G�̃��[�h
	void			PrisonerLoad(MAP MapNum);								// �ߗ��̃��[�h
	void			ObstacleLoad(MAP MapNum);								// ��Q���̃��[�h
	void			PlayerTankLoad(MAP MapNum);								// �v���C���[�p�̐�Ԃ̃��[�h
	void			ModelSave(MAP MapNum);									// ���f���̃Z�[�u
	void			EnemySave(MAP MapNum);									// �G�̃Z�[�u
	void			PrisonerSave(MAP MapNum);								// �ߗ��̃Z�[�u
	void			ObstacleSave(MAP MapNum);								// ��Q���̃Z�[�u
	void			PlayerTankSave(MAP MapNum);								// ��Q���̃Z�[�u
	void			AllSaveButton();										// �z�u�������f����S�ăZ�[�u����{�^��
	void			MapModelTab();											// �}�b�v�ɔz�u���郂�f���̃^�u
	void			MapModelSet();											// �}�b�v�ɔz�u���郂�f���̐ݒu
	void			ObstacleSet();											// ��Q���̐ݒu
	void			EnemySet();												// �G�̐ݒu
	void			PlayerTankSet();										// ��Ԃ̐ݒu
	bool			ObstacleComboBox(int &nType);							// ��Q���̃R���{�{�b�N�X
	void			PrisonerSet();											// �ߗ��̐ݒu
	bool			EnemyComboBox(int &nType);								// �G�̃R���{�{�b�N�X
	bool			PrisonerComboBox(int &nType);							// �ߗ��̃R���{�{�b�N�X
	bool			PlayerTankComboBox(int &nType);							// ��Ԃ̃R���{�{�b�N�X

	/* �ÓI�����o�ϐ� */
	static char					*m_MapFileName[MAP_MAX];					// �}�b�v�t�@�C����
	static char					*m_EnemyFileName[MAP_MAX];					// �G�t�@�C����
	static char					*m_PrisonerFileName[MAP_MAX];				// �ߗ��t�@�C����
	static char					*m_ObstacleFileName[MAP_MAX];				// ��Q���t�@�C����
	static char					*m_PlayerTankFileName[MAP_MAX];				// ��ԃt�@�C����
	static MAP					m_MapNum;									// �}�b�v�ԍ�

	/* �����o�ϐ� */
	std::vector<CModel*>		m_pModel;									// �ϒ��z�� �ݒu���郂�f��
	std::vector<CEnemy*>		m_pEnemy;									// �ϒ��z�� �ݒu�����G�l�~�[
	std::vector<CPrisoner*>		m_pPrisoner;								// �ϒ��z�� �ݒu�����ߗ�
	std::vector<CObstacle*>		m_pObstacle;								// �ϒ��z�� �ݒu������Q��
	std::vector<CPlayertank*>	m_pPlayerTank;								// �ϒ��z�� �ݒu�������
	int							m_nOldSelect;								// �O��I�����Ă������m�̔ԍ�
};
#endif