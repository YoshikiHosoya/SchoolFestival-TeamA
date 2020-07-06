#pragma once
//=============================================================================
// �v���C���[�w�b�_�[ [player.h]
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"
#include "Scene.h"
#include "Character.h"
class CModel;
class CMeshOrbit;
class CParticle;
class CUI;
class CGun;
class CGrenadeFire;
class CPrisoner;
class CKnife;
class CPlayerUI;

//�����_�����O�N���X
class CPlayer :public CCharacter
{
public:
	typedef enum
	{
		DEBUG_NORMAL = 0,			//�ʏ�
		DEBUG_CREATE_MAP,			//�}�b�v�쐬
		DEBUG_CREATE_ENEMY,			//�G�l�~�[�쐬
		DEBUG_MAX					//�ő吔
	}DEBUG_STATE;

	CPlayer(OBJ_TYPE type);
	~CPlayer();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DebugInfo(void);
	void MoveUpdate(void);
	void CollisionUpdate(void);
	void AttackUpdate(void);
	DEBUG_STATE GetDebugState(void);
	static CPlayer *Create(void);
	bool DefaultMotion(void);
	CGun			*GetGun() { return  m_pGun; };					// �e�̃|�C���^�擾
	CGrenadeFire	*GetGrenadeFire() { return  m_pGrenadeFire; };	// �O���l�[�h���ˈʒu�̃|�C���^�擾
	CPlayerUI		*GetPlayerUI() { return  m_pPlayerUI; };		// �v���C���[UI�̃|�C���^�擾

private:
	void Move(float move, float fdest);
		DEBUG_STATE m_DebugState;						//�f�o�b�O�̃X�e�[�^�X
		bool m_bAttack_Enemy;							//�U����
		bool m_bAttack_Prisoner;						//�U����
		float m_Angle;
		WORD Oldstate;											//�R���g���[���[��1frame�O�̃X�e�[�g
		CGun			*m_pGun;								// �K���N���X�̃|�C���^
		CGrenadeFire	*m_pGrenadeFire;						// �O���l�[�h���˃N���X�̃|�C���^
		CPlayerUI		*m_pPlayerUI;							// �v���C���[UI�̃|�C���^
		CKnife			*m_pKnife;
};
#endif