//------------------------------------------------------------------------------
//
//�V�[������  [scene.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _SCENE_H_
#define _SCENE_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include <vector>
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CScene2D;

class CScene
{
public:

	enum OBJTYPE
	{
		OBJTYPE_NONE = 0,					//���ݒ�
		OBJTYPE_BACK,						//���
		OBJTYPE_MESHFIELD,					//���b�V��
		OBJTYPE_MESHWALL,					//���b�V��
		OBJTYPE_MESHSPHERE,					//���b�V��
		OBJTYPE_EFFECT_CIRCLE,				//�~�G�t�F�N�g
		OBJTYPE_TRACES,						//����
		OBJTYPE_MAPOBJECT,					//�}�b�v�ɔz�u�����I�u�W�F�N�g
		OBJTYPE_PLAYER,						//�v���C���[
		OBJTYPE_ENEMY,						//�G
		OBJTYPE_BULLET,						//�e
		OBJTYPE_OBJ,						//�I�u�W�F�N�g
		OBJTYPE_ORBIT,						//�O��
		OBJTYPE_2DGAUGE,					//2D�Q�[�W
		OBJTYPE_3DGAUGE,					//3D�Q�[�W
		OBJTYPE_EFFECT,						//�G�t�F�N�g
		OBJTYPE_EFFECT_PARTICLE,			//�G�t�F�N�g
		OBJTYPE_EFFECT_SPHERE,				//�X�t�B�A�G�t�F�N�g
		OBJTYPE_UI_BG,						//UI
		OBJTYPE_UI,							//UI
		OBJTYPE_2DUI,						//2D��UI
		OBJTYPE_DEBUG_CYLINDER,				//debug
		OBJTYPE_NUMBER,						//����
		OBJTYPE_2DEFFECT,					//�G�t�F�N�g
		OBJTYPE_MINIMAP,					//�~�j�}�b�v
		OBJTYPE_FRONTUI,					//�o�b�NUI
		OBJTYPE_PAUSE,						//�|�[�Y
		OBJTYPE_OPTION,						//�I�v�V����

		OBJTYPE_FRONT,						//�O��
		OBJTYPE_DEBUG,						//�f�o�b�O�n
		OBJTYPE_MAX							//�ő�l
	};

	CScene();

	//�������z�֐��@�I�[�o�[���C�h�p
	virtual ~CScene();
	virtual HRESULT Init() = 0;														//������
	virtual void Uninit() = 0;														//�I��
	virtual void Update() = 0;														//�X�V
	virtual void Draw() = 0;														//�`��
	virtual void ShowDebugInfo() = 0;												//�f�o�b�O���\�L

	static void ShowNumAll();

	static void ReleaseAll();														//�������J��
	static void UpdateAll();														//�X�V����
	static void DrawAll();															//�`�揈��
	static void ShowDebugInfoAll();													//�S�Ẵf�o�b�O���\�L����

	static void ReleaseSpecificObject(OBJTYPE objtype);								//�I�������I�u�W�F�N�g�^�C�v��S�ă����[�X

	CScene::OBJTYPE GetObjType()				{ return m_objtype; };				//�I�u�W�F�N�g�̎�ގ擾
	static int GetNumAll()						{ return m_nNumAll; };				//�����擾

	void Release()								{ m_bDeadFlag = true; };			//�������J��
	void SetObjType(OBJTYPE objtype)			{ m_objtype = objtype; };			//�I�u�W�F�N�g�^�C�v�ݒ�֐�

	static bool CheckStop()						{ return m_bStop; };				//�X�g�b�v���Ă邩�`�F�b�N
	static void Set1FAction();														//�PF�����i�߂鏈��
	static void SetStop(bool bStop)				{m_bStop = bStop;};					//�X�g�b�v����

	static void GetSceneList(OBJTYPE objtype, std::vector<std::shared_ptr<CScene>> &SceneList);			//�V�[�����擾�i�z�񂲂Ɓj

	template <class T> void AddUniqueList(T ptr)		 //���X�g�ɒǉ�
	{
		//���j�[�N�|�C���^�̃��X�g�Ɏ�����ǉ�
		m_UniqueSceneList[ptr->m_objtype].emplace_back(std::move(ptr));
	};

	template <class T> void AddSharedList(T ptr) 		//���X�g�ɒǉ�
	{
		//���L�|�C���^�̃��X�g�Ɏ�����ǉ�
		m_SharedSceneList[m_objtype].emplace_back(ptr);
	};

protected:

private:
	static int m_nNumAll;					//�I�u�W�F�N�g����
	static int m_nCntStop;					//�X�g�b�v�̃J�E���g
	static std::vector<std::unique_ptr<CScene>> m_UniqueSceneList[OBJTYPE_MAX];		//���j�[�N�|�C���^�@�Ɛ肷�ׂ��|�C���^
	static std::vector<std::shared_ptr<CScene>> m_SharedSceneList[OBJTYPE_MAX];		//�V�F�A�|�C���^	���L����鎖������Ǝv����|�C���^
	static bool m_bStop;					//��ʃX�g�b�v���邩�ǂ���
	static bool m_b1FAction;				//1F�����A�N�V�������邩

	bool m_bNonStop;						//�X�g�b�v���Ȃ�
	bool m_bDeadFlag;						//���S�t���O
	OBJTYPE	m_objtype;						//�^�C�v
};

#endif

