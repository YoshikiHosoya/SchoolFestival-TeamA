//------------------------------------------------------------------------------
//
//�I�v�V��������  [option.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _OPTION_H_
#define _OPTION_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CScene2D;

class COption : public CScene
{
public:
	COption();
	~COption();

	//�e�N�X�`���̎��
	enum TEX_TYPE
	{
		TEX_OPTION_BG,		//�w�i
		TEX_OPTION_LOGO,	//���S
		TEX_OPTION_MENU,	//���j���[
		TEX_ON_OFF,			//ON�@OFF
		TEX_MAX
	};

	enum OPTION_ITEM
	{
		OPTION_CAMERA_AUTO_ROTATION = 0,		//�J�����̎�����]
		OPTION_CAMERA_FLIP_X,					//X�����]
		OPTION_CAMERA_FLIP_Y,					//Y�����]
		OPTOIN_MAX
	};

	HRESULT Init();									//������
	void Uninit();									//�I��
	void Update();									//�X�V
	void Draw();									//�`��
	void ShowDebugInfo();							//�f�o�b�O���\�L
	static std::unique_ptr<COption> Create();		//��������

	//Get�֐�
	static bool GetAutoRotation() { return m_bAutoRotation; };		//�J�����̎�����]
	static bool GetCameraFlip_X() { return m_bCameraFlip_X; };		//X�����]
	static bool GetCameraFlip_Y() { return m_bCameraFlip_Y; };		//Y�����]

private:
	std::vector<std::unique_ptr<CScene2D>> m_pScene2DList;			//2D�|���S��
	std::vector<std::unique_ptr<CScene2D>> m_pOptionItemList;		//2D�|���S���I�v�V�����̃��X�g
	std::vector<std::unique_ptr<CScene2D>> m_OnOffList;				//ONOFF�̃��X�g

	int m_NowSelectItem;											//���ݑI�����Ă���A�C�e��

	static bool m_bCameraFlip_X;		//�J����X���̔��]
	static bool m_bCameraFlip_Y;		//�J����Y���̔��]
	static bool m_bAutoRotation;		//�J����������]
};

#endif