//*************************************************************************************************************
//
// 3D�p�[�e�B�N���̏���[particle.h]
// Author : Fujiwara Masato
//
//*************************************************************************************************************
#ifndef _3DPARTICLE_H_
#define _3DPARTICLE_H_

//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "main.h"
#include "Scene.h"

//-------------------------------------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------
// �N���X��`
//-------------------------------------------------------------------------------------------------------------
class C3DParticle :public CScene
{
public:
	typedef enum
	{
		TYPE_NORMAL = 0,
		TYPE_CHARGE,
		TYPE_MAX,
	} TYPE;

	typedef enum
	{
		OFFSET_ID_NONE = -1,
		OFFSET_ID_EXPLOSION,
		OFFSET_ID_EXPLOSIONWAVE,
		OFFSET_ID_GET,
		OFFSET_ID_MAX,
	} PARTICLE_OFFSET_ID;

	typedef struct
	{
		int					nFrame;				// �t���[����
		int					nNumber;			// ��
		int					nEffeTexType;		// �G�t�F�N�g�̃e�N�X�`���̎��
		int					nEffeType;			// �G�t�F�N�g�̎��
		C3DParticle::TYPE	type;				// ���(��Ɉړ���)

		D3DXVECTOR3			*pSpeedRate;			// ���x���[�g

		D3DXVECTOR3			*pPos;				// �ʒu�̃|�C���^
		PINTEGER2			pPosXRand;			// �ʒuX���W�����_���p�̃|�C���^
		PINTEGER2			pPosYRand;			// �ʒuY���W�����_���p�̃|�C���^
		PINTEGER2			pPosZRand;			// �ʒuY���W�����_���p�̃|�C���^

		float				*pfLength;			// ���_����̋����̃|�C���^
		PINTEGER2			pnLengthRand;		// ���_����̋��������_���p�̃|�C���^

		D3DXCOLOR			*pCol;				// �F�̃|�C���^

		float				*pfRadius;			// ���a�̃|�C���^
		PINTEGER2			pnRadiusRand;		// ���a�̃����_���p�̃|�C���^

		float				*pfRadiusValue;	// ���a�̕ω��ʂ̃|�C���^

		float				*pfAngle;			// �p�x�̃|�C���^
		PINTEGER2			pnAngleRand;		// �p�x�̃����_���p�̃|�C���^

		float				*pfSpeed;			// ���x�̃|�C���^
		PINTEGER2			pnSpeedRand;		// ���x�̃����_���p�̃|�C���^

		int					*pnLife;			// ���C�t�̃|�C���^
		PINTEGER2			pnLifeRand;		// ���C�t�̃����_���p�̃|�C���^
	} PARTICLE_OFFSET;



	C3DParticle();
	~C3DParticle();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static C3DParticle * Create(PARTICLE_OFFSET_ID OffsetID, CONST D3DXVECTOR3 origin);
	void SetParticle(PARTICLE_OFFSET_ID OffsetID);
	static void Load(void);
	static void Unload(void);

	void SetOrigin(CONST D3DXVECTOR3 &Origin);

private:
	static PARTICLE_OFFSET	m_ParticleOffset[OFFSET_ID_MAX];	// �p�[�e�B�N���̃I�t�Z�b�g
	PARTICLE_OFFSET_ID		m_offsetID;							// �I�t�Z�b�gID
	int						m_nFlameCount;						// �t���[���̃J�E���g
	D3DXVECTOR3				m_Origin;							// ���_
};

#endif
