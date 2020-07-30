游戏开发大师课程——小志学习笔记
=============================
*主要工具： VS Studio；*    
*C++ 内容： C++服务器与客户端开发、linux游戏服务器开发，android\mac\ios\windows客户端开发；*      
*引擎内容： UE4、Unity、Cocos与服务器通讯*  

****
|作者|CG欧吉桑|
|---|---
|知乎|欧吉桑
|公众号|微信hooyoog5
****
# 目录
* [第一章](#第一章)
* [第二章](#第二章)
* [向下跳转](#文本)
    * 普通文本
****

# 第一章
## WindowsXP！WHAT？欧吉桑！我们肆00后耶！哪懂得什么是WindowsXP！

*第一步  请安装虚拟机软件VmWare并安装windowsXP！ *

```diff   
+ 有没有搞错？   
- 不是直接买 I9+泰坦 后，安装UE5和Unity3d下载模块点击播放就OK了吗？   
! 是不是搞昨年代了？现在是2021年！   
# 这难道是很老的教程？   
```   

  
*请小朋友们稍安勿躁！听欧吉桑解释！ *   

## 答案：
1 因为我们要学习的是大师的游戏开发算法技巧、服务器百万并发和3D优化技巧；  
2 国外的大师以前已经把课程都讲过了；  
3 大师们懒得再讲一遍，他们都已经70岁了，40-50岁的大师没空理咱们；  
4 他们讲的技巧案例在win10里已经跑不起来了，我们不是高手，我们需要翻译一遍；  
5 你不跟着以前教程的学，你做的UE5的画面只不过是一个“建筑游离”，不是游戏；  
6 腾讯之所以用UE和Unity是因为即使他出了80个G的手机游戏，大家也会下载的，普及后他再花1亿请大师优化成脱离引擎的版本，你出的游戏如果100-500G没人愿意下载，必须控制在40个G以内，小厂商和个人的游戏内容必须丰富，没人玩小厂商的一张地图的撸啊撸。
7  避免新手由于安装老的OpenGL和direct类库，把自己的win10开发环境搞坏了  
8 笔记本通常跑不动UE4  
9 感受一下什么摩尔定律背后的操控者   


*所以让我们开始吧，每节课的目标都是把游戏大师的教程案例运行在 Win10、android、ios、mac上！*   



|标题|内容|
|---|---
|安装虚拟机 | vmware workstation
|安装windows| iso镜像
|安装vc6| 《魔兽》与《侠盗猎车》的编译环境



****
# 第二章  
*** 案例1 打飞机 不通过引擎，做一个打飞机游戏，移植到全平台***  

*日本世嘉虽然出了本教程，但是案例用棋牌逻辑开始，棋牌逻辑很难，一上来就干蒙了所有0基础的，再讲图形化时大家就跟不上了，将图形化应该用RPG和射击类游戏讲*   

|标题|工具|  
|---|---   
|语言C++ | vs6  
|directDraw | direct8SDK    

windows VC中包含的头文件名，不区分大小写如 #include "head.h" = #include "HEAD.H"。  

*如果使用的是vs2008:  
1.安装directx8 sdk。

2.在工具/选项/项目及解决方案/vc++目录/包含文件中，加入sdk安装目录下的include，在工具/选项/项目及解决方案/vc++目录/库文件中，加入sdk安装目录下的lib。

3.在使用时，在cpp中加入：   

#include<d3d8.h>   
#include<d3dx8.h>  
#include<ddraw.h>   
#pragma comment(lib,"d3d8.lib")     
#pragma comment(lib,"d3dx8.lib")    
#pragma comment(lib,"ddraw.lib")    
#pragma comment(lib,"dxguid.lib")  






4.如果编译时报：

duringImage错误，那么在项目/项目属性/配置属性/链接器/常规/启用增量链接,将"是"改为"否"。


5.另外：c:\program files\microsoft sdks\windows\v6.0a\include\winnt.h
编译器通知我们POINTER_64没有定义。   
#define POINTER_64 __ptr64
typedef void *PVOID;
typedef void * POINTER_64 PVOID64;

6.语法错误 : 标识符“SHANDLE_PTR”    
c:\program files\microsoft sdks\windows\v6.0a\include\exdisp.h   
include path.即改变包含路径的顺序，保证DirectX包含路径在PlatformSDK包含路径之后   


* 

## 1.  Visual studio使用
*Visoul C++基础*   

1. 安装，最好用ISO光盘镜像完全安装,包括重要工具，MSDN（Micrsoft Developer Nwtwork）帮助文件  
2. 目标：学会看帮助文档，由被动学习转为主动学习   
3. 包括好工具：Psy++ 、ActiveX Test Container 、Install Shiels安装界面生成器、
如果开发时出现（Linking）卡死，安装MSDN补丁   
4. 左侧分页栏，前三个vc自带，视图、资源、源文件；后面的是VC助手添加的，方便查看文件和符号
5. AppWizard应用程序向导,用于生成各种应用程序的骨干框架。   
6. ClassWizard（类向导）   
7. Resource Editor 编辑资源、如菜单工具栏、位图等   

8. 平缓的学习曲线,对抗无厘头的WIDOWS    

|标题|内容|   
|---|---    
|基础|基本的C语言编程（过程式模式）   
|WinAPI|WinAPI编程模式(事件驱动)，掌握一些API   
|MFC|MFC运行机制，理解对应API是如何封装的    
|MFC类库|尽可能多的掌握MFC类库     
|高手阶段|组件编程   

  
## 2.Windows事件驱动编程模式       
1.  软件不按照变成顺序执行，而是等待监听用户的输入激励程序的执行，这种不按顺序发生的激励叫做“消息”
2.   “消息”是API和MFC中非常重要的概念。 类似于CPU的中断，中断后“轮询”。
3.  “消息”是c结构体，包含1名称、2一些相关参数、3处理这个消息的指针；  
 
消息分类    

|名称|内容|   
|---|---   
|输入消息|鼠标键盘等   
|控件消息|按钮、文本框等通信，此类消息一般不经过消息队列，直接发到控件对象上。   
|系统消息|如何创建窗体等   
|用户自定义消息|重要、比如qq,规划自定义消息，登录，好友在线等。通讯程序中最重要的消息。      
 

## 3.Windows的API编程入门   
新建一个空程序，输入   
```c
#include<windows.h>
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int NShowCmd)
{
	MessageBox(NULL,TEXT("Hello , World"),TEXT("hello"),0);
	return 0;
}

```   
 
消息分类    

|名称|内容|   
|---|---   
|#include<windows.h>|相当于<stdio.h>   
|WinMain|相当于main()。   
|WINAPI 提示编译识别子|规定在编译时，如何生成二进制代码、函数参数的入栈顺序、参数放置位置,是这样定义的  ```#define WINAPI _stdcall``` 
|_stdcall|Windows程序通用函数调用方式。 
|WinMain的前两个参数HINSTANCE|句柄类型，和指针类似，win程序或资源的一个编号，以便查找，第一个是当前程序实例的编号，第二个没用，以前的遗留    
|LPSTR|字符串指针，指向启动时一些命令的参数   
|NShowCmd|程序最初的显示方式，例如最大化   
|MessageBox|显示短信息   
|第一个参数NULL|母体窗体代号，没有写NULL   
|第二个参数TEXT("Hello , World")|窗体显示内容   
|第三个参数TEXT("hello")|窗口标题   
|第四个参数0|窗口风格，例如只有MB_OK确认或者有确认和取消MB_OKCANCEL    



## 4.Windows的API编程提高   
vs新建一个helloworld app


**原理**  
* *  

|网络通讯|本地存储|
|---|---
|建立|相当于打开
|输入|相当于本地写写字板
|发送|相当于本地存储写字板内容
|关闭|关闭写字板 



**实践：搭建服务器**
| 名称 | 内容 |
|---|---
| 1.  | ```  ;```  
| 2.  |  
| 3.  | 查看 
| 4.  | 查看 
| 5.  | 查看 
| 6.  | 查看 
| 7.  | 查看 


## 3.简单 

1. 创建工程 

2. 理解他

| 名称 | 内容 | 相当于 |
|---|---|---
| 1.  | 查看  | 打开写字板
| 2.  | 查看  | 打开写字板
| 3. | 查看  | 解析写字板内容 
| 4.  | 查看  | 关闭写字板


3. 写代码  
* *   

4. 复习  
** **  
** **  

| 名称 | 内容 |
|---|---
| 1.  | point
| 2.  | &a
| 3.  | &q
| 4.  | ``` ```
| 5.  |  ``` ```
| 6.  |     

* *  
* *  

## 4. 
  
  **  **   
  
```c

```  
  





