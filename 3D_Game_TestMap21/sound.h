// =====================================================================================================================================================================
//
// サウンド処理 [sound.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

// =====================================================================================================================================================================
// 前方宣言	( ポインタだけなら使える )
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// サウンドクラス
// =====================================================================================================================================================================
class CSound
{
public:

// =====================================================================================================================================================================
// パラメータ構造体定義
// =====================================================================================================================================================================
typedef struct
{
	char *pFilename;	// ファイル名
	int nCntLoop;		// ループカウント
} SOUNDPARAM;

	// サウンドファイル
	typedef enum
	{
		SOUND_LABEL_BGM_TITLE = 0,	// タイトル
		SOUND_LABEL_BGM_GAME,		// メイン
		SOUND_LABEL_BGM_OVER,		// ゲームオーバー
		SOUND_LABEL_BGM_RANK,		// ランキング
		SOUND_LABEL_SE_JUMP,		// ジャンプ
		SOUND_LABEL_SE_LAND,		// 着地
		SOUND_LABEL_SE_ITEM,		// アイテム
		SOUND_LABEL_SE_HEAL,		// 回復
		SOUND_LABEL_SE_DEATH,		// 死
		SOUND_LABEL_SE_GAYSER,		// 間欠泉
		SOUND_LABEL_SE_ENTER,		// 決定
		SOUND_LABEL_SE_GAGE,		// ゲージ
		SOUND_LABEL_SE_CHANGE,		// 切替え
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	CSound();												// コンストラクタ
	~CSound();												// デストラクタ

	/* メンバ関数 */
	HRESULT				Init(HWND hWnd);					// 初期化
	void				Uninit();							// 終了

	/* 静的メンバ関数 */

	/* メンバ関数 */
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

private:
	/* 静的メンバ変数 */

	/* メンバ関数 */
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	// メンバ変数
	IXAudio2				*m_pXAudio2							= NULL;				// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice	*m_pMasteringVoice					= NULL;				// マスターボイス
	IXAudio2SourceVoice		*m_apSourceVoice[SOUND_LABEL_MAX]	= {};				// ソースボイス
	BYTE					*m_apDataAudio[SOUND_LABEL_MAX]		= {};				// オーディオデータ
	DWORD					m_aSizeAudio[SOUND_LABEL_MAX]		= {};				// オーディオデータサイズ

	// 各音素材のパラメータ
	SOUNDPARAM m_aParam[SOUND_LABEL_MAX] =
	{
		{ "data/SOUND/BGM/title.wav", -1 },				// タイトル
		{ "data/SOUND/BGM/game.wav", -1 },				// メイン
		{ "data/SOUND/BGM/clear.wav", -1 },				// ゲームオーバー
		{ "data/SOUND/BGM/rank.wav", -1 },				// ランキング
		{ "data/SOUND/SE/jump.wav", 0 },				// ジャンプ
		{ "data/SOUND/SE/land.wav", 0 },				// 着地
		{ "data/SOUND/SE/item.wav", 0 },				// アイテム
		{ "data/SOUND/SE/heal.wav", 0 },				// 回復
		{ "data/SOUND/SE/death.wav", 0 },				// 死
		{ "data/SOUND/SE/gayser.wav", 0 },				// 間欠泉
		{ "data/SOUND/SE/enter.wav", 0 },				// 決定
		{ "data/SOUND/SE/gage.wav", 0 },				// ゲージ
		{ "data/SOUND/SE/change.wav", 0 },				// 切替え
	};

};
#endif