//----------------------------------------------------------------------------
//
// �e�N�X�`���A�j���[�V�����p�̊��N���X [TexAnimationBase.h]
// Author : Yoshiki Hosoya
//
//----------------------------------------------------------------------------
#ifndef _TEXANIMATION_BASE_H_
#define _TEXANIMATION_BASE_H_
//----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//----------------------------------------------------------------------------
#include "main.h"

//----------------------------------------------------------------------------
// �}�N����`
//----------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CSceneBase;

class CTexAnimationBase
{
public:
	CTexAnimationBase();									//�R���X�g���N�^
	~CTexAnimationBase();									//�f�X�g���N�^

	bool UpdateAnimation();			//�X�V
	D3DXVECTOR2 CalcUV();

	//Set�֐�
	void SetTex(CTexture::SEPARATE_TEX_TYPE Tex)		{ m_EffectTex = Tex; };				//�e�N�X�`���ݒ�
	void SetLife(int nLife)								{ m_nLife = nLife; };				//���C�t
	void SetCntSwitch(int nCntSwitch)					{ m_nCntSwitch = nCntSwitch; };		//�ؑւ̃t���[��
	void SetLoop(bool bLoop)							{ m_bLoop = bLoop; };				//���[�v���邩

	//Get�֐�
	CTexture::SEPARATE_TEX_TYPE GetEffectTex()			{ return m_EffectTex; };			//�g���Ă�e�N�X�`���擾
	int GetLife()										{ return m_nLife; };				//���C�t
	int GetCntSwitch()									{ return m_nCntSwitch; };			//�ؑւ̃t���[��
	int GetLoop()										{ return m_bLoop; };				//���[�v���邩

	int GetCntAnim()									{ return m_nCntAnim; };				//�A�j���[�V�����J�E���^
	int GetPatternAnim()								{ return m_nPatternAnim; };			//�A�j���[�V�����p�^�[��
	bool GetEndFlag()									{ return m_bEnd; };					//�I���t���O
private:
	CTexture::SEPARATE_TEX_TYPE m_EffectTex;				//�G�t�F�N�g�̃^�C�v
	int m_nLife;											//���C�t�@�A�j���[�V�����I���ŏ����Ȃ��G�t�F�N�g�i���[�v�Ƃ��j�p
	int m_nCntAnim;											//�A�j���[�V�����J�E���^�[
	int m_nPatternAnim;										//�A�j���[�V�����p�^�[��
	int m_nCntSwitch;										//�A�j���[�V�����ؑւ̃t���[��
	bool m_bLoop;											//�A�j���[�V�������[�v���邩
	bool m_bEnd;											//�I���t���O

};

#endif