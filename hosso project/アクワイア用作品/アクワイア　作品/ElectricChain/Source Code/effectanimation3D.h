//------------------------------------------------------------------------------
//
//エフェクトアニメーション処理  [effectanimation.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _EFFECTANIMATION_H_
#define _EFFECTANIMATION_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "scene3D.h"
//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CEffectAnimation3D : public CScene3D
{
public:
	CEffectAnimation3D();		//コンストラクタ
	~CEffectAnimation3D();		//デストラクタ

	HRESULT Init();				//初期化
	void Uninit();				//終了
	void Update();				//更新
	void Draw();				//描画
	void ShowDebugInfo();		//デバッグ情報表示
	static void Create(D3DXVECTOR3 pos , D3DXVECTOR3 size, CTexture::SEPARATE_TEX_TYPE type,D3DXCOLOR col, float fAngle,int nCntSwitch);	//生成処理

private:
	CTexture::SEPARATE_TEX_TYPE m_Type;						//エフェクトのタイプ
	int m_nCntAnim;											//アニメーションカウンター
	int m_nPatternAnim;										//アニメーションパターン
	int m_nCntSwitch;										//1コマ当たりの時間 切り替えまでの時間

	static std::vector<std::string> m_apFileName;			//ファイル名
};

#endif