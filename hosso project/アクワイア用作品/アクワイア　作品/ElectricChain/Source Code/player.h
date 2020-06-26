//------------------------------------------------------------------------------
//
//�v���C���[����  [player.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_
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
class CGauge_2D;

class CPlayer : public CCharacter
{
public:
	CPlayer();															//�R���X�g���N�^
	~CPlayer();															//�f�X�g���N�^

	virtual HRESULT Init();												//������
	virtual void Uninit();												//�I��
	virtual void Update();												//�X�V
	virtual void Draw();												//�`��
	virtual void ShowDebugInfo();										//�f�o�b�O���\�L
	void DamageAction();												//�_���[�W���̃��A�N�V����
	void DeathAction();													//���S���̃��A�N�V����
	void AttackTurning();												//�U�����̐���
	void SetState(STATE nextstate);										//�X�e�[�g�ύX����
	void StartChainThunder();											//�A���J�n
	static std::shared_ptr<CPlayer> Create(D3DXVECTOR3 pos);			//����

	void SetChainThunder(bool bChain) { m_bChainThunder = bChain; };	//����������Ԑݒ�
	bool GetChainThunder() { return m_bChainThunder; };					//��������Ԃ��擾


protected:
	void ChainThunder();												//�A��
	void MoveMotionCheck();												//�ړ��n�̃��[�V�����`�F�b�N

private:
	static bool m_bClearedAlive;										//�Q�[���N���A���ɐ����Ă�����
	bool m_bChainThunder;												//�A�������
	int m_nCntChainThunder;												//�A�����̌o�ߎ���
	std::shared_ptr<CGauge_2D> m_pGauge;								//�Q�[�W�̃|�C���^

	void MoveInput();													//�ړ��̓���
	bool AttackInput();													//�U���̓��͏���
private:
};
#endif