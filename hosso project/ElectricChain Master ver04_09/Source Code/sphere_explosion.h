//------------------------------------------------------------------------------
//
//�X�t�B�A�`�̔�������  [sphere_explosion.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _SPHERE_EXPLOSION_H_
#define _SPHERE_EXPLOSION_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "meshsphere.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CCollision;

class CSphere_Explosion : public CMeshSphere
{
public:
	CSphere_Explosion();		//�R���X�g���N�^
	~CSphere_Explosion();		//�f�X�g���N�^

	HRESULT Init();				//������
	void Uninit();				//�I��
	void Update();				//�X�V
	void Draw();				//�`��
	void ShowDebugInfo();		//�f�o�b�O���\�L

	static std::shared_ptr<CSphere_Explosion> Create(D3DXVECTOR3 const pos, float const fRadius,int const nLife);	//��������

protected:

private:
	int m_nLife;								//���C�t
	std::unique_ptr<CCollision>	m_pCollision;	//�����蔻��
	void CollisionExplosion();					//�����̔��菈��

};
#endif