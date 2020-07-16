//------------------------------------------------------------------------------
//
//パーティクルのパラメータクラス  [particleparamater.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _PARTICLEPARAMATER_H_
#define _PARTICLEPARAMATER_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define DEFAULT_TEXTURE (CTexture::TEX_EFFECT_PARTICLE)			//デフォルトで使用するテクスチャ
#define DEFAULT_DAMPING (0.95f)									//デフォルトの減衰値
#define DEFAULT_GRAVITY_POWER (0.8f)							//デフォルトの重力の大きさ
//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CParticleParam
{
public:
	//パーティクルのテキスト
	enum PARTICLE_TEXT
	{
		PARTICLE_DEFAULT = 0,
		PARTICLE_EXPLOSION,
		PARTICLE_BLOOD,
		PARTICLE_SUMPLE,
		PARTICLE_HEAVY_MACHINEGUN,
		PARTICLE_TANKGUN,
		PARTICLE_LAZER,

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
		m_bGravity = false;														//重力
		m_bSpeedRandom = false;													//速度がランダムかどうか
		m_bAlphaBlend = true;													//αブレンドするか

		m_nLife = 50;															//ライフ
		m_nNumber = 10;															//個数
		m_fSpeed = 10.0f;														//速度
		m_fRange = 0.5f;														//範囲
		m_fAlphaDamping = DEFAULT_DAMPING;										//アルファ値の減衰値
		m_fGravityPower = DEFAULT_GRAVITY_POWER;								//重力の大きさ

		m_bAnimation = false;													//アニメーションするかどうか
		m_bAnimationLoop = false;												//アニメーションループするかどうか
		m_nAnimationCntSwitch = 1;												//アニメーション切替のカウント

		m_Size = D3DXVECTOR3(15.0f,15.0f,0.0f);									//サイズ
		m_SizeDamping = D3DXVECTOR3(DEFAULT_DAMPING, DEFAULT_DAMPING, 0.0f);	//サイズの減衰地
		m_col = WhiteColor;														//色
		m_rot = ZeroVector3;													//角度

		m_Textype = CTexture::TEX_EFFECT_PARTICLE;								//テクスチャ
		m_SeparateTex = CTexture::SEPARATE_TEX_EFFECT_EXPLOSION01;				//分割テクスチャ
		m_shape = SHAPE_SPHERE;													//パーティクルの方向
		m_ParticleType = PARTICLE_DEFAULT;										//パーティクルのタイプ
	}
	~CParticleParam() {};

	void SetParamater(int nLife, D3DXVECTOR3 size, D3DXCOLOR col,int nNumber,float fSpeed);
	void UpdateParam();


	static HRESULT LoadParticleDefaultParam();
	static HRESULT SaveParticleDefaultParam(CParticleParam *pSaveParam);

	//Get関数
	static std::vector<std::string> &GetFileNameList() {	return m_aFileNameList;};

	bool&GetSpeedRandom()								{ return m_bSpeedRandom; };			//パーティクルの速度がランダムかどうか
	bool &GetGravity()									{ return m_bGravity; };				//重力
	bool &GetAlphaBlend()								{ return m_bAlphaBlend;};			//αブレンドするか
	int &GetLife()										{ return m_nLife; };				//ライフ
	int &GetNumber()									{ return m_nNumber; };				//個数
	float &GetSpeed()									{ return m_fSpeed; };				//速度
	float &GetRange()									{ return m_fRange; };				//角度
	float &GetAlphaDamping()							{ return m_fAlphaDamping; };		//アルファ値の減衰値
	float &GetGravityPower()							{ return m_fGravityPower; };		//重力の大きさ
	D3DXVECTOR3 &GetSize()								{ return m_Size; };					//サイズ
	D3DXVECTOR3 &GetSizeDamping()						{ return m_SizeDamping; };			//サイズの減衰地
	D3DXCOLOR &GetCol()									{ return m_col; };					//色
	D3DXVECTOR3 &GetRot()								{ return m_rot;};					//角度
	bool &GetAnimation()								{ return m_bAnimation;};			//アニメーションするかどうか
	bool &GetAnimationLoop()							{ return m_bAnimationLoop; };		//アニメーションループするかどうか
	int &GetAnimationCntSwitch()						{ return m_nAnimationCntSwitch; };	//アニメーション切替のカウント

	PARTICLE_SHAPE &GetShape()							{ return m_shape; };				//パーティクルの方向
	CTexture::TEX_TYPE &GetTex()						{ return m_Textype; };				//テクスチャ
	CTexture::SEPARATE_TEX_TYPE &GetSeparateTex()		{ return m_SeparateTex; };			//分割テクスチャ
	PARTICLE_TEXT &GetType()							{ return m_ParticleType; };			//パーティクルのタイプ

	static CParticleParam *GetDefaultParam(CParticleParam::PARTICLE_TEXT type) { return m_pParticleDefaultParamList[type].get(); };
	static bool ShowParamConboBox(CParticleParam::PARTICLE_TEXT & rType);

	//オペレータ
	void *operator = (const CParticleParam *pParam);

private:
	static std::vector<std::unique_ptr<CParticleParam>> m_pParticleDefaultParamList;	//パーティクルの初期パラメータのリスト
	static FILENAME_LIST m_aFileNameList;												//読み込むファイルのリスト

	bool m_bSpeedRandom;							//速度がランダムかどうか
	bool m_bGravity;								//重力をかけるか
	bool m_bAlphaBlend;								//加算合成するか
	int m_nLife;									//ライフ
	int m_nNumber;									//個数
	float m_fSpeed;									//速度
	float m_fRange;									//範囲
	float m_fAlphaDamping;							//アルファ値の減衰値
	float m_fGravityPower;							//重力の大きさ
	bool m_bAnimation;								//アニメーションするか
	bool m_bAnimationLoop;							//アニメーションがループするか
	int m_nAnimationCntSwitch;						//アニメーションが切り替わるカウント
	D3DXVECTOR3 m_Size;								//サイズ
	D3DXVECTOR3 m_SizeDamping;						//サイズの減衰値
	D3DXCOLOR m_col;								//色
	D3DXVECTOR3 m_rot;								//角度

	PARTICLE_SHAPE m_shape;							//パーティクルの出方
	CTexture::TEX_TYPE m_Textype;					//テクスチャ
	CTexture::SEPARATE_TEX_TYPE m_SeparateTex;		//分割テクスチャ
	PARTICLE_TEXT m_ParticleType;					//パーティクルのタイプ

};


class CreaterParam
{
public:
	//コンストラクタ
	CreaterParam()
	{
		m_bLoop = false;
		m_nLoopNum = 0;
		m_nLoopInterval = 0;
		m_text = CParticleParam::PARTICLE_TEXT::PARTICLE_DEFAULT;
	}
	~CreaterParam() {};

private:
	bool m_bLoop;								//ループしたかどうか
	int m_nLoopNum;								//ループの回数
	int m_nLoopInterval;						//ループのインターバル
	CParticleParam::PARTICLE_TEXT m_text;		//読み込むテキスト
};

class CreatorWave
{
public:
	//コンストラクタ
	CreatorWave() { m_ParamList.clear(); };
	~CreatorWave() { m_ParamList.clear(); };
private:
	std::vector<std::unique_ptr<CreaterParam>> m_ParamList;
};


//パーティクルの生成口
class CParticleCreators
{
public:
	CParticleCreators() {};				//コンストラクタ
	~CParticleCreators() {};				//デストラクタ

	static void LoadParticleCreators();			//パーティクル生成口のロード
	static CParticleCreators *Create();
private:
	int m_nCntTime;		//時間計測
	int m_nCntLoop;		//ループした回数計測

	static std::vector<std::unique_ptr<CreatorWave>> m_pCreatorParamList;
	static FILENAME_LIST m_aFileNameList;
};
#endif
