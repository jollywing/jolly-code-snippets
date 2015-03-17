//程序名：Server.c
//
//程序功能：本程序为通信网络系统设备询问及状态接收端。它向设备状态发送端发送设备状态询问信息，并接收设备状态发送端的设备状态信息。
//

#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>


#define DEFAULT_PORT 5555
#define DEFAULT_BUFFER 1024
#define DEFAULT_MESSAGE "中国人民解放军国防科学技术大学"
#define DEFAULT_IP_Address "127.0.0.1"

char char_Client_IP_Address[128];
char char_Server_Sendto_Message[1024];
short int_Server_IP_Port=DEFAULT_PORT;


//主程序
int main()
{
  WSADATA  wsd;
  SOCKET   sck_Server_Socket;
  struct sockaddr_in Client;
  int      int_Sendto_Message_Size;
  int      int_ReturnValue_from_sendto;

  //Socket初始化，WSAStartup为windows扩展函数，返回值0表示成功

  if (WSAStartup(MAKEWORD(2,2),&wsd)!=0)
    {
       printf("Socket初始化失败\n");
       return 1;
    }

  //创建Socket，socket()返回引用新套接口的描述字
  sck_Server_Socket=socket(AF_INET,SOCK_DGRAM,0);
  if (sck_Server_Socket==INVALID_SOCKET)
    {
       printf("创建Socket失败\n");
       return 1;
    }

  //填写客户端信息
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
		  printf("gethostbyname失败\n");
		  WSACleanup();
		  return 1;
	  }
  }
  //循环发送询问信息
  while(1)
    {
      //询问信息加载
      strcpy(char_Server_Sendto_Message,DEFAULT_MESSAGE);
      int_Sendto_Message_Size=sizeof(Client);

      //发送信息
      int_ReturnValue_from_sendto=sendto(sck_Server_Socket,char_Server_Sendto_Message,strlen(char_Server_Sendto_Message),0,(SOCKADDR *)&Client,sizeof(Client));
      if (int_ReturnValue_from_sendto==SOCKET_ERROR)
        {
           printf("发送信息失败\n");
           break;
        }

      Sleep(1000);
    } //end while(1):循环接收连接信息和创建线程进行处理

  //关闭Socket，服务器端
  closesocket(sck_Server_Socket);//实际没有执行
  WSACleanup();
  return 0;
}