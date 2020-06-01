// ----------------------------------------
//
// サウンド処理の説明[sound.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _SOUND_H_
#define _SOUND_H_	 // ファイル名を基準を決める

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
#include "main.h"

// ----------------------------------------
//
// マクロ定義
//
// ----------------------------------------
#define MAX_SOUND (10)

// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class CSound
{
public:
	/* 列挙型 */
	// ラベル
	typedef enum
	{
		LABEL_BGM_TITLE,		// タイトル
		LABEL_BGM_GAME,			// ゲーム
		LABEL_BGM_RUN,			// 走る
		LABEL_BGM_BREATH,		// 息切れ
		LABEL_BGM_RESULT,		// リザルト
		LABEL_SE_7,				// コイン
		LABEL_MAX,
	} LABEL;
	/* 関数 */
	CSound();
	~CSound();
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(LABEL label);
	void StopSound(LABEL label);
	void StopSound(void);
protected:

private:
	/* 関数 */
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	/* 変数 */
	static char m_pFilename[LABEL_MAX][64];					// ファイル名
	static int m_nCntLoop[LABEL_MAX];						// ループカウント
	static IXAudio2 *m_pXAudio2;							// XAudio2オブジェクトへのインターフェイス
	static IXAudio2MasteringVoice *m_pMasteringVoice;		// マスターボイス
	static IXAudio2SourceVoice *m_apSourceVoice[LABEL_MAX];	// ソースボイス
	static BYTE *m_apDataAudio[LABEL_MAX];					// オーディオデータ
	static DWORD m_aSizeAudio[LABEL_MAX];					// オーディオデータサイズ
};

#endif