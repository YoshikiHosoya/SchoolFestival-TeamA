//=============================================================================
// ���f������ [Model.cpp]
//=============================================================================
#include "model.h"
#include "inputKeyboard.h"
#include "Player.h"
#include "scene.h"
#include "debugproc.h"
CModel::MODEL CModel::m_Model[TYPE_MAX][MAX_ALLMODEL] = {};
char *CModel::m_PlayerFileName[MODEL_PLAYER_MAX] =
{
	{ "data/MODEL/secondchar/Head.x"},
	{ "data/MODEL/secondchar/Body.x" },
	{ "data/MODEL/secondchar/L_Sholder.x" },
	{ "data/MODEL/secondchar/R_Sholder.x" },
	{ "data/MODEL/secondchar/L_Hand.x" },
	{ "data/MODEL/secondchar/R_Hand.x" },
	{ "data/MODEL/secondchar/L_Foot.x" },
	{ "data/MODEL/secondchar/R_Foot.x" },
	{ "data/MODEL/secondchar/L_Leg.x" },
	{ "data/MODEL/secondchar/R_Leg.x" },
	{ "data/MODEL/secondchar/����.x" },
	{ "data/MODEL/secondchar/�X��.x" },
	{ "data/MODEL/secondchar/����.x" },
	{ "data/MODEL/earth000.x" },
};
char *CModel::m_MapFileName[MODEL_MAP_MAX] =
{
	{ "data/MODEL/�₾��.x" },
	{ "data/MODEL/block02.x" },
	{ "data/MODEL/MPPotion.x" },
	{ "data/MODEL/HPPotion.x" },
	{ "data/MODEL/block03.x" },
	{ "data/MODEL/block04.x" },
};
char *CModel::m_EnemyFileName[MODEL_ENEMY_MAX] =
{
	{ "data/MODEL/EnemyFire/EnemyHead01.x" },		//1  ==��==
	{ "data/MODEL/EnemyFire/EnemyBody01.x" },		//2
	{ "data/MODEL/EnemyFire/EnemySholder_L01.x" },	//3
	{ "data/MODEL/EnemyFire/EnemySholder_R01.x" },	//4
	{ "data/MODEL/EnemyFire/EnemyHand_L01.x" },		//5
	{ "data/MODEL/EnemyFire/EnemyHand_R01.x" },		//6
	{ "data/MODEL/EnemyFire/EnemyFoot_L01.x" },		//9
	{ "data/MODEL/EnemyFire/EnemyFoot_R01.x" },		//10
	{ "data/MODEL/EnemyFire/EnemyLeg_L01.x" },		//7
	{ "data/MODEL/EnemyFire/EnemyLeg_R01.x" },		//8
	{ "data/MODEL/EnemyFire/Enemy_Wepon01.x" },		//11
	{ "data/MODEL/EnemyDark/EnemyHead02.x" },		//12  ==��==
	{ "data/MODEL/EnemyDark/EnemyChin.x" },			//13
	{ "data/MODEL/EnemyDark/EnemyBody02.x" },		//14
	{ "data/MODEL/EnemyDark/EnemySholder_L02.x" },	//15
	{ "data/MODEL/EnemyDark/EnemySholder_R02.x" },	//16
	{ "data/MODEL/EnemyDark/EnemyHand_L02.x" },		//17
	{ "data/MODEL/EnemyDark/EnemyHand_R02.x" },		//18
	{ "data/MODEL/EnemyDark/EnemyLeg_L02.x" },		//19
	{ "data/MODEL/EnemyDark/EnemyLeg_R02.x" },		//20
	{ "data/MODEL/EnemyDark/EnemyFoot_L02.x" },		//21
	{ "data/MODEL/EnemyDark/EnemyFoot_R02.x" },		//22
	{ "data/MODEL/EnemyDark/EnemyWepon02.x" },		//23
	{ "data/MODEL/EnemyIce/EnemyHead03.x" },		//24  ==�X==
	{ "data/MODEL/EnemyIce/EnemyBody03.x" },		//25
	{ "data/MODEL/EnemyIce/EnemySholder_L03.x" },	//26
	{ "data/MODEL/EnemyIce/EnemySholder_R03.x" },	//27
	{ "data/MODEL/EnemyIce/EnemyHand_L03.x" },		//28
	{ "data/MODEL/EnemyIce/EnemyHand_R03.x" },		//29
	{ "data/MODEL/EnemyIce/EnemyLeg03.x" },			//30
	{ "data/MODEL/EnemyIce/Enemy_Wepon03.x" },		//31
	{ "data/MODEL/EnemyBoss/head.x" },				//32  ==�X==
	{ "data/MODEL/EnemyBoss/body.x" },				//33
	{ "data/MODEL/EnemyBoss/L_arm.x" },				//34
	{ "data/MODEL/EnemyBoss/R_arm.x" },				//35
	{ "data/MODEL/EnemyBoss/L_hand.x" },			//36
	{ "data/MODEL/EnemyBoss/R_hand.x" },			//27
	{ "data/MODEL/EnemyBoss/L_leg.x" },				//38
	{ "data/MODEL/EnemyBoss/R_leg.x" },				//39
	{ "data/MODEL/EnemyBoss/foot.x" },				//40
	{ "data/MODEL/EnemyBoss/axe.x" },				//41
	{ "data/MODEL/EnemyBoss/sowrd.x" },				//42
};
CModel::CModel()
{
}

CModel::~CModel()
{
}
//====================================================================
//���f���̃��[�h
//====================================================================
void CModel::LoadModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	D3DXMATERIAL *pMat;

	//�v���C���[�̃��f���ǂݍ���
	for (int nCnt = 0; nCnt < MODEL_PLAYER_MAX; nCnt++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(
			m_PlayerFileName[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_Model[PLAYER_MODEL][nCnt].pBuffmat,
			NULL,
			&m_Model[PLAYER_MODEL][nCnt].nNumMat,
			&m_Model[PLAYER_MODEL][nCnt].pMesh
		);
		m_Model[PLAYER_MODEL][nCnt].m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_Model[PLAYER_MODEL][nCnt].nNumMat];
		pMat = (D3DXMATERIAL*)m_Model[PLAYER_MODEL][nCnt].pBuffmat->GetBufferPointer();

		for (int nCntmat = 0; nCntmat < (int)m_Model[PLAYER_MODEL][nCnt].nNumMat; nCntmat++)
		{
			m_Model[PLAYER_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
			D3DXCreateTextureFromFile(pDevice, pMat[nCntmat].pTextureFilename, &m_Model[PLAYER_MODEL][nCnt].m_pTexture[nCntmat]);
		}
	}

	//�}�b�v�̃��f���ǂݍ���
	for (int nCnt = 0; nCnt < MODEL_MAP_MAX; nCnt++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(
			m_MapFileName[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_Model[MAP_MODEL][nCnt].pBuffmat,
			NULL,
			&m_Model[MAP_MODEL][nCnt].nNumMat,
			&m_Model[MAP_MODEL][nCnt].pMesh
		);
		m_Model[MAP_MODEL][nCnt].vtxMin = D3DXVECTOR3(1000, 1000, 1000);
		m_Model[MAP_MODEL][nCnt].vtxMax = D3DXVECTOR3(-1000, -1000, -1000);
		//�e�N�X�`���̃������m��
		m_Model[MAP_MODEL][nCnt].m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_Model[MAP_MODEL][nCnt].nNumMat];
		pMat = (D3DXMATERIAL*)m_Model[MAP_MODEL][nCnt].pBuffmat->GetBufferPointer();

		//�e�N�X�`���}�e���A�����̊i�[
		for (int nCntmat = 0; nCntmat < (int)m_Model[MAP_MODEL][nCnt].nNumMat; nCntmat++)
		{
			m_Model[MAP_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
			D3DXCreateTextureFromFile(pDevice, pMat[nCntmat].pTextureFilename, &m_Model[MAP_MODEL][nCnt].m_pTexture[nCntmat]);
		}
	}
	//�G�l�~�[�̃��f���ǂݍ���
	for (int nCnt = 0; nCnt < MODEL_ENEMY_MAX; nCnt++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(
			m_EnemyFileName[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_Model[ENEMY_MODEL][nCnt].pBuffmat,
			NULL,
			&m_Model[ENEMY_MODEL][nCnt].nNumMat,
			&m_Model[ENEMY_MODEL][nCnt].pMesh
		);
		//�e�N�X�`���̃������m��
		m_Model[ENEMY_MODEL][nCnt].m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_Model[ENEMY_MODEL][nCnt].nNumMat];
		pMat = (D3DXMATERIAL*)m_Model[ENEMY_MODEL][nCnt].pBuffmat->GetBufferPointer();

		for (int nCntmat = 0; nCntmat < (int)m_Model[ENEMY_MODEL][nCnt].nNumMat; nCntmat++)
		{
			m_Model[ENEMY_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
			D3DXCreateTextureFromFile(pDevice, pMat[nCntmat].pTextureFilename, &m_Model[ENEMY_MODEL][nCnt].m_pTexture[nCntmat]);
		}
	}
}
//====================================================================
//���f���̊J��
//====================================================================
void CModel::UnLoad(void)
{
	//�}�b�v�̃��f���ǂݍ���
	for (int nCnt = 0; nCnt < MODEL_PLAYER_MAX; nCnt++)
	{
		if (m_Model[PLAYER_MODEL][nCnt].pBuffmat != NULL)
		{
			m_Model[PLAYER_MODEL][nCnt].pBuffmat->Release();
			m_Model[PLAYER_MODEL][nCnt].pBuffmat = NULL;
		}
		if (m_Model[PLAYER_MODEL][nCnt].pMesh != NULL)
		{
			m_Model[PLAYER_MODEL][nCnt].pMesh->Release();
			m_Model[PLAYER_MODEL][nCnt].pMesh = NULL;
		}
		if (m_Model[PLAYER_MODEL][nCnt].m_pTexture != NULL)
		{
			for (int nCntmat = 0; nCntmat < (int)m_Model[PLAYER_MODEL][nCnt].nNumMat; nCntmat++)
			{
				if (m_Model[PLAYER_MODEL][nCnt].m_pTexture[nCntmat] != NULL)
				{
					m_Model[PLAYER_MODEL][nCnt].m_pTexture[nCntmat]->Release();
					m_Model[PLAYER_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
				}
			}
			delete[] m_Model[PLAYER_MODEL][nCnt].m_pTexture;
			m_Model[PLAYER_MODEL][nCnt].m_pTexture = NULL;
		}
	}
	for (int nCnt = 0; nCnt < MODEL_MAP_MAX; nCnt++)
	{
		if (m_Model[MAP_MODEL][nCnt].pBuffmat != NULL)
		{
			m_Model[MAP_MODEL][nCnt].pBuffmat->Release();
			m_Model[MAP_MODEL][nCnt].pBuffmat = NULL;
		}
		if (m_Model[MAP_MODEL][nCnt].pMesh != NULL)
		{
			m_Model[MAP_MODEL][nCnt].pMesh->Release();
			m_Model[MAP_MODEL][nCnt].pMesh = NULL;
		}
		if (m_Model[MAP_MODEL][nCnt].m_pTexture != NULL)
		{
			for (int nCntmat = 0; nCntmat < (int)m_Model[MAP_MODEL][nCnt].nNumMat; nCntmat++)
			{
				if (m_Model[MAP_MODEL][nCnt].m_pTexture[nCntmat] != NULL)
				{
					m_Model[MAP_MODEL][nCnt].m_pTexture[nCntmat]->Release();
					m_Model[MAP_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
				}
			}
			delete[] m_Model[MAP_MODEL][nCnt].m_pTexture;
			m_Model[MAP_MODEL][nCnt].m_pTexture = NULL;
		}
	}
	for (int nCnt = 0; nCnt < MODEL_ENEMY_MAX; nCnt++)
	{
		if (m_Model[ENEMY_MODEL][nCnt].pBuffmat != NULL)
		{
			m_Model[ENEMY_MODEL][nCnt].pBuffmat->Release();
			m_Model[ENEMY_MODEL][nCnt].pBuffmat = NULL;
		}
		if (m_Model[ENEMY_MODEL][nCnt].pMesh != NULL)
		{
			m_Model[ENEMY_MODEL][nCnt].pMesh->Release();
			m_Model[ENEMY_MODEL][nCnt].pMesh = NULL;
		}
		if (m_Model[ENEMY_MODEL][nCnt].m_pTexture != NULL)
		{
			for (int nCntmat = 0; nCntmat < (int)m_Model[ENEMY_MODEL][nCnt].nNumMat; nCntmat++)
			{
				if (m_Model[ENEMY_MODEL][nCnt].m_pTexture[nCntmat] != NULL)
				{
					m_Model[ENEMY_MODEL][nCnt].m_pTexture[nCntmat]->Release();
					m_Model[ENEMY_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
				}
			}
			delete[] m_Model[ENEMY_MODEL][nCnt].m_pTexture;
			m_Model[ENEMY_MODEL][nCnt].m_pTexture = NULL;
		}
	}
}
//====================================================================
//������
//====================================================================
HRESULT CModel::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	int nNumVertices;
	DWORD sizeFVF;
	BYTE *pVertexBuffer;

	for (int nCnt = 0; nCnt < MODEL_MAP_MAX; nCnt++)
	{
		if (m_Model[MAP_MODEL][nCnt].pMesh != NULL)
		{
			//���_�����擾
			nNumVertices = m_Model[MAP_MODEL][nCnt].pMesh->GetNumVertices();
			//���_�t�H�[�}�b�g�̃T�C�Y���擾
			sizeFVF = D3DXGetFVFVertexSize(m_Model[MAP_MODEL][nCnt].pMesh->GetFVF());
			//���_�o�b�t�@�����b�N
			m_Model[MAP_MODEL][nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertexBuffer);
			for (int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVertexBuffer;
				//���ׂĂ̒��_�����r���čŏ��A�ő�𔲂��o��
				if (m_Model[MAP_MODEL][nCnt].vtxMin.x > vtx.x)
				{
					m_Model[MAP_MODEL][nCnt].vtxMin.x = vtx.x;
				}
				if (m_Model[MAP_MODEL][nCnt].vtxMin.y > vtx.y)
				{
					m_Model[MAP_MODEL][nCnt].vtxMin.y = vtx.y;
				}
				if (m_Model[MAP_MODEL][nCnt].vtxMin.z > vtx.z)
				{
					m_Model[MAP_MODEL][nCnt].vtxMin.z = vtx.z;
				}
				if (m_Model[MAP_MODEL][nCnt].vtxMax.x < vtx.x)
				{
					m_Model[MAP_MODEL][nCnt].vtxMax.x = vtx.x;
				}
				if (m_Model[MAP_MODEL][nCnt].vtxMax.y < vtx.y)
				{
					m_Model[MAP_MODEL][nCnt].vtxMax.y = vtx.y;
				}
				if (m_Model[MAP_MODEL][nCnt].vtxMax.z < vtx.z)
				{
					m_Model[MAP_MODEL][nCnt].vtxMax.z = vtx.z;
				}
				pVertexBuffer += sizeFVF; // �T�C�Y���|�C���^��i�߂�
			}
			//���_�o�b�t�@���A�����b�N
			m_Model[MAP_MODEL][nCnt].pMesh->UnlockVertexBuffer();
		}
	}
	return S_OK;
}
//====================================================================
//�I��
//====================================================================
void CModel::Uninit(void)
{
	for (int nCnttype = 0; nCnttype < TYPE_MAX; nCnttype++)
	{
		for (int nCnt = 0; nCnt < MODEL_MAP_MAX; nCnt++)
		{
			// ���b�V���̊J��
			if (m_Model[nCnttype][nCnt].pMesh != NULL)
			{
				m_Model[nCnttype][nCnt].pMesh->Release();
				m_Model[nCnttype][nCnt].pMesh = NULL;
			}

			// �}�e���A���̊J��
			if (m_Model[nCnttype][nCnt].pBuffmat != NULL)
			{
				m_Model[nCnttype][nCnt].pBuffmat->Release();
				m_Model[nCnttype][nCnt].pBuffmat = NULL;
			}
		}
	}
}
//====================================================================
//�X�V
//====================================================================
void CModel::Update(void)
{
}
//====================================================================
//�`��
//====================================================================
void CModel::Draw(D3DXMATRIX mat)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans,mtxScal;
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 matDef;
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y,
		m_rot.x,
		m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x,
		m_pos.y,
		m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxTrans);

	// �|���S���̕`��
	pDevice->SetTexture(0, NULL);
	//�e�q�֌W
	if (m_pParent== NULL)
	{
		D3DXMatrixMultiply(&m_mtxWorld,
			&m_mtxWorld,
			&mat);
	}
	else
	{
		D3DXMatrixMultiply(&m_mtxWorld,
			&m_mtxWorld,
			&m_pParent->m_mtxWorld);
	}
	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);
	// �}�e���A�����ɑ΂���|�C���^���擾
	if (m_Model[m_type][m_modelCount].pBuffmat != NULL)
	{
		pMat = (D3DXMATERIAL*)m_Model[m_type][m_modelCount].pBuffmat->GetBufferPointer();
		pDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);						// ���؂���烂�[�h�L��
		for (int nCnt = 0; nCnt < (int)m_Model[m_type][m_modelCount].nNumMat; nCnt++)
		{
			pDevice->SetTexture(0, m_Model[m_type][m_modelCount].m_pTexture[nCnt]);
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCnt].MatD3D);
			// �`��
			m_Model[m_type][m_modelCount].pMesh->DrawSubset(nCnt);
		}
	}
	pDevice->SetRenderState(D3DRS_SPECULARENABLE, FALSE);						// ���؂���烂�[�h�L��

	// �}�e���A�����f�t�H���g�ɖ߂�
	//pDevice->SetMaterial(&matDef);
}
//====================================================================
//���f���̃N���G�C�g
//====================================================================
CModel *CModel::Create(int type, int modelCount)
{
	CModel*pModel;
	pModel = new CModel();
	pModel->Init();
	pModel->m_type = type;
	pModel->m_modelCount = modelCount;
	return pModel;
}
//====================================================================
//�e�̐ݒ�
//====================================================================
void CModel::SetParent(CModel * pModel)
{
	m_pParent = pModel;
}
//====================================================================
//���f���̃I�t�Z�b�g�w��
//====================================================================
void CModel::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
void CModel::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
void CModel::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}
void CModel::SetType(int type)
{
	m_modelCount = type;
}
//====================================================================
//�ʒu�̎擾
//====================================================================
D3DXVECTOR3 &CModel::GetPosition(void)
{
	return m_pos;
}
//====================================================================
//��]�̎擾
//====================================================================
D3DXVECTOR3 &CModel::GetRot(void)
{
	return m_rot;
}
//====================================================================
//���f���^�C�v�̎擾
//====================================================================
int CModel::GetType(void)
{
	return m_modelCount;
}
//====================================================================
//���b�V���擾
//====================================================================
LPD3DXMESH CModel::GetMesh(void)
{
	return m_Model[m_type][m_modelCount].pMesh;
}
//====================================================================
//�}�g���b�N�X�̎擾
//====================================================================
D3DXMATRIX *CModel::GetMatrix(void)
{
	return &m_mtxWorld;
}
//====================================================================
//���_����MAX�擾
//====================================================================
D3DXVECTOR3 CModel::GetvtxMax(int nCnt)
{
	return m_Model[MAP_MODEL][nCnt].vtxMax;
}
//====================================================================
//���_����MIN�擾
//====================================================================
D3DXVECTOR3 CModel::GetvtxMin(int nCnt)
{
	return m_Model[MAP_MODEL][nCnt].vtxMin;
}
