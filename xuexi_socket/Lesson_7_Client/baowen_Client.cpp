#define W32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS//仅windows起效

#define _CRT_SECURE_NO_WARNINGS

#include<WinSock2.h>
#include<Windows.h>
#include<stdio.h>
#include<iostream>

//定义两种状态登录与退出
enum CMD
{
	CMD_LOGIN,
	CMD_LOGOUT,
	CMD_ERROR
};


//匹配一下4个消息结构器
struct DataHeader
{
	short dataLength;//数据长度
	short cmd;//命令
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

	/////////////////////
	//████新建Socket████
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	//████连接并判断████
	int ret = connect(_sock, (sockaddr*)&_sin, sizeof(sockaddr_in));
	if (ret == SOCKET_ERROR) {
		printf("SOCKET_ERROR\n");
	}
	else {

		printf("CONNECT SUCCUSSE!!!\n");
	}

	//████输入请求████
	char cmdBuf[128] = {};//申请客户端字符串命令空间


	while (1) {//连接成功后加入循环
		//输入
		scanf("%s", cmdBuf);

		//████判断请求████
		//判断自己写的是啥，是否是退出
		if (0 == strcmp(cmdBuf, "exit")) {
			printf("退出\n");
			break;
		}
		else if (0 == strcmp(cmdBuf, "login")) {
			//████发送请求████
			//发送给服务器login

			
			

			//定义数据头-包头
			DataHeader dh = { sizeof(Login),CMD_LOGIN };
			//发送->包头
			send(_sock, (const char*)&dh, sizeof(dh), 0);

			//发送->包体
			Login login = { "username","abcd1234" };//定义数据
			//目前服务器没有判断，所以将会直接通过
			send(_sock, (const char*)&login, sizeof(login), 0);

			//████接收服务器返回数据████
			//先接受 包头
			DataHeader retHeader = {};
			recv(_sock, (char*)&retHeader, sizeof(retHeader), 0);

			//后接受包体
			LoginResult loginRet = {};
			recv(_sock, (char*)&loginRet, sizeof(LoginResult), 0);

			printf("LoginResult: %d\n", loginRet.result);

		}
		else if (0 == strcmp(cmdBuf, "logout")) {
			//████发送请求████
			//否则发送给服务器退出命令
			Logout logout = { "username" };
			DataHeader dh = { sizeof(logout),CMD_LOGOUT };
			//发送->包头
			send(_sock, (const char*)&dh, sizeof(dh), 0);

			//发送->包体
			send(_sock, (const char*)&logout, sizeof(logout), 0);

			//████接收服务器返回数据████
			//先接受 包头
			DataHeader retHeader = {};
			recv(_sock, (char*)&retHeader, sizeof(retHeader), 0);

			//后接受 包体
			LoginResult logoutRet = {};
			recv(_sock, (char*)&logoutRet, sizeof(logoutRet), 0);

			printf("LoginResult: %d\n", logoutRet.result);


		}
		else {
			printf("不支持的命令,重新输入：\n");
		}


	}



	//████关闭████
	closesocket(_sock);

	/////////////////////
	WSACleanup();

	int x;
	std::cin>> x;

	printf("结束，并退出");
	//char s;
	getchar();

	return 0;
}