//------------------------------------------------------------------------------
//
//�p�[�c�ƂȂ郂�f���̏���  [modelparts.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MODELPARTS_H_
#define _MODELPARTS_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "sceneX.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CCollision;
class CModel_Object : public CSceneX
{
public:
	CModel_Object();
	virtual ~CModel_Object();

	HRESULT Init();														//������
	void Uninit();														//�I��
	void Update();														//�X�V
	void Draw();														//�`��
	void ShowDebugInfo();												//�f�o�b�O���\�L
	static void Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				//��������
	CCollision *GetCollision() { return m_pCollision.get(); };			//����̎擾

private:
	std::shared_ptr<CCollision> m_pCollision;							//�����蔻��̃|�C���^

};
#endif