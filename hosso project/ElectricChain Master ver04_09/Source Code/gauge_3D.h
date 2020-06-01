//-----------------------------------------------------------------------------
//
//3D�Q�[�W����  [3Dgauge.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _GAUGE_3D_H_
#define _GAUGE_3D_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "gauge.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CScene3D;

class CGauge_3D : public::CGauge
{
public:
	CGauge_3D();			//�R���X�g���N�^
	~CGauge_3D();			//�f�X�g���N�^


	HRESULT Init();			//������
	void Uninit();			//�I��
	void Update();			//�X�V
	void Draw();			//�`��
	void ShowDebugInfo();	//�f�o�b�O���\�L
	static std::shared_ptr<CGauge_3D> Create(D3DXVECTOR3 const &pos, D3DXVECTOR3 const &gaugeSize, D3DXVECTOR3 const &offset,int const nMaxLife, D3DXMATRIX mtx);		//��������

	void UpdateGaugeMag(float GreenMag, float RedMag, float BlueMag);	//�Q�[�W�̍X�V����
	void SetPos(D3DXVECTOR3 const &pos);								//���W�ݒ�
	void SetMtx(D3DXMATRIX mtx);										//�}�g���b�N�X�ݒ�
	void SetFlash(bool bFlash) { m_bFlashing = bFlash; };				//�t���b�V����Ԑݒ�

private:
	std::vector<std::shared_ptr<CScene3D>> m_pScene3DList;				//3D�|���S���̃��X�g
	D3DXVECTOR3 m_offset;												//�����傩��Q�[�W�܂ł̃I�t�Z�b�g
	D3DXMATRIX m_Mtx;													//������̃}�g���b�N�X
	bool m_bFlashing;													//�_�ŏ��
	int m_nCntFlash;													//�_�ŗp�̃J�E���^
	void MakeGauge(D3DXVECTOR3 pos, D3DXVECTOR3 size);					//�Q�[�W����
};

#endif