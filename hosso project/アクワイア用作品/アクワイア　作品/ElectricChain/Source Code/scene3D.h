//------------------------------------------------------------------------------
//
//�V�[��3D����  [scene3D.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _SCENE3D_H_
#define _SCENE3D_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CScene3D : public CScene
{
public:

	CScene3D();
	virtual ~CScene3D();

	virtual HRESULT Init();								//������
	virtual void Uninit();								//�I��
	virtual void Update();								//�X�V
	virtual void Draw();								//�`��
	virtual void ShowDebugInfo();						//�f�o�b�O���\�L

	void DrawSettingMtx(D3DXMATRIX const &Mtx);				//�n�����Ōv�Z�������[���h�}�g���b�N�X�����ɕ`��
	void DrawPolygon();

	void SetPos(D3DXVECTOR3 pos);								//���W�ݒ�
	void SetSize(D3DXVECTOR3 size);								//�T�C�Y�ݒ�
	void SetRot(D3DXVECTOR3 rot);								//��]�ݒ�
	void SetVtxCol(D3DXCOLOR col);								//���_�J���[�ݒ�
	void SetAnimation(D3DXVECTOR2 UV, D3DXVECTOR2 size);		//�e�N�X�`��UV���W�ݒ�
	void SetNormal();											//�@���ݒ�

	void SetBboard(bool bBboard)	{m_bBboard = bBboard;};		//�r���{�[�h��
	void SetDisp(bool bDisp)		{m_bDisp = bDisp;};			//�\����\���ݒ�

	void UpdateGauge(float fMag);								//�Q�[�W�p�̍X�V����

	D3DXVECTOR3 &GetPos()			{ return m_pos; };			//���W�擾����
	D3DXVECTOR3 &GetSize()			{ return m_size; };			//�T�C�Y�擾����
	D3DXVECTOR3 &GetRot()			{ return m_rot; };			//��]�ʎ擾����

	D3DXCOLOR &GetCol()				{ return m_col; };			//�F���擾����
	bool GetDisp()					{ return m_bDisp; };		//��ʂɉf���Ă邩�擾
	D3DXMATRIX *GetMtxPtr()			{ return &m_mtxWorld; };	//���[���h�}�g���b�N�X�擾 �|�C���^

	static std::shared_ptr<CScene3D> Create_Shared(D3DXVECTOR3 pos, D3DXVECTOR3 size, OBJTYPE objtype);	//���������i���L�Ǘ�
	static void Create_SceneManagement(D3DXVECTOR3 pos, D3DXVECTOR3 size, OBJTYPE objtype);				//���������iCScene�݂̂ŊǗ�
	static std::unique_ptr<CScene3D> Create_SelfManagement(D3DXVECTOR3 pos, D3DXVECTOR3 size);			//���������iReturn��ŊǗ�

	void BindTexture(LPDIRECT3DTEXTURE9 pTex) { m_pTexture = pTex; };									//�e�N�X�`���ݒ�
	static int GetNumScene3D() { return m_nNumScene3D; };												//3D�|���S�������擾

private:
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;					//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9		m_pTexture;					//�e�N�X�`���ւ̃|�C���^
	static int m_nNumScene3D;

	D3DXVECTOR3 m_pos;									//���W
	D3DXVECTOR3 m_size;									//�傫��
	D3DXVECTOR3 m_rot;									//��]
	D3DXCOLOR m_col;									//�F
	bool m_bBboard;										//�r���{�[�h���ǂ���
	bool m_bDisp;										//��ʂɎʂ����ǂ���

	D3DXMATRIX		m_mtxWorld;							//���[���h�}�g���b�N�X
	VERTEX_3D		m_Vtx3D[4];							//���_���@debug�p
};
#endif