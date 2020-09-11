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
#include "../manager.h"
#include "../renderer.h"
#include "../inputKeyboard.h"
#include "../XInputPad.h"
#include "../sound.h"

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------
PAD_STICK CHossoLibrary::m_PadStick[MAX_CONTROLLER] = {};
DIRECTION CHossoLibrary::m_direction				= DIRECTION::LEFT;

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
//前回のスティック情報を保存
//------------------------------------------------------------------------------
void CHossoLibrary::SaveLastStickInfo()
{
	CXInputPad *InpudPad[MAX_CONTROLLER] = {};

	for (int nCnt = 0; nCnt < MAX_CONTROLLER; nCnt++)
	{
		InpudPad[nCnt] = CManager::GetPad((TAG)nCnt);

		// 上下の入力判定
		if(fabsf(m_PadStick[nCnt].fLeftStickValue_Y / STICK_MAX_RANGE) > 0.8f)
		{
			m_PadStick[nCnt].bLeftStickDown_Y = true;
		}
		else
		{
			m_PadStick[nCnt].bLeftStickDown_Y = false;
		}
		// 左スティックの入力取得
		InpudPad[nCnt]->GetStickLeft(&m_PadStick[nCnt].fLeftStickValue_X, &m_PadStick[nCnt].fLeftStickValue_Y);
	}
}

//------------------------------------------------------------------------------
//スティックを倒している方向をチェック
//------------------------------------------------------------------------------
DIRECTION CHossoLibrary::CheckPadStick()
{
	// 変数
	CKeyboard	*Keyboard					= CManager::GetInputKeyboard();
	CXInputPad	*InpudPad[MAX_CONTROLLER]	= {};
	DIRECTION	Direction					= (DIRECTION)-1;

	// ゲームパッド
	for (int nCnt = 0; nCnt < MAX_CONTROLLER; nCnt++)
	{
		InpudPad[nCnt] = CManager::GetPad((TAG)nCnt);

		// 上
		if (InpudPad[nCnt]->GetTrigger(CXInputPad::JOYPADKEY_UP, 1) || ((m_PadStick[nCnt].fLeftStickValue_Y / STICK_MAX_RANGE) > 0.8f && m_PadStick[nCnt].bLeftStickDown_Y == false))
		{
			Direction = DIRECTION::UP;
			return Direction;
		}
		// 下
		if (InpudPad[nCnt]->GetTrigger(CXInputPad::JOYPADKEY_DOWN, 1) || ((m_PadStick[nCnt].fLeftStickValue_Y / STICK_MAX_RANGE) <= -0.8f && m_PadStick[nCnt].bLeftStickDown_Y == false))
		{
			Direction = DIRECTION::DOWN;
			return Direction;
		}
	}
	// キーボード
	// 上
	if (Keyboard->GetKeyboardTrigger(DIK_UP) || Keyboard->GetKeyboardTrigger(DIK_W))
	{
		Direction = DIRECTION::UP;
		return Direction;
	}
	// 下
	if (Keyboard->GetKeyboardTrigger(DIK_DOWN) || Keyboard->GetKeyboardTrigger(DIK_S))
	{
		Direction = DIRECTION::DOWN;
		return Direction;
	}

	return Direction;
}
//------------------------------------------------------------------------------
//何かしらキーを押したとき
//------------------------------------------------------------------------------
bool CHossoLibrary::PressAnyButton(void)
{
	CKeyboard *Keyboard;
	Keyboard = CManager::GetInputKeyboard();
	CXInputPad *InpudPad[MAX_CONTROLLER] = {};

	for (int nCnt = 0; nCnt < MAX_CONTROLLER; nCnt++)
	{
		InpudPad[nCnt] = CManager::GetPad((TAG)nCnt);

		if (Keyboard->GetKeyboardTrigger(DIK_RETURN) ||
			Keyboard->GetKeyboardTrigger(DIK_SPACE) ||
			InpudPad[nCnt]->GetTrigger(CXInputPad::JOYPADKEY_START, 1) ||
			InpudPad[nCnt]->GetTrigger(CXInputPad::JOYPADKEY_A, 1) ||
			InpudPad[nCnt]->GetTrigger(CXInputPad::JOYPADKEY_B, 1) ||
			InpudPad[nCnt]->GetTrigger(CXInputPad::JOYPADKEY_X, 1) ||
			InpudPad[nCnt]->GetTrigger(CXInputPad::JOYPADKEY_Y, 1))
		{
			//CManager::GetSound()->Play(CSound::LABEL_SE_DECISION);
			return true;
		}
	}
	return false;
}
//------------------------------------------------------------------------------
//スタートボタンを押したとき
//------------------------------------------------------------------------------
bool CHossoLibrary::PressStartButton(void)
{
	CKeyboard *Keyboard;
	Keyboard = CManager::GetInputKeyboard();
	CXInputPad *InpudPad[MAX_CONTROLLER] = {};
	for (int nCnt = 0; nCnt < MAX_CONTROLLER; nCnt++)
	{
		InpudPad[nCnt] = CManager::GetPad((TAG)nCnt);

		if (Keyboard->GetKeyboardTrigger(DIK_RETURN) || InpudPad[nCnt]->GetTrigger(CXInputPad::JOYPADKEY_START, 1))
		{
			return true;
		}
	}
	return false;
}

//------------------------------------------------------------------------------
//ポーズボタンを押したとき
//------------------------------------------------------------------------------
bool CHossoLibrary::PressPauseButton()
{
	// 変数
	CKeyboard *Keyboard = CManager::GetInputKeyboard();
	CXInputPad *InpudPad[MAX_CONTROLLER] = {};

	for (int nCnt = 0; nCnt < MAX_CONTROLLER; nCnt++)
	{
		InpudPad[nCnt] = CManager::GetPad((TAG)nCnt);

		if (InpudPad[nCnt]->GetTrigger(CXInputPad::JOYPADKEY_START, 1))
		{
			return true;
		}
	}
	if (Keyboard->GetKeyboardTrigger(DIK_P))
	{
		return true;
	}
	return false;
}

//------------------------------------------------------------------------------
//決定ボタンを押したとき
//------------------------------------------------------------------------------
bool CHossoLibrary::PressDeterminationButton(void)
{
	// 変数
	CKeyboard *Keyboard = CManager::GetInputKeyboard();
	CXInputPad *InpudPad[MAX_CONTROLLER] = {};

	for (int nCnt = 0; nCnt < MAX_CONTROLLER; nCnt++)
	{
		InpudPad[nCnt] = CManager::GetPad((TAG)nCnt);

		if (Keyboard->GetKeyboardTrigger(DIK_RETURN) || InpudPad[nCnt]->GetTrigger(CXInputPad::JOYPADKEY_A, 1))
		{
			return true;
		}
	}
	return false;
}

//------------------------------------------------------------------------------
//ImGuiのコンボボックス
//------------------------------------------------------------------------------
bool CHossoLibrary::ImGui_Combobox(std::vector<std::string> aItemNameList, std::string aTitle, int & nValue)
{
	bool bChange = false;

#ifdef _DEBUG
	//combo開始
	if (ImGui::BeginCombo(aTitle.data(), aItemNameList[nValue].data()))
	{
		//要素分繰り返す
		for (size_t nCnt = 0; nCnt < aItemNameList.size(); nCnt++)
		{

			//選択番号があってるかどうか
			bool is_selected = (aItemNameList[nValue] == aItemNameList[nCnt]);

			//選択された時の処理
			if (ImGui::Selectable(aItemNameList[nCnt].data(), is_selected))
			{
				//現在の選択項目設定
				nValue = nCnt;
				bChange = true;
			}
		}
		//combo終了
		ImGui::EndCombo();

	}
#endif //DEBUG
	return bChange;
}

//------------------------------------------------------------------------------
//パッドの入力処理
//------------------------------------------------------------------------------
bool CHossoLibrary::PadMoveInput(D3DXVECTOR3 & rMove, DIRECTION & direction, bool bJump, TAG Tag)
{
	bool bInput = false;

	CXInputPad *pad;

	pad = CManager::GetPad(Tag);
	D3DXVECTOR3 InputValue = ZeroVector3;
	pad->GetStickLeft(&InputValue.x, &InputValue.y);//パッドの入力値を代入
	InputValue.x /= STICK_MAX_RANGE;//値の正規化
	InputValue.y /= STICK_MAX_RANGE;//値の正規化

	CDebugProc::Print_Left("パッドの入力値 X : %2f Y : %2f\n", InputValue.x, InputValue.y);

	//右
	if (InputValue.x > 0.5f)
	{
		rMove = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
		direction = DIRECTION::RIGHT;
		bInput = true;

	}
	//左
	else if (InputValue.x < -0.5f)
	{
		rMove = D3DXVECTOR3(0.5f, 0.5f, 0.0f);
		direction = DIRECTION::LEFT;
		bInput = true;

	}
	//上
	if (InputValue.y > 0.6f)
	{
		direction = DIRECTION::UP;

	}
	//下
	else if (InputValue.y < -0.6f && bJump == false)
	{
		direction = DIRECTION::DOWN;
	}
	return bInput;
}

//------------------------------------------------------------------------------
//ビルボード設定 XとZのみ
//------------------------------------------------------------------------------
void CHossoLibrary::SetBillboard_XZ_Only(D3DXMATRIX * pMtx)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

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
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

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
//-3.14～3.14を返す
//------------------------------------------------------------------------------
float CHossoLibrary::Random_PI()
{
	return Random(3.14f);
}
//------------------------------------------------------------------------------
//入力された値の+-ランダムな値で返す
//------------------------------------------------------------------------------
float CHossoLibrary::Random(float fInputValue)
{
	//0除算防止
	if (fInputValue <= 0.0f)
	{
		return 0.0f;
	}

	int nValue = int(fInputValue * 100);

	float fValue;

	rand() % 2 ?
		fValue = float(rand() % nValue / 100.0f) :
		fValue = -float(rand() % nValue / 100.0f);

	return fValue;
}

//------------------------------------------------------------------------------
//入力された値の+-ランダムな値で返す
//------------------------------------------------------------------------------
D3DXVECTOR3 CHossoLibrary::RandomVector3(float Max)
{
	D3DXVECTOR3 Value = ZeroVector3;

	Value.x = Random(Max);
	Value.y = Random(Max);
	//Value.z = Random(Max);


	return Value;
}
