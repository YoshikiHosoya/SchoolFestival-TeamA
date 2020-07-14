//------------------------------------------------------------------------------
//
//当たり判定付きテクスチャアニメーション3D処理  [TexAnimation3D_Collision.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _EFFECTANIMATION3D_COLLISION_H_
#define _EFFECTANIMATION3D_COLLISION_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "TexAnimation3D.h"
//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CCollision;

class CTexAnimation3D_Collision : public CTexAnimation3D
{
public:

	CTexAnimation3D_Collision();					//コンストラクタ
	CTexAnimation3D_Collision(OBJ_TYPE obj);		//コンストラクタ
	~CTexAnimation3D_Collision();					//デストラクタ

	HRESULT Init();				//初期化
	void Uninit();				//終了
	void Update();				//更新
	void Draw();				//描画
	void ShowDebugInfo();		//デバッグ情報表示
	static void Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,D3DXVECTOR3 rot, CTexture::SEPARATE_TEX_TYPE type, int nCntSwitch, CScene::OBJ_TYPE objtype,bool bPlayer);	//生成処理

private:
	CCollision *m_pCollision;	//コリジョンのポインタ
	bool m_bPlayer;
	D3DXVECTOR3 m_CollisionPosOrigin = ZeroVector3;			//当たり判定用の座標

	bool Collision();
};

#endif