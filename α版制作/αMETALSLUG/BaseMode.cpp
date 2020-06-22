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
#include "bullet.h"
//==========================================================
//デバッグコマンド
//==========================================================
void CBaseMode::DebugCommand(void)
{
#ifdef _DEBUG
	//キーボード取得
	CKeyboard *key = CManager::GetInputKeyboard();

	//使い方説明
	CDebugProc::Print("---------Debug Command----------\n");
	CDebugProc::Print("[Ctrl] + テンキー [0] : 現在のModeに遷移\n");
	CDebugProc::Print("[Ctrl] + テンキー [1] : Titleに遷移\n");
	CDebugProc::Print("[Ctrl] + テンキー [2] : Gameに遷移\n");
	CDebugProc::Print("[Ctrl] + テンキー [3] : Resultに遷移\n");
	CDebugProc::Print("[Ctrl] + テンキー [9] : MotionViewerに遷移\n");

	//Ctrl押しながら
	if (key->GetKeyboardPress(DIK_LCONTROL))
	{
		//現在のモード再始動
		if (key->GetKeyboardTrigger(DIK_NUMPAD0))
		{
			CManager::GetRendere()->GetFade()->SetFade(CManager::GetGameState());
		}
		//タイトル
		if (key->GetKeyboardTrigger(DIK_NUMPAD1))
		{
			//CManager::GetRendere()->GetFade()->SetFade(CManager::MODE_TITLE);
		}
		//ゲーム
		if (key->GetKeyboardTrigger(DIK_NUMPAD2))
		{
			CManager::GetRendere()->GetFade()->SetFade(CManager::MODE_GAME);
		}
		//リザルト
		if (key->GetKeyboardTrigger(DIK_NUMPAD3))
		{
			//CManager::GetRendere()->GetFade()->SetFade(CManager::MODE_RESULT);
		}
		//モーションビューワ
		if (key->GetKeyboardTrigger(DIK_NUMPAD9))
		{
			CManager::GetRendere()->GetFade()->SetFade(CManager::MODE_DEBUG_MODELVIEWER);
		}
	}

	//デバッグ情報表記
	//オーバーライド用　それぞれのモードで処理
	ShowDebugInfo();

#endif //_DEBUG
}
//==========================================================
//使うテクスチャやモデルの読み込み
//==========================================================
void CBaseMode::BaseLoad(HWND hWnd)
{
	//テクスチャロード
	CTexture::TexLoad(hWnd);
	//モデルロード
	CModel::LoadModel();
	//モーションロード
	CCharacter::LoadMotion();
	//弾のパラメーターロード
	CBullet::BulletLoad();
}
//==========================================================
//生成したものを全て破棄
//==========================================================
void CBaseMode::BaseUnload(void)
{
	CModel::UnLoad();
	CTexture::TexUnload();
}
