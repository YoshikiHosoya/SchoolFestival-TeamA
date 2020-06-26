//------------------------------------------------------------------------------
//
//シーン2D処理  [scene2D.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _SCENE2D_H_
#define _SCENE2D_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CScene2D : public CScene
{
public:
	CScene2D();
	virtual ~CScene2D();

	virtual HRESULT Init();					//初期化
	virtual void Uninit();					//終了
	virtual void Update();					//更新
	virtual void Draw();					//描画
	virtual void ShowDebugInfo();			//デバッグ情報表記

	void UpdateGauge(float fMag);			//ゲージ用

	//Set関数
	void SetPos(D3DXVECTOR3 pos);							//座標設定
	void SetSize(D3DXVECTOR3 size);							//サイズ設定
	void SetVtxCol(D3DXCOLOR col);							//頂点カラー設定
	void SetAngle(float fAngle);							//回転の角度設定
	void SetAnimation(D3DXVECTOR2 UV,D3DXVECTOR2 size);		//テクスチャUV座標設定
	void SetDisp(bool bDisp) { m_bDisp = bDisp; };

	//Get関数
	D3DXVECTOR3 &GetPos()	{ return m_pos; };				//座標取得処理
	D3DXVECTOR3 &GetSize()	{ return m_size; };				//サイズ取得処理
	D3DXCOLOR &GetCol()		{ return m_col; };				//色情報取得
	float &GetAngle()		{ return m_fAngle; };			//角度情報取得
	bool &GetDisp()			{ return m_bDisp; };			//描画するかどうかの判定取得

	static std::shared_ptr<CScene2D> Create_Shared			(D3DXVECTOR3 pos, D3DXVECTOR3 size, OBJTYPE objtype);	//生成処理（共有管理
	static void Create_SceneManagement						(D3DXVECTOR3 pos, D3DXVECTOR3 size, OBJTYPE objtype);	//生成処理（CSceneのみで管理
	static std::unique_ptr<CScene2D> Create_SelfManagement	(D3DXVECTOR3 pos, D3DXVECTOR3 size);					//生成処理（Return先で管理


	void BindTexture(LPDIRECT3DTEXTURE9 pTex)	{ m_pTexture = pTex; };						//テクスチャ情報設定
	static int GetNumScene2D()					{ return m_nNumScene2D; };					//2Dの総数取得

	bool Collision(D3DXVECTOR3 const &pos);
private:
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = NULL;	//頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;	//テクスチャへのポインタ
	static int m_nNumScene2D;			//総数

	D3DXVECTOR3 m_pos;					//座標
	D3DXVECTOR3 m_size;					//大きさ
	D3DXVECTOR3 m_rot;					//回転
	D3DXCOLOR m_col;					//色
	D3DXCOLOR m_colalpha;				//半透明化処理の時に使う
	float m_fLength;					//長さ
	float m_fAngle;						//角度
	bool m_bDisp;						//描画するかどうか
};

#endif