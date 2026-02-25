#include "pch.h"
#include "framework.h"

#define MAX_DISP    100

extern BOOL bdrag;
extern BOOL xStartPos, yStartPos;



void ShowHello(HWND hWnd, HDC hdc)
{
    // 디바이스 컨택스트를 얻는다.
    // HDC hdc = ::GetDC(hWnd);

    LPCWSTR lpszMessage = L"안녕하세요";
    int len = wcslen(lpszMessage);

    RECT rt;
    ::GetClientRect(hWnd, &rt); // rt구조체에 윈도우의 크기를 돌려줌
    int width = rt.right - rt.left;     // 윈도우의 내부 넓이
    int height = rt.bottom - rt.top;    // 윈도우의 내부 높이

    int center_x = width / 2;
    int center_y = height / 2;

    // TextOutW: 디바이스 컨택스트에 문자열 출력하는 함수
    ::TextOutW(hdc, center_x, center_y, lpszMessage, len);

    // ::ReleaseDC(hWnd, hdc);
}


void ShowRectangle(HWND hWnd, HDC hdc)
{
    // 펜 오브젝트 생성
    HPEN hPen = ::CreatePen(PS_SOLID, 3, RGB(0, 0, 128));
    // 브러시 오브젝트 생성
    HBRUSH hBrush = ::CreateSolidBrush(RGB(64, 255, 64));
    // DC에 그릴 오브젝트를 선택한다.
    HGDIOBJ hOldPen = ::SelectObject(hdc, hPen);
    HGDIOBJ hOldBrush = ::SelectObject(hdc, hBrush);

    // 사각형을 그린다. (10,10위치에 100 x 100 크기의 사각형을 그림)
    ::Rectangle(hdc, 10, 10, 110, 110);

    // 펜과 브러시를 다 사용했으면 원래대로 돌려놓기
    ::SelectObject(hdc, hOldPen);
    ::SelectObject(hdc, hOldBrush);

    // 메모리에서 삭제시킴
    ::DeleteObject(hPen);
    ::DeleteObject(hBrush);
}


void ShowMouseLocation(HWND hwnd, HDC hdc, int xPos, int yPos)
{
    HPEN hPen = ::CreatePen(PS_SOLID, 30, RGB(0, 255, 255));
    HGDIOBJ hOldPen = ::SelectObject(hdc, hPen);
    // HDC hdc = ::GetDC(hWnd);
    if (!bdrag)
        return;
    RECT rt;
    ::GetClientRect(hwnd, &rt);
    int cx = rt.right - rt.left;
    int cy = rt.bottom - rt.top;
    // 메모리 dc를 생성함
    HDC hMemDc = ::CreateCompatibleDC(hdc);
    HBITMAP hbmp = ::CreateCompatibleBitmap(hdc, cx, cy); //도화지 생성

    HGDIOBJ hOldbmp = ::SelectObject(hMemDc, hbmp); //도화지 적용
    WCHAR strOut[MAX_DISP] = { 0 };
    wsprintfW(strOut, L"X 좌표: %d", xPos);
    ::TextOutW(hdc, 10, 10, strOut, wcslen(strOut));

    wsprintfW(strOut, L"Y 좌표: %d", yPos);
    ::TextOutW(hdc, 10, 30, strOut, wcslen(strOut));

    //시작점을 이동시킴
    ::MoveToEx(hdc, xStartPos, yStartPos, NULL);

    ::LineTo(hdc, xPos, yPos);
    ::SelectObject(hdc, hOldPen);
    ::DeleteObject(hPen);
    // ::ReleaseDC(hWnd, hdc);
}