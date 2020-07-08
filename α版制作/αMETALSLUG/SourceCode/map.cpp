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
// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
CMap::MAP CMap::m_MapNum = MAP_1;		// マップ番号

// =====================================================================================================================================================================
// テキストファイル名
// =====================================================================================================================================================================
char *CMap::m_MapFileName[MAP_MAX] =
{
	{ "data/Load/Map/testMap.txt" },
	{ "data/Load/Map/testMap.txt" },
};
char *CMap::m_EnemyFileName[MAP_MAX] =
{
	{ "data/Load/Enemy/Enemy_Map_01.txt" },
	{ "data/Load/Enemy/Enemy_Map_02.txt" },
};
char *CMap::m_PrisonerFileName[MAP_MAX] =
{
	{ "data/Load/Prisoner/Prisoner_Map_01.txt" },
	{ "data/Load/Prisoner/Prisoner_Map_02.txt" },
};

char *CMap::m_ObstacleFileName[MAP_MAX] =
{
	{ "data/Load/Obstacle/Obstacle_Map_01.txt" },
	{ "data/Load/Obstacle/Obstacle_Map_02.txt" },
};

char *CMap::m_PlayerTankFileName[MAP_MAX] =
{
	{ "data/Load/PlayerTank/PlayerTank_Map_01.txt" },
	{ "data/Load/PlayerTank/PlayerTank_Map_02.txt" },
};


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
// モデルのロード
//
// =====================================================================================================================================================================
void CMap::ModelLoad(MAP MapNum)
{
	// ファイルポイント
	FILE *pFile;

	char cReadText[128];			// 文字として読み取る
	char cHeadText[128];			// 比較用
	char cDie[128];					// 不要な文字
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	CModel::CREATE_MAP_MODEL ModelCount = CModel::MODEL_MAP_BLOCK;		// 種類

	// ファイルを開く
	pFile = fopen(m_MapFileName[MapNum], "r");

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
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &ModelCount);		// 比較用テキストにTYPEを代入
						}
						// POSが来たら
						else if (strcmp(cHeadText, "POS") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &pos.x, &pos.y, &pos.z);		// 比較用テキストにPOSを代入
						}
						else if (strcmp(cHeadText, "END_MODELSET") == 0)
						{
							// オブジェクトの生成
							m_pModel.emplace_back(CModel::CreateSceneManagement(CModel::MAP_MODEL, ModelCount));
							// 位置の設定
							m_pModel[m_pModel.size() - 1]->SetPosition(pos);
						}
					}
				}
			}
		}
		// ファイルを閉じる
		fclose(pFile);
	}
}

// =====================================================================================================================================================================
//
// エネミーのロード
//
// =====================================================================================================================================================================
void CMap::EnemyLoad(MAP MapNum)
{
	// ファイルポイント
	FILE *pFile;

	char cReadText[128];			// 文字として読み取る
	char cHeadText[128];			// 比較用
	char cDie[128];					// 不要な文字
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	int nLife		= 0;								// 体力
	//CEnemy::TYPE type = CEnemy::NONE;		// 種類
	int nType = 0;

	// ファイルを開く
	pFile = fopen(m_EnemyFileName[MapNum], "r");

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

				// ENEMYSETが来たら
				if (strcmp(cHeadText, "ENEMYSET") == 0)
				{
					// END_ENEMYSETが来るまでループ
					while (strcmp(cHeadText, "END_ENEMYSET") != 0)
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
						else if (strcmp(cHeadText, "END_ENEMYSET") == 0)
						{
							// オブジェクトの生成
							m_pEnemy.emplace_back(CEnemy::Create());
							// 位置の設定
							m_pEnemy[m_pEnemy.size() - 1]->SetPosition(pos);
							// 体力の設定
							m_pEnemy[m_pEnemy.size() - 1]->SetLife(nLife);
						}
					}
				}
			}
		}
		// ファイルを閉じる
		fclose(pFile);
	}
}

// =====================================================================================================================================================================
//
// 捕虜の配置
//
// =====================================================================================================================================================================
void CMap::PrisonerLoad(MAP MapNum)
{
	// ファイルポイント
	FILE *pFile;

	char cReadText[128];								// 文字として読み取る
	char cHeadText[128];								// 比較用
	char cDie[128];										// 不要な文字
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	// ファイルを開く
	pFile = fopen(m_PrisonerFileName[MapNum], "r");

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

				// PRISONERSETが来たら
				if (strcmp(cHeadText, "PRISONERSET") == 0)
				{
					// END_PRISONERSETが来るまでループ
					while (strcmp(cHeadText, "END_PRISONERSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
						sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入

						// POSが来たら
						if (strcmp(cHeadText, "POS") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &pos.x, &pos.y, &pos.z);		// 比較用テキストにPOSを代入
						}
						else if (strcmp(cHeadText, "END_PRISONERSET") == 0)
						{
							// 捕虜の生成
							m_pPrisoner.emplace_back(CPrisoner::Create());
							// 位置の設定
							m_pPrisoner[m_pPrisoner.size() - 1]->SetPosition(pos);
						}
					}
				}
			}
		}
		// ファイルを閉じる
		fclose(pFile);
	}
}

// =====================================================================================================================================================================
//
// 障害物の配置
//
// =====================================================================================================================================================================
void CMap::ObstacleLoad(MAP MapNum)
{
	// ファイルポイント
	FILE *pFile;
	char cReadText[128];			// 文字として読み取る
	char cHeadText[128];			// 比較用
	char cDie[128];					// 不要な文字
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	int nLife = 0;										// 体力
	int nType = 0;										// 種類

	// ファイルを開く
	pFile = fopen(m_ObstacleFileName[MapNum], "r");

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

				// OBSTACLESETが来たら
				if (strcmp(cHeadText, "OBSTACLESET") == 0)
				{
					// END_OBSTACLESETが来るまでループ
					while (strcmp(cHeadText, "END_OBSTACLESET") != 0)
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
						else if (strcmp(cHeadText, "END_OBSTACLESET") == 0)
						{
							// オブジェクトの生成
							m_pObstacle.emplace_back(CObstacle::Create());
							// タイプの代入
							m_pObstacle[m_pObstacle.size() - 1]->SetModelConut(nType);
							// 位置の設定
							m_pObstacle[m_pObstacle.size() - 1]->SetPosition(pos);
							// 体力の設定
							m_pObstacle[m_pObstacle.size() - 1]->SetLife(nLife);
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
		MessageBox(NULL, "障害物のパラメーター読み込み失敗", "警告", MB_ICONWARNING);
	}
}

// =====================================================================================================================================================================
//
// プレイヤー用の戦車の配置
//
// =====================================================================================================================================================================
void CMap::PlayerTankLoad(MAP MapNum)
{
	// ファイルポイント
	FILE *pFile;
	char cReadText[128];			// 文字として読み取る
	char cHeadText[128];			// 比較用
	char cDie[128];					// 不要な文字
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置

	// ファイルを開く
	pFile = fopen(m_PlayerTankFileName[MapNum], "r");

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

															// OBSTACLESETが来たら
				if (strcmp(cHeadText, "PLAYERTANKSET") == 0)
				{
					// END_OBSTACLESETが来るまでループ
					while (strcmp(cHeadText, "END_PLAYERTANKSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
						sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入

						// POSが来たら
						if (strcmp(cHeadText, "POS") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &pos.x, &pos.y, &pos.z);		// 比較用テキストにPOSを代入
						}
						else if (strcmp(cHeadText, "END_PLAYERTANKSET") == 0)
						{
							// オブジェクトの生成
							m_pPlayerTank.emplace_back(CPlayertank::Create());
							// 位置の設定
							m_pPlayerTank[m_pPlayerTank.size() - 1]->SetPosition(pos);
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
		MessageBox(NULL, "プレイヤー戦車のパラメーター読み込み失敗", "警告", MB_ICONWARNING);
	}
}

// =====================================================================================================================================================================
//
// マップの生成
//
// =====================================================================================================================================================================
CMap *CMap::MapCreate(MAP MapNum)
{
	// 変数
	CMap *pMap;

	// メモリの確保
	pMap = new CMap();

	// モデルのロード
	pMap->ModelLoad(MapNum);
	// 敵のロード
	pMap->EnemyLoad(MapNum);
	// 捕虜のロード
	//pMap->PrisonerLoad(MapNum);
	// 障害物のロード
	//pMap->ObstacleLoad(MapNum);
	// プレイヤー戦車のロード
	pMap->PlayerTankLoad(MapNum);

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
// モデルのセーブ
//
// =====================================================================================================================================================================
void CMap::ModelSave(MAP MapNum)
{
	// ファイルポイント
	FILE	*pFile;

	// ファイルを開く
	pFile = fopen(m_MapFileName[MapNum], "w");

	// 開いているとき
	if (pFile != NULL)
	{
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# モデルの配置情報\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# TYPE情報\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	[ 0 ]	床\n");
		fprintf(pFile, "#	[ 1 ]	壁\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");

		fprintf(pFile, "SCRIPT\n\n");

		for (unsigned int nCntModel = 0; nCntModel < m_pModel.size(); nCntModel++)
		{
			// NULLチェック
			if (!m_pModel[nCntModel])
			{
				D3DXVECTOR3 ModelPos = m_pModel[nCntModel]->GetPosition();	// モデルの位置取得

				fprintf(pFile, "MODELSET									# %d\n", nCntModel);
				fprintf(pFile, "	TYPE	= %d\n", m_pModel[nCntModel]->GetType());
				fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", ModelPos.x, ModelPos.y, ModelPos.z);
				fprintf(pFile, "END_MODELSET\n\n");
			}
		}
		fprintf(pFile, "END_SCRIPT\n");

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		// メッセージウィンドウで警告
		MessageBox(NULL, "ファイルが読み込めません", "警告", MB_OK | MB_ICONWARNING);
	}
}

// =====================================================================================================================================================================
//
// 敵のセーブ
//
// =====================================================================================================================================================================
void CMap::EnemySave(MAP MapNum)
{
	// ファイルポイント
	FILE	*pFile;

	// ファイルを開く
	pFile = fopen(m_EnemyFileName[MapNum], "w");

	// 開いているとき
	if (pFile != NULL)
	{
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# 敵の配置情報\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# TYPE情報\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	[ 0 ]	兵士\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");

		fprintf(pFile, "SCRIPT\n\n");

		for (unsigned int nCntEnemy = 0; nCntEnemy < m_pEnemy.size(); nCntEnemy++)
		{
			// NULLチェック
			if (m_pEnemy[nCntEnemy])
			{
				D3DXVECTOR3 EnemyPos = m_pEnemy[nCntEnemy]->GetPosition();	// モデルの位置取得

				fprintf(pFile, "ENEMYSET									# %d\n", nCntEnemy);
				fprintf(pFile, "	TYPE	= %d\n", 0 /*m_pEnemy[nCntEnemy]->GetType()*/);
				fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", EnemyPos.x, EnemyPos.y, EnemyPos.z);
				fprintf(pFile, "	LIFE	= %d\n", m_pEnemy[nCntEnemy]->GetLife());
				fprintf(pFile, "END_ENEMYSET\n\n");
			}
		}
		fprintf(pFile, "END_SCRIPT\n");

		// メッセージウィンドウで表示
		MessageBox(NULL, "敵の配置データをセーブしました", "結果", MB_OK | MB_ICONINFORMATION);

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		// メッセージウィンドウで警告
		MessageBox(NULL, "ファイルが読み込めません", "警告", MB_OK | MB_ICONWARNING);
	}
}

// =====================================================================================================================================================================
//
// 捕虜のセーブ
//
// =====================================================================================================================================================================
void CMap::PrisonerSave(MAP MapNum)
{
	// ファイルポイント
	FILE	*pFile;

	// ファイルを開く
	pFile = fopen(m_PrisonerFileName[MapNum], "w");

	// 開いているとき
	if (pFile != NULL)
	{
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# 捕虜の配置情報\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# TYPE情報\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	[ 0 ]	兵士\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");

		fprintf(pFile, "SCRIPT\n\n");

		for (unsigned int nCntPrisoner = 0; nCntPrisoner < m_pPrisoner.size(); nCntPrisoner++)
		{
			// NULLチェック
			if (m_pPrisoner[nCntPrisoner])
			{
				D3DXVECTOR3 PrisonerPos = m_pPrisoner[nCntPrisoner]->GetPosition();	// モデルの位置取得

				fprintf(pFile, "PRISONERSET									# %d\n", nCntPrisoner);
				fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", PrisonerPos.x, PrisonerPos.y, PrisonerPos.z);
				fprintf(pFile, "END_PRISONERSET\n\n");
			}
		}
		fprintf(pFile, "END_SCRIPT\n");

		// メッセージウィンドウで表示
		MessageBox(NULL, "捕虜の配置データをセーブしました", "結果", MB_OK | MB_ICONINFORMATION);

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		// メッセージウィンドウで警告
		MessageBox(NULL, "ファイルが読み込めません", "警告", MB_OK | MB_ICONWARNING);
	}
}

// =====================================================================================================================================================================
//
// 障害物のセーブ
//
// =====================================================================================================================================================================
void CMap::ObstacleSave(MAP MapNum)
{
	// ファイルポイント
	FILE	*pFile;

	// ファイルを開く
	pFile = fopen(m_ObstacleFileName[MapNum], "w");

	// 開いているとき
	if (pFile != NULL)
	{
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# 障害物の配置情報\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# TYPE情報\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	[ 0 ]	箱\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");

		fprintf(pFile, "SCRIPT\n\n");

		for (unsigned int nCntObstacle = 0; nCntObstacle < m_pObstacle.size(); nCntObstacle++)
		{
			// NULLチェック
			if (m_pObstacle[nCntObstacle])
			{
				D3DXVECTOR3 ObstaclePos = m_pObstacle[nCntObstacle]->GetPosition();	// モデルの位置取得

				fprintf(pFile, "OBSTACLESET									# %d\n", nCntObstacle);
				fprintf(pFile, "	TYPE	= %d\n", m_pObstacle[nCntObstacle]->GetModelCount());
				fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", ObstaclePos.x, ObstaclePos.y, ObstaclePos.z);
				fprintf(pFile, "	LIFE	= %d\n", m_pObstacle[nCntObstacle]->GetLife());
				fprintf(pFile, "END_OBSTACLESET\n\n");
			}
		}
		// メッセージウィンドウで表示
		MessageBox(NULL, "障害物の配置データをセーブしました", "結果", MB_OK | MB_ICONINFORMATION);

		fprintf(pFile, "END_SCRIPT\n");

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		// メッセージウィンドウで警告
		MessageBox(NULL, "ファイルが読み込めません", "警告", MB_OK | MB_ICONWARNING);
	}
}

void CMap::PlayerTankSave(MAP MapNum)
{
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
		// 障害物のセーブ
		ObstacleSave(m_MapNum);
		// 捕虜のセーブ
		PrisonerSave(m_MapNum);
		// 敵のセーブ
		EnemySave(m_MapNum);
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

			// オブジェクトの位置の設定
			m_pObstacle[nNowSelect]->SetPosition(D3DXVECTOR3((float)x, (float)y, (float)z));
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
		ObstacleSave(m_MapNum);
	}

	// 全てセーブ
	AllSaveButton();

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
		PrisonerSave(m_MapNum);
	}

	// 全てセーブ
	AllSaveButton();

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
		EnemySave(m_MapNum);
	}

	// 全てセーブ
	AllSaveButton();

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
		//// コンボボックス
		//if (EnemyComboBox(nPlayerTankType))
		//{
		//	// NULLチェック
		//	if (m_pPlayerTank[nNowSelect])
		//	{
		//		// 敵の種類の取得
		//		CModel::PLAYERTANK_TYPE PlayerTankType = (CModel::OBSTACLE_TYPE)m_pPlayerTank[nNowSelect]->GetModelCount();

		//		// 前回と違うとき
		//		if (PlayerTankType != nPlayerTankType)
		//		{
		//			// 種類代入
		//			PlayerTankType = (CModel::PLAYERTANK_TYPE)nPlayerTankType;
		//			// 敵のタイプの設定
		//			m_pPlayerTank[nNowSelect]->SetModelConut(PlayerTankType);
		//		}
		//	}
		//}

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
		// 敵のセーブ
		EnemySave(m_MapNum);
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
// プレイヤーの戦車のコンボボックス
//
// =====================================================================================================================================================================
bool CMap::PlayerTankComboBox(int & nType)
{
	return false;
}

// =====================================================================================================================================================================
//
// 死亡フラグ確認関数
//
// =====================================================================================================================================================================
void CMap::UpdateDieFlag()
{
	for (size_t nCnt = 0; nCnt < m_pEnemy.size(); nCnt++)
	{
		if (m_pEnemy[nCnt]->GetDieFlag())
		{
			m_pEnemy[nCnt]->Rerease();
			m_pEnemy[nCnt] = nullptr;
			m_pEnemy.erase(m_pEnemy.begin() + nCnt);
		}
	}

	for (size_t nCnt = 0; nCnt < m_pObstacle.size(); nCnt++)
	{
		if (m_pObstacle[nCnt]->GetDieFlag())
		{
			m_pObstacle[nCnt]->Rerease();
			m_pObstacle[nCnt] = nullptr;
			m_pObstacle.erase(m_pObstacle.begin() + nCnt);
		}
	}

	for (size_t nCnt = 0; nCnt < m_pPrisoner.size(); nCnt++)
	{
		if (m_pPrisoner[nCnt]->GetDieFlag())
		{
			m_pPrisoner[nCnt]->Rerease();
			m_pPrisoner[nCnt] = nullptr;
			m_pPrisoner.erase(m_pPrisoner.begin() + nCnt);
		}
	}

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
