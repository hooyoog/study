小志学习笔记
=============================
*主要工具： VS Studio；*    
*C++ 内容： C++服务器与客户端开发、linux游戏服务器开发，android\mac\ios\windows客户端开发；*      
*引擎内容： UE4、Unity、Cocos与服务器通讯*  

****
|作者|小志|
|---|---
|知乎|嚎呦啃
|公众号|微信hooyoog5
****
# 目录
* [第一章](#第一章)
* [第二章](#第二章)
* [向下跳转](#文本)
    * 普通文本
****

# 第一章
## 工具的设置与调试
|标题|内容|
|---|---
|项目->属性->常规->目录|```$(SolutionDir)/bin/$(Platform)/$(Configuration)/```  ```$(SolutionDir)/temp/$(Platform)/$(Configuration)/$(ProjectName)```
|连接器->输入->增加库|```ws2_32.lib;```
|避免vsStudio编译报错|```#define W32_LEAN_AND_MEAN```   ```#define _WINSOCK_DEPRECATED_NO_WARNINGS```

## github使用方法
1. 在github官网，创建新项目。在本地VS创建的解决方案文件夹里右键打开github工具
2. git config --global user.email "XXXXXXXX@qq.com" //输入一次就成
3. git config --global user.name "honeypet"//输入一次就成
4. git init
5. 设置并提交到官网上
git add .  
git commit -m "first commit"  
git remote add origin https://github.com/hooyoog/study.git  
git push -u origin master



****
# 第二章
***网络游戏开发***  

## 1.Lesson_1模板
*注意：关闭vsStudio,才能使用github*  

1. 模板在本工程的xuexi_socket/Lesson_1_*中  
2. 修改属性目录和连接器输入  


## 2.简单的socket服务器Lesson_2_Server  
1. 创建工程和连接器等
2. 写代码  

**原理**  
*网络编程虽然很难，但是干脆把他理解成往本地存储就不难了*  

|网络通讯|本地存储|
|---|---
|建立连接|相当于打开
|输入网络命令|相当于本地写写字板
|发送命令|相当于本地存储写字板内容
|关闭连接|关闭写字板 



**实践：搭建服务器**
| 名称 | 内容 |
|---|---
| 1.导入模板 | ```WORD ver = MAKEWORD(2, 2);```  ```WSADATA dat;```  ```WSAStartup(ver, &dat);```  
| 2.建立socket | 查看Lesson_2->socket()
| 3.绑定端口 | 查看Lesson_2->bind()
| 4.监听端口 | 查看Lesson_2->listen()
| 5.接收数据 | 查看Lesson_2->accept()
| 6.回发数据 | 查看Lesson_2->send()
| 7.关闭socket | 查看Lesson_2


## 3.简单的socket服务器Lesson_3_Client

1. 创建工程和连接器\复制模板等

2. 理解他

| 名称 | 内容 | 相当于 |
|---|---|---
| 1.建立客户端socket | 查看Lesson_3->socket() | 打开写字板
| 2.建立连接 | 查看Lesson_3->connect() | 打开写字板
| 3.接收数据 | 查看Lesson_3->recv() | 解析写字板内容，读取写字板内容
| 4.关闭 | 查看Lesson_3->closesocket() | 关闭写字板


3. 写代码  
*代码在Lesson_3_Client，历史第一次提交*   

4. 复习一下指针  
**说实在点什么是指针？**  
**反正返回值是地址的都能当指针，填进小括号里使用**  

| 名称 | 内容 |
|---|---
| 1.指针名字什么都不加是指针 | point
| 2.变量前面加&是指针 | &a
| 3.引用前面加&是指针 | &q
| 4.数组名字什么都不加是指针 | ```int []array  ---> array```
| 5.集合名字加&是指针 |  ```mySet={}  ---> &mySet```
| 6.迭代器压根就是指针 |  iterator  

*碰见这些就往需要指针的参数小括号里填*  
*如果需要强制类型转换，就转他（某类型```*```）后面跟着是个不得不被转换的指针*  

## 4.把服务器改成-先接收请求再判断并回复Lesson_4_Server
  
  **做几步就编译一下，不然长时间不编译，出错不知道出在哪里**   
  
```c
1. 删掉char msgBuf【】 
2. _recvBuf[128] = {}; //创建缓冲区  
3. 删掉send(_cSock, msgBuf, strlen(msgBuf) + 1, 0);  
4. 在while以上   
_cSock = accept(_sock, (sockaddr*)&clientAddr, &nAddrLen);
	if (_cSock == INVALID_SOCKET) {
		printf("连接错误\n");
	}
	printf("客户端连接，IP：%s\n", inet_ntoa(clientAddr.sin_addr));
5. int nLen=recv(_cSock, _recvBuf,128,0);  
		if (nLen <= 0) {  
			printf("客户端退出，任务结束\n");  
			break;  
		}  
		//████处理请求，并发送数据████  
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
```  
  
## 5.把客户端改成-先请求再接收回复Lesson_5_Client  
1. 新建工程，做哪些设置的事  
2. 删掉以前的缓冲区  
3. 新建128的缓冲区  
4. 在while循环里，首先要求客户输入  
5. 判断一下输入的内容  
6. 如果是合法内容，发送出去  
7. 建立另一个缓冲区用于接收
8. 接受内容并存在缓冲区，并返还一个长度，  
9. 如果长度>0就打印出返还值  
10. #define _CRT_SECURE_NO_WARNINGS  
11. 把服务器与客户端增强一些，加一些_cSock打印，与申请内容打印  


## 6.由最简易的字符串服务器迭代成 -> struct结构体版本  
1. 复习一下结构体struct  

| 名称 | 内容 |  
|---|---  
| 1.struct是数据表 | 也只是个表格  
| 2.struct是类 | 也有类的一些功能，比如继承  
| 3.struct中的数据注意对齐 | 每一个最好都是32bit  
| 3.struct可以直接在打括号后面新建一个对象 | struct A{} duixiang ;  

**a. 定义一个数据结构，包括年龄和姓名**   
**b. 判断recv收到的内容是不是申请得到信息，如果是，直接把这个struct扔回去**   
**c. 把客户端定义同样的数据结构，顺序必须一样，变量名可以不一样**  
**d. 取出recv中的数据，强转成struct类型的指针，然后就可以按照本地stuct数据使用了**  



## 7. 包头\包体---->报文方法,服务器与客户端通信   
**先定义枚举说明状态**  
**再定义结构体，包括报头和包体，说明业务逻辑可以存在表格里**   
**接收包头数据，分析是哪种请求，进入switch**  
**根据包头申请包体空间，存入胞体信息，读取包体信息，检查包体信息**  
**服务器定义返回值，定义包头，定义包体，都发回去**  
**客户端，线连接，然后书写命令，根据命令，申请空间，定义包头，定义包体，都发过去，申请结果空间，等着结果**  
**好处是可以根据包头使用switch分派任务，分派空间**  
**坏处是，客户端发送顺序，必须跟服务端接受顺序一样**    



##8. 服务器改造成合体struct  
**1. 整理**   
**2. 增加两种枚举类型，分别是登陆结果和退出结果**  
**3. 所有的其他结构体都 继承 header，并用其构造函数，初始化header,并初始化结果**  
**4. 然后在main中接收长度为包体和头部总和，指针定在头部以后**  
**5. 直接初始化结果，因为结果都通过无参构造函数赋值了**  
**6. 取出属性打印**  
**7. 回发登陆结果**    

##9. 客户端改造成合体struct   
**1. 拷贝数据结构**   
**2. 输入->判断->设置数据->发包->收包**  

##10. 服务器改造为用缓冲区和指针操作，客户端没变    
**1. 把数据读到缓冲区，可以利用指针只读头部那么多，这些操作全都是因为客户端与服务器数据长度相等**   
**2. 根据头，再往缓冲区里流入本条数据，用指针指着他们的名字做业务**  

****  
#第三章

##跨平台C++   

|平台|特点|
|---|---
|windows|有很多windows宏，是它自己定义的，别的平台没有，需要照着他的宏自己定义    
|linux|标准的C++,只是没有好的IDE   
|macOS|标准的C++,xcode比较熬好用，检查、提醒的比较细，只是没有大括号成对常亮    

mac移植   

1. 头文件   

```c
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
```   

2. windows 模板   
```c
int main() {

#ifdef _WIN32
    WORD ver = MAKEWORD(2, 2);
    WSADATA dat;
    WSAStartup(ver, &dat);
#endif
```   

3. 兼容性绑定平台   

```c
#ifdef _WIN32
    _sin.sin_addr.S_un.S_addr = inet_addr("192.168.79.1");
#else
    _sin.sin_addr.s_addr = inet_addr("192.168.79.1");
#endif
```

4. 关闭  

```c
#ifdef _WIN32
    closesocket(_sock);
    
    WSACleanup();
    
#else
    close(_sock);
    
#endif

```   



