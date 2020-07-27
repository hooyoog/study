
#ifdef _WIN32

#define W32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS//仅windows起效
#define _CRT_SECURE_NO_WARNINGS
#include<WinSock2.h>
#include<Windows.h>
#else
#include<unistd.h> //nui std
#include<arpa/inet.h>
#include<string.h>
#define SOCKET int
#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR            (-1)

#endif

#include<stdio.h>
#include<iostream>

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

struct Login :public DataHeader
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

#ifdef _WIN32
    WORD ver = MAKEWORD(2, 2);
    WSADATA dat;
    WSAStartup(ver, &dat);
#endif


    SOCKET _sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in _sin = {};
    _sin.sin_family = AF_INET;
    _sin.sin_port = htons(4567);
#ifdef _WIN32
    _sin.sin_addr.S_un.S_addr = inet_addr("192.168.79.1");
#else
    _sin.sin_addr.s_addr = inet_addr("192.168.79.1");
#endif
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
        //输入
        scanf("%s", cmdBuf);

        if (0 == strcmp(cmdBuf, "exit")) {
            printf("退出\n");
            break;
        }
        else if (0 == strcmp(cmdBuf, "login")) {



            //发送->包
            Login login;
            strcpy(login.userName, "shijin");
            strcpy(login.passWord, "aaaaaaaaaa");
            send(_sock, (const char*)&login, sizeof(login), 0);



            //后接受包体
            LoginResult loginRet = {};
            recv(_sock, (char*)&loginRet, sizeof(LoginResult), 0);
            printf("LoginResult: %d\n", loginRet.result);

        }
        else if (0 == strcmp(cmdBuf, "logout")) {
            //发送->包体
            Logout logout;
            strcpy(logout.userName, "shijin");
            send(_sock, (const char*)&logout, sizeof(logout), 0);



            //后接受 包
            LoginResult logoutRet = {};
            recv(_sock, (char*)&logoutRet, sizeof(logoutRet), 0);
            printf("LoginResult: %d\n", logoutRet.result);


        }
        else {
            printf("不支持的命令,重新输入：\n");
        }


    }


    //█关闭█
#ifdef _WIN32
    closesocket(_sock);

    WSACleanup();

#else
    close(_sock);

#endif
    int x;
    std::cin >> x;

    printf("结束，并退出");
    //char s;
    getchar();
    return 0;
}
