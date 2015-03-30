//��������Server.c
//
//�����ܣ�������Ϊͨ������ϵͳ�豸ѯ�ʼ�״̬���նˡ������豸״̬���Ͷ˷����豸״̬ѯ����Ϣ���������豸״̬���Ͷ˵��豸״̬��Ϣ��
//

#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>


#define DEFAULT_PORT 5555
#define DEFAULT_BUFFER 1024
#define DEFAULT_MESSAGE "�й������ž�������ѧ������ѧ"
#define DEFAULT_IP_Address "127.0.0.1"

char char_Client_IP_Address[128];
char char_Server_Sendto_Message[1024];
short int_Server_IP_Port=DEFAULT_PORT;


//������
int main()
{
  WSADATA  wsd;
  SOCKET   sck_Server_Socket;
  struct sockaddr_in Client;
  int      int_Sendto_Message_Size;
  int      int_ReturnValue_from_sendto;

  //Socket��ʼ����WSAStartupΪwindows��չ����������ֵ0��ʾ�ɹ�

  if (WSAStartup(MAKEWORD(2,2),&wsd)!=0)
    {
       printf("Socket��ʼ��ʧ��\n");
       return 1;
    }

  //����Socket��socket()�����������׽ӿڵ�������
  sck_Server_Socket=socket(AF_INET,SOCK_DGRAM,0);
  if (sck_Server_Socket==INVALID_SOCKET)
    {
       printf("����Socketʧ��\n");
       return 1;
    }

  //��д�ͻ�����Ϣ
  strcpy(char_Client_IP_Address,DEFAULT_IP_Address);

  Client.sin_family=AF_INET;
  Client.sin_port=htons((short)int_Server_IP_Port);
  Client.sin_addr .s_addr = inet_addr(char_Client_IP_Address);
  if((Client.sin_addr.s_addr = inet_addr(char_Client_IP_Address))==INADDR_NONE)
  {
	  struct hostent *host=NULL;
	  host=gethostbyname(char_Client_IP_Address);
	  if(host)
		  CopyMemory(&Client.sin_addr,host->h_addr_list[0],host->h_length);
	  else
	  {
		  printf("gethostbynameʧ��\n");
		  WSACleanup();
		  return 1;
	  }
  }
  //ѭ������ѯ����Ϣ
  while(1)
    {
      //ѯ����Ϣ����
      strcpy(char_Server_Sendto_Message,DEFAULT_MESSAGE);
      int_Sendto_Message_Size=sizeof(Client);

      //������Ϣ
      int_ReturnValue_from_sendto=sendto(sck_Server_Socket,char_Server_Sendto_Message,strlen(char_Server_Sendto_Message),0,(SOCKADDR *)&Client,sizeof(Client));
      if (int_ReturnValue_from_sendto==SOCKET_ERROR)
        {
           printf("������Ϣʧ��\n");
           break;
        }

      Sleep(1000);
    } //end while(1):ѭ������������Ϣ�ʹ����߳̽��д���

  //�ر�Socket����������
  closesocket(sck_Server_Socket);//ʵ��û��ִ��
  WSACleanup();
  return 0;
}