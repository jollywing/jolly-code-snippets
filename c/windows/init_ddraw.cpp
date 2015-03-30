/*本程序的内容包括：
1。初始化ddraw，
2。在屏幕上显示画面，
3。释放ddraw
4。指定客户区大小，如何知道窗口的大小，见init_window()
5。给定窗口的矩形，如何获得客户区的矩形，见GetClientRect()
6。页面丢失时，如何恢复，见WinProc中的处理*/
//2005-07-22

//第一步要设置ddraw编程环境，首先工具/选择/目录，添加dx的include目录和lib目录
//然后工程/设置/link中添加ddraw.lib

//第二步将开发包中的ddutil.cpp拷贝到工程目录下，并添加到工程，因为我们要用到其中的函数
//并且注意#include <ddutil.h>

#include <windows.h>
#include <ddraw.h>
#include <ddutil.h>
#include "resource.h" //千万别忘了#include "resource.h"

//宏定义区
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

//变量函数声明区
HWND hWnd;
LPDIRECTDRAW lpDD;
LPDIRECTDRAWSURFACE lpDDSPrimary; //主页面
LPDIRECTDRAWSURFACE lpDDSTemp;//临时页面
RECT RectWindow, RectClient;
RECT RectTemp;
int flag =0; //标志ddraw未初始化
int diff_x, diff_y;//用于获取客户区矩形的变量

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
		MessageBox(NULL, "初始化窗体失败！", "ERROR", MB_OK);
		return FALSE;
	}

//	GetClientRect(hWnd, &RectWindow); 返回的是相对坐标，左上角为(0，0)
//	GetWindowRect(hWnd, &RectWindow); 返回的rect会包含标题栏


	if(!InitDDraw())
	{
		MessageBox(NULL, "初始化DDRAW过程出错！", "ERROR", MB_OK);
		FreeDDraw();
		return FALSE;
	}
	flag =1;//标志初始化ddraw完成

	while (GetMessage(&msg,NULL, 0, 0))//第二个参数设为NULL，表明接收程序创建的所有窗口的所有消息
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
		return 0; //这里一定要是return，而不是break，否则不显示画面
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
	/* 根据客户区窗口矩形得到整个窗体的矩形*/
	diff_x = 0 - RectWindow.left ;
	diff_y = 0 - RectWindow.top ;/*保存这两个变量用于随时获取客户区矩形 */

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

	DirectDrawCreate(NULL, &lpDD, NULL);//产生一个DDRAW对象。
	/*第一个参数是要创建的驱动类型，设为NULL，表示使用当前的显示驱动
	第三个参数用于今后与COM对象兼容，目前都设为NULL*/

	lpDD->SetCooperativeLevel (hWnd, DDSCL_NORMAL);//设置协作级别

	ZeroMemory( &ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS;
	/*主页面的大小和像素格式都是由当前的显示模式决定的，
	所以不能指定，否则发生错误*/
	ddsd.ddsCaps .dwCaps = DDSCAPS_PRIMARYSURFACE;
	ddrval = lpDD->CreateSurface (&ddsd, &lpDDSPrimary, NULL);
	/*第三个参数也是用于与COM对象兼容，目前只能设为NULL*/
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
	/*页面的大小可以和实际图片大小不一样，但会产生失真*/

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
