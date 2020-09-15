// =====================================================================================================================================================================
//
// マップの処理 [map.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "main.h"			// インクルードファイル
#include "map.h"
#include "debugproc.h"
#include "enemy.h"
#include "model.h"
#include <stdio.h>
#include "Obstacle.h"
#include "prisoner.h"
#include "playertank.h"
#include "Player.h"
#include "BaseMode.h"
#include "item.h"
#include "Boss.h"
#include "scene2D.h"
#include "Boss_One.h"
#include "WeakEnemy.h"
#include "sound.h"
#include "ModelSet.h"
#include "model.h"
// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
CMap::MAP					CMap::m_MapNum				= MAP_TUTORIAL;				// マップ番号
CMap::ARRANGEMENT_MODEL		CMap::m_ArrangmentModel		= ARRANGEMENT_MODEL_MAP;	// 配置するモデルの種類
CMap::WAVE_INFO				CMap::m_aWaveInfo[WAVE_MAX] = {};						// ウェーブの情報

// =====================================================================================================================================================================
// テキストファイル名
// =====================================================================================================================================================================
/* ----- マップ(初期配置) ----- */
// マップ
char *CMap::m_MapModelFileName[MAP_MAX] =
{
	{ "data/Load/Map/MAP_Tutorial.txt" },
	{ "data/Load/Map/Map_1_1.txt" },
	{ "data/Load/Map/Map_1_2.txt" },
	{ "data/Load/Map/Map_1_3.txt" },
	{ "data/Load/Map/Map_1_BOSS.txt" },
	{ "data/Load/Map/Map_2_1.txt" },
	{ "data/Load/Map/Map_2_2.txt" },
	{ "data/Load/Map/Map_2_3.txt" },
	{ "data/Load/Map/Map_2_BOSS.txt" },
};

/* ----- ウェーブ ----- */
char *CMap::m_WaveFileName[WAVE_MAX] =
{
	{ "data/Load/Wave/Wave_1_1_1.txt" },
	{ "data/Load/Wave/Wave_1_1_2.txt" },
	{ "data/Load/Wave/Wave_1_2_1.txt" },
	{ "data/Load/Wave/Wave_1_2_2.txt" },
	{ "data/Load/Wave/Wave_1_3_1.txt" },
	{ "data/Load/Wave/Wave_1_3_2.txt" },
	{ "data/Load/Wave/Wave_1_BOSS.txt" },

	{ "data/Load/Wave/Wave_2_1_1.txt" },
	{ "data/Load/Wave/Wave_2_1_2.txt" },
	{ "data/Load/Wave/Wave_2_2_1.txt" },
	{ "data/Load/Wave/Wave_2_2_2.txt" },
	{ "data/Load/Wave/Wave_2_3_1.txt" },
	{ "data/Load/Wave/Wave_2_3_2.txt" },
	{ "data/Load/Wave/Wave_2_BOSS.txt" },

};

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define TranslucentColor			(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f))		// 半透明
#define ButtonSpace					(250)									// ボタンの間隔
#define CameraMoveSpeed				(25.0f)									// カメラの移動速度
#define BG_ID						(100)									// 背景の認識ID

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CMap::CMap()
{
	// 初期化
	m_pMapModel.clear();											// マップモデル
	m_pEnemy.clear();												// 敵
	m_pPrisoner.clear();											// 捕虜
	m_pObstacle.clear();											// 障害物
	m_pPlayerTank.clear();											// 戦車

	m_nOldSelect			= 0;									// 前回選択していたもの
	m_WavePos				= ZeroVector3;							// ウェーブの位置
	m_TransitionPos			= ZeroVector3;							// 遷移する位置
	m_CameraPos				= ZeroVector3;							// カメラの位置
	m_TransitionMapID		= 0;									// 次に遷移するための番号
	m_nBGTexID				= 0;									// 背景のテクスチャ番号
	m_bCameraFollowing		= false;								// カメラを追従するフラグ
	m_bMapExclusion			= false;								// マップモデル以外適用するフラグ
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CMap::~CMap()
{

}

// =====================================================================================================================================================================
//
// 配置するモデルのロード
//
// =====================================================================================================================================================================
void CMap::MapModelLoad()
{
	FILE			*pFile			= nullptr;							// ファイルのポインタ
	D3DXVECTOR3		pos				= ZeroVector3;						// 位置
	int				nType			= 0;								// 種類
	int				nItemType		= 0;								// アイテムの種類
	char			*cFileName		= nullptr;							// ファイル名
	int				nModelType		= -1;								// モデルの種類
	int				nBGTexID		= 0;								// 背景のテクスチャ番号
	char			cReadText[128];										// 文字として読み取る
	char			cHeadText[128];										// 比較用
	char			cDie[128];											// 不要な文字


	switch (m_MapNum)
	{
	case CMap::MAP_1_1:
		CManager::GetSound()->StopAll();
		CManager::GetSound()->Play(CSound::LABEL_BGM_STAGE_01);
		break;

	case CMap::MAP_2_1:
		CManager::GetSound()->StopAll();
		CManager::GetSound()->Play(CSound::LABEL_BGM_STAGE_02);
		break;


	case CMap::MAP_1_BOSS:
		CManager::GetSound()->StopAll();
		CManager::GetSound()->Play(CSound::LABEL_BGM_STAGE_01_BOSS);
		break;

	case CMap::MAP_2_BOSS:
		CManager::GetSound()->StopAll();
		CManager::GetSound()->Play(CSound::LABEL_BGM_STAGE_02_BOSS);
		break;

	default:
		break;
	}

	// ファイルを開く
	pFile = fopen(m_MapModelFileName[m_MapNum], "r");

	// 開いているとき
	if (pFile != NULL)
	{
		// SCRIPTが来るまでループ
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
			sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入
		}

		// SCRIPTが来たら
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			// END_SCRIPTが来るまでループ
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s", &cHeadText);

				if (strcmp(cHeadText, "TRANSITION_POS_X") == 0)
				{
					sscanf(cReadText, "%s %s %f", &cDie, &cDie,&m_TransitionPos.x);
				}
				if (strcmp(cHeadText, "TRANSITION_MAP_ID") == 0)
				{
					sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_TransitionMapID);
				}

				char cEndSetText[32];			// END_SET

				if (strcmp(cHeadText, "MAPSET") == 0)
				{
					strcpy(cEndSetText, "END_MAPSET");
					nModelType = ARRANGEMENT_MODEL_MAP;
				}
				else if (strcmp(cHeadText, "ENEMYSET") == 0)
				{
					sprintf(cEndSetText, "%s", "END_ENEMYSET");
					nModelType = ARRANGEMENT_MODEL_ENEMY;
				}
				else if (strcmp(cHeadText, "PRISONERSET") == 0)
				{
					sprintf(cEndSetText, "%s", "END_PRISONERSET");
					nModelType = ARRANGEMENT_MODEL_PRISONER;
				}
				else if (strcmp(cHeadText, "OBSTACLESET") == 0)
				{
					sprintf(cEndSetText, "%s", "END_OBSTACLESET");
					nModelType = ARRANGEMENT_MODEL_OBSTACLE;
				}
				else if (strcmp(cHeadText, "TANKSET") == 0)
				{
					sprintf(cEndSetText, "%s", "END_TANKSET");
					nModelType = ARRANGEMENT_MODEL_TANK;
				}
				else if (strcmp(cHeadText, "BOSSSET") == 0)
				{
					sprintf(cEndSetText, "%s", "END_BOSSSET");
					nModelType = ARRANGEMENT_MODEL_BOSS;
				}
				else if (strcmp(cHeadText, "BGSET") == 0)
				{
					sprintf(cEndSetText, "%s", "END_BGSET");
					nModelType = BG_ID;
				}
				else if (strcmp(cHeadText, "BOSSONESET") == 0)
				{
					sprintf(cEndSetText, "%s", "END_BOSSONESET");
					nModelType = ARRANGEMENT_MODEL_BOSS_ONE;
				}
				if (nModelType >= 0)
				{
					// END_MODELSETが来るまでループ
					while (strcmp(cHeadText, cEndSetText) != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile);
						sscanf(cReadText, "%s", &cHeadText);

						// TYPEが来たら
						if (strcmp(cHeadText, "TYPE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nType);
						}
						// ITEMTYPEが来たら
						else if (strcmp(cHeadText, "ITEMTYPE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nItemType);
						}
						// POSが来たら
						else if (strcmp(cHeadText, "POS") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &pos.x, &pos.y, &pos.z);
						}
						// BG_TEX_IDが来たら
						else if (strcmp(cHeadText, "BG_TEX_ID") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nBGTexID);
						}
						else if (strcmp(cHeadText, cEndSetText) == 0)
						{
							if (nModelType < ARRANGEMENT_MODEL_MAX)
							{
								// 配置するモデルの生成
								MapModelCreate(nModelType, nType, pos, nItemType);
							}
							else if (nModelType == BG_ID)
							{
								// 背景の生成とテクスチャの設定
								CScene2D *pScene2D = CScene2D::CreateSceneManagement(SCREEN_CENTER_POS, SCREEN_SIZE, CScene::OBJTYPE_BG);
								pScene2D->BindTexture(CTexture::GetTexture(CTexture::TEX_BG_SKY_SUNNY));
							}
							nModelType = -1;
						}
					}
				}
			}
		}
		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		// 読み込み失敗時の警告表示
		MessageBox(NULL, "読み込み失敗", m_MapModelFileName[m_MapNum], MB_ICONWARNING);
	}
}

// =====================================================================================================================================================================
//
// 配置するモデルのセーブ
//
// =====================================================================================================================================================================
void CMap::MapModelSave()
{
	int nNum = 0;

	// ファイルポイント
	FILE	*pFile = nullptr;

	// ファイルを開く
	pFile = fopen(m_MapModelFileName[m_MapNum], "w");

	// 開いているとき
	if (pFile != NULL)
	{
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// マップの初期配置情報\n");
		fprintf(pFile, COMMENT02);

		fprintf(pFile, "SCRIPT\n");
		fprintf(pFile, NEWLINE);

		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// 遷移するための情報\n");
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "TRANSITION_POS_X		= %.0f\n", m_TransitionPos.x);
		fprintf(pFile, "TRANSITION_MAP_ID		= %d\n", m_TransitionMapID);
		fprintf(pFile, NEWLINE);

		for (int nModelType = 0; nModelType < ARRANGEMENT_MODEL_MAX; nModelType++)
		{
			// セーブするモデルのヘッダー
			SaveModelHeader(pFile, nModelType);

			// 各モデルの種類分回す
			for (size_t nCntModel = 0; nCntModel < GetMaxMapModel(nModelType); nCntModel++)
			{
				if (GetMapModel(nModelType, nCntModel))
				{
					// セーブするモデルの情報
					SaveModelContents(pFile, nModelType, nCntModel, nNum);

					nNum++;
				}
			}
		}
		// セーブする背景の情報
		SaveBGContents(pFile);

		fprintf(pFile, "END_SCRIPT\n");

		// 読み込み成功時の結果表示
		MessageBox(NULL, "セーブしました", m_MapModelFileName[m_MapNum], MB_OK | MB_ICONINFORMATION);

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		// 読み込み失敗時の警告表示
		MessageBox(NULL, "読み込み失敗", m_MapModelFileName[m_MapNum], MB_ICONWARNING);
	}
}

// =====================================================================================================================================================================
//
// 配置するモデルの生成
//
// =====================================================================================================================================================================
void CMap::MapModelCreate(int ModelType, int nType, D3DXVECTOR3 pos,int nItemType)
{
	switch (ModelType)
	{
	/* --- マップ --- */
	case CMap::ARRANGEMENT_MODEL_MAP:
		// オブジェクトの生成
		m_pMapModel.emplace_back(CModel::CreateSceneManagement(CModel::MODEL_TYPE::MAP_MODEL, m_MapNum));
		// 位置の設定
		m_pMapModel[m_pMapModel.size() - 1]->SetPosition(pos);
		break;

	/* --- 敵 --- */
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		// オブジェクトの生成
		m_pEnemy.emplace_back(CWeakEnemy::Create((CWeakEnemy::ENEMY_TYPE)nType));
		// 位置の設定
		m_pEnemy[m_pEnemy.size() - 1]->SetPosition(pos);
		break;

	/* --- 捕虜 --- */
	case CMap::ARRANGEMENT_MODEL_PRISONER:
		// オブジェクトの生成
		m_pPrisoner.emplace_back(CPrisoner::Create());
		// 位置の設定
		m_pPrisoner[m_pPrisoner.size() - 1]->SetPosition(pos);
		// ドロップタイプの設定
		m_pPrisoner[m_pPrisoner.size() - 1]->SetPrisonerType((CPrisoner::PRISONER_ITEM_DROPTYPE)nType);
		// アイテムの種類の設定
		m_pPrisoner[m_pPrisoner.size() - 1]->SetPrisonerItem((CItem::ITEMTYPE)nItemType);

		break;

	/* --- 障害物 --- */
	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		// オブジェクトの生成
		m_pObstacle.emplace_back(CObstacle::Create());
		// 障害物種類の設定
		m_pObstacle[m_pObstacle.size() - 1]->SetModelConut(nType);
		// 位置の設定
		m_pObstacle[m_pObstacle.size() - 1]->SetPosition(pos);
		// 当たり判定の大きさの設定
		m_pObstacle[m_pObstacle.size() - 1]->SetCollisionSize((CObstacle::OBSTACLE_TYPE)nType);
		break;

	/* --- 戦車 --- */
	case CMap::ARRANGEMENT_MODEL_TANK:
		// オブジェクトの生成
		m_pPlayerTank.emplace_back(CPlayertank::Create());
		// 位置の設定
		m_pPlayerTank[m_pPlayerTank.size() - 1]->SetPosition(pos);
		break;

		/* --- ボス --- */
	case CMap::ARRANGEMENT_MODEL_BOSS:
		// オブジェクトの生成
		m_pEnemy.emplace_back(CBoss::Create());
		// 位置の設定
		m_pEnemy[m_pEnemy.size() - 1]->SetPosition(pos);
		break;

		/* --- ボス1 --- */
	case CMap::ARRANGEMENT_MODEL_BOSS_ONE:
		// オブジェクトの生成
		m_pEnemy.emplace_back(CBoss_One::Create());
		// 位置の設定
		m_pEnemy[m_pEnemy.size() - 1]->SetPosition(pos);
		break;
	}
}

// =====================================================================================================================================================================
//
// 読み込み成功時の結果表示
//
// =====================================================================================================================================================================
void CMap::LoadSuccessMessage(int ModelType)
{
	switch (ModelType)
	{
		/* --- マップ --- */
	case CMap::ARRANGEMENT_MODEL_MAP:
		MessageBox(NULL, "マップモデルの配置データをセーブしました", "結果", MB_OK | MB_ICONINFORMATION);
		break;

		/* --- 敵 --- */
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		MessageBox(NULL, "敵の配置データをセーブしました", "結果", MB_OK | MB_ICONINFORMATION);
		break;

		/* --- 捕虜 --- */
	case CMap::ARRANGEMENT_MODEL_PRISONER:
		MessageBox(NULL, "捕虜の配置データをセーブしました", "結果", MB_OK | MB_ICONINFORMATION);
		break;

		/* --- 障害物 --- */
	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		MessageBox(NULL, "障害物の配置データをセーブしました", "結果", MB_OK | MB_ICONINFORMATION);
		break;

		/* --- 戦車 --- */
	case CMap::ARRANGEMENT_MODEL_TANK:
		MessageBox(NULL, "戦車の配置データをセーブしました", "結果", MB_OK | MB_ICONINFORMATION);
		break;
	}
}

// =====================================================================================================================================================================
//
// マップの生成
//
// =====================================================================================================================================================================
CMap *CMap::MapCreate()
{
	// 変数
	CMap *pMap;

	// メモリの確保
	pMap = new CMap();

	return pMap;
}

// =====================================================================================================================================================================
//
// マップの更新
//
// =====================================================================================================================================================================
void CMap::MapUpdate()
{
#ifdef _DEBUG

	static int nNowMapSelect = 0;		// 現在選択しているマップ番号

	// オブジェクトウィンドウ
	ImGui::Begin("MapEditor", nullptr, ImGuiWindowFlags_MenuBar);

	//Tab
	if (ImGui::BeginTabBar("EditorType"))
	{
		if (ImGui::BeginTabItem("MapEditor"))
		{
			// マップのコンボボックス
			MapComboBox(nNowMapSelect, nNowMapSelect);
			// マップモデルのタブ
			MapModelTab();
			ImGui::Separator();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("MapModelType"))
		{
			// マップモデルの変更
			MapTypeComboBox();
			ImGui::Separator();
			ImGui::EndTabItem();
		}

		//TabEnd
		ImGui::EndTabBar();
	}

	ImGui::End();
#endif
}

// =====================================================================================================================================================================
//
// マップのロード
//
// =====================================================================================================================================================================
void CMap::MapLoad(MAP MapNum)
{
	// 現在のマップ番号
	m_MapNum = MapNum;

	// マップで配置するモデルのロード
	MapModelLoad();

	if (MapNum == CMap::MAP_1_BOSS)
	{
		CManager::GetRenderer()->GetCamera()->SetCameraStopMove(true);
		CManager::GetRenderer()->GetCamera()->SetPosR(D3DXVECTOR3(0.0f, 200.0f, 0.0f));

	}
	if (MapNum == CMap::MAP_2_BOSS)
	{
		CManager::GetRenderer()->GetCamera()->SetCameraStopMove(true);
		CManager::GetRenderer()->GetCamera()->SetPosR(D3DXVECTOR3(0.0f, 250.0f, 0.0f));

	}
	if (MapNum == CMap::MAP_TUTORIAL)
	{
		CManager::GetRenderer()->GetCamera()->SetCameraStopMove(true);
		CManager::GetRenderer()->GetCamera()->SetPosR(D3DXVECTOR3(0.0f, 200.0f, 0.0f));
	}
}

// =====================================================================================================================================================================
//
// ウェーブのロード
//
// =====================================================================================================================================================================
void CMap::WaveLoad()
{
	FILE		*pFile				= nullptr;							// ファイルポインタ
	char		*cFileName			= nullptr;							// ファイル名
	int			nFrame				= 0;								// フレーム
	D3DXVECTOR3	pos					= ZeroVector3;						// 位置
	int			nModelType			= -1;								// モデルの種類
	int			nType				= 0;								// 種類
	int			nItemType			= 0;								// ドロップするアイテムの種類
	int			nEvent				= 0;								// boolに変換するようの格納
	WAVE_PARAM	*pParam				= nullptr;							// ウェーブのパラメータ保存用
	char		cReadText[128];											// 文字として読み取る
	char		cHeadText[128];											// 比較用
	char		cDie[128];												// 不要な文字

	for (int nCnt = 0; nCnt < CMap::WAVE::WAVE_MAX; nCnt++)
	{
		// ファイルを開く
		pFile = fopen(m_WaveFileName[nCnt], "r");

		// 開いているとき
		if (pFile != NULL)
		{
			// SCRIPTが来るまでループ
			while (strcmp(cHeadText, "SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
				sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入
			}

			// SCRIPTが来たら
			if (strcmp(cHeadText, "SCRIPT") == 0)
			{
				// END_SCRIPTが来るまでループ
				while (strcmp(cHeadText, "END_SCRIPT") != 0)
				{
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s", &cHeadText);

					// イベントが起きるマップ番号
					if (strcmp(cHeadText, "EVENT_BEGIN_MAP") == 0)
					{
						sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_aWaveInfo[nCnt].EventBeginMapNum);
					}

					// イベントが起きる位置を保存
					if (strcmp(cHeadText, "EVENTPOS") == 0)
					{
						sscanf(cReadText, "%s %s %f", &cDie, &cDie, &m_aWaveInfo[nCnt].EventPos.x);
					}

					char cEndSetText[32];			// END_SET

					// 読み込みモデル
					if (strcmp(cHeadText, "ENEMYSET") == 0)
					{
						sprintf(cEndSetText, "%s", "END_ENEMYSET");
						nModelType = ARRANGEMENT_MODEL_ENEMY;
					}
					else if (strcmp(cHeadText, "PRISONERSET") == 0)
					{
						sprintf(cEndSetText, "%s", "END_PRISONERSET");
						nModelType = ARRANGEMENT_MODEL_PRISONER;
					}

					if (nModelType >= 0)
					{
						pParam = new WAVE_PARAM;

						// END_〇〇SETが来るまでループ
						while (strcmp(cHeadText, cEndSetText) != 0)
						{
							fgets(cReadText, sizeof(cReadText), pFile);
							sscanf(cReadText, "%s", &cHeadText);

							// TYPEが来たら
							if (strcmp(cHeadText, "TYPE") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nType);
							}
							// ITEMTYPEが来たら
							else if (strcmp(cHeadText, "ITEMTYPE") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nItemType);
							}
							// POSが来たら
							else if (strcmp(cHeadText, "POS") == 0)
							{
								sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &pos.x, &pos.y, &pos.z);
							}
							// FRAMEが来たら
							else if (strcmp(cHeadText, "FRAME") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nFrame);
							}
							// EVENTが来たら
							else if (strcmp(cHeadText, "EVENT") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nEvent);
							}
							else if (strcmp(cHeadText, cEndSetText) == 0)
							{
								pParam->pos = pos;
								pParam->nType = nType;
								pParam->nItemType = nItemType;
								pParam->nFrame = nFrame;
								pParam->bEvent = nEvent ? true : false;

								// 情報保存
								if (nModelType == ARRANGEMENT_MODEL_ENEMY)
								{
									m_aWaveInfo[nCnt].EnemyWaveInfo.emplace_back(pParam);
								}
								else if (nModelType == ARRANGEMENT_MODEL_PRISONER)
								{
									m_aWaveInfo[nCnt].PrisonerWaveInfo.emplace_back(pParam);
								}
								nModelType = -1;
							}
						}
					}
				}
			}

			//パラメータロード
			std::cout << "Load WaveInfo - " << nCnt << m_WaveFileName[nCnt] << NEWLINE;

			// ファイルを閉じる
			fclose(pFile);
		}
		else
		{
			// 読み込み失敗時の警告表示
			MessageBox(NULL, "読み込み失敗", m_WaveFileName[nCnt], MB_ICONWARNING);
		}
	}
}
// =====================================================================================================================================================================
//
// ウェーブ情報開放
//
// =====================================================================================================================================================================
void CMap::WaveUnLoad()
{
	if (m_aWaveInfo)
	{
		for (int nCntWave = 0; nCntWave < CMap::WAVE::WAVE_MAX; nCntWave++)
		{
			if (!m_aWaveInfo[nCntWave].EnemyWaveInfo.empty())
			{
				for (size_t nCnt = 0; nCnt < m_aWaveInfo[nCntWave].EnemyWaveInfo.size(); nCnt++)
				{
					delete m_aWaveInfo[nCntWave].EnemyWaveInfo[nCnt];
					m_aWaveInfo[nCntWave].EnemyWaveInfo[nCnt] = nullptr;
				}
			}
			if (!m_aWaveInfo[nCntWave].PrisonerWaveInfo.empty())
			{
				for (size_t nCnt = 0; nCnt < m_aWaveInfo[nCntWave].PrisonerWaveInfo.size(); nCnt++)
				{
					delete m_aWaveInfo[nCntWave].PrisonerWaveInfo[nCnt];
					m_aWaveInfo[nCntWave].PrisonerWaveInfo[nCnt] = nullptr;
				}
			}
			m_aWaveInfo[nCntWave].EnemyWaveInfo.clear();
			m_aWaveInfo[nCntWave].PrisonerWaveInfo.clear();
		}
	}
}

// =====================================================================================================================================================================
//
// モデルの最大数取得
//
// =====================================================================================================================================================================
int CMap::GetMaxModel()
{
	if (!m_pMapModel.empty())
	{
		return m_pMapModel.size();
	}
	return 0;
}

// =====================================================================================================================================================================
//
// 敵の最大数取得
//
// =====================================================================================================================================================================
int CMap::GetMaxEnemy()
{
	if (!m_pEnemy.empty())
	{
		return m_pEnemy.size();
	}
	return 0;
}

// =====================================================================================================================================================================
//
// 捕虜の最大数取得
//
// =====================================================================================================================================================================
int CMap::GetMaxPrisoner()
{
	if (!m_pPrisoner.empty())
	{
		return m_pPrisoner.size();
	}
	return 0;
}

// =====================================================================================================================================================================
//
// 障害物の最大数取得
//
// =====================================================================================================================================================================
int CMap::GetMaxObstacle()
{
	if (!m_pObstacle.empty())
	{
		return m_pObstacle.size();
	}
	return 0;
}

// =====================================================================================================================================================================
//
// 戦車の最大数取得
//
// =====================================================================================================================================================================
int CMap::GetMaxPlayerTank()
{
	if (!m_pPlayerTank.empty())
	{
		return m_pPlayerTank.size();
	}
	return 0;
}

// =====================================================================================================================================================================
//
// メッシュの取得
//
// =====================================================================================================================================================================
LPD3DXMESH CMap::GetMesh(int nCnt)
{
	if (!m_pMapModel.empty())
	{
		return m_pMapModel[nCnt]->GetMesh();
	}
	return 0;
}

// =====================================================================================================================================================================
//
// セーブするモデルのヘッダー
//
// =====================================================================================================================================================================
void CMap::SaveModelHeader(FILE * pFile, int ModelType)
{
	switch (ModelType)
	{
		/* --- マップ --- */
	case CMap::ARRANGEMENT_MODEL_MAP:
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// マップモデルの配置情報\n");
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// マップの種類 ( TYPE )\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, "//	[ 0 ]	チュートリアル\n");
		fprintf(pFile, "//	[ 1 ]	ステージ1_1\n");
		fprintf(pFile, "//	[ 2 ]	ステージ1_2\n");
		fprintf(pFile, "//	[ 3 ]	ステージ1_3\n");
		fprintf(pFile, "//	[ 4 ]	ステージ1_BOSS\n");
		fprintf(pFile, "//	[ 5 ]	ステージ2_1\n");
		fprintf(pFile, "//	[ 6 ]	ステージ2_2\n");
		fprintf(pFile, "//	[ 7 ]	ステージ2_3\n");
		fprintf(pFile, "//	[ 8 ]	ステージ2_BOSS\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, COMMENT02);
		fprintf(pFile, NEWLINE);
		break;

		/* --- 敵 --- */
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// 敵の配置情報\n");
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// 敵の種類 ( TYPE )\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, "//	[ 0 ]	通常兵士\n");
		fprintf(pFile, "//	[ 1 ]	盾持ち兵士\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, COMMENT02);
		fprintf(pFile, NEWLINE);
		break;

		/* --- 捕虜 --- */
	case CMap::ARRANGEMENT_MODEL_PRISONER:
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// 捕虜の配置情報\n");
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// 捕虜の種類 ( TYPE )\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, "//	[ 0 ]	確定ドロップする捕虜\n");
		fprintf(pFile, "//	[ 1 ]	範囲ドロップする捕虜\n");
		fprintf(pFile, "//	[ 2 ]	ランダムドロップする捕虜\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// 捕虜の種類 ( ITEMTYPE )\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, "//	[ -1 ]	NONE\n");
		fprintf(pFile, "//	[ 0 ]	ヘビーマシンガン\n");
		fprintf(pFile, "//	[ 1 ]	ショットガン\n");
		fprintf(pFile, "//	[ 2 ]	レーザーガン\n");
		fprintf(pFile, "//	[ 3 ]	ロケットランチャー\n");
		fprintf(pFile, "//	[ 4 ]	フレイムショット\n");
		fprintf(pFile, "//	[ 5 ]	クマ\n");
		fprintf(pFile, "//	[ 6 ]	コイン\n");
		fprintf(pFile, "//	[ 7 ]	宝石\n");
		fprintf(pFile, "//	[ 8 ]	メダル\n");
		fprintf(pFile, "//	[ 9 ]	ボム増加\n");
		fprintf(pFile, "//	[ 10 ]	エネルギー増加\n");
		fprintf(pFile, "//	[ 11 ]	弾薬数増加\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, COMMENT02);
		fprintf(pFile, NEWLINE);
		break;

		/* --- 障害物 --- */
	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// 障害物の配置情報\n");
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// 障害物の種類 ( TYPE )\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, "//	[ 0 ]	箱\n");
		fprintf(pFile, "//	[ 1 ]	樽\n");
		fprintf(pFile, "//	[ 2 ]	木\n");
		fprintf(pFile, "//	[ 3 ]	金庫\n");
		fprintf(pFile, "//	[ 4 ]	土嚢\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, COMMENT02);
		fprintf(pFile, NEWLINE);
		break;

		/* --- 戦車 --- */
	case CMap::ARRANGEMENT_MODEL_TANK:
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// 戦車の配置情報\n");
		fprintf(pFile, COMMENT02);
		fprintf(pFile, NEWLINE);
		break;
	}
}

// =====================================================================================================================================================================
//
// セーブするモデルの情報
//
// =====================================================================================================================================================================
void CMap::SaveModelContents(FILE *pFile, int ModelType, int nCnt, int nNum)
{
	switch (ModelType)
	{
		/* --- マップ --- */
	case CMap::ARRANGEMENT_MODEL_MAP:
		fprintf(pFile, "MAPSET										# %d\n", nNum);
		fprintf(pFile, "	TYPE		= %d\n", m_pMapModel[nCnt]->GetModelCount());
		fprintf(pFile, "	POS			= %.0f %.0f %.0f\n", m_pMapModel[nCnt]->GetPosition().x, m_pMapModel[nCnt]->GetPosition().y, m_pMapModel[nCnt]->GetPosition().z);
		fprintf(pFile, "END_MAPSET\n\n");
		break;

		/* --- 敵 --- */
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		fprintf(pFile, "ENEMYSET									# %d\n", nNum);
		fprintf(pFile, "	TYPE		= %d\n", m_pEnemy[nCnt]->GetEnemyType());
		fprintf(pFile, "	POS			= %.0f %.0f %.0f\n", m_pEnemy[nCnt]->GetPosition().x, m_pEnemy[nCnt]->GetPosition().y, m_pEnemy[nCnt]->GetPosition().z);
		fprintf(pFile, "END_ENEMYSET\n\n");
		break;

		/* --- 捕虜 --- */
	case CMap::ARRANGEMENT_MODEL_PRISONER:
		fprintf(pFile, "PRISONERSET									# %d\n", nNum);
		fprintf(pFile, "	TYPE		= %d\n", m_pPrisoner[nCnt]->GetPrisonerDropType());
		fprintf(pFile, "	ITEMTYPE	= %d\n", m_pPrisoner[nCnt]->GetPrisonerDropItem());
		fprintf(pFile, "	POS			= %.0f %.0f %.0f\n", m_pPrisoner[nCnt]->GetPosition().x, m_pPrisoner[nCnt]->GetPosition().y, m_pPrisoner[nCnt]->GetPosition().z);
		fprintf(pFile, "END_PRISONERSET\n\n");
		break;

		/* --- 障害物 --- */
	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		fprintf(pFile, "OBSTACLESET									# %d\n", nNum);
		fprintf(pFile, "	TYPE		= %d\n", m_pObstacle[nCnt]->GetModelCount());
		fprintf(pFile, "	POS			= %.0f %.0f %.0f\n", m_pObstacle[nCnt]->GetPosition().x, m_pObstacle[nCnt]->GetPosition().y, m_pObstacle[nCnt]->GetPosition().z);
		fprintf(pFile, "END_OBSTACLESET\n\n");
		break;

		/* --- 戦車 --- */
	case CMap::ARRANGEMENT_MODEL_TANK:
		fprintf(pFile, "TANKSET										# %d\n", nNum);
		fprintf(pFile, "	POS			= %.0f %.0f %.0f\n", m_pPlayerTank[nCnt]->GetPosition().x, m_pPlayerTank[nCnt]->GetPosition().y, m_pPlayerTank[nCnt]->GetPosition().z);
		fprintf(pFile, "END_TANKSET\n\n");
		break;
	}
}

// =====================================================================================================================================================================
//
// セーブする背景の情報
//
// =====================================================================================================================================================================
void CMap::SaveBGContents(FILE * pFile)
{
	fprintf(pFile, COMMENT02);
	fprintf(pFile, "// 背景のテクスチャ情報\n");
	fprintf(pFile, COMMENT02);
	fprintf(pFile, COMMENT01);
	fprintf(pFile, "//	[ %d ]	空の背景 ( 晴れ )\n", CTexture::TEX_BG_SKY_SUNNY);
	fprintf(pFile, "//	[ %d ]	空の背景 ( 曇り )\n", CTexture::TEX_BG_SKY_CLOUDY);
	fprintf(pFile, "//	[ %d ]	空の背景 ( 暗雲 )\n", CTexture::TEX_BG_SKY_DARKCLOUDS);
	fprintf(pFile, COMMENT01);
	fprintf(pFile, COMMENT02);
	fprintf(pFile, "BGSET\n");
	fprintf(pFile, "	BG_TEX_ID			= %d\n", CTexture::TEX_BG_SKY_SUNNY);
	fprintf(pFile, "END_BGSET\n");
	fprintf(pFile, NEWLINE);
}

// =====================================================================================================================================================================
//
// 配置するモデルの最大数取得
//
// =====================================================================================================================================================================
size_t CMap::GetMaxMapModel(int ModelType)
{
	switch (ModelType)
	{
		/* --- マップ --- */
	case CMap::ARRANGEMENT_MODEL_MAP:
		return m_pMapModel.size();
		break;

		/* --- 敵 --- */
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		return m_pEnemy.size();
		break;

		/* --- 捕虜 --- */
	case CMap::ARRANGEMENT_MODEL_PRISONER:
		return m_pPrisoner.size();
		break;

		/* --- 障害物 --- */
	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		return m_pObstacle.size();
		break;

		/* --- 戦車 --- */
	case CMap::ARRANGEMENT_MODEL_TANK:
		return m_pPlayerTank.size();
		break;
	}
	return 0;
}

// =====================================================================================================================================================================
//
// 配置するモデルのポインタ
//
// =====================================================================================================================================================================
void * CMap::GetMapModel(int ModelType, int nCnt)
{
	switch (ModelType)
	{
		/* --- マップ --- */
	case CMap::ARRANGEMENT_MODEL_MAP:
		return m_pMapModel[nCnt];
		break;

		/* --- 敵 --- */
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		return m_pEnemy[nCnt];
		break;

		/* --- 捕虜 --- */
	case CMap::ARRANGEMENT_MODEL_PRISONER:
		return m_pPrisoner[nCnt];
		break;

		/* --- 障害物 --- */
	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		return m_pObstacle[nCnt];
		break;

		/* --- 戦車 --- */
	case CMap::ARRANGEMENT_MODEL_TANK:
		return m_pPlayerTank[nCnt];
		break;
	}
	return nullptr;
}

// =====================================================================================================================================================================
//
// 配置したモデルをデリート
//
// =====================================================================================================================================================================
void CMap::ModelDelete(int nNowSelect)
{
	switch (m_ArrangmentModel)
	{
	case CMap::ARRANGEMENT_MODEL_MAP:
		// マップ
		m_pMapModel[nNowSelect]->Rerease();
		m_pMapModel[nNowSelect] = nullptr;
		m_pMapModel.erase(m_pMapModel.begin() + nNowSelect);
		break;

	case CMap::ARRANGEMENT_MODEL_ENEMY:
		// 敵
		m_pEnemy[nNowSelect]->Rerease();
		m_pEnemy[nNowSelect] = nullptr;
		m_pEnemy.erase(m_pEnemy.begin() + nNowSelect);
		break;

	case CMap::ARRANGEMENT_MODEL_PRISONER:
		// 捕虜
		m_pPrisoner[nNowSelect]->Rerease();
		m_pPrisoner[nNowSelect] = nullptr;
		m_pPrisoner.erase(m_pPrisoner.begin() + nNowSelect);
		break;

	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		// 障害物
		m_pObstacle[nNowSelect]->Rerease();
		m_pObstacle[nNowSelect] = nullptr;
		m_pObstacle.erase(m_pObstacle.begin() + nNowSelect);
		break;

	case CMap::ARRANGEMENT_MODEL_TANK:
		// 戦車
		m_pPlayerTank[nNowSelect]->Rerease();
		m_pPlayerTank[nNowSelect] = nullptr;
		m_pPlayerTank.erase(m_pPlayerTank.begin() + nNowSelect);
		break;
	}
}

// =====================================================================================================================================================================
//
// 配置したモデルを生成する
//
// =====================================================================================================================================================================
void CMap::ModelCreat()
{
	// 生成
	switch (m_ArrangmentModel)
	{
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		// 敵
		m_pEnemy.emplace_back(CWeakEnemy::Create(CWeakEnemy::ENEMY_TYPE::ENEMY_NORMAL));
		break;

	case CMap::ARRANGEMENT_MODEL_PRISONER:
		// 捕虜
		m_pPrisoner.emplace_back(CPrisoner::Create());
		break;

	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		// 障害物
		m_pObstacle.emplace_back(CObstacle::Create());
		break;

	case CMap::ARRANGEMENT_MODEL_TANK:
		// 戦車
		m_pPlayerTank.emplace_back(CPlayertank::Create());
		break;
	}
}

// =====================================================================================================================================================================
//
// 配置しているモデルを全て破棄する処理
//
// =====================================================================================================================================================================
void CMap::AllDelete()
{
	if (!m_bMapExclusion)
	{
		// マップモデル
		for (size_t nCnt = 0; nCnt < m_pMapModel.size(); nCnt++)
		{
			m_pMapModel[nCnt]->Rerease();
			m_pMapModel[nCnt] = nullptr;
		}
	}
	// 障害物
	for (size_t nCnt = 0; nCnt < m_pObstacle.size(); nCnt++)
	{
		m_pObstacle[nCnt]->Rerease();
		m_pObstacle[nCnt] = nullptr;
	}
	// 敵
	for (size_t nCnt = 0; nCnt < m_pEnemy.size(); nCnt++)
	{
		m_pEnemy[nCnt]->Rerease();
		m_pEnemy[nCnt] = nullptr;
	}

	// 捕虜
	for (size_t nCnt = 0; nCnt < m_pPrisoner.size(); nCnt++)
	{
		m_pPrisoner[nCnt]->Rerease();
		m_pPrisoner[nCnt] = nullptr;
	}
	// 戦車
	for (size_t nCnt = 0; nCnt < m_pPlayerTank.size(); nCnt++)
	{
		m_pPlayerTank[nCnt]->Rerease();
		m_pPlayerTank[nCnt] = nullptr;
	}
	// 全ての要素の削除
	if (!m_bMapExclusion)
	{
		m_pMapModel.clear();
	}
	m_pObstacle.clear();
	m_pEnemy.clear();
	m_pPrisoner.clear();
	m_pPlayerTank.clear();

	m_bMapExclusion = false;
}


// =====================================================================================================================================================================
//
// Waveの生成
//
// =====================================================================================================================================================================
void CMap::WaveCreate(int nModelType, D3DXVECTOR3 eventpos, WAVE_PARAM * pWaveParam)
{
	if (nModelType == ARRANGEMENT_MODEL_ENEMY)
	{
		// 敵
		m_pEnemy.emplace_back(CWeakEnemy::Create(CWeakEnemy::ENEMY_TYPE::ENEMY_NORMAL));
		m_pEnemy[m_pEnemy.size() - 1]->SetPosition(pWaveParam->pos + eventpos);
		m_pEnemy[m_pEnemy.size() - 1]->SetEventFlag(pWaveParam->bEvent);
	}
	else if (nModelType == ARRANGEMENT_MODEL_PRISONER)
	{
		// 捕虜
		m_pPrisoner.emplace_back(CPrisoner::Create());
		m_pPrisoner[m_pPrisoner.size() - 1]->SetPosition(pWaveParam->pos + eventpos);
		m_pPrisoner[m_pPrisoner.size() - 1]->SetPrisonerType((CPrisoner::PRISONER_ITEM_DROPTYPE)pWaveParam->nType);
		m_pPrisoner[m_pPrisoner.size() - 1]->SetPrisonerItem((CItem::ITEMTYPE)pWaveParam->nItemType);
	}
}

// =====================================================================================================================================================================
//
// マップ情報表記
//
// =====================================================================================================================================================================
void CMap::ShowDebugInfo()
{
	CDebugProc::Print_Left("------ MapInfo ----------\n");

	CDebugProc::Print_Left("EnemyNum >> %d\n", m_pEnemy.size());
	CDebugProc::Print_Left("PrisonerNum >> %d\n", m_pPrisoner.size());
}

// =====================================================================================================================================================================
//
// 選択しているモデルの位置の取得
//
// =====================================================================================================================================================================
D3DXVECTOR3 CMap::GetMapModelPos(int nNowSelect)
{
	D3DXVECTOR3 pos = ZeroVector3;

	if (nNowSelect < 0)
	{
		nNowSelect = 0;
	}

	switch (m_ArrangmentModel)
	{
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		// 敵
		pos = m_pEnemy[nNowSelect]->GetPosition();
		break;

	case CMap::ARRANGEMENT_MODEL_PRISONER:
		// 捕虜
		pos = m_pPrisoner[nNowSelect]->GetPosition();
		break;

	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		// 障害物
		pos = m_pObstacle[nNowSelect]->GetPosition();
		break;

	case CMap::ARRANGEMENT_MODEL_TANK:
		// 戦車
		pos = m_pPlayerTank[nNowSelect]->GetPosition();
		break;
	}

	return pos;
}

// =====================================================================================================================================================================
//
// 選択しているモデルの位置の設定
//
// =====================================================================================================================================================================
void CMap::SetMapModelPos(D3DXVECTOR3 pos, int nNowSelect)
{
	switch (m_ArrangmentModel)
	{
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		// 敵
		m_pEnemy[nNowSelect]->SetPosition(pos);
		break;

	case CMap::ARRANGEMENT_MODEL_PRISONER:
		// 捕虜
		m_pPrisoner[nNowSelect]->SetPosition(pos);
		break;

	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		// 障害物
		m_pObstacle[nNowSelect]->SetPosition(pos);
		break;

	case CMap::ARRANGEMENT_MODEL_TANK:
		// 戦車
		m_pPlayerTank[nNowSelect]->SetPosition(pos);
		break;
	}
}

// =====================================================================================================================================================================
//
// 選択しているモデルの色を半透明にするフラグの設定
//
// =====================================================================================================================================================================
void CMap::SetMapModelColorChangeFlag(bool bFlag, int nNowSelect)
{
	// 色変更フラグをオンして選択している障害物を半透明化
	if (bFlag)
	{
		switch (m_ArrangmentModel)
		{
		case CMap::ARRANGEMENT_MODEL_ENEMY:
			// 敵
			m_pEnemy[nNowSelect]->GetModelSet()->ChangeColor(true, -TranslucentColor);
			break;

		case CMap::ARRANGEMENT_MODEL_PRISONER:
			// 捕虜
			m_pPrisoner[nNowSelect]->GetModelSet()->ChangeColor(true, -TranslucentColor);
			break;

		case CMap::ARRANGEMENT_MODEL_OBSTACLE:
			// 障害物
			m_pObstacle[nNowSelect]->SetColorChangeFlag(true);
			m_pObstacle[nNowSelect]->SetAddColor(-TranslucentColor);
			break;

		case CMap::ARRANGEMENT_MODEL_TANK:
			// 戦車
			break;
		}
	}
	// 色変更無し
	else
	{
		switch (m_ArrangmentModel)
		{
		case CMap::ARRANGEMENT_MODEL_ENEMY:
			// 敵の位置の設定
			m_pEnemy[m_nOldSelect]->GetModelSet()->ChangeColor(false, ZeroColor);
			break;

		case CMap::ARRANGEMENT_MODEL_PRISONER:
			// 捕虜
			m_pPrisoner[m_nOldSelect]->GetModelSet()->ChangeColor(false, ZeroColor);
			break;

		case CMap::ARRANGEMENT_MODEL_OBSTACLE:
			// 障害物
			m_pObstacle[m_nOldSelect]->SetColorChangeFlag(false);
			break;

		case CMap::ARRANGEMENT_MODEL_TANK:
			// 戦車
			break;
		}
	}
}

// =====================================================================================================================================================================
//
// マップに配置するモデルのタブ
//
// =====================================================================================================================================================================
void CMap::MapModelTab()
{
	//Tab
	if (ImGui::BeginTabBar("MapType"))
	{
		// 障害物の設置
		if (ImGui::BeginTabItem("Obstacle"))
		{
			m_ArrangmentModel = ARRANGEMENT_MODEL_OBSTACLE;
			MapModelSet();
			ImGui::EndTabItem();
		}
		// 捕虜の設置
		if (ImGui::BeginTabItem("Prisoner"))
		{
			m_ArrangmentModel = ARRANGEMENT_MODEL_PRISONER;
			MapModelSet();
			ImGui::EndTabItem();
		}
		// 敵の設置
		if (ImGui::BeginTabItem("Enemy"))
		{
			m_ArrangmentModel = ARRANGEMENT_MODEL_ENEMY;
			MapModelSet();
			ImGui::EndTabItem();
		}
		// 戦車の設置
		if (ImGui::BeginTabItem("Tank"))
		{
			m_ArrangmentModel = ARRANGEMENT_MODEL_TANK;
			MapModelSet();
			ImGui::EndTabItem();
		}
		//TabEnd
		ImGui::EndTabBar();
	}
}

// =====================================================================================================================================================================
//
// マップに配置するモデルの設置
//
// =====================================================================================================================================================================
void CMap::MapModelSet()
{
#ifdef _DEBUG

	static int nNowSelect = -1;			// 現在選択している番号
	static int nFrame = 0;
	static bool bEvent = false;

	// オブジェクト番号の選択
	ImGui::InputInt("nowSelect", &nNowSelect, 1, 20, 0);
	// カメラを追従するフラグの切り替え
	ImGui::Checkbox("CameraFollowing", &m_bCameraFollowing);

	// 範囲制限
	if (nNowSelect <= -1)
	{
		nNowSelect = -1;
	}
	else if (nNowSelect >= (int)GetMaxMapModel(m_ArrangmentModel))
	{
		nNowSelect = (int)GetMaxMapModel(m_ArrangmentModel);
	}
	// 選択しているモデルが生成されているとき
	else if (nNowSelect >= 0 || nNowSelect <= (int)GetMaxMapModel(m_ArrangmentModel))
	{
		// コンボボックス
		ComboBoxAll(nNowSelect);

		// NULLチェック
		if (GetMapModel(m_ArrangmentModel, nNowSelect))
		{
			// 現在地
			int x = (int)GetMapModelPos(nNowSelect).x,
				y = (int)GetMapModelPos(nNowSelect).y,
				z = (int)GetMapModelPos(nNowSelect).z;

			// オブジェクトの移動
			ImGui::DragInt("X", &x);
			ImGui::DragInt("Y", &y);
			ImGui::DragInt("Z", &z);

			// 選択しているモデルの位置の設定
			SetMapModelPos(D3DXVECTOR3((float)x, (float)y, (float)z), nNowSelect);

			if (m_bCameraFollowing)
			{
				// 選択しているモデルを注視点の目的地に設定
				SetSelectMapModelPosRDest(GetMapModelPos(nNowSelect));
				// カメラの現在地
				m_CameraPos = GetMapModelPos(nNowSelect);
			}

			// 前回選択していたものと違うとき
			if (m_nOldSelect != nNowSelect)
			{
				// 配置されているモデルのみ
				if ((int)GetMaxMapModel(m_ArrangmentModel) > m_nOldSelect)
				{
					// 色変更無し
					SetMapModelColorChangeFlag(false, nNowSelect);
				}
			}
			else
			{
				// 色変更フラグをオンして選択している障害物を半透明化
				SetMapModelColorChangeFlag(true, nNowSelect);
			}
			// 前回選択していたもの
			m_nOldSelect = nNowSelect;
		}
	}

	if (!m_bCameraFollowing)
	{
		// モデルを追従せずカメラのみの移動
		SetSelectMapModelPosRDest(m_CameraPos);
	}

	// 改行
	ImGui::Separator();

	if (ImGui::Button("Crate"))
	{
		//モデルを生成する
		ModelCreat();

		// 新しく生成したモデルを現在選択しているモデルと同じ位置に生成する
		SetMapModelPos(GetMapModelPos(nNowSelect), (int)GetMaxMapModel(m_ArrangmentModel) - 1);
	}

	// 改行キャンセル
	ImGui::SameLine();

	if (ImGui::Button("Save"))
	{
		// 配置したモデルをセーブする
		MapModelSave();
	}

	ImGui::SameLine();

	ImGui::SameLine(ButtonSpace);

	if (ImGui::Button("Delete"))
	{
		// 配置したモデルをデリートする
		ModelDelete(nNowSelect);
	}

	ImGui::SameLine();

	if (ImGui::Button("AllDelete"))
	{
		// マップモデルを除く
		m_bMapExclusion = true;
		// 配置したモデルを全てデリートする
		AllDelete();
	}
#endif
}

// =====================================================================================================================================================================
//
// 全てのコンボボックス
//
// =====================================================================================================================================================================
void CMap::ComboBoxAll(int nNowSelect)
{
	static int nSelectType		= 0;	// 選んでいる種類
	static int nSelectItemType	= 0;	// 選んでいるアイテムの種類

	switch (m_ArrangmentModel)
	{
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		// 敵の種類選択
		EnemyTypeComboBox(nSelectType, nNowSelect);
		break;

	case CMap::ARRANGEMENT_MODEL_PRISONER:
		// 捕虜のドロップタイプ選択
		PrisonerDropTypeComboBox(nSelectType, nNowSelect);
		// 捕虜のアイテムタイプ選択
		PrisonerItemTypeComboBox(nSelectItemType, nNowSelect);
		break;

	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		// 障害物の種類選択
		ObstacleTypeComboBox(nSelectType, nNowSelect);
		break;
	}
}

// =====================================================================================================================================================================
//
// マップのコンボボックス
//
// =====================================================================================================================================================================
void CMap::MapComboBox(int & nSelectType, int nNowSelect)
{
#ifdef _DEBUG
	// ファイル名格納用
	std::vector<std::string > aFileName = {};

	//for
	for (int nCnt = 0; nCnt < MAP::MAP_MAX; nCnt++)
	{
		//配列に追加
		aFileName.emplace_back(m_MapModelFileName[nCnt]);
	}

	if (CHossoLibrary::ImGui_Combobox(aFileName, "MapTxt", nSelectType))
	{
		// マップのロード
		AllDelete();
		MapLoad((MAP)nSelectType);
	}
#endif
}

// =====================================================================================================================================================================
//
// マップの種類のコンボボックス
//
// =====================================================================================================================================================================
void CMap::MapTypeComboBox()
{
#ifdef _DEBUG
	//static int nSelectType = 0;		// 選んでいる種類
	//int nNowSelect = 0;
	//// ファイル名格納用
	//std::vector<std::string > aFileName = {};

	//	int nCnt = GetModelSet()->
	////for
	//for (int nCnt = 0; nCnt < CModel::MODEL_MAP_MAX; nCnt++)
	//{
	//	//配列に追加
	//	aFileName.emplace_back(CModel::GetModelFileName(CModel::MODEL_TYPE::MAP_MODEL, nCnt));
	//}

	//if (CHossoLibrary::ImGui_Combobox(aFileName, "MapModelType", nSelectType))
	//{
	//	// NULLチェック
	//	if (m_pMapModel[nNowSelect])
	//	{
	//		// マップの種類の取得
	//		int MapType = m_pMapModel[nNowSelect]->GetModelCount();

	//		// 前回と違うとき
	//		if (MapType != nSelectType)
	//		{
	//			// 種類代入
	//			MapType = nSelectType;
	//			// マップのの種類の設定
	//			m_pMapModel[nNowSelect]->SetModelConut(MapType);
	//		}
	//	}
	//}
#endif
}

// =====================================================================================================================================================================
//
// 障害物の種類のコンボボックス
//
// =====================================================================================================================================================================
void CMap::ObstacleTypeComboBox(int &nSelectType, int nNowSelect)
{
#ifdef _DEBUG
	// ファイル名格納用
	std::vector<std::string > aFileName = {};

	//for
	for (int nCnt = 0; nCnt < (CModel::OBSTACLE_TYPE_MAX - CModel::OBSTACLE_TYPE_BOX); nCnt++)
	{
		//配列に追加
		aFileName.emplace_back(CModel::GetModelFileName(CModel::MODEL_TYPE::OBSTACLE_MODEL, nCnt));
	}

	if (CHossoLibrary::ImGui_Combobox(aFileName, "Type", nSelectType))
	{
		// NULLチェック
		if (m_pObstacle[nNowSelect])
		{
			// 障害物の種類の取得
			int ObstacleType = m_pObstacle[nNowSelect]->GetModelCount();

			// 前回と違うとき
			if (ObstacleType != nSelectType)
			{
				// 種類代入
				ObstacleType = nSelectType;
				// 障害物の種類の設定
				m_pObstacle[nNowSelect]->SetModelConut(ObstacleType);
			}
		}
	}
#endif
}

// =====================================================================================================================================================================
//
// 敵の種類のコンボボックス
//
// =====================================================================================================================================================================
void CMap::EnemyTypeComboBox(int &nSelectType, int nNowSelect)
{
#ifdef _DEBUG
	std::vector<std::string > aEnemyType = {"NORMAL", "SHIELD", "HELICOPTER", "MELTYHONEY", "ZYCOCCA"};

	// 現在のタイプを反映
	nSelectType = (int)m_pEnemy[nNowSelect]->GetEnemyType();

	if (CHossoLibrary::ImGui_Combobox(aEnemyType, "Type", nSelectType))
	{
		// NULLチェック
		if (m_pEnemy[nNowSelect])
		{
			// 敵の種類の取得
			CWeakEnemy::ENEMY_TYPE EnemyType = m_pEnemy[nNowSelect]->GetEnemyType();

			// 前回と違うとき
			if ((int)EnemyType != nSelectType)
			{
				// 種類代入
				EnemyType = (CWeakEnemy::ENEMY_TYPE)nSelectType;
				// 敵の種類の設定
				m_pEnemy[nNowSelect]->SetEnemyType(EnemyType);
			}
		}
	}
#endif
}

// =====================================================================================================================================================================
//
// 捕虜のドロップタイプのコンボボックス
//
// =====================================================================================================================================================================
void CMap::PrisonerDropTypeComboBox(int &nSelectType, int nNowSelect)
{
#ifdef _DEBUG
	std::vector<std::string > aPrisonerType = { "DESIGNATE_ONE", "DESIGNATE_RANGE", "ALL" };

	// 現在のドロップタイプを反映
	nSelectType = (int)m_pPrisoner[nNowSelect]->GetPrisonerDropType();

	if (CHossoLibrary::ImGui_Combobox(aPrisonerType, "DropType", nSelectType))
	{
		// NULLチェック
		if (m_pPrisoner[nNowSelect])
		{
			// 捕虜のドロップタイプの取得
			CPrisoner::PRISONER_ITEM_DROPTYPE PrisonerType = m_pPrisoner[nNowSelect]->GetPrisonerDropType();

			// 前回と違うとき
			if (PrisonerType != nSelectType)
			{
				// 種類代入
				PrisonerType = (CPrisoner::PRISONER_ITEM_DROPTYPE)nSelectType;
				// 捕虜のドロップタイプの設定
				m_pPrisoner[nNowSelect]->SetPrisonerType(PrisonerType);
			}
		}
	}

#endif
}

// =====================================================================================================================================================================
//
// 捕虜のアイテムタイプのコンボボックス
//
// =====================================================================================================================================================================
void CMap::PrisonerItemTypeComboBox(int &nSelectType, int nNowSelect)
{
#ifdef _DEBUG
	std::vector<std::string > aPrisonerItem = { "NONE","HMG","SG","LG","RL","FS","BEAR","COIN","JEWELRY","MEDAL","BOMBUP","ENERGYUP","BULLETUP" };

	// 現在のアイテムタイプを反映	( NONEがあるため +1 )
	nSelectType = (int)m_pPrisoner[nNowSelect]->GetPrisonerDropItem() + 1;

	if (CHossoLibrary::ImGui_Combobox(aPrisonerItem, "ItemType", nSelectType))
	{
		// NULLチェック
		if (m_pPrisoner[nNowSelect])
		{
			// 捕虜が落とすアイテムの種類の取得
			CItem::ITEMTYPE PrisonerItem = m_pPrisoner[nNowSelect]->GetPrisonerDropItem();

			// 前回と違うとき
			if (PrisonerItem != nSelectType)
			{
				// 種類代入	( NONEがあるため -1 )
				PrisonerItem = (CItem::ITEMTYPE)(nSelectType - 1);
				// 捕虜が落とすアイテムの種類の設定
				m_pPrisoner[nNowSelect]->SetPrisonerItem(PrisonerItem);
			}
		}
	}
#endif
}

// =====================================================================================================================================================================
//
// 選択しているモデルを注視点の目的地に設定
//
// =====================================================================================================================================================================
void CMap::SetSelectMapModelPosRDest(D3DXVECTOR3 posR)
{
	D3DXVECTOR3 pos = ZeroVector3;

	// カメラの取得
	CCamera *pCamera = CManager::GetRenderer()->GetCamera();
	// キーボードの取得
	CKeyboard *pKeyboard = CManager::GetInputKeyboard();

	// 追従フラグ
	if (m_bCameraFollowing)
	{
		pos = posR;
	}
	else
	{
		//[W]キーを押した時
		if (pKeyboard->GetKeyboardPress(DIK_W))
		{
			//奥
			m_CameraPos.y += CameraMoveSpeed;
		}
		//[S]キーを押した時
		if (pKeyboard->GetKeyboardPress(DIK_S))
		{
			//前
			m_CameraPos.y += -CameraMoveSpeed;
		}
		//[A]キーを押した時
		if (pKeyboard->GetKeyboardPress(DIK_A))
		{
			//左
			m_CameraPos.x += -CameraMoveSpeed;
		}
		//[D]キーを押した時
		if (pKeyboard->GetKeyboardPress(DIK_D))
		{
			//右
			m_CameraPos.x += CameraMoveSpeed;
		}
		pos = m_CameraPos;
	}
	// 注視点の目的地の設定
	pCamera->SetCameraPosRDest(pos);
}

// =====================================================================================================================================================================
//
// 死亡フラグ確認関数
//
// =====================================================================================================================================================================
void CMap::UpdateDieFlag()
{
	// エネミーの削除
	for (size_t nCnt = 0; nCnt < m_pEnemy.size(); nCnt++)
	{
		if (m_pEnemy[nCnt]->GetDieFlag())
		{
			m_pEnemy[nCnt]->Rerease();
			m_pEnemy[nCnt] = nullptr;
			m_pEnemy.erase(m_pEnemy.begin() + nCnt);
		}
	}

	// 障害物の削除
	for (size_t nCnt = 0; nCnt < m_pObstacle.size(); nCnt++)
	{
		if (m_pObstacle[nCnt]->GetDieFlag())
		{
			m_pObstacle[nCnt]->Rerease();
			m_pObstacle[nCnt] = nullptr;
			m_pObstacle.erase(m_pObstacle.begin() + nCnt);
		}
	}

	// 捕虜の削除
	for (size_t nCnt = 0; nCnt < m_pPrisoner.size(); nCnt++)
	{
		if (m_pPrisoner[nCnt]->GetDieFlag())
		{
			m_pPrisoner[nCnt]->Rerease();
			m_pPrisoner[nCnt] = nullptr;
			m_pPrisoner.erase(m_pPrisoner.begin() + nCnt);
		}
	}

	// プレイヤー用戦車の削除
	for (size_t nCnt = 0; nCnt < m_pPlayerTank.size(); nCnt++)
	{
		if (m_pPlayerTank[nCnt]->GetDieFlag())
		{
			m_pPlayerTank[nCnt]->Rerease();
			m_pPlayerTank[nCnt] = nullptr;
			m_pPlayerTank.erase(m_pPlayerTank.begin() + nCnt);
		}
	}
}