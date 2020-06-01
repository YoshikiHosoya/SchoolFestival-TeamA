// ----------------------------------------
//
// タイル床処理の説明[floartile.h]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
#include "floartile.h"
#include "model_info.h"
#include "enemy.h"
#include "player.h"
#include "debugproc.h"
// ----------------------------------------
//
// 静的変数宣言
//
// ----------------------------------------
LPDIRECT3DTEXTURE9 CFloarTile::m_pTexture = NULL;				// テクスチャへのポインタ
CLoad	*CFloarTile::m_pload = NULL;							// ロード
CModel_info	*CFloarTile::m_pmodel_info = NULL;					// モデル情報
int		CFloarTile::m_aTileType[MAX_TILENUMBER] = {};			// タイルの種類
int		CFloarTile::m_aTileNum[MAX_TILENUMBER] = {};			// タイルの数
int CFloarTile::m_nPlayerSavepos = 0;							// プレイヤーが踏んだマスを保存
CFloarTile *CFloarTile::m_paFloarTile[MAX_WALKTILENUMBER] = {}; // 歩行可能なマスの総数
// ----------------------------------------
// コンストラクタ
// ----------------------------------------
CFloarTile::CFloarTile() : CScene_X::CScene_X(ACTOR_FLOATTILE, LAYER_3DOBJECT)
{
	m_type = TILE_TYPE_WALL;			// タイルの種類
	m_Dire = DIRECTION_FORWARD;
	m_pEnemy = NULL;
	m_pFloarTile = NULL;
	m_nTileNum = 0;
	m_nEnemySavepos = 0;
	m_nSaveArrayNumber = 0;
	m_nDirection = 0;
	m_bLand_Enemy = false;
	m_nDirEnemyBackward = 0;
	for (int nCount = 0; nCount < DIRECTION_ALL; nCount++)
	{
		m_bFlag[nCount] = false;
	}
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CFloarTile::~CFloarTile()
{
	m_bLand_Enemy = false;
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void CFloarTile::Init(void)
{
	// Xオブジェクト生成
	CScene_X::Init();
	// モデル情報設定
	CScene_X::BindModel(m_pmodel_info->GetModel_info());
	// テクスチャー設定
	CScene_X::BindTexture(m_pTexture);
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void CFloarTile::Uninit(void)
{
	CScene_X::Uninit();
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void CFloarTile::Update(void)
{
	// 判定処理
	//PlayerJudg();

	// 判定処理
	EnemyJudg();

	CScene_X::Update();
}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void CFloarTile::Draw(void)
{
	CScene_X::Draw();
}

// ----------------------------------------
// 作成処理
// ----------------------------------------
CFloarTile * CFloarTile::Create(void)
{
	// 変数宣言
	CFloarTile * pFloarTile;		// シーン3Dクラス
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pFloarTile = new CFloarTile();
	// 初期化処理
	pFloarTile->Init();
	// 生成したオブジェクトを返す
	return pFloarTile;
}

// ----------------------------------------
// 読み込み作成処理
// ----------------------------------------
void CFloarTile::LoadCreate(void)
{
	// 変数宣言
	int nCount = 0;
	for (int nCntTile = 0; nCntTile < MAX_TILENUMBER; nCntTile++)
	{
		// タイルの種類が歩行可能な通常の床だったら
		if (m_aTileType[nCntTile] == TILE_TYPE_TILE_NOR)
		{
			m_paFloarTile[nCount] = CFloarTile::Create();						// 生成
			m_paFloarTile[nCount]->SetPos(m_pload->GetInfo(nCount).pos);		// 座標

			m_paFloarTile[nCount]->m_nTileNum = m_aTileNum[nCntTile];			// タイルの番号を代入
			m_paFloarTile[nCount]->m_type = (TILE_TYPE)m_aTileType[nCntTile];	// タイプ(歩行可能マス)

			nCount++; // カウント加算
		}
		// タイルの種類が歩行可能で敵と判定を取るようの床だったら
		else if (m_aTileType[nCntTile] == TILE_TYPE_TILE_SP)
		{
			m_paFloarTile[nCount] = CFloarTile::Create();						// 生成
			m_paFloarTile[nCount]->SetPos(m_pload->GetInfo(nCount).pos);		// 座標

			m_paFloarTile[nCount]->m_nTileNum = m_aTileNum[nCntTile];			// タイルの番号を代入
			m_paFloarTile[nCount]->m_type = (TILE_TYPE)m_aTileType[nCntTile];	// タイプ(歩行可能マス)

			nCount++; // カウント加算
		}
	}
}

// ----------------------------------------
// 判定処理
// ----------------------------------------
void CFloarTile::PlayerJudg()
{
}

// ----------------------------------------
// 判定処理
// ----------------------------------------
void CFloarTile::EnemyJudg()
{
	// エネミーのポインタを探す
	for (int nCntlayer = 0; nCntlayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntlayer++)
	{
		if (m_pEnemy = (CEnemy *)CScene::GetActor(CScene::ACTOR_ENEMY, CScene::LAYER_3DOBJECT, nCntlayer)) break;
	}

	// 敵が存在していて判定が出ていなかった
	if (m_pEnemy != NULL)
	{
		for (int nCntTile = 0; nCntTile < MAX_WALKTILENUMBER; nCntTile++)
		{
			// 床と敵との判定
			if (CCalculation::Plane_GetOn(
				m_paFloarTile[nCntTile]->GetPos(),
				D3DXVECTOR3(150.0f, 0.0f, 150.0f),
				m_pEnemy->GetPos(),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f)))
			{
				// 今いる地点のマスが前回のマスでないかどうか
				if (m_nEnemySavepos != m_paFloarTile[nCntTile]->m_nTileNum)
				{
					// 今触れているマスの番号を保存
					m_nEnemySavepos = m_paFloarTile[nCntTile]->m_nTileNum;

					// タイルに触れていない時 いらないかもしれない
					if (m_bLand_Enemy == false)
					{
						// タイルのタイプが敵の進行判定用のタイルだったら
						if (m_paFloarTile[nCntTile]->m_type == TILE_TYPE_TILE_SP)
						{
							// 配列番号を保存
							m_nSaveArrayNumber = nCntTile;

							// 敵の行動を制御するAI
							EnemyAi();

							// マスに触れているフラグ
							m_bLand_Enemy = true;
						}
					}

					//// 今触れているマスの番号を保存
					//m_nEnemySavepos = m_paFloarTile[nCntTile]->m_nTileNum;
				}
			}

			else
			{
				// 触れていない時、判定フラグを元に戻す
				m_bLand_Enemy = false;
			}
		}
	}
}

// ----------------------------------------
// 敵の進行を決める計算
// ----------------------------------------
void CFloarTile::EnemyAi()
{
	for (int nCount = 0; nCount < DIRECTION_ALL; nCount++)
	{
		m_bFlag[nCount] = false;
	}

	// 上下左右のマスが進行可能か調べる	//

	//----- 今いるマスの番号 - 一列分の長さ の場所にあるタイルが歩行可能なタイルかどうか -----//

	// 前方が壁じゃなかったら
	if ((TILE_TYPE)m_aTileType[m_paFloarTile[m_nSaveArrayNumber]->m_nTileNum - MAX_HORIZONTALNUM] != TILE_TYPE_WALL)
	{
		m_bFlag[DIRECTION_FORWARD] = true;
	}

	//----- 今いるマスの番号 + 一列分の長さ の場所にあるタイルが歩行可能なタイルかどうか -----//

	// 後方が壁じゃなかったら
	if ((TILE_TYPE)m_aTileType[m_paFloarTile[m_nSaveArrayNumber]->m_nTileNum + MAX_HORIZONTALNUM] != TILE_TYPE_WALL)
	{
		m_bFlag[DIRECTION_BACKWARD] = true;
	}

	//----- 今いるマスの番号 - 一マス分の長さ の場所にあるタイルが歩行可能なタイルかどうか -----//

	// 左が壁じゃなかったら
	if ((TILE_TYPE)m_aTileType[m_paFloarTile[m_nSaveArrayNumber]->m_nTileNum - 1] != TILE_TYPE_WALL)
	{
		m_bFlag[DIRECTION_LEFT] = true;
	}

	//----- 今いるマスの番号 + 一マス分の長さ の場所にあるタイルが歩行可能なタイルかどうか -----//

	// 右が壁じゃなかったら
	if ((TILE_TYPE)m_aTileType[m_paFloarTile[m_nSaveArrayNumber]->m_nTileNum + 1] != TILE_TYPE_WALL)
	{
		m_bFlag[DIRECTION_RIGHT] = true;
	}

	//------------------------------------------------------------//

	// 敵の回転状態から後方を確認 //
	if (m_pEnemy->GetEnemyROT() == CEnemy::ROT_FORWARD)			// 前なら後ろ
	{
		m_bFlag[DIRECTION_BACKWARD] = false;
		m_nDirEnemyBackward = DIRECTION_BACKWARD;
	}
	else if (m_pEnemy->GetEnemyROT() == CEnemy::ROT_BACKWARD)	// 後ろなら前
	{
		m_bFlag[DIRECTION_FORWARD] = false;
		m_nDirEnemyBackward = DIRECTION_FORWARD;
	}
	else if (m_pEnemy->GetEnemyROT() == CEnemy::ROT_LEFT)		// 左なら右
	{
		m_bFlag[DIRECTION_RIGHT] = false;
		m_nDirEnemyBackward = DIRECTION_RIGHT;
	}
	else if (m_pEnemy->GetEnemyROT() == CEnemy::ROT_RIGHT)		// 右なら左
	{
		m_bFlag[DIRECTION_LEFT] = false;
		m_nDirEnemyBackward = DIRECTION_LEFT;
	}

	//------------------------------------------------------------//

	bool bOK = false;

	// 進行をランダムに決める
	//do {
	//	// 進行する方向が決まるまでランダムで数字を求める
	//	this->m_nDirection = rand() % DIRECTION_ALL;
	//} while (m_bFlag[this->m_nDirection] == false && this->m_nDirection == m_nDirEnemyBackward);

	if (m_bFlag[m_nDirection] == true && m_nDirection != m_nDirEnemyBackward)
	{
		bOK = true;
	}
	else
	{
		// 進行をランダムに決める
		do {
			// 進行する方向が決まるまでランダムで数字を求める
			m_nDirection = rand() % DIRECTION_ALL;
		} while (m_bFlag[m_nDirection] == false && m_nDirection == m_nDirEnemyBackward);
	}


	// 計算結果が出たら決まった進行方向に回転させる
	if (bOK == true)
	{
		if (this->m_nDirection == DIRECTION_FORWARD && m_nDirEnemyBackward != DIRECTION_FORWARD)
		{
			m_pEnemy->SetRot(D3DXVECTOR3(0.0f, 3.14f, 0.0f), CEnemy::ROT_FORWARD);
			for (int nCount = 0; nCount < DIRECTION_ALL; nCount++)
			{
				m_bFlag[nCount] = false;
			}
		}
		else if (this->m_nDirection == DIRECTION_BACKWARD && m_nDirEnemyBackward != DIRECTION_BACKWARD)
		{
			m_pEnemy->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::ROT_BACKWARD);
			for (int nCount = 0; nCount < DIRECTION_ALL; nCount++)
			{
				m_bFlag[nCount] = false;
			}
		}
		else if (this->m_nDirection == DIRECTION_LEFT && m_nDirEnemyBackward != DIRECTION_LEFT)
		{
			m_pEnemy->SetRot(D3DXVECTOR3(0.0f, 1.57f, 0.0f), CEnemy::ROT_LEFT);
			for (int nCount = 0; nCount < DIRECTION_ALL; nCount++)
			{
				m_bFlag[nCount] = false;
			}
		}
		else if (this->m_nDirection == DIRECTION_RIGHT && m_nDirEnemyBackward != DIRECTION_RIGHT)
		{
			m_pEnemy->SetRot(D3DXVECTOR3(0.0f, -1.57f, 0.0f), CEnemy::ROT_RIGHT);
			for (int nCount = 0; nCount < DIRECTION_ALL; nCount++)
			{
				m_bFlag[nCount] = false;
			}
		}

		bOK = false;
	}

	m_nDirEnemyBackward = 0;
}

// ----------------------------------------
// 読み込み処理
// ----------------------------------------
HRESULT CFloarTile::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice =
		CManager::GetRenderer()->GetDevice();
	// テクスチャー名
	char cTex[128] =
	{
		"data/TEXTURE/FLOOR/floor01.png",
	};
	// モデルファイル名
	char cModelfile[128] =
	{
		"data/MODEL/object/tile.x"
	};

	// 0から最大数までの数を代入
	for (int nCntObj = 0; nCntObj < MAX_TILENUMBER; nCntObj++)
	{
		m_aTileNum[nCntObj] += nCntObj;
	}

	// テクスチャー設定
	D3DXCreateTextureFromFile(pDevice, cTex, &m_pTexture);
	// 全てのマスの種類読み込み
	LoadTileNum("data/LOAD/OBJECT/Tile_Infor.txt");
	// ロード生成
	m_pload = new CLoad;
	// ロード読み込み
	m_pload->Load("data/LOAD/OBJECT/Tile_Location.txt");
	// モデル情報生成
	m_pmodel_info = new CModel_info;
	// モデル読み込み
	m_pmodel_info->Load(pDevice, cModelfile);
	return S_OK;
}

// ----------------------------------------
// unload処理
// ----------------------------------------
void CFloarTile::UnLoad(void)
{
	// テクスチャー設定
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// ロードの破棄
	delete m_pload;
	m_pload = NULL;
	// モデルの破棄
	m_pmodel_info->Unload();
	delete m_pmodel_info;
	m_pmodel_info = NULL;
}

// ----------------------------------------
// load処理
// ----------------------------------------
HRESULT CFloarTile::LoadTileNum(const char * filename)
{
	// ファイルポイント
	FILE *pFile;

	// 変数宣言
	int	nCntObj = 0;		// モデルカウント
	char cRaedText[128];	// 文字として読み取り用
	char cHeadText[128];	// 比較するよう
	char cDie[128];			// 不必要な文字

							// ファイル開
	pFile = fopen(filename, "r");

	// 開けた
	if (pFile != NULL)
	{
		// スクリプトが来るまでループ
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cRaedText, sizeof(cRaedText), pFile);	// 一文を読み込む
			sscanf(cRaedText, "%s", &cHeadText);		// 比較用テクストに文字を代入
		}

		// スクリプトだったら
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			// エンドスクリプトが来るまでループ
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				// 初期化
				cHeadText[0] = '\0';
				fgets(cRaedText, sizeof(cRaedText), pFile);
				sscanf(cRaedText, "%s", &cHeadText);

				// タイプ情報読み込み
				if (strcmp(cHeadText, "TYPE") == 0)
				{
					sscanf(cRaedText, "%s %s %d", &cDie, &cDie,
						&m_aTileType[nCntObj]);

					// 配列の更新
					nCntObj++;
				}

			}
		}
		// ファイル閉
		fclose(pFile);
	}

	// 開けない
	else
	{
		MessageBox(NULL, "オブジェクト読み込みに失敗しました", "警告！", MB_ICONWARNING);
	}

	// 全体の総数
	return nCntObj;
}

// ----------------------------------------
// 位置の設定処理
// ----------------------------------------
void CFloarTile::SetPos(D3DXVECTOR3 pos)
{
	CScene_X::SetPos(pos);
}

// ----------------------------------------
// 回転の設定処理
// ----------------------------------------
void CFloarTile::SetRot(D3DXVECTOR3 rot)
{
	CScene_X::SetRot(rot);
}

// ----------------------------------------
// 位置の取得処理
// ----------------------------------------
D3DXVECTOR3 CFloarTile::GetPos(void)
{
	return CScene_X::GetPos();
}