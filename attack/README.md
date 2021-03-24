## Attack Lab

- [ ] problem1

  代码注入



#### 汇编代码

- ctarget

```assembly
Disassembly of section .text:

000000000040102a <initialize_target>:
  40102a:       55                      push   %rbp
  40102b:       53                      push   %rbx
  40102c:       48 81 ec 18 21 00 00    sub    $0x2118,%rsp
  401033:       89 f5                   mov    %esi,%ebp
  401035:       64 48 8b 04 25 28 00    mov    %fs:0x28,%rax
  40103c:       00 00
  40103e:       48 89 84 24 08 21 00    mov    %rax,0x2108(%rsp)
  401045:       00
  401046:       31 c0                   xor    %eax,%eax
  401048:       89 3d 8a 34 20 00       mov    %edi,0x20348a(%rip)        # 6044d8 <check_level>
  40104e:       8b 3d f4 30 20 00       mov    0x2030f4(%rip),%edi        # 604148 <target_id>
  401054:       e8 65 1c 00 00          callq  402cbe <gencookie>
  401059:       89 05 85 34 20 00       mov    %eax,0x203485(%rip)        # 6044e4 <cookie>
  40105f:       89 c7                   mov    %eax,%edi
  401061:       e8 58 1c 00 00          callq  402cbe <gencookie>
  401066:       89 05 74 34 20 00       mov    %eax,0x203474(%rip)        # 6044e0 <authkey>
  40106c:       8b 05 d6 30 20 00       mov    0x2030d6(%rip),%eax        # 604148 <target_id>
  401072:       8d 78 01                lea    0x1(%rax),%edi
  401075:       e8 16 fc ff ff          callq  400c90 <srandom@plt>
  40107a:       e8 31 fd ff ff          callq  400db0 <random@plt>
  40107f:       89 c7                   mov    %eax,%edi
  401081:       e8 02 03 00 00          callq  401388 <scramble>
  401086:       89 c3                   mov    %eax,%ebx
  401088:       ba 00 00 00 00          mov    $0x0,%edx
  40108d:       85 ed                   test   %ebp,%ebp
  40108f:       74 18                   je     4010a9 <initialize_target+0x7f>
  401091:       bf 00 00 00 00          mov    $0x0,%edi
  401096:       e8 05 fd ff ff          callq  400da0 <time@plt>
  40109b:       89 c7                   mov    %eax,%edi
  40109d:       e8 ee fb ff ff          callq  400c90 <srandom@plt>
  4010a2:       e8 09 fd ff ff          callq  400db0 <random@plt>
  4010a7:       89 c2                   mov    %eax,%edx
  4010a9:       01 da                   add    %ebx,%edx
  4010ab:       0f b7 d2                movzwl %dx,%edx
  4010ae:       8d 04 d5 00 01 00 00    lea    0x100(,%rdx,8),%eax
  4010b5:       89 c0                   mov    %eax,%eax
  4010b7:       48 89 05 c2 33 20 00    mov    %rax,0x2033c2(%rip)        # 604480 <buf_offset>
  4010be:       c6 05 43 40 20 00 63    movb   $0x63,0x204043(%rip)        # 605108 <target_prefix>
  4010c5:       83 3d bc 33 20 00 00    cmpl   $0x0,0x2033bc(%rip)        # 604488 <notify>
  4010cc:       0f 84 b9 00 00 00       je     40118b <initialize_target+0x161>
  4010d2:       83 3d 0f 34 20 00 00    cmpl   $0x0,0x20340f(%rip)        # 6044e8 <is_checker>
  4010d9:       0f 85 ac 00 00 00       jne    40118b <initialize_target+0x161>
  4010df:       be 00 01 00 00          mov    $0x100,%esi
  4010e4:       48 89 e7                mov    %rsp,%rdi
  4010e7:       e8 44 fd ff ff          callq  400e30 <gethostname@plt>
  4010ec:       bb 00 00 00 00          mov    $0x0,%ebx
  4010f1:       85 c0                   test   %eax,%eax
  4010f3:       74 23                   je     401118 <initialize_target+0xee>
  4010f5:       bf 68 2e 40 00          mov    $0x402e68,%edi
  4010fa:       e8 c1 fb ff ff          callq  400cc0 <puts@plt>
  4010ff:       bf 08 00 00 00          mov    $0x8,%edi
  401104:       e8 37 fd ff ff          callq  400e40 <exit@plt>
  401109:       48 89 e6                mov    %rsp,%rsi
  40110c:       e8 5f fb ff ff          callq  400c70 <strcasecmp@plt>
  401111:       85 c0                   test   %eax,%eax
  401113:       74 1a                   je     40112f <initialize_target+0x105>
  401115:       83 c3 01                add    $0x1,%ebx
  401118:       48 63 c3                movslq %ebx,%rax
  40111b:       48 8b 3c c5 60 41 60    mov    0x604160(,%rax,8),%rdi
  401122:       00
  401123:       48 85 ff                test   %rdi,%rdi
  401126:       75 e1                   jne    401109 <initialize_target+0xdf>
  401128:       b8 00 00 00 00          mov    $0x0,%eax
  40112d:       eb 05                   jmp    401134 <initialize_target+0x10a>
  40112f:       b8 01 00 00 00          mov    $0x1,%eax
  401134:       85 c0                   test   %eax,%eax
  401136:       75 1c                   jne    401154 <initialize_target+0x12a>
  401138:       48 89 e2                mov    %rsp,%rdx
  40113b:       be a0 2e 40 00          mov    $0x402ea0,%esi
  401140:       bf 01 00 00 00          mov    $0x1,%edi
  401145:       e8 a6 fc ff ff          callq  400df0 <__printf_chk@plt>
  40114a:       bf 08 00 00 00          mov    $0x8,%edi
  40114f:       e8 ec fc ff ff          callq  400e40 <exit@plt>
  401154:       48 8d bc 24 00 01 00    lea    0x100(%rsp),%rdi
  40115b:       00
  40115c:       e8 c3 18 00 00          callq  402a24 <init_driver>
  401161:       85 c0                   test   %eax,%eax
  401163:       79 26                   jns    40118b <initialize_target+0x161>
  401165:       48 8d 94 24 00 01 00    lea    0x100(%rsp),%rdx
  40116c:       00
  40116d:       be e0 2e 40 00          mov    $0x402ee0,%esi
  401172:       bf 01 00 00 00          mov    $0x1,%edi
  401177:       b8 00 00 00 00          mov    $0x0,%eax
  40117c:       e8 6f fc ff ff          callq  400df0 <__printf_chk@plt>
  401181:       bf 08 00 00 00          mov    $0x8,%edi
  401186:       e8 b5 fc ff ff          callq  400e40 <exit@plt>
  40118b:       48 8b 84 24 08 21 00    mov    0x2108(%rsp),%rax
  401192:       00
  401193:       64 48 33 04 25 28 00    xor    %fs:0x28,%rax
  40119a:       00 00
  40119c:       74 05                   je     4011a3 <initialize_target+0x179>
  40119e:       e8 3d fb ff ff          callq  400ce0 <__stack_chk_fail@plt>
  4011a3:       48 81 c4 18 21 00 00    add    $0x2118,%rsp
  4011aa:       5b                      pop    %rbx
  4011ab:       5d                      pop    %rbp
  4011ac:       c3                      retq

00000000004011ad <main>:
  4011ad:       41 56                   push   %r14
  4011af:       41 55                   push   %r13
  4011b1:       41 54                   push   %r12
  4011b3:       55                      push   %rbp
  4011b4:       53                      push   %rbx
  4011b5:       41 89 fc                mov    %edi,%r12d
  4011b8:       48 89 f3                mov    %rsi,%rbx
  4011bb:       be c5 1d 40 00          mov    $0x401dc5,%esi
  4011c0:       bf 0b 00 00 00          mov    $0xb,%edi
  4011c5:       e8 86 fb ff ff          callq  400d50 <signal@plt>
  4011ca:       be 77 1d 40 00          mov    $0x401d77,%esi
  4011cf:       bf 07 00 00 00          mov    $0x7,%edi
  4011d4:       e8 77 fb ff ff          callq  400d50 <signal@plt>
  4011d9:       be 13 1e 40 00          mov    $0x401e13,%esi
  4011de:       bf 04 00 00 00          mov    $0x4,%edi
  4011e3:       e8 68 fb ff ff          callq  400d50 <signal@plt>
  4011e8:       bd a5 2f 40 00          mov    $0x402fa5,%ebp
  4011ed:       83 3d f4 32 20 00 00    cmpl   $0x0,0x2032f4(%rip)        # 6044e8 <is_checker>
  4011f4:       74 1e                   je     401214 <main+0x67>
  4011f6:       be 61 1e 40 00          mov    $0x401e61,%esi
  4011fb:       bf 0e 00 00 00          mov    $0xe,%edi
  401200:       e8 4b fb ff ff          callq  400d50 <signal@plt>
  401205:       bf 05 00 00 00          mov    $0x5,%edi
  40120a:       e8 01 fb ff ff          callq  400d10 <alarm@plt>
  40120f:       bd aa 2f 40 00          mov    $0x402faa,%ebp
  401214:       48 8b 05 85 32 20 00    mov    0x203285(%rip),%rax        # 6044a0 <stdin@@GLIBC_2.2.5>
  40121b:       48 89 05 ae 32 20 00    mov    %rax,0x2032ae(%rip)        # 6044d0 <infile>
  401222:       41 bd 00 00 00 00       mov    $0x0,%r13d
  401228:       41 be 00 00 00 00       mov    $0x0,%r14d
  40122e:       e9 c6 00 00 00          jmpq   4012f9 <main+0x14c>
  401233:       83 e8 61                sub    $0x61,%eax
  401236:       3c 10                   cmp    $0x10,%al
  401238:       0f 87 9c 00 00 00       ja     4012da <main+0x12d>
  40123e:       0f b6 c0                movzbl %al,%eax
  401241:       ff 24 c5 f0 2f 40 00    jmpq   *0x402ff0(,%rax,8)
  401248:       48 8b 3b                mov    (%rbx),%rdi
  40124b:       e8 50 fd ff ff          callq  400fa0 <usage>
  401250:       be 6d 32 40 00          mov    $0x40326d,%esi
  401255:       48 8b 3d 4c 32 20 00    mov    0x20324c(%rip),%rdi        # 6044a8 <optarg@@GLIBC_2.2.5>
  40125c:       e8 9f fb ff ff          callq  400e00 <fopen@plt>
  401261:       48 89 05 68 32 20 00    mov    %rax,0x203268(%rip)        # 6044d0 <infile>
  401268:       48 85 c0                test   %rax,%rax
  40126b:       0f 85 88 00 00 00       jne    4012f9 <main+0x14c>
  401271:       48 8b 0d 30 32 20 00    mov    0x203230(%rip),%rcx        # 6044a8 <optarg@@GLIBC_2.2.5>
  401278:       ba b2 2f 40 00          mov    $0x402fb2,%edx
  40127d:       be 01 00 00 00          mov    $0x1,%esi
  401282:       48 8b 3d 27 32 20 00    mov    0x203227(%rip),%rdi        # 6044b0 <stderr@@GLIBC_2.2.5>
  401289:       e8 d2 fb ff ff          callq  400e60 <__fprintf_chk@plt>
  40128e:       b8 01 00 00 00          mov    $0x1,%eax
  401293:       e9 e4 00 00 00          jmpq   40137c <main+0x1cf>
  401298:       ba 10 00 00 00          mov    $0x10,%edx
  40129d:       be 00 00 00 00          mov    $0x0,%esi
  4012a2:       48 8b 3d ff 31 20 00    mov    0x2031ff(%rip),%rdi        # 6044a8 <optarg@@GLIBC_2.2.5>
  4012a9:       e8 72 fb ff ff          callq  400e20 <strtoul@plt>
  4012ae:       41 89 c6                mov    %eax,%r14d
  4012b1:       eb 46                   jmp    4012f9 <main+0x14c>
  4012b3:       ba 0a 00 00 00          mov    $0xa,%edx
  4012b8:       be 00 00 00 00          mov    $0x0,%esi
  4012bd:       48 8b 3d e4 31 20 00    mov    0x2031e4(%rip),%rdi        # 6044a8 <optarg@@GLIBC_2.2.5>
  4012c4:       e8 b7 fa ff ff          callq  400d80 <strtol@plt>
  4012c9:       41 89 c5                mov    %eax,%r13d
  4012cc:       eb 2b                   jmp    4012f9 <main+0x14c>
  4012ce:       c7 05 b0 31 20 00 00    movl   $0x0,0x2031b0(%rip)        # 604488 <notify>
  4012d5:       00 00 00
  4012d8:       eb 1f                   jmp    4012f9 <main+0x14c>
  4012da:       0f be d2                movsbl %dl,%edx
  4012dd:       be cf 2f 40 00          mov    $0x402fcf,%esi
  4012e2:       bf 01 00 00 00          mov    $0x1,%edi
  4012e7:       b8 00 00 00 00          mov    $0x0,%eax
  4012ec:       e8 ff fa ff ff          callq  400df0 <__printf_chk@plt>
  4012f1:       48 8b 3b                mov    (%rbx),%rdi
  4012f4:       e8 a7 fc ff ff          callq  400fa0 <usage>
  4012f9:       48 89 ea                mov    %rbp,%rdx
  4012fc:       48 89 de                mov    %rbx,%rsi
  4012ff:       44 89 e7                mov    %r12d,%edi
  401302:       e8 09 fb ff ff          callq  400e10 <getopt@plt>
  401307:       89 c2                   mov    %eax,%edx
  401309:       3c ff                   cmp    $0xff,%al
  40130b:       0f 85 22 ff ff ff       jne    401233 <main+0x86>
  401311:       be 00 00 00 00          mov    $0x0,%esi
  401316:       44 89 ef                mov    %r13d,%edi
  401319:       e8 0c fd ff ff          callq  40102a <initialize_target>
  40131e:       83 3d c3 31 20 00 00    cmpl   $0x0,0x2031c3(%rip)        # 6044e8 <is_checker>
  401325:       74 2a                   je     401351 <main+0x1a4>
  401327:       44 3b 35 b2 31 20 00    cmp    0x2031b2(%rip),%r14d        # 6044e0 <authkey>
  40132e:       74 21                   je     401351 <main+0x1a4>
  401330:       44 89 f2                mov    %r14d,%edx
  401333:       be 08 2f 40 00          mov    $0x402f08,%esi
  401338:       bf 01 00 00 00          mov    $0x1,%edi
  40133d:       b8 00 00 00 00          mov    $0x0,%eax
  401342:       e8 a9 fa ff ff          callq  400df0 <__printf_chk@plt>
  401347:       b8 00 00 00 00          mov    $0x0,%eax
  40134c:       e8 ba 06 00 00          callq  401a0b <check_fail>
  401351:       8b 15 8d 31 20 00       mov    0x20318d(%rip),%edx        # 6044e4 <cookie>
  401357:       be e2 2f 40 00          mov    $0x402fe2,%esi
  40135c:       bf 01 00 00 00          mov    $0x1,%edi
  401361:       b8 00 00 00 00          mov    $0x0,%eax
  401366:       e8 85 fa ff ff          callq  400df0 <__printf_chk@plt>
  40136b:       48 8b 3d 0e 31 20 00    mov    0x20310e(%rip),%rdi        # 604480 <buf_offset>
  401372:       e8 ea 0b 00 00          callq  401f61 <stable_launch>
  401377:       b8 00 00 00 00          mov    $0x0,%eax
  40137c:       5b                      pop    %rbx
  40137d:       5d                      pop    %rbp
  40137e:       41 5c                   pop    %r12
  401380:       41 5d                   pop    %r13
  401382:       41 5e                   pop    %r14
  401384:       c3                      retq
  401385:       90                      nop
  401386:       90                      nop
  401387:       90                      nop

0000000000401388 <scramble>:
  401388:       b8 00 00 00 00          mov    $0x0,%eax
  40138d:       eb 11                   jmp    4013a0 <scramble+0x18>
  40138f:       69 c8 7f 79 00 00       imul   $0x797f,%eax,%ecx
  401395:       01 f9                   add    %edi,%ecx
  401397:       89 c2                   mov    %eax,%edx
  401399:       89 4c 94 c8             mov    %ecx,-0x38(%rsp,%rdx,4)
  40139d:       83 c0 01                add    $0x1,%eax
  4013a0:       83 f8 09                cmp    $0x9,%eax
  4013a3:       76 ea                   jbe    40138f <scramble+0x7>
  4013a5:       8b 44 24 dc             mov    -0x24(%rsp),%eax
  4013a9:       69 c0 44 a6 00 00       imul   $0xa644,%eax,%eax
  4013af:       89 44 24 dc             mov    %eax,-0x24(%rsp)
  4013b3:       8b 44 24 e8             mov    -0x18(%rsp),%eax
  4013b7:       69 c0 d5 50 00 00       imul   $0x50d5,%eax,%eax
  4013bd:       89 44 24 e8             mov    %eax,-0x18(%rsp)
  4013c1:       8b 44 24 e4             mov    -0x1c(%rsp),%eax
  4013c5:       69 c0 00 3a 00 00       imul   $0x3a00,%eax,%eax
  4013cb:       89 44 24 e4             mov    %eax,-0x1c(%rsp)
  4013cf:       8b 44 24 e4             mov    -0x1c(%rsp),%eax
  4013d3:       69 c0 29 9f 00 00       imul   $0x9f29,%eax,%eax
  4013d9:       89 44 24 e4             mov    %eax,-0x1c(%rsp)
  4013dd:       8b 44 24 ec             mov    -0x14(%rsp),%eax
  4013e1:       69 c0 96 16 00 00       imul   $0x1696,%eax,%eax
  4013e7:       89 44 24 ec             mov    %eax,-0x14(%rsp)
  4013eb:       8b 44 24 d4             mov    -0x2c(%rsp),%eax
  4013ef:       69 c0 4d 29 00 00       imul   $0x294d,%eax,%eax
  4013f5:       89 44 24 d4             mov    %eax,-0x2c(%rsp)
  4013f9:       8b 44 24 ec             mov    -0x14(%rsp),%eax
  4013fd:       69 c0 7d c8 00 00       imul   $0xc87d,%eax,%eax
  401403:       89 44 24 ec             mov    %eax,-0x14(%rsp)
  401407:       8b 44 24 d4             mov    -0x2c(%rsp),%eax
  40140b:       69 c0 7e 90 00 00       imul   $0x907e,%eax,%eax
  401411:       89 44 24 d4             mov    %eax,-0x2c(%rsp)
  401415:       8b 44 24 c8             mov    -0x38(%rsp),%eax
  401419:       69 c0 5f c3 00 00       imul   $0xc35f,%eax,%eax
  40141f:       89 44 24 c8             mov    %eax,-0x38(%rsp)
  401423:       8b 44 24 d0             mov    -0x30(%rsp),%eax
  401427:       69 c0 32 43 00 00       imul   $0x4332,%eax,%eax
  40142d:       89 44 24 d0             mov    %eax,-0x30(%rsp)
  401431:       8b 44 24 dc             mov    -0x24(%rsp),%eax
  401435:       69 c0 d9 3f 00 00       imul   $0x3fd9,%eax,%eax
  40143b:       89 44 24 dc             mov    %eax,-0x24(%rsp)
  40143f:       8b 44 24 cc             mov    -0x34(%rsp),%eax
  401443:       69 c0 d7 49 00 00       imul   $0x49d7,%eax,%eax
  401449:       89 44 24 cc             mov    %eax,-0x34(%rsp)
  40144d:       8b 44 24 c8             mov    -0x38(%rsp),%eax
  401451:       69 c0 7a 8c 00 00       imul   $0x8c7a,%eax,%eax
  401457:       89 44 24 c8             mov    %eax,-0x38(%rsp)
  40145b:       8b 44 24 d4             mov    -0x2c(%rsp),%eax
  40145f:       69 c0 f8 0e 00 00       imul   $0xef8,%eax,%eax
  401465:       89 44 24 d4             mov    %eax,-0x2c(%rsp)
  401469:       8b 44 24 e0             mov    -0x20(%rsp),%eax
  40146d:       69 c0 2d 12 00 00       imul   $0x122d,%eax,%eax
  401473:       89 44 24 e0             mov    %eax,-0x20(%rsp)
  401477:       8b 44 24 d0             mov    -0x30(%rsp),%eax
  40147b:       69 c0 16 c6 00 00       imul   $0xc616,%eax,%eax
  401481:       89 44 24 d0             mov    %eax,-0x30(%rsp)
  401485:       8b 44 24 e0             mov    -0x20(%rsp),%eax
  401489:       69 c0 41 48 00 00       imul   $0x4841,%eax,%eax
  40148f:       89 44 24 e0             mov    %eax,-0x20(%rsp)
  401493:       8b 44 24 e4             mov    -0x1c(%rsp),%eax
  401497:       69 c0 44 92 00 00       imul   $0x9244,%eax,%eax
  40149d:       89 44 24 e4             mov    %eax,-0x1c(%rsp)
  4014a1:       8b 44 24 e4             mov    -0x1c(%rsp),%eax
  4014a5:       69 c0 19 5f 00 00       imul   $0x5f19,%eax,%eax
  4014ab:       89 44 24 e4             mov    %eax,-0x1c(%rsp)
  4014af:       8b 44 24 e4             mov    -0x1c(%rsp),%eax
  4014b3:       69 c0 8d 3a 00 00       imul   $0x3a8d,%eax,%eax
  4014b9:       89 44 24 e4             mov    %eax,-0x1c(%rsp)
  4014bd:       8b 44 24 e0             mov    -0x20(%rsp),%eax
  4014c1:       69 c0 30 4a 00 00       imul   $0x4a30,%eax,%eax
  4014c7:       89 44 24 e0             mov    %eax,-0x20(%rsp)
  4014cb:       8b 44 24 dc             mov    -0x24(%rsp),%eax
  4014cf:       69 c0 74 f2 00 00       imul   $0xf274,%eax,%eax
  4014d5:       89 44 24 dc             mov    %eax,-0x24(%rsp)
  4014d9:       8b 44 24 d8             mov    -0x28(%rsp),%eax
  4014dd:       69 c0 04 82 00 00       imul   $0x8204,%eax,%eax
  4014e3:       89 44 24 d8             mov    %eax,-0x28(%rsp)
  4014e7:       8b 44 24 dc             mov    -0x24(%rsp),%eax
  4014eb:       69 c0 82 d5 00 00       imul   $0xd582,%eax,%eax
  4014f1:       89 44 24 dc             mov    %eax,-0x24(%rsp)
  4014f5:       8b 44 24 dc             mov    -0x24(%rsp),%eax
  4014f9:       69 c0 cc 01 00 00       imul   $0x1cc,%eax,%eax
  4014ff:       89 44 24 dc             mov    %eax,-0x24(%rsp)
  401503:       8b 44 24 e0             mov    -0x20(%rsp),%eax
  401507:       69 c0 77 0d 00 00       imul   $0xd77,%eax,%eax
  40150d:       89 44 24 e0             mov    %eax,-0x20(%rsp)
  401511:       8b 44 24 e0             mov    -0x20(%rsp),%eax
  401515:       69 c0 50 d8 00 00       imul   $0xd850,%eax,%eax
  40151b:       89 44 24 e0             mov    %eax,-0x20(%rsp)
  40151f:       8b 44 24 d4             mov    -0x2c(%rsp),%eax
  401523:       69 c0 45 02 00 00       imul   $0x245,%eax,%eax
  401529:       89 44 24 d4             mov    %eax,-0x2c(%rsp)
  40152d:       8b 44 24 dc             mov    -0x24(%rsp),%eax
  401531:       69 c0 5c b6 00 00       imul   $0xb65c,%eax,%eax
  401537:       89 44 24 dc             mov    %eax,-0x24(%rsp)
  40153b:       8b 44 24 d0             mov    -0x30(%rsp),%eax
  40153f:       69 c0 62 b1 00 00       imul   $0xb162,%eax,%eax
  401545:       89 44 24 d0             mov    %eax,-0x30(%rsp)
  401549:       8b 44 24 cc             mov    -0x34(%rsp),%eax
  40154d:       69 c0 2f b8 00 00       imul   $0xb82f,%eax,%eax
  401553:       89 44 24 cc             mov    %eax,-0x34(%rsp)
  401557:       8b 44 24 e0             mov    -0x20(%rsp),%eax
  40155b:       69 c0 fc 80 00 00       imul   $0x80fc,%eax,%eax
  401561:       89 44 24 e0             mov    %eax,-0x20(%rsp)
  401565:       8b 44 24 e8             mov    -0x18(%rsp),%eax
  401569:       69 c0 65 8e 00 00       imul   $0x8e65,%eax,%eax
  40156f:       89 44 24 e8             mov    %eax,-0x18(%rsp)
  401573:       8b 44 24 c8             mov    -0x38(%rsp),%eax
  401577:       69 c0 b2 82 00 00       imul   $0x82b2,%eax,%eax
  40157d:       89 44 24 c8             mov    %eax,-0x38(%rsp)
  401581:       8b 44 24 d4             mov    -0x2c(%rsp),%eax
  401585:       69 c0 ad 44 00 00       imul   $0x44ad,%eax,%eax
  40158b:       89 44 24 d4             mov    %eax,-0x2c(%rsp)
  40158f:       8b 44 24 dc             mov    -0x24(%rsp),%eax
  401593:       69 c0 2e 63 00 00       imul   $0x632e,%eax,%eax
  401599:       89 44 24 dc             mov    %eax,-0x24(%rsp)
  40159d:       8b 44 24 c8             mov    -0x38(%rsp),%eax
  4015a1:       69 c0 19 21 00 00       imul   $0x2119,%eax,%eax
  4015a7:       89 44 24 c8             mov    %eax,-0x38(%rsp)
  4015ab:       8b 44 24 e4             mov    -0x1c(%rsp),%eax
  4015af:       69 c0 8a a1 00 00       imul   $0xa18a,%eax,%eax
  4015b5:       89 44 24 e4             mov    %eax,-0x1c(%rsp)
  4015b9:       8b 44 24 d8             mov    -0x28(%rsp),%eax
  4015bd:       69 c0 95 d8 00 00       imul   $0xd895,%eax,%eax
  4015c3:       89 44 24 d8             mov    %eax,-0x28(%rsp)
  4015c7:       8b 44 24 d4             mov    -0x2c(%rsp),%eax
  4015cb:       69 c0 81 e8 00 00       imul   $0xe881,%eax,%eax
  4015d1:       89 44 24 d4             mov    %eax,-0x2c(%rsp)
  4015d5:       8b 44 24 d8             mov    -0x28(%rsp),%eax
  4015d9:       69 c0 c1 8f 00 00       imul   $0x8fc1,%eax,%eax
  4015df:       89 44 24 d8             mov    %eax,-0x28(%rsp)
  4015e3:       8b 44 24 d0             mov    -0x30(%rsp),%eax
  4015e7:       69 c0 07 1c 00 00       imul   $0x1c07,%eax,%eax
  4015ed:       89 44 24 d0             mov    %eax,-0x30(%rsp)
  4015f1:       8b 44 24 c8             mov    -0x38(%rsp),%eax
  4015f5:       69 c0 47 4d 00 00       imul   $0x4d47,%eax,%eax
  4015fb:       89 44 24 c8             mov    %eax,-0x38(%rsp)
  4015ff:       8b 44 24 cc             mov    -0x34(%rsp),%eax
  401603:       69 c0 dd cc 00 00       imul   $0xccdd,%eax,%eax
  401609:       89 44 24 cc             mov    %eax,-0x34(%rsp)
  40160d:       8b 44 24 d4             mov    -0x2c(%rsp),%eax
  401611:       69 c0 89 2f 00 00       imul   $0x2f89,%eax,%eax
  401617:       89 44 24 d4             mov    %eax,-0x2c(%rsp)
  40161b:       8b 44 24 c8             mov    -0x38(%rsp),%eax
  40161f:       69 c0 2d cc 00 00       imul   $0xcc2d,%eax,%eax
  401625:       89 44 24 c8             mov    %eax,-0x38(%rsp)
  401629:       8b 44 24 cc             mov    -0x34(%rsp),%eax
  40162d:       69 c0 b8 f5 00 00       imul   $0xf5b8,%eax,%eax
  401633:       89 44 24 cc             mov    %eax,-0x34(%rsp)
  401637:       8b 44 24 dc             mov    -0x24(%rsp),%eax
  40163b:       69 c0 29 e8 00 00       imul   $0xe829,%eax,%eax
  401641:       89 44 24 dc             mov    %eax,-0x24(%rsp)
  401645:       8b 44 24 dc             mov    -0x24(%rsp),%eax
  401649:       69 c0 69 60 00 00       imul   $0x6069,%eax,%eax
  40164f:       89 44 24 dc             mov    %eax,-0x24(%rsp)
  401653:       8b 44 24 e8             mov    -0x18(%rsp),%eax
  401657:       69 c0 9c 71 00 00       imul   $0x719c,%eax,%eax
  40165d:       89 44 24 e8             mov    %eax,-0x18(%rsp)
  401661:       8b 44 24 e8             mov    -0x18(%rsp),%eax
  401665:       69 c0 1a 28 00 00       imul   $0x281a,%eax,%eax
  40166b:       89 44 24 e8             mov    %eax,-0x18(%rsp)
  40166f:       8b 44 24 ec             mov    -0x14(%rsp),%eax
  401673:       69 c0 f3 33 00 00       imul   $0x33f3,%eax,%eax
  401679:       89 44 24 ec             mov    %eax,-0x14(%rsp)
  40167d:       8b 44 24 e4             mov    -0x1c(%rsp),%eax
  401681:       69 c0 6c 2a 00 00       imul   $0x2a6c,%eax,%eax
  401687:       89 44 24 e4             mov    %eax,-0x1c(%rsp)
  40168b:       8b 44 24 e4             mov    -0x1c(%rsp),%eax
  40168f:       69 c0 51 ec 00 00       imul   $0xec51,%eax,%eax
  401695:       89 44 24 e4             mov    %eax,-0x1c(%rsp)
  401699:       8b 44 24 e0             mov    -0x20(%rsp),%eax
  40169d:       69 c0 8a 4c 00 00       imul   $0x4c8a,%eax,%eax
  4016a3:       89 44 24 e0             mov    %eax,-0x20(%rsp)
  4016a7:       8b 44 24 d4             mov    -0x2c(%rsp),%eax
  4016ab:       69 c0 63 dd 00 00       imul   $0xdd63,%eax,%eax
  4016b1:       89 44 24 d4             mov    %eax,-0x2c(%rsp)
  4016b5:       8b 44 24 d0             mov    -0x30(%rsp),%eax
  4016b9:       69 c0 ca ca 00 00       imul   $0xcaca,%eax,%eax
  4016bf:       89 44 24 d0             mov    %eax,-0x30(%rsp)
  4016c3:       8b 44 24 dc             mov    -0x24(%rsp),%eax
  4016c7:       69 c0 5d 44 00 00       imul   $0x445d,%eax,%eax
  4016cd:       89 44 24 dc             mov    %eax,-0x24(%rsp)
  4016d1:       8b 44 24 d8             mov    -0x28(%rsp),%eax
  4016d5:       69 c0 b7 17 00 00       imul   $0x17b7,%eax,%eax
  4016db:       89 44 24 d8             mov    %eax,-0x28(%rsp)
  4016df:       8b 44 24 d0             mov    -0x30(%rsp),%eax
  4016e3:       69 c0 b5 1b 00 00       imul   $0x1bb5,%eax,%eax
  4016e9:       89 44 24 d0             mov    %eax,-0x30(%rsp)
  4016ed:       8b 44 24 d8             mov    -0x28(%rsp),%eax
  4016f1:       69 c0 7a 8f 00 00       imul   $0x8f7a,%eax,%eax
  4016f7:       89 44 24 d8             mov    %eax,-0x28(%rsp)
  4016fb:       8b 44 24 e0             mov    -0x20(%rsp),%eax
  4016ff:       69 c0 f9 2e 00 00       imul   $0x2ef9,%eax,%eax
  401705:       89 44 24 e0             mov    %eax,-0x20(%rsp)
  401709:       8b 44 24 d8             mov    -0x28(%rsp),%eax
  40170d:       69 c0 0c 35 00 00       imul   $0x350c,%eax,%eax
  401713:       89 44 24 d8             mov    %eax,-0x28(%rsp)
  401717:       8b 44 24 cc             mov    -0x34(%rsp),%eax
  40171b:       69 c0 50 09 00 00       imul   $0x950,%eax,%eax
  401721:       89 44 24 cc             mov    %eax,-0x34(%rsp)
  401725:       8b 44 24 d0             mov    -0x30(%rsp),%eax
  401729:       69 c0 fd 81 00 00       imul   $0x81fd,%eax,%eax
  40172f:       89 44 24 d0             mov    %eax,-0x30(%rsp)
  401733:       8b 44 24 cc             mov    -0x34(%rsp),%eax
  401737:       69 c0 8c 3a 00 00       imul   $0x3a8c,%eax,%eax
  40173d:       89 44 24 cc             mov    %eax,-0x34(%rsp)
  401741:       8b 44 24 dc             mov    -0x24(%rsp),%eax
  401745:       69 c0 b6 4f 00 00       imul   $0x4fb6,%eax,%eax
  40174b:       89 44 24 dc             mov    %eax,-0x24(%rsp)
  40174f:       8b 44 24 c8             mov    -0x38(%rsp),%eax
  401753:       69 c0 4a f3 00 00       imul   $0xf34a,%eax,%eax
  401759:       89 44 24 c8             mov    %eax,-0x38(%rsp)
  40175d:       8b 44 24 cc             mov    -0x34(%rsp),%eax
  401761:       69 c0 fd 43 00 00       imul   $0x43fd,%eax,%eax
  401767:       89 44 24 cc             mov    %eax,-0x34(%rsp)
  40176b:       8b 44 24 e4             mov    -0x1c(%rsp),%eax
  40176f:       69 c0 24 7d 00 00       imul   $0x7d24,%eax,%eax
  401775:       89 44 24 e4             mov    %eax,-0x1c(%rsp)
  401779:       8b 44 24 ec             mov    -0x14(%rsp),%eax
  40177d:       69 c0 6d b4 00 00       imul   $0xb46d,%eax,%eax
  401783:       89 44 24 ec             mov    %eax,-0x14(%rsp)
  401787:       ba 00 00 00 00          mov    $0x0,%edx
  40178c:       b8 00 00 00 00          mov    $0x0,%eax
  401791:       eb 0b                   jmp    40179e <scramble+0x416>
  401793:       89 d1                   mov    %edx,%ecx
  401795:       8b 4c 8c c8             mov    -0x38(%rsp,%rcx,4),%ecx
  401799:       01 c8                   add    %ecx,%eax
  40179b:       83 c2 01                add    $0x1,%edx
  40179e:       83 fa 09                cmp    $0x9,%edx
  4017a1:       76 f0                   jbe    401793 <scramble+0x40b>
  4017a3:       f3 c3                   repz retq
  4017a5:       90                      nop
  4017a6:       90                      nop
  4017a7:       90                      nop

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

000000000040184c <hexmatch>:
  40184c:       41 54                   push   %r12
  40184e:       55                      push   %rbp
  40184f:       53                      push   %rbx
  401850:       48 83 c4 80             add    $0xffffffffffffff80,%rsp
  401854:       41 89 fc                mov    %edi,%r12d
  401857:       48 89 f5                mov    %rsi,%rbp
  40185a:       64 48 8b 04 25 28 00    mov    %fs:0x28,%rax
  401861:       00 00
  401863:       48 89 44 24 78          mov    %rax,0x78(%rsp)
  401868:       31 c0                   xor    %eax,%eax
  40186a:       e8 41 f5 ff ff          callq  400db0 <random@plt>
  40186f:       48 89 c1                mov    %rax,%rcx
  401872:       48 ba 0b d7 a3 70 3d    movabs $0xa3d70a3d70a3d70b,%rdx
  401879:       0a d7 a3
  40187c:       48 f7 ea                imul   %rdx
  40187f:       48 01 ca                add    %rcx,%rdx
  401882:       48 c1 fa 06             sar    $0x6,%rdx
  401886:       48 89 c8                mov    %rcx,%rax
  401889:       48 c1 f8 3f             sar    $0x3f,%rax
  40188d:       48 29 c2                sub    %rax,%rdx
  401890:       48 8d 04 92             lea    (%rdx,%rdx,4),%rax
  401894:       48 8d 04 80             lea    (%rax,%rax,4),%rax
  401898:       48 c1 e0 02             shl    $0x2,%rax
  40189c:       48 29 c1                sub    %rax,%rcx
  40189f:       48 8d 1c 0c             lea    (%rsp,%rcx,1),%rbx
  4018a3:       45 89 e0                mov    %r12d,%r8d
  4018a6:       b9 e2 30 40 00          mov    $0x4030e2,%ecx
  4018ab:       48 c7 c2 ff ff ff ff    mov    $0xffffffffffffffff,%rdx
  4018b2:       be 01 00 00 00          mov    $0x1,%esi
  4018b7:       48 89 df                mov    %rbx,%rdi
  4018ba:       b8 00 00 00 00          mov    $0x0,%eax
  4018bf:       e8 ac f5 ff ff          callq  400e70 <__sprintf_chk@plt>
  4018c4:       ba 09 00 00 00          mov    $0x9,%edx
  4018c9:       48 89 de                mov    %rbx,%rsi
  4018cc:       48 89 ef                mov    %rbp,%rdi
  4018cf:       e8 cc f3 ff ff          callq  400ca0 <strncmp@plt>
  4018d4:       85 c0                   test   %eax,%eax
  4018d6:       0f 94 c0                sete   %al
  4018d9:       0f b6 c0                movzbl %al,%eax
  4018dc:       48 8b 74 24 78          mov    0x78(%rsp),%rsi
  4018e1:       64 48 33 34 25 28 00    xor    %fs:0x28,%rsi
  4018e8:       00 00
  4018ea:       74 05                   je     4018f1 <hexmatch+0xa5>
  4018ec:       e8 ef f3 ff ff          callq  400ce0 <__stack_chk_fail@plt>
  4018f1:       48 83 ec 80             sub    $0xffffffffffffff80,%rsp
  4018f5:       5b                      pop    %rbx
  4018f6:       5d                      pop    %rbp
  4018f7:       41 5c                   pop    %r12
  4018f9:       c3                      retq

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

