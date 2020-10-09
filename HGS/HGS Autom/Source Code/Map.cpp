//------------------------------------------------------------------------------
//
//�}�b�v����  [map.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "Map.h"
#include "renderer.h"
#include "manager.h"
#include "meshfield.h"
#include "meshsphere.h"
#include "model_object.h"
#include "sound.h"
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define MESH_SIZE		(200.0f)
#define MESH_BLOCK_NUM	(INTEGER2(40,40))
#define WALL_BLOCK_NUM	(INTEGER2(8,8))
#define WALL_SIZE		(400.0f)
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CMap::CMap()
{
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CMap::~CMap()
{
}
//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
std::unique_ptr<CMap> CMap::Create()
{
	//�������m��
	std::unique_ptr<CMap> pMap(new CMap);

	//�t�B�[���h����
	CreateField(D3DXVECTOR3(MESH_SIZE, 0.0f, MESH_SIZE), INTEGER2(MESH_BLOCK_NUM.x, MESH_BLOCK_NUM.y));

	////�ǐ����@�t�B�[���h�̔����̃T�C�Y
	CreateWall(INTEGER2(WALL_BLOCK_NUM.x, WALL_BLOCK_NUM.x));

	return pMap;
}
//------------------------------------------------------------------------------
//�t�B�[���h�̍L���擾
//------------------------------------------------------------------------------
D3DXVECTOR3 CMap::GetFieldSize()
{
	return D3DXVECTOR3(WALL_SIZE * WALL_BLOCK_NUM.x - 130.0f, 0.0f, WALL_SIZE * WALL_BLOCK_NUM.y - 130.0f);
}
//------------------------------------------------------------------------------
//�t�B�[���h�쐬
//------------------------------------------------------------------------------
void CMap::CreateField(D3DXVECTOR3 size, INTEGER2 BlockNum)
{
	//�t�B�[���h
	CMeshField::Create(ZeroVector3, size, BlockNum);

}
//------------------------------------------------------------------------------
//���ɂȂ�悤�ɕǂ�z�u�@���̑傫����BlockNum�ɂ���Č��܂�
//------------------------------------------------------------------------------
void CMap::CreateWall(INTEGER2 BlockNum)
{
	//�O��̕�
	for (int nCntV = 0; nCntV < BlockNum.x; nCntV++)
	{
		CModel_Object::Create(D3DXVECTOR3(BlockNum.x * WALL_SIZE * 0.5f - nCntV * WALL_SIZE - (WALL_SIZE * 0.5f), 0.0f, WALL_SIZE * BlockNum.y * 0.5f), ZeroVector3);									//�O
		CModel_Object::Create(D3DXVECTOR3(BlockNum.x * WALL_SIZE * 0.5f - nCntV * WALL_SIZE - (WALL_SIZE * 0.5f), 0.0f, -WALL_SIZE * BlockNum.y * 0.5f), ZeroVector3);									//��
	}
	//���E�̕�
	for (int nCntH = 0; nCntH < BlockNum.x; nCntH++)
	{
		CModel_Object::Create(D3DXVECTOR3(-WALL_SIZE * BlockNum.x * 0.5f, 0.0f, BlockNum.y * WALL_SIZE * 0.5f - nCntH * WALL_SIZE - (WALL_SIZE * 0.5f)), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));		//��
		CModel_Object::Create(D3DXVECTOR3(WALL_SIZE * BlockNum.x * 0.5f, 0.0f, BlockNum.y * WALL_SIZE * 0.5f - nCntH * WALL_SIZE - (WALL_SIZE * 0.5f)), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));		//�E
	}
}
