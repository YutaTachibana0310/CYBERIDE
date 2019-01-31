//=====================================
//
//�l�[���G���g���[���͏���[nameEntryInput.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "nameEntryController.h"
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

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
���ꏈ��
***************************************/
void OnEnterNameEntryInput(NAMEENTRY *entity)
{
	if (entity->highScore->playerName[entity->nameIndex] == CHARCHIP_NONE)
		entity->highScore->playerName[entity->nameIndex] = CHARCHIP_A;
}

/**************************************
�X�V����
***************************************/
void OnUpdateNameEntryInput(NAMEENTRY *entity)
{
	//���O��I��
	int inputY = GetVerticalInputRepeat();
	int *chara = &entity->highScore->playerName[entity->nameIndex];
	*chara = WrapAround(CHARCHIP_A, CHARCHIP_QUESTION, *chara - inputY);

	//������������o
	int inputX = GetHorizontalInputRepeat();
	entity->nameIndex = Clamp(0, DATACONTAINER_PLAYERNAME_MAX, entity->nameIndex + inputX);

	//�J�[�\�����Z�b�g
	SetNameEntryCursor(entity->scoreIndex, entity->nameIndex);

	//��ԑJ��
	if (inputX == 0)
		return;

	if (entity->nameIndex == DATACONTAINER_PLAYERNAME_MAX)
	{
		SetStateNameEntryCursor(false);
		ChangeStateNameEntryController(NAMEENTRY_END);
	}
	else
	{
		ChangeStateNameEntryController(NAMEENTRY_INPUT);
	}
}
