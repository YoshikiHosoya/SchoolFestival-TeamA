//------------------------------------------------------------------------------
//
//�e�N�X�`���A�j���[�V����3D����  [TexAnimation3D.h]
//Author:Fujiwara Masato
//
//------------------------------------------------------------------------------
#ifndef _TEXTUREANIMATION3D_H_
#define _TEXTUREANIMATION3D_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scene3D.h"
#include "TexAnimationBase.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
//2�d�p��
//Scene���Ń|���S������ATexAnimation���ŃA�j���[�V��������
class CTexAnimation3D : public CScene3D, public CTexAnimationBase
{
public:
	CTexAnimation3D();					//�R���X�g���N�^
	CTexAnimation3D(OBJ_TYPE obj);		//�R���X�g���N�^
	~CTexAnimation3D();					//�f�X�g���N�^

	HRESULT Init();				//������
	void Uninit();				//�I��
	void Update();				//�X�V
	void Draw();				//�`��
	void ShowDebugInfo();		//�f�o�b�O���\��
	static void Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, CTexture::SEPARATE_TEX_TYPE type,
		int nCntSwitch, CScene::OBJ_TYPE objtype,bool bLoop);	//��������
private:
};

#endif