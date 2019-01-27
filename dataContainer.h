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

/**************************************
�\���̒�`
***************************************/

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
int GetHighScore(void);
int GetLockonMax(void);

float GetPlayerHP(void);
void AddPlayerHP(float value);
#endif