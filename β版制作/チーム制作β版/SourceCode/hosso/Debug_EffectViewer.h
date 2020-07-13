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
class CDebug_WorldLine;
class C3DLine;

class CDebug_EffectViewer : public CBaseMode
{
public:

	CDebug_EffectViewer();
	~CDebug_EffectViewer();
	HRESULT Init();						//������
	void Uninit();						//�I��
	void Update();						//�X�V
	void Draw();						//�`��
	void ShowDebugInfo();				//�f�o�b�O���\�L

	CMap *GetMap() { return nullptr; };
	CPlayer* GetPlayer() { return nullptr; };

private:
	CDebug_WorldLine *m_pWorldLine;						//���[���h��
	std::unique_ptr<CParticleParam> m_pParticleParam;	//�p�[�e�B�N���̃p�����[�^

	bool m_bLoop;										//���[�v�����邩
	int m_nLoopInterval;								//���[�v�̃C���^�[�o��
	int m_nCnt;											//�J�E���g

	C3DLine *m_p3DLine;									//3D�̐� Shape�Ƃ�rot�����o�������

};

#endif