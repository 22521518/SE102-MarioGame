#pragma once
#include <Windows.h>

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight,
	LPCWSTR windowIcon, LPCWSTR windowClassName, LPCWSTR windowTitle);
