//------------------------------------------------------------------------------
//
//���b�V���X�t�B�A����  [meshsphere.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "renderer.h"
#include "manager.h"
#include "renderer.h"
#include "sphere_explosion.h"
#include "collision.h"
#include "enemy.h"
#include "traces.h"
#include "sound.h"
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define BLOCK_NUM			(INTEGER2(8,8))						//���b�V���̃u���b�N��
#define EXPLOSION_DAMAGE	(35)									//�����_���[�W
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CSphere_Explosion::CSphere_Explosion()
{
	m_nLife = 0;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CSphere_Explosion::~CSphere_Explosion()
{

}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CSphere_Explosion::Init()
{
	CMeshSphere::Init();

	return S_OK;

}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CSphere_Explosion::Uninit()
{
	CMeshSphere::Uninit();
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CSphere_Explosion::Update()
{
	//���C�t���S���Ȃ�����I��
	if (m_nLife-- < 0)
	{
		Release();
		return;
	}

	//��]
	D3DXVECTOR3 &rRot = GetRot();
	float &rRadius = GetRadius();

	//������Ɖ�]
	rRot.y += 0.02f;
	rRot.z += 0.001f;

	//������Ƃ��g��
	rRadius += 3.0f;

	//���_�Đݒ�
	ResetVtx(D3DXVECTOR3(rRadius, rRadius, rRadius));

	//�F���擾
	D3DXCOLOR rCol = GetCol();
	rCol.a -= 0.015f;
	//���C�t���S���Ȃ�����I��
	if (rCol.a < 0)
	{
		Release();
		return;
	}
	SetCol(rCol);

	//�X�t�B�A�X�V
	CMeshSphere::Update();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CSphere_Explosion::Draw()
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���C�e�B���OOFF
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_LIGHTING_OFF);

	//���Z����
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ALPHABLEND_ADD);

	//Z�e�X�g������Z���C�e�B���O�L��
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_ON_ZWRITING_OFF);

	//�`��
	CMeshSphere::Draw();

	//Z�e�X�g�ʏ�
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);

	//�ʏ퍇��
	CManager::GetRenderer()->SetRendererCommand(CRenderer::REDNERER_ALPHABLEND_DEFAULT);

	//���C�e�B���OON
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_LIGHTING_ON);
}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CSphere_Explosion::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}
//------------------------------------------------------------------------------
//����
//------------------------------------------------------------------------------
std::shared_ptr<CSphere_Explosion> CSphere_Explosion::Create(D3DXVECTOR3 const pos, float const fRadius, int const nLife)
{
	std::shared_ptr<CSphere_Explosion> pSphereExplosion(new CSphere_Explosion);

	if (pSphereExplosion)
	{
		//�������@���ݒ�
		pSphereExplosion->Init();
		pSphereExplosion->SetPos(pos);
		pSphereExplosion->SetSize(D3DXVECTOR3(fRadius * 2.0f, fRadius* 2.0f, fRadius* 2.0f));
		pSphereExplosion->SetBlockNum(BLOCK_NUM);
		pSphereExplosion->m_nLife = nLife;

		//���_�ݒ�
		pSphereExplosion->MakeVertex();
		pSphereExplosion->SetNormal();

		//�}�g���b�N�X�̌v�Z�@����F�ł����g��Ȃ�
		CHossoLibrary::CalcMatrix(pSphereExplosion->GetMtx(), pSphereExplosion->GetPos(), pSphereExplosion->GetRot());

		//����̐���
		pSphereExplosion->m_pCollision = CCollision::Create(pSphereExplosion->GetMtx(),CCollision::COLLISION_EXPLOSION);
		pSphereExplosion->m_pCollision->SetCollisionInfo(fRadius * 1.5f, 0.0f);

		//�A��
		pSphereExplosion->CollisionExplosion();

		//���Ղ̑傫���@�󒆂Ŕ������������͏���������
		float fTracesRadius = fRadius * 5.0f - (pos.y);

		//���̔����̍��Ղ��c��
		CTraces::Create(D3DXVECTOR3(pos.x, 0.0f, pos.z), D3DXVECTOR3(fTracesRadius, 0.0f, fTracesRadius));

		//�e�N�X�`������t��
		pSphereExplosion->BindTexture(CTexture::GetTexture(CTexture::TEX_SPHEREEXPLOISON));

		//���Đ�
		CManager::GetSound()->Play(CSound::LABEL_SE_EXPLOSION);

		//�V�[���ɒǉ�
		pSphereExplosion->SetObjType(OBJTYPE_EFFECT_SPHERE);
		pSphereExplosion->AddSharedList(pSphereExplosion);

		//���_�X�V
		pSphereExplosion->Update();

		CHossoLibrary::StartVibration(5);
	}

	return pSphereExplosion;
}

//------------------------------------------------------------------------------
//�����̔���
//------------------------------------------------------------------------------
void CSphere_Explosion::CollisionExplosion()
{
	//�V�[���̃��X�g
	std::vector<std::shared_ptr<CScene>> pSceneList;

	//�V�[�����擾
	CScene::GetSceneList(CScene::OBJTYPE_ENEMY, pSceneList);

	//�z��ɓ����Ă邩
	if (!pSceneList.empty())
	{
		//�v�f��
		for (size_t nCnt = 0; nCnt < pSceneList.size(); nCnt++)
		{
			//�|�C���^�擾 CMeshField�^�ɃL���X�g
			CEnemy *pEnemy = ((CEnemy*)pSceneList[nCnt].get());
			//nullcheck
			if (pEnemy)
			{
				//���G����̂Ȃ��Ƃ�
				if (!pEnemy->GetInvincible())
				{
					if (m_pCollision->CollisionExplosion(pEnemy->GetCollision()))
					{
						pEnemy->ApplyDamage(EXPLOSION_DAMAGE, 0);
					}
				}
			}
		}
	}
}