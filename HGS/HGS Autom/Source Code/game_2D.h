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
class CMultiNumber;

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
	void AddTimer(int nAddTime);
	void SetGamestate(CGame::STATE state);


protected:
private:
	int m_nCnt;
	int m_nSpeed;										//�ړ����x
	int m_nScoreDistance;								//��������
	DIRECTION m_direction;								//����

	float m_fNextBendingPoint;							//���̋Ȃ���p�܂ł̋���
	D3DXVECTOR3 *m_pNextBendingWayPos;					//���̋Ȃ���ӏ��̍��W
	DIRECTION m_NextBendingDirection;					//���̋Ȃ���p�̕���
	bool m_bBendingFlag;								//�Ȃ���̃t���O
	int m_nBendingTime;									//�Ȃ����Ă鎞��
	int m_nTime;										//�^�C��
	int m_nBendingCountDown;							//�Ȃ���Ƃ��̃J�E���g�_�E��

	std::shared_ptr<CMultiNumber> m_pScoreNumber;
	std::shared_ptr<CMultiNumber> m_pTimeNumber;
	std::shared_ptr<CScene2D> m_pScore;
	std::shared_ptr<CScene2D> m_pNextBending;

	std::shared_ptr<CScene2D> m_pReadyGo;


	std::vector<std::shared_ptr<CWay>> m_pWayList;


};

#endif