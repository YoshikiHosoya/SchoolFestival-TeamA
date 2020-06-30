//------------------------------------------------------------------------------
//
//�������̐����̏���  [multinumber.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MULTINUMBER_H_
#define _MULTINUMBER_H_
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

//�O���錾
class CNumber;

class CMultiNumber : public CScene
{
public:
	//���
	enum TYPE
	{
		TYPE_NORMAL,							//�ʏ�
		TYPE_RED,								//�Ԏ�
		TYPE_FLASHING,							//�_��
		TYPE_CENTER_DISAPPEAR,					//�����ɏo�Ă��Ď��R�ɏ����Ă�
	};

	CMultiNumber();
	~CMultiNumber();
	HRESULT Init();													//������
	void Uninit();													//�I��
	void Update();													//�X�V
	void Draw();													//�`��
	void ShowDebugInfo();											//�f�o�b�O���
	static std::shared_ptr<CMultiNumber> Create(D3DXVECTOR3 pos, D3DXVECTOR3 onesize, int nValue, int nDigits, CScene::OBJTYPE objtype);	//��������
	void SetMultiNumber(int nValue);								//�X�R�A�ݒ菈��
	void SetChangeAnimation(int nValue,int nValueOld);				//�؂�ւ�������̃A�j���[�V��������

	void SetCol(D3DXCOLOR col);										//�F�ݒ�
	void SetPos(D3DXVECTOR3 pos);									//���W�ݒ�
	void SetSize(D3DXVECTOR3 size);									//�T�C�Y�ݒ�
	void Settype(CMultiNumber::TYPE type) { m_type = type; };		//��ސݒ�

	D3DXVECTOR3 GetPos() { return m_pos; };							//���W�擾
	D3DXVECTOR3 GetSize() { return m_onesize; };					//�T�C�Y�擾

private:
	std::vector<std::unique_ptr<CNumber>> m_pNumberList;	//�i���o�[�̃|�C���^�̃��X�g
	D3DXVECTOR3 m_pos;										//���W
	D3DXVECTOR3 m_onesize;									//1������̃T�C�Y
	int m_nValue;											//�l
	int m_nCnt;												//�_�ŃJ�E���g
	TYPE m_type;											//���

};

#endif