//=====================================
//
//�f�[�^�R���e�i����[dataContainer.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "dataContainer.h"
#include "powerUpTelop.h"
#include "battleController.h"

/**************************************
�}�N����`
***************************************/
#define DATACONTAINER_POWEUP_MAX		(7)		//�p���[�A�b�v�ő��
#define DATACONTAINER_SHOTLEVEL_MAX		(4)		//�V���b�g���x���}�b�N�X
#define DATACONTAINER_PlAYERHP_INIT		(100.0f)//HP�����l
/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
//�X�R�A�֘A�p�����[�^
static int currentScore, highScore;

//�p���[�A�b�v�֘A�p�����[�^
static int cntPowerUp, shotLevel, lockLevel;

//�p���[�A�b�v�̂������l
static const int PowerUpBorder[DATACONTAINER_POWEUP_MAX] = {
	500000,
	1000000,
	1500000,
	2000000,
	2500000,
	3000000,
	(int)INFINITY
};

//�e���b�N�I�����x���ł̍ő働�b�N�I����
static const int LockonMax[DATACONTAINER_LOCKLEVEL_MAX + 1] = {
	18, 36, 48, 54
};

//�v���C���[HP
static float playerHP;

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitDataContainer(int num)
{

	currentScore = 0;
	highScore = 0;			//TODO:�n�C�X�R�A�̓ǂݍ��݂�����

	cntPowerUp = 0;
	shotLevel = 0;
	lockLevel = 0;

	playerHP = DATACONTAINER_PlAYERHP_INIT;

}

/**************************************
�X�R�A�֘A����������
***************************************/
void InitScoreParameter(void)
{
	currentScore = 0;
	highScore = 0;				//TODO:�n�C�X�R�A�̓ǂݍ��݂�ǉ�
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
	currentScore += addValue;

	//�p���[�A�b�v���菈��
	if (currentScore >= PowerUpBorder[cntPowerUp])
		SetPowerUp();

	//�G�N�X�e���h����

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

	//�V���b�g���x�������b�N���x�����A�b�v
	if (cntPowerUp % 2 == 0)
		lockLevel++;
	else
		shotLevel++;

	//�e���b�v�\������
	StartPowerUpTelopAnimation(cntPowerUp % 2);
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
int GetHighScore(void)
{
	return highScore;
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