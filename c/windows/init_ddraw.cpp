/*����������ݰ�����
1����ʼ��ddraw��
2������Ļ����ʾ���棬
3���ͷ�ddraw
4��ָ���ͻ�����С�����֪�����ڵĴ�С����init_window()
5���������ڵľ��Σ���λ�ÿͻ����ľ��Σ���GetClientRect()
6��ҳ�涪ʧʱ����λָ�����WinProc�еĴ���*/
//2005-07-22

//��һ��Ҫ����ddraw��̻��������ȹ���/ѡ��/Ŀ¼�����dx��includeĿ¼��libĿ¼
//Ȼ�󹤳�/����/link�����ddraw.lib

//�ڶ������������е�ddutil.cpp����������Ŀ¼�£�����ӵ����̣���Ϊ����Ҫ�õ����еĺ���
//����ע��#include <ddutil.h>

#include <windows.h>
#include <ddraw.h>
#include <ddutil.h>
#include "resource.h" //ǧ�������#include "resource.h"

//�궨����
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

//��������������
HWND hWnd;
LPDIRECTDRAW lpDD;
LPDIRECTDRAWSURFACE lpDDSPrimary; //��ҳ��
LPDIRECTDRAWSURFACE lpDDSTemp;//��ʱҳ��
RECT RectWindow, RectClient;
RECT RectTemp;
int flag =0; //��־ddrawδ��ʼ��
int diff_x, diff_y;//���ڻ�ȡ�ͻ������εı���

HWND InitWindow(HINSTANCE, int);
HRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitDDraw(void);
void FreeDDraw(void);
RECT GetClientRect(HWND, int, int);

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	MSG msg;

	hWnd = InitWindow(hInstance, nShowCmd);
	if(!hWnd)
	{
		MessageBox(NULL, "��ʼ������ʧ�ܣ�", "ERROR", MB_OK);
		return FALSE;
	}

//	GetClientRect(hWnd, &RectWindow); ���ص���������꣬���Ͻ�Ϊ(0��0)
//	GetWindowRect(hWnd, &RectWindow); ���ص�rect�����������


	if(!InitDDraw())
	{
		MessageBox(NULL, "��ʼ��DDRAW���̳���", "ERROR", MB_OK);
		FreeDDraw();
		return FALSE;
	}
	flag =1;//��־��ʼ��ddraw���

	while (GetMessage(&msg,NULL, 0, 0))//�ڶ���������ΪNULL���������ճ��򴴽������д��ڵ�������Ϣ
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam ;
}

HRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
		if(flag)
		{
			RectClient = GetClientRect(hWnd, diff_x, diff_y);
			HRESULT ddrval = lpDDSPrimary->Blt (&RectClient, 
				lpDDSTemp, &RectTemp, DDBLT_WAIT, NULL);
			if(ddrval == DDERR_SURFACELOST)
			{
				ddrval = lpDDSPrimary->Restore();
				if (ddrval != DD_OK)
					break;
			}
		}
		return 0; //����һ��Ҫ��return��������break��������ʾ����
	case WM_DESTROY:
		FreeDDraw();
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

HWND InitWindow(HINSTANCE hInstance, int nShowCmd)
{
	HWND hwnd;
	WNDCLASS wc;

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WinProc;
	wc.lpszClassName = "02init_ddraw";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW|CS_VREDRAW;

	RegisterClass(&wc);

	RectWindow.left = 0;
	RectWindow.top = 0;
	RectWindow.right = SCREEN_WIDTH;
	RectWindow.bottom = SCREEN_HEIGHT;

	AdjustWindowRect(&RectWindow, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, FALSE);
	/* ���ݿͻ������ھ��εõ���������ľ���*/
	diff_x = 0 - RectWindow.left ;
	diff_y = 0 - RectWindow.top ;/*��������������������ʱ��ȡ�ͻ������� */

	int w = RectWindow.right - RectWindow.left ;
	int h = RectWindow.bottom - RectWindow.top ;

	hwnd = CreateWindow("02init_ddraw", "02 init ddraw", 
		WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, w, h, NULL, NULL,
		hInstance, NULL);
	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	return hwnd;
}

BOOL InitDDraw()
{
	DDSURFACEDESC ddsd;
	HRESULT ddrval;

	DirectDrawCreate(NULL, &lpDD, NULL);//����һ��DDRAW����
	/*��һ��������Ҫ�������������ͣ���ΪNULL����ʾʹ�õ�ǰ����ʾ����
	�������������ڽ����COM������ݣ�Ŀǰ����ΪNULL*/

	lpDD->SetCooperativeLevel (hWnd, DDSCL_NORMAL);//����Э������

	ZeroMemory( &ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS;
	/*��ҳ��Ĵ�С�����ظ�ʽ�����ɵ�ǰ����ʾģʽ�����ģ�
	���Բ���ָ��������������*/
	ddsd.ddsCaps .dwCaps = DDSCAPS_PRIMARYSURFACE;
	ddrval = lpDD->CreateSurface (&ddsd, &lpDDSPrimary, NULL);
	/*����������Ҳ��������COM������ݣ�Ŀǰֻ����ΪNULL*/
	if(ddrval != DD_OK)
	{
		return FALSE;
	}
	
	ZeroMemory( &ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS| DDSD_HEIGHT| DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	ddsd.dwHeight = 600;
	ddsd.dwWidth = 800;
	/*ҳ��Ĵ�С���Ժ�ʵ��ͼƬ��С��һ�����������ʧ��*/

	RectTemp.left = 0;
	RectTemp.top = 0;
	RectTemp.right = ddsd.dwWidth;
	RectTemp.bottom = ddsd.dwHeight;
	

	lpDD->CreateSurface (&ddsd, &lpDDSTemp, NULL);
	if(ddrval != DD_OK)
	{
		return FALSE;
	}

	DDReLoadBitmap( lpDDSTemp, "gameover.bmp");

	return TRUE;

}

void FreeDDraw()
{
	if(lpDD != NULL)
	{
		if(lpDDSPrimary != NULL)
		{
			lpDDSPrimary->Release();
			lpDDSPrimary = NULL;
		}
		if(lpDDSTemp != NULL)
		{
			lpDDSTemp->Release ();
			lpDDSTemp = NULL;
		}
		lpDD->Release ();
		lpDD = NULL;
	}
	return;
}

RECT GetClientRect(HWND hwnd, int x, int y)
{
	RECT rect1, rect2;
	GetWindowRect(hwnd, &rect1);
	rect2.left = rect1.left + x;
	rect2.top = rect1.top + y;
	rect2.right = rect2.left + SCREEN_WIDTH;
	rect2.bottom = rect2.top + SCREEN_HEIGHT;

	return rect2;

}
