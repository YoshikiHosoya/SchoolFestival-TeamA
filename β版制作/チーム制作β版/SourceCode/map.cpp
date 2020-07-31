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
#include "battleplane.h"
#include "helicopter.h"
#include "Player.h"
#include "BaseMode.h"
#include "item.h"
#include "Boss.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
CMap::MAP					CMap::m_MapNum				= MAP_TUTORIAL;				// マップ番号
CMap::WAVE					CMap::m_WaveNum				= WAVE_1;					// ウェーブ番号
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

};

/* ----- ウェーブ ----- */
char *CMap::m_WaveFileName[WAVE_MAX] =
{
	{ "data/Load/Wave/Wave_01.txt" },
	{ "data/Load/Wave/Wave_02.txt" },
	{ "data/Load/Wave/Wave_03.txt" },
};

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define TranslucentColor			(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f))		//半透明
#define ButtonSpace					(250)									// ボタンの間隔

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CMap::CMap()
{
	// 初期化
	m_pMapModel.clear();
	m_pEnemy.clear();
	m_pPrisoner.clear();
	m_pObstacle.clear();
	m_pPlayerTank.clear();
	m_pBattlePlane.clear();
	m_pHelicopter.clear();
	m_pVehicle.clear();
	m_nOldSelect = 0;
	m_WavePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_ModelPosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
	char			cReadText[128];										// 文字として読み取る
	char			cHeadText[128];										// 比較用
	char			cDie[128];											// 不要な文字
	D3DXVECTOR3		pos				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	int				nType			= 0;								// 種類
	char			*cFileName		= nullptr;							// ファイル名
	int				nModelType		= -1;								// モデルの種類

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
				else if (strcmp(cHeadText, "BATTLEPLANESET") == 0)
				{
					sprintf(cEndSetText, "%s", "END_BATTLEPLANESET");
					nModelType = ARRANGEMENT_MODEL_BATTLEPLANE;
				}
				else if (strcmp(cHeadText, "HELICOPTERSET") == 0)
				{
					sprintf(cEndSetText, "%s", "END_HELICOPTERSET");
					nModelType = ARRANGEMENT_MODEL_HELICOPTER;
				}
				else if (strcmp(cHeadText, "BOSSSET") == 0)
				{
					sprintf(cEndSetText, "%s", "END_BOSSSET");
					nModelType = ARRANGEMENT_MODEL_BOSS;
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
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nType);		// 比較用テキストにTYPEを代入
						}
						// POSが来たら
						else if (strcmp(cHeadText, "POS") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &pos.x, &pos.y, &pos.z);		// 比較用テキストにPOSを代入
						}
						else if (strcmp(cHeadText, cEndSetText) == 0)
						{
							// 配置するモデルの生成
							MapModelCreate(nModelType, nType, pos);
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
		LoadFailureMessage(nModelType);
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

		for (int nModelType = 0; nModelType < ARRANGEMENT_MODEL_MAX; nModelType++)
		{
			// セーブするモデルのヘッダー
			SaveModelHeader(pFile, nModelType);

			// 各モデルの種類分回す
			for (unsigned int nCntModel = 0; nCntModel < GetMaxMapModel(nModelType); nCntModel++)
			{
				if (GetMapModel(nModelType, nCntModel))
				{
					// セーブするモデルの情報
					SaveModelContents(pFile, nModelType, nCntModel, nNum);

					nNum++;
				}
			}
		}
		fprintf(pFile, "END_SCRIPT\n");

		for (int nModelType = 0; nModelType < ARRANGEMENT_MODEL_MAX; nModelType++)
		{
			// 読み込み成功時の結果表示
			LoadSuccessMessage(nModelType);
		}

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		// 読み込み失敗時の警告表示
		//LoadFailureMessage(ModelType);
	}
}

//// =====================================================================================================================================================================
////
//// ウェーブのセーブ
////
//// =====================================================================================================================================================================
//void CMap::WaveSave()
//{
//	int nNum = 0;
//
//	// ファイルポイント
//	FILE	*pFile = nullptr;
//
//	// ファイルを開く
//	pFile = fopen(m_WaveFileName[m_WaveNum], "w");
//
//	// 開いているとき
//	if (pFile != NULL)
//	{
//		fprintf(pFile, COMMENT02);
//		fprintf(pFile, "// ウェーブの配置情報\n");
//		fprintf(pFile, COMMENT02);
//
//		fprintf(pFile, "SCRIPT\n");
//		fprintf(pFile, NEWLINE);
//		fprintf(pFile, "	EVENTPOS		= %.0f %.0f %.0f\n", m_aWaveInfo[m_WaveNum].EventPos.x, m_aWaveInfo[m_WaveNum].EventPos.y, m_aWaveInfo[m_WaveNum].EventPos.z);
//		fprintf(pFile, NEWLINE);
//
//		for (int nModelType = 0; nModelType < ARRANGEMENT_MODEL_MAX; nModelType++)
//		{
//			if (nModelType == ARRANGEMENT_MODEL_ENEMY || nModelType == ARRANGEMENT_MODEL_PRISONER)
//			{
//				// セーブするモデルのヘッダー
//				SaveModelHeader(pFile, nModelType);
//
//				// 各モデルの種類分回す
//				for (unsigned int nCntModel = 0; nCntModel < GetMaxMapModel(nModelType); nCntModel++)
//				{
//					if (GetMapModel(nModelType, nCntModel))
//					{
//						// セーブするモデルの情報
//						//SaveWaveContents(pFile, nModelType, nCntModel, nNum);
//
//						nNum++;
//					}
//				}
//			}
//		}
//		fprintf(pFile, "END_SCRIPT\n");
//
//		for (int nModelType = 0; nModelType < ARRANGEMENT_MODEL_MAX; nModelType++)
//		{
//			// 読み込み成功時の結果表示
//			LoadSuccessMessage(nModelType);
//		}
//
//		// ファイルを閉じる
//		fclose(pFile);
//	}
//	else
//	{
//		// 読み込み失敗時の警告表示
//		//LoadFailureMessage(ModelType);
//	}
//}

// =====================================================================================================================================================================
//
// 配置するモデルの生成
//
// =====================================================================================================================================================================
void CMap::MapModelCreate(int ModelType, int nType, D3DXVECTOR3 pos)
{
	switch (ModelType)
	{
	/* --- マップ --- */
	case CMap::ARRANGEMENT_MODEL_MAP:
		// オブジェクトの生成
		m_pMapModel.emplace_back(CModel::CreateSceneManagement(CModel::MODEL_TYPE::MAP_MODEL, nType));
		// 位置の設定
		m_pMapModel[m_pMapModel.size() - 1]->SetPosition(pos);
		break;

	/* --- 敵 --- */
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		// オブジェクトの生成
		m_pEnemy.emplace_back(CEnemy::Create());
		// 位置の設定
		m_pEnemy[m_pEnemy.size() - 1]->SetPosition(pos);
		break;

	/* --- 捕虜 --- */
	case CMap::ARRANGEMENT_MODEL_PRISONER:
		// オブジェクトの生成
		m_pPrisoner.emplace_back(CPrisoner::Create());
		// 位置の設定
		m_pPrisoner[m_pPrisoner.size() - 1]->SetPosition(pos);
		// 種類の設定
		m_pPrisoner[m_pPrisoner.size() - 1]->SetPrisonerType((CPrisoner::PRISONER_ITEM_DROPTYPE)nType);
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

	/* --- 戦闘機 --- */
	case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
		//// オブジェクトの生成
		//m_pBattlePlane.emplace_back(CBattlePlane::Create());
		//// 位置の設定
		//m_pBattlePlane[m_pBattlePlane.size() - 1]->SetPosition(pos);
		break;

	/* --- ヘリコプター --- */
	case CMap::ARRANGEMENT_MODEL_HELICOPTER:
		//// オブジェクトの生成
		//m_pHelicopter.emplace_back(CHelicopter::Create());
		//// 位置の設定
		//m_pHelicopter[m_pHelicopter.size() - 1]->SetPosition(pos);
		//// 種類の設定
		//m_pHelicopter[m_pHelicopter.size() - 1]->SetVehicleType((CVehicle::VEHICLE_TYPE)nType);
		break;

		/* --- ボス --- */
	case CMap::ARRANGEMENT_MODEL_BOSS:
		// オブジェクトの生成
		m_pEnemy.emplace_back(CBoss::Create());
		// 位置の設定
		m_pEnemy[m_pEnemy.size() - 1]->SetPosition(pos);
		break;
	}
}

// =====================================================================================================================================================================
//
// 読み込み失敗時の警告表示
//
// =====================================================================================================================================================================
void CMap::LoadFailureMessage(int ModelType)
{
	switch (ModelType)
	{
		/* --- マップ --- */
	case CMap::ARRANGEMENT_MODEL_MAP:
		MessageBox(NULL, "マップモデルの読み込み失敗", "警告", MB_ICONWARNING);
		break;

		/* --- 敵 --- */
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		MessageBox(NULL, "敵の読み込み失敗", "警告", MB_ICONWARNING);
		break;

		/* --- 捕虜 --- */
	case CMap::ARRANGEMENT_MODEL_PRISONER:
		MessageBox(NULL, "捕虜の読み込み失敗", "警告", MB_ICONWARNING);
		break;

		/* --- 障害物 --- */
	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		MessageBox(NULL, "障害物の読み込み失敗", "警告", MB_ICONWARNING);
		break;

		/* --- 戦車 --- */
	case CMap::ARRANGEMENT_MODEL_TANK:
		MessageBox(NULL, "戦車の読み込み失敗", "警告", MB_ICONWARNING);
		break;

		/* --- 戦闘機 --- */
	case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
		MessageBox(NULL, "戦闘機の読み込み失敗", "警告", MB_ICONWARNING);
		break;

		/* --- ヘリコプター --- */
	case CMap::ARRANGEMENT_MODEL_HELICOPTER:
		MessageBox(NULL, "ヘリコプターの読み込み失敗", "警告", MB_ICONWARNING);
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

		/* --- 戦闘機 --- */
	case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
		MessageBox(NULL, "戦闘機の配置データをセーブしました", "結果", MB_OK | MB_ICONINFORMATION);
		break;

		/* --- ヘリコプター --- */
	case CMap::ARRANGEMENT_MODEL_HELICOPTER:
		MessageBox(NULL, "ヘリコプターの配置データをセーブしました", "結果", MB_OK | MB_ICONINFORMATION);
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
	ImGui::Begin("MapModel", nullptr, ImGuiWindowFlags_MenuBar);

	//Tab
	if (ImGui::BeginTabBar("EditorType"))
	{
		// マップエディター
		if (ImGui::BeginTabItem("MapEditor"))
		{
			MapComboBox(nNowMapSelect, nNowMapSelect);

			//// オブジェクト番号の選択
			//ImGui::InputInt("nowMapNum", &nNowMapSelect, 1, 20, 0);

			//// 範囲制限
			//if (nNowMapSelect <= 0)
			//{
			//	nNowMapSelect = 0;
			//}
			//else if (nNowMapSelect >= MAP_MAX)
			//{
			//	// 最後の番号にする
			//	nNowMapSelect = MAP_MAX - 1;
			//}

			//// 選択したマップ番号代入
			//m_MapNum = (MAP)nNowMapSelect;

			////m_pMapModel[nNowMapSelect]->SetModelConut(nNowMapSelect);

			ImGui::EndTabItem();
		}
		//TabEnd
		ImGui::EndTabBar();
	}

	// マップモデルのタブ
	MapModelTab();

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
void CMap::WaveLoad(WAVE WaveNum)
{
	// 現在のウェーブ番号
	m_WaveNum = WaveNum;

	FILE		*pFile				= nullptr;							// ファイルポインタ
	char		*cFileName			= nullptr;							// ファイル名
	int			nFrame				= 0;								// フレーム
	D3DXVECTOR3	pos					= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	char		cReadText[128];											// 文字として読み取る
	char		cHeadText[128];											// 比較用
	char		cDie[128];												// 不要な文字
	int			nModelType			= -1;								// モデルの種類
	int			nType				= 0;								// 種類
	int			nEvent				= 0;								//boolに変換するようの格納
	WAVE_PARAM	*pParam				= nullptr;							// ウェーブのパラメータ保存用

	// ファイルを開く
	pFile = fopen(m_MapModelFileName[WaveNum], "r");

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

				// イベントが起きる位置を保存
				if (strcmp(cHeadText, "EVENTPOS") == 0)
				{
					sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
						&m_aWaveInfo[WaveNum].EventPos.x, &m_aWaveInfo[WaveNum].EventPos.y, &m_aWaveInfo[WaveNum].EventPos.z);
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
						// FRAMEが来たら
						else if (strcmp(cHeadText, "EVENT") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nEvent);
						}
						else if (strcmp(cHeadText, cEndSetText) == 0)
						{
							pParam->pos = pos;
							pParam->nType = nType;
							pParam->nFrame = nFrame;
							pParam->bEvent = nEvent ? true : false;

							if (nModelType == ARRANGEMENT_MODEL_ENEMY)
							{
								m_aWaveInfo[WaveNum].EnemyWaveInfo.emplace_back(pParam);
							}
							else if (nModelType == ARRANGEMENT_MODEL_PRISONER)
							{
								m_aWaveInfo[WaveNum].PrisonerWaveInfo.emplace_back(pParam);
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
		LoadFailureMessage(nModelType);
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
// 戦闘機の最大数取得
//
// =====================================================================================================================================================================
int CMap::GetMaxBattlePlane()
{
	if (!m_pBattlePlane.empty())
	{
		return m_pBattlePlane.size();
	}
	return 0;
}

// =====================================================================================================================================================================
//
// ヘリの最大数取得
//
// =====================================================================================================================================================================
int CMap::GetMaxHelicopter()
{
	if (!m_pHelicopter.empty())
	{
		return m_pHelicopter.size();
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
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// MAPTYPE情報\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, "//	[ 0 ]	床\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, COMMENT02);
		fprintf(pFile, NEWLINE);
		break;

		/* --- 敵 --- */
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// 敵の配置情報\n");
		fprintf(pFile, COMMENT02);
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// ENEMYTYPE情報\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, "//	[ 0 ]	兵士\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, COMMENT02);
		fprintf(pFile, NEWLINE);
		break;

		/* --- 捕虜 --- */
	case CMap::ARRANGEMENT_MODEL_PRISONER:
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// 捕虜の配置情報\n");
		fprintf(pFile, COMMENT02);
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// PRISONERTYPE情報\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, "//	[ 0 ]	確定ドロップする捕虜\n");
		fprintf(pFile, "//	[ 1 ]	範囲ドロップする捕虜\n");
		fprintf(pFile, "//	[ 2 ]	ランダムドロップする捕虜\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, COMMENT02);
		fprintf(pFile, NEWLINE);
		break;

		/* --- 障害物 --- */
	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// 障害物の配置情報\n");
		fprintf(pFile, COMMENT02);
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// OBSTACLETYPE情報\n");
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

		/* --- 戦闘機 --- */
	case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// 戦闘機の配置情報\n");
		fprintf(pFile, COMMENT02);
		fprintf(pFile, NEWLINE);
		break;

		/* --- ヘリコプター --- */
	case CMap::ARRANGEMENT_MODEL_HELICOPTER:
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// ヘリコプターの配置情報\n");
		fprintf(pFile, COMMENT02);
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
		fprintf(pFile, "MAPSET									# %d\n", nNum);
		fprintf(pFile, "	TYPE	= %d\n", m_pMapModel[nCnt]->GetModelCount());
		fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", m_pMapModel[nCnt]->GetPosition().x, m_pMapModel[nCnt]->GetPosition().y, m_pMapModel[nCnt]->GetPosition().z);
		fprintf(pFile, "END_MAPSET\n\n");
		break;

		/* --- 敵 --- */
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		fprintf(pFile, "ENEMYSET									# %d\n", nNum);
		fprintf(pFile, "	TYPE	= %d\n", 0 /*m_pEnemy[nCnt]->GetType()*/);
		fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", m_pEnemy[nCnt]->GetPosition().x, m_pEnemy[nCnt]->GetPosition().y, m_pEnemy[nCnt]->GetPosition().z);
		fprintf(pFile, "END_ENEMYSET\n\n");
		break;

		/* --- 捕虜 --- */
	case CMap::ARRANGEMENT_MODEL_PRISONER:
		fprintf(pFile, "PRISONERSET									# %d\n", nNum);
		fprintf(pFile, "	TYPE	= %d\n", m_pPrisoner[nCnt]->GetPrisonerDropType());
		fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", m_pPrisoner[nCnt]->GetPosition().x, m_pPrisoner[nCnt]->GetPosition().y, m_pPrisoner[nCnt]->GetPosition().z);
		fprintf(pFile, "END_PRISONERSET\n\n");
		break;

		/* --- 障害物 --- */
	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		fprintf(pFile, "OBSTACLESET									# %d\n", nNum);
		fprintf(pFile, "	TYPE	= %d\n", m_pObstacle[nCnt]->GetModelCount());
		fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", m_pObstacle[nCnt]->GetPosition().x, m_pObstacle[nCnt]->GetPosition().y, m_pObstacle[nCnt]->GetPosition().z);
		fprintf(pFile, "END_OBSTACLESET\n\n");
		break;

		/* --- 戦車 --- */
	case CMap::ARRANGEMENT_MODEL_TANK:
		fprintf(pFile, "TANKSET									# %d\n", nNum);
		fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", m_pPlayerTank[nCnt]->GetPosition().x, m_pPlayerTank[nCnt]->GetPosition().y, m_pPlayerTank[nCnt]->GetPosition().z);
		fprintf(pFile, "END_TANKSET\n\n");
		break;

		/* --- 戦闘機 --- */
	case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
		fprintf(pFile, "BATTLEPLANESET									# %d\n", nNum);
		fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", m_pBattlePlane[nCnt]->GetPosition().x, m_pBattlePlane[nCnt]->GetPosition().y, m_pBattlePlane[nCnt]->GetPosition().z);
		fprintf(pFile, "END_BATTLEPLANESET\n\n");
		break;

		/* --- ヘリコプター --- */
	case CMap::ARRANGEMENT_MODEL_HELICOPTER:
		fprintf(pFile, "HELICOPTERSET									# %d\n", nNum);
		fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", m_pHelicopter[nCnt]->GetPosition().x, m_pHelicopter[nCnt]->GetPosition().y, m_pHelicopter[nCnt]->GetPosition().z);
		fprintf(pFile, "END_HELICOPTERSET\n\n");
		break;
	}
}

// =====================================================================================================================================================================
//
// セーブするウェーブの情報
//
// =====================================================================================================================================================================
void CMap::SaveWaveContents(FILE * pFile, int ModelType, int nType, int nCnt, int nNum)
{
	switch (ModelType)
	{
		/* --- 敵 --- */
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		fprintf(pFile, "ENEMYSET									# %d\n", nNum);
		fprintf(pFile, "	TYPE	= %d\n", 0 /*m_pEnemy[nCnt]->GetType()*/);
		fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", m_pEnemy[nCnt]->GetPosition().x, m_pEnemy[nCnt]->GetPosition().y, m_pEnemy[nCnt]->GetPosition().z);
		fprintf(pFile, "	FRAME	= %d\n", 0 /*m_pEnemy[nCnt]->GetType()*/);
		fprintf(pFile, "	EVENT	= %d\n", 0 /*m_pEnemy[nCnt]->GetType()*/);
		fprintf(pFile, "END_ENEMYSET\n\n");
		break;

		/* --- 捕虜 --- */
	case CMap::ARRANGEMENT_MODEL_PRISONER:
		fprintf(pFile, "PRISONERSET									# %d\n", nNum);
		fprintf(pFile, "	TYPE	= %d\n", m_pPrisoner[nCnt]->GetPrisonerDropType());
		fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", m_pPrisoner[nCnt]->GetPosition().x, m_pPrisoner[nCnt]->GetPosition().y, m_pPrisoner[nCnt]->GetPosition().z);
		fprintf(pFile, "	FRAME	= %d\n", 0 /*m_pEnemy[nCnt]->GetType()*/);
		fprintf(pFile, "END_PRISONERSET\n\n");
		break;
	}
}

// =====================================================================================================================================================================
//
// 配置するモデルの最大数取得
//
// =====================================================================================================================================================================
unsigned int CMap::GetMaxMapModel(int ModelType)
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

		/* --- 戦闘機 --- */
	case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
		return m_pBattlePlane.size();
		break;

		/* --- ヘリコプター --- */
	case CMap::ARRANGEMENT_MODEL_HELICOPTER:
		return m_pHelicopter.size();
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

		/* --- 戦闘機 --- */
	case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
		return m_pBattlePlane[nCnt];
		break;

		/* --- ヘリコプター --- */
	case CMap::ARRANGEMENT_MODEL_HELICOPTER:
		return m_pHelicopter[nCnt];
		break;
	}
	return nullptr;
}

// =====================================================================================================================================================================
//
// 配置したモデルを全てセーブするボタン
//
// =====================================================================================================================================================================
void CMap::AllSaveButton()
{
	// 改行キャンセル
	ImGui::SameLine();

	// セーブ
	if (ImGui::Button("AllSave"))
	{
		for (int nCnt = 0; nCnt < ARRANGEMENT_MODEL_MAX; nCnt++)
		{
			// 配置するモデルのセーブ
			MapModelSave();
		}
	}
}

// =====================================================================================================================================================================
//
// 配置したモデルを全てロードするボタン
//
// =====================================================================================================================================================================
void CMap::AllLoadButton()
{
	// 改行キャンセル
	ImGui::SameLine();

	// セーブ
	if (ImGui::Button("AllLoad"))
	{
		// マップで配置するモデルのロード
		MapModelLoad();
	}
}

// =====================================================================================================================================================================
//
// 配置したモデルを全てデリートするボタン
//
// =====================================================================================================================================================================
void CMap::AllDeleteButton()
{
	// 改行キャンセル
	ImGui::SameLine();

	// 全てデリート
	if (ImGui::Button("AllDelete"))
	{
		AllDelete();
	}
}

// =====================================================================================================================================================================
//
// 配置したモデルをデリートするボタン
//
// =====================================================================================================================================================================
void CMap::ModelDeleteButton(int nNowSelect)
{
	// 消去
	if (ImGui::Button("Delete"))
	{
		switch (m_ArrangmentModel)
		{
		case CMap::ARRANGEMENT_MODEL_MAP:
			// 敵
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

		case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
			// 戦闘機
			m_pBattlePlane[nNowSelect]->Rerease();
			m_pBattlePlane[nNowSelect] = nullptr;
			m_pBattlePlane.erase(m_pBattlePlane.begin() + nNowSelect);
			break;

		case CMap::ARRANGEMENT_MODEL_HELICOPTER:
			// ヘリコプター
			m_pHelicopter[nNowSelect]->Rerease();
			m_pHelicopter[nNowSelect] = nullptr;
			m_pHelicopter.erase(m_pHelicopter.begin() + nNowSelect);
			break;
		}
	}
}

// =====================================================================================================================================================================
//
// 配置したモデルを生成するボタン
//
// =====================================================================================================================================================================
void CMap::ModelCreateButton()
{
	// 生成
	if (ImGui::Button("Crate"))
	{
		switch (m_ArrangmentModel)
		{
		case CMap::ARRANGEMENT_MODEL_ENEMY:
			// 敵
			m_pEnemy.emplace_back(CEnemy::Create());
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

		case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
			// 戦闘機
			m_pBattlePlane.emplace_back(CBattlePlane::Create());
			break;

		case CMap::ARRANGEMENT_MODEL_HELICOPTER:
			// ヘリコプター
			m_pHelicopter.emplace_back(CHelicopter::Create());
			break;
		}
	}
}

// =====================================================================================================================================================================
//
// 配置しているモデルを全て破棄する処理
//
// =====================================================================================================================================================================
void CMap::AllDelete()
{
	// 障害物
	for (unsigned int nCnt = 0; nCnt < m_pMapModel.size(); nCnt++)
	{
		m_pMapModel[nCnt]->Rerease();
		m_pMapModel[nCnt] = nullptr;
	}
	// 障害物
	for (unsigned int nCnt = 0; nCnt < m_pObstacle.size(); nCnt++)
	{
		m_pObstacle[nCnt]->Rerease();
		m_pObstacle[nCnt] = nullptr;
	}
	// 敵
	for (unsigned int nCnt = 0; nCnt < m_pEnemy.size(); nCnt++)
	{
		m_pEnemy[nCnt]->Rerease();
		m_pEnemy[nCnt] = nullptr;
	}
	// 捕虜
	for (unsigned int nCnt = 0; nCnt < m_pPrisoner.size(); nCnt++)
	{
		m_pPrisoner[nCnt]->Rerease();
		m_pPrisoner[nCnt] = nullptr;
	}
	// 戦車
	for (unsigned int nCnt = 0; nCnt < m_pPlayerTank.size(); nCnt++)
	{
		m_pPlayerTank[nCnt]->Rerease();
		m_pPlayerTank[nCnt] = nullptr;
	}
	// 戦闘機
	for (unsigned int nCnt = 0; nCnt < m_pBattlePlane.size(); nCnt++)
	{
		m_pBattlePlane[nCnt]->Rerease();
		m_pBattlePlane[nCnt] = nullptr;
	}
	// ヘリコプター
	for (unsigned int nCnt = 0; nCnt < m_pHelicopter.size(); nCnt++)
	{
		m_pHelicopter[nCnt]->Rerease();
		m_pHelicopter[nCnt] = nullptr;
	}
	// 全ての要素の削除
	m_pMapModel.clear();
	m_pObstacle.clear();
	m_pEnemy.clear();
	m_pPrisoner.clear();
	m_pPlayerTank.clear();
	m_pBattlePlane.clear();
	m_pHelicopter.clear();
}

// =====================================================================================================================================================================
//
// 選択しているモデルの位置の取得
//
// =====================================================================================================================================================================
D3DXVECTOR3 CMap::GetMapModelPos(int nNowSelect)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

	case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
		// 戦闘機
		pos = m_pBattlePlane[nNowSelect]->GetPosition();
		break;

	case CMap::ARRANGEMENT_MODEL_HELICOPTER:
		// ヘリコプター
		pos = m_pHelicopter[nNowSelect]->GetPosition();
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

	case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
		// 戦闘機
		m_pBattlePlane[nNowSelect]->SetPosition(pos);
		break;

	case CMap::ARRANGEMENT_MODEL_HELICOPTER:
		// ヘリコプター
		m_pHelicopter[nNowSelect]->SetPosition(pos);
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
			m_pEnemy[nNowSelect]->ChangeColor(true, -TranslucentColor);
			break;

		case CMap::ARRANGEMENT_MODEL_PRISONER:
			// 捕虜
			m_pPrisoner[nNowSelect]->ChangeColor(true, -TranslucentColor);
			break;

		case CMap::ARRANGEMENT_MODEL_OBSTACLE:
			// 障害物
			m_pObstacle[nNowSelect]->SetColorChangeFlag(true);
			m_pObstacle[nNowSelect]->SetAddColor(-TranslucentColor);
			break;

		case CMap::ARRANGEMENT_MODEL_TANK:
			// 戦車
			break;

		case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
			// 戦闘機
			break;

		case CMap::ARRANGEMENT_MODEL_HELICOPTER:
			// ヘリコプター
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
			m_pEnemy[m_nOldSelect]->ChangeColor(false, ZeroColor);
			break;

		case CMap::ARRANGEMENT_MODEL_PRISONER:
			// 捕虜
			m_pPrisoner[m_nOldSelect]->ChangeColor(false, ZeroColor);
			break;

		case CMap::ARRANGEMENT_MODEL_OBSTACLE:
			// 障害物
			m_pObstacle[m_nOldSelect]->SetColorChangeFlag(false);
			break;

		case CMap::ARRANGEMENT_MODEL_TANK:
			// 戦車
			break;

		case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
			// 戦闘機
			break;

		case CMap::ARRANGEMENT_MODEL_HELICOPTER:
			// ヘリコプター
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
	if (ImGui::BeginTabBar("MapModelType"))
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
		// 戦闘機の設置
		if (ImGui::BeginTabItem("BattlePlane"))
		{
			m_ArrangmentModel = ARRANGEMENT_MODEL_BATTLEPLANE;
			MapModelSet();
			ImGui::EndTabItem();
		}
		// ヘリの設置
		if (ImGui::BeginTabItem("Helicopter"))
		{
			m_ArrangmentModel = ARRANGEMENT_MODEL_HELICOPTER;
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

			// モデルの前回の位置保存
			m_ModelPosOld = GetMapModelPos(nNowSelect);

			// 選択しているモデルを注視点の目的地に設定
			SetSelectMapModelPosRDest(GetMapModelPos(nNowSelect));

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

	// 改行
	ImGui::Separator();

	// 配置したモデルを生成するボタン
	ModelCreateButton();

	// 改行キャンセル
	ImGui::SameLine();

	// 配置したモデルをセーブするボタン
	if (ImGui::Button("Save"))
	{
		// セーブ
		MapModelSave();
	}

	// 配置したモデルを全てロードするボタン
	AllLoadButton();

	// 改行キャンセル
	ImGui::SameLine(ButtonSpace);

	// 配置したモデルをデリートするボタン
	ModelDeleteButton(nNowSelect);

	// 配置したモデルを全てデリートするボタン
	AllDeleteButton();
#endif
}

// =====================================================================================================================================================================
//
// 全てのコンボボックス
//
// =====================================================================================================================================================================
void CMap::ComboBoxAll(int nNowSelect)
{
	static int nSelectType = 0;		// 選んでいる種類

	switch (m_ArrangmentModel)
	{
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		//// 敵の種類選択
		//EnemyComboBox(nSelectType, nNowSelect);
		break;

	case CMap::ARRANGEMENT_MODEL_PRISONER:
		// 捕虜の種類選択
		PrisonerComboBox(nSelectType, nNowSelect);
		break;

	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		// 障害物の種類選択
		ObstacleComboBox(nSelectType, nNowSelect);
		break;
	}
}

// =====================================================================================================================================================================
//
// 障害物のコンボボックス
//
// =====================================================================================================================================================================
void CMap::MapComboBox(int & nSelectType, int nNowSelect)
{
	// ファイル名格納用
	std::vector<std::string > aFileName = {};

	//for
	for (int nCnt = 0; nCnt < CModel::OBSTACLE_TYPE_MAX; nCnt++)
	{
		//配列に追加
		aFileName.emplace_back(CModel::GetModelFileName(CModel::MODEL_TYPE::MAP_MODEL, nCnt));
	}

	if (CHossoLibrary::ImGui_Combobox(aFileName, "MapType", nSelectType))
	{
		// マップのロード
		AllDelete();
		MapLoad((MAP)nSelectType);

		//// NULLチェック
		//if (m_pMapModel[nNowSelect])
		//{
		//	// 捕虜の種類の取得
		//	int MapType = m_pMapModel[nNowSelect]->GetModelCount();

		//	// 前回と違うとき
		//	if (MapType != nSelectType)
		//	{
		//		// 種類代入
		//		MapType = nSelectType;
		//		// 敵のタイプの設定
		//		m_pMapModel[nNowSelect]->SetModelConut(MapType);
		//	}
		//}
	}
}

// =====================================================================================================================================================================
//
// 障害物のコンボボックス
//
// =====================================================================================================================================================================
void CMap::ObstacleComboBox(int &nSelectType, int nNowSelect)
{
#ifdef _DEBUG
	// ファイル名格納用
	std::vector<std::string > aFileName = {};

	//for
	for (int nCnt = 0; nCnt < CModel::OBSTACLE_TYPE_MAX; nCnt++)
	{
		//配列に追加
		aFileName.emplace_back(CModel::GetModelFileName(CModel::MODEL_TYPE::OBSTACLE_MODEL, nCnt));
	}

	if (CHossoLibrary::ImGui_Combobox(aFileName, "Type", nSelectType))
	{
		// NULLチェック
		if (m_pObstacle[nNowSelect])
		{
			// 捕虜の種類の取得
			CModel::OBSTACLE_TYPE ObstacleType = (CModel::OBSTACLE_TYPE)m_pObstacle[nNowSelect]->GetModelCount();

			// 前回と違うとき
			if (ObstacleType != nSelectType)
			{
				// 種類代入
				ObstacleType = (CModel::OBSTACLE_TYPE)nSelectType;
				// 敵のタイプの設定
				m_pObstacle[nNowSelect]->SetModelConut(ObstacleType);
			}
		}
	}
#endif
}

// =====================================================================================================================================================================
//
// 敵のコンボボックス
//
// =====================================================================================================================================================================
void CMap::EnemyComboBox(int &nSelectType, int nNowSelect)
{
#ifdef _DEBUG
	//std::vector<std::string > aEnemyType = { "DESIGNATE_ONE", "DESIGNATE_RANGE", "ALL" };

	//if (CHossoLibrary::ImGui_Combobox(aEnemyType, "Type", nSelectType))
	//{
	//	// NULLチェック
	//	if (m_pPrisoner[nNowSelect])
	//	{
	//		// 捕虜の種類の取得
	//		CPrisoner::PRISONER_ITEM_DROPTYPE PrisonerType = m_pPrisoner[nNowSelect]->GetPrisonerDropType();

	//		// 前回と違うとき
	//		if (PrisonerType != nSelectType)
	//		{
	//			// 種類代入
	//			PrisonerType = (CPrisoner::PRISONER_ITEM_DROPTYPE)nSelectType;
	//			// 敵のタイプの設定
	//			m_pPrisoner[nNowSelect]->SetPrisonerType(PrisonerType);
	//		}
	//	}
	//}
#endif
}

// =====================================================================================================================================================================
//
// 捕虜のコンボボックス
//
// =====================================================================================================================================================================
void CMap::PrisonerComboBox(int &nSelectType, int nNowSelect)
{
#ifdef _DEBUG
	std::vector<std::string > aPrisonerType = { "DESIGNATE_ONE", "DESIGNATE_RANGE", "ALL" };

	if (CHossoLibrary::ImGui_Combobox(aPrisonerType, "Type", nSelectType))
	{
		// NULLチェック
		if (m_pPrisoner[nNowSelect])
		{
			// 捕虜の種類の取得
			CPrisoner::PRISONER_ITEM_DROPTYPE PrisonerType = m_pPrisoner[nNowSelect]->GetPrisonerDropType();

			// 前回と違うとき
			if (PrisonerType != nSelectType)
			{
				// 種類代入
				PrisonerType = (CPrisoner::PRISONER_ITEM_DROPTYPE)nSelectType;
				// 敵のタイプの設定
				m_pPrisoner[nNowSelect]->SetPrisonerType(PrisonerType);
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
	// カメラの取得
	CCamera *pCamera = CManager::GetRenderer()->GetCamera();

	// 注視点の目的地の設定
	pCamera->SetCameraPosRDest(posR);
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
			// ランダムな確率でアイテムをドロップする
			if (CItem::DropRate())
			{
				//アイテムを生成
				CItem::DropCreate(m_pEnemy[nCnt]->GetPosition(),
					CItem::ITEMDROP_WEAPON,
					CItem::ITEMDROP_PATTERN_RANDOM,
					CItem::ITEMTYPE_HEAVYMACHINEGUN);
			}
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

	// 戦闘機の削除
	for (size_t nCnt = 0; nCnt < m_pBattlePlane.size(); nCnt++)
	{
		if (m_pBattlePlane[nCnt]->GetDieFlag())
		{
			m_pBattlePlane[nCnt]->Rerease();
			m_pBattlePlane[nCnt] = nullptr;
			m_pBattlePlane.erase(m_pBattlePlane.begin() + nCnt);
		}
	}

	// ヘリの削除
	for (size_t nCnt = 0; nCnt < m_pHelicopter.size(); nCnt++)
	{
		if (m_pHelicopter[nCnt]->GetDieFlag())
		{
			m_pHelicopter[nCnt]->Rerease();
			m_pHelicopter[nCnt] = nullptr;
			m_pHelicopter.erase(m_pHelicopter.begin() + nCnt);
		}
	}
}