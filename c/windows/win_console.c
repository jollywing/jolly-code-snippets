#include <stdio.h>
#include <windows.h>
#include <stdio.h>

main()
{
	//设置console窗口的标题
	SetConsoleTitle("copying...");
	printf("\n");

	int i = 0;
	printf("files copied %3d%%...\n", i);

	COORD origin = {13, 1};	//只有在声明时可以这样赋值
	HANDLE hConsoleOut;
	DWORD charWritten;
	char buf[16];

	//得到console的句柄
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);

	while(i < 100)
	{
		i++;
		//转换成10进制的数的字符串，存到buf中。
		_itoa(i, buf, 10);	

		//在指定的位置输出字符串，charWritten表示输出的字符数
		WriteConsoleOutputCharacter( hConsoleOut, buf, 3, origin, &charWritten);
		Sleep(200);

	}

	strcpy( buf, "completed. \n");
	WriteConsoleOutputCharacter( hConsoleOut, buf, strlen(buf) + 1 , origin, &charWritten);

	//关闭标准输出的句柄。
	//CloseHandle减少object的引用计数
	//当引用计数为0时，系统会清除该对象
	CloseHandle( hConsoleOut);

}