//------------------------------------------------------------------------------
//
//パーティクルの管理処理  [ParticleManager.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _PARTICLE_MANAGER_H_
#define _PARTICLE_MANAGER_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"
#include "Particle.h"

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define MAX_PARTICLE (100000)
//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
//class CParticleCreateManager
//{
//public:
//	CParticleCreateManager();
//	~CParticleCreateManager();
//
//	static std::unique_ptr<CParticleCreateManager> Create();
//
//private:
//	int m_nCnt;

//	bool m_bLoop;
//	int m_nLoopNum;
//	int m_nLoopInterval;
//	int m_n
//
//};


//パーティクルのまとまり
class CParticleManager : public CScene
{
public:
	CParticleManager();									//コンストラクタ
	CParticleManager(OBJ_TYPE obj);						//コンストラクタ
	~CParticleManager();								//デストラクタ

	HRESULT Init();									//初期化
	void Uninit();									//終了
	void Update();									//更新
	void Draw();									//描画
	void DebugInfo();							//デバッグ情報表記

	static void Create();
	static void AddParticleList(std::unique_ptr<CParticle> pParticle);

private:
	static std::vector<std::unique_ptr<CParticle>> m_pParticleList;		//パーティクルの構造体のリスト
	int m_nCnt;															//カウント

};

#endif