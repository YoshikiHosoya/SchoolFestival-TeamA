//------------------------------------------------------------------------------
//
//�~�j�}�b�v����  [minimap.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MINIMAP_H_
#define _MINIMAP_H_
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
class CScene2D;
class CEnemy;

class CMiniMap : public::CScene
{
public:
	enum TEX_TYPE
	{
		TEX_MAP = 0,			//�}�b�v
		TEX_PLAYER,				//�v���C���[
		TEX_EXPLOSION,			//����
		TEX_ENEMY,				//�G
		TEX_MAX
	};


	CMiniMap();
	~CMiniMap();

	HRESULT Init();									//������
	void Uninit();									//�I��
	void Update();									//�X�V
	void Draw();									//�`��
	void ShowDebugInfo();							//�f�o�b�O���\�L

	static void Create();							//��������
protected:

private:
	std::vector<std::shared_ptr<CScene2D>> m_pEnemyMappingList;			//�G�̃}�b�v��̃|���S��
	std::vector<std::shared_ptr<CScene2D>> m_pExplosionMappingList;		//�����̃}�b�v��̃|���S��
	std::shared_ptr<CScene2D> m_pPlayerMapping;							//�v���C���[�̃}�b�v��̃|���S��
};
#endif