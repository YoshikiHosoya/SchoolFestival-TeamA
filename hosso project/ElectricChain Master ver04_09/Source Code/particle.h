//------------------------------------------------------------------------------
//
//�p�[�e�B�N������  [particle.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _PARTICLE_H_
#define _PARTICLE_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define MAX_PARTICLE (10000)
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
//�p�[�e�B�N���̗��q
class COneParticle
{
	public:
		COneParticle() { nNumParticleAll++; };		//�R���X�g���N�^
		~COneParticle() { nNumParticleAll--; };		//�f�X�g���N�^

	//�����֐�
	static std::unique_ptr<COneParticle> Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot)
	{
		//�������m��
		std::unique_ptr<COneParticle> pOneParticle(new COneParticle);

		//�����
		pOneParticle->m_pos = pos;
		pOneParticle->m_move = move;
		pOneParticle->m_rot = rot;

		//return
		return pOneParticle;
	}
	static int GetNumAll() {return nNumParticleAll;};		//�����擾

	D3DXVECTOR3 m_pos;				//���W
	D3DXVECTOR3 m_move;				//�ړ���
	D3DXVECTOR3 m_rot;				//��]��
	D3DXMATRIX m_Mtx;				//�}�g���b�N�X
	static int nNumParticleAll;		//����
};

//�p�[�e�B�N���̂܂Ƃ܂�
class CParticle : public CScene
{
public:
	CParticle();									//�R���X�g���N�^
	~CParticle();									//�f�X�g���N�^

	HRESULT Init();									//������
	void Uninit();									//�I��
	void Update();									//�X�V
	void Draw();									//�`��
	void ShowDebugInfo();							//�f�o�b�O���\�L
	void UpdateVartex();							//���_�̍X�V
	static void Create(D3DXVECTOR3 pos, int nLife, float fRadius, D3DXCOLOR col,int nNumber, float fSpeed);		//��������
	static void ResetVertex();						//���_���Z�b�g
	static void UpdateAllParticle();				//�p�[�e�B�N���S�čX�V
	static HRESULT MakeVertex();					//���_����
	static void ReleaseVertex();					//���_�j��
	static void ResetVertexID();					//���_ID���Z�b�g�@��ʂ���~���Ă��p�[�e�B�N���̏������s����

private:
	static LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;						//���_�o�b�t�@�ւ̃|�C���^
	static int m_nVertexID;											//���_ID
	int m_nLife;													//���C�t
	int m_nNumber;													//��
	float m_fRadius;												//���a
	D3DXCOLOR m_col;												//�F
	std::vector<std::unique_ptr<COneParticle>> m_pParticleList;		//�p�[�e�B�N���̍\���̂̃��X�g

	void SetParticle(D3DXVECTOR3 &pos,float fSpeed);				//�p�[�e�B�N���ݒ�
}; 

#endif