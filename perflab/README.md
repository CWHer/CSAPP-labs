## Performance Lab

不知道接下来优化的方向了...

~~没找到什么参考资料~~



#### 环境

CPU: i7-10710U 

OS: VMware Ubuntu 2010 



- [x] rotate

baseline: ~17

1. 尝试调换循环顺序

   发现出奇的快...

   加速比: ~28

2. 分块 (block size=8)

   仅分块和两者结合差不多，加速比: ~31



- [x] smooth

baseline: ~23

1. 减少3x3重叠部分的计算

   加速比: ~50

2. 尝试调换循环顺序，效果变差

3. 二维前缀和

   加速比: ~70

