//------------------------------------------------------------------------------
//
//���[�V��������  [motion.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MOTION_H_
#define _MOTION_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include <vector>

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CModelCharacter;

class CMotion
{
public:
	//�L�[
	struct KEY
	{
		D3DXVECTOR3 rotDest;	//rot�̍s��

		//�R���X�g���N�^
		KEY()
		{
			//������
			rotDest = ZeroVector3;
		}
	};
	//�L�[���
	struct KEY_INFO
	{
		std::vector<std::unique_ptr<KEY>> pKeyList;		//key�̃|�C���^
		int nFrame;										//�t���[����
		float fOriginHeight;							//���_�̍���

		//�R���X�g���N�^
		KEY_INFO()
		{
			//������
			fOriginHeight = 0.0f;
			nFrame = 30;
		}
	};
	//�U���֌W�̏��
	struct ATTACK_INFO
	{
		int nAttack;			//�U����
		int nBlueAttack;		//�U����
		D3DXCOLOR orbitcol;		//�O�Ղ̐F
		float fLength;			//�R���W�����̔���̒���
		float fRadius;			//�R���W�����̔��a

		int nStartCollisonKey;	//�R���W�����J�n�̃L�[
		int nEndCollisionKey;	//�R���W�����I���̃L�[

		int nMoveKey;			//�ړ����鎞�̃L�[
		float fMoveFront;		//�����Ă�����ɑ΂���ړ���
		float fMoveUp;			//�㉺�̈ړ���

		float fKnockBack_Front;	//�O��̃m�b�N�o�b�N
		float fKnockBack_Up;	//�㉺�̃m�b�N�o�b�N

		//�R���X�g���N�^
		ATTACK_INFO()
		{
			//������
			nAttack = 0;
			nBlueAttack = 0;
			orbitcol = WhiteColor;
			fLength = 0.0f;
			fRadius = 0.0f;
			nStartCollisonKey = 0;
			nEndCollisionKey = 0;
			nMoveKey = 0;
			fMoveFront = 0.0f;
			fMoveUp = 0.0f;
			fKnockBack_Front = 0.0f;
			fKnockBack_Up = 0.0f;
		}
	};
	//���[�V�����̏��
	struct MOTION_INFO
	{
		std::vector<std::unique_ptr<KEY_INFO>> pKeyInfoList;	//keyInfo�ւ̃|�C���^
		int nNumKey;											//�L�[��
		bool bLoop;												//���[�v���邩�ǂ���
		bool bAttack;											//�U�����ǂ���
		std::unique_ptr<ATTACK_INFO> pAttackInfo;				//�U���Ɋւ�����

		//�R���X�g���N�^
		MOTION_INFO()
		{
			//������
			nNumKey = 0;
			bLoop = false;
			bAttack = false;
		}
	};

	//���[�V����
	enum MOTION_TYPE
	{
		MOTION_NONE = -1,				//����

		PLAYER_NEUTRAL,					//�v���C���[�@�j���[�g����
		PLAYER_WALK,					//�v���C���[�@����
		PLAYER_DASH,					//�v���C���[�@����
		PLAYER_JUMP,					//�v���C���[�@�W�����v
		PLAYER_HIT,						//�v���C���[�@��e
		PLAYER_DEATH,					//�v���C���[�@���S
		MOTION_MAX						//�ő�l
	};

	CMotion();
	~CMotion();

	static HRESULT Load();			//���[�V�������ǂݍ���
	static void UnLoad();			//���[�V�������j��
	static void ShowDebugInfo();	//�f�o�b�O�̏��

	static void AddKeyInfo(MOTION_TYPE NowMotion, int model);		//�L�[���ǉ�
	static void PopbackKeyInfo(MOTION_TYPE NowMotion);					//�L�[������

	//Get�֐�
	static D3DXVECTOR3 GetRotDest(MOTION_TYPE NowMotion,int nKey,int nIndex)	{ return m_pMotionInfoList[NowMotion]->pKeyInfoList[nKey]->pKeyList[nIndex]->rotDest; };		//���[�V�����̉�]�̃S�[���擾
	static float GetOriginHeight(MOTION_TYPE NowMotion, int nKey)				{ return m_pMotionInfoList[NowMotion]->pKeyInfoList[nKey]->fOriginHeight; };					//���[�V�����̍��̍����擾
	static int GetFrame(MOTION_TYPE NowMotion, int nKey)						{ return m_pMotionInfoList[NowMotion]->pKeyInfoList[nKey]->nFrame; };							//���[�V�����̃t���[�����擾
	static int GetNumKey(MOTION_TYPE NowMotion)									{ return m_pMotionInfoList[NowMotion]->nNumKey; };												//���[�V�����̃L�[���擾
	static bool CheckLoop(MOTION_TYPE NowMotion)								{ return m_pMotionInfoList[NowMotion]->bLoop; };												//���[�V�����̃��[�v���邩�ǂ����擾
	static bool CheckAttack(MOTION_TYPE NowMotion)								{ return m_pMotionInfoList[NowMotion]->bAttack; };												//���[�V�������U�����ǂ��������Ԃ�
	static ATTACK_INFO *GetAttackInfo(MOTION_TYPE NowMotion)					{ return m_pMotionInfoList[NowMotion]->pAttackInfo.get(); };									//�U�����ǂݍ���
	static MOTION_INFO *GetMotion(MOTION_TYPE NowMotion)						{ return m_pMotionInfoList[NowMotion].get(); };													//���[�V�������擾
	static std::vector<std::string> &GetFileName()								{ return m_apFileName; };																		//�t�@�C�����擾

	static bool CheckAttackKey(MOTION_TYPE NowMotion, int nNowKey);			//�U�����ǂ���

	static HRESULT SaveMotion(MOTION_TYPE motiontype);													//���[�V�����ۑ�
	static void MotionCopy(MOTION_TYPE Nowmotion, int NowKey, MOTION_TYPE CopyMotion, int CopyKey);		//���[�V�����R�s�[
	static void LoadMotionFileName();																	//���[�V�����̃t�@�C�����ǂݍ���

private:
	static std::vector<std::unique_ptr<MOTION_INFO>> m_pMotionInfoList;		//���[�V�����̏��
	static HRESULT LoadMotion(MOTION_TYPE motiontype);						//���[�V�����ǂݍ���

	static std::vector<std::string> m_apFileName;							//�t�@�C����
};
#endif