//------------------------------------------------------------------------------
//
//debug ビューワ用のキャラクター処理  [Debug_ViewerCharacter.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "Debug_ViewerCharacter.h"
#include "../../manager.h"
#include "../../renderer.h"
#include "../../game.h"
#include "../../camera.h"
#include "../../inputKeyboard.h"
#include "../../model.h"

//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CDebug_ViewerCharacter::CDebug_ViewerCharacter()
{
}

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CDebug_ViewerCharacter::CDebug_ViewerCharacter(OBJ_TYPE type) : CCharacter(type)
{
}

//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CDebug_ViewerCharacter::~CDebug_ViewerCharacter()
{
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CDebug_ViewerCharacter::Init()
{
	CCharacter::Init();

	CCharacter::LoadOffset(CCharacter::CHARACTER_TYPE_PLAYER);

	//成功
	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CDebug_ViewerCharacter::Uninit()
{
	CCharacter::Uninit();
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CDebug_ViewerCharacter::Update()
{
	CCharacter::Update();
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CDebug_ViewerCharacter::Draw()
{
	CCharacter::Draw();
}
//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CDebug_ViewerCharacter::ShowDebugInfo()
{
#ifdef _DEBUG
	static bool bMotion = true;
#endif //DEBUG
}

//------------------------------------------------------------------------------
//生成
//------------------------------------------------------------------------------
CDebug_ViewerCharacter* CDebug_ViewerCharacter::Create()
{
	//変数宣言
	CDebug_ViewerCharacter *pCharacter = new CDebug_ViewerCharacter(OBJTYPE_PLAYER);

	if (pCharacter)
	{
		//初期化7
		pCharacter->Init();

		////オブジェクトタイプ設定
		pCharacter->SetObjType(OBJTYPE_PLAYER);
	}

	//生成した情報
	return pCharacter;
}

//------------------------------------------------------------------------------
//コンボボックス
//------------------------------------------------------------------------------
bool CDebug_ViewerCharacter::ShowMotionComboBox(CCharacter::MOTION &motiontype)
{
	bool bChange = false;

#ifdef _DEBUG

	//std::vector<std::string > &aFileName = CMotion::GetFileName();

	////combo開始
	//if (ImGui::BeginCombo("MotionName", aFileName[motiontype].data()))
	//{
	//	//要素分繰り返す
	//	for (size_t nCnt = 0; nCnt < aFileName.size(); nCnt++)
	//	{

	//		//選択番号があってるかどうか
	//		bool is_selected = (aFileName[motiontype] == aFileName[nCnt]);

	//		//選択された時の処理
	//		if (ImGui::Selectable(aFileName[nCnt].data(), is_selected))
	//		{
	//			//現在の選択項目設定
	//			motiontype = (CMotion::MOTION_TYPE)nCnt;
	//			bChange = true;
	//		}

	//		////
	//		//if (is_selected)
	//		//{
	//		//	//スクロールの初期位置設定
	//		//	ImGui::SetItemDefaultFocus();
	//		//}
	//	}
	//	//combo終了
	//	ImGui::EndCombo();

	//}
#endif //DEBUG
	return bChange;
}
//------------------------------------------------------------------------------
//モーションビューワ
//------------------------------------------------------------------------------
void CDebug_ViewerCharacter::MotionViewer()
{
	//キーボードのポインタ
	CKeyboard *pKeyboard = CManager::GetInputKeyboard();

	//現在のキー
	int &nNowKey = CCharacter::GetKeySet();
	int &nNowFrame = CCharacter::GetFram();

	//モーションに関する情報
	CCharacter::CHARACTER_MOTION_STATE &NowMotionType = GetMotionType();
	CCharacter::MOTION *MotionInfo = CCharacter::GetCharacterMotion(NowMotionType);

	//攻撃系の情報が変わったかどうか
	bool bChangeAttackInfo = false;
	bool bChangeNowKey = false;

	//コピペ用のキー
	static CCharacter::CHARACTER_MOTION_STATE CopyMotionType = CHARACTER_MOTION_STATE_NONE;
	static int nCopyKey = -1;



	////プレイヤー座標リセット
	//if (ImGui::Button("PlayerPosReset"))
	//{
	//	SetPos(ZeroVector3);
	//}

	////モーションのコンボボックス
	//if (ShowMotionComboBox(NowMotionType))
	//{
	//	nNowKey = 0;
	//	SetAttack(false);
	//	ChangeMotion(NowMotionType);
	//	pModelCharacter->ForcedUpdate(NowMotionType, nNowKey);
	//	MotionInfo = CMotion::GetMotion(NowMotionType);
	//}

	//モーションリスタート
	if (ImGui::Button("ReStart") || pKeyboard->GetKeyboardTrigger(DIK_RETURN))
	{
		nNowKey = 0;
		SetMotion(NowMotionType);
		ForcedUpdate();
		MotionInfo = CCharacter::GetCharacterMotion(NowMotionType);
	}

	//Widgetの大きさ設定
	ImGui::PushItemWidth(100);

	////モーションストップ
	//if (ImGui::Checkbox("bMotionStop", &pModelCharacter->GetMotionStop()))
	//{

	//}

	//ループ
	//if (ImGui::Checkbox("bLoop", (bool*)MotionInfo->nLoop))
	//{

	//}

	//改行
	ImGui::Separator();

	//１F前のキーフレーム
	int nNumKeyOld = MotionInfo->nNumKey;

	ImGui::Text("NowKey : %d / ", nNowKey);

	ImGui::SameLine();

	//キー数
	if (ImGui::InputInt("NumKey", &MotionInfo->nNumKey))
	{
		//範囲内に修正する
		CHossoLibrary::RangeLimit_Equal_Int(MotionInfo->nNumKey, 0, 100);

		////キーが増えたか減ったか
		//MotionInfo->nNumKey > nNumKeyOld ?
		//	CMotion::AddKeyInfo(NowMotionType, pModelCharacter->GetType()) :			//要素の追加　末尾
		//	CMotion::PopbackKeyInfo(NowMotionType);										//要素の削除　末尾
	}

	ImGui::Text("NowFrame : %d / ", nNowFrame);

	ImGui::SameLine();


	//フレーム数
	if (ImGui::InputInt("MaxFrame", &MotionInfo->key_info[nNowKey]->nFram))
	{

	}

	////改行
	//ImGui::Separator();
	////原点の高さ調節
	//if (ImGui::DragFloat("OriginHeight", &MotionInfo->pKeyInfoList[nNowKey]->fOriginHeight, 0.05f, -70.0f, 70.0f))
	//{
	//	//モーション強制変更
	//	pModelCharacter->ForcedUpdate(NowMotionType, nNowKey);
	//}




	//キーボードの←→でも現在のキー変えたい
	if (pKeyboard->GetKeyboardTrigger(DIK_LEFT))
	{
		bChangeNowKey = true;
		nNowKey--;
	}

	if (pKeyboard->GetKeyboardTrigger(DIK_RIGHT))
	{
		bChangeNowKey = true;
		nNowKey++;
	}

	//モーションの保存
	if (ImGui::Button("Copy"))
	{
		//コピーのキーとモーションを保存
		nCopyKey = nNowKey;
		CopyMotionType = NowMotionType;
	}

	//改行しない
	ImGui::SameLine();

	//モーションの保存
	if (ImGui::Button("Paste"))
	{
		//コピーしたのをはりつけ
		//MotionCopy(NowMotionType, nNowKey, CopyMotionType, nCopyKey);

		//モーション強制変更
		ForcedUpdate();

	}

	//コピー中のモーションとキー
	ImGui::Text("CopyMotion [%d] CopyKey [%d]", CopyMotionType, nCopyKey);

	//現在のキーに変更があった時
	if (bChangeNowKey)
	{
		//0以下は０
		if (nNowKey < 0)
		{
			nNowKey = 0;
		}
		////キーチェック
		//pModelCharacter->KeyCheck();

		//モーション強制変更
		ForcedUpdate();
	}

	//改行
	ImGui::Separator();
	//パーツ回転
	if (ImGui::TreeNode("PartsRot"))
	{

		//モデル数分繰り替えす
		for (size_t nCnt = 0; nCnt < MotionInfo->key_info[nNowKey]->key.size(); nCnt++)
		{
			//モデル名取得
			//std::string aPartsName = CModelCharacter::GetModelName(pModelCharacter->GetType(), nCnt).data();

			////頭の部分の文字列を消す("data/MODEL/)
			//aPartsName.erase(aPartsName.begin(), aPartsName.begin() + 11);

			//次の項目の枠の大きさ設定
			ImGui::SetNextItemWidth(250);

			////それぞれの回転量を調整
			//if (ImGui::DragFloat3(aPartsName.data(), MotionInfo->key_info[nNowKey]->key[nCnt]->rot, 0.01f, -3.14f, 3.14f))
			//{
			//	//モーション強制変更
			//	ForcedUpdate();
			//}
		}

		//回転量リセット
		if (ImGui::Button("AllReset"))
		{
			//モデル数分繰り替えす
			for (size_t nCnt = 0; nCnt < MotionInfo->key_info[nNowKey]->key.size(); nCnt++)
			{
				//モーション強制変更
				MotionInfo->key_info[nNowKey]->key[nCnt]->rot = ZeroVector3;
				ForcedUpdate();
			}
		}
		//tree
		ImGui::TreePop();
	}

	//改行
	ImGui::Separator();

	////モーションの保存
	//if (ImGui::Button("MotionSave"))
	//{
	//	CMotion::SaveMotion(NowMotionType);
	//}

	//Widgetの大きさ調整終了
	ImGui::PopItemWidth();
}
//------------------------------------------------------------------------------
//オフセットの設定
//------------------------------------------------------------------------------
void CDebug_ViewerCharacter::OffsetViewer()
{
	CModel * pModel;

	std::vector<CModel*> vModelList = GetCharacterModelList();

	//モデル数分繰り替えす
	for (size_t nCnt = 0; nCnt < vModelList.size(); nCnt++)
	{
		//モデル名取得
		std::string aPartsName = CModel::GetModelFileName(vModelList[nCnt]->GetType(), nCnt);

		//頭の部分の文字列を消す("data/MODEL/)
		aPartsName.erase(aPartsName.begin(), aPartsName.begin() + 11);

		//次の項目の枠の大きさ設定
		ImGui::SetNextItemWidth(250);

		//モデルパーツのポインタ取得
		pModel = GetCharacterModelList()[nCnt];

		//それぞれのオフセットを調整
		if (ImGui::DragFloat3(aPartsName.data(), pModel->GetPosition(), 0.05f, -100.0f, 100.0f))
		{

		}
	}

	//if(ImGui::Button("OffsetSave"))
	//{
	//	pModelCharacter->SaveModelOffset();
	//}
}
