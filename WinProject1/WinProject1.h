#pragma once

#include "resource.h"


typedef enum {
	RECTANGLE, CIRCLE, LINE, FREE
}DRAW_MODE;


void ShowHello(HWND hWnd, HDC hdc);
void ShowRectangle(HWND hWnd, HDC hdc);
void Draw(HWND hwnd, int xPos, int yPos);
void DestroyGlobalMemDC();
void CreateGlobalMemDc(HWND hWnd);

void SelectPenColor(HWND hwnd);
void SelectBrushColor(HWND hwnd)
;

