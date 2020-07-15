//------------------------------------------------------------------------------
//
//�����蔻��t���e�N�X�`���A�j���[�V����3D����  [TexAnimation3D_Collision.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _EFFECTANIMATION3D_COLLISION_H_
#define _EFFECTANIMATION3D_COLLISION_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "TexAnimation3D.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CCollision;

class CTexAnimation3D_Collision : public CTexAnimation3D
{
public:

	CTexAnimation3D_Collision();					//�R���X�g���N�^
	CTexAnimation3D_Collision(OBJ_TYPE obj);		//�R���X�g���N�^
	~CTexAnimation3D_Collision();					//�f�X�g���N�^

	HRESULT Init();				//������
	void Uninit();				//�I��
	void Update();				//�X�V
	void Draw();				//�`��
	void ShowDebugInfo();		//�f�o�b�O���\��
	static void Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,D3DXVECTOR3 rot, CTexture::SEPARATE_TEX_TYPE type,
						int nCntSwitch, CScene::OBJ_TYPE objtype,TAG tag,int nAttackValue,int nCntCollision, bool bOriginCenter);	//��������

private:
	CCollision *m_pCollision;	//�R���W�����̃|�C���^
	TAG m_tag;
	D3DXVECTOR3 m_CollisionPosOrigin = ZeroVector3;			//�����蔻��p�̍��W
	int m_nAttackValue;			//�U����
	int m_nCntCollision;		//����̂��鎞��
	bool Collision();			//���菈��
};

#endif