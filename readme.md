# urqmd_vishnew

urqmd_vishnew主要实现这样的功能: 对urqmd进行Gaussian Smearing,然后使用这个初态进行vishnew 2+1流体演化,利用iSS进行sample,最后通过urqmd进行freestreaming得到输出.其中本程序主要创新再与其中的Gaussian Smearing初态,参考文献0712.3715 1205.5019

## 安装

本程序使用cmake进行安装,在程序根目录执行如下指令

- `mkdir build`
- `cd build`
- `cmake ..`
- `make install`

从而可以发现根目录下出现`PlayGround`目录,内部各个目录里面有对应的可执行文件以及参数.同时还有python脚本文件`run.py`提供一个参考的运行流程,注意这一流程类不包含进行QGP判断的部分

## transform

这里对于transform本身使用的物理和参数等进行一个简单的介绍

### 代码格式

- transform用c++编写,主要使用doxygen语法格式进行注释,所以可以使用`doxygen`相关命令进行产生程序文档方便阅读
- transform的代码中,遵循Google开源命名原则,并附加一条规则:一切全局变量都会以`Ex_`开头命名,这类变量基本就是参数文件中对应的变量
- 参数卡为`Transform_para.txt`,内部包含对应参数的解释,同时包含DEBUG选项,可以选择是否输出各种的初态信息以及潜在问题记录

### 基本流程

transform内部运行大致进行如下流程

1. 从urqmd输出的ftn14格式文件中读入Minkow坐标(t,x,y,z)的粒子数据,然后输出Miline($\tau$,x,y,$\eta$)坐标上的$\tau=\tau0$面上的粒子.具体转化方法是扫描每时刻的所有粒子,如果这个粒子的$\tau<\tau_0$则判断如果粒子进行匀速直线运动能否在下一个时间格点前到达$\tau_0$面,如果可以,记录,反之忽略.如果已经扫描到了最后一个时间格点,那么直接记录粒子进行无限长时间匀速直线运动后到达$\tau_0$面上的数据.但是对于每一时刻的粒子,如果粒子的$\tau\geq\tau_0$,那么忽略.同时,如果这个粒子是urqmd的spectator,那么同样忽略
2. 对于使用上述方法得到的粒子,进行Gaussian Smearing,可以得到一个三维空间的能动量张量矩阵,然后可以对这个矩阵进行一次QGP判断,从原先记录的$\tau_0$面上的粒子剔除不会在QGP内部的粒子,然后重新生成能动量张量矩阵,输出.

### QGP判据

目前的QGP判据并不完善,主要使用一下3种判据

- QGP_volume: 计算能动量张量上面所有$e>Edec$并且连通的格点的总体积(连通是指某一格点的x,y,$\eta$距离其最近的6个格点是否有满足条件的格点),但总体积大于某一临界值的时候,认为产生QGP,输出的时候去除所有不在volume内部的粒子
- calculate eta_cut: 计算$\tau_0$面上的两个$\eta$边界,使得这个边界内的每一个xy平面上都有$e>Edec$的格点,具体是否接受可以在程序外的接口上判断
- input eta_cut: 判断同上,但是这一cut是自主输入,然后可以判断这一cut内部的能量信息
- spectator: 同样使用volume判据,但是只去除spectator

以上3种判断方式都未经实验数据验证,具体判据参数还需要标定
