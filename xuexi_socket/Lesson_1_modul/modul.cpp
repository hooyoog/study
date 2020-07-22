#define W32_LEAN_AND_MEAN

#include<WinSock2.h>
#include<Windows.h>





int main() {

	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);

	WSACleanup();
	/////////业务逻辑写在这里///////////



	///////////////////
	return 0;
}