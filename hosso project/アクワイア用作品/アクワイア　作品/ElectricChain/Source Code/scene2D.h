//------------------------------------------------------------------------------
//
//�V�[��2D����  [scene2D.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _SCENE2D_H_
#define _SCENE2D_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CScene2D : public CScene
{
public:
	CScene2D();
	virtual ~CScene2D();

	virtual HRESULT Init();					//������
	virtual void Uninit();					//�I��
	virtual void Update();					//�X�V
	virtual void Draw();					//�`��
	virtual void ShowDebugInfo();			//�f�o�b�O���\�L

	void UpdateGauge(float fMag);			//�Q�[�W�p

	//Set�֐�
	void SetPos(D3DXVECTOR3 pos);							//���W�ݒ�
	void SetSize(D3DXVECTOR3 size);							//�T�C�Y�ݒ�
	void SetVtxCol(D3DXCOLOR col);							//���_�J���[�ݒ�
	void SetAngle(float fAngle);							//��]�̊p�x�ݒ�
	void SetAnimation(D3DXVECTOR2 UV,D3DXVECTOR2 size);		//�e�N�X�`��UV���W�ݒ�
	void SetDisp(bool bDisp) { m_bDisp = bDisp; };

	//Get�֐�
	D3DXVECTOR3 &GetPos()	{ return m_pos; };				//���W�擾����
	D3DXVECTOR3 &GetSize()	{ return m_size; };				//�T�C�Y�擾����
	D3DXCOLOR &GetCol()		{ return m_col; };				//�F���擾
	float &GetAngle()		{ return m_fAngle; };			//�p�x���擾
	bool &GetDisp()			{ return m_bDisp; };			//�`�悷�邩�ǂ����̔���擾

	static std::shared_ptr<CScene2D> Create_Shared			(D3DXVECTOR3 pos, D3DXVECTOR3 size, OBJTYPE objtype);	//���������i���L�Ǘ�
	static void Create_SceneManagement						(D3DXVECTOR3 pos, D3DXVECTOR3 size, OBJTYPE objtype);	//���������iCScene�݂̂ŊǗ�
	static std::unique_ptr<CScene2D> Create_SelfManagement	(D3DXVECTOR3 pos, D3DXVECTOR3 size);					//���������iReturn��ŊǗ�


	void BindTexture(LPDIRECT3DTEXTURE9 pTex)	{ m_pTexture = pTex; };						//�e�N�X�`�����ݒ�
	static int GetNumScene2D()					{ return m_nNumScene2D; };					//2D�̑����擾

	bool Collision(D3DXVECTOR3 const &pos);
private:
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = NULL;	//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^
	static int m_nNumScene2D;			//����

	D3DXVECTOR3 m_pos;					//���W
	D3DXVECTOR3 m_size;					//�傫��
	D3DXVECTOR3 m_rot;					//��]
	D3DXCOLOR m_col;					//�F
	D3DXCOLOR m_colalpha;				//�������������̎��Ɏg��
	float m_fLength;					//����
	float m_fAngle;						//�p�x
	bool m_bDisp;						//�`�悷�邩�ǂ���
};

#endif