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
/**************************************
�v���g�^�C�v�錾
***************************************/

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
	static float valueLength[BATTLE_SPACE_MAX];
	static float valueTime[BATTLE_SPACE_MAX];
	static float fuzzyValue[BATTLE_SPACE_MAX];
	static int decidedPos;

	D3DXVECTOR3 playerPos;
	float maxValue = -9999.9f;

	cntFrame++;

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
	if (cntFrame % 10 == 0)
	{
		lastEmittFrame[decidedPos] = cntFrame;
		EmmittCubeObject(10, &emmittPos[decidedPos]);
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

		ImGui::End();

	}
}

/**************************************
�`�揈��
***************************************/
void DrawBattleController(void)
{

}
