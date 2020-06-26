//------------------------------------------------------------------------------
//
//�G�l�~�[����  [enemy.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "character.h"

//------------------------------------------------------------------------------
//�O���錾
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CGauge_3D;

class CEnemy : public CCharacter
{
public:
	//AI�̃p�^�[��
	enum AI_MOVE
	{
		AI_NEUTRAL = 0,				//�j���[�g����
		AI_RANDOM_MOVE,				//�����_���Ɉړ�
		AI_PLAYER_FOLLOWING,		//�v���C���[�̕����Ɉړ�
		AI_ATTACK,					//�U��
	};

	//�G�̎��
	enum ENEMY_TYPE
	{
		TYPE_NORMAL = 0,			//�ʏ�
		TYPE_TUTORIAL_STANING,		//�`���[�g���A���̃X�^����Ԃ̂��
		TYPE_SPEEDY,				//�����ړ�
		TYPE_STRONG,				//���G
		TYPE_MAX
	};

	CEnemy();																						//�R���X�g���N�^
	~CEnemy();																						//�f�X�g���N�^

	HRESULT Init();																					//������
	void Uninit();																					//�I��
	void Update();																					//�X�V
	void Draw();																					//�`��
	void ShowDebugInfo();																			//�f�o�b�O���\�L
	void DamageAction();																			//HP�Q�[�W�X�V
	void DeathAction();																				//���S���̃��A�N�V����
	void AttackTurning();																			//�U�����̐���
	void Collision();																				//�����蔻��
	static std::shared_ptr<CEnemy> Create(D3DXVECTOR3 const pos, ENEMY_TYPE const enemytype);		//����
	static void ChainExplosion(D3DXVECTOR3 pos);													//�A����������
	void SetState(STATE nextstate);																	//�X�e�[�g�ύX����

	//SET�֐�
	void SetStan(bool bStan)				{ m_bStan = bStan; };				//�X�^���ݒ�
	void SetContact(bool bContact)			{ m_bContact = bContact; };			//�ڐG

	//GET�֐�
	bool GetStan()							{ return m_bStan; };				//�X�^����Ԃ��擾
	bool GetContact()						{ return m_bContact; };				//�ڐG

	static int	GetEnemyNum()				{ return m_nNumEnemy; };			//�G�̑����擾
	static int	GetStanEnemyNum()			{ return m_nNumStanEnemy; };		//�X�^����Ԃ̓G�̑����擾
	static void ResetEnemyStaticInfo();											//static�֌W�̏�񃊃Z�b�g

private:
	static int m_nNumEnemy;								//�G�̑���
	static int m_nNumStanEnemy;							//�X�^����Ԃ̓G�̑���
	static bool m_bChain;								//����F�Ń`�F�C��������
	std::shared_ptr<CGauge_3D> m_pGauge;				//�Q�[�W�̃|�C���^
	bool m_bStan;										//�X�^�����Ă��邩�ǂ���
	bool m_bContact;									//�ڐG

	ENEMY_TYPE m_enemytype;								//�G�̎��
	AI_MOVE m_AIMove;									//AI�̏��
	int m_nCntAIMove;									//AIMove�p�̃J�E���^
	float m_fMoveAngle;									//�ړ��̕���


	void HyperKnockBack();								//���������
	void AIMove();										//AI�ňړ�
	void StartStan();									//�X�^���J�n
};
#endif