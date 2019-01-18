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

#define HARDCUBE_SCALE_HOMING		(1.5f)
#define HARDCUBE_SCALE_CHARGE		(0.7f)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

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
	switch (ptr->type)
	{
	case HardCubeNormalType:
		ptr->scale = RandomRangef(HARDCUBE_SCALE_CHARGE, HARDCUBE_SCALE_HOMING);
		break;

	case HardCubeHomingType:
		ptr->scale = RandomRangef(HARDCUBE_SCALE_HOMING, HARDCUBE_SCALE_MAX);
		break;

	default:
		ptr->scale = RandomRangef(HARDCUBE_SCALE_MIN, HARDCUBE_SCALE_CHARGE);
	}

	ptr->hp = HARDCUBE_INIT_HP * ptr->scale;
	ChangeStateHardCube(ptr, HardCubeMove);
}

/**************************************
�X�V����
***************************************/
void OnUpdateHardCubeInit(HARD_CUBE_OBJECT *ptr)
{

}