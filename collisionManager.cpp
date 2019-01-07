//=====================================
//
//�e���v���[�g����[collisionManager.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "collisionManager.h"
#include "collider.h"

/**************************************
�}�N����`
***************************************/
#define COLLISION_DIVISIONSPACE_LEVEL_MAX		(9)			//��ԃ��x���̍ő僌�x��
#define COLLISION_REGION_LEFT					(-500.0f)	//�����Ԃ̍��[
#define COLLISION_REGION_RIGHT					(500.0f)	//�����Ԃ̉E�[
#define COLLISION_REGION_TOP					(5000.0f)	//�����Ԃ̏�[
#define COLLISION_REGION_BOTTOM					(-5000.0f)	//�����Ԃ̉��[

//�P�ʕ�����Ԃ̕�
#define COLLISION_UNIT_WIDTH ((COLLISION_REGION_RIGHT - COLLISION_REGION_LEFT) / (1 << COLLISION_DIVISIONSPACE_LEVEL_MAX))

//�P�ʕ�����Ԃ̍���
#define COLLISION_UNIT_HEIGHT ((COLLISION_REGION_TOP - COLLISION_REGION_BOTTOM) / (1 << COLLISION_DIVISIONSPACE_LEVEL_MAX))

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static unsigned int spaceNum[COLLISION_DIVISIONSPACE_LEVEL_MAX + 1];	//�e���x���̋�Ԑ�
static DWORD cellNum;					//��Ԑ��̑��a
static CCell **cellArray[OFT_ID_MAX];	//�e�I�u�W�F�N�g���o�^������Ԃ̔z��

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

/**************************************
����������
***************************************/
void InitCollisionManager(int num)
{

}

/**************************************
�I������
***************************************/
void UninitCollisionManager(int num)
{

}

/**************************************
�X�V����
***************************************/
void UpdateCollisionManager(void)
{

}

/**************************************
�I�u�W�F�N�g�o�^����
***************************************/
bool RegisterObjectToSpace(float left, float top, float right, float bottom, OBJECT_FOR_TREE *obj, OFT_ID id)
{
	DWORD elem = GetMortonNumber(left, top, right, bottom);
	if (elem < cellNum)
	{
		//��Ԃ������蓖�Ă̏ꍇ�͐V�K�쐬
		if (cellArray[id][elem] == NULL)
			CreateNewCell(elem, id);

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
		DWORD check = (def >> (i * 2)) & 0x03;
		if (check != 0)
			hiLevel = i + 1;
	}
	DWORD spaceIndex = rb >> (hiLevel * 2);
	DWORD addNum = (spaceNum[COLLISION_DIVISIONSPACE_LEVEL_MAX - hiLevel] - 1) / 3;
	spaceIndex += addNum;

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
	return (WORD)(BitSeparate32(x) | (BitSeparate32(y) << 1));
}

/**************************************
���W�����`4���ؗv�f�ԍ��ϊ�����
***************************************/
DWORD GetPointElem(float posX, float posY)
{
	return Get2DMortonNumber((WORD)((posX - COLLISION_REGION_LEFT) / COLLISION_UNIT_WIDTH), (WORD)((posY + COLLISION_REGION_TOP) / COLLISION_UNIT_HEIGHT));
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