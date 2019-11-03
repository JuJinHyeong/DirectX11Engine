#include<windows.h>
#include<iostream>
#define IDBUTTON 102

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParams, LPARAM lParams);

/* 클래스 이름을 전역 변수로 생성 */
TCHAR szClassName[] = TEXT("MyFirstProgram");
HINSTANCE g_hInst;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	HWND hWnd;                    /* 윈도우를 위한 처리기 */
	MSG msg;                      /* 프로그램에 전송된 메시지가 저장 */
	WNDCLASSEX wcex;              /* windowclass를 위한 자료 구조체 */

	/* 윈도우 구조체 */
	g_hInst = hInstance;
	wcex.hInstance = hInstance;
	wcex.lpszClassName = szClassName;
	wcex.lpfnWndProc = DefWindowProc;   /* 이 함수는 윈도우에 의해 호출됩니다 */
	wcex.style = CS_VREDRAW | CS_HREDRAW;
	wcex.cbSize = sizeof(WNDCLASSEX);

	/* 기본 아이콘과 포인터 사용 */
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.lpszMenuName = NULL;     /* 메뉴 사용안함 */
	wcex.cbClsExtra = 0;          /* 윈도우 클래스 뒤에 여우 바이트 없음 */
	wcex.cbWndExtra = 0;          /* 윈도우 인스턴스 또는 구조체 */
	/* 창의 배경으로 윈도우의 기본 색상 사용 */
	wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);

	/* 윈도우 클래스 등록. 실패 시 프로그램 종료 */
	if (!RegisterClassEx(&wcex))
		return 0;

	/* 클래스는 등록되었다. 이제 프로그램을 만들자 */
	hWnd = CreateWindowEx(0,     /* 변화를 위한 확장 가능성 */
		szClassName,                /* 클래스 이름 */
		TEXT("test"),  /* 제목 */
		WS_OVERLAPPEDWINDOW,        /* 기본 창 */
		CW_USEDEFAULT,              /* 프로그램이 화면에 표시 될 때의 */
		CW_USEDEFAULT,              /* 윈도우 위치 선언 */
		600,                        /* 프로그램 너비와 */
		400,                         /* 높이 (pixel 단위) */
		HWND_DESKTOP,               /* 이 창은 바탕화면의 자식 창이다 */
		NULL,                       /* 메뉴 없음 */
		hInstance,                  /* 프로그램 인스턴스 처리 */
		NULL);                      /* 윈도우 생성 자료 없음 */

	  /* 윈도우를 화면에 보이게 */
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	/* 메시지 순환 실행. GetMessage()가 0을 반환 할 때 까지 작동 */
	while (GetMessage(&msg, NULL, 0, 0))
	{
		/* 가상의 키 메시지를 문자 메시지로 해석 */
		TranslateMessage(&msg);
		/* 메시지를 WndProc으로 전송 */
		DispatchMessage(&msg);
	}
	/* 프로그램 반환 값은 0 입니다. (PostQuicMessage()에서 받은 값) */
	return msg.wParam;
}