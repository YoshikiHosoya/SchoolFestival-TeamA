//*************************************************************************************************************
//
// 3D�G�t�F�N�g�̏���[effect.h]
// Author : Fujiwara Masato
//
//*************************************************************************************************************
#ifndef _3DEFFECT_H_
#define _3DEFFECT_H_

//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"

//-------------------------------------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------------------------------------
#define EFFECT_MAX			(10000)						// �ő吔
#define EFFECT_NUM_VERTEX	(4)							// ���_��

//-------------------------------------------------------------------------------------------------------------
// �N���X��`
//-------------------------------------------------------------------------------------------------------------
class CRenderer;
class C3DEffect : public CScene
{
public:
	typedef enum
	{
		EFFECT_TYPE_NONE = -1,	// �Ȃ�
		EFFECT_TYPE_EXPLOSION,	// ����
		EFFECT_TYPE_SPARK,		// �Ή�
		EFFECT_TYPE_SMOKE,		// ��
		EFFECT_TYPE_MAX			// �ő吔
	} EFFECT_TYPE;

	typedef struct
	{
		D3DXVECTOR3		pos;			// �ʒu
		D3DXVECTOR3		rot;			// ��]��
		D3DXVECTOR3		move;			// �ړ���
		D3DXCOLOR		col;			// �F
		D3DXMATRIX		mtxWorld;		// ���[���h�}�g���b�N�X
		D3DXMATRIX		mtxView;		// �}�g���b�N�X�r���[
		float			fRadius;		// ���a
		float			fAngle;			// �p�x
		float			fRadiusValue;	// ���a�̕ω��l
		float			fAlphaValue;	// �A���t�@�l�̕ω��l
		int				nLife;			// ��������
		int				nTexType;		// �e�N�X�`���̎��
		bool			bUse;			// �g�p���Ă��邩�ǂ���
		EFFECT_TYPE		EffectType;		// �G�t�F�N�g�̎��
	} EFFECT;

	typedef struct
	{
		char string[64];
	} FILETAG, *PFILETAG;

	typedef struct
	{
		LPDIRECT3DTEXTURE9 pTexture;	// �e�N�X�`�����
	} TEXTURE_INFO;

	C3DEffect();
	~C3DEffect();
	static HRESULT Load(void);
	static void Unload(void);
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void InitValues(void);
	HRESULT MakeVertex(LPDIRECT3DDEVICE9 pDevice);
	static void SetVartexSize(VERTEX_3D *pVtx,EFFECT *pEffect = NULL, const int *nIndex = NULL);
	static void SetVetexColor(VERTEX_3D *pVtx,EFFECT *pEffect = NULL, const int *nIndex = NULL);
	static C3DEffect *Create(void);
	void Delete(int nCntIndex);
	static void Set3DEffect(
		EFFECT_TYPE EffectType, int nTexType,
		D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col,
		float fRadius, int nLife, float fRadiusValue = 0.0f);
private:
	/* -- �����o�֐� -- */
	static int LoadNumber(const char *TextFile, const char  * SetItem);
	static void LoadPass(const char * sFileName, PFILETAG sFilePass, const char * ItemName);
	static void LoadTextureFile(const char * sFileName, PFILETAG TexName, const int &nNumMax);
	static bool Existenceofscript(FILE *pFile);
	bool UpdateLife(VERTEX_3D *pVtx, EFFECT *pEffect);
	bool UpdateVetex(VERTEX_3D *pVtx, EFFECT *pEffect);
	void UpdateMove(VERTEX_3D *pVtx, EFFECT *pEffect);
	/* -- �����o�ϐ� -- */
	static LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;					// �o�b�t�@���
	static TEXTURE_INFO				*m_pTexInfo;				// �e�N�X�`�����
	static EFFECT					m_aEffect[EFFECT_MAX];		// �G�t�F�N�g���
	static const float				m_cfBaseAngle;				// ��{�p�x
	static int						m_nNumTextureMax;			// �e�N�X�`���̍ő吔
};

#endif