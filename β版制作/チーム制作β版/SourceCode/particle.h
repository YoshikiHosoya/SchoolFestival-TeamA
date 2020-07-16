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
#include "ParticleParamater.h"
#include "TexAnimationBase.h"
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define MAX_PARTICLE (100000)									//�p�[�e�B�N���̍ő吔
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CParticleParam;

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
//�e�N�X�`���A�j���[�V�����p��
class CParticle : public CTexAnimationBase
{
public:
	CParticle();									//�R���X�g���N�^
	~CParticle();									//�f�X�g���N�^

	HRESULT Init();									//������
	void Uninit();									//�I��
	void Update();									//�X�V
	void Draw();									//�`��
	void ShowDebugInfo();							//�f�o�b�O���\�L
	void UpdateVertex();							//���_�̍X�V
	static void ResetVertex();						//���_���Z�b�g
	static HRESULT MakeVertex();					//���_����
	static void ReleaseVertex();					//���_�j��
	static void ResetVertexID();					//���_ID���Z�b�g�@��ʂ���~���Ă��p�[�e�B�N���̏������s����

	static void CreateFromParam(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CParticleParam *pInputParam);
	static void CreateFromText(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CParticleParam::PARTICLE_TEXT type);

	bool GetDeleteFlag() { return m_bDeleteFlag; };

private:
	static LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;											//���_�o�b�t�@�ւ̃|�C���^
	static int m_nVertexID;																//���_ID
	std::unique_ptr<CParticleParam> m_pParticleParam;									//�p�[�e�B�N���̌��݂̃p�����[�^

	std::vector<std::unique_ptr<COneParticle>> m_pParticleList;		//�p�[�e�B�N���̍\���̂̃��X�g
	bool m_bDeleteFlag;												//�����t���O

	void SetParticle(D3DXVECTOR3 const &pos, D3DXVECTOR3 const &rot, CParticleParam *pParam);				//�p�[�e�B�N���ݒ�
	void SetAnimationParam();												//�A�j���[�V�����̃p�����[�^�ݒ�
};

#endif
