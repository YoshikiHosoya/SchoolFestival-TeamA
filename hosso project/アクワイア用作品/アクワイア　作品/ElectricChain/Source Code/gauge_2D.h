//-----------------------------------------------------------------------------
//
//2Dゲージ処理  [2Dgauge.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _GAUGE_2D_H_
#define _GAUGE_2D_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "gauge.h"

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CScene2D;

class CGauge_2D : public::CGauge
{
public:
	CGauge_2D();			//コンストラクタ
	~CGauge_2D();			//デストラクタ


	HRESULT Init();			//初期化
	void Uninit();			//終了
	void Update();			//更新
	void Draw();			//描画
	void ShowDebugInfo();	//デバッグ情報表記
	static std::shared_ptr<CGauge_2D> Create(D3DXVECTOR3 const &pos, D3DXVECTOR3 const &gaugeSize,int const nMaxLife);

	void UpdateGaugeMag(float GreenMag, float RedMag, float BlueMag);	//ゲージの更新処理
	void SetPos(D3DXVECTOR3 const &pos);								//座標設定
protected:

private:
	std::vector<std::shared_ptr<CScene2D>> m_pScene2DList;		//2Dポリゴンのリスト
	void MakeGauge(D3DXVECTOR3 pos, D3DXVECTOR3 size);			//ゲージ生成
};

#endif