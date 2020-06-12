// =====================================================================================================================================================================
//
// マップの処理 [map.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "map.h"			// インクルードファイル
#include "debugproc.h"
#include "manager.h"
#include "game.h"
#include "objectmodel.h"
#include "effect.h"
#include "item.h"
#include "object2D.h"
#include "slope.h"

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define MAP_FILE_NAME00			("data/FILE/MAP/map.txt")		// マップテキスト

#define MAP2D_FILE_NAME00		("data/FILE/MAP/2Dmap.txt")		// 2Dオブジェクトテキスト

#define ITEM_FILE_NAME00		("data/FILE/MAP/item.txt")		// アイテムテキスト

#define SLOPE_FILE_NAME00		("data/FILE/MAP/sloppe.txt")	// 坂のテキスト

#define OBJECT2D_POS_X			(-148)							// 2DオブジェクトのXのPos

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
CObjectModel	*CMap::m_pObject[MAX_OBJECT]	= {};	// オブジェクト情報
CObject2D		*CMap::m_pObject2D[MAX_OBJECT2D]	= {};	// 2Dオブジェクト情報
CItem			*CMap::m_pItem[MAX_ITEM]		= {};	// アイテム情報
CSlope			*CMap::m_pSlope[MAX_SLOPE]		= {};	// 坂の情報

// =====================================================================================================================================================================
//
// オブジェクトの当たり判定
//
// =====================================================================================================================================================================
bool CMap::CollisionObjectAll(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pSize)
{
	// 変数宣言
	bool bLand = false;						// 着地フラグ

	// オブジェクトモデルの情報
	CObjectModel *pObject;

	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_pObject[nCntObject] != NULL)
		{
			if (m_pObject[nCntObject]->CollisionObject(pPos, pPosOld, pMove, pSize, &pObject))
			{
				bLand = true;
			}
		}
	}
	return bLand;
}

// =====================================================================================================================================================================
//
// 2Dオブジェクトの当たり判定
//
// =====================================================================================================================================================================
bool CMap::CollisionObject2DAll(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove, D3DXVECTOR3 * pSize)
{
	bool bLand = false;

	// オブジェクトモデルの情報
	CObject2D *pObject2D;

	for (int nCntObject2D = 0; nCntObject2D < MAX_OBJECT2D; nCntObject2D++)
	{
		if (m_pObject2D[nCntObject2D] != NULL)
		{
			if (m_pObject2D[nCntObject2D]->CollisionObject2D(pPos, pPosOld, pMove, pSize, &pObject2D))
			{
				bLand = true;
			}
		}
	}
	return bLand;
}

// =====================================================================================================================================================================
//
// 坂の高さの取得
//
// =====================================================================================================================================================================
bool CMap::GetHeightSlopeAll(D3DXVECTOR3 &pos, D3DXVECTOR3 &move)
{
	bool bLand = false;

	for (int nCntSlope = 0; nCntSlope < MAX_SLOPE; nCntSlope++)
	{
		if (m_pSlope[nCntSlope] != NULL)
		{
			// 高さの取得
			if (m_pSlope[nCntSlope]->GetHeight(pos))
			{
				CDebugProc::Print("pos %.2f,%.2f %.2f\n", pos.x, pos.y, pos.z);
				CDebugProc::Print("move %.2f,%.2f %.2f\n", move.x, move.y, move.z);

				move.y = 0.0f;
				bLand = true;
			}
		}
	}
	return bLand;
}

// =====================================================================================================================================================================
//
// マップの更新
//
// =====================================================================================================================================================================
void CMap::MapUpdate()
{
	// オブジェクトのセット
	ObjectSet();

	// 2Dオブジェクトのセット
	Object2DSet();

	// アイテムのセット
	ItemSet();

	// 坂のセット
	SlopeSet();
}

// =====================================================================================================================================================================
//
// マップの読み込み
//
// =====================================================================================================================================================================
void CMap::ObjectLoad()
{
	// ファイルポイント
	FILE *pFile;

	char cReadText[128];			// 文字として読み取る
	char cHeadText[128];			// 比較用
	char cDie[128];					// 不要な文字
	static int nCntObject = 0;		// 番号
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	CObjectModel::OBJECTTYPE type = CObjectModel::OBJECTTYPE_NONE;						// 種類

	// ファイルを開く
	pFile = fopen(MAP_FILE_NAME00, "r");

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
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &type);		// 比較用テキストにTYPEを代入
						}
						// POSが来たら
						else if (strcmp(cHeadText, "POS") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &pos.x, &pos.y, &pos.z);		// 比較用テキストにPOSを代入
						}
						else if (strcmp(cHeadText, "END_MODELSET") == 0)
						{
							if (m_pObject[nCntObject] == NULL)
							{
								// オブジェクトの生成
								m_pObject[nCntObject] = CObjectModel::Create(pos, type);
							}
						}
					}
					// カウントアップ
					nCntObject++;
				}
			}
		}
		// ファイルを閉じる
		fclose(pFile);
	}
	nCntObject = 0;
}

// =====================================================================================================================================================================
//
// 2Dオブジェクトの読み込み
//
// =====================================================================================================================================================================
void CMap::Object2DLoad(void)
{
	// ファイルポイント
	FILE *pFile;

	char cReadText[128];			// 文字として読み取る
	char cHeadText[128];			// 比較用
	char cDie[128];					// 不要な文字
	static int nCntObject2D = 0;	// 番号
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	CObject2D::OBJECT_2D_TYPE type = CObject2D::OBJECT_2D_TYPE_NONE;		// 種類

	// ファイルを開く
	pFile = fopen(MAP2D_FILE_NAME00, "r");

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
				if (strcmp(cHeadText, "2DOBJECTSET") == 0)
				{
					// END_MODELSETが来るまでループ
					while (strcmp(cHeadText, "END_2DOBJECTSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
						sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入

						// TYPEが来たら
						if (strcmp(cHeadText, "TYPE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &type);		// 比較用テキストにTYPEを代入
						}
						// POSが来たら
						else if (strcmp(cHeadText, "POS") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &pos.x, &pos.y, &pos.z);		// 比較用テキストにPOSを代入
						}
						else if (strcmp(cHeadText, "END_2DOBJECTSET") == 0)
						{
							if (m_pObject2D[nCntObject2D] == NULL)
							{
								// 2Dオブジェクトの生成
								m_pObject2D[nCntObject2D] = CObject2D::Create(pos, type);
							}
						}
					}
					// カウントアップ
					nCntObject2D++;
				}
			}
		}
		// ファイルを閉じる
		fclose(pFile);
	}
	nCntObject2D = 0;
}

// =====================================================================================================================================================================
//
// アイテムの読み込み
//
// =====================================================================================================================================================================
void CMap::ItemLoad(void)
{
	// ファイルポイント
	FILE *pFile;

	char cReadText[128];			// 文字として読み取る
	char cHeadText[128];			// 比較用
	char cDie[128];					// 不要な文字
	static int nCntItem = 0;		// 番号
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	CItem::ITEMTYPE type = CItem::ITEMTYPE_NONE;		// 種類

	// ファイルを開く
	pFile = fopen(ITEM_FILE_NAME00, "r");

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

				// ITEMSETが来たら
				if (strcmp(cHeadText, "ITEMSET") == 0)
				{
					// END_ITEMSETが来るまでループ
					while (strcmp(cHeadText, "END_ITEMSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
						sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入

						// TYPEが来たら
						if (strcmp(cHeadText, "TYPE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &type);		// 比較用テキストにTYPEを代入
						}
						// POSが来たら
						else if (strcmp(cHeadText, "POS") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &pos.x, &pos.y, &pos.z);		// 比較用テキストにPOSを代入
						}
						else if (strcmp(cHeadText, "END_ITEMSET") == 0)
						{
							if (m_pItem[nCntItem] == NULL)
							{
								// オブジェクトの生成
								m_pItem[nCntItem] = CItem::Create(pos, type);
							}
						}
					}
					// カウントアップ
					nCntItem++;
				}
			}
		}
		// ファイルを閉じる
		fclose(pFile);
	}
	nCntItem = 0;
}

// =====================================================================================================================================================================
//
// 坂の読み込み
//
// =====================================================================================================================================================================
void CMap::SlopeLoad(void)
{
	// ファイルポイント
	FILE *pFile;

	char cReadText[128];			// 文字として読み取る
	char cHeadText[128];			// 比較用
	char cDie[128];					// 不要な文字
	static int nCntSlope	 = 0;	// 番号
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	float fSlope = 0.0f;								// 斜面

	// ファイルを開く
	pFile = fopen(SLOPE_FILE_NAME00, "r");

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
				if (strcmp(cHeadText, "SLOPESET") == 0)
				{
					// END_MODELSETが来るまでループ
					while (strcmp(cHeadText, "END_SLOPESET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
						sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入

						// SLOPEが来たら
						if (strcmp(cHeadText, "SLOPE") == 0)
						{
							sscanf(cReadText, "%s %s %f", &cDie, &cDie, &fSlope);		// 比較用テキストにSLOPEを代入
						}
						// POSが来たら
						else if (strcmp(cHeadText, "POS") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &pos.x, &pos.y, &pos.z);		// 比較用テキストにPOSを代入
						}
						else if (strcmp(cHeadText, "END_SLOPESET") == 0)
						{
							if (m_pSlope[nCntSlope] == NULL)
							{
								// 2Dオブジェクトの生成
								m_pSlope[nCntSlope] = CSlope::Create(pos, fSlope);
							}
						}
					}
					// カウントアップ
					nCntSlope++;
				}
			}
		}
	}
	nCntSlope = 0;
}

// =====================================================================================================================================================================
//
// マップの解放
//
// =====================================================================================================================================================================
void CMap::ReleaseMap()
{
	// 3Dオブジェクト
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_pObject[nCntObject] != NULL)
		{
			m_pObject[nCntObject] = NULL;
		}
	}

	// 2Dオブジェクト
	for (int nCntObject2D = 0; nCntObject2D < MAX_OBJECT2D; nCntObject2D++)
	{
		if (m_pObject2D[nCntObject2D] != NULL)
		{
			m_pObject2D[nCntObject2D] = NULL;
		}
	}

	// アイテム
	for (int nCntItem = 0; nCntItem < MAX_OBJECT2D; nCntItem++)
	{
		if (m_pItem[nCntItem] != NULL)
		{
			m_pItem[nCntItem] = NULL;
		}
	}

	// 坂
	for (int nCntSlope = 0; nCntSlope < MAX_OBJECT2D; nCntSlope++)
	{
		if (m_pSlope[nCntSlope] != NULL)
		{
			m_pSlope[nCntSlope] = NULL;
		}
	}
}

// =====================================================================================================================================================================
//
// 試験的マップの配置
//
// =====================================================================================================================================================================
void CMap::SetProvisionalMap(void)
{
	m_pSlope[0] = CSlope::Create(D3DXVECTOR3(0.0f, 200.0f, 1000.0f), 30);
	m_pSlope[1] = CSlope::Create(D3DXVECTOR3(0.0f, 150.0f, 500.0f), -30);
}

// =====================================================================================================================================================================
//
// マップの書き込み
//
// =====================================================================================================================================================================
void CMap::ObjectSave()
{
	// ファイルポイント
	FILE	*pFile;

	// ファイルを開く
	pFile = fopen(MAP_FILE_NAME00, "w");

	// 開いているとき
	if (pFile != NULL)
	{
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# オブジェクトの配置情報\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# TYPE情報\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	[ 0 ]	石\n");
		fprintf(pFile, "#	[ 1 ]	箱\n");
		fprintf(pFile, "#	[ 2 ]	地面 ( 大\n");
		fprintf(pFile, "#	[ 3 ]	地面 ( 中\n");
		fprintf(pFile, "#	[ 4 ]	地面 ( 小\n");
		fprintf(pFile, "#	[ 5 ]	間欠泉\n");
		fprintf(pFile, "#	[ 6 ]	足場\n");
		fprintf(pFile, "#	[ 7 ]	2Dでも当たる足場\n");
		fprintf(pFile, "#	[ 8 ]	動く足場\n");
		fprintf(pFile, "#	[ 9 ]	壁\n");
		fprintf(pFile, "#	[ 10 ]	地面 (ハーフ\n");
		fprintf(pFile, "#	[ 11 ]	看板 (落ちる\n");
		fprintf(pFile, "#	[ 12 ]	看板 (ジャンプ\n");
		fprintf(pFile, "#	[ 13 ]	看板 (間欠泉\n");
		fprintf(pFile, "#	[ 14 ]	看板 (カメラ切替え\n");
		fprintf(pFile, "#	[ 15 ]	看板 (2Dでも乗れる\n");
		fprintf(pFile, "#	[ 16 ]	看板 (3Dでしか乗れない\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");

		fprintf(pFile, "SCRIPT\n\n");

		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			// NULLチェック
			if (m_pObject[nCntObject] != NULL)
			{
				D3DXVECTOR3 ObjectPos = m_pObject[nCntObject]->GetPos();	// オブジェクトの位置取得

				fprintf(pFile, "MODELSET									# %d\n", nCntObject);

				fprintf(pFile, "	TYPE	= %d\n", m_pObject[nCntObject]->GetObjectType());
				fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", ObjectPos.x, ObjectPos.y, ObjectPos.z);

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
// 2Dオブジェクトの書き込み
//
// =====================================================================================================================================================================
void CMap::Object2DSave(void)
{
	// ファイルポイント
	FILE	*pFile;

	// ファイルを開く
	pFile = fopen(MAP2D_FILE_NAME00, "w");

	// 開いているとき
	if (pFile != NULL)
	{
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# 2Dオブジェクトの配置情報\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# TYPE情報\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	[ 0 ]	床\n");
		fprintf(pFile, "#	[ 1 ]	壁\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");

		fprintf(pFile, "SCRIPT\n\n");

		for (int nCntObject2D = 0; nCntObject2D < MAX_OBJECT2D; nCntObject2D++)
		{
			// NULLチェック
			if (m_pObject2D[nCntObject2D] != NULL)
			{
				D3DXVECTOR3 Object2DPos = m_pObject2D[nCntObject2D]->GetPos();	// 2Dオブジェクトの位置取得

				fprintf(pFile, "2DOBJECTSET									# %d\n", nCntObject2D);

				fprintf(pFile, "	TYPE	= %d\n", m_pObject2D[nCntObject2D]->GetObject2DType());
				fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", Object2DPos.x, Object2DPos.y, Object2DPos.z);

				fprintf(pFile, "END_2DOBJECTSET\n\n");
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
// アイテムの書き込み
//
// =====================================================================================================================================================================
void CMap::ItemSave(void)
{
	// ファイルポイント
	FILE	*pFile;

	// ファイルを開く
	pFile = fopen(ITEM_FILE_NAME00, "w");

	// 開いているとき
	if (pFile != NULL)
	{
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# アイテムの配置情報\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# TYPE情報\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	[ 0 ]	スピードアップ\n");
		fprintf(pFile, "#	[ 1 ]	ダイヤ\n");
		fprintf(pFile, "#	[ 2 ]	宝石\n");
		fprintf(pFile, "#	[ 3 ]	金貨\n");
		fprintf(pFile, "#	[ 4 ]	鍵\n");
		fprintf(pFile, "#	[ 5 ]	1up\n");
		fprintf(pFile, "#	[ 6 ]	財宝\n");
		fprintf(pFile, "#	[ 7 ]	エネルギー\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");

		fprintf(pFile, "SCRIPT\n\n");

		for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
		{
			// NULLチェック
			if (m_pItem[nCntItem] != NULL)
			{
				D3DXVECTOR3 ItemPos = m_pItem[nCntItem]->GetPos();	// アイテムの位置取得

				fprintf(pFile, "ITEMSET									# %d\n", nCntItem);

				fprintf(pFile, "	TYPE	= %d\n", m_pItem[nCntItem]->GetItemType());
				fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", ItemPos.x, ItemPos.y, ItemPos.z);

				fprintf(pFile, "END_ITEMSET\n\n");
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
// 坂の書き込み
//
// =====================================================================================================================================================================
void CMap::SlopeSave(void)
{
	// ファイルポイント
	FILE	*pFile;

	// ファイルを開く
	pFile = fopen(SLOPE_FILE_NAME00, "w");

	// 開いているとき
	if (pFile != NULL)
	{
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# 坂の配置情報\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");

		fprintf(pFile, "SCRIPT\n\n");

		for (int nCntSlope = 0; nCntSlope < MAX_SLOPE; nCntSlope++)
		{
			// NULLチェック
			if (m_pSlope[nCntSlope] != NULL)
			{
				D3DXVECTOR3 SlopePos = m_pSlope[nCntSlope]->GetPos();	// 坂の位置取得

				fprintf(pFile, "SLOPESET									# %d\n", nCntSlope);

				fprintf(pFile, "	SLOPE	= %f\n", m_pSlope[nCntSlope]->GetSlope());
				fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", SlopePos.x, SlopePos.y, SlopePos.z);

				fprintf(pFile, "END_SLOPESET\n\n");
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
// オブジェクトのセット
//
// =====================================================================================================================================================================
void CMap::ObjectSet(void)
{
	static int nObjectType = 0;		// オブジェクトの種類
	static int nNowSelect = -1;		// 現在選択しているオブジェクト番号
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置

	CEffect *pEffect = CManager::GetGame()->GetEffect();	// エフェクト情報取得

	// オブジェクトウィンドウ
	ImGui::Begin("Object", nullptr, ImGuiWindowFlags_MenuBar);

	// ファイル (セーブ・ロード)
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save"))
			{
				// オブジェクトの書き込み
				ObjectSave();
			}
			if (ImGui::MenuItem("Load"))
			{
				// オブジェクトの読み込み
				ObjectLoad();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	// オブジェクトのコンボボックス
	if (CLibrary::SetObjectComboBox(nObjectType))
	{
		// NULLチェック
		if (m_pObject[nNowSelect] != NULL)
		{
			// オブジェクトの種類の取得
			CObjectModel::OBJECTTYPE ObjectType = m_pObject[nNowSelect]->GetObjectType();

			// 前回と違うとき
			if (ObjectType != nObjectType)
			{
				ObjectType = (CObjectModel::OBJECTTYPE)nObjectType;	// 代入

				// オブジェクトタイプの設定
				m_pObject[nNowSelect]->SetObjectType(ObjectType);
			}
		}
	}

	// オブジェクト番号の選択
	ImGui::InputInt("nowSelect", &nNowSelect, 1, 20, 0);

	// 範囲制限
	if (nNowSelect <= -1)
	{
		nNowSelect = -1;
	}
	else if (nNowSelect >= 0)
	{
		// NULLチェック
		if (m_pObject[nNowSelect] != NULL)
		{
			// 現在地
			int x = (int)m_pObject[nNowSelect]->GetPos().x,
				y = (int)m_pObject[nNowSelect]->GetPos().y,
				z = (int)m_pObject[nNowSelect]->GetPos().z;

			// オブジェクトの移動
			ImGui::DragInt("X", &x);
			ImGui::DragInt("Y", &y);
			ImGui::DragInt("Z", &z);

			// オブジェクトの位置の設定
			m_pObject[nNowSelect]->SetPos(D3DXVECTOR3((float)x, (float)y, (float)z));

			if (pEffect != NULL)
			{
				// エフェクトの位置の設定
				pEffect->SetPos(D3DXVECTOR3((float)x, (float)y + 50.0f, (float)z));
			}
		}
	}
	// オブジェクトの生成
	if (ImGui::Button("Crate"))
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_pObject[nCntObject] == NULL)
			{
				// オブジェクトの生成
				m_pObject[nCntObject] = CObjectModel::Create(pos, (CObjectModel::OBJECTTYPE)nObjectType);
				break;
			}
		}
	}

	ImGui::End();
}

// =====================================================================================================================================================================
//
// 2Dオブジェクトのセット
//
// =====================================================================================================================================================================
void CMap::Object2DSet(void)
{
	static int nObject2DType = 0;		// 2Dオブジェクトの種類
	static int nNowSelect = -1;			// 現在選択しているアイテム番号
	D3DXVECTOR3 pos = D3DXVECTOR3(OBJECT2D_POS_X, 0.0f, 0.0f);	// 位置

	CEffect *pEffect = CManager::GetGame()->GetEffect();	// エフェクト情報取得

	// 2Dオブジェクトウィンドウ
	ImGui::Begin("Object2D", nullptr, ImGuiWindowFlags_MenuBar);

	// ファイル (セーブ・ロード)
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save"))
			{
				// 2Dオブジェクトの書き込み
				Object2DSave();
			}
			if (ImGui::MenuItem("Load"))
			{
				// 2Dオブジェクトの読み込み
				Object2DLoad();
			}

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	// 2Dオブジェクトのコンボボックス
	if (CLibrary::SetObject2DComboBox(nObject2DType))
	{
		// NULLチェック
		if (m_pObject2D[nNowSelect] != NULL)
		{
			// 2Dオブジェクトの種類の取得
			CObject2D::OBJECT_2D_TYPE ObjectType = m_pObject2D[nNowSelect]->GetObject2DType();

			// 前回と違うとき
			if (ObjectType != nObject2DType)
			{
				ObjectType = (CObject2D::OBJECT_2D_TYPE)nObject2DType;	// 代入

				// 2Dオブジェクトタイプの設定
				m_pObject2D[nNowSelect]->SetObject2DType(ObjectType);
			}
		}
	}

	// 2Dオブジェクト番号の選択
	ImGui::InputInt("nowSelect", &nNowSelect, 1, 20, 0);

	// 範囲制限
	if (nNowSelect <= -1)
	{
		nNowSelect = -1;
	}
	else if (nNowSelect >= 0)
	{
		// NULLチェック
		if (m_pObject2D[nNowSelect] != NULL)
		{
			// 現在地
			int x = (int)m_pObject2D[nNowSelect]->GetPos().x,
				y = (int)m_pObject2D[nNowSelect]->GetPos().y,
				z = (int)m_pObject2D[nNowSelect]->GetPos().z;

			// 2Dオブジェクトの移動
			ImGui::DragInt("X", &x);
			ImGui::DragInt("Y", &y);
			ImGui::DragInt("Z", &z);

			// 2Dオブジェクトの位置の設定
			m_pObject2D[nNowSelect]->SetPos(D3DXVECTOR3((float)x, (float)y, (float)z));

			if (pEffect != NULL)
			{
				// エフェクトの位置の設定
				pEffect->SetPos(D3DXVECTOR3((float)x, (float)y + 0.0f, (float)z));
			}
		}
	}
	// 2Dオブジェクトの生成
	if (ImGui::Button("Crate"))
	{
		for (int nCntObject2D = 0; nCntObject2D < MAX_OBJECT2D; nCntObject2D++)
		{
			if (m_pObject2D[nCntObject2D] == NULL)
			{
				// 2Dオブジェクトの生成
				m_pObject2D[nCntObject2D] = CObject2D::Create(pos, (CObject2D::OBJECT_2D_TYPE)nObject2DType);
				break;
			}
		}
	}
	ImGui::End();
}

// =====================================================================================================================================================================
//
// アイテムのセット
//
// =====================================================================================================================================================================
void CMap::ItemSet(void)
{
	static int nItemType = 0;		// アイテムの種類
	static int nNowSelect = -1;		// 現在選択しているアイテム番号
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置

	CEffect *pEffect = CManager::GetGame()->GetEffect();	// エフェクト情報取得

	// アイテムウィンドウ
	ImGui::Begin("Item", nullptr, ImGuiWindowFlags_MenuBar);

	// ファイル (セーブ・ロード)
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save"))
			{
				// オブジェクトの書き込み
				ItemSave();
			}
			if (ImGui::MenuItem("Load"))
			{
				// オブジェクトの読み込み
				ItemLoad();
			}

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	// アイテムのコンボボックス
	if (CLibrary::SetItemComboBox(nItemType))
	{
		// NULLチェック
		if (m_pItem[nNowSelect] != NULL)
		{
			// アイテムの種類の取得
			CItem::ITEMTYPE ItemType = m_pItem[nNowSelect]->GetItemType();

			// 前回と違うとき
			if (ItemType != nItemType)
			{
				ItemType = (CItem::ITEMTYPE)nItemType;	// 代入

				// アイテムタイプの設定
				m_pItem[nNowSelect]->SetItemType(ItemType);
			}
		}
	}

	// アイテム番号の選択
	ImGui::InputInt("nowSelect", &nNowSelect, 1, 20, 0);

	// 範囲制限
	if (nNowSelect <= -1)
	{
		nNowSelect = -1;
	}
	else if (nNowSelect >= 0)
	{
		// NULLチェック
		if (m_pItem[nNowSelect] != NULL)
		{
			// 現在地
			int x = (int)m_pItem[nNowSelect]->GetPos().x,
				y = (int)m_pItem[nNowSelect]->GetPos().y,
				z = (int)m_pItem[nNowSelect]->GetPos().z;

			// アイテムの移動
			ImGui::DragInt("X", &x);
			ImGui::DragInt("Y", &y);
			ImGui::DragInt("Z", &z);

			// アイテムの位置の設定
			m_pItem[nNowSelect]->SetPos(D3DXVECTOR3((float)x, (float)y, (float)z));

			if (pEffect != NULL)
			{
				// エフェクトの位置の設定
				pEffect->SetPos(D3DXVECTOR3((float)x, (float)y + 0.0f, (float)z));
			}
		}
	}
	// アイテムの生成
	if (ImGui::Button("Crate"))
	{
		for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
		{
			if (m_pItem[nCntItem] == NULL)
			{
				// アイテムの生成
				m_pItem[nCntItem] = CItem::Create(pos, (CItem::ITEMTYPE)nItemType);
				break;
			}
		}
	}

	ImGui::End();
}

// =====================================================================================================================================================================
//
// 坂のセット
//
// =====================================================================================================================================================================
void CMap::SlopeSet(void)
{
	static int		fSlope		= 0;								// 坂の斜面
	static int		nNowSelect	= -1;								// 現在選択している坂の番号
	D3DXVECTOR3		pos			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	CEffect			*pEffect	= CManager::GetGame()->GetEffect();	// エフェクト情報取得

	// 坂ウィンドウ
	ImGui::Begin("Slope", nullptr, ImGuiWindowFlags_MenuBar);

	// ファイル (セーブ・ロード)
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save"))
			{
				// オブジェクトの書き込み
				SlopeSave();
			}
			if (ImGui::MenuItem("Load"))
			{
				// オブジェクトの読み込み
				SlopeLoad();
			}

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	// NULLチェック
	if (m_pSlope[nNowSelect] != NULL)
	{
		// 坂の斜面の取得
		fSlope = (int)m_pSlope[nNowSelect]->GetSlope();

		// 坂のコンボボックス
		ImGui::InputInt("Slope", &fSlope, 1, 20, 0);
		{
			// 坂の斜面の設定
			m_pSlope[nNowSelect]->SetSlopSize((float)fSlope);
		}
	}

	// 坂の番号の選択
	ImGui::InputInt("nowSelect", &nNowSelect, 1, 20, 0);

	// 範囲制限
	if (nNowSelect <= -1)
	{
		nNowSelect = -1;
	}
	else if (nNowSelect >= 0)
	{
		// NULLチェック
		if (m_pSlope[nNowSelect] != NULL)
		{
			// 現在地
			int x = (int)m_pSlope[nNowSelect]->GetPos().x,
				y = (int)m_pSlope[nNowSelect]->GetPos().y,
				z = (int)m_pSlope[nNowSelect]->GetPos().z;

			// 坂の移動
			ImGui::DragInt("X", &x);
			ImGui::DragInt("Y", &y);
			ImGui::DragInt("Z", &z);

			// 坂の位置の設定
			m_pSlope[nNowSelect]->SetPos(D3DXVECTOR3((float)x, (float)y, (float)z));

			if (pEffect != NULL)
			{
				// エフェクトの位置の設定
				pEffect->SetPos(D3DXVECTOR3((float)x, (float)y + 0.0f, (float)z));
			}
		}
	}
	// 坂の生成
	if (ImGui::Button("Crate"))
	{
		for (int nCntSlope = 0; nCntSlope < MAX_SLOPE; nCntSlope++)
		{
			if (m_pSlope[nCntSlope] == NULL)
			{
				// オブジェクトの生成
				m_pSlope[nCntSlope] = CSlope::Create(pos, (float)fSlope);
				break;
			}
		}
	}

	ImGui::End();
}