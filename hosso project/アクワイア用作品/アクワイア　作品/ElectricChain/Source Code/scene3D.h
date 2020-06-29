//------------------------------------------------------------------------------
//
//シーン3D処理  [scene3D.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _SCENE3D_H_
#define _SCENE3D_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CScene3D : public CScene
{
public:

	CScene3D();
	virtual ~CScene3D();

	virtual HRESULT Init();								//初期化
	virtual void Uninit();								//終了
	virtual void Update();								//更新
	virtual void Draw();								//描画
	virtual void ShowDebugInfo();						//デバッグ情報表記

	void DrawSettingMtx(D3DXMATRIX const &Mtx);				//渡す側で計算したワールドマトリックスを元に描画
	void DrawPolygon();

	void SetPos(D3DXVECTOR3 pos);								//座標設定
	void SetSize(D3DXVECTOR3 size);								//サイズ設定
	void SetRot(D3DXVECTOR3 rot);								//回転設定
	void SetVtxCol(D3DXCOLOR col);								//頂点カラー設定
	void SetAnimation(D3DXVECTOR2 UV, D3DXVECTOR2 size);		//テクスチャUV座標設定
	void SetNormal();											//法線設定

	void SetBboard(bool bBboard)	{m_bBboard = bBboard;};		//ビルボード化
	void SetDisp(bool bDisp)		{m_bDisp = bDisp;};			//表示非表示設定

	void UpdateGauge(float fMag);								//ゲージ用の更新処理

	D3DXVECTOR3 &GetPos()			{ return m_pos; };			//座標取得処理
	D3DXVECTOR3 &GetSize()			{ return m_size; };			//サイズ取得処理
	D3DXVECTOR3 &GetRot()			{ return m_rot; };			//回転量取得処理

	D3DXCOLOR &GetCol()				{ return m_col; };			//色情報取得処理
	bool GetDisp()					{ return m_bDisp; };		//画面に映ってるか取得
	D3DXMATRIX *GetMtxPtr()			{ return &m_mtxWorld; };	//ワールドマトリックス取得 ポインタ

	static std::shared_ptr<CScene3D> Create_Shared(D3DXVECTOR3 pos, D3DXVECTOR3 size, OBJTYPE objtype);	//生成処理（共有管理
	static void Create_SceneManagement(D3DXVECTOR3 pos, D3DXVECTOR3 size, OBJTYPE objtype);				//生成処理（CSceneのみで管理
	static std::unique_ptr<CScene3D> Create_SelfManagement(D3DXVECTOR3 pos, D3DXVECTOR3 size);			//生成処理（Return先で管理

	void BindTexture(LPDIRECT3DTEXTURE9 pTex) { m_pTexture = pTex; };									//テクスチャ設定
	static int GetNumScene3D() { return m_nNumScene3D; };												//3Dポリゴン総数取得

private:
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;					//頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9		m_pTexture;					//テクスチャへのポインタ
	static int m_nNumScene3D;

	D3DXVECTOR3 m_pos;									//座標
	D3DXVECTOR3 m_size;									//大きさ
	D3DXVECTOR3 m_rot;									//回転
	D3DXCOLOR m_col;									//色
	bool m_bBboard;										//ビルボードかどうか
	bool m_bDisp;										//画面に写すかどうか

	D3DXMATRIX		m_mtxWorld;							//ワールドマトリックス
	VERTEX_3D		m_Vtx3D[4];							//頂点情報　debug用
};
#endif