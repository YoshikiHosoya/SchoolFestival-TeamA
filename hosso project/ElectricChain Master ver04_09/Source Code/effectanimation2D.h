//------------------------------------------------------------------------------
//
//エフェクトアニメーション2D処理  [effectanimation2D.h]
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
#include "scene.h"
//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CEffectAnimation2D : public CScene2D
{
public:
	CEffectAnimation2D();		//コンストラクタ
	~CEffectAnimation2D();		//デストラクタ

	HRESULT Init();				//初期化
	void Uninit();				//終了
	void Update();				//更新
	void Draw();				//描画
	void ShowDebugInfo();		//デバッグ情報表示
	static void Create(D3DXVECTOR3 pos , D3DXVECTOR3 size,CTexture::SEPARATE_TEX_TYPE type,float fAngle, int nCntSwitch,OBJTYPE objtype);	//生成処理

private:
	CTexture::SEPARATE_TEX_TYPE m_Type;						//エフェクトのタイプ
	int m_nCntAnim;											//アニメーションカウンター
	int m_nPatternAnim;										//アニメーションパターン
	int m_nCntSwitch;										//アニメーション切替のフレーム

	static std::vector<std::string> m_apFileName;			//ファイル名
};

#endif