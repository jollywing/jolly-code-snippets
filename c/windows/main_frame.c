#define Win32_LEAN_AND_MEAN//指示编译器不包含无关的MFC操作

#include <windows.h>//包含所有的windows头文件

HWND hWnd;
LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	MSG msg;

	//创建窗口类 
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_VREDRAW| CS_HREDRAW;
	wc.lpfnWndProc = WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;	//没有菜单
	wc.lpszClassName = "myWndClass";
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//注册窗口类
	RegisterClassEx(&wc);

	//创建窗口
	hWnd = CreateWindowEx(NULL, "myWndClass", "win32程序", WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);
	if(!hWnd) 
	{
		MessageBox( NULL, "创建窗口失败！", "错误", MB_OK);
		return 1;
	}

	//显示窗口
	ShowWindow( hWnd, nShowCmd);
	//更新窗口
	UpdateWindow(hWnd);

	while(GetMessage(&msg, NULL, 0, 0))//接收到WM_QUIT消息时，GetMessage才会返回零值
	{
		TranslateMessage(&msg);//对加速键消息进行转换
		DispatchMessage(&msg);//将消息发送到WindProc
	}
	return msg.wParam ;

}


//消息处理函数
LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch( message )
	{
	case WM_DESTROY:
		PostQuitMessage(0); //发出WM_QUIT消息，让Windows回收资源。WM_DESTROY只是毁掉窗口，而程序还在后台运行
		return 0;

	}
	return DefWindowProc(hwnd, message, wParam, lParam);

}