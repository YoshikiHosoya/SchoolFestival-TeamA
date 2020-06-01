//-----------------------------------------------------------------------------
//
//2D�Q�[�W����  [2Dgauge.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _GAUGE_2D_H_
#define _GAUGE_2D_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "gauge.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CScene2D;

class CGauge_2D : public::CGauge
{
public:
	CGauge_2D();			//�R���X�g���N�^
	~CGauge_2D();			//�f�X�g���N�^


	HRESULT Init();			//������
	void Uninit();			//�I��
	void Update();			//�X�V
	void Draw();			//�`��
	void ShowDebugInfo();	//�f�o�b�O���\�L
	static std::shared_ptr<CGauge_2D> Create(D3DXVECTOR3 const &pos, D3DXVECTOR3 const &gaugeSize,int const nMaxLife);

	void UpdateGaugeMag(float GreenMag, float RedMag, float BlueMag);	//�Q�[�W�̍X�V����
	void SetPos(D3DXVECTOR3 const &pos);								//���W�ݒ�
protected:

private:
	std::vector<std::shared_ptr<CScene2D>> m_pScene2DList;		//2D�|���S���̃��X�g
	void MakeGauge(D3DXVECTOR3 pos, D3DXVECTOR3 size);			//�Q�[�W����
};

#endif