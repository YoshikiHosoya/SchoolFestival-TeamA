// ----------------------------------------
//
// X�V�[�������̐���[scene_X.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _SCENE_X_H_
#define _SCENE_X_H_	 // �t�@�C������������߂�

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "scene.h"
#include "model_info.h"

// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CScene_X : public CScene
{
public:
	/* �֐� */
	CScene_X();
	CScene_X(ACTOR actor, LAYER layer);
	~CScene_X();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	// ��񋤗L
	void BindTexture(LPDIRECT3DTEXTURE9 p_Tex);		// �e�N�X�`���[�Ɩ���
	void BindModel(MODEL_INFO const &model_info);	// ���f��
	static CScene_X * Create();						// �쐬
	// �ݒ�
	void SetPos(D3DXVECTOR3 pos);					// �ʒu
	void SetRot(D3DXVECTOR3 rot);					// ��]
	void SetSize(D3DXVECTOR3 size);					// �T�C�Y
	void SetColor(D3DXCOLOR col);					// �F
	// �擾
	D3DXVECTOR3 GetPos(void);						// �ʒu
	D3DXVECTOR3 GetRot(void);						// ��]

protected:
private:
	/* �֐� */
	/* �ϐ� */
	MODEL_INFO		m_model_info;	// ���f�����
	D3DXMATRIX		m_mtxWorld;		// ���[���h�}�g���b�N�X
	LPDIRECT3DTEXTURE9	pTexture[3];			// �e�N�X�`���ւ̃|�C���^
	int m_nCount;
};

#endif