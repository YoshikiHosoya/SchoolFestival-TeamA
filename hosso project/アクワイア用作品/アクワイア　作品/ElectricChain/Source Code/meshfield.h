//------------------------------------------------------------------------------
//
//���b�V���t�B�[���h����  [meshfield.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "mesh.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CMeshField : public CMesh
{
public:
	CMeshField();
	~CMeshField();

	HRESULT Init();												//������
	void Uninit();												//�I��
	void Update();												//�X�V
	void Draw();												//�`��
	void ShowDebugInfo();										//�f�o�b�O���\�L
	D3DXVECTOR3 SetVtx(INTEGER2 nCnt, INTEGER2 BlockNum);		//���_�ݒ�

	//Set
	void SetSize(D3DXVECTOR3 size) { m_size = size; };			//�T�C�Y�ݒ�

	//Get
	D3DXVECTOR3 GetSize() { return m_size; };					//�T�C�Y�擾

	static std::shared_ptr<CMeshField> Create(D3DXVECTOR3 const pos, D3DXVECTOR3 const onesize, INTEGER2 const BlockNum);	//��������
	bool GetHeight(D3DXVECTOR3 &pos);					//�����擾

protected:

private:
	D3DXVECTOR3 m_size;		//�T�C�Y


};
#endif