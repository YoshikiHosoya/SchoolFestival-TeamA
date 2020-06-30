//------------------------------------------------------------------------------
//
//���U���g����  [result.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _RESULT_H_
#define _RESULT_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "basemode.h"
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CMultiNumber;

class CResult : public CBaseMode
{
public:
	CResult();
	~CResult();

	enum RESULT_ITEM
	{
		RESULT_COMBO = 0,
		REUSLT_KILL,
		RESULT_TOTAL
	};

	HRESULT Init(HWND hWnd);			//������
	void Uninit();						//�I��
	void Update();						//�X�V
	void Draw();						//�`��
	void ShowDebugInfo() {};			//�f�o�b�O���\�L

	CPlayer* GetPlayer() { return nullptr; };		//�v���C���[�擾����

private:
	int m_nCntResult;												//�J�E���^
	std::vector<std::shared_ptr<CMultiNumber>>	m_pNumberList;		//���l�̃��X�g
	void PopResultItem();											//�J�E���^�ɉ����ă��U���g�̍��ڏo��
};

#endif