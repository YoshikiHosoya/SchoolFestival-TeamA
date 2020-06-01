//------------------------------------------------------------------------------
//
//�f�o�b�O�p�̃L�����N�^  [Debug_OneModelCharacter.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _DEBUG_ONE_MODEL_CHARACTER
#define _DEBUG_ONE_MODEL_CHARACTER
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "../main.h"
#include "../model_object.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class Debug_OneModelCharacter : public CModel_Object
{
public:

	Debug_OneModelCharacter();						//�R���X�g���N�^
	~Debug_OneModelCharacter();						//�f�X�g���N�^

	HRESULT Init();									//������
	void Uninit();									//�I��
	void Update();									//�X�V
	void Draw();									//�`��
	void ShowDebugInfo();							//�f�o�b�O���\�L

	static void Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			//���W
private:
};
#endif