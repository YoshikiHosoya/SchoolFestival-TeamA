//------------------------------------------------------------------------------
//
//3D�v���C���[����  [3Dplayer.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _PLAYER_3D_H_
#define _PLAYER_3D_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "player.h"
#include "character_3D.h"

//------------------------------------------------------------------------------
//�O���錾
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CPlayer_3D : public CCharacter_3D,public CPlayer
{
public:
	CPlayer_3D();															//�R���X�g���N�^
	~CPlayer_3D();															//�f�X�g���N�^

	virtual HRESULT Init();												//������
	virtual void Uninit();												//�I��
	virtual void Update();												//�X�V
	virtual void Draw();												//�`��
	virtual void ShowDebugInfo();										//�f�o�b�O���\�L
	void DamageAction();												//�_���[�W���̃��A�N�V����
	void DeathAction();													//���S���̃��A�N�V����
	void SetState(STATE nextstate);										//�X�e�[�g�ύX����
	static std::shared_ptr<CPlayer_3D> Create(D3DXVECTOR3 pos);			//����

	D3DXVECTOR3 GetPlayerPos() override { return GetPos(); };
protected:

private:
};
#endif