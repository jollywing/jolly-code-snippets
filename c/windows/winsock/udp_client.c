#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>

//�궨����
#define DEFAULT_PORT 5555
#define DEFAULT_IP_ADDRESS "127.0.0.1"
#define DEFAULT_BUFFER_LENGTH 1024
//ȫ�ֱ�����
short int_Local_IP_Port = DEFAULT_PORT;
char char_Local_IP_Address[128];
char char_Server_IP_Address[128];

main()
{
	//����
	WSADATA wsd;
	SOCKET sck_client_socket;
	struct sockaddr_in local, sender;
	char  char_Recieved_Message[1024] ;
	DWORD dword_sender_size;
	int int_message_byte;
	//��ʼ��socket
	if(WSAStartup(MAKEWORD(2,2),&wsd)!=0)
	{
		printf("socket��ʼ��ʧ�ܣ�\n");
		return 1;
	}
	//����socket
	sck_client_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if(sck_client_socket == INVALID_SOCKET)
	{
		printf("����socketʧ�ܣ�\n");
		return 1;
	}
	//���˿���Ϣ
	strcpy(char_Local_IP_Address, DEFAULT_IP_ADDRESS);
	local.sin_family = AF_INET;
	local.sin_port = htons((short)int_Local_IP_Port);
	local.sin_addr.s_addr = inet_addr(char_Local_IP_Address);//���֮��ע��һ��sin_addr�ṹ�Ķ���

	strcpy(char_Server_IP_Address, DEFAULT_IP_ADDRESS);
	sender.sin_family = AF_INET;
	sender.sin_port = htons((short)int_Local_IP_Port);
	sender.sin_addr .s_addr = inet_addr(char_Server_IP_Address);

	dword_sender_size = sizeof(sender);

	//��SOCKET
	if(bind(sck_client_socket, (SOCKADDR *)&local, sizeof(local))== SOCKET_ERROR)
	{
		printf("��ʧ�ܣ�\n");
		return 1;
	}

	//���뻺�����ռ�
/*	char_Recieved_Message =(char *) GlobalAlloc(GMEM_FIXED, DEFAULT_BUFFER_LENGTH);
	if(!char_Recieved_Message)
	{
		printf("����ռ�ʧ�ܣ�\n");
		return 1;
	}*/

	//ѭ����������
	while(1)
	{
		Sleep(1000);
		//��������
		int_message_byte = recvfrom(sck_client_socket, char_Recieved_Message, 128, 0, 
			(SOCKADDR *)&sender, (int *)&dword_sender_size);
		//Ϊʲô��Ϣ���м䱻�ض�
		char_Recieved_Message[int_message_byte] = '\0'; //
		printf("���յ�%d���ֽڵ���Ϣ�ǣ�%s\n", int_message_byte, char_Recieved_Message);

	}
	//�ر�socket
	closesocket(sck_client_socket);
//	GlobalFree(char_Recieved_Message);
	WSACleanup();
	return 0;
}