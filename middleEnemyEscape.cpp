//=====================================
//
//�~�h���G�l�~�[��������[middleEnemyEscape.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "middleEnemyModel.h"
#include "EasingVector.h"

/**************************************
�}�N����`
***************************************/
#define MIDDLEENEMY_ESCAPE_GOALPOS	(D3DXVECTOR3(200.0f, -300.0f, -200.0f))
#define MIDDLEENEMY_ESCAPE_END		(300)

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
void EnterMiddleEnemyEscape(MIDDLEENEMY *enemy)
{
	enemy->cntFrame = 0;

	//�ړ��̎n�_�ƏI�_��ݒ�
	enemy->startPos = enemy->pos;
	enemy->goalPos = D3DXVECTOR3(0.0f, -300.0f, -500.0f);
	if (enemy->pos.x < 0)
	{
		enemy->goalPos *= -1;
	}
}

/**************************************
�X�V����
***************************************/
void UpdateMiddleEnemyEscape(MIDDLEENEMY *enemy)
{
	enemy->cntFrame++;

	float t = (float)enemy->cntFrame / MIDDLEENEMY_ESCAPE_END;
	enemy->pos = EaseInCubicVector(t, enemy->startPos, enemy->goalPos);

	if (enemy->cntFrame == MIDDLEENEMY_ESCAPE_END)
	{
		enemy->active = false;
	}
}

/**************************************
�ޏꏈ��
***************************************/
void ExitMiddleEnemyEscape(MIDDLEENEMY *enemy)
{

}