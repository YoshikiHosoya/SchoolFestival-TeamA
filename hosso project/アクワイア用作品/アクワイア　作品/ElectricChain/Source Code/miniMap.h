//------------------------------------------------------------------------------
//
//ミニマップ処理  [minimap.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MINIMAP_H_
#define _MINIMAP_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CScene2D;
class CEnemy;

class CMiniMap : public::CScene
{
public:
	enum TEX_TYPE
	{
		TEX_MAP = 0,			//マップ
		TEX_PLAYER,				//プレイヤー
		TEX_EXPLOSION,			//爆発
		TEX_ENEMY,				//敵
		TEX_MAX
	};


	CMiniMap();
	~CMiniMap();

	HRESULT Init();									//初期化
	void Uninit();									//終了
	void Update();									//更新
	void Draw();									//描画
	void ShowDebugInfo();							//デバッグ情報表記

	static void Create();							//生成処理
protected:

private:
	std::vector<std::shared_ptr<CScene2D>> m_pEnemyMappingList;			//敵のマップ上のポリゴン
	std::vector<std::shared_ptr<CScene2D>> m_pExplosionMappingList;		//爆発のマップ上のポリゴン
	std::shared_ptr<CScene2D> m_pPlayerMapping;							//プレイヤーのマップ上のポリゴン
};
#endif