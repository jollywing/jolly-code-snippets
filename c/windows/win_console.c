#include <stdio.h>
#include <windows.h>
#include <stdio.h>

main()
{
	//����console���ڵı���
	SetConsoleTitle("copying...");
	printf("\n");

	int i = 0;
	printf("files copied %3d%%...\n", i);

	COORD origin = {13, 1};	//ֻ��������ʱ����������ֵ
	HANDLE hConsoleOut;
	DWORD charWritten;
	char buf[16];

	//�õ�console�ľ��
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);

	while(i < 100)
	{
		i++;
		//ת����10���Ƶ������ַ������浽buf�С�
		_itoa(i, buf, 10);	

		//��ָ����λ������ַ�����charWritten��ʾ������ַ���
		WriteConsoleOutputCharacter( hConsoleOut, buf, 3, origin, &charWritten);
		Sleep(200);

	}

	strcpy( buf, "completed. \n");
	WriteConsoleOutputCharacter( hConsoleOut, buf, strlen(buf) + 1 , origin, &charWritten);

	//�رձ�׼����ľ����
	//CloseHandle����object�����ü���
	//�����ü���Ϊ0ʱ��ϵͳ������ö���
	CloseHandle( hConsoleOut);

}