//-----------------------------------------------------------------------------
//
//3Dゲージ処理  [3Dgauge.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _GAUGE_3D_H_
#define _GAUGE_3D_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "gauge.h"

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CScene3D;

class CGauge_3D : public::CGauge
{
public:
	CGauge_3D();			//コンストラクタ
	~CGauge_3D();			//デストラクタ


	HRESULT Init();			//初期化
	void Uninit();			//終了
	void Update();			//更新
	void Draw();			//描画
	void ShowDebugInfo();	//デバッグ情報表記
	static std::shared_ptr<CGauge_3D> Create(D3DXVECTOR3 const &pos, D3DXVECTOR3 const &gaugeSize, D3DXVECTOR3 const &offset,int const nMaxLife, D3DXMATRIX mtx);		//生成処理

	void UpdateGaugeMag(float GreenMag, float RedMag, float BlueMag);	//ゲージの更新処理
	void SetPos(D3DXVECTOR3 const &pos);								//座標設定
	void SetMtx(D3DXMATRIX mtx);										//マトリックス設定
	void SetFlash(bool bFlash) { m_bFlashing = bFlash; };				//フラッシュ状態設定

private:
	std::vector<std::shared_ptr<CScene3D>> m_pScene3DList;				//3Dポリゴンのリスト
	D3DXVECTOR3 m_offset;												//持ち主からゲージまでのオフセット
	D3DXMATRIX m_Mtx;													//持ち主のマトリックス
	bool m_bFlashing;													//点滅状態
	int m_nCntFlash;													//点滅用のカウンタ
	void MakeGauge(D3DXVECTOR3 pos, D3DXVECTOR3 size);					//ゲージ生成
};

#endif