//��������Client.c
//
//�����ܣ�������Ϊͨ������ϵͳ�豸״̬���Ͷˡ���ͨ��TCP�����豸״̬���նˣ������豸״̬��Ϣ�������ս��ն˵Ļش���Ϣ��
//
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_PORT 5150
#define DEFAULT_IP_Address "127.0.0.1"
#define DEFAULT_BUFFER 1024
#define DEFAULT_MESSAGE "Network System, Device Code, OK!"

char char_Server_IP_Address[128],char_Device_status_Message[1024];
int  int_Server_IP_Port=DEFAULT_PORT;
BOOL bool_SentOnly=TRUE;              //TRUE:ֻ������Ϣ��������

int main()
{
  WSADATA  wsd;
  SOCKET   sck_Client_Socket;
  char     char_Message_from_Server[DEFAULT_BUFFER];
  int      int_ReturnValue_from_Send_or_Recive;

  struct sockaddr_in server;

  //Socket��ʼ��
  if (WSAStartup(MAKEWORD(2,2),&wsd)!=0)
    {
       printf("Socket��ʼ��ʧ��\n");
       return 1;
    }

  //����Socket
  sck_Client_Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
  if (sck_Client_Socket==INVALID_SOCKET)
    {
       printf("����Socketʧ��\n");
       return 1;
    }

  //��д��������Ϣ
  strcpy(char_Server_IP_Address,DEFAULT_IP_Address);
  server.sin_family=AF_INET;
  server.sin_port=htons(int_Server_IP_Port);//htons��htonl������
  server.sin_addr.s_addr = inet_addr(char_Server_IP_Address);

  //���ӷ�����
  if (connect(sck_Client_Socket,(struct sockaddr far *)&server,sizeof(server))==SOCKET_ERROR)
    {
       printf("����ʧ��\n");
       return 1;
    }

  //ѭ�����պͷ���
  while(1)
    {
      if (bool_SentOnly==FALSE)
        {
         //������Ϣ
         int_ReturnValue_from_Send_or_Recive=recv(sck_Client_Socket,char_Message_from_Server,DEFAULT_BUFFER,0);
         if ((int_ReturnValue_from_Send_or_Recive==0) || (int_ReturnValue_from_Send_or_Recive==SOCKET_ERROR))
           {
              printf("����ʧ��\n");
              break;
           }
         char_Message_from_Server[int_ReturnValue_from_Send_or_Recive]='\0';
         printf("������Ϣ [%d bytes]: '%s'\n",int_ReturnValue_from_Send_or_Recive,char_Message_from_Server);
        }

      //�豸״̬��Ϣ����
      strcpy(char_Device_status_Message,DEFAULT_MESSAGE);

      //������Ϣ
      int_ReturnValue_from_Send_or_Recive=send(sck_Client_Socket,char_Device_status_Message,strlen(char_Device_status_Message),0);
      if ((int_ReturnValue_from_Send_or_Recive==0) || (int_ReturnValue_from_Send_or_Recive==SOCKET_ERROR))
        {
           printf("����ʧ��\n");
           break;
        }
	  Sleep(1500);
    } //end while(1):ѭ�����պͷ���

  //�ر�Socket
  closesocket(sck_Client_Socket);
  WSACleanup();
  return 0;
}