//=====================================
//
//�n�[�h�L���[�u������ԏ���[hardCubeInit.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "hardCubeObject.h"

/**************************************
�}�N����`
***************************************/
#define HARDCUBE_SCALE_MAX			(2.0f)
#define HARDCUBE_SCALE_MIN			(0.2f)
#define HARDCUBE_INIT_HP			(10.0f)						//����HP

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static const float InitHp[HardCubeTypeMax] = {
	50.0f, 100.0f, 15.0f, 30.0f, 50.0f
};

static const float InitScale[HardCubeTypeMax] = {
	1.2f, 1.7f, 0.7f, 0.4f, 1.2f
};

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
���ꏈ��
***************************************/
void OnEnterHardCubeInit(HARD_CUBE_OBJECT *ptr)
{
	/* �X�P�[���̎��������͈�U�}�X�N���A�X�e�[�W�f�[�^�ɍ��킹�ăX�P�[���ݒ� */
	//ptr->scale = RandomRangef(HARDCUBE_SCALE_MIN, HARDCUBE_SCALE_MAX);
	ptr->scale = InitScale[ptr->type];
	ptr->hp = InitHp[ptr->type];

	if (ptr->type != HardCubeBezierType)
		ChangeStateHardCube(ptr, HardCubeMove);
	else
		ChangeStateHardCube(ptr, HardCubeBezier);
}

/**************************************
�X�V����
***************************************/
void OnUpdateHardCubeInit(HARD_CUBE_OBJECT *ptr)
{

}