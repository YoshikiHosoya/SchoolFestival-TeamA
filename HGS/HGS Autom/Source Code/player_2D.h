//------------------------------------------------------------------------------
//
//2D�v���C���[����  [3Dplayer.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _PLAYER_2D_H_
#define _PLAYER_2D_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "player.h"
#include "character_2D.h"

//------------------------------------------------------------------------------
//�O���錾
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CPlayer_2D : public CCharacter_2D,public CPlayer
{
public:
	CPlayer_2D();															//�R���X�g���N�^
	~CPlayer_2D();															//�f�X�g���N�^

	virtual HRESULT Init();												//������
	virtual void Uninit();												//�I��
	virtual void Update();												//�X�V
	virtual void Draw();												//�`��
	virtual void ShowDebugInfo();										//�f�o�b�O���\�L
	D3DXVECTOR3 GetPlayerPos() override { return GetPos(); };
	void DamageAction();												//�_���[�W���̃��A�N�V����
	void DeathAction();													//���S���̃��A�N�V����
	void SetState(STATE nextstate);										//�X�e�[�g�ύX����
	void MoveInput();													//�ړ��̓���
	static std::shared_ptr<CPlayer_2D> Create(D3DXVECTOR3 pos);			//����

protected:

private:
	bool m_bMove;

};
#endif