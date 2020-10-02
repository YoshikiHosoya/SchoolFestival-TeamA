//------------------------------------------------------------------------------
//
//テクスチャアニメーション3D処理  [TexAnimation3D.h]
//Author:Fujiwara Masato
//
//------------------------------------------------------------------------------
#ifndef _TEXTUREANIMATION3D_H_
#define _TEXTUREANIMATION3D_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "scene3D.h"
#include "TexAnimationBase.h"
//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
//2重継承
//Scene側でポリゴン制御、TexAnimation側でアニメーション処理
class CTexAnimation3D : public CScene3D, public CTexAnimationBase
{
public:
	CTexAnimation3D();					//コンストラクタ
	CTexAnimation3D(OBJ_TYPE obj);		//コンストラクタ
	~CTexAnimation3D();					//デストラクタ

	HRESULT Init();				//初期化
	void Uninit();				//終了
	void Update();				//更新
	void Draw();				//描画
	void ShowDebugInfo();		//デバッグ情報表示
	static void Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, CTexture::SEPARATE_TEX_TYPE type,
		int nCntSwitch, CScene::OBJ_TYPE objtype,bool bLoop);	//生成処理
private:
};

#endif