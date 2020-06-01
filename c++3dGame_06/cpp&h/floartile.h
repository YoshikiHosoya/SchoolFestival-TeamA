// ----------------------------------------
//
// �^�C���������̐���[floartile.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _FLOARTILE_H_
#define _FLOARTILE_H_	 // �t�@�C������������߂�

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
#define MAX_TILENUMBER (713)		// �S�Ẵ}�X�̑���
#define MAX_WALKTILENUMBER (228)	// �i�s�ł���^�C���̑���
#define MAX_VERTICALNUM (31)		// �^�C���̏c�̐�-2
#define MAX_HORIZONTALNUM (23)		// �^�C���̉��̐�-2

//=============================================================================
// �O���錾
//=============================================================================
class CEnemy;
// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CFloarTile : public CScene_X
{
public:
	/* �񋓌^ */
	// �^�C���̎��
	typedef enum
	{
		TILE_TYPE_WALL = 0,		// ���s�s�\�}�X
		TILE_TYPE_TILE_NOR,		// ���s�\�Ȓʏ�}�X
		TILE_TYPE_TILE_SP,		// �G�Ɣ������邽�߂̃}�X
		TILE_TYPE_MAX			// �^�C���̎�ނ̑���
	} TILE_TYPE;

	// ����
	typedef enum
	{
		DIRECTION_FORWARD = 0,	// �O��
		DIRECTION_BACKWARD,		// ���
		DIRECTION_LEFT,			// ��
		DIRECTION_RIGHT,		// �E
		DIRECTION_ALL			// �S����
	} DIRECTION;


	/* �֐� */
	CFloarTile();
	~CFloarTile();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos);									// �ʒu�ݒ�
	void SetRot(D3DXVECTOR3 rot);									// ��]�ݒ�
	D3DXVECTOR3 GetPos(void);										// �ʒu�擾

	static CFloarTile * Create(void);								// �쐬
	static void CFloarTile::LoadCreate(void);						// �ǂݍ��񂾂��̂𐶐�

	void PlayerJudg();												// ����
	void EnemyJudg();												// ����
	void EnemyAi();													// �G�̐i�s�����߂�v�Z
	static HRESULT Load(void);										// �ǂݍ���
	static void UnLoad(void);										// �j��
	static HRESULT LoadTileNum(const char * filename);				// �ǂݍ���

protected:
private:
	static LPDIRECT3DTEXTURE9	m_pTexture;							// �e�N�X�`���ւ̃|�C���^
	static CLoad				*m_pload;							// ���[�h
	static CModel_info			*m_pmodel_info;						// ���f�����
	static CFloarTile			*m_paFloarTile[MAX_WALKTILENUMBER]; // ���s�\�^�C���p�ϐ�
	static int					m_aTileType[MAX_TILENUMBER];		// �^�C���̎��
	static int					m_aTileNum[MAX_TILENUMBER];			// �^�C���̐�
	static int					m_nPlayerSavepos;					// �v���C���[�����񂾃}�X��ۑ�

	TILE_TYPE					m_type;								// �^�C���̎��
	DIRECTION					m_Dire;								// �i�s����
	CEnemy					    *m_pEnemy;							// �G�l�~�[�̃|�C���^
	CFloarTile					*m_pFloarTile;						// �^�C���̃|�C���^
	int							m_nEnemySavepos;					// �G�l�~�[�[�����񂾃}�X��ۑ�
	int							m_nTileNum;							// �^�C����myNumber
	int							m_nSaveArrayNumber;					// �z��̔ԍ���ۑ�
	int							m_nDirection;						// ����
	bool						m_bLand_Enemy;						// �G���}�X�𓥂�ł��邩�ǂ���
	bool						m_bFlag[4];							// �G���i�s�ł��邩�̃t���O
	int							m_nDirEnemyBackward;
};

#endif