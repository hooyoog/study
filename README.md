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
## 工具的调试
|标题|内容|
|---|---
|项目->属性->常规->目录|```$(SolutionDir)/bin/$(Plantform)/$(Configuration)/```  ```$(SolutionDir)/temp/$(Plantform)/$(Configuration)/$(ProjectName)```
|连接器->输入->增加库|```ws2_32.lib;```
|避免vsStudio编译报错|```#define W32_LEAN_AND_MEAN    #define _WINSOCK_DEPRECATED_NO_WARNINGS```

## github使用方法
1. 在github官网，创建新项目。在本地某个文件夹里右键打开github工具
2. git config --global user.email "XXXXXXXX@qq.com" //输入一次就成
3. git config --global user.name "honeypet"//输入一次就成
4. git init
5. 设置并提交到官网上
```git add .  
git commit -m "first commit"  
git remote add origin https://github.com/hooyoog/study.git  
git push -u origin master```  
















