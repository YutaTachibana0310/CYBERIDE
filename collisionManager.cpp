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
#include "memoryAllocater.h"

#include "debugWindow.h"

/**************************************
�}�N����`
***************************************/
#define COLLISION_REGION_LEFT					(-500.0f)	//�����Ԃ̍��[
#define COLLISION_REGION_RIGHT					(500.0f)	//�����Ԃ̉E�[
#define COLLISION_REGION_TOP					(-5000.0f)	//�����Ԃ̏�[
#define COLLISION_REGION_BOTTOM					(5000.0f)	//�����Ԃ̉��[

#define PLAYERBULLET_DAMAGE						(1.0f)
/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
//static unsigned int manager.spaceNum[COLLISION_DIVISIONSPACE_LEVEL_MAX + 1];	//�e���x���̋�Ԑ�
//static DWORD manager.cellNum;					//��Ԑ��̑��a
//static CCell **manager.cellArray[OFT_ID_MAX];	//�e�I�u�W�F�N�g���o�^������Ԃ̔z��
static COLLISION_MANAGER manager;

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

void CheckCollisionCubeObject(COLLISION_MANAGER *manager);		//�L���[�u�I�u�W�F�N�g�̏Փ˔���
void CheckCollisionHardCube(COLLISION_MANAGER *manager);		//�n�[�h�L���[�u�̏Փ˔���
void CheckCollisionBonusCube(COLLISION_MANAGER *manager);		//�{�[�i�X�L���[�u�̏Փ˔���
void CheckCollisionEnemyBullet(COLLISION_MANAGER *manager);		//�G�l�~�[�o���b�g�̏Փ˔���
void CheckCollisionEnemyHomingBullet(COLLISION_MANAGER *manager);//�G�l�~�[�z�[�~���O�o���b�g�̏Փ˔���

/**************************************
����������
***************************************/
void InitCollisionManager(int num)
{
	static bool initialized = false;

	if (initialized)
		return;

	//�e���x���̋�Ԑ����Z�o
	manager.spaceNum[0] = 1;
	for (int i = 1; i < COLLISION_DIVISIONSPACE_LEVEL_MAX + 1; i++)
	{
		manager.spaceNum[i] = manager.spaceNum[i - 1] * 4;
	}

	//��Ԕz��̃��������m��
	manager.cellNum = (manager.spaceNum[COLLISION_DIVISIONSPACE_LEVEL_MAX] * 4 - 1) / 3;
	for (int OFTid = 0; OFTid < OFT_ID_MAX; OFTid++)
	{
		//manager.cellArray[OFTid] = (CCell**)malloc(sizeof(CCell*) * manager.cellNum);
		manager.cellArray[OFTid] = (CCell**)AllocMemory(sizeof(CCell*) * manager.cellNum, "CollisionManager");
		ZeroMemory(manager.cellArray[OFTid], sizeof(CCell*) * manager.cellNum);
	}
	initialized = true;
}

/**************************************
�I������
***************************************/
void UninitCollisionManager(int num)
{
	if (num == 0)
	{
		for (int OFTid = 0; OFTid < OFT_ID_MAX; OFTid++)
		{
			//free(manager.cellArray[OFTid]);
			ReleaseMemory(sizeof(*manager.cellArray[OFTid]), "CollisionManager", manager.cellArray[OFTid]);
			manager.cellArray[OFTid] = NULL;
		}
	}
}
#include "input.h"
/**************************************
�X�V����
***************************************/
void UpdateCollisionManager(void)
{
	static DWORD cnt = 0, cntFrame = 0;

	CheckCollisionCubeObject(&manager);
	CheckCollisionHardCube(&manager);
	CheckCollisionBonusCube(&manager);
	CheckCollisionEnemyBullet(&manager);
	CheckCollisionEnemyHomingBullet(&manager);

	BeginDebugWindow("CollisionManager");
	DebugText("CheckCount : %d", cnt);
	EndDebugWindow("CollisionManager");

	if (++cntFrame % 20 == 0)
		cnt = cntCheck;
	cntCheck = 0;
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
	if (elem < manager.cellNum)
	{
		//��Ԃ������蓖�Ă̏ꍇ�͐V�K�쐬
		if (manager.cellArray[id][elem] == NULL)
			CreateNewCell(elem, id);

#ifdef _DEBUG
		obj->elem = elem;
#endif

		return PushObjectToList(manager.cellArray[id][elem], obj);
	}

	return false;
}

/**************************************
��ԍ쐬����
***************************************/
bool CreateNewCell(DWORD elem, OFT_ID OFTid)
{
	//��Ԃ��쐬��A���[�g��ԂɒH�蒅���܂ő�����
	while (!manager.cellArray[OFTid][elem])
	{
		//�w��̋�Ԃ��쐬
		manager.cellArray[OFTid][elem] = (CCell*)malloc(sizeof(CCell));
		manager.cellArray[OFTid][elem]->latestObj = NULL;

		//�e��ԂɃW�����v
		elem = (elem - 1) >> 2;

		if (elem >= manager.cellNum)
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
	DWORD addNum = (manager.spaceNum[COLLISION_DIVISIONSPACE_LEVEL_MAX - hiLevel] - 1) / 3;
	DWORD spaceIndex = baseNum + addNum;

	if (spaceIndex > manager.cellNum)
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