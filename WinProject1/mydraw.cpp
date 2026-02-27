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

extern BOOL bDrawLineDone;
extern DRAW_MODE dm;

extern COLORREF g_penColor; //디폴트 컬러 Black
extern COLORREF g_brColor; //디폴트 컬러 Black



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
    HPEN hPen = ::CreatePen(PS_SOLID, 30, g_penColor);
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


void DrawLIne(HWND hwnd, int xPos, int yPos)
{
    HDC hdc = ::GetDC(hwnd);

    HPEN hPen = ::CreatePen(PS_SOLID, 30, g_penColor);
    HGDIOBJ  hOldPen = ::SelectObject(hdc, hPen);


    ::SetROP2(hdc, R2_NOTXORPEN);

    MoveToEx(hdc, xStartPos, yStartPos, NULL);
    LineTo(hdc, xPrevPos, yPrevPos);


    MoveToEx(hdc, xStartPos, yStartPos, NULL);
    LineTo(hdc, xPos, yPos);

    ::SelectObject(hdc, hOldPen);
    ::DeleteObject(hPen);
    ::ReleaseDC(hwnd, hdc);

    ::ReleaseDC(hwnd, hdc);
}


void DrawRectangle(HWND hwnd, int xPos, int yPos, BOOL isCircle = FALSE)
{
    HDC hdc = ::GetDC(hwnd);
    HPEN hPen = ::CreatePen(PS_SOLID, 30, g_penColor);
    HGDIOBJ  hOldPen = ::SelectObject(hdc, hPen);

    HBRUSH hbr = ::CreateSolidBrush(g_brColor);
    HGDIOBJ hOldbr = ::SelectObject(hdc, hbr);


    ::SetROP2(hdc, R2_NOTXORPEN);

    if (!isCircle)
    {
        ::Rectangle(hdc, xStartPos, yStartPos, xPrevPos, yPrevPos);
        ::Rectangle(hdc, xStartPos, yStartPos, xPos, yPos);
    }
    else
    {
        ::Ellipse(hdc, xStartPos, yStartPos, xPrevPos, yPrevPos);
        ::Ellipse(hdc, xStartPos, yStartPos, xPos, yPos);


    }

    ::SelectObject(hdc, hOldPen);
    ::DeleteObject(hPen);
    ::SelectObject(hdc, hOldbr);
    ::DeleteObject(hbr);

    ::ReleaseDC(hwnd, hdc);
}

void Draw(HWND hwnd, int xPos, int yPos)
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


    HPEN hPen = ::CreatePen(PS_SOLID, 30, g_penColor);
    HGDIOBJ  hOldPen = ::SelectObject(g_hmemdc, hPen);

    HBRUSH hbr = ::CreateSolidBrush(g_brColor);
    HGDIOBJ hOldbr = ::SelectObject(g_hmemdc, hbr);


    //XOR모드 설정
    //SetROP2(g_hmemdc, R2_NOTXORPEN);
    BOOL isCircle = dm == CIRCLE;

    switch (dm)
    {
    case CIRCLE:
    case RECTANGLE:
        if (bDrawLineDone)
        {
            if (isCircle)
                Ellipse(g_hmemdc, xStartPos, yStartPos, xPos, yPos);
            else
                Rectangle(g_hmemdc, xStartPos, yStartPos, xPos, yPos);
        }
        else
        {
            DrawRectangle(hwnd, xPos, yPos, isCircle);
        }
        break;
   
    
    case LINE:
    {
        if (bDrawLineDone)
        {

            MoveToEx(g_hmemdc, xStartPos, yStartPos, NULL);
            LineTo(g_hmemdc, xPrevPos, yPrevPos);


            MoveToEx(g_hmemdc, xStartPos, yStartPos, NULL);
            LineTo(g_hmemdc, xPos, yPos);
        }
        else
        {
            DrawLIne(hwnd, xPos, yPos);
        }
  

        break;
    }
    case FREE:
    {

        SetROP2(g_hmemdc, R2_COPYPEN);
        ::MoveToEx(g_hmemdc, xPrevPos, yPrevPos, NULL);

        ::LineTo(g_hmemdc, xPos, yPos);
      
    }
    }
    

    

    xPrevPos = xPos;
    yPrevPos = yPos;

   
    //원래대로 돌려놓기
 

    ::SelectObject(g_hmemdc, hOldPen);
    ::DeleteObject(hPen);

    ::SelectObject(g_hmemdc, hOldbr);
    ::DeleteObject(hbr);

   
    ::ReleaseDC(hwnd, g_hmemdc);
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


void SelectPenColor(HWND hwnd)
{
    COLORREF cl[16] = { 0 };

    CHOOSECOLOR cc = { 0 };
    cc.lStructSize = sizeof(cc);
    cc.hwndOwner = hwnd;
    cc.rgbResult = g_penColor;
    cc.lpCustColors = cl;
    cc.Flags = CC_FULLOPEN | CC_RGBINIT;
    if (ChooseColorW(&cc))
    {
        g_penColor = cc.rgbResult;
    }
}

void SelectBrushColor(HWND hwnd)
{
    COLORREF cl[16] = { 0 };

    CHOOSECOLOR cc = { 0 };
    cc.lStructSize = sizeof(cc);
    cc.hwndOwner = hwnd;
    cc.rgbResult = g_brColor;
    cc.lpCustColors = cl;
    cc.Flags = CC_FULLOPEN | CC_RGBINIT;
    if (ChooseColorW(&cc))
    {
        g_brColor = cc.rgbResult;
    }
}