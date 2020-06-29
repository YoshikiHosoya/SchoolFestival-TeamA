//------------------------------------------------------------------------------
//
//デバッグ用のキャラクタ  [character.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _DEBUG_CHARACTER_H_
#define _DEBUG_CHARACTER_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "../main.h"
#include "../character.h"
#include "../motion.h"
//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CModelCharacter;

class CDebug_Character : public CCharacter
{
public:

	CDebug_Character();								//コンストラクタ
	~CDebug_Character();							//デストラクタ

	HRESULT Init();									//初期化
	void Uninit();									//終了
	void Update();									//更新
	void Draw();									//描画
	void ShowDebugInfo();							//デバッグ情報表記
	void DamageAction() {};							//ダメージ時のリアクション
	void DeathAction() {};							//死亡時のリアクション
	void AttackTurning() {};						//攻撃時の旋回
	static std::shared_ptr<CDebug_Character> Create(MODEL_TYPE modeltype,CCharacter::PARAM_TYPE paramtype);		//生成関数

private:
	bool ShowMotionComboBox(CMotion::MOTION_TYPE &motiontype);		//モーションのコンボボックス

	void MotionViewer();		//モーションビューワ
	void OffsetViewer();		//オフセットビューワ
};
#endif