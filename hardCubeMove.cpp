//=====================================
//
//�n�[�h�L���[�u�ړ���ԏ���[hardCubeMove.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "hardCubeObject.h"
#include "EasingVector.h"

/**************************************
�}�N����`
***************************************/
#define HARDCUBE_MOVE_Z_NEAR			(300.0f)
#define HARDCUBE_MOVE_Z_FAR				(600.0f)

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
void OnEnterHardCubeMove(HARD_CUBE_OBJECT *ptr)
{
	ptr->startPos = ptr->pos;
	ptr->goalPos = ptr->startPos + D3DXVECTOR3(0.0f, 0.0f, RandomRangef(HARDCUBE_MOVE_Z_NEAR, HARDCUBE_MOVE_Z_FAR));
	ptr->cntFrame = 0;
	ptr->moveDurtaion = 120;
}

/**************************************
�X�V����
***************************************/
void OnUpdateHardCubeMove(HARD_CUBE_OBJECT *ptr)
{
	ptr->cntFrame++;
	float t = (float)ptr->cntFrame / (float)ptr->moveDurtaion;
	ptr->pos = EaseOutCubicVector(t, ptr->startPos, ptr->goalPos);

	if (ptr->cntFrame == ptr->moveDurtaion)
	{
		int next = (ptr->scale > 1.0f) ? HardCubeHomingAttack : (ptr->scale > 1.0f) ? HardCubeNormalAttack : HardCubeCharge;
		ChangeStateHardCube(ptr, next);
	}
}