//------------------------------------------------------------------------------
//
//���b�V���X�t�B�A����  [meshsphere.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MESHSPHERE_H_
#define _MESHSPHERE_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "mesh.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CMeshSphere : public CMesh
{
public:
	CMeshSphere();
	~CMeshSphere();

	virtual HRESULT Init();												//������
	virtual void Uninit();												//�I��
	virtual void Update();												//�X�V
	virtual void Draw();												//�`��
	virtual void ShowDebugInfo();										//�f�o�b�O���\�L
	static std::shared_ptr<CMeshSphere> Create(D3DXVECTOR3 const pos, float const fRadius, INTEGER2 const BlockNum);	//��������

	D3DXVECTOR3 SetVtx(INTEGER2 nCnt, INTEGER2 BlockNum);				//���_�ݒ�
	void SetSize(D3DXVECTOR3 size) { m_fRadius = size.x; };				//�T�C�Y�ݒ�
	float &GetRadius() { return m_fRadius; };							//���a�擾

protected:

private:
	float m_fRadius;			//���a
};
#endif