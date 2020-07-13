//------------------------------------------------------------------------------
//
//デバッグ　エフェクトビューワ用の処理  [Debug_EffectViewer.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "Debug_ModelViewer.h"
#include "Debug_ViewerCharacter.h"
#include "../Scene.h"
#include "../manager.h"
#include "../renderer.h"
#include "../inputKeyboard.h"
#include "../camera.h"
#include "../fade.h"
#include "../meshfield.h"
#include "../model.h"


//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define DEFAULT_CAMERA_DISTANCE (200.0f)
#define DEFAULT_CAMERA_ROT (D3DXVECTOR3(0.2f,0.0f,0.0f))
#define DEFAULT_CAMERA_POSR (D3DXVECTOR3(30.0f, 50.0f, 0.0f))

#define OFFSET_TEXT_PASS ("data/Load/SaveOffset.txt")

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CDebug_ModelViewer::CDebug_ModelViewer()
{

}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CDebug_ModelViewer::~CDebug_ModelViewer()
{

}

//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CDebug_ModelViewer::Init()
{
	//ビューワ用のキャラクター作成
	m_pViewerCharacter = CDebug_ViewerCharacter::Create();

	CManager::GetRenderer()->GetCamera()->SetCameraPosfromDistance(DEFAULT_CAMERA_POSR, DEFAULT_CAMERA_ROT, DEFAULT_CAMERA_DISTANCE);

	CMeshField::Create(ZeroVector3, D3DXVECTOR3(50.0f, 50.0f, 50.0f), INTEGER2(20, 20));

	return S_OK;
}

//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CDebug_ModelViewer::Uninit()
{
	//終了処理
	CScene::RereaseAll();
}

//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CDebug_ModelViewer::Update()
{

}

//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CDebug_ModelViewer::Draw()
{

}
//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CDebug_ModelViewer::ShowDebugInfo()
{
#ifdef _DEBUG

	//キャラクター情報情報
	ImGui::Begin("MotionViewer");

		//Tab
		if (ImGui::BeginTabBar("Viewer", m_bModel))
		{
			//Tab
			if (ImGui::BeginTabItem("MotionViewer"))
			{
				//モーションビューワ
				m_pViewerCharacter->MotionViewer();
				ImGui::EndTabItem();
			}
			//Tab
			if (ImGui::BeginTabItem("OffsetViewer"))
			{
				//オフセットビューワ
				OffsetViewer(m_pViewerCharacter->GetCharacterModelList());
				ImGui::EndTabItem();
			}
			//TabEnd
			ImGui::EndTabBar();
		}

	ImGui::End();
#endif
}

//------------------------------------------------------------------------------
//オフセットビューワ
//------------------------------------------------------------------------------
void CDebug_ModelViewer::OffsetViewer(std::vector<CModel*> vModelList)
{
	//モデル数分繰り替えす
	for (size_t nCnt = 0; nCnt < vModelList.size(); nCnt++)
	{
		//モデル名取得
		std::string aPartsName = CModel::GetModelFileName(vModelList[nCnt]->GetType(), vModelList[nCnt]->GetModelCount());

		//頭の部分の文字列を消す("data/MODEL/)
		aPartsName.erase(aPartsName.begin(), aPartsName.begin() + 11);

		//次の項目の枠の大きさ設定
		ImGui::SetNextItemWidth(200);

		//それぞれのオフセットを調整
		if (ImGui::DragFloat3(aPartsName.data(), vModelList[nCnt]->GetPosition(), 0.05f, -100.0f, 100.0f))
		{

		}

		//同じ行に
		ImGui::SameLine();

		//親番号 >>
		ImGui::Text("ParentIdx >>");

		//次の項目の枠の大きさ設定
		ImGui::SetNextItemWidth(20);

		//モデル番号
		char aId[64];
		sprintf(aId, "[%d]", vModelList[nCnt]->GetModelCount());

		//同じ行
		ImGui::SameLine();

		//親番号
		if (ImGui::InputInt(aId, &vModelList[nCnt]->GetParentIdx(), -1, vModelList.size()))
		{
			vModelList[nCnt]->SetParent(vModelList[vModelList[nCnt]->GetParentIdx()]);
		}
	}

	//オフセットのセーブ
	if (ImGui::Button("OffsetSave"))
	{
		SaveModelOffset(vModelList);
	}

	//オフセット全てリセット
	if (ImGui::Button("AllReset"))
	{
		//モデル数分繰り替えす
		for (size_t nCnt = 0; nCnt < vModelList.size(); nCnt++)
		{
			//０にする
			vModelList[nCnt]->SetPosition(ZeroVector3);
		}
	}
}

//------------------------------------------------------------------------------
//オフセット保存
//------------------------------------------------------------------------------
HRESULT CDebug_ModelViewer::SaveModelOffset(std::vector<CModel*> vModelList)
{
	FILE *pFile;

	int nRotNum = 0;
	char cHeadtext[128];
	char cWriteText[128];

	//ファイル読み込み
	pFile = fopen(OFFSET_TEXT_PASS, "w");

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
		//nullcheck
		if (!vModelList.empty())
		{
			for (size_t nCnt = 0; nCnt < vModelList.size(); nCnt++)
			{

				//スタート
				sprintf(cWriteText, "%s %s%d%s", "SET_START", "---------[", nCnt, "]----------");
				fputs(cWriteText, pFile);
				fputs(NEWLINE, pFile);

				//モデルの種類
				sprintf(cWriteText, "	%s %s %d", "MODEL_TYPE", &EQUAL, vModelList[nCnt]->GetType());
				fputs(cWriteText, pFile);
				fputs(NEWLINE, pFile);

				//インデックス
				sprintf(cWriteText, "	%s %s %d", "INDEX", &EQUAL, vModelList[nCnt]->GetModelCount());
				fputs(cWriteText, pFile);
				fputs(NEWLINE, pFile);

				//親番号
				sprintf(cWriteText, "	%s %s %d", "PARENT", &EQUAL, vModelList[nCnt]->GetParentIdx());
				fputs(cWriteText, pFile);
				fputs(NEWLINE, pFile);

				//座標
				sprintf(cWriteText, "	%s %s %.1f %.1f %.1f", "POS", &EQUAL,
					vModelList[nCnt]->GetPosition().x,
					vModelList[nCnt]->GetPosition().y,
					vModelList[nCnt]->GetPosition().z);
				fputs(cWriteText, pFile);
				fputs(NEWLINE, pFile);

				//パーツセット終了
				fputs("SET_END", pFile);
				fputs(NEWLINE, pFile);
				fputs(NEWLINE, pFile);

			}
		}

		//オフセット設定終了
		fputs("MODEL_OFFSET_END", pFile);

		//保存成功
		std::cout << "Offset Save Succsess!! >> " << OFFSET_TEXT_PASS << NEWLINE;

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		//ファイルが開けませんでした
		std::cout << "Motion Save FAILED!!  Can't Open File >> " << OFFSET_TEXT_PASS << NEWLINE;
		return E_FAIL;
	}
	return S_OK;
}
