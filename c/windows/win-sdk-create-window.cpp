//�ó���������δ���һ�����ڣ��Լ����ʹ���Զ����ͼ��͹����Դ
//ʹ���Զ�����û�гɹ���ԭ�����
//2005-07-22

#include <windows.h>
//#include <windowsX.h>
#include "resource.h"

//�궨����

//��������������
HWND hWnd;
HCURSOR hCursor;

HWND Init_Window(HINSTANCE, int);
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	MSG msg;

	hWnd = Init_Window(hInstance, nShowCmd);
	if(!hWnd)
		MessageBox(NULL, "��������ʧ�ܣ�", "����", MB_OK);
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
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO); //ʹ��Ԥ�����ͼ�꣬��һ������ΪNULL;ʹ���Զ���ͼ�꣬��һ������ΪhInstance
//	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON)); //ʹ���Զ������Դ
	//***************************************************************************
	//ʹ���Զ���ͼ��ķ���: �½�RESOURCE SCRIPT�����Զ�����.rc��resource.h�����ļ�
	//�Ժ�Ĺ�����develop studioҲ���Զ�ά�����ǡ�����Ҫע����ǽ�ϵͳ���ɵ�resource.h
	//��ӵ������С�������Ҫ��ͼ����Դ��Ȼ�����ɹ���
	//*******************************************************************************
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); //ʹ��Ԥ��������
	//temp = MAKEINTRESOURCE(IDC_SWORD);
	//wc.hCursor = LoadCursor(hInstance, temp);//��ʹ���Զ���ͼ������
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;//��Ҫ�˵�
	wc.lpszClassName = "myWindowsClass";
	//wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);//СӦ�ó���ͼ��

	hCursor = wc.hCursor;

	RegisterClass(&wc);//ע�ᴰ����

	hwnd = CreateWindow("myWindowsClass", "�ҵļ���Ϸ",  
		WS_POPUP|WS_BORDER|WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,//ȫʹ��ϵͳĬ��ֵ
		NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, nShowCmd);//����ڴ��������������WS_VISIBLE�������д�����Բ�Ҫ��
	UpdateWindow(hwnd);//��Windows����һ��WM_PAINT��Ϣ

	return hwnd;
	
}

LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch( message )
	{
	case WM_DESTROY:
		PostQuitMessage(0); //����һ���˳���ʽ����Ϣ��WM_DESTROYֻ�ǻٵ����ڣ��������ں�̨����
		return 0;
	case WM_MOUSEMOVE:
		SetCursor(hCursor);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);

}