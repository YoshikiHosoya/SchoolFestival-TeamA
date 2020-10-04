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

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CItem::CItem()
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

	// 重力の初期値
	m_fGravity = 1.0f;

	// 当たり判定生成
	m_pCollision = CCollision::Create();

	return S_OK;
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CItem::Uninit(void)
{
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

	//// レイの判定に一回でも触れていた時
	//if (m_nHitRayCount >= 1)
	//{
	//	// アイテムの滞在時間管理
	//	RemainTimer();
	//}
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CItem::Draw(void)
{
}

// =====================================================================================================================================================================
//
// アイテムの挙動の種類ごとの種類
//
// =====================================================================================================================================================================
void CItem::BehaviorType(D3DXVECTOR3 & pos)
{
	// 挙動が弾け飛ぶ状態だった時
	if (m_Behavior == BEHAVIOR_FULLBURSTS)
	{
		pos += m_Move * 8.0f;
	}
	// 挙動が弾け飛ぶ状態だった時
	else if (m_Behavior == BEHAVIOR_BURSTS)
	{
		pos += m_Move * 5.0f;
	}
	// それ以外
	else
	{
		pos += m_Move * 1.5f;
	}
}



// =====================================================================================================================================================================
//
// アイテム取得時の種類別処理
//
// =====================================================================================================================================================================
void CItem::ItemAcquisition(ITEMTYPE type, TAG Tag)
{
	// アイテム取得時の光
	m_pPlayer[(int)Tag]->SetState(CCharacter::CHARACTER_STATE_ITEMGET_FLASH);
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
	DropPos.x = (float)GetRandRange((int)originpos.x - radius, (int)originpos.x + radius);
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
		this->SwitchTexture(this->RandDropItem(ITEMDROP_FRUIT));
		break;

	case CItem::LIST_FOOD:
		// 食べ物のみ
		this->SwitchTexture(this->RandDropItem(ITEMDROP_FOOD));
		break;

	case CItem::LIST_COIN:
		// コインのみ
		this->SwitchTexture(this->RandDropItem(ITEMDROP_COIN));
		break;

	case CItem::LIST_WEAPON:
		// コインのみ
		this->SwitchTexture(this->RandDropItem(ITEMDROP_WEAPON));
		break;

	case CItem::LIST_RARE:
		// レアなアイテムのみ
		this->SwitchTexture(this->RandDropItem(ITEMDROP_RARE));
		break;



	case CItem::LIST_ANI_NORMAL:
		// レアなアイテムのみ
		this->SwitchTexture(this->RandDropItem(ITEMDROP_ANI_NORMAL));
		break;

	case CItem::LIST_ANI_RARE:
		// レアなアイテムのみ
		this->SwitchTexture(this->RandDropItem(ITEMDROP_ANI_RARE));
		break;

	case CItem::LIST_ANI_MONKEY:
		// レアなアイテムのみ
		this->SwitchTexture(this->RandDropItem(ITEMDROP_ANI_MONKEY));
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
}

// =====================================================================================================================================================================
//
// 反射処理
//
// =====================================================================================================================================================================
void CItem::ReflectionItem()
{
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

		// 弾け飛ぶ
	case CItem::BEHAVIOR_FULLBURSTS:
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
		if (nNum == 5)
		{
			SetMove(D3DXVECTOR3(-2.5f, -5.0f, 0.0f));
		}
		if (nNum == 6)
		{
			SetMove(D3DXVECTOR3(-7.5f, -5.0f, 0.0f));
		}
		if (nNum == 7)
		{
			SetMove(D3DXVECTOR3(0.0f, -5.0f, 0.0f));
		}
		if (nNum == 8)
		{
			SetMove(D3DXVECTOR3(7.5f, -5.0f, 0.0f));
		}
		if (nNum == 9)
		{
			SetMove(D3DXVECTOR3(2.5f, -5.0f, 0.0f));
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
		//
		else if (key->GetKeyboardTrigger(DIK_NUMPAD5))
		{
			//CItem::DebugCreate(ITEMTYPE_BEAR_2);
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
	//CItem * pItem = new CItem(OBJTYPE_ITEM);

	//// 初期化
	//pItem->Init();

	//// サイズの設定
	//pItem->SetSize(D3DXVECTOR3(
	//	m_ItemData.CollisionSize.x / 2,
	//	m_ItemData.CollisionSize.y / 2,
	//	m_ItemData.CollisionSize.z / 2));

	//CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer(TAG::PLAYER_1);

	//if (pPlayer != nullptr)
	//{
	//	D3DXVECTOR3 pos = pPlayer->GetPosition();
	//	// アイテムが生成される位置の調整
	//	pItem->SetDropPos(pos);

	//	// アイテムの位置の設定
	//	pItem->SetPosition(pos);

	//	pItem->m_Type = type;

	//	pItem->m_Behavior = BEHAVIOR_NONE;
	//}

	//// 種類別にテクスチャを設定
	//pItem->SwitchTexture(pItem->m_Type, pItem);

	return nullptr;
}

// =====================================================================================================================================================================
//
// レアリティの生成
//
// =====================================================================================================================================================================
void CItem::SetRarityList()
{
	// --- 武器のみ --- //
	//// 各レアリティに該当するアイテムの設定
	//CItem::m_nBoxRandDefaultRarityData = {
	//	{ ITEMTYPE_HEAVYMACHINEGUN, ITEMTYPE_ROCKETLAUNCHER },	// ★のアイテムリスト
	//	{ ITEMTYPE_LASERGUN },									// ★★のアイテムリスト
	//	{ ITEMTYPE_SHOTGUN, ITEMTYPE_FLAMESHOT },				// ★★★のアイテムリスト
	//};

	// --- ボスマップで使う方 --- //
	// 各レアリティに該当するアイテムの設定
	CItem::m_nBoxRandDefaultRarityData = {
		{ ITEMTYPE_HEAVYMACHINEGUN, ITEMTYPE_ROCKETLAUNCHER },	// ★のアイテムリスト
		{ ITEMTYPE_LASERGUN },									// ★★のアイテムリスト
		{ ITEMTYPE_SHOTGUN, ITEMTYPE_FLAMESHOT },				// ★★★のアイテムリスト
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
// デバッグ用アイテム生成
//
// =====================================================================================================================================================================
CItem * CItem::DropCreate_TEST()
{
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer((TAG)(0));
	D3DXVECTOR3 pos = pPlayer->GetPosition();

	// 変数
	//CItem *pItem;

	// メモリの確保
	//pItem = new CItem(OBJTYPE_ITEM);

	//// 初期化
	//pItem->Init();

	//// サイズの設定
	//pItem->SetSize(D3DXVECTOR3(
	//	m_ItemData.CollisionSize.x / 2,
	//	m_ItemData.CollisionSize.y / 2,
	//	m_ItemData.CollisionSize.z / 2));

	//// アイテムが生成される位置の調整
	//pItem->SetDropPos(pos);
	//// アイテムの位置の設定
	//pItem->SetPosition(pos);
	//// ボックスランドでアイテムを選出する
	//pItem->m_Type = pItem->BoxRand();
	//// 種類別にテクスチャを設定
	//pItem->SwitchTexture(pItem->m_Type, pItem);

	return nullptr;
}

// =====================================================================================================================================================================
//
// ランダムに武器のアイテムのタイプを返す
//
// =====================================================================================================================================================================
CItem::ITEMTYPE CItem::RandomWeapon()
{
	return 	ItemRandomRange(ITEMTYPE_HEAVYMACHINEGUN, ITEMTYPE_FLAMESHOT);
}

// =====================================================================================================================================================================
//
// 種類別テクスチャバインド処理
//
// =====================================================================================================================================================================
void CItem::SwitchTexture(ITEMTYPE type)
{
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

		// --- アニメーションするアイテム --- //
	case CItem::ITEMDROP_ANI_NORMAL:
		return m_Type = ItemRandomRange(ANIM_ITEMTYPE_ROASTCHICKEN, ANIM_ITEMTYPE_MEDAL2);
		break;
	case CItem::ITEMDROP_ANI_RARE:
		return m_Type = ItemRandomRange(ANIM_ITEMTYPE_COIN, ANIM_ITEMTYPE_PRISONER);
		break;
	case CItem::ITEMDROP_ANI_MONKEY:
		return m_Type = ItemRandomRange(ANIM_ITEMTYPE_DANCEMONKEY, ANIM_ITEMTYPE_PRISONER);
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
