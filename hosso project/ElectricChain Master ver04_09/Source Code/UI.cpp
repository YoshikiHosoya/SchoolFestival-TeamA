//------------------------------------------------------------------------------
//
//シーン2D処理  [scene2D.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "UI.h"
#include "scene2D.h"
#include "renderer.h"
#include "menu.h"
#include "manager.h"
#include "keyboard.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------
std::vector<LPDIRECT3DTEXTURE9> CUI::m_pTextureList = {};
std::vector<std::string> CUI::m_aTexNameList = {};

//ファイルの場所
std::vector<std::string> CUI::m_aPlaceFileName =
{
	{ "data/SAVEDATA/UI/TitleUI_Place.txt " },
	{ "data/SAVEDATA/UI/GameUI_Place.txt " },
	{ "data/SAVEDATA/UI/ResultUI_Place.txt " },
	{ "data/SAVEDATA/UI/PauseUI_Place.txt " },
	{ "data/SAVEDATA/UI/GameendUI_Place.txt " },
	{ "data/SAVEDATA/UI/RankingUI_Place.txt " },
};

//UIのタイプ
std::vector<std::string> CUI::m_aTypeNameList =
{
	{ "Scene2D" },
	{ "Menu_Vertical" },
	{ "Menu_Horizon" },
};
//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define TEXFILE_NAME ("data/SAVEDATA/UI/TexName.txt")
#define SAVEFILE_NAME ("data/SAVEDATA/UI/Save.txt")
#define FLASHING_INTERVAL_ALPHA (0.015f)

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CUI::CUI()
{

}

//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CUI::~CUI()
{

}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CUI::Init()
{

	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CUI::Uninit()
{
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CUI::Update()
{

}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CUI::Draw()
{
}
//------------------------------------------------------------------------------
//生成処理
//------------------------------------------------------------------------------
void CUI::Create()
{

}
//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CUI::ShowDebugInfo()
{
#ifdef _DEBUG

	//UI情報
	if (ImGui::TreeNode("UIINfo"))
	{
		//tree終了
		ImGui::TreePop();
	}
#endif //DEBUG
}

//------------------------------------------------------------------------------
//テクスチャ名読み込み
//------------------------------------------------------------------------------
HRESULT CUI::LoadTexName()
{
	//変数宣言
	FILE *pFile;			//ファイルのポインタ
	char cReadText[MAX_TEXT];
	char cHeadText[MAX_TEXT];
	char cDieText[MAX_TEXT];
	int nCntTex = 0;
	int nNumTex = 0;

	//デバイス情報取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ファイルを開く
	pFile = fopen(TEXFILE_NAME, "r");

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
				//モデル番号だったら
				else if (strcmp(cHeadText, "NUM_TEXTURE") == 0)
				{
					sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &nNumTex);

					while (1)
					{
						fgets(cReadText, sizeof(cReadText), pFile);
						sscanf(cReadText, "%s", &cHeadText);

						//ファイルネームの読み込み
						if (strcmp(cHeadText, "TEXTURE_FILENAME") == 0)
						{
							LPDIRECT3DTEXTURE9 pTex;

							//仮 テクスチャ名
							char cData[MAX_TEXT];

							//モデル名代入
							sscanf(cReadText, "%s %s %s %s %s", &cDieText, &cDieText, &cData, &cDieText, &cDieText);

							//テクスチャの読み込み
							D3DXCreateTextureFromFile(pDevice,
								cData,
								&pTex);

							//NULLチェック
							if (!pTex)
							{
								//失敗
								std::cout << "テクスチャ読み込み失敗 " << "-" << nNumTex << NEWLINE;
							}


							//配列に追加
							m_aTexNameList.emplace_back(cData);
							m_pTextureList.emplace_back(pTex);

							//debug
							std::cout << "new  : " << "pTexName" << "-" << nCntTex << "-";
							std::cout << "Name" << ">>" << m_aTexNameList[nCntTex].data() << NEWLINE;

							//モデル数カウントアップ
							nCntTex++;

							//最初に宣言されたモデル数になった時
							if (nCntTex == nNumTex)
							{
								//ループを抜ける
								break;
							}
						}
					}
				}
			}
		}
		//ファイルを閉じる
		fclose(pFile);
	}
	//開けなかった時
	else
	{
		std::cout << "テキスト読み込み失敗" << "LoadTexname()" << NEWLINE;
		return E_FAIL;
	}
	return S_OK;
}
//------------------------------------------------------------------------------
//配置情報保存
//------------------------------------------------------------------------------
HRESULT CUI::SavePlaceData()
{
	FILE *pFile;

	int nRotNum = 0;
	char cHeadtext[128];
	char cWriteText[128];

	pFile = fopen(SAVEFILE_NAME, "w");

	if (pFile != nullptr)
	{
		//ブロックコメント
		fputs(COMMENT02, pFile);
		fputs(COMMENT01, pFile);

		strcpy(cHeadtext, "#Block\n");
		fputs(cHeadtext, pFile);

		strcpy(cHeadtext, "#Author:Yoshiki Hosoya\n");
		fputs(cHeadtext, pFile);

		fputs(COMMENT01, pFile);
		fputs(COMMENT02, pFile);
		fputs(NEWLINE, pFile);

		//ブロックコメント終了//

		//スクリプト
		strcpy(cHeadtext, "SCRIPT");
		fputs(cHeadtext, pFile);
		fputs(NEWLINE, pFile);

		//nullcheck
		if (!m_pScene2DUIList.empty())
		{
			for (size_t nCnt = 0; nCnt < m_pScene2DUIList.size(); nCnt++)
			{
				//Scene2Dセット
				strcpy(cHeadtext, "SCENE2DSET\n");
				sprintf(cWriteText, "	%s", &cHeadtext);
				fputs(cWriteText, pFile);

				//テクスチャ種類
				strcpy(cHeadtext, "TEX_TYPE");
				sprintf(cWriteText, "		%s %s %d", &cHeadtext, &EQUAL, m_pScene2DUIList[nCnt]->GetTexID());
				fputs(cWriteText, pFile);
				fputs(NEWLINE, pFile);

				//座標
				strcpy(cHeadtext, "POS");
				sprintf(cWriteText, "		%s %s %0.1f %0.1f %0.1f", &cHeadtext, &EQUAL, m_pScene2DUIList[nCnt]->GetPos().x, m_pScene2DUIList[nCnt]->GetPos().y, m_pScene2DUIList[nCnt]->GetPos().z);
				fputs(cWriteText, pFile);
				fputs(NEWLINE, pFile);

				//サイズ
				strcpy(cHeadtext, "SIZE");
				sprintf(cWriteText, "		%s %s %0.1f %0.1f %0.1f", &cHeadtext, &EQUAL, m_pScene2DUIList[nCnt]->GetSize().x, m_pScene2DUIList[nCnt]->GetSize().y, m_pScene2DUIList[nCnt]->GetSize().z);
				fputs(cWriteText, pFile);
				fputs(NEWLINE, pFile);

				//エンドセット
				strcpy(cHeadtext, "END_SCENE2DSET");
				sprintf(cWriteText, "	%s", &cHeadtext);
				fputs(cWriteText, pFile);
				fputs(NEWLINE, pFile);
				fputs(NEWLINE, pFile);

				std::cout << "SavingScene2D : " << nCnt << NEWLINE;

			}
		}
		else
		{
			//配列が空
			std::cout << "m_pScene2DUIList.empty() " << NEWLINE;
		}


		//nullcheck
		if (!m_pMenuList.empty())
		{

		}
		else
		{
			//配列が空
			std::cout << "m_pMenuList.empty() " << NEWLINE;
		}

		//スクリプト
		strcpy(cHeadtext, "END_SCRIPT");
		fputs(cHeadtext, pFile);
		fputs(NEWLINE, pFile);

		//セーブ成功
		std::cout << "Save Success! SavePlaceData()" << NEWLINE;

		//ファイルを閉じる
		fclose(pFile);

	}
	else
	{
		//ファイルが開けませんでした
		std::cout << "Save FAILED!!  Can't Open File. SavePlaceData()" << NEWLINE;
		return E_FAIL;
	}
	return S_OK;
}

//------------------------------------------------------------------------------
//配置情報読み込み
//------------------------------------------------------------------------------
HRESULT CUI::LoadPlace(UI_SCENE scene)
{
	//変数宣言
	FILE *pFile;			//ファイルのポインタ
	char cReadText[MAX_TEXT];
	char cHeadText[MAX_TEXT];
	char cDieText[MAX_TEXT];

	int nTexID = 0;							//テクスチャID
	D3DXVECTOR3 pos;						//座標
	D3DXVECTOR3 size;						//サイズ
	D3DXCOLOR col;							//色

	//デバイス情報取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ファイルを開く
	pFile = fopen(m_aPlaceFileName[scene].data(), "r");

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
				//モデル番号だったら
				else if (strcmp(cHeadText, "SCENE2DSET") == 0)
				{
					//エンドスクリプトが来る前ループ
					while (strcmp(cHeadText, "END_SCENE2DSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile);
						sscanf(cReadText, "%s", &cHeadText);

						//テクスチャの種類
						if (strcmp(cHeadText, "TEX_TYPE") == 0)
						{
							sscanf(cReadText, "%s %s %d",&cDieText, &cDieText, &nTexID);
						}

						//座標
						if (strcmp(cHeadText, "POS") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDieText, &cDieText, &pos.x, &pos.y, &pos.z);
						}

						//サイズ
						if (strcmp(cHeadText, "SIZE") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDieText, &cDieText, &size.x, &size.y, &size.z);
						}
						//色
						if (strcmp(cHeadText, "COLOR") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f %f", &cDieText, &cDieText, &col.r, &col.g, &col.b, &col.a);
						}

						//終了
						if (strcmp(cHeadText, "END_SCENE2DSET") == 0)
						{
							CScene2D_UI::Create(pos, size, col,nTexID,CScene::OBJTYPE_2DUI);
						}
					}
				}
			}
		}
	}
	//開けなかった時
	else
	{
		std::cout << "テキスト読み込み失敗" << "LoadPlace()" << NEWLINE;
		return E_FAIL;
	}
	return S_OK;

}
//------------------------------------------------------------------------------
//コンボボックス(Tex)
//------------------------------------------------------------------------------
bool CUI::ShowTexComboBox(int &nTexID)
{
	bool bChange = false;

#ifdef _DEBUG
		//combo開始
	if (ImGui::BeginCombo("TextureName", m_aTexNameList[nTexID].data()))
	{
		//要素分繰り返す
		for (size_t nCnt = 0; nCnt < m_aTexNameList.size(); nCnt++)
		{
			//選択番号があってるかどうか
			bool is_selected = (m_aTexNameList[nTexID] == m_aTexNameList[nCnt]);

			//選択された時の処理
			if (ImGui::Selectable(m_aTexNameList[nCnt].data(), is_selected))
			{
				//現在の選択項目設定
				nTexID = nCnt;
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
//コンボボックス(Type)
//------------------------------------------------------------------------------
bool CUI::ShowTypeComboBox(int & nType)
{
	bool bChange = false;

#ifdef _DEBUG
	//combo開始
	if (ImGui::BeginCombo("TypeName", m_aTypeNameList[nType].data()))
	{
		//要素分繰り返す
		for (size_t nCnt = 0; nCnt < m_aTypeNameList.size(); nCnt++)
		{
			//選択番号があってるかどうか
			bool is_selected = (m_aTypeNameList[nType] == m_aTypeNameList[nCnt]);

			//選択された時の処理
			if (ImGui::Selectable(m_aTypeNameList[nCnt].data(), is_selected))
			{
				//現在の選択項目設定
				nType = nCnt;
				bChange = true;

				//テクスチャ設定
			}
		}
		//combo終了
		ImGui::EndCombo();
	}
#endif //DEBUG
	return bChange;
}
//------------------------------------------------------------------------------
//テクスチャ情報取得
//------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CUI::GetTexture(int nTexID)
{
	return m_pTextureList[nTexID];
}
//------------------------------------------------------------------------------
//消去
//------------------------------------------------------------------------------
void CUI::DeleteAll()
{
	//nullcheck
	if (!m_pScene2DUIList.empty())
	{
		for (size_t nCnt = 0; nCnt < m_pScene2DUIList.size(); nCnt++)
		{
			m_pScene2DUIList[nCnt]->Release();
		}
		m_pScene2DUIList.clear();
	}
}

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CScene2D_UI::CScene2D_UI()
{
	m_nCnt = 0;
	m_nTexID = CTexture::TEX_NONE;
}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CScene2D_UI::~CScene2D_UI()
{
}
//------------------------------------------------------------------------------
//初期化
//------------------------------------------------------------------------------
HRESULT CScene2D_UI::Init()
{
	CScene2D::Init();

	return S_OK;
}
//------------------------------------------------------------------------------
//終了
//------------------------------------------------------------------------------
void CScene2D_UI::Uninit()
{
	CScene2D::Uninit();

}
//------------------------------------------------------------------------------
//更新
//------------------------------------------------------------------------------
void CScene2D_UI::Update()
{
	CScene2D::Update();

	switch (m_nTexID)
	{

	case CTexture::TEX_UI_PRESS_ANY_BUTTON:
		//カウントアップ
		m_nCnt++;

		float fCol_a;

		//a値取得
		fCol_a = GetCol().a;

		//一定周期で点滅
		m_nCnt % 180 >= 90 ? fCol_a += FLASHING_INTERVAL_ALPHA : fCol_a -= FLASHING_INTERVAL_ALPHA;

		//色設定
		SetVtxCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, fCol_a));
		break;

	}

}
//------------------------------------------------------------------------------
//描画
//------------------------------------------------------------------------------
void CScene2D_UI::Draw()
{
	CScene2D::Draw();

}

//------------------------------------------------------------------------------
//生成
//------------------------------------------------------------------------------
std::shared_ptr<CScene2D_UI> CScene2D_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, int nTexID,CScene::OBJTYPE objtype)
{
	//初期化
	std::shared_ptr<CScene2D_UI> pScene2D_UI = std::make_shared<CScene2D_UI>();

	//nullcheck
	if (pScene2D_UI)
	{
		pScene2D_UI->Init();

		//座標とサイズ設定
		pScene2D_UI->SetPos(pos);
		pScene2D_UI->SetSize(size);
		pScene2D_UI->SetVtxCol(col);
		pScene2D_UI->SetTexID((CTexture::TEX_TYPE)nTexID);

		//Sceneのポインタに追加
		pScene2D_UI->SetObjType(objtype);
		pScene2D_UI->AddSharedList(pScene2D_UI);

		return pScene2D_UI;
	}
	return nullptr;
}
//------------------------------------------------------------------------------
//デバッグ情報表示
//------------------------------------------------------------------------------
void CScene2D_UI::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}
//------------------------------------------------------------------------------
//テクスチャ設定
//------------------------------------------------------------------------------
void CScene2D_UI::SetTexID(CTexture::TEX_TYPE TexID)
{
	//テクスチャ番号設定
	m_nTexID = TexID;

	//テクスチャ設定
	BindTexture(CTexture::GetTexture((CTexture::TEX_TYPE)TexID));
}
//------------------------------------------------------------------------------
//テクスチャ番号出力
//------------------------------------------------------------------------------
CTexture::TEX_TYPE CScene2D_UI::GetTexID()
{
	return m_nTexID;
}
