//=====================================
//
//�������A���P�[�^����[memoryAllocater.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <windows.h>
#include "debugWindow.h"

/**************************************
�}�N����`
***************************************/
#define MEMORYALLOCATER_LABEL_MAX	(32)
/**************************************
�\���̒�`
***************************************/
typedef struct _MEMORYINFO {
	char label[MEMORYALLOCATER_LABEL_MAX];
	size_t size;
	_MEMORYINFO *next;
}MEMORIINFO;

/**************************************
�O���[�o���ϐ�
***************************************/
static MEMORIINFO *nodeHead = NULL;

/**************************************
�v���g�^�C�v�錾
***************************************/
void OnAllocMemory(size_t size, const char* label, bool isAlloc);

/**************************************
�I������
***************************************/
void UninitMemoryAllocater(void)
{
	MEMORIINFO *node = nodeHead;
	while (node != NULL)
	{
		MEMORIINFO *tmp = node->next;
		free(node);
		node = tmp;
	}
}

/*************************************
�X�V����
***************************************/
void UpdateMemoryAllocater(void)
{
	BeginDebugWindow("Memory Usage");

	for (MEMORIINFO *node = nodeHead; node != NULL; node = node->next)
	{
		DebugText("%s : %d[Byte]", node->label, node->size);
	}

	EndDebugWindow("Memory Usage");
}

/**************************************
�������m�ۏ���
***************************************/
void* AllocMemory(size_t size, const char* label)
{
	void *p = NULL;


	p = malloc(size);

	if (!p)
	{
		assert(p);
		return NULL;
	}

	OnAllocMemory(size, label, true);
	return p;
}

/**************************************
�������������
***************************************/
void ReleaseMemory(size_t size, const char* label, void *p)
{
	if (p == NULL)
	{
		assert(p);
		return;
	}

	OnAllocMemory(size, label, false);
	free(p);
}

/**************************************
���������X�V����
***************************************/
void OnAllocMemory(size_t size, const char* label, bool isAlloc)
{
	for (MEMORIINFO *node = nodeHead; node != NULL; node = node->next)
	{
		if (strcmp(node->label, label) == 0)
		{
			if (isAlloc)
				node->size += size;
			else
				node->size -= size;

			return;
		}
	}

	MEMORIINFO *newNode = (MEMORIINFO*)malloc(sizeof(MEMORIINFO));
	ZeroMemory(newNode, sizeof(MEMORIINFO));

	strcpy_s(newNode->label, MEMORYALLOCATER_LABEL_MAX, label);
	newNode->size = size;
	newNode->next = nodeHead;
	nodeHead = newNode;
}