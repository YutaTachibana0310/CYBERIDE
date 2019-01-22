//=====================================
//
//�X�e�[�W�f�[�^����[stageData.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "stageData.h"
#include <stdio.h>


/**************************************
�}�N����`
***************************************/
#define STAGEDATA_PATH	"data/STAGE/StageData.dat"

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static STAGE_DATA *dataHead;
static int currentIndex;
static int dataMax;

/**************************************
�v���g�^�C�v�錾
***************************************/
bool LoadStageData(void);

/**************************************
����������
***************************************/
void InitStageData(int num)
{
	static bool initialized = false;
	currentIndex = 0;

	if (!initialized)
	{
		LoadStageData();
		initialized = true;
	}
}

/**************************************
�I������
***************************************/
void UninitStageData(int num)
{
	if (num == 0)
	{
		free(dataHead);
	}
}

/**************************************
�X�V����
***************************************/
int UpdateStageData(STAGE_DATA **out, DWORD currentFrame)
{
	int cntData = 0;
	while (currentIndex < dataMax && dataHead[currentIndex].emmittFrame == currentFrame)
	{
		if (cntData == 0)
			*out = &dataHead[currentIndex];
		currentIndex++;
		cntData++;
	}


	return cntData;
}

/**************************************
�X�e�[�W�f�[�^�ǂݍ��ݏ���
***************************************/
bool LoadStageData(void)
{
	FILE *fp = NULL;

	//�t�@�C���ǂݍ���
	fp = fopen(STAGEDATA_PATH, "r");
	if (fp == NULL)
		return false;

	//�������m��
	dataMax = 0;
	int loadRes = fscanf(fp, "%d", &dataMax);

	if (loadRes == EOF)
		return false;

	dataHead = (STAGE_DATA*)malloc(sizeof(STAGE_DATA) * dataMax);
	ZeroMemory(dataHead, sizeof(STAGE_DATA) * dataMax);

	//�f�[�^�ǂݍ���
	STAGE_DATA *ptr = dataHead;
	int sumEmmittFrame = 0;
	for (int i = 0; i < dataMax; i++, ptr++)
	{
		fscanf(fp, "%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
			&ptr->emmittFrame,
			&ptr->type,
			&ptr->initPos.x,
			&ptr->initPos.y,
			&ptr->initPos.z,
			&ptr->targetPos.x,
			&ptr->targetPos.y,
			&ptr->targetPos.z,
			&ptr->controller1.x,
			&ptr->controller1.y,
			&ptr->controller1.z,
			&ptr->controller2.x,
			&ptr->controller2.y,
			&ptr->controller2.z);

		ptr->emmittFrame += sumEmmittFrame;
		sumEmmittFrame = ptr->emmittFrame;
	}

	fclose(fp);
	return true;
}