#define W32_LEAN_AND_MEAN

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include<WinSock2.h>
#include<Windows.h>
#include<stdio.h>
#include<iostream>
#include<string>




using namespace std;

//#pragma* comment(lib,ws2_32.lib)//████尽在windows中起效


enum CMD
{
	CMD_1,//武将1
	CMD_2,//武将2
	CMD_DA,
	CMD_START,

	CMD_START_RESULT,
	CMD_DA_RESULT,
	CMD_DEAD_RESULT,

	CMD_TO_CLIENT,

	CMD_ERROR
};

struct DataHeader
{
	short dataLength;
	short cmd;
	
};

struct WuJiangResult :public DataHeader
{
	WuJiangResult() {
		dataLength = sizeof(WuJiangResult);
		cmd = CMD_START;
		strcpy(name, "夏侯惇");
		hp = 200;
	}
	char name[32];
	int hp ;
};







struct Da :public DataHeader
{
	Da() {
		dataLength = sizeof(Da);
		cmd = CMD_DA;
	
		gingJiLi = 100;
	}
	int gingJiLi;

};

struct StarGame :public DataHeader
{
	StarGame() {
		dataLength = sizeof(StarGame);
		cmd = CMD_START;
	}

};

WuJiangResult xiaHouDun;





int main() {

	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);



	//█新建socket█
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	_sin.sin_addr.S_un.S_addr = INADDR_ANY;//inet_addr("127.0.0.1");


	//█绑定端口█
	if (SOCKET_ERROR == bind(_sock, (sockaddr*)&_sin, sizeof(_sin))) {
		printf("绑定错误\n");
	}
	else {
		printf("绑定端口成功\n");
	}


	//█监听端口█
	listen(_sock, 5);
	sockaddr_in clientAddr = {};
	int nAddrLen = sizeof(sockaddr_in);
	SOCKET _cSock = INVALID_SOCKET;


	//█接收连接█
	_cSock = accept(_sock, (sockaddr*)&clientAddr, &nAddrLen);
	if (_cSock == INVALID_SOCKET) {
		printf("连接错误\n");
	}
	printf("客户端连接，SOCKET：%d - IP：%s\n", (int)_cSock, inet_ntoa(clientAddr.sin_addr));


	while (1) {


		char szRecv[2048] = {};



		//先接受头
		int nLen = recv(_cSock, szRecv, sizeof(DataHeader), 0);

		DataHeader* header = (DataHeader*)szRecv;



		if (nLen <= 0) {
			printf("客户端退出，任务结束\n");
			break;
		}



		switch (header->cmd) {
			case CMD_START: {


				printf("好歹进入start了\n");
				//recv(_cSock, szRecv + sizeof(DataHeader), header->dataLength - sizeof(DataHeader), 0);
				//printf("好歹接收成功了\n");


				
				
				send(_cSock, (char*)&xiaHouDun, sizeof(WuJiangResult), 0);

				printf("发送完毕，爱收到不受到:-----%d\n",xiaHouDun.hp);

				xiaHouDun.hp -= 100;
				printf("挨打测试:-----%d\n", xiaHouDun.hp);

				send(_cSock, (char*)&xiaHouDun, sizeof(WuJiangResult), 0);


			}break;


			case CMD_DA: {

				

				recv(_cSock, szRecv + sizeof(DataHeader), header->dataLength - sizeof(DataHeader), 0);

				Da* da = (Da*)szRecv;
				
				printf("用户攻击力%d\n",da->gingJiLi);

				if (xiaHouDun.hp>0) {
					xiaHouDun.hp -= da->gingJiLi;
					if (xiaHouDun.hp<=0) {
						send(_cSock, (char*)&xiaHouDun, sizeof(WuJiangResult), 0);
						printf("死了\n");
					}
					else {
						printf("继续打\n");

						send(_cSock, (char*)&xiaHouDun, sizeof(WuJiangResult), 0);
					}
				}
				else {
					printf("死了还打\n");
					DataHeader header;
					header.cmd = CMD_ERROR;
					header.dataLength = 0;
					send(_cSock, (char*)&header, sizeof(header), 0);
				}
				

				

			}break;

			default:
				DataHeader header;
				header.cmd = CMD_ERROR;
				header.dataLength = 0;
				send(_cSock, (char*)&header, sizeof(header), 0);

				break;
		}



	}



	//█关闭SOCKET█
	closesocket(_sock);



	WSACleanup();
	printf("结束，并退出");
	getchar();

	return 0;
}