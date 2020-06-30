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

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================

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
	{ "data/Load/Enemy/Enemy_Map01.txt" },
	{ "data/Load/Enemy/Enemy_Map01.txt" },
};

char *CMap::m_ObstacleFileName[MAP_MAX] =
{
	{ "data/Load/Map/Obstacle_Box.txt" },
	{ "data/Load/Map/Obstacle_Box.txt" },
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
void CMap::ModelLoad(int nCnt)
{
	// ファイルポイント
	FILE *pFile;

	char cReadText[128];			// 文字として読み取る
	char cHeadText[128];			// 比較用
	char cDie[128];					// 不要な文字
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	CModel::CREATE_MAP_MODEL ModelCount = CModel::MODEL_MAP_BLOCK;		// 種類

	// ファイルを開く
	pFile = fopen(m_MapFileName[nCnt], "r");

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
void CMap::EnemyLoad(int nCnt)
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
	pFile = fopen(m_EnemyFileName[nCnt], "r");

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
// 障害物の配置
//
// =====================================================================================================================================================================
void CMap::ObstacleLoad(int nCnt)
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
	pFile = fopen(m_ObstacleFileName[nCnt], "r");

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
				if (strcmp(cHeadText, "OBSTACLESET") == 0)
				{
					// END_ENEMYSETが来るまでループ
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
							m_pObstacle[m_pObstacle.size() - 1]->SetType(nType);
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
// マップのデバッグ配置
//
// =====================================================================================================================================================================
void CMap::DebugMap()
{
	//CKeyboard *key;
	//key = CManager::GetInputKeyboard();
	////プレイヤー座標の取得
	//D3DXVECTOR3 pPos;
	//int pState;
	//CScene *pScene;
	//pScene = CScene::GetScene(OBJTYPE_PLAYER);
	//if (pScene != NULL)
	//{
	//	pPos = ((CPlayer*)pScene)->GetPosition();
	//	pState = ((CPlayer*)pScene)->GetDebugState();

	//	if (pState == CPlayer::DEBUG_CREATE_MAP)
	//	{
	//		//モデルタイプを前のモデルに変更
	//		if (key->GetKeyboardTrigger(DIK_1))
	//		{
	//			if (m_type > 0)
	//			{
	//				m_type--;
	//			}
	//		}
	//		//モデルタイプを次のモデルに変更
	//		if (key->GetKeyboardTrigger(DIK_2))
	//		{
	//			if (m_type < CModel::MODEL_MAP_MAX - 1)
	//			{
	//				m_type++;
	//			}
	//		}
	//		//モデルの設置
	//		if (key->GetKeyboardTrigger(DIK_RETURN))
	//		{
	//			//末尾に要素を追加する
	//			m_vec.emplace_back(CModel::Create(CModel::MAP_MODEL, m_type));
	//			m_vec[m_vec.size() - 1]->SetPosition(D3DXVECTOR3(pPos.x, pPos.y, pPos.z));
	//			m_vec[m_vec.size() - 1]->SetSize(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	//		}
	//		//モデルの位置をセーブ
	//		if (key->GetKeyboardTrigger(DIK_F9))
	//		{
	//			Save();
	//		}
	//		//モデルのロード
	//		if (key->GetKeyboardTrigger(DIK_F7))
	//		{
	//			Load(0);
	//		}

	//		if (m_map.size() > 0)
	//		{
	//			m_map[m_map.size() - 1]->SetPosition(D3DXVECTOR3(pPos.x, pPos.y, pPos.z));
	//			m_map[m_map.size() - 1]->SetSize(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	//			m_map[0]->SetType(m_type);
	//		}
	//		CDebugProc::Print("[設置の操作]\n");
	//		CDebugProc::Print("マップのセーブ    :[F9]\n");
	//		CDebugProc::Print("マップのロード     :[F7]\n");
	//		CDebugProc::Print("モデルの切り替え:[1]:[2]\n");
	//		CDebugProc::Print("モデルの移動      :[0]\n");
	//		CDebugProc::Print("モデルの削除      :[3]\n");
	//		CDebugProc::Print("モデルの設置      :[ENTER]\n");
	//		CDebugProc::Print("上昇                   :[SPACE]\n");
	//		CDebugProc::Print("下向                   :[LCTRL]\n");
	//	}
	//	//if (pState == CPlayer::DEBUG_CREATE_ENEMY)
	//	//{
	//	//	if (m_type > CEnemy::ENEMY_TYPE_MAX - 1)
	//	//	{
	//	//		m_type = 0;
	//	//	}
	//	//	//モデルタイプを前のモデルに変更
	//	//	if (key->GetKeyboardTrigger(DIK_1))
	//	//	{
	//	//		if (m_type > 0)
	//	//		{
	//	//			m_type--;
	//	//		}
	//	//	}
	//	//	//モデルタイプを次のモデルに変更
	//	//	if (key->GetKeyboardTrigger(DIK_2))
	//	//	{
	//	//		if (m_type < CEnemy::ENEMY_TYPE_MAX - 1)
	//	//		{
	//	//			m_type++;
	//	//		}
	//	//	}
	//	//	if (key->GetKeyboardTrigger(DIK_RETURN))
	//	//	{
	//	//		//末尾に要素を追加する
	//	//		m_Enemy.emplace_back(CEnemy::Create(m_type));
	//	//		m_Enemy[m_Enemy.size() - 1]->SetPosition(D3DXVECTOR3(pPos.x, pPos.y - 50, pPos.z));
	//	//	}
	//	//	//モデルの位置をセーブ
	//	//	if (key->GetKeyboardTrigger(DIK_F9))
	//	//	{
	//	//		Save();
	//	//	}
	//	//	CDebugProc::Print("[設置の操作]\n");
	//	//	CDebugProc::Print("マップのセーブ    :[F9]\n");
	//	//	CDebugProc::Print("エネミーの切り替え:[1]:[2]\n");
	//	//	CDebugProc::Print("エネミーの設置      :[ENTER]\n");
	//	//	CDebugProc::Print("上昇                   :[SPACE]\n");
	//	//	CDebugProc::Print("下向                   :[LCTRL]\n");
	//	//	CDebugProc::Print("エネミータイプ%d\n", m_type);
	//	//}
	//}
	//if (m_Enemy.size() == 0)
	//{
	//	for (unsigned int nCnt = 0; nCnt < m_vec.size(); nCnt++)
	//	{
	//		if (m_vec[nCnt]->GetType() == CModel::MODEL_MAP_BLOCK02)
	//		{
	//			m_vec.erase(m_vec.begin() + nCnt);//最初から[nCnt]番目を消去
	//		}
	//	}
	//}
	//else
	//{
	//	CDebugProc::Print("[F2]でマップエディタ\n");
	//}
	////for (unsigned int nCnt = 0; nCnt < m_Enemy.size(); nCnt++)
	////{
	////	if (m_Enemy[nCnt] != nullptr)
	////	{
	////		if (m_Enemy[nCnt]->GetLife() <= 0)
	////		{
	////			m_Enemy[nCnt]->Uninit();
	////			m_Enemy[nCnt]->Rerease();
	////			m_Enemy.erase(m_Enemy.begin() + nCnt);
	////		}
	////	}
	////}
	//Collision();
}

// =====================================================================================================================================================================
//
// モデルの最大数取得
//
// =====================================================================================================================================================================
CMap *CMap::MapCreate(int nCnt)
{
	// 変数
	CMap *pMap;

	// メモリの確保
	pMap = new CMap();

	// モデルのロード
	pMap->ModelLoad(nCnt);
	// 敵のロード
	pMap->EnemyLoad(nCnt);
	// 障害物のロード
	pMap->ObstacleLoad(nCnt);

	return pMap;
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
void CMap::ModelSave()
{
	// ファイルポイント
	FILE	*pFile;

	// ファイルを開く
	pFile = fopen(m_MapFileName[MAP_1], "w");

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
	pFile = fopen(m_EnemyFileName[MAP_1], "w");

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
			if (!m_pEnemy[nCntEnemy])
			{
				D3DXVECTOR3 EnemyPos = m_pEnemy[nCntEnemy]->GetPosition();	// モデルの位置取得

				fprintf(pFile, "ENEMYSET									# %d\n", nCntEnemy);
				fprintf(pFile, "	TYPE	= %d\n", 0 /*m_pEnemy[nCntEnemy]->GetType()*/);
				fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", EnemyPos.x, EnemyPos.y, EnemyPos.z);
				fprintf(pFile, "	LIFE	= %d\n", m_pEnemy[nCntEnemy]->GetLife());
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
}
