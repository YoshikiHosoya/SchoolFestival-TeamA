//------------------------------------------------------------------------------
//
//連鎖の電撃処理  [ChainElectric.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _CHAINELECTRIC_H_
#define _CHAINELECTRIC_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"
//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CChainElectric : public CScene
{
public:
	CChainElectric();						//コンストラクタ
	~CChainElectric();						//デストラクタ

	HRESULT Init();							//初期化
	void Uninit();							//終了
	void Update();							//更新
	void Draw();							//描画
	void ShowDebugInfo();					//デバッグ情報表示
	static void Create(D3DXVECTOR3 StartPos , D3DXVECTOR3 GoalPos, D3DXVECTOR3 size,D3DXCOLOR col,int nCntEnd);	//生成処理

private:
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;		//頂点バッファへのポインタ
	int m_nCntAnim;							//アニメーションカウンター
	int m_nPatternAnim;						//アニメーションパターン

	D3DXVECTOR3 m_pos;						//座標
	D3DXVECTOR3 m_rot;						//回転
	D3DXVECTOR3 m_size;						//サイズ
	D3DXCOLOR m_col;						//色
	D3DXMATRIX m_Mtx;						//マトリックス
	int m_nLife;

	void MakeVertex();						//頂点生成
};

#endif