// ----------------------------------------
//
// �V�[�������̐���[scene_load.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "scene_load.h"

/* �`�� */
#include "tlybg.h"
#include "title_ui.h"
#include "pause.h"
#include "floor.h"
#include "player.h"
#include "item.h"
#include "3Deffect.h"
#include "3Dparticle.h"
#include "meshdome.h"
#include "collision.h"
#include "gauge.h"
#include "meshsphere.h"
#include "wall.h"
#include "enemy.h"
#include "3ditem.h"
#include "3dline.h"
#include "object.h"
#include "TitleObject.h"
#include "lighteffect.h"
#include "gate.h"
#include "explosion.h"
#include "titleEnemy.h"
#include "telop.h"
#include "TelopComment.h"
#include "bulletinboard.h"
#include "2DAnimationUI.h"
#include "key.h"
#include "floartile.h"
#include "3DTexture.h"
#include "ceiling.h"
#include "mapmark.h"
#include "gameui.h"
#include "manual.h"

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CScene_load::CScene_load()
{
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CScene_load::~CScene_load()
{
}

// ----------------------------------------
// �V�[���e�q�쐬����
// ----------------------------------------
void CScene_load::LoadAll(void)
{
	/* �e�N�X�`���[�ǂݍ��� */
	// �w�i
	CTlyBg::Load();
	// �|�[�Y
	CPause::Load();
	// �^�C�g��UI
	CTitle_ui::Load();
	// �`���[�g���A��UI
	//CTutorial_ui::Load();
	// �^�C�g��UI
	CGame_ui::Load();
	// ��
	CFloor::Load();
	// ���b�V���h�[��
	CMeshdome::Load();
	// ���b�V���X�t�B�A
	CMeshsphere::Load();
	// �v���C���[
	CPlayer::Load();
	// �A�C�e��
	CItem::Load();
	// 3DItem
	C3DItem::Load();
	// 3Deffect
	C3DEffect::Load();
	// 3Dparticle
	C3DParticle::Load();
	// �����蔻��
	CCollision::Load();
	// �Q�[�W
	CGauge::Load();
	// ��ʃX�R�A
	//CTopscore::Load();
	// ��
	CWall::Load();
	// �G
	CEnemy::Load();
	//
	//C3DLine::Load();
	// �I�u�W�F�N�g
	CObject::Load();
	// �^�C�g���p�I�u�W�F�N�g
	CTitleObject::Load();
	// ���C�g�G�t�F�N�g
	CLightEffect::Load();
	// �Q�[�����J�n���邽�߂̃Q�[�g
	CGate::Load();
	// �����G�t�F�N�g
	CExplosion::Load();
	// �^�C�g���p�̓G
	CTitleEnemy::Load();
	// �e���b�v
	CTelop::Load();
	// �e���b�v�R�����g
	CTelopComment::Load();
	// �f����
	CBulletinBoard::Load();
	// 2DAnimation
	C2DAnimation::Load();
	// ��
	CKey::Load();
	// ���^�C��
	CFloarTile::Load();
	// 3d�e�N�X�`��
	C3DTexture::Load();
	// �V��
	CCeiling::Load();
	// �}�b�v�}�[�N
	CMapMark::Load();
	// �}�j���A��
	CManual::Load();
}

// ----------------------------------------
// �ǂݍ��񂾂��̂�j�����鏈��
// ----------------------------------------
void CScene_load::UnLoadAll(void)
{
	/* �ǂݍ��񂾂��̂̔j��*/
	// �w�i
	CTlyBg::UnLoad();
	// �|�[�Y
	CPause::UnLoad();
	// �^�C�g��UI
	CTitle_ui::UnLoad();
	// �`���[�g���A��UI
	//CTutorial_ui::UnLoad();
	// �^�C�g��UI
	CGame_ui::UnLoad();
	// ��
	CFloor::UnLoad();
	// ���b�V���h�[��
	CMeshdome::UnLoad();
	// ���b�V���X�t�B�A
	CMeshsphere::Unload();
	// �v���C���[
	CPlayer::UnLoad();
	// �A�C�e��
	CItem::UnLoad();
	// 3DItem
	C3DItem::UnLoad();
	// 3Deffect
	C3DEffect::Unload();
	// 3Dparticle
	C3DParticle::Unload();
	// �Q�[�W
	CGauge::UnLoad();
	// ��
	CWall::UnLoad();
	// �G
	CEnemy::UnLoad();
	//
	//C3DLine::UnLoad();
	//�I�u�W�F�N�g
	CObject::UnLoad();
	// �^�C�g���p�I�u�W�F�N�g
	CTitleObject::UnLoad();
	// ���C�g�G�t�F�N�g
	CLightEffect::UnLoad();
	// �Q�[�����J�n���邽�߂̃Q�[�g
	CGate::UnLoad();
	// �^�C�g���p�̓G
	CExplosion::UnLoad();
	// �^�C�g���p�̓G
	CTitleEnemy::UnLoad();
	// �e���b�v
	CTelop::UnLoad();
	// �e���b�v�R�����g
	CTelopComment::UnLoad();
	// �f����
	CBulletinBoard::UnLoad();
	// 2DAnimation
	C2DAnimation::UnLoad();
	// ��
	CKey::UnLoad();
	// ���^�C��
	CFloarTile::UnLoad();
	// 3d�e�N�X�`��
	C3DTexture::UnLoad();
	// �V��
	CCeiling::UnLoad();
	// �}�b�v�}�[�N
	CMapMark::UnLoad();
	// �}�j���A��
	CManual::UnLoad();
}