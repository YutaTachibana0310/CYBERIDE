//=====================================
//
//�o�g���R���g���[������[battleController.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "battleController.h"
#include "fuzzyLogic.h"
#include "playerModel.h"
#include "debugWindow.h"
#include "battleCamera.h"
#include "enemyManager.h"
#include "bonusTelop.h"

#include "cubeObject.h"
/**************************************
�}�N����`
***************************************/
#define BATTLE_SPACE_DIVIDE_NUM			(4)					//�G�l�~�[�����͈͕�����
#define BATTLE_SPACE_LEFT_BORDER		(-300.0f)			//�G�l�~�[�̐������W�͈́i���[�j
#define BATTLE_SPACE_TOP_BORDER			(300.0f)			//�G�l�~�[�̐������W�͈́i��[�j
#define BATTLE_SPACE_RIGHT_BORDER		(300.0f)			//�G�l�~�[�̐������W�͈́i�E�[�j
#define BATTLE_SPACE_BOTTOM_BORDER		(-300.0f)			//�G�l�~�[�̐������W�͈́i���[�j
#define BATTLE_EMITTPOS_Z				(2500.0f)			//�G�l�~�[�������WZ�l

#define BATTLE_FUZZY_NEAR_BORDER		(0.0f)				//�����Ɋւ���t�@�W�B���_�̂������l1
#define BATTLE_FUZZY_MIDDLE_BORDER		(SCREEN_HEIGHT)		//�����Ɋւ���t�@�W�B���_�̂������l2
#define BATTLE_FUZZY_FAR_BORDER			(SCREEN_WIDTH*2.5f)	//�����Ɋւ���t�@�W�B���_�̂������l3
#define BATTLE_FUZZY_RECENTLY_BORDER	(120.0f)			//���ԂɊւ���t�@�W�B���_�̂������l1
#define BATTLE_FUZZY_LATELY_BORDER		(1200.0f)			//���ԂɊւ���t�@�W�B���_�̂������l2

#define BATTLE_SPACE_MAX (BATTLE_SPACE_DIVIDE_NUM*BATTLE_SPACE_DIVIDE_NUM)	//�������ꂽ��Ԃ̑���

#define BATTLE_BONUS_DURATION			(570)				//�{�[�i�X�^�C������		
#define BATTLE_BONUS_START				(30)				//�{�[�i�X�^�C���̃X�^�[�g�I�t�Z�b�g

#define BATTLE_CUBEEMMITT_INTERBAL		(120)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static D3DXVECTOR2 enemyEmittPos[BATTLE_SPACE_MAX];	//�G�l�~�[�������W
static DWORD lastEmittFrame[BATTLE_SPACE_MAX];		//�e��ԂɃG�l�~�[���������ꂽ�Ō�̃t���[��
static DWORD cntFrame;								//�t���[���J�E���g
static D3DXVECTOR3 checkPos[BATTLE_SPACE_MAX];		//������W
static D3DXVECTOR3 emmittPos[BATTLE_SPACE_MAX];		//�G�l�~�[�����ʒu
static DWORD bonusStartFrame;
static bool isBonusTime;

/**************************************
�v���g�^�C�v�錾
***************************************/
void EmmittOnBonusTime(void);
void EmmittOnNormalTime(void);

/**************************************
����������
***************************************/
void InitBattleController(int num)
{
	if (num == 0)
	{
		//�����͈͂𕪊����ăG�l�~�[�̐������W���v�Z
		float spaceUnitWidth = SCREEN_WIDTH / BATTLE_SPACE_DIVIDE_NUM;
		float spaceUnitHeight = SCREEN_HEIGHT / BATTLE_SPACE_DIVIDE_NUM;

		for (int y = 0; y < BATTLE_SPACE_DIVIDE_NUM; y++)
		{
			for (int x = 0; x < BATTLE_SPACE_DIVIDE_NUM; x++)
			{
				checkPos[y * BATTLE_SPACE_DIVIDE_NUM + x].x = spaceUnitWidth * (x + 0.5f);
				checkPos[y * BATTLE_SPACE_DIVIDE_NUM + x].y = spaceUnitHeight * (y + 0.5f);

				emmittPos[y * BATTLE_SPACE_DIVIDE_NUM + x].x = (BATTLE_SPACE_RIGHT_BORDER - BATTLE_SPACE_LEFT_BORDER) / BATTLE_SPACE_DIVIDE_NUM * (x + 0.5f) + BATTLE_SPACE_LEFT_BORDER;
				emmittPos[y * BATTLE_SPACE_DIVIDE_NUM + x].y = (BATTLE_SPACE_TOP_BORDER - BATTLE_SPACE_BOTTOM_BORDER) / BATTLE_SPACE_DIVIDE_NUM * (y + 0.5f) + BATTLE_SPACE_BOTTOM_BORDER;
				emmittPos[y * BATTLE_SPACE_DIVIDE_NUM + x].z = 5000.0f;
			}
		}
	}

	//�e�p�����[�^��������
	cntFrame = 0;
	for (int i = 0; i < BATTLE_SPACE_MAX; i++)
	{
		lastEmittFrame[i] = 0xffffffff;
	}

	isBonusTime = false;
}

/**************************************
�I������
***************************************/
void UninitBattleController(int num)
{

}

/**************************************
�X�V����
***************************************/
void UpdateBattleController(void)
{
	cntFrame++;

	if (cntFrame == 1)
		EmittHardCubeObject(1, &D3DXVECTOR3(50.0f, 50.0f, -100.0f));
		//EmmittBonusCube(&D3DXVECTOR3(0.0f, 0.0f, -100.0f));

	if(isBonusTime)
		EmmittOnBonusTime();
	else
		EmmittOnNormalTime();
}

/**************************************
�{�[�i�X�^�C���J�n����
***************************************/
void StartBonusTime(void)
{
	if (isBonusTime)
		return;

	bonusStartFrame = cntFrame;// +BATTLE_BONUS_START;
	isBonusTime = true;
	StartBonusTelopAnim(true);
}

/**************************************
�{�[�i�X�^�C�����̃L���[�u��������
***************************************/
void EmmittOnBonusTime(void)
{
	static float posZ = 3000.0f;

	for (int i = 0; i < 10; i++)
	{
		D3DXVECTOR3 emmittPos;
		emmittPos.x = RandomRangef(-200.0f, 200.0f);
		emmittPos.y = RandomRangef(-200.0f, 200.0f);
		emmittPos.z = posZ;

		EmmittCubeObject(1, &emmittPos, 20.0f);
	}

	if ((int)(cntFrame - bonusStartFrame) > BATTLE_BONUS_DURATION)
	{
		isBonusTime = false;
	}
}

/**************************************
�ʏ펞�̃L���[�u��������
***************************************/
void EmmittOnNormalTime(void)
{
	static float valueLength[BATTLE_SPACE_MAX];
	static float valueTime[BATTLE_SPACE_MAX];
	static float fuzzyValue[BATTLE_SPACE_MAX];
	static int decidedPos;

	D3DXVECTOR3 playerPos;
	float maxValue = -9999.9f;

	D3DXVec3TransformCoord(&playerPos, &GetPlayerAdr(0)->pos, &GetBattleCameraView());
	D3DXVec3TransformCoord(&playerPos, &playerPos, &GetBattleCameraProjection());
	TranslateViewPort(&playerPos, &playerPos);

	//�e�������W�ɑ΂��ăt�@�W�B���_�ŏd�݂��v�Z
	for (int i = 0; i < BATTLE_SPACE_MAX; i++)
	{
		float length = D3DXVec2Length(&(D3DXVECTOR2)(playerPos - checkPos[i]));
		float elapsedTime = (float)(cntFrame - lastEmittFrame[i]);

		valueLength[i] = fFuzzyTriangle(length, BATTLE_FUZZY_NEAR_BORDER, BATTLE_FUZZY_MIDDLE_BORDER, BATTLE_FUZZY_FAR_BORDER);
		valueTime[i] = fFuzzyRightGrade(elapsedTime, BATTLE_FUZZY_RECENTLY_BORDER, BATTLE_FUZZY_LATELY_BORDER);
		fuzzyValue[i] = valueLength[i] * valueTime[i];
		if (maxValue < fuzzyValue[i])
		{
			decidedPos = i;
			maxValue = fuzzyValue[i];
		}
	}

	//�d�݂���ԑ傫���������W�փG�l�~�[�𐶐�
	if (cntFrame % BATTLE_CUBEEMMITT_INTERBAL == 0)
	{
		lastEmittFrame[decidedPos] = cntFrame;
		EmmittCubeObject(10, &emmittPos[decidedPos], 5.0f);
	}

	//�f�o�b�O���\��
	{
		ImGui::Begin("BattleController");

		ImGui::Text("PlayerPos : %f, %f", playerPos.x, playerPos.y);

		ImGui::NewLine();
		ImGui::Text("Length");
		for (int i = 0; i < BATTLE_SPACE_MAX; i++)
		{
			if (i % BATTLE_SPACE_DIVIDE_NUM != 0)
				ImGui::SameLine();
			ImGui::Text("%4f ", valueLength[i]);
		}
		for (int i = 0; i < BATTLE_SPACE_DIVIDE_NUM; i++)
			ImGui::PlotHistogram("", &valueLength[i * BATTLE_SPACE_DIVIDE_NUM], BATTLE_SPACE_DIVIDE_NUM);

		ImGui::NewLine();
		ImGui::Text("Time");
		for (int i = 0; i < BATTLE_SPACE_MAX; i++)
		{
			if (i % BATTLE_SPACE_DIVIDE_NUM != 0)
				ImGui::SameLine();
			ImGui::Text("%4f ", valueTime[i]);
		}
		for (int i = 0; i < BATTLE_SPACE_DIVIDE_NUM; i++)
			ImGui::PlotHistogram("", &valueTime[i * BATTLE_SPACE_DIVIDE_NUM], BATTLE_SPACE_DIVIDE_NUM);

		ImGui::NewLine();
		for (int i = 0; i < BATTLE_SPACE_DIVIDE_NUM; i++)
			ImGui::PlotHistogram("FuzzyValues",
				&fuzzyValue[i * BATTLE_SPACE_DIVIDE_NUM],
				BATTLE_SPACE_DIVIDE_NUM);

		ImGui::NewLine();
		if (ImGui::Button("Init Cube"))
		{
			UninitCubeObject(1);
		}
		if (ImGui::Button("Start Bonus"))
		{
			StartBonusTime();
		}
		ImGui::End();

	}
}

/**************************************
�{�[�i�X�^�C�����ǂ���
***************************************/
bool IsBonusTime(void)
{
	return isBonusTime;
}