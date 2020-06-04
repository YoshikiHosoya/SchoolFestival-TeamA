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
	~CDebug_ViewerCharacter();							//デストラクタ

	HRESULT Init();									//初期化
	void Uninit();									//終了
	void Update();									//更新
	void Draw();									//描画
	void ShowDebugInfo();							//デバッグ情報表記
	void DamageAction() {};							//ダメージ時のリアクション
	void DeathAction() {};							//死亡時のリアクション
	void AttackTurning() {};						//攻撃時の旋回
	static CDebug_ViewerCharacter* Create();		//生成関数

private:
	bool ShowMotionComboBox(CCharacter::MOTION_PLAYER &motiontype);		//モーションのコンボボックス

	void MotionViewer();		//モーションビューワ
	void OffsetViewer();		//オフセットビューワ
};
#endif