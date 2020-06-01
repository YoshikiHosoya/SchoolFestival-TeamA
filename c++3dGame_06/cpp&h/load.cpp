// ----------------------------------------
//
// ロード情報処理 [load.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------
#include "load.h"

// ----------------------------------------
//
// 静的変数宣言
//
// ----------------------------------------

// ----------------------------------------
// コンストラクタ処理
// ----------------------------------------
CLoad::CLoad()
{
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CLoad::~CLoad()
{
}

// ----------------------------------------
// Unload
// ----------------------------------------
void CLoad::Unload(void)
{
}

// ----------------------------------------
// 読み込み
// ----------------------------------------
int CLoad::Load(const char * filename)
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

			// 3dアイテムの総数読み込み
			if (strcmp(cHeadText, "TOTAL") == 0)
			{
				sscanf(cRaedText, "%s %s %d", &cDie, &cDie,
					&m_nMax3DItem);
			}
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
				// マテリアルセット来たら
				if (strcmp(cHeadText, "OBJECTSET") == 0)
				{
					// エンドマテリアルセットが来るまでループ
					while (strcmp(cHeadText, "END_OBJECTSET") != 0)
					{
						// 初期化
						cHeadText[0] = '\0';
						fgets(cRaedText, sizeof(cRaedText), pFile);
						sscanf(cRaedText, "%s", &cHeadText);
						// 親情報読み込み
						if (strcmp(cHeadText, "TYPE") == 0)
						{
							sscanf(cRaedText, "%s %s %d", &cDie, &cDie,
								&info[nCntObj].nType);
						}
						// 位置情報読み込み
						else if (strcmp(cHeadText, "POS") == 0)
						{
							sscanf(cRaedText, "%s %s %f %f %f",
								&cDie, &cDie,
								&info[nCntObj].pos.x,
								&info[nCntObj].pos.y,
								&info[nCntObj].pos.z);
						}
						// 回転情報読み込み
						else if (strcmp(cHeadText, "ROT") == 0)
						{
							sscanf(cRaedText, "%s %s %f %f %f", &cDie, &cDie,
								&info[nCntObj].rot.x,
								&info[nCntObj].rot.y,
								&info[nCntObj].rot.z);
						}

						// 色情報読み込み
						else if (strcmp(cHeadText, "COL") == 0)
						{
							sscanf(cRaedText, "%s %s %f %f %f %f", &cDie, &cDie,
								&info[nCntObj].col.r,
								&info[nCntObj].col.g,
								&info[nCntObj].col.b,
								&info[nCntObj].col.a);
						}
						// 縦ブロック情報読み込み
						else if (strcmp(cHeadText, "BLOCK_DEPTH") == 0)
						{
							sscanf(cRaedText, "%s %s %d", &cDie, &cDie,
								&info[nCntObj].nBlockDipth);
						}
						// 横ブロック情報読み込み
						else if (strcmp(cHeadText, "BLOCK_WIDTH") == 0)
						{
							sscanf(cRaedText, "%s %s %d", &cDie, &cDie,
								&info[nCntObj].nBlockWidth);
						}
						// サイズ情報読み込み
						else if (strcmp(cHeadText, "SIZE") == 0)
						{
							sscanf(cRaedText, "%s %s %f %f %f", &cDie, &cDie,
								&info[nCntObj].size.x,
								&info[nCntObj].size.y,
								&info[nCntObj].size.z);
						}
					}
					// モデルの更新
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
// 読み込み
// ----------------------------------------
CLoad::INFO &CLoad::GetInfo(int nID)
{
	return info[nID];
}

// ----------------------------------------
// ジャンプ取得
// ----------------------------------------
int & CLoad::GetShard(void)
{
	return m_nMax3DItem;
}