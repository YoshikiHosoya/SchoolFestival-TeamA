// ----------------------------------------
//
// プレイヤー処理 [player.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------
#include "player.h"
#include "enemy.h"
#include "floor.h"
#include "input.h"
#include "debugproc.h"
#include "camera.h"
#include "3Dparticle.h"
#include "gauge.h"
#include "game.h"
#include "item.h"
#include "score.h"
#include "manager.h"
#include "fade.h"
#include "title.h"
#include "mapmark.h"
#include "gameui.h"
// ----------------------------------------
//
// マクロ定義
//
// ----------------------------------------
#define PLAYER_KEYMOVE			(1.3f)					// キー移動
#define PLAYER_COLLISIONSIZE	(50.0f)					// 当たり判定の大きさ
#define PLAYER_RESISTANCE (0.9f)						// 抵抗力
#define PLAYER_REST_X (1300.0f)							// xの範囲
#define PLAYER_REST_Z (200.0f)							// zの範囲

// ----------------------------------------
//
// 静的変数宣言
//
// ----------------------------------------
CModel_info		*CPlayer::m_pModel_info = NULL;		// モデル情報
MODEL_OFFSET	*CPlayer::m_pModel_offset = NULL;	// モデルの初期配置
MOTION			*CPlayer::m_pMotion = NULL;			// モーション情報の保存

// ----------------------------------------
// コンストラクタ処理
// ----------------------------------------
CPlayer::CPlayer() : CScene::CScene(ACTOR_PLAYER, LAYER_3DOBJECT)
{
	if (CManager::GetMode() == CManager::MODE_TITLE)
	{
		m_pos = D3DXVECTOR3(0.0f, 320.0f, 2300.0f);				// 位置
		m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 現在回転量
	}
	else if (CManager::GetMode() == CManager::MODE_GAME)
	{
		m_pos = D3DXVECTOR3(0.0f, 220.0f, 0.0f);				// 位置
		m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 現在回転量
	}

	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		CManager::GetRenderer()->GetCamera()->SetRot(D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	}

	m_posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 前の位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 移動量
	m_rotLast = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 向きたい方向
	m_rotbetween = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転の差分
	m_size = D3DXVECTOR3(										// モデルのサイズ
		PLAYER_COLLISIONSIZE,
		PLAYER_COLLISIONSIZE,
		PLAYER_COLLISIONSIZE);

	m_pCollision = NULL;										// 当たり判定
	m_bRun = false;												// 走る
	m_nAbilityPoint = 0;										// アビリティのポイント
	m_nCoolTime = 0;											// アビリティのクールタイム
	m_bAbilityFlag = false;										// アビリティを使っているかどうか
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CPlayer::~CPlayer()
{
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void CPlayer::Init(void)
{
	// モデルの設定
	for (int nCntModel = 0; nCntModel < PLAYERTYPE_MAX; nCntModel++)
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

	// 当たり判定生成
	m_pCollision = CCollision::Create();
	m_pCollision->SetPos(&m_pos);
	m_pCollision->SetSize(m_size);
	m_pCollision->SetMove(&m_move);
	m_pCollision->SetType(CCollision::OBJTYPE_PLAYER);
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void CPlayer::Uninit(void)
{
	// モデル
	for (int nCntModel = 0; nCntModel < PLAYERTYPE_MAX; nCntModel++)
	{
		// ヌルチェック
		if (m_pModel[nCntModel] != NULL)
		{
			delete m_pModel[nCntModel];
			m_pModel[nCntModel] = NULL;
		}
	}
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void CPlayer::Update(void)
{
	// タイトルの状態が行動可能状態かモードがゲームの時、移動可能
	if (CManager::GetTitle()->GetMode() == CManager::GetTitle()->TITLEMODE_FREE || CManager::GetMode() == CManager::MODE_GAME)
	{
		// 移動
		Move();
	}

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
			else
			{// ループする時
				// 初期化
				m_keyinfoCnt = 0;				// キー情報
			}
		}
	}
	// モデル
	for (int nCntModel = 0; nCntModel < PLAYERTYPE_MAX; nCntModel++)
	{
		// ヌルチェック
		if (m_pModel[nCntModel] != NULL)
		{
			m_pModel[nCntModel]->SetMotion(m_pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].Key[nCntModel], m_pMotion[m_nMotiontype].KeyInfo[m_keyinfoCnt].nFrame);
			m_pModel[nCntModel]->Update();
		}
	}

	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		// アビリティ―
		Ability();
	}

	//行動範囲制限
	Restriction();

	//当たり判定の座標更新
	m_pCollision->SetPos(&m_pos);

	CDebugproc::Print("プレイヤーのステータス情報\n");
	CDebugproc::Print("座標		: %.2f,%.2f,%.2f\n", GetPos().x, GetPos().y, GetPos().z);
}

// ----------------------------------------
// 移動処理
// ----------------------------------------
void CPlayer::Move(void)
{
	// 変数宣言
	float fRot;
	CFloor * pFloor = NULL;	// 床

	int nValueH = 0;//スティックの横
	int nValueV = 0;//スティックの縦

	// 情報取得
	for (int nCntLayer = 0; nCntLayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntLayer++)
	{
		if (pFloor == NULL) pFloor = (CFloor*)CScene::GetActor(CScene::ACTOR_FLOOR, CScene::LAYER_3DOBJECT, nCntLayer);	// 床
	}

	fRot = CManager::GetRenderer()->GetCamera()->GetRot().y;	// 回転情報取得

	//ジョイパッドでの処理
	CManager::GetJoy()->GetStickLeft(0, &nValueH, &nValueV);

	if (nValueH != 0 || nValueV != 0)
	{
		// 左に倒している時
		if (nValueH <= -1)
		{
			if (nValueV >= 1)
			{
				m_move.x += sinf(D3DX_PI * 0.75f + fRot) * PLAYER_KEYMOVE;
				m_move.z += cosf(D3DX_PI * 0.75f + fRot) * PLAYER_KEYMOVE;
			}
			else if (nValueV <= -1)
			{
				m_move.x += sinf(D3DX_PI * 0.25f + fRot) * PLAYER_KEYMOVE;
				m_move.z += cosf(D3DX_PI * 0.25f + fRot) * PLAYER_KEYMOVE;
			}
			else
			{
				m_move.x += sinf(D3DX_PI * 0.5f + fRot) * PLAYER_KEYMOVE;
				m_move.z += cosf(D3DX_PI * 0.5f + fRot) * PLAYER_KEYMOVE;
			}
		}

		// 右に倒している時
		else if (nValueH >= 1)
		{
			if (nValueV  >= 1)
			{
				m_move.x += sinf(-D3DX_PI * 0.75f + fRot) * PLAYER_KEYMOVE;
				m_move.z += cosf(-D3DX_PI * 0.75f + fRot) * PLAYER_KEYMOVE;
			}

			else if (nValueV <= -1)
			{
				m_move.x += sinf(-D3DX_PI * 0.25f + fRot) * PLAYER_KEYMOVE;
				m_move.z += cosf(-D3DX_PI * 0.25f + fRot) * PLAYER_KEYMOVE;
			}

			else
			{
				m_move.x += sinf(-D3DX_PI * 0.5f + fRot) * PLAYER_KEYMOVE;
				m_move.z += cosf(-D3DX_PI * 0.5f + fRot) * PLAYER_KEYMOVE;
			}
		}

		else if (nValueV >= 1)
		{
			m_move.x += sinf(D3DX_PI * 1.0f + fRot) * PLAYER_KEYMOVE;
			m_move.z += cosf(D3DX_PI * 1.0f + fRot) * PLAYER_KEYMOVE;
		}
		else if (nValueV <= -1)
		{
			m_move.x += sinf(D3DX_PI * 0.0f + fRot) * PLAYER_KEYMOVE;
			m_move.z += cosf(D3DX_PI * 0.0f + fRot) * PLAYER_KEYMOVE;
		}

		// 走っていたら
		if (m_bRun == false)
		{
			CManager::GetSound()->PlaySound(CSound::LABEL_BGM_RUN);
			CManager::GetSound()->PlaySound(CSound::LABEL_BGM_BREATH);
			m_bRun = true;
		}
	}

	// 走っていなかったら
	else
	{
		CManager::GetSound()->StopSound(CSound::LABEL_BGM_RUN);
		CManager::GetSound()->StopSound(CSound::LABEL_BGM_BREATH);
		m_bRun = false;
	}

	// 移動 //
	// 左
	if (CManager::GetKeyboard()->GetKeyboardPress(DIK_A))
	{
		// 奥
		if (CManager::GetKeyboard()->GetKeyboardPress(DIK_W))
		{
			//m_rotLast.y = -D3DX_PI * 0.25f + fRot;

			m_move.x += sinf(D3DX_PI * 0.75f + fRot) * PLAYER_KEYMOVE;
			m_move.z += cosf(D3DX_PI * 0.75f + fRot) * PLAYER_KEYMOVE;
		}
		// 手前
		else if (CManager::GetKeyboard()->GetKeyboardPress(DIK_S))
		{
			//m_rotLast.y = -D3DX_PI * 0.75f + fRot;

			m_move.x += sinf(D3DX_PI * 0.25f + fRot) * PLAYER_KEYMOVE;
			m_move.z += cosf(D3DX_PI * 0.25f + fRot) * PLAYER_KEYMOVE;
		}
		// 左
		else
		{
			//m_rotLast.y = -D3DX_PI * 0.5f + fRot;

			m_move.x += sinf(D3DX_PI * 0.5f + fRot) * PLAYER_KEYMOVE;
			m_move.z += cosf(D3DX_PI * 0.5f + fRot) * PLAYER_KEYMOVE;
		}
	}
	// 右
	else if (CManager::GetKeyboard()->GetKeyboardPress(DIK_D))
	{
		// 奥
		if (CManager::GetKeyboard()->GetKeyboardPress(DIK_W))
		{
			//m_rotLast.y = D3DX_PI * 0.25f + fRot;

			m_move.x += sinf(-D3DX_PI * 0.75f + fRot) * PLAYER_KEYMOVE;
			m_move.z += cosf(-D3DX_PI * 0.75f + fRot) * PLAYER_KEYMOVE;
		}
		// 手前
		else if (CManager::GetKeyboard()->GetKeyboardPress(DIK_S))
		{
			//m_rotLast.y = D3DX_PI * 0.75f + fRot;

			m_move.x += sinf(-D3DX_PI * 0.25f + fRot) * PLAYER_KEYMOVE;
			m_move.z += cosf(-D3DX_PI * 0.25f + fRot) * PLAYER_KEYMOVE;
		}
		// 右
		else
		{
			//m_rotLast.y = D3DX_PI * 0.5f + fRot;

			m_move.x += sinf(-D3DX_PI * 0.5f + fRot) * PLAYER_KEYMOVE;
			m_move.z += cosf(-D3DX_PI * 0.5f + fRot) * PLAYER_KEYMOVE;
		}
	}
	// 奥に行く
	else if (CManager::GetKeyboard()->GetKeyboardPress(DIK_W))
	{
		//m_rotLast.y = -D3DX_PI * 0.0f + fRot;
		m_move.x += sinf(-D3DX_PI * 1.0f + fRot) * PLAYER_KEYMOVE;
		m_move.z += cosf(-D3DX_PI * 1.0f + fRot) * PLAYER_KEYMOVE;
	}
	// 手前に行く
	else if (CManager::GetKeyboard()->GetKeyboardPress(DIK_S))
	{
		//m_rotLast.y = D3DX_PI * 1.0f + fRot;

		m_move.x += sinf(D3DX_PI * 0.0f + fRot) * PLAYER_KEYMOVE;
		m_move.z += cosf(D3DX_PI * 0.0f + fRot) * PLAYER_KEYMOVE;
	}

	// 現在回転差分
	m_rotbetween.y = m_rotLast.y - m_rot.y;

	// 限度調整
	m_rotbetween.y = CCalculation::Rot_One_Limit(m_rotbetween.y);

	// 回転移動
	m_rot.y += m_rotbetween.y * 0.1f;

	// 限度調整
	m_rot.y = CCalculation::Rot_One_Limit(m_rot.y);

	// 重力
	//m_move.y -= PLAYER_G;	// 移動量
	m_pos += m_move;

	// 抵抗力
	m_move.x *= PLAYER_RESISTANCE;
	m_move.z *= PLAYER_RESISTANCE;

	// 床の高さを代入
	/*if (pFloor != NULL)
	{
		if (m_pos.y < pFloor->GetHeight(m_pos))
		{
			m_pos.y = pFloor->GetHeight(m_pos);
		}
	}*/

	m_pCollision->Collision();
	// 当たり判定に触れたら
	//if (m_pCollision->Collision_Player())
	//{

	//}
	//else
	//{
	//	//どこにも当たっていなかったらフラグをfalseにする
	//	ResetFlag();
	//}

	// 制限区域
	//Restriction();
}

// ----------------------------------------
// 能力処理
// ----------------------------------------
void CPlayer::Ability(void)
{
	// アビリティ―ポイントがたまっていたら
	if (CGame_ui::GetbUse())
	{
		if (m_bAbilityFlag == false)
		{
			// アビリティ―ゲージが溜まっていて尚且つスペースを押したとき
			if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_SPACE))
			{
				// カウントを下げ、敵の更新を決めた秒数止める
				CGame_ui::SetAP(-10);
				CEnemy::SetFreezeFlag();
				CGauge::Create();
				m_nCoolTime = 0;
				m_bAbilityFlag = true;
			}
		}
	}

	// アビリティを使ったら
	if (m_bAbilityFlag == true)
	{
		// クールタイム加算
		m_nCoolTime++;

		if (m_nCoolTime >= (ONEMIN * 10))
		{
			m_bAbilityFlag = false;
		}
	}
}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void CPlayer::Draw(void)
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
	for (int nCntModel = 0; nCntModel < PLAYERTYPE_MAX; nCntModel++)
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
D3DXVECTOR3 CPlayer::GetPos(void)
{
	return m_pos;
}

// ----------------------------------------
// 回転取得処理
// ----------------------------------------
D3DXVECTOR3 CPlayer::GetRot(void)
{
	return m_rot;
}

// ----------------------------------------
// 生成処理
// ----------------------------------------
CPlayer * CPlayer::Create()
{
	// 変数宣言
	CPlayer * pPlayer;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pPlayer = new CPlayer();
	// 初期化処理
	pPlayer->Init();
	// 生成したオブジェクトを返す
	return pPlayer;
}

// ----------------------------------------
// 読み込み処理
// ----------------------------------------
void CPlayer::Load(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();
	// モデル情報の生成
	m_pModel_info = new CModel_info[PLAYERTYPE_MAX];
	// モデルのオフセットの生成
	m_pModel_offset = new MODEL_OFFSET[PLAYERTYPE_MAX];
	// モーションの生成
	m_pMotion = new MOTION[MOTIONTYPE_MAX];
	// テクスチャー情報代入
	char ModelData[PLAYERTYPE_MAX][72] =
	{
		"data/MODEL/bane/Head.x",			// [頭]01
		"data/MODEL/bane/Head.x",			// [体]00
	};
	// モデルのオフセット設定
	CModel_info::ModelOffset(
		m_pModel_offset,					// モデルのオフセット
		"data/MOTION/motion_banekun.txt"	// ファイル名
	);
	// モーションの設定
	CMotion::Load(
		m_pMotion,							// モーション
		m_pModel_offset,					// オフセット
		PLAYERTYPE_MAX,						// キー
		"data/MOTION/motion_banekun.txt"	// ファイル名
	);
	// モデルの保存
	for (int nCntModelLoad = 0; nCntModelLoad < PLAYERTYPE_MAX; nCntModelLoad++)
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
void CPlayer::UnLoad(void)
{
	// モデルの描画情報破棄
	for (int nCntModelLoad = 0; nCntModelLoad < PLAYERTYPE_MAX; nCntModelLoad++)
	{
		// モデル情報の開放
		m_pModel_info[nCntModelLoad].Unload();
	}
	// モーションの破棄
	CMotion::UnLoad(
		m_pMotion,					// モーション
		MOTIONTYPE_MAX
	);
	// モデル情報の破棄
	delete[] m_pModel_info;
	// モデルのオフセットの破棄
	delete[] m_pModel_offset;
}

// ----------------------------------------
// プレイヤーの行動できる範囲を制限
// ----------------------------------------
void CPlayer::Restriction(void)
{
	//タイトルのモードがフリーだった時
	if (CManager::GetTitle()->GetMode() == CManager::GetTitle()->TITLEMODE_FREE &&
		CManager::GetMode() == CManager::MODE_TITLE)
	{
		if (m_pos.x >= 2500)
		{
			m_pos.x = 2500;
		}

		else if (m_pos.x <= -2500)
		{
			m_pos.x = -2500;
		}

		if (m_pos.z >= 2000)
		{
			m_pos.z = 2000;
		}

		else if (m_pos.z <= -2000)
		{
			m_pos.z = -2000;
		}
	}
}

// ----------------------------------------
// 移動量の取得
// ----------------------------------------
D3DXVECTOR3 CPlayer::GetMove(void)
{
	return m_move;
}

// ----------------------------------------
// アビリティ―ポイントの計算
// ----------------------------------------
void CPlayer::SetAbilityPoint(void)
{
	m_nAbilityPoint++;
}

// ----------------------------------------
// アビリティ―フラグの取得
// ----------------------------------------
bool CPlayer::GetAbilityFlag(void)
{
	return m_bAbilityFlag;
}
