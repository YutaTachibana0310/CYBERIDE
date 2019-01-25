//=====================================
//
//�������A���P�[�^����[memoryAllocater.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "memoryAllocater.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <windows.h>
#include "debugWindow.h"

/**************************************
�}�N����`
***************************************/
#define MEMORYALLOCATER_LABEL_MAX	(32)	//�����郉�x���̍ő啶����

/**************************************
�\���̒�`
***************************************/
typedef struct _MEMORYINFO {
	char label[MEMORYALLOCATER_LABEL_MAX];	//���x��
	size_t size;							//�m�ۂ��ꂽ�������̃T�C�Y
	_MEMORYINFO *next;						//���X�g�̎��̃��������
}MEMORYINFO;	//���������\����

/**************************************
�O���[�o���ϐ�
***************************************/
static MEMORYINFO *nodeHead = NULL;			//���X�g�������������̐擪

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
�I������
***************************************/
void UninitMemoryAllocater(void)
{
	//���X�g�����������������ׂĉ��
	MEMORYINFO *node = nodeHead;
	while (node != NULL)
	{
		MEMORYINFO *tmp = node->next;
		free(node);
		node = tmp;
	}
}

/*************************************
�X�V����
***************************************/
void UpdateMemoryAllocater(void)
{
	//����������\��
	BeginDebugWindow("Memory Usage");

	for (MEMORYINFO *node = nodeHead; node != NULL; node = node->next)
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

	//���������m��
	p = malloc(size);

	if (!p)
	{
		assert(p);
		return NULL;
	}

	//�m�ۂ��������������X�g�ɒǉ�
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

	//����������Ƃ����X�g�ɒʒm
	OnAllocMemory(size, label, false);
	free(p);
}

/**************************************
���������X�V����
***************************************/
void OnAllocMemory(size_t size, const char* label, bool isAlloc)
{
	//���X�g�̒����烉�x���Ɉ�v���郁���������������čX�V
	for (MEMORYINFO *node = nodeHead; node != NULL; node = node->next)
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

	//���X�g���ɂȂ������̂ŐV�K�쐬���Ēǉ�
	MEMORYINFO *newNode = (MEMORYINFO*)malloc(sizeof(MEMORYINFO));
	ZeroMemory(newNode, sizeof(MEMORYINFO));

	strcpy_s(newNode->label, MEMORYALLOCATER_LABEL_MAX, label);
	newNode->size = size;
	newNode->next = nodeHead;
	nodeHead = newNode;
}