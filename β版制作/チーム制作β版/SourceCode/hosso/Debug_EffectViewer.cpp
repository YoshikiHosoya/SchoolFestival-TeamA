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
#define LINE_LENGTH (500.0f)
#define LINE_OFFSET (D3DXVECTOR3(0.0f,LINE_LENGTH,0.0f))

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
	if (m_p3DLine)
	{
		m_p3DLine->Rerease();
		m_p3DLine = nullptr;
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
	m_p3DLine = C3DLine::Create(EFFECT_CREATE_POS, ZeroVector3, ZeroVector3, LINE_OFFSET, D3DXCOLOR(0.4f, 0.4f, 0.8f, 1.0f));

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
			//エフェクトビューワ
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
	static CParticleParam::PARTICLE_TEXT NowText = CParticleParam::PARTICLE_TEXT::EFFECT_DEFAULT;
	static FILENAME_LIST aShapeName = { "Sphere","Cone","Circle_XY","Line" };
	static bool bSquare = false;	//正方形を保つか
	//キーボードのポインタ取得
	CKeyboard *pKeyboard = CManager::GetInputKeyboard();

	//止まってるかどうか
	if (!CScene::GetStopFlag())
	{
		//カウンタ++
		m_nCnt++;
	}


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



	//項目の大きさ設定
	ImGui::PushItemWidth(200);


	//アニメーションするかどうか
	ImGui::Checkbox("bAnimation", &m_pParticleParam->GetAnimation());

	//コンボボックス　テクスチャ
	m_pParticleParam->GetAnimation() ?
		CHossoLibrary::ImGui_Combobox(CTexture::GetSeparateFileName(), "SeparateTex", (int&)m_pParticleParam->GetSeparateTex()) :	//真
		CHossoLibrary::ImGui_Combobox(CTexture::GetTexFileName(), "Texture", (int&)m_pParticleParam->GetTex());						//偽

	//アニメーションする時
	if (m_pParticleParam->GetAnimation())
	{
		//ツリー
		if(ImGui::TreeNode("AnimationParam"))
		{
			//アニメーションパラメータ設定

			//ループするか
			ImGui::Checkbox("bAnimationLoop", &m_pParticleParam->GetAnimationLoop());

			//アニメーション切り替えの家運後
			ImGui::InputInt("AnimationCntSwitch", &m_pParticleParam->GetAnimationCntSwitch(), 1, 1, 20);

			//ツリー終了
			ImGui::TreePop();
		}
	}

	//当たり判定があるかどうか
	ImGui::Checkbox("bCollision", &m_pParticleParam->GetCollision());

	//当たり判定がある時
	if (m_pParticleParam->GetCollision())
	{
		//ツリー
		if (ImGui::TreeNode("CollisionParam"))
		{
			//当たり判定があるかどうか
			ImGui::Checkbox("m_bCollisionSizeCalc", &m_pParticleParam->GetCollisionSizeCalc());

			//アニメーションパラメータ設定
			ImGui::DragFloat3("CollisionSize", m_pParticleParam->GetCollisionSize(), 0.5f, 1.0f, 250.0f);

			//コリジョンの継続時間
			ImGui::InputInt("CollisionCnt", &m_pParticleParam->GetCollisionCnt(), 1, 1, 20);

			//攻撃力
			ImGui::InputInt("CollisionAttackValue", &m_pParticleParam->GetCollisionAttackValue(), 1, 1, 100);

			//ツリー終了
			ImGui::TreePop();
		}
	}

	//αブレンドするか
	ImGui::Checkbox("bAlphaBlend", &m_pParticleParam->GetAlphaBlend());


	//それぞれのオフセットを調整
	if (ImGui::DragFloat3("rot", m_pParticleParam->GetRot(), 0.005f, -D3DX_PI, D3DX_PI))
	{
		D3DXVECTOR3 TargetPos = D3DXVECTOR3(-sinf(m_pParticleParam->GetRot().y) * cosf(m_pParticleParam->GetRot().x) * LINE_LENGTH,
									sinf(m_pParticleParam->GetRot().x) * LINE_LENGTH,
									-cosf(m_pParticleParam->GetRot().y) * cosf(m_pParticleParam->GetRot().x) * LINE_LENGTH);


		m_p3DLine->SetPos(ZeroVector3, TargetPos);


	}
	ImGui::DragFloat("fRange", &m_pParticleParam->GetRange(), 0.01f, -D3DX_PI, D3DX_PI);


	//パラメータ設定
	ImGui::DragInt("Life", &m_pParticleParam->GetLife(), 1, 1, 300);
	ImGui::DragFloat("Speed", &m_pParticleParam->GetSpeed(), 0.5f, 0.0f, 250.0f);
	ImGui::DragInt("ParticleNum", &m_pParticleParam->GetNumber(), 1, 1, 300);

	//正方形を保つか
	ImGui::Checkbox("Square", &bSquare);

	//正方形を保つとき
	if (bSquare)
	{
		//サイズで設定した値をxとyにちゃんと入れる
		//xのパラメータをいじってる
		float fSize = m_pParticleParam->GetSize().x;
		float fSizeDamping = m_pParticleParam->GetSizeDamping().x;

		ImGui::DragFloat("Size", &fSize, 0.5f, 1.0f, 250.0f);
		ImGui::DragFloat("SizeDamping", &fSizeDamping, 0.001f, 0.5f, 1.0f);

		m_pParticleParam->GetSize().x = m_pParticleParam->GetSize().y = fSize;
		m_pParticleParam->GetSizeDamping().x = m_pParticleParam->GetSizeDamping().y = fSizeDamping;
	}
	else
	{
		//x.y.zそれぞれのパラメータ
		ImGui::DragFloat3("Size", m_pParticleParam->GetSize(), 0.5f, 1.0f, 250.0f);
		ImGui::DragFloat3("SizeDamping", m_pParticleParam->GetSizeDamping(), 0.001f, 0.5f, 1.0f);
	}

	//a値の減衰量
	ImGui::DragFloat("AlphaDamping", &m_pParticleParam->GetAlphaDamping(), 0.001f, 0.5f, 1.0f);

	//速度のランダムとか重力とか
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
	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) || ((m_bLoop && m_nCnt % m_nLoopInterval == 0) && !CScene::GetStopFlag()))
	{
		CParticle::CreateFromParam(EFFECT_CREATE_POS,ZeroVector3 ,m_pParticleParam.get());
	}

}
