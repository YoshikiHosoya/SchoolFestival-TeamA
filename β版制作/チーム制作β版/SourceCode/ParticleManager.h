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
#include "Particle.h"

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define MAX_PARTICLE (100000)
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------


//�p�[�e�B�N���̂܂Ƃ܂�
class CParticleManager : public CScene
{
public:
	CParticleManager();									//�R���X�g���N�^
	CParticleManager(OBJ_TYPE obj);						//�R���X�g���N�^
	~CParticleManager();								//�f�X�g���N�^

	HRESULT Init();									//������
	void Uninit();									//�I��
	void Update();									//�X�V
	void Draw();									//�`��
	void DebugInfo();							//�f�o�b�O���\�L

	static void Create();
	static void AddParticleList(std::unique_ptr<CParticle> pParticle);

private:
	static std::vector<std::unique_ptr<CParticle>> m_pParticleList;		//�p�[�e�B�N���̍\���̂̃��X�g
};

#endif