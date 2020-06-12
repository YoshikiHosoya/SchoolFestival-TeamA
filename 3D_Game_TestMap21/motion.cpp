// =====================================================================================================================================================================
//
// ロードの処理 [motion.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "motion.h"			// インクルードファイル
#include "keyboard.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
MOTION_INFO CMotion::m_aMotion[PLAYER_MOTION] = {};

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define MOTION_FILE_NAME			("data/MOTION/PlayerMotion0.txt")		// セーブファイル

// =====================================================================================================================================================================
//
// モーションの読み込み
//
// =====================================================================================================================================================================
void CMotion::MotionLoad()
{
	// ファイルポイント
	FILE *pFile;

	char		cReadText[128];			// 文字として読み取る
	char		cHeadText[128];			// 比較用
	char		cDie[128];				// 不要な文字
	int			nCntMotion	= 0;		// モーションカウント
	int			nCntKeySet	= 0;		// キーセットカウント
	int			nCntKey		= 0;		// キーカウント
	int			nLoop		= 0;		// ループの有無
	int			nNumKey		= 0;		// 何番目のキー
	int			nNumFrame	= 0;		// フレーム数
	D3DXVECTOR3 pos			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 位置

	// ファイルを開く
	pFile = fopen(MOTION_FILE_NAME, "r");

	// 開いている
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

				// MOTIONSETが来たら
				if (strcmp(cHeadText, "MOTIONSET") == 0)
				{
					// キーセットの初期化
					nCntKeySet = 0;

					// END_POSSETが来るまでループ
					while (strcmp(cHeadText, "END_MOTIONSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
						sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入

						// LOOPが来たら
						if (strcmp(cHeadText, "LOOP") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_aMotion[nCntMotion].nLoop);		// 比較用テキストにループするかの数字を代入
						}

						// NUM_KEYが来たら
						else if (strcmp(cHeadText, "NUM_KEY") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_aMotion[nCntMotion].nNumKey);		// 比較用テキストにキー数を代入
						}

						// KEYSETが来たら
						else if (strcmp(cHeadText, "KEYSET") == 0)
						{
							fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
							sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入

							// FRAMEが来たら
							if (strcmp(cHeadText, "FRAME") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_aMotion[nCntMotion].aKeySet[nCntKeySet].nFrame);		// 比較用テキストにフレーム数を代入
							}

							// キーの初期化
							nCntKey = 0;

							// END_KEYSETが来るまでループ
							while (strcmp(cHeadText, "END_KEYSET") != 0)
							{
								fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
								sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入

								// KEYが来たら
								if (strcmp(cHeadText, "KEY") == 0)
								{
									// END_KEYが来るまでループ
									while (strcmp(cHeadText, "END_KEY") != 0)
									{
										fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
										sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入

										// ROTが来たら
										if (strcmp(cHeadText, "ROT") == 0)
										{
											sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &m_aMotion[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].rot.x,
												&m_aMotion[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].rot.y,
												&m_aMotion[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].rot.z);		// 比較用テキストにROTを代入
										}
									}
									nCntKey++;
								}
							}
							nCntKeySet++;
						}
					}
					nCntMotion++;
				}
			}
		}
	}
}