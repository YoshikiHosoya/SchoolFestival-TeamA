// ----------------------------------------
//
// ��ʏ�ʃX�R�A�����̐���[topscore.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _TOPSCORE_H_
#define _TOPSCORE_H_	 // �t�@�C������������߂�

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "scene.h"

// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
#define MAX_NUMBERSCORE (7)
#define MAX_TOPSCORE (5)

class CNumber;
class CMark;
// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CTopscore : public CScene
{
public:
	/* �֐� */
	CTopscore();
	~CTopscore();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTopscore(int nNumber);
	static void Load(void);
	static void Save(void);
	static void SetScore(const int nScore);			// �X�R�A�ݒ�
	static CTopscore * Create(D3DXVECTOR3 pos);	// �쐬

protected:

private:
	/* �֐� */
	/* �ϐ� */
	static int m_nTopScore[MAX_TOPSCORE];	// ��ʃX�R�A
	static int m_nMyScore;					// �}�C�X�R�A
	static int m_nInRank;					// �����N�C��
	CNumber *m_pNumber[MAX_NUMBERSCORE];	// ��ʃX�R�A�\��
	D3DXVECTOR3 m_pos;						// �ʒu���
	int m_nScore;						// ���_
};

#endif