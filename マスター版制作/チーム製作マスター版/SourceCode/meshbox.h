//------------------------------------------------------------------------------
//
//���b�V���{�b�N�X����  [meshbox.h]
//Author:fujiwaramasato
//
//------------------------------------------------------------------------------
#ifndef _MESHBOX_H_
#define _MESHBOX_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CMeshBox : public CScene
{
public:

	//���b�V���̎��
	enum COLLISION_TYPE
	{
		TYPE_CENTER, // ���W�����S
		TYPE_GROUND	 // �n�ʂ����S
	};

	CMeshBox();
	CMeshBox(OBJ_TYPE obj) : CScene(obj) {};
	~CMeshBox();

	HRESULT Init();																//������
	void Uninit();																//�I��
	void Update();																//�X�V
	void Draw();																//�`��
	void DebugInfo();															//�f�o�b�O���\�L

	void MakeVertex();															//���_����
	void SetTexPos();															//�e�N�X�`��UV���W�ݒ�

	void SetPos(D3DXVECTOR3 const& pos);										//���W�ݒ�
	void SetCol(D3DXCOLOR const& col);											//�F�ݒ�
	void SetSize(D3DXVECTOR3 size);												//�T�C�Y�ݒ�

	D3DXVECTOR3 &GetPos() { return m_pos; };									//���W�擾����
	D3DXVECTOR3 &GetRot() { return m_rot; };									//��]�ʎ擾
	D3DXCOLOR	&GetCol() { return m_col; };									//�F�擾
	D3DXMATRIX	*GetMtx() { return &m_mtxWorld; };								//���[���h�}�g���b�N�X�擾
	D3DXVECTOR3 GetSize() { return m_size; };									//�T�C�Y�擾

	static CMeshBox *Create(D3DXVECTOR3 const &pos, D3DXVECTOR3 const &onesize ,
		COLLISION_TYPE  const &type);	//��������

protected:

private:
	D3DXMATRIX				m_mtxWorld;			// ���[���h�}�g���b�N�X
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuff;			// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;				// ���W
	D3DXVECTOR3				m_size;				// �T�C�Y
	D3DXVECTOR3				m_rot;				// ��]
	D3DXCOLOR				m_col;				// �F
	COLLISION_TYPE			m_Type;
};
#endif