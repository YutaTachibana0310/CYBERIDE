//=====================================
//
//�f�[�^�R���e�i�w�b�_[dataContainer.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _DATACONTAINER_H_
#define _DATACONTAINER_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/
#define DATACONTAINER_SHOTLEVEL_MAX		(4)		//�V���b�g���x���ő�l
#define DATACONTAINER_LOCKLEVEL_MAX		(3)		//���b�N�I�����x���ő�l
#define DATACONTAINER_PLAYERNAME_MAX	(5)		//�v���C���[���ő啶����
#define DATACONTAINER_HIGHSCORE_MAX		(10)	//�n�C�X�R�A�̕ۑ���
/**************************************
�\���̒�`
***************************************/
typedef struct {
	int score;
	char playerName[DATACONTAINER_PLAYERNAME_MAX];
}DATA_HIGHSCRE;

/**************************************
�v���g�^�C�v�錾
***************************************/
void InitDataContainer(int num);

void AddScore(int addValue);
void SetPowerUp(void);
void InitPlayerHP(void);

int GetShotLevel(void);
int GetLockonLevel(void);
int GetCurrentScore(void);
DATA_HIGHSCRE* GetHighScore(void);
int GetLockonMax(void);

float GetPlayerHP(void);
void AddPlayerHP(float value);

bool LoadHighScoreData(void);
bool SaveHighScoreData(void);

#endif