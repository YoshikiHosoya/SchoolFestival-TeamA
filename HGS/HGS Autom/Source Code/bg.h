//------------------------------------------------------------------------------
//
//�w�i�̏���  [bg.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _BG_H_
#define _BG_H_
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

class CBg : public CScene
{
public:
	enum class BG_FIGURE
	{
		BG_NONE = -1, 
		BG_Circle,			// �܂�
		BG_Triangle,		// �O�p
		BG_Square,			// �l�p
		BG_Star,			// ��
		BG_Cross,			// �΂�
		BG_MAX,
	};

	enum class BG_FIGURE_SIZE
	{
		NONE = -1,
		SMALL,			// ��
		MEDIUM,			// ��
		BIG,			// ��
		FIGURE_SIZE_MAX,
	};

	CBg();
	~CBg();

	HRESULT Init();						//������
	void Uninit();						//�I��
	void Update();						//�X�V
	void Draw();						//�`��
	void ShowDebugInfo() {};			//�f�o�b�O���\�L

	static std::unique_ptr<CBg> Create(int DropNum);			//��������

private:
	void	RandomFigure();						// �����_���}�`�̐���

	std::vector<std::shared_ptr<CScene2D>>		m_apScene2D;						// �w�i
	std::shared_ptr<CScene2D>					m_pGridLine;						// �O���b�h��

	D3DXVECTOR3			m_FigureSize;			// �}�`�̃T�C�Y
	D3DXVECTOR3			m_FigureMove;			// �}�`�̈ړ���
	BG_FIGURE_SIZE		m_FigureSizeType;		// �}�`�̃T�C�Y�̎��
	BG_FIGURE			m_FigureType;			// �}�`�̎��
	int					m_nCntScroll;			// �X�N���[���J�E���g
	int					m_DropRangeNum;			// �����鋖�e�͈�
};

#endif