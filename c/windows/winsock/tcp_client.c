//程序名：Client.c
//
//程序功能：本程序为通信网络系统设备状态发送端。它通过TCP连接设备状态接收端，发送设备状态信息，并接收接收端的回传信息。
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
BOOL bool_SentOnly=TRUE;              //TRUE:只发送信息，不接收

int main()
{
  WSADATA  wsd;
  SOCKET   sck_Client_Socket;
  char     char_Message_from_Server[DEFAULT_BUFFER];
  int      int_ReturnValue_from_Send_or_Recive;

  struct sockaddr_in server;

  //Socket初始化
  if (WSAStartup(MAKEWORD(2,2),&wsd)!=0)
    {
       printf("Socket初始化失败\n");
       return 1;
    }

  //创建Socket
  sck_Client_Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
  if (sck_Client_Socket==INVALID_SOCKET)
    {
       printf("创建Socket失败\n");
       return 1;
    }

  //填写服务器信息
  strcpy(char_Server_IP_Address,DEFAULT_IP_Address);
  server.sin_family=AF_INET;
  server.sin_port=htons(int_Server_IP_Port);//htons和htonl都用于
  server.sin_addr.s_addr = inet_addr(char_Server_IP_Address);

  //连接服务器
  if (connect(sck_Client_Socket,(struct sockaddr far *)&server,sizeof(server))==SOCKET_ERROR)
    {
       printf("连接失败\n");
       return 1;
    }

  //循环接收和发送
  while(1)
    {
      if (bool_SentOnly==FALSE)
        {
         //接收信息
         int_ReturnValue_from_Send_or_Recive=recv(sck_Client_Socket,char_Message_from_Server,DEFAULT_BUFFER,0);
         if ((int_ReturnValue_from_Send_or_Recive==0) || (int_ReturnValue_from_Send_or_Recive==SOCKET_ERROR))
           {
              printf("接收失败\n");
              break;
           }
         char_Message_from_Server[int_ReturnValue_from_Send_or_Recive]='\0';
         printf("接收信息 [%d bytes]: '%s'\n",int_ReturnValue_from_Send_or_Recive,char_Message_from_Server);
        }

      //设备状态信息加载
      strcpy(char_Device_status_Message,DEFAULT_MESSAGE);

      //发送信息
      int_ReturnValue_from_Send_or_Recive=send(sck_Client_Socket,char_Device_status_Message,strlen(char_Device_status_Message),0);
      if ((int_ReturnValue_from_Send_or_Recive==0) || (int_ReturnValue_from_Send_or_Recive==SOCKET_ERROR))
        {
           printf("发送失败\n");
           break;
        }
	  Sleep(1500);
    } //end while(1):循环接收和发送

  //关闭Socket
  closesocket(sck_Client_Socket);
  WSACleanup();
  return 0;
}