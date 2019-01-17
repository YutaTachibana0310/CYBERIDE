//=====================================
//
//�n�[�h�L���[�u�ːi����[hardCubeCharge.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "hardCubeObject.h"
#include "playerModel.h"
#include "Easing.h"

/**************************************
�}�N����`
***************************************/
#define HARDCUBE_CHARGE_DURATION		(60)
#define HARDCUBE_CHARGE_SPEED			(10.0f)

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
void OnEnterHardCubeCharge(HARD_CUBE_OBJECT *ptr)
{
	ptr->cntFrame = 0;
	ptr->moveSpeed = 0;
	ptr->moveDir = GetPlayerAdr(0)->pos - ptr->pos;
	D3DXVec3Normalize(&ptr->moveDir, &ptr->moveDir);
}

/**************************************
�X�V����
***************************************/
void OnUpdateHardCubeCharge(HARD_CUBE_OBJECT *ptr)
{
	ptr->cntFrame++;
	float t = (float)ptr->cntFrame / (float)HARDCUBE_CHARGE_DURATION;
	ptr->moveSpeed = EaseInCubic(t, 0.0f, HARDCUBE_CHARGE_SPEED);
	ptr->pos += ptr->moveDir * ptr->moveSpeed;
}