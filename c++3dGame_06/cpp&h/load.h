//=============================================================================
//
// ���[�h��񏈗� [load.h]
// Author : Fujiwara Masato
//
//=============================================================================
#ifndef _LOAD_H_
#define _LOAD_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �O���錾
//=============================================================================

//=============================================================================
// �\����
//=============================================================================
// �}�e���A�����
typedef struct
{
	int nType;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
} MATERIAL_INFO;

// �r���{�[�h���
typedef struct
{
	int nType;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 size;
} BILLBOARD_INFO;

// ���b�V�����
typedef struct
{
	int nType;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	int			nBlockDipth;
	int			nBlockWidth;
	float		fSizeX;
	float		fSizeZ;
} MESH_INFO;

//=============================================================================
// �N���X
//=============================================================================
class CLoad
{
public:
	/* �\���� */
	// ���
	typedef struct
	{
		int nType;
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		D3DXCOLOR	col;
		D3DXVECTOR3	size;
		int			nBlockDipth;
		int			nBlockWidth;
	} INFO;

	/* �֐� */
	CLoad();
	~CLoad();
	// ���擾
	// �ǂݍ���
	// �J��
	void Unload(void);
	// �ǂݍ���
	int Load(
		const char* filename		// �t�@�C����
	);
	// �擾
	INFO &GetInfo(int nID);			// ���
	int &GetShard(void);				// �W�����v
protected:
private:
	INFO info[1500];					// ���
	//
	int m_nMax3DItem;					// 3D�A�C�e���̑���
};

#endif
