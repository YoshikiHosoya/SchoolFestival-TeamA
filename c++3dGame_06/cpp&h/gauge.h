// ----------------------------------------
//
// �`���[�g���A��UI�����̐���[tutorial_ui.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _GAUGE_UI_H_
#define _GAUGE_UI_H_	 // �t�@�C������������߂�

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "scene_two.h"

// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
#define GAGE_VALUE_MAX		(120)			// �Q�[�W�̒l�̍ő�

#define GAGE_VALUE_FAST		(GAGE_VALUE_MAX * 0.3333f)	// �Q�[�W�̒l1
#define GAGE_VALUE_SECOND	(GAGE_VALUE_MAX * 0.6666f)	// �Q�[�W�̒l2
#define GAGE_VALUE_THIRD	(GAGE_VALUE_MAX * 1.0f)		// �Q�[�W�̒l3

// ----------------------------------------
//
// �O���錾
//
// ----------------------------------------

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CGauge : public CScene
{
public:
	/* �񋓌^ */
	typedef enum
	{
		GAUGE_GAUGE = 0,//�Q�[�W�̊O�g
		GAUGE_FRAME,//�Q�[�W�{��
		GAUGE_MAX
	} GAUGE;

	/* �֐� */
	CGauge();
	~CGauge();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);		// �ǂݍ���
	static void UnLoad(void);		// UnLoad����
	static CGauge * Create(void);	// �쐬
protected:

private:
	/* �֐� */
	void Various(int nCnt);											// ��ޕʏ���

	/* �ϐ� */
	static LPDIRECT3DTEXTURE9	m_pTex[GAUGE_MAX];			// �e�N�X�`���[�ݒ�
	static D3DXVECTOR3			m_pos[GAUGE_MAX];			// �ʒu���
	static D3DXVECTOR2			m_size[GAUGE_MAX];			// �T�C�Y���
	CScene_TWO					*m_aScene_Two[GAUGE_MAX];	// �`���[�g���A���pui2D
	int							m_nMaxGauge;				// �Q�[�W�̍ő�l
	float						m_fTex;						//�e�N�X�`���̍��W
	float						m_fAbilityTime;
};

#endif