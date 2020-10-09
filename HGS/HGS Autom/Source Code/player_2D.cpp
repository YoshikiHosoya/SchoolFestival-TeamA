//------------------------------------------------------------------------------
//
//プレイヤー2D処理  [player_2D.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "player_2D.h"
#include "manager.h"
#include "renderer.h"
#include "Pad_XInput.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CPlayer_2D::CPlayer_2D()
{
}

//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CPlayer_2D::~CPlayer_2D()
{
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CPlayer_2D::Init()
{
	CCharacter_2D::Init();

	//メモリ確保
	std::unique_ptr<CScene2D> pScene2D = CScene2D::Create_SelfManagement(GetPos(), D3DXVECTOR3(50.0f, 50.0f, 0.0f));

	//テクスチャ設定
	pScene2D->BindTexture(CTexture::GetTexture(CTexture::SEPARATE_TEX_PLAYER));

	//Scene2Dセット
	SetScene2D(std::move(pScene2D));

	//重力無効
	CCharacter::SetGravity(false);

	//成功
	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CPlayer_2D::Uninit()
{
	CCharacter_2D::Uninit();
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CPlayer_2D::Update()
{
	//移動入力
	MoveInput();

	//更新
	CCharacter_2D::Update();
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CPlayer_2D::Draw()
{
	CCharacter_2D::Draw();
}

//------------------------------------------------------------------------------
//移動の入力
//------------------------------------------------------------------------------
void CPlayer_2D::MoveInput()
{
	//ゲームパッドの情報取得
	CPad_XInput *pGamePad = CManager::GetXInput();

	//変数宣言
	float joypadX, joypadY;

	//ジョイパッドの移動処理
	pGamePad->GetStickLeft(&joypadX, &joypadY);

	if (joypadX != 0 || joypadY != 0)
	{
		GetMove().x += joypadX * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed() / 32768.0f;
		GetMove().y -= joypadY * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed() / 32768.0f;
	}

	//[D]キーを押した時
	if (CHossoLibrary::CheckMove(CHossoLibrary::RIGHT))
	{
		//[W]キーを押した時
		if (CHossoLibrary::CheckMove(CHossoLibrary::UP))
		{
			//右上に移動
			GetMove().x += sinf(D3DX_PI * 0.75f) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();
			GetMove().y += cosf(D3DX_PI * 0.75f) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();

		}
		//[S]キーを押した時
		else if (CHossoLibrary::CheckMove(CHossoLibrary::DOWN))
		{
			//右下に移動
			GetMove().x += sinf(D3DX_PI * 0.25f) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();
			GetMove().y += cosf(D3DX_PI * 0.25f) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();
		}
		else
		{
			//右に移動
			GetMove().x += sinf(D3DX_PI * 0.5f) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();
			GetMove().y += cosf(D3DX_PI * 0.5f) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();

		}
	}
	//[A]キーを押した時
	else if (CHossoLibrary::CheckMove(CHossoLibrary::LEFT))
	{
		//[W]キーを押した時
		if (CHossoLibrary::CheckMove(CHossoLibrary::UP))
		{
			//左上に移動
			GetMove().x += sinf(-D3DX_PI * 0.75f) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();
			GetMove().y += cosf(-D3DX_PI * 0.75f) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();
		}
		//[S]キーを押した時
		else if (CHossoLibrary::CheckMove(CHossoLibrary::DOWN))
		{
			//左下に移動
			GetMove().x += sinf(-D3DX_PI * 0.25f) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();
			GetMove().y += cosf(-D3DX_PI * 0.25f) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();
		}
		else
		{
			//左に移動
			GetMove().x += sinf(-D3DX_PI * 0.5f) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();
			GetMove().y += cosf(-D3DX_PI * 0.5f) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();

		}
	}
	//[W]キーを押した時
	else if (CHossoLibrary::CheckMove(CHossoLibrary::UP))
	{
		//上に移動
		GetMove().x += sinf(D3DX_PI * 1.0f) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();
		GetMove().y += cosf(D3DX_PI * 1.0f) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();
	}
	//[S]キーを押した時
	else if (CHossoLibrary::CheckMove(CHossoLibrary::DOWN))
	{
		//下に移動
		GetMove().x += sinf(D3DX_PI * 0) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();
		GetMove().y += cosf(D3DX_PI * 0) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();
	}
}

//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CPlayer_2D::ShowDebugInfo()
{
#ifdef _DEBUG
	//プレイヤー情報情報
	if (ImGui::TreeNode("PlayerInfo"))
	{
		//キャラクター情報表示
		ShowCharacterInfo();

		ImGui::TreePop();
	}
#endif //DEBUG
}

//------------------------------------------------------------------------------
//ダメージ受けた後の処理
//------------------------------------------------------------------------------
void CPlayer_2D::DamageAction()
{

}
//------------------------------------------------------------------------------
//死亡時の処理
//------------------------------------------------------------------------------
void CPlayer_2D::DeathAction()
{
	////ゲーム終了
	//CManager::GetGame()->SetGamestate(CGame::STATE_GAMECLEAR);
}
//------------------------------------------------------------------------------
//ステート変更処理
//------------------------------------------------------------------------------
void CPlayer_2D::SetState(STATE nextstate)
{
	CCharacter_2D::SetState(nextstate);
	switch (nextstate)
	{
	case CCharacter::STATE_NORMAL:
		break;
	}
}


//------------------------------------------------------------------------------
//生成処理
//------------------------------------------------------------------------------
std::shared_ptr<CPlayer_2D> CPlayer_2D::Create(D3DXVECTOR3 pos)
{
	//変数宣言
	std::shared_ptr<CPlayer_2D> pPlayer = std::make_shared<CPlayer_2D>();


	if (pPlayer)
	{
		//初期化
		pPlayer->Init();

		//座標設定
		pPlayer->SetPos(pos);

		//オブジェクトタイプ設定
		pPlayer->SetObjType(OBJTYPE_PLAYER);

		//リストに追加
		pPlayer->AddSharedList(pPlayer);

		return pPlayer;
	}

	//生成した情報
	return nullptr;
}

