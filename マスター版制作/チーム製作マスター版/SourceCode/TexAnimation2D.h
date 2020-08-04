//------------------------------------------------------------------------------
//
//�e�N�X�`���A�j���[�V����2D����  [TexAnimation2D.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _EFFECTANIMATION2D_H_
#define _EFFECTANIMATION2D_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scene2D.h"
#include "TexAnimationBase.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
//2�d�p��
//Scene���Ń|���S������ATexAnimation���ŃA�j���[�V��������
class CTexAnimation2D : public CScene2D , public CTexAnimationBase
{
public:
	CTexAnimation2D();					//�R���X�g���N�^
	CTexAnimation2D(OBJ_TYPE obj);		//�R���X�g���N�^
	~CTexAnimation2D();					//�f�X�g���N�^

	HRESULT Init();				//������
	void Uninit();				//�I��
	void Update();				//�X�V
	void Draw();				//�`��
	void ShowDebugInfo();		//�f�o�b�O���\��
	static void Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,D3DXVECTOR3 rot, CTexture::SEPARATE_TEX_TYPE type, int nCntSwitch, CScene::OBJ_TYPE objtype);	//��������

private:
};

#endif