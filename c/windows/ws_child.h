/*================================================
 *	内容：	产生子窗口
 *			子窗口消息处理
 *	作者：	吴吉庆
 *	时间：	2007-10-29
 *===============================================*/
 #include <windows.h>

/*********************窗口子类化**************************
滚动条控件的窗口消息处理程序是Windows内部的。
但是，将GWL_WNDPROC标识符作为参数来呼叫GetWindowLong，
您就可以得到这个窗口消息处理程序的地址。
另外，您可以呼叫SetWindowLong给该滚动条设定一个新的窗口消息处理程序，
这个技术叫做「窗口子类别化」，非常有用。
它能让您给现存的窗口消息处理程序设定「挂勾」，
以便在自己的程序中处理一些消息，
同时将其它所有消息传递给旧的窗口消息处理程序。

********************************************************/
/*-----------------------------------------------
 *	按钮类型：	 BS_PUSHBUTTON		普通按钮
 *				BS_DEFPUSHBUTTON	内定的普通按钮，边框略粗一些
 *				BS_CHECKBOX			复选框
 *				BS_AUTOCHECKBOX		复选框，不需要手动SETCHECK
 *				BS_3STATE			3态复选框，还有一种禁止状态
 *				BS_AUTO3STATE		自动3态复选框
 *				BS_RADIOBUTTON		单选框
 *				BS_AUTORADIOBUTTON	自动单选框，只用于对话框
 *				BS_GROUPBOX			分组框
 *
 *	下面是一个产生普通按钮的例子：
 CreateWindow(TEXT("button"), "按钮", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
			10, 10, 60, 25, hwnd, (HMENU)1, hInst, NULL);
 *---------------------------------------------*/

/*----------------按钮的文字--------------------------
 *	改变按钮的文字
 *	SetWindowText (hwnd, pszString) ;

 *	获取按钮的文字
 *	iLength = GetWindowText (hwnd, pszBuffer, iMaxLength) ;
 *	iMaxLength是放入pszBuffer的最大字符数。iLength传回实际复制的字符数。

 *	获得按钮文字的长度
 *	iLength = GetWindowTextLength (hwnd) ;
 *-------------------------------------------------*/

/*---------------按钮的显示与隐藏--------------------
 *	ShowWindow (hwndChild, SW_SHOWNORMAL)		显示
 *	ShowWindow (hwndChild, SW_HIDE)				隐藏
 *	IsWindowVisible (hwndChild)				是否可见
 *-------------------------------------------------*/

/*---------------按钮的启用与禁止-----------------------
 *	EnableWindow (hwndChild, FALSE) ;
 *	EnableWindow (hwndChild, TRUE) ;
 *	IsWindowEnabled (hwndChild) ;
 *---------------------------------------------------*/

/*------------------------------------------------
 *	当鼠标单击按钮时，按钮会向父窗口发送WM_COMMAND消息
 *	LOWORD (wParam)		子窗口ID
 *	HIWORD (wParam)		通知码
 *	lParam				子窗口句柄
 *-----------------------------------------------*/

/*--------------------------------------------------
 *	父窗口也能向子窗口控件发送按钮消息
 *	BM_GETCHECK			获取复选框单选框是否选中
 *	BM_SETCHECK			设置复选框单选框是否选中
 *	BM_GETSTATE			按钮处于正常状态还是按下状态
 *	BM_SETSTATE
 *	BM_SETSTYLE			按钮生成后还可以改变类型
 *	BM_CLICK
 *	BM_GETIMAGE
 *	BM_SETIMAGE

 *	例如你想知道复选框是否选中，向它发送消息
 *	iCheck = (int) SendMessage (hwndButton, BM_GETCHECK, 0, 0) ;
 *--------------------------------------------------*/

/*=========================静态文本========================*/

/*------------------静态文本的样式----------------------
 *	SS_BLACKRECT
 *	SS_GRAYRECT
 *	SS_WHITERECT
 *	SS_BLACKFRAME
 *	SS_GRAYFRAME
 *	SS_WHITEFRAME
 *
 *	当使用这些样式CreateWindow时，窗口文本参数将被忽略
 *	即使使用SetWindowText设置文本也不起作用
 *	一个产生静态文本的例子
 CreateWindow(TEXT("static"), "静态文本", WS_CHILD|WS_VISIBLE|SS_LEFT,
			10, 200, 100, 30, hwnd, (HMENU)4, hInst, NULL);
 *---------------------------------------------------*/
/*------------------静态文本的文字样式-------------------
 *	SS_LEFT、SS_RIGHT和SS_CENTER
 *---------------------------------------------------*/
/*-------------------------------------------------
 *	子窗口与父窗口交互的一些函数：
 *
 *	获取父窗口句柄（一般用在子窗口自己的消息函数中）
 *	hwndParent = GetParent (hwnd) ;
 *
 *	通过窗口句柄获取程序实例
 *	GetWindowLong (hwnd, GWL_HINSTANCE)

 *	通过子窗口句柄获取子窗口id
 *	id = GetWindowLong (hwndChild, GWL_ID) ;或
 *	id = GetDlgCtrlID (hwndChild) ;（不局限于dlg，都可以用）

 *	通过子窗口id获取子窗口句柄
 *	hwndChild = GetDlgItem (hwndParent, id) ;


 */