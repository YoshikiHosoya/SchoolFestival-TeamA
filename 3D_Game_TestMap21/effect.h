// =====================================================================================================================================================================
//
// �G�t�F�N�g�̏��� [effect.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

// =====================================================================================================================================================================
// �C���N���[�h�t�@�C��
// =====================================================================================================================================================================
#include "main.h"
#include "scene3D.h"

// =====================================================================================================================================================================
// �G�t�F�N�g�N���X
// =====================================================================================================================================================================
class CEffect : public CScene3D
{
public:

	// �G�t�F�N�g�̎��
	enum EFFECTTYPE
	{
		EFFECTTYPE_NONE = -1,
		EFFECTTYPE_AURA,					// �I�[��
		EFFECTTYPE_GAYSER,					// �Ԍ���
		EFFECTTYPE_ITEM,					// �A�C�e��
		EFFECTTYPE_MAX,
	};

	CEffect();									// �R���X�g���N�^
	~CEffect();									// �f�X�g���N�^

	/* �����o�֐� */
	void				Init();					// ������
	void				Uninit();				// �I��
	void				Update();				// �X�V
	void				Draw();					// �`��

	/* �ÓI�����o�֐� */
	static	CEffect		*Create(D3DXVECTOR3 pos, EFFECTTYPE type);			// �G�t�F�N�g�̐���
	static	HRESULT		Load();												// ���[�h
	static	void		Unload();											// �A�����[�h

private:
	/* �����o�֐� */
	bool						CollisionEffect();							// �G�t�F�N�g�̓����蔻��
	void						EffectConfig(EFFECTTYPE type);				// �G�t�F�N�g�̐ݒ�
	/* �ÓI�����o�ϐ� */
	static	LPDIRECT3DTEXTURE9	m_apTexture[EFFECTTYPE::EFFECTTYPE_MAX];	// ���L�e�N�X�`���̃|�C���^
	/* �����o�ϐ� */
	D3DXVECTOR3					m_size;										// �T�C�Y
	D3DXVECTOR3					m_move;										// �ړ�
	D3DXCOLOR					m_col;										// �F
	EFFECTTYPE					m_type;										// ���
	int							m_nCntAnim;									// �J�E���^�[�A�j���[�V����
	int							m_nPatternAnim;								// �p�^�[���A�j���[�V����
	float						m_fRadius;									// ���a
	bool						m_bDamage;									// �_���[�W�t���O
	bool						m_bAction;									// �A�N�V�����t���O
	int							m_nCntFrame;								// �t���[���J�E���g
	bool						m_bAdditiveSynthesis;						// ���Z����������t���O
	D3DXVECTOR2					m_UVsize;									// UV�T�C�Y
	INTEGER2					m_UVcut;									// ������
	int							m_nAnimSpeed;								// �A�j���[�V�����̃X�s�[�h

};
#endif
