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
#include "../main.h"
#include "../character.h"
#include "../ModelSet.h"
//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CGun;
class CKnife;

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
	void DebugInfo();								//デバッグ情報表記
	static CDebug_ViewerCharacter* Create();		//生成関数
	bool DefaultMotion() { GetModelSet()->GetMotion() = false; GetModelSet()->GetKeySet()--; return false; };

	void MotionViewer();							//モーションビューワ
private:
	bool ShowMotionComboBox(CModelSet::CHARACTER_MOTION_STATE &motiontype);		//モーションのコンボボックス

	void AddKeyInfo(CModelSet::MOTION *pMotion);
	void PopbackKeyInfo(CModelSet::MOTION *pMotion);
	void ResetKey();
	void CopyMotionPaste(CModelSet::CHARACTER_MOTION_STATE CopyMotionType, int nCopyKey, CModelSet::CHARACTER_MOTION_STATE NowMotion, int nNowKey);
	HRESULT SaveMotion(CModelSet::CHARACTER_MOTION_STATE motiontype);

	CGun *m_pGun;				//ナイフ銃ポインタ
	CKnife *m_pKnife;			//ナイフのポインタ
};
#endif