//------------------------------------------------------------------------------
//
//�^�C�}�[�\������  [timer.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _TIMER_H_
#define _TIMER_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------

//�O���錾
class CMultiNumber;

class CTimer : public CScene
{
public:
	CTimer();
	~CTimer();
	HRESULT Init();																//������
	void Uninit();																//�I��
	void Update();																//�X�V
	void Draw();																//�`��
	void ShowDebugInfo();														//�f�o�b�O���\�L
	static std::unique_ptr<CTimer> Create(D3DXVECTOR3 pos,int nTimer);			//��������
	static int GetTimer();														//�^�C�}�[�擾
	void StopTimer();															//�^�C�}�[�X�g�b�v
private:
	std::shared_ptr<CMultiNumber> m_pMultiNumber;								//�i���o�[�̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture;										//�e�N�X�`���̃|�C���^

	static int m_nTimer;														//�^�C�}�[ �b�ŊǗ�
	int m_nCntFlame;															//�J�E���g �t���[��
	bool m_bStop;																//�X�g�b�v
};

#endif