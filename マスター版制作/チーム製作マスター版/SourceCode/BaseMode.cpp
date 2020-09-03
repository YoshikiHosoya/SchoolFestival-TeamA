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
#include "Obstacle.h"
#include "particle.h"
#include "item.h"
#include "prisoner.h"
#include "sound.h"
#include "scoremanager.h"
#include "player.h"
#include "boss_one.h"
#include "grenade.h"
#include "map.h"

//==========================================================
//デバッグコマンド
//==========================================================
void CBaseMode::DebugCommand(void)
{
#ifdef _DEBUG
	//キーボード取得
	CKeyboard *key = CManager::GetInputKeyboard();

	//使い方説明
	CDebugProc::Print_Right("---------Debug Command----------\n");
	CDebugProc::Print_Right("[F3] : 一時停止\n");
	CDebugProc::Print_Right("[F4] : 一時停止中に1Fだけ更新\n");
	CDebugProc::Print_Right("[F5] : デバッグ表記 on/off\n");
	CDebugProc::Print_Right("[F6] : ミュート on/off\n");

	CDebugProc::Print_Right("[Ctrl] + テンキー [0] : 現在のModeに遷移\n");
	CDebugProc::Print_Right("[Ctrl] + テンキー [1] : Titleに遷移\n");
	CDebugProc::Print_Right("[Ctrl] + テンキー [2] : Gameに遷移\n");
	CDebugProc::Print_Right("[Ctrl] + テンキー [4] : Rankingに遷移\n");
	CDebugProc::Print_Right("[Ctrl] + テンキー [7] : MapEditorに遷移\n");
	CDebugProc::Print_Right("[Ctrl] + テンキー [8] : EffectViewerに遷移\n");
	CDebugProc::Print_Right("[Ctrl] + テンキー [9] : MotionViewerに遷移\n");


	//一時停止
	if (key->GetKeyboardTrigger(DIK_F3))
	{
		CScene::StopUpdate();
	}

	//1Fだけ更新
	if (key->GetKeyboardTrigger(DIK_F4))
	{
		CScene::Set1FUpdate();
	}

	//デバッグ表記on/off
	if (key->GetKeyboardTrigger(DIK_F5))
	{
		CManager::GetRenderer()->SetShowDebug();
	}

	//ミュート表記on/off
	if (key->GetKeyboardTrigger(DIK_F6))
	{
		CManager::GetSound()->SetMute(CManager::GetSound()->GetMute() ^ 1);
	}

	//Ctrl押しながら
	if (key->GetKeyboardPress(DIK_LCONTROL))
	{
		//現在のモード再始動
		if (key->GetKeyboardTrigger(DIK_NUMPAD0))
		{
			CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MODE, CManager::GetMode());
		}
		//タイトル
		if (key->GetKeyboardTrigger(DIK_NUMPAD1))
		{
			CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MODE, CManager::MODE_TITLE);
		}
		//ゲーム
		if (key->GetKeyboardTrigger(DIK_NUMPAD2))
		{
			CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MODE, CManager::MODE_GAME);
		}
		//リザルト
		if (key->GetKeyboardTrigger(DIK_NUMPAD4))
		{
			CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MODE, CManager::MODE_RANKING);
		}
		//マップエディター
		if (key->GetKeyboardTrigger(DIK_NUMPAD7))
		{
			CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MODE, CManager::MODE_DEBUG_MAPEDITOR);
		}
		//エフェクトビューワ
		if (key->GetKeyboardTrigger(DIK_NUMPAD8))
		{
			CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MODE, CManager::MODE_DEBUG_EFFECTVIEWER);
		}
		//モーションビューワ
		if (key->GetKeyboardTrigger(DIK_NUMPAD9))
		{
			CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MODE, CManager::MODE_DEBUG_MODELVIEWER);
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
	//グレネードのパラメーターロード
	CGrenade::GrenadePramLoad();
	//障害物のパラメーターロード
	CObstacle::ObstacleLoad();
	//パーティクルのパラメータロード
	CParticleParam::LoadParticleDefaultParam();
	// アイテムのデータのロード
	CItem::ItemLoad();
	// 捕虜のデータの読み込み
	CPrisoner::PrisonerLoad();
	// スコアのデータの読み込み
	CScoreManager::ScoreLoad();
	// プレイヤーのデータの読み込み
	CPlayer::PlayerLoad();
	// ボス1のデータの読み込み ドラゴンノスケ
	CBoss_One::Boss_One_DataLoad();
	// ウェーブ情報読み込み
	CMap::WaveLoad();
}
//==========================================================
//生成したものを全て破棄
//==========================================================
void CBaseMode::BaseUnload(void)
{
	CModel::UnLoad();
	CTexture::TexUnload();
	CCharacter::CharacterUnLoad();
	CMap::WaveUnLoad();

}