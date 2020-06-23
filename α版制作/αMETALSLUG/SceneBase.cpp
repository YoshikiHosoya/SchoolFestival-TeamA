//==========================================================
// SceneBase処理：NORI
//==========================================================
//==========================================================
// インクルードファイル
//==========================================================
#include "main.h"
#include "SceneBase.h"
#include "renderer.h"
#include "manager.h"
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"
//==========================================================
// コンストラクタ
//==========================================================
CSceneBase::CSceneBase()
{
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_size = D3DXVECTOR3(0, 0, 0);
	m_col = D3DXCOLOR(1, 1, 1, 1);
}
//==========================================================
// コンストラクタ
//==========================================================
CSceneBase::CSceneBase(OBJ_TYPE type) : CScene(type)
{
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_size = D3DXVECTOR3(0, 0, 0);
	m_col = D3DXCOLOR(1, 1, 1, 1);
}
//==========================================================
// デストラクタ
//==========================================================
CSceneBase::~CSceneBase()
{
}
//============= =============================================
// 初期化
//==========================================================
HRESULT CSceneBase::Init(void)
{
	return S_OK;
}
//==========================================================
// 終了
//==========================================================
void CSceneBase::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}
//==========================================================
// 色の設定
//==========================================================
void CSceneBase::SetColor(D3DXCOLOR col)
{
	m_col = col;
}
//==========================================================
// 回転の設定
//==========================================================
void CSceneBase::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//==========================================================
// 大きさの設定
//==========================================================
void CSceneBase::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}
//==========================================================
// マトリックス情報の計算
//==========================================================
void CSceneBase::MtxCalc(void)
{
	D3DXMATRIX mtxRot, mtxTrans;
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y,
		m_rot.x,
		m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxTrans);
}
//==========================================================
// 位置の設定
//==========================================================
void CSceneBase::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//==========================================================
// テクスチャの設定
//==========================================================
void CSceneBase::BindTexture(LPDIRECT3DTEXTURE9 tex)
{
	m_pTexture = tex;
}
//==========================================================
// 頂点バッファの設定
//==========================================================
void CSceneBase::BindVtxBuff(LPDIRECT3DVERTEXBUFFER9 pVtxBuff)
{
	m_pVtxBuff = pVtxBuff;
}
//==========================================================
// ワールドマトリックスの設定
//==========================================================
void CSceneBase::SetMtxWorld(D3DXMATRIX mtxWorld)
{
	m_mtxWorld = mtxWorld;
}
//==========================================================
// ポジションの取得
//==========================================================
D3DXVECTOR3 &CSceneBase::GetPosition(void)
{
	return m_pos;
}
//==========================================================
// 色の取得
//==========================================================
D3DXCOLOR &CSceneBase::GetColor(void)
{
	return m_col;
}
//==========================================================
// 回転の取得
//==========================================================
D3DXVECTOR3 &CSceneBase::GetRot(void)
{
	return m_rot;
}
//==========================================================
// テクスチャの取得
//==========================================================
LPDIRECT3DTEXTURE9 CSceneBase::GetTexture(void)
{
	return m_pTexture;
}
//==========================================================
// 頂点バッファの取得
//==========================================================
LPDIRECT3DVERTEXBUFFER9 CSceneBase::GetVtxBuff(void)
{
	return m_pVtxBuff;
}
//==========================================================
// ワールドマトリックスの取得
//==========================================================
D3DXMATRIX *CSceneBase::GetMtxWorld(void)
{
	return &m_mtxWorld;
}
//==========================================================
// 大きさの取得
//==========================================================
D3DXVECTOR3 &CSceneBase::GetSize(void)
{
	return m_size;
}
