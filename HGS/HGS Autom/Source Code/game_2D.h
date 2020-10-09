//------------------------------------------------------------------------------
//
//�Q�[������  [game.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _GAME_2D_H_
#define _GAME_2D_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "game.h"
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CWay;
class CScene2D;

class CGame_2D : public CGame
{
public:
	CGame_2D();
	~CGame_2D();
	HRESULT Init(HWND hWnd);								//������
	void Uninit();											//�I��
	void Update();											//�X�V
	void Draw();											//�`��
	void ShowDebugInfo();									//�f�o�b�O���\�L


	int GetSpeed() { return m_nSpeed; };
	DIRECTION GetDirection() { return m_direction; };
	void Bending();
	void PlayerBending(DIRECTION Direction);
	void GameEnd();

protected:
private:
	int m_nCnt;
	int m_nSpeed;										//�ړ����x
	int m_nScoreDistance;								//��������
	DIRECTION m_direction;								//����

	float m_fNextBendingPoint;							//���̋Ȃ���p�܂ł̋���
	DIRECTION m_NextBendingDirection;					//���̋Ȃ���p�̕���
	bool m_bBendingFlag;								//�Ȃ���̃t���O
	int m_nBendingTime;									//�Ȃ����Ă鎞��

	std::vector<std::shared_ptr<CWay>> m_pWayList;


};

#endif