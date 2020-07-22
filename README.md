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
|项目->属性->常规->目录|```$(SolutionDir)/bin/$(Plantform)/$(Configuration)/```  ```$(SolutionDir)/temp/$(Plantform)/$(Configuration)/$(ProjectName)```
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
网络游戏开发

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
| 2.建立socket | 查看Lesson_2
| 3.绑定端口 | 查看Lesson_2
| 4.监听端口 | 查看Lesson_2
| 5.接收数据 | 查看Lesson_2
| 6.回发数据 | 查看Lesson_2
| 7.关闭socket | 查看Lesson_2



