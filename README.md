DIPHomeWork
===========

# 这是什么?

数字图像处理作业程序实现，
包含两个版本，其一时采用OpenCV 2.4.x运算库配合Python编写；
其二是在Visual Studio环境下采用OpenCV 2.4.x配合C++编写，
并采用MFC控件增加了可视化程度．
实现过程尽量避免使用比较高级的库函数, i.e. ,尽量从底层实现算法.

# 如何运行?

## Python版本
流程:配置python+opencv->运行
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

###　运行
每个功能装在一个文件内，直接运行即可:

`python *.py`

注意：`DIP.py`封装了所有的算法模块，不需要运行它．


