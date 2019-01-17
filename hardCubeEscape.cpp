//=====================================
//
//�n�[�h�L���[�u������ԏ���[hardCubeEscape.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "hardCubeObject.h"
#include "Easing.h"

/**************************************
�}�N����`
***************************************/
#define HARDCUBE_ESCAPE_DURATION		(180)
#define HARDCUBE_ESCAPE_SPEED_MAX		(20.0f)
#define HARDCUBE_ESCAPE_Z_END			(10000.0f)

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
void OnEnterHardCubeEscape(HARD_CUBE_OBJECT *ptr)
{
	ptr->cntFrame = 0;
	ptr->moveSpeed = 0;
}

/**************************************
�X�V����
***************************************/
void OnUpdateHardCubeEscape(HARD_CUBE_OBJECT *ptr)
{
	ptr->cntFrame++;
	float t = (float)ptr->cntFrame / HARDCUBE_ESCAPE_DURATION;
	ptr->moveSpeed = EaseInCubic(t, 0.0f, HARDCUBE_ESCAPE_SPEED_MAX);

	ptr->pos.z += ptr->moveSpeed;

	if (ptr->pos.z > HARDCUBE_ESCAPE_Z_END)
		DisableHardCube(ptr);
}