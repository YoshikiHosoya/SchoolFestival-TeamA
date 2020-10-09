//------------------------------------------------------------------------------
//
//��  [way.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _WAY_H_
#define _WAY_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scene2D.h"

//------------------------------------------------------------------------------
//�O���錾
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CWay : public CScene2D
{
public:

	enum WAY_TYPE
	{
		UP,
		RIGHT_01,
		RIGHT_02,
		LEFT_01,
		LEFT_02,

	};

	CWay();																					//�R���X�g���N�^
	~CWay();																				//�f�X�g���N�^

	virtual HRESULT Init();																	//������
	virtual void Uninit();																	//�I��
	virtual void Update();																	//�X�V
	virtual void Draw();																	//�`��
	virtual void ShowDebugInfo();															//�f�o�b�O���\�L
	static std::shared_ptr<CWay> Create(D3DXVECTOR3 pos,WAY_TYPE waytype);					//����

	WAY_TYPE GetWayType() { return m_waytype; };

protected:

private:
	WAY_TYPE m_waytype;

};
#endif