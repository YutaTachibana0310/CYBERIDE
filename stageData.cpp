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
#define STAGEDATA_MODEMAX	(3)

/**************************************
�\���̒�`
***************************************/
typedef struct {
	STAGE_DATA *head;
	int current;
	int dataMax;
}CONTAINER_STAGEDATA;
/**************************************
�O���[�o���ϐ�
***************************************/
static CONTAINER_STAGEDATA container[STAGEDATA_MODEMAX];

static const char* FilePath[STAGEDATA_MODEMAX] = {
	"data/STAGE/StageDataFPS.dat",
	"data/STAGE/StageDataTop.dat",
	"data/STAGE/StageDataSide.dat"
};

/**************************************
�v���g�^�C�v�錾
***************************************/
bool LoadStageData(int i);

/**************************************
����������
***************************************/
void InitStageData(int num)
{
	static bool initialized = false;
	for(int i = 0; i < STAGEDATA_MODEMAX; i++)
		container[i].current = 0;

	if (!initialized)
	{
		for(int i = 0; i < STAGEDATA_MODEMAX; i++)
			LoadStageData(i);
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
		for(int i = -0; i < STAGEDATA_MODEMAX; i++)
			free(container[i].head);
	}
}

/**************************************
�X�V����
***************************************/
int UpdateStageData(STAGE_DATA **out, DWORD currentFrame, int mode)
{
	int cntData = 0;
	CONTAINER_STAGEDATA *ptr = &container[mode];
	while (ptr->current < ptr->dataMax && ptr->head[ptr->current].emmittFrame == currentFrame)
	{
		if (cntData == 0)
			*out = &ptr->head[ptr->current];
		ptr->current++;
		cntData++;
	}


	return cntData;
}

/**************************************
�X�e�[�W�f�[�^�ǂݍ��ݏ���
***************************************/
bool LoadStageData(int mode)
{
	FILE *fp = NULL;
	CONTAINER_STAGEDATA *entity = &container[mode];

	//�t�@�C���ǂݍ���
	fp = fopen(FilePath[mode], "r");
	if (fp == NULL)
		return false;

	//�������m��
	entity->dataMax = 0;
	int loadRes = fscanf(fp, "%d", &entity->dataMax);

	if (loadRes == EOF)
		return false;

	entity->head = (STAGE_DATA*)malloc(sizeof(STAGE_DATA) * entity->dataMax);
	ZeroMemory(entity->head, sizeof(STAGE_DATA) * entity->dataMax);

	//�f�[�^�ǂݍ���
	STAGE_DATA *ptr = entity->head;
	int sumEmmittFrame = 0;
	for (int i = 0; i < entity->dataMax; i++, ptr++)
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

/**************************************
�X�e�[�W�f�[�^���I����Ă��邩�ǂ���
***************************************/
bool IsStageEnd(void)
{
	bool res = true;
	for (int i = 0; i < STAGEDATA_MODEMAX; i++)
	{
		if (container[i].current != container[i].dataMax)
		{
			res = false;
			break;
		}
}
	return res;
}

/**************************************
�{�[�i�X�^�C���v���[���p�̃f�[�^�ǂݍ���
***************************************/
void LoadBonusPresenData(void)
{
	CONTAINER_STAGEDATA *entity = &container[0];

	//���Ƀf�[�^���ǂݍ��܂�Ă����珉����
	if (entity->head != NULL)
	{
		free(entity->head);
		ZeroMemory(entity->head, sizeof(STAGE_DATA) * entity->dataMax);
	}

	FILE *fp = NULL;
	//�t�@�C���ǂݍ���
	fp = fopen("data/STAGE/StageDataBonus.dat", "r");
	if (fp == NULL)
		return;

	//�������m��
	entity->dataMax = 0;
	int loadRes = fscanf(fp, "%d", &entity->dataMax);

	if (loadRes == EOF)
		return;

	entity->head = (STAGE_DATA*)malloc(sizeof(STAGE_DATA) * entity->dataMax);
	ZeroMemory(entity->head, sizeof(STAGE_DATA) * entity->dataMax);

	//�f�[�^�ǂݍ���
	STAGE_DATA *ptr = entity->head;
	int sumEmmittFrame = 0;
	for (int i = 0; i < entity->dataMax; i++, ptr++)
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
}