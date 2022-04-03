# 智能车视觉组仓库

第17界智能车竞赛-AHSTU-视觉小白队

## 任务列表:cactus:

- [x] `VOFA+`上位机-PID波形
- [x] PID调试
- [ ] 学习C语言指针
- [ ] 编码器滤波
- [ ] 编码器积分算出位移
- [ ] 姿态传感器闭环
- [ ] `OpenArt`和`RT1064`之间的通讯
- [ ] `OpenArt `坐标识别优化（透视变换）
- [ ] `OpenArt`坐标识别和图片识别整合
- [ ] 路径规划

## 更新日志:rabbit:

2022-4-2

> 1. 硬件万事俱备，开始专注写BUG :-)，今天第一次尝试用回流焊，焊接了两块电机驱动板，虽然一开始并没有成功，经过调试之后，效果还是不错的，板子焊完比较干净，全程都很优雅。
> 2. 加入了PID控制，也学会了`RT1064`的中断操作，还没有调参，打算明天搞定VOFA+上位机！
> 3. PID调试中，应该先调整`I`的值，这个值和时间积分有关（个人理解）越大变化越快，然后再调`P`，这个值和能否快速回到目标速度有关。

2022-4-3

> 1. 搞定了VOFA+上位机，显示出来了波形
> 1. 增加按键，目前按键的功能是调目标速度
> 2. 调了PID的参数，可能还不太准确，但是比之前盲调要好多了
> 2. 明天打算搞定滤波和位置环

## 备忘录:notebook:

1. 先用杰哥的车验证方案（3-12-直接放弃了）
2. 5月前要完成小车麦克纳木轮的闭环驱动，IMU驱动整合，apriltag定位
3. 项目总体计划：先搞定A4纸识别部分，然后搞定定位部分，最后想好要不要搞定搬运部分
3. 非常感谢王乐老师愿意给我们买车模和元件
3. 目前想了两种运动方式：一种是先转向再使用前进冲过去；另一种是车头永远朝前，利用麦克纳木轮的运动学逆解“螃蟹走步过去”

### 1、OpenArt透视变换（未解决）

1. [find_rects 识别矩形 · OpenMV中文入门教程](https://book.openmv.cc/example/09-Feature-Detection/find-rects.html)、透视变换[教程](https://book.openmv.cc/example/04-Image-Filters/perspective-correction.html)
2. 4-2 已经提交了issu并[得到回复](https://github.com/NXPmicro/OpenART/tree/dev)，有希望能解决openart透视变换函数报错问题，但是我不会编译OpenArt的固件:cry:

### 2、麦轮转向

![max](images/max.png)

> ### 参考链接🔗
>
> 1. .[恩智浦AI视觉组入门教程发布--逐飞科技](https://mp.weixin.qq.com/s/y90pT2_g0IPRuaNQPzZUqg)
> 2. [智能车竞赛AI组OpenART mini视觉传感器图像识别模块Open ART逐飞-淘宝网](https://item.taobao.com/item.htm?spm=a1z10.5-c.w4002-22508770847.38.3f9d5f26PVLIVv&id=637029649233&mt=)
> 3. [恩智浦AI视觉组浅析--逐飞科技 ](https://mp.weixin.qq.com/s/y2IzQTzd_mr4BtPH-oOKcQ)
> 4. [智能视觉组比赛细则](https://bj.bcebos.com/cdstm-hyetecforthesmartcar-bucket/source/doc-2kd6k14jliw0.pdf)
> 5. [智能视觉组补充说明](https://bj.bcebos.com/cdstm-hyetecforthesmartcar-bucket/source/doc-888jo99kh9g0.pdf)
> 6. [17界比赛总规则](https://bj.bcebos.com/cdstm-hyetecforthesmartcar-bucket/source/doc-7f76k5yp26g0.pdf)
> 8. [NXP_OpenART](https://github.com/NXPmicro/OpenART/blob/master/README_zh.md)
>

