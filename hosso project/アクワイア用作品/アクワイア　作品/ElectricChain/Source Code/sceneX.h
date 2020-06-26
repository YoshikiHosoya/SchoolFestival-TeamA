//------------------------------------------------------------------------------
//
//Xファイルモデル処理  [SceneX.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MODEL_H_
#define _MODEL_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CSceneX : public CScene
{
public:
	//マテリアルカラー
	enum MATERIAL_COL
	{
		MAT_NORMAL = -1,
		MAT_ENEMY_BLACK,
		MAT_ENEMY_GREEN,
		MAT_MAX
	};

	CSceneX();
	virtual ~CSceneX();

	virtual HRESULT Init();						//初期化
	virtual void Uninit();						//終了
	virtual void Update();						//更新
	virtual void Draw();						//描画
	void DrawMesh();							//モデルのメッシュ描画
	void DrawShadow();							//影の描画
	virtual void ShowDebugInfo();				//デバッグ情報表記


	void SetPos(D3DXVECTOR3 pos)							{ m_pos = pos; };					//座標設定
	void SetRot(D3DXVECTOR3 rot)							{ m_rot = rot; };					//回転設定
	void SetMaterialCol(MATERIAL_COL matcol)				{ m_MatCol = matcol; };				//マテリアルカラー設定

	D3DXVECTOR3 &GetPos()									{ return m_pos; };					//座標取得処理
	D3DXVECTOR3 &GetRot()									{ return m_rot; };					//回転取得処理
	D3DXMATRIX *GetMtx()									{ return &m_mtxWorld; };			//マトリックス取得
	MATERIAL_COL GetMaterialCol()							{ return m_MatCol; };				//マテリアルカラー取得

	static CSceneX *Create(D3DXVECTOR3 pos,OBJTYPE objtype);		//生成処理
	static int GetNumSceneX() { return m_nNumSceneX; };				//数取得
	void BindModelInfo(std::shared_ptr<CModelInfo> pSceneXInfo) { m_SceneXInfo = pSceneXInfo; };	//モデルセット

private:
	static int m_nNumSceneX;									//総数カウント
	static std::vector<D3DMATERIAL9> m_MaterialColor[MAT_MAX];	//マテリアルの色

	D3DXVECTOR3 m_pos;											//座標
	D3DXVECTOR3 m_rot;											//回転
	D3DXMATRIX	m_mtxWorld;										//ワールドマトリックス
	MATERIAL_COL m_MatCol;										//マテリアルカラー
	std::shared_ptr<CModelInfo>	m_SceneXInfo;					//モデル情報
};
#endif