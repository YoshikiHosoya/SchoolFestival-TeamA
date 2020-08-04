//------------------------------------------------------------------------------
//
//テクスチャアニメーション2D処理  [TexAnimation2D.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _EFFECTANIMATION2D_H_
#define _EFFECTANIMATION2D_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "scene2D.h"
#include "TexAnimationBase.h"
//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
//2重継承
//Scene側でポリゴン制御、TexAnimation側でアニメーション処理
class CTexAnimation2D : public CScene2D , public CTexAnimationBase
{
public:
	CTexAnimation2D();					//コンストラクタ
	CTexAnimation2D(OBJ_TYPE obj);		//コンストラクタ
	~CTexAnimation2D();					//デストラクタ

	HRESULT Init();				//初期化
	void Uninit();				//終了
	void Update();				//更新
	void Draw();				//描画
	void ShowDebugInfo();		//デバッグ情報表示
	static void Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,D3DXVECTOR3 rot, CTexture::SEPARATE_TEX_TYPE type, int nCntSwitch, CScene::OBJ_TYPE objtype);	//生成処理

private:
};

#endif