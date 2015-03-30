//程序名：Server.c
//
//程序功能：本程序为通信网络系统设备状态接收端。它接收设备状态发送端的连接并创建接收线程，由线程接收设备状态信息，并向发送端的送询问信息。
//
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_PORT 5150
#define DEFAULT_BUFFER 1024
#define DEFAULT_MESSAGE "Message from Server"

char char_Server_IP_Address[128],char_Server_Return_Message[1024];
int  int_Server_IP_Port=DEFAULT_PORT;
BOOL bool_ReciveOnly=TRUE;              //TRUE:只接收信息，不发送

//函数：ClientThread，作为线程被调用。
//
//函数功能：读取发送端送来的信息，并发送相应信息。
DWORD WINAPI ClientThread(LPVOID lpParam)
{
  SOCKET sock=(SOCKET)lpParam;
  char   char_Buffer[DEFAULT_BUFFER];
  int    int_ReturnValue_from_recv_or_sent;

  while(1)
  {
    //从网络上读取数据
    int_ReturnValue_from_recv_or_sent=recv(sock,char_Buffer,DEFAULT_BUFFER,0);
    if ((int_ReturnValue_from_recv_or_sent==0)||(int_ReturnValue_from_recv_or_sent==SOCKET_ERROR))
    {
       printf("读数据失败\n");
       break;
    }
    char_Buffer[int_ReturnValue_from_recv_or_sent]='\0';
    printf("读取的数据是：'%s'\n\n",char_Buffer);

    if(bool_ReciveOnly==FALSE)
    {
      //反馈信息加载
      strcpy(char_Server_Return_Message,DEFAULT_MESSAGE);

      //发送数据
      int_ReturnValue_from_recv_or_sent=send(sock,char_Server_Return_Message,strlen(char_Server_Return_Message),0);
      if ((int_ReturnValue_from_recv_or_sent==0) || (int_ReturnValue_from_recv_or_sent==SOCKET_ERROR))
        {
           printf("发送失败\n");
           break;
        }
    }
  }
  return 0;
}

//主程序
int main()
{
  WSADATA  wsd;
  SOCKET   sck_Client_Socket,sck_Server_Listen;
  int      int_Client_Address_Size;
  HANDLE   handle_Thread;
  DWORD    dword_ThreadID;

  struct sockaddr_in server,Client;

  //Socket初始化
  if (WSAStartup(MAKEWORD(2,2),&wsd)!=0)
    {
       printf("Socket初始化失败\n");
       return 1;
    }

  //创建Socket
  sck_Server_Listen=socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
  if (sck_Server_Listen ==SOCKET_ERROR)
    {
       printf("创建Socket失败\n");
       return 1;
    }

  //填写服务器信息
  server.sin_family=AF_INET;
  server.sin_port=htons(int_Server_IP_Port);
  server.sin_addr.s_addr = htonl(INADDR_ANY);

  //绑定
  if (bind(sck_Server_Listen,(struct sockaddr *)&server,sizeof(server))==SOCKET_ERROR)
    {
       printf("绑定失败\n");
       return 1;
    }

  //侦听
  listen(sck_Server_Listen,8);

  //循环接收连接信息和创建线程进行处理（可处理多个连接）
  while(1)
    {
      //接收连接信息
      int_Client_Address_Size=sizeof(Client);
      sck_Client_Socket=accept(sck_Server_Listen,(struct sockaddr *)&Client,&int_Client_Address_Size);
      if (sck_Client_Socket==INVALID_SOCKET)
        {
           printf("接收连接信息失败\n");
           break;
        }
      printf("被接收的发送端信息：%s:%d\n",inet_ntoa(Client.sin_addr),ntohs(Client.sin_port));

      //创建线程，接收发送端送来的信息
      handle_Thread=CreateThread(NULL,0,ClientThread,(LPVOID)sck_Client_Socket,0,&dword_ThreadID);
      if (handle_Thread==NULL)
        {
           printf("创建线程失败\n");
           break;
        }
      CloseHandle(handle_Thread);
    } //end while(1):循环接收连接信息和创建线程进行处理

  //关闭Socket
  closesocket(sck_Client_Socket);
  WSACleanup();
  return 0;
}