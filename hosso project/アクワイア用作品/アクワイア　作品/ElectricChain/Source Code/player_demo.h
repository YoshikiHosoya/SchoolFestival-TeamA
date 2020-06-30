//------------------------------------------------------------------------------
//
//�f���p�̃v���C���[����  [player_demo.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _PLAYER_DEMO_H_
#define _PLAYER_DEMO_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "player.h"

//------------------------------------------------------------------------------
//�O���錾
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�N���X��`
class CEnemy;

class CPlayer_Demo : public CPlayer
{
public:
	//�U���̓���
	enum ATTACK_INPUT
	{
		ATTACK_NONE,	//�U�����ĂȂ�
		ATTACK_X,		//X�{�^��
		ATTACK_Y,		//Y�{�^��
		ATTACK_B,		//B�{�^��
		ATTACK_MAX
	};

	CPlayer_Demo();													//�R���X�g���N�^
	~CPlayer_Demo();												//�f�X�g���N�^

	HRESULT Init();													//������
	void Uninit();													//�I��
	void Update();													//�X�V
	void Draw();													//�`��
	void ShowDebugInfo();											//�f�o�b�O���\�L
	static std::shared_ptr<CPlayer_Demo> Create(D3DXVECTOR3 pos);	//����

private:
	ATTACK_INPUT m_AttackInput;										//�U���̓���
	void MoveAI();													//�ړ��̓���
	bool AttackInput();												//�U���̓��͏���
	void SetTargetEnemy();											//�^�[�Q�b�g�̓G�ݒ�

	std::weak_ptr<CEnemy> m_pTargetEnemy;							//�^�[�Q�b�g�̓G�̃|�C���^
};
#endif