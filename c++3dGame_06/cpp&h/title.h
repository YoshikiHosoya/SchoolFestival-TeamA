// ------------------------------------------
//
// タイトルヘッダー処理 [title.h]
// Author : Fujiwara Masato
//
// ------------------------------------------
#ifndef _TITLE_H_
#define _TITLE_H_

#define _CRT_SECURE_NO_WARNINGS

// ------------------------------------------
//
// インクルードファイル
//
// ------------------------------------------
#include "main.h"

// ------------------------------------------
//
// マクロ定義
//
// ------------------------------------------
//#define ONEMIN (60)

// ------------------------------------------
//
// 前方宣言
//
// ------------------------------------------
class CTitle_ui;
class CTitleEnemy;
class CLightEffect;
class CTelop;
// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class CTitle
{
public:
	/* 列挙型 */
	typedef enum
	{
		/* タイトルプレイ中には出現しないUI */
		TITLEMODE_TITLE = 0,				// タイトル表示モード
		TITLEMODE_TUTORIAL,					// チュートリアルモード
		TITLEMODE_FREE,						// 自由に行動可能
		TITLEMODE_MAX
	} TITLEMODE;

	/* 関数 */
	CTitle();
	~CTitle();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void CreateTitleObj(void);				//タイトルで使うオブジェクトの生成

	void SetMode(void);						//タイトルのモード設定
	void Mode(void);						//タイトルモードごとの処理
	TITLEMODE GetMode(void);				//タイトルの現在のモード取得
	void SetEnterflag(void);
	bool GetEnterflag(void);

protected:
private:
	TITLEMODE	m_Mode;						//タイトルのモード
	static CTitle_ui * m_pTitle_ui;			//タイトルの変数
	static CTitleEnemy *m_pTitleEnemy;		//タイトル用の敵
	static CLightEffect *m_pLightEffect;	//ライトの変数
	static CTelop *m_pTelop;				//テロップに変数
	static bool m_bFlag;					//一度だけ処理を通すようのフラグ
	static bool m_bStartFlag;				//一度だけ処理を通すようのフラグ
	static bool m_bTelopFlag;				//一度だけ処理を通すようのフラグ
	int			m_CreateCnt;				//生成されるまでのカウント
	bool		m_Enterflag;				//エンターを押したらtrueになるフラグ
	int			m_PhaseCount;				//次の段階へ行くまでのクールタイム
	bool		m_Phaseflag;				//一回目だけ処理を通すフラグ
};
#endif
