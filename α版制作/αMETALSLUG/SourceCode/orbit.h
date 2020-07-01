//------------------------------------------------------------------------------
//
//�O�Տ���  [orbit.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MESHORBIT_H_
#define _MESHORBIT_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scene2D.h"
#include "scene.h"

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define MAX_ORBIT_LENGTH	(50)
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class COrbit : public CScene
{
public:
	COrbit();
	COrbit(OBJ_TYPE obj) : CScene(obj) {};
	~COrbit();

	HRESULT Init();													//������
	void Uninit();													//�I��
	void Update();													//�X�V
	void Draw();													//�`��
	void DebugInfo();												//�f�o�b�O���\�L
	void SetOrbit(D3DXVECTOR3 pos01, D3DXVECTOR3 pos02);			//�O�Րݒ�
	void DeleteOrbit();												//�O�Տ���
	static COrbit *Create(D3DXMATRIX *pMtx);		//��������

	//Set�֐�
	void SetLife(int nLife) { m_nLife = nLife; };									//���C�t�ݒ�
	void SetCol(D3DXCOLOR col) { m_coldefault = col; };								//�F�ݒ�
	void SetMtx(D3DXMATRIX *pMtx) { m_pParentMtx = pMtx; };							//�}�g���b�N�X�̃|�C���^�ݒ�
	void SetPosOffset(D3DXVECTOR3 posOffset) { m_posOffset = posOffset; };			//���΍��W�ݒ�

private:
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;						//���_�o�b�t�@�ւ̃|�C���^

	D3DXMATRIX *m_pParentMtx;								//�e�̃}�g���b�N�X�ւ̃|�C���^
	D3DXVECTOR3 m_posOffset;								//��[�ւ̑��΍��W

	int m_nLife;											//�t���O�������Ă���̃��C�t
	bool m_bDeleteFlag;										//�����邩�ǂ���
	float m_fLength;										//�O�Ղ̒���
	D3DXCOLOR m_coldefault;									//�ŏ��̐F
	D3DXCOLOR m_col[MAX_ORBIT_LENGTH];						//�F
	D3DXVECTOR3 m_posVertex[MAX_ORBIT_LENGTH];				//�e���_�̍��W

	void CalcOrbitPos();									//�O�Ղ̍��W�v�Z
	void SetDefaultVtxPos();								//�����ݒ�

};

#endif