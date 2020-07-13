//------------------------------------------------------------------------------
//
//ナンバー処理  [number.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _NUMBER_H_
#define _NUMBER_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "scene2D.h"
//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CNumber : public CScene2D
{
public:
	CNumber();
	~CNumber();

	HRESULT Init();																			//初期化
	void Uninit();																			//終了
	void Update();																			//更新
	void Draw();																			//描画
	void ShowDebugInfo();																	//デバッグ情報表示
	static std::unique_ptr<CNumber> Create(D3DXVECTOR3 pos , D3DXVECTOR3 size);				//生成処理
	void SetChangeAnimtion() { m_bChangeAnimation = true; m_nCntAnimation = 0; };			//数字が変わったアニメーション設定

	void SetDisp(bool bDisp)	{ m_bDisp = bDisp; };
	bool GetDisp()				{ return m_bDisp; };

private:
	static D3DXVECTOR2 m_UVsize;															//テクスチャのUVサイズ
	D3DXVECTOR3 m_DefaultSize;																//初期の大きさ
	bool m_bChangeAnimation;																//数値が切り替わった時にアニメーション
	int m_nCntAnimation;																	//アニメーション用のカウンタ
	bool m_bDisp;
};

#endif