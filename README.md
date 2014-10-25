DIPHomeWork
===========

# 这是什么?

数字图像处理作业程序实现，
包含两个版本，其一是采用OpenCV 2.4.x运算库配合Python编写；
其二是在Visual Studio环境下采用OpenCV 2.4.x配合C++编写，
并采用MFC控件增加了可视化程度．
实现过程尽量避免使用比较高级的库函数, i.e. ,尽量从底层实现算法.

# 如何运行?

## Python版本
流程:1.配置python+opencv  ->  2.运行.
### 开发环境配置
#### Python

首先需要安装python,这在一般的Linux发行版和Mac OS X上都是预装的，

以Ubuntu为例：
`sudo apt-get install python`

在Windows下可以到[Python](https://www.python.org/)网站下载二进制安装包.

#### OpenCV
在Ubuntu环境下，完整的配置可以参考[西郊书院](http://oncemore2020.github.io/blog/opencv2install/)
的这篇文章．

在Windows下，下载的OpenCV压缩包内包含了预编译的运算库，可以直接使用．

### 运行
每个功能装在一个文件内，直接运行即可:

`python *.py`

注意：`DIP.py`封装了所有的算法模块，不需要运行它．

## C++版本
### 环境配置
流程: 1.安装Visual Studio;  ->  2.配置OpenCV和libtiff;  ->  3.编译运行
#### Visual Studio
这个工程最初是在Visual Studio 2010下面创建的，后来迁移到了Visual Studio 2013以方便配合OpenCV针对
Visual Studio开发环境发布的Image Watch插件，这个插件可以在调试的过程中可视化显示cv::Mat类局部变量．
采用Visual Studio 2013打开解决方案是肯定不会出问题的，Visual Stuio 2010应该也不会出问题．

**PostScript:我为什么要用Visual Studio比较新的版本？**

因为我之前没有使用VC++6.0的经历(或者说没有在Windows环境下写过可视化程序),
所以不存在转移VS或VC版本的痛苦，也就果断选择了较新的版本．

#### OpenCV 配置
可以参考[OpenCV在Windows的配置](http://user.qzone.qq.com/626691687/blog/1368530158)这篇文章,
需要注意的是需要针对解压OpenCV的路径和特定的OpenCV版本号修改**头文件路径**，**库路径**，**链接器输入附加依赖项列表**
这三个地方(文章中使用2.4.5版本，这个项目文件使用2.4.10版本).

Note: 对环境变量配置不清楚的可以参考[Opencv 完美配置攻略](http://my.phirobot.com/blog/2014-02-opencv_configuration_in_vs.html)
这篇文章，注意操作系统并不需要是Windows 8.1．另外一点非常欣赏这篇文章的一个方法是采用文本方式编辑和配置工程属性表,
使上面提到的三个配置变得一目了然．

#### libtiff 配置
首先下载[libtiff](ftp://ftp.remotesensing.org/pub/libtiff),我使用的是最新版本，配置思路和OpenCV的配置一样，
需要完成**设置头文件路径**,**设置库文件路径**,**设置链接器输入附加依赖项**以及**环境变量**这４个步骤．

### 运行
打开工程后点`F5`开始调试，或者使用无调试运行`Ctrl+F5`．

![界面](https://github.com/OnceMore2020/DIPHomeWork/blob/master/CPP_MFC/mainwindow.PNG)
