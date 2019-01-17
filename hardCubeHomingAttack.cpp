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
#define HARDCUBE_HOMINGATTACK_INTERBAL		(120)
#define HARDCUBE_HOMINGATTACK_DURATION		(HARDCUBE_HOMINGATTACK_INTERBAL*4)
#define HARDCUBE_HOMINGATTACK_DIRNUM		(4)
#define HARDCUBE_HOMINGATTACK_REACHFRAME	(60)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static const D3DXVECTOR3 bulletVelocity[HARDCUBE_HOMINGATTACK_DIRNUM] = {
	/*			dir			*		speed	*/
	D3DXVECTOR3(1.0f, 1.0f, 0.0f) * 50,
	D3DXVECTOR3(-1.0f, 1.0f, 0.0f) * 50,
	D3DXVECTOR3(1.0f, -1.0f, 0.0f) * 50,
	D3DXVECTOR3(-1.0f, -1.0f, 0.0f) * 50,
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
	ptr->cntFrame++;
	if (ptr->cntFrame % HARDCUBE_HOMINGATTACK_INTERBAL == 0)
	{
		for (int i = 0; i < HARDCUBE_HOMINGATTACK_DIRNUM; i++)
		{
			SetEnemyHomingBullet(ptr->pos, bulletVelocity[i], HARDCUBE_HOMINGATTACK_REACHFRAME);
		}
	}

	if (ptr->cntFrame == HARDCUBE_HOMINGATTACK_DURATION)
		ChangeStateHardCube(ptr, HardCubeEscape);
}