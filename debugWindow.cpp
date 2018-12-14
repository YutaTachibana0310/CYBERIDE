//=====================================
//
//�e���v���[�g����[template.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "debugWindow.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
LARGE_INTEGER timeCountBegin;

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitDebugWindow(HWND hWnd, LPDIRECT3DDEVICE9 pDevice)
{
	ImGui::CreateContext();

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(pDevice);

	ImGui::StyleColorsDark();
}

/**************************************
�I������
***************************************/
void UninitDebugWindow(int num)
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
}

/**************************************
�X�V����
***************************************/
void UpdateDebugWindow()
{
	ImGui_ImplWin32_NewFrame();
	ImGui_ImplDX9_NewFrame();
	ImGui::NewFrame();
}

/**************************************
�`�揈��
***************************************/
void DrawDebugWindow(void)
{
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

/**************************************
���𑜓x�^�C�}�[�ł̌v���J�n����
***************************************/
void BeginTimerCount(void)
{
	QueryPerformanceCounter(&timeCountBegin);
}

/**************************************
�v���J�n����̌o�ߎ���[�P�ʁFmsec]
***************************************/
double GetProgressTimerCount(void)
{
	//�^�C�}�[�̎��g�����擾
	LARGE_INTEGER frequencyTimer;
	QueryPerformanceFrequency(&frequencyTimer);

	//�J�E���g�擾
	LARGE_INTEGER timeCurrent;
	QueryPerformanceCounter(&timeCurrent);

	//�v���J�n����̌o�ߎ���[msec]���v�Z
	LONGLONG span = timeCurrent.QuadPart - timeCountBegin.QuadPart;
	double msec = (double)span * 1000 / (double)frequencyTimer.QuadPart;

	return msec;
}
