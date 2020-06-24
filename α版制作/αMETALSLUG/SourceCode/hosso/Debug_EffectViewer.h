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
class CDebug_EffectViewer : public CBaseMode
{
public:

	CDebug_EffectViewer();
	~CDebug_EffectViewer();
	HRESULT Init();			//������
	void Uninit();						//�I��
	void Update();						//�X�V
	void Draw();						//�`��
	void ShowDebugInfo();				//�f�o�b�O���\�L

	CMap *GetMap() { return nullptr; };
	CPlayer* GetPlayer() { return nullptr; };

private:
	int m_nLife;					//�p�[�e�B�N���̃��C�t
	int m_nNumParticle;				//�p�[�e�B�N���̐�
	float m_fRadius;				//���a
	float m_fSpeed;					//���x
	float m_fRadiusDamping;			//���a�̌���
	float m_fAlphaDamping;			//�A���t�@�l�̌���
	CTexture::TEX_TYPE m_textype;	//�e�N�X�`��
	D3DXCOLOR m_col;				//�F

	bool m_bLoop;					//���[�v�����邩
	int m_nLoopInterval;			//���[�v�̃C���^�[�o��
	int m_nCnt;						//�J�E���g


};

#endif