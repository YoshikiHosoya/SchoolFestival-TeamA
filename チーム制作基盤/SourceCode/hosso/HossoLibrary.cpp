//------------------------------------------------------------------------------
//
//ライブラリ処理  [HossoLibrary.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "hossolibrary.h"
#include "../../manager.h"
#include "../../renderer.h"
//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//2Dの外積計算
//------------------------------------------------------------------------------
float CHossoLibrary::Vec2Cross(D3DXVECTOR2 const &rVecA, D3DXVECTOR2 const &rVecB)
{
	return rVecA.x * rVecB.y - rVecB.x * rVecA.y;
}

//------------------------------------------------------------------------------
//マトリックス計算
//------------------------------------------------------------------------------
void CHossoLibrary::CalcMatrix(D3DXMATRIX *pMtx, D3DXVECTOR3 const &rPos, D3DXVECTOR3 const &rRot)
{
	D3DXMATRIX	mtxRot, mtxTrans;			//計算用

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(pMtx);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rRot.y, rRot.x, rRot.z);
	D3DXMatrixMultiply(pMtx, pMtx, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, rPos.x, rPos.y, rPos.z);
	D3DXMatrixMultiply(pMtx, pMtx, &mtxTrans);
}

//------------------------------------------------------------------------------
//回転の計算　360度以内にする
//------------------------------------------------------------------------------
void CHossoLibrary::CalcRotation(float &fRot)
{
	//差分が3.14を以上の時
	if (fRot > D3DX_PI)
	{
		//6.28引く
		fRot -= D3DX_PI * 2;
	}
	//差分が-3.14以下の時
	if (fRot < -D3DX_PI)
	{
		//6.28加算
		fRot += D3DX_PI * 2;
	}
}

//------------------------------------------------------------------------------
//ビルボード設定 XとZのみ
//------------------------------------------------------------------------------
void CHossoLibrary::SetBillboard_XZ_Only(D3DXMATRIX * pMtx)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();

	//計算用変数
	D3DXMATRIX mtxView;

	//ビューマトリックス初期化
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ビルボード設定
	pMtx->_11 = mtxView._11;
	pMtx->_12 = mtxView._21;
	pMtx->_13 = mtxView._31;
	//pMtx->_21 = mtxView._12;
	//pMtx->_22 = mtxView._22;
	//pMtx->_23 = mtxView._32;
	pMtx->_31 = mtxView._13;
	pMtx->_32 = mtxView._23;
	pMtx->_33 = mtxView._33;
}
//------------------------------------------------------------------------------
//ビルボード設定
//------------------------------------------------------------------------------
void CHossoLibrary::SetBillboard(D3DXMATRIX * pMtx)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();

	//計算用変数
	D3DXMATRIX mtxView;

	//ビューマトリックス初期化
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ビルボード設定
	pMtx->_11 = mtxView._11;
	pMtx->_12 = mtxView._21;
	pMtx->_13 = mtxView._31;
	pMtx->_21 = mtxView._12;
	pMtx->_22 = mtxView._22;
	pMtx->_23 = mtxView._32;
	pMtx->_31 = mtxView._13;
	pMtx->_32 = mtxView._23;
	pMtx->_33 = mtxView._33;
}
//------------------------------------------------------------------------------
//範囲内の値に修正
//------------------------------------------------------------------------------
bool CHossoLibrary::RangeLimit_Equal_Int(int & nValue, int nMin, int nMax)
{
	//最小値より小さい時
	if (nValue < nMin)
	{
		//最小値に合わす
		nValue = nMin;
		return true;
	}
	//最大値より大きい時
	if (nValue > nMax)
	{
		//最大値に合わす
		nValue = nMax;
		return true;
	}
	return false;
}
//------------------------------------------------------------------------------
//範囲内の値に修正
//------------------------------------------------------------------------------
bool CHossoLibrary::RangeLimit_Equal_Float(float & nValue, float nMin, float nMax)
{
	//最小値より小さい時
	if (nValue < nMin)
	{
		//最小値に合わす
		nValue = nMin;
		return true;
	}
	//最大値より大きい時
	if (nValue > nMax)
	{
		//最大値に合わす
		nValue = nMax;
		return true;
	}
	return false;
}
//------------------------------------------------------------------------------
//-3.14〜3.14を返す
//------------------------------------------------------------------------------
float CHossoLibrary::Random_PI()
{
	return float(rand() % 314 / 100.0f) - float(rand() % 314) / 100.0f;
}
