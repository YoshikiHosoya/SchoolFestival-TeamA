//------------------------------------------------------------------------------
//
//デバッグ用のキャラクタ  [Debug_OneModelCharacter.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _DEBUG_ONE_MODEL_CHARACTER
#define _DEBUG_ONE_MODEL_CHARACTER
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "../main.h"
#include "../model_object.h"
//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class Debug_OneModelCharacter : public CModel_Object
{
public:

	Debug_OneModelCharacter();						//コンストラクタ
	~Debug_OneModelCharacter();						//デストラクタ

	HRESULT Init();									//初期化
	void Uninit();									//終了
	void Update();									//更新
	void Draw();									//描画
	void ShowDebugInfo();							//デバッグ情報表記

	static void Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			//座標
private:
};
#endif