//=====================================
//
//���m�g�[������[monotone.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "monotone.h"
#include "postEffectManager.h"
#include "Easing.h"

#include "debugWindow.h"

/**************************************
�}�N����`
***************************************/
#define MONOTONE_EFFECT_NAME		"data/EFFECT/monotone.fx"
#define MONOTONE_FADE_DURATION		(30)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static LPD3DXEFFECT effect;
static D3DXHANDLE tech, power;
static bool active = false;
static int cntFrame;

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitMonotone(int num)
{
	static bool initialized = false;

	if (initialized)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXCreateEffectFromFile(pDevice, MONOTONE_EFFECT_NAME, 0, 0, 0, 0, &effect, 0);

	effect->GetTechniqueByName("tech");
	effect->SetTechnique(tech);

	power = effect->GetParameterByName(NULL, STR(power));

	initialized = true;

	active = false;
	SetPostEffectUse(EFFECT_MONOTONE,  active);
}

/**************************************
�I������
***************************************/
void UninitMonotone(int num)
{
	if (num == 0)
	{
		SAFE_RELEASE(effect);
	}
}

/**************************************
�X�V����
***************************************/
void UpdateMonotone(void)
{
	if (!active)
		return;

	cntFrame++;
	float t = (float)cntFrame / (float)MONOTONE_FADE_DURATION;
	float setPower = EaseLinear(t, 0.0f, 1.0f);
	effect->SetFloat(power, setPower);
}

/**************************************
�`�揈��
***************************************/
void DrawMonotone(void)
{
	if (!active)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	effect->Begin(NULL, 0);
	effect->BeginPass(0);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	effect->EndPass();
	effect->End();
}

/**************************************
�Z�b�g����
***************************************/
void SetMonotoneEffect(bool state)
{
	active = state;
	SetPostEffectUse(EFFECT_MONOTONE, state);
}
