//------------------------------------------------------------------------------
//
//デバッグ用のキャラクタ  [character.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _DEBUG_VIEWER_CHARACTER_H_
#define _DEBUG_VIEWER_CHARACTER_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "../../main.h"
#include "../../character.h"
//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CModelCharacter;

class CDebug_ViewerCharacter : public CCharacter
{
public:

	CDebug_ViewerCharacter();							//コンストラクタ
	CDebug_ViewerCharacter(OBJ_TYPE type);
	~CDebug_ViewerCharacter();							//デストラクタ

	HRESULT Init();									//初期化
	void Uninit();									//終了
	void Update();									//更新
	void Draw();									//描画
	void ShowDebugInfo();							//デバッグ情報表記
	static CDebug_ViewerCharacter* Create();		//生成関数
	void DefaultMotion() { return SetMotion(CCharacter::PLAYER_MOTION_NORMAL); };

	void MotionViewer();							//モーションビューワ
	void OffsetViewer();							//オフセットビューワ
private:
	bool ShowMotionComboBox(CCharacter::CHARACTER_MOTION_STATE &motiontype);		//モーションのコンボボックス

	void AddKeyInfo(CCharacter::MOTION *pMotion);
	void PopbackKeyInfo(CCharacter::MOTION *pMotion);
	void ResetKey();
	void CopyMotionPaste(CCharacter::CHARACTER_MOTION_STATE CopyMotionType, int nCopyKey, CCharacter::CHARACTER_MOTION_STATE NowMotion, int nNowKey);
	HRESULT SaveMotion(CCharacter::CHARACTER_MOTION_STATE motiontype);
	HRESULT SaveModelOffset();
};
#endif