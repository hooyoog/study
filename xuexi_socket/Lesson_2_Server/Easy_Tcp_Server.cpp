#define W32_LEAN_AND_MEAN

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<WinSock2.h>
#include<Windows.h>
#include<stdio.h>




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
	char msgBuf[] = "Hello , i'm Server.\n";//新建了一个数据用于回复
	

	while (1) {//不停的在接受就是监听
		//████接收数据████

		//接受连接
		_cSock = accept(_sock, (sockaddr*)&clientAddr, &nAddrLen);//这个方法将返还一个socket
		if (_cSock == INVALID_SOCKET) {
			printf("连接错误\n");
		}
		printf("客户端连接，IP：%s\n", inet_ntoa(clientAddr.sin_addr));

		//████发送数据████

		send(_cSock, msgBuf, (strlen(msgBuf) + 1), 0);
	}



	//████关闭SOCKET████
	closesocket(_sock);
	/////////////////////


	WSACleanup();


	return 0;
}