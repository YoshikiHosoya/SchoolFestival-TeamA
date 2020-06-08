//==========================================================
// ベースモードクラス [basemode.cpp]
//==========================================================
#include "basemode.h"
#include "character.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "inputKeyboard.h"
#include "model.h"
//==========================================================
//デバッグコマンド
//==========================================================
void CBaseMode::DebugCommand(void)
{
	//キーボード取得
	CKeyboard *key = CManager::GetInputKeyboard();

	//現在のモード再始動
	if (key->GetKeyboardTrigger(DIK_NUMPAD0))
	{
		CManager::GetRendere()->GetFade()->SetFade(CManager::GetGameState());
	}
	//タイトル
	if (key->GetKeyboardTrigger(DIK_NUMPAD1))
	{
		CManager::GetRendere()->GetFade()->SetFade(CManager::MODE_TITLE);
	}
}
//==========================================================
//使うテクスチャやモデルの読み込み
//==========================================================
void CBaseMode::BaseLoad(HWND hWnd)
{
	//テクスチャロード
	CTexture::TexLoad(hWnd);
	CModel::LoadModel();
	CCharacter::LoadMotion();
}
//==========================================================
//生成したものを全て破棄
//==========================================================
void CBaseMode::BaseUnload(void)
{
	CModel::UnLoad();
	CTexture::TexUnload();
}
