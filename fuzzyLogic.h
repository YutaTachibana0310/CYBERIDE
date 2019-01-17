//=====================================
//
//�t�@�W�[�w�b�_[fuzzy.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _FUZZY_H_
#define _FUZZY_H_

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


float fFuzzyRightGrade(float value, float x0, float x1);
float fFuzzyLeftGrade(float value, float x0, float x1);
float fFuzzyTriangle(float value, float x0, float x1, float x2);
float fFuzzyTrapezoid(float value, float x0, float x1, float x2, float x3);

float dwFuzzyRightGrade(DWORD value, DWORD x0, DWORD x1);
float dwFuzzyLeftGrade(DWORD value, DWORD x0, DWORD x1);
float dwFuzzyTriangle(DWORD value, DWORD x0, DWORD x1, DWORD x2);
float dwFuzzyTrapezoid(DWORD value, DWORD x0, DWORD x1, DWORD x2, DWORD x3);

float FuzzyAnd(float a, float b);
float FuzzyOr(float a, float b);
float FuzzyNot(float a);

/*�{���̓e���v���[�g�֐����g������*/
#if 0
/**************************************
�E�オ��ΕӃ����o�[�V�b�v�֐�
***************************************/
template <typename T>
float FuzzyRightGrade(T value, T x0, T x1)
{
	assert(x0 <= x1);

	if (value <= x0)
		return 0;

	if (value >= x1)
		return 1;

	float diff = x1 - x0;

	return (value - x0) / diff;
}

/**************************************
���オ��ΕӃ����o�[�V�b�v�֐�
***************************************/
template <typename T>
float FuzzyLeftGrade(T value, T x0, T x1)
{
	assert(x0 <= x1);

	if (value <= x0)
		return 1;

	if (value >= x1)
		return 0;

	float diff = x1 - x0;

	return (x1 - value) / diff;
}

/**************************************
�O�p�`�����o�[�V�b�v�֐�
***************************************/
template <typename T>
float FuzzyTriangle(T value, T x0, T x1, T x2)
{
	assert(x0 <= x1);
	assert(x1 <= x2);

	if (value <= x0)
		return 0;

	if (value >= x2)
		return 0;

	if (value > x0 && value < x1)
		return FuzzyRightGrade(value, x0, x1);

	return FuzzyLeftGrade(value, x1, x2);
}

/**************************************
��`�����o�[�V�b�v�֐�
***************************************/
template <typename T>
float FuzzyTrapezoid(T value, T x0, T x1, T x2, T x3)
{
	assert(x0 <= x1);
	assert(x1 <= x2);
	assert(x2 <= x3);

	if (value <= x0 || value >= x3)
		return 0;

	if (value >= x1 && value <= x2)
		return 1;

	if (value < x1)
		return FuzzyRightGrade(value, x0, x1);

	return FuzzyLeftGrade(value, x2, x3);
}
#endif

#endif