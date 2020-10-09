//------------------------------------------------------------------------------
//
//�i���o�[����  [number.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _NUMBER_H_
#define _NUMBER_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scene2D.h"
#include "TexAnimationBase.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CNumber : public CScene2D ,public CTexAnimationBase
{
public:
	CNumber();
	~CNumber();

	HRESULT Init();																			//������
	void Uninit();																			//�I��
	void Update();																			//�X�V
	void Draw();																			//�`��
	void ShowDebugInfo();																	//�f�o�b�O���\��
	static std::unique_ptr<CNumber> Create(D3DXVECTOR3 pos , D3DXVECTOR3 size);				//��������
	void SetChangeAnimtion() { m_bChangeAnimation = true; m_nCntAnimation = 0; };			//�������ς�����A�j���[�V�����ݒ�
private:
	static D3DXVECTOR2 m_UVsize;															//�e�N�X�`����UV�T�C�Y
	D3DXVECTOR3 m_DefaultSize;																//�����̑傫��
	bool m_bChangeAnimation;																//���l���؂�ւ�������ɃA�j���[�V����
	int m_nCntAnimation;																	//�A�j���[�V�����p�̃J�E���^

};

#endif