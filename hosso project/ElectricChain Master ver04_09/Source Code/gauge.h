//-----------------------------------------------------------------------------
//
//�Q�[�W����  [gauge.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _GAUGE_H_
#define _GAUGE_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CGauge : public::CScene
{
public:
	CGauge();		//�R���X�g���N�^
	~CGauge();		//�f�X�g���N�^

	enum GAUGETYPE
	{
		GAUGE_FLAME = 0,	//�Q�[�W�g
		GAUGE_RED,			//�ԃQ�[�W�@�_���[�W�H�������������Ƃ�����
		GAUGE_BLUE,			//�Q�[�W�@���_���[�W�@�S�����Ȃ�����X�^��
		GAUGE_GREEN,		//�΃Q�[�W
		GAUGE_MAX
	};

	virtual HRESULT Init();					//������
	virtual void Uninit();					//�I��
	virtual void Update();					//�X�V
	virtual void Draw();					//�`��
	virtual void ShowDebugInfo();			//�f�o�b�O���\�L

	virtual void UpdateGaugeMag(float GreenMag, float RedMag, float BlueMag) = 0;		//�Q�[�W�̔{���v�Z�@�I�[�o�[���C�h�p

	void SetLife(int nLife, int nBlueLife);	//���C�t�ݒ�
	void SetMaxLife(int nMaxLife);			//�ő僉�C�t�ݒ�
	void DeleteGauge();						//�Q�[�W����

	int GetLife() { return m_nLife; };		//���C�t�̒l�擾
protected:

private:
	int m_nMaxLife;							//�ő�HP
	int m_nLife;							//HP
	int m_nLifeBlue;						//HP�̐Ԃ�����
	int m_nLifeRed;							//HP�̐Ԃ�����
	int m_nLifeRedInterval;					//�Ԃ�����������n�߂�܂ł̎���
	int m_nRedGaugeDeleteSpeed;				//�Ԃ������̌��鑬�x
	void CalcGaugeMag();					//�Q�[�W�̔{���v�Z
};

#endif