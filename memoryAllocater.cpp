//=====================================
//
//�������A���P�[�^����[memoryAllocater.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include <stdlib.h>
#include <assert.h>
#include <string.h>

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
static MEMORIINFO *memInfo = NULL;

/**************************************
�v���g�^�C�v�錾
***************************************/

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

	return p;
}

/**************************************
�������������
***************************************/
void ReleaseMemory(void *p)
{
	free(p);
}