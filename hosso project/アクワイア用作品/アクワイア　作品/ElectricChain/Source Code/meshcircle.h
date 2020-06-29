//------------------------------------------------------------------------------
//
//���b�V���t�B�[���h����  [meshfield.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MESHCIRCLE_H_
#define _MESHCIRCLE_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "mesh.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CMeshCircle : public CMesh
{
public:
	CMeshCircle();
	~CMeshCircle();

	HRESULT Init();				//������
	void Uninit();				//�I��
	void Update();				//�X�V
	void Draw();				//�`��
	void ShowDebugInfo();		//�f�o�b�O���\�L
	D3DXVECTOR3 SetVtx(INTEGER2 nCnt, INTEGER2 BlockNum);				//���_�ݒ�

	//Set
	void SetSize(D3DXVECTOR3 size) {  };						//�T�C�Y
	void SetRadius(float fRadius) { m_fRadius = fRadius; };		//���a
	void SetWidth(float fWidth) { m_fWidth = fWidth; };			//��


	//Get
	D3DXVECTOR3 GetSize() { return D3DXVECTOR3(m_fRadius,0.0f, m_fRadius); };	//�T�C�Y
	float &GetRadius() { return m_fRadius; };									//���a
	float &GetWidth() { return m_fWidth; };										//��

	static std::shared_ptr<CMeshCircle> Create(D3DXVECTOR3 const pos, float fRadius, float fWidth, INTEGER2 const BlockNum);	//��������

protected:

private:
	float m_fRadius;	//���a
	float m_fWidth;		//��

};
#endif