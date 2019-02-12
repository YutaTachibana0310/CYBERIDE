//=====================================
//
//�o�g���V�[��GUI����[BattleSceneGUI.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "lockonGUI.h"
#include "scoreGUI.h"
#include "hpGUI.h"
#include "scoreMagniNumGUI.h"
#include "lockonLevelGUI.h"
#include "lockonNumGUI.h"
#include "scoreMagniGauge.h"
#include "powerUpTelop.h"
#include "bonusTelop.h"
#include "bonusTimeGUI.h"
#include "bonusPositinoTelop.h"
#include "cautionTelop.h"
#include "Easing.h"
#include "numGUI.h"
#include "playerModel.h"

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
void OnEnterBattleSceneGUI(void)
{
	InitLockonGUI(0);
	InitScoreGUI(0);
	InitHpGUI(0);
	InitScoreMagniNumGUI(0);
	InitLockonLevelGUI(0);
	InitLockonNumGUI(0);
	InitScoreMagniGauge(0);
	InitPowerUpTelop(0);
	InitBonusTelop(0);
	InitBonusTimeGUI(0);
	InitBonusPositionTelop(0);
	InitCautionTelop(0);
}

/**************************************
�X�V����
***************************************/
void OnUpdateBattleSceneGUI(void)
{
	UpdateLockonGUI();
	UpdateScoreGUI();
	UpdateHpGUI();
	UpdateScoreMagniNumGUI();
	UpdateLockonLevelGUI();
	UpdateLockonNumGUI();
	UpdateScoreMagniGauge();
	UpdatePowerUpTelop();
	UpdateBonusTelop();
	UpdateBonusTimeGUI();
	UpdateBonusPositionTelop();
	UpdateCautionTelop();
}

/**************************************
�`�揈��
***************************************/
void OnDrawBattleSceneGUI(void)
{
	PLAYERMODEL *player = GetPlayerAdr(0);
	D3DXVECTOR3 screenPos;
	D3DXMATRIX view, proj;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->GetTransform(D3DTS_VIEW, &view);
	pDevice->GetTransform(D3DTS_PROJECTION, &proj);

	D3DXVec3TransformCoord(&screenPos, &player->pos, &view);
	D3DXVec3TransformCoord(&screenPos, &screenPos, &proj);
	TranslateViewPort(&screenPos, &screenPos);

	float alpha = EaseLinear((screenPos.x - 100.0f) / 600.0f, 0.2f, 1.0f);

	DrawLockonGUI();

	NumGUI::GetInstance()->SetAlpha(alpha);
	DrawScoreGUI(alpha);
	DrawHpGUI(alpha);
	DrawScoreMagniNumGUI(alpha);
	DrawLockonLevelGUI(alpha);
	DrawLockonNumGUI(alpha);
	DrawScoreMagniGauge(alpha);
	NumGUI::GetInstance()->SetAlpha(1.0f);

	DrawPowerUpTelop();
	DrawBonusTelop();
	DrawBonusTimeGUI();
	DrawBonusPositionTelop();
	DrawCautionTelop();
}