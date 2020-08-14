// =====================================================================================================================================================================
//
// �Q�[���̏��� [game.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#ifndef _GAME_H_
#define _GAME_H_

// =====================================================================================================================================================================
// �C���N���[�h�t�@�C��
// =====================================================================================================================================================================
#include "main.h"
#include "BaseMode.h"

// =====================================================================================================================================================================
// �O���錾
// =====================================================================================================================================================================
class CRenderer;
class CKeyboard;
class CPlayer;
class CPause;
class CMap;
class CResultManager;
class CGameManager;
class CShield;
// =====================================================================================================================================================================
// �Q�[���N���X
// =====================================================================================================================================================================
class CGame :public CBaseMode
{
public:
	// �Q�[�����[�h
	enum GAME_STATE
	{
		GAME_MODE_NORMAL,		// �ʏ�̃Q�[���v���C���
		GAME_MODE_RESULT,		// ���U���g�\�����
	};

	/* �����o�֐� */
	CGame();
	~CGame();
	HRESULT		Init(void);
	void		Uninit(void);
	void		Update(void);
	CPlayer		*GetPlayer(void);
	CMap		*GetMap(void);

	GAME_STATE	GetGameMode()					{ return m_GameState; };
	void		SetGameMode(GAME_STATE mode)	{ m_GameState = mode; };
	CResultManager *GetResultManager()			{ return m_pResultManager; };

	void Draw(void);							//�`��
	void ShowDebugInfo(void);					//�f�o�b�O���\�L


private:
	/* �����o�֐� */
	void DebugCollision(CKeyboard *key);		// �f�o�b�O�p�����蔻��̉���on off
	void DebugItem(CKeyboard *key);				// �f�o�b�O�p�A�C�e��

	/* �ÓI�����o�ϐ� */
	static LPDIRECT3DTEXTURE9			m_pTexture;
	static CPlayer						*m_pPlayer;
	static CMap							*m_pMap;
	static int							m_Counter;

	/* �����o�ϐ� */
	CPause								*m_pPause;
	GAME_STATE							m_GameState;
	CResultManager						*m_pResultManager;
	std::unique_ptr<CGameManager>		m_pGameManager;			//�Q�[���̐i�s�Ǘ�
	int									m_nFrame;
	int									m_nCntNum;
	bool								m_bEventFlag;
	CShield								*m_pShield;
};
#endif