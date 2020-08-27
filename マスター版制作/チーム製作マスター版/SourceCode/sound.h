//------------------------------------------------------------------------------
//
// サウンド処理 [sound.h]
// Author : Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _SOUND_H_
#define _SOUND_H_

#define _CRT_SECURE_NO_WARNINGS

//-----------------------------------------------------------------------------
// インクルードファイル
//-----------------------------------------------------------------------------
#include "main.h"
#include "xaudio2.h"


class CSound
{
public:

	// サウンドファイル
	typedef enum
	{
		LABEL_BGM_TITLE = 0,						//タイトル
		LABEL_BGM_TUTORIAL,							//チュートリアル
		LABEL_BGM_STAGE_01,							//ステージ1
		LABEL_BGM_STAGE_02,							//ステージ2
		LABEL_BGM_STAGE_01_BOSS,					//ステージ1ボス
		LABEL_BGM_STAGE_02_BOSS,					//ステージ2ボス
		LABEL_BGM_RANKING,							//ランキング

		//キャラクターアクション
		LABEL_SE_WALK,								//歩く
		LABEL_SE_JUMP,								//ジャンプ
		LABEL_SE_LANDING,							//着地

		//エフェクト
		LABEL_SE_EXPLOSION_00,						//爆発
		LABEL_SE_EXPLOSION_01,						//爆発
		LABEL_SE_EXPLOSION_02,						//爆発
		LABEL_SE_EXPLOSION_03,						//爆発
		LABEL_SE_EXPLOSION_04,						//爆発

		//武器関連
		LABEL_SE_SHOT_HANDGUN,						//ハンドガン
		LABEL_SE_SHOT_MACHINEGUN,					//マシンガン
		LABEL_SE_SHOT_LAUNCHER,						//ランチャー
		LABEL_SE_SHOT_SHOTGUN,						//ショットガン
		LABEL_SE_SHOT_LASER,						//レーザー
		LABEL_SE_SHOT_FIRE,							//ファイア
		LABEL_SE_SHOT_BOSSLASER,					//レーザー
		LABEL_SE_SHOT_CHARGE,						//チャージ
		LABEL_SE_SHOT_FLASHING,						//光るやつ

		//環境音とか
		LABEL_SE_DECISION,							//決定
		LABEL_SE_CANCEL,							//キャンセル
		LABEL_SE_SELECT,							//選択
		LABEL_SE_PAUSE,								//ポーズ
		LABEL_SE_GAMEOVER,							//ゲームオーバー
		LABEL_SE_GAMECLEAR,							//ゲームクリア

		//ゲーム内効果音
		LABEL_SE_GET_WEAPON,						//武器取得
		LABEL_SE_GET_SCORE_ITEM,					//スコアアイテム取得
		LABEL_SE_ADD_SCORE00,						//リザルト時のスコア加算
		LABEL_SE_ADD_SCORE01,						//リザルト時のスコア加算
		LABEL_SE_ADD_SCORE_BONUS,					//リザルト時のスコア加算
		LABEL_SE_BULLET_HIT,						//ナイフダメージ
		LABEL_SE_KNIFE_HIT,							//弾ダメージ

		//武器系アイテム取得時のボイス
		LABEL_SE_VOICE_HEAVYMACHINEGUN,				//ヘビーマシンガン
		LABEL_SE_VOICE_DEATH,						//死亡時　ｳﾜｰ


		LABEL_MAX,
	} LABEL;

	HRESULT Init(HWND hWnd);
	void Uninit(void);

	HRESULT Play(LABEL label);
	void Stop(LABEL label);
	void StopAll(void);

	void SetMute(bool bMute)	{ m_bMute = bMute; };
	bool GetMute()				{ return m_bMute; };

private:

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[LABEL_MAX] = {};	// ソースボイス
	BYTE *m_apDataAudio[LABEL_MAX] = {};					// オーディオデータ
	DWORD m_aSizeAudio[LABEL_MAX] = {};						// オーディオデータサイズ

	bool m_bMute;											//ミュート

	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} SOUNDPARAM;

	// 各音素材のパラメータ
	SOUNDPARAM m_aParam[LABEL_MAX] =
	{
		{ "data/BGM/title.wav", -1 },								//BGM
		{ "data/BGM/tutorial.wav", -1 },							//BGM
		{ "data/BGM/stage_01.wav", -1 },							//BGM
		{ "data/BGM/stage_02.wav", -1 },							//BGM
		{ "data/BGM/stage_01_boss.wav", -1 },						//BGM
		{ "data/BGM/stage_02_boss.wav", -1 },						//BGM
		{ "data/BGM/ranking.wav", -1 },								//BGM

		//キャラクターアクション
		{ "data/SE/CharacterAction/walking.wav", 0 },				//SE 歩く
		{ "data/SE/CharacterAction/jump.wav", 0 },					//SE ジャンプ
		{ "data/SE/CharacterAction/landing.wav", 0 },				//SE 着地

		//エフェクト
		{ "data/SE/Effect/explosion_00.wav", 0 },					//SE 爆発
		{ "data/SE/Effect/explosion_01.wav", 0 },					//SE 爆発
		{ "data/SE/Effect/explosion_02.wav", 0 },					//SE 爆発
		{ "data/SE/Effect/explosion_03.wav", 0 },					//SE 爆発
		{ "data/SE/Effect/explosion_04.wav", 0 },					//SE 爆発

		//武器
		{ "data/SE/Weapon/handgun.wav", 0 },						//SE ハンドガン
		{ "data/SE/Weapon/machinegun.wav", 0 },						//SE マシンガン
		{ "data/SE/Weapon/launcher.wav", 0 },						//SE ランチャー
		{ "data/SE/Weapon/shotgun.wav", 0 },						//SE ショットガン
		{ "data/SE/Weapon/laser.wav", 0 },							//SE レーザー
		{ "data/SE/Weapon/Fire.wav", 0 },							//SE ファイア
		{ "data/SE/Weapon/boss_laser.wav", 0 },						//SE ボスレーザー
		{ "data/SE/Weapon/boss_charge.wav", 0 },					//SE チャージ
		{ "data/SE/Weapon/boss_flashing.wav", 0 },					//SE 何か光るやつ

		//環境音
		{ "data/SE/System/decision.wav", 0 },						//SE 決定
		{ "data/SE/System/cancel.wav", 0 },							//SE キャンセル
		{ "data/SE/System/select.wav", 0 },							//SE 選択
		{ "data/SE/System/pause.wav", 0 },							//SE ポーズ
		{ "data/SE/System/gameover.wav", 0 },						//SE ゲームオーバー
		{ "data/SE/System/stage_clear.wav", 0 },					//SE ステージクリア

		//ゲーム効果音
		{ "data/SE/Game/getweapon.wav", 0 },						//SE 武器取得
		{ "data/SE/Game/getscore.wav", 0 },							//SE スコアアイテム取得
		{ "data/SE/Game/score_00.wav", 0 },							//SE リザルト時のスコア加算
		{ "data/SE/Game/score_01.wav", 0 },							//SE リザルト時のスコア加算
		{ "data/SE/Game/score_bonus.wav", 0 },						//SE リザルト時のスコア加算
		{ "data/SE/Game/hit_bullet.wav", 0 },						//SE 弾ダメージ
		{ "data/SE/Game/hit_knife.wav", 0 },						//SE ナイフダメージ

		//武器系アイテム取得時
		{ "data/SE/Voice/HeavyMachineGun.wav", 0 },				//SE HMG
		{ "data/SE/Voice/Death.wav", 0 },						//SE 死亡ボイス

	};

};


#endif
