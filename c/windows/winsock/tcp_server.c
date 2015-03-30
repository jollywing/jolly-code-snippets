//��������Server.c
//
//�����ܣ�������Ϊͨ������ϵͳ�豸״̬���նˡ��������豸״̬���Ͷ˵����Ӳ����������̣߳����߳̽����豸״̬��Ϣ�������Ͷ˵���ѯ����Ϣ��
//
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_PORT 5150
#define DEFAULT_BUFFER 1024
#define DEFAULT_MESSAGE "Message from Server"

char char_Server_IP_Address[128],char_Server_Return_Message[1024];
int  int_Server_IP_Port=DEFAULT_PORT;
BOOL bool_ReciveOnly=TRUE;              //TRUE:ֻ������Ϣ��������

//������ClientThread����Ϊ�̱߳����á�
//
//�������ܣ���ȡ���Ͷ���������Ϣ����������Ӧ��Ϣ��
DWORD WINAPI ClientThread(LPVOID lpParam)
{
  SOCKET sock=(SOCKET)lpParam;
  char   char_Buffer[DEFAULT_BUFFER];
  int    int_ReturnValue_from_recv_or_sent;

  while(1)
  {
    //�������϶�ȡ����
    int_ReturnValue_from_recv_or_sent=recv(sock,char_Buffer,DEFAULT_BUFFER,0);
    if ((int_ReturnValue_from_recv_or_sent==0)||(int_ReturnValue_from_recv_or_sent==SOCKET_ERROR))
    {
       printf("������ʧ��\n");
       break;
    }
    char_Buffer[int_ReturnValue_from_recv_or_sent]='\0';
    printf("��ȡ�������ǣ�'%s'\n\n",char_Buffer);

    if(bool_ReciveOnly==FALSE)
    {
      //������Ϣ����
      strcpy(char_Server_Return_Message,DEFAULT_MESSAGE);

      //��������
      int_ReturnValue_from_recv_or_sent=send(sock,char_Server_Return_Message,strlen(char_Server_Return_Message),0);
      if ((int_ReturnValue_from_recv_or_sent==0) || (int_ReturnValue_from_recv_or_sent==SOCKET_ERROR))
        {
           printf("����ʧ��\n");
           break;
        }
    }
  }
  return 0;
}

//������
int main()
{
  WSADATA  wsd;
  SOCKET   sck_Client_Socket,sck_Server_Listen;
  int      int_Client_Address_Size;
  HANDLE   handle_Thread;
  DWORD    dword_ThreadID;

  struct sockaddr_in server,Client;

  //Socket��ʼ��
  if (WSAStartup(MAKEWORD(2,2),&wsd)!=0)
    {
       printf("Socket��ʼ��ʧ��\n");
       return 1;
    }

  //����Socket
  sck_Server_Listen=socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
  if (sck_Server_Listen ==SOCKET_ERROR)
    {
       printf("����Socketʧ��\n");
       return 1;
    }

  //��д��������Ϣ
  server.sin_family=AF_INET;
  server.sin_port=htons(int_Server_IP_Port);
  server.sin_addr.s_addr = htonl(INADDR_ANY);

  //��
  if (bind(sck_Server_Listen,(struct sockaddr *)&server,sizeof(server))==SOCKET_ERROR)
    {
       printf("��ʧ��\n");
       return 1;
    }

  //����
  listen(sck_Server_Listen,8);

  //ѭ������������Ϣ�ʹ����߳̽��д����ɴ��������ӣ�
  while(1)
    {
      //����������Ϣ
      int_Client_Address_Size=sizeof(Client);
      sck_Client_Socket=accept(sck_Server_Listen,(struct sockaddr *)&Client,&int_Client_Address_Size);
      if (sck_Client_Socket==INVALID_SOCKET)
        {
           printf("����������Ϣʧ��\n");
           break;
        }
      printf("�����յķ��Ͷ���Ϣ��%s:%d\n",inet_ntoa(Client.sin_addr),ntohs(Client.sin_port));

      //�����̣߳����շ��Ͷ���������Ϣ
      handle_Thread=CreateThread(NULL,0,ClientThread,(LPVOID)sck_Client_Socket,0,&dword_ThreadID);
      if (handle_Thread==NULL)
        {
           printf("�����߳�ʧ��\n");
           break;
        }
      CloseHandle(handle_Thread);
    } //end while(1):ѭ������������Ϣ�ʹ����߳̽��д���

  //�ر�Socket
  closesocket(sck_Client_Socket);
  WSACleanup();
  return 0;
}