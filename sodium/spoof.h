#pragma once

#include <Windows.h>
#include "import_spoof.h"
#include "string_hider.h"

#include "function_spoofer.h"

BOOL(*_GetCursorPos)(LPPOINT lpPoint) = nullptr;
BOOL(*_SetLayeredWindowAttributes)(HWND hwnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags) = nullptr;
LRESULT(*_DefWindowProc)(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam) = nullptr;
HWND(*_CreateWindowExA)(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam) = nullptr;
LONG(*_SetWindowLongA)(HWND hwnd, int nIndex, LONG dwNewLong) = nullptr;
LONG(*_GetWindowLongA)(HWND hwnd, int nIndex) = nullptr;
ATOM(*_RegisterClassExA)(const WNDCLASSEXA*) = nullptr;
int(*_GetSystemMetrics)(int nIndex) = nullptr;
HWND(*_FindWindowA)(LPCSTR lpClassName, LPCSTR lpWindowName) = nullptr;
SHORT(*_GetAsyncKeyState)(int vKey) = nullptr;
HWND(*_GetForegroundWindow)() = nullptr;
BOOL(*_MoveWindow)(HWND hWnd, int X, int Y, int nWidth, int nHeight, bool bRepaint) = nullptr;
BOOL(*_PeekMessageA)(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg) = nullptr;
BOOL(*_TranslateMessage)(const MSG* lpMsg) = nullptr;
LRESULT(*_DispatchMessageA)(const MSG* lpMsg) = nullptr;
HANDLE(*_CreateThread)(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE     lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId) = nullptr;
BOOL(*_CloseHandle)(HANDLE hObject) = nullptr;
BOOL(*_SetWindowPos)(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags) = nullptr;
BOOL(*_ShowWindow)(HWND hWnd, int nCmdShow) = nullptr;
BOOL(*_SetWindowDisplayAffinity)(HWND hWnd, DWORD dwAffinity) = nullptr;
BOOL(*_mouse_event)(DWORD, DWORD, DWORD, DWORD, ULONG_PTR) = nullptr;
BOOL(*_UpdateWindow)(HWND) = nullptr;
BOOL(*_GetClientRect)(HWND, LPRECT) = nullptr;
BOOL(*_ClientToScreen)(HWND, LPPOINT) = nullptr;

void Star_Mouse()
{
	FUNC;

	HMODULE user32 = IMPORT(LoadLibraryA).get()(HIDE("user32.dll"));
	HMODULE kernel32 = IMPORT(LoadLibraryA).get()(HIDE("Kernel32.dll"));
	HMODULE win32u = IMPORT(LoadLibraryA).get()(HIDE("win32u.dll"));
	HMODULE dwmapi = IMPORT(LoadLibraryA).get()(HIDE("dwmapi.dll"));

	if (!win32u) {
		FUNC;
		return;
	}

	if (!user32) {
		FUNC;
		return;
	}

	if (!dwmapi) {
		FUNC;
		return;
	}

	if (!kernel32) {
		FUNC;
		return;
	}

	void* NtUserInjectMouseInputAddress = (void*)IMPORT(GetProcAddress).get()(win32u, HIDE("NtUserInjectMouseInput"));
	void* GetCursorPos = (void*)IMPORT(GetProcAddress).get()(user32, HIDE("GetCursorPos"));
	void* SetLayeredWindowAttributes = (void*)IMPORT(GetProcAddress).get()(user32, HIDE("SetLayeredWindowAttributes"));
	void* DwmExtendFrameIntoClientArea = (void*)IMPORT(GetProcAddress).get()(dwmapi, HIDE("DwmExtendFrameIntoClientArea"));
	void* DefWindowProcA = (void*)IMPORT(GetProcAddress).get()(user32, HIDE("DefWindowProcA"));
	void* CreateWindowExA = (void*)IMPORT(GetProcAddress).get()(user32, HIDE("CreateWindowExA"));
	void* SetWindowLongA = (void*)IMPORT(GetProcAddress).get()(user32, HIDE("SetWindowLongA"));
	void* GetWindowLongA = (void*)IMPORT(GetProcAddress).get()(user32, HIDE("GetWindowLongA"));
	void* RegisterClassExA = (void*)IMPORT(GetProcAddress).get()(user32, HIDE("RegisterClassExA"));
	void* GetSystemMetrics = (void*)IMPORT(GetProcAddress).get()(user32, HIDE("GetSystemMetrics"));
	void* FindWindowA = (void*)IMPORT(GetProcAddress).get()(user32, HIDE("FindWindowA"));
	void* GetAsyncKeyState = (void*)IMPORT(GetProcAddress).get()(user32, HIDE("GetAsyncKeyState"));
	void* GetForegroundWindow = (void*)IMPORT(GetProcAddress).get()(user32, HIDE("GetForegroundWindow"));
	void* MoveWindow = (void*)IMPORT(GetProcAddress).get()(user32, HIDE("MoveWindow"));
	void* PeekMessageA = (void*)IMPORT(GetProcAddress).get()(user32, HIDE("PeekMessageA"));
	void* TranslateMessage = (void*)IMPORT(GetProcAddress).get()(user32, HIDE("TranslateMessage"));
	void* DispatchMessageA = (void*)IMPORT(GetProcAddress).get()(user32, HIDE("DispatchMessageA"));
	void* CreateThread = (void*)IMPORT(GetProcAddress).get()(kernel32, HIDE("CreateThread"));
	void* SetWindowPos = (void*)IMPORT(GetProcAddress).get()(user32, HIDE("SetWindowPos"));
	void* CloseHandle = (void*)IMPORT(GetProcAddress).get()(kernel32, HIDE("CloseHandle"));
	void* ShowWindow = (void*)IMPORT(GetProcAddress).get()(user32, HIDE("ShowWindow"));
	void* SetWindowDisplayAffinity = (void*)IMPORT(GetProcAddress).get()(user32, HIDE("SetWindowDisplayAffinity"));
	void* mouzeevent = (void*)IMPORT(GetProcAddress).get()(user32, HIDE("mouse_event"));
	void* updetewindow = (void*)IMPORT(GetProcAddress).get()(user32, HIDE("UpdateWindow"));
	void* clientrect = (void*)IMPORT(GetProcAddress).get()(user32, HIDE("GetClientRect"));
	void* clienttoscreen = (void*)IMPORT(GetProcAddress).get()(user32, HIDE("ClientToScreen"));

	if (!NtUserInjectMouseInputAddress) {
		FUNC;
		return;
	}

	if (!GetCursorPos) {
		FUNC;
		return;
	}

	if (!SetLayeredWindowAttributes) {
		FUNC;
		return;
	}

	if (!DwmExtendFrameIntoClientArea) {
		FUNC;
		return;
	}

	if (!DefWindowProcA) {
		FUNC;
		return;
	}

	if (!CreateWindowExA) {
		FUNC;
		return;
	}

	if (!SetWindowLongA) {
		FUNC;
		return;
	}

	if (!GetWindowLongA) {
		FUNC;
		return;
	}

	if (!RegisterClassExA) {
		FUNC;
		return;
	}

	if (!GetSystemMetrics) {
		FUNC;
		return;
	}

	if (!FindWindowA) {
		FUNC;
		return;
	}

	if (!GetAsyncKeyState) {
		FUNC;
		return;
	}

	if (!GetForegroundWindow) {
		FUNC;
		return;
	}

	if (!MoveWindow) {
		FUNC;
		return;
	}

	if (!PeekMessageA) {
		FUNC;
		return;
	}

	if (!TranslateMessage) {
		FUNC;
		return;
	}

	if (!DispatchMessageA) {
		FUNC;
		return;
	}

	if (!CreateThread) {
		FUNC;
		return;
	}

	if (!CloseHandle) {
		FUNC;
		return;
	}

	if (!SetWindowPos) {
		FUNC;
		return;
	}

	if (!ShowWindow) {
		FUNC;
		return;
	}

	if (!SetWindowDisplayAffinity) {
		FUNC;
		return;
	}

	if (!mouzeevent) {
		FUNC;
		return;
	}

	if (!updetewindow) {
		FUNC;
		return;
	}

	if (!clientrect) {
		FUNC;
		return;
	}

	if (!clienttoscreen) {
		FUNC;
		return;
	}

	*(void**)&_GetCursorPos = GetCursorPos;
	*(void**)&_SetLayeredWindowAttributes = SetLayeredWindowAttributes;
	*(void**)&_DefWindowProc = DefWindowProcA;
	*(void**)&_CreateWindowExA = CreateWindowExA;
	*(void**)&_SetWindowLongA = SetWindowLongA;
	*(void**)&_GetWindowLongA = GetWindowLongA;
	*(void**)&_RegisterClassExA = RegisterClassExA;
	*(void**)&_GetSystemMetrics = GetSystemMetrics;
	*(void**)&_FindWindowA = FindWindowA;
	*(void**)&_GetAsyncKeyState = GetAsyncKeyState;
	*(void**)&_GetForegroundWindow = GetForegroundWindow;
	*(void**)&_MoveWindow = MoveWindow;
	*(void**)&_PeekMessageA = PeekMessageA;
	*(void**)&_TranslateMessage = TranslateMessage;
	*(void**)&_DispatchMessageA = DispatchMessageA;
	*(void**)&_CreateThread = CreateThread;
	*(void**)&_CloseHandle = CloseHandle;
	*(void**)&_SetWindowPos = SetWindowPos;
	*(void**)&_ShowWindow = ShowWindow;
	*(void**)&_SetWindowDisplayAffinity = SetWindowDisplayAffinity;
	*(void**)&_mouse_event = mouzeevent;
	*(void**)&_UpdateWindow = updetewindow;
	*(void**)&_GetClientRect = clientrect;
	*(void**)&_ClientToScreen = clienttoscreen;

	IMPORT(FreeLibrary).get()(kernel32);
	IMPORT(FreeLibrary).get()(user32);
	IMPORT(FreeLibrary).get()(win32u);
	IMPORT(FreeLibrary).get()(dwmapi);
}

BOOL GetCursorPosA_Spoofed(LPPOINT lpPoint)
{
	FUNC;

	return _GetCursorPos(lpPoint);
}

BOOL SetLayeredWindowAttributes_Spoofed(HWND hwnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags)
{
	FUNC;

	return _SetLayeredWindowAttributes(hwnd, crKey, bAlpha, dwFlags);
}

LRESULT __stdcall DefWindowProcA_Spoofed(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	FUNC;

	return _DefWindowProc(hwnd, Msg, wParam, lParam);
}

HWND __stdcall CreateWindowExA_Spoofed(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	FUNC;

	return _CreateWindowExA(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

LONG __stdcall SetWindowLongA_Spoofed(HWND hwnd, int nIndex, LONG dwNewLong)
{
	FUNC;

	return _SetWindowLongA(hwnd, nIndex, dwNewLong);
}

LONG __stdcall GetWindowLongA_Spoofed(HWND hwnd, int nIndex)
{
	FUNC;

	return _GetWindowLongA(hwnd, nIndex);
}

ATOM __stdcall RegisterClassExA_Spoofed(const WNDCLASSEXA* softaim) {
	FUNC;

	return _RegisterClassExA(softaim);
}

int __stdcall GetSystemMetrics_Spoofed(int nIndex) {
	FUNC;

	return _GetSystemMetrics(nIndex);
}

HWND __stdcall FindWindowA_Spoofed(LPCSTR lpClassName, LPCSTR lpWindowName) {
	FUNC;

	return _FindWindowA(lpClassName, lpWindowName);
}

HWND __stdcall GetForegroundWindow_Spoofed() {
	FUNC;

	return _GetForegroundWindow();
}

SHORT GetAsyncKeyState_Spoofed(int vKey) {
	FUNC;

	return _GetAsyncKeyState(vKey);
}

SHORT MoveWindow_Spoofed(HWND hWnd, int X, int Y, int nWidth, int nHeight, bool bRepaint) {
	FUNC;

	return _MoveWindow(hWnd, X, Y, nWidth, nHeight, bRepaint);
}

BOOL __stdcall PeekMessageA_Spoofed(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg) {
	FUNC;

	return _PeekMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
}

BOOL __stdcall TranslateMessage_Spoofed(const MSG* lpMsg) {
	FUNC;

	return _TranslateMessage(lpMsg);
}

LRESULT __stdcall DispatchMessageA_Spoofed(const MSG* lpMsg) {
	FUNC;

	return _DispatchMessageA(lpMsg);
}

HANDLE __stdcall CreateThread_Spoofed(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId) {
	FUNC;

	return _CreateThread(lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
}

BOOL __stdcall CloseHandle_Spoofed(HANDLE hObject) {
	FUNC;

	return _CloseHandle(hObject);
}

BOOL __stdcall SetWindowPos_Spoofed(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags) {
	FUNC;

	return _SetWindowPos(hWnd, hWndInsertAfter, X, Y, cx, cy, uFlags);
}

BOOL __stdcall ShowWindow_Spoofed(HWND hWnd, int nCmdShow) {
	FUNC;

	return _ShowWindow(hWnd, nCmdShow);
}

BOOL __stdcall SetWindowDisplayAffinity_Spoofed(HWND hWnd, DWORD dwAffinity) {
	FUNC;

	return _SetWindowDisplayAffinity(hWnd, dwAffinity);
}

BOOL __stdcall mouse_event_Spoofed(DWORD dwFlags, DWORD dx, DWORD dy, DWORD dwData, ULONG_PTR dwExtraInfo) {
	FUNC;

	return _mouse_event(dwFlags, dx, dy, dwData, dwExtraInfo);
}

BOOL __stdcall UpdateWindow_Spoofed(HWND hWnd) {
	FUNC;

	return _UpdateWindow(hWnd);
}

BOOL __stdcall GetClientRect_Spoofed(HWND hWnd, LPRECT lpRect) {
	FUNC;

	return _GetClientRect(hWnd, lpRect);
}

BOOL __stdcall ClientToScreen_Spoofed(HWND hWnd, LPPOINT lpRect) {
	FUNC;

	return _ClientToScreen(hWnd, lpRect);
}


inline const BYTE XOR_KEY = 0xACACACADDEDFFFA;

inline void EncryptFunctionBytes(BYTE* bytes, size_t size) {
	for (size_t i = 0; i < size; ++i) {
		bytes[i] ^= XOR_KEY;
	}
}

inline void DecryptFunctionBytes(BYTE* bytes, size_t size) {
	for (size_t i = 0; i < size; ++i) {
		bytes[i] ^= XOR_KEY;
	}
}


enum TYPES
{
	move = 1,
	left_up = 4,
	left_down = 2,
	right_up = 8,
	right_down = 16
};

struct MOUSE_INFO
{
	int move_direction_x;
	int move_direction_y;
	unsigned int mouse_data;
	TYPES mouse_options;
	unsigned int time_offset_in_miliseconds;
	void* extra_info;
};

bool(*MOVE)(MOUSE_INFO*, int) = nullptr;

enum INFO : int {
	FAIL = 0,
	SUCCESS = 1
};

namespace MOUSE_HOOK
{
	class c_hooking {
	public:
		auto WINAPI HOOK() -> BOOLEAN {

			auto win32u = IMPORT(LoadLibraryA).safe_cached()(HIDE("win32u.dll"));
			void* ADDRESS = (void*)IMPORT(GetProcAddress).safe_cached()(win32u, HIDE("NtUserInjectMouseInput"));
			if (!ADDRESS) return INFO::FAIL;
			*(void**)&MOVE = ADDRESS;
			IMPORT(FreeLibrary).get()(win32u);
			return INFO::SUCCESS;
		}
	};
} static MOUSE_HOOK::c_hooking* hook_mouse = new MOUSE_HOOK::c_hooking();

namespace MOUSE_MOVEMENT {
	class c_movement {
	public:
		auto WINAPI Move(int X, int Y, unsigned int time = 0) -> BOOLEAN {
			FUNC
				MOUSE_INFO info = {};
			info.mouse_data = 0;
			info.mouse_options = TYPES::move;
			info.move_direction_x = X;
			info.move_direction_y = Y;
			info.time_offset_in_miliseconds = time;
			return MOVE(&info, 1);
		}

		bool Left(int x = 0, int y = 0)
		{
			FUNC
				MOUSE_INFO info = {};
			info.mouse_data = 0;
			info.mouse_options = TYPES::left_down;
			info.move_direction_x = x;
			info.move_direction_y = y;
			info.time_offset_in_miliseconds = 0;
			return MOVE(&info, 1);
		}

		bool Up(int x = 0, int y = 0)
		{
			FUNC
				MOUSE_INFO info = {};
			info.mouse_data = 0;
			info.mouse_options = TYPES::left_up;
			info.move_direction_x = x;
			info.move_direction_y = y;
			info.time_offset_in_miliseconds = 0;
			return MOVE(&info, 1);
		}
	};
} static MOUSE_MOVEMENT::c_movement* MOVE_MOUSE = new MOUSE_MOVEMENT::c_movement();