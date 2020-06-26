//------------------------------------------------------------------------------
//
//�~�̃G�t�F�N�g����  [circle_effect.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _CIRCLE_EFFECT_H_
#define _CIRCLE_EFFECT_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "meshcircle.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CCircle_Effect : public CMeshCircle
{
public:
	CCircle_Effect();			//�R���X�g���N�^
	~CCircle_Effect();			//�f�X�g���N�^

	HRESULT Init();				//������
	void Uninit();				//�I��
	void Update();				//�X�V
	void Draw();				//�`��
	void ShowDebugInfo();		//�f�o�b�O���\�L

	static std::shared_ptr<CCircle_Effect> Create(D3DXVECTOR3 const pos,D3DXCOLOR col, int const nLife, float const fRadius ,float const fWidth, int const nSeparate,
												float const fRaidiusAddValue, float const fWidthAddValue,float const fAlphaDanpingValue);	//��������

private:
	int m_nLife;						//���C�t
	float m_fAlphaDampingValue;			//�A���t�@�l�̌�����
	float m_fRadiusAddValue;			//���a�̑�����
	float m_fWidthAddValue;				//���̑�����
};
#endif