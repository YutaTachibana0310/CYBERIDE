//=====================================
//
//�������A���P�[�^�w�b�_[memoryAllocater.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _MEMORYALLOCATER_H_
#define _MEMORYALLOCATER_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/
void UninitMemoryAllocater(void);
void UpdateMemoryAllocater(void);
void* AllocMemory(size_t size, const char* label);
void ReleaseMemory(size_t size, const char* label, void *p);

#endif