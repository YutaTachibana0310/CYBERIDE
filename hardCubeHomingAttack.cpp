//=====================================
//
//�n�[�h�L���[�u�z�[�~���O�U������[hardCubeHomingAttack.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "hardCubeObject.h"
#include "enemyHomingBullet.h"

/**************************************
�}�N����`
***************************************/
#define HARDCUBE_HOMINGATTACK_INTERBAL		(180)
#define HARDCUBE_HOMINGATTACK_DURATION		(HARDCUBE_HOMINGATTACK_INTERBAL*5)
#define HARDCUBE_HOMINGATTACK_DIRNUM		(4)
#define HARDCUBE_HOMINGATTACK_REACHFRAME	(100)
#define HARDCUBE_HOMINGATTACK_SPEED			(150.0f)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static const D3DXVECTOR3 bulletVelocity[HARDCUBE_HOMINGATTACK_DIRNUM] = {
	/*			dir			*		speed	*/
	D3DXVECTOR3(1.0f, 1.0f, 0.0f) * HARDCUBE_HOMINGATTACK_SPEED,
	D3DXVECTOR3(-1.0f, 1.0f, 0.0f) * HARDCUBE_HOMINGATTACK_SPEED,
	D3DXVECTOR3(1.0f, -1.0f, 0.0f) * HARDCUBE_HOMINGATTACK_SPEED,
	D3DXVECTOR3(-1.0f, -1.0f, 0.0f) * HARDCUBE_HOMINGATTACK_SPEED,
};
/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
���ꏈ��
***************************************/
void OnEnterHardCubeHomingAttack(HARD_CUBE_OBJECT *ptr)
{
	ptr->cntFrame = 0;
}

/**************************************
�X�V����
***************************************/
void OnUpdateHardCubeHomingAttack(HARD_CUBE_OBJECT *ptr)
{
	if (ptr->cntFrame % HARDCUBE_HOMINGATTACK_INTERBAL == 0)
	{
		for (int i = 0; i < HARDCUBE_HOMINGATTACK_DIRNUM; i++)
		{
			SetEnemyHomingBullet(ptr->pos, bulletVelocity[i], HARDCUBE_HOMINGATTACK_REACHFRAME);
		}
	}
	ptr->cntFrame++;

	if (ptr->cntFrame == HARDCUBE_HOMINGATTACK_DURATION)
		ChangeStateHardCube(ptr, HardCubeEscape);
}