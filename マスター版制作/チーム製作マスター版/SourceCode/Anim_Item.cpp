// =====================================================================================================================================================================
//
// アニメーションアイテム処理の説明[animation_item.cpp]
// Author : Fujiwara Masato
//
// =====================================================================================================================================================================

// =====================================================================================================================================================================
//インクルード
// =====================================================================================================================================================================
#include "Anim_Item.h"
#include "collision.h"
#include "basemode.h"
#include "manager.h"
#include "renderer.h"
#include "particle.h"
#include "sound.h"
#include "player.h"
#include "scoremanager.h"
#include "playerui.h"
#include "map.h"

// =====================================================================================================================================================================
//静的メンバ変数の初期化
// =====================================================================================================================================================================

// =====================================================================================================================================================================
//マクロ
// =====================================================================================================================================================================
#define SWITCHCOUNT (5)
// =====================================================================================================================================================================
//コンストラクタ
// =====================================================================================================================================================================
CAnimationItem::CAnimationItem(OBJ_TYPE obj) : CItem(), CTexAnimation3D(obj)
{
}
// =====================================================================================================================================================================
//デストラクタ
// =====================================================================================================================================================================
CAnimationItem::~CAnimationItem()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CAnimationItem::Init()
{
	// ポリゴンの生成
	CTexAnimation3D::Init();
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
void CAnimationItem::Uninit(void)
{
	// アイテムの終了処理
	CItem::Uninit();
	// ポリゴンの解放
	CTexAnimation3D::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CAnimationItem::Update(void)
{
	// 1フレーム前の座標を設定
	m_PosOld = GetPosition();

	// アイテムの挙動ごとの移動
	BehaviorType(GetPosition());

	// アイテムの判定
	ItemCollision();

	// アイテムの滞在時間管理
	RemainTimer();

	// 座標を更新
	SetPosition(GetPosition());

	// アイテムの更新
	CItem::Update();
	// ポリゴンの更新
	CTexAnimation3D::Update();
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CAnimationItem::Draw(void)
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
	CTexAnimation3D::Draw();

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
void CAnimationItem::DebugInfo()
{
}

// =====================================================================================================================================================================
//
// 種類別テクスチャバインド処理
//
// =====================================================================================================================================================================
void CAnimationItem::SwitchTexture(ITEMTYPE type)
{
	switch (type)
	{
	case CItem::ANIM_ITEMTYPE_ROASTCHICKEN:
		this->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_ROASTCHICKEN));
		this->SetTex(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_ROASTCHICKEN);
		this->SetCntSwitch(SWITCHCOUNT);
		break;

	case CItem::ANIM_ITEMTYPE_FISH:
		this->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_FISH));
		this->SetTex(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_FISH);
		this->SetCntSwitch(SWITCHCOUNT);
		break;
	case CItem::ANIM_ITEMTYPE_BEAR:
		this->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_BEAR));
		this->SetTex(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_BEAR);
		this->SetCntSwitch(SWITCHCOUNT);
		break;


	case CItem::ANIM_ITEMTYPE_DOLL:
		this->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_DOLL));
		this->SetTex(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_DOLL);
		this->SetCntSwitch(SWITCHCOUNT);
		break;
	case CItem::ANIM_ITEMTYPE_LETTER:
		this->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_LETTER));
		this->SetTex(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_LETTER);
		this->SetCntSwitch(SWITCHCOUNT);
		break;
	case CItem::ANIM_ITEMTYPE_MEDAL:
		this->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_MEDAL));
		this->SetTex(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_MEDAL);
		this->SetCntSwitch(SWITCHCOUNT);
		break;
	case CItem::ANIM_ITEMTYPE_MEDAL2:
		this->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_MEDAL2));
		this->SetTex(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_MEDAL2);
		this->SetCntSwitch(SWITCHCOUNT);
		break;
	case CItem::ANIM_ITEMTYPE_COIN:
		this->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_COIN));
		this->SetTex(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_COIN);
		this->SetCntSwitch(SWITCHCOUNT);
		break;

	case CItem::ANIM_ITEMTYPE_RUBY:
		this->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_RUBY));
		this->SetTex(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_RUBY);
		this->SetCntSwitch(SWITCHCOUNT);
		break;
	case CItem::ANIM_ITEMTYPE_SAPPHIRE:
		this->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_SAPPHIRE));
		this->SetTex(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_SAPPHIRE);
		this->SetCntSwitch(SWITCHCOUNT);
		break;
	case CItem::ANIM_ITEMTYPE_TOPAZ:
		this->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_TOPAZ));
		this->SetTex(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_TOPAZ);
		this->SetCntSwitch(SWITCHCOUNT);
		break;
	case CItem::ANIM_ITEMTYPE_DANCEMONKEY:
		this->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_DANCEMONKEY));
		this->SetTex(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_DANCEMONKEY);
		this->SetCntSwitch(SWITCHCOUNT);
		break;
	case CItem::ANIM_ITEMTYPE_JUMPMONKEY:
		this->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_JUMPMONKEY));
		this->SetTex(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_JUMPMONKEY);
		this->SetCntSwitch(SWITCHCOUNT);
		break;
	case CItem::ANIM_ITEMTYPE_PRISONER:
		this->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_PRISONER));
		this->SetTex(CTexture::SEPARATE_TEX_TYPE::SEPARATE_TEX_ITEM_PRISONER);
		this->SetCntSwitch(SWITCHCOUNT);
		break;
	}
}

// =====================================================================================================================================================================
//
// アイテムの判定
//
// =====================================================================================================================================================================
void CAnimationItem::ItemCollision()
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
			if (GetCollision()->RayCollision(pMap, GetPosition(), m_PosOld))
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
				else
				{
					// 重力の初期化
					m_fGravity = 0.0f;
					m_Move = ZeroVector3;
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
void CAnimationItem::ReflectionItem()
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
void CAnimationItem::Flashing()
{
	CItem::Flashing();

	// 余りが0の時透明にする
	if (m_nColCnt % 30 == 0)
	{
		this->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}
	// 余りが0の時通常状態にする
	else if (m_nColCnt % 15 == 0)
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
void CAnimationItem::RemainTimer()
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
void CAnimationItem::HitItem(ITEMTYPE type, TAG Tag)
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
void CAnimationItem::ItemAcquisition(ITEMTYPE type, TAG Tag)
{
	// アイテムの種類ごとの処理
	switch (type)
	{
	case CItem::ANIM_ITEMTYPE_ROASTCHICKEN:
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_ANI_FOOD), (int)Tag);
		break;
	case CItem::ANIM_ITEMTYPE_FISH:
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_ANI_FOOD), (int)Tag);
		break;
	case CItem::ANIM_ITEMTYPE_BEAR:
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_ANI_BEAR), (int)Tag);
		break;
	case CItem::ANIM_ITEMTYPE_DOLL:
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_ANI_BEAR), (int)Tag);
		break;
	case CItem::ANIM_ITEMTYPE_LETTER:
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_ANI_LETTER), (int)Tag);
		break;
	case CItem::ANIM_ITEMTYPE_MEDAL:
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_ANI_MEDAL), (int)Tag);
		break;
	case CItem::ANIM_ITEMTYPE_MEDAL2:
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_ANI_MEDAL), (int)Tag);
		break;
	case CItem::ANIM_ITEMTYPE_COIN:
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_GCOIN), (int)Tag);
		break;
	case CItem::ANIM_ITEMTYPE_RUBY:
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_ANI_JEWELRY), (int)Tag);
		break;
	case CItem::ANIM_ITEMTYPE_SAPPHIRE:
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_ANI_JEWELRY), (int)Tag);
		break;
	case CItem::ANIM_ITEMTYPE_TOPAZ:
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_ANI_JEWELRY), (int)Tag);
		break;
	case CItem::ANIM_ITEMTYPE_DANCEMONKEY:
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_ANI_MONKEY), (int)Tag);
		break;
	case CItem::ANIM_ITEMTYPE_JUMPMONKEY:
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		CItem::GetPlayer((int)Tag)->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_ANI_MONKEY), (int)Tag);
		break;
	case CItem::ANIM_ITEMTYPE_PRISONER:
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		CItem::GetPlayer((int)Tag)->SetLife(GetPlayer((int)Tag)->GetLife() + 1);
		break;
	}

	CItem::ItemAcquisition(type, Tag);
}


// =====================================================================================================================================================================
//
// キャラクターがアイテムを落とすときの生成処理 確定しないならtypeにNONEを入れる
//
// =====================================================================================================================================================================
CAnimationItem * CAnimationItem::DropItem(D3DXVECTOR3 droppos, bool fixed, ITEMTYPE type)
{
	// メモリの確保
	CAnimationItem *pItem = new CAnimationItem(OBJTYPE_ANIMATIONITEM);

	// 初期化
	pItem->Init();
	// サイズの設定
	pItem->SetSize(D3DXVECTOR3(
		pItem->GetItem_Data().CollisionSize.x / 2,
		pItem->GetItem_Data().CollisionSize.y / 2,
		pItem->GetItem_Data().CollisionSize.z / 2));

	// アイテムが生成される位置の調整
	//pItem->SetDropPos(droppos);

	droppos.y += 30.0f;
	droppos.z = 0.0f;
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
void CAnimationItem::DropItem_Multiple(const D3DXVECTOR3 originpos, ITEM_LIST_DROPMULTIPLE type, ITEM_BEHAVIOR behavior)
{
	int nForNum = MULTIPLE_ITEM_NUM;

	if (behavior == BEHAVIOR_FULLBURSTS)
	{
		nForNum = MULTIPLE_ITEM_NUM*2;
	}

	// 生成する数分
	for (int nNum = 0; nNum < nForNum; nNum++)
	{
		// メモリの確保
		CAnimationItem *pItem = new CAnimationItem(OBJTYPE_ANIMATIONITEM);

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
				D3DXVECTOR3 pos = originpos;
				pItem->SetPosition(D3DXVECTOR3(pos.x, pos.y, 0.0f));
			}
		}

		// 挙動の設定
		pItem->SetBehavior(behavior);

		// 複数体のタイプ設定
		pItem->SetMultiType(type);

		// アイテムの挙動と種類の設定
		pItem->DropPattern_Multiple(type, behavior, nNum);
	}
}
