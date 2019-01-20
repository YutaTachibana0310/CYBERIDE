//=====================================
//
//�n�[�h�L���[�u�x�W�F����[hardCubeBezier.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "hardCubeObject.h"

/**************************************
�}�N����`
***************************************/
#define HARDCUBE_BEZIER_DURATION		(300)

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
void OnEnterHardCubeBezier(HARD_CUBE_OBJECT *ptr)
{
	ptr->cntFrame = 0;
	ptr->scale = 0.5f;
	ptr->startPos = ptr->pos;
}

/**************************************
�X�V����
***************************************/
void OnUpdateHardCubeBezier(HARD_CUBE_OBJECT *ptr)
{
	ptr->cntFrame++;
	float t = (float)ptr->cntFrame / (float)HARDCUBE_BEZIER_DURATION;

	//�ړ���̍��W��3���x�W�F�Ȑ��ɂ�苁�߂�
	ptr->pos =
		powf(1 - t, 3) * ptr->startPos
		+ 3 * powf(1 - t, 2) * t * ptr->controller1
		+ 3 * (1 - t) * t * t * ptr->controller2
		+ t * t * t * ptr->goalPos;

	if (ptr->cntFrame == HARDCUBE_BEZIER_DURATION)
	{
		DisableHardCube(ptr);
	}
}