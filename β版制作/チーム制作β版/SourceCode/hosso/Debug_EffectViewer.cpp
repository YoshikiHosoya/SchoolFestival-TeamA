//------------------------------------------------------------------------------
//
//デバッグ　エフェクトビューワ用の処理  [Debug_EffectViewer.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "Debug_EffectViewer.h"
#include "Debug_WorldLine.h"
#include "../Scene.h"
#include "../manager.h"
#include "../renderer.h"
#include "../inputKeyboard.h"
#include "../camera.h"
#include "../fade.h"
#include "../particle.h"
#include "../ParticleManager.h"
#include "../MeshField.h"
#include "../3Dline.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define EFFECT_CREATE_POS (D3DXVECTOR3(0.0f, 50.0f, 100.0f))
#define LINE_OFFSET (D3DXVECTOR3(0.0f,500.0f,0.0f))

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CDebug_EffectViewer::CDebug_EffectViewer()
{
	m_bLoop = false;
	m_nLoopInterval = 60;
	m_nCnt = 0;
	m_pParticleParam.reset();
	m_p3DLine = nullptr;
}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CDebug_EffectViewer::~CDebug_EffectViewer()
{
	if (m_pWorldLine)
	{
		delete m_pWorldLine;
		m_pWorldLine = nullptr;
	}
}

//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CDebug_EffectViewer::Init()
{
	//床
	CMeshField::Create(ZeroVector3, D3DXVECTOR3(50.0f, 50.0f, 50.0f), INTEGER2(20, 20));

	//基準線
	m_pWorldLine = CDebug_WorldLine::Create(EFFECT_CREATE_POS);

	//ラインの生成
	m_p3DLine = C3DLine::Create(EFFECT_CREATE_POS, ZeroVector3, ZeroVector3, LINE_OFFSET, WhiteColor);

	//パーティクルのマネージャ
	CParticleManager::Create();

	//パーティクルのパラメータのメモリ確保
	m_pParticleParam.reset(new CParticleParam);

	return S_OK;
}

//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CDebug_EffectViewer::Uninit()
{

	//終了処理
	CScene::RereaseAll();
}

//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CDebug_EffectViewer::Update()
{

}

//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CDebug_EffectViewer::Draw()
{

}
//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CDebug_EffectViewer::ShowDebugInfo()
{
#ifdef _DEBUG
	//キャラクター情報情報
	ImGui::Begin("EffectViewer");

	////Tab
	//if (ImGui::BeginTabBar("Viewer", m_bModel))
	//{
	//	//Tab
	//	if (ImGui::BeginTabItem("MotionViewer"))
	//	{
			//モーションビューワ
			ParticleParamaterViewer();
			//ImGui::EndTabItem();
	//	}

	//	//TabEnd
	//	ImGui::EndTabBar();
	//}

	ImGui::End();

#endif
}

//------------------------------------------------------------------------------
//パーティクルのパラメータのビューワ
//------------------------------------------------------------------------------
void CDebug_EffectViewer::ParticleParamaterViewer()
{
	//読み込むテキストの番号
	static CParticleParam::PARTICLE_TEXT NowText = CParticleParam::PARTICLE_TEXT::PARTICLE_DEFAULT;
	static FILENAME_LIST aShapeName = { "Sphere","Cone","Circle_XY","Line" };

	//止まってるかどうか
	if (!CScene::GetStopFlag())
	{
		//カウンタ++
		m_nCnt++;
	}

	//キーボードのポインタ取得
	CKeyboard *pKeyboard = CManager::GetInputKeyboard();

	//Debug
	CDebugProc::Print("[Enter] パーティクル発生\n");
	CDebugProc::Print("[Ctrl] + [Enter] Loop %d \n", m_bLoop);

	//コンボボックス　ファイル名
	if (CHossoLibrary::ImGui_Combobox(CParticleParam::GetFileNameList(), "ParamFileName", (int&)NowText))
	{
		//メモリ確保
		CParticleParam *pParam = new CParticleParam;

		//パラメータをコピー
		//unique_ptrだと代入できない
		*pParam = *CParticleParam::GetDefaultParam(NowText);

		//メモリ確保しなおし
		m_pParticleParam.reset(std::move(pParam));
	}

	//コンボボックス　Shape
	if (CHossoLibrary::ImGui_Combobox(aShapeName, "Shape", (int&)m_pParticleParam->GetShape()))
	{

	}

	//アニメーションするかどうか
	ImGui::Checkbox("bAnimation", &m_pParticleParam->GetAnimation());

	//コンボボックス　テクスチャ
	m_pParticleParam->GetAnimation() ?
		CHossoLibrary::ImGui_Combobox(CTexture::GetSeparateFileName(), "SeparateTex", (int&)m_pParticleParam->GetSeparateTex()) :	//真
		CHossoLibrary::ImGui_Combobox(CTexture::GetTexFileName(), "Texture", (int&)m_pParticleParam->GetTex());						//偽

	ImGui::Checkbox("bAlphaBlend", &m_pParticleParam->GetAlphaBlend());


	//それぞれのオフセットを調整
	ImGui::DragFloat3("rot", m_pParticleParam->GetRot(), 0.005f, -D3DX_PI, D3DX_PI);
	ImGui::DragFloat("fRange", &m_pParticleParam->GetRange(), 0.01f, -D3DX_PI, D3DX_PI);

	//項目の大きさ設定
	ImGui::PushItemWidth(120);

	//パラメータ設定
	ImGui::DragInt("Life", &m_pParticleParam->GetLife(), 1, 1, 300);
	ImGui::DragFloat("Radius", &m_pParticleParam->GetRadius(), 0.5f, 1.0f, 250.0f);
	ImGui::DragFloat("Speed", &m_pParticleParam->GetSpeed(), 0.5f, 1.0f, 250.0f);
	ImGui::DragInt("ParticleNum", &m_pParticleParam->GetNumber(), 1, 0, 300);
	ImGui::DragFloat("RadiusDamping", &m_pParticleParam->GetRadiusDamping(), 0.001f, 0.5f, 1.0f);
	ImGui::DragFloat("AlphaDamping", &m_pParticleParam->GetAlphaDamping(), 0.001f, 0.5f, 1.0f);

	ImGui::Checkbox("bSpeedRandom", &m_pParticleParam->GetSpeedRandom());
	ImGui::Checkbox("bGravity", &m_pParticleParam->GetGravity());
	//重力がONの時
	if (m_pParticleParam->GetGravity())
	{
		//同じ行
		ImGui::SameLine();

		//重力の大きさ
		ImGui::DragFloat("GravityPower", &m_pParticleParam->GetGravityPower(), 0.005f, 0.1f, 2.0f);
	}

	//軌跡の色　float型にキャスト
	float *rCol = m_pParticleParam->GetCol();

	//項目の大きさ設定
	ImGui::SetNextItemWidth(250);

	//色の設定
	ImGui::ColorEdit4("Color", rCol);

	//パーティクル情報保存
	if (ImGui::Button("Save"))
	{
		//セーブ
		CParticleParam::SaveParticleDefaultParam(m_pParticleParam.get());
	}

	//[Ctrl] + [Enter]
	if ((pKeyboard->GetKeyboardPress(DIK_LCONTROL) && pKeyboard->GetKeyboardTrigger(DIK_RETURN)))
	{
		//onoff設定
		m_bLoop ^= 1;
	}

	//( [Enter]を押したとき　または　ループする時 ) なおかつSceneが止まってない時
	if ((pKeyboard->GetKeyboardTrigger(DIK_RETURN) || (m_bLoop && m_nCnt % m_nLoopInterval == 0)) && !CScene::GetStopFlag())
	{
		CParticle::CreateFromParam(EFFECT_CREATE_POS, m_pParticleParam.get());
	}

}
