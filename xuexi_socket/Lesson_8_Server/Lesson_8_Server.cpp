#define W32_LEAN_AND_MEAN

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<WinSock2.h>
#include<Windows.h>
#include<stdio.h>

//#pragma* comment(lib,ws2_32.lib)//████尽在windows中起效


enum CMD
{
	CMD_LOGIN,
	CMD_LOGOUT,
	CMD_ERROR
};


struct DataHeader
{
	short dataLength;
	short cmd;
};

struct Login
{
	char userName[32];
	char passWord[32];
};

struct LoginResult
{
	int result;

};

struct Logout
{
	char userName[32];

};
struct LogoutResult
{
	int result;

};



int main() {

	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);


	
	//█新建socket█
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	_sin.sin_addr.S_un.S_addr = INADDR_ANY;


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
		
		DataHeader header = {};
		//█接收数据请求█

		int nLen = recv(_cSock, (char*)&header, sizeof(DataHeader), 0);
		//因为客户端肯定是先发包头
		if (nLen <= 0) {
			printf("客户端退出，任务结束\n");
			break;
		}
		//█处理请求，并发送数据█
		printf("收到命令:%d ，数据长度:%d\n", header.cmd, header.dataLength);


		switch (header.cmd) {
		case CMD_LOGIN: {

			Login login = {};
			recv(_cSock, (char*)&login, sizeof(Login), 0);
			
			printf("密码对了%d\n", &login.passWord);
		
			LoginResult ret = { 1 };
			
			send(_cSock, (char*)&header, sizeof(DataHeader), 0);
			send(_cSock, (char*)&ret, sizeof(LoginResult), 0);

		}
					  break;

				
		case CMD_LOGOUT: {
			Logout logout = {};
			recv(_cSock, (char*)&logout, sizeof(Logout), 0);
			
			LogoutResult ret = { 1 };
			
			send(_cSock, (char*)&header, sizeof(DataHeader), 0);
			send(_cSock, (char*)&ret, sizeof(LogoutResult), 0);
		}
					   break;

					   
		default:
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