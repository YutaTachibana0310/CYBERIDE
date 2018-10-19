//============================================
//
//�G�l�~�[�~�T�C���w�b�_[enemyMissile.h]
//AUthor:GP11A341 21 ���ԗY��
//
//============================================
#ifndef _ENEMYMISSILE_H_
#define _ENEMYMISSILE_H_

#include "main.h"
#include "collider.h"

/**********************************************
�}�N����`
**********************************************/

/**********************************************
�\���̒�`
**********************************************/
typedef struct
{
	bool active;					//�g�p�t���O
	D3DXVECTOR3 pos;				//���W
	D3DXQUATERNION rot;				//��]�N�H�[�^�j�I��
	D3DXVECTOR3 moveDir;			//�ړ�����
	D3DXVECTOR3 targetPos;			//�ڕW���W
	float speed;					//�ړ��X�s�[�h
	SPHERE collider;				//�����蔻��
	bool flgHoming;					//�z�[�~���O�t���O
	int cntFrame;					//�t���[���J�E���g
}ENEMYMISSILE;
/**********************************************
�v���g�^�C�v�錾
**********************************************/
void InitEnemyMissile(int num);
void UninitEnemyMissile(void);
void UpdateEnemyMissile(void);
void DrawEnemyMissile(void);
ENEMYMISSILE *GetEnemyMissileAdr(int n);

#endif