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
#include "../main.h"
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

// タグ
enum TAG
{
	TAG_PLAYER = 0,
	TAG_ENEMY,
	TAG_MAX,
};

enum class DIRECTION
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
};

//------------------------------------------------------------------------------
//エイリアス宣言
//------------------------------------------------------------------------------
using FILENAME_LIST = std::vector<std::string>;		//ファイル名のリスト


//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CKeyboard;
class CXInputPad;
class CHossoLibrary
{
public:

	static float Vec2Cross(D3DXVECTOR2 const &rVecA, D3DXVECTOR2 const &rVecB);									//2D 外積計算
	static void CalcMatrix(D3DXMATRIX *pMtx,D3DXVECTOR3 const &rPos, D3DXVECTOR3 const &rRot);					//ワールドマトリックス計算
	static void SetBillboard(D3DXMATRIX *pMtx);																	//ビルボード設定
	static void SetBillboard_XZ_Only(D3DXMATRIX *pMtx);															//ビルボード設定　XとZのみ

	static float Random_PI();																					//-3.14から3.14までのランダムで返す
	static float Random(float fInputValue);																		//入力された値の+-ランダムな値で返す
	static D3DXVECTOR3 RandomVector3(float Max);																//ランダムなvector3型で値を返す
	static void CalcRotation(float &fRot);																		//回転を360度以内にする計算

	static bool PressAnyButton(void);
	static bool PressStartButton(void);
	static bool ImGui_Combobox(std::vector<std::string> aItemNameList, std::string aTitle, int &nValue);

	static bool PadMoveInput(D3DXVECTOR3 & rMove, DIRECTION & direction,bool bJump);

	//------------------------------------------------------------------------------
	//範囲内の値に修正する関数
	//intでもfloatでもいけるようにテンプレート
	//------------------------------------------------------------------------------
	template <class X> static bool RangeLimit_Equal(X &Value, X Min, X Max)
	{
		//最小値より小さい時
		if (Value < Min)
		{
			//最小値に合わす
			Value = Min;
			return true;
		}
		//最大値より大きい時
		if (Value > Max)
		{
			//最大値に合わす
			Value = Max;
			return true;
		}
		return false;
	}

private:

};

#endif