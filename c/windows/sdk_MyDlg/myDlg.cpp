#include <windows.h>

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,					
					PSTR szCmdLine, int iCmdShow)					
{	
	static TCHAR szAppName[] = TEXT ("myDlg") ;	
	HWND                          hwnd ;	
	MSG                           msg ;	
	WNDCLASS                      wndclass ;
	
	wndclass.style                       = CS_HREDRAW | CS_VREDRAW;	
	wndclass.lpfnWndProc                 = WndProc ;	
	wndclass.cbClsExtra                  = 0 ;	
	wndclass.cbWndExtra                  = DLGWINDOWEXTRA ;                // Note!	
	wndclass.hInstance                   = hInstance ;	
	wndclass.hIcon                       = LoadIcon (hInstance, szAppName) ;	
	wndclass.hCursor                     = LoadCursor (NULL, IDC_ARROW) ;	
	wndclass.hbrBackground               = (HBRUSH) (COLOR_BTNFACE + 1) ;	
	wndclass.lpszMenuName                = NULL ;	
	wndclass.lpszClassName               = szAppName ;	
	
	
	if (!RegisterClass (&wndclass))        
    {        
		MessageBox (  NULL, TEXT ("This program requires Windows NT!"),			
			szAppName, MB_ICONERROR) ;        
		return 0 ;        
	}
	
	hwnd = CreateDialog (hInstance, szAppName, 0, NULL) ;
	if(!hwnd){
		MessageBox(NULL, "create dialog failure!", "error", MB_ICONERROR);
		return 1;
	}
	
	ShowWindow (hwnd, iCmdShow) ;
	
	while (GetMessage (&msg, NULL, 0, 0))        
	{        
		TranslateMessage (&msg) ;        
		DispatchMessage (&msg) ;        
    }
	
	return msg.wParam ;	
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam,LPARAM lParam)        
{        
	switch (message)        
	{
	case   WM_DESTROY:
		PostQuitMessage (0) ;
		return 0 ;
	}
	
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}
