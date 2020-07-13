// =====================================================================================================================================================================
//
//乗り物の処理 [vehicle.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "vehicle.h"
#include "model.h"
#include "collision.h"
#include "game.h"
#include "map.h"
#include "manager.h"
#include "debugproc.h"
#include "inputKeyboard.h"
#include "Xinput.h"
#include "hosso\/Debug_ModelViewer.h"
#include "playertank.h"


//====================================================================
// モデルのオフセット読み込みファイルの設定
//====================================================================
char *CVehicle::m_LoadOffsetFileName[VEHICLE_TYPE_MAX] =
{
	{ "data/Load/PlayerTank/PlayerTankOffset.txt" },
};

//====================================================================
//マクロ定義
//====================================================================
#define VEHICLE_GRAVITY (0.5f)

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CVehicle::CVehicle(OBJ_TYPE type) :CScene(type)
{
	// 当たり判定のポインタをnullにする
	m_pCollision = nullptr;
}
// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CVehicle::~CVehicle()
{
	// 当たり判定の削除
	if (m_pCollision != nullptr)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}
}
// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CVehicle::Init(void)
{
	// 座標の初期化
	m_pos			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// 1フレーム前の座標の初期化
	m_posOld		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// 移動量の初期化
	m_move			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// 回転の初期化
	m_rot			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// 加算する回転量の初期化
	m_AddRot		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// 体力の初期化
	m_nLife			= 100;
	// 状態の初期化
	m_state			= VEHICLE_STATE_NORMAL;
	// 回転量の初期化
	m_rotDest.y		= -0.5f*  D3DX_PI;
	// 重力フラグの初期化
	m_bGravity		= true;
	// 死亡フラグの初期化
	m_bDieFlag		= false;
	// 弾の回転の初期化
	m_ShotRot		= D3DXVECTOR3(0.0f, 0.5f, 0.0f);
	// 当たり判定生成
	m_pCollision	= CCollision::Create();
	// マトリックス初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	// 乗り物の行動状態を初期化
	m_Behaviorstate = VEHICLE_BEHAVIOR_NORMAL;
	// 種類を初期化
	m_VehicleType = VEHICLE_TYPE_TANK;
	// 無敵状態から通常状態に戻るまでのカウント
	m_nStateCnt = 0;
	// 向き
	m_VehicleDirection = VEHICLE_RIGHT;
	// ジャンプしているかのフラグを初期化
	m_bJump = false;

	return S_OK;
}
//====================================================================
//
//終了
//
//====================================================================
void CVehicle::Uninit(void)
{
}
//====================================================================
//
//更新
//
//====================================================================
void CVehicle::Update(void)
{
	// 慣性処理
	Inertia();

	// 重力処理
	Gravity();

	// 回転量計算処理
	Rot();

	// 状態別処理
	State();

	// 弾を撃つ方向の計算
	ShotDirection();

	// 座標の更新
	m_pos += m_move;

	// 体力が0以下になった時
	if (this->m_nLife <= 0)
	{
		// 状態を破壊に変更
		m_state = VEHICLE_STATE_BREAK;
	}
}
//====================================================================
//
//描画
//
//====================================================================
void CVehicle::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y,
		m_rot.x,
		m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x,
		m_pos.y,
		m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxTrans);

	// 特定のパーツだけを回転させる
	for (unsigned int nCnt = 0; nCnt < m_vModelList.size(); nCnt++)
	{
		// 描画処理
		m_vModelList[nCnt]->Draw(m_mtxWorld);
	}
}
//====================================================================
//デバッグ
//====================================================================
void CVehicle::DebugInfo(void)
{
	CDebug_ModelViewer::OffsetViewer(m_vModelList);


	//CDebugProc::Print("");
}

//====================================================================
// パーツの回転条件別処理
//====================================================================
void CVehicle::VehiclePartsRotCondition(CModel *pModel, PARTS_ROT_TYPE type)
{
	switch (type)
	{
		// 動かさない
	case MODEL_ROT_TYPE_NONE:
		break;

		// 常に回転する
	case MODEL_ROT_TYPE_ALWAYS:
		// 条件ごと回転させる
		this->VehiclePartsRot(pModel, 0.1f);
		break;

		// 移動している時のみ
	case MODEL_ROT_TYPE_MOVING:
		// 車輪の回転処理
		WheelRot(pModel);
		break;

		// 操作している時のみ
	case MODEL_ROT_TYPE_OPERATION:
		// 銃の回転処理
		GunRot(pModel);
		break;

	default:
		break;
	}
}

//====================================================================
// パーツの回転条件別処理
//====================================================================
void CVehicle::VehiclePartsRot(CModel *pModel, float fRot)
{
	//3.14の超過分の初期化（回転）
	CHossoLibrary::CalcRotation(fRot);
	// モデルの回転
	pModel->GetRot().x += fRot;
	// モデルの回転の更新設定
	pModel->SetRot(pModel->GetRot());
}

//====================================================================
// パーツの回転条件別処理 上限付き
//====================================================================
void CVehicle::VehiclePartsRotLimit(CModel * pModel, float fRot)
{
	//3.14の超過分の回転量の初期化
	CHossoLibrary::CalcRotation(pModel->GetRot().x);
	// --- 指定された角度になるまで回転する --- //

	// 目標回転量と現在の回転量の差分を求める
	float diffRot = fRot - pModel->GetRot().x;

	//3.14の超過分の初期化（回転）
	if (pModel->GetRot().x > D3DX_PI)
	{
		pModel->GetRot().x -= D3DX_PI * 2;
	}
	else if (pModel->GetRot().x < -D3DX_PI)
	{
		pModel->GetRot().x += D3DX_PI * 2;
	}
	if (diffRot > D3DX_PI)
	{
		diffRot -= D3DX_PI * 2;
	}
	else if (diffRot < -D3DX_PI)
	{
		diffRot += D3DX_PI * 2;
	}

	//求めた差分だけ回転する計算
	pModel->GetRot().x += diffRot * 0.1f;

	// モデルの回転の更新設定
	pModel->SetRot(pModel->GetRot());
}

//====================================================================
// 慣性処理
//====================================================================
void CVehicle::Inertia()
{
	m_move.x += (0 - m_move.x)* 0.2f;
	m_move.z += (0 - m_move.z)* 0.2f;
	m_move.y += m_move.y * -0.1f;
}

//====================================================================
// 重力処理
//====================================================================
void CVehicle::Gravity()
{
	// 重力フラグがtrueだった時
	if (m_bGravity == true)
	{
		// 重力
		m_move.y -= VEHICLE_GRAVITY;
	}
}

//====================================================================
// 回転量計算処理
//====================================================================
void CVehicle::Rot()
{
	//目標点と現在の差分（回転）
	float diffRot = m_rotDest.y - m_rot.y;
	//3.14の超過分の初期化（回転）
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}
	if (diffRot > D3DX_PI)
	{
		diffRot -= D3DX_PI * 2;
	}
	else if (diffRot < -D3DX_PI)
	{
		diffRot += D3DX_PI * 2;
	}
	//求めた差分だけ追従する計算
	m_rot.y += diffRot * 0.1f;
}

//====================================================================
// 乗り物の状態別処理
//====================================================================
void CVehicle::State()
{
	//ステータスの処理
	switch (m_state)
	{
		// 通常状態
	case VEHICLE_STATE_NORMAL:
		break;

		// ダメージを受けた時
	case VEHICLE_STATE_DAMAGE:
		m_state = VEHICLE_STATE_NORMAL;
		break;

		// 無敵時間
	case VEHICLE_STATE_INVINCIBLE:
		m_nStateCnt++;
		if (m_nStateCnt % 30 == 0)
		{
			m_state = VEHICLE_STATE_NORMAL;
		}
		break;

	case VEHICLE_STATE_BREAK:
		// 破壊時のエフェクト

		// 削除
		Rerease();
		break;
	}
}

//====================================================================
// 弾を撃つ方向の計算
//====================================================================
void CVehicle::ShotDirection()
{
	switch (m_VehicleDirection)
	{
	case VEHICLE_LEFT:
		m_ShotRot.x = 0.0f;
		m_ShotRot.y = 0.5f * D3DX_PI;
		m_AddRot.x = 0.0f;
		break;

	case VEHICLE_RIGHT:
		m_ShotRot.x = 0.0f;
		m_ShotRot.y = -0.5f * D3DX_PI;
		m_AddRot.x = 0.0f;
		break;
	case VEHICLE_UP:
		m_ShotRot.x = 0.5f * D3DX_PI;
		m_ShotRot.y = 0.0f;
		m_AddRot.x = 0.75f;
		break;
	case VEHICLE_DOWN:
		m_ShotRot.x = -0.5f * D3DX_PI;
		m_ShotRot.y = 0.5f * D3DX_PI;
		m_AddRot.x = -0.75f;
		break;

	default:
		break;
	}
}

//====================================================================
// 車輪の回転車輪
//====================================================================
void CVehicle::WheelRot(CModel *pModel)
{
	// 左回転
	if (this->GetMove().x <= -2)
	{
		// 条件ごと回転させる
		this->VehiclePartsRot(pModel, 0.1f);
	}
	// 右回転
	else if (this->GetMove().x >= 2)
	{
		// 条件ごと回転させる
		this->VehiclePartsRot(pModel, -0.1f);
	}
	// 無回転
	else if (this->GetMove().x <= 1.0f && this->GetMove().x >= -1.0f)
	{
		// 条件ごと回転させる
		this->VehiclePartsRot(pModel, 0.0f);
	}
}

//====================================================================
// 銃の回転車輪
//====================================================================
void CVehicle::GunRot(CModel * pModel)
{
	// 戦車の総数分
	for (int nCntVehicle = 0; nCntVehicle < CManager::GetBaseMode()->GetMap()->GetMaxPlayerTank(); nCntVehicle++)
	{
		// 乗り物のポインタ取得
		CPlayertank *pPlayertank = CManager::GetBaseMode()->GetMap()->GetPlayertank(nCntVehicle);
		// 戦車が存在した時
		if (pPlayertank != nullptr)
		{
			if (pPlayertank->GetVehicleDirection() == VEHICLE_LEFT)
			{
				// 条件ごと回転させる
				this->VehiclePartsRotLimit(pModel, D3DX_PI * 0.5f);
			}
			else if (pPlayertank->GetVehicleDirection() == VEHICLE_RIGHT)
			{
				// 条件ごと回転させる
				this->VehiclePartsRotLimit(pModel, -D3DX_PI * 0.5f);
			}
			else if (pPlayertank->GetVehicleDirection() == VEHICLE_UP)
			{
				// 条件ごと回転させる
				this->VehiclePartsRotLimit(pModel, D3DX_PI * 0.0f);
			}
			else if (pPlayertank->GetVehicleDirection() == VEHICLE_DOWN)
			{
				// 条件ごと回転させる
				this->VehiclePartsRotLimit(pModel, D3DX_PI * 1.0f);
			}
		}
	}
}

//====================================================================
//移動
//====================================================================
void CVehicle::Move(float move, float fdest)
{
	GetMove().x += sinf(move * -D3DX_PI) * 1.0f;
	GetMove().z += cosf(move * -D3DX_PI) * 1.0f;
	GetRotDest().y = fdest *  D3DX_PI;
}

//====================================================================
//ダメージを受けた時の処理
//====================================================================
void CVehicle::AddDamage(int Damage)
{
	// 乗り物の状態を変更
	m_state = VEHICLE_STATE_DAMAGE;
	// 体力からダメージ量分を減算
	this->m_nLife -= Damage;
	// 結果を更新
	SetLife(m_nLife);
}

//====================================================================
//オフセットの読み込み
//====================================================================
void CVehicle::LoadOffset(VEHICLE_TYPE nType)
{
	char cReadText[1080];	//文字として読み取り用
	char cHeadText[1080];	//比較する用
	char cDie[1080];		//不要な文字
	int nCnt = 0;
	FILE *pFile;

	D3DXVECTOR3 pos;
	int nIdxParent;			//親のインデックス
	int nIdx;				//モデルのインデックス
	int type;

	pFile = fopen(m_LoadOffsetFileName[nType], "r");
	if (pFile != NULL)
	{
		while (strcmp(cHeadText, "MODEL_OFFSET_END") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile);
			sscanf(cReadText, "%s", &cHeadText);
			//配置するモデルの最大数の読み込み
			if (strcmp(cHeadText, "SET_START") == 0)
			{
				//END_SETが来るまでループ
				while (strcmp(cHeadText, "SET_END") != 0)
				{
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s", &cHeadText);
					//MODEL_TYPEだったら
					if (strcmp(cHeadText, "MODEL_TYPE") == 0)
					{
						sscanf(cReadText, "%s %s %d",
							&cDie, &cDie,
							&type);
					}
					//IDXだったら
					else if (strcmp(cHeadText, "INDEX") == 0)
					{
						sscanf(cReadText, "%s %s %d",
							&cDie, &cDie,
							&nIdx);
					}
					//PARENTだったら
					else if (strcmp(cHeadText, "PARENT") == 0)
					{
						sscanf(cReadText, "%s %s %d",
							&cDie, &cDie,
							&nIdxParent);
					}
					//POSだったら
					else if (strcmp(cHeadText, "POS") == 0)
					{
						sscanf(cReadText, "%s %s %f %f %f",
							&cDie, &cDie,
							&pos.x,
							&pos.y,
							&pos.z);
					}
					//SET_ENDが来たら作成し追加
					else if (strcmp(cHeadText, "SET_END") == 0)
					{
						CModel *pModel = CModel::Create(type, nIdx);
						pModel->SetPosition(pos);
						pModel->SetParentIdx(nIdxParent);
						if (nIdxParent == -1)
						{
							pModel->SetParent(NULL);
						}
						else
						{
							pModel->SetParent(m_vModelList[nIdxParent]);
						}
						m_vModelList.emplace_back(pModel);
					}
				}
			}
		}

		fclose(pFile);
	}
	else
	{

	}

}
