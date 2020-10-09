//------------------------------------------------------------------------------
//
//���f�����Ǘ�  [modelinfo.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MODELINFO_H_
#define _MODELINFO_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
//�O���錾
class CModelInfo
{
public:
	CModelInfo();
	~CModelInfo();

	enum MODEL_TYPE
	{
		MODEL_NONE = -1,

		//�}�b�v�I�u�W�F�N�g 0�ԑ�
		MODEL_MAPOBJECT_WALL,					//�I�u�W�F�N�g�@��
		MODEL_MAPOBJECT_BLOCK,					//�I�u�W�F�N�g�@�u���b�N
		MODEL_MAPOBJECT_SPHERE,					//�I�u�W�F�N�g�@�X�t�B�A
		//�v���C���[�p�[�c 100�ԑ�
		MODEL_PARTS_PLAYER_WAIST = 100,			//�v���C���[�@��
		MODEL_PARTS_PLAYER_BODY,				//�v���C���[�@��
		MODEL_PARTS_PLAYER_HEAD,				//�v���C���[�@��
		MODEL_PARTS_PLAYER_R_SHOULDER,			//�v���C���[�@�E�r
		MODEL_PARTS_PLAYER_R_ARM,				//�v���C���[�@�E�I����
		MODEL_PARTS_PLAYER_R_HAND,				//�v���C���[�@�E��
		MODEL_PARTS_PLAYER_L_SHOULDER,			//�v���C���[�@���r
		MODEL_PARTS_PLAYER_L_ARM,				//�v���C���[�@���I�����
		MODEL_PARTS_PLAYER_L_HAND,				//�v���C���[�@����
		MODEL_PARTS_PLAYER_R_KNEE,				//�v���C���[�@�E��
		MODEL_PARTS_PLAYER_R_LEG,				//�v���C���[�@�E�r
		MODEL_PARTS_PLAYER_R_FOOT,				//�v���C���[�@�E��
		MODEL_PARTS_PLAYER_L_KNEE,				//�v���C���[�@����
		MODEL_PARTS_PLAYER_L_LEG,				//�v���C���[�@���r
		MODEL_PARTS_PLAYER_L_FOOT,				//�v���C���[�@����

		//�G�̃p�[�c 200�ԑ�
		MODEL_PARTS_ENEMY_WAIST = 200,			//�G�@��
		MODEL_PARTS_ENEMY_BODY,					//�G�@��
		MODEL_PARTS_ENEMY_HEAD,					//�G�@��
		MODEL_PARTS_ENEMY_R_SHOULDER,			//�G�@�E�r
		MODEL_PARTS_ENEMY_R_ARM,				//�G�@�E�I�����
		MODEL_PARTS_ENEMY_R_HAND,				//�G�@�E��
		MODEL_PARTS_ENEMY_L_SHOULDER,			//�G�@���r
		MODEL_PARTS_ENEMY_L_ARM,				//�G�@���I�����
		MODEL_PARTS_ENEMY_L_HAND,				//�G�@����
		MODEL_PARTS_ENEMY_R_KNEE,				//�G�@�E��
		MODEL_PARTS_ENEMY_R_LEG,				//�G�@�E�r
		MODEL_PARTS_ENEMY_R_FOOT,				//�G�@�E��
		MODEL_PARTS_ENEMY_L_KNEE,				//�G�@����
		MODEL_PARTS_ENEMY_L_LEG,				//�G�@���r
		MODEL_PARTS_ENEMY_L_FOOT,				//�G�@����

		//���� 900�ԑ�
		MODEL_WEAPONPARTS_LONG_SWORD = 900,		//�����@�v���C���[�p
		MODEL_WEAPONPARTS_SHORT_SWORD,			//������ƒZ�����@�G�p
	};


	typedef struct MODELNAME
	{
		std::string modelname;
		MODEL_TYPE modeltype;
	}MODELNAME;

	static void ModelLoad(HWND hwnd);			//���f������
	static void ModelUnload();					//���f������

	static std::shared_ptr<CModelInfo> GetModelInfo(CModelInfo::MODEL_TYPE modeltype);			//���f�����擾

	//Get�֐�
	std::string GetName() { return m_aName; };				//���f����
	LPD3DXMESH GetMesh() { return m_mesh; };				//���b�V�����
	LPD3DXBUFFER GetMatBuff() { return m_matBuff; };		//���_���
	DWORD GetMatNum() { return m_matNum; };					//�}�e���A����
	MODEL_TYPE GetModelType() { return m_modeltype; };		//���f���^�C�v

private:
	static std::vector<std::shared_ptr<CModelInfo>> m_apModelList;		//���f���ւ̃|�C���^�̃��X�g
	static std::vector<MODELNAME> m_aModelFileNameList;				//���f���̃t�@�C����

	MODEL_TYPE		m_modeltype;		//���f���̎��
	std::string		m_aName;			//���f����
	LPD3DXMESH		m_mesh;				//���b�V��
	LPD3DXBUFFER	m_matBuff;			//���_���
	DWORD			m_matNum;			//�}�e���A����

};

#endif


