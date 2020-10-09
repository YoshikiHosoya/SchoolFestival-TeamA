//-----------------------------------------------------------------------------
//
//���f�����Ǘ�  [modelinfo.cpp]
// Author : Yoshiki Hosoya
//
//-----------------------------------------------------------------------------
#include "modelinfo.h"
#include "manager.h"
#include "renderer.h"
//-----------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//-----------------------------------------------------------------------------
std::vector<std::shared_ptr<CModelInfo>> CModelInfo::m_apModelList = {};

//�e�N�X�`�����̐ݒ�
std::vector<CModelInfo::MODELNAME> CModelInfo::m_aModelFileNameList =
{
	{ "data/MODEL/Map/Wall.x" ,				MODEL_MAPOBJECT_WALL },					//��
	{ "data/MODEL/Map/Block.x" ,			MODEL_MAPOBJECT_BLOCK },				//��
	{ "data/MODEL/Map/Sphere.x" ,			MODEL_MAPOBJECT_SPHERE },				//��

	{ "data/MODEL/Woman/00_waist.x" ,		MODEL_PARTS_PLAYER_WAIST },				//�v���C���[�@��
	{ "data/MODEL/Woman/01_body.x" ,		MODEL_PARTS_PLAYER_BODY },				//�v���C���[�@��
	{ "data/MODEL/Woman/02_head.x" ,		MODEL_PARTS_PLAYER_HEAD },				//�v���C���[�@��
	{ "data/MODEL/Woman/03_R_Shoulder.x" ,	MODEL_PARTS_PLAYER_R_SHOULDER },		//�v���C���[�@�E�r
	{ "data/MODEL/Woman/04_R_Arm.x" ,		MODEL_PARTS_PLAYER_R_ARM },				//�v���C���[�@�E�I�����
	{ "data/MODEL/Woman/05_R_Hand.x" ,		MODEL_PARTS_PLAYER_R_HAND },			//�v���C���[�@�E��
	{ "data/MODEL/Woman/06_L_Shoulder.x" ,	MODEL_PARTS_PLAYER_L_SHOULDER },		//�v���C���[�@���r
	{ "data/MODEL/Woman/07_L_Arm.x" ,		MODEL_PARTS_PLAYER_L_ARM },				//�v���C���[�@���I�����
	{ "data/MODEL/Woman/08_L_Hand.x" ,		MODEL_PARTS_PLAYER_L_HAND },			//�v���C���[�@����
	{ "data/MODEL/Woman/09_R_Knee.x",		MODEL_PARTS_PLAYER_R_KNEE },			//�v���C���[�@�E��
	{ "data/MODEL/Woman/10_R_Leg.x" ,		MODEL_PARTS_PLAYER_R_LEG },				//�v���C���[�@�E�r
	{ "data/MODEL/Woman/11_R_Foot.x" ,		MODEL_PARTS_PLAYER_R_FOOT },			//�v���C���[�@�E��
	{ "data/MODEL/Woman/12_L_Knee.x" ,		MODEL_PARTS_PLAYER_L_KNEE },			//�v���C���[�@����
	{ "data/MODEL/Woman/13_L_Leg.x" ,		MODEL_PARTS_PLAYER_L_LEG },				//�v���C���[�@���r
	{ "data/MODEL/Woman/14_L_Foot.x" ,		MODEL_PARTS_PLAYER_L_FOOT },			//�v���C���[�@����

	{ "data/MODEL/Armor/00_waist.x" ,		MODEL_PARTS_ENEMY_WAIST },				//�G�@��
	{ "data/MODEL/Armor/01_body.x" ,		MODEL_PARTS_ENEMY_BODY },				//�G�@��
	{ "data/MODEL/Armor/02_head.x" ,		MODEL_PARTS_ENEMY_HEAD },				//�G�@��
	{ "data/MODEL/Armor/03_R_Shoulder.x" ,	MODEL_PARTS_ENEMY_R_SHOULDER },			//�G�@�E�r
	{ "data/MODEL/Armor/04_R_Arm.x" ,		MODEL_PARTS_ENEMY_R_ARM },				//�G�@�E�I�����
	{ "data/MODEL/Armor/05_R_Hand.x" ,		MODEL_PARTS_ENEMY_R_HAND },				//�G�@�E��
	{ "data/MODEL/Armor/06_L_Shoulder.x" ,	MODEL_PARTS_ENEMY_L_SHOULDER },			//�G�@���r
	{ "data/MODEL/Armor/07_L_Arm.x" ,		MODEL_PARTS_ENEMY_L_ARM },				//�G�@���I�����
	{ "data/MODEL/Armor/08_L_Hand.x" ,		MODEL_PARTS_ENEMY_L_HAND },				//�G�@����
	{ "data/MODEL/Armor/09_R_Knee.x",		MODEL_PARTS_ENEMY_R_KNEE },				//�G�@�E��
	{ "data/MODEL/Armor/10_R_Leg.x" ,		MODEL_PARTS_ENEMY_R_LEG },				//�G�@�E�r
	{ "data/MODEL/Armor/11_R_Foot.x" ,		MODEL_PARTS_ENEMY_R_FOOT },				//�G�@�E��
	{ "data/MODEL/Armor/12_L_Knee.x" ,		MODEL_PARTS_ENEMY_L_KNEE },				//�G�@����
	{ "data/MODEL/Armor/13_L_Leg.x" ,		MODEL_PARTS_ENEMY_L_LEG },				//�G�@���r
	{ "data/MODEL/Armor/14_L_Foot.x" ,		MODEL_PARTS_ENEMY_L_FOOT },				//�G�@����

	{ "data/MODEL/Woman/15_weapon.x" ,	MODEL_WEAPONPARTS_LONG_SWORD },				//����
	{ "data/MODEL/Armor/15_weapon.x" ,	MODEL_WEAPONPARTS_SHORT_SWORD },			//����
};

//-----------------------------------------------------------------------------
//�R���X�g���N�^
//-----------------------------------------------------------------------------
CModelInfo::CModelInfo()
{
	//������
	m_aName = {};
	m_matBuff = nullptr;
	m_mesh = nullptr;
	m_matNum = 0;
};

//-----------------------------------------------------------------------------
//�f�X�g���N�^
//-----------------------------------------------------------------------------
CModelInfo::~CModelInfo()
{
	//�o�b�t�@�J��
	if (m_matBuff)
	{
		m_matBuff->Release();
		m_matBuff = nullptr;
	}
	//���b�V���J��
	if (m_mesh)
	{
		m_mesh->Release();
		m_mesh = nullptr;
	}
}

//-----------------------------------------------------------------------------
//���f���ǂݍ���
//----------------------------------------------------------------------------
void CModelInfo::ModelLoad(HWND hwnd)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (size_t nCnt = 0; nCnt < m_aModelFileNameList.size(); nCnt++)
	{
		//debug
		std::cout << "Model Load - " << nCnt << m_aModelFileNameList[nCnt].modelname.data() << NEWLINE;

		m_apModelList.emplace_back(std::make_shared<CModelInfo>());
		m_apModelList[nCnt]->m_modeltype = m_aModelFileNameList[nCnt].modeltype;

		// X�t�@�C���̓ǂݍ���
		if (FAILED(D3DXLoadMeshFromX(m_aModelFileNameList[nCnt].modelname.data(),
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_apModelList[nCnt]->m_matBuff,
			NULL,
			&m_apModelList[nCnt]->m_matNum,
			&m_apModelList[nCnt]->m_mesh)))
		{
			//���s�����Ƃ�
			std::cout << "���s���S" << NEWLINE;
		}
	}
}

//-----------------------------------------------------------------------------
//���f���j��
//----------------------------------------------------------------------------
void CModelInfo::ModelUnload()
{

}

//-----------------------------------------------------------------------------
//���f���擾
//----------------------------------------------------------------------------
std::shared_ptr<CModelInfo> CModelInfo::GetModelInfo(CModelInfo::MODEL_TYPE modeltype)
{
	//�T�C�Y���J��Ԃ�
	for (size_t nCnt = 0; nCnt < m_apModelList.size(); nCnt++)
	{
		//nullcheck
		if (m_apModelList[nCnt])
		{
			//���f���^�C�v����v���Ă��邩�ǂ���
			if (m_apModelList[nCnt]->GetModelType() == modeltype)
			{
				return m_apModelList[nCnt];
			}
		}
	}
	return nullptr;
}
