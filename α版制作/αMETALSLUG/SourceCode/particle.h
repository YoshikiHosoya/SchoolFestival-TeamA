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
#define MAX_PARTICLE (100000)									//パーティクルの最大数
#define DEFAULT_TEXTURE (CTexture::TEX_EFFECT_PARTICLE)			//デフォルトで使用するテクスチャ
#define DEFAULT_DAMPING (0.95f)									//デフォルトの減衰値
//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------


class CParticleParam
{
public:
	//パーティクルの種類
	enum PARTICLE_TYPE
	{
		PARTICLE_DEFAULT = 0,
		PARTICLE_EXPLOSION,
		PARTICLE_BLOOD,
		PARTICLE_MAX,
	};

	//パーティクルの向き
	enum PARTICLE_SHAPE
	{
		SHAPE_SPHERE = 0 ,
		SHAPE_CONE,
		SHAPE_CIRCLE_XY,
		SHAPE_LINE,
	};

	//コンストラクタ
	CParticleParam()
	{
		m_nLife = 50;										//ライフ
		m_fRadius = 15.0f;									//半径
		m_col = WhiteColor;									//色

		m_nNumber = 10;										//個数
		m_fSpeed = 10.0f;									//速度

		m_fRadiusDamping = DEFAULT_DAMPING;					//半径の減衰地
		m_fAlphaDamping = DEFAULT_DAMPING;					//アルファ値の減衰値
		m_Textype = CTexture::TEX_EFFECT_PARTICLE;			//テクスチャ
		m_shape = SHAPE_SPHERE;
		m_ParticleType = PARTICLE_DEFAULT;					//パーティクルのタイプ

	}
	~CParticleParam() {};

	void SetParamater(int nLife, float fRadius, D3DXCOLOR col, float fRadiusDamping = DEFAULT_DAMPING, float fAlphaDamping = DEFAULT_DAMPING,
						CTexture::TEX_TYPE textype = CTexture::TEX_EFFECT_PARTICLE,int nNumber = 10,float fSpeed = 10.0f);
	void UpdateParam();


	static HRESULT LoadParticleDefaultParam();
	static HRESULT SaveParticleDefaultParam(CParticleParam *pSaveParam);

	//Get関数
	int &GetLife()					{ return m_nLife; };				//ライフ
	float &GetRadius()				{ return m_fRadius; };				//半径
	D3DXCOLOR &GetCol()				{ return m_col; };					//色

	int &GetNumber()				{ return m_nNumber; };				//個数
	float &GetSpeed()				{ return m_fSpeed; };				//速度
	PARTICLE_SHAPE &GetShape()		{ return m_shape; };				//パーティクルの方向
	bool&GetSpeedRandom()			{ return m_bSpeedRandom; };			//パーティクルの速度がランダムかどうか

	float &GetRadiusDamping()		{ return m_fRadiusDamping; };		//半径の減衰地
	float &GetAlphaDamping()		{ return m_fAlphaDamping; };		//アルファ値の減衰値
	CTexture::TEX_TYPE &GetTex()	{ return m_Textype; };				//テクスチャ
	PARTICLE_TYPE &GetType()		{ return m_ParticleType; };			//テクスチャ

	static CParticleParam *GetDefaultParam(CParticleParam::PARTICLE_TYPE type) { return m_pParticleDefaultParamList[type].get(); };
	static bool ShowParamConboBox(CParticleParam::PARTICLE_TYPE & rType);
	//オペレータ
	void *operator = (const CParticleParam *pParam);

private:
	static std::vector<std::unique_ptr<CParticleParam>> m_pParticleDefaultParamList;	//パーティクルの初期パラメータのリスト
	static std::vector<std::string> m_aFileNameList;									//読み込むファイルのリスト

	int m_nLife;									//ライフ
	float m_fRadius;								//半径
	D3DXCOLOR m_col;								//色

	int m_nNumber;									//個数
	float m_fSpeed;									//速度
	PARTICLE_SHAPE m_shape;							//パーティクルの出方
	bool m_bSpeedRandom;							//速度がランダムかどうか

	float m_fRadiusDamping;							//半径の減衰値
	float m_fAlphaDamping;							//アルファ値の減衰値
	CTexture::TEX_TYPE m_Textype;					//テクスチャ
	PARTICLE_TYPE m_ParticleType;					//パーティクルのタイプ

};

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
	static void DetailsCreate(D3DXVECTOR3 pos, int nLife, float fRadius, D3DXCOLOR col, int nNumber,
							float fSpeed, float fAlphaDamping, float fRadiusDamping, CTexture::TEX_TYPE textype);

	static void CreateFromText(D3DXVECTOR3 pos, CParticleParam::PARTICLE_TYPE type);

	bool GetDeleteFlag() { return m_bDeleteFlag; };

private:
	static LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;											//頂点バッファへのポインタ
	static int m_nVertexID;																//頂点ID
	std::unique_ptr<CParticleParam> m_pParticleParam;									//パーティクルの現在のパラメータ

	std::vector<std::unique_ptr<COneParticle>> m_pParticleList;		//パーティクルの構造体のリスト
	CParticleParam::PARTICLE_TYPE m_type;							//パーティクルの種類
	bool m_bDeleteFlag;												//消去フラグ

	void SetParticle(D3DXVECTOR3 &pos, CParticleParam *pShape);				//パーティクル設定

};

#endif
