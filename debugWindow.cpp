//=====================================
//
//テンプレート処理[template.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "debugWindow.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"
#include "input.h"

/**************************************
マクロ定義
***************************************/
#define INTERBAL_GETTIMER		(20)
//#define USE_DEBUGFUNC _DEBUG

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/
LARGE_INTEGER timeCountBegin;
static unsigned int cntFrame = 0;

/**************************************
プロトタイプ宣言
***************************************/
IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

/**************************************
デバッグウィンドウ用コールバック
***************************************/
LRESULT DebugWindPrcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
#ifdef USE_DEBUGFUNC
	return ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam);
#else
	return S_OK;
#endif
}

/**************************************
初期化処理
***************************************/
void InitDebugWindow(HWND hWnd, LPDIRECT3DDEVICE9 pDevice)
{
#ifdef USE_DEBUGFUNC
	ImGui::CreateContext();

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(pDevice);

	ImGui::StyleColorsDark();
#endif
}

/**************************************
終了処理
***************************************/
void UninitDebugWindow(int num)
{
#ifdef USE_DEBUGFUNC
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
#endif
}

/**************************************
更新処理
***************************************/
void UpdateDebugWindow(void)
{
#ifdef USE_DEBUGFUNC
	ImGui_ImplWin32_NewFrame();
	ImGui_ImplDX9_NewFrame();
	ImGui::NewFrame();

	cntFrame++;
#endif
}

/**************************************
描画処理
***************************************/
void DrawDebugWindow(void)
{
#ifdef USE_DEBUGFUNC
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
#endif
}

/**************************************
高解像度タイマーでの計測開始処理
***************************************/
void BeginTimerCount(void)
{
#ifdef USE_DEBUGFUNC
	QueryPerformanceCounter(&timeCountBegin);
#endif
}

/**************************************
計測開始からの経過時間[単位：msec]
***************************************/
double GetProgressTimerCount(void)
{
#ifdef USE_DEBUGFUNC
	//タイマーの周波数を取得
	LARGE_INTEGER frequencyTimer;
	QueryPerformanceFrequency(&frequencyTimer);

	//カウント取得
	LARGE_INTEGER timeCurrent;
	QueryPerformanceCounter(&timeCurrent);

	//計測開始からの経過時間[msec]を計算
	LONGLONG span = timeCurrent.QuadPart - timeCountBegin.QuadPart;
	double msec = (double)span * 1000 / (double)frequencyTimer.QuadPart;

	return msec;
#else 
	return 0.0f;
#endif
}

/**************************************
タイマーカウント取得処理（20フレームおきに動作）
***************************************/
void GetTimerCount(LARGE_INTEGER *ptr)
{
#ifdef	USE_DEBUGFUNC
	if (cntFrame % INTERBAL_GETTIMER != 0)
		return;

	QueryPerformanceCounter(ptr);
#endif
}

/**************************************
経過時間取得処理[msec]
***************************************/
double CalcProgressTime(LARGE_INTEGER start, LARGE_INTEGER end)
{
#ifdef USE_DEBUGFUNC
	//タイマーの周波数取得
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	//経過時間を計算
	LONGLONG span = end.QuadPart - start.QuadPart;
	double msec = (double)span * 1000.0f / (double)frequency.QuadPart;

	return msec;
#else
	return 0.0f;
#endif
}

/*************************************
デバッグウィンドウ開始処理
***************************************/
void BeginDebugWindow(const char *label)
{
#ifdef USE_DEBUGFUNC
	ImGui::Begin(label);
#endif
}

/*************************************
デバッグウィンドウ終了処理
***************************************/
void EndDebugWindow(const char *label)
{
#ifdef USE_DEBUGFUNC
	ImGui::End();
#endif
}

/*************************************
デバッグテキスト表示処理
***************************************/
void DebugText(const char *str, ...)
{
#ifdef USE_DEBUGFUNC
	va_list ap;
	va_start(ap, str);
	ImGui::TextV(str, ap);
	//ImGui::Text(str, ap);
	va_end(ap);
#endif
}

/*************************************
デバッグボタン表示処理
***************************************/
bool DebugButton(const char *label)
{
#ifdef USE_DEBUGFUNC
	return ImGui::Button(label);
#else
	return false;
#endif
}

/*************************************
デバッグスライダー処理
***************************************/
bool DebugSliderFloat(const char *label, float *adr, float min, float max)
{
#ifdef USE_DEBUGFUNC
	return ImGui::SliderFloat(label, adr, min, max);

#else
	return false;
#endif
}

/*************************************
デバッグカラーピッカー処理
***************************************/
void DebugColorEditor(const char *label, float array[4])
{
#ifdef USE_DEBUGFUNC
	ImGui::ColorEdit4(label, array);
#endif
}

/*************************************
デバッグウィンドウ改行処理
***************************************/
void DebugNewLine(void)
{
#ifdef USE_DEBUGFUNC
	ImGui::NewLine();
#endif
}

/*************************************
デバッグウィンドウ連続行処理
***************************************/
void DebugSameLine(void)
{
#ifdef USE_DEBUGFUNC
	ImGui::SameLine();
#endif
}

/*************************************
ツリー構造展開処理
***************************************/
void DebugTreeExpansion(bool isOpen)
{
#ifdef USE_DEBUGFUNC
	ImGui::SetNextTreeNodeOpen(isOpen, ImGuiSetCond_Once);
#endif
}

/*************************************
ツリー構造プッシュ処理
***************************************/
bool DebugTreePush(const char *label)
{
#ifdef USE_DEBUGFUNC
	return ImGui::TreeNode(label);
#else
	return  false;
#endif
}

/*************************************
ツリー構造ポップ処理
***************************************/
void DebugTreePop(void)
{
#ifdef USE_DEBUGFUNC
	ImGui::TreePop();
#endif
}

/*************************************
プログレスバー処理
***************************************/
void DebugProgressBar(float fraction, const char* label, D3DXVECTOR2 size)
{
#ifdef USE_DEBUGFUNC
	ImGui::ProgressBar(fraction, ImVec2(size.x, size.y), label);
#endif
}

/*************************************
3次元ベクトル入力処理
***************************************/
void DebugInputVector3(const char* label, D3DXVECTOR3 *vec)
{
#ifdef USE_DEBUGFUNC
	ImGui::InputFloat3(label, (float*)vec);
#endif
}

/*************************************
2次元ベクトル入力処理
***************************************/
void DebugInputVector2(const char* label, D3DXVECTOR2 *vec)
{
#ifdef USE_DEBUGFUNC
	ImGui::InputFloat2(label, (float*)vec);
#endif
}

/*************************************
float型入力処理
***************************************/
void DebugInputFloat(const char* label, float *var)
{
#ifdef USE_DEBUGFUNC
	ImGui::InputFloat(label, var);
#endif
}