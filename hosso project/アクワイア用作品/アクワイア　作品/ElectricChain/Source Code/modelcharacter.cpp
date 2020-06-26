//------------------------------------------------------------------------------
//
//キャラクター用モデル処理  [modelcharacter.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "modelcharacter.h"
#include "modelparts.h"
#include "modelparts_weapon.h"
#include "manager.h"
#include "keyboard.h"
#include "game.h"
#include "sceneX.h"
#include "game.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------
std::vector<std::unique_ptr<CModelCharacterInfo>> CModelCharacter::m_pModelCharacterList;
char *CModelCharacter::m_aFileName[MODEL_MAX]
{
	{ "data/SAVEDATA/Woman/Woman.txt" },
	{ "data/SAVEDATA/Armor/Armor.txt" },

};
//------------------------------------------------------------------------------
// マクロ
//------------------------------------------------------------------------------
#define OFFSET_SAVE_TEXT ("data/SAVEDATA/Offset.txt")
//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CModelCharacter::CModelCharacter()
{
	m_pModelPartsList.clear();
	m_CharacterMtx = nullptr;
	m_nFrame = 0;
	m_nKey = 0;
	m_type = MODEL_TYPE::MODEL_PLAYER;
	m_motion = CMotion::MOTION_NONE;
	m_motionOld = CMotion::MOTION_NONE;
	m_bMotionStop = false;
}

//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CModelCharacter::~CModelCharacter()
{
	m_pModelPartsList.clear();
	m_pModelPartsWeaponList.clear();
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CModelCharacter::Init()
{
	//モデル数分繰り返す
	for (size_t nCnt = 0; nCnt < m_pModelCharacterList[m_type]->pModelInfoList.size(); nCnt++)
	{
		//武器IDが見つからなかった場合
		if (m_pModelCharacterList[m_type]->nWeaponID.end() == std::find(m_pModelCharacterList[m_type]->nWeaponID.begin(), m_pModelCharacterList[m_type]->nWeaponID.end(), nCnt))
		{
			//メモリ確保+配列に追加
			m_pModelPartsList.emplace_back(std::move(CModelParts::Create(m_pModelCharacterList[m_type]->pModelInfoList[nCnt])));

		}
		//武器IDが見つかった場合
		else
		{
			//メモリ確保+配列に追加
			m_pModelPartsWeaponList.emplace_back(std::move(CModelParts_Weapon::Create(m_pModelCharacterList[m_type]->pModelInfoList[nCnt])));
		}
	}
	//パーツの相対座標取得
	LoadModelRelativeValue(m_type);

	//初期モーションセット
	SetDefaultMotion();

	//強制的にモーションの所まで回転
	ForcedUpdate(m_motion, m_nKey);

	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CModelCharacter::Uninit()
{
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CModelCharacter::Update()
{
	//1F前のモーション保存
	m_motionOld = m_motion;

	//フレーム加算
	m_nFrame++;

	//フレームが最大いったかどうか
	FrameCheck();

	if (!m_bMotionStop)
	{
		//nullcheck
		if (!m_pModelPartsList.empty())
		{
			//モデル数分繰り返す
			for (size_t nCnt = 0; nCnt < m_pModelPartsList.size(); nCnt++)
			{
				//更新
				m_pModelPartsList[nCnt]->Update();
			}
		}
		//武器
		//nullcheck
		if (!m_pModelPartsWeaponList.empty())
		{
			//モデル数分繰り返す
			for (size_t nCnt = 0; nCnt < m_pModelPartsWeaponList.size(); nCnt++)
			{
				//更新
				m_pModelPartsWeaponList[nCnt]->Update();
			}
		}
	}
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CModelCharacter::Draw()
{
	//nullcheck
	if (!m_pModelPartsList.empty())
	{
		//モデル数分繰り返す
		for (size_t nCnt = 0; nCnt < m_pModelPartsList.size(); nCnt++)
		{
			//描画
			m_pModelPartsList[nCnt]->Draw();
		}
	}
	//武器
	//nullcheck
	if (!m_pModelPartsWeaponList.empty())
	{
		//モデル数分繰り返す
		for (size_t nCnt = 0; nCnt < m_pModelPartsWeaponList.size(); nCnt++)
		{
			//描画
			m_pModelPartsWeaponList[nCnt]->Draw();
		}
	}
}
//------------------------------------------------------------------------------
//生成
//------------------------------------------------------------------------------
std::unique_ptr<CModelCharacter> CModelCharacter::Create(MODEL_TYPE const modeltype)
{
	//メモリ確保
	std::unique_ptr<CModelCharacter>  pModelCharacter(new CModelCharacter);

	//タイプ
	pModelCharacter->m_type = modeltype;

	//初期化
	pModelCharacter->Init();

	//return
	return pModelCharacter;
}

//------------------------------------------------------------------------------
//読み込み
//------------------------------------------------------------------------------
HRESULT CModelCharacter::Load()
{
	for (int nCntModel = 0; nCntModel < MODEL_MAX; nCntModel++)
	{
		//モデルキャラクタ用のメモリ確保
		std::unique_ptr<CModelCharacterInfo> pModelCharacter(new CModelCharacterInfo);

		m_pModelCharacterList.emplace_back(std::move(pModelCharacter));

		std::cout << "new MODELCHARACTER : " << nCntModel << NEWLINE;


		//モデル名取得
		SUCCEEDED(LoadModelName((MODEL_TYPE)nCntModel)) ?
			std::cout << "LoadModelName [Success] : " << nCntModel << NEWLINE :		//成功
			std::cout << "LoadModelName [Failed] : " << nCntModel << NEWLINE;			//失敗

		//モデル生成
		for (size_t nCnt = 0; nCnt < m_pModelCharacterList[nCntModel]->pModelInfoList.size(); nCnt++)
		{
			CHossoLibrary::CreateModelInfo(m_pModelCharacterList[nCntModel]->pModelInfoList[nCnt].get());
		}
		std::cout << NEWLINE;
	}

	return S_OK;
}
//------------------------------------------------------------------------------
//開放
//------------------------------------------------------------------------------
void CModelCharacter::UnLoad()
{
	if (m_pModelCharacterList.empty())
	{
		m_pModelCharacterList.clear();
	}
}
//------------------------------------------------------------------------------
//キャラクターのマトリックス設定
//------------------------------------------------------------------------------
void CModelCharacter::SetCharacterMtx(D3DXMATRIX *mtx)
{
	//モデル総数分
	for (size_t nCnt = 0; nCnt < m_pModelPartsList.size(); nCnt++)
	{
		//親がいない時
		if (m_pModelPartsList[nCnt]->GetParent() == -1)
		{
			//大元のマトリックス設定
			m_pModelPartsList[nCnt]->SetParentMtx(mtx);
		}
		else
		{
			//親パーツのマトリックス設定
			m_pModelPartsList[nCnt]->SetParentMtx(m_pModelPartsList[m_pModelPartsList[nCnt]->GetParent()]->GetMtx());
		}
	}
	//モデル総数分
	for (size_t nCnt = 0; nCnt < m_pModelPartsWeaponList.size(); nCnt++)
	{
		//親がいない時
		if (m_pModelPartsWeaponList[nCnt]->GetParent() == -1)
		{
			//大元のマトリックス設定
			m_pModelPartsWeaponList[nCnt]->SetParentMtx(mtx);
		}
		else
		{
			//親パーツのマトリックス設定
			m_pModelPartsWeaponList[nCnt]->SetParentMtx(m_pModelPartsList[m_pModelPartsWeaponList[nCnt]->GetParent()]->GetMtx());
		}
	}
}

//------------------------------------------------------------------------------
//モーションセット
//------------------------------------------------------------------------------
void CModelCharacter::SetMotion(CMotion::MOTION_TYPE motiontype)
{
	//nullcheck
	if (m_pModelCharacterList[m_type])
	{
		//モーションが切り替わった時
		if (m_motionOld != motiontype)
		{
			//ダッシュ連打とか歩く連打とかされても足が交互に出るように
			switch (m_motionOld)
			{
			case CMotion::PLAYER_WALK:
				m_nKey <= 1 ? m_bWalkMoveKey = true : m_bWalkMoveKey = false;

				break;
			case CMotion::PLAYER_DASH:
				m_nKey <= 1 ? m_bDashMoveKey = true : m_bDashMoveKey = false;
				break;

			}
			//フレームとキーリセット
			ResetMotion();

			//ダッシュ連打とか歩く連打とかされても足が交互に出るように
			switch (motiontype)
			{
			case CMotion::PLAYER_WALK:
				m_nKey = m_bWalkMoveKey * 2;
				break;

			case CMotion::PLAYER_DASH:
				m_nKey = m_bDashMoveKey * 2;
				break;
			}

			//モーション再生
			SetMotionStop(false);
		}

		//モーションの切り替え
		m_motion = motiontype;

		//nullcheck
		if (!m_pModelPartsList.empty())
		{
			m_pModelPartsList[0]->SetMotionPosDest(motiontype, m_nKey);

			//モデル数分繰り返す
			for (size_t nCnt = 0; nCnt < m_pModelPartsList.size(); nCnt++)
			{
				//モーションの回転の決定先取得
				m_pModelPartsList[nCnt]->SetMotionRotDest(motiontype, m_nKey);
			}
		}

		//nullcheck
		if (!m_pModelPartsWeaponList.empty())
		{
			//モデル数分繰り返す
			for (size_t nCnt = 0; nCnt < m_pModelPartsWeaponList.size(); nCnt++)
			{
				//モーションが切り替わって0Key目の時&&bAttackがtrueの時
				if (m_nKey == 0 && CMotion::CheckAttack(motiontype))
				{
					//敵の無敵時間リセット
					m_pModelPartsWeaponList[nCnt]->ResetEnemyInvincible();
				}

				//モーションの回転の決定先取得
				m_pModelPartsWeaponList[nCnt]->SetMotionRotDest(motiontype, m_nKey);

				//攻撃をする場合
				if (CMotion::CheckAttackKey(motiontype, m_nKey))
				{
					//攻撃設定
					m_pModelPartsWeaponList[nCnt]->StartAttack();
					m_pModelPartsWeaponList[nCnt]->SetAttackInfo(motiontype);
				}
				else
				{
					//攻撃終了
					m_pModelPartsWeaponList[nCnt]->EndAttack();
				}

			}
		}
	}
}
//------------------------------------------------------------------------------
//デフォルトのモーションセット
//------------------------------------------------------------------------------
void CModelCharacter::SetDefaultMotion()
{
	switch (m_type)
	{
	case MODEL_TYPE::MODEL_PLAYER:
		//ニュートラルに戻す
		m_motion = CMotion::PLAYER_NEUTRAL;
		break;

	case MODEL_TYPE::MODEL_ENEMY:
		//ニュートラルに戻す
		m_motion = CMotion::ENEMY_ARMOR_NEUTRAL;

		break;

	default:
		break;
	}
}

//------------------------------------------------------------------------------
//imgui用
//------------------------------------------------------------------------------
void CModelCharacter::ShowModelCharacterInfo()
{
#ifdef _DEBUG

	//キャラクター情報情報
	if (ImGui::TreeNode("ModelCharacterInfo"))
	{
		ImGui::Text("Motion ; %d", m_motion);
		ImGui::Text("Key ; %d", m_nKey);
		ImGui::Text("Frame ; %d", m_nFrame);

		ImGui::TreePop();
	}
#endif //DEBUG
}

//------------------------------------------------------------------------------
// パーツ情報読み込み
//------------------------------------------------------------------------------
HRESULT CModelCharacter::LoadModelRelativeValue(MODEL_TYPE type)
{
	//変数宣言
	FILE *pFile;			//ファイルのポインタ
	char cReadText[MAX_TEXT];
	char cHeadText[MAX_TEXT];
	char cDieText[MAX_TEXT];
	int nCntParts = 0;			//パーツ数
	int nCntWeaponParts = 0;	//武器パーツ数
	bool bOrbit = false;

	D3DXVECTOR3 pos = ZeroVector3;
	D3DXVECTOR3 rot = ZeroVector3;
	D3DXVECTOR3 OrbitOffset = ZeroVector3;
	int nParent = 0;
	int nIndex = 0;

	//ファイルを開く
	pFile = fopen(m_aFileName[type], "r");

	//ファイルがあった場合
	if (pFile)
	{
		//スクリプトがくるまで
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile);
			sscanf(cReadText, "%s", &cHeadText);
		}
		//スクリプトだったら
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			//エンドスクリプトが来る前ループ
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s", &cHeadText);
				//改行
				if (strcmp(cHeadText, "\n") == 0)
				{
				}
				//キャラクターセットだったら
				else if (strcmp(cHeadText, "CHARACTERSET") == 0)
				{
					//エンドキャラクターセットがくるまでループ
					while (strcmp(cHeadText, "END_CHARACTERSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile);
						sscanf(cReadText, "%s", &cHeadText);
						//改行
						if (strcmp(cHeadText, "\n") == 0)
						{
						}
						//パーツセットだったら
						else if (strcmp(cHeadText, "PARTSSET") == 0)
						{
							bOrbit = false;
							OrbitOffset = ZeroVector3;

							//エンドパーツセットがくるまでループ
							while (strcmp(cHeadText, "END_PARTSSET") != 0)
							{
								fgets(cReadText, sizeof(cReadText), pFile);
								sscanf(cReadText, "%s", &cHeadText);

								//軌跡描画するかどうか
								if (strcmp(cHeadText, "ORBIT") == 0)
								{
									int nOrbit = 0;
									sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &nOrbit);
									nOrbit ? bOrbit = true : bOrbit = false;
								}
								//軌跡のオフセット座標
								if (strcmp(cHeadText, "ORBIT_OFFSET") == 0)
								{
									sscanf(cReadText, "%s %s %f %f %f", &cDieText, &cDieText, &OrbitOffset.x, &OrbitOffset.y, &OrbitOffset.z);
								}
								//インデックス
								if (strcmp(cHeadText, "INDEX") == 0)
								{
									sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &nIndex);
								}
								//親番号
								if (strcmp(cHeadText, "PARENT") == 0)
								{
									sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &nParent);
								}
								//ポジション
								if (strcmp(cHeadText, "POS") == 0)
								{
									sscanf(cReadText, "%s %s %f %f %f", &cDieText, &cDieText, &pos.x, &pos.y, &pos.z);
								}
								//回転量
								if (strcmp(cHeadText, "ROT") == 0)
								{
									sscanf(cReadText, "%s %s %f %f %f", &cDieText, &cDieText, &rot.x, &rot.y, &rot.z);
								}

								if (strcmp(cHeadText, "END_PARTSSET") == 0)
								{
									if (!bOrbit)
									{
										m_pModelPartsList[nCntParts]->SetPartsInfo(nIndex, nParent, pos, rot);

										//カウントアップ
										nCntParts++;
									}
									else
									{
										m_pModelPartsWeaponList[nCntWeaponParts]->SetPartsInfo(nIndex, nParent, pos, rot);
										nCntWeaponParts++;
									}
								}
							}
						}
					}
				}
			}
		}
		fclose(pFile);
	}

	//開けなかった時
	else
	{
		std::cout << "テキスト読み込み失敗" << "LoadModelRelativeValue()" << NEWLINE;
		return E_FAIL;
	}
	return S_OK;
}
//------------------------------------------------------------------------------
// モデル名読み込み
//------------------------------------------------------------------------------
HRESULT CModelCharacter::LoadModelName(MODEL_TYPE type)
{
	//変数宣言
	FILE *pFile;					//ファイルのポインタ
	char cReadText[MAX_TEXT];
	char cHeadText[MAX_TEXT];
	char cDieText[MAX_TEXT];
	int nBool = 0;
	int nNumModel = 0;		//モデル数
	int nCntModel = 0;		//モデル数のカウント
	int nWeaponID = 0;		//武器番号

							//ファイルを開く
	pFile = fopen(m_aFileName[type], "r");

	//ファイルがあった場合
	if (pFile != NULL)
	{
		//スクリプトがくるまで
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile);
			sscanf(cReadText, "%s", &cHeadText);
		}
		//スクリプトだったら
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			//エンドスクリプトが来る前ループ
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s", &cHeadText);
				//改行
				if (strcmp(cHeadText, "\n") == 0)
				{
				}
				//モデル番号だったら
				else if (strcmp(cHeadText, "NUM_MODEL") == 0)
				{
					//モデル数
					sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &nNumModel);

					while (1)
					{
						fgets(cReadText, sizeof(cReadText), pFile);
						sscanf(cReadText, "%s", &cHeadText);
						//ファイルネームの読み込み
						if (strcmp(cHeadText, "MODEL_FILENAME") == 0)
						{
							//メモリ確保
							std::unique_ptr<CModelInfo> pModelInfo(new CModelInfo);

							//配列に追加
							m_pModelCharacterList[type]->pModelInfoList.emplace_back(std::move(pModelInfo));

							//debug
							std::cout << "new ModelCharacter->pModelInfo : " << type << "-" << nCntModel << "-";

							char aName[128] = {};

							//モデル名代入
							sscanf(cReadText, "%s %s %s %s %s", &cDieText, &cDieText, &aName, &cDieText, &cDieText);

							m_pModelCharacterList[type]->pModelInfoList[nCntModel]->aName = aName;

							//debug モデル名出力
							std::cout << "Name >> " << m_pModelCharacterList[type]->pModelInfoList[nCntModel]->aName.data() << NEWLINE;

							//モデル数カウントアップ
							nCntModel++;

							//最初に宣言されたモデル数になった時
							if (nCntModel == nNumModel)
							{
								//ループを抜ける
								break;
							}
						}
					}
				}
				//モデル番号だったら
				else if (strcmp(cHeadText, "WEAPON_ID") == 0)
				{
					//武器番号取得
					sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &nWeaponID);

					//配列に追加
					m_pModelCharacterList[type]->nWeaponID.emplace_back(nWeaponID);

					//debug モデル名出力
					std::cout << "WeaponID >> " << nWeaponID << NEWLINE;

				}

			}
		}
		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		//失敗
		std::cout << "テキスト読み込み失敗" << "LoadModelName()" << NEWLINE;

		return E_FAIL;
	}

	return S_OK;
}

//------------------------------------------------------------------------------
// オフセット情報保存
//------------------------------------------------------------------------------
HRESULT CModelCharacter::SaveModelOffset()
{
	FILE *pFile;

	int nRotNum = 0;
	char cHeadtext[128];
	char cWriteText[128];

	//ファイル読み込み
	pFile = fopen(OFFSET_SAVE_TEXT, "w");

	//nullcheck
	if (pFile != nullptr)
	{
		//ブロックコメント
		fputs(COMMENT02, pFile);
		fputs(COMMENT01, pFile);

		strcpy(cHeadtext, "//Offset\n");
		strcpy(cHeadtext, "//テキストにコピペしてください\n");

		fputs(cHeadtext, pFile);

		strcpy(cHeadtext, "//Author:Yoshiki Hosoya\n");
		fputs(cHeadtext, pFile);

		fputs(COMMENT01, pFile);
		fputs(COMMENT02, pFile);
		fputs(NEWLINE, pFile);

		//ブロックコメント終了//

			//キャラクターセット
			fputs("CHARACTERSET", pFile);
			fputs(NEWLINE, pFile);

			//nullcheck
			if (!m_pModelPartsList.empty())
			{
				for (size_t nCnt = 0; nCnt < m_pModelPartsList.size(); nCnt++)
				{

					//パーツセット
					fputs("	PARTSSET", pFile);
					fputs(NEWLINE, pFile);

					//インデックス
					sprintf(cWriteText, "		%s %s %d", "INDEX", &EQUAL, m_pModelPartsList[nCnt]->GetIndex());
					fputs(cWriteText, pFile);
					fputs(NEWLINE, pFile);

					//親番号
					sprintf(cWriteText, "		%s %s %d", "PARENT", &EQUAL, m_pModelPartsList[nCnt]->GetParent());
					fputs(cWriteText, pFile);
					fputs(NEWLINE, pFile);

					//座標
					sprintf(cWriteText, "		%s %s %.1f %.1f %.1f", "POS", &EQUAL,
						m_pModelPartsList[nCnt]->GetPos().x,
						m_pModelPartsList[nCnt]->GetPos().y,
						m_pModelPartsList[nCnt]->GetPos().z);
					fputs(cWriteText, pFile);
					fputs(NEWLINE, pFile);

					//回転
					sprintf(cWriteText, "		%s %s %.1f %.1f %.1f", "ROT", &EQUAL,
						m_pModelPartsList[nCnt]->GetRot().x,
						m_pModelPartsList[nCnt]->GetRot().y,
						m_pModelPartsList[nCnt]->GetRot().z);
					fputs(cWriteText, pFile);
					fputs(NEWLINE, pFile);

					//パーツセット終了
					fputs("	END_PARTSSET", pFile);
					fputs(NEWLINE, pFile);
					fputs(NEWLINE, pFile);

				}
			}

			//nullcheck
			if (!m_pModelPartsWeaponList.empty())
			{
				for (size_t nCnt = 0; nCnt < m_pModelPartsWeaponList.size(); nCnt++)
				{

					//パーツセット
					fputs("	PARTSSET", pFile);
					fputs(NEWLINE, pFile);

					//軌跡on
					sprintf(cWriteText, "		%s %s %d", "ORBIT", &EQUAL, 1);
					fputs(cWriteText, pFile);
					fputs(NEWLINE, pFile);

					//インデックス
					sprintf(cWriteText, "		%s %s %d", "INDEX", &EQUAL, m_pModelPartsWeaponList[nCnt]->GetIndex());
					fputs(cWriteText, pFile);
					fputs(NEWLINE, pFile);

					//親番号
					sprintf(cWriteText, "		%s %s %d", "PARENT", &EQUAL, m_pModelPartsWeaponList[nCnt]->GetParent());
					fputs(cWriteText, pFile);
					fputs(NEWLINE, pFile);

					//座標
					sprintf(cWriteText, "		%s %s %.1f %.1f %.1f", "POS", &EQUAL,
						m_pModelPartsWeaponList[nCnt]->GetPos().x,
						m_pModelPartsWeaponList[nCnt]->GetPos().y,
						m_pModelPartsWeaponList[nCnt]->GetPos().z);
					fputs(cWriteText, pFile);
					fputs(NEWLINE, pFile);

					//回転
					sprintf(cWriteText, "		%s %s %.1f %.1f %.1f", "ROT", &EQUAL,
						m_pModelPartsWeaponList[nCnt]->GetRot().x,
						m_pModelPartsWeaponList[nCnt]->GetRot().y,
						m_pModelPartsWeaponList[nCnt]->GetRot().z);
					fputs(cWriteText, pFile);
					fputs(NEWLINE, pFile);

					//パーツセット終了
					fputs("	END_PARTSSET", pFile);
					fputs(NEWLINE, pFile);
					fputs(NEWLINE, pFile);

				}
			}
			//アタックセット終了
			fputs("END_CHARACTERSET", pFile);
			fputs(NEWLINE, pFile);
			fputs(NEWLINE, pFile);


		std::cout << "Save Succsess!!  SaveModelOffset()" << NEWLINE;

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		//ファイルが開けませんでした
		std::cout << "Save FAILED!!  Can't Open File. SaveModelOffset()" << NEWLINE;
		return E_FAIL;
	}
	return S_OK;
}
//------------------------------------------------------------------------------
// フレームが最後まで行ったか確認
//------------------------------------------------------------------------------
void CModelCharacter::FrameCheck()
{
	//フレームが一定値まで来た時
	if (m_nFrame >= CMotion::GetFrame(m_motion, m_nKey))
	{
		//フレーム初期化
		m_nFrame = 0;

		//キー加算
		m_nKey++;

		//キーが最後まで行ったか
		KeyCheck();

		//次のモーション情報をセット
		SetMotion(m_motion);
	}
}

//------------------------------------------------------------------------------
// 強制的にモーション切り替え　０F目の回転のとこにもってく
//------------------------------------------------------------------------------
void CModelCharacter::ForcedUpdate(CMotion::MOTION_TYPE motiontype, int nKey)
{
	m_pModelPartsList[0]->SetForcedPos(motiontype, m_nKey);

	//モデル数分繰り返す
	for (size_t nCnt = 0; nCnt < m_pModelPartsList.size(); nCnt++)
	{
		//モーションの回転の決定先取得
		m_pModelPartsList[nCnt]->SetForcedRot(motiontype, m_nKey);
	}
	//モデル数分繰り返す
	for (size_t nCnt = 0; nCnt < m_pModelPartsWeaponList.size(); nCnt++)
	{
		//モーションの回転の決定先取得
		m_pModelPartsWeaponList[nCnt]->SetForcedRot(motiontype, m_nKey);
	}
}
//------------------------------------------------------------------------------
// 攻撃に関する情報の更新
//------------------------------------------------------------------------------
void CModelCharacter::UpdateAttackInfo()
{
	//nullcheck
	if (!m_pModelPartsWeaponList.empty())
	{
		//モデル数分繰り返す
		for (size_t nCnt = 0; nCnt < m_pModelPartsWeaponList.size(); nCnt++)
		{
			//攻撃をする場合
			if (CMotion::CheckAttackKey(m_motion,m_nKey))
			{
				//攻撃の設定変更
				m_pModelPartsWeaponList[nCnt]->SetAttackInfo(m_motion);
			}
		}
	}
}
//------------------------------------------------------------------------------
// 移動するキーか確認
//------------------------------------------------------------------------------
bool CModelCharacter::CheckMoveKey()
{
	//フレームが０の時
	if (m_nFrame == 0)
	{
		//nullcheck
		if (CMotion::GetAttackInfo(m_motion))
		{
			//キーが指定されたキーの時
			if (CMotion::GetAttackInfo(m_motion)->nMoveKey == m_nKey)
			{
				return true;
			}
		}
	}
	return false;
}
//------------------------------------------------------------------------------
// キャラクターのポインタ
//------------------------------------------------------------------------------
void CModelCharacter::SetCharacterPtr(std::shared_ptr<CCharacter> pCharacter)
{
	if (!m_pModelPartsWeaponList.empty())
	{
		//武器モデル数分
		for (size_t nCnt = 0; nCnt < m_pModelPartsWeaponList.size(); nCnt++)
		{
			//キャラクターのポインタ
			m_pModelPartsWeaponList[nCnt]->SetHasCharacterPtr(pCharacter);
		}
	}
}
//------------------------------------------------------------------------------
//腰の高さ取得
//------------------------------------------------------------------------------
float CModelCharacter::GetWaistHeight()
{
	return m_pModelPartsList[0]->GetPos().y;
}
//------------------------------------------------------------------------------
//それぞれのパーツへマテリアルカラー設定
//------------------------------------------------------------------------------
void CModelCharacter::SetPartsMaterialCol(CSceneX::MATERIAL_COL matCol)
{
	//nullcheck
	if (!m_pModelPartsList.empty())
	{
		//モデル総数文
		for (size_t nCnt = 0; nCnt < m_pModelPartsList.size(); nCnt++)
		{
			m_pModelPartsList[nCnt]->SetMaterialCol(matCol);
		}
	}
	//nullcheck
	if (!m_pModelPartsWeaponList.empty())
	{
		//モデル総数分
		for (size_t nCnt = 0; nCnt < m_pModelPartsWeaponList.size(); nCnt++)
		{
			m_pModelPartsWeaponList[nCnt]->SetMaterialCol(matCol);
		}
	}
}
//------------------------------------------------------------------------------
// パーツのインデックス情報取得
//------------------------------------------------------------------------------
CModelParts * CModelCharacter::GetPartsPtr(int nIndex)
{
	//モデル総数分
	for (size_t nCnt = 0; nCnt < m_pModelPartsList.size(); nCnt++)
	{
		//インデックスがあってるか
		if (m_pModelPartsList[nCnt]->GetIndex() == nIndex)
		{
			//return
			return m_pModelPartsList[nCnt].get();
		}

	}
	//モデル総数分
	for (size_t nCnt = 0; nCnt < m_pModelPartsWeaponList.size(); nCnt++)
	{
		//インデックスがあってるか
		if (m_pModelPartsWeaponList[nCnt]->GetIndex() == nIndex)
		{
			//return
			return m_pModelPartsWeaponList[nCnt].get();
		}
	}

	return nullptr;
}

//------------------------------------------------------------------------------
// キーが最後までいったのを確認
//------------------------------------------------------------------------------
void CModelCharacter::KeyCheck()
{
	//キーが一定値まで来た時
	if (m_nKey >= CMotion::GetNumKey(m_motion))
	{
		//フレームとキー初期化
		ResetMotion();

		//ループしない時
		if (!CMotion::CheckLoop(m_motion))
		{
			if (CManager::GetMode() != CManager::MODE_DEBUG_MOTION_VIEWER)
			{
				//デフォルトモーションセット
				SetDefaultMotion();
			}
			else
			{
				//デバッグ中は動きを止める
				SetMotionStop(true);
			}
		}
	}
}
