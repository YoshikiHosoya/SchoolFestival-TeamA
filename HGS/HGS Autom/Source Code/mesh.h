//------------------------------------------------------------------------------
//
//���b�V������  [mesh.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MESH_H_
#define _MESH_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"
#include "hossolibrary.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CMesh : public CScene
{
public:
	//���b�V���̎��
	enum MESHTYPE
	{
		MESH_FIELD = 0,		//�t�B�[���h
		MESH_WALL,			//�E�H�[��
		MESH_CYLINDER,		//�V�����_�[
		MESH_SPHERE			//�X�t�B�A
	};

	CMesh();
	~CMesh();

	virtual HRESULT Init();				//������
	virtual void Uninit();				//�I��
	virtual void Update();				//�X�V
	virtual void Draw();				//�`��
	virtual void ShowDebugInfo();		//�f�o�b�O���\�L
	virtual D3DXVECTOR3 SetVtx(INTEGER2 nCnt, INTEGER2 BlockNum) = 0;				//���_�ݒ菈��
	virtual void SetSize(D3DXVECTOR3 size) = 0;				//�T�C�Y�ݒ�@�I�[�o�[���C�h�p
	void MakeVertex();										//���_����

	void SetTexSphere();									//�e�N�X�`��UV���W�ݒ� ���̗p
	void SetNormal();										//�@���ݒ�
	void SetTex(bool bTex) { m_bTex = bTex; };				//�e�N�X�`���ݒ�

	void SetPos(D3DXVECTOR3 const& pos)				{ m_pos = pos; };				//���W�ݒ�
	void SetRot(D3DXVECTOR3 const& rot)				{ m_rot = rot; };				//��]�ݒ�
	void SetBlockNum(INTEGER2 const& blocknum)		{ m_BlockNum = blocknum; };		//�u���b�N���ݒ�
	void BindTexture(LPDIRECT3DTEXTURE9 pTex)		{ m_pTexture = pTex; };			//�e�N�X�`���Z�b�g
	void SetCol(D3DXCOLOR const& col);								//�F�ݒ�@�F�X����̂ŃC�����C������Ȃ�
	void ResetVtx (D3DXVECTOR3 size);								//�T�C�Y�擾���Ē��_���Đݒ�

	D3DXVECTOR3 &GetPos()		{ return m_pos; };					//���W�擾����
	D3DXVECTOR3 &GetRot()		{ return m_rot; };					//��]�ʎ擾
	INTEGER2	&GetBlockNum()	{ return m_BlockNum; };				//�u���b�N���擾
	D3DXCOLOR	&GetCol()		{ return m_col; };					//�F�擾
	D3DXMATRIX	*GetMtx()		{ return &m_mtxWorld; };			//���[���h�}�g���b�N�X�擾
	static int GetNumMesh()		{ return m_nNumMesh; };				//�����擾
protected:
	std::vector<std::unique_ptr<D3DXVECTOR3>>	m_apNormalList;		//�ʂ̖@���̃|�C���^
	std::vector<std::unique_ptr<VERTEX_3D>>		m_pVtxMeshList;		//���_���@�ۑ��p

private:
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9		m_pTexture;			//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuff;			//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^

	static int m_nNumMesh;			//����
	D3DXVECTOR3 m_pos;				//���W
	D3DXVECTOR3 m_rot;				//��]
	D3DXCOLOR m_col;				//�F
	MESHTYPE m_type;				//���
	INTEGER2 m_BlockNum;			//�u���b�N��
	int m_nNumVertex;				//���_��
	int m_nNumIdx;					//�C���f�b�N�X��
	int m_nNumPolygon;				//�|���S����
	bool m_bTex;					//�e�N�X�`���g�����ǂ���
	D3DXMATRIX		m_mtxWorld;		//���[���h�}�g���b�N�X
};
#endif