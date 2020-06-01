//------------------------------------------------------
//
//	�L���萔�Ƌ^������
//
//--------------------------------------------------------
#ifndef _TIME_H_
#define _TIME_H_
//------------------------------------------------------
//
//	�C���N���[�h�t�@�C��
//
//--------------------------------------------------------
#include "scene.h"
#include "renderer.h"
#include "number.h"
//------------------------------------------------------
//
//	�}�N����`
//
//--------------------------------------------------------
#define TIME_DIGIT (3)//����
#define TIMEX	(20)//��
#define TIMEY	(40)//����
#define TIME_POSX	(1025.0f)//X���W
#define TIME_POSY	(150.0f)//Y���W
#define TIME_SPACE	(40.0f)//�Ԋu
//------------------------------------------------------
//
//	�O���錾
//
//--------------------------------------------------------
class CScene;
//===========================================================
//
//	�N���X�^�̒�`
//
//===========================================================
class CTime :public CScene
{
public:

	//�֐��錾
	CTime();//�R���X�g���N�^ (�C���X�^���X�����������Ǝ����I�ɌĂяo�����)
	~CTime();//�f�X�g���N�^ (�C���X�^���X���j�������Ǝ����I�ɌĂяo�����)

	void Init(void);//������
	void Uninit(void);//�I��
	void Update(void);//�X�V
	void Draw(void);//�`��

	static CTime * Create(void);//����
	void SetPosition(D3DXVECTOR3 pos);//���W�̐ݒ�
	void DecreasesTime(void);//���Ԃ̌���

	bool GetTimeOverFlag(void);

private:

	//�ÓI�ϐ��錾

	//�ϐ��錾
	CNumber *m_apNumber[TIME_DIGIT];//�������̕ϐ�
	D3DXVECTOR3 m_pos;//���W
	int m_nTime;//����
	bool m_bTimeOver;
};
#endif

