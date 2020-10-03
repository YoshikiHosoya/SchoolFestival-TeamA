// =====================================================================================================================================================================
//
// 通常のアイテム処理[normal_item.cpp]
// Author : Fujiwara Masato
//
// =====================================================================================================================================================================

// =====================================================================================================================================================================
//インクルード
// =====================================================================================================================================================================
#include "Normal_Iten.h"
#include "collision.h"
#include "basemode.h"
#include "manager.h"
#include "renderer.h"
#include "particle.h"
#include "sound.h"
#include "player.h"
#include "scoremanager.h"
#include "playerui.h"
#include "grenade.h"

// =====================================================================================================================================================================
//静的メンバ変数の初期化
// =====================================================================================================================================================================

// =====================================================================================================================================================================
//マクロ
// =====================================================================================================================================================================

// =====================================================================================================================================================================
//コンストラクタ
// =====================================================================================================================================================================
CNormalItem::CNormalItem(OBJ_TYPE obj) : CItem(),CScene3D(obj)
{
}
// =====================================================================================================================================================================
//デストラクタ
// =====================================================================================================================================================================
CNormalItem::~CNormalItem()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CNormalItem::Init()
{
	// ポリゴンの生成
	CScene3D::Init();
	// アイテムの初期化
	CItem::Init();

	// 当たり判定の座標の設定
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetSize(GetItem_Data().CollisionSize);
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);

	return S_OK;
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CNormalItem::Uninit(void)
{
	// アイテムの終了処理
	CItem::Uninit();
	// ポリゴンの解放
	CScene3D::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CNormalItem::Update(void)
{
	// 1フレーム前の座標を設定
	m_PosOld = GetPosition();

	// アイテムの挙動ごとの移動
	BehaviorType(GetPosition());

	// アイテムの判定
	ItemCollision();

	// レイの判定に一回でも触れていた時
	//if (m_nHitRayCount >= 1)
	//{
		// アイテムの滞在時間管理
		RemainTimer();
	//}

	// 座標を更新
	SetPosition(GetPosition());

	// アイテムの更新
	CItem::Update();
	// ポリゴンの更新
	CScene3D::Update();
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CNormalItem::Draw(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice =									// デバイスの取得
		CManager::GetRenderer()->GetDevice();

	// アルファテストの設定に変更
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// アルファテスト有効
	pDevice->SetRenderState(D3DRS_ALPHAREF, 200);				// アルファ値の基準設定(基準より大きいと描画する)
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// 状況に応じてアルファテストを実行する(新ピクセル > 現在のピクセル)
	pDevice->SetRenderState(D3DRS_LIGHTING, false);				// ライティングoff
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// ビューマトリックスの代入用
	D3DXMATRIX mtxView;
	// 現在のビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// ビルボード処理
	CHossoLibrary::SetBillboard(&mtxView);

	// 描画
	CScene3D::Draw();

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	// アルファテストの設定を戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		// アルファテスト無効
	pDevice->SetRenderState(D3DRS_LIGHTING, true);				// ライティングon
}

// =====================================================================================================================================================================
//
// デバッグ
//
// =====================================================================================================================================================================
void CNormalItem::DebugInfo()
{
}

// =====================================================================================================================================================================
//
// 種類別テクスチャバインド処理
//
// =====================================================================================================================================================================
void CNormalItem::SwitchTexture(ITEMTYPE type)
{
	switch (type)
	{
	case CItem::ITEMTYPE_HEAVYMACHINEGUN:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_HEAVYMACHINEGUN));
	break;
	case CItem::ITEMTYPE_SHOTGUN:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_SHOTGUN));
	break;
	case CItem::ITEMTYPE_LASERGUN:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_LASERGUN));
	break;
	case CItem::ITEMTYPE_ROCKETLAUNCHER:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_ROCKETLAUNCHER));
	break;
	case CItem::ITEMTYPE_FLAMESHOT:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_FLAMESHOT));
	break;
	case CItem::ITEMTYPE_GOLDCOIN:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_GOLDCOIN));
	break;
	case CItem::ITEMTYPE_SILVERCOIN:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_SILVERCOIN));
	break;
	case CItem::ITEMTYPE_BRONZESCOIN:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BRONZESCOIN));
	break;
	case CItem::ITEMTYPE_DIAMOND:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_DIAMOND));
	break;
	case CItem::ITEMTYPE_BEAR:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BEAR));
	break;
	case CItem::ITEMTYPE_LETTER:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_LETTER));
	break;
	case CItem::ITEMTYPE_APPLE:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_APPLE));
	break;
	case CItem::ITEMTYPE_MELON:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_MELON));
	break;
	case CItem::ITEMTYPE_BANANA:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BANANA));
	break;
	case CItem::ITEMTYPE_MEAT:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_MEAT));
	break;
	case CItem::ITEMTYPE_RICEBALL:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_RICEBALL));
	break;
	case CItem::ITEMTYPE_CANDY:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_CANDY));
	break;
	case CItem::ITEMTYPE_DONUT:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_DONUT));
	break;
	case CItem::ITEMTYPE_LOLIPOP:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_LOLIPOP));
	break;
	case CItem::ITEMTYPE_BREAD:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BREAD));
	break;
	case CItem::ITEMTYPE_CHOCOLATE:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_CHOCOLATE));
	break;
	case CItem::ITEMTYPE_ICE:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_ICE));
	break;
	case CItem::ITEMTYPE_BOMBUP:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BOMBUP));
	break;
	case CItem::ITEMTYPE_BULLETUP:
	this->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BULLETUP));
	break;
	}

	SetItemType(type);
}

// =====================================================================================================================================================================
//
// アイテムの判定
//
// =====================================================================================================================================================================
void CNormalItem::ItemCollision()
{
	// 当たり判定
	if (GetCollision() != nullptr)
	{
		// 座標の更新 pos
		GetCollision()->SetPos(&GetPosition());
		// マップのポインタ取得
		CMap *pMap = CManager::GetBaseMode()->GetMap();

		if (pMap)
		{
			if (GetCollision()->RayCollision(pMap, m_PosOld,GetPosition()))
			{
				if (GetBehavior() != BEHAVIOR_NONE)
				{
					// まだレイの判定に一度も触れていなかった時
					if (m_nHitRayCount <= 0)
					{
						// アイテムの反射処理
						ReflectionItem();
						// 重力の初期化
						m_fGravity = 0.0f;
					}
					else
					{
						m_Move = ZeroVector3;
					}
				}

				m_nHitRayCount++;
			}
			else
			{
				if (m_nHitRayCount < 2)
				{
					// 正規化
					D3DXVec3Normalize(&m_Move, &m_Move);

					if (GetBehavior() == BEHAVIOR_BURSTS)
					{
						m_fGravity += 0.05f;
					}
					else
					{
						// 重力を加速
						m_fGravity += 0.04f;
					}
					// 重力を反映
					GetPosition().y -= m_fGravity;
				}
			}
		}
	}
}

// =====================================================================================================================================================================
//
// 反射処理
//
// =====================================================================================================================================================================
void CNormalItem::ReflectionItem()
{
	// 法線ベクトル
	const D3DXVECTOR3 NormalV = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	// 進行ベクトル
	D3DXVECTOR3 ProgressV = m_PosOld - GetPosition();
	// レイの判定にに触れたとき進行ベクトルを法線ベクトルの方向に変換する
	ReflectingVectorCalculation(&m_Move, ProgressV, NormalV);
}

// =====================================================================================================================================================================
//
// 点滅処理
//
// =====================================================================================================================================================================
void CNormalItem::Flashing()
{
	CItem::Flashing();

	// 余りが0の時透明にする
	if (m_nColCnt % 30 == 0)
	{
		this->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}
	// 余りが0の時通常状態にする
	else if(m_nColCnt % 15 == 0)
	{
		this->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	// 規定時間を過ぎ時
	if (m_nColCnt >= GetItem_Data().nFlashTime)
	{
		// アイテムの削除
		Rerease();
		// 変数の初期化
		m_nColCnt = 0;
	}
}

// =====================================================================================================================================================================
//
// 滞在時間を計算し0になったら削除する
//
// =====================================================================================================================================================================
void CNormalItem::RemainTimer()
{
	// アイテムの滞在時間を減少
	CItem::RemainTimer();

	// 残り時間が0以下になったら削除
	if (GetRemainTime() <= 0)
	{
		// 点滅させる
		Flashing();
	}
}

// =====================================================================================================================================================================
//
// アイテムが判定をもらった時
//
// =====================================================================================================================================================================
void CNormalItem::HitItem(ITEMTYPE type, TAG Tag)
{
	// アイテムが判定をもらった時
	CItem::HitItem(type, Tag);

	// アイテム取得エフェクトを出す
	CParticle::CreateFromText(GetPosition(), ZeroVector3, CParticleParam::EFFECT_GETWEAPON);
	// 削除
	Rerease();
}

// =====================================================================================================================================================================
//
// アイテム取得時の種類別処理
//
// =====================================================================================================================================================================
void CNormalItem::ItemAcquisition(ITEMTYPE type, TAG Tag)
{
	// アイテムの種類ごとの処理
	switch (type)
	{
		// ヘビーマシンガン
	case (ITEMTYPE_HEAVYMACHINEGUN): {
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_WEAPON);
		CManager::GetSound()->Play(CSound::LABEL_SE_VOICE_HEAVYMACHINEGUN);

		CItem::GetPlayer((int)Tag)->GetGun()->SetGunType(CGun::GUNTYPE_HEAVYMACHINEGUN);
	}break;

		// ショットガン
	case (ITEMTYPE_SHOTGUN): {
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_WEAPON);
		CManager::GetSound()->Play(CSound::LABEL_SE_VOICE_SHOTGUN);

		CItem::GetPlayer((int)Tag)->GetGun()->SetGunType(CGun::GUNTYPE_SHOTGUN);
	}break;

		// レーザーガン
	case (ITEMTYPE_LASERGUN): {
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_WEAPON);
		CManager::GetSound()->Play(CSound::LABEL_SE_VOICE_LAZERGUN);

		CItem::GetPlayer((int)Tag)->GetGun()->SetGunType(CGun::GUNTYPE_LASERGUN);
	}break;

		// ロケットランチャー
	case (ITEMTYPE_ROCKETLAUNCHER): {
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_WEAPON);
		CManager::GetSound()->Play(CSound::LABEL_SE_VOICE_ROCKETLAUNCHER);

		CItem::GetPlayer((int)Tag)->GetGun()->SetGunType(CGun::GUNTYPE_ROCKETLAUNCHER);
	}break;

		// フレイムショット
	case (ITEMTYPE_FLAMESHOT): {
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_WEAPON);
		CManager::GetSound()->Play(CSound::LABEL_SE_VOICE_FLAMESHOT);

		CItem::GetPlayer((int)Tag)->GetGun()->SetGunType(CGun::GUNTYPE_FLAMESHOT);
	}break;

		// 金貨
	case (ITEMTYPE_GOLDCOIN): {
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_GCOIN), (int)Tag);
	}break;

		// 銀貨
	case (ITEMTYPE_SILVERCOIN): {
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_SCOIN), (int)Tag);
	}break;

		// 銅貨
	case (ITEMTYPE_BRONZESCOIN): {
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_BCOIN), (int)Tag);
	}break;

		// ダイアモンド
	case (ITEMTYPE_DIAMOND): {
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_DIAMOND), (int)Tag);
	}break;
		// 熊
	case (ITEMTYPE_BEAR): {
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_BEAR), (int)Tag);
	}break;

		// 手紙
	case (ITEMTYPE_LETTER): {
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_LETTER), (int)Tag);

	}break;

		// リンゴ
	case ITEMTYPE_APPLE:
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FRUIT), (int)Tag);
		break;
		// メロン
	case ITEMTYPE_MELON:
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FRUIT), (int)Tag);
		break;
		// バナナ
	case ITEMTYPE_BANANA:
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FRUIT), (int)Tag);
		break;


		// 肉
	case ITEMTYPE_MEAT:
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD), (int)Tag);
		break;
		// おにぎり
	case (ITEMTYPE_RICEBALL):
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD), (int)Tag);
		break;
		// 飴
	case (ITEMTYPE_CANDY):
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD), (int)Tag);
		break;
		// ドーナツ
	case (ITEMTYPE_DONUT):
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD), (int)Tag);
		break;
		// ロリポップ
	case (ITEMTYPE_LOLIPOP):
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD), (int)Tag);
		break;
		// 熊
	case (ITEMTYPE_BREAD):
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD), (int)Tag);
		break;
		// チョコレート
	case (ITEMTYPE_CHOCOLATE):
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD), (int)Tag);
		break;
		// アイス
	case (ITEMTYPE_ICE):
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD), (int)Tag);
		break;

		// 爆弾の数を増やす
	case (ITEMTYPE_BOMBUP): {
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_WEAPON);
		CItem::GetPlayer((int)Tag)->GetGrenadeFire()->GrenadeAddAmmo();
	}break;

		// ハンドガン以外の弾の残弾数を増やす
	case (ITEMTYPE_BULLETUP): {
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_WEAPON);
		CItem::GetPlayer((int)Tag)->GetGun()->GunAddAmmo(CItem::GetPlayer((int)Tag)->GetGun()->GetGunType());
	}break;
	}

	CItem::ItemAcquisition(type, Tag);
}


// =====================================================================================================================================================================
//
// キャラクターがアイテムを落とすときの生成処理 確定しないならtypeにNONEを入れる
//
// =====================================================================================================================================================================
CNormalItem * CNormalItem::DropItem(D3DXVECTOR3 droppos, bool fixed, ITEMTYPE type)
{
	// メモリの確保
	CNormalItem *pItem = new CNormalItem(OBJTYPE_NORMALITEM);

	// 初期化
	pItem->Init();
	// サイズの設定
	pItem->SetSize(D3DXVECTOR3(
		pItem->GetItem_Data().CollisionSize.x /2,
		pItem->GetItem_Data().CollisionSize.y /2,
		pItem->GetItem_Data().CollisionSize.z /2));

	// アイテムが生成される位置の調整
	//pItem->SetDropPos(droppos);

	droppos.y += 30.0f;

	// アイテムの位置の設定
	pItem->SetPosition(droppos);

	pItem->SetBehavior(BEHAVIOR_NONE);

	// アイテムのドロップをパターンごとに変える
	pItem->DropPattern(fixed, type);

	// 種類別にテクスチャを設定
	pItem->SwitchTexture(pItem->GetItemType());

	return pItem;
}

// =====================================================================================================================================================================
//
// アイテムを複数一気にドロップさせる時
//
// =====================================================================================================================================================================
void CNormalItem::DropItem_Multiple(const D3DXVECTOR3 originpos, ITEM_LIST_DROPMULTIPLE type, ITEM_BEHAVIOR behavior)
{
	// 生成する数分
	for (int nNum = 0; nNum < MULTIPLE_ITEM_NUM; nNum++)
	{
		// メモリの確保
		CNormalItem *pItem = new CNormalItem(OBJTYPE_NORMALITEM);

		// 初期化
		pItem->Init();

		// サイズの設定
		pItem->SetSize(D3DXVECTOR3(
			pItem->GetItem_Data().CollisionSize.x / 2,
			pItem->GetItem_Data().CollisionSize.y / 2,
			pItem->GetItem_Data().CollisionSize.z / 2));

		// 木から落ちるアイテムだけ
		if (behavior == BEHAVIOR_FREEFALL)
		{
			pItem->SetPosition(pItem->RandomDropPosX(originpos, 100));
		}
		// その他は原点座標を基準にする
		else
		{
			if (behavior == BEHAVIOR_BURSTS)
			{
				D3DXVECTOR3 pos = originpos;
				pItem->SetPosition(D3DXVECTOR3(pos.x, pos.y + 50, pos.z));

			}
			else
			{
				pItem->SetPosition(originpos);
			}
		}

		// 挙動の設定
		pItem->SetBehavior(behavior);

		// 特別なアイテムリストを指定された時のみアイテムの選考方法を変える
		if (type == LIST_SPECIAL)
		{
			// 乱数リストからアイテムをランダムに選び設定する
			pItem->SwitchTexture(pItem->BoxRand());
		}
		else
		{
			// 複数体のタイプ設定
			pItem->SetMultiType(type);
		}

		// アイテムの挙動と種類の設定
		pItem->DropPattern_Multiple(type, behavior, nNum);
	}
}
