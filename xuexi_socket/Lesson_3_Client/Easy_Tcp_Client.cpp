#define W32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<WinSock2.h>
#include<Windows.h>
#include<stdio.h>




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


	char recvBuf[256] = {};
	int nlen = recv(_sock, recvBuf, 256, 0);//recv（）是接收
	if (nlen > 0) {
		printf("OK:%s", recvBuf);
	}
	else {
		printf("ERROR");
	}

	closesocket(_sock);
	char s;
	getchar();
	/////////////////////
	WSACleanup();





	return 0;
}