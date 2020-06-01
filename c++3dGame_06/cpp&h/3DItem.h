// ----------------------------------------
//
// 3DItem�����̐���[3DItem.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _3DITEM_H_
#define _3DITEM_H_	 // �t�@�C������������߂�

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "scene_X.h"

// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------

//=============================================================================
// �O���錾
//=============================================================================

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class C3DItem : public CScene_X
{
public:
	/* �񋓌^ */
	// �^�C�v
	typedef enum
	{
		TYPE_SHARD = 0,	// �N���A����
		TYPE_MAX
	} TYPE;

	/* �֐� */
	C3DItem();
	C3DItem(ACTOR actor, LAYER layer);
	~C3DItem();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos);					// �ʒu�ݒ�
	void SetRot(D3DXVECTOR3 rot);					// ��]�ݒ�
	D3DXVECTOR3 GetPos(void);						// �ʒu�擾
	static int GetShardNum(void);					// ���Ђ̑���
	bool ShardFlag(void);							// ���Ђ��S�ĂȂ��Ȃ������̔���

	static void Except3DItem(void);					// 3D�A�C�e���̑��������炷
	static C3DItem * Create(void);					// �쐬
	static void C3DItem::LoadCreate(void);			// �ǂݍ��񂾂��̂𐶐�
	static HRESULT Load(void);						// �ǂݍ���
	static void UnLoad(void);						// �j��

protected:
private:
	typedef struct
	{
		// �A�C�e����Id
		int nId;
	} ItemID;



	static LPDIRECT3DTEXTURE9 m_pTexture[1];		// �e�N�X�`���ւ̃|�C���^
	static CLoad		*m_pload;					// ���[�h
	static CModel_info	*m_pmodel_info;				// ���f�����
	static int			m_nAll;						// ����
	TYPE				m_Type;						// �^�C�v
	D3DXMATRIX			m_mtxWorld;					// �s��
	bool				m_bShard;					// ���Ђ̐���0�ȉ��ɂȂ�����true
	static int			m_nShardNum;				// ���Ђ̑���
	//int					m_nId;						// �A�C�e�������ʂ���ԍ�
	ItemID				m_ID;
};

#endif
