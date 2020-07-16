//------------------------------------------------------------------------------
//
//パーティクルのパラメータクラス  [particleparamater.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "ParticleParamater.h"
#include "manager.h"
#include "renderer.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------
std::vector<std::unique_ptr<CParticleParam>> CParticleParam::m_pParticleDefaultParamList = {};
FILENAME_LIST CParticleParam::m_aFileNameList =
{
	{ "data/Load/Effect/Paramater/Default.txt" },
	{ "data/Load/Effect/Paramater/Explosion.txt" },
	{ "data/Load/Effect/Paramater/Blood.txt" },
	{ "data/Load/Effect/Paramater/Sumple.txt" },
	{ "data/Load/Effect/Paramater/HeavyMachinegun.txt" },
	{ "data/Load/Effect/Paramater/TankGun.txt" },
	{ "data/Load/Effect/Paramater/Lazer.txt" },

};

FILENAME_LIST CParticleCreators::m_aFileNameList =
{
	{ "data/Load/Effect/Creator/Default.txt" },
};

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define PARAMATER_SAVE_FILENAME ("data/Load/Effect/Paramater/SaveParamater.txt")
//------------------------------------------------------------------------------
//テキストからパラメータ取得
//------------------------------------------------------------------------------
HRESULT CParticleParam::LoadParticleDefaultParam()
{
	//ファイルポイント
	FILE *pFile;
	char cReadText[128];	//文字として読み取り用k
	char cHeadText[128];	//比較する用
	char cDie[128];			//不要な文字
	int n_BoolValue;		//boolに変換するようの格納
	HRESULT hResult = S_OK;

	CParticleParam *pParam;

	//ファイル数分
	for (size_t nCnt = 0; nCnt < m_aFileNameList.size(); nCnt++)
	{
		//ファイル読み込み
		pFile = fopen(m_aFileNameList[nCnt].data(), "r");

		//ファイルが開けた時
		if (pFile != NULL)
		{
			//スクリプトが来るまでループ
			while (strcmp(cHeadText, "SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);	//一文を読み込む
				sscanf(cReadText, "%s", &cHeadText);		//比較用テキストに文字を代入
			}
			//スクリプトだったら
			if (strcmp(cHeadText, "SCRIPT") == 0)
			{
				//エンドスクリプトが来るまでループ
				while (strcmp(cHeadText, "END_SCRIPT") != 0)
				{
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s", &cHeadText);

					//パラメータセットだったら
					if (strcmp(cHeadText, "PARAMSET") == 0)
					{
						//メモリ確保
						pParam = new CParticleParam;

						//エンド来るまでループ
						while (strcmp(cHeadText, "END_PARAMSET") != 0)
						{

							fgets(cReadText, sizeof(cReadText), pFile);
							sscanf(cReadText, "%s", &cHeadText);


							//それぞれの項目を読み込み
							if (strcmp(cHeadText, "SPEEDRANDOM") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &n_BoolValue);
								pParam->m_bSpeedRandom = n_BoolValue ? true : false;
							}
							if (strcmp(cHeadText, "GRAVITY") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &n_BoolValue);
								pParam->m_bGravity = n_BoolValue ? true : false;
							}
							if (strcmp(cHeadText, "ALPHABLEND") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &n_BoolValue);
								pParam->m_bAlphaBlend = n_BoolValue ? true : false;
							}
							if (strcmp(cHeadText, "ANIMATION") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &n_BoolValue);
								pParam->m_bAnimation = n_BoolValue ? true : false;
							}
							if (strcmp(cHeadText, "TEXTURE") == 0)
							{
								//アニメーションするかどうかで代入する場所が変わる
								//通常テクスチャか分割テクスチャか
								pParam->m_bAnimation ?
									sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pParam->m_Textype) :
									sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pParam->m_SeparateTex);
							}
							if (strcmp(cHeadText, "SHAPE") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pParam->m_shape);
							}
							if (strcmp(cHeadText, "LIFE") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pParam->m_nLife);
							}
							if (strcmp(cHeadText, "NUMBER") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pParam->m_nNumber);
							}
							if (strcmp(cHeadText, "SPEED") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDie, &cDie, &pParam->m_fSpeed);
							}
							if (strcmp(cHeadText, "RANGE") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDie, &cDie, &pParam->m_fRange);
							}
							if (strcmp(cHeadText, "ALPHADAMPING") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDie, &cDie, &pParam->m_fAlphaDamping);
							}
							if (strcmp(cHeadText, "GRAVITYPOWER") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDie, &cDie, &pParam->m_fGravityPower);
							}
							if (strcmp(cHeadText, "SIZE") == 0)
							{
								sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
									&pParam->m_Size.x, &pParam->m_Size.y, &pParam->m_Size.z);
							}
							if (strcmp(cHeadText, "SIZEDAMPING") == 0)
							{
								sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
									&pParam->m_SizeDamping.x, &pParam->m_SizeDamping.y, &pParam->m_SizeDamping.z);
							}
							if (strcmp(cHeadText, "COLOR") == 0)
							{
								sscanf(cReadText, "%s %s %f %f %f %f", &cDie, &cDie,
										&pParam->m_col.r, &pParam->m_col.g, &pParam->m_col.b, &pParam->m_col.a);
							}
							if (strcmp(cHeadText, "ROT") == 0)
							{
								sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
									&pParam->m_rot.x, &pParam->m_rot.y, &pParam->m_rot.z);
							}
							if (strcmp(cHeadText, "END_PARAMSET") == 0)
							{
								pParam->m_ParticleType = (CParticleParam::PARTICLE_TEXT)nCnt;
								m_pParticleDefaultParamList.emplace_back(std::move(pParam));
							}
						}
					}
				}
			}

			//パラメータロード
			std::cout << "DefaultParticleParamLoad >>" << m_aFileNameList[nCnt].data() << NEWLINE;

			//ファイルを閉じる
			fclose(pFile);
		}

		//ファイル読み込めなかった場合
		else
		{
			std::cout << "LoadFailed!!  >>" << m_aFileNameList[nCnt].data() << NEWLINE;
			MessageBox(NULL, "パーティクルのパラメータ読み込み失敗", "警告", MB_ICONWARNING);
			hResult = E_FAIL;
		}
	}
	return S_OK;
}

//------------------------------------------------------------------------------
//パーティクルのパラメータ保存
//------------------------------------------------------------------------------
HRESULT CParticleParam::SaveParticleDefaultParam(CParticleParam *pSaveParam)
{
	FILE *pFile;

	int nRotNum = 0;
	char cWriteText[128];

	//ファイル読み込み
	pFile = fopen(PARAMATER_SAVE_FILENAME, "w");

	//nullcheck
	if (pFile && pSaveParam)
	{
		//ブロックコメント
		fputs(COMMENT02, pFile);
		fputs(COMMENT01, pFile);

		fputs("//ParticleParamater\n", pFile);
		fputs("//読み込み用のテキストにコピーしてください\n", pFile);
		fputs("//Author:Yoshiki Hosoya\n", pFile);

		fputs(COMMENT01, pFile);
		fputs(COMMENT02, pFile);
		fputs(NEWLINE, pFile);

		//ブロックコメント終了//

		//スクリプト
		fputs("SCRIPT", pFile);
		fputs(NEWLINE, pFile);


		//パラメータセット
		fputs("	PARAMSET", pFile);
		fputs(NEWLINE, pFile);

		//改行
		fputs(NEWLINE, pFile);


		//それぞれの項目書き出し
		sprintf(cWriteText, "		%s %s %d					%s", "SPEEDRANDOM", &EQUAL, pSaveParam->m_bSpeedRandom, "//速度がランダムかどうか");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %d						%s", "GRAVITY", &EQUAL, pSaveParam->m_bGravity, "//重力をつけるか");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %d					%s", "ALPHABLEND", &EQUAL, pSaveParam->m_bAlphaBlend, "//αブレンドするか");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %d					%s", "ANIMATION", &EQUAL, pSaveParam->m_bAnimation, "//アニメーションするか");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		//アニメーションするかしないかでテクスチャ番号変更
		//通常のテクスチャか分割テクスチャか
		int TexID = pSaveParam->m_bAnimation ?
			pSaveParam->m_SeparateTex : pSaveParam->m_Textype;
		sprintf(cWriteText, "		%s %s %d						%s", "TEXTURE", &EQUAL, TexID, "//テクスチャ");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %d						%s", "SHAPE", &EQUAL, pSaveParam->m_shape, "//パーティクルの出し方");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %d						%s", "LIFE", &EQUAL, pSaveParam->m_nLife, "//ライフ");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %d						%s", "NUMBER", &EQUAL, pSaveParam->m_nNumber, "//個数");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %.1f					%s", "SPEED", &EQUAL, pSaveParam->m_fSpeed, "//速度");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %.1f						%s", "RANGE", &EQUAL, pSaveParam->m_fRange, "//範囲");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %.2f				%s", "ALPHADAMPING", &EQUAL, pSaveParam->m_fAlphaDamping, "//アルファ値の減衰値");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %.2f				%s", "GRAVITYPOWER", &EQUAL, pSaveParam->m_fGravityPower, "//重力の強さ");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %.2f %.2f %.2f		%s", "SIZE", &EQUAL,
			pSaveParam->m_Size.x, pSaveParam->m_Size.y, pSaveParam->m_Size.z, "//サイズ");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %.2f %.2f %.2f		%s", "SIZEDAMPING", &EQUAL,
			pSaveParam->m_SizeDamping.x, pSaveParam->m_SizeDamping.y, pSaveParam->m_SizeDamping.z, "//サイズ減衰量");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %.1f %.1f %.1f %.1f			%s", "COLOR", &EQUAL,
			pSaveParam->m_col.r, pSaveParam->m_col.g, pSaveParam->m_col.b, pSaveParam->m_col.a, "//色");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		sprintf(cWriteText, "		%s %s %.2f %.2f %.2f			%s", "ROT", &EQUAL,
				pSaveParam->m_rot.x, pSaveParam->m_rot.y, pSaveParam->m_rot.z, "//回転量");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);


		//改行
		fputs(NEWLINE, pFile);

		//パラメータセット
		fputs("	END_PARAMSET", pFile);
		fputs(NEWLINE, pFile);

		//キーセット終了
		fputs("END_SCRIPT", pFile);
		fputs(NEWLINE, pFile);

		//保存成功
		std::cout << "ParticleParam Save Succsess!! >>" << PARAMATER_SAVE_FILENAME << NEWLINE;

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		//ファイルが開けませんでした
		std::cout << "ParticleParam Save FAILED!!  Can't Open File. SaveParticleDefaultParam()" << NEWLINE;
		return E_FAIL;
	}
	return S_OK;
}


//------------------------------------------------------------------------------
//コンボボックス
//------------------------------------------------------------------------------
bool CParticleParam::ShowParamConboBox(CParticleParam::PARTICLE_TEXT &rType)
{
	bool bChange = false;

#ifdef _DEBUG
	//combo開始
	if (ImGui::BeginCombo("ParamFileName", m_aFileNameList[rType].data()))
	{
		//要素分繰り返す
		for (size_t nCnt = 0; nCnt < m_aFileNameList.size(); nCnt++)
		{

			//選択番号があってるかどうか
			bool is_selected = (m_aFileNameList[rType] == m_aFileNameList[nCnt]);

			//選択された時の処理
			if (ImGui::Selectable(m_aFileNameList[nCnt].data(), is_selected))
			{
				//現在の選択項目設定
				rType = (CParticleParam::PARTICLE_TEXT)nCnt;
				bChange = true;
			}
		}
		//combo終了
		ImGui::EndCombo();

	}
#endif //DEBUG
	return bChange;
}
//------------------------------------------------------------------------------
//パラメータ設定
//------------------------------------------------------------------------------
void CParticleParam::SetParamater(int nLife, D3DXVECTOR3 size, D3DXCOLOR col, int nNumber, float fSpeed)
{
	m_nLife = nLife;
	m_Size = size;
	m_col = col;

	m_nNumber = nNumber;
	m_fSpeed = fSpeed;
}


//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CParticleParam::UpdateParam()
{
	m_nLife--;
	m_Size.x *= m_SizeDamping.x;
	m_Size.y *= m_SizeDamping.y;
	m_Size.z *= m_SizeDamping.z;

	m_col.a *= m_fAlphaDamping;
}


//------------------------------------------------------------------------------
//オペレータ
//クラスのパラメータを丸ごと代入できるように
//ポインタ同士
//------------------------------------------------------------------------------
void * CParticleParam::operator=(const CParticleParam * pParam)
{
	m_nLife					= pParam->m_nLife;
	m_Size					= pParam->m_Size;
	m_col					= pParam->m_col;
	m_nNumber				= pParam->m_nNumber;
	m_fSpeed				= pParam->m_fSpeed;
	m_SizeDamping			= pParam->m_SizeDamping;
	m_fAlphaDamping			= pParam->m_fAlphaDamping;
	m_Textype				= pParam->m_Textype;
	m_ParticleType			= pParam->m_ParticleType;
	m_shape					= pParam->m_shape;
	m_bGravity				= pParam->m_bGravity;
	m_fGravityPower			= pParam->m_fGravityPower;
	m_bSpeedRandom			= pParam->m_bSpeedRandom;
	m_rot					= pParam->m_rot;
	m_fRange				= pParam->m_fRange;
	m_SeparateTex			= pParam->m_SeparateTex;
	m_bAnimation			= pParam->m_bAnimation;
	m_bAlphaBlend			= pParam->m_bAlphaBlend;
	return this;
}

//------------------------------------------------------------------------------
//パラメータ設定
//------------------------------------------------------------------------------
void CParticleCreators::LoadParticleCreators()
{
	////ファイルポイント
	//FILE *pFile;
	//char cReadText[128];	//文字として読み取り用
	//char cHeadText[128];	//比較する用
	//char cDie[128];			//不要な文字
	//int n_BoolValue;		//boolに変換するようの格納
	//HRESULT hResult = S_OK;

	//CParticleCreators *pCreator;

	////ファイル数分
	//for (size_t nCnt = 0; nCnt < m_aFileNameList.size(); nCnt++)
	//{
	//	//ファイル読み込み
	//	pFile = fopen(m_aFileNameList[nCnt].data(), "r");

	//	//ファイルが開けた時
	//	if (pFile != NULL)
	//	{
	//		//スクリプトが来るまでループ
	//		while (strcmp(cHeadText, "SCRIPT") != 0)
	//		{
	//			fgets(cReadText, sizeof(cReadText), pFile);	//一文を読み込む
	//			sscanf(cReadText, "%s", &cHeadText);		//比較用テキストに文字を代入
	//		}
	//		//スクリプトだったら
	//		if (strcmp(cHeadText, "SCRIPT") == 0)
	//		{
	//			//エンドスクリプトが来るまでループ
	//			while (strcmp(cHeadText, "END_SCRIPT") != 0)
	//			{
	//				fgets(cReadText, sizeof(cReadText), pFile);
	//				sscanf(cReadText, "%s", &cHeadText);

	//				//パラメータセットだったら
	//				if (strcmp(cHeadText, "PARAMSET") == 0)
	//				{
	//					//メモリ確保
	//					pCreator = new CParticleCreators;

	//					//エンド来るまでループ
	//					while (strcmp(cHeadText, "END_PARAMSET") != 0)
	//					{

	//						fgets(cReadText, sizeof(cReadText), pFile);
	//						sscanf(cReadText, "%s", &cHeadText);


	//						//それぞれの項目を読み込み
	//						if (strcmp(cHeadText, "SPEEDRANDOM") == 0)
	//						{
	//							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &n_BoolValue);
	//							pCreator-> = n_BoolValue ? true : false;
	//						}

	//						if (strcmp(cHeadText, "SHAPE") == 0)
	//						{
	//							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pCreator->m_shape);
	//						}
	//						if (strcmp(cHeadText, "TEXTURE") == 0)
	//						{
	//							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pCreator->m_Textype);
	//						}

	//					}
	//				}
	//			}
	//		}

	//		//パラメータロード
	//		std::cout << "DefaultParticleParamLoad >>" << m_aFileNameList[nCnt].data() << NEWLINE;

	//		//ファイルを閉じる
	//		fclose(pFile);
	//	}

	//	//ファイル読み込めなかった場合
	//	else
	//	{
	//		std::cout << "LoadFailed!!  >>" << m_aFileNameList[nCnt].data() << NEWLINE;
	//		MessageBox(NULL, "パーティクルのパラメータ読み込み失敗", "警告", MB_ICONWARNING);
	//		hResult = E_FAIL;
	//	}
	//}
	//return S_OK;
}


//------------------------------------------------------------------------------
//パラメータ設定
//------------------------------------------------------------------------------
CParticleCreators * CParticleCreators::Create()
{
	return nullptr;
}
