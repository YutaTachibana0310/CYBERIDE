//=========================================================
//
//�r���f�B���O�t�B�[���h�w�b�_�mbuildingField.h�n
//Author�FGP11A341 21 ���ԗY��
//=========================================================
#ifndef _BUILDINGFIELD_H_
#define _BUILDINGFIELD_H_

#include "main.h"

/*********************************************************
�\���̒�`
*********************************************************/
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 vtxBuff;	//���_�o�b�t�@
	D3DXVECTOR3 pos;					//�t�B�[���h�̃��[���h���W
	float *heightMap;					//���_�̍����̃}�b�v
}BUILDINGFIELD;

/************************************************************
�v���g�^�C�v�錾
*************************************************************/
void InitDesertField(int num);
void UninitDesertField(void);
void UpdateDesertField(void);
void DrawDesertField(void);

#endif