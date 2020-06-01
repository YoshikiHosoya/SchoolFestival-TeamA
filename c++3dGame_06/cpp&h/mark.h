// ----------------------------------------
//
// �ڈ󏈗��̐���[mark.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _MARK_H_
#define _MARK_H_	 // �t�@�C������������߂�

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
#define MAX_MARK (2)

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CMark : public CScene
{
public:
	/* �֐� */
	CMark();
	CMark(CScene::ACTOR actor);
	~CMark();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR2 size);			// �ʒu�E�T�C�Y�ݒ�
	void SetPosGoal(D3DXVECTOR3 pos, D3DXVECTOR2 size);		// �ڕW�̈ʒu�E�T�C�Y�ݒ�
	D3DXVECTOR3 GetPos(void);								// �ʒu���擾
	D3DXVECTOR2 GetSize(void);								// �T�C�Y���擾
	static HRESULT Load(void);
	static void UnLoad(void);
	static CMark * Create(D3DXVECTOR3 pos,D3DXVECTOR2 size,CScene::ACTOR actor);	// �쐬
protected:

private:
	/* �֐� */
	void Animation(int nCnt);				// �A�j���[�V�����Ǘ�

	/* �ϐ� */
	static LPDIRECT3DTEXTURE9 m_pTex[MAX_MARK];
	D3DXVECTOR3 m_pos = {};			// �ʒu���
	D3DXVECTOR3 m_posGoal = {};		// �ڕW�̈ʒu���
	D3DXVECTOR2 m_size = {};			// �T�C�Y���
	D3DXVECTOR2 m_sizeGoal = {};		// �ڕW�̃T�C�Y���
	int m_nHorizonAnim[MAX_MARK];		// �����̃A�j���[�V�����p�^�[��
	int m_nVirticalAnim[MAX_MARK];		// �����̃A�j���[�V�����p�^�[��
	int m_nCntAnim[MAX_MARK];			// �A�j���[�V�����J�E���g
	CScene_TWO *m_aScene_Two[MAX_MARK];
};

#endif