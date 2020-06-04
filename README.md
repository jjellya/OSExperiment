<p align="center">
<h1 align="center">OSExperiment </h1>
<p align="center">2020春大二下操作系统课程实验——单处理器系统的进程调度</p>
<p align="center">
    <a href="https://github.com/CoderGay/">
        <img src="https://img.shields.io/badge/license-MIT-green" alt="MIT License" />
    </a>
    <a href="https://www.qt.io/">
        <img src="https://img.shields.io/badge/GUI- Qt 5.13.2-success/" alt="Qt5.0">
    </a>
    <a href="https://github.com/CoderGay">
        <img src="https://img.shields.io/badge/author-CoderGay-blueviolet" alt="Author">
    </a>
</p>
 

## 单处理器系统的进程调度模拟实验
[程序下载网盘地址](https://pan.baidu.com/s/18BUbMNT6QtY9M95VbEWiXw)

提取码：t3ir

本程序使用C++和 Qt5 编写.
### 使用说明
1.打开程序后，四台单处理器系统处于初始状态，用户需要首先创建进程，才可以调度进程；

2.`创建进程`点击后创建一个进程，`创建进程x10`点击后连续创建10个进程；

3.若只在`调度进程`前`创建进程`，SPN调度算法(非抢占)和SRT调度算法(抢占)呈现的队列看不出区别，
需在SPN和SRT在`调度进程`的过程中点击`创建进程`按钮，才有可能致使SRT调度算法出现抢占的局面
(比如：创建的进程刚好所需时间少于当前所有进程)；

4.根据[《操作系统分析与设计实习 指导书》](null)的题目要求，本实验只提供N=10个用于存储PCB的内存单元，
故最多只可创建10个进程，超过则本实验系统不予响应；

5.根据[《操作系统分析与设计实习 指导书》](null)的题目要求，进程ID(PCB唯一标识符)、运行所需时间、优先级是系统自动分配给PCB的;

### 程序截图

[![ProgramPicture.png](https://wx1.sbimg.cn/2020/06/04/ProgramPicture.png)](https://sbimg.cn/image/kzRVj)
