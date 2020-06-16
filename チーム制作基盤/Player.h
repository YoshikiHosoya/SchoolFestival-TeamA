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
	DEBUG_STATE GetDebugState(void);
	static CPlayer *Create(void);
	void DefaultMotion(void);
private:
	void Move(float move, float fdest);
		DEBUG_STATE m_DebugState;						//�f�o�b�O�̃X�e�[�^�X
		bool m_Attack;									//�U����
		float m_Angle;
		XINPUT_STATE state;								//�R���g���[���[�̃X�e�[�^�X
		XINPUT_VIBRATION vibration;						//�R���g���[���[�̃o�C�u���[�V����
		WORD Oldstate;									//�R���g���[���[��1frame�O�̃X�e�[�g
		CGun	*m_pGun;								// �K���N���X�̃|�C���^
		D3DXVECTOR3 m_ShotRot;							//������
};
#endif