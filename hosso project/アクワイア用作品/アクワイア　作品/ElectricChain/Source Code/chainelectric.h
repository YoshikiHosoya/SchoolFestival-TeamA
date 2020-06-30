//------------------------------------------------------------------------------
//
//�A���̓d������  [ChainElectric.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _CHAINELECTRIC_H_
#define _CHAINELECTRIC_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CChainElectric : public CScene
{
public:
	CChainElectric();						//�R���X�g���N�^
	~CChainElectric();						//�f�X�g���N�^

	HRESULT Init();							//������
	void Uninit();							//�I��
	void Update();							//�X�V
	void Draw();							//�`��
	void ShowDebugInfo();					//�f�o�b�O���\��
	static void Create(D3DXVECTOR3 StartPos , D3DXVECTOR3 GoalPos, D3DXVECTOR3 size,D3DXCOLOR col,int nCntEnd);	//��������

private:
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	int m_nCntAnim;							//�A�j���[�V�����J�E���^�[
	int m_nPatternAnim;						//�A�j���[�V�����p�^�[��

	D3DXVECTOR3 m_pos;						//���W
	D3DXVECTOR3 m_rot;						//��]
	D3DXVECTOR3 m_size;						//�T�C�Y
	D3DXCOLOR m_col;						//�F
	D3DXMATRIX m_Mtx;						//�}�g���b�N�X
	int m_nLife;

	void MakeVertex();						//���_����
};

#endif