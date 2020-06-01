// ----------------------------------------
//
// シーン処理の説明[scene_load.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
#include "scene_load.h"

/* 描画 */
#include "tlybg.h"
#include "title_ui.h"
#include "pause.h"
#include "floor.h"
#include "player.h"
#include "item.h"
#include "3Deffect.h"
#include "3Dparticle.h"
#include "meshdome.h"
#include "collision.h"
#include "gauge.h"
#include "meshsphere.h"
#include "wall.h"
#include "enemy.h"
#include "3ditem.h"
#include "3dline.h"
#include "object.h"
#include "TitleObject.h"
#include "lighteffect.h"
#include "gate.h"
#include "explosion.h"
#include "titleEnemy.h"
#include "telop.h"
#include "TelopComment.h"
#include "bulletinboard.h"
#include "2DAnimationUI.h"
#include "key.h"
#include "floartile.h"
#include "3DTexture.h"
#include "ceiling.h"
#include "mapmark.h"
#include "gameui.h"
#include "manual.h"

// ----------------------------------------
// コンストラクタ処理
// ----------------------------------------
CScene_load::CScene_load()
{
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CScene_load::~CScene_load()
{
}

// ----------------------------------------
// シーン親子作成処理
// ----------------------------------------
void CScene_load::LoadAll(void)
{
	/* テクスチャー読み込み */
	// 背景
	CTlyBg::Load();
	// ポーズ
	CPause::Load();
	// タイトルUI
	CTitle_ui::Load();
	// チュートリアルUI
	//CTutorial_ui::Load();
	// タイトルUI
	CGame_ui::Load();
	// 床
	CFloor::Load();
	// メッシュドーム
	CMeshdome::Load();
	// メッシュスフィア
	CMeshsphere::Load();
	// プレイヤー
	CPlayer::Load();
	// アイテム
	CItem::Load();
	// 3DItem
	C3DItem::Load();
	// 3Deffect
	C3DEffect::Load();
	// 3Dparticle
	C3DParticle::Load();
	// 当たり判定
	CCollision::Load();
	// ゲージ
	CGauge::Load();
	// 上位スコア
	//CTopscore::Load();
	// 壁
	CWall::Load();
	// 敵
	CEnemy::Load();
	//
	//C3DLine::Load();
	// オブジェクト
	CObject::Load();
	// タイトル用オブジェクト
	CTitleObject::Load();
	// ライトエフェクト
	CLightEffect::Load();
	// ゲームを開始するためのゲート
	CGate::Load();
	// 爆発エフェクト
	CExplosion::Load();
	// タイトル用の敵
	CTitleEnemy::Load();
	// テロップ
	CTelop::Load();
	// テロップコメント
	CTelopComment::Load();
	// 掲示板
	CBulletinBoard::Load();
	// 2DAnimation
	C2DAnimation::Load();
	// 鍵
	CKey::Load();
	// 床タイル
	CFloarTile::Load();
	// 3dテクスチャ
	C3DTexture::Load();
	// 天井
	CCeiling::Load();
	// マップマーク
	CMapMark::Load();
	// マニュアル
	CManual::Load();
}

// ----------------------------------------
// 読み込んだものを破棄する処理
// ----------------------------------------
void CScene_load::UnLoadAll(void)
{
	/* 読み込んだものの破棄*/
	// 背景
	CTlyBg::UnLoad();
	// ポーズ
	CPause::UnLoad();
	// タイトルUI
	CTitle_ui::UnLoad();
	// チュートリアルUI
	//CTutorial_ui::UnLoad();
	// タイトルUI
	CGame_ui::UnLoad();
	// 床
	CFloor::UnLoad();
	// メッシュドーム
	CMeshdome::UnLoad();
	// メッシュスフィア
	CMeshsphere::Unload();
	// プレイヤー
	CPlayer::UnLoad();
	// アイテム
	CItem::UnLoad();
	// 3DItem
	C3DItem::UnLoad();
	// 3Deffect
	C3DEffect::Unload();
	// 3Dparticle
	C3DParticle::Unload();
	// ゲージ
	CGauge::UnLoad();
	// 壁
	CWall::UnLoad();
	// 敵
	CEnemy::UnLoad();
	//
	//C3DLine::UnLoad();
	//オブジェクト
	CObject::UnLoad();
	// タイトル用オブジェクト
	CTitleObject::UnLoad();
	// ライトエフェクト
	CLightEffect::UnLoad();
	// ゲームを開始するためのゲート
	CGate::UnLoad();
	// タイトル用の敵
	CExplosion::UnLoad();
	// タイトル用の敵
	CTitleEnemy::UnLoad();
	// テロップ
	CTelop::UnLoad();
	// テロップコメント
	CTelopComment::UnLoad();
	// 掲示板
	CBulletinBoard::UnLoad();
	// 2DAnimation
	C2DAnimation::UnLoad();
	// 鍵
	CKey::UnLoad();
	// 床タイル
	CFloarTile::UnLoad();
	// 3dテクスチャ
	C3DTexture::UnLoad();
	// 天井
	CCeiling::UnLoad();
	// マップマーク
	CMapMark::UnLoad();
	// マニュアル
	CManual::UnLoad();
}