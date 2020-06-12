// =====================================================================================================================================================================
//
// ���f���L�����N�^�[�̏��� [modelcharacter.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _MODELCHARACTER_H_
#define _MODELCHARACTER_H_

// =====================================================================================================================================================================
// �C���N���[�h�t�@�C��
// =====================================================================================================================================================================
#include "main.h"
#include "scene.h"
#include "sceneX.h"

// =====================================================================================================================================================================
// �O���錾
// =====================================================================================================================================================================
class CPartsModel;				// �p�[�c���f���N���X

// =====================================================================================================================================================================
// ���f���L�����N�^�[
// =====================================================================================================================================================================
class CModelCharacter
{
public:
	// �v���C���[�̃��[�V�����̎��
	enum PlayerMotionType
	{
		PlayerMotionType_NEUTRAL = 0,			// �ҋ@
		PlayerMotionType_WALK,					// ����
		PlayerMotionType_JUMP,					// �W�����v
		PlayerMotionType_LANDING,				// ���n
		PlayerMotionType_MAX,
	};

	CModelCharacter();							// �R���X�g���N�^
	virtual ~CModelCharacter();					// �f�X�g���N�^
	
	/* �����o�֐� */
	void				Init();					// ������
	void				Uninit();				// �I��
	void				Update();				// �X�V
	void				Draw();					// �`��

	/* �ÓI�����o�֐� */
	static	CModelCharacter		*Create();		// 3D�|���S���̐���	

	/* �����o�֐� */
	void				SetMatrix(D3DXMATRIX *mtx);					// �}�g���b�N�X�̐ݒ�
	void				SetMotion(PlayerMotionType MotionType);		// ���[�V�����̐ݒ�

private:
	/* �����o�֐� */
	void				ModelLoad();			// ���f���̓ǂݍ���
	void				MotionUpdate();			// ���[�V�����̍X�V

	/* �����o�ϐ� */
	D3DXVECTOR3							m_pos;						// ���݂̈ʒu
	D3DXVECTOR3							m_posOld;					// �O��̈ʒu
	D3DXVECTOR3							m_posDif;					// �ʒu�̍���
	D3DXVECTOR3							m_posDest;					// �ړI�̈ʒu
	D3DXVECTOR3							m_posInit;					// �����ʒu
	D3DXVECTOR3							m_rot;						// ����(��])
	D3DXVECTOR3							m_rotDiff;					// �����̍���
	D3DXVECTOR3							m_rotDest;					// �ړI����
	D3DXVECTOR3							m_move;						// �ړ�
	D3DXMATRIX							m_mtxWorld;					// ���[���h�}�g���b�N�X
	LPDIRECT3DTEXTURE9					m_pTexture = {};			// �e�N�X�`���ւ̃|�C���^
	CPartsModel							*m_pModel[PLAYER_PARTS];	// ���f���ւ̃|�C���^

	/* �ÓI�����o�ϐ� */
	static	LPD3DXMESH					m_pMesh;					// ���b�V�����ւ̃|�C���^
	static	LPD3DXBUFFER				m_pBuffMat;					// �}�e���A�����ւ̃|�C���^
	static	DWORD						m_nNumMat;					// �}�e���A�����̐�
	static	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;					// ���_�o�b�t�@�ւ̃|�C���^
	static	PlayerMotionType			m_PlayerMotionType;			// ���݃v���C���[�̃��[�V�����̎��
	static	PlayerMotionType			m_PlayerMotionTypeOld;		// �O��̃v���C���[�̃��[�V�����̎��
	static	int							m_nFrame;					// �t���[����
	static	int							m_nKeySet;					// ���݂̃L�[

};
#endif
