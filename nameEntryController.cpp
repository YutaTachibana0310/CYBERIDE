//=====================================
//
//�l�[���G���g���[�R���g���[������[nameEntryController.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "nameEntryController.h"
#include "dataContainer.h"
#include "rankingName.h"
#include "input.h"
#include "nameEntryCursor.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static unsigned int scoreIndex;
static unsigned int nameIndex;
static DATA_HIGHSCRE *highScore = NULL;

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitNameEntryController(int num)
{
	scoreIndex = 1;
	nameIndex = 0;

	highScore = GetHighScore(scoreIndex);
	for (int i = 0; i < DATACONTAINER_PLAYERNAME_MAX; i++)
	{
		highScore->playerName[i] = 31;
	}
}

/**************************************
�I������
***************************************/
void UninitNameEntryController(int num)
{

}

/**************************************
�X�V����
***************************************/
void UpdateNameEntryController(void)
{
	DATA_HIGHSCRE *data = GetHighScore();
	int inputX = GetHorizontalInputRepeat();
	int inputY = GetVerticalInputRepeat();

	nameIndex = Clamp(0, DATACONTAINER_PLAYERNAME_MAX - 1, nameIndex + inputX);

	if(highScore->playerName[nameIndex] == 31 )
		
	if(highScore->playerName[nameIndex] != 31)
		highScore->playerName[nameIndex] = WrapAround(0, CHARCHIP_END, highScore->playerName[nameIndex] - inputY);

	SetNameEntryCursor(scoreIndex, nameIndex);
}

/**************************************
�`�揈��
***************************************/
void DrawNameEntryController(void)
{

}
