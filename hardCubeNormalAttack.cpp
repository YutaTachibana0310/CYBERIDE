//=====================================
//
//�n�[�h�L���[�u�ʏ�U������[hardCubeNormalAttack.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "hardCubeObject.h"
#include "playerModel.h"
#include "enemyBullet.h"

/**************************************
�}�N����`
***************************************/
#define HARDCUBE_NORMALATTACK_INTERBAL		(60)
#define HARDCUBE_NORMALATTACK_DURATION		(HARDCUBE_NORMALATTACK_INTERBAL*5)
#define HARDCUBE_NORNALATTACL_BULLETSPEED	(10.0f)

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
void OnEnterHardCubeNormalAttack(HARD_CUBE_OBJECT *ptr)
{
	ptr->cntFrame = 0;
}

/**************************************
�X�V����
***************************************/
void OnUpdateHardCubeNormalAttack(HARD_CUBE_OBJECT *ptr)
{
	ptr->cntFrame++;
	if (ptr->cntFrame % HARDCUBE_NORMALATTACK_INTERBAL == 0)
	{
		D3DXVECTOR3 dir = GetPlayerAdr(0)->pos - ptr->pos;
		D3DXVec3Normalize(&dir, &dir);
		SetEnemyBullet(ptr->pos, dir, HARDCUBE_NORNALATTACL_BULLETSPEED);
	}

	if (ptr->cntFrame == HARDCUBE_NORMALATTACK_DURATION)
		ChangeStateHardCube(ptr, HardCubeEscape);
}