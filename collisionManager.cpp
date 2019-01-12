//=====================================
//
//�e���v���[�g����[collisionManager.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "collisionManager.h"
#include "collider.h"

#include "playerBullet.h"
#include "cubeObject.h"
#include "hardCubeObject.h"
#include "bonusCube.h"

#include "debugWindow.h"

/**************************************
�}�N����`
***************************************/
#define COLLISION_DIVISIONSPACE_LEVEL_MAX		(6)			//��ԃ��x���̍ő僌�x��
#define COLLISION_REGION_LEFT					(-500.0f)	//�����Ԃ̍��[
#define COLLISION_REGION_RIGHT					(500.0f)	//�����Ԃ̉E�[
#define COLLISION_REGION_TOP					(-5000.0f)	//�����Ԃ̏�[
#define COLLISION_REGION_BOTTOM					(5000.0f)	//�����Ԃ̉��[

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static unsigned int spaceNum[COLLISION_DIVISIONSPACE_LEVEL_MAX + 1];	//�e���x���̋�Ԑ�
static DWORD cellNum;					//��Ԑ��̑��a
static CCell **cellArray[OFT_ID_MAX];	//�e�I�u�W�F�N�g���o�^������Ԃ̔z��

//�P�ʋ�Ԃ̕�
static const float UnitWidth = (COLLISION_REGION_RIGHT - COLLISION_REGION_LEFT) / (1 << COLLISION_DIVISIONSPACE_LEVEL_MAX);

//�P�ʋ�Ԃ̍���
static const float UnitHeight = (COLLISION_REGION_BOTTOM - COLLISION_REGION_TOP) / (1 << COLLISION_DIVISIONSPACE_LEVEL_MAX);

static DWORD cntCheck = 0;

/**************************************
�v���g�^�C�v�錾
***************************************/
bool PushObjectToList(CCell *space, OBJECT_FOR_TREE *obj);					//���X�g�ւ̃I�u�W�F�N�g�o�^����
bool OnObjectRemoveFromList(CCell *space, OBJECT_FOR_TREE *obj);			//��Ԃւ̃I�u�W�F�N�g���E�ʒm����
bool CreateNewCell(DWORD elem, OFT_ID OFTid);								//��ԍ쐬����
DWORD GetMortonNumber(float left, float top, float right, float bottom);	//��Ԕԍ��Z�o����
DWORD BitSeparate32(DWORD n);												//�r�b�g��������
WORD Get2DMortonNumber(WORD x, WORD y);										//2D���[�g���ԍ��Z�o����
DWORD GetPointElem(float posX, float posY);									//���W�����`4���ؗv�f�ԍ��ϊ�����

void CheckCollisionPlayerBullet(void);												//�v���C���[�o���b�g�̏Փ˔���
bool CheckCollisionPlayerBulletAndCubeLower(DWORD elem, PLAYERBULLET *bullet, bool isCheckedUpper);		//�v���C���[�o���b�g�ƃL���[�u�̔���(�e���Ver)
bool CheckCollisionPlayerBulletAndCubeUpper(DWORD elem, PLAYERBULLET *bullet);		//�v���C���[�o���b�g�ƃL���[�u�̔���(�q���Ver)

void CheckCollisionHardCube(void);															//�n�[�h�L���[�u�̏Փ˔���
bool CheckCollisionPlayerBulletAndHardCubeLower(DWORD elem, HARD_CUBE_OBJECT *hardCube, bool isCheckedUpper);	//�v���C���[�o���b�g�ƃn�[�h�L���[�u�̔���(�e���Ver)
bool CheckCollisionPlayerBulletAndHardCubeUpper(DWORD elem, HARD_CUBE_OBJECT *hardCube);	//�v���C���[�o���b�g�ƃn�[�h�L���[�u�̔���(�q���Ver)

bool CheckCollisionBonusCube(void);
bool CheckCollisionBonusCubeAndPlayerBulletLower(DWORD elem, BONUS_CUBE_OBJECT *bonusCube, bool isCheckedUpper);
bool CheckCollisionBonusCubeAndPlayerBulletUpper(DWORD elem, BONUS_CUBE_OBJECT *bonusCube);

/**************************************
����������
***************************************/
void InitCollisionManager(int num)
{
	//�e���x���̋�Ԑ����Z�o
	spaceNum[0] = 1;
	for (int i = 1; i < COLLISION_DIVISIONSPACE_LEVEL_MAX + 1; i++)
	{
		spaceNum[i] = spaceNum[i - 1] * 4;
	}

	//��Ԕz��̃��������m��
	cellNum = (spaceNum[COLLISION_DIVISIONSPACE_LEVEL_MAX] * 4 - 1) / 3;
	for (int OFTid = 0; OFTid < OFT_ID_MAX; OFTid++)
	{
		cellArray[OFTid] = (CCell**)malloc(sizeof(CCell*) * cellNum);
		ZeroMemory(cellArray[OFTid], sizeof(CCell*) * cellNum);
	}
}

/**************************************
�I������
***************************************/
void UninitCollisionManager(int num)
{
	for (int OFTid = 0; OFTid < OFT_ID_MAX; OFTid++)
	{
		free(cellArray[OFTid]);
		cellArray[OFTid] = NULL;
	}
}

/**************************************
�X�V����
***************************************/
void UpdateCollisionManager(void)
{
	static DWORD cnt = 0, cntFrame = 0;

	CheckCollisionPlayerBullet();
	CheckCollisionHardCube();
	CheckCollisionBonusCube();
	
	ImGui::Begin("CollisionManager");
	ImGui::Text("CheckCount : %d", cnt);

	ImGui::End();

	if (++cntFrame % 20 == 0)
		cnt = cntCheck;
	cntCheck = 0;
}

/**************************************
�v���C���[�o���b�g�̏Փ˔���
***************************************/
void CheckCollisionPlayerBullet(void)
{
	for (DWORD cntCell = 0; cntCell < cellNum; cntCell++)
	{
		//��Ԃ��쐬����Ă��Ȃ��ꍇ�̔���
		if (!cellArray[OFT_PLAYERBULLET][cntCell])
			continue;

		//��ԂɃI�u�W�F�N�g���o�^����Ă��Ȃ��ꍇ�̔���
		if (cellArray[OFT_PLAYERBULLET][cntCell]->latestObj == NULL)
			continue;

		//��Ԃɓo�^����Ă���o���b�g�S�Ăɑ΂��Ĕ���
		OBJECT_FOR_TREE *playerBulletOFT = cellArray[OFT_PLAYERBULLET][cntCell]->latestObj;
		for( ; playerBulletOFT != NULL; playerBulletOFT = playerBulletOFT->next)
		{
			PLAYERBULLET *playerBullet = (PLAYERBULLET*)playerBulletOFT->object;
			//�L���[�u�I�u�W�F�N�g�Ƃ̔���
			{
				bool result;
				result = CheckCollisionPlayerBulletAndCubeLower(cntCell, playerBullet,false);
				if (result)
					continue;
			}
		}
	}
}

/**************************************
�v���C���[�o���b�g�ƃL���[�u�I�u�W�F�N�g�̏Փ˔���
***************************************/
bool CheckCollisionPlayerBulletAndCubeLower(DWORD elem, PLAYERBULLET *bullet, bool isCheckedUpper)
{
	//�w�肳�ꂽ��Ԃ��ő��Ԑ��𒴂��Ă��锻��
	if (elem >= cellNum)
		return false;

	//�e��ԂŔ���
	if(!isCheckedUpper)
	{
		bool result;
		result = CheckCollisionPlayerBulletAndCubeUpper(elem, bullet);
		if (result)
			return true;
	}

	//��Ԃ��쐬����Ă��Ȃ��ꍇ�̔���
	if (!cellArray[OFT_CUBEOBJECT][elem])
		return false;

	//�w�肳�ꂽ��ԓ��̃L���[�u�I�u�W�F�N�g�ɑ΂��Ĕ���
	if (cellArray[OFT_CUBEOBJECT][elem]->latestObj != NULL)
	{
		OBJECT_FOR_TREE *cubeOFT = cellArray[OFT_CUBEOBJECT][elem]->latestObj;
		while (cubeOFT != NULL)
		{
			//�Փ˔���
			CUBE_OBJECT *cube = (CUBE_OBJECT*)cubeOFT->object;
			cntCheck++;
			if (ChechHitBoundingCube(&bullet->collider2, &cube->collider))
			{
				cube->hp -= 1.0f;
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
		bool result = CheckCollisionPlayerBulletAndCubeLower(nextElem, bullet, true);
		if (!result)
			return true;
	}

	return false;
}

/**************************************
�v���C���[�o���b�g�ƃL���[�u�I�u�W�F�N�g�̏Փ˔���
***************************************/
bool CheckCollisionPlayerBulletAndCubeUpper(DWORD elem, PLAYERBULLET *bullet)
{
	for(elem = (elem - 1) >> 2; elem < cellNum; elem = (elem - 1) >> 2)
	{
		//��Ԃ��쐬����Ă��Ȃ��ꍇ�̔���
		if (!cellArray[OFT_CUBEOBJECT][elem])
			continue;;

		//�w�肳��ċ�ԓ��̃I�u�W�F�N�g�ɑ΂��Ĕ���
		if (cellArray[OFT_CUBEOBJECT][elem]->latestObj != NULL)
		{
			OBJECT_FOR_TREE *cubeOFT = cellArray[OFT_CUBEOBJECT][elem]->latestObj;
			while (cubeOFT != NULL)
			{
				//�Փ˔���
				CUBE_OBJECT *cube = (CUBE_OBJECT*)cubeOFT->object;
				cntCheck++;
				if (ChechHitBoundingCube(&bullet->collider2, &cube->collider))
				{
					cube->hp -= 1.0f;
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

/**************************************
�n�[�h�L���[�u�̏Փ˔���
***************************************/
void CheckCollisionHardCube(void)
{
	for (DWORD cntCell = 0; cntCell < cellNum; cntCell++)
	{
		//��Ԃ��쐬����Ă��Ȃ��ꍇ�̔���
		if (!cellArray[OFT_HARDCUBE][cntCell])
			continue;

		//��ԂɃI�u�W�F�N�g���o�^����Ă��Ȃ��ꍇ�̔���
		if (cellArray[OFT_HARDCUBE][cntCell]->latestObj == NULL)
			continue;

		//��Ԃɓo�^����Ă���o���b�g�S�Ăɑ΂��Ĕ���
		OBJECT_FOR_TREE *hardCubeOFT = cellArray[OFT_HARDCUBE][cntCell]->latestObj;
		for (; hardCubeOFT != NULL; hardCubeOFT = hardCubeOFT->next)
		{
			HARD_CUBE_OBJECT *hardCube = (HARD_CUBE_OBJECT*)hardCubeOFT->object;
			CheckCollisionPlayerBulletAndHardCubeLower(cntCell, hardCube, false);
		}
	}
}

/**************************************
�v���C���[�o���b�g�ƃn�[�h�L���[�u�̏Փ˔���(�q���Ver)
***************************************/
bool CheckCollisionPlayerBulletAndHardCubeLower(DWORD elem,	HARD_CUBE_OBJECT *hardCube, bool isCheckedUpper)
{
	//�w�肳�ꂽ��Ԃ��ő��Ԑ��𒴂��Ă��锻��
	if (elem >= cellNum)
		return false;

	//�e��Ԃł̔���
	if(isCheckedUpper)
	{
		bool result;
		result = CheckCollisionPlayerBulletAndHardCubeUpper(elem, hardCube);
		if (result)
			return true;
	}
	
	//��Ԃ��쐬����Ă��Ȃ��ꍇ�̔���
	if (!cellArray[OFT_PLAYERBULLET][elem])
		return false;

	//�w�肳��ċ�ԓ��̃I�u�W�F�N�g�ɑ΂��Ĕ���
	if (cellArray[OFT_PLAYERBULLET][elem]->latestObj != NULL)
	{
		OBJECT_FOR_TREE *bulletOFT = cellArray[OFT_PLAYERBULLET][elem]->latestObj;
		while (bulletOFT != NULL)
		{
			//�Փ˔���
			PLAYERBULLET *bullet = (PLAYERBULLET*)bulletOFT->object;
			if (ChechHitBoundingCube(&bullet->collider2, &hardCube->collider))
			{
				BurstPlayerBullet(bullet);
				hardCube->hp -= 1.0f;
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
		result = CheckCollisionPlayerBulletAndHardCubeLower(nextElem, hardCube, true);
	}

	return false;
}

/**************************************
�v���C���[�o���b�g�ƃn�[�h�L���[�u�̏Փ˔���(�e���Ver)
***************************************/
bool CheckCollisionPlayerBulletAndHardCubeUpper(DWORD elem, HARD_CUBE_OBJECT *hardCube)
{
	//���[�g��ԂɃW�����v����܂Ń��[�v
	for(elem = (elem - 1) >> 2; elem < cellNum; elem = (elem - 1) >> 2)
	{	
		//��Ԃ��쐬����Ă��Ȃ��ꍇ�̔���
		if (!cellArray[OFT_PLAYERBULLET][elem])
			continue;

		//�w�肳��ċ�ԓ��̃I�u�W�F�N�g�ɑ΂��Ĕ���
		if (cellArray[OFT_PLAYERBULLET][elem]->latestObj != NULL)
		{
			OBJECT_FOR_TREE *bulletOFT = cellArray[OFT_PLAYERBULLET][elem]->latestObj;
			while (bulletOFT != NULL)
			{
				//�Փ˔���
				PLAYERBULLET *bullet = (PLAYERBULLET*)bulletOFT->object;
				if (ChechHitBoundingCube(&bullet->collider2, &hardCube->collider))
				{
					BurstPlayerBullet(bullet);
					hardCube->hp -= 1.0f;
					return true;
				}

				//���̃L���[�u��
				bulletOFT = bulletOFT->next;
			}
		}
	}

	return false;
}

/**************************************
�{�[�i�X�L���[�u�̏Փ˔���
***************************************/
bool CheckCollisionBonusCube(void)
{
	for (DWORD cntCell = 0; cntCell < cellNum; cntCell++)
	{
		//��Ԃ��쐬����Ă��Ȃ��ꍇ�̔���
		if (!cellArray[OFT_BONUSCUBE][cntCell])
			continue;

		//��ԂɃI�u�W�F�N�g���o�^����Ă��Ȃ��ꍇ�̔���
		if (cellArray[OFT_BONUSCUBE][cntCell]->latestObj == NULL)
			continue;

		//��Ԃɓo�^����Ă���L���[�u�S�Ăɑ΂��Ĕ���
		OBJECT_FOR_TREE *bonusCubeOFT = cellArray[OFT_BONUSCUBE][cntCell]->latestObj;
		for (; bonusCubeOFT != NULL; bonusCubeOFT = bonusCubeOFT->next)
		{
			BONUS_CUBE_OBJECT *bonusCube = (BONUS_CUBE_OBJECT*)bonusCubeOFT->object;
			CheckCollisionBonusCubeAndPlayerBulletLower(cntCell, bonusCube, false);
		}
	}

	return false;
}

/**************************************
�{�[�i�X�L���[�u�ƃv���C���[�o���b�g�̏Փ˔���i�q���Ver)
***************************************/
bool CheckCollisionBonusCubeAndPlayerBulletLower(DWORD elem, BONUS_CUBE_OBJECT *bonusCube, bool isCheckedUpper)
{
	//��Ԑ��̔���
	if (elem >= cellNum)
		return false;

	//�e��Ԃł̔���
	if (!isCheckedUpper)
	{
		CheckCollisionBonusCubeAndPlayerBulletUpper(elem, bonusCube);
	}

	//��Ԃ��쐬����Ă��Ȃ��ꍇ�̔���
	if (!cellArray[OFT_PLAYERBULLET][elem])
		return false;

	//��Ԃɓo�^����Ă���o���b�g�Ɣ���
	if (cellArray[OFT_PLAYERBULLET][elem]->latestObj != NULL)
	{
		OBJECT_FOR_TREE *bulletOFT = cellArray[OFT_PLAYERBULLET][elem]->latestObj;
		for (; bulletOFT != NULL; bulletOFT = bulletOFT->next)
		{
			PLAYERBULLET *bullet = (PLAYERBULLET*)bulletOFT->object;
			if (ChechHitBoundingCube(&bullet->collider2, &bonusCube->collider))
			{
				BurstPlayerBullet(bullet);
				bonusCube->hp -= 1.0f;
			}
		}
	}

	//�q��Ԃł�����
	for (int i = 0; i < 4; i++)
	{
		DWORD nextElem = elem * 4 + 1 + i;
		CheckCollisionBonusCubeAndPlayerBulletLower(nextElem, bonusCube, true);
	}

	return false;
}

/**************************************
�{�[�i�X�L���[�u�ƃv���C���[�o���b�g�̏Փ˔���i�e���Ver�j
***************************************/
bool CheckCollisionBonusCubeAndPlayerBulletUpper(DWORD elem, BONUS_CUBE_OBJECT *bonusCube)
{
	//���[�g��Ԃւ��ǂ�܂Ń��[�v
	for (elem = (elem - 1) >> 2; elem < cellNum; elem = (elem - 1) >> 2)
	{
		//��Ԃ��쐬����Ă��邩����
		if (!cellArray[OFT_PLAYERBULLET][elem])
			continue;

		if (cellArray[OFT_PLAYERBULLET][elem]->latestObj != NULL)
		{
			OBJECT_FOR_TREE *bulletOFT = cellArray[OFT_PLAYERBULLET][elem]->latestObj;
			while (bulletOFT != NULL)
			{
				PLAYERBULLET *bullet = (PLAYERBULLET*)bulletOFT->object;
				if (ChechHitBoundingCube(&bullet->collider2, &bonusCube->collider))
				{
					BurstPlayerBullet(bullet);
					bonusCube->hp -= 1.0f;
				}

				bulletOFT = bulletOFT->next;
			}
		}
	}

	return false;
}
/**************************************
�I�u�W�F�N�g�o�^����
***************************************/
//bool RegisterObjectToSpace(float left, float top, float right, float bottom, OBJECT_FOR_TREE *obj, OFT_ID id)
bool RegisterObjectToSpace(COLLIDER_CUBE *collider, OBJECT_FOR_TREE *obj, OFT_ID id)
{
	float left = collider->pos->x - collider->length.x;
	float top = collider->pos->y - collider->length.z;
	float right = collider->pos->x + collider->length.x;
	float bottom = collider->pos->y + collider->length.z;

	DWORD elem = GetMortonNumber(left, top, right, bottom);
	if (elem < cellNum)
	{
		//��Ԃ������蓖�Ă̏ꍇ�͐V�K�쐬
		if (cellArray[id][elem] == NULL)
			CreateNewCell(elem, id);

#ifdef _DEBUG
		obj->elem = elem;
#endif

		return PushObjectToList(cellArray[id][elem], obj);
	}

	return false;
}

/**************************************
��ԍ쐬����
***************************************/
bool CreateNewCell(DWORD elem, OFT_ID OFTid)
{
	//��Ԃ��쐬��A���[�g��ԂɒH�蒅���܂ő�����
	while (!cellArray[OFTid][elem])
	{
		//�w��̋�Ԃ��쐬
		cellArray[OFTid][elem] = (CCell*)malloc(sizeof(CCell));
		cellArray[OFTid][elem]->latestObj = NULL;

		//�e��ԂɃW�����v
		elem = (elem - 1) >> 2;

		if (elem >= cellNum)
			break;
	}

	return true;
}
/**************************************
��Ԕԍ��Z�o����
***************************************/
DWORD GetMortonNumber(float left, float top, float right, float bottom)
{
	//���E�}�`��2D���[�g���ԍ����Z�o
	DWORD lt = GetPointElem(left, top);
	DWORD rb = GetPointElem(right, bottom);

	//�������x�����Z�o
	DWORD def = rb ^ lt;
	unsigned int hiLevel = 0;
	for (unsigned int i = 0; i < COLLISION_DIVISIONSPACE_LEVEL_MAX; i++)
	{
		DWORD check = (def >> (i * 2)) & 0x3;
		if (check != 0)
			hiLevel = i + 1;
	}
	DWORD baseNum = rb >> (hiLevel * 2);
	DWORD addNum = (spaceNum[COLLISION_DIVISIONSPACE_LEVEL_MAX - hiLevel] - 1) / 3;
	DWORD spaceIndex = baseNum + addNum;

	if (spaceIndex > cellNum)
		return 0xffffffff;

	return spaceIndex;
}

/**************************************
�r�b�g���Z����
***************************************/
DWORD BitSeparate32(DWORD n)
{
	n = (n | (n << 8)) & 0x00ff00ff;
	n = (n | (n << 4)) & 0x0f0f0f0f;
	n = (n | (n << 2)) & 0x33333333;
	return (n | (n << 1)) & 0x55555555;
}

/**************************************
2D���[�g���ԍ��Z�o����
***************************************/
WORD Get2DMortonNumber(WORD x, WORD y)
{
	return (WORD)(BitSeparate32(x) | (WORD)(BitSeparate32(y) << 1));
}

/**************************************
���W�����`4���ؗv�f�ԍ��ϊ�����
***************************************/
DWORD GetPointElem(float posX, float posY)
{
	return Get2DMortonNumber((WORD)((posX - COLLISION_REGION_LEFT) / UnitWidth), (WORD)((posY - COLLISION_REGION_TOP) / UnitHeight));
}

/**************************************
��Ԃ���I�u�W�F�N�g����菜������
***************************************/
bool RemoveObjectFromSpace(OBJECT_FOR_TREE *obj)
{
	//���łɎ�菜����Ă���ꍇ�̔���
	if (obj->registerSpace == NULL)
		return false;

	//�o�^����Ă����Ԃɗ��E��ʒm
	if (!OnObjectRemoveFromList(obj->registerSpace, obj))
		return false;

	//�O��̃I�u�W�F�N�g��A������
	if (obj->prev != NULL)
	{
		obj->prev->next = obj->next;
	}
	if (obj->next != NULL)
	{
		obj->next->prev = obj->prev;
	}

	//���E
	obj->prev = NULL;
	obj->next = NULL;
	obj->registerSpace = NULL;
	return true;
}

/**************************************
���X�g�ւ̃I�u�W�F�N�g�o�^����
***************************************/
bool PushObjectToList(CCell *space, OBJECT_FOR_TREE *obj)
{
	//NULL�`�F�b�N
	if (obj == NULL)
		return false;

	//��d�o�^�`�F�b�N
	if (obj->registerSpace == space)
		return false;

	//�V�K�o�^
	if (space->latestObj == NULL)
	{
		space->latestObj = obj;
	}
	//�ǉ��o�^
	else
	{
		obj->next = space->latestObj;
		space->latestObj->prev = obj;
		space->latestObj = obj;
	}

	//��Ԃ�o�^
	obj->registerSpace = space;
	return true;
}

/**************************************
���E�I�u�W�F�N�g�̃`�F�b�N����
***************************************/
bool OnObjectRemoveFromList(CCell *space, OBJECT_FOR_TREE *obj)
{
	//�폜�����I�u�W�F�N�g���擪�̏ꍇ�A�}���ւ�
	if (space->latestObj == obj)
	{
		if (space->latestObj != NULL)
			space->latestObj = space->latestObj->next;
	}
	return true;
}

/**************************************
OBJECT_FOR_TREE�쐬����
***************************************/
void CreateOFT(OBJECT_FOR_TREE *oft, void *object)
{
	oft->registerSpace = NULL;
	oft->object = object;
	oft->prev = NULL;
	oft->prev = NULL;
}