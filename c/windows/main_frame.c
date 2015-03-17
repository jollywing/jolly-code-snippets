#define Win32_LEAN_AND_MEAN//ָʾ�������������޹ص�MFC����

#include <windows.h>//�������е�windowsͷ�ļ�

HWND hWnd;
LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	MSG msg;

	//���������� 
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
	wc.lpszMenuName = NULL;	//û�в˵�
	wc.lpszClassName = "myWndClass";
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//ע�ᴰ����
	RegisterClassEx(&wc);

	//��������
	hWnd = CreateWindowEx(NULL, "myWndClass", "win32����", WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);
	if(!hWnd) 
	{
		MessageBox( NULL, "��������ʧ�ܣ�", "����", MB_OK);
		return 1;
	}

	//��ʾ����
	ShowWindow( hWnd, nShowCmd);
	//���´���
	UpdateWindow(hWnd);

	while(GetMessage(&msg, NULL, 0, 0))//���յ�WM_QUIT��Ϣʱ��GetMessage�Ż᷵����ֵ
	{
		TranslateMessage(&msg);//�Լ��ټ���Ϣ����ת��
		DispatchMessage(&msg);//����Ϣ���͵�WindProc
	}
	return msg.wParam ;

}


//��Ϣ������
LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch( message )
	{
	case WM_DESTROY:
		PostQuitMessage(0); //����WM_QUIT��Ϣ����Windows������Դ��WM_DESTROYֻ�ǻٵ����ڣ��������ں�̨����
		return 0;

	}
	return DefWindowProc(hwnd, message, wParam, lParam);

}