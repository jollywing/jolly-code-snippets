#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>

//宏定义区
#define DEFAULT_PORT 5555
#define DEFAULT_IP_ADDRESS "127.0.0.1"
#define DEFAULT_BUFFER_LENGTH 1024
//全局变量区
short int_Local_IP_Port = DEFAULT_PORT;
char char_Local_IP_Address[128];
char char_Server_IP_Address[128];

main()
{
	//变量
	WSADATA wsd;
	SOCKET sck_client_socket;
	struct sockaddr_in local, sender;
	char  char_Recieved_Message[1024] ;
	DWORD dword_sender_size;
	int int_message_byte;
	//初始化socket
	if(WSAStartup(MAKEWORD(2,2),&wsd)!=0)
	{
		printf("socket初始化失败！\n");
		return 1;
	}
	//创建socket
	sck_client_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if(sck_client_socket == INVALID_SOCKET)
	{
		printf("创建socket失败！\n");
		return 1;
	}
	//填充端口信息
	strcpy(char_Local_IP_Address, DEFAULT_IP_ADDRESS);
	local.sin_family = AF_INET;
	local.sin_port = htons((short)int_Local_IP_Port);
	local.sin_addr.s_addr = inet_addr(char_Local_IP_Address);//编程之后注意一下sin_addr结构的定义

	strcpy(char_Server_IP_Address, DEFAULT_IP_ADDRESS);
	sender.sin_family = AF_INET;
	sender.sin_port = htons((short)int_Local_IP_Port);
	sender.sin_addr .s_addr = inet_addr(char_Server_IP_Address);

	dword_sender_size = sizeof(sender);

	//绑定SOCKET
	if(bind(sck_client_socket, (SOCKADDR *)&local, sizeof(local))== SOCKET_ERROR)
	{
		printf("绑定失败！\n");
		return 1;
	}

	//申请缓冲区空间
/*	char_Recieved_Message =(char *) GlobalAlloc(GMEM_FIXED, DEFAULT_BUFFER_LENGTH);
	if(!char_Recieved_Message)
	{
		printf("申请空间失败！\n");
		return 1;
	}*/

	//循环接收数据
	while(1)
	{
		Sleep(1000);
		//接收数据
		int_message_byte = recvfrom(sck_client_socket, char_Recieved_Message, 128, 0, 
			(SOCKADDR *)&sender, (int *)&dword_sender_size);
		//为什么信息从中间被截断
		char_Recieved_Message[int_message_byte] = '\0'; //
		printf("接收的%d个字节的信息是：%s\n", int_message_byte, char_Recieved_Message);

	}
	//关闭socket
	closesocket(sck_client_socket);
//	GlobalFree(char_Recieved_Message);
	WSACleanup();
	return 0;
}