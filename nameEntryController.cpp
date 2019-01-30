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

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitNameEntryController(int num)
{
	scoreIndex = 0;
	nameIndex = 0;
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
	data[scoreIndex].playerName[nameIndex] = WrapAround(0, CHARCHIP_END, data[scoreIndex].playerName[nameIndex] + inputY);
}

/**************************************
�`�揈��
***************************************/
void DrawNameEntryController(void)
{

}
