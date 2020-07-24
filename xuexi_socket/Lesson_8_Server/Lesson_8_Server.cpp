#define W32_LEAN_AND_MEAN

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<WinSock2.h>
#include<Windows.h>
#include<stdio.h>

//#pragma* comment(lib,ws2_32.lib)//████尽在windows中起效


enum CMD
{
	CMD_LOGIN,
	CMD_LOGIN_RESULT,
	CMD_LOGOUT,
	CMD_LOGOUT_RESULT,
	CMD_ERROR
};


struct DataHeader
{
	short dataLength;
	short cmd;
};

struct Login:public DataHeader
{
	Login() {
		dataLength = sizeof(Login);
		cmd = CMD_LOGIN;
	}
	char userName[32];
	char passWord[32];
};


struct LoginResult :public DataHeader
{
	LoginResult() {
		dataLength = sizeof(LoginResult);
		cmd = CMD_LOGIN_RESULT;
		result = 0;
	}
	int result;

};

struct Logout :public DataHeader
{
	Logout() {
		dataLength = sizeof(Logout);
		cmd = CMD_LOGOUT;
	}
	char userName[32];

};
struct LogoutResult :public DataHeader
{
	LogoutResult() {
		dataLength = sizeof(LogoutResult);
		cmd = CMD_LOGOUT_RESULT;
		result = 0;
	}
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
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");


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
		

		char szRecv[1024] = {};




		int nLen = recv(_cSock, szRecv, sizeof(DataHeader), 0);

		DataHeader* header = (DataHeader*)szRecv;




		
		if (nLen <= 0) {
			printf("客户端退出，任务结束\n");
			break;
		}





		switch (header->cmd) {
		case CMD_LOGIN: {

			
			
			recv(_cSock, szRecv +sizeof(DataHeader), header->dataLength - sizeof(DataHeader), 0);
			

			Login* login = (Login*)szRecv;//收到数据后，改为用指针

			printf("收到命令: CMD_LOGIN，数据长度:%d,username=%s, passWord=%s\n",
				login->dataLength, login->userName, login->passWord);//接收命令与数据长度





			LoginResult ret;
			send(_cSock, (char*)&ret, sizeof(LoginResult), 0);



		}
					  break;

				
		case CMD_LOGOUT: {
			Logout* logout = (Logout*)szRecv;
			recv(_cSock, szRecv + sizeof(DataHeader), header->dataLength - sizeof(DataHeader), 0);
			
			printf("收到命令: CMD_LOGIN，数据长度:%d,username=%s\n", 
				logout->dataLength, logout->userName);

			LogoutResult ret;
			send(_cSock, (char*)&ret, sizeof(LogoutResult), 0);
		}
					   break;

					   
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