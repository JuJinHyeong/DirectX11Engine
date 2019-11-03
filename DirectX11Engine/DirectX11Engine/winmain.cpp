#include<windows.h>
#include<iostream>
#define IDBUTTON 102

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParams, LPARAM lParams);

/* Ŭ���� �̸��� ���� ������ ���� */
TCHAR szClassName[] = TEXT("MyFirstProgram");
HINSTANCE g_hInst;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	HWND hWnd;                    /* �����츦 ���� ó���� */
	MSG msg;                      /* ���α׷��� ���۵� �޽����� ���� */
	WNDCLASSEX wcex;              /* windowclass�� ���� �ڷ� ����ü */

	/* ������ ����ü */
	g_hInst = hInstance;
	wcex.hInstance = hInstance;
	wcex.lpszClassName = szClassName;
	wcex.lpfnWndProc = DefWindowProc;   /* �� �Լ��� �����쿡 ���� ȣ��˴ϴ� */
	wcex.style = CS_VREDRAW | CS_HREDRAW;
	wcex.cbSize = sizeof(WNDCLASSEX);

	/* �⺻ �����ܰ� ������ ��� */
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.lpszMenuName = NULL;     /* �޴� ������ */
	wcex.cbClsExtra = 0;          /* ������ Ŭ���� �ڿ� ���� ����Ʈ ���� */
	wcex.cbWndExtra = 0;          /* ������ �ν��Ͻ� �Ǵ� ����ü */
	/* â�� ������� �������� �⺻ ���� ��� */
	wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);

	/* ������ Ŭ���� ���. ���� �� ���α׷� ���� */
	if (!RegisterClassEx(&wcex))
		return 0;

	/* Ŭ������ ��ϵǾ���. ���� ���α׷��� ������ */
	hWnd = CreateWindowEx(0,     /* ��ȭ�� ���� Ȯ�� ���ɼ� */
		szClassName,                /* Ŭ���� �̸� */
		TEXT("test"),  /* ���� */
		WS_OVERLAPPEDWINDOW,        /* �⺻ â */
		CW_USEDEFAULT,              /* ���α׷��� ȭ�鿡 ǥ�� �� ���� */
		CW_USEDEFAULT,              /* ������ ��ġ ���� */
		600,                        /* ���α׷� �ʺ�� */
		400,                         /* ���� (pixel ����) */
		HWND_DESKTOP,               /* �� â�� ����ȭ���� �ڽ� â�̴� */
		NULL,                       /* �޴� ���� */
		hInstance,                  /* ���α׷� �ν��Ͻ� ó�� */
		NULL);                      /* ������ ���� �ڷ� ���� */

	  /* �����츦 ȭ�鿡 ���̰� */
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	/* �޽��� ��ȯ ����. GetMessage()�� 0�� ��ȯ �� �� ���� �۵� */
	while (GetMessage(&msg, NULL, 0, 0))
	{
		/* ������ Ű �޽����� ���� �޽����� �ؼ� */
		TranslateMessage(&msg);
		/* �޽����� WndProc���� ���� */
		DispatchMessage(&msg);
	}
	/* ���α׷� ��ȯ ���� 0 �Դϴ�. (PostQuicMessage()���� ���� ��) */
	return msg.wParam;
}