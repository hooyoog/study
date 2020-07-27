#define W32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS//仅windows起效

#define _CRT_SECURE_NO_WARNINGS

#include<WinSock2.h>
#include<Windows.h>
#include<stdio.h>
#include<iostream>

using namespace std;

//#pragma* comment(lib,ws2_32.lib)//█尽在windows中起效


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



struct ClientWuJiang :public DataHeader
{
	ClientWuJiang() {
		dataLength = sizeof(ClientWuJiang);
		cmd = CMD_TO_CLIENT;
	}
	char name[32];
	int hp;
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
	int hp;
};

WuJiangResult* xiaHouDun;





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

int main() {


	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);

	/////////////////////
	//█新建Socket█
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	//█连接并判断█
	int ret = connect(_sock, (sockaddr*)&_sin, sizeof(sockaddr_in));
	if (ret == SOCKET_ERROR) {
		printf("SOCKET_ERROR\n");
	}
	else {

		printf("CONNECT SUCCUSSE!!!\n");
	}


	char cmdBuf[128] = {};
	

	while (1) {
		
	
		scanf("%s", cmdBuf);

		if (0 == strcmp(cmdBuf, "exit")) {
			printf("退出\n");
			break;
		}
		else if (0 == strcmp(cmdBuf, "start")) {
			
			StarGame start;
			send(_sock, (const char*)&start, sizeof(StarGame), 0);
			

			char szRecv[1024] = {};
			
			int nLen = recv(_sock, szRecv, sizeof(DataHeader), 0);
			
			if (nLen <= 0) {
				printf("客户端退出，任务结束\n");
				break;
			}
			DataHeader* header = (DataHeader*)szRecv;
			
			recv(_sock, szRecv + sizeof(DataHeader), header->dataLength - sizeof(DataHeader), 0);
			
			printf("--------收了--------\n");

			ClientWuJiang* wuJiang = (ClientWuJiang*)szRecv;
			printf("武将名字：%s,武将HP：%d\n", wuJiang->name, wuJiang->hp);
			



			recv(_sock, szRecv, sizeof(DataHeader), 0);

			header = (DataHeader*)szRecv;

			recv(_sock, szRecv + sizeof(DataHeader), header->dataLength - sizeof(DataHeader), 0);

			printf("--------收了2--------\n");

			wuJiang = (ClientWuJiang*)szRecv;
			printf("武将名字：%s,武将HP：%d\n", wuJiang->name, wuJiang->hp);
		
		}else {
			printf("不支持的命令,重新输入：\n");
		}
	
	
	}



	//█关闭█
	closesocket(_sock);

	/////////////////////
	WSACleanup();

	int x;
	std::cin >> x;

	printf("结束，并退出");
	//char s;
	getchar();

	return 0;



}