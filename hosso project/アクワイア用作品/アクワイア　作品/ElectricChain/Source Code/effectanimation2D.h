//------------------------------------------------------------------------------
//
//�G�t�F�N�g�A�j���[�V����2D����  [effectanimation2D.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _EFFECTANIMATION2D_H_
#define _EFFECTANIMATION2D_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scene2D.h"
#include "scene.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CEffectAnimation2D : public CScene2D
{
public:
	CEffectAnimation2D();		//�R���X�g���N�^
	~CEffectAnimation2D();		//�f�X�g���N�^

	HRESULT Init();				//������
	void Uninit();				//�I��
	void Update();				//�X�V
	void Draw();				//�`��
	void ShowDebugInfo();		//�f�o�b�O���\��
	static void Create(D3DXVECTOR3 pos , D3DXVECTOR3 size,CTexture::SEPARATE_TEX_TYPE type,float fAngle, int nCntSwitch,OBJTYPE objtype);	//��������

private:
	CTexture::SEPARATE_TEX_TYPE m_Type;						//�G�t�F�N�g�̃^�C�v
	int m_nCntAnim;											//�A�j���[�V�����J�E���^�[
	int m_nPatternAnim;										//�A�j���[�V�����p�^�[��
	int m_nCntSwitch;										//�A�j���[�V�����ؑւ̃t���[��

	static std::vector<std::string> m_apFileName;			//�t�@�C����
};

#endif