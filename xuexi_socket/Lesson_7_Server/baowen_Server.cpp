#define W32_LEAN_AND_MEAN

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<WinSock2.h>
#include<Windows.h>
#include<stdio.h>

//#pragma* comment(lib,ws2_32.lib)//████尽在windows中起效

//████网络数据包是一种固定的网络传送格式
//████首先要定义-包头
//████其次要定义-包体
//████客户端与服务器，都先读包头，根据包头，开辟包体数据的内存空间

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


	//////
	//████新建socket████
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	//_sin.sin_addr.S_un.S_addr = INADDR_ANY;//inet_addr("127.0.0.1");
	_sin.sin_addr.S_un.S_addr = INADDR_ANY;


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
	int nAddrLen = sizeof(sockaddr_in);
	SOCKET _cSock = INVALID_SOCKET;
	

	//████接收连接████
	_cSock = accept(_sock, (sockaddr*)&clientAddr, &nAddrLen);
	if (_cSock == INVALID_SOCKET) {
		printf("连接错误\n");
	}
	printf("客户端连接，SOCKET：%d - IP：%s\n", (int)_cSock, inet_ntoa(clientAddr.sin_addr));

	//创建接收缓冲区
	//以前是用这个来接收的char _recvBuf[128] = {};
	//现在不能用简单的接收方发了*

	while (1) {
		//*而是使用包头
		DataHeader header = {};
		//████接收数据请求████

		int nLen = recv(_cSock, (char*)&header, sizeof(DataHeader), 0);
		if (nLen <= 0) {
			printf("客户端退出，任务结束\n");
			break;
		}
		//████处理请求，并发送数据███
		printf("收到命令:%d ，数据长度:%d\n", header.cmd, header.dataLength);//接收命令与数据长度

		//判断
		switch (header.cmd) {
		case CMD_LOGIN: {
			
			Login login = {};
			recv(_cSock, (char*)&login, sizeof(Login), 0);
			//if (login.passWord == "abcd1234") {
				printf("密码对了%d\n", &login.passWord);
			//}
			//忽略判断用户密码是否正确
			LoginResult ret = { 1 };
			//先发包头
			send(_cSock, (char*)&header, sizeof(DataHeader), 0);
			send(_cSock, (char*)&ret, sizeof(LoginResult), 0);

		}
					  break;

					  //登出
		case CMD_LOGOUT: {
			Logout logout = {};
			recv(_cSock, (char*)&logout, sizeof(Logout), 0);
			//
			LogoutResult ret = { 1 };
			//先发包头
			send(_cSock, (char*)&header, sizeof(DataHeader), 0);
			send(_cSock, (char*)&ret, sizeof(LogoutResult), 0);
		}
					   break;

					   //默认判断错误输入
		default:
			header.cmd = CMD_ERROR;
			header.dataLength = 0;
			send(_cSock, (char*)&header, sizeof(header), 0);

			break;
		}




	}



	//████关闭SOCKET████
	closesocket(_sock);
	/////////////////////


	WSACleanup();
	printf("结束，并退出");
	//char s;
	getchar();

	return 0;
}