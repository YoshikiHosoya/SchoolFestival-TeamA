//=============================================================================
// ���f������ [Model.cpp]
//=============================================================================
#include "model.h"
#include "inputKeyboard.h"
#include "Player.h"
#include "scene.h"
#include "debugproc.h"
#include "collision.h"
#include "ModelSet.h"
std::vector<CModel::MODEL*> CModel::m_vModel = {};

std::vector<CModel::MODEL_FILE_NAME> CModel::m_vModelFileName =
{
	//�v���C���[
	{ "data/MODEL/character/Player/Waist.x",				MODEL_PLAYER_WAIST				},		// �v���C���[�̍�
	{ "data/MODEL/character/Player/Body.x" ,				MODEL_PLAYER_BODY				},		// �v���C���[�̑�
	{ "data/MODEL/character/Player/Head.x" ,				MODEL_PLAYER_HEAD				},		// �v���C���[�̓�
	{ "data/MODEL/character/Player/L_Sholder.x",			MODEL_PLAYER_L_SHOLDER			},		// �v���C���[�̍���
	{ "data/MODEL/character/Player/R_Sholder.x",			MODEL_PLAYER_R_SHOLDER			},		// �v���C���[�̉E��
	{ "data/MODEL/character/Player/L_Arm.x" ,				MODEL_PLAYER_LARM				},		// �v���C���[�̍��r
	{ "data/MODEL/character/Player/R_Arm.x" ,				MODEL_PLAYER_RARM				},		// �v���C���[�̉E�r
	{ "data/MODEL/character/Player/L_Hand.x",				MODEL_PLAYER_LHAND				},		// �v���C���[�̍���
	{ "data/MODEL/character/Player/R_Hand.x",				MODEL_PLAYER_RHAND				},		// �v���C���[�̉E��
	{ "data/MODEL/character/Player/L_Knee.x",				MODEL_PLAYER_LKNEE				},		// �v���C���[�̍��G
	{ "data/MODEL/character/Player/R_Knee.x",				MODEL_PLAYER_RKNEE				},		// �v���C���[�̉E�G
	{ "data/MODEL/character/Player/L_Foot.x",				MODEL_PLAYER_LLEG				},		// �v���C���[�̍��r
	{ "data/MODEL/character/Player/R_Foot.x",				MODEL_PLAYER_RLEG				},		// �v���C���[�̉E�r
	{ "data/MODEL/character/Player/L_Leg.x",				MODEL_PLAYER_LFOOT				},		// �v���C���[�̍���
	{ "data/MODEL/character/Player/R_Leg.x",				MODEL_PLAYER_RFOOT				},		// �v���C���[�̉E��

	{ "data/MODEL/character/Player/2pModel/Waist.x",		MODEL_PLAYER_2P_WAIST			 },		// 2P�v���C���[�̍�
	{ "data/MODEL/character/Player/2pModel/Body.x",			MODEL_PLAYER_2P_BODY			 },		// 2P�v���C���[�̑�
	{ "data/MODEL/character/Player/2pModel/L_Knee.x",		MODEL_PLAYER_2P_LKNEE			 },		// 2P�v���C���[�̍��G
	{ "data/MODEL/character/Player/2pModel/R_Knee.x",		MODEL_PLAYER_2P_RKNEE			 },		// 2P�v���C���[�̉E�G
	{ "data/MODEL/character/Player/2pModel/L_Foot.x",		MODEL_PLAYER_2P_LFOOT			 },		// 2P�v���C���[�̍��r
	{ "data/MODEL/character/Player/2pModel/R_Foot.x",		MODEL_PLAYER_2P_RFOOT			 },		// 2P�v���C���[�̉E�r


	//�G
	{ "data/MODEL/Enemy/EnemyHuman/Waist.x",				MODEL_ENEMY_HUMAN_WAIST },				// ��
	{ "data/MODEL/Enemy/EnemyHuman/Body.x" ,				MODEL_ENEMY_HUMAN_HEAD },				// ��
	{ "data/MODEL/Enemy/EnemyHuman/Head.x" ,				MODEL_ENEMY_HUMAN_BODY },				// ��
	{ "data/MODEL/Enemy/EnemyHuman/L_Sholder.x" ,			MODEL_ENEMY_HUMAN_L_SHOLDER },			// ����
	{ "data/MODEL/Enemy/EnemyHuman/R_Sholder.x" ,			MODEL_ENEMY_HUMAN_R_SHOLDER },			// �E��
	{ "data/MODEL/Enemy/EnemyHuman/L_Arm.x" ,				MODEL_ENEMY_HUMAN_LARM },				// ���r
	{ "data/MODEL/Enemy/EnemyHuman/R_Arm.x" ,				MODEL_ENEMY_HUMAN_RARM },				// �E�r
	{ "data/MODEL/Enemy/EnemyHuman/L_Hand.x" ,				MODEL_ENEMY_HUMAN_LHAND },				// ����
	{ "data/MODEL/Enemy/EnemyHuman/R_Hand.x" ,				MODEL_ENEMY_HUMAN_RHAND },				// �E��
	{ "data/MODEL/Enemy/EnemyHuman/L_Knee.x" ,				MODEL_ENEMY_HUMAN_LKNEE },				// ���G
	{ "data/MODEL/Enemy/EnemyHuman/R_Knee.x" ,				MODEL_ENEMY_HUMAN_RKNEE },				// �E�G
	{ "data/MODEL/Enemy/EnemyHuman/L_Foot.x" ,				MODEL_ENEMY_HUMAN_LLEG },				// ���r
	{ "data/MODEL/Enemy/EnemyHuman/R_Foot.x" ,				MODEL_ENEMY_HUMAN_RLEG },				// �E�r
	{ "data/MODEL/Enemy/EnemyHuman/L_Leg.x" ,				MODEL_ENEMY_HUMAN_LFOOT },				// ����
	{ "data/MODEL/Enemy/EnemyHuman/R_Leg.x" ,				MODEL_ENEMY_HUMAN_RFOOT },				// �E��
	//
	{ "data/MODEL/Enemy/EnemyHelicopter/Body.x" ,			MODEL_ENEMY_HELICOPTER_BODY },			// �E��
	{ "data/MODEL/Enemy/EnemyHelicopter/Propeller.x" ,		MODEL_ENEMY_HELICOPTER_PROPELLER },		// �E��
	//
	{ "data/MODEL/Enemy/MeltyHoney/Body.x" ,				MODEL_ENEMY_MELTYHONEY_BODY },			// �E��
	{ "data/MODEL/Enemy/MeltyHoney/wheel.x" ,				MODEL_ENEMY_MELTYHONEY_WHEEL },			// �E��
	//
	{ "data/MODEL/Enemy/Zycocca/Body.x" ,					MODEL_ENEMY_ZYCOCCA_BODY },				// �E��
	{ "data/MODEL/Enemy/Zycocca/wheel.x" ,					MODEL_ENEMY_ZYCOCCA_WHEEL },			// �E��

	// �h���[�� sky
	{ "data/MODEL/Enemy/Drone/SkyDrone_x/Drone_Body.x" ,	MODEL_DRONE_BODY },						// ��
	{ "data/MODEL/Enemy/Drone/SkyDrone_x/Drone_Hand_L.x" ,	MODEL_DRONE_HAND_L },					// ����
	{ "data/MODEL/Enemy/Drone/SkyDrone_x/Drone_Hand_R.x" ,	MODEL_DRONE_HAND_R },					// �E��
	{ "data/MODEL/Enemy/Drone/SkyDrone_x/Drone_Eye.x" ,		MODEL_DRONE_EYE },						// ��

	// �h���[�� wall
	{ "data/MODEL/Enemy/Drone/WallDrone_x/WallDrone_Head.x" ,		MODEL_DRONE_HEAD },				// 0�h���[���̓�-1
	{ "data/MODEL/Enemy/Drone/WallDrone_x/WallDrone_Joint.x" ,		MODEL_DRONE_JOINT_F_R },		// 1�E�O���֐�0
	{ "data/MODEL/Enemy/Drone/WallDrone_x/WallDrone_Thigh_F_R.x" ,	MODEL_DRONE_THIGH_F_R },		// 2�E�O���1
	{ "data/MODEL/Enemy/Drone/WallDrone_x/WallDrone_Leg_F_R.x" ,	MODEL_DRONE_LEG_F_R },			// 3�E�O��2
	{ "data/MODEL/Enemy/Drone/WallDrone_x/WallDrone_Joint.x" ,		MODEL_DRONE_JOINT_B_R },		// 4�E�㑫�֐�0
	{ "data/MODEL/Enemy/Drone/WallDrone_x/WallDrone_Thigh_B_R.x" ,	MODEL_DRONE_THIGH_B_R },		// 5�E����4
	{ "data/MODEL/Enemy/Drone/WallDrone_x/WallDrone_Leg_B_R.x" ,	MODEL_DRONE_LEG_B_R },			// 6�E�㑫5
	{ "data/MODEL/Enemy/Drone/WallDrone_x/WallDrone_Joint.x" ,		MODEL_DRONE_JOINT_F_L },		// 7���O���֐�0
	{ "data/MODEL/Enemy/Drone/WallDrone_x/WallDrone_Thigh_F_L.x" ,	MODEL_DRONE_THIGH_F_L },		// 8���O���7
	{ "data/MODEL/Enemy/Drone/WallDrone_x/WallDrone_Leg_F_L.x" ,	MODEL_DRONE_LEG_F_L },			// 9���O��8
	{ "data/MODEL/Enemy/Drone/WallDrone_x/WallDrone_Joint.x" ,		MODEL_DRONE_JOINT_B_L },		// 10���㑫�֐�0
	{ "data/MODEL/Enemy/Drone/WallDrone_x/WallDrone_Thigh_B_L.x" ,	MODEL_DRONE_THIGH_B_L },		// 11������10
	{ "data/MODEL/Enemy/Drone/WallDrone_x/WallDrone_Leg_B_L.x" ,	MODEL_DRONE_LEG_B_L },			// 12���㑫11

	//�}�b�v
	{ "data/MODEL/map/Map1_Boss stage.x" ,					MODEL_MAP_TUTORIAL },					// �`���[�g���A���}�b�v
	{ "data/MODEL/map/Stage1-1.x" ,							MODEL_MAP_STAGE1_1 },					// �X�e�[�W1-1
	{ "data/MODEL/map/Stage1-2.x" ,							MODEL_MAP_STAGE1_2 },					// �X�e�[�W1-2
	{ "data/MODEL/map/Stage1-3.x" ,							MODEL_MAP_STAGE1_3 },					// �X�e�[�W1-3
	{ "data/MODEL/map/Map1_Boss stage.x" ,					MODEL_MAP_STAGE1_BOSS },				// �{�X�X�e�[�W1
	{ "data/MODEL/map/Stage2-1.x" ,							MODEL_MAP_STAGE2_1 },					// �X�e�[�W2-1
	{ "data/MODEL/map/Stage2-2.x" ,							MODEL_MAP_STAGE2_2 },					// �X�e�[�W2-2
	{ "data/MODEL/map/Stage2-3.x" ,							MODEL_MAP_STAGE2_3 },					// �X�e�[�W2-3
	{ "data/MODEL/map/Map1_Boss stage.x" ,					MODEL_MAP_STAGE2_BOSS },				// �{�X�X�e�[�W2
	{ "data/MODEL/map/Stage2-1_Nocollision.x" ,				MODEL_MAP_NO_COLLISION_STAGE2_1 },					// �X�e�[�W2-1 �����蔻�薳��
	{ "data/MODEL/map/Stage2-2_Nocollision.x" ,				MODEL_MAP_NO_COLLISION_STAGE2_2 },					// �X�e�[�W2-2 �����蔻�薳��
	{ "data/MODEL/map/Stage2-3_Nocollision.x" ,				MODEL_MAP_NO_COLLISION_STAGE2_3 },					// �X�e�[�W2-3 �����蔻�薳��


	//����
	{ "data/MODEL/Gun/Gun.x" ,								MODEL_GUN_HANDGUN },					// �n���h�K��
	{ "data/MODEL/Gun/Assaultrifle.x" ,						MODEL_GUN_HEAVYMACHINEGUN },			// �w�r�[�}�V���K��
	{ "data/MODEL/Gun/Shootgun.x" ,							MODEL_GUN_SHOTGUN },					// �V���b�g�K��
	{ "data/MODEL/Gun/Chargerifle.x" ,						MODEL_GUN_LASERGUN },					// ���[�U�[�K��
	{ "data/MODEL/Gun/Rocketlauncher.x" ,					MODEL_GUN_ROCKETLAUNCHER },				// ���P�b�g�����`���[
	{ "data/MODEL/Gun/Flameshoot.x" ,						MODEL_GUN_FLAMESHOT },					// �t���C���V���b�g
	{ "data/MODEL/Gun/TankGun.x" ,							MODEL_GUN_TANKGUN },					// ��Ԃ̏e
	{ "data/MODEL/Gun/PlaneGun.x" ,							MODEL_GUN_PLANEGUN },					// �퓬�@�̏e
	{ "data/MODEL/Gun/HeliGun.x" ,							MODEL_GUN_HELIGUN },					// �w���̏e
	{ "data/MODEL/Gun/Balkan.x" ,							MODEL_GUN_BALKAN },						// �o���J��
	{ "data/MODEL/Gun/Flamethrower.x" ,						MODEL_GUN_FLAMETHROWER },				// �Ή����ˊ�
	{ "data/MODEL/Gun/Incendiary.x" ,						MODEL_GUN_INCENDIARY },					// �ĈΒe
	{ "data/MODEL/Gun/Knife.x" ,							MODEL_KNIFE },							// �i�C�t

	//�e
	{ "data/MODEL/Bullet/Sphere.x" ,						MODEL_BULLET_SPHERE, },					// ��
	{ "data/MODEL/Bullet/Rockets.x" ,						MODEL_BULLET_ROCKETLAUNCHER, },			// ���P�b�g�����`���[
	{ "data/MODEL/Bullet/Grenade.x" ,						MODEL_BULLET_GRENADE, },				// �O���l�[�h
	{ "data/MODEL/Bullet/Tankmissile.x" ,					MODEL_BULLET_TANKGRENADE, },			// ��Ԃ̃O���l�[�h
	{ "data/MODEL/Bullet/Missile.x" ,						MODEL_BULLET_MISSILE, },				// �~�T�C��

	//�I�u�W�F�N�g
	{ "data/MODEL/Object/Obstacle_Box.x" ,					OBSTACLE_TYPE_BOX },					// ��
	{ "data/MODEL/Object/Obstacle_Barrel.x" ,				OBSTACLE_TYPE_BARREL },					// �M
	{ "data/MODEL/Object/Obstacle_BarrelBomb.x" ,			OBSTACLE_TYPE_BARRELBOMB },				// �M���e
	{ "data/MODEL/Object/Obstacle_Tree.x" ,					OBSTACLE_TYPE_TREE },					// ��
	{ "data/MODEL/Object/Obstacle_Chest.x" ,				OBSTACLE_TYPE_CHEST },					// ����
	{ "data/MODEL/Object/Obstacle_Sandbags.x" ,				OBSTACLE_TYPE_SANDBAGS },				// �y�X
	{ "data/MODEL/Object/Obstacle_Car.x" ,					OBSTACLE_TYPE_CAR },					// ��
	{ "data/MODEL/Object/Obstacle_Balloon.x" ,				OBSTACLE_TYPE_BALLOON },				// ���D
	{ "data/MODEL/Object/Obstacle_PresentBox01.x" ,			OBSTACLE_TYPE_PRESENTBOX },				// �v���[���g
	{ "data/MODEL/Object/Obstacle_PresentBox00.x" ,			OBSTACLE_TYPE_PRESENTBOX_RARE },		// �v���[���g ���A

	//�ߗ�
	{ "data/MODEL/Prisoner/Waist.x",						MODEL_PRISONER_WAIST			},		// �ߗ��̍�
	{ "data/MODEL/Prisoner/Body.x" ,						MODEL_PRISONER_BODY				},		// �ߗ��̑�
	{ "data/MODEL/Prisoner/Head.x" ,						MODEL_PRISONER_HEAD				},		// �ߗ��̓�
	{ "data/MODEL/Prisoner/L_Sholder.x" ,					MODEL_PRISONER_L_SHOLDER		},		// �ߗ��̍���
	{ "data/MODEL/Prisoner/R_Sholder.x" ,					MODEL_PRISONER_R_SHOLDER		},		// �ߗ��̉E��
	{ "data/MODEL/Prisoner/L_Arm.x" ,						MODEL_PRISONER_LARM				},		// �ߗ��̍��r
	{ "data/MODEL/Prisoner/R_Arm.x" ,						MODEL_PRISONER_RARM				},		// �ߗ��̉E�r
	{ "data/MODEL/Prisoner/L_Hand.x" ,						MODEL_PRISONER_LHAND			},		// �ߗ��̍���
	{ "data/MODEL/Prisoner/R_Hand.x" ,						MODEL_PRISONER_RHAND			},		// �ߗ��̉E��
	{ "data/MODEL/Prisoner/L_Knee.x" ,						MODEL_PRISONER_LKNEE			},		// �ߗ��̍��G
	{ "data/MODEL/Prisoner/R_Knee.x" ,						MODEL_PRISONER_RKNEE			},		// �ߗ��̉E�G
	{ "data/MODEL/Prisoner/L_Foot.x" ,						MODEL_PRISONER_LLEG				},		// �ߗ��̍��r
	{ "data/MODEL/Prisoner/R_Foot.x" ,						MODEL_PRISONER_RLEG				},		// �ߗ��̉E�r
	{ "data/MODEL/Prisoner/L_Leg.x" ,						MODEL_PRISONER_LFOOT			},		// �ߗ��̍���
	{ "data/MODEL/Prisoner/R_Leg.x" ,						MODEL_PRISONER_RFOOT			},		// �ߗ��̉E��

	//���
	{ "data/MODEL/Tank/Tankbody.x" ,					MODEL_TANK_TANKBODY,			},		// ��Ԃ̑�
	{ "data/MODEL/Tank/Tank_frontwheel.x" ,				MODEL_TANK_TANK_FRONTWHEEL,		},		// ��Ԃ̑O�^�C��
	{ "data/MODEL/Tank/Tank_backwheel.x" ,				MODEL_TANK_TANK_BACKWHEEL,		},		// ��Ԃ̌�^�C��
	{ "data/MODEL/Tank/Tankgun.x" ,						MODEL_TANK_TANKGUN,				},		// ��Ԃ̏e
	//{ "data/MODEL/Tank/Tankgun.x" ,						MODEL_TANK_TANKHEAD,				},// ��Ԃ̏e

	//�퓬�@
	{ "data/MODEL/BattlePlane/BattlePlane_Body.x",		MODEL_PLANE_BODY,				},		// �퓬�@�̋@��
	{ "data/MODEL/BattlePlane/BattlePlane_Gun.x",		MODEL_PLANE_GUN,				},		// �퓬�@�̏e

	//�w��
	{ "data/MODEL/Helicopter/Helicopter_Body.x" ,		MODEL_HELIBODY,					},		// �w���R�v�^�[�̋@��
	{ "data/MODEL/Helicopter/Helicopter_Propeller.x",	MODEL_HELIPROPELLER				},		// �w���R�v�^�[�̃v���y��
	{ "data/MODEL/Helicopter/Helicopter_Gun.x" ,		MODEL_HELIGUN					},		// �w���R�v�^�[�̏e

	//�{�X�@�\���f���J
	{ "data/MODEL/Boss/SolodeRoca.x" ,					MODEL_BOSS_BODY					},		// �\���f���J

	//�{�X�@�h���R���m�X�P
	{ "data/MODEL/DragonNosuke/Body.x" ,				MODEL_BOSSONE_BODY				},		// ��
	{ "data/MODEL/DragonNosuke/Head.x" ,				MODEL_BOSSONE_HEAD				},		// ��
	{ "data/MODEL/DragonNosuke/Knee_L_F.x" ,			MODEL_BOSSONE_KNEE_L_FRONT		},		// ���O���
	{ "data/MODEL/DragonNosuke/Knee_L_R.x" ,			MODEL_BOSSONE_KNEE_L_REAR		},		// ������
	{ "data/MODEL/DragonNosuke/Knee_R_F.x" ,			MODEL_BOSSONE_KNEE_R_FRONT		},		// �E�O���
	{ "data/MODEL/DragonNosuke/Knee_R_R.x" ,			MODEL_BOSSONE_KNEE_R_REAR		},		// �E����
	{ "data/MODEL/DragonNosuke/Knee2_L_F.x" ,			MODEL_BOSSONE_KNEE2_L_FRONT		},		// ���O���2
	{ "data/MODEL/DragonNosuke/Knee2_L_R.x" ,			MODEL_BOSSONE_KNEE2_L_REAR		},		// ������2
	{ "data/MODEL/DragonNosuke/Knee2_R_F.x" ,			MODEL_BOSSONE_KNEE2_R_FRONT		},		// �E�O���2
	{ "data/MODEL/DragonNosuke/Knee2_R_R.x" ,			MODEL_BOSSONE_KNEE2_R_REAR		},		// �E����2
	{ "data/MODEL/DragonNosuke/Leg_L_F.x" ,				MODEL_BOSSONE_LEG_L_FRONT		},		// ���O����
	{ "data/MODEL/DragonNosuke/Leg_L_R.x" ,				MODEL_BOSSONE_LEG_L_REAR		},		// ���㉺��
	{ "data/MODEL/DragonNosuke/Leg_R_F.x" ,				MODEL_BOSSONE_LEG_R_FRONT		},		// �E�O����
	{ "data/MODEL/DragonNosuke/Leg_R_R.x" ,				MODEL_BOSSONE_LEG_R_REAR		},		// �E�㉺��
	{ "data/MODEL/DragonNosuke/R_Ventilation.x" ,		MODEL_BOSSONE_L_VENTILATION		},		// �S��
	{ "data/MODEL/DragonNosuke/L_Ventilation.x" ,		MODEL_BOSSONE_R_VENTILATION		},		// �S��
	{ "data/MODEL/DragonNosuke/Light_L_F.x" ,			MODEL_BOSSONE_LIGHT_L_FRONT		},		// �d�C
	{ "data/MODEL/DragonNosuke/Light_L_R.x" ,			MODEL_BOSSONE_LIGHT_L_REAR		},		// �d�C
	{ "data/MODEL/DragonNosuke/Light_R_F.x" ,			MODEL_BOSSONE_LIGHT_R_FRONT		},		// �d�C
	{ "data/MODEL/DragonNosuke/Light_R_R.x" ,			MODEL_BOSSONE_LIGHT_R_REAR		},		// �d�C
	{ "data/MODEL/DragonNosuke/Balkan.x" ,				MODEL_BOSSONE_GUN_BALKAN		},		// ����̏ꏊ�ɒu�������f��
	{ "data/MODEL/DragonNosuke/Flamethrower.x" ,		MODEL_BOSSONE_GUN_FLAMETHROWER	},		// ����̏ꏊ�ɒu�������f��
	{ "data/MODEL/DragonNosuke/Incendiary.x" ,			MODEL_BOSSONE_GUN_INCENDIARY	},		// ����̏ꏊ�ɒu�������f��

	{ "data/MODEL/Wepon/Shield.x" ,						MODEL_WEPON_SHIELD },// ��
};


CModel::CModel(OBJ_TYPE type) : CScene(type)
{
	m_pCollision = nullptr;							// �����蔻��̃|�C���^
}

CModel::~CModel()
{
	// �����蔻��̍폜
	if (m_pCollision != nullptr)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}
}
//====================================================================
//���f���̃��[�h
//====================================================================
void CModel::LoadModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATERIAL *pMat;
	//���f���ǂݍ���
	for (int nCnt = 0; nCnt < (signed)m_vModelFileName.size(); nCnt++)
	{
		m_vModel.emplace_back(new CModel::MODEL);
		// X�t�@�C���̓ǂݍ���
		if (FAILED(D3DXLoadMeshFromX(
			m_vModelFileName[nCnt].modelFileName,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_vModel[nCnt]->pBuffmat,
			NULL,
			&m_vModel[nCnt]->nNumMat,
			&m_vModel[nCnt]->pMesh
		)))
		{
			std::cout << "LOAD FAILED!!! ModelFile - " << nCnt << m_vModelFileName[nCnt].modelFileName << NEWLINE;
		}
		else
		{
			std::cout << "Model Load - " << nCnt << m_vModelFileName[nCnt].modelFileName << NEWLINE;

			m_vModel[nCnt]->m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_vModel[nCnt]->nNumMat];
			pMat = (D3DXMATERIAL*)m_vModel[nCnt]->pBuffmat->GetBufferPointer();

			for (int nCntmat = 0; nCntmat < (int)m_vModel[nCnt]->nNumMat; nCntmat++)
			{
				m_vModel[nCnt]->m_pTexture[nCntmat] = NULL;
				D3DXCreateTextureFromFile(pDevice, pMat[nCntmat].pTextureFilename, &m_vModel[nCnt]->m_pTexture[nCntmat]);
			}
		}
	}

}
//====================================================================
//���f���̊J��
//====================================================================
void CModel::UnLoad(void)
{
	//�}�b�v�̃��f���ǂݍ���
	for (size_t nCnt = 0; nCnt < m_vModel.size(); nCnt++)
	{
		if (m_vModel[nCnt]->pBuffmat != NULL)
		{
			m_vModel[nCnt]->pBuffmat->Release();
			m_vModel[nCnt]->pBuffmat = NULL;
		}
		if (m_vModel[nCnt]->pMesh != NULL)
		{
			m_vModel[nCnt]->pMesh->Release();
			m_vModel[nCnt]->pMesh = NULL;
		}
		if (m_vModel[nCnt]->m_pTexture != NULL)
		{
			for (int nCntmat = 0; nCntmat < (int)m_vModel[nCnt]->nNumMat; nCntmat++)
			{
				if (m_vModel[nCnt]->m_pTexture[nCntmat] != NULL)
				{
					m_vModel[nCnt]->m_pTexture[nCntmat]->Release();
					m_vModel[nCnt]->m_pTexture[nCntmat] = NULL;
				}
			}
			delete[] m_vModel[nCnt]->m_pTexture;
			m_vModel[nCnt]->m_pTexture = NULL;
		}
		delete m_vModel[nCnt];
		m_vModel[nCnt] = nullptr;
	}
	m_vModel.clear();
}
//====================================================================
//������
//====================================================================
HRESULT CModel::Init(void)
{
	//m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ��]
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// �J���[
	m_AddColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// ���Z����F
	m_bDieFlag = false;								// ���S�t���O
	m_bColorChangeFlag = false;									// �F�ύX�t���O
	m_bDisp = true;									// �`�悷��
	m_type = 0;									// ���
	m_modelCount = 0;
	int nNumVertices;
	DWORD sizeFVF;
	BYTE *pVertexBuffer;
	// �����蔻�萶��
	m_pCollision = CCollision::Create();
	int nCntID = GetModelID(m_modelID);
	for (size_t nCnt = 0; nCnt < m_vModel.size(); nCnt++)
	{
		if (nCnt > 200 && nCnt < 208)
		{
			if (m_vModel[nCnt]->pMesh != NULL)
			{
				//���_�����擾
				nNumVertices = m_vModel[nCnt]->pMesh->GetNumVertices();
				//���_�t�H�[�}�b�g�̃T�C�Y���擾
				sizeFVF = D3DXGetFVFVertexSize(m_vModel[nCnt]->pMesh->GetFVF());
				//���_�o�b�t�@�����b�N
				m_vModel[nCnt]->pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertexBuffer);
				for (int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++)
				{
					D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVertexBuffer;
					//���ׂĂ̒��_�����r���čŏ��A�ő�𔲂��o��
					if (m_vModel[nCnt]->vtxMin.x > vtx.x)
					{
						m_vModel[nCnt]->vtxMin.x = vtx.x;
					}
					if (m_vModel[nCnt]->vtxMin.y > vtx.y)
					{
						m_vModel[nCnt]->vtxMin.y = vtx.y;
					}
					if (m_vModel[nCnt]->vtxMin.z > vtx.z)
					{
						m_vModel[nCnt]->vtxMin.z = vtx.z;
					}
					if (m_vModel[nCnt]->vtxMax.x < vtx.x)
					{
						m_vModel[nCnt]->vtxMax.x = vtx.x;
					}
					if (m_vModel[nCnt]->vtxMax.y < vtx.y)
					{
						m_vModel[nCnt]->vtxMax.y = vtx.y;
					}
					if (m_vModel[nCnt]->vtxMax.z < vtx.z)
					{
						m_vModel[nCnt]->vtxMax.z = vtx.z;
					}
					pVertexBuffer += sizeFVF; // �T�C�Y���|�C���^��i�߂�
				}
				//���_�o�b�t�@���A�����b�N
				m_vModel[nCnt]->pMesh->UnlockVertexBuffer();
			}
		}
	}
	return S_OK;
}
//====================================================================
//�I��
//====================================================================
void CModel::Uninit(void)
{
}
//====================================================================
//�X�V
//====================================================================
void CModel::Update(void)
{
	//nullcheck
	if (m_pCollision)
	{
		//���W�ݒ�
		m_pCollision->SetPos(&m_pos);
	}
}
//====================================================================
//�`��
//====================================================================
void CModel::Draw(D3DXMATRIX mat)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �}�g���b�N�X�̌v�Z
	CHossoLibrary::CalcMatrix(&m_mtxWorld, m_pos, m_rot);

	// �|���S���̕`��
	pDevice->SetTexture(0, NULL);

	//�e�q�֌W
	if (m_pParent== NULL)
	{
		D3DXMatrixMultiply(&m_mtxWorld,
			&m_mtxWorld,
			&mat);
	}
	else
	{
		D3DXMatrixMultiply(&m_mtxWorld,
			&m_mtxWorld,
			&m_pParent->m_mtxWorld);
	}

	// �`��
	DrawMesh();
}
//====================================================================
//�`��
//====================================================================
void CModel::Draw()
{
	// �}�g���b�N�X�̌v�Z
	CHossoLibrary::CalcMatrix(&m_mtxWorld, m_pos, m_rot);

	// �`��
	DrawMesh();
}
//====================================================================
//�f�o�b�O
//====================================================================
void CModel::DebugInfo()
{

}
//====================================================================
//���f���̃N���G�C�g
//====================================================================
CModel *CModel::Create(int type, int modelCount)
{
	CModel*pModel;
	pModel = new CModel(TYPE_NONE);
	pModel->Init();
	pModel->m_type = type;
	pModel->m_modelCount = modelCount;
	pModel->m_modelID = (CHARA_MODEL)((type * 100) + modelCount);

	return pModel;
}
//====================================================================
//���f���̃N���G�C�g(�V�[���ŊǗ�����)
//====================================================================
CModel * CModel::CreateSceneManagement(int type, int modelCount, OBJ_TYPE objtype)
{
	CModel*pModel;
	pModel = new CModel(objtype);
	pModel->Init();
	pModel->m_type = type;
	pModel->m_modelCount = modelCount;
	pModel->m_modelID = (CHARA_MODEL)((type * 100) + modelCount);
	return pModel;
}
//====================================================================
//���f���̃t�@�C�����擾
//====================================================================
char * CModel::GetModelFileName(int nType, int nModelCount)
{
	int nCntID =((nType * 100) + nModelCount);
	return m_vModelFileName[GetModelID((CHARA_MODEL)nCntID)].modelFileName;
}

//====================================================================
 //�}�g���b�N�X�v�Z
 //====================================================================
void CModel::NotDrawCalcMtxOnly(D3DXMATRIX * pParentMtx)
{
	// �}�g���b�N�X�̌v�Z
	CHossoLibrary::CalcMatrix(&m_mtxWorld, m_pos, m_rot);

	//�e�}�g���b�N�X�̌v�Z
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		pParentMtx);
}
//====================================================================
//�^�C�v�̐ݒ�
//====================================================================
void CModel::SetType(int type)
{
	m_type = type;
	m_modelID = (CHARA_MODEL)((m_type * 100) + m_modelCount);
}
//====================================================================
//���f���̎�ނ̐ݒ�
//====================================================================
void CModel::SetModelConut(int nModelCount)
{
	m_modelCount = nModelCount;
	m_modelID = (CHARA_MODEL)((m_type * 100) + m_modelCount);
}
//====================================================================
//���b�V�����̎擾
//====================================================================
LPD3DXMESH CModel::GetMesh(void)
{
	int nCntID = GetModelID(m_modelID);
	return m_vModel[nCntID]->pMesh;
}
//====================================================================
//�R���W��������
//====================================================================
void CModel::DeleteCollision()
{
	// �����蔻��̍폜
	if (m_pCollision != nullptr)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}
}
//====================================================================
//���f��ID�̐ݒ�
//====================================================================
void CModel::SetModelID(CHARA_MODEL model)
{
	m_modelID = model;
	m_type = m_modelID / 100;
	m_modelCount = m_modelID % 100;
}
//====================================================================
//���f���̔Ԑ��̎擾
//====================================================================
int CModel::GetModelID(CHARA_MODEL model)
{
	for (size_t nCnt = 0; nCnt < m_vModel.size(); nCnt++)
	{
		if (m_vModelFileName[nCnt].FileModelID == model)
		{
			return nCnt;
		}
	}
	return -1;
}

//====================================================================
//�`��
//====================================================================
void CModel::DrawMesh()
{
	//�`�悵�Ȃ�����return
	if (!m_bDisp)
	{
		return;
	}
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATERIAL *pMat;
	int nCntID = GetModelID(m_modelID);
	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	// �}�e���A�����ɑ΂���|�C���^���擾
	if (m_vModel[nCntID]->pBuffmat != NULL)
	{
		pMat = (D3DXMATERIAL*)m_vModel[nCntID]->pBuffmat->GetBufferPointer();
		pDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);						// ���؂���烂�[�h�L��

		for (int nCnt = 0; nCnt < (int)m_vModel[nCntID]->nNumMat; nCnt++)
		{
			// ���[�J���̃}�e���A��
			D3DMATERIAL9 LocalMat = pMat[nCnt].MatD3D;

			// �F�ύX�t���O���I���̂Ƃ�
			if (m_bColorChangeFlag)
			{
				// �}�e���A���J���[
				D3DXCOLOR MatCol = LocalMat.Diffuse;
				// ���Z����F����
				MatCol += m_AddColor;
				// ���[�J���}�e���A���̐F�ύX
				LocalMat.Diffuse = MatCol;
			}
			pDevice->SetTexture(0, m_vModel[nCntID]->m_pTexture[nCnt]);
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&LocalMat);
			// �`��
			m_vModel[nCntID]->pMesh->DrawSubset(nCnt);
		}
	}
	pDevice->SetRenderState(D3DRS_SPECULARENABLE, FALSE);						// ���؂���烂�[�h����
}

