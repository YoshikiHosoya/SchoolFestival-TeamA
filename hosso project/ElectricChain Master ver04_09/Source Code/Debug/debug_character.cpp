//------------------------------------------------------------------------------
//
//キャラクター処理  [character.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "debug_character.h"
#include "../modelinfo.h"
#include "../manager.h"
#include "../renderer.h"
#include "../sound.h"
#include "../game.h"
#include "../camera.h"
#include "../modelcharacter.h"
#include "../motion.h"
#include "../collision.h"
#include "../keyboard.h"
#include "../meshfield.h"
#include "../modelparts.h"
#include "../modelparts_weapon.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CDebug_Character::CDebug_Character()
{
}

//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CDebug_Character::~CDebug_Character()
{
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CDebug_Character::Init()
{
	CCharacter::Init();

	//成功
	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CDebug_Character::Uninit()
{
	CCharacter::Uninit();
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CDebug_Character::Update()
{
	CCharacter::Update();
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CDebug_Character::Draw()
{
	CCharacter::Draw();
}
//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CDebug_Character::ShowDebugInfo()
{
#ifdef _DEBUG
	static bool bMotion = true;

	//キャラクター情報情報
	if (ImGui::Begin("MotionViewer"))
	{
		if (ImGui::BeginTabBar("Viewer", bMotion))
		{
			if (ImGui::BeginTabItem("MotionViewer"))
			{
				MotionViewer();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("OffsetViewer"))
			{
				OffsetViewer();
				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}

		ImGui::End();

	}
#endif //DEBUG
}

//------------------------------------------------------------------------------
//生成
//------------------------------------------------------------------------------
std::shared_ptr<CDebug_Character> CDebug_Character::Create(CHARACTER_TYPE chara, CCharacter::PARAM_TYPE paramtype)
{
	//変数宣言
	std::shared_ptr<CDebug_Character> pCharacter = std::make_shared<CDebug_Character>();

	if (pCharacter)
	{
		//初期化7
		pCharacter->Init();

		//パラメータ設定
		pCharacter->SetParameter(chara, paramtype,pCharacter);

		//オブジェクトタイプ設定
		pCharacter->SetObjType(OBJTYPE_PLAYER);

		//リストに追加
		pCharacter->AddSharedList(pCharacter);
	}

	//生成した情報
	return pCharacter;
}

//------------------------------------------------------------------------------
//コンボボックス
//------------------------------------------------------------------------------
bool CDebug_Character::ShowMotionComboBox(CMotion::MOTION_TYPE &motiontype)
{
	bool bChange = false;

#ifdef _DEBUG

	std::vector<std::string > &aFileName = CMotion::GetFileName();

	//combo開始
	if (ImGui::BeginCombo("MotionName", aFileName[motiontype].data()))
	{
		//要素分繰り返す
		for (size_t nCnt = 0; nCnt < aFileName.size(); nCnt++)
		{

			//選択番号があってるかどうか
			bool is_selected = (aFileName[motiontype] == aFileName[nCnt]);

			//選択された時の処理
			if (ImGui::Selectable(aFileName[nCnt].data(), is_selected))
			{
				//現在の選択項目設定
				motiontype = (CMotion::MOTION_TYPE)nCnt;
				bChange = true;
			}

			////
			//if (is_selected)
			//{
			//	//スクロールの初期位置設定
			//	ImGui::SetItemDefaultFocus();
			//}
		}
		//combo終了
		ImGui::EndCombo();

	}
#endif //DEBUG
	return bChange;
}
//------------------------------------------------------------------------------
//モーションビューワ
//------------------------------------------------------------------------------
void CDebug_Character::MotionViewer()
{
	//キーボードのポインタ
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	//モデルキャラクターのポインタ
	CModelCharacter *pModelCharacter = GetModelCharacterPtr();

	//現在のキー
	int &nNowKey = pModelCharacter->GetKey();

	//モーションに関する情報
	CMotion::MOTION_TYPE &NowMotionType = pModelCharacter->GetMotion();
	CMotion::MOTION_INFO *MotionInfo = CMotion::GetMotion(NowMotionType);

	//攻撃系の情報が変わったかどうか
	bool bChangeAttackInfo = false;
	bool bChangeNowKey = false;

	//コピペ用のキー
	static CMotion::MOTION_TYPE CopyMotionType = CMotion::MOTION_NONE;
	static int nCopyKey = -1;



	//プレイヤー座標リセット
	if (ImGui::Button("PlayerPosReset"))
	{
		SetPos(ZeroVector3);
	}

	//モーションのコンボボックス
	if (ShowMotionComboBox(NowMotionType))
	{
		nNowKey = 0;
		SetAttack(false);
		ChangeMotion(NowMotionType);
		pModelCharacter->ForcedUpdate(NowMotionType, nNowKey);
		MotionInfo = CMotion::GetMotion(NowMotionType);

	}

	//改行しない
	ImGui::SameLine();

	//モーションリスタート
	if (ImGui::Button("ReStart") || pKeyboard->GetTrigger(DIK_RETURN))
	{
		nNowKey = 0;
		SetAttack(false);
		pModelCharacter->SetMotionStop(false);
		ChangeMotion(NowMotionType);
		pModelCharacter->ForcedUpdate(NowMotionType, nNowKey);
		MotionInfo = CMotion::GetMotion(NowMotionType);
	}

	//Widgetの大きさ設定
	ImGui::PushItemWidth(100);

	//ループ
	if (ImGui::Checkbox("bMotionStop", &pModelCharacter->GetMotionStop()))
	{

	}

	//ループ
	if (ImGui::Checkbox("bLoop", &MotionInfo->bLoop))
	{

	}

	//攻撃するかどうか
	ImGui::Text("bAttack %d", (int)MotionInfo->bAttack);

	//改行
	ImGui::Separator();

	//攻撃のモーションだった時
	if (MotionInfo->bAttack)
	{
		if (ImGui::TreeNode("AttackInfo"))
		{

			//軌跡の色　float型にキャスト
			float *rCol = MotionInfo->pAttackInfo->orbitcol;

			ImGui::SetNextItemWidth(250.0f);

			//色の設定
			if (ImGui::ColorEdit4("OrbitColor", rCol)) { bChangeAttackInfo = true; };

			//攻撃に関する情報
			if (ImGui::DragInt("AttackValue", &MotionInfo->pAttackInfo->nAttack, 0.3f, 0, 100))
			{
				bChangeAttackInfo = true;
			}
			if (ImGui::DragInt("BlueAttackValue", &MotionInfo->pAttackInfo->nBlueAttack, 0.3f, 0, 100))
			{
				bChangeAttackInfo = true;
			}
			if (ImGui::DragFloat("CollisionLength", &MotionInfo->pAttackInfo->fLength, 0.1f, 0.0f, 200.0f))
			{
				bChangeAttackInfo = true;
			}
			if (ImGui::DragFloat("CollisionRadius", &MotionInfo->pAttackInfo->fRadius, 0.1f, 0.0f, 50.0f))
			{
				bChangeAttackInfo = true;
			}

			//攻撃に関する情報が変わった時
			if (bChangeAttackInfo)
			{
				//攻撃の情報更新
				pModelCharacter->UpdateAttackInfo();
			}

			//開始のキー
			if (ImGui::InputInt("CollisionStartKey", &MotionInfo->pAttackInfo->nStartCollisonKey))
			{
				//範囲内に修正する
				CHossoLibrary::RangeLimit_Equal_Int(MotionInfo->pAttackInfo->nStartCollisonKey, 0, MotionInfo->pAttackInfo->nEndCollisionKey);

			}
			//終了のキー
			if (ImGui::InputInt("CollisionEndKEy", &MotionInfo->pAttackInfo->nEndCollisionKey))
			{
				//範囲内に修正する
				CHossoLibrary::RangeLimit_Equal_Int(MotionInfo->pAttackInfo->nEndCollisionKey, MotionInfo->pAttackInfo->nStartCollisonKey, MotionInfo->nNumKey);
			}

			//移動速度
			if (ImGui::DragFloat("MoveFront", &MotionInfo->pAttackInfo->fMoveFront, 0.02f, 0.0f, 30.0f))
			{

			}
			ImGui::SameLine();
			//移動速度
			if (ImGui::DragFloat("MoveUp", &MotionInfo->pAttackInfo->fMoveUp, 0.02f, -30.0f, 30.0f))
			{

			}
			ImGui::SameLine();
			//移動速度
			if (ImGui::InputInt("MoveKey", &MotionInfo->pAttackInfo->nMoveKey))
			{
				//範囲内に修正する
				CHossoLibrary::RangeLimit_Equal_Int(MotionInfo->pAttackInfo->nMoveKey, 0, MotionInfo->nNumKey);
			}

			//ノックバック
			if (ImGui::DragFloat("KnockBack_Front", &MotionInfo->pAttackInfo->fKnockBack_Front, 0.02f, 0.0f, 30.0f))
			{

			}
			ImGui::SameLine();
			//ノックバック
			if (ImGui::DragFloat("KnockBack_Up", &MotionInfo->pAttackInfo->fKnockBack_Up, 0.02f, -30.0f, 30.0f))
			{

			}
			ImGui::TreePop();
		}
		//改行
		ImGui::Separator();
	}

	//１F前のキーフレーム
	int nNumKeyOld = MotionInfo->nNumKey;

	//キー数
	if (ImGui::InputInt("NumKey", &MotionInfo->nNumKey))
	{
		//範囲内に修正する
		CHossoLibrary::RangeLimit_Equal_Int(MotionInfo->nNumKey, 0, 100);

		//キーが増えたか減ったか
		MotionInfo->nNumKey > nNumKeyOld ?
			CMotion::AddKeyInfo(NowMotionType, pModelCharacter->GetType()) :			//要素の追加　末尾
			CMotion::PopbackKeyInfo(NowMotionType);										//要素の削除　末尾
	}

	//フレーム数
	if (ImGui::InputInt("MaxFrame", &MotionInfo->pKeyInfoList[nNowKey]->nFrame))
	{

	}

	//改行
	ImGui::Separator();
	//原点の高さ調節
	if (ImGui::DragFloat("OriginHeight", &MotionInfo->pKeyInfoList[nNowKey]->fOriginHeight, 0.05f, -70.0f, 70.0f))
	{
		//モーション強制変更
		pModelCharacter->ForcedUpdate(NowMotionType, nNowKey);
	}


	//現在のキー
	if (ImGui::InputInt("NowKey", &nNowKey))
	{
		bChangeNowKey = true;
	}

	//キーボードの←→でも現在のキー変えたい
	if (pKeyboard->GetTrigger(DIK_LEFT))
	{
		bChangeNowKey = true;
		nNowKey--;
	}

	if (pKeyboard->GetTrigger(DIK_RIGHT))
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
		CMotion::MotionCopy(NowMotionType, nNowKey, CopyMotionType, nCopyKey);

		//モーション強制変更
		pModelCharacter->ForcedUpdate(NowMotionType, nNowKey);

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
		//キーチェック
		pModelCharacter->KeyCheck();

		//モーション強制変更
		pModelCharacter->ForcedUpdate(NowMotionType, nNowKey);
	}

	//改行
	ImGui::Separator();
	//パーツ回転
	if (ImGui::TreeNode("PartsRot"))
	{

		////モデル数分繰り替えす
		//for (int nCnt = 0; nCnt < pModelCharacter->GetModelNum(pModelCharacter->GetType()); nCnt++)
		//{
		//	//モデル名取得
		//	//std::string aPartsName = CModelCharacter::GetModelName(pModelCharacter->GetType(), nCnt).data();

		//	//頭の部分の文字列を消す("data/MODEL/)
		//	aPartsName.erase(aPartsName.begin(), aPartsName.begin() + 11);

		//	//次の項目の枠の大きさ設定
		//	ImGui::SetNextItemWidth(250);

		//	//それぞれの回転量を調整
		//	if (ImGui::DragFloat3(aPartsName.data(), MotionInfo->pKeyInfoList[nNowKey]->pKeyList[nCnt]->rotDest, 0.01f, -3.14f, 3.14f))
		//	{
		//		//モーション強制変更
		//		pModelCharacter->ForcedUpdate(NowMotionType, nNowKey);
		//	}
		//}

		//回転量リセット
		if (ImGui::Button("AllReset"))
		{
			//モデル数分繰り替えす
			for (int nCnt = 0; nCnt < pModelCharacter->GetModelNum(pModelCharacter->GetType()); nCnt++)
			{
				//モーション強制変更
				MotionInfo->pKeyInfoList[nNowKey]->pKeyList[nCnt]->rotDest = ZeroVector3;
				pModelCharacter->ForcedUpdate(NowMotionType, nNowKey);
			}
		}
		//tree
		ImGui::TreePop();
	}

	//改行
	ImGui::Separator();

	//モーションの保存
	if (ImGui::Button("MotionSave"))
	{
		CMotion::SaveMotion(NowMotionType);
	}

	//Widgetの大きさ調整終了
	ImGui::PopItemWidth();

}
//------------------------------------------------------------------------------
//オフセットの設定
//------------------------------------------------------------------------------
void CDebug_Character::OffsetViewer()
{
	//モデルキャラクターのポインタ
	CModelCharacter *pModelCharacter = GetModelCharacterPtr();

	CModelParts *pModelParts;

	////モデル数分繰り替えす
	//for (int nCnt = 0; nCnt < pModelCharacter->GetModelNum(pModelCharacter->GetType()); nCnt++)
	//{
	//	//モデル名取得
	//	std::string aPartsName = CModelCharacter::GetModelName(pModelCharacter->GetType(), nCnt).data();

	//	//頭の部分の文字列を消す("data/MODEL/)
	//	aPartsName.erase(aPartsName.begin(), aPartsName.begin() + 11);

	//	//次の項目の枠の大きさ設定
	//	ImGui::SetNextItemWidth(250);

	//	//モデルパーツのポインタ取得
	//	pModelParts = pModelCharacter->GetPartsPtr(nCnt);

	//	//それぞれの回転量を調整
	//	if (ImGui::DragFloat3(aPartsName.data(), pModelParts->GetPos(), 0.05f, -100.0f, 100.0f))
	//	{

	//	}
	//}

	if(ImGui::Button("OffsetSave"))
	{
		pModelCharacter->SaveModelOffset();
	}
}
