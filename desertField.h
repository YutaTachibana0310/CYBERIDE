//=========================================================
//
//�����t�B�[���h�w�b�_�mdesertField.h�n
//Author�FGP11A341 21 ���ԗY��
//=========================================================
#ifndef _DESERTFIELD_H_
#define _DESERTFIELD_H_

#include "main.h"

/*********************************************************
�\���̒�`
*********************************************************/
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 vtxBuff;	//���_�o�b�t�@
	D3DXVECTOR3 pos;					//�t�B�[���h�̃��[���h���W
	float *heightMap;					//���_�̍����̃}�b�v
}DESERTFIELD;
/************************************************************
�v���g�^�C�v�錾
*************************************************************/
void InitDesertField(int num);
void UninitDesertField(void);
void UpdateDesertField(void);
void DrawDesertField(void);


#endif