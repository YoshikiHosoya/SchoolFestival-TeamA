//------------------------------------------------------------------------------
//
//�L�����N�^�[�p�̃��f������  [modelcharacter.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MODELCHARACTER_H_
#define _MODELCHARACTER_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "sceneX.h"
#include "motion.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CModelParts;
class CCharacter;

//�L�����N�^�[�̌`�ɂȂ郂�f���̏��
class CModelCharacterInfo
{
public:
	std::vector<std::shared_ptr<CModelInfo>> pModelInfoList;	//���f���̕`��ɕK�v�ȏ��
	std::vector<int> nWeaponID;									//����ԍ�
};

//�L�����N�^�[�̃��f��
class CModelCharacter
{
public:
	CModelCharacter();
	~CModelCharacter();

	//���f���̎��
	enum CHARACTER_TYPE
	{
		CHARACTER_NONE = -1,	//
		CHARACTER_PLAYER,		//�v���C���[
		CHARACTER_ENEMY,		//�G
		CHARACTER_MAX
	};

	HRESULT Init();																//������
	void Uninit();																//�I��
	void Update();																//�X�V
	void Draw();																//�`��
	static std::unique_ptr<CModelCharacter> Create(CHARACTER_TYPE const modeltype);	//��������
	static HRESULT Load();														//���f���ǂݍ���
	static void UnLoad();														//���f���J��

	void ShowModelCharacterInfo();												//���f���̏��\��

	//Set�֐�
	void SetCharacterMtx(D3DXMATRIX *mtx);										//�e�}�g���b�N�X�ݒ�֐�
	void SetMotion(CMotion::MOTION_TYPE motiontype);							//���[�V�����Z�b�g
	void SetDefaultMotion();													//�f�t�H���g�̃��[�V�����Z�b�g

	void SetFrame(int nFrame)		{ m_nFrame = nFrame; };						//�t���[����
	void SetKey(int nKey)			{ m_nKey = nKey; };							//�L�[��
	void ResetMotion()				{ m_nFrame = 0; m_nKey = 0; };				//���[�V�����̏��̏�����
	void SetMotionStop(bool bStop)	{ m_bMotionStop = bStop; };					//���[�V�����X�g�b�v�ݒ�

	//Get�֐�
	int &GetFrame()							{ return m_nFrame; };				//�t���[����
	int &GetKey()							{ return m_nKey; };					//�L�[��
	CHARACTER_TYPE &GetType()				{ return m_type; };					//���f���̎�ގ擾
	CMotion::MOTION_TYPE &GetMotion()		{ return m_motion; };				//���݂̃��[�V�������擾
	bool &GetMotionStop()					{ return m_bMotionStop; };			//���[�V�����X�g�b�v�擾

	void KeyCheck();															//�L�[�`�F�b�N
	void FrameCheck();															//�t���[���`�F�b�N
	void ForcedUpdate(CMotion::MOTION_TYPE motiontype, int nKey);				//�����I�Ƀ��[�V�����`�F���W
	bool CheckMoveKey();														//�ړ�����L�[���m�F
	float GetWaistHeight();														//���̍����擾

	HRESULT SaveModelOffset();													//�I�t�Z�b�g���ۑ�

	static int GetModelNum(CHARACTER_TYPE const modeltype)							{return  m_pModelCharacterList[modeltype]->pModelInfoList.size();};							//���f�����擾

	CModelParts *GetPartsPtr(int nIndex);
protected:
private:
	static std::vector<std::unique_ptr<CModelCharacterInfo>> m_pModelCharacterList;	//�S�Ẵ��f���L�����N�^�̏����i�[
	std::vector<std::unique_ptr<CModelParts>> m_pModelPartsList;				//���f���̃p�[�c�̃|�C���^

	CHARACTER_TYPE m_type;															//���f���̎��
	D3DXMATRIX *m_CharacterMtx;													//�L�����N�^�[�̃}�g���b�N�X
	CMotion::MOTION_TYPE m_motion;												//���݂̃��[�V����
	CMotion::MOTION_TYPE m_motionOld;											//1F�O�̃��[�V����
	int m_nFrame;																//���݂̃t���[��
	int m_nKey;																	//���݂̃L�[
	bool m_bMotionStop;															//���[�V�����X�g�b�v

	HRESULT LoadModelRelativeValue(CHARACTER_TYPE const modeltype);				//���f���̑��΍��W�ǂݍ���
	static HRESULT LoadModelName(CHARACTER_TYPE const modeltype);				//���f�����ǂݍ���

	static char *m_aFileName[CHARACTER_MAX];
};
#endif