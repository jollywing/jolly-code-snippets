//该程序讲述了如何创建一个窗口，以及如何使用自定义的图标和光标资源
//使用自定义光标没有成功，原因待查
//2005-07-22

#include <windows.h>
//#include <windowsX.h>
#include "resource.h"

//宏定义区

//变量函数声明区
HWND hWnd;
HCURSOR hCursor;

HWND Init_Window(HINSTANCE, int);
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	MSG msg;

	hWnd = Init_Window(hInstance, nShowCmd);
	if(!hWnd)
		MessageBox(NULL, "创建窗口失败！", "错误", MB_OK);
		return FALSE;

	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam ;

}

HWND Init_Window(HINSTANCE hInstance, int nShowCmd)
{
	HWND hwnd;

	WNDCLASS wc;

//	char * temp;

//	wc.cbSize = sizeof(WNDCLASS);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.style = CS_VREDRAW| CS_HREDRAW| CS_OWNDC;
	wc.lpfnWndProc = WinProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO); //使用预定义的图标，第一个参数为NULL;使用自定义图标，第一个参数为hInstance
//	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON)); //使用自定义的资源
	//***************************************************************************
	//使用自定义图标的方法: 新建RESOURCE SCRIPT，会自动生成.rc和resource.h两个文件
	//以后的过程中develop studio也会自动维护他们。这里要注意的是将系统生成的resource.h
	//添加到工程中。插入想要的图标资源，然后编译成功。
	//*******************************************************************************
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); //使用预定义的鼠标
	//temp = MAKEINTRESOURCE(IDC_SWORD);
	//wc.hCursor = LoadCursor(hInstance, temp);//与使用自定义图标类似
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;//不要菜单
	wc.lpszClassName = "myWindowsClass";
	//wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);//小应用程序图标

	hCursor = wc.hCursor;

	RegisterClass(&wc);//注册窗口类

	hwnd = CreateWindow("myWindowsClass", "我的简单游戏",  
		WS_POPUP|WS_BORDER|WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,//全使用系统默认值
		NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, nShowCmd);//如果在窗口类型中添加了WS_VISIBLE，则这行代码可以不要。
	UpdateWindow(hwnd);//让Windows产生一个WM_PAINT消息

	return hwnd;
	
}

LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch( message )
	{
	case WM_DESTROY:
		PostQuitMessage(0); //发出一个退出程式的消息。WM_DESTROY只是毁掉窗口，而程序还在后台运行
		return 0;
	case WM_MOUSEMOVE:
		SetCursor(hCursor);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);

}