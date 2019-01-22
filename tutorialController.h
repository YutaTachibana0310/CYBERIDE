//=====================================
//
//�`���[�g���A���R���g���[���[�w�b�_[tutorialController.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _TUTORIALCONTROLLER_H_
#define _TUTORIALCONTROLLER_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/
enum TUTORIAL_INDEX {
	TutorialMove,
	TutorialLockon,
	TutorialHomingAttack,
	TutorialHardCube,
	TutorialBonusCube,
	TutorialBonusTime,
	TutorialEnd,
	TutorialIndexMax
};
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitTutorialController(int num);
void UninitTutorialController(int num);
void UpdateTutorialController(void);
void DrawTutorialController(void);
void ChangeStateTutorialController(TUTORIAL_INDEX next);

//���ꏈ��
void OnEnterTutorialMove(void);
void OnEnterTutorialLockon(void);
void OnEnterTutorialHomingAttack(void);
void OnEnterTutorialHardCube(void);
void OnEnterTutorialBonusCube(void);
void OnEnterTutorialBonusTime(void);
void OnEnterTutorialEnd(void);

//�X�V����
void OnUpdateTutorialMove(void);
void OnUpdateTutorialLockon(void);
void OnUpdateTutorialHomingAttack(void);
void OnUpdateTutorialHardCube(void);
void OnUpdateTutorialBonusCube(void);
void OnUpdateTutorialBonusTime(void);
void OnUpdateTutorialEnd(void);

//�`�揈��
void OnDrawTutorialMove(LPDIRECT3DTEXTURE9 tex);
void OnDrawTutorialLockon(LPDIRECT3DTEXTURE9 tex);
void OnDrawTutorialHomingAttack(LPDIRECT3DTEXTURE9 tex);
void OnDrawTutorialHardCube(LPDIRECT3DTEXTURE9 tex);
void OnDrawTutorialBonusCube(LPDIRECT3DTEXTURE9 tex);
void OnDrawTutorialBonusTime(LPDIRECT3DTEXTURE9 tex);
void OnDrawTutorialEnd(LPDIRECT3DTEXTURE9 tex);
#endif