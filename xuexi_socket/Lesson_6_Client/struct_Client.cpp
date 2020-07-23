#define W32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include<WinSock2.h>
#include<Windows.h>
#include<stdio.h>

#include<iostream>




int main() {

	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);

	/////////////////////

	SOCKET _sock = socket(AF_INET, SOCK_STREAM, 0);//建立客户端socket
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	int ret = connect(_sock, (sockaddr*)&_sin, sizeof(sockaddr_in));//建立连接
	if (ret == SOCKET_ERROR) {
		printf("SOCKET_ERROR\n");
	}
	else {
		printf("CONNECT SUCCUSSE!!!\n");
	}


	//char recvBuf[256] = {};
	//int nlen = recv(_sock, recvBuf, 256, 0);//recv（）是接收
	//if (nlen > 0) {
	//	printf("OK:%s", recvBuf);
	//}
	//else {
	//	printf("ERROR");
	//}
	char cmdBuf[128] = {};//申请客户端字符串空间


	while (1) {//连接成功后加入循环
		//输入
		scanf("%s", cmdBuf);

		//████判断请求████
		//判断自己写的是啥，是否是退出
		if (0 == strcmp(cmdBuf, "exit")) {
			break;
		}
		else {
			//████发送请求████
			//否则发送给服务器
			send(_sock, cmdBuf, strlen(cmdBuf) + 1, 0);
		}

		//████把接收数据移植到主循环里████
		char recvBuf[128] = {};
		int nlen = recv(_sock, recvBuf, 128, 0);
		if (nlen > 0) {
			printf("OK:%s\n", recvBuf);
		}
		else {
			printf("ERROR");
		}
	}


	closesocket(_sock);
	char s;
	std::cin >> s;
	/////////////////////
	WSACleanup();





	return 0;

}



