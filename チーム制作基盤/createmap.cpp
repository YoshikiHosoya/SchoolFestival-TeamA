//　　　createmap.cpp		
#include "main.h"
#include "createmap.h"
#include "debugproc.h"
#include "Player.h"
#include "model.h"
#include <stdio.h>
char *CCreateMap::m_LoadFileName[LOOAD_MAP_MAX] =
{
	{ "data/Load/Map.txt" },
	{ "data/Load/Map.txt" },
	{ "data/Load/Map03.txt" },
	{ "data/Load/MapBoss.txt" },
};
//====================================================================
//コンストラクタ
//====================================================================
CCreateMap::CCreateMap(OBJ_TYPE type) :CScene(type)
{
	SetObjType(OBJTYPE_CREATE);
	m_map.emplace_back(CModel::Create(CModel::MAP_MODEL,0));
}
//====================================================================
//デストラクタ
//====================================================================
CCreateMap::~CCreateMap()
{
}
//====================================================================
//初期化
//====================================================================
HRESULT CCreateMap::Init(void)
{
	m_pos	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col	= D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_vec.clear();
	return S_OK;
}
//====================================================================
//終了
//====================================================================
void CCreateMap::Uninit(void)
{
}
//====================================================================
//更新
//====================================================================
void CCreateMap::Update(void)
{
	CKeyboard *key;
	key = CManager::GetInputKeyboard();
	//プレイヤー座標の取得
	D3DXVECTOR3 pPos;
	int pState;
	CScene *pScene;
	pScene = CScene::GetScene(OBJTYPE_PLAYER);
	if (pScene != NULL)
	{
		pPos = ((CPlayer*)pScene)->GetPosition();
		pState = ((CPlayer*)pScene)->GetDebugState();

		if (pState == CPlayer::DEBUG_CREATE_MAP)
		{
			//モデルタイプを前のモデルに変更
			if (key->GetKeyboardTrigger(DIK_1))
			{
				if (m_type > 0)
				{
					m_type--;
				}
			}
			//モデルタイプを次のモデルに変更
			if (key->GetKeyboardTrigger(DIK_2))
			{
				if (m_type < CModel::MODEL_MAP_MAX - 1)
				{
					m_type++;
				}
			}
			//モデルの設置
			if (key->GetKeyboardTrigger(DIK_RETURN))
			{
				//末尾に要素を追加する
				m_vec.emplace_back(CModel::Create(CModel::MAP_MODEL, m_type));
				m_vec[m_vec.size() - 1]->SetPosition(D3DXVECTOR3(pPos.x, pPos.y, pPos.z));
				m_vec[m_vec.size() - 1]->SetSize(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
			}
			//モデルの位置をセーブ
			if (key->GetKeyboardTrigger(DIK_F9))
			{
				Save();
			}
			//モデルのロード
			if (key->GetKeyboardTrigger(DIK_F7))
			{
				Load(0);
			}

			if (m_map.size() > 0)
			{
				m_map[m_map.size() - 1]->SetPosition(D3DXVECTOR3(pPos.x, pPos.y, pPos.z));
				m_map[m_map.size() - 1]->SetSize(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
				m_map[0]->SetType(m_type);
			}
			CDebugProc::Print("[設置の操作]\n");
			CDebugProc::Print("マップのセーブ    :[F9]\n");
			CDebugProc::Print("マップのロード     :[F7]\n");
			CDebugProc::Print("モデルの切り替え:[1]:[2]\n");
			CDebugProc::Print("モデルの移動      :[0]\n");
			CDebugProc::Print("モデルの削除      :[3]\n");
			CDebugProc::Print("モデルの設置      :[ENTER]\n");
			CDebugProc::Print("上昇                   :[SPACE]\n");
			CDebugProc::Print("下向                   :[LCTRL]\n");
		}
		//if (pState == CPlayer::DEBUG_CREATE_ENEMY)
		//{
		//	if (m_type > CEnemy::ENEMY_TYPE_MAX - 1)
		//	{
		//		m_type = 0;
		//	}
		//	//モデルタイプを前のモデルに変更
		//	if (key->GetKeyboardTrigger(DIK_1))
		//	{
		//		if (m_type > 0)
		//		{
		//			m_type--;
		//		}
		//	}
		//	//モデルタイプを次のモデルに変更
		//	if (key->GetKeyboardTrigger(DIK_2))
		//	{
		//		if (m_type < CEnemy::ENEMY_TYPE_MAX - 1)
		//		{
		//			m_type++;
		//		}
		//	}
		//	if (key->GetKeyboardTrigger(DIK_RETURN))
		//	{
		//		//末尾に要素を追加する
		//		m_Enemy.emplace_back(CEnemy::Create(m_type));
		//		m_Enemy[m_Enemy.size() - 1]->SetPosition(D3DXVECTOR3(pPos.x, pPos.y - 50, pPos.z));
		//	}
		//	//モデルの位置をセーブ
		//	if (key->GetKeyboardTrigger(DIK_F9))
		//	{
		//		Save();
		//	}
		//	CDebugProc::Print("[設置の操作]\n");
		//	CDebugProc::Print("マップのセーブ    :[F9]\n");
		//	CDebugProc::Print("エネミーの切り替え:[1]:[2]\n");
		//	CDebugProc::Print("エネミーの設置      :[ENTER]\n");
		//	CDebugProc::Print("上昇                   :[SPACE]\n");
		//	CDebugProc::Print("下向                   :[LCTRL]\n");
		//	CDebugProc::Print("エネミータイプ%d\n", m_type);
		//}
	}
	if (m_Enemy.size() == 0)
	{
		for (unsigned int nCnt = 0; nCnt < m_vec.size(); nCnt++)
		{
			if (m_vec[nCnt]->GetType() == CModel::MODEL_MAP_BLOCK02)
			{
				m_vec.erase(m_vec.begin() + nCnt);//最初から[nCnt]番目を消去
			}
		}
	}
	else
	{
		CDebugProc::Print("[F2]でマップエディタ\n");
	}
	//for (unsigned int nCnt = 0; nCnt < m_Enemy.size(); nCnt++)
	//{
	//	if (m_Enemy[nCnt] != nullptr)
	//	{
	//		if (m_Enemy[nCnt]->GetLife() <= 0)
	//		{
	//			m_Enemy[nCnt]->Uninit();
	//			m_Enemy[nCnt]->Rerease();
	//			m_Enemy.erase(m_Enemy.begin() + nCnt);
	//		}
	//	}
	//}
	Collision();
}
//====================================================================
//描画
//====================================================================
void CCreateMap::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	int pState;
	CScene *pScene;
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	pScene = CScene::GetScene(OBJTYPE_PLAYER);
	if (pScene != NULL)
	{
		pState = ((CPlayer*)pScene)->GetDebugState();


		if (pState == CPlayer::DEBUG_CREATE_MAP)
		{
			for (unsigned int nCnt = 0; nCnt < m_map.size(); nCnt++)
			{
				m_map[nCnt]->Draw(m_mtxWorld);
			}
		}
	}
	//モデルの描画
	for (unsigned int nCnt = 0; nCnt < m_vec.size(); nCnt++)
	{
		m_vec[nCnt]->Draw(m_mtxWorld);
	}
		CDebugProc::Print("[モデル数]\n%d\n", m_vec.size());
		CDebugProc::Print("[エネミー数]\n%d\n", m_Enemy.size());
}
//====================================================================
//クリエイト
//====================================================================
CCreateMap *CCreateMap::Create(int type)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	CCreateMap*pCreateMap;
	pCreateMap= new CCreateMap(OBJTYPE_CREATE);
	pCreateMap->Init();
	pCreateMap->Load(type);
	return pCreateMap;
}
//====================================================================
//当たり判定
//====================================================================
bool CCreateMap::Collision(void)
{
	CKeyboard *key;
	key = CManager::GetInputKeyboard();
	int pState;
	CScene *pScene;
	pScene = CScene::GetScene(OBJTYPE_PLAYER);
	if (pScene != NULL)
	{
		pState = ((CPlayer*)pScene)->GetDebugState();

		if (pState == CPlayer::DEBUG_CREATE_MAP)
		{
			for (unsigned int nCnt = 0; nCnt < m_vec.size(); nCnt++)
			{
				//モデルの座標の取得
				D3DXVECTOR3 ModelPos = m_vec[nCnt]->GetPosition();//モデルの位置の代入
				//プレイヤー座標の取得
				D3DXVECTOR3 pPos;
				CScene *pScene;
				pScene = CScene::GetScene(OBJTYPE_PLAYER);
				if (pScene != NULL)
				{
					pPos = ((CPlayer*)pScene)->GetPosition();//プレイヤーの位置の代入
					if (pPos.x + 100 > ModelPos.x && pPos.x - 100 < ModelPos.x &&
						pPos.z + 100 > ModelPos.z && pPos.z - 100 < ModelPos.z &&
						pPos.y > ModelPos.y && pPos.y - 250 < ModelPos.y)
					{
						//触れているモデルの移動
						if (set == false)
						{
							if (key->GetKeyboardPress(DIK_0))
							{
								set = true;
								m_vec[nCnt]->SetPosition(D3DXVECTOR3(pPos.x, pPos.y - 150, pPos.z));
							}
						}
						else
						{
							set = false;
						}
						//触れているモデルの消去
						if (key->GetKeyboardTrigger(DIK_3))
						{
							if (0 < m_vec.size())
							{
								m_vec.erase(m_vec.begin() + nCnt);//最初から[nCnt]番目を消去
							}
						}
						CDebugProc::Print("モデル何番目：%d\n", nCnt);
					}
				}
			}
		}
	}
	return false;
}

//bool CCreateMap::CollisionModel(D3DXVECTOR3 *size, D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move)
//{
//	bool bLand = false;
//	int ntype;
//	for (int nCount = 0; nCount < m_vec.size(); nCount++)
//	{
//		ntype = m_vec[nCount]->GetType();
//		//モデルの座標の取得
//		D3DXVECTOR3 ModelPos = m_vec[nCount]->GetPosition();//モデルの位置の代入
//			//---------------------------------------------------------■■■■■
//		if (pos->z + size->z / 2 > m_vec[nCount]->GetvtxMin(ntype).z + ModelPos.z  &&
//			pos->z - size->z / 2 < m_vec[nCount]->GetvtxMax(ntype).z + ModelPos.z)
//		{
//			if (pos->x + size->x / 2 > m_vec[nCount]->GetvtxMin(ntype).x + ModelPos.x &&
//				pos->x - size->x / 2 < m_vec[nCount]->GetvtxMax(ntype).x + ModelPos.x)
//			{
//				if (pos->y + size->y / 2 > m_vec[nCount]->GetvtxMin(ntype).y + ModelPos.y&&
//					pos->y - size->y / 2 < m_vec[nCount]->GetvtxMax(ntype).y + ModelPos.y)
//				{
//					if (ntype != CModel::MODEL_MAP_BLOCK)
//					{
//						//プレイヤーがモデルの←壁に当たった時の判定
//						if (posOld->x - size->x / 2 >= m_vec[nCount]->GetvtxMax(ntype).x + ModelPos.x &&
//							pos->x - size->x / 2 < m_vec[nCount]->GetvtxMax(ntype).x + ModelPos.x)
//						{
//							pos->x = m_vec[nCount]->GetvtxMax(ntype).x + ModelPos.x + size->x / 2;
//							move->x = 0.0f;
//							//((CPlayer*)pScene)->SetPosition(pos);
//						}
//						//プレイヤーがモデル→壁に当たった時の判定
//						if (posOld->x + size->x / 2 <= m_vec[nCount]->GetvtxMin(ntype).x + ModelPos.x&&
//							pos->x + size->x / 2 > m_vec[nCount]->GetvtxMin(ntype).x + ModelPos.x)
//						{
//							pos->x = m_vec[nCount]->GetvtxMin(ntype).x + ModelPos.x - size->x / 2;
//							move->x = 0.0f;
//							//((CPlayer*)pScene)->SetPosition(pos);
//						}
//						//プレイヤーがモデルの↓壁に当たった時の判定
//						if (posOld->z - size->z / 2 >= m_vec[nCount]->GetvtxMax(ntype).z + ModelPos.z &&
//							pos->z - size->z / 2 < m_vec[nCount]->GetvtxMax(ntype).z + ModelPos.z)
//						{
//							pos->z = m_vec[nCount]->GetvtxMax(ntype).z + ModelPos.z + size->z / 2;
//							move->z = 0.0f;
//							//((CPlayer*)pScene)->SetPosition(pos);
//						}
//						//プレイヤーがモデル↑壁に当たった時の判定
//						if (posOld->z + size->z / 2 <= m_vec[nCount]->GetvtxMin(ntype).z + ModelPos.z &&
//							pos->z + size->z / 2 > m_vec[nCount]->GetvtxMin(ntype).z + ModelPos.z)
//						{
//							pos->z = m_vec[nCount]->GetvtxMin(ntype).z + ModelPos.z - size->z / 2;
//							move->z = 0.0f;
//							//((CPlayer*)pScene)->SetPosition(pos);
//						}
//
//						//プレイヤーがモデルの上に乗った時の判定
//						if (posOld->y >= m_vec[nCount]->GetvtxMax(ntype).y + ModelPos.y &&
//							pos->y < m_vec[nCount]->GetvtxMax(ntype).y + ModelPos.y)
//						{
//							pos->y = m_vec[nCount]->GetvtxMax(ntype).y + ModelPos.y;
//							move->y = 0.0f;
//							//((CPlayer*)pScene)->SetPosition(pos);
//							bLand = true;
//						}
//					}
//					if (ntype == CModel::MODEL_MAP_BLOCK)
//					{
//					}
//					CScene *pScene;
//					pScene = CScene::GetScene(OBJTYPE_PLAYER);
//					if (pScene != NULL)
//					{
//						D3DXVECTOR3 PlayerPos = ((CPlayer*)pScene)->GetPosition();
//						if (ntype == CModel::MODEL_MAP_HPPOTION)
//						{
//							((CPlayer*)pScene)->SetHPPotionCnt(1);
//							m_vec.erase(m_vec.begin() + nCount);//最初から[nCnt]番目を消去
//							CSound::PlaySound(CSound::SOUND_LABEL_SE_POTIONGET);
//							CParticle *pParticle;
//							pParticle = CParticle::Create(CParticle::PARTICLE_TYPE_DEFAULT,
//								D3DXVECTOR3(PlayerPos.x, PlayerPos.y + 30, PlayerPos.z),
//								D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f),
//								40, 50, 30, 2);
//						}
//						else if (ntype == CModel::MODEL_MAP_MPPOTION)
//						{
//							((CPlayer*)pScene)->SetMPPotionCnt(1);
//							m_vec.erase(m_vec.begin() + nCount);//最初から[nCnt]番目を消去
//							CSound::PlaySound(CSound::SOUND_LABEL_SE_POTIONGET);
//							CParticle *pParticle;
//							pParticle = CParticle::Create(CParticle::PARTICLE_TYPE_DEFAULT,
//								D3DXVECTOR3(PlayerPos.x, PlayerPos.y + 30, PlayerPos.z),
//								D3DXCOLOR(0.4f, 0.4f, 1.0f, 1.0f),
//								40, 50, 30, 2);
//
//						}
//						if (((CPlayer*)pScene)->GetDebugState() == CPlayer::DEBUG_NORMAL)
//						{
//							if (ntype == CModel::MODEL_MAP_PORTAL)
//							{
//								if (CManager::GetGameState() == CManager::MODE_TUTORIAL)
//								{
//									CFADE::SetFade(CManager::MODE_GAME);
//								}
//								else if (CManager::GetGameState() == CManager::MODE_GAME)
//								{
//									CFADE::SetFade(CManager::MODE_GAME2);
//								}
//								else if (CManager::GetGameState() == CManager::MODE_GAME2)
//								{
//									CFADE::SetFade(CManager::MODE_GAME3);
//								}
//								else if (CManager::GetGameState() == CManager::MODE_GAME3)
//								{
//									CFADE::SetFade(CManager::MODE_CLEAR);
//								}
//
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//
//	//---------------------------------------------------------■■■■■
//	return bLand;
//}

//====================================================================
//モデル情報の書き込み
//====================================================================
void CCreateMap::Save(void)
{
	FILE *pFile;
	pFile = fopen("data/Save/Map.txt", "w");
	if (pFile != NULL)
	{
		fprintf(pFile, "■■■==========モデル情報==========■■■\n");
		fprintf(pFile, "MAXMODEL = %d\n\n", m_vec.size());
		for (unsigned int nCnt = 0; nCnt < m_vec.size(); nCnt++)
		{
			fprintf(pFile, "SET\n\n");
			fprintf(pFile, "  POS = %.1f %.1f %.1f \n  TYPE = %d \n\n",
				m_vec[nCnt]->GetPosition().x,
				m_vec[nCnt]->GetPosition().y,
				m_vec[nCnt]->GetPosition().z,
				m_vec[nCnt]->GetType());
			fprintf(pFile, "END_SET\n\n");
		}
		fprintf(pFile, "END_SETMODEL\n\n");

		//fprintf(pFile, "■■■==========エネミー情報==========■■■\n");
		//fprintf(pFile, "MAXENEMY = %d\n\n", m_Enemy.size());
		//for (unsigned int nCnt = 0; nCnt < m_Enemy.size(); nCnt++)
		//{
		//	fprintf(pFile, "ENEMY_SET\n\n");
		//	fprintf(pFile, "  POS = %.1f %.1f %.1f \n  TYPE = %d \n\n",
		//		m_Enemy[nCnt]->GetPosition().x,
		//		m_Enemy[nCnt]->GetPosition().y,
		//		m_Enemy[nCnt]->GetPosition().z,
		//		m_Enemy[nCnt]->GetEnemyType());
		//	fprintf(pFile, "END_ENEMY_SET\n\n");
		//}
		//fprintf(pFile, "END_SETENEMY_TXT\n\n");
	}
	fclose(pFile);
}
//====================================================================
//読み込み
//====================================================================
void CCreateMap::Load(int type)
{
	char cReadText[1080];	//文字として読み取り用
	char cHeadText[1080];	//比較する用
	char cDie[1080];			//不要な文字
	int nCnt = 0;
	FILE *pFile;

	D3DXVECTOR3 pos;
	int nType;

	pFile = fopen(m_LoadFileName[type], "r");
	if (pFile != NULL)
	{
		//モデル情報が来るまでループ
		while (strcmp(cHeadText, "■■■==========モデル情報==========■■■") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile);	//一文を読み込む
			sscanf(cReadText, "%s", &cHeadText);		//比較用テキストに文字を代入
		}
		while (strcmp(cHeadText, "END_SETMODEL") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile);
			sscanf(cReadText, "%s", &cHeadText);
			//配置するモデルの最大数の書き込み
			if (strcmp(cHeadText, "MAXMODEL") == 0)
			{
				sscanf(cReadText, "%s %s %d",
					&cDie, &cDie,
					&m_max);
			}
			else if (strcmp(cHeadText, "SET") == 0)
			{
				//END_SETが来るまでループ
				while (strcmp(cHeadText, "END_SET") != 0)
				{
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s", &cHeadText);
					//POSだったら
					if (strcmp(cHeadText, "POS") == 0)
					{
						sscanf(cReadText, "%s %s %f %f %f",
							&cDie, &cDie,
							&pos.x,
							&pos.y,
							&pos.z);
					}
					//TYPEだったら
					else if (strcmp(cHeadText, "TYPE") == 0)
					{
						sscanf(cReadText, "%s %s %d",
							&cDie, &cDie,
							&nType);
					}
				}
					m_vec.emplace_back(CModel::Create(CModel::MAP_MODEL,nType));
					m_vec[m_vec.size() - 1]->SetPosition(pos);
					m_vec[m_vec.size() - 1]->SetSize(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
			}
		}
		////モデル情報が来るまでループ
		//while (strcmp(cHeadText, "■■■==========エネミー情報==========■■■") != 0)
		//{
		//	fgets(cReadText, sizeof(cReadText), pFile);	//一文を読み込む
		//	sscanf(cReadText, "%s", &cHeadText);		//比較用テキストに文字を代入
		//}
		//while (strcmp(cHeadText, "END_SETENEMY_TXT") != 0)
		//{
		//	fgets(cReadText, sizeof(cReadText), pFile);
		//	sscanf(cReadText, "%s", &cHeadText);
		//	//配置するモデルの最大数の書き込み
		//	if (strcmp(cHeadText, "MAXENEMY") == 0)
		//	{
		//		sscanf(cReadText, "%s %s %d",
		//			&cDie, &cDie,
		//			&m_max);
		//	}
		//	else if (strcmp(cHeadText, "ENEMY_SET") == 0)
		//	{
		//		//END_SETが来るまでループ
		//		while (strcmp(cHeadText, "END_ENEMY_SET") != 0)
		//		{
		//			fgets(cReadText, sizeof(cReadText), pFile);
		//			sscanf(cReadText, "%s", &cHeadText);
		//			//POSだったら
		//			if (strcmp(cHeadText, "POS") == 0)
		//			{
		//				sscanf(cReadText, "%s %s %f %f %f",
		//					&cDie, &cDie,
		//					&pos.x,
		//					&pos.y,
		//					&pos.z);
		//			}
		//			//TYPEだったら
		//			else if (strcmp(cHeadText, "TYPE") == 0)
		//			{
		//				sscanf(cReadText, "%s %s %d",
		//					&cDie, &cDie,
		//					&nType);
		//			}
		//		}
		//		m_Enemy.emplace_back(CEnemy::Create(nType));
		//		m_Enemy[m_Enemy.size() - 1]->SetPosition(pos);
		//	}
		//}
		fclose(pFile);
	}
	else
	{

	}
}

D3DXVECTOR3 CCreateMap::GetPosition(void)
{
	return m_pos;
}
//====================================================================
//メッシュの取得
//====================================================================

LPD3DXMESH CCreateMap::GetMesh(int nCnt)
{
	if (!m_vec.empty())
	{
		return m_vec[nCnt]->GetMesh();
	}
	return 0;
}
//====================================================================
//モデルの取得
//====================================================================

CModel * CCreateMap::GetModel(int nCnt)
{
	return m_vec[nCnt];
}
//====================================================================
//設置したモデルの最大取得
//====================================================================

int CCreateMap::GetMaxModel(void)
{
	if (!m_vec.empty())
	{
		return m_vec.size();
	}
	return 0;
}


