//=====================================
//
//�f�[�^�R���e�i����[dataContainer.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "dataContainer.h"
#include "powerUpTelop.h"
#include "battleController.h"
#include <stdio.h>
#include <string.h>

/**************************************
�}�N����`
***************************************/
#define DATACONTAINER_POWEUP_MAX			(7)			//�p���[�A�b�v�ő��
#define DATACONTAINER_SHOTLEVEL_MAX			(4)			//�V���b�g���x���}�b�N�X
#define DATACONTAINER_PlAYERHP_INIT			(100.0f)	//HP�����l
#define DATACONTAINER_SAVEDATA_PATH			"data/SETTINGS/data.ini"	//�n�C�X�R�A�f�[�^�̃t�@�C���p�X	
#define DATACONTAINER_MAGNICOUNT_DURATION	(120)
#define DATACONTAINER_SCOREMAGNI_MAX		(16.0f)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
//�X�R�A�֘A�p�����[�^
static int currentScore;
static DATA_HIGHSCRE highScore[DATACONTAINER_HIGHSCORE_MAX];
static float scoreMagni;

//�p���[�A�b�v�֘A�p�����[�^
static int cntPowerUp, shotLevel, lockLevel;

//�p���[�A�b�v�̂������l
static const int PowerUpBorder[DATACONTAINER_POWEUP_MAX] = {
	10000,
	50000,
	100000,
	1500000,
	2000000,
	3000000,
	(int)INFINITY
};

//�e���b�N�I�����x���ł̍ő働�b�N�I����
static const int LockonMax[DATACONTAINER_LOCKLEVEL_MAX] = {
	18, 26, 34, 42, 50, 58, 66
};

//�v���C���[HP
static float playerHP;

//�{���J�E���^
int cntFrameMagni;

/**************************************
�v���g�^�C�v�錾
***************************************/
void UpdateRanking(int index);

/**************************************
����������
***************************************/
void InitDataContainer(int num)
{

	currentScore = 0;
	LoadHighScoreData();

	cntPowerUp = 0;
	shotLevel = 0;
	lockLevel = 0;

	playerHP = DATACONTAINER_PlAYERHP_INIT;

	scoreMagni = 1.0f;

}
/**************************************
�X�V����
***************************************/
void UpdateDataContainer(void)
{
	if (cntFrameMagni < DATACONTAINER_MAGNICOUNT_DURATION)
	{
		cntFrameMagni++;
		if (cntFrameMagni == DATACONTAINER_MAGNICOUNT_DURATION)
		{
			scoreMagni = 1.0f;
		}
	}
}


/**************************************
�X�R�A�֘A����������
***************************************/
void InitScoreParameter(void)
{
	currentScore = 0;

	//highScore = 0;				//TODO:�n�C�X�R�A�̓ǂݍ��݂�ǉ�
}

/**************************************
�p���[�A�b�v�֘A����������
***************************************/
void InitPowerUpParameter(void)
{
	cntPowerUp = 0;
	shotLevel = 0;
	lockLevel = 0;
}

/**************************************
HP����������
***************************************/
void InitPlayerHP(void)
{
	playerHP = DATACONTAINER_PlAYERHP_INIT;
}

/**************************************
�X�R�A���Z����
***************************************/
void AddScore(int addValue)
{
	//�X�R�A���Z����
	currentScore += (int)(addValue * scoreMagni);

	//�p���[�A�b�v���菈��
	if (currentScore >= PowerUpBorder[cntPowerUp])
		SetPowerUp();

	//�G�N�X�e���h����

}

/**************************************
�����L���O�X�V�m�F����
***************************************/
bool CheckUpdateRanking(int *index)
{
	for (int i = 0; i < DATACONTAINER_HIGHSCORE_MAX; i++)
	{
		if (currentScore > highScore[i].score)
		{
			UpdateRanking(i);
			*index = i;
			return true;
		}
	}

	return false;
}

/**************************************
�����L���O�X�V�m�F����
***************************************/
void UpdateRanking(int index)
{
	memcpy(&highScore[index + 1], &highScore[index], sizeof(DATA_HIGHSCRE)*(DATACONTAINER_HIGHSCORE_MAX - 1 - index));
	highScore[index].score = currentScore;
}

/**************************************
�p���[�A�b�v����
***************************************/
void SetPowerUp(void)
{
	if (cntPowerUp >= DATACONTAINER_POWEUP_MAX)
		return;

	//�p���[�A�b�v�J�E���g�ǉ�
	 cntPowerUp++;

	//���b�N���x�����A�b�v
	lockLevel = Clamp(0, DATACONTAINER_LOCKLEVEL_MAX - 1, lockLevel + 1);

	//�e���b�v�\������
	StartPowerUpTelopAnimation(0);
}

/**************************************
�V���b�g���x���擾����
***************************************/
int GetShotLevel(void)
{
	return IsBonusTime() ? DATACONTAINER_SHOTLEVEL_MAX : 0;
}

/**************************************
���b�N�I�����x���擾����
***************************************/
int GetLockonLevel(void)
{
	return lockLevel;
}

/**************************************
�ő働�b�N�I���擾����
***************************************/
int GetLockonMax(void)
{
	return LockonMax[lockLevel];
}

/**************************************
�X�R�A�擾����
***************************************/
int GetCurrentScore(void)
{
	return currentScore;
}

/**************************************
�n�C�X�R�A�擾����
***************************************/
DATA_HIGHSCRE* GetHighScore(int id)
{
	return &highScore[id];
}

/**************************************
HP�擾����
***************************************/
float GetPlayerHP(void)
{
	return playerHP;
}

/**************************************
HP�����擾����
***************************************/
void AddPlayerHP(float value)
{
	playerHP += value;

	if (playerHP < 0.0f)
		playerHP = 0.0f;
}

/**************************************
�n�C�X�R�A�f�[�^�ǂݍ��ݏ���
***************************************/
bool LoadHighScoreData(void)
{
	FILE *fp = NULL;
	fp = fopen(DATACONTAINER_SAVEDATA_PATH, "rb");

	//�ǂݍ��݂Ɏ��s�����̂Ńn�C�X�R�A�����������ă��^�[��
	if (fp == NULL)
	{
		for (int i = 0; i < DATACONTAINER_HIGHSCORE_MAX; i++)
		{
			highScore[DATACONTAINER_HIGHSCORE_MAX - i - 1].score = (i + 1) * 10000;
			highScore[DATACONTAINER_HIGHSCORE_MAX - i - 1].playerName[0] = 7;
			highScore[DATACONTAINER_HIGHSCORE_MAX - i - 1].playerName[1] = 0;
			highScore[DATACONTAINER_HIGHSCORE_MAX - i - 1].playerName[2] = 11;
			highScore[DATACONTAINER_HIGHSCORE_MAX - i - 1].playerName[3] = 26;
			highScore[DATACONTAINER_HIGHSCORE_MAX - i - 1].playerName[4] = 26;
		}
		return false;
	}

	fread(&highScore, sizeof(DATA_HIGHSCRE), DATACONTAINER_HIGHSCORE_MAX, fp);
	fclose(fp);
	return true;
}

/**************************************
�n�C�X�R�A�f�[�^�ۑ�����
***************************************/
bool SaveHighScoreData(void)
{
	FILE *fp = NULL;
	fp = fopen(DATACONTAINER_SAVEDATA_PATH, "wb");

	//�ǂݍ��ݎ��s
	if (fp == NULL)
	{
		return false;
	}

	fwrite(highScore, sizeof(DATA_HIGHSCRE), DATACONTAINER_HIGHSCORE_MAX, fp);
	fclose(fp);
	return true;
}

/**************************************
���b�N�I���������ɂ��X�R�A�{���Z�b�g����
***************************************/
void SetScoreMagni(int lockonNum)
{
	//���݂̍ő働�b�N���ɑ΂��Ċ����Z�o
	float per = (float)lockonNum / (float)LockonMax[lockLevel];

	//������0����16�̊Ԃɐ��`���
	scoreMagni = per * DATACONTAINER_SCOREMAGNI_MAX;

	//�J�E���^�Z�b�g
	cntFrameMagni = 0;
}

/**************************************
���b�N�I���{���擾����
***************************************/
float GetScoreMagni(void)
{
	return scoreMagni;
}