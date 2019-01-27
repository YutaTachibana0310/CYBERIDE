//=====================================
//
//�n�[�h�L���[�u�Փ˔��菈��[collisionHardCube.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "collisionManager.h"
#include "playerBullet.h"
#include "hardCubeObject.h"

/**************************************
�}�N����`
***************************************/
#define HARDCUBE_PLAYERBULLET_DAMAGE	(1.0f)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/
bool CheckCollisionHardCubeLower(DWORD elem, HARD_CUBE_OBJECT *hardCube, bool isCheckedUpper, COLLISION_MANAGER *manager);
bool CheckCollisionHardCubeUpper(DWORD elem, HARD_CUBE_OBJECT *hardCube, COLLISION_MANAGER *manager);

/**************************************
�Փ˔���
***************************************/
void CheckCollisionHardCube(COLLISION_MANAGER *manager)
{
	for (DWORD cntCell = 0; cntCell < manager->cellNum; cntCell++)
	{
		//��Ԃ��쐬����Ă��Ȃ��ꍇ�̔���
		if (!manager->cellArray[OFT_HARDCUBE][cntCell])
			continue;

		//��ԂɃI�u�W�F�N�g���o�^����Ă��Ȃ��ꍇ�̔���
		if (manager->cellArray[OFT_HARDCUBE][cntCell]->latestObj == NULL)
			continue;

		//��Ԃɓo�^����Ă���o���b�g�S�Ăɑ΂��Ĕ���
		OBJECT_FOR_TREE *hardCubeOFT = manager->cellArray[OFT_HARDCUBE][cntCell]->latestObj;
		for (; hardCubeOFT != NULL; hardCubeOFT = hardCubeOFT->next)
		{
			HARD_CUBE_OBJECT *hardCube = (HARD_CUBE_OBJECT*)hardCubeOFT->object;
			CheckCollisionHardCubeLower(cntCell, hardCube, false, manager);
		}
	}
}

/**************************************
�q��Ԃł̏Փ˔���
***************************************/
bool CheckCollisionHardCubeLower(DWORD elem, HARD_CUBE_OBJECT *hardCube, bool isCheckedUpper, COLLISION_MANAGER *manager)
{
	//�w�肳�ꂽ��Ԃ��ő��Ԑ��𒴂��Ă��锻��
	if (elem >= manager->cellNum)
		return false;

	//�e��Ԃł̔���
	if (isCheckedUpper)
	{
		bool result;
		result = CheckCollisionHardCubeUpper(elem, hardCube, manager);
		if (result)
			return true;
	}

	//��Ԃ��쐬����Ă��Ȃ��ꍇ�̔���
	if (!manager->cellArray[OFT_PLAYERBULLET][elem])
		return false;

	//�w�肳��ċ�ԓ��̃I�u�W�F�N�g�ɑ΂��Ĕ���
	if (manager->cellArray[OFT_PLAYERBULLET][elem]->latestObj != NULL)
	{
		OBJECT_FOR_TREE *bulletOFT = manager->cellArray[OFT_PLAYERBULLET][elem]->latestObj;
		while (bulletOFT != NULL)
		{
			//�Փ˔���
			PLAYERBULLET *bullet = (PLAYERBULLET*)bulletOFT->object;
			if (ChechHitBoundingCube(&bullet->collider2, &hardCube->collider))
			{
				BurstPlayerBullet(bullet);
				hardCube->hp -= HARDCUBE_PLAYERBULLET_DAMAGE;
			}

			//���̃L���[�u��
			bulletOFT = bulletOFT->next;
		}
	}

	//�q��Ԃł�����
	for (int i = 0; i < 4; i++)
	{
		DWORD nextElem = elem * 4 + 1 + i;
		bool result;
		result = CheckCollisionHardCubeLower(nextElem, hardCube, true, manager);
	}

	return false;
}

/**************************************
�e��Ԃł̏Փ˔���
***************************************/
bool CheckCollisionHardCubeUpper(DWORD elem, HARD_CUBE_OBJECT *hardCube, COLLISION_MANAGER *manager)
{
	//���[�g��ԂɃW�����v����܂Ń��[�v
	for (elem = (elem - 1) >> 2; elem < manager->cellNum; elem = (elem - 1) >> 2)
	{
		//��Ԃ��쐬����Ă��Ȃ��ꍇ�̔���
		if (!manager->cellArray[OFT_PLAYERBULLET][elem])
			continue;

		//�w�肳��ċ�ԓ��̃I�u�W�F�N�g�ɑ΂��Ĕ���
		if (manager->cellArray[OFT_PLAYERBULLET][elem]->latestObj != NULL)
		{
			OBJECT_FOR_TREE *bulletOFT = manager->cellArray[OFT_PLAYERBULLET][elem]->latestObj;
			while (bulletOFT != NULL)
			{
				//�Փ˔���
				PLAYERBULLET *bullet = (PLAYERBULLET*)bulletOFT->object;
				if (ChechHitBoundingCube(&bullet->collider2, &hardCube->collider))
				{
					BurstPlayerBullet(bullet);
					hardCube->hp -= HARDCUBE_PLAYERBULLET_DAMAGE;
					return true;
				}

				//���̃L���[�u��
				bulletOFT = bulletOFT->next;
			}
		}
	}

	return false;
}