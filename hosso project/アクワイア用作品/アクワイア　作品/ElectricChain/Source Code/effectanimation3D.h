//------------------------------------------------------------------------------
//
//�G�t�F�N�g�A�j���[�V��������  [effectanimation.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _EFFECTANIMATION_H_
#define _EFFECTANIMATION_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scene3D.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CEffectAnimation3D : public CScene3D
{
public:
	CEffectAnimation3D();		//�R���X�g���N�^
	~CEffectAnimation3D();		//�f�X�g���N�^

	HRESULT Init();				//������
	void Uninit();				//�I��
	void Update();				//�X�V
	void Draw();				//�`��
	void ShowDebugInfo();		//�f�o�b�O���\��
	static void Create(D3DXVECTOR3 pos , D3DXVECTOR3 size, CTexture::SEPARATE_TEX_TYPE type,D3DXCOLOR col, float fAngle,int nCntSwitch);	//��������

private:
	CTexture::SEPARATE_TEX_TYPE m_Type;						//�G�t�F�N�g�̃^�C�v
	int m_nCntAnim;											//�A�j���[�V�����J�E���^�[
	int m_nPatternAnim;										//�A�j���[�V�����p�^�[��
	int m_nCntSwitch;										//1�R�}������̎��� �؂�ւ��܂ł̎���

	static std::vector<std::string> m_apFileName;			//�t�@�C����
};

#endif