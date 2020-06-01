// ----------------------------------------
//
// モデル処理 [enemy.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------
#include "enemy.h"
#include "scene_X.h"
#include "input.h"
#include "debugproc.h"
#include "game.h"
#include "floartile.h"
#include "player.h"
// ----------------------------------------
//
// マクロ定義
//
// ----------------------------------------
#define ENEMY_MOVE				(0.4f)		// キー移動
#define ENEMY_RESISTANCE		(0.9f)		// 抵抗力
#define ENEMY_COLLISIONSIZE_X	(50.0f)		// 当たり判定の大きさ
#define ENEMY_COLLISIONSIZE_Y	(50.0f)		// 当たり判定の大きさ
#define ENEMY_COLLISIONSIZE_Z	(50.0f)		// 当たり判定の大きさ
#define ENEMY_REST_X			(200.0f)	// xの範囲
#define ENEMY_REST_Z			(200.0f)	// zの範囲
#define ENEMY_ROT				(3.14f)		// 回転初期値

// ----------------------------------------
//
// 静的変数宣言
//
// ----------------------------------------
CLoad			*CEnemy::m_pload = NULL;			// ロード
CModel_info		*CEnemy::m_pModel_info = NULL;		// モデル情報
MODEL_OFFSET	*CEnemy::m_pModel_offset = NULL;	// モデルの初期配置
MOTION			*CEnemy::m_pMotion = NULL;			// モーション情報の保存
bool			 CEnemy::m_bCaught = false;			//
bool			 CEnemy::m_bFreeze = false;
// ----------------------------------------
// コンストラクタ処理
// ----------------------------------------
CEnemy::CEnemy() : CScene::CScene(ACTOR_ENEMY, LAYER_3DOBJECT)
{
	m_pos = D3DXVECTOR3(900.0f, 0.0f, -3900.0f);		// 位置
	m_posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 前の位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 移動量
	m_rot = D3DXVECTOR3(0.0f, ENEMY_ROT, 0.0f);			// 現在回転量
	m_rotLast = D3DXVECTOR3(0.0f, ENEMY_ROT, 0.0f);		// 向きたい方向
	m_rotbetween = D3DXVECTOR3(0.0f, ENEMY_ROT, 0.0f);	// 回転の差分

	m_size = D3DXVECTOR3(							// モデルのサイズ
		ENEMY_COLLISIONSIZE_X,
		ENEMY_COLLISIONSIZE_Y,
		ENEMY_COLLISIONSIZE_Z);

	m_bStopMove = false;
	m_bJudg = false;
	m_bProcessing = false;
	m_pFloarTile = NULL;
	m_bUse = false;
	m_nResult = 0;
	m_nCount = 0;
	m_nMotiontype = 2;

	m_bForward = false;
	m_bBackward = false;
	m_bLeft = false;
	m_bRight = false;
	//srand((unsigned int)time(NULL));//乱数生成
	m_RotState = ROT_FORWARD;
	m_RotCurrentB = ROT_BACKWARD;
	m_RotPossible = ROT_FORWARD;
	m_nDirectionCnt = 0;
	m_bStopFlag = false;
	m_FreezeCnt = 0;
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CEnemy::~CEnemy()
{
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void CEnemy::Init(void)
{
	// モデルの設定
	for (int nCntModel = 0; nCntModel < ENEMYTYPE_MAX; nCntModel++)
	{
		// モデル生成
		m_pModel[nCntModel] = CModel::Create();
		// モデル情報渡し
		m_pModel[nCntModel]->BindModel(
			m_pModel_info[nCntModel].GetModel_info(),
			m_pModel_offset[nCntModel]
		);
		// すべての親以外
		if (nCntModel != 0)
		{
			// 親情報設定
			m_pModel[nCntModel]->SetParent(m_pModel[m_pModel[nCntModel]->GetModelInfo()->nParent]);
		}
	}
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void CEnemy::Uninit(void)
{
	// モデル
	for (int nCntModel = 0; nCntModel < ENEMYTYPE_MAX; nCntModel++)
	{
		// ヌルチェック
		if (m_pModel[nCntModel] != NULL)
		{
			delete m_pModel[nCntModel];
			m_pModel[nCntModel] = NULL;
		}

		//m_pModel[nCntModel]->Uninit();
	}

	m_bCaught = false;
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void CEnemy::Update(void)
{
	//if (m_bFreeze == false)
	//{
	//	// 移動
	//	Move();
	//	// モーション
	//	Motion();
	//}
	//else
	//{
	//	m_FreezeCnt++;
	//	if (m_FreezeCnt >= ONEMIN * 5)
	//	{
	//		m_bFreeze = false;
	//	}
	//}

	//// 回転慣性
	//RotInertia();

	//CDebugproc::Print("敵ステータス情報\n");
	CDebugproc::Print("敵 座標		: %.2f,%.2f,%.2f\n", m_pos.x, m_pos.y,m_pos.z);
	CDebugproc::Print("敵 回転状態		: %d \n", m_RotState);
}

// ----------------------------------------
// 移動処理
// ----------------------------------------
void CEnemy::Move(void)
{
	if (m_bStopFlag == false)
	{
		// エネミーの回転量を含めた移動量の計算
		m_move.x += sinf(D3DX_PI + m_rot.y) * ENEMY_MOVE;
		m_move.z += cosf(D3DX_PI + m_rot.y) * ENEMY_MOVE;

		// 移動量を座標に加算
		m_pos += m_move;

		// 抵抗力
		m_move.x *= 0.9f;
		m_move.z *= 0.9f;
	}
}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void CEnemy::Draw(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX			mtxRot, mtxTrans;	// 計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y,
		m_rot.x,
		m_rot.z);

	// 行列の積(1:ワールド行列 = 2:ワールド行列 * 3:回転行列)
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld, &mtxRot);

	// 位置を反映 //
	// 平行移動行列作成(オフセット)
	D3DXMatrixTranslation(&mtxTrans,	// 総合の入れ物
		m_pos.x,
		m_pos.y,
		m_pos.z);

	// 行列の積(1:ワールド行列 = 2:ワールド行列 * 3:移動行列)
	D3DXMatrixMultiply(&m_mtxWorld,	// 1
		&m_mtxWorld,				// 2
		&mtxTrans);					// 3

	// モデル
	for (int nCntModel = 0; nCntModel < ENEMYTYPE_MAX; nCntModel++)
	{
		// ヌルチェック
		if (m_pModel[nCntModel] != NULL)
		{
			m_pModel[nCntModel]->Draw(m_mtxWorld);
		}
	}
}

// ----------------------------------------
// 回転更新処理
// ----------------------------------------
void CEnemy::SetRot(D3DXVECTOR3 rot, ROT rotstate)
{
	m_rotLast = rot;
	m_RotState = rotstate;
}

void CEnemy::StopMove(void)
{
	m_bStopFlag = true;
}

// ----------------------------------------
// 位置取得処理
// ----------------------------------------
D3DXVECTOR3 CEnemy::GetPos(void)
{
	return m_pos;
}

// ----------------------------------------
// 回転取得処理
// ----------------------------------------
D3DXVECTOR3 CEnemy::GetRot(void)
{
	return m_rot;
}

// ----------------------------------------
// 回転状態取得処理
// ----------------------------------------
CEnemy::ROT CEnemy::GetEnemyROT(void)
{
	return m_RotState;
}

// ----------------------------------------
// 生成処理
// ----------------------------------------
CEnemy * CEnemy::Create()
{
	// 変数宣言
	CEnemy * pEnemy;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pEnemy = new CEnemy();
	// 初期化処理
	pEnemy->Init();
	// 生成したオブジェクトを返す
	return pEnemy;
}

// ----------------------------------------
// 読み込み処理
// ----------------------------------------
void CEnemy::Load(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();
	// モデル情報の生成
	m_pModel_info = new CModel_info[ENEMYTYPE_MAX];
	// モデルのオフセットの生成
	m_pModel_offset = new MODEL_OFFSET[ENEMYTYPE_MAX];
	// モーションの生成
	m_pMotion = new MOTION[MOTIONTYPE_ENEMY_MAX];
	// テクスチャー情報代入
	char ModelData[ENEMYTYPE_MAX][512] =
	{
		"data/MODEL/enemy/Body.x",			// [体]			00
		"data/MODEL/enemy/Head.x",			// [頭]			01
		"data/MODEL/enemy/Arm_L.x",			// [左腕]		02
		"data/MODEL/enemy/Arm_R.x",			// [右腕]		03
		"data/MODEL/enemy/Leg_L.x",			// [左足]		04
		"data/MODEL/enemy/Leg_R.x",			// [右足]		05
	};

	// モデルのオフセット設定
	CModel_info::ModelOffset(
		m_pModel_offset,					// モデルのオフセット
		"data/MOTION/motion_enemy.txt"		// ファイル名
	);
	// モーションの設定
	CMotion::Load(
		m_pMotion,							// モーション
		m_pModel_offset,					// オフセット
		ENEMYTYPE_MAX,						// キー
		"data/MOTION/motion_enemy.txt"		// ファイル名
	);
	// モデルの保存
	for (int nCntModelLoad = 0; nCntModelLoad < ENEMYTYPE_MAX; nCntModelLoad++)
	{
		// モデル情報を読み込み
		m_pModel_info[nCntModelLoad].Load(
			pDevice,
			ModelData[nCntModelLoad]);
	}
}

// ----------------------------------------
// 読み込んだ情報を破棄処理
// ----------------------------------------
void CEnemy::UnLoad(void)
{
	// モデルの描画情報破棄
	for (int nCntModelLoad = 0; nCntModelLoad < ENEMYTYPE_MAX; nCntModelLoad++)
	{
		// モデル情報の開放
		m_pModel_info[nCntModelLoad].Unload();
	}
	// モーションの破棄
	CMotion::UnLoad(
		m_pMotion,
		MOTIONTYPE_ENEMY_MAX
	);
	// モデル情報の破棄
	delete[] m_pModel_info;
	// モデルのオフセットの破棄
	delete[] m_pModel_offset;
}

// ----------------------------------------
// レベルの設定
// ----------------------------------------
void CEnemy::AddLevel(void)
{
}

// ----------------------------------------
// 床との判定
// ----------------------------------------
void CEnemy::EnemyColi()
{
	//CPlayer *pPlayer = NULL;	// プレイヤー

	//for (int nCntlayer = 0; nCntlayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntlayer++)
	//{
	//	if (pPlayer = (CPlayer *)CScene::GetActor(CScene::ACTOR_PLAYER, CScene::LAYER_3DOBJECT, nCntlayer)) break;
	//}

	////
	//if (CCalculation::Collision_Circle(
	//	D3DXVECTOR3(GetPos().x, GetPos().y + 250, GetPos().z),
	//	// 自分の位置
	//	150.0f, 		// 自分の半径
	//	D3DXVECTOR3(pPlayer->GetPos().x, pPlayer->GetPos().y, pPlayer->GetPos().z), 			// 相手の位置
	//	100.0f))		// 相手の半径
	//{
	//	SetEndFlag();
	//}
}

// ----------------------------------------
// AI処理
// ----------------------------------------
void CEnemy::EnemyAI(void)
{
}

// ----------------------------------------
// 進行方向を決定
// ----------------------------------------
void CEnemy::Direction(void)
{
}

// ----------------------------------------
// 後方を求める
// ----------------------------------------
void CEnemy::SeekBackwards(void)
{
}

// ----------------------------------------
// 回転
// ----------------------------------------
void CEnemy::Rot(ROT rot)
{
}

// ----------------------------------------
// モーション
// ----------------------------------------
void CEnemy::Motion()
{
	// フレームカウントアップ
	m_nFrame++;
	// モーションタイプが変化
	// 初期化
	if (m_nMotiontype != m_nMotiontypeOld)
	{
		m_nFrame = 0;		// フレームキー情報のカウント
		m_keyinfoCnt = 0;	// キー情報のカウント
	}
	// モーションの保存
	m_nMotiontypeOld = m_nMotiontype;
	// フレーム数が同じになったら
	if (m_nFrame == m_pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].nFrame)
	{
		// 初期化
		m_nFrame = 0;	// フレーム
						// カウントアップ
		m_keyinfoCnt++;
		// キー情報が超えたら
		if (m_keyinfoCnt >= m_pMotion[m_nMotiontype].nNumKey)
		{
			// ループしないとき
			if (m_pMotion[m_nMotiontype].nLoop == 0)
			{
				// 初期化
				m_keyinfoCnt = 0;				// キー情報
				m_nMotiontype = 0;	// モーションタイプ
			}

			// ループする時
			else
			{
				// 初期化
				m_keyinfoCnt = 0;				// キー情報
			}
		}
	}
	// モデル
	for (int nCntModel = 0; nCntModel < ENEMYTYPE_MAX; nCntModel++)
	{
		// ヌルチェック
		if (m_pModel[nCntModel] != NULL)
		{
			m_pModel[nCntModel]->SetMotion(m_pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].Key[nCntModel], m_pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].nFrame);
			m_pModel[nCntModel]->Update();
		}
	}
}

// ----------------------------------------
// 回転の慣性
// ----------------------------------------
void CEnemy::RotInertia(void)
{
	// 現在回転差分
	m_rotbetween.y = m_rotLast.y - m_rot.y;

	// 限度調整
	m_rotbetween.y = CCalculation::Rot_One_Limit(m_rotbetween.y);

	// 回転移動
	m_rot.y += m_rotbetween.y * 0.1f;

	// 限度調整
	m_rot.y = CCalculation::Rot_One_Limit(m_rot.y);
}

// ----------------------------------------
// プレイヤーを捕まえた時フラグをtrue
// ----------------------------------------
void CEnemy::SetEndFlag(void)
{
	m_bCaught = true;
}

// ----------------------------------------
// フラグの取得
// ----------------------------------------
bool CEnemy::GetEndFlag(void)
{
	return m_bCaught;
}

// ----------------------------------------
// フラグをセットする
// ----------------------------------------
void CEnemy::SetFreezeFlag(void)
{
	m_bFreeze = true;
}
