//===========================================================
//
//�t���N�^���v�Z�w�b�_[fractal.h]
//Author�FGP11A341 21 ���ԗY��
//
//===========================================================
#ifndef _FRACTAL_H_
#define _FRACTAL_H_

#include "main.h"

/*
�v���g�^�C�v�錾
*/
void InitializeHeightMap1(float *map, int elemNum, float centerHeight, int center); //2�����̃n�C�g�}�b�v����
void InitializeHeightMap2(float *map, int elemNum); //3�����̃n�C�g�}�b�v����
float *getHeightMap2(void);
#endif // !_FRACTAL_H_
