//=====================================
//
//�L���[�u�I�u�W�F�N�g�Փ˔��菈��[collisionCubeObject.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "collisionManager.h"
#include "cubeObject.h"
#include "playerBullet.h"

/**************************************
�}�N����`
***************************************/
#define CUBEOBJ_PLAYERBULLET_DAMAGE						(1.0f)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/
bool CheckCollisionCubeObjLower(DWORD elem, PLAYERBULLET *bullet, bool isCheckUpper, COLLISION_MANAGER *manager);
bool CheckCollisionCubeObjUpper(DWORD elem, PLAYERBULLET *bullet, COLLISION_MANAGER *manager);

/**************************************
�Փ˔���
***************************************/
void CheckCollisionCubeObject(COLLISION_MANAGER *manager)
{
	for (DWORD cntCell = 0; cntCell < manager->cellNum; cntCell++)
	{
		//��Ԃ��쐬����Ă��Ȃ��ꍇ�̔���
		if (!manager->cellArray[OFT_PLAYERBULLET][cntCell])
			continue;

		//��ԂɃI�u�W�F�N�g���o�^����Ă��Ȃ��ꍇ�̔���
		if (manager->cellArray[OFT_PLAYERBULLET][cntCell]->latestObj == NULL)
			continue;

		//��Ԃɓo�^����Ă���o���b�g�S�Ăɑ΂��Ĕ���
		OBJECT_FOR_TREE *playerBulletOFT = manager->cellArray[OFT_PLAYERBULLET][cntCell]->latestObj;
		for (; playerBulletOFT != NULL; playerBulletOFT = playerBulletOFT->next)
		{
			PLAYERBULLET *playerBullet = (PLAYERBULLET*)playerBulletOFT->object;
			//�L���[�u�I�u�W�F�N�g�Ƃ̔���
			{
				bool result;
				result = CheckCollisionCubeObjLower(cntCell, playerBullet, false, manager);
				if (result)
					continue;
			}
		}
	}
}

/**************************************
�q��ԂƂ̏Փ˔���
**************************************/
bool CheckCollisionCubeObjLower(DWORD elem, PLAYERBULLET *bullet, bool isCheckedUpper, COLLISION_MANAGER *manager)
{
	//�w�肳�ꂽ��Ԃ��ő��Ԑ��𒴂��Ă��锻��
	if (elem >= manager->cellNum)
		return false;

	//�e��ԂŔ���
	if (!isCheckedUpper)
	{
		bool result;
		result = CheckCollisionCubeObjUpper(elem, bullet, manager);
		if (result)
			return true;
	}

	//��Ԃ��쐬����Ă��Ȃ��ꍇ�̔���
	if (!manager->cellArray[OFT_CUBEOBJECT][elem])
		return false;

	//�w�肳�ꂽ��ԓ��̃L���[�u�I�u�W�F�N�g�ɑ΂��Ĕ���
	if (manager->cellArray[OFT_CUBEOBJECT][elem]->latestObj != NULL)
	{
		OBJECT_FOR_TREE *cubeOFT = manager->cellArray[OFT_CUBEOBJECT][elem]->latestObj;
		while (cubeOFT != NULL)
		{
			//�Փ˔���
			CUBE_OBJECT *cube = (CUBE_OBJECT*)cubeOFT->object;
			//cntCheck++;
			if (ChechHitBoundingCube(&bullet->collider2, &cube->collider))
			{
				cube->hp -= CUBEOBJ_PLAYERBULLET_DAMAGE;
				bullet->destroyRequest = true;
				return true;
			}

			//�o�^����Ă��鎟�̃L���[�u��
			cubeOFT = cubeOFT->next;
		}
	}

	//�q��Ԃł�����
	for (int i = 0; i < 4; i++)
	{
		DWORD nextElem = elem * 4 + 1 + i;
		bool result = CheckCollisionCubeObjLower(nextElem, bullet, true, manager);
		if (!result)
			return true;
	}

	return false;
}

/*************************************
�e��ԂƂ̏Փ˔���
**************************************/
bool CheckCollisionCubeObjUpper(DWORD elem, PLAYERBULLET *bullet, COLLISION_MANAGER *manager)
{
	for (elem = (elem - 1) >> 2; elem < manager->cellNum; elem = (elem - 1) >> 2)
	{
		//��Ԃ��쐬����Ă��Ȃ��ꍇ�̔���
		if (!manager->cellArray[OFT_CUBEOBJECT][elem])
			continue;;

		//�w�肳��ċ�ԓ��̃I�u�W�F�N�g�ɑ΂��Ĕ���
		if (manager->cellArray[OFT_CUBEOBJECT][elem]->latestObj != NULL)
		{
			OBJECT_FOR_TREE *cubeOFT = manager->cellArray[OFT_CUBEOBJECT][elem]->latestObj;
			while (cubeOFT != NULL)
			{
				//�Փ˔���
				CUBE_OBJECT *cube = (CUBE_OBJECT*)cubeOFT->object;
				//cntCheck++;
				if (ChechHitBoundingCube(&bullet->collider2, &cube->collider))
				{
					cube->hp -= CUBEOBJ_PLAYERBULLET_DAMAGE;
					bullet->destroyRequest = true;
					return false;
				}

				//���̃L���[�u��
				cubeOFT = cubeOFT->next;
			}
		}
	}

	return false;
}