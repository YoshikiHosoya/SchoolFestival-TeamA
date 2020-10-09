//------------------------------------------------------------------------------
//
//�p�[�e�B�N���̃p�����[�^�N���X  [particleparamater.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _PARTICLEPARAMATER_H_
#define _PARTICLEPARAMATER_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
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
	enum PARTICLE_TYPE
	{
		EFFECT_DEFAULT = 0,						//
		EFFECT_COUNTDOWN,						//
		EFFECT_CIRCLE,							//
		EFFECT_TRIANGLE,						//
		EFFECT_SQUARE,							//
		EFFECT_STAR,							//
		EFFECT_CROSS,							//
		EFFECT_PLAYERENGINE,					//
		EFFECT_PLAYERDEATH01,					//
		EFFECT_PLAYERDEATH02,					//

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
	CParticleParam();
	~CParticleParam();

	void SetParamater(int nLife, D3DXVECTOR3 size, D3DXCOLOR col,int nNumber,float fSpeed);
	void UpdateParam();


	static HRESULT LoadParticleDefaultParam();
	static HRESULT SaveParticleDefaultParam(CParticleParam *pSaveParam,std::string aSaveFileName);

	//Get�֐�
	static std::vector<std::string> &GetFileNameList() {	return m_aFileNameList;};

	bool&GetSpeedRandom()								{ return m_bSpeedRandom; };					//�p�[�e�B�N���̑��x�������_�����ǂ���
	bool &GetGravity()									{ return m_bGravity; };						//�d��
	bool &GetFollowing()								{ return m_bFollowing; };					//�Ǐ]���邩

	bool &GetAlphaBlend_Add()							{ return m_bAlphaBlend_Add;};				//���Z�������邩
	bool &GetAlphaBlend_Sub()							{ return m_bAlphaBlend_Sub;};				//���Z�������邩
	bool &GetZTest()									{ return m_bZtest;};						//Z�e�X�g���邩
	bool &GetZWrite()									{ return m_bZWrite;};						//Z���C�e�B���O���邩
	bool &GetBillboard()								{ return m_bBillboard; };					//�r���{�[�h

	int &GetLife()										{ return m_nLife; };						//���C�t
	int &GetNumber()									{ return m_nNumber; };						//��
	float &GetSpeed()									{ return m_fSpeed; };						//���x
	float &GetRange()									{ return m_fConeRange; };						//�p�x
	float &GetAlphaDamping()							{ return m_fAlphaDamping; };				//�A���t�@�l�̌����l
	float &GetGravityPower()							{ return m_fGravityPower; };				//�d�͂̑傫��

	D3DXVECTOR3 &GetLocalRandomPosRange()				{ return m_LocalPosRandomRange; };			//���[�J�����W���烉���_���ŏo�鎞�̒l
	D3DXVECTOR3 &GetLocalPos()							{ return m_LocalPos; };						//���[�J�����W
	D3DXVECTOR3 &GetSize()								{ return m_Size; };							//�T�C�Y
	D3DXVECTOR3 &GetSizeDamping()						{ return m_SizeDamping; };					//�T�C�Y�̌����n
	D3DXCOLOR &GetCol()									{ return m_col; };							//�F
	D3DXVECTOR3 &GetRot()								{ return m_rot;};							//�p�x

	bool &GetAnimation()								{ return m_bAnimation;};					//�A�j���[�V�������邩�ǂ���
	bool &GetAnimationLoop()							{ return m_bAnimationLoop; };				//�A�j���[�V�������[�v���邩�ǂ���
	int &GetAnimationCntSwitch()						{ return m_nAnimationCntSwitch; };			//�A�j���[�V�����ؑւ̃J�E���g

	D3DXVECTOR3 &GetCollisionSize()						{ return m_CollisionSize; };				//�����_���������͈̔�
	bool &GetCollision()								{ return m_bCollision; };					//�����蔻�肠�邩
	bool &GetPenetration()								{ return m_bPenetration; };					//�ђʂ��邩�ǂ���
	bool &GetCollisionSizeCalc()						{ return m_bCollisionSizeCalc; };			//�����蔻�萶�����ɃT�C�Y���v�Z���邩�ǂ����@ShotGun�Ƃ��ɕK�v
	int &GetCollisionAttackValue()						{ return m_nCollisionAttackValue; };		//�U����
	int &GetCollisionCnt()								{ return m_nCollisionCnt; };				//��������鎞��

	PARTICLE_SHAPE &GetShape()							{ return m_shape; };						//�p�[�e�B�N���̕���
	CTexture::TEX_TYPE &GetTex()						{ return m_Textype; };						//�e�N�X�`��
	CTexture::SEPARATE_TEX_TYPE &GetSeparateTex()		{ return m_SeparateTex; };					//�����e�N�X�`��
	PARTICLE_TYPE &GetType()							{ return m_ParticleType; };					//�p�[�e�B�N���̃^�C�v

	static CParticleParam *GetDefaultParam(CParticleParam::PARTICLE_TYPE type) { return m_pParticleDefaultParamList[type].get(); };
	static bool ShowParamConboBox(CParticleParam::PARTICLE_TYPE & rType);

	//�I�y���[�^
	void *operator = (const CParticleParam *pParam);

private:
	static std::vector<std::unique_ptr<CParticleParam>> m_pParticleDefaultParamList;	//�p�[�e�B�N���̏����p�����[�^�̃��X�g
	static FILENAME_LIST m_aFileNameList;												//�ǂݍ��ރt�@�C���̃��X�g

	bool m_bSpeedRandom;							//���x�������_�����ǂ���
	bool m_bGravity;								//�d�͂������邩
	bool m_bFollowing;								//�Ǐ]���邩
	bool m_bAlphaBlend_Sub;							//���Z�������邩
	bool m_bAlphaBlend_Add;							//���Z�������邩
	bool m_bZtest;									//Z�e�X�g���邩
	bool m_bZWrite;									//Z���C�e�B���O���邩
	bool m_bBillboard;								//�r���{�[�h���邩�ǂ���

	int m_nLife;									//���C�t
	int m_nNumber;									//��
	float m_fSpeed;									//���x
	float m_fConeRange;								//�͈�
	float m_fAlphaDamping;							//�A���t�@�l�̌����l
	float m_fGravityPower;							//�d�͂̑傫��

	bool m_bAnimation;								//�A�j���[�V�������邩
	bool m_bAnimationLoop;							//�A�j���[�V���������[�v���邩
	int m_nAnimationCntSwitch;						//�A�j���[�V�������؂�ւ��J�E���g

	D3DXVECTOR3 m_CollisionSize;					//�����蔻��̑傫��
	bool m_bCollision;								//�����蔻�肠�邩
	bool m_bCollisionSizeCalc;						//�����蔻�萶�����ɃT�C�Y���v�Z���邩�ǂ����@ShotGun�Ƃ��ɕK�v
	bool m_bPenetration;							//�ђʂ��邩�ǂ���
	int m_nCollisionAttackValue;					//�U����
	int m_nCollisionCnt;							//��������鎞��

	D3DXVECTOR3 m_LocalPos;							//�����������W
	D3DXVECTOR3 m_LocalPosRandomRange;				//�����_���������͈̔�
	D3DXVECTOR3 m_Size;								//�T�C�Y
	D3DXVECTOR3 m_SizeDamping;						//�T�C�Y�̌����l
	D3DXCOLOR m_col;								//�F
	D3DXVECTOR3 m_rot;								//�p�x

	PARTICLE_SHAPE m_shape;							//�p�[�e�B�N���̏o��
	CTexture::TEX_TYPE m_Textype;					//�e�N�X�`��
	CTexture::SEPARATE_TEX_TYPE m_SeparateTex;		//�����e�N�X�`��
	PARTICLE_TYPE m_ParticleType;					//�p�[�e�B�N���̃^�C�v

};


class CreaterParam
{
public:
	//�R���X�g���N�^
	CreaterParam()
	{
		m_bLoop = false;
		m_nLoopNum = 0;
		m_nLoopInterval = 0;
		m_text = CParticleParam::PARTICLE_TYPE::EFFECT_DEFAULT;
	}
	~CreaterParam() {};

private:
	bool m_bLoop;								//���[�v�������ǂ���
	int m_nLoopNum;								//���[�v�̉�
	int m_nLoopInterval;						//���[�v�̃C���^�[�o��
	CParticleParam::PARTICLE_TYPE m_text;		//�ǂݍ��ރe�L�X�g
};

class CreatorWave
{
public:
	//�R���X�g���N�^
	CreatorWave() { m_ParamList.clear(); };
	~CreatorWave() { m_ParamList.clear(); };
private:
	std::vector<std::unique_ptr<CreaterParam>> m_ParamList;
};

//
////�p�[�e�B�N���̐�����
//class CParticleCreators
//{
//public:
//	CParticleCreators() {};				//�R���X�g���N�^
//	~CParticleCreators() {};				//�f�X�g���N�^
//
//	static void LoadParticleCreators();			//�p�[�e�B�N���������̃��[�h
//	static CParticleCreators *Create();
//private:
//	int m_nCntTime;		//���Ԍv��
//	int m_nCntLoop;		//���[�v�����񐔌v��
//
//	static std::vector<std::unique_ptr<CreatorWave>> m_pCreatorParamList;
//	static FILENAME_LIST m_aFileNameList;
//};
#endif
