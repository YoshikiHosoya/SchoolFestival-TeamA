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
#include "WeakEnemy.h"
#include "obstacle.h"
#include "prisoner.h"

// =====================================================================================================================================================================
// �O���錾
// =====================================================================================================================================================================
class CModel;
class CEnemy;
class CPrisoner;
class CObstacle;
class CPlayertank;
class CModelSet;
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

	// �}�b�v�̎��
	enum MAP
	{
		MAP_TUTORIAL,		// �`���[�g���A��
		MAP_1_1,			// 1_1
		MAP_1_2,			// 1_2
		MAP_1_3,			// 1_3
		MAP_1_BOSS,			// 1_BOSS
		MAP_2_1,			// 2_1
		MAP_2_2,			// 2_2
		MAP_2_3,			// 2_3
		MAP_2_BOSS,			// 2_BOSS
		MAP_MAX
	};

	// �z�u���郂�f���̎��
	enum ARRANGEMENT_MODEL
	{
		ARRANGEMENT_MODEL_MAP,					// �}�b�v
		ARRANGEMENT_MODEL_MAP_NOCOLLISION,		// �}�b�v
		ARRANGEMENT_MODEL_ENEMY,				// �G
		ARRANGEMENT_MODEL_PRISONER,				// �ߗ�
		ARRANGEMENT_MODEL_OBSTACLE,				// ��Q��
		ARRANGEMENT_MODEL_TANK,					// ���
		ARRANGEMENT_MODEL_BOSS,					// �{�X
		ARRANGEMENT_MODEL_BOSS_ONE,				// �{�X1
		ARRANGEMENT_MODEL_MAX
	};

	// �E�F�[�u�̎��
	enum WAVE
	{
		WAVE_1_1_1,									// �E�F�[�u1_1_1
		WAVE_1_1_2,									// �E�F�[�u1_1_2
		WAVE_1_2_1,									// �E�F�[�u1_2_1
		WAVE_1_2_2,									// �E�F�[�u1_2_2
		WAVE_1_3_1,									// �E�F�[�u1_3_1
		WAVE_1_3_2,									// �E�F�[�u1_3_2
		WAVE_1_BOSS,								// �E�F�[�u1_BOSS
		WAVE_2_1_1,									// �E�F�[�u2_1_1
		WAVE_2_1_2,									// �E�F�[�u2_1_2
		WAVE_2_2_1,									// �E�F�[�u2_2_1
		WAVE_2_2_2,									// �E�F�[�u2_2_1
		WAVE_2_3_1,									// �E�F�[�u2_3_1
		WAVE_2_3_2,									// �E�F�[�u2_3_1
		WAVE_2_BOSS,								// �E�F�[�u2_BOSS
		WAVE_MAX
	};

	// �E�F�[�u�̏��
	typedef struct
	{
		std::vector<WAVE_PARAM*> EnemyWaveInfo;			// �G�̃E�F�[�u�̃p�����[�^�[
		std::vector<WAVE_PARAM*> PrisonerWaveInfo;		// �ߗ��̃E�F�[�u�p�����[�^�[
		D3DXVECTOR3 EventPos;							// �C�x���g���N����ʒu
		MAP EventBeginMapNum;							// �C�x���g���N����}�b�v�ԍ�
 	} WAVE_INFO;

	CMap();																			// �R���X�g���N�^
	~CMap();																		// �f�X�g���N�^

	/* �ÓI�����o�֐� */
	static	CMap	*MapCreate();													// �}�b�v�̐���
	static void		WaveLoad();														// �E�F�[�u�̃��[�h
	static void		WaveUnLoad();													// �E�F�[�u�̃��[�h

	/* �����o�֐� */
	void			MapUpdate();													// �}�b�v�̍X�V
	void			MapLoad(MAP MapNum);											// �}�b�v�̃��[�h
	void			UpdateDieFlag();												// ���S�t���O�m�F�֐�
	void			AllDelete();													// �z�u���Ă��郂�f����S�Ĕj��
	void			WaveCreate(int nModelType, D3DXVECTOR3 eventpos, WAVE_PARAM *pWaveParam, CWeakEnemy::ENEMY_TYPE EnemyType);	// Wave�̐���
	CObstacle		*PresentCreate(D3DXVECTOR3 pos, CObstacle::OBSTACLE_TYPE Type);	// �v���[���g�{�b�N�X�̐���
	void			BossWaveCreate(int nModelType, D3DXVECTOR3 eventpos,
		CWeakEnemy::ENEMY_TYPE EnemyType,CPrisoner::PRISONER_TYPE type);			// �{�X�̃}�b�v�p�ŏo���G��ߗ��p

	void			ShowDebugInfo();												// �f�o�b�O���\�L

	int				GetMaxModel();													// ���f���̍ő吔�擾
	int				GetMaxEnemy();													// �G�̍ő吔�擾
	int				GetMaxPrisoner();												// �ߗ��̍ő吔�擾
	int				GetMaxObstacle();												// ��Q���̍ő吔�擾
	int				GetMaxPlayerTank();												// ��Ԃ̍ő吔�擾

	LPD3DXMESH		GetMesh(int nCnt);												// ���b�V���̎擾
	MAP				GetMapNum() { return m_MapNum; };								// �}�b�v�ԍ��擾
	CModel			*GetModel(int nCnt) { return m_pMapModel[nCnt]; };				// ���f���̎擾
	CEnemy			*GetEnemy(int nCnt) { return m_pEnemy[nCnt]; };					// �G�̎擾
	CPrisoner		*GetPrisoner(int nCnt) { return m_pPrisoner[nCnt]; };			// �ߗ��̎擾
	CObstacle		*GetObstacle(int nCnt) { return m_pObstacle[nCnt]; };			// ��Q���̎擾
	CPlayertank		*GetPlayertank(int nCnt) { return m_pPlayerTank[nCnt]; };		// ��Ԃ̎擾
	WAVE_INFO		*GetWaveInfo(int nWaveNum) { return &m_aWaveInfo[nWaveNum]; };	// �E�F�[�u���̎擾
	D3DXVECTOR3		GetTransitionPos() { return m_TransitionPos; };					// �J�ڂ��邽�߂̈ʒu�̎擾
	int				GetTransitionMapID() { return m_TransitionMapID; }				// ���ɑJ�ڂ��邽�߂̃}�b�v�ԍ��̎擾

private:
	/* �����o�֐� */
	void			MapModelLoad();																// �z�u���郂�f���̃��[�h
	void			MapModelSave();																// �z�u���郂�f���̃Z�[�u
	void			MapModelCreate(int ModelType, int nType, D3DXVECTOR3 pos, int nItemType);	// �z�u���郂�f���̐���
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
	static ARRANGEMENT_MODEL	m_ArrangmentModel;							// �z�u���郂�f���̎��
	static WAVE_INFO			m_aWaveInfo[WAVE_MAX];						// �E�F�[�u�̏��

	/* �����o�ϐ� */
	std::vector<CModel*>		m_pMapModel;								// �ϒ��z�� �ݒu����}�b�v���f��
	std::vector<CEnemy*>		m_pEnemy;									// �ϒ��z�� �ݒu�����G�l�~�[
	std::vector<CPrisoner*>		m_pPrisoner;								// �ϒ��z�� �ݒu�����ߗ�
	std::vector<CObstacle*>		m_pObstacle;								// �ϒ��z�� �ݒu������Q��
	std::vector<CPlayertank*>	m_pPlayerTank;								// �ϒ��z�� �ݒu�������

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