## Data Lab

仅仅是可行解

- [x] `bitXor(x,y)`

  ```c++
  ^: (~x&y)|(~y&x)
  |: ~(~x&~y)
  ```

- [x] `tmin()`

- [x] `Tmax(x)`

  判断`~x`与`x+1`是否相等，并排除-1

- [x] `allOddBits(x)`

- [x] `negate(x)`

- [ ] `isAsciDigit(x)`

  生成上下界之后类似`isLessOrEqual(x, y)`

- [x] `isLessOrEqual(x, y)`

  减完判断符号位，注意溢出

- [x] `logicalNeg(x)`

  x不为0时，`x`和`-x`的符号位至少有一个为1

- [x] `howManyBits(x)`

  对于正数，找最高位1的位置，且需要加上一位符号位，否则最高位权值不为正

  对于负数，取反后找最高位1的位置再加上符号位

  找最高位1的位置时使用倍增

- [x] `floatScale2(uf)`

  操作限制很少，分类讨论即可

- [x] `floatFloat2Int(uf)`

- [x] `floatPower2(x)`



#### 参考资料

1.[_CSAPP 之 DataLab详解，没有比这更详细的了_](https://zhuanlan.zhihu.com/p/59534845)

​	部分有误