//=====================================
//
//�~�h���G�l�~�[���f������[middleEnemyModel.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "middleEnemyModel.h"

/**************************************
�}�N����`
***************************************/
#define MIDDLEENMY_MODEL_NAME		"data/MODEL/MiddileEnemy.x"

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static LPD3DXMESH mesh = NULL;
static LPD3DXBUFFER materials = NULL;
static DWORD numMaterial = 0;
static MIDDLEENMYMODEL middleEnemy[MIDDLEENEMY_MAX];

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitMiddleEnemyModel(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (num == 0)
	{
		D3DXLoadMeshFromX(MIDDLEENMY_MODEL_NAME, D3DXMESH_SYSTEMMEM, pDevice, NULL, &materials, NULL, &numMaterial, &mesh);
	}

	MIDDLEENMYMODEL *ptr = &middleEnemy[0];
	for (int i = 0; i < MIDDLEENEMY_MAX; i++, ptr++)
	{
	

	}
}

/**************************************
�I������
***************************************/
void UninitMiddleEnemyModel(int num)
{

}

/**************************************
�X�V����
***************************************/
void UpdateMiddleEnemyModel(void)
{

}

/**************************************
�`�揈��
***************************************/
void DrawMiddleEnemyModel(void)
{

}
