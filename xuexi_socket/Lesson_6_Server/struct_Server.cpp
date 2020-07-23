#define W32_LEAN_AND_MEAN

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<WinSock2.h>
#include<Windows.h>
#include<stdio.h>

#include<iostream>


int main() {

	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);


	//////
	//████新建socket████
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in _sin = {};//为连接申请空间
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);//绑定端口号
	//_sin.sin_addr.S_un.S_addr = INADDR_ANY;//inet_addr("127.0.0.1");
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//设置IP


	//████绑定端口████
	if (SOCKET_ERROR == bind(_sock, (sockaddr*)&_sin, sizeof(_sin))) {
		printf("绑定错误\n");
	}
	else {
		printf("绑定端口成功\n");
	}


	//████监听端口████
	listen(_sock, 5);


	sockaddr_in clientAddr = {};
	int nAddrLen = sizeof(sockaddr_in);//为客户端的数据申请空间
	SOCKET _cSock = INVALID_SOCKET;//建立客户端的socket

	_cSock = accept(_sock, (sockaddr*)&clientAddr, &nAddrLen);
	if (_cSock == INVALID_SOCKET) {
		printf("连接错误\n");
	}

	printf("客户端连接，SOCKET：%d - IP：%s\n", (int)_cSock, inet_ntoa(clientAddr.sin_addr));

	//创建接收缓冲区
	char _recvBuf[128] = {};
	while (1) {//不停的在接受就是监听
		//████发送数据████
		//████接收数据请求████
		int nLen = recv(_cSock, _recvBuf, 128, 0);//以前服务器不接收
		if (nLen <= 0) {
			printf("客户端退出，任务结束\n");
			break;
		}
		//████处理请求，并发送数据████
		printf("收到客户申请:%s\n", _recvBuf);
		if (0 == strcmp(_recvBuf, "getName")) {
			char msgBuf[] = "ShiJin";
			send(_cSock, msgBuf, strlen(msgBuf) + 1, 0);
		}
		else if (0 == strcmp(_recvBuf, "getAge")) {
			char msgBuf[] = "18";
			send(_cSock, msgBuf, strlen(msgBuf) + 1, 0);
		}
		else {
			char msgBuf[] = "???";
			send(_cSock, msgBuf, strlen(msgBuf) + 1, 0);
		}


	}



	//████关闭SOCKET████
	closesocket(_sock);
	/////////////////////

	char s;
	std::cin >> s;
	WSACleanup();


	return 0;
}