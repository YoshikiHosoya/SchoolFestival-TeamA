//------------------------------------------------------------------------------
//
//武器となるモデル処理  [modelparts_weapon.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MODELPARTSWEAPON_H_
#define _MODELPARTSWEAPON_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "modelparts.h"

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CCharacter;
class COrbit;
class CCollision;
class CMotion;

class CModelParts_Weapon : public CModelParts
{
public:
	CModelParts_Weapon();
	virtual ~CModelParts_Weapon();

	HRESULT Init();										//初期化
	void Uninit();										//終了
	void Update();										//更新
	void Draw();										//描画
	static std::unique_ptr<CModelParts_Weapon> Create(std::shared_ptr<CModelInfo> pModelInfo);		//生成処理
	void ShowDebugInfo();								//デバッグ情報表記
	void StartAttack();									//攻撃の開始
	void EndAttack();									//攻撃の終了
	void SetAttackInfo(CMotion::MOTION_TYPE motiontype);//攻撃の情報更新
	void ResetEnemyInvincible();						//敵の無敵状態解除　モーション切り替わった時に発動

	void SetHasCharacterPtr(std::shared_ptr<CCharacter> pCharacter) { m_pWeaponHasCharacter = std::weak_ptr<CCharacter>(pCharacter); };		//武器を持っているキャラクターへのポインタ
protected:

private:
	std::shared_ptr<COrbit> m_pOrbit;					//軌跡のポインタ
	std::unique_ptr<CCollision> m_pCollision;			//当たり判定のポインタ

	void Collision();

	int m_nDamage;										//ダメージ
	int m_nBlueDamage;									//青ダメージ
	float m_fKnockBack_Front;							//ノックバック量
	float m_fKnockBack_Up;								//ノックバック量

	std::weak_ptr<CCharacter> m_pWeaponHasCharacter;	//武器を持ってるキャラクターのポインタ

};
#endif