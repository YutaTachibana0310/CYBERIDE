//===========================================================
//
//�t���N�^���v�Z����[fractal.cpp]
//Author�FGP11A341 21 ���ԗY��
//
//===========================================================

#include "fractal.h"
#include "MyLibrary.h"
#include "input.h"

/******************************************************
�\���̒�`
******************************************************/
typedef struct
{
	int z;
	int x;
	float height;
}Point;

/****************************************************
�v���g�^�C�v�錾
****************************************************/
void CreateHeightMap1(int start, int end, float range, float *map);
void CreateHeightMap2(float *map);

/***************************************************
�O���[�o���ϐ�
***************************************************/
static float d = 2.0f;
static const float minHeight = -400.0f, maxHeight = 400.0f;
static int vtxNum;

/**************************************
�t���N�^���Z�b�g�A�b�v�֐�
***************************************/
void SetUpFractal(int num, float seed)
{
	vtxNum = num;
	d = seed;
}

/*************************************************
�֐�	�Fvoid InitializeHeightMap1(void)
����	�Ffloat *heightmap	�F���������n�C�g�}�b�v��ۑ�����|�C���^
����	�Fint elemNum		�F�n�C�g�}�b�v�̗v�f��
����	�Ffloat centerHeight�F�ŏ��̓����_�̍���
����	�Fint center		�F�ŏ��̓����_�̓Y��
�߂�l	�Fvoid
����	�F2�����n�C�g�}�b�v������
**************************************************/
void InitializeHeightMap1(float *map, int elemNum, float centerHeight, int center)
{
	map[center] = centerHeight;
	CreateHeightMap1(0, center, 20.0f, map);
	CreateHeightMap1(center, elemNum, 20.0f, map);
}

/*************************************************
�֐�	�Fvoid CreateHeightMap1(int start, int end, float range, float *map)
����	�Fint start		�F�n�_
����	�Fint end		�F�I�_
����	�Ffloat range	�F������ψق�����͈�
����	�Ffloat *map	�F�n�C�g�}�b�v��ۑ�����|�C���^
�߂�l	�Fvoid
����	�F2�����n�C�g�}�b�v����
**************************************************/
void CreateHeightMap1(int start, int end, float range, float *map)
{
	if (abs(end - start) <= 1)
	{
		return;
	}

	int c = start + (end - start) / 2;
	map[c] = (map[end] + map[start]) / 2;
	map[c] += RandomRangef(-range / 2, range / 2);

	CreateHeightMap1(start, c, range / 2, map);
	CreateHeightMap1(c, end, range / 2, map);

	return;
}

/*************************************************
�֐�	�Fvoid InitializeHeightMap1(void)
����	�Ffloat *heightmap	�F���������n�C�g�}�b�v��ۑ�����|�C���^
����	�Fint elemNum		�F�n�C�g�}�b�v�̗v�f��
����	�Ffloat centerHeight�F�ŏ��̓����_�̍���
����	�Fint center		�F�ŏ��̓����_�̓Y��
�߂�l	�Fvoid
����	�F3�����n�C�g�}�b�v������
**************************************************/
void InitializeHeightMap2(float *map, int elemNum)
{
	const float maxHeight = 300.0f;
	const float minHeight = -300.0f;

	Point bottomL = { vtxNum, 0, RandomRangef(minHeight, maxHeight) };
	//map[bottomL.x][bottomL.x] = bottomL.height;
	map[bottomL.x * vtxNum + bottomL.x] = bottomL.height;

	Point bottomR = { vtxNum, vtxNum, RandomRangef(minHeight, maxHeight) };
	//map[bottomR.z][bottomR.x] = bottomR.height;
	map[bottomR.z * vtxNum + bottomR.x] = bottomR.height;

	Point topL = { 0, 0, RandomRangef(minHeight, maxHeight) };
	//map[topL.z][topL.x] = topL.height;
	map[topL.z * vtxNum + topL.x] = topL.height;

	Point topR = { 0, vtxNum, RandomRangef(minHeight, maxHeight) };
	//map[topR.z][topR.x] = topR.height;
	map[topR.z * vtxNum + topR.x] = topR.height;

	Point center = { vtxNum / 2, vtxNum / 2, 1000.0f };
	//map[center.z][center.x] = center.height;
	map[center.z *vtxNum + center.x] = center.height;

	Point bottom = { bottomL.z, center.x, (bottomL.height + bottomR.height) / 2 };
	//map[bottom.z][bottom.x] = bottom.height;
	map[bottom.z * vtxNum + bottom.x] = bottom.height;

	Point top = { topR.z, center.x, (topL.height + topR.height) / 2 };
	//map[top.z][top.x] = top.height;
	map[top.z * vtxNum + top.x] = top.height;

	Point left = { center.z, topL.x, (topL.height + bottomL.height) / 2 };
	//map[left.z][left.x] = left.height;
	map[left.z + vtxNum + left.z] = left.height;

	Point right = { center.z, topR.x, (topR.height + bottomR.height) / 2 };
	//map[right.z][right.x] = right.height;
	map[right.z * vtxNum + right.z] = right.height;

	CreateHeightMap2(map);
}

/*************************************************
�֐�	�Fvoid CreateHeightMap2(Point tr, Point tl, Point br, Point bl, float range, float *map, int elemNum)
����	�FPoint tr		�F�E��̃|�C���g
����	�FPoint tl		�F����̃|�C���g
����	�FPoint br		�F�E���̃|�C���g
����	�FPoint bl		�F�����̃|�C���g
����	�Ffloat range	�F�ψق����镝
����	�Ffloat *map	�F�n�C�g�}�b�v��ۑ�����|�C���^
����	�Fint elemNum	�F�n�C�g�}�b�v�̗v�f��
�߂�l	�Fvoid
����	�F3�����n�C�g�}�b�v����
**************************************************/
void CreateHeightMap2(float *map)
{

	int i, j, ni, nj, mi, mj, pmi, pmj, rectSize = vtxNum;
	float dh = (float)1000 / 2, r = (float)pow(2, -1 * 0.9);

	//map[0][0] = 0;
	map[0] = 0;

	while (rectSize > 0)
	{
		for (int i = 0; i < vtxNum; i += rectSize)
		{
			for (int j = 0; j < vtxNum; j += rectSize)
			{
				ni = (i + rectSize) % vtxNum;
				nj = (j + rectSize) % vtxNum;

				mi = (i + rectSize / 2);
				mj = (j + rectSize / 2);

				//map[mj][mi] = (map[j][i] + map[j][ni] + map[nj][i] + map[nj][ni]) / 4 + RandomRangef(-dh / 2, dh / 2);
				float average = (map[j * vtxNum + i] + map[j * vtxNum + ni] + map[nj * vtxNum + i] + map[nj * vtxNum + ni]) / 4;
				map[mj * vtxNum + mi] = average + RandomRangef(-dh / 2, dh / 2);
			}
		}

		for (int i = 0; i < vtxNum; i += rectSize)
		{
			for (int j = 0; j < vtxNum; j += rectSize)
			{
				ni = (i + rectSize) % vtxNum;
				nj = (j + rectSize) % vtxNum;

				mi = (i + rectSize / 2);
				mj = (j + rectSize / 2);

				pmi = (i - rectSize / 2 + vtxNum) % vtxNum;
				pmj = (j - rectSize / 2 + vtxNum) % vtxNum;

				//map[j][mi] = (map[j][i] + map[j][ni] + map[pmj][mi] + map[mj][mi]) / 4 + RandomRangef(-dh / 2, dh / 2);
				float average1 = (map[j * vtxNum + i] + map[j * vtxNum + ni] + map[pmj * vtxNum + mi] + map[mj * vtxNum + mi]) / 4;
				map[j * vtxNum + mi] = average1 + RandomRangef(-dh / 2, dh / 2);

				//map[mj][i] = (map[j][i] + map[nj][i] + map[mj][pmi] + map[mj][mi]) / 4 + RandomRangef(-dh / 2, dh / 2);
				float average2 = (map[j * vtxNum + i] + map[nj * vtxNum + i] + map[mj * vtxNum + pmi] + map[mj * vtxNum + mi]) / 4;
				map[mj * vtxNum + i] = average2 + RandomRangef(-dh / 2, dh / 2);
			}
		}

		rectSize /= 2;
		dh *= r;
	}
}