//------------------------------------------------------------------------------
//
//メッシュボックス処理  [meshbox.h]
//Author:fujiwaramasato
//
//------------------------------------------------------------------------------
#ifndef _MESHBOX_H_
#define _MESHBOX_H_
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
class CMeshBox : public CScene
{
public:

	//メッシュの種類
	enum COLLISION_TYPE
	{
		TYPE_CENTER, // 座標が中心
		TYPE_GROUND	 // 地面が中心
	};

	CMeshBox();
	CMeshBox(OBJ_TYPE obj) : CScene(obj) {};
	~CMeshBox();

	HRESULT Init();																//初期化
	void Uninit();																//終了
	void Update();																//更新
	void Draw();																//描画
	void DebugInfo();															//デバッグ情報表記

	void MakeVertex();															//頂点生成
	void SetTexPos();															//テクスチャUV座標設定

	void SetPos(D3DXVECTOR3 const& pos);										//座標設定
	void SetCol(D3DXCOLOR const& col);											//色設定
	void SetSize(D3DXVECTOR3 size);												//サイズ設定

	D3DXVECTOR3 &GetPos() { return m_pos; };									//座標取得処理
	D3DXVECTOR3 &GetRot() { return m_rot; };									//回転量取得
	D3DXCOLOR	&GetCol() { return m_col; };									//色取得
	D3DXMATRIX	*GetMtx() { return &m_mtxWorld; };								//ワールドマトリックス取得
	D3DXVECTOR3 GetSize() { return m_size; };									//サイズ取得

	static CMeshBox *Create(D3DXVECTOR3 const &pos, D3DXVECTOR3 const &onesize ,
		COLLISION_TYPE  const &type);	//生成処理

protected:

private:
	D3DXMATRIX				m_mtxWorld;			// ワールドマトリックス
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;			// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuff;			// インデックスバッファへのポインタ
	D3DXVECTOR3				m_pos;				// 座標
	D3DXVECTOR3				m_size;				// サイズ
	D3DXVECTOR3				m_rot;				// 回転
	D3DXCOLOR				m_col;				// 色
	COLLISION_TYPE			m_Type;
};
#endif