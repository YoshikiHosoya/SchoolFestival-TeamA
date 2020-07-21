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

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
CMap::MAP					CMap::m_MapNum			= MAP_1;					// マップ番号
CMap::EDITOR				CMap::m_Editor			= EDITOR_MAP;				// マップエディター
int							CMap::m_ArrangmentModel = ARRANGEMENT_MODEL_MAP;	// 配置するモデルの種類

// =====================================================================================================================================================================
// テキストファイル名
// =====================================================================================================================================================================
// マップファイル名
char *CMap::m_MapFileName[MAP_MAX] =
{
	{ "data/Load/Map/testMap.txt" },
	{ "data/Load/Map/testMap.txt" },
};
// 敵ファイル名
char *CMap::m_EnemyFileName[MAP_MAX] =
{
	{ "data/Load/Enemy/Enemy_Map_01.txt" },
	{ "data/Load/Enemy/Enemy_Map_02.txt" },
};
// 捕虜ファイル名
char *CMap::m_PrisonerFileName[MAP_MAX] =
{
	{ "data/Load/Prisoner/Prisoner_Map_01.txt" },
	{ "data/Load/Prisoner/Prisoner_Map_02.txt" },
};
// 障害物ファイル名
char *CMap::m_ObstacleFileName[MAP_MAX] =
{
	{ "data/Load/Obstacle/Obstacle_Map_01.txt" },
	{ "data/Load/Obstacle/Obstacle_Map_02.txt" },
};
// 戦車ファイル名
char *CMap::m_PlayerTankFileName[MAP_MAX] =
{
	{ "data/Load/PlayerTank/PlayerTank_Map_01.txt" },
	{ "data/Load/PlayerTank/PlayerTank_Map_02.txt" },
};
// 戦闘機ファイル名
char *CMap::m_BattlePlaneFileName[MAP_MAX] =
{
	{ "data/Load/BattlePlane/BattlePlane_Map_01.txt" },
	{ "data/Load/BattlePlane/BattlePlane_Map_02.txt" },
};
// ヘリコプターファイル名
char *CMap::m_HelicopterFileName[MAP_MAX] =
{
	{ "data/Load/Helicopter/Helicopter_Map_01.txt" },
	{ "data/Load/Helicopter/Helicopter_Map_02.txt" },
};

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define TranslucentColor			(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f))		//半透明

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CMap::CMap()
{
	// 初期化
	m_pModel.clear();
	m_pEnemy.clear();
	m_pPrisoner.clear();
	m_pObstacle.clear();
	m_pPlayerTank.clear();
	m_pBattlePlane.clear();
	m_pHelicopter.clear();
	m_nOldSelect = 0;
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
void CMap::ArrangementModelLoad()
{
	// ファイルポイント
	FILE *pFile;
	char cReadText[128];			// 文字として読み取る
	char cHeadText[128];			// 比較用
	char cDie[128];					// 不要な文字
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 大きさ
	int nLife = 0;										// 体力
	int nType = 0;										// 種類
	char *cFileName = nullptr;			// ファイル名

	for (int nCnt = 0; nCnt < ARRANGEMENT_MODEL_MAX; nCnt++)
	{
		// 各モデルファイルのファイルを開く
		pFile = fopen(ArrangementModelFileName(nCnt), "r");

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
					fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
					sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入

					// MODELSETが来たら
					if (strcmp(cHeadText, "MODELSET") == 0)
					{
						// END_MODELSETが来るまでループ
						while (strcmp(cHeadText, "END_MODELSET") != 0)
						{
							fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
							sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入

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
							// LIFEが来たら
							else if (strcmp(cHeadText, "LIFE") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nLife);		// 比較用テキストにTYPEを代入
							}
							// SIZEが来たら
							else if (strcmp(cHeadText, "SIZE") == 0)
							{
								sscanf(cReadText, "%s %s %f %f %f ", &cDie, &cDie, &size.x, &size.y, &size.z);		// 比較用テキストにTYPEを代入
							}
							else if (strcmp(cHeadText, "END_MODELSET") == 0)
							{
								// 配置するモデルの生成
								ArrangementModelCreate(nCnt, nType, pos, nLife, size);
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
			LoadFailureMessage(nCnt);
		}
	}
}

// =====================================================================================================================================================================
//
// 配置するモデルの生成
//
// =====================================================================================================================================================================
void CMap::ArrangementModelCreate(int ModelType, int nType, D3DXVECTOR3 pos, int nLife, D3DXVECTOR3 size)
{
	switch (ModelType)
	{
	/* --- マップ --- */
	case CMap::ARRANGEMENT_MODEL_MAP:
		// オブジェクトの生成
		m_pModel.emplace_back(CModel::CreateSceneManagement(CModel::MAP_MODEL, nType));
		// 位置の設定
		m_pModel[m_pModel.size() - 1]->SetPosition(pos);
		break;

	/* --- 敵 --- */
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		// オブジェクトの生成
		m_pEnemy.emplace_back(CEnemy::Create());
		// 位置の設定
		m_pEnemy[m_pEnemy.size() - 1]->SetPosition(pos);
		// 体力の設定
		m_pEnemy[m_pEnemy.size() - 1]->SetLife(nLife);
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
		// 体力の設定
		m_pObstacle[m_pObstacle.size() - 1]->SetLife(nLife);
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
// 配置するモデルファイル名(初期配置)
//
// =====================================================================================================================================================================
char * CMap::ArrangementModelFileName(int ModelType)
{
	char *cFileName = nullptr;			// ファイル名

	switch (ModelType)
	{
	/* --- マップ --- */
	case CMap::ARRANGEMENT_MODEL_MAP:
		cFileName = m_MapFileName[m_MapNum];
		break;

	/* --- 敵 --- */
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		cFileName = m_EnemyFileName[m_MapNum];
		break;

	/* --- 捕虜 --- */
	case CMap::ARRANGEMENT_MODEL_PRISONER:
		cFileName = m_PrisonerFileName[m_MapNum];
		break;

	/* --- 障害物 --- */
	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		cFileName = m_ObstacleFileName[m_MapNum];
		break;

	/* --- 戦車 --- */
	case CMap::ARRANGEMENT_MODEL_TANK:
		cFileName = m_PlayerTankFileName[m_MapNum];
		break;

	/* --- 戦闘機 --- */
	case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
		cFileName = m_BattlePlaneFileName[m_MapNum];
		break;

	/* --- ヘリコプター --- */
	case CMap::ARRANGEMENT_MODEL_HELICOPTER:
		cFileName = m_HelicopterFileName[m_MapNum];
		break;
	}
	return cFileName;
}

// =====================================================================================================================================================================
//
// マップの生成
//
// =====================================================================================================================================================================
CMap *CMap::MapCreate(MAP MapNum)
{
	// 現在のマップ番号
	m_MapNum = MapNum;

	// 変数
	CMap *pMap;

	// メモリの確保
	pMap = new CMap();

	// 配置するモデルのロード
	pMap->ArrangementModelLoad();

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
			// マップエディター
			m_Editor = EDITOR_MAP;

			// オブジェクト番号の選択
			ImGui::InputInt("nowMapNum", &nNowMapSelect, 1, 20, 0);

			// 範囲制限
			if (nNowMapSelect <= 0)
			{
				nNowMapSelect = 0;
			}
			else if (nNowMapSelect >= MAP_MAX)
			{
				// 最後の番号にする
				nNowMapSelect = MAP_MAX - 1;
			}

			// 選択したマップ番号代入
			m_MapNum = (MAP)nNowMapSelect;

			ImGui::EndTabItem();
		}
		// ウェーブエディター
		if (ImGui::BeginTabItem("WaveEditor"))
		{
			// ウェーブエディター
			m_Editor = EDITOR_WAVE;

			// オブジェクト番号の選択
			ImGui::InputInt("nowWaveNum", &nNowMapSelect, 1, 20, 0);

			// 範囲制限
			if (nNowMapSelect <= 0)
			{
				nNowMapSelect = 0;
			}
			else if (nNowMapSelect >= WAVE_MAX)
			{
				// 最後の番号にする
				nNowMapSelect = MAP_MAX - 1;
			}

			// 選択したマップ番号代入

			ImGui::EndTabItem();
		}
		// 小隊エディター
		if (ImGui::BeginTabItem("PlatoonEditor"))
		{
			// 小隊エディター
			m_Editor = EDITOR_PLATOON;

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
// モデルの最大数取得
//
// =====================================================================================================================================================================
int CMap::GetMaxModel()
{
	if (!m_pModel.empty())
	{
		return m_pModel.size();
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
	if (!m_pModel.empty())
	{
		return m_pModel[nCnt]->GetMesh();
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
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# マップモデルの配置情報\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# TYPE情報\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	[ 0 ]	床\n");
		fprintf(pFile, "#	[ 1 ]	壁\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		break;

		/* --- 敵 --- */
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# 敵の配置情報\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# TYPE情報\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	[ 0 ]	兵士\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		break;

		/* --- 捕虜 --- */
	case CMap::ARRANGEMENT_MODEL_PRISONER:
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# 捕虜の配置情報\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# TYPE情報\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	[ 0 ]	捕虜\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		break;

		/* --- 障害物 --- */
	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# 障害物の配置情報\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# TYPE情報\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	[ 0 ]	箱\n");
		fprintf(pFile, "#	[ 1 ]	樽\n");
		fprintf(pFile, "#	[ 2 ]	木\n");
		fprintf(pFile, "#	[ 3 ]	金庫\n");
		fprintf(pFile, "#	[ 4 ]	土嚢\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		break;

		/* --- 戦車 --- */
	case CMap::ARRANGEMENT_MODEL_TANK:
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# 戦車の配置情報\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# TYPE情報\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	[ 0 ]	戦車\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		break;

		/* --- 戦闘機 --- */
	case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# 戦闘機の配置情報\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# TYPE情報\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	[ 0 ]	戦闘機\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		break;

		/* --- ヘリコプター --- */
	case CMap::ARRANGEMENT_MODEL_HELICOPTER:
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# ヘリコプターの配置情報\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# TYPE情報\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	[ 0 ]	ヘリコプター\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		break;
	}
}

// =====================================================================================================================================================================
//
// セーブするモデルの情報
//
// =====================================================================================================================================================================
void CMap::SaveModelContents(FILE *pFile, int ModelType, int nCnt)
{
	switch (ModelType)
	{
		/* --- マップ --- */
	case CMap::ARRANGEMENT_MODEL_MAP:
		break;

		/* --- 敵 --- */
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		fprintf(pFile, "	TYPE	= %d\n", 0 /*m_pEnemy[nCnt]->GetType()*/);
		fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", m_pEnemy[nCnt]->GetPosition().x, m_pEnemy[nCnt]->GetPosition().y, m_pEnemy[nCnt]->GetPosition().z);
		fprintf(pFile, "	LIFE	= %d\n", m_pEnemy[nCnt]->GetLife());
		break;

		/* --- 捕虜 --- */
	case CMap::ARRANGEMENT_MODEL_PRISONER:
		fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", m_pPrisoner[nCnt]->GetPosition().x, m_pPrisoner[nCnt]->GetPosition().y, m_pPrisoner[nCnt]->GetPosition().z);
		break;

		/* --- 障害物 --- */
	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		fprintf(pFile, "	TYPE	= %d\n", m_pObstacle[nCnt]->GetModelCount());
		fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", m_pObstacle[nCnt]->GetPosition().x, m_pObstacle[nCnt]->GetPosition().y, m_pObstacle[nCnt]->GetPosition().z);
		fprintf(pFile, "	LIFE	= %d\n", m_pObstacle[nCnt]->GetLife());
		fprintf(pFile, "	SIZE	= %.0f %.0f %.0f\n", m_pObstacle[nCnt]->GetSize().x, m_pObstacle[nCnt]->GetSize().y, m_pObstacle[nCnt]->GetSize().z);
		break;

		/* --- 戦車 --- */
	case CMap::ARRANGEMENT_MODEL_TANK:
		fprintf(pFile, "	TYPE	= %d\n", 0 /*m_pPlayerTank[nCnt]->GetModelCount()*/);
		fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", m_pPlayerTank[nCnt]->GetPosition().x, m_pPlayerTank[nCnt]->GetPosition().y, m_pPlayerTank[nCnt]->GetPosition().z);
		fprintf(pFile, "	LIFE	= %d\n", m_pPlayerTank[nCnt]->GetLife());
		break;

		/* --- 戦闘機 --- */
	case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
		fprintf(pFile, "	TYPE	= %d\n", 0 /*m_pBattlePlane[nCnt]->GetModelCount()*/);
		fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", m_pBattlePlane[nCnt]->GetPosition().x, m_pBattlePlane[nCnt]->GetPosition().y, m_pBattlePlane[nCnt]->GetPosition().z);
		fprintf(pFile, "	LIFE	= %d\n", m_pBattlePlane[nCnt]->GetLife());
		break;

		/* --- ヘリコプター --- */
	case CMap::ARRANGEMENT_MODEL_HELICOPTER:
		fprintf(pFile, "	TYPE	= %d\n", 0 /*m_pBattlePlane[nCnt]->GetModelCount()*/);
		fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", m_pHelicopter[nCnt]->GetPosition().x, m_pHelicopter[nCnt]->GetPosition().y, m_pHelicopter[nCnt]->GetPosition().z);
		fprintf(pFile, "	LIFE	= %d\n", m_pHelicopter[nCnt]->GetLife());
		break;
	}
}

// =====================================================================================================================================================================
//
// 配置するモデルの最大数取得
//
// =====================================================================================================================================================================
unsigned int CMap::GetMaxArrangementModel(int ModelType)
{
	switch (ModelType)
	{
		/* --- マップ --- */
	case CMap::ARRANGEMENT_MODEL_MAP:
		return m_pModel.size();
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
void * CMap::GetArrangementModel(int ModelType, int nCnt)
{
	switch (ModelType)
	{
		/* --- マップ --- */
	case CMap::ARRANGEMENT_MODEL_MAP:
		return m_pModel[nCnt];
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
// 配置するモデルのセーブ
//
// =====================================================================================================================================================================
void CMap::ArrangementModelSave(int ModelType)
{
	// ファイルポイント
	FILE	*pFile;

	// マップモデル以外のとき
	if (ModelType != ARRANGEMENT_MODEL_MAP)
	{
		// 各モデルファイルのファイルを開く
		pFile = fopen(ArrangementModelFileName(ModelType), "w");

		// 開いているとき
		if (pFile != NULL)
		{
			// セーブするモデルのヘッダー
			SaveModelHeader(pFile, ModelType);

			fprintf(pFile, "SCRIPT\n\n");

			for (unsigned int nCntModel = 0; nCntModel < GetMaxArrangementModel(ModelType); nCntModel++)
			{
				if (GetArrangementModel(ModelType, nCntModel))
				{
					fprintf(pFile, "MODELSET									# %d\n", nCntModel);

					// セーブするモデルの情報
					SaveModelContents(pFile, ModelType, nCntModel);

					fprintf(pFile, "END_MODELSET\n\n");
				}
			}
			fprintf(pFile, "END_SCRIPT\n");

			// 読み込み成功時の結果表示
			LoadSuccessMessage(ModelType);

			// ファイルを閉じる
			fclose(pFile);
		}
		else
		{
			// 読み込み失敗時の警告表示
			LoadFailureMessage(ModelType);
		}
	}
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
			ArrangementModelSave(nCnt);
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
		// 障害物
		if (ImGui::BeginTabItem("Obstacle"))
		{
			// 障害物の設置
			ObstacleSet();
			ImGui::EndTabItem();
		}
		// 捕虜
		if (ImGui::BeginTabItem("Prisoner"))
		{
			// 捕虜の設置
			PrisonerSet();
			ImGui::EndTabItem();
		}
		// 敵
		if (ImGui::BeginTabItem("Enemy"))
		{
			// 敵の設置
			EnemySet();
			ImGui::EndTabItem();
		}
		// 戦車
		if (ImGui::BeginTabItem("Tank"))
		{
			// 戦車の設置
			PlayerTankSet();
			ImGui::EndTabItem();
		}
		// 戦闘機
		if (ImGui::BeginTabItem("BattlePlane"))
		{
			// 戦闘機の設置
			BattlePlaneSet();
			ImGui::EndTabItem();
		}
		// ヘリ
		if (ImGui::BeginTabItem("Helicopter"))
		{
			// ヘリの設置
			HelicopterSet();
			ImGui::EndTabItem();
		}
		//TabEnd
		ImGui::EndTabBar();
	}
}

// =====================================================================================================================================================================
//
// 障害物の設置
//
// =====================================================================================================================================================================
void CMap::ObstacleSet()
{
#ifdef _DEBUG

	static int nObstacleType = 0;		// 障害物の種類
	static int nNowSelect = -1;			// 現在選択している番号

	// オブジェクト番号の選択
	ImGui::InputInt("nowSelect", &nNowSelect, 1, 20, 0);

	// 範囲制限
	if (nNowSelect <= -1)
	{
		nNowSelect = -1;
	}
	else if (nNowSelect >= (int)m_pObstacle.size())
	{
		nNowSelect = (int)m_pObstacle.size();
	}
	// 選択しているモデルが生成されているとき
	else if (nNowSelect >= 0 || nNowSelect <= (int)m_pObstacle.size())
	{
		// コンボボックス
		if (ObstacleComboBox(nObstacleType))
		{
			// NULLチェック
			if (m_pObstacle[nNowSelect])
			{
				// 障害物の種類の取得
				CModel::OBSTACLE_TYPE ObstacleType = (CModel::OBSTACLE_TYPE)m_pObstacle[nNowSelect]->GetModelCount();

				// 前回と違うとき
				if (ObstacleType != nObstacleType)
				{
					// 種類代入
					ObstacleType = (CModel::OBSTACLE_TYPE)nObstacleType;
					// 障害物のタイプの設定
					m_pObstacle[nNowSelect]->SetModelConut(ObstacleType);
				}
			}
		}

		// NULLチェック
		if (m_pObstacle[nNowSelect])
		{
			// 現在地
			int x = (int)m_pObstacle[nNowSelect]->GetPosition().x,
				y = (int)m_pObstacle[nNowSelect]->GetPosition().y,
				z = (int)m_pObstacle[nNowSelect]->GetPosition().z;

			// オブジェクトの移動
			ImGui::DragInt("X", &x);
			ImGui::DragInt("Y", &y);
			ImGui::DragInt("Z", &z);

			// 障害物の位置の設定
			m_pObstacle[nNowSelect]->SetPosition(D3DXVECTOR3((float)x, (float)y, (float)z));

			// 選択しているモデルを注視点の目的地に設定
			SetSelectMapModelPosRDest(m_pObstacle[nNowSelect]->GetPosition());

			// 選択しているモデルにカメラを合わせる

			// 前回選択していたものと違うとき
			if (m_nOldSelect != nNowSelect)
			{
				// 配置されているモデルのみ
				if (m_pObstacle.size() > (unsigned)m_nOldSelect)
				{
					// 色変更無し
					m_pObstacle[m_nOldSelect]->SetColorChangeFlag(false);
				}
			}
			else
			{
				// 色変更フラグをオンして選択している障害物を半透明化
				m_pObstacle[nNowSelect]->SetColorChangeFlag(true);
				m_pObstacle[nNowSelect]->SetAddColor(-TranslucentColor);
			}
			// 前回選択していたもの
			m_nOldSelect = nNowSelect;
		}
	}

	// 改行
	ImGui::Separator();

	// 生成
	if (ImGui::Button("Crate"))
	{
		// オブジェクトの生成
		m_pObstacle.emplace_back(CObstacle::Create());
	}

	// 改行キャンセル
	ImGui::SameLine();

	// セーブ
	if (ImGui::Button("Save"))
	{
		// 障害物のセーブ
		ArrangementModelSave(ARRANGEMENT_MODEL_OBSTACLE);
	}

	// 全てセーブ
	AllSaveButton();

	// 改行キャンセル
	ImGui::SameLine(250);

	// 消去
	if (ImGui::Button("Delete"))
	{
		m_pObstacle[nNowSelect]->Rerease();
		m_pObstacle[nNowSelect] = nullptr;
		m_pObstacle.erase(m_pObstacle.begin() + nNowSelect);
	}

#endif
}

// =====================================================================================================================================================================
//
// 捕虜の設置
//
// =====================================================================================================================================================================
void CMap::PrisonerSet()
{
#ifdef _DEBUG

	static int nPrisonerType = 0;		// 捕虜の種類
	static int nNowSelect = -1;			// 現在選択している番号

	// オブジェクト番号の選択
	ImGui::InputInt("nowSelect", &nNowSelect, 1, 20, 0);

	// 範囲制限
	if (nNowSelect <= -1)
	{
		nNowSelect = -1;
	}
	else if (nNowSelect >= (int)m_pPrisoner.size())
	{
		nNowSelect = (int)m_pPrisoner.size();
	}
	// 選択しているモデルが生成されているとき
	else if (nNowSelect >= 0 || nNowSelect <= (int)m_pPrisoner.size())
	{
		//// コンボボックス
		//if (PrisonerComboBox(nPrisonerType))
		//{
		//	// NULLチェック
		//	if (m_pPrisoner[nNowSelect])
		//	{
		//		// 捕虜の種類の取得
		//		CModel::PRISONER_TYPE PrisonerType = (CModel::OBSTACLE_TYPE)m_pPrisoner[nNowSelect]->GetModelCount();

		//		// 前回と違うとき
		//		if (PrisonerType != nPrisonerType)
		//		{
		//			// 種類代入
		//			PrisonerType = (CModel::PRISONER_TYPE)nPrisonerType;
		//			// 敵のタイプの設定
		//			m_pPrisoner[nNowSelect]->SetModelConut(PrisonerType);
		//		}
		//	}
		//}

		// NULLチェック
		if (m_pPrisoner[nNowSelect])
		{
			// 現在地
			int x = (int)m_pPrisoner[nNowSelect]->GetPosition().x,
				y = (int)m_pPrisoner[nNowSelect]->GetPosition().y,
				z = (int)m_pPrisoner[nNowSelect]->GetPosition().z;

			// オブジェクトの移動
			ImGui::DragInt("X", &x);
			ImGui::DragInt("Y", &y);
			ImGui::DragInt("Z", &z);

			// オブジェクトの位置の設定
			m_pPrisoner[nNowSelect]->SetPosition(D3DXVECTOR3((float)x, (float)y, (float)z));

			// 選択しているモデルを注視点の目的地に設定
			SetSelectMapModelPosRDest(m_pPrisoner[nNowSelect]->GetPosition());

			// 前回選択していたものと違うとき
			if (m_nOldSelect != nNowSelect)
			{
				// 配置されているモデルのみ
				if (m_pObstacle.size() > (unsigned)m_nOldSelect)
				{
					// 色変更無し
					m_pPrisoner[m_nOldSelect]->ChangeColor(false, ZeroColor);
				}
			}
			else
			{
				// 色変更フラグをオンして選択している障害物を半透明化
				m_pPrisoner[nNowSelect]->ChangeColor(true, -TranslucentColor);
			}
			// 前回選択していたもの
			m_nOldSelect = nNowSelect;
		}
	}

	// 改行
	ImGui::Separator();

	// 生成
	if (ImGui::Button("Crate"))
	{
		// オブジェクトの生成
		m_pPrisoner.emplace_back(CPrisoner::Create());
	}

	// 改行キャンセル
	ImGui::SameLine();

	// セーブ
	if (ImGui::Button("Save"))
	{
		// 捕虜のセーブ
		ArrangementModelSave(ARRANGEMENT_MODEL_PRISONER);
	}

	// 全てセーブ
	AllSaveButton();

	// 改行キャンセル
	ImGui::SameLine(250);

	// 消去
	if (ImGui::Button("Delete"))
	{
		m_pPrisoner[nNowSelect]->Rerease();
		m_pPrisoner[nNowSelect] = nullptr;
		m_pPrisoner.erase(m_pPrisoner.begin() + nNowSelect);
	}
#endif
}

// =====================================================================================================================================================================
//
// 敵の設置
//
// =====================================================================================================================================================================
void CMap::EnemySet()
{
#ifdef _DEBUG

	static int nEnemyType = 0;			// 敵の種類
	static int nNowSelect = -1;			// 現在選択している番号

	// オブジェクト番号の選択
	ImGui::InputInt("nowSelect", &nNowSelect, 1, 20, 0);

	// 範囲制限
	if (nNowSelect <= -1)
	{
		nNowSelect = -1;
	}
	else if (nNowSelect >= (int)m_pEnemy.size())
	{
		nNowSelect = (int)m_pEnemy.size();
	}
	// 選択しているモデルが生成されているとき
	else if (nNowSelect >= 0 || nNowSelect <= (int)m_pEnemy.size())
	{
		//// コンボボックス
		//if (EnemyComboBox(nEnemyType))
		//{
		//	// NULLチェック
		//	if (m_pEnemy[nNowSelect])
		//	{
		//		// 敵の種類の取得
		//		CModel::ENEMY_TYPE EnemyType = (CModel::OBSTACLE_TYPE)m_pEnemy[nNowSelect]->GetModelCount();

		//		// 前回と違うとき
		//		if (EnemyType != nEnemyType)
		//		{
		//			// 種類代入
		//			EnemyType = (CModel::ENEMY_TYPE)nEnemyType;
		//			// 敵のタイプの設定
		//			m_pEnemy[nNowSelect]->SetModelConut(EnemyType);
		//		}
		//	}
		//}

		// NULLチェック
		if (m_pEnemy[nNowSelect])
		{
			// 現在地
			int x = (int)m_pEnemy[nNowSelect]->GetPosition().x,
				y = (int)m_pEnemy[nNowSelect]->GetPosition().y,
				z = (int)m_pEnemy[nNowSelect]->GetPosition().z;

			// オブジェクトの移動
			ImGui::DragInt("X", &x);
			ImGui::DragInt("Y", &y);
			ImGui::DragInt("Z", &z);

			// オブジェクトの位置の設定
			m_pEnemy[nNowSelect]->SetPosition(D3DXVECTOR3((float)x, (float)y, (float)z));

			// 選択しているモデルを注視点の目的地に設定
			SetSelectMapModelPosRDest(m_pEnemy[nNowSelect]->GetPosition());

			// 前回選択していたものと違うとき
			if (m_nOldSelect != nNowSelect)
			{
				// 配置されているモデルのみ
				if (m_pObstacle.size() > (unsigned)m_nOldSelect)
				{
					// 色変更無し
					m_pEnemy[m_nOldSelect]->ChangeColor(false, ZeroColor);
				}
			}
			else
			{
				// 色変更フラグをオンして選択している障害物を半透明化
				m_pEnemy[nNowSelect]->ChangeColor(true, -TranslucentColor);
			}
			// 前回選択していたもの
			m_nOldSelect = nNowSelect;
		}
	}

	// 改行
	ImGui::Separator();

	// 生成
	if (ImGui::Button("Crate"))
	{
		// オブジェクトの生成
		m_pEnemy.emplace_back(CEnemy::Create());
	}

	// 改行キャンセル
	ImGui::SameLine();

	// セーブ
	if (ImGui::Button("Save"))
	{
		// 敵のセーブ
		ArrangementModelSave(ARRANGEMENT_MODEL_ENEMY);
	}

	// 全てセーブ
	AllSaveButton();

	// 改行キャンセル
	ImGui::SameLine(250);

	// 消去
	if (ImGui::Button("Delete"))
	{
		m_pEnemy[nNowSelect]->Rerease();
		m_pEnemy[nNowSelect] = nullptr;
		m_pEnemy.erase(m_pEnemy.begin() + nNowSelect);
	}
#endif
}

// =====================================================================================================================================================================
//
// プレイヤーの戦車の設置
//
// =====================================================================================================================================================================
void CMap::PlayerTankSet()
{
#ifdef _DEBUG

	static int nPlayerTankType = 0;		// 戦車の種類
	static int nNowSelect = -1;			// 現在選択している番号

	// オブジェクト番号の選択
	ImGui::InputInt("nowSelect", &nNowSelect, 1, 20, 0);

	// 範囲制限
	if (nNowSelect <= -1)
	{
		nNowSelect = -1;
	}
	else if (nNowSelect >= (int)m_pPlayerTank.size())
	{
		nNowSelect = (int)m_pPlayerTank.size();
	}
	// 選択しているモデルが生成されているとき
	else if (nNowSelect >= 0 || nNowSelect <= (int)m_pPlayerTank.size())
	{
		// NULLチェック
		if (m_pPlayerTank[nNowSelect])
		{
			// 現在地
			int x = (int)m_pPlayerTank[nNowSelect]->GetPosition().x,
				y = (int)m_pPlayerTank[nNowSelect]->GetPosition().y,
				z = (int)m_pPlayerTank[nNowSelect]->GetPosition().z;

			// オブジェクトの移動
			ImGui::DragInt("X", &x);
			ImGui::DragInt("Y", &y);
			ImGui::DragInt("Z", &z);

			// オブジェクトの位置の設定
			m_pPlayerTank[nNowSelect]->SetPosition(D3DXVECTOR3((float)x, (float)y, (float)z));

			// 選択しているモデルを注視点の目的地に設定
			SetSelectMapModelPosRDest(m_pPlayerTank[nNowSelect]->GetPosition());
		}
	}

	// 改行
	ImGui::Separator();

	// 生成
	if (ImGui::Button("Crate"))
	{
		// オブジェクトの生成
		m_pPlayerTank.emplace_back(CPlayertank::Create());
	}

	// 改行キャンセル
	ImGui::SameLine();

	// セーブ
	if (ImGui::Button("Save"))
	{
		// プレイヤーの戦車のセーブ
		ArrangementModelSave(ARRANGEMENT_MODEL_TANK);
	}

	// 全てセーブ
	AllSaveButton();

	// 改行キャンセル
	ImGui::SameLine(250);

	// 消去
	if (ImGui::Button("Delete"))
	{
		m_pPlayerTank[nNowSelect]->Rerease();
		m_pPlayerTank[nNowSelect] = nullptr;
		m_pPlayerTank.erase(m_pPlayerTank.begin() + nNowSelect);
	}
#endif

}

// =====================================================================================================================================================================
//
// 戦闘機の設置
//
// =====================================================================================================================================================================
void CMap::BattlePlaneSet()
{
#ifdef _DEBUG

	static int nBattlePlaneType = 0;	// 戦闘機の種類
	static int nNowSelect = -1;			// 現在選択している番号

	// オブジェクト番号の選択
	ImGui::InputInt("nowSelect", &nNowSelect, 1, 20, 0);

	// 範囲制限
	if (nNowSelect <= -1)
	{
		nNowSelect = -1;
	}
	else if (nNowSelect >= (int)m_pBattlePlane.size())
	{
		nNowSelect = (int)m_pBattlePlane.size();
	}
	// 選択しているモデルが生成されているとき
	else if (nNowSelect >= 0 || nNowSelect <= (int)m_pBattlePlane.size())
	{
		// NULLチェック
		if (m_pBattlePlane[nNowSelect])
		{
			// 現在地
			int x = (int)m_pBattlePlane[nNowSelect]->GetPosition().x,
				y = (int)m_pBattlePlane[nNowSelect]->GetPosition().y,
				z = (int)m_pBattlePlane[nNowSelect]->GetPosition().z;

			// オブジェクトの移動
			ImGui::DragInt("X", &x);
			ImGui::DragInt("Y", &y);
			ImGui::DragInt("Z", &z);

			// オブジェクトの位置の設定
			m_pBattlePlane[nNowSelect]->SetPosition(D3DXVECTOR3((float)x, (float)y, (float)z));

			// 選択しているモデルを注視点の目的地に設定
			SetSelectMapModelPosRDest(m_pBattlePlane[nNowSelect]->GetPosition());
		}
	}

	// 改行
	ImGui::Separator();

	// 生成
	if (ImGui::Button("Crate"))
	{
		// オブジェクトの生成
		m_pBattlePlane.emplace_back(CBattlePlane::Create());
	}

	// 改行キャンセル
	ImGui::SameLine();

	// セーブ
	if (ImGui::Button("Save"))
	{
		// 戦闘機のセーブ
		ArrangementModelSave(ARRANGEMENT_MODEL_BATTLEPLANE);
	}

	// 全てセーブ
	AllSaveButton();

	// 改行キャンセル
	ImGui::SameLine(250);

	// 消去
	if (ImGui::Button("Delete"))
	{
		m_pBattlePlane[nNowSelect]->Rerease();
		m_pBattlePlane[nNowSelect] = nullptr;
		m_pBattlePlane.erase(m_pBattlePlane.begin() + nNowSelect);
	}
#endif

}

// =====================================================================================================================================================================
//
// ヘリの設置
//
// =====================================================================================================================================================================
void CMap::HelicopterSet()
{
#ifdef _DEBUG

	static int nHelicopterType = 0;		// ヘリの種類
	static int nNowSelect = -1;			// 現在選択している番号

										// オブジェクト番号の選択
	ImGui::InputInt("nowSelect", &nNowSelect, 1, 20, 0);

	// 範囲制限
	if (nNowSelect <= -1)
	{
		nNowSelect = -1;
	}
	else if (nNowSelect >= (int)m_pHelicopter.size())
	{
		nNowSelect = (int)m_pHelicopter.size();
	}
	// 選択しているモデルが生成されているとき
	else if (nNowSelect >= 0 || nNowSelect <= (int)m_pHelicopter.size())
	{
		// NULLチェック
		if (m_pHelicopter[nNowSelect])
		{
			// 現在地
			int x = (int)m_pHelicopter[nNowSelect]->GetPosition().x,
				y = (int)m_pHelicopter[nNowSelect]->GetPosition().y,
				z = (int)m_pHelicopter[nNowSelect]->GetPosition().z;

			// オブジェクトの移動
			ImGui::DragInt("X", &x);
			ImGui::DragInt("Y", &y);
			ImGui::DragInt("Z", &z);

			// オブジェクトの位置の設定
			m_pHelicopter[nNowSelect]->SetPosition(D3DXVECTOR3((float)x, (float)y, (float)z));

			// 選択しているモデルを注視点の目的地に設定
			SetSelectMapModelPosRDest(m_pHelicopter[nNowSelect]->GetPosition());
		}
	}

	// 改行
	ImGui::Separator();

	// 生成
	if (ImGui::Button("Crate"))
	{
		// オブジェクトの生成
		m_pHelicopter.emplace_back(CHelicopter::Create());
	}

	// 改行キャンセル
	ImGui::SameLine();

	// セーブ
	if (ImGui::Button("Save"))
	{
		// ヘリコプターのセーブ
		ArrangementModelSave(ARRANGEMENT_MODEL_HELICOPTER);
	}

	// 全てセーブ
	AllSaveButton();

#endif

}

// =====================================================================================================================================================================
//
// 障害物のコンボボックス
//
// =====================================================================================================================================================================
bool CMap::ObstacleComboBox(int &nType)
{
	bool bSelect = false;	// 選択

#ifdef _DEBUG

	// ファイル名格納用
	std::vector<std::string > aFileName = {};

	//for
	for (int nCnt = 0; nCnt < CModel::OBSTACLE_TYPE_MAX; nCnt++)
	{
		//配列に追加
		aFileName.emplace_back(CModel::GetModelFileName(CModel::MODEL_TYPE::OBSTACLE_MODEL, nCnt));
	}

	// コンボボックス
	if (ImGui::BeginCombo("Type", aFileName[nType].data()))
	{
		for (size_t nCnt = 0; nCnt < aFileName.size(); nCnt++)
		{
			//選択番号があってるかどうか
			bool is_selected = (aFileName[nType] == aFileName[nCnt]);

			//選択された時の処理
			if (ImGui::Selectable(aFileName[nCnt].data(), is_selected))
			{
				//現在の選択項目設定
				nType = nCnt;
				bSelect = true;
			}
			if (is_selected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}
#endif
	return bSelect;
}

// =====================================================================================================================================================================
//
// 敵のコンボボックス
//
// =====================================================================================================================================================================
bool CMap::EnemyComboBox(int & nType)
{
	bool bSelect = false;	// 選択

#ifdef _DEBUG

	//// ファイル名格納用
	//std::vector<std::string > aFileName = {};

	////for
	//for (int nCnt = 0; nCnt < CModel::ENEMY_TYPE_MAX; nCnt++)
	//{
	//	//配列に追加
	//	aFileName.emplace_back(CModel::GetModelFileName(CModel::MODEL_TYPE::ENEMY_MODEL, nCnt));
	//}

	//// コンボボックス
	//if (ImGui::BeginCombo("Type", aFileName[nType].data()))
	//{
	//	for (size_t nCnt = 0; nCnt < aFileName.size(); nCnt++)
	//	{
	//		//選択番号があってるかどうか
	//		bool is_selected = (aFileName[nType] == aFileName[nCnt]);

	//		//選択された時の処理
	//		if (ImGui::Selectable(aFileName[nCnt].data(), is_selected))
	//		{
	//			//現在の選択項目設定
	//			nType = nCnt;
	//			bSelect = true;
	//		}
	//		if (is_selected)
	//		{
	//			ImGui::SetItemDefaultFocus();
	//		}
	//	}
	//	ImGui::EndCombo();
	//}
#endif
	return bSelect;
}

// =====================================================================================================================================================================
//
// 捕虜のコンボボックス
//
// =====================================================================================================================================================================
bool CMap::PrisonerComboBox(int & nType)
{
	bool bSelect = false;	// 選択

#ifdef _DEBUG

							//// ファイル名格納用
							//std::vector<std::string > aFileName = {};

							////for
							//for (int nCnt = 0; nCnt < CModel::ENEMY_TYPE_MAX; nCnt++)
							//{
							//	//配列に追加
							//	aFileName.emplace_back(CModel::GetModelFileName(CModel::MODEL_TYPE::ENEMY_MODEL, nCnt));
							//}

							//// コンボボックス
							//if (ImGui::BeginCombo("Type", aFileName[nType].data()))
							//{
							//	for (size_t nCnt = 0; nCnt < aFileName.size(); nCnt++)
							//	{
							//		//選択番号があってるかどうか
							//		bool is_selected = (aFileName[nType] == aFileName[nCnt]);

							//		//選択された時の処理
							//		if (ImGui::Selectable(aFileName[nCnt].data(), is_selected))
							//		{
							//			//現在の選択項目設定
							//			nType = nCnt;
							//			bSelect = true;
							//		}
							//		if (is_selected)
							//		{
							//			ImGui::SetItemDefaultFocus();
							//		}
							//	}
							//	ImGui::EndCombo();
							//}
#endif
	return bSelect;}

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
