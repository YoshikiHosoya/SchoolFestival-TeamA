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

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
std::vector<CModel*>	CMap::m_pModel = {};
std::vector<CEnemy*>	CMap::m_pEnemy = {};

// =====================================================================================================================================================================
// テキストファイル名
// =====================================================================================================================================================================
char *CMap::m_FileName[MAPOBJECT_MAX] =
{
	{ "data/Load/testMap.txt" },
	{ "data/Load/Enemy.txt" },
};

// =====================================================================================================================================================================
//
// モデルのロード
//
// =====================================================================================================================================================================
void CMap::ModelLoad()
{
	// ファイルポイント
	FILE *pFile;

	char cReadText[128];			// 文字として読み取る
	char cHeadText[128];			// 比較用
	char cDie[128];					// 不要な文字
	static int nCntModel = 0;		// 番号
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	CModel::CREATE_MAP_MODEL ModelCount = CModel::MODEL_MAP_BLOCK;		// 種類

	// ファイルを開く
	pFile = fopen(m_FileName[MAPOBJECT_MODEL], "r");

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
							if (m_pModel[nCntModel])
							{
								// オブジェクトの生成
								m_pModel.emplace_back(CModel::Create(CModel::MAP_MODEL, ModelCount));
								// 位置の設定
								m_pModel[m_pModel.size() - 1]->SetPosition(pos);
							}
						}
					}
					// カウントアップ
					nCntModel++;
				}
			}
		}
		// ファイルを閉じる
		fclose(pFile);
	}
	nCntModel = 0;
}

// =====================================================================================================================================================================
//
// エネミーのロード
//
// =====================================================================================================================================================================
void CMap::EnemyLoad()
{
	// ファイルポイント
	FILE *pFile;

	char cReadText[128];			// 文字として読み取る
	char cHeadText[128];			// 比較用
	char cDie[128];					// 不要な文字
	static int nCntEnemy = 0;		// 番号
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	//CEnemy::TYPE type = CEnemy::NONE;		// 種類
	int nType = 0;

	// ファイルを開く
	pFile = fopen(m_FileName[MAPOBJECT_ENEMY], "r");

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
						else if (strcmp(cHeadText, "END_ENEMYSET") == 0)
						{
							if (m_pEnemy[nCntEnemy])
							{
								// オブジェクトの生成
								m_pEnemy.emplace_back(CEnemy::Create());
								// 位置の設定
								m_pEnemy[m_pEnemy.size() - 1]->SetPosition(pos);
							}
						}
					}
					// カウントアップ
					nCntEnemy++;
				}
			}
		}
		// ファイルを閉じる
		fclose(pFile);
	}
	nCntEnemy = 0;
}

// =====================================================================================================================================================================
//
// モデルのセーブ
//
// =====================================================================================================================================================================
void CMap::ModelSave()
{
	// ファイルポイント
	FILE	*pFile;

	// ファイルを開く
	pFile = fopen(m_FileName[MAPOBJECT_MODEL], "w");

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
		MessageBox(NULL, "ファイルが開かれています", "警告", MB_OK | MB_ICONWARNING);
	}
}

// =====================================================================================================================================================================
//
// 敵のセーブ
//
// =====================================================================================================================================================================
void CMap::EnemySave()
{
	// ファイルポイント
	FILE	*pFile;

	// ファイルを開く
	pFile = fopen(m_FileName[MAPOBJECT_ENEMY], "w");

	// 開いているとき
	if (pFile != NULL)
	{
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# 敵の配置情報\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# TYPE情報\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	[ 0 ]	床\n");
		fprintf(pFile, "#	[ 1 ]	壁\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");

		fprintf(pFile, "SCRIPT\n\n");

		for (unsigned int nCntEnemy = 0; nCntEnemy < m_pEnemy.size(); nCntEnemy++)
		{
			// NULLチェック
			if (!m_pEnemy[nCntEnemy])
			{
				D3DXVECTOR3 EnemyPos = m_pEnemy[nCntEnemy]->GetPosition();	// モデルの位置取得

				fprintf(pFile, "ENEMYSET									# %d\n", nCntEnemy);
				fprintf(pFile, "	TYPE	= %d\n", 0 /*m_pEnemy[nCntEnemy]->GetType()*/);
				fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", EnemyPos.x, EnemyPos.y, EnemyPos.z);
				fprintf(pFile, "END_ENEMYSETSET\n\n");
			}
		}
		fprintf(pFile, "END_SCRIPT\n");

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		// メッセージウィンドウで警告
		MessageBox(NULL, "ファイルが開かれています", "警告", MB_OK | MB_ICONWARNING);
	}
}

// =====================================================================================================================================================================
//
// モデルの取得
//
// =====================================================================================================================================================================
CModel * CMap::GetModel(int nCnt)
{
	return m_pModel[nCnt];
}

// =====================================================================================================================================================================
//
// 敵の取得
//
// =====================================================================================================================================================================
CEnemy * CMap::GetEnemy(int nCnt)
{
	return m_pEnemy[nCnt];
}