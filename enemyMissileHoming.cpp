//==================================
//
//�G�l�~�[�~�T�C�����ˏ���[enemyMissileHoming.cpp]
//Author:GP11A341 21 ���ԗY��
//
//==================================
#include "enemyMissileHoming.h"

/***********************************
�}�N����`
***********************************/
#define ENEMYMISSILE_HOMINGANGLE	(1.0f)			//�z�[�~���O�̉�]�p�x
#define ENEMYMISSILE_FORWORD		(D3DXVECTOR3(0.0f, 0.0f, -1.0f))	//��ƂȂ�i�s����

/***********************************
�J�n����
************************************/
void EnemyMissileHomingEnter(ENEMYMISSILE *ptr)
{

}

/***********************************
�X�V����
************************************/
void EnemyMissileHomingUpdate(ENEMYMISSILE *ptr)
{
	//�ړ������̃z�[�~���O
	D3DXVECTOR3 axis;
	D3DXVECTOR3 targetDir = ptr->targetPos - ptr->pos;
	D3DXVec3Cross(&axis, &ptr->moveDir, &targetDir);
	RotateByQuaternion(&ptr->moveDir, &axis, ENEMYMISSILE_HOMINGANGLE , &ptr->moveDir);

	//��]�N�H�[�^�j�I����ݒ�
	D3DXVec3Cross(&axis, &ENEMYMISSILE_FORWORD, &ptr->moveDir);
	D3DXQuaternionRotationAxis(&ptr->rot, &axis, acosf(D3DXVec3Dot(&ptr->moveDir, &ENEMYMISSILE_FORWORD)));

	//���W�̍X�V
	ptr->pos += ptr->moveDir * ptr->speed;

	//�J��
	if (GetAngleFromTwoVector(&targetDir, &ptr->moveDir) <= 0.0f)
	{
		ChangeStateEnemyMissile(ptr, ENEMYMISSILE_STRAIGHT);
	}
}

/***********************************
�I������
************************************/
void EnemyMissileHomingExit(ENEMYMISSILE *ptr)
{

}