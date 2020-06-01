//------------------------------------------------------------------------------
//
//キャラクター処理  [character.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "Debug_OneModelCharacter.h"
#include "../modelinfo.h"
#include "../manager.h"
#include "../renderer.h"
#include "../camera.h"
#include "../modelcharacter.h"
#include "../collision.h"
#include "../meshfield.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define MOVESPEED (10.0f)

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
Debug_OneModelCharacter::Debug_OneModelCharacter()
{
}

//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
Debug_OneModelCharacter::~Debug_OneModelCharacter()
{
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT Debug_OneModelCharacter::Init()
{
	CModel_Object::Init();

	CSceneX::BindModelInfo(CModelInfo::GetModelInfo(CModelInfo::MODEL_MAPOBJECT_HEAD));


	//成功
	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void Debug_OneModelCharacter::Uninit()
{
	CModel_Object::Uninit();
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void Debug_OneModelCharacter::Update()
{
	CModel_Object::Update();

	//カメラ回転情報取得
	float fCameraRot = CManager::GetRenderer()->GetCamera()->GetCameraRot().y;

	//座標取得
	D3DXVECTOR3 &rPos = GetPos();

	if (CHossoLibrary::CheckMove(CHossoLibrary::LEFT))
	{
		if (CHossoLibrary::CheckMove(CHossoLibrary::UP))
		{
			//左上
			rPos.x += sinf(-D3DX_PI * 0.75f - fCameraRot) * MOVESPEED;
			rPos.z -= cosf(-D3DX_PI * 0.75f - fCameraRot) * MOVESPEED;

		}
		else if (CHossoLibrary::CheckMove(CHossoLibrary::DOWN))
		{
			//左下
			rPos.x += sinf(-D3DX_PI * 0.25f - fCameraRot) * MOVESPEED;
			rPos.z -= cosf(-D3DX_PI * 0.25f - fCameraRot) * MOVESPEED;

		}
		else
		{
			//左
			rPos.x += sinf(-D3DX_PI * 0.5f - fCameraRot) * MOVESPEED;
			rPos.z -= cosf(-D3DX_PI * 0.5f - fCameraRot) * MOVESPEED;

		}
	}
	else if (CHossoLibrary::CheckMove(CHossoLibrary::RIGHT))
	{
		if (CHossoLibrary::CheckMove(CHossoLibrary::UP))
		{
			//右上
			rPos.x += sinf(D3DX_PI * 0.75f - fCameraRot) * MOVESPEED;
			rPos.z -= cosf(D3DX_PI * 0.75f - fCameraRot) * MOVESPEED;

		}
		else if (CHossoLibrary::CheckMove(CHossoLibrary::DOWN))
		{
			//右下
			rPos.x += sinf(D3DX_PI * 0.25f - fCameraRot) * MOVESPEED;
			rPos.z -= cosf(D3DX_PI * 0.25f - fCameraRot) * MOVESPEED;

		}
		else
		{
			//右
			rPos.x += sinf(D3DX_PI * 0.5f - fCameraRot) * MOVESPEED;
			rPos.z -= cosf(D3DX_PI * 0.5f - fCameraRot) * MOVESPEED;


		}
	}
	else if (CHossoLibrary::CheckMove(CHossoLibrary::UP))
	{
		//上
		rPos.x += sinf(D3DX_PI * 1.0f - fCameraRot) * MOVESPEED;
		rPos.z -= cosf(D3DX_PI * 1.0f - fCameraRot) * MOVESPEED;


	}
	else if (CHossoLibrary::CheckMove(CHossoLibrary::DOWN))
	{
		//下
		rPos.x += sinf(D3DX_PI * 0 - fCameraRot) * MOVESPEED;
		rPos.z -= cosf(D3DX_PI * 0 - fCameraRot) * MOVESPEED;

	}

	//重力
	rPos.y -= 50.0f;

	//Sceneのリスト
	std::vector<std::shared_ptr<CScene>> pSceneList;

	//シーン情報取得
	CScene::GetSceneList(CScene::OBJTYPE_MESHFIELD, pSceneList);
	//配列に入ってるか
	if (!pSceneList.empty())
	{
		//要素分
		for (size_t nCnt = 0; nCnt < pSceneList.size(); nCnt++)
		{
			//ポインタ取得 CMeshField型にキャスト
			CMeshField *pMeshField = ((CMeshField*)pSceneList[nCnt].get());

			//nullcheck
			if (pMeshField)
			{
				//高さ取得
				pMeshField->GetHeight(GetPos());
			}
		}
	}


}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void Debug_OneModelCharacter::Draw()
{
	CModel_Object::Draw();
}
//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void Debug_OneModelCharacter::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}

//------------------------------------------------------------------------------
//生成
//------------------------------------------------------------------------------
void Debug_OneModelCharacter::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//メモリ確保
	std::shared_ptr<Debug_OneModelCharacter> pOneModelChara(new Debug_OneModelCharacter);

	//nullcheck
	if (pOneModelChara)
	{
		//初期化
		pOneModelChara->Init();

		//情報設定
		pOneModelChara->SetPos(pos);
		pOneModelChara->SetRot(rot);

		//オブジェクトタイプ設定
		pOneModelChara->SetObjType(OBJTYPE_MAPOBJECT);
		pOneModelChara->AddSharedList(pOneModelChara);
	}
}