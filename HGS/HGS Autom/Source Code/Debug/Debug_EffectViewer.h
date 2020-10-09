//------------------------------------------------------------------------------
//
//�G�t�F�N�g�r���[���p����  [Debug_EffectViewer.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _DEBUG_EFFECTVIEWER_H_
#define _DEBUG_EFFECTVIEWER_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "../main.h"
#include "../basemode.h"

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CParticleParam;

class CDebug_EffectViewer : public CBaseMode
{
public:

	CDebug_EffectViewer();
	~CDebug_EffectViewer();
	HRESULT Init(HWND hWnd);						//������
	void Uninit();						//�I��
	void Update();						//�X�V
	void Draw();						//�`��
	void ShowDebugInfo();				//�f�o�b�O���\�L


	CPlayer* GetPlayer() { return nullptr; };

private:
	std::unique_ptr<CParticleParam> m_pParticleParam;	//�p�[�e�B�N���̃p�����[�^

	bool m_bLoop;										//���[�v�����邩
	int m_nLoopInterval;								//���[�v�̃C���^�[�o��
	int m_nCnt;											//�J�E���g

	void ParticleParamaterViewer();						//�p�[�e�B�N���̃p�����[�^�n�̃r���[��

};

#endif