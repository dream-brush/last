#pragma once

#include "resource.h"


typedef enum {
	RECTANGLE, CIRCLE, LINE, FREE
}DRAW_MODE;


void ShowHello(HWND hWnd, HDC hdc);
void ShowRectangle(HWND hWnd, HDC hdc);
void ShowMouseLocation(HWND hwnd, int xPos, int yPos);
void DestroyGlobalMemDC();
void CreateGlobalMemDc(HWND hWnd);
