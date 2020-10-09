//------------------------------------------------------------------------------
//
//���b�V���V�����_�[����  [meshcylinder.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "mesh.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CMeshCylinder : public CMesh
{
public:
	CMeshCylinder();
	~CMeshCylinder();

	HRESULT Init();				//������
	void Uninit();				//�I��
	void Update();				//�X�V
	void Draw();				//�`��
	void ShowDebugInfo();		//�f�o�b�O���\�L
	D3DXVECTOR3 SetVtx(INTEGER2 nCnt, INTEGER2 BlockNum);		//���_�ݒ�
	void SetSize(D3DXVECTOR3 size) { m_size = size; };			//�T�C�Y�ݒ�
	static std::shared_ptr<CMeshCylinder> Create(D3DXVECTOR3 const pos, D3DXVECTOR3 const onesize, INTEGER2 const BlockNum, D3DXMATRIX *pMtx);	//��������

protected:

private:
	D3DXMATRIX *m_pParentMtx;			//�e�̃}�g���b�N�X�̃|�C���^
	D3DXVECTOR3 m_size;					//�T�C�Y

};
#endif