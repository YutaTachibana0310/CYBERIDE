//=====================================
//
//�J�����V�F�C�J�[����[cameraShaker.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "cameraShaker.h"

/**************************************
�}�N����`
***************************************/
#define CAMERASHAKER_DURATION		(30)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static int cntFrame;
static D3DXVECTOR3 cameraOffset;
static float offsetLength;
static bool active;

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitCameraShaker(int num)
{
	cntFrame = 0;
	cameraOffset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	offsetLength = 0.0f;
	active = false;
}

/**************************************
�I������
***************************************/
void UninitCameraShaker(int num)
{

}

/**************************************
�X�V����
***************************************/
void UpdateCameraShaker(void)
{
	if (!active)
		return;

	cntFrame++;

	if (cntFrame > CAMERASHAKER_DURATION)
	{
		cameraOffset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		active = false;
		return;
	}

	cameraOffset = D3DXVECTOR3(RandomRangef(-offsetLength, offsetLength), RandomRangef(-offsetLength, offsetLength), RandomRangef(-offsetLength, offsetLength));
}

/**************************************
�Z�b�g����
***************************************/
void SetCameraShaker(float length)
{
	cntFrame = 0;
	offsetLength = length;
	active = true;
}

/**************************************
�I�t�Z�b�g�l�擾����
***************************************/
D3DXVECTOR3 GetCameraOffsetValue(void)
{
	return cameraOffset;
}