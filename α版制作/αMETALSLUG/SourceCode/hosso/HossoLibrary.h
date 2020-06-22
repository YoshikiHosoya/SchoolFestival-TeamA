//------------------------------------------------------------------------------
//
//ライブラリ処理  [hossolibrary.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _HOSSOLIBRARY_H_
#define _HOSSOLIBRARY_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "../../main.h"
//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define ZeroVector4			(D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f))		//初期化用
#define ZeroVector3			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))				//初期化用
#define ZeroVector2			(D3DXVECTOR2(0.0f, 0.0f))					//初期化用
#define ZeroColor			(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f))			//透明
#define WhiteColor			(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))			//白
#define RedColor			(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f))			//赤
#define GreenColor			(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f))			//緑
#define BlueColor			(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f))			//青
#define YellowColor			(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))			//黄
#define OrangeColor			(D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f))			//橙
#define BlackColor			(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f))			//黒

#define MAX_TEXT			(128)
#define SCREEN_CENTER_POS	(D3DXVECTOR3(SCREEN_WIDTH * 0.5f , SCREEN_HEIGHT * 0.5f ,0.0f))			//画面中央の座標
#define SCREEN_SIZE			(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT,0.0f))							//画面のサイズ
#define NEWLINE				("\n")																	//改行
#define COMMENT01			("//\n")																//テキスト用　コメント　改行
#define COMMENT02			("//------------------------------------------------------------\n")	//テキスト用　線
#define EQUAL				("=")																	//テキスト用　イコール

//------------------------------------------------------------------------------
//構造体定義
//------------------------------------------------------------------------------
//int型を二つ格納できる
typedef struct INTEGER2
{
	int x;
	int y;

	//コンストラクタ
	INTEGER2()
	{
		//引数で数値が入ってこなかったら0
		x = 0;
		y = 0;
	};
	INTEGER2(int nX, int nY)
	{
		//引数通りの数値
		x = nX;
		y = nY;
	};
}INTEGER2;

//int型を3つ格納できる
typedef struct INTEGER3
{
	int x;
	int y;
	int z;

	//コンストラクタ
	INTEGER3()
	{
		//引数で数値が入ってこなかったら0
		x = 0;
		y = 0;
		z = 0;
	};
	INTEGER3(int nX, int nY,int nZ)
	{
		//引数通りの数値
		x = nX;
		y = nY;
		z = nZ;
	};
}INTEGER3;


//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CHossoLibrary
{
public:
	static float Vec2Cross(D3DXVECTOR2 const &rVecA, D3DXVECTOR2 const &rVecB);									//2D 外積計算
	static void CalcMatrix(D3DXMATRIX *pMtx,D3DXVECTOR3 const &rPos, D3DXVECTOR3 const &rRot);					//ワールドマトリックス計算
	static void SetBillboard(D3DXMATRIX *pMtx);																	//ビルボード設定
	static void SetBillboard_XZ_Only(D3DXMATRIX *pMtx);															//ビルボード設定　XとZのみ

	static bool RangeLimit_Equal_Int(int &nValue, int nMin, int nMax);											//範囲内に抑える(int)
	static bool RangeLimit_Equal_Float(float &nValue, float nMin, float nMax);									//範囲内に抑える(float)

	static float Random_PI();																					//-3.14から3.14までのランダムで返す
	static void CalcRotation(float &fRot);	//回転を360度以内にする計算

private:

};

#endif