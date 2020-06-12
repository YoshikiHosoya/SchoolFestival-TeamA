// =====================================================================================================================================================================
//
// �p�[�e�B�N���̏��� [particle.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

// =====================================================================================================================================================================
// �C���N���[�h�t�@�C��
// =====================================================================================================================================================================
#include "main.h"
#include "scene3D.h"

// =====================================================================================================================================================================
// �p�[�e�B�N���N���X
// =====================================================================================================================================================================
class CParticle : public CScene3D
{
public:

	// �p�[�e�B�N���̎��
	enum PARTICLETYPE
	{
		PARTICLE_NONE = -1,
		PARTICLE_RED,							// ��
		PARTICLE_BLUE,							// ��
		PARTICLE_MAX,
	};

	CParticle();								// �R���X�g���N�^
	~CParticle();								// �f�X�g���N�^

	/* �����o�֐� */
	void				Init();					// ������
	void				Uninit();				// �I��
	void				Update();				// �X�V
	void				Draw();					// �`��

	/* �ÓI�����o�֐� */
	static	CParticle	*Create(D3DXVECTOR3 pos, PARTICLETYPE type);		// �p�[�e�B�N���̐���
	static	HRESULT		Load();												// ���[�h
	static	void		Unload();											// �A�����[�h

private:
	/* �����o�ϐ� */
	bool						CollisionPlayer();							// �v���C���[�Ƃ̓����蔻��
	void						ParticleCircle();							// �~�̃p�[�e�B�N��
	void						ParticleCircleShort();						// �������~�̃p�[�e�B�N��
	/* �ÓI�����o�ϐ� */
	static	LPDIRECT3DTEXTURE9	m_apTexture[PARTICLETYPE::PARTICLE_MAX];	// ���L�e�N�X�`���̃|�C���^
	static	D3DXVECTOR2			m_UVsize;									// UV�T�C�Y
	static	INTEGER2			m_UVcut;									// ������
	/* �����o�ϐ� */
	D3DXVECTOR3					m_move;										// �ړ�
	D3DXVECTOR3					m_size;										// �T�C�Y
	D3DXCOLOR					m_col;										// �F
	PARTICLETYPE				m_type;										// ���
	int							m_nCntAnim;									// �J�E���^�[�A�j���[�V����
	int							m_nPatternAnim;								// �p�^�[���A�j���[�V����
	int							m_nSpeed;									// ����
	float						m_fRot;										// ��]
	float						m_fAngle;									// �p�x
	float						m_fLength;									// ����
	float						m_fRadius;									// ���a

};
#endif
