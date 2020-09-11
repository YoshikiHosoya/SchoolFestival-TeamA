//=============================================================================
// キャラクターモデル総括処理 [Character.cpp] : NORI
//=============================================================================
#include "ModelSet.h"
#include "inputKeyboard.h"
#include "model.h"
#include "game.h"
#include "fade.h"
#include "map.h"
#include "Xinput.h"
#include "collision.h"
#include "hosso\/Debug_ModelViewer.h"
#include "particle.h"
#include "sound.h"

//=============================================================================
// 静的メンバ変数初期化
//=============================================================================
std::vector<CModelSet::MOTION*> CModelSet::m_CharacterMotion = {};

//オフセットの読み込みファイル
char *CModelSet::m_LoadOffsetFileName[CHARACTER_TYPE_MAX] =
{
	{ "data/Load/Player/PlayerOffset.txt" },
	{ "data/Load/Enemy/Enemy_Human_Offset.txt" },
	{ "data/Load/Enemy/Enemy_Helicopter_Offset.txt" },
	{ "data/Load/Enemy/Enemy_MeltyHoney_Offset.txt" },
	{ "data/Load/Enemy/Enemy_Zycocca_Offset.txt" },
	{ "data/Load/Prisoner/PrisonerOffset.txt" },
	{ "data/Load/Boss/BossOffset.txt" },
	{ "data/Load/DragonNosuke/Boss_OneOffset.txt" },
	{ "data/Load/PlayerTank/PlayerTankOffset.txt" },
	{ "data/Load/BattlePlane/BattlePlaneOffset.txt" },
	{ "data/Load/Helicopter/HelicopterOffset.txt" },
};
//モーションの読み込みファイル
char *CModelSet::m_LoadMotionFileName[CHARACTER_MOTION_MAX] =
{
	{ "data/Load/Player/Motion/Neutral.txt" },
	{ "data/Load/Player/Motion/Walk.txt" },
	{ "data/Load/Player/Motion/Attack.txt" },
	{ "data/Load/Player/Motion/Grenade.txt" },
	{ "data/Load/Player/Motion/Jump.txt" },
	{ "data/Load/Player/Motion/JumpStop.txt" },
	{ "data/Load/Player/Motion/Shoot.txt" },
	{ "data/Load/Player/Motion/Squat.txt" },
	{ "data/Load/Player/Motion/SquatStop.txt" },
	{ "data/Load/Player/Motion/Dead.txt" },
	{ "data/Load/Enemy/Motion/EnemyNeutral.txt" },
	{ "data/Load/Enemy/Motion/EnemyWalk.txt" },
	{ "data/Load/Enemy/Motion/EnemySquatStop.txt" },
	{ "data/Load/Enemy/Motion/EnemyDead_1.txt" },
	{ "data/Load/Enemy/Motion/EnemyDead_2.txt" },
	{ "data/Load/Enemy/Motion/EnemyGrenade.txt" },
	{ "data/Load/Enemy/Motion/EnemyJumpAttack.txt" },
	{ "data/Load/Enemy/Motion/EnemyKnifeAttack.txt" },
	{ "data/Load/Boss/Motion/Neutral.txt" },
	{ "data/Load/Prisoner/Motion/PrisonerStay.txt" },
	{ "data/Load/Prisoner/Motion/PrisonerRelease.txt" },
	{ "data/Load/Prisoner/Motion/PrisonerRun.txt" },
	{ "data/Load/Prisoner/Motion/PrisonerSalute.txt" },
	{ "data/Load/Prisoner/Motion/PrisonerFall.txt" },
	{ "data/Load/Prisoner/Motion/PrisonerSkip.txt" },
};

//=============================================================================
// マクロ
//=============================================================================
#define ADD_ROTATION_SPEED (0.15f)

//====================================================================
//コンストラクタ
//====================================================================
CModelSet::CModelSet()
{
}
//====================================================================
//デストラクタ
//====================================================================
CModelSet::~CModelSet()
{
	//nullcheck
	if (!m_vModelList.empty())
	{
		//パーツ数分
		for (size_t nCnt = 0; nCnt < m_vModelList.size(); nCnt++)
		{
			//メモリ開放
			delete m_vModelList[nCnt];
			m_vModelList[nCnt] = nullptr;
		}
		//配列を空にする
		m_vModelList.clear();
	}
}
//====================================================================
//初期化
//====================================================================
HRESULT CModelSet::Init(void)
{
	m_HeightBet = 0.0f;											//
	m_state = CHARACTER_STATE_NORMAL;							// 状態
	m_bMotion = true;											// モーションするかどうか
	m_bFall = false;											//
	m_bDraw = true;												//描画するかどうか
	//マトリックス初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	return S_OK;
}
//====================================================================
//終了
//====================================================================
void CModelSet::Uninit(void)
{
}
//====================================================================
//ステートのカウント設定
//====================================================================
void CModelSet::SetStateCount(int nCntState)
{
	m_nStateCnt = nCntState;
}
//====================================================================
//マトリックスの設定
//====================================================================
void CModelSet::SetMtxWorld(D3DXMATRIX mtxWorld)
{
	m_mtxWorld = mtxWorld;
}
//====================================================================
//モーションの設定
//====================================================================
void CModelSet::SetMotion(CHARACTER_MOTION_STATE type)
{
	if (m_MotionType != type)
	{
		m_Fram = 0;
		m_CntKeySet = 0;
	}
	m_MotionType = type;
}
//====================================================================
//キャラクターの状態の取得
//====================================================================
CModelSet::CHARACTER_STATE CModelSet::GetCharacterState(void)
{
	return m_state;
}
//====================================================================
//モーション情報の取得
//====================================================================
CModelSet::MOTION *CModelSet::GetCharacterMotion(CHARACTER_MOTION_STATE type)
{
	return m_CharacterMotion[type];
}
//====================================================================
//オフセットのファイル取得
//====================================================================
char * CModelSet::GetOffsetFileName(CHARACTER_TYPE type)
{
	return m_LoadOffsetFileName[type];
}
//====================================================================
//モーションのファイル取得
//====================================================================
char * CModelSet::GetMotionFileName(CHARACTER_MOTION_STATE motionstate)
{
	return m_LoadMotionFileName[motionstate];
}
//====================================================================
//色変更
//====================================================================
void CModelSet::ChangeColor(bool ColorChangeFlag, D3DXCOLOR AddColor)
{
	//モデルの色変更
	for (unsigned int nCnt = 0; nCnt < m_vModelList.size(); nCnt++)
	{
		// 加算する色の設定
		m_vModelList[nCnt]->SetAddColor(AddColor);
		// 色変更フラグの設定
		m_vModelList[nCnt]->SetColorChangeFlag(ColorChangeFlag);
	}
}
//====================================================================
//モーションのロード
//====================================================================
void CModelSet::LoadMotion(void)
{
	//ファイルポイント
	FILE *pFile;
	int nCntModel = 0;		//モデルのカウント
	int nCntKeySet = 0;		//フーレームの分割数
	int nCntKey = 0;
	char cReadText[128];	//文字として読み取り用
	char cHeadText[128];	//比較する用
	char cDie[128];			//不要な文字

	KEY *key;
	KEY_INFO *key_info;

	MOTION *pMotion;
	for (int nCnt = 0; nCnt < CHARACTER_MOTION_MAX; nCnt++)
	{
		pFile = fopen(m_LoadMotionFileName[nCnt], "r");//ファイルを開く
													   //あいたら
		if (pFile != NULL)
		{
			pMotion = new MOTION;
			m_CharacterMotion.emplace_back(pMotion);
			//スクリプトが来るまでループ
			while (strcmp(cHeadText, "SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);	//一文を読み込む
				sscanf(cReadText, "%s", &cHeadText);		//比較用テキストに文字を代入
			}
			//スクリプトだったら
			if (strcmp(cHeadText, "SCRIPT") == 0)
			{
				//フレーム分割数の初期化
				nCntKeySet = 0;
				//エンドスクリプトが来るまでループ
				while (strcmp(cHeadText, "END_SCRIPT") != 0)
				{
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s", &cHeadText);

					//ループするかどうかの情報読み込み
					if (strcmp(cHeadText, "LOOP") == 0)
					{
						sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_CharacterMotion[nCnt]->nLoop);
					}
					else if (strcmp(cHeadText, "NUM_KEY") == 0)
					{
						sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_CharacterMotion[nCnt]->nNumKey);
					}
					else if (strcmp(cHeadText, "KEYSET") == 0)
					{
						key_info = new KEY_INFO;
						m_CharacterMotion[nCnt]->key_info.emplace_back(key_info);
						nCntKey = 0;

						while (strcmp(cHeadText, "END_KEYSET") != 0)
						{
							fgets(cReadText, sizeof(cReadText), pFile);
							sscanf(cReadText, "%s", &cHeadText);

							if (strcmp(cHeadText, "FRAME") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_CharacterMotion[nCnt]->key_info[nCntKeySet]->nFram);
							}
							//高さ
							else if (strcmp(cHeadText, "HEIGHT") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDie, &cDie, &m_CharacterMotion[nCnt]->key_info[nCntKeySet]->fHeight);
							}
							//キーだったら
							else if (strcmp(cHeadText, "KEY") == 0)
							{
								//メモリ確保
								key = new KEY;

								//配列に追加
								m_CharacterMotion[nCnt]->key_info[nCntKeySet]->key.emplace_back(key);

								sscanf(cReadText, "%s %s %s %f %f %f", &cDie, &cDie, &cDie,
									&m_CharacterMotion[nCnt]->key_info[nCntKeySet]->key[nCntKey]->rot.x,
									&m_CharacterMotion[nCnt]->key_info[nCntKeySet]->key[nCntKey]->rot.y,
									&m_CharacterMotion[nCnt]->key_info[nCntKeySet]->key[nCntKey]->rot.z);

								//キー加算
								nCntKey++;
							}
						}
						nCntKeySet++;
					}
				}

			}

			//debug
			std::cout << "Motion Load - " << nCnt << m_LoadMotionFileName[nCnt] << NEWLINE;

			//ファイルを閉じる
			fclose(pFile);
		}
		else
		{
			//debug
			std::cout << "LOAD FAILED!!! MotionFile - " << nCnt << m_LoadMotionFileName[nCnt] << NEWLINE;

			//失敗
			MessageBox(NULL, "モーション読み込み失敗", m_LoadMotionFileName[nCnt], MB_OK | MB_ICONHAND);
		}
	}
}
//====================================================================
//モーション
//====================================================================
bool CModelSet::Motion(void)
{
	D3DXVECTOR3 Difrot;
	float Difpos;
	m_MotionOld = m_MotionType;

	if (m_MotionType != m_MotionOld)
	{
		m_Fram = 0;
		m_CntKeySet = 0;
	}
	if (m_MotionType != -1)
	{
		for (unsigned int nCnt = 0; nCnt < m_vModelList.size(); nCnt++)
		{
			if (m_Fram == 0)
			{
				if (m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->nFram != 0)
				{
					//移動量ROTの計算-------------------------------------■■■■■
					Difrot = (m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->key[nCnt]->rot - m_vModelList[nCnt]->GetRot());
					Difpos = m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->fHeight - m_vModelList[0]->GetPosition().y;
					if (Difrot.y > D3DX_PI)
					{
						Difrot.y -= D3DX_PI * 2;
					}
					else if (Difrot.y < -D3DX_PI)
					{
						Difrot.y += D3DX_PI * 2;
					}

					if (Difrot.x > D3DX_PI)
					{
						Difrot.x -= D3DX_PI * 2;
					}
					else if (Difrot.x < -D3DX_PI)
					{
						Difrot.x += D3DX_PI * 2;
					}

					m_rotBET[nCnt] = Difrot / (float)m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->nFram;

					m_HeightBet = Difpos / (float)m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->nFram;
					//----------------------------------------------------■■■■■
				}
				else
				{
					//m_vModelList[nCnt]->GetPosition() = m_CharacterMotion[m_MotionType].key_info[m_CntKeySet].key[nCnt].pos;
					//m_vModelList[nCnt]->GetRot()		 = m_CharacterMotion[m_MotionType].key_info[m_CntKeySet].key[nCnt].rot;
					//posBET[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					//rotBET[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
			}
			//フレーム移動--------------------------------------------■■■■■
			if (m_Fram <= m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->nFram)
			{
				//	m_vModelList[nCnt]->SetPosition(m_vModelList[nCnt]->GetPosition() + posBET[nCnt]);
				m_vModelList[nCnt]->SetRot(m_vModelList[nCnt]->GetRot() + m_rotBET[nCnt]);
				if (nCnt == 0)
				{
					m_vModelList[0]->GetPosition().y += m_HeightBet;
				}

				if (m_vModelList[nCnt]->GetRot().y > D3DX_PI)
				{
					m_vModelList[nCnt]->SetRot(m_vModelList[nCnt]->GetRot() - D3DXVECTOR3(0.0f, D3DX_PI * 2.0f, 0.0f));
				}
				else if (m_vModelList[nCnt]->GetRot().y < -D3DX_PI)
				{
					m_vModelList[nCnt]->SetRot(m_vModelList[nCnt]->GetRot() + D3DXVECTOR3(0.0f, D3DX_PI * 2.0f, 0.0f));
				}
				if (m_vModelList[nCnt]->GetRot().x > D3DX_PI)
				{
					m_vModelList[nCnt]->SetRot(m_vModelList[nCnt]->GetRot() - D3DXVECTOR3(D3DX_PI * 2.0f, 0.0f, 0.0f));
				}
				else if (m_vModelList[nCnt]->GetRot().x < -D3DX_PI)
				{
					m_vModelList[nCnt]->SetRot(m_vModelList[nCnt]->GetRot() + D3DXVECTOR3(D3DX_PI * 2.0f, 0.0f, 0.0f));
				}
			}
			//--------------------------------------------------------■■■■■
		}
		if (m_Fram == m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->nFram)
		{
			m_CntKeySet++;
			m_Fram = 0;

			//キーセット数が規定値と同じになったら--------------------■■■■■
			if (m_CntKeySet == m_CharacterMotion[m_MotionType]->nNumKey)
			{
				//ループしないとき------------------------------------■■■■■
				if (m_CharacterMotion[m_MotionType]->nLoop == 0)
				{
						m_CntKeySet = 0;
						m_Fram = m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->nFram;
						return true;
				}
				//ループするとき--------------------------------------■■■■■
				else if (m_CharacterMotion[m_MotionType]->nLoop == 1)
				{
					m_CntKeySet = 0;
					return false;
				}
			}
		}
		//フレーム数が規定値と同じではないとき------------------------■■■■■
		else
		{
			//モーションをするとき
			if (m_bMotion)
			{
				m_Fram++;
			}
		}
	}
	else
	{
		m_Fram = 0;
		m_CntKeySet = 0;
	}
	return false;
}
//====================================================================
//全部のモデルのDisp情報設定
//====================================================================
void CModelSet::SetAllModelDisp(bool bDisp)
{
	//モデル数分
	for (unsigned int nCnt = 0; nCnt < m_vModelList.size(); nCnt++)
	{
		if (m_vModelList[nCnt])
		{
			m_vModelList[nCnt]->SetDisp(bDisp);
		}
	}
}
//====================================================================
//オフセットの読み込み
//====================================================================
void CModelSet::LoadOffset(CHARACTER_TYPE nType)
{
	char cReadText[1080];	//文字として読み取り用
	char cHeadText[1080];	//比較する用
	char cDie[1080];		//不要な文字
	int nCnt = 0;
	FILE *pFile;

	cReadText[0] = '\0';
	cHeadText[0] = '\0';
	D3DXVECTOR3 pos;
	int nIdxParent;			//親のインデックス
	int nIdx;				//モデルのインデックス
	int type;

	pFile = fopen(m_LoadOffsetFileName[nType], "r");
	if (pFile != NULL)
	{
		while (strcmp(cHeadText, "MODEL_OFFSET_END") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile);
			sscanf(cReadText, "%s", &cHeadText);
			//配置するモデルの最大数の読み込み
			if (strcmp(cHeadText, "SET_START") == 0)
			{
				//END_SETが来るまでループ
				while (strcmp(cHeadText, "SET_END") != 0)
				{
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s", &cHeadText);
					//MODEL_TYPEだったら
					if (strcmp(cHeadText, "MODEL_TYPE") == 0)
					{
						sscanf(cReadText, "%s %s %d",
							&cDie, &cDie,
							&type);
					}
					//IDXだったら
					else if (strcmp(cHeadText, "INDEX") == 0)
					{
						sscanf(cReadText, "%s %s %d",
							&cDie, &cDie,
							&nIdx);
					}
					//PARENTだったら
					else if (strcmp(cHeadText, "PARENT") == 0)
					{
						sscanf(cReadText, "%s %s %d",
							&cDie, &cDie,
							&nIdxParent);
					}
					//POSだったら
					else if (strcmp(cHeadText, "POS") == 0)
					{
						sscanf(cReadText, "%s %s %f %f %f",
							&cDie, &cDie,
							&pos.x,
							&pos.y,
							&pos.z);
					}
					//SET_ENDが来たら作成し追加
					else if (strcmp(cHeadText, "SET_END") == 0)
					{
						CModel *pModel = CModel::Create(type, nIdx);
						pModel->SetPosition(pos);
						pModel->SetParentIdx(nIdxParent);
						if (nIdxParent == -1)
						{
							pModel->SetParent(NULL);
						}
						else
						{
							pModel->SetParent(m_vModelList[nIdxParent]);
						}
						m_vModelList.emplace_back(pModel);
					}
				}
			}
		}

		fclose(pFile);
	}
	else
	{

	}

}
//====================================================================
//強制的に更新
//====================================================================
void CModelSet::ForcedUpdate()
{
	//モデル数分繰り返す
	for (size_t nCntKey = 0; nCntKey < m_vModelList.size(); nCntKey++)
	{
		//モーションの回転の決定先取得
		m_vModelList[nCntKey]->SetRot(m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->key[nCntKey]->rot);
	}

	m_vModelList[0]->GetPosition().y = m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->fHeight;
}
//====================================================================
//開放
//====================================================================
void CModelSet::CharacterUnLoad(void)
{
	if (!m_CharacterMotion.empty())
	{
		for (size_t nCnt = 0; nCnt < m_CharacterMotion.size(); nCnt++)
		{
			if (!m_CharacterMotion[nCnt]->key_info.empty())
			{
				for (size_t nCntinfo = 0; nCntinfo < m_CharacterMotion[nCnt]->key_info.size(); nCntinfo++)
				{
					if (!m_CharacterMotion[nCnt]->key_info[nCntinfo]->key.empty())
					{
						for (size_t nCntkey = 0; nCntkey < m_CharacterMotion[nCnt]->key_info[nCntinfo]->key.size(); nCntkey++)
						{
							delete m_CharacterMotion[nCnt]->key_info[nCntinfo]->key[nCntkey];
							m_CharacterMotion[nCnt]->key_info[nCntinfo]->key[nCntkey] = nullptr;
						}
					}
					delete m_CharacterMotion[nCnt]->key_info[nCntinfo];
					m_CharacterMotion[nCnt]->key_info[nCntinfo] = nullptr;

				}
			}
			delete m_CharacterMotion[nCnt];
			m_CharacterMotion[nCnt] = nullptr;
		}
	}
	m_CharacterMotion.clear();
}
//====================================================================
//モデルセットのクリエイト
//====================================================================
CModelSet * CModelSet::CreateModelSet(void)
{
	CModelSet *pModelSet;
	pModelSet = new CModelSet();
	pModelSet->Init();
	return pModelSet;
}
//====================================================================
//回転の計算
//====================================================================
void CModelSet::CalcRotation()
{

	//目標点と現在の差分（回転）
	float diffRot = m_rotDest.y - m_rot.y;

	//3.14の超過分の初期化（回転）
	CHossoLibrary::CalcRotation(m_rot.y);
	CHossoLibrary::CalcRotation(diffRot);

	//求めた差分だけ追従する計算
	m_rot.y += diffRot * ADD_ROTATION_SPEED;
}
//====================================================================
//モーションタイプの取得
//====================================================================
CModelSet::CHARACTER_MOTION_STATE &CModelSet::GetMotionType(void)
{
	return m_MotionType;
}
//====================================================================
//前のモーションタイプの取得
//====================================================================
CModelSet::CHARACTER_MOTION_STATE CModelSet::GetMotionOldType(void)
{
	return m_MotionOld;
}
//====================================================================
//モーションしてるかどうか取得
//====================================================================
bool & CModelSet::GetMotion()
{
	return m_bMotion;
}
//====================================================================
//キーセットの取得
//====================================================================
int &CModelSet::GetKeySet(void)
{
	return m_CntKeySet;
}
//====================================================================
//フレームの取得
//====================================================================
int &CModelSet::GetFram(void)
{
	return m_Fram;

}
//====================================================================
//モデルのリストを返す	参照渡し
//====================================================================
std::vector<CModel*>& CModelSet::GetCharacterModelList()
{
	return m_vModelList;
}
//====================================================================
//モデルパーツのリストを返す	参照渡し
//====================================================================
//CModel* CModelSet::GetCharacterModelPartsList(int nCnt)
//{
//	return m_vModelList[nCnt];
//}
//====================================================================
//腰の高さの取得
//====================================================================
float CModelSet::GetHeightBet(void)
{
	return m_HeightBet;
}
//====================================================================
//前のモーションタイプの設定
//====================================================================
void CModelSet::SetMotionOldType(CHARACTER_MOTION_STATE type)
{
	m_MotionOld = type;
}
//====================================================================
//キーセットの設定
//====================================================================
void CModelSet::SetKeySet(int keyset)
{
	m_CntKeySet = keyset;
}
//====================================================================
//フレームの設定
//====================================================================
void CModelSet::SetFram(int fram)
{
	m_Fram = fram;
}
//====================================================================
//モーションするかしないか
//====================================================================
void CModelSet::SetUseMotion(bool use)
{
	m_bMotion = use;
}
//====================================================================
//キャラクタータイプ設定
//====================================================================
void CModelSet::SetCharacterType(CHARACTER_TYPE CharaType)
{
	m_CharaType = CharaType;
}
//====================================================================
//キャラクタータイプの設定
//====================================================================
CModelSet::CHARACTER_TYPE CModelSet::GetCharacterType()
{
	return m_CharaType;
}
//====================================================================
//回転の取得
//====================================================================
D3DXVECTOR3 &CModelSet::GetRot(void)
{
	return m_rot;
}
