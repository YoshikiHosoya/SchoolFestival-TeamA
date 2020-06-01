//------------------------------------------------------
//
//	�L���萔�Ƌ^������
//
//--------------------------------------------------------
#ifndef _SCORE_H_
#define _SCORE_H_
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
#define SCORE_DIGIT (8)			//����
#define SCOREX	(20)			//��
#define SCOREY	(40)			//����
#define SCORE_POSX	(900.0f)	//X���W
#define SCORE_POSY	(50.0f)		//Y���W
#define SCORE_SPACE	(40.0f)		//�X�R�A�̊Ԋu
#define SCORE_UP	(500)		// �X�R�A�̏㏸

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
class CScore :public CScene
{
public:
	//�֐��錾
	CScore();//�R���X�g���N�^ (�C���X�^���X�����������Ǝ����I�ɌĂяo�����)
	~CScore();//�f�X�g���N�^ (�C���X�^���X���j�������Ǝ����I�ɌĂяo�����)

	void Init(void);//������
	void Uninit(void);//�I��
	void Update(void);//�X�V
	void Draw(void);//�`��

	static CScore * Create(void);//����
	void AddScore(int nValue);//�X�R�A�̒ǉ�
	void SetPosition(D3DXVECTOR3 pos);//���W�̐ݒ�
	int GetScore(void);					// �X�R�A�̎擾
private:

	//�ÓI�ϐ��錾

	//�ϐ��錾
	CNumber *m_apNumber[SCORE_DIGIT];//�������̔z��
	D3DXVECTOR3 m_pos;//���W
	int m_nScore;
};
#endif

