//==========================================================
// シーン処理 [Scene.cpp]: NORI
//==========================================================
//==========================================================
// インクルードファイル
//==========================================================
#include "scene.h"
#include "renderer.h"
#include "pause.h"
#include "inputKeyboard.h"

//プロトタイプ宣言
//グローバル変数　何番目の表示↓　↓表示の最高数
int CScene::m_NumAll = 0;
bool CScene::m_bStopFlag = false;
bool CScene::m_b1FUpdateFlag = false;
std::vector<CScene*> CScene::m_pSceneList[TYPE_MAX] = {};

//debug
#ifdef _DEBUG
std::vector<int> CScene::m_fUpdateTimeList(CScene::TYPE_MAX);
std::vector<int> CScene::m_fDrawTimeList(CScene::TYPE_MAX);
#endif // _DEBUG
//==========================================================
//コンストラクタ
//==========================================================
CScene::CScene(OBJ_TYPE type)
{
	// オブジェクトタイプのチェック
	if (type != TYPE_NONE)
	{
		m_bflag = false;

		m_pSceneList[type].emplace_back(this);
	}
	else
	{
		return;
	}
}
//==========================================================
//デストラクタ
//==========================================================
CScene::~CScene()
{
}
//==========================================================
//すべての更新
//==========================================================
void CScene::UpdateAll(void)
{
	//ストップのフラグ確認
	if (!m_bStopFlag || m_b1FUpdateFlag)
	{
		//OBJTYPE分回す
		for (int nCntObjtype = 0; nCntObjtype < TYPE_MAX; nCntObjtype++)
		{
#ifdef _DEBUG
			//更新する前の時間を保存
			DWORD dwBeforeUpdateTime = timeGetTime();
#endif // _DEBUG
			//配列が空かどうか
			if (!m_pSceneList[nCntObjtype].empty())
			{
				//Sceneの配列の大きさ分
				for (size_t nCnt = 0; nCnt < m_pSceneList[nCntObjtype].size(); nCnt++)
				{
					//nullcheck
					if (m_pSceneList[nCntObjtype][nCnt])
					{
						//更新処理
						m_pSceneList[nCntObjtype][nCnt]->Update();
					}
				}
			}
#ifdef _DEBUG
			//配列の値を書き換え
			//現在の時間 - 前回の更新が終わった時間
			m_fUpdateTimeList[nCntObjtype] = timeGetTime() - dwBeforeUpdateTime;
#endif // _DEBUG
		}
	}

	//OBJTYPE分回す
	for (int nCntObjtype = 0; nCntObjtype < TYPE_MAX; nCntObjtype++)
	{
		//配列が空かどうか
		if (!m_pSceneList[nCntObjtype].empty())
		{
			//Sceneの配列の大きさ分
			for (size_t nCnt = 0; nCnt < m_pSceneList[nCntObjtype].size(); nCnt++)
			{
				//フラグチェック
				if (m_pSceneList[nCntObjtype][nCnt]->m_bflag)
				{
					//終了処理
					m_pSceneList[nCntObjtype][nCnt]->Uninit();
					//メモリ開放
					delete m_pSceneList[nCntObjtype][nCnt];
					m_pSceneList[nCntObjtype][nCnt] = nullptr;

					//配列から削除
					m_pSceneList[nCntObjtype].erase(m_pSceneList[nCntObjtype].begin() + nCnt);

					//配列でずれた分修正
					nCnt--;

				}
			}
		}
	}

	m_b1FUpdateFlag = false;
}
//==========================================================
//すべての消去
//==========================================================
void CScene::RereaseAll(void)
{
	//OBJTYPE分回す
	for (int nCntObjtype = 0; nCntObjtype < TYPE_MAX; nCntObjtype++)
	{
		//配列が空かどうか
		if (!m_pSceneList[nCntObjtype].empty())
		{
			//Sceneの配列の大きさ分
			for (size_t nCnt = 0; nCnt < m_pSceneList[nCntObjtype].size(); nCnt++)
			{
				//nullcheck
				if (m_pSceneList[nCntObjtype][nCnt])
				{
					//終了処理
					m_pSceneList[nCntObjtype][nCnt]->Uninit();

					//メモリ開放
					delete m_pSceneList[nCntObjtype][nCnt];
					m_pSceneList[nCntObjtype][nCnt] = nullptr;
				}
			}
			//配列を空にする
			m_pSceneList[nCntObjtype].clear();
		}
	}
	//配列を空にする
	m_pSceneList->clear();
}
//==========================================================
//すべての描画
//==========================================================
void CScene::DrawAll(void)
{
	//OBJTYPE分回す
	for (int nCntObjtype = 0; nCntObjtype < TYPE_MAX; nCntObjtype++)
	{
#ifdef _DEBUG
		//更新する前の時間を保存
		DWORD dwBeforeUpdateTime = timeGetTime();
#endif // _DEBUG

		//配列が空かどうか
		if (!m_pSceneList[nCntObjtype].empty())
		{
			//Sceneの配列の大きさ分
			for (size_t nCnt = 0; nCnt < m_pSceneList[nCntObjtype].size(); nCnt++)
			{
				//nullcheck
				if (m_pSceneList[nCntObjtype][nCnt])
				{
					//描画
					m_pSceneList[nCntObjtype][nCnt]->Draw();
				}
			}
		}
#ifdef _DEBUG
		//現在の時間 - 前回の更新が終わった時間
		m_fDrawTimeList[nCntObjtype] = timeGetTime() - dwBeforeUpdateTime;
#endif // _DEBUG
	}
}
//==========================================================
//すべての取得
//==========================================================
int  CScene::GetAll(void)
{
	return m_NumAll;
}
//==========================================================
//デバッグ情報の表示
//==========================================================
void CScene::DebugAll(void)
{
#ifdef _DEBUG
	//OBJTYPE分回す
	for (int nCntObjtype = 0; nCntObjtype < TYPE_MAX; nCntObjtype++)
	{
		//配列が空かどうか
		if (!m_pSceneList[nCntObjtype].empty())
		{
			//Sceneの配列の大きさ分
			for (size_t nCnt = 0; nCnt < m_pSceneList[nCntObjtype].size(); nCnt++)
			{
				//nullcheck
				if (m_pSceneList[nCntObjtype][nCnt])
				{
					//更新処理
					m_pSceneList[nCntObjtype][nCnt]->DebugInfo();
				}
			}
		}
	}
#endif
}
//==========================================================
//デバッグ更新や描画にかかる時間を表記
//==========================================================
void CScene::ShowUpdateGraph()
{
#ifdef _DEBUG

	//グラフ用のウィンドウ
	ImGui::Begin("Gragh");

	//出力用の配列
	std::vector<float> OutputDataList(TYPE_MAX);

	//CDebugProc::Print("FPS_IntervalCount >> %d\n", GetFPSInterval());
	CDebugProc::Print("FPS >> %d\n", GetFps());

	//更新のグラフ
	if (ImGui::TreeNode("Update_Graph"))
	{
		//出力用のデータに計算
		for (int nCntObjType = 0; nCntObjType < TYPE_MAX; nCntObjType++)
		{
			//更新にかかった時間 / 全部の更新と描画にかかった時間
			OutputDataList[nCntObjType] = (float)m_fUpdateTimeList[nCntObjType];
		}

		//ヒストグラフ生成
		ImGui::PlotHistogram("Update (mSec)", OutputDataList.data(), OutputDataList.size(), 0, NULL, 0.0f, 16.0f, ImVec2(0, 100));

		//ツリー終了
		ImGui::TreePop();

	}

	//更新のグラフ
	if (ImGui::TreeNode("Draw_Graph"))
	{
		//出力用のデータに計算
		for (int nCntObjType = 0; nCntObjType < TYPE_MAX; nCntObjType++)
		{
			//描画にかかった時間 / 全部の更新と描画にかかった時間
			OutputDataList[nCntObjType] = (float)m_fDrawTimeList[nCntObjType];
		}

		//ヒストグラフ生成
		ImGui::PlotHistogram("Renderer (mSec)", OutputDataList.data(), OutputDataList.size(), 0, NULL, 0.0f, 16.0f, ImVec2(0, 100));

		//ツリー終了
		ImGui::TreePop();
	}
	//配列の開放
	OutputDataList.clear();

	//
	ImGui::End();

#endif // _DEBUG
}

//==========================================================
//ストップの状態取得
//==========================================================
bool &CScene::GetStopFlag(void)
{
	return m_bStopFlag;
}

//==========================================================
//オブジェクトの設定
//==========================================================
void CScene::SetObjType(OBJ_TYPE type)
{
	objtype = type;
}
//==========================================================
//シーンの取得
//==========================================================
CScene *CScene::GetScene(OBJ_TYPE type)
{
	return NULL;
}
//==========================================================
//シーンの配列取得
//==========================================================
void CScene::GetSceneList(OBJ_TYPE objtype, std::vector<CScene*>& rSceneList)
{
	rSceneList = m_pSceneList[objtype];
}
//==========================================================
//オブジェクトタイプの取得
//==========================================================
CScene::OBJ_TYPE CScene::GetObjType(void)
{
	return objtype;
}
//==========================================================
//消去のフラグ
//==========================================================
void CScene::Rerease(void)
{
 	m_bflag = true;
}

//==========================================================
//ストップの変更
//==========================================================
void CScene::StopUpdate(void)
{
	m_bStopFlag ^= 1;
}