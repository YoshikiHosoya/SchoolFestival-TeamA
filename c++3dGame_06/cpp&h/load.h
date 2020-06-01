//=============================================================================
//
// ロード情報処理 [load.h]
// Author : Fujiwara Masato
//
//=============================================================================
#ifndef _LOAD_H_
#define _LOAD_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// 前方宣言
//=============================================================================

//=============================================================================
// 構造体
//=============================================================================
// マテリアル情報
typedef struct
{
	int nType;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
} MATERIAL_INFO;

// ビルボード情報
typedef struct
{
	int nType;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 size;
} BILLBOARD_INFO;

// メッシュ情報
typedef struct
{
	int nType;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	int			nBlockDipth;
	int			nBlockWidth;
	float		fSizeX;
	float		fSizeZ;
} MESH_INFO;

//=============================================================================
// クラス
//=============================================================================
class CLoad
{
public:
	/* 構造体 */
	// 情報
	typedef struct
	{
		int nType;
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		D3DXCOLOR	col;
		D3DXVECTOR3	size;
		int			nBlockDipth;
		int			nBlockWidth;
	} INFO;

	/* 関数 */
	CLoad();
	~CLoad();
	// 情報取得
	// 読み込み
	// 開放
	void Unload(void);
	// 読み込み
	int Load(
		const char* filename		// ファイル名
	);
	// 取得
	INFO &GetInfo(int nID);			// 情報
	int &GetShard(void);				// ジャンプ
protected:
private:
	INFO info[1500];					// 情報
	//
	int m_nMax3DItem;					// 3Dアイテムの総数
};

#endif
