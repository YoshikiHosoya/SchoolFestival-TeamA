// =====================================================================================================================================================================
//
// モデルキャラクターの処理 [modelcharacter.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "modelcharacter.h"			// インクルードファイル
#include "debugproc.h"
#include "manager.h"
#include "renderer.h"
#include "partsmodel.h"
#include "motion.h"

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define SPEED				(1.0f)						// 移動速度
#define PLAYER_FILE_NAME			("data/FILE/PLAYER_MODEL/PlayerModel0.txt")		// セーブファイル

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
LPDIRECT3DVERTEXBUFFER9				CModelCharacter::m_pVtxBuff				= NULL;
LPD3DXMESH							CModelCharacter::m_pMesh				= NULL;
LPD3DXBUFFER						CModelCharacter::m_pBuffMat				= NULL;
DWORD								CModelCharacter::m_nNumMat				= NULL;
CModelCharacter::PlayerMotionType	CModelCharacter::m_PlayerMotionType		= PlayerMotionType_NEUTRAL;
CModelCharacter::PlayerMotionType	CModelCharacter::m_PlayerMotionTypeOld	= PlayerMotionType_NEUTRAL;
int									CModelCharacter::m_nFrame				= 0;
int									CModelCharacter::m_nKeySet				= 0;

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CModelCharacter::CModelCharacter()
{
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CModelCharacter::~CModelCharacter()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
void CModelCharacter::Init(void)
{
	// 初期化
	for (int nCntParts = 0; nCntParts < PLAYER_PARTS; nCntParts++)
	{
		m_pModel[nCntParts] = CPartsModel::Create();		// パーツモデルの生成
	}

	m_nFrame	= 0;			// フレーム数
	m_nKeySet	= 0;			// 現在のキー

	// モデルの読み込み
	ModelLoad();
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CModelCharacter::Uninit(void)
{
	for (int nCntParts = 0; nCntParts < PLAYER_PARTS; nCntParts++)
	{
		m_pModel[nCntParts]->Uninit();

		delete m_pModel[nCntParts];
		m_pModel[nCntParts] = NULL;
	}
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CModelCharacter::Update(void)
{
	// 前回のモーション情報
	m_PlayerMotionTypeOld = m_PlayerMotionType;

	// モーションの更新
	MotionUpdate();

	for (int nCntParts = 0; nCntParts < PLAYER_PARTS; nCntParts++)
	{
		m_pModel[nCntParts]->Update();
	}
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CModelCharacter::Draw(void)
{	
	for (int nCntParts = 0; nCntParts < PLAYER_PARTS; nCntParts++)
	{
		m_pModel[nCntParts]->Draw();
	}
}

// =====================================================================================================================================================================
//
// モデルの生成
//
// =====================================================================================================================================================================
CModelCharacter * CModelCharacter::Create()
{
	// 変数
	CModelCharacter *pModelCharacter;

	// メモリの確保
	pModelCharacter = new CModelCharacter;

	// 初期化
	pModelCharacter->Init();

	return pModelCharacter;
}

// =====================================================================================================================================================================
//
// ワールドマトリックスの設定
//
// =====================================================================================================================================================================
void CModelCharacter::SetMatrix(D3DXMATRIX *mtx)
{
	for (int nCntParts = 0; nCntParts < PLAYER_PARTS; nCntParts++)
	{
		if (m_pModel[nCntParts]->GetParent() >= 0)
		{
			//親のworldマトリックスのポインタ取得
			m_pModel[nCntParts]->SetParentWorldMatrix(m_pModel[m_pModel[nCntParts]->GetParent()]->GetMatrix());
		}
		else
		{
			//親のworldマトリックスのポインタ取得
			m_pModel[nCntParts]->SetParentWorldMatrix(mtx);
		}
	}
}

// =====================================================================================================================================================================
//
// モーションの設定
//
// =====================================================================================================================================================================
void CModelCharacter::SetMotion(PlayerMotionType MotionType)
{
	// 現在のモーション情報
	m_PlayerMotionType = MotionType;

	// 現在と前回の情報が同じじゃなかったら初期化
	if (m_PlayerMotionType != m_PlayerMotionTypeOld)
	{
		m_nFrame = 0;
		m_nKeySet = 0;

		for (int nCntParts = 0; nCntParts < PLAYER_PARTS; nCntParts++)
		{
			// プレイヤーのモーション
			m_pModel[nCntParts]->SetMotionPlayer(m_PlayerMotionType, m_nKeySet);
		}
	}

}

// =====================================================================================================================================================================
//
// モデルの読み込み
//
// =====================================================================================================================================================================
void CModelCharacter::ModelLoad(void)
{
	// ファイルポイント
	FILE *pFile;

	char		cReadText[128];			// 文字として読み取る
	char		cHeadText[128];			// 比較用
	char		cDie[128];				// 不要な文字
	D3DXVECTOR3 pos				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 位置
	int			nIndex			= 0;	// インデックス
	int			nParent			= 0;	// 親
	int			nCntParts		= 0;	// パーツカウント

	// ファイルを開く
	pFile = fopen(PLAYER_FILE_NAME, "r");

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

				// PARTSSETが来たら
				if (strcmp(cHeadText, "PARTSSET") == 0)
				{
					// END_PARTSSETが来るまでループ
					while (strcmp(cHeadText, "END_PARTSSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
						sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入

						// POSが来たら
						if (strcmp(cHeadText, "POS") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &pos.x, &pos.y, &pos.z);		// 比較用テキストにPOSを代入
						}
						// INDEXが来たら
						else if (strcmp(cHeadText, "INDEX") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nIndex);		// 比較用テキストにINDEXを代入
						}
						// PARENTが来たら
						else if (strcmp(cHeadText, "PARENT") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nParent);		// 比較用テキストにPARENTを代入
						}
						else if (strcmp(cHeadText, "END_PARTSSET") == 0)
						{
							// 位置の設定
							m_pModel[nCntParts]->SetPos(pos);

							// インデックスの設定
							m_pModel[nCntParts]->SetIndex(nIndex);

							// 親の設定
							m_pModel[nCntParts]->SetParent(nParent);

							// カウントアップ
							nCntParts++;
						}
					}
				}
			}
		}
	}
}

// =====================================================================================================================================================================
//
// モーションの更新
//
// =====================================================================================================================================================================
void CModelCharacter::MotionUpdate(void)
{
	int nFlame = CMotion::GetMotionFrame(m_PlayerMotionType, m_nKeySet);
	int nNumKey = CMotion::GetMotionNumKey(m_PlayerMotionType);
	int nLoop = CMotion::GetMotionLoop(m_PlayerMotionType);

	// プレイヤーとモーションのフレーム数が同じとき
	if (m_nFrame == nFlame)
	{
		// キーセット更新
		m_nKeySet++;

		// プレイヤーとモーションのキーセット数が同じとき
		if (m_nKeySet == nNumKey)
		{
			m_nKeySet = 0;											// キーセットカウントリセット

			// ループしないとき
			if (nLoop == 0)
			{
				m_PlayerMotionType = PlayerMotionType_NEUTRAL;		// プレイヤーのモーションをニュートラルに

				m_nFrame = CMotion::GetMotionFrame(m_PlayerMotionType, m_nKeySet);		// フレーム数を設定
			}
			else
			{// ループするとき
			}
		}
		if (m_nKeySet < nNumKey)
		{
			for (int nCntParts = 0; nCntParts < PLAYER_PARTS; nCntParts++)
			{
				// プレイヤーのモーション
				m_pModel[nCntParts]->SetMotionPlayer(m_PlayerMotionType, m_nKeySet);
			}

			m_nFrame = 0;		// プレイヤーのフレーム数をリセット
		}
	}
	else
	{
		// カウントアップ
		m_nFrame++;
	}

	// デバッグ表示
	CDebugProc::Print("Flame: %d\n", m_nFrame);
	CDebugProc::Print("NumKey: %d\n", m_nKeySet);
	CDebugProc::Print("Loop: %d\n", nLoop);
	CDebugProc::Print("Type: %d\n\n", m_PlayerMotionType);
}