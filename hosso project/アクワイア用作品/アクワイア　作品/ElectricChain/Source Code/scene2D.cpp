//------------------------------------------------------------------------------
//
//シーン2D処理  [scene2D.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "keyboard.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------
int CScene2D::m_nNumScene2D = 0;

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CScene2D::CScene2D()
{
	//初期化
	m_pos = ZeroVector3;
	m_size = ZeroVector3;
	m_rot = ZeroVector3;
	m_col = WhiteColor;
	m_colalpha = WhiteColor;
	m_fAngle = 0.0f;
	m_fLength = 0.0f;
	m_bDisp = true;

	//総数加算
	m_nNumScene2D++;
}

//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CScene2D::~CScene2D()
{
	//頂点バッファの開放
	if (m_pVtxBuff)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//総数減算
	m_nNumScene2D--;
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CScene2D::Init()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			//頂点フォーマット
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点の座標
	pVtx[0].pos = m_pos + D3DXVECTOR3(-m_size.x * 0.5f, -m_size.y * 0.5f, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_size.x * 0.5f, -m_size.y * 0.5f, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-m_size.x * 0.5f, m_size.y * 0.5f, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_size.x * 0.5f, m_size.y * 0.5f, 0.0f);

	//頂点の同次座標
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点の色
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点データをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CScene2D::Uninit()
{

}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CScene2D::Update()
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点の座標
	pVtx[0].pos.x = m_pos.x + sinf(-D3DX_PI + m_fAngle + m_rot.z)	* m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(-D3DX_PI + m_fAngle + m_rot.z)	* m_fLength;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = m_pos.x + sinf(D3DX_PI - m_fAngle + m_rot.z)	* m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(D3DX_PI - m_fAngle + m_rot.z)	* m_fLength;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = m_pos.x + sinf(-m_fAngle + m_rot.z)	* m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(-m_fAngle + m_rot.z)	* m_fLength;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = m_pos.x + sinf(m_fAngle + m_rot.z)	* m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_fAngle + m_rot.z)	* m_fLength;
	pVtx[3].pos.z = 0.0f;

	//頂点データをアンロック
	m_pVtxBuff->Unlock();
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CScene2D::Draw()
{
	//写すかどうか
	if (m_bDisp)
	{
		//デバイス取得
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		//頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, m_pTexture);

		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
								0,					//開始するインデックス(頂点)
								2);					//ポリゴンの枚数
	}
}
//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CScene2D::ShowDebugInfo()
{
#ifdef _DEBUG
	//2D情報
	if (ImGui::TreeNode("Scene2DInfo"))
	{
		//座標
		if (ImGui::TreeNode("pos"))
		{
			if (ImGui::InputFloat3("pos", m_pos))
			{
				//座標設定
				SetPos(m_pos);
			}
			ImGui::TreePop();
		}
		//サイズ
		if (ImGui::TreeNode("size"))
		{
			if (ImGui::InputFloat3("size", m_size))
			{
				//座標設定
				SetSize(m_size);
			}
			ImGui::TreePop();
		}
		//色
		if (ImGui::TreeNode("col"))
		{
			if (ImGui::ColorEdit4("col", m_col))
			{
				//色設定
				SetVtxCol(m_col);
			}
			//tree終了
			ImGui::TreePop();
		}
		//tree終了
		ImGui::TreePop();
	}
#endif //DEBUG
}
//------------------------------------------------------------------------------
//設定処理
//------------------------------------------------------------------------------
void CScene2D::SetPos(D3DXVECTOR3 pos)
{
	//座標
	m_pos = pos;
}

//------------------------------------------------------------------------------
//サイズの設定
//------------------------------------------------------------------------------
void CScene2D::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
	m_fAngle = atan2f(m_size.x, m_size.y);
	m_fLength = (float)sqrt(m_size.x * m_size.x + m_size.y * m_size.y) / 2;
}
//------------------------------------------------------------------------------
//色の設定
//------------------------------------------------------------------------------
void CScene2D::SetVtxCol(D3DXCOLOR col)
{
	//色設定
	m_col = col;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//頂点データをアンロック
	m_pVtxBuff->Unlock();
}

//------------------------------------------------------------------------------
//角度の設定
//------------------------------------------------------------------------------
void CScene2D::SetAngle(float fAngle)
{
	m_rot.z = fAngle;
}

//------------------------------------------------------------------------------
//テクスチャアニメーションの更新
//------------------------------------------------------------------------------
void CScene2D::SetAnimation(D3DXVECTOR2 UV, D3DXVECTOR2 size)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(UV.x, UV.y);
	pVtx[1].tex = D3DXVECTOR2(UV.x + size.x, UV.y);
	pVtx[2].tex = D3DXVECTOR2(UV.x, UV.y + size.y);
	pVtx[3].tex = D3DXVECTOR2(UV.x + size.x, UV.y + size.y);

	//頂点データをアンロック
	m_pVtxBuff->Unlock();
}

//------------------------------------------------------------------------------
//生成処理　共有管理用
//------------------------------------------------------------------------------
std::shared_ptr<CScene2D> CScene2D::Create_Shared(D3DXVECTOR3 pos, D3DXVECTOR3 size, OBJTYPE objtype)
{
	//メモリ確保
	std::shared_ptr<CScene2D> pScene2D = std::make_shared<CScene2D>();

	//初期化
	pScene2D->Init();

	//座標とサイズ設定
	pScene2D->SetPos(pos);
	pScene2D->SetSize(size);

	//Sceneで管理
	pScene2D->SetObjType(objtype);
	pScene2D->AddSharedList(pScene2D);

	//return
	return pScene2D;
}
//------------------------------------------------------------------------------
//生成処理　Csceneで管理用
//------------------------------------------------------------------------------
void CScene2D::Create_SceneManagement(D3DXVECTOR3 pos, D3DXVECTOR3 size, OBJTYPE objtype)
{
	//メモリ確保
	std::unique_ptr<CScene2D> pScene2D(new CScene2D);

	//初期化
	pScene2D->Init();

	//座標とサイズ設定
	pScene2D->SetPos(pos);
	pScene2D->SetSize(size);

	//Sceneで管理
	pScene2D->SetObjType(objtype);
	pScene2D->AddUniqueList(std::move(pScene2D));
}
//------------------------------------------------------------------------------
//生成処理　Return先で管理用
//------------------------------------------------------------------------------
std::unique_ptr<CScene2D> CScene2D::Create_SelfManagement(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	std::unique_ptr<CScene2D> pScene2D(new CScene2D);

	//初期化
	pScene2D->Init();

	//座標とサイズ設定
	pScene2D->SetPos(pos);
	pScene2D->SetSize(size);

	//return
	return std::move(pScene2D);
}

//------------------------------------------------------------------------------
//ゲージ用の更新処理
//------------------------------------------------------------------------------
void CScene2D::UpdateGauge(float fMag)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点の座標
	pVtx[0].pos = m_pos + D3DXVECTOR3(-m_size.x * 0.5f, -m_size.y * 0.5f, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_size.x * 0.5f - fMag * m_size.x, -m_size.y * 0.5f, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-m_size.x * 0.5f, m_size.y * 0.5f, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_size.x * 0.5f - fMag * m_size.x, m_size.y * 0.5f, 0.0f);

	//頂点データをアンロック
	m_pVtxBuff->Unlock();
}


//------------------------------------------------------------------------------
//ポリゴン内かどうか
//------------------------------------------------------------------------------
bool CScene2D::Collision(D3DXVECTOR3 const & pos)
{
	//範囲内かチェック
	if (pos.x <= m_pos.x + m_size.x * 0.5f &&
		pos.x >= m_pos.x - m_size.x * 0.5f &&
		pos.y <= m_pos.y + m_size.y * 0.5f &&
		pos.y >= m_pos.y - m_size.y * 0.5f)
	{
		//true
		return true;
	}
	//false
	return false;
}