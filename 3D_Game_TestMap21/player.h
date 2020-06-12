// =====================================================================================================================================================================
//
// �v���C���[�̏��� [player.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

// =====================================================================================================================================================================
// �C���N���[�h�t�@�C��
// =====================================================================================================================================================================
#include "main.h"
#include "scene.h"

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define PLAYER_MOTION				(4)					// �v���C���[�̃��[�V������

// =====================================================================================================================================================================
// �O���錾
// =====================================================================================================================================================================
class CModelCharacter;			// ���f���L�����N�^�[�N���X

// =====================================================================================================================================================================
// �v���C���[�N���X
// =====================================================================================================================================================================
class CPlayer : public CScene
{
public:
	// �v���C���[�̏��
	enum PLAYERSTATE
	{
		PLAYERSTATE_NONE = -1,
		PLAYERSTATE_APPEAR,						// �o����
		PLAYERSTATE_NORMAL,						// �ʏ펞
		PLAYERSTATE_SPEED,						// �X�s�[�h�A�b�v��
		PLAYERSTATE_FALL,						// ������
		PLAYERSTATE_DEATH,						// ���S��
		PLAYERSTATE_MAX,						// �ő吔
	};

	CPlayer();									// �R���X�g���N�^
	CPlayer(PRIORITY Priority);					// �R���X�g���N�^
	~CPlayer();									// �f�X�g���N�^

	/* �����o�֐� */
	void				Init();					// ������
	void				Uninit();				// �I��
	void				Update();				// �X�V
	void				Draw();					// �`��

	/* �����o�֐� */
	void				SetPos(D3DXVECTOR3 pos)			{ m_pos = pos; };						// �ʒu�̐ݒ�
	void				SetRestartPos(D3DXVECTOR3 pos)	{ m_posRestart = pos; };				// �ĊJ�n�_�̐ݒ�
	D3DXVECTOR3			GetPos()						{ return m_pos; };						// �ʒu�̎擾
	D3DXVECTOR3			GetOldPos()						{ return m_posOld; };					// �ߋ��̈ʒu�̎擾
	float				GetLandingPos()					{ return m_fLandingPos; };				// ���n�������̈ʒu�̎擾
	float				GetJumpingPos()					{ return m_fJumpingPos; };				// �n�ʂ��痣�ꂽ�u�Ԃ̈ʒu�̎擾
	bool				GetLandFlag()					{ return m_bLand; };					// ���n�t���O�̎擾
	D3DXVECTOR3			GetSize()						{ return m_size; };						// �T�C�Y�̎擾
	D3DXVECTOR3			GetRot()						{ return m_rot; };						// ��]�̎擾
	CModelCharacter		*GetModelCharacter()			{ return m_pModelCharacter; };			// ���f���L�����N�^�[�̎擾
	PLAYERSTATE			GetPlayerState()				{ return m_state; };					// �v���C���[�̏�Ԃ̎擾
	void				PlayerDamage(int nLife);	// �_���[�W
	void				PlayerRecovery(int nLife);	// ��

	/* �ÓI�����o�֐� */
	static  CPlayer		*Create();					// �v���C���[�̐���
	static	HRESULT		Load();						// ���[�h
	static	void		Unload();					// �A�����[�h
	static	void		SetPlayerState(PLAYERSTATE state) { m_state = state; };	// �v���C���[�̏�Ԃ̐ݒ�

private:
	/* �����o�֐� */
	void				MovePlayer();						// �v���C���[�̈ړ�����
	void				PlayerStateConfig();				// �v���C���[�̏�Ԃ̊e�ݒ�
	void				PlayerFallDeath();					// �v���C���[�̗�����
	/* �����o�ϐ� */
	D3DXVECTOR3							m_pos;				// �ʒu
	D3DXVECTOR3							m_posOld;			// �ߋ��̈ʒu
	D3DXVECTOR3							m_posRestart;		// �ĊJ�ʒu
	D3DXVECTOR3							m_size;				// �T�C�Y
	D3DXVECTOR3							m_move;				// �ړ�
	D3DXVECTOR3							m_rot;				// ����(��])
	D3DXVECTOR3							m_rotDiff;			// �����̍���
	D3DXVECTOR3							m_rotDest;			// �ړI�̌���
	float								m_fJumpingPos;		// �n�ʂ��痣�ꂽ�u�Ԃ̈ʒu
	float								m_fLandingPos;		// ���n�������̈ʒu
	D3DXMATRIX							m_mtxWorld;			// ���[���h�}�g���b�N�X
	bool								m_bJump;			// �W�����v�t���O
	bool								m_bFlashing;		// ���񂾂Ƃ��̓_�Ńt���O
	bool								m_bLand;			// ���n�����Ƃ��̃t���O
	int									m_nCntDeath;		// ���񂾂Ƃ��̃J�E���g
	int									m_nLife;			// �̗�
	float								m_LeftStick_X;		// ���X�e�B�b�N��X�̒l
	float								m_LeftStick_Y;		// ���X�e�B�b�N��Y�̒l
	float								m_RightStick_X;		// �E�X�e�B�b�N��X�̒l
	float								m_RightStick_Y;		// �E�X�e�B�b�N��Y�̒l
	/* �ÓI�����o�ϐ� */
	static	LPD3DXMESH					m_pMesh;			// ���b�V�����ւ̃|�C���^
	static	LPD3DXBUFFER				m_pBuffMat;			// �}�e���A�����ւ̃|�C���^
	static	DWORD						m_nNumMat;			// �}�e���A�����̐�
	static	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^
	static	CModelCharacter				*m_pModelCharacter;	// ���f���L�����N�^�[�̃|�C���^
	static	PLAYERSTATE					m_state;			// ���
};
#endif
