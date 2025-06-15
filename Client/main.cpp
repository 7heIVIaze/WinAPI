// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "Client.h"
#include "CCore.h"
#include <vector>
using std::vector;

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND g_hWnd;                                    // 메인 윈도우 핸들.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

struct tObjInfo
{
    POINT g_ptObjPos;
    POINT g_ptObjScale;
};

vector<tObjInfo> g_vecInfo;

// 좌 상단
POINT g_ptLT;

// 우 하단
POINT g_ptRB;

bool bLbtnDown = false;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// _In_, _In_opt_(optional) 등은 SAL 주석으로 매개 변수의 특징을 알리기 위한 주석.
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, /* 실행된 프로세스의 시작 주소(가상 메모리 공간에서의 주소임) */
                     _In_opt_ HINSTANCE hPrevInstance, 
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance); // 아무 일도 하지 않는 매크로임. -> 주석처럼 사용하는 매크로로 주석과 동일함.
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
    
    // 윈도우 정보 등록.
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다(등록된 정보대로 윈도우 생성): 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // Core 초기화
    if (FAILED(CCore::GetInst()->init(g_hWnd, POINT{1280, 768})))
    {
        MessageBox(nullptr, L"Core 객체 초기화 실패", L"Error", MB_OK);
        return FALSE;
    }



    // 단축키 테이블 정보 로딩 == 단축키 관련 정보를 세팅하는 과정.(단축키를 쓰지 않겠다면 필요없는 코드)
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg;

    //SetTimer(g_hWnd, 0, 0, nullptr); // 언리얼 엔진의 Timer와 동일하게 함수를 지정된 시간마다 호출하는 코드. Elapsed time은 밀리세컨드로 1000이어야 1초.

    // 기본 메시지 루프입니다:
    /* GetMessage인 경우 
       메시지 큐에서 메시지 확인할 때까지 대기.
       msg.message == WM_QUIT인 경우 false를 반환 => 프로그램 종료. */

    /*
        PeekMessage
        메시지 유무와 관계없이 항상 반환. => 즉 메시지 큐에서 메시지를 확인한 상황이면 true, 없으면 false를 반환할 것(유추하면)
    */
    while (1)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        // 메시지가 발생하지 않는 대부분의 시간
        else
        {
            // 메시지가 없는 동안 호출
           

            // Game 코드 수행
            // 디자인 패턴(설계 유형)
            // 싱글톤 패턴
            CCore::GetInst()->progress();
        }
    }

   // KillTimer(g_hWnd, 0);

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CLIENT); // nullptr로 하면 메뉴바가 없어짐.
    wcex.lpszClassName  = szWindowClass; // 윈도우의 키값으로 등록(추후 InitInstance에서 이 키값을 토대로 윈도우 생성함). 즉 키 값은 변경가능하고, InitInstance에서 키 값을 그 값으로 변경하면 상관없음.
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT: // 무효화(invalidate) 영역이 발생한 경우 이 이벤트가 발생함. -> 최근에 무효화 영역은 최소화되었다가 다시 창을 띄울 때 발생.
        {
            PAINTSTRUCT ps;

            // Device Context를 만들어서 ID 반환.
            HDC hdc = BeginPaint(hWnd, &ps); // Device Context(그리기 작업을 수행하고 필요한 Data(현실로 치자면 펜, 브러쉬 등등) 집합)
            // DC의 목적지는 hWnd, 펜은 기본펜(Black), 브러쉬는 기본 브러쉬(White)

            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            /*
            // 직접 펜을 만들어서 DC에 지급.
            HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
            HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));
            // 기존에 만들어진 펜, 브러시를 가져오는 방법도 있는데 GetStockObject로 가져옴. 이들은 DeleteObject를 해서는 안 됨.


            HPEN hDefaultPen = (HPEN)SelectObject(hdc, hRedPen); // 펜을 바꿔주면 기존 펜 ID가 리턴됨.
            HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hBlueBrush); // 브러쉬를 바꿔주면 기존 브러쉬 ID가 리턴됨.
            // SelectObject는 범용적으로 사용하는 함수이므로 void 포인터로 리턴해줌. 따라서 직접 캐스팅 필요.

            // 윈도우 핸들(윈도우의 포인터), 윈도우 좌표(단위는 픽셀), HDC?
            if (bLbtnDown)
            {
                Rectangle(hdc,
                    g_ptLT.x, g_ptLT.y,
                    g_ptRB.x, g_ptRB.y);
            }

            // 추가된 사각형들도 그려준다.
            for (size_t i = 0; i < g_vecInfo.size(); ++i)
            {
                Rectangle(hdc,
                    g_vecInfo[i].g_ptObjPos.x - g_vecInfo[i].g_ptObjScale.x / 2,
                    g_vecInfo[i].g_ptObjPos.y - g_vecInfo[i].g_ptObjScale.y / 2,
                    g_vecInfo[i].g_ptObjPos.x + g_vecInfo[i].g_ptObjScale.x / 2,
                    g_vecInfo[i].g_ptObjPos.y + g_vecInfo[i].g_ptObjScale.y / 2);
            }

            // DC의 펜을 원래 펜으로 변경.
            SelectObject(hdc, hDefaultPen);
            SelectObject(hdc, hDefaultBrush);

            // 다 사용한 Red펜 삭제 요청
            DeleteObject(hRedPen);
            DeleteObject(hBlueBrush);
            */

            // Rectangle(hdc, 1180, 668, 1280, 768);
            // 그리기 종료
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_KEYDOWN: // 처음 누를 때 바로 들어오고, 1초 이상 누르고 있으면 그 이후 바로 들어옴. => 개선할 여지.
    {
        //switch(wParam) // 키 관련 이벤트 파라미터는 WPARAM에 저장됨. 
        //{
        //case VK_UP:
        //    //g_ptObjectPos.y -= 10;
        //    InvalidateRect(hWnd, nullptr, true); // 무효화 영역이 발생했으니, WM_PAINT를 강제로 발생시키는 함수.
        //    break;
        //case VK_DOWN:
        //    //g_ptObjectPos.y += 10;
        //    InvalidateRect(hWnd, nullptr, true); // 무효화 영역이 발생했으니, WM_PAINT를 강제로 발생시키는 함수.
        //    break;
        //case VK_LEFT:
        //    //g_ptObjectPos.x -= 10;
        //    InvalidateRect(hWnd, nullptr, true); // 무효화 영역이 발생했으니, WM_PAINT를 강제로 발생시키는 함수.
        //    break;
        //case VK_RIGHT:
        //    //g_ptObjectPos.x += 10;
        //    InvalidateRect(hWnd, nullptr, true); // 무효화 영역이 발생했으니, WM_PAINT를 강제로 발생시키는 함수.
        //    break;
        //case 'W': // W, A, S, D 등은 대문자 기준임.
        //    break;
        //}
        //int a = 0;

    }
        break;
    case WM_LBUTTONDOWN: // 마우스 좌클릭 이벤트
    {
        // 마우스 관련 이벤트 파라미터는 LPARAM임.
        //g_ptLT.x = LOWORD(lParam); // 마우스 x 좌표
        //g_ptLT.y = HIWORD(lParam); // 마우스 y 좌표
        //bLbtnDown = true;
    }
        break;
    case WM_MOUSEMOVE:
        //g_ptRB.x = LOWORD(lParam); // 마우스 x 좌표
        //g_ptRB.y = HIWORD(lParam); // 마우스 y 좌표
        //InvalidateRect(hWnd, nullptr, true); // 무효화 영역이 발생했으니, WM_PAINT를 강제로 발생시키는 함수.
        break;
    case WM_LBUTTONUP:
   /* {
        tObjInfo info = {};
        info.g_ptObjPos.x = (g_ptLT.x + g_ptRB.x) / 2;
        info.g_ptObjPos.y = (g_ptLT.y + g_ptRB.y) / 2;

        info.g_ptObjScale.x = abs(g_ptLT.x - g_ptRB.x);
        info.g_ptObjScale.y = abs(g_ptLT.y - g_ptRB.y);

        g_vecInfo.push_back(info);
        bLbtnDown = false;
        InvalidateRect(hWnd, nullptr, true);
    }*/
        break;
    case WM_TIMER:

        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
