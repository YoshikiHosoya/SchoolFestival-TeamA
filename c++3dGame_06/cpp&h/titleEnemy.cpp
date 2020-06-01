// ----------------------------------------
//
// タイトル用敵処理 [titleenemy.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------
#include "titleEnemy.h"
// ----------------------------------------
//
// マクロ定義
//
// ----------------------------------------
#define ENEMY_KEYMOVE			(2)			// キー移動
#define ENEMY_RESISTANCE (0.9f)				// 抵抗力
#define ENEMY_COLLISIONSIZE_X	(50.0f)		// 当たり判定の大きさ
#define ENEMY_COLLISIONSIZE_Y	(50.0f)		// 当たり判定の大きさ
#define ENEMY_COLLISIONSIZE_Z	(50.0f)		// 当たり判定の大きさ
#define ENEMY_REST_X (1300.0f)				// xの範囲
#define ENEMY_REST_Z (200.0f)				// zの範囲
// ----------------------------------------
//
// 静的変数宣言
//
// ----------------------------------------
CLoad			*CTitleEnemy::m_pload = NULL;			// ロード
CModel_info		*CTitleEnemy::m_pModel_info = NULL;		// モデル情報
MODEL_OFFSET	*CTitleEnemy::m_pModel_offset = NULL;	// モデルの初期配置
MOTION			*CTitleEnemy::m_pMotion = NULL;			// モーション情報の保存
// ----------------------------------------
// コンストラクタ処理
// ----------------------------------------
CTitleEnemy::CTitleEnemy() : CScene::CScene(ACTOR_ENEMY, LAYER_3DOBJECT)
{
	m_pos = D3DXVECTOR3(0.0f, 120.0f, -1600.0f);	// 位置
	//m_pos = D3DXVECTOR3(1200.0f, 0.0f, -300.0f);	// 位置
	//m_pos = D3DXVECTOR3(1200.0f, 0.0f, 2100.0f);	// 位置
	m_posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 前の位置
	//m_move = D3DXVECTOR3(0.0f, 0.0f, -5.0f);		// 移動量
	m_rot = D3DXVECTOR3(0.0f, 3.14f, 0.0f);		// 現在回転量
	//m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 現在回転量

	m_rotLast = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向きたい方向
	m_rotbetween = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転の差分
	m_size = D3DXVECTOR3(							// モデルのサイズ
		ENEMY_COLLISIONSIZE_X,
		ENEMY_COLLISIONSIZE_Y,
		ENEMY_COLLISIONSIZE_Z);

	m_pCollision = NULL;
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CTitleEnemy::~CTitleEnemy()
{
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void CTitleEnemy::Init(void)
{
	// モデルの設定
	for (int nCntModel = 0; nCntModel < TITLE_ENEMYTYPE_MAX; nCntModel++)
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
void CTitleEnemy::Uninit(void)
{
	// モデル
	for (int nCntModel = 0; nCntModel < TITLE_ENEMYTYPE_MAX; nCntModel++)
	{
		// ヌルチェック
		if (m_pModel[nCntModel] != NULL)
		{
			delete m_pModel[nCntModel];
			m_pModel[nCntModel] = NULL;
		}

		//m_pModel[nCntModel]->Uninit();
	}
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void CTitleEnemy::Update(void)
{
	//m_nMotiontype = 2;
	//m_pos += m_move;
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
	for (int nCntModel = 0; nCntModel < TITLE_ENEMYTYPE_MAX; nCntModel++)
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
// 描画処理
// ----------------------------------------
void CTitleEnemy::Draw(void)
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
	for (int nCntModel = 0; nCntModel < TITLE_ENEMYTYPE_MAX; nCntModel++)
	{
		// ヌルチェック
		if (m_pModel[nCntModel] != NULL)
		{
			m_pModel[nCntModel]->Draw(m_mtxWorld);
		}
	}
}

// ----------------------------------------
// 位置取得処理
// ----------------------------------------
D3DXVECTOR3 CTitleEnemy::GetPos(void)
{
	return m_pos;
}

// ----------------------------------------
// 回転取得処理
// ----------------------------------------
D3DXVECTOR3 CTitleEnemy::GetRot(void)
{
	return m_rot;
}

// ----------------------------------------
// 生成処理
// ----------------------------------------
CTitleEnemy * CTitleEnemy::Create()
{
	// 変数宣言
	CTitleEnemy * pTitleEnemy;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pTitleEnemy = new CTitleEnemy();
	// 初期化処理
	pTitleEnemy->Init();

	// 生成したオブジェクトを返す
	return pTitleEnemy;
}

// ----------------------------------------
// 読み込み処理
// ----------------------------------------
void CTitleEnemy::Load(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();

	// モデル情報の生成
	m_pModel_info = new CModel_info[TITLE_ENEMYTYPE_MAX];
	// モデルのオフセットの生成
	m_pModel_offset = new MODEL_OFFSET[TITLE_ENEMYTYPE_MAX];
	// モーションの生成
	m_pMotion = new MOTION[MOTIONTYPE_TITLE_ENEMY_MAX];
	// テクスチャー情報代入
	char ModelData[TITLE_ENEMYTYPE_MAX][512] =
	{
		"data/MODEL/enemy/Body.x",			// [体]		00
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
		TITLE_ENEMYTYPE_MAX,						// キー
		"data/MOTION/motion_enemy.txt"		// ファイル名
	);
	// モデルの保存
	for (int nCntModelLoad = 0; nCntModelLoad < TITLE_ENEMYTYPE_MAX; nCntModelLoad++)
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
void CTitleEnemy::UnLoad(void)
{
	// モデルの描画情報破棄
	for (int nCntModelLoad = 0; nCntModelLoad < TITLE_ENEMYTYPE_MAX; nCntModelLoad++)
	{
		// モデル情報の開放
		m_pModel_info[nCntModelLoad].Unload();
	}
	// モーションの破棄
	//CMotion::UnLoad(
	//	m_pMotion,					// モーション
	//	MOTIONTYPE_TITLE_ENEMY_MAX
	//);
	// モデル情報の破棄
	delete[] m_pModel_info;
	// モデルのオフセットの破棄
	delete[] m_pModel_offset;
}

// ----------------------------------------
// オブジェクトの削除
// ----------------------------------------
void CTitleEnemy::ReleaseTEne(void)
{
	Release();
}

// ----------------------------------------
// タイトル用 モーションの切り替え
// ----------------------------------------
void CTitleEnemy::SetMotion(void)
{
	m_nMotiontype = MOTIONTYPE_TITLE_ENEMY_RUN;
}
