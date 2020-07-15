//------------------------------------------------------------------------------
//
//�e�N�X�`���A�j���[�V�����̊��N���X  [TexAnimationBase.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "manager.h"
#include "TexAnimationBase.h"
#include "SceneBase.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CTexAnimationBase::CTexAnimationBase()
{
	//������
	m_nPatternAnim = 0;
	m_nCntAnim = 0;
	m_nCntSwitch = 0;
	m_nLife = 120;
	m_bLoop = false;
	m_EffectTex = CTexture::SEPARATE_TEX_EFFECT_EXPLOSION01;
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CTexAnimationBase::~CTexAnimationBase()
{
}

//------------------------------------------------------------------------------
//�A�j���[�V�����̍X�V
//�A�j���[�V�����I����false��Ԃ�
//------------------------------------------------------------------------------
bool CTexAnimationBase::UpdateAnimation()
{
	if (m_nLife-- <= 0)
	{
		//�I���t���Otrue
		m_bEnd = true;

		return false;
	}
	//�J�E���^�[��i�߂�
	m_nCntAnim++;

	//2�t���[�����Ƃ�
	if (m_nCntAnim % m_nCntSwitch == 0)
	{
		//�p�^�[����i�߂�
		m_nPatternAnim++;

		//�Ō�̃p�^�[���܂Ői�񂾎�
		if (m_nPatternAnim >= CTexture::GetSparateTex_UVCnt(m_EffectTex).x *  CTexture::GetSparateTex_UVCnt(m_EffectTex).y)
		{
			m_bLoop ?
				m_nPatternAnim = 0 :		//���[�v���鎞		�p�^�[���ŏ��ɖ߂�
				m_bEnd = true;				//���[�v���Ȃ����@	�t���O�𗧂Ă�
			return true;
		}
	}
	return false;
}

D3DXVECTOR2 CTexAnimationBase::CalcUV(int nPatternAnim, CTexture::SEPARATE_TEX_TYPE tex)
{
	//UV���W�v�Z
	D3DXVECTOR2 UV;
	UV.x = nPatternAnim % (int)CTexture::GetSparateTex_UVCnt(tex).x * CTexture::GetSparateTex_UVSize(tex).x;
	UV.y = nPatternAnim / (int)CTexture::GetSparateTex_UVCnt(tex).x * CTexture::GetSparateTex_UVSize(tex).y;

	//return
	return UV;
}

