//-----------------------------------------------------------------------------
//
// ���b�V���h�[������ [meshsphere.h]
// Author : Fujiwara Masato
//
//-----------------------------------------------------------------------------
#ifndef _MESHSPHERE_H_
#define _MESHSPHERE_H_

#define _CRT_SECURE_NO_WARNINGS

//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "Scene.h"


//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define MAX_MESHSPHERE	(20)
#define RADIUS_SIZE		(45.0f)
#define SEPARATE		(15)


//-----------------------------------------------------------------------------
// �N���X��`
//-----------------------------------------------------------------------------
class CMeshsphere :public CScene
{
public:
	typedef struct
	{
		D3DXVECTOR3		pos;								//���W
		D3DXVECTOR3		rot;								//��]
		D3DXCOLOR		col;								//�F
		D3DXMATRIX		mtxWorldMeshSphere;					//���[���h�}�g���b�N�X
		float			fRadius;							//���a
		float			fRot;								//�e���_�̊p�x
		float			fRot2;								//�e���_�̊p�x
		int				nHeightBlock;						//�����̕�����
		int				nSeparate;							//�~�̒��_�̌�
		int				nMaxVtx;							//���_�̌�
		int				nMaxIndex;							//�C���f�b�N�X�̌�
		int				nMaxPolygon;						//�|���S���̖���
		int				nIdxCollisionSphere;				//�~�����ID
		bool			bUse;								//���_�ƒ����_�̋���
		bool			bDisp;								//�ʂ����ǂ���
		LPDIRECT3DVERTEXBUFFER9	pVtxBuffMeshSphere = NULL;	//���_�o�b�t�@�ւ̃|�C���^
		LPDIRECT3DINDEXBUFFER9	pIdxBuffMeshSphere = NULL;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	}	MESHSPHERE;
	CMeshsphere();
	~CMeshsphere();

	static CMeshsphere *create(void);
	void Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��
	static void Load(void);	// �ǂݍ���
	static void Unload(void);	// �j��
	static int Set(CONST D3DXVECTOR3 pos, const float fRadius);

	static void SetPosition(int nIdxCollisionSphere, D3DXVECTOR3 pos);
	static void DeleteCollision(int nIdxCollisionSphere);
	static void SetRadius(int nIdxCollisionSphere, float fRadius);
private:
	static MESHSPHERE	m_aMeshSphere[MAX_MESHSPHERE];
	static LPDIRECT3DTEXTURE9 m_pTex;
};

#endif
