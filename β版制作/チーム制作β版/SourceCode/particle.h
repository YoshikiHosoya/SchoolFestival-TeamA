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
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define MAX_PARTICLE (100000)									//�p�[�e�B�N���̍ő吔
#define DEFAULT_TEXTURE (CTexture::TEX_EFFECT_PARTICLE)			//�f�t�H���g�Ŏg�p����e�N�X�`��
#define DEFAULT_DAMPING (0.95f)									//�f�t�H���g�̌����l
#define DEFAULT_GRAVITY_POWER (0.8f)							//�f�t�H���g�̏d�͂̑傫��
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------


class CParticleParam
{
public:
	//�p�[�e�B�N���̃e�L�X�g
	enum PARTICLE_TEXT
	{
		PARTICLE_DEFAULT = 0,
		PARTICLE_EXPLOSION,
		PARTICLE_BLOOD,
		PARTICLE_SUMPLE,
		PARTICLE_BULLET_ORBIT,
		PARTICLE_MAX,
	};

	//�p�[�e�B�N���̌���
	enum PARTICLE_SHAPE
	{
		SHAPE_SPHERE = 0 ,
		SHAPE_CONE,
		SHAPE_CIRCLE_XY,
		SHAPE_LINE,
	};

	//�R���X�g���N�^
	CParticleParam()
	{
		m_nLife = 50;										//���C�t
		m_fRadius = 15.0f;									//���a
		m_col = WhiteColor;									//�F

		m_nNumber = 10;										//��
		m_fSpeed = 10.0f;									//���x
		m_bSpeedRandom = false;								//���x�������_�����ǂ���
		m_shape = SHAPE_SPHERE;								//�p�[�e�B�N���̕���
		m_rot = ZeroVector3;								//�p�x
		m_fRange = 0.0f;									//�͈�

		m_fRadiusDamping = DEFAULT_DAMPING;					//���a�̌����n
		m_fAlphaDamping = DEFAULT_DAMPING;					//�A���t�@�l�̌����l
		m_Textype = CTexture::TEX_EFFECT_PARTICLE;			//�e�N�X�`��
		m_ParticleType = PARTICLE_DEFAULT;					//�p�[�e�B�N���̃^�C�v
		m_bGravity = false;									//�d��
		m_nGravityPower = DEFAULT_GRAVITY_POWER;			//�d�͂̑傫��
	}
	~CParticleParam() {};

	void SetParamater(int nLife, float fRadius, D3DXCOLOR col,int nNumber,float fSpeed);
	void UpdateParam();


	static HRESULT LoadParticleDefaultParam();
	static HRESULT SaveParticleDefaultParam(CParticleParam *pSaveParam);

	//Get�֐�
	static std::vector<std::string> &GetFileNameList() {	return m_aFileNameList;};

	int &GetLife()					{ return m_nLife; };				//���C�t
	float &GetRadius()				{ return m_fRadius; };				//���a
	D3DXCOLOR &GetCol()				{ return m_col; };					//�F

	int &GetNumber()				{ return m_nNumber; };				//��
	float &GetSpeed()				{ return m_fSpeed; };				//���x
	PARTICLE_SHAPE &GetShape()		{ return m_shape; };				//�p�[�e�B�N���̕���
	bool&GetSpeedRandom()			{ return m_bSpeedRandom; };			//�p�[�e�B�N���̑��x�������_�����ǂ���
	D3DXVECTOR3 &GetRot()			{ return m_rot;};					//�p�x
	float &GetRange()				{ return m_fRange; };					//�p�x

	float &GetRadiusDamping()		{ return m_fRadiusDamping; };		//���a�̌����n
	float &GetAlphaDamping()		{ return m_fAlphaDamping; };		//�A���t�@�l�̌����l
	CTexture::TEX_TYPE &GetTex()	{ return m_Textype; };				//�e�N�X�`��
	PARTICLE_TEXT &GetType()		{ return m_ParticleType; };			//�p�[�e�B�N���̃^�C�v
	bool &GetGravity()				{ return m_bGravity; };				//�d��
	float &GetGravityPower()		{ return m_nGravityPower; };		//�d�͂̑傫��

	static CParticleParam *GetDefaultParam(CParticleParam::PARTICLE_TEXT type) { return m_pParticleDefaultParamList[type].get(); };
	static bool ShowParamConboBox(CParticleParam::PARTICLE_TEXT & rType);

	//�I�y���[�^
	void *operator = (const CParticleParam *pParam);

private:
	static std::vector<std::unique_ptr<CParticleParam>> m_pParticleDefaultParamList;	//�p�[�e�B�N���̏����p�����[�^�̃��X�g
	static std::vector<std::string> m_aFileNameList;									//�ǂݍ��ރt�@�C���̃��X�g

	int m_nLife;									//���C�t
	float m_fRadius;								//���a
	D3DXCOLOR m_col;								//�F

	int m_nNumber;									//��
	float m_fSpeed;									//���x
	bool m_bSpeedRandom;							//���x�������_�����ǂ���
	PARTICLE_SHAPE m_shape;							//�p�[�e�B�N���̏o��
	D3DXVECTOR3 m_rot;								//�p�x
	float m_fRange;									//�͈�

	float m_fRadiusDamping;							//���a�̌����l
	float m_fAlphaDamping;							//�A���t�@�l�̌����l
	CTexture::TEX_TYPE m_Textype;					//�e�N�X�`��
	PARTICLE_TEXT m_ParticleType;					//�p�[�e�B�N���̃^�C�v
	bool m_bGravity;								//�d�͂������邩
	float m_nGravityPower;							//�d�͂̑傫��

};

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
class CParticle
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

	static void Create(D3DXVECTOR3 pos, int nLife, float fRadius, D3DXCOLOR col,int nNumber, float fSpeed);		//��������
	static void CreateFromParam(D3DXVECTOR3 pos, CParticleParam *pInputParam);

	static void CreateFromText(D3DXVECTOR3 pos, CParticleParam::PARTICLE_TEXT type);

	bool GetDeleteFlag() { return m_bDeleteFlag; };

private:
	static LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;											//���_�o�b�t�@�ւ̃|�C���^
	static int m_nVertexID;																//���_ID
	std::unique_ptr<CParticleParam> m_pParticleParam;									//�p�[�e�B�N���̌��݂̃p�����[�^

	std::vector<std::unique_ptr<COneParticle>> m_pParticleList;		//�p�[�e�B�N���̍\���̂̃��X�g
	bool m_bDeleteFlag;												//�����t���O

	void SetParticle(D3DXVECTOR3 &pos, CParticleParam *pShape);				//�p�[�e�B�N���ݒ�

};

#endif
