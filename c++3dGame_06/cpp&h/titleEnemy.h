//=============================================================================
//
// �^�C�g���p�G���f������ [titleenemy.h]
// Author : Fujiwara Masato
//
//=============================================================================
#ifndef _TITLEENEMY_H_
#define _TITLEENEMY_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"
#include "model.h"
#include "motion.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���錾
//=============================================================================

//=============================================================================
// �N���X
//=============================================================================
class CTitleEnemy : public CScene
{
public:
	// ---------���[�V�����^�C�v---------- //
	typedef enum
	{
		MOTIONTYPE_TITLE_ENEMY_WAIT = 0,		//�ҋ@���[�V����
		MOTIONTYPE_TITLE_ENEMY_RUN,				//�ړ����[�V����(����)
		MOTIONTYPE_TITLE_ENEMY_KILLCAMERA,		//�v���C���[��߂܂�����
		MOTIONTYPE_TITLE_ENEMY_MAX
	} MOTIONTYPE_TITLE_ENEMY;

	typedef enum
	{
		ENEMY_STATE_LEVEL1 = 0,	//�ʏ펞
		ENEMY_STATE_LEVEL2		//������
	} TITLE_ENEMY_STATE;

	// ---------���f�����---------- //
	typedef enum
	{//J = JOINT R = RIGHT L = LEFT
		TITLE_ENEMYTYPE_00_BODY = 0,		// [��]			00
		TITLE_ENEMYTYPE_01_HEAD,			// [��]			01
		TITLE_ENEMYTYPE_02_ARM_L,			// [���r]		02
		TITLE_ENEMYTYPE_03_ARM_R,			// [�E�r]		03
		TITLE_ENEMYTYPE_04_LEG_L,			// [����]		04
		TITLE_ENEMYTYPE_05_LEG_R,			// [�E��]		05
		TITLE_ENEMYTYPE_MAX				//���v�p�[�c��
	} TITLE_ENEMYTYPE;

	/* �֐� */
	CTitleEnemy();
	~CTitleEnemy();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPos(void);		// �ʒu�擾
	D3DXVECTOR3 GetRot(void);		// ��]�擾
	static CTitleEnemy * Create();	// �쐬
	static void Load(void);			// �ǂݍ���
	static void UnLoad(void);		// UnLoad����
	void ReleaseTEne(void);			// �폜
	void SetMotion(void);			// ���[�V����

protected:
private:
	/* �֐� */
	/* �ϐ� */
	static CLoad				*m_pload;							// ���[�h
	static CModel_info			*m_pModel_info;						// ���f�����̕ۑ�
	static MODEL_OFFSET			*m_pModel_offset;					// ���f���̏����z�u
	static MOTION				*m_pMotion;							// ���[�V�������̕ۑ�

	CModel 						*m_pModel[TITLE_ENEMYTYPE_MAX] = {};		// ���f��

	D3DXMATRIX					m_mtxWorld;							// �s��
	D3DXVECTOR3					m_pos;								// �ʒu
	D3DXVECTOR3					m_posold;							// �O�̈ʒu
	D3DXVECTOR3					m_move;								// �ړ���
	D3DXVECTOR3					m_rot;								// ���݉�]��
	D3DXVECTOR3					m_rotLast;							// ������������
	D3DXVECTOR3					m_rotbetween;						// ��]�̍���
	D3DXVECTOR3					m_size;								// ���f���̃T�C�Y
	int							m_nMaxModel;						// �ő僂�f����
	int							m_nMotiontype;						// ���[�V�����^�C�v
	int							m_nMotiontypeOld;					// �O��̃��[�V�����^�C�v
	int							m_nMaxMotion;						// �ő僂�[�V������
	int							m_keyinfoCnt;						// �L�[���̃J�E���g
	int							m_nFrame;							// �t���[���J�E���g
	CCollision					*m_pCollision;						// �����蔻����
};
#endif
