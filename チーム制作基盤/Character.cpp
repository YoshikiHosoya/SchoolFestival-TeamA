//=============================================================================
// キャラクターモデル総括処理 [Character.cpp] : NORI
//=============================================================================
#include "Character.h"
#include "inputKeyboard.h"
#include "model.h"
#include "game.h"
#include "fade.h"
#include "createmap.h"
#include "Xinput.h"

#define MAX_RAY_LENGTH (35)		//Rayの最大の長さ
#define RAY_FIRST_POINT (40.0f)	//Rayの始点
char *CCharacter::m_LoadFileName = { "data/Load/LoadOffset01.txt" };

CCharacter::CCharacter(OBJ_TYPE type) :CScene(type)
{
	SetObjType(OBJTYPE_PLAYER);
}

CCharacter::~CCharacter()
{
}
//====================================================================
//初期化
//====================================================================
HRESULT CCharacter::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Life = 50;
	m_state = CHARACTER_STATE_NORMAL;
	LoadOffset();
	return S_OK;
}
//====================================================================
//終了
//====================================================================
void CCharacter::Uninit(void)
{
}
//====================================================================
//更新
//====================================================================
void CCharacter::Update(void)
{
	CKeyboard *key;
	key = CManager::GetInputKeyboard();
	m_posold = m_pos;
	m_MotionOld = m_MotionType;
	//慣性の抵抗
	m_move.x += (0 - m_move.x)* 0.2f;
	m_move.z += (0 - m_move.z)* 0.2f;
	m_move.y -= 1;
	m_pos += m_move;

	if (m_pos.y < 0)
	{
		m_move.y = 0;
		m_pos.y = 0;
	}
	//目標点と現在の差分（回転）
	float diffRot = m_rotDest.y - m_rot.y;
	//3.14の超過分の初期化（回転）
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}
	if (diffRot > D3DX_PI)
	{
		diffRot -= D3DX_PI * 2;
	}
	else if (diffRot < -D3DX_PI)
	{
		diffRot += D3DX_PI * 2;
	}
	//ステータスの処理
	switch (m_state)
	{
	case CHARACTER_STATE_NORMAL:
		break;
	case CHARACTER_STATE_DAMAGE:
		m_nStateCnt++;
		if (m_nStateCnt % 60 == 0)
		{
			m_state = CHARACTER_STATE_NORMAL;
		}

		break;
	case CHARACTER_STATE_INVINCIBLE:
		m_nStateCnt++;
		if (m_nStateCnt % 30 == 0)
		{
			m_state = CHARACTER_STATE_NORMAL;
		}
		break;
	}
	//死んだとき
	if (m_Life <= 0)
	{
		CFADE::SetFade(CManager::MODE_RESULT);
		Rerease();
	}
	m_MotionType = PLAYER_MOTION_WALK;
	RayCollision();
}
//====================================================================
//描画
//====================================================================
void CCharacter::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y,
		m_rot.x,
		m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x,
		m_pos.y,
		m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxTrans);

	//モデルの描画
	for (unsigned int nCnt = 0; nCnt < m_vModelList.size(); nCnt++)
	{
		m_vModelList[nCnt]->Draw(m_mtxWorld);
	}
}
//====================================================================
//モデルのクリエイト
//====================================================================
CCharacter *CCharacter::Create(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	CCharacter*pSceneX;
	pSceneX = new CCharacter(OBJTYPE_PLAYER);
	pSceneX->Init();
	return pSceneX;
}
//====================================================================
//モデルのムーヴ
//====================================================================
void CCharacter::Move(float move, float fdest)
{
	m_move.x += sinf(move * -D3DX_PI) * 1.0f;
	m_move.z += cosf(move * -D3DX_PI) * 1.0f;
	m_rotDest.y = fdest *  D3DX_PI;
}
//====================================================================
//ポジションの設定
//====================================================================
void CCharacter::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//====================================================================
//前のポジションの設定
//====================================================================
void CCharacter::SetPotisionOld(D3DXVECTOR3 posOld)
{
	m_posold = posOld;
}
//====================================================================
//ムーブの設定
//====================================================================
void CCharacter::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}
//====================================================================
//回転の設定
//====================================================================
void CCharacter::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//====================================================================
//ダメージを受けた時の処理
//====================================================================
void CCharacter::AddDamage(int Damage)
{
	m_state = CHARACTER_STATE_DAMAGE;
	int Life = GetLife();
	Life -= Damage;
	SetLife(Life);
}
//====================================================================
//回転の差分の設定
//====================================================================
void CCharacter::SetRotDest(D3DXVECTOR3 rotDest)
{
	m_rotDest = rotDest;
}
//====================================================================
//体力の設定
//====================================================================
void CCharacter::SetLife(int Life)
{
	m_Life = Life;
}
//====================================================================
//キャラ状態の設定
//====================================================================
void CCharacter::SetState(CHARACTER_STATE state)
{
	m_state = state;
}
//====================================================================
//マトリックスの設定
//====================================================================
void CCharacter::SetMtxWorld(D3DXMATRIX mtxWorld)
{
	m_mtxWorld = mtxWorld;
}
//====================================================================
//回転の差分の取得
//====================================================================
D3DXVECTOR3 CCharacter::GetRotDest(void)
{
	return m_rotDest;
}
//====================================================================
//キャラクターの状態の取得
//====================================================================
CCharacter::CHARACTER_STATE CCharacter::GetCharacterState(void)
{
	return m_state;
}
//====================================================================
//ポジションの取得
//====================================================================
D3DXVECTOR3 CCharacter::GetPosition(void)
{
	return m_pos;
}
//====================================================================
//前のポジションの取得
//====================================================================
D3DXVECTOR3 CCharacter::GetPositionOld(void)
{
	return m_posold;
}
//====================================================================
//ムーブの取得
//====================================================================
D3DXVECTOR3 &CCharacter::GetMove(void)
{
	return m_move;
}
//====================================================================
//回転の取得
//====================================================================
D3DXVECTOR3 CCharacter::GetRot(void)
{
	return m_rot;
}
//====================================================================
//体力の取得
//====================================================================
int CCharacter::GetLife(void)
{
	return m_Life;
}
//====================================================================
//マトリックスの取得
//====================================================================
D3DXMATRIX CCharacter::GetMtxWorld(void)
{
	return m_mtxWorld;
}
//====================================================================
//当たり判定
//====================================================================
void CCharacter::RayCollision(void)
{
	CCreateMap *pCreateMap;
	pCreateMap = CManager::GetGame()->GetCreateMap();
	// 地形判定
	BOOL  bIsHit = false;
	float fLandDistance = 0;
	DWORD dwHitIndex = -1;
	float fHitU = 0;
	float fHitV = 0;
	D3DXMATRIX invmat;		//	逆行列を格納する変数
	D3DXVECTOR3 m_posAfter;	//	逆行列で出した終点情報を格納する
	D3DXVECTOR3 m_posBefore;//	終点情報を格納する
	D3DXVECTOR3 direction;	//	変換後の位置、方向を格納する変数：
	std::vector<float> vDistance;//長さの配列保存
	float fData = 0.0f;
	for (int nCnt = 0; nCnt < pCreateMap->GetMaxModel(); nCnt++)
	{
		D3DXMatrixInverse(&invmat, NULL, pCreateMap->GetModel(nCnt)->GetMatrix());	//	逆行列の取得
																					//	逆行列を使用し、レイ始点情報を変換　位置と向きで変換する関数が異なるので要注意
		D3DXVec3TransformCoord(&m_posBefore, &D3DXVECTOR3(m_pos.x, m_pos.y + RAY_FIRST_POINT, m_pos.z), &invmat);
		//	レイ終点情報を変換
		D3DXVec3TransformCoord(&m_posAfter, &D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), &invmat);
		//	レイ方向情報を変換
		D3DXVec3Normalize(&direction, &(m_posAfter - m_posBefore));
		//Rayを飛ばす
		D3DXIntersect(pCreateMap->GetMesh(nCnt), &m_posBefore, &direction, &bIsHit, &dwHitIndex, &fHitU, &fHitV, &fLandDistance, NULL, NULL);
		if (bIsHit == TRUE)
		{
			CDebugProc::Print("当たってるよ\n");
			vDistance.emplace_back(fLandDistance); //長さの保存追加
		}
		else
		{
			CDebugProc::Print("当たって無いよ\n");
		}
	}
	//Rayのヒットした物があったとき
	if (!vDistance.empty())
	{
		//最初の比較対象
		fData = vDistance[0];
		for (unsigned int nCnt = 0; vDistance.size() > nCnt; nCnt++)
		{
			if (vDistance[nCnt] < fData)
			{
				//比較対象が小さかったら代入
				fData = vDistance[nCnt];
			}
		}
		if (fData < MAX_RAY_LENGTH)//Rayの長さの指定条件
		{
			m_pos.y = m_pos.y - fData + MAX_RAY_LENGTH;
			m_move.y = 0;
		}
	}
	CDebugProc::Print("Rayの長さ(%f)\n", fLandDistance);
	CDebugProc::Print("キャラの高さ(%f)\n", m_pos.y);
	CDebugProc::Print("Rayからキャラの位置を引いた値(%f)\n", m_pos.y - fLandDistance);
}
//====================================================================
//モーションのロード
//====================================================================
void CCharacter::LoadMotion(void)
{
	//ファイルポイント
	FILE *pFile;
	int nCntMotion = 0;		//モーションの数
	int nCntModel = 0;		//モデルのカウント
	int nCntKeySet = 0;		//フーレームの分割数
	int nCntKey = 0;		//パーツの番号
	char cReadText[128];	//文字として読み取り用
	char cHeadText[128];	//比較する用
	char cDie[128];			//不要な文字

							//ファイルを開く
	pFile = fopen("data/Load/PlayerMotion.txt", "r");

	//あいたら
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
				//モーションセットが来たら
				if (strcmp(cHeadText, "MOTIONSET") == 0)
				{
					//フレーム分割数の初期化
					nCntKeySet = 0;
					//エンドモーションセットが来るまでループ
					while (strcmp(cHeadText, "END_MOTIONSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile);//一文を抜き取る
						sscanf(cReadText, "%s", &cHeadText);
						//ループするかどうかの情報読み込み
						if (strcmp(cHeadText, "LOOP") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_PlayerMotion[nCntMotion].nLoop);
						}
						else if (strcmp(cHeadText, "NUM_KEY") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_PlayerMotion[nCntMotion].nNumKey);
						}
						else if (strcmp(cHeadText, "KEYSET") == 0)
						{
							nCntKey = 0;//キー情報初期化
							while (strcmp(cHeadText, "END_KEYSET") != 0)
							{
								fgets(cReadText, sizeof(cReadText), pFile);
								sscanf(cReadText, "%s", &cHeadText);

								if (strcmp(cHeadText, "FRAME") == 0)
								{
									sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_PlayerMotion[nCntMotion].key_info[nCntKeySet].nFram);
								}
								else if (strcmp(cHeadText, "KEY") == 0)
								{
									while (strcmp(cHeadText, "END_KEY") != 0)
									{
										fgets(cReadText, sizeof(cReadText), pFile);
										sscanf(cReadText, "%s", &cHeadText);
										if (strcmp(cHeadText, "POS") == 0)
										{
											//sscanf(cReadText, "%s %s %f %f %f",
											//	&cDie, &cDie,
											//	&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].pos.x,
											//	&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].pos.y,
											//	&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].pos.z);

											//m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].pos += m_vModelList[nCntKey]->GetPosition();
										}
										else if (strcmp(cHeadText, "ROT") == 0)
										{
											sscanf(cReadText, "%s %s %f %f %f",
												&cDie, &cDie,
												&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].rot.x,
												&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].rot.y,
												&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].rot.z);
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
		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		MessageBox(NULL, "モデルデータの読み込み失敗", "警告", MB_ICONWARNING);
	}
}
//====================================================================
//モーション
//====================================================================
void CCharacter::Moation(void)
{
	CKeyboard *key;
	key = CManager::GetInputKeyboard();
	D3DXVECTOR3 Difrot;
	if (m_MotionType != m_MotionOld)
	{
		m_Fram = 0;
		m_CntKeySet = 0;
	}
	for (unsigned int nCnt = 0; nCnt < m_vModelList.size(); nCnt++)
	{
		if (m_Fram == 0)
		{
			if (m_PlayerMotion[m_MotionType].key_info[m_CntKeySet].nFram != 0)
			{
				//移動量ROTの計算-------------------------------------■■■■■
				Difrot = (m_PlayerMotion[m_MotionType].key_info[m_CntKeySet].key[nCnt].rot - m_vModelList[nCnt]->GetRot());

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

				rotBET[nCnt] = Difrot / (float)m_PlayerMotion[m_MotionType].key_info[m_CntKeySet].nFram;
				//----------------------------------------------------■■■■■
			}
			else
			{
				//m_vModelList[nCnt]->GetPosition() = m_PlayerMotion[m_MotionType].key_info[m_CntKeySet].key[nCnt].pos;
				//m_vModelList[nCnt]->GetRot()		 = m_PlayerMotion[m_MotionType].key_info[m_CntKeySet].key[nCnt].rot;
				//posBET[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				//rotBET[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}

		//フレーム移動--------------------------------------------■■■■■
		if (m_Fram <= m_PlayerMotion[m_MotionType].key_info[m_CntKeySet].nFram)
		{
			//	m_vModelList[nCnt]->SetPosition(m_vModelList[nCnt]->GetPosition() + posBET[nCnt]);
			m_vModelList[nCnt]->SetRot(m_vModelList[nCnt]->GetRot() + rotBET[nCnt]);
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
	if (m_Fram == m_PlayerMotion[m_MotionType].key_info[m_CntKeySet].nFram)
	{
		m_CntKeySet++;
		m_Fram = 0;
		//キーセット数が規定値と同じになったら--------------------■■■■■
		if (m_CntKeySet == m_PlayerMotion[m_MotionType].nNumKey)
		{
			//ループしないとき------------------------------------■■■■■
			if (m_PlayerMotion[m_MotionType].nLoop == 0)
			{
				m_CntKeySet = 0;
				m_MotionType = 0;
				m_Fram = m_PlayerMotion[m_MotionType].key_info[m_CntKeySet].nFram;
			}
			//ループするとき--------------------------------------■■■■■
			else if (m_PlayerMotion[m_MotionType].nLoop == 1)
			{
				m_CntKeySet = 0;
				m_MotionType = 0;
			}
		}
	}
	//フレーム数が規定値と同じではないとき------------------------■■■■■
	else
	{
		m_Fram++;
	}
}
//====================================================================
//オフセットの読み込み
//====================================================================
void CCharacter::LoadOffset(void)
{
	char cReadText[1080];	//文字として読み取り用
	char cHeadText[1080];	//比較する用
	char cDie[1080];		//不要な文字
	int nCnt = 0;
	FILE *pFile;

	D3DXVECTOR3 pos;
	int nIdxParent;			//親のインデックス
	int nIdx;				//モデルのインデックス
	int type;

	pFile = fopen(m_LoadFileName, "r");
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
						CModel *pModel = CModel::Create(type , nIdx);
						pModel->SetPosition(pos);
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
