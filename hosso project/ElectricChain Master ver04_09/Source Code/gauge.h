//-----------------------------------------------------------------------------
//
//ゲージ処理  [gauge.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _GAUGE_H_
#define _GAUGE_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CGauge : public::CScene
{
public:
	CGauge();		//コンストラクタ
	~CGauge();		//デストラクタ

	enum GAUGETYPE
	{
		GAUGE_FLAME = 0,	//ゲージ枠
		GAUGE_RED,			//赤ゲージ　ダメージ食らった時ちょっとずつ減る
		GAUGE_BLUE,			//青ゲージ　仮ダメージ　全部青くなったらスタン
		GAUGE_GREEN,		//緑ゲージ
		GAUGE_MAX
	};

	virtual HRESULT Init();					//初期化
	virtual void Uninit();					//終了
	virtual void Update();					//更新
	virtual void Draw();					//描画
	virtual void ShowDebugInfo();			//デバッグ情報表記

	virtual void UpdateGaugeMag(float GreenMag, float RedMag, float BlueMag) = 0;		//ゲージの倍率計算　オーバーライド用

	void SetLife(int nLife, int nBlueLife);	//ライフ設定
	void SetMaxLife(int nMaxLife);			//最大ライフ設定
	void DeleteGauge();						//ゲージ消去

	int GetLife() { return m_nLife; };		//ライフの値取得
protected:

private:
	int m_nMaxLife;							//最大HP
	int m_nLife;							//HP
	int m_nLifeBlue;						//HPの赤い部分
	int m_nLifeRed;							//HPの赤い部分
	int m_nLifeRedInterval;					//赤い部分が減り始めるまでの時間
	int m_nRedGaugeDeleteSpeed;				//赤い部分の減る速度
	void CalcGaugeMag();					//ゲージの倍率計算
};

#endif