// =====================================================================================================================================================================
//
// アイテム処理の説明[item.cpp]
// Author : Fujiwara Masato
//
// =====================================================================================================================================================================
#include "item.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "collision.h"
#include "debugproc.h"
#include "player.h"
#include "playerui.h"
#include "playergetscoreui.h"
#include "gun.h"
#include <random>
#include "inputKeyboard.h"
#include "sound.h"
#include "scoremanager.h"
#include "particle.h"
#include "grenadefire.h"
#include <algorithm>

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
ITEM_DATA	CItem::m_ItemData				 = {};
int			CItem::m_nAddCoin				 = 1;
ITEM_GACHA CItem::m_ItemGachaData			 = {};

std::vector<unsigned int>					CItem::m_nSaveHitItem				 = {};
std::vector<CItem::ITEM_RARITY>				CItem::m_nBoxRandRarityDataList		 = {};
std::vector<CItem::ITEM_RARITY>				CItem::m_nDefaultRarityList			 = {};
std::vector<std::vector<CItem::ITEMTYPE>>	CItem::m_nBoxRandDefaultRarityData	 = {};

// =====================================================================================================================================================================
// テキストファイル名
// =====================================================================================================================================================================
char *CItem::m_ItemFileName =
{
	"data/Load/Item/ItemData.txt" ,			// アイテムの情報
};

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define FULLRAND_HITPROBABILITY (5)
#define MULTIPLE_ITEM_NUM (5)// まとめて生成する際の数

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CItem::CItem(OBJ_TYPE type) :CScene3D(type)
{
	// プレイヤーのポインタ
	m_pPlayer[MAX_CONTROLLER] = {};
	// 当たり判定のポインタ
	m_pCollision = nullptr;
	// アイテムがマップに残る時間
	m_nRemainTime = m_ItemData.nDeleteTime;
	// αカラーカウント
	m_nColCnt = 0;
	// アイテムの種類
	m_Type = ITEMTYPE_NONE;
	// アイテムをドロップさせる種類
	m_Drop = ITEMDROP_WEAPON;
	// 移動量
	m_Move = D3DXVECTOR3(0.0f,-1.0f, 0.0f);
	// 重力の初期値
	m_fGravity = 0.0f;
	// 判定回数の初期化
	m_nHitRayCount = 0;
	// 1フレーム前の座標
	m_PosOld = ZeroVector3;
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CItem::~CItem()
{
	// 当たり判定の削除
	if (m_pCollision != nullptr)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CItem::Init()
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_CONTROLLER; nCntPlayer++)
	{
		m_pPlayer[nCntPlayer] = CManager::GetBaseMode()->GetPlayer((TAG)(nCntPlayer));
	}

	// 初期化
	CScene3D::Init();

	// 重力の初期値
	m_fGravity = 1.0f;

	// 当たり判定生成
	m_pCollision = CCollision::Create();
	m_pCollision->SetPos(&GetPosition());
	m_pCollision->SetSize(m_ItemData.CollisionSize);
	m_pCollision->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);

	return S_OK;
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CItem::Uninit(void)
{
	// 終了処理
	CScene3D::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CItem::Update(void)
{
	// 当たり判定系
	ItemCollision();

	// レイの判定に一回でも触れていた時
	if (m_nHitRayCount >= 1)
	{
		// アイテムの滞在時間管理
		RemainTimer();
	}

	if (m_Behavior == BEHAVIOR_BURSTS)
	{
		GetPosition() += m_Move * 4.0f;
	}
	else
	{
		GetPosition() += m_Move * 1.5f;
	}
	SetPosition(GetPosition());

	// 更新
	CScene3D::Update();
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CItem::Draw(void)
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
// アイテム取得時の種類別処理
//
// =====================================================================================================================================================================
void CItem::ItemAcquisition(ITEMTYPE type, TAG Tag)
{
	// アイテムの種類ごとの処理
	switch (type)
	{
		// ヘビーマシンガン
	case (ITEMTYPE_HEAVYMACHINEGUN): {
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_WEAPON);
		CManager::GetSound()->Play(CSound::LABEL_SE_VOICE_HEAVYMACHINEGUN);

		m_pPlayer[(int)Tag]->GetGun()->SetGunType(CGun::GUNTYPE_HEAVYMACHINEGUN);
	}break;

		// ショットガン
	case (ITEMTYPE_SHOTGUN): {
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_WEAPON);
		CManager::GetSound()->Play(CSound::LABEL_SE_VOICE_SHOTGUN);

		m_pPlayer[(int)Tag]->GetGun()->SetGunType(CGun::GUNTYPE_SHOTGUN);
	}break;

		// レーザーガン
	case (ITEMTYPE_LASERGUN): {
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_WEAPON);
		CManager::GetSound()->Play(CSound::LABEL_SE_VOICE_LAZERGUN);

		m_pPlayer[(int)Tag]->GetGun()->SetGunType(CGun::GUNTYPE_LASERGUN);
	}break;

		// ロケットランチャー
	case (ITEMTYPE_ROCKETLAUNCHER): {
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_WEAPON);
		CManager::GetSound()->Play(CSound::LABEL_SE_VOICE_ROCKETLAUNCHER);

		m_pPlayer[(int)Tag]->GetGun()->SetGunType(CGun::GUNTYPE_ROCKETLAUNCHER);
	}break;

		// フレイムショット
	case (ITEMTYPE_FLAMESHOT): {
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_WEAPON);
		CManager::GetSound()->Play(CSound::LABEL_SE_VOICE_FLAMESHOT);

		m_pPlayer[(int)Tag]->GetGun()->SetGunType(CGun::GUNTYPE_FLAMESHOT);
	}break;

		// 金貨
	case (ITEMTYPE_GOLDCOIN): {
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_GCOIN));
	}break;

		// 銀貨
	case (ITEMTYPE_SILVERCOIN): {
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_SCOIN));
	}break;

		// 銅貨
	case (ITEMTYPE_BRONZESCOIN): {
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_BCOIN));
	}break;

		// ダイアモンド
	case (ITEMTYPE_DIAMOND): {
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_DIAMOND));
	}break;
		// 熊
	case (ITEMTYPE_BEAR): {
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_BEAR));
	}break;

		// 手紙
	case (ITEMTYPE_LETTER): {
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);

		// コインを取るたびにコインのスコアアップ
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(AddCoinScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_LETTER)));
	}break;

		// リンゴ
	case ITEMTYPE_APPLE:
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FRUIT));
		break;
		// メロン
	case ITEMTYPE_MELON:
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FRUIT));
		break;
		// バナナ
	case ITEMTYPE_BANANA:
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FRUIT));
	break;


		// 肉
	case ITEMTYPE_MEAT:
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD));
		break;
		// おにぎり
	case (ITEMTYPE_RICEBALL):
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD));
		break;
		// 飴
	case (ITEMTYPE_CANDY):
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD));
		break;
		// ドーナツ
	case (ITEMTYPE_DONUT):
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD));
		break;
		// ロリポップ
	case (ITEMTYPE_LOLIPOP):
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD));
		break;
		// 熊
	case (ITEMTYPE_BREAD):
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD));
		break;
		// チョコレート
	case (ITEMTYPE_CHOCOLATE):
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD));
		break;
		// アイス
	case (ITEMTYPE_ICE):
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_SCORE_ITEM);
		// スコアアップ
		m_pPlayer[(int)Tag]->GetPlayerUI()->SetItemScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_ITEM_FOOD));
	break;

		// 爆弾の数を増やす
	case (ITEMTYPE_BOMBUP): {
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_WEAPON);
		m_pPlayer[(int)Tag]->GetGrenadeFire()->GrenadeAddAmmo();
	}break;

		// ハンドガン以外の弾の残弾数を増やす
	case (ITEMTYPE_BULLETUP): {
		// SEを鳴らす
		CManager::GetSound()->Play(CSound::LABEL_SE_GET_WEAPON);
		m_pPlayer[(int)Tag]->GetGun()->GunAddAmmo(m_pPlayer[(int)Tag]->GetGun()->GetGunType());
	}break;
	}

	m_pPlayer[(int)Tag]->SetState(CCharacter::CHARACTER_STATE_ITEMGET_FLASH);

	CParticle::CreateFromText(GetPosition(), ZeroVector3, CParticleParam::EFFECT_GETWEAPON);
}

// =====================================================================================================================================================================
//
// デバッグ
//
// =====================================================================================================================================================================
void CItem::DebugInfo()
{
}

// =====================================================================================================================================================================
//
// アイテムが判定をもらった時
//
// =====================================================================================================================================================================
void CItem::HitItem(ITEMTYPE type, TAG Tag)
{
	// 種類ごとの処理
	ItemAcquisition(type, Tag);
	// 削除
	Rerease();
}

// =====================================================================================================================================================================
//
// アイテムを落とす位置の設定
//
// =====================================================================================================================================================================
void CItem::SetDropPos(D3DXVECTOR3 &characterpos)
{
	// プレイヤーのポインタ取得
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer(TAG::PLAYER_1);
	// プレイヤーが存在した時
	if (pPlayer != nullptr)
	{
		// プレイヤーの向きを取得
		if (pPlayer->GetCharacterDirection() == DIRECTION::LEFT)
		{
			characterpos.x -= 50;
		}
		else if(pPlayer->GetCharacterDirection() == DIRECTION::RIGHT)
		{
			characterpos.x += 50;
		}

		characterpos.y += 50;
	}
}

// =====================================================================================================================================================================
//
// 移動量の設定
//
// =====================================================================================================================================================================
void CItem::SetMove(D3DXVECTOR3 move)
{
	m_Move = move;
}

// =====================================================================================================================================================================
//
// 滞在時間を計算し0になったら削除する
//
// =====================================================================================================================================================================
void CItem::RemainTimer()
{
	// アイテムの滞在時間を減少
	m_nRemainTime--;

	// 残り時間が0以下になったら削除
	if (m_nRemainTime <= 0)
	{
		// 点滅させる
		Flashing();
	}
}

// =====================================================================================================================================================================
//
// 点滅処理
//
// =====================================================================================================================================================================
void CItem::Flashing()
{
	// カウント加算
	m_nColCnt++;
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

	// 3秒以上経過したらアイテムを削除する
	if (m_nColCnt >= m_ItemData.nFlashTime)
	{
		// 変数の初期化
		m_nColCnt = 0;
		// 削除
		Rerease();
	}
}

// =====================================================================================================================================================================
//
// ランダム生成
//
// =====================================================================================================================================================================
uint64_t CItem::GetRandRange(uint64_t min_val, uint64_t max_val)
{
	// メルセンヌ・ツイスター法による擬似乱数生成器を、
	// ハードウェア乱数をシードにして初期化
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());

	// 乱数生成器
	static std::mt19937_64 mt64(seed_gen());

	// [min_val, max_val] の一様分布整数 (int) の分布生成器
	std::uniform_int_distribution<uint64_t> get_rand_uni_int(min_val, max_val);

	// 乱数を生成
	return get_rand_uni_int(mt64);
}

// =====================================================================================================================================================================
//
// コインのスコアを加算する処理
//
// =====================================================================================================================================================================
int CItem::AddCoinScore(int nScore)
{
	// スコアとカウントをかける
	nScore *= m_nAddCoin;

	// カウントを倍にする
	m_nAddCoin += m_nAddCoin;

	// スコアの値を返す
	return nScore;
}

// =====================================================================================================================================================================
//
// 完全乱数
//
// =====================================================================================================================================================================
CItem::ITEMTYPE CItem::FullRand()
{
	//FULLRAND_HITPROBABILITY
	// 完全乱数で出たアイテムの結果を保存
	//nSaveHitItem
	// n回連続で★3が出ていなかった時強制的に★3のアイテムをドロップする
	//if
	return ITEMTYPE();
}

// =====================================================================================================================================================================
//
// ボックス乱数
//
// =====================================================================================================================================================================
CItem::ITEMTYPE CItem::BoxRand()
{
	// ピックされた末尾の要素を削除する
	if (!m_nDefaultRarityList.empty())
	{
		// レアリティリストの末尾からピックする(リストは既にランダム化されている)
		const ITEM_RARITY Rarity = m_nDefaultRarityList.back();
		// ピックされた末尾の要素を削除する
		m_nDefaultRarityList.pop_back();
		// レアリティリストからピックされたレアリティのリストの中からランダムにアイテムを選出する
		//v.list[Rarity].最初　.最後 何行目の何番目か (0番目から最大数分)
		//const ITEMTYPE type = ItemRandomRange(m_nBoxRandDefaultRarityData.at(Rarity).at(0), m_nBoxRandDefaultRarityData.at(Rarity).at(m_nBoxRandDefaultRarityData.at(Rarity).size() - 1));
		const ITEMTYPE type = ItemWhichOnePick(m_nBoxRandDefaultRarityData, Rarity);

		// 配列が空だった時
		if (m_nDefaultRarityList.empty())
		{
			// ボックスランドのリスト再設定
			SetBoxRandDataList();
		}

		return type;
	}

	// エラー防止
	return ITEMTYPE_HEAVYMACHINEGUN;
}

// =====================================================================================================================================================================
//
// ボックス乱数の母数が0以下になった時結果をリセットする 現在のマップの状況によって結果を変える
//
// =====================================================================================================================================================================
void CItem::SetBoxRandDataList()
{
	// ボックスランドのリストにデータを設定
	AddBoxRandList();
}

// =====================================================================================================================================================================
//
// アイテムのレアリティと母数を元にランダムなリストを生成する
//
// =====================================================================================================================================================================
void CItem::AddBoxRandList()
{
	// デフォルトのボックス乱数のデータ
	// レアリティ*各レアリティの数
	for (int nNum = 0; nNum < ITEM_RARITY_TOTAL; nNum++)
	{
		for (unsigned int nCnt = 0; nCnt < m_ItemGachaData.BoxRandDefault_RarityNum[nNum]; nCnt++)
		{
			// リストに各レアリティの数を数分追加
			m_nDefaultRarityList.emplace_back((ITEM_RARITY)nNum);
		}
	}

	// 要素をシャッフルし設定する
	random_shuffle(m_nDefaultRarityList.begin(), m_nDefaultRarityList.end());
}

// =====================================================================================================================================================================
//
// 複数個一気にアイテムが生成される時のアイテムの挙動制御
//
// =====================================================================================================================================================================
void CItem::BurstsItem()
{
}

// =====================================================================================================================================================================
//
// 空中にあったアイテムが床に着いた時跳ね返る処理
//
// =====================================================================================================================================================================
void CItem::BounceItem()
{
}

// =====================================================================================================================================================================
//
// 原点から指定された指定範囲のX座標を返す
//
// =====================================================================================================================================================================
D3DXVECTOR3 CItem::RandomDropPosX(const D3DXVECTOR3 originpos, int radius)
{
	// アイテムをドロップさせる座標
	D3DXVECTOR3 DropPos = originpos;
	// 原点から半径を引いた座標と半径を足した座標の範囲内の座標をランダムに返す
	//DropPos.x = (float)GetRandRange((int)originpos.x - radius, (int)originpos.x + radius);

	DropPos.x = CHossoLibrary::Random((float)radius);
	DropPos.z = 0.0f;

	return DropPos;
}

// =====================================================================================================================================================================
//
// 複数体のタイプ設定
//
// =====================================================================================================================================================================
void CItem::SetMultiType(ITEM_LIST_DROPMULTIPLE list)
{
	switch (list)
	{
	case CItem::LIST_FRUIT:
		// フルーツのみ
		SwitchTexture(this->RandDropItem(ITEMDROP_FRUIT), this);
		break;

	case CItem::LIST_FOOD:
		// 食べ物のみ
		SwitchTexture(this->RandDropItem(ITEMDROP_FOOD), this);
		break;

	case CItem::LIST_COIN:
		// コインのみ
		SwitchTexture(this->RandDropItem(ITEMDROP_COIN), this);
		break;

	case CItem::LIST_RARE:
		// レアなアイテムのみ
		SwitchTexture(this->RandDropItem(ITEMDROP_RARE), this);
		break;
	}
}

// =====================================================================================================================================================================
//
// 判定系
//
// =====================================================================================================================================================================
void CItem::ItemCollision()
{
	// 当たり判定
	if (m_pCollision != nullptr)
	{
		// 座標の更新 pos
		m_pCollision->SetPos(&GetPosition());
		// マップのポインタ取得
		CMap *pMap = CManager::GetBaseMode()->GetMap();
		// 1フレーム前の座標を求める
		m_PosOld = GetPosition();

		if (pMap)
		{
			if (m_pCollision->RayCollision(pMap,GetPosition() - D3DXVECTOR3(0.0f,30.0f,0.0f),GetPosition()))
			{
				if (m_Behavior != BEHAVIOR_NONE)
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

					if (m_Behavior == BEHAVIOR_BURSTS)
					{
						m_fGravity += 0.1f;
					}
					else
					{
						// 重力を加速
						m_fGravity += 0.05f;
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
void CItem::ReflectionItem()
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
// テスト用
//
// =====================================================================================================================================================================
D3DXVECTOR3 * CItem::ReflectingVectorCalculation(D3DXVECTOR3 *outV, const D3DXVECTOR3 &ProgressV, const D3DXVECTOR3 &Normal)
{
	// 法線ベクトル変換用
	D3DXVECTOR3 NormalVector;
	// 法線ベクトルを正規化
	D3DXVec3Normalize(&NormalVector, &Normal);
	// 反射ベクトルを求める
	return D3DXVec3Normalize(outV, &(ProgressV - 2.0f * D3DXVec3Dot(&ProgressV, &NormalVector) * NormalVector));
}

// =====================================================================================================================================================================
//
// ランダム　アイテムの種類の範囲
//
// =====================================================================================================================================================================
CItem::ITEMTYPE CItem::ItemRandomRange(ITEMTYPE min, ITEMTYPE max)
{
	// 範囲でランダムに値を求め値を返す
	return (ITEMTYPE)GetRandRange(min, max);
}

// =====================================================================================================================================================================
//
// ランダム アイテムのレアリティの範囲
//
// =====================================================================================================================================================================
CItem::ITEM_RARITY CItem::RarityRandomRange(ITEM_RARITY min, ITEM_RARITY max)
{
	return (ITEM_RARITY)GetRandRange(min, max);
}

// =====================================================================================================================================================================
//
// アイテムをドロップする時のパターン
//
// =====================================================================================================================================================================
void CItem::DropPattern(bool fixed, ITEMTYPE type)
{
	// 確定しているならそのタイプを設定する
	if (fixed)
	{
		m_Type = type;
	}
	// 確定していないなら武器以外のタイプを設定する
	else
	{
		// タイプをランダムに設定
		m_Type = RandDropItem(ITEMDROP_SCO_CHA);
	}
}

// =====================================================================================================================================================================
//
// アイテムを複数一気にドロップさせる時 移動量,方向の設定
//
// =====================================================================================================================================================================
void CItem::DropPattern_Multiple(ITEM_LIST_DROPMULTIPLE list, ITEM_BEHAVIOR behavior,int nNum)
{
	switch (behavior)
	{
	case CItem::BEHAVIOR_NONE:
		break;

		// 自由落下
	case CItem::BEHAVIOR_FREEFALL:
		break;

		// 弾け飛ぶ
	case CItem::BEHAVIOR_BURSTS:

		// 左側から順に斜めに飛ばすnNum5回

		if (nNum == 0)
		{
			SetMove(D3DXVECTOR3(-2.5f, 5.0f, 0.0f));
		}
		if (nNum == 1)
		{
			SetMove(D3DXVECTOR3(-7.5f, 5.0f, 0.0f));
		}
		if (nNum == 2)
		{
			SetMove(D3DXVECTOR3(0.0f, 5.0f, 0.0f));
		}
		if (nNum == 3)
		{
			SetMove(D3DXVECTOR3(7.5f, 5.0f, 0.0f));
		}
		if (nNum == 4)
		{
			SetMove(D3DXVECTOR3(2.5f, 5.0f, 0.0f));
		}
		break;
	}
}

// =====================================================================================================================================================================
//
// デバッグ用アイテムコマンド
//
// =====================================================================================================================================================================
void CItem::DebugItemCommand(CKeyboard *key)
{
	//使い方説明
	CDebugProc::Print_Right("\n---------Debug ItemCommand----------\n");

	CDebugProc::Print_Right("[LShift] + テンキー [0] : ヘビーマシンガン\n");
	CDebugProc::Print_Right("[LShift] + テンキー [1] : ショットガン\n");
	CDebugProc::Print_Right("[LShift] + テンキー [2] : レーザーガン\n");
	CDebugProc::Print_Right("[LShift] + テンキー [3] : ロケットランチャー\n");
	CDebugProc::Print_Right("[LShift] + テンキー [4] : フレイムショット\n");
	CDebugProc::Print_Right("[LShift] + テンキー [5] : コイン\n");
	CDebugProc::Print_Right("[LShift] + テンキー [6] : BomUp\n");
	CDebugProc::Print_Right("[LShift] + テンキー [7] : BulletUp\n");
	CDebugProc::Print_Right("[LShift] + テンキー [ENTER] : BoxRand\n");

	//LShift押しながら
	if (key->GetKeyboardPress(DIK_LSHIFT))
	{
		// ヘビーマシンガンの生成
		if (key->GetKeyboardTrigger(DIK_NUMPAD0))
		{
			CItem::DebugCreate(ITEMTYPE_HEAVYMACHINEGUN);
		}
		// ショットガン生成
		else if (key->GetKeyboardTrigger(DIK_NUMPAD1))
		{
			CItem::DebugCreate(ITEMTYPE_SHOTGUN);
		}
		// レーザーガン生成
		else if (key->GetKeyboardTrigger(DIK_NUMPAD2))
		{
			CItem::DebugCreate(ITEMTYPE_LASERGUN);
		}
		// ロケットランチャー生成
		else if (key->GetKeyboardTrigger(DIK_NUMPAD3))
		{
			CItem::DebugCreate(ITEMTYPE_ROCKETLAUNCHER);
		}
		// フレイムショット生成
		else if (key->GetKeyboardTrigger(DIK_NUMPAD4))
		{
			CItem::DebugCreate(ITEMTYPE_FLAMESHOT);
		}
		// コインの生成
		else 	if (key->GetKeyboardTrigger(DIK_NUMPAD6))
		{
			CItem::DebugCreate(ITEMTYPE_GOLDCOIN);
		}
		// BomUp生成
		else if (key->GetKeyboardTrigger(DIK_NUMPAD9))
		{
			CItem::DebugCreate(ITEMTYPE_BOMBUP);
		}
		// BulletUp生成
		else if (key->GetKeyboardTrigger(DIK_NUMPADPLUS))
		{
			CItem::DebugCreate(ITEMTYPE_BULLETUP);
		}
		// boxramdテスト用
		else if (key->GetKeyboardTrigger(DIK_NUMPADENTER))
		{
			CItem::DropCreate_TEST();
		}
	}
}

// =====================================================================================================================================================================
//
// 静的変数の初期化 game終了時
//
// =====================================================================================================================================================================
void CItem::InitVariable()
{
	// コインのカウント加算用変数の初期化
	m_nAddCoin = 1;
	// 配列の全要素を削除
	m_nSaveHitItem.clear();
	m_nBoxRandRarityDataList.clear();
}

// =====================================================================================================================================================================
//
// // ドロップ率を元にアイテムがドロップするかを決めて結果を返す
//
// =====================================================================================================================================================================
bool CItem::DecideIfItemDrop(int nRate)
{
	// アイテムをドロップするかのフラグ
	bool bDrop = false;

	// 一旦
	if (GetRandRange(0, nRate) == 0)
	{
		bDrop = true;
	}

	return bDrop;
}

// =====================================================================================================================================================================
//
// デバッグ用アイテム生成
//
// =====================================================================================================================================================================
CItem * CItem::DebugCreate(ITEMTYPE type)
{
	// メモリの確保
	CItem * pItem = new CItem(OBJTYPE_ITEM);

	// 初期化
	pItem->Init();

	// サイズの設定
	pItem->SetSize(D3DXVECTOR3(
		m_ItemData.CollisionSize.x / 2,
		m_ItemData.CollisionSize.y / 2,
		m_ItemData.CollisionSize.z / 2));

	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer(TAG::PLAYER_1);

	if (pPlayer != nullptr)
	{
		D3DXVECTOR3 pos = pPlayer->GetPosition();
		// アイテムが生成される位置の調整
		pItem->SetDropPos(pos);

		// アイテムの位置の設定
		pItem->SetPosition(pos);

		pItem->m_Type = type;

		pItem->m_Behavior = BEHAVIOR_NONE;
	}

	// 種類別にテクスチャを設定
	pItem->SwitchTexture(pItem->m_Type, pItem);

	return pItem;
}

// =====================================================================================================================================================================
//
// レアリティの生成
//
// =====================================================================================================================================================================
void CItem::SetRarityList()
{
	// 各レアリティに該当するアイテムの設定
	CItem::m_nBoxRandDefaultRarityData = {
		{ ITEMTYPE_HEAVYMACHINEGUN, ITEMTYPE_ROCKETLAUNCHER },
		{ ITEMTYPE_LASERGUN },
		{ ITEMTYPE_SHOTGUN, ITEMTYPE_FLAMESHOT },
	};

	// 各レアリティの要素数を設定
	for (unsigned int Line = 0; Line < m_nBoxRandDefaultRarityData.size(); Line++)
	{
		m_ItemGachaData.BoxRandDefault_RarityNum[Line] = m_nBoxRandDefaultRarityData.at(Line).size();
	}

	// リストに情報を追加
	AddBoxRandList();
}

// =====================================================================================================================================================================
//
// 乱数リストの中から1つを選び結果を返す
//
// =====================================================================================================================================================================
CItem::ITEMTYPE CItem::ItemWhichOnePick(std::vector<std::vector<CItem::ITEMTYPE>> list ,int line)
{
	// リストのアイテムの一覧を保存する変数
	std::vector<ITEMTYPE> Pick;
	// 最終的にピックするアイテムの種類
	ITEMTYPE type;

	for (unsigned int Column = 0; Column < list.at(line).size(); Column++)
	{
		// リストからアイテム情報の一覧を取得
		Pick.emplace_back(list.at(line).at(Column));
	}

	std::random_device get_rand_dev;
	std::mt19937 get_rand_mt(get_rand_dev()); // seedに乱数を指定
	std::shuffle(Pick.begin(), Pick.end(), get_rand_mt);

	type = Pick.back();

	return type;
}

// =====================================================================================================================================================================
//
// アイテムのデータの読み込み
//
// =====================================================================================================================================================================
void CItem::ItemLoad()
{
	// ファイルポイント
	FILE *pFile;

	char cReadText[128];			// 文字として読み取る
	char cHeadText[128];			// 比較用
	char cDie[128];					// 不要な文字

	// ファイルを開く
	pFile = fopen(m_ItemFileName, "r");

	// 開いているとき
	if (pFile != NULL)
	{
		// SCRIPTが来るまでループ
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
			sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入
		}

		// SCRIPTが来たら
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			// END_SCRIPTが来るまでループ
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
				sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入

				// 1つ目のファイルだった時
				if (strcmp(cHeadText, "ITEMSET") == 0)
				{
					// END_ITEMSETが来るまでループ
					while (strcmp(cHeadText, "END_ITEMSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
						sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入

																	// SPEEDが来たら
						if (strcmp(cHeadText, "RATE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ItemData.nDropRate);		// 比較用テキストにRATEを代入
						}
						// LIFEが来たら
						else if (strcmp(cHeadText, "DELETE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ItemData.nDeleteTime);	// 比較用テキストにDELETEを代入
						}
						// FLASHが来たら
						else if (strcmp(cHeadText, "FLASH") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ItemData.nFlashTime);	// 比較用テキストにFLASHを代入
						}
						// COLLISIONSIZEが来たら
						else if (strcmp(cHeadText, "COLLISIONSIZE") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
								&m_ItemData.CollisionSize.x,
								&m_ItemData.CollisionSize.y,
								&m_ItemData.CollisionSize.z);										// 比較用テキストにCOLLISIONSIZEを代入
						}
						else if (strcmp(cHeadText, "END_ITEMSET") == 0)
						{
						}
					}
				}
			}
		}

		// レアリティリストの設定
		SetRarityList();

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		MessageBox(NULL, "アイテムのデータ読み込み失敗", "警告", MB_ICONWARNING);
	}
}

// =====================================================================================================================================================================
//
// キャラクターがアイテムを落とすときの生成処理 確定しないならtypeにNONEを入れる
//
// =====================================================================================================================================================================
CItem * CItem::DropItem(D3DXVECTOR3 droppos, bool fixed,ITEMTYPE type)
{
	// メモリの確保
	CItem *pItem = new CItem(OBJTYPE_ITEM);

	// 初期化
	pItem->Init();

	// サイズの設定
	pItem->SetSize(D3DXVECTOR3(
		m_ItemData.CollisionSize.x /2,
		m_ItemData.CollisionSize.y /2,
		m_ItemData.CollisionSize.z /2));

	// アイテムが生成される位置の調整
	//pItem->SetDropPos(droppos);

	droppos.y += 30.0f;

	// アイテムの位置の設定
	pItem->SetPosition(droppos);

	pItem->m_Behavior = BEHAVIOR_NONE;

	// アイテムのドロップをパターンごとに変える
	pItem->DropPattern(fixed, type);

	// 種類別にテクスチャを設定
	pItem->SwitchTexture(pItem->m_Type, pItem);

	return pItem;
}

// =====================================================================================================================================================================
//
// アイテムを複数一気にドロップさせる時
//
// =====================================================================================================================================================================
void CItem::DropItem_Multiple(const D3DXVECTOR3 originpos, ITEM_LIST_DROPMULTIPLE type, ITEM_BEHAVIOR behavior)
{
	// 生成する数分
	for (int nNum = 0; nNum < MULTIPLE_ITEM_NUM; nNum++)
	{
		// メモリの確保
		CItem *pItem = new CItem(OBJTYPE_ITEM);

		// 初期化
		pItem->Init();

		// サイズの設定
		pItem->SetSize(D3DXVECTOR3(
			m_ItemData.CollisionSize.x / 2,
			m_ItemData.CollisionSize.y / 2,
			m_ItemData.CollisionSize.z / 2));

		// 木から落ちるアイテムだけ
		if (behavior == BEHAVIOR_FREEFALL)
		{
			pItem->SetPosition(pItem->RandomDropPosX(originpos, 100));
			//pItem->SetPosition(originpos);
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
		pItem->m_Behavior = behavior;
		// 複数体のタイプ設定
		pItem->SetMultiType(type);
		// アイテムの挙動と種類の設定
		pItem->DropPattern_Multiple(type, behavior, nNum);
	}
}

// =====================================================================================================================================================================
//
// デバッグ用アイテム生成
//
// =====================================================================================================================================================================
CItem * CItem::DropCreate_TEST()
{
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer((TAG)(0));
	D3DXVECTOR3 pos = pPlayer->GetPosition();

	// 変数
	CItem *pItem;

	// メモリの確保
	pItem = new CItem(OBJTYPE_ITEM);

	// 初期化
	pItem->Init();

	// サイズの設定
	pItem->SetSize(D3DXVECTOR3(
		m_ItemData.CollisionSize.x / 2,
		m_ItemData.CollisionSize.y / 2,
		m_ItemData.CollisionSize.z / 2));

	// アイテムが生成される位置の調整
	pItem->SetDropPos(pos);
	// アイテムの位置の設定
	pItem->SetPosition(pos);
	// ボックスランドでアイテムを選出する
	pItem->m_Type = pItem->BoxRand();
	// 種類別にテクスチャを設定
	pItem->SwitchTexture(pItem->m_Type, pItem);

	return pItem;
}

// =====================================================================================================================================================================
//
// 種類別テクスチャバインド処理
//
// =====================================================================================================================================================================
void CItem::SwitchTexture(ITEMTYPE type, CItem *pItem)
{
	switch (type)
	{
	case CItem::ITEMTYPE_HEAVYMACHINEGUN:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_HEAVYMACHINEGUN));
		break;
	case CItem::ITEMTYPE_SHOTGUN:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_SHOTGUN));
		break;
	case CItem::ITEMTYPE_LASERGUN:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_LASERGUN));
		break;
	case CItem::ITEMTYPE_ROCKETLAUNCHER:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_ROCKETLAUNCHER));
		break;
	case CItem::ITEMTYPE_FLAMESHOT:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_FLAMESHOT));
		break;
	case CItem::ITEMTYPE_GOLDCOIN:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_GOLDCOIN));
		break;
	case CItem::ITEMTYPE_SILVERCOIN:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_SILVERCOIN));
		break;
	case CItem::ITEMTYPE_BRONZESCOIN:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BRONZESCOIN));
		break;
	case CItem::ITEMTYPE_DIAMOND:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_DIAMOND));
		break;
	case CItem::ITEMTYPE_BEAR:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BEAR));
		break;
	case CItem::ITEMTYPE_LETTER:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_LETTER));
		break;
	case CItem::ITEMTYPE_APPLE:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_APPLE));
		break;
	case CItem::ITEMTYPE_MELON:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_MELON));
		break;
	case CItem::ITEMTYPE_BANANA:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BANANA));
		break;
	case CItem::ITEMTYPE_MEAT:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_MEAT));
		break;
	case CItem::ITEMTYPE_RICEBALL:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_RICEBALL));
		break;
	case CItem::ITEMTYPE_CANDY:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_CANDY));
		break;
	case CItem::ITEMTYPE_DONUT:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_DONUT));
		break;
	case CItem::ITEMTYPE_LOLIPOP:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_LOLIPOP));
		break;
	case CItem::ITEMTYPE_BREAD:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BREAD));
		break;
	case CItem::ITEMTYPE_CHOCOLATE:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_CHOCOLATE));
		break;
	case CItem::ITEMTYPE_ICE:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_ICE));
		break;
	case CItem::ITEMTYPE_BOMBUP:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BOMBUP));
		break;
	case CItem::ITEMTYPE_BULLETUP:
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BULLETUP));
		break;
	}
}

// =====================================================================================================================================================================
//
// ドロップするアイテムのランダム処理
//
// =====================================================================================================================================================================
CItem::ITEMTYPE CItem::RandDropItem(ITEMDROP drop)
{
	switch (drop)
	{
	case CItem::ITEMDROP_WEAPON:
		return m_Type = ItemRandomRange(ITEMTYPE_HEAVYMACHINEGUN, ITEMTYPE_FLAMESHOT);
		break;
	case CItem::ITEMDROP_SCORE:
		return m_Type = ItemRandomRange(ITEMTYPE_BEAR, ITEMTYPE_ICE);
		break;
	case CItem::ITEMDROP_CHARGE:
		return m_Type = ItemRandomRange(ITEMTYPE_BOMBUP, ITEMTYPE_BULLETUP);
		break;
	case CItem::ITEMDROP_SCO_CHA:
		return m_Type = ItemRandomRange(ITEMTYPE_BEAR, ITEMTYPE_BULLETUP);
		break;
	case CItem::ITEMDROP_FRUIT:
		return m_Type = ItemRandomRange(ITEMTYPE_APPLE, ITEMTYPE_BANANA);
		break;
	case CItem::ITEMDROP_COIN:
		return m_Type = ItemRandomRange(ITEMTYPE_GOLDCOIN, ITEMTYPE_BRONZESCOIN);
		break;
	case CItem::ITEMDROP_RARE:
		return m_Type = ItemRandomRange(ITEMTYPE_GOLDCOIN, ITEMTYPE_LETTER);
		break;
	case CItem::ITEMDROP_FOOD:
		return m_Type = ItemRandomRange(ITEMTYPE_MEAT, ITEMTYPE_ICE);
		break;
	case CItem::ITEMDROP_ALL:
		return m_Type = ItemRandomRange(ITEMTYPE_HEAVYMACHINEGUN, ITEMTYPE_BULLETUP);
		break;
	}

	return ITEMTYPE_NONE;
}

// =====================================================================================================================================================================
//
// アイテムをドロップする確率を求める
//
// =====================================================================================================================================================================
bool CItem::DropRate()
{
	// ランダムにドロップするかを求める
	return DecideIfItemDrop(m_ItemData.nDropRate);
}
