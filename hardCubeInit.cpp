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
#define HARDCUBE_SCALE_MIN			(0.5f)
#define HARDCUBE_INIT_HP			(10.0f)						//����HP

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
	ptr->scale = RandomRangef(HARDCUBE_SCALE_MIN, HARDCUBE_SCALE_MAX);
	ptr->hp = HARDCUBE_INIT_HP * ptr->scale;
	ChangeStateHardCube(ptr, HardCubeMove);
}

/**************************************
�X�V����
***************************************/
void OnUpdateHardCubeInit(HARD_CUBE_OBJECT *ptr)
{

}