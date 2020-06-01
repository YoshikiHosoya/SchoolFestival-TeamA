//------------------------------------------------------------------------------
//
//�~�j�}�b�v����  [minimap.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "minimap.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "enemy.h"
#include "camera.h"
#include "basemode.h"
#include "scene2D.h"
#include "UI.h"
#include "sphere_explosion.h"
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define MINIMAP_POS			(D3DXVECTOR3(1180.0f,100.0f,100.0f))
#define MINIMAP_RANGE		(80.0f)
#define MAX_MAPPING			(100)
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CMiniMap::CMiniMap()
{
	m_pEnemyMappingList.clear();
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CMiniMap::~CMiniMap()
{
	m_pEnemyMappingList.clear();
}
//------------------------------------------------------------------------------
//������
//------------------------------------------------------------------------------
HRESULT CMiniMap::Init()
{
	//���[�_�[�́Z
	std::shared_ptr<CScene2D> pMap = CScene2D::Create_Shared(MINIMAP_POS, D3DXVECTOR3(MINIMAP_RANGE * 2, MINIMAP_RANGE * 2, 0.0f), CScene::OBJTYPE_MINIMAP);
	pMap->BindTexture(CTexture::GetTexture(CTexture::TEX_MINIMAP_MAP));

	//�G�̃}�b�s���O�Ɣ����̃}�b�s���O�ݒ�
	for (int nCnt = 0; nCnt < MAX_MAPPING; nCnt++)
	{
		//�G�̃}�b�s���O
		m_pEnemyMappingList.emplace_back(CScene2D::Create_Shared(MINIMAP_POS, D3DXVECTOR3(10.0f, 10.0f, 0.0f),CScene::OBJTYPE_MINIMAP));
		m_pEnemyMappingList[nCnt]->SetDisp(false);
		m_pEnemyMappingList[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_MINIMAP_ENEMY));

		//�����̃}�b�s���O
		m_pExplosionMappingList.emplace_back(CScene2D::Create_Shared(MINIMAP_POS, D3DXVECTOR3(20.0f, 20.0f, 0.0f), CScene::OBJTYPE_MINIMAP));
		m_pExplosionMappingList[nCnt]->SetDisp(false);
		m_pExplosionMappingList[nCnt]->SetVtxCol(YellowColor);
		m_pExplosionMappingList[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_MINIMAP_EXPLOSION));
	}

	//�v���C���[�̃}�b�s���O
	m_pPlayerMapping = CScene2D::Create_Shared(MINIMAP_POS, D3DXVECTOR3(15.0f, 15.0f, 0.0f), CScene::OBJTYPE_MINIMAP);
	m_pPlayerMapping->SetVtxCol(GreenColor);
	m_pPlayerMapping->BindTexture(CTexture::GetTexture(CTexture::TEX_MINIMAP_PLAYER));

	return S_OK;

}
//------------------------------------------------------------------------------
//�I��
//------------------------------------------------------------------------------
void CMiniMap::Uninit()
{

}
//------------------------------------------------------------------------------s
//�X�V
//------------------------------------------------------------------------------
void CMiniMap::Update()
{
	//�}�b�s���O�S�����\���ɐݒ�
	for (size_t nCnt = 0; nCnt < MAX_MAPPING; nCnt++)
	{
		m_pEnemyMappingList[nCnt]->SetDisp(false);
		m_pExplosionMappingList[nCnt]->SetDisp(false);
	}

	//Scene�̃��X�g
	std::vector<std::shared_ptr<CScene>> pSceneList;

	//�G�̃��X�g�擾
	CScene::GetSceneList(CScene::OBJTYPE_ENEMY, pSceneList);
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
	float fCameraRot = CManager::GetRenderer()->GetCamera()->GetCameraRot().y;

	//�p�x�ݒ�
	m_pPlayerMapping->SetAngle(-pPlayer->GetRot().y + fCameraRot);

	//nullcheck
	if (!pSceneList.empty() && pPlayer)
	{
		//�v�f��
		for (size_t nCnt = 0; nCnt < pSceneList.size(); nCnt++)
		{
			//�|�C���^�擾 CEnemy�^�ɃL���X�g
			CEnemy *pEnemy = ((CEnemy*)pSceneList[nCnt].get());

			//nullcheck
			if (pEnemy)
			{
				//�}�b�v��̓G�̍��W�v�Z
				D3DXVECTOR3 posDiff = (pPlayer->GetPos() - pEnemy->GetPos()) * 0.1f;

				//y���͔��]
				posDiff.x *= -1.0f;

				//�����Ɗp�x�����߂�
				float fDistance = D3DXVec2Length(&D3DXVECTOR2(posDiff.x, posDiff.z));
				float fAngle = atan2f(posDiff.x, posDiff.z);

				//�͈͓��ɗ}����
				CHossoLibrary::RangeLimit_Equal_Float(fDistance, 0.0f, MINIMAP_RANGE);

				//�}�b�s���O��̓G�̍��W�v�Z
				D3DXVECTOR3 pMappingEnemyPos = ZeroVector3;
				pMappingEnemyPos.x = MINIMAP_POS.x + sinf(fAngle + fCameraRot) * fDistance;
				pMappingEnemyPos.z = MINIMAP_POS.z + cosf(fAngle + fCameraRot) * fDistance;

				//�}�b�v��̓G�̍��W�ݒ�
				m_pEnemyMappingList[nCnt]->SetPos(D3DXVECTOR3(pMappingEnemyPos.x, pMappingEnemyPos.z, 0.0f));
				m_pEnemyMappingList[nCnt]->SetDisp(true);

				//�X�^�����͐@����ȊO�͐�
				if (pEnemy->GetStan())
				{
					m_pEnemyMappingList[nCnt]->SetVtxCol(BlueColor);
				}
				else
				{
					m_pEnemyMappingList[nCnt]->SetVtxCol(RedColor);
				}
			}
		}
	}

	//�����̃��X�g�擾
	CScene::GetSceneList(CScene::OBJTYPE_EFFECT_SPHERE, pSceneList);

	//nullcheck
	if (!pSceneList.empty() && pPlayer)
	{
		//�v�f��
		for (size_t nCnt = 0; nCnt < pSceneList.size(); nCnt++)
		{
			//�|�C���^�擾 CSphere_Explosion�^�ɃL���X�g
			CSphere_Explosion *pExplosion = ((CSphere_Explosion*)pSceneList[nCnt].get());

			//nullcheck
			if (pExplosion)
			{
				//�}�b�v��̓G�̍��W�v�Z
				D3DXVECTOR3 posDiff = (pPlayer->GetPos() - pExplosion->GetPos()) * 0.1f;

				//y���͔��]
				posDiff.x *= -1.0f;

				//�����Ɗp�x�����߂�
				float fDistance = D3DXVec2Length(&D3DXVECTOR2(posDiff.x, posDiff.z));
				float fAngle = atan2f(posDiff.x, posDiff.z);

				//�͈͓��ɗ}����
				CHossoLibrary::RangeLimit_Equal_Float(fDistance, 0.0f, MINIMAP_RANGE);

				//�}�b�s���O��̓G�̍��W�v�Z
				D3DXVECTOR3 pMappingExplosionPos = ZeroVector3;
				pMappingExplosionPos.x = MINIMAP_POS.x + sinf(fAngle + fCameraRot) * fDistance;
				pMappingExplosionPos.z = MINIMAP_POS.z + cosf(fAngle + fCameraRot) * fDistance;

				//�}�b�v��̓G�̍��W�ݒ�
				m_pExplosionMappingList[nCnt]->SetPos(D3DXVECTOR3(pMappingExplosionPos.x, pMappingExplosionPos.z, 0.0f));
				m_pExplosionMappingList[nCnt]->SetDisp(true);
			}
		}
	}
}
//------------------------------------------------------------------------------
//�`��
//------------------------------------------------------------------------------
void CMiniMap::Draw()
{

}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CMiniMap::ShowDebugInfo()
{
}
//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
void CMiniMap::Create()
{
	//�������m��
	std::unique_ptr<CMiniMap> pMap(new CMiniMap);

	if (pMap)
	{
		//������
		pMap->Init();

		//�I�u�W�F�N�g�ݒ�
		pMap->SetObjType(CScene::OBJTYPE_MINIMAP);
		pMap->AddUniqueList(std::move(pMap));
	}
}
