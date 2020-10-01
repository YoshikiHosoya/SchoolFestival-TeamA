//=============================================================================
// モデル処理 [Model.cpp]
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
	//プレイヤー
	{ "data/MODEL/character/Player/Waist.x",				MODEL_PLAYER_WAIST				},		// プレイヤーの腰
	{ "data/MODEL/character/Player/Body.x" ,				MODEL_PLAYER_BODY				},		// プレイヤーの体
	{ "data/MODEL/character/Player/Head.x" ,				MODEL_PLAYER_HEAD				},		// プレイヤーの頭
	{ "data/MODEL/character/Player/L_Sholder.x",			MODEL_PLAYER_L_SHOLDER			},		// プレイヤーの左肩
	{ "data/MODEL/character/Player/R_Sholder.x",			MODEL_PLAYER_R_SHOLDER			},		// プレイヤーの右肩
	{ "data/MODEL/character/Player/L_Arm.x" ,				MODEL_PLAYER_LARM				},		// プレイヤーの左腕
	{ "data/MODEL/character/Player/R_Arm.x" ,				MODEL_PLAYER_RARM				},		// プレイヤーの右腕
	{ "data/MODEL/character/Player/L_Hand.x",				MODEL_PLAYER_LHAND				},		// プレイヤーの左手
	{ "data/MODEL/character/Player/R_Hand.x",				MODEL_PLAYER_RHAND				},		// プレイヤーの右手
	{ "data/MODEL/character/Player/L_Knee.x",				MODEL_PLAYER_LKNEE				},		// プレイヤーの左膝
	{ "data/MODEL/character/Player/R_Knee.x",				MODEL_PLAYER_RKNEE				},		// プレイヤーの右膝
	{ "data/MODEL/character/Player/L_Foot.x",				MODEL_PLAYER_LLEG				},		// プレイヤーの左脚
	{ "data/MODEL/character/Player/R_Foot.x",				MODEL_PLAYER_RLEG				},		// プレイヤーの右脚
	{ "data/MODEL/character/Player/L_Leg.x",				MODEL_PLAYER_LFOOT				},		// プレイヤーの左足
	{ "data/MODEL/character/Player/R_Leg.x",				MODEL_PLAYER_RFOOT				},		// プレイヤーの右足

	{ "data/MODEL/character/Player/2pModel/Waist.x",		MODEL_PLAYER_2P_WAIST			 },		// 2Pプレイヤーの腰
	{ "data/MODEL/character/Player/2pModel/Body.x",			MODEL_PLAYER_2P_BODY			 },		// 2Pプレイヤーの体
	{ "data/MODEL/character/Player/2pModel/L_Knee.x",		MODEL_PLAYER_2P_LKNEE			 },		// 2Pプレイヤーの左膝
	{ "data/MODEL/character/Player/2pModel/R_Knee.x",		MODEL_PLAYER_2P_RKNEE			 },		// 2Pプレイヤーの右膝
	{ "data/MODEL/character/Player/2pModel/L_Foot.x",		MODEL_PLAYER_2P_LFOOT			 },		// 2Pプレイヤーの左脚
	{ "data/MODEL/character/Player/2pModel/R_Foot.x",		MODEL_PLAYER_2P_RFOOT			 },		// 2Pプレイヤーの右脚


	//敵
	{ "data/MODEL/Enemy/EnemyHuman/Waist.x",				MODEL_ENEMY_HUMAN_WAIST },				// 腰
	{ "data/MODEL/Enemy/EnemyHuman/Body.x" ,				MODEL_ENEMY_HUMAN_HEAD },				// 頭
	{ "data/MODEL/Enemy/EnemyHuman/Head.x" ,				MODEL_ENEMY_HUMAN_BODY },				// 体
	{ "data/MODEL/Enemy/EnemyHuman/L_Sholder.x" ,			MODEL_ENEMY_HUMAN_L_SHOLDER },			// 左肩
	{ "data/MODEL/Enemy/EnemyHuman/R_Sholder.x" ,			MODEL_ENEMY_HUMAN_R_SHOLDER },			// 右肩
	{ "data/MODEL/Enemy/EnemyHuman/L_Arm.x" ,				MODEL_ENEMY_HUMAN_LARM },				// 左腕
	{ "data/MODEL/Enemy/EnemyHuman/R_Arm.x" ,				MODEL_ENEMY_HUMAN_RARM },				// 右腕
	{ "data/MODEL/Enemy/EnemyHuman/L_Hand.x" ,				MODEL_ENEMY_HUMAN_LHAND },				// 左手
	{ "data/MODEL/Enemy/EnemyHuman/R_Hand.x" ,				MODEL_ENEMY_HUMAN_RHAND },				// 右手
	{ "data/MODEL/Enemy/EnemyHuman/L_Knee.x" ,				MODEL_ENEMY_HUMAN_LKNEE },				// 左膝
	{ "data/MODEL/Enemy/EnemyHuman/R_Knee.x" ,				MODEL_ENEMY_HUMAN_RKNEE },				// 右膝
	{ "data/MODEL/Enemy/EnemyHuman/L_Foot.x" ,				MODEL_ENEMY_HUMAN_LLEG },				// 左脚
	{ "data/MODEL/Enemy/EnemyHuman/R_Foot.x" ,				MODEL_ENEMY_HUMAN_RLEG },				// 右脚
	{ "data/MODEL/Enemy/EnemyHuman/L_Leg.x" ,				MODEL_ENEMY_HUMAN_LFOOT },				// 左足
	{ "data/MODEL/Enemy/EnemyHuman/R_Leg.x" ,				MODEL_ENEMY_HUMAN_RFOOT },				// 右足
	//
	{ "data/MODEL/Enemy/EnemyHelicopter/Body.x" ,			MODEL_ENEMY_HELICOPTER_BODY },			// 右足
	{ "data/MODEL/Enemy/EnemyHelicopter/Propeller.x" ,		MODEL_ENEMY_HELICOPTER_PROPELLER },		// 右足
	//
	{ "data/MODEL/Enemy/MeltyHoney/Body.x" ,				MODEL_ENEMY_MELTYHONEY_BODY },			// 右足
	{ "data/MODEL/Enemy/MeltyHoney/wheel.x" ,				MODEL_ENEMY_MELTYHONEY_WHEEL },			// 右足
	//
	{ "data/MODEL/Enemy/Zycocca/Body.x" ,					MODEL_ENEMY_ZYCOCCA_BODY },				// 右足
	{ "data/MODEL/Enemy/Zycocca/wheel.x" ,					MODEL_ENEMY_ZYCOCCA_WHEEL },			// 右足

	// ドローン sky
	{ "data/MODEL/Enemy/Drone/SkyDrone_x/Drone_Body.x" ,	MODEL_DRONE_BODY },						// 体
	{ "data/MODEL/Enemy/Drone/SkyDrone_x/Drone_Hand_L.x" ,	MODEL_DRONE_HAND_L },					// 左手
	{ "data/MODEL/Enemy/Drone/SkyDrone_x/Drone_Hand_R.x" ,	MODEL_DRONE_HAND_R },					// 右手
	{ "data/MODEL/Enemy/Drone/SkyDrone_x/Drone_Eye.x" ,		MODEL_DRONE_EYE },						// 目

	// ドローン wall
	{ "data/MODEL/Enemy/Drone/WallDrone_x/WallDrone_Head.x" ,		MODEL_DRONE_HEAD },				// 0ドローンの頭-1
	{ "data/MODEL/Enemy/Drone/WallDrone_x/WallDrone_Joint.x" ,		MODEL_DRONE_JOINT_F_R },		// 1右前足関節0
	{ "data/MODEL/Enemy/Drone/WallDrone_x/WallDrone_Thigh_F_R.x" ,	MODEL_DRONE_THIGH_F_R },		// 2右前大腿1
	{ "data/MODEL/Enemy/Drone/WallDrone_x/WallDrone_Leg_F_R.x" ,	MODEL_DRONE_LEG_F_R },			// 3右前足2
	{ "data/MODEL/Enemy/Drone/WallDrone_x/WallDrone_Joint.x" ,		MODEL_DRONE_JOINT_B_R },		// 4右後足関節0
	{ "data/MODEL/Enemy/Drone/WallDrone_x/WallDrone_Thigh_B_R.x" ,	MODEL_DRONE_THIGH_B_R },		// 5右後大腿4
	{ "data/MODEL/Enemy/Drone/WallDrone_x/WallDrone_Leg_B_R.x" ,	MODEL_DRONE_LEG_B_R },			// 6右後足5
	{ "data/MODEL/Enemy/Drone/WallDrone_x/WallDrone_Joint.x" ,		MODEL_DRONE_JOINT_F_L },		// 7左前足関節0
	{ "data/MODEL/Enemy/Drone/WallDrone_x/WallDrone_Thigh_F_L.x" ,	MODEL_DRONE_THIGH_F_L },		// 8左前大腿7
	{ "data/MODEL/Enemy/Drone/WallDrone_x/WallDrone_Leg_F_L.x" ,	MODEL_DRONE_LEG_F_L },			// 9左前足8
	{ "data/MODEL/Enemy/Drone/WallDrone_x/WallDrone_Joint.x" ,		MODEL_DRONE_JOINT_B_L },		// 10左後足関節0
	{ "data/MODEL/Enemy/Drone/WallDrone_x/WallDrone_Thigh_B_L.x" ,	MODEL_DRONE_THIGH_B_L },		// 11左後大腿10
	{ "data/MODEL/Enemy/Drone/WallDrone_x/WallDrone_Leg_B_L.x" ,	MODEL_DRONE_LEG_B_L },			// 12左後足11

	//マップ
	{ "data/MODEL/map/Map1_Boss stage.x" ,					MODEL_MAP_TUTORIAL },					// チュートリアルマップ
	{ "data/MODEL/map/Stage1-1.x" ,							MODEL_MAP_STAGE1_1 },					// ステージ1-1
	{ "data/MODEL/map/Stage1-2.x" ,							MODEL_MAP_STAGE1_2 },					// ステージ1-2
	{ "data/MODEL/map/Stage1-3.x" ,							MODEL_MAP_STAGE1_3 },					// ステージ1-3
	{ "data/MODEL/map/Map1_Boss stage.x" ,					MODEL_MAP_STAGE1_BOSS },				// ボスステージ1
	{ "data/MODEL/map/Stage2-1.x" ,							MODEL_MAP_STAGE2_1 },					// ステージ2-1
	{ "data/MODEL/map/Stage2-2.x" ,							MODEL_MAP_STAGE2_2 },					// ステージ2-2
	{ "data/MODEL/map/Stage2-3.x" ,							MODEL_MAP_STAGE2_3 },					// ステージ2-3
	{ "data/MODEL/map/Map1_Boss stage.x" ,					MODEL_MAP_STAGE2_BOSS },				// ボスステージ2
	{ "data/MODEL/map/Stage2-1_Nocollision.x" ,				MODEL_MAP_NO_COLLISION_STAGE2_1 },					// ステージ2-1 当たり判定無し
	{ "data/MODEL/map/Stage2-2_Nocollision.x" ,				MODEL_MAP_NO_COLLISION_STAGE2_2 },					// ステージ2-2 当たり判定無し
	{ "data/MODEL/map/Stage2-3_Nocollision.x" ,				MODEL_MAP_NO_COLLISION_STAGE2_3 },					// ステージ2-3 当たり判定無し


	//武器
	{ "data/MODEL/Gun/Gun.x" ,								MODEL_GUN_HANDGUN },					// ハンドガン
	{ "data/MODEL/Gun/Assaultrifle.x" ,						MODEL_GUN_HEAVYMACHINEGUN },			// ヘビーマシンガン
	{ "data/MODEL/Gun/Shootgun.x" ,							MODEL_GUN_SHOTGUN },					// ショットガン
	{ "data/MODEL/Gun/Chargerifle.x" ,						MODEL_GUN_LASERGUN },					// レーザーガン
	{ "data/MODEL/Gun/Rocketlauncher.x" ,					MODEL_GUN_ROCKETLAUNCHER },				// ロケットランチャー
	{ "data/MODEL/Gun/Flameshoot.x" ,						MODEL_GUN_FLAMESHOT },					// フレイムショット
	{ "data/MODEL/Gun/TankGun.x" ,							MODEL_GUN_TANKGUN },					// 戦車の銃
	{ "data/MODEL/Gun/PlaneGun.x" ,							MODEL_GUN_PLANEGUN },					// 戦闘機の銃
	{ "data/MODEL/Gun/HeliGun.x" ,							MODEL_GUN_HELIGUN },					// ヘリの銃
	{ "data/MODEL/Gun/Balkan.x" ,							MODEL_GUN_BALKAN },						// バルカン
	{ "data/MODEL/Gun/Flamethrower.x" ,						MODEL_GUN_FLAMETHROWER },				// 火炎放射器
	{ "data/MODEL/Gun/Incendiary.x" ,						MODEL_GUN_INCENDIARY },					// 焼夷弾
	{ "data/MODEL/Gun/Knife.x" ,							MODEL_KNIFE },							// ナイフ

	//弾
	{ "data/MODEL/Bullet/Sphere.x" ,						MODEL_BULLET_SPHERE, },					// 丸
	{ "data/MODEL/Bullet/Rockets.x" ,						MODEL_BULLET_ROCKETLAUNCHER, },			// ロケットランチャー
	{ "data/MODEL/Bullet/Grenade.x" ,						MODEL_BULLET_GRENADE, },				// グレネード
	{ "data/MODEL/Bullet/Tankmissile.x" ,					MODEL_BULLET_TANKGRENADE, },			// 戦車のグレネード
	{ "data/MODEL/Bullet/Missile.x" ,						MODEL_BULLET_MISSILE, },				// ミサイル

	//オブジェクト
	{ "data/MODEL/Object/Obstacle_Box.x" ,					OBSTACLE_TYPE_BOX },					// 箱
	{ "data/MODEL/Object/Obstacle_Barrel.x" ,				OBSTACLE_TYPE_BARREL },					// 樽
	{ "data/MODEL/Object/Obstacle_BarrelBomb.x" ,			OBSTACLE_TYPE_BARRELBOMB },				// 樽爆弾
	{ "data/MODEL/Object/Obstacle_Tree.x" ,					OBSTACLE_TYPE_TREE },					// 木
	{ "data/MODEL/Object/Obstacle_Chest.x" ,				OBSTACLE_TYPE_CHEST },					// 金庫
	{ "data/MODEL/Object/Obstacle_Sandbags.x" ,				OBSTACLE_TYPE_SANDBAGS },				// 土嚢
	{ "data/MODEL/Object/Obstacle_Car.x" ,					OBSTACLE_TYPE_CAR },					// 車
	{ "data/MODEL/Object/Obstacle_Balloon.x" ,				OBSTACLE_TYPE_BALLOON },				// 風船
	{ "data/MODEL/Object/Obstacle_PresentBox01.x" ,			OBSTACLE_TYPE_PRESENTBOX },				// プレゼント
	{ "data/MODEL/Object/Obstacle_PresentBox00.x" ,			OBSTACLE_TYPE_PRESENTBOX_RARE },		// プレゼント レア

	//捕虜
	{ "data/MODEL/Prisoner/Waist.x",						MODEL_PRISONER_WAIST			},		// 捕虜の腰
	{ "data/MODEL/Prisoner/Body.x" ,						MODEL_PRISONER_BODY				},		// 捕虜の体
	{ "data/MODEL/Prisoner/Head.x" ,						MODEL_PRISONER_HEAD				},		// 捕虜の頭
	{ "data/MODEL/Prisoner/L_Sholder.x" ,					MODEL_PRISONER_L_SHOLDER		},		// 捕虜の左肩
	{ "data/MODEL/Prisoner/R_Sholder.x" ,					MODEL_PRISONER_R_SHOLDER		},		// 捕虜の右肩
	{ "data/MODEL/Prisoner/L_Arm.x" ,						MODEL_PRISONER_LARM				},		// 捕虜の左腕
	{ "data/MODEL/Prisoner/R_Arm.x" ,						MODEL_PRISONER_RARM				},		// 捕虜の右腕
	{ "data/MODEL/Prisoner/L_Hand.x" ,						MODEL_PRISONER_LHAND			},		// 捕虜の左手
	{ "data/MODEL/Prisoner/R_Hand.x" ,						MODEL_PRISONER_RHAND			},		// 捕虜の右手
	{ "data/MODEL/Prisoner/L_Knee.x" ,						MODEL_PRISONER_LKNEE			},		// 捕虜の左膝
	{ "data/MODEL/Prisoner/R_Knee.x" ,						MODEL_PRISONER_RKNEE			},		// 捕虜の右膝
	{ "data/MODEL/Prisoner/L_Foot.x" ,						MODEL_PRISONER_LLEG				},		// 捕虜の左脚
	{ "data/MODEL/Prisoner/R_Foot.x" ,						MODEL_PRISONER_RLEG				},		// 捕虜の右脚
	{ "data/MODEL/Prisoner/L_Leg.x" ,						MODEL_PRISONER_LFOOT			},		// 捕虜の左足
	{ "data/MODEL/Prisoner/R_Leg.x" ,						MODEL_PRISONER_RFOOT			},		// 捕虜の右足

	//戦車
	{ "data/MODEL/Tank/Tankbody.x" ,					MODEL_TANK_TANKBODY,			},		// 戦車の体
	{ "data/MODEL/Tank/Tank_frontwheel.x" ,				MODEL_TANK_TANK_FRONTWHEEL,		},		// 戦車の前タイヤ
	{ "data/MODEL/Tank/Tank_backwheel.x" ,				MODEL_TANK_TANK_BACKWHEEL,		},		// 戦車の後タイヤ
	{ "data/MODEL/Tank/Tankgun.x" ,						MODEL_TANK_TANKGUN,				},		// 戦車の銃
	//{ "data/MODEL/Tank/Tankgun.x" ,						MODEL_TANK_TANKHEAD,				},// 戦車の銃

	//戦闘機
	{ "data/MODEL/BattlePlane/BattlePlane_Body.x",		MODEL_PLANE_BODY,				},		// 戦闘機の機体
	{ "data/MODEL/BattlePlane/BattlePlane_Gun.x",		MODEL_PLANE_GUN,				},		// 戦闘機の銃

	//ヘリ
	{ "data/MODEL/Helicopter/Helicopter_Body.x" ,		MODEL_HELIBODY,					},		// ヘリコプターの機体
	{ "data/MODEL/Helicopter/Helicopter_Propeller.x",	MODEL_HELIPROPELLER				},		// ヘリコプターのプロペラ
	{ "data/MODEL/Helicopter/Helicopter_Gun.x" ,		MODEL_HELIGUN					},		// ヘリコプターの銃

	//ボス　ソルデロカ
	{ "data/MODEL/Boss/SolodeRoca.x" ,					MODEL_BOSS_BODY					},		// ソルデロカ

	//ボス　ドラコンノスケ
	{ "data/MODEL/DragonNosuke/Body.x" ,				MODEL_BOSSONE_BODY				},		// 体
	{ "data/MODEL/DragonNosuke/Head.x" ,				MODEL_BOSSONE_HEAD				},		// 頭
	{ "data/MODEL/DragonNosuke/Knee_L_F.x" ,			MODEL_BOSSONE_KNEE_L_FRONT		},		// 左前大腿
	{ "data/MODEL/DragonNosuke/Knee_L_R.x" ,			MODEL_BOSSONE_KNEE_L_REAR		},		// 左後大腿
	{ "data/MODEL/DragonNosuke/Knee_R_F.x" ,			MODEL_BOSSONE_KNEE_R_FRONT		},		// 右前大腿
	{ "data/MODEL/DragonNosuke/Knee_R_R.x" ,			MODEL_BOSSONE_KNEE_R_REAR		},		// 右後大腿
	{ "data/MODEL/DragonNosuke/Knee2_L_F.x" ,			MODEL_BOSSONE_KNEE2_L_FRONT		},		// 左前大腿2
	{ "data/MODEL/DragonNosuke/Knee2_L_R.x" ,			MODEL_BOSSONE_KNEE2_L_REAR		},		// 左後大腿2
	{ "data/MODEL/DragonNosuke/Knee2_R_F.x" ,			MODEL_BOSSONE_KNEE2_R_FRONT		},		// 右前大腿2
	{ "data/MODEL/DragonNosuke/Knee2_R_R.x" ,			MODEL_BOSSONE_KNEE2_R_REAR		},		// 右後大腿2
	{ "data/MODEL/DragonNosuke/Leg_L_F.x" ,				MODEL_BOSSONE_LEG_L_FRONT		},		// 左前下腿
	{ "data/MODEL/DragonNosuke/Leg_L_R.x" ,				MODEL_BOSSONE_LEG_L_REAR		},		// 左後下腿
	{ "data/MODEL/DragonNosuke/Leg_R_F.x" ,				MODEL_BOSSONE_LEG_R_FRONT		},		// 右前下腿
	{ "data/MODEL/DragonNosuke/Leg_R_R.x" ,				MODEL_BOSSONE_LEG_R_REAR		},		// 右後下腿
	{ "data/MODEL/DragonNosuke/R_Ventilation.x" ,		MODEL_BOSSONE_L_VENTILATION		},		// 鉄板
	{ "data/MODEL/DragonNosuke/L_Ventilation.x" ,		MODEL_BOSSONE_R_VENTILATION		},		// 鉄板
	{ "data/MODEL/DragonNosuke/Light_L_F.x" ,			MODEL_BOSSONE_LIGHT_L_FRONT		},		// 青電気
	{ "data/MODEL/DragonNosuke/Light_L_R.x" ,			MODEL_BOSSONE_LIGHT_L_REAR		},		// 青電気
	{ "data/MODEL/DragonNosuke/Light_R_F.x" ,			MODEL_BOSSONE_LIGHT_R_FRONT		},		// 青電気
	{ "data/MODEL/DragonNosuke/Light_R_R.x" ,			MODEL_BOSSONE_LIGHT_R_REAR		},		// 青電気
	{ "data/MODEL/DragonNosuke/Balkan.x" ,				MODEL_BOSSONE_GUN_BALKAN		},		// 武器の場所に置く仮モデル
	{ "data/MODEL/DragonNosuke/Flamethrower.x" ,		MODEL_BOSSONE_GUN_FLAMETHROWER	},		// 武器の場所に置く仮モデル
	{ "data/MODEL/DragonNosuke/Incendiary.x" ,			MODEL_BOSSONE_GUN_INCENDIARY	},		// 武器の場所に置く仮モデル

	{ "data/MODEL/Wepon/Shield.x" ,						MODEL_WEPON_SHIELD },// 盾
};


CModel::CModel(OBJ_TYPE type) : CScene(type)
{
	m_pCollision = nullptr;							// 当たり判定のポインタ
}

CModel::~CModel()
{
	// 当たり判定の削除
	if (m_pCollision != nullptr)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}
}
//====================================================================
//モデルのロード
//====================================================================
void CModel::LoadModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATERIAL *pMat;
	//モデル読み込み
	for (int nCnt = 0; nCnt < (signed)m_vModelFileName.size(); nCnt++)
	{
		m_vModel.emplace_back(new CModel::MODEL);
		// Xファイルの読み込み
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
//モデルの開放
//====================================================================
void CModel::UnLoad(void)
{
	//マップのモデル読み込み
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
//初期化
//====================================================================
HRESULT CModel::Init(void)
{
	//m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 回転
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// カラー
	m_AddColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// 加算する色
	m_bDieFlag = false;								// 死亡フラグ
	m_bColorChangeFlag = false;									// 色変更フラグ
	m_bDisp = true;									// 描画する
	m_type = 0;									// 種類
	m_modelCount = 0;
	int nNumVertices;
	DWORD sizeFVF;
	BYTE *pVertexBuffer;
	// 当たり判定生成
	m_pCollision = CCollision::Create();
	int nCntID = GetModelID(m_modelID);
	for (size_t nCnt = 0; nCnt < m_vModel.size(); nCnt++)
	{
		if (nCnt > 200 && nCnt < 208)
		{
			if (m_vModel[nCnt]->pMesh != NULL)
			{
				//頂点数を取得
				nNumVertices = m_vModel[nCnt]->pMesh->GetNumVertices();
				//頂点フォーマットのサイズを取得
				sizeFVF = D3DXGetFVFVertexSize(m_vModel[nCnt]->pMesh->GetFVF());
				//頂点バッファをロック
				m_vModel[nCnt]->pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertexBuffer);
				for (int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++)
				{
					D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVertexBuffer;
					//すべての頂点情報を比較して最小、最大を抜き出す
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
					pVertexBuffer += sizeFVF; // サイズ分ポインタを進める
				}
				//頂点バッファをアンロック
				m_vModel[nCnt]->pMesh->UnlockVertexBuffer();
			}
		}
	}
	return S_OK;
}
//====================================================================
//終了
//====================================================================
void CModel::Uninit(void)
{
}
//====================================================================
//更新
//====================================================================
void CModel::Update(void)
{
	//nullcheck
	if (m_pCollision)
	{
		//座標設定
		m_pCollision->SetPos(&m_pos);
	}
}
//====================================================================
//描画
//====================================================================
void CModel::Draw(D3DXMATRIX mat)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// マトリックスの計算
	CHossoLibrary::CalcMatrix(&m_mtxWorld, m_pos, m_rot);

	// ポリゴンの描画
	pDevice->SetTexture(0, NULL);

	//親子関係
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

	// 描画
	DrawMesh();
}
//====================================================================
//描画
//====================================================================
void CModel::Draw()
{
	// マトリックスの計算
	CHossoLibrary::CalcMatrix(&m_mtxWorld, m_pos, m_rot);

	// 描画
	DrawMesh();
}
//====================================================================
//デバッグ
//====================================================================
void CModel::DebugInfo()
{

}
//====================================================================
//モデルのクリエイト
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
//モデルのクリエイト(シーンで管理する)
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
//モデルのファイル名取得
//====================================================================
char * CModel::GetModelFileName(int nType, int nModelCount)
{
	int nCntID =((nType * 100) + nModelCount);
	return m_vModelFileName[GetModelID((CHARA_MODEL)nCntID)].modelFileName;
}

//====================================================================
 //マトリックス計算
 //====================================================================
void CModel::NotDrawCalcMtxOnly(D3DXMATRIX * pParentMtx)
{
	// マトリックスの計算
	CHossoLibrary::CalcMatrix(&m_mtxWorld, m_pos, m_rot);

	//親マトリックスの計算
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		pParentMtx);
}
//====================================================================
//タイプの設定
//====================================================================
void CModel::SetType(int type)
{
	m_type = type;
	m_modelID = (CHARA_MODEL)((m_type * 100) + m_modelCount);
}
//====================================================================
//モデルの種類の設定
//====================================================================
void CModel::SetModelConut(int nModelCount)
{
	m_modelCount = nModelCount;
	m_modelID = (CHARA_MODEL)((m_type * 100) + m_modelCount);
}
//====================================================================
//メッシュ情報の取得
//====================================================================
LPD3DXMESH CModel::GetMesh(void)
{
	int nCntID = GetModelID(m_modelID);
	return m_vModel[nCntID]->pMesh;
}
//====================================================================
//コリジョン消去
//====================================================================
void CModel::DeleteCollision()
{
	// 当たり判定の削除
	if (m_pCollision != nullptr)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}
}
//====================================================================
//モデルIDの設定
//====================================================================
void CModel::SetModelID(CHARA_MODEL model)
{
	m_modelID = model;
	m_type = m_modelID / 100;
	m_modelCount = m_modelID % 100;
}
//====================================================================
//モデルの番数の取得
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
//描画
//====================================================================
void CModel::DrawMesh()
{
	//描画しない時はreturn
	if (!m_bDisp)
	{
		return;
	}
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATERIAL *pMat;
	int nCntID = GetModelID(m_modelID);
	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	// マテリアル情報に対するポインタを取得
	if (m_vModel[nCntID]->pBuffmat != NULL)
	{
		pMat = (D3DXMATERIAL*)m_vModel[nCntID]->pBuffmat->GetBufferPointer();
		pDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);						// すぺきゅらモード有効

		for (int nCnt = 0; nCnt < (int)m_vModel[nCntID]->nNumMat; nCnt++)
		{
			// ローカルのマテリアル
			D3DMATERIAL9 LocalMat = pMat[nCnt].MatD3D;

			// 色変更フラグがオンのとき
			if (m_bColorChangeFlag)
			{
				// マテリアルカラー
				D3DXCOLOR MatCol = LocalMat.Diffuse;
				// 加算する色を代入
				MatCol += m_AddColor;
				// ローカルマテリアルの色変更
				LocalMat.Diffuse = MatCol;
			}
			pDevice->SetTexture(0, m_vModel[nCntID]->m_pTexture[nCnt]);
			// マテリアルの設定
			pDevice->SetMaterial(&LocalMat);
			// 描画
			m_vModel[nCntID]->pMesh->DrawSubset(nCnt);
		}
	}
	pDevice->SetRenderState(D3DRS_SPECULARENABLE, FALSE);						// すぺきゅらモード無効
}

