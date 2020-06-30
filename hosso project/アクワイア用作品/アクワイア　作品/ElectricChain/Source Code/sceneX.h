//------------------------------------------------------------------------------
//
//X�t�@�C�����f������  [SceneX.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MODEL_H_
#define _MODEL_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CSceneX : public CScene
{
public:
	//�}�e���A���J���[
	enum MATERIAL_COL
	{
		MAT_NORMAL = -1,
		MAT_ENEMY_BLACK,
		MAT_ENEMY_GREEN,
		MAT_MAX
	};

	CSceneX();
	virtual ~CSceneX();

	virtual HRESULT Init();						//������
	virtual void Uninit();						//�I��
	virtual void Update();						//�X�V
	virtual void Draw();						//�`��
	void DrawMesh();							//���f���̃��b�V���`��
	void DrawShadow();							//�e�̕`��
	virtual void ShowDebugInfo();				//�f�o�b�O���\�L


	void SetPos(D3DXVECTOR3 pos)							{ m_pos = pos; };					//���W�ݒ�
	void SetRot(D3DXVECTOR3 rot)							{ m_rot = rot; };					//��]�ݒ�
	void SetMaterialCol(MATERIAL_COL matcol)				{ m_MatCol = matcol; };				//�}�e���A���J���[�ݒ�

	D3DXVECTOR3 &GetPos()									{ return m_pos; };					//���W�擾����
	D3DXVECTOR3 &GetRot()									{ return m_rot; };					//��]�擾����
	D3DXMATRIX *GetMtx()									{ return &m_mtxWorld; };			//�}�g���b�N�X�擾
	MATERIAL_COL GetMaterialCol()							{ return m_MatCol; };				//�}�e���A���J���[�擾

	static CSceneX *Create(D3DXVECTOR3 pos,OBJTYPE objtype);		//��������
	static int GetNumSceneX() { return m_nNumSceneX; };				//���擾
	void BindModelInfo(std::shared_ptr<CModelInfo> pSceneXInfo) { m_SceneXInfo = pSceneXInfo; };	//���f���Z�b�g

private:
	static int m_nNumSceneX;									//�����J�E���g
	static std::vector<D3DMATERIAL9> m_MaterialColor[MAT_MAX];	//�}�e���A���̐F

	D3DXVECTOR3 m_pos;											//���W
	D3DXVECTOR3 m_rot;											//��]
	D3DXMATRIX	m_mtxWorld;										//���[���h�}�g���b�N�X
	MATERIAL_COL m_MatCol;										//�}�e���A���J���[
	std::shared_ptr<CModelInfo>	m_SceneXInfo;					//���f�����
};
#endif