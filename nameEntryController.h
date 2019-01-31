//=====================================
//
//�l�[���G���g���[�R���g���[���w�b�_[nameEntryController.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _NAMEENTYCONTROLLER_H_
#define _NAMEENTYCONTROLLER_H_

#include "main.h"
#include "dataContainer.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/
typedef struct {
	int scoreIndex;
	int nameIndex;
	DATA_HIGHSCRE *highScore = NULL;
	int currentState;
	int prevState;
}NAMEENTRY;

enum NAMEENTRY_STATE {
	NAMEENTRY_INPUT,
	NAMEENTRY_END,
	NAMEENTRY_STATEMAX
};
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitNameEntryController(int num);
void UninitNameEntryController(int num);
void UpdateNameEntryController(void);
void DrawNameEntryController(void);
void ChangeStateNameEntryController(int next);

//���ꏈ��
void OnEnterNameEntryInput(NAMEENTRY *entity);
void OnEnterNameEntryEnd(NAMEENTRY *entity);

//�X�V����
void OnUpdateNameEntryInput(NAMEENTRY *entity);
void OnUpdateNameEntryEnd(NAMEENTRY *entity);
#endif