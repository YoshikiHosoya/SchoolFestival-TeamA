//------------------------------------------------------------------------------
//
//スフィア形の爆発処理  [sphere_explosion.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _SPHERE_EXPLOSION_H_
#define _SPHERE_EXPLOSION_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "meshsphere.h"

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CCollision;

class CSphere_Explosion : public CMeshSphere
{
public:
	CSphere_Explosion();		//コンストラクタ
	~CSphere_Explosion();		//デストラクタ

	HRESULT Init();				//初期化
	void Uninit();				//終了
	void Update();				//更新
	void Draw();				//描画
	void ShowDebugInfo();		//デバッグ情報表記

	static std::shared_ptr<CSphere_Explosion> Create(D3DXVECTOR3 const pos, float const fRadius,int const nLife);	//生成処理

protected:

private:
	int m_nLife;								//ライフ
	std::unique_ptr<CCollision>	m_pCollision;	//当たり判定
	void CollisionExplosion();					//爆発の判定処理

};
#endif