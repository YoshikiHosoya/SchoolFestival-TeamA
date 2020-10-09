//------------------------------------------------------------------------------
//
//�p�[�e�B�N���̊Ǘ�����  [ParticleManager.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _PARTICLE_MANAGER_H_
#define _PARTICLE_MANAGER_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CParticle;

//�p�[�e�B�N���̊Ǘ�
class CParticleManager : public CScene
{
public:
	CParticleManager();									//�R���X�g���N�^
	~CParticleManager();								//�f�X�g���N�^

	HRESULT Init();									//������
	void Uninit();									//�I��
	void Update();									//�X�V
	void Draw();									//�`��
	void ShowDebugInfo();							//�f�o�b�O���\�L

	static void Create();
	static void Release();
	static void AddParticleList(std::unique_ptr<CParticle> pParticle);

private:
	static std::vector<std::unique_ptr<CParticle>> m_pParticleList;		//�p�[�e�B�N���̍\���̂̃��X�g
};

#endif