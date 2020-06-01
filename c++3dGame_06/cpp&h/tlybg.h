// ----------------------------------------
//
// �����w�i�����̐���[tlybg.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _TLYBG_H_
#define _TLYBG_H_	 // �t�@�C������������߂�

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "main.h"
#include "scene_two.h"

// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
#define MAX_TLYBG (1)

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CTlyBg : public CScene
{
public:
	/* �֐� */
	CTlyBg();
	~CTlyBg();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void UnLoad(void);
	static CTlyBg * Create(CManager::MODE mode);	// �쐬
protected:

private:
	static LPDIRECT3DTEXTURE9 m_pTex[CManager::MODE_MAX][MAX_TLYBG];
	static CManager::MODE m_mode;									// ���[�h
	static D3DXVECTOR3 m_pos[CManager::MODE_MAX][MAX_TLYBG];			// �ʒu���
	static D3DXVECTOR2 m_size[CManager::MODE_MAX][MAX_TLYBG];			// �T�C�Y���
	CScene_TWO *m_aScene_Two[MAX_TLYBG];
};

#endif