//------------------------------------------------------------------------------
//
//パーティクル処理  [particle.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _PARTICLE_H_
#define _PARTICLE_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define MAX_PARTICLE (100000)
//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
//パーティクルの粒子
class COneParticle
{
	public:
		COneParticle() { nNumParticleAll++; };		//コンストラクタ
		~COneParticle() { nNumParticleAll--; };		//デストラクタ

	//生成関数
	static std::unique_ptr<COneParticle> Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot)
	{
		//メモリ確保
		std::unique_ptr<COneParticle> pOneParticle(new COneParticle);

		//情報代入
		pOneParticle->m_pos = pos;
		pOneParticle->m_move = move;
		pOneParticle->m_rot = rot;

		//return
		return pOneParticle;
	}
	static int GetNumAll() {return nNumParticleAll;};		//総数取得

	D3DXVECTOR3 m_pos;				//座標
	D3DXVECTOR3 m_move;				//移動量
	D3DXVECTOR3 m_rot;				//回転量
	D3DXMATRIX m_Mtx;				//マトリックス
	static int nNumParticleAll;		//総数
};

//パーティクルのまとまり
class CParticle
{
public:
	CParticle();									//コンストラクタ
	~CParticle();									//デストラクタ

	HRESULT Init();									//初期化
	void Uninit();									//終了
	void Update();									//更新
	void Draw();									//描画
	void ShowDebugInfo();							//デバッグ情報表記
	void UpdateVertex();							//頂点の更新
	static void ResetVertex();						//頂点リセット
	static HRESULT MakeVertex();					//頂点生成
	static void ReleaseVertex();					//頂点破棄
	static void ResetVertexID();					//頂点IDリセット　画面が停止してもパーティクルの処理を行う為

	static void Create(D3DXVECTOR3 pos, int nLife, float fRadius, D3DXCOLOR col,int nNumber, float fSpeed);		//生成処理
	static void DetailsCreate(D3DXVECTOR3 pos, int nLife, float fRadius, D3DXCOLOR col, int nNumber, float fSpeed, float fAlphaDamping, float fRadiusDamping, CTexture::TEX_TYPE textype);

	bool GetDeleteFlag() { return m_bDeleteFlag; };

private:
	static LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;						//頂点バッファへのポインタ
	static int m_nVertexID;											//頂点ID
	int m_nLife;													//ライフ
	int m_nNumber;													//個数
	float m_fRadius;												//半径
	D3DXCOLOR m_col;												//色
	float m_fRadiusDamping;											//半径の減衰値
	float m_fAlphaDamping;											//アルファ値の減衰値
	CTexture::TEX_TYPE m_Textype;									//テクスチャ
	std::vector<std::unique_ptr<COneParticle>> m_pParticleList;		//パーティクルの構造体のリスト

	bool m_bDeleteFlag;												//消去フラグ

	void SetParticle(D3DXVECTOR3 &pos,float fSpeed);				//パーティクル設定
};

#endif