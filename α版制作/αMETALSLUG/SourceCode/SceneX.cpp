//==========================================================
// SceneX処理：NORI
//==========================================================
//==========================================================
// インクルードファイル
//==========================================================
#include "SceneX.h"
#include "inputKeyboard.h"
//==========================================================
// コンストラクタ
//==========================================================
CSceneX::CSceneX(OBJ_TYPE type) :CScene(type)
{
}
//==========================================================
// デストラクタ
//==========================================================

CSceneX::~CSceneX()
{
}
//==========================================================
// 初期化
//==========================================================
HRESULT CSceneX::Init(void)
{

	return S_OK;
}
//==========================================================
// 終了
//==========================================================
void CSceneX::Uninit(void)
{
}
//==========================================================
// 更新
//==========================================================
void CSceneX::Update(void)
{
}
//==========================================================
// 描画
//==========================================================
void CSceneX::Draw(void)
{
}
//==========================================================
// デバッグ
//==========================================================
void CSceneX::DebugInfo(void)
{
}
//==========================================================
// クリエイト
//==========================================================
CSceneX *CSceneX::Create(void)
{
	CSceneX*pSceneX;
	pSceneX = new CSceneX();
	pSceneX->Init();
	return pSceneX;
}