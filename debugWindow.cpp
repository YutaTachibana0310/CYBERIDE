//=====================================
//
//�e���v���[�g����[template.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "debugWindow.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"
#include "input.h"

/**************************************
�}�N����`
***************************************/
#define INTERBAL_GETTIMER		(20)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
LARGE_INTEGER timeCountBegin;
static unsigned int cntFrame = 0;

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
void UpdateDebugWindow(void)
{
	ImGui_ImplWin32_NewFrame();
	ImGui_ImplDX9_NewFrame();
	ImGui::NewFrame();

	cntFrame++;
}

/**************************************
�`�揈��
***************************************/
void DrawDebugWindow(void)
{
	static bool enableDraw = true;

	if (GetKeyboardTrigger(DIK_D) && GetKeyboardPress(DIK_LCONTROL))
		enableDraw = !enableDraw;

	if (!enableDraw)
	{
		ImGui::EndFrame();
		return;
	}
	
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

/**************************************
�^�C�}�[�J�E���g�擾�����i20�t���[�������ɓ���j
***************************************/
void GetTimerCount(LARGE_INTEGER *ptr)
{
	if (cntFrame % INTERBAL_GETTIMER != 0)
		return;

	QueryPerformanceCounter(ptr);
}

/**************************************
�o�ߎ��Ԏ擾����[msec]
***************************************/
double CalcProgressTime(LARGE_INTEGER start, LARGE_INTEGER end)
{
	//�^�C�}�[�̎��g���擾
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	//�o�ߎ��Ԃ��v�Z
	LONGLONG span = end.QuadPart - start.QuadPart;
	double msec = (double)span * 1000.0f / (double)frequency.QuadPart;

	return msec;
}

/*************************************
�f�o�b�O�E�B���h�E�J�n����
***************************************/
void BeginDebugWindow(const char *label)
{
	ImGui::Begin(label);
}

/*************************************
�f�o�b�O�E�B���h�E�I������
***************************************/
void EndDebugWindow(const char *label)
{
	ImGui::End();
}

/*************************************
�f�o�b�O�e�L�X�g�\������
***************************************/
void DebugText(const char *str, ...)
{
	va_list ap;
	va_start(ap, str);
	ImGui::TextV(str, ap);
	//ImGui::Text(str, ap);
	va_end(ap);
}

/*************************************
�f�o�b�O�{�^���\������
***************************************/
bool DebugButton(const char *label)
{
	return ImGui::Button(label);
}

/*************************************
�f�o�b�O�X���C�_�[����
***************************************/
void DebugSliderFloat(const char *label, float *adr, float min, float max)
{
	ImGui::SliderFloat(label, adr, min, max);
}

/*************************************
�f�o�b�O�J���[�s�b�J�[����
***************************************/
void DebugColorEditor(const char *label, float array[4])
{
	ImGui::ColorEdit4(label, array);
}

/*************************************
�f�o�b�O�E�B���h�E���s����
***************************************/
void DebugNewLine(void)
{
	ImGui::NewLine();
}

/*************************************
�c���[�\���W�J����
***************************************/
void DebugTreeExpansion(bool isOpen)
{
	ImGui::SetNextTreeNodeOpen(isOpen, ImGuiSetCond_Once);
}

/*************************************
�c���[�\���v�b�V������
***************************************/
bool DebugTreePush(const char *label)
{
	return ImGui::TreeNode(label);
}

/*************************************
�c���[�\���|�b�v����
***************************************/
void DebugTreePop(void)
{
	ImGui::TreePop();
}