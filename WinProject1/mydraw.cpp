#include "pch.h"

#include "WinProject1.h"

#define MAX_DISP    100

extern BOOL bdrag;
extern BOOL xStartPos, yStartPos, xPrevPos, yPrevPos;

extern int cx, cy; //window의 넓이와 높이

//깜박임 현상을 방지하기 위해 전역변수로 처리함
extern HDC g_hmemdc;
extern HBITMAP g_hbmp;
extern HBITMAP g_holdbmp;


extern DRAW_MODE dm;


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


void ShowMouseLocation(HWND hwnd, int xPos, int yPos)
{
   
    // HDC hdc = ::GetDC(hWnd);
    if (!bdrag)
        return;
    RECT rt;
    ::GetClientRect(hwnd, &rt);
    ////배경 흰색으로 초기화
    //HBRUSH hbr = (HBRUSH)::GetStockObject(WHITE_BRUSH);
    //::FillRect(g_hmemdc, &rt, hbr);

    WCHAR strOut[MAX_DISP] = { 0 };
    wsprintfW(strOut, L"X 좌표: %d", xPos);
    ::TextOutW(g_hmemdc, 10, 10, strOut, wcslen(strOut));

    wsprintfW(strOut, L"Y 좌표: %d", yPos);
    ::TextOutW(g_hmemdc, 10, 30, strOut, wcslen(strOut));

    //XOR모드 설정
    SetROP2(g_hmemdc, R2_NOTXORPEN);


    switch (dm)
    {
    case RECTANGLE:
        break;
    case CIRCLE:
        break;
    case LINE:
    {
        ::MoveToEx(g_hmemdc, xStartPos, yStartPos, NULL);
        ::LineTo(g_hmemdc, xPrevPos, yPrevPos);

        //시작점을 이동시킴
        ::MoveToEx(g_hmemdc, xStartPos, yStartPos, NULL);

        ::LineTo(g_hmemdc, xPos, yPos);


        break;
    }
    case FREE:
    {

        SetROP2(g_hmemdc, R2_COPYPEN);
        ::MoveToEx(g_hmemdc, xPrevPos, yPrevPos, NULL);

        ::LineTo(g_hmemdc, xPos, yPos);
        break;
    }
    }
    

    

    xPrevPos = xPos;
    yPrevPos = yPos;

    HPEN hPen = ::CreatePen(PS_SOLID, 30, RGB(0, 255, 255));
    HGDIOBJ  hOldPen = ::SelectObject(g_hmemdc, hPen);

    //원래대로 돌려놓기
 

    ::SelectObject(g_hmemdc, hOldPen);
    ::DeleteObject(hPen);

   
    // ::ReleaseDC(hWnd, hdc);
}

void CreateGlobalMemDc(HWND hWnd)
{
    HDC hdc = ::GetDC(hWnd);

    RECT rt;
    ::GetClientRect(hWnd, &rt);
    cx = rt.right;
    cy = rt.bottom;

    //Back Memory DC 생성
    g_hmemdc = ::CreateCompatibleDC(hdc);
    g_hbmp = ::CreateCompatibleBitmap(hdc, cx, cy);
    g_holdbmp = (HBITMAP)::SelectObject(g_hmemdc, g_hbmp);

    //배경 흰색으로 초기화
    HBRUSH hbr = (HBRUSH)::GetStockObject(WHITE_BRUSH);
    ::FillRect(g_hmemdc, &rt, hbr);

    ::ReleaseDC(hWnd, hdc);
}

void DestroyGlobalMemDC()
{
    if (g_hmemdc)
    {
        ::SelectObject(g_hmemdc, g_holdbmp);
        ::DeleteObject(g_hbmp);
        ::DeleteDC(g_hmemdc);
    }
}